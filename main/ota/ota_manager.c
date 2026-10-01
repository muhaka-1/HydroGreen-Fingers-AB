#include "ota_manager.h"
#include "hydro_mqtt_client.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_app_desc.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_system.h"
#include "mbedtls/sha256.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "OTA_MANAGER";

// ---------------------------------------------------------------------------
// Intern state
// ---------------------------------------------------------------------------
static esp_ota_handle_t        s_ota_handle    = 0;
static const esp_partition_t  *s_update_part   = NULL;
static volatile bool           s_in_progress   = false;
static size_t                  s_bytes_written = 0;

static char s_url[OTA_MAX_URL_LEN + 1];
static char s_sha256_expected[65];
static bool s_sha256_check = false;

// ---------------------------------------------------------------------------
// Hjälpfunktion: publicera OTA-status till MQTT (best effort)
// ---------------------------------------------------------------------------
static void ota_publish_status(const char *state, int progress_pct, const char *detail)
{
    char payload[192];
    snprintf(payload, sizeof(payload),
             "{\"device\":\"" MQTT_CLIENT_ID "\",\"ota\":\"%s\",\"progress\":%d,\"detail\":\"%s\"}",
             state, progress_pct, detail ? detail : "");

    if (mqtt_client_module_is_connected()) {
        mqtt_client_module_publish(MQTT_TOPIC_STATUS, payload);
    }
}

static bool hex_equals_ignore_case(const char *a, const char *b, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Init / rollback
// ---------------------------------------------------------------------------
esp_err_t ota_manager_init(void)
{
    const esp_partition_t *running = esp_ota_get_running_partition();
    const esp_app_desc_t *desc = esp_app_get_description();

    ESP_LOGI(TAG, "Körande partition: %s vid offset 0x%lx",
             running ? running->label : "okänd",
             running ? (unsigned long)running->address : 0UL);
    ESP_LOGI(TAG, "Firmware: %s v%s (byggd %s %s)",
             desc->project_name, desc->version, desc->date, desc->time);

    const esp_partition_t *next = esp_ota_get_next_update_partition(NULL);
    if (next == NULL) {
        ESP_LOGE(TAG, "Ingen OTA-partition hittades - kontrollera partitionstabellen (ota_0/ota_1)");
        return ESP_ERR_NOT_FOUND;
    }
    ESP_LOGI(TAG, "Nästa OTA-partition: %s (0x%lx)", next->label, (unsigned long)next->address);

    esp_ota_img_states_t state;
    if (running && esp_ota_get_state_partition(running, &state) == ESP_OK &&
        state == ESP_OTA_IMG_PENDING_VERIFY) {
        ESP_LOGW(TAG, "Ny firmware väntar på verifiering - anropa ota_manager_mark_valid() när systemet fungerar");
    }
    return ESP_OK;
}

esp_err_t ota_manager_mark_valid(void)
{
    static bool s_done = false;
    if (s_done) return ESP_OK;               // redan hanterat sedan uppstart

    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_ota_img_states_t state;

    // Endast en nyss OTA-uppdaterad image (PENDING_VERIFY) behöver markeras.
    // Från factory eller redan verifierad image finns inget att göra.
    if (running == NULL ||
        esp_ota_get_state_partition(running, &state) != ESP_OK ||
        state != ESP_OTA_IMG_PENDING_VERIFY) {
        s_done = true;
        return ESP_OK;
    }

    esp_err_t err = esp_ota_mark_app_valid_cancel_rollback();
    if (err == ESP_OK) {
        s_done = true;
        ESP_LOGI(TAG, "Ny firmware verifierad och markerad som giltig");
    } else {
        ESP_LOGW(TAG, "Kunde inte markera firmware som giltig: %s", esp_err_to_name(err));
    }
    return err;
}

// ---------------------------------------------------------------------------
// Chunk-API
// ---------------------------------------------------------------------------
esp_err_t ota_manager_begin(void)
{
    s_update_part = esp_ota_get_next_update_partition(NULL);
    if (s_update_part == NULL) {
        ESP_LOGE(TAG, "Ingen OTA-partition tillgänglig");
        return ESP_ERR_NOT_FOUND;
    }

    esp_err_t err = esp_ota_begin(s_update_part, OTA_SIZE_UNKNOWN, &s_ota_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_begin() misslyckades: %s", esp_err_to_name(err));
        s_ota_handle = 0;
        return err;
    }
    s_bytes_written = 0;
    ESP_LOGI(TAG, "OTA startad mot partition %s", s_update_part->label);
    return ESP_OK;
}

esp_err_t ota_manager_write_chunk(const uint8_t *data, size_t length)
{
    if (s_ota_handle == 0) return ESP_ERR_INVALID_STATE;
    if (data == NULL || length == 0) return ESP_ERR_INVALID_ARG;

    esp_err_t err = esp_ota_write(s_ota_handle, data, length);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_write() misslyckades: %s", esp_err_to_name(err));
        return err;
    }
    s_bytes_written += length;
    return ESP_OK;
}

esp_err_t ota_manager_finish(void)
{
    if (s_ota_handle == 0 || s_update_part == NULL) return ESP_ERR_INVALID_STATE;

    esp_err_t err = esp_ota_end(s_ota_handle);   // validerar image (magic, checksum, ev. signatur)
    s_ota_handle = 0;
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_end() misslyckades (ogiltig image?): %s", esp_err_to_name(err));
        return err;
    }

    err = esp_ota_set_boot_partition(s_update_part);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_set_boot_partition() misslyckades: %s", esp_err_to_name(err));
        return err;
    }
    ESP_LOGI(TAG, "OTA uppdatering slutförd (%u bytes). Boot-partition: %s",
             (unsigned)s_bytes_written, s_update_part->label);
    return ESP_OK;
}

void ota_manager_abort(void)
{
    if (s_ota_handle != 0) {
        esp_ota_abort(s_ota_handle);
        s_ota_handle = 0;
        ESP_LOGW(TAG, "OTA avbruten");
    }
}

bool ota_manager_in_progress(void)
{
    return s_in_progress;
}

// ---------------------------------------------------------------------------
// Download-task
// ---------------------------------------------------------------------------
static void ota_fail(const char *reason, esp_http_client_handle_t client)
{
    ESP_LOGE(TAG, "OTA misslyckades: %s", reason);
    ota_manager_abort();
    if (client) {
        esp_http_client_close(client);
        esp_http_client_cleanup(client);
    }
    ota_publish_status("failed", 0, reason);
    s_in_progress = false;
    vTaskDelete(NULL);
}

static void ota_task(void *arg)
{
    (void)arg;
    ota_publish_status("started", 0, "");

    esp_http_client_config_t cfg = {
        .url = s_url,
        .crt_bundle_attach = esp_crt_bundle_attach,   // verifierar servercertifikat
        .timeout_ms = 10000,
        .keep_alive_enable = true,
        .buffer_size = 2048,       // GitHub-redirect har lång signerad URL
        .buffer_size_tx = 1024,
    };
    esp_http_client_handle_t client = esp_http_client_init(&cfg);
    if (client == NULL) ota_fail("http_init", NULL);

    int content_len = 0, status = 0;
    for (int hop = 0; hop < 5; hop++) {          // följ upp till 5 omdirigeringar
        if (esp_http_client_open(client, 0) != ESP_OK) ota_fail("http_open", client);
        content_len = esp_http_client_fetch_headers(client);
        status = esp_http_client_get_status_code(client);
        if (status == 301 || status == 302 || status == 303 || status == 307 || status == 308) {
            ESP_LOGI(TAG, "Omdirigering (%d), följer...", status);
            if (esp_http_client_set_redirection(client) != ESP_OK) ota_fail("redirect", client);
            esp_http_client_close(client);
            continue;
        }
        break;
    }
    if (status != 200) ota_fail("http_status", client);
    ESP_LOGI(TAG, "Laddar ner firmware (%d bytes) från %s", content_len, s_url);

    if (ota_manager_begin() != ESP_OK) ota_fail("ota_begin", client);

    mbedtls_sha256_context sha;
    mbedtls_sha256_init(&sha);
    mbedtls_sha256_starts(&sha, 0);

    static uint8_t buf[1024];
    int total = 0, last_pct = -10;

    while (1) {
        int n = esp_http_client_read(client, (char *)buf, sizeof(buf));
        if (n < 0) { mbedtls_sha256_free(&sha); ota_fail("http_read", client); }
        if (n == 0) {
            if (esp_http_client_is_complete_data_received(client)) break;
            mbedtls_sha256_free(&sha);
            ota_fail("connection_closed", client);
        }

        mbedtls_sha256_update(&sha, buf, n);
        if (ota_manager_write_chunk(buf, n) != ESP_OK) {
            mbedtls_sha256_free(&sha);
            ota_fail("flash_write", client);
        }
        total += n;

        if (content_len > 0) {
            int pct = (int)((int64_t)total * 100 / content_len);
            if (pct >= last_pct + 10) {
                last_pct = pct;
                ESP_LOGI(TAG, "OTA framsteg: %d%%", pct);
                ota_publish_status("downloading", pct, "");
            }
        }
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);

    uint8_t hash[32];
    mbedtls_sha256_finish(&sha, hash);
    mbedtls_sha256_free(&sha);

    if (s_sha256_check) {
        char hex[65];
        for (int i = 0; i < 32; i++) sprintf(&hex[i * 2], "%02x", hash[i]);
        if (!hex_equals_ignore_case(hex, s_sha256_expected, 64)) {
            ESP_LOGE(TAG, "SHA-256 mismatch! fick %s", hex);
            ota_fail("sha256_mismatch", NULL);
        }
        ESP_LOGI(TAG, "SHA-256 verifierad");
    }

    if (ota_manager_finish() != ESP_OK) ota_fail("image_invalid", NULL);

    ota_publish_status("success", 100, "rebooting");
    ESP_LOGI(TAG, "Startar om om 2 sekunder...");
    vTaskDelay(pdMS_TO_TICKS(2000));   // ge MQTT tid att skicka status
    esp_restart();
}

// ---------------------------------------------------------------------------
// Publikt: starta uppdatering
// ---------------------------------------------------------------------------
esp_err_t ota_manager_start_update(const char *url, const char *sha256_hex)
{
    if (url == NULL || strncmp(url, OTA_URL_REQUIRED_PREFIX, strlen(OTA_URL_REQUIRED_PREFIX)) != 0) {
        ESP_LOGE(TAG, "OTA-URL måste börja med %s", OTA_URL_REQUIRED_PREFIX);
        ota_publish_status("rejected", 0, "url_must_be_https");
        return ESP_ERR_INVALID_ARG;
    }
    if (strlen(url) > OTA_MAX_URL_LEN) {
        ota_publish_status("rejected", 0, "url_too_long");
        return ESP_ERR_INVALID_ARG;
    }
    if (sha256_hex != NULL && strlen(sha256_hex) != 64) {
        ota_publish_status("rejected", 0, "bad_sha256");
        return ESP_ERR_INVALID_ARG;
    }
    if (s_in_progress) {
        ESP_LOGW(TAG, "OTA pågår redan");
        return ESP_ERR_INVALID_STATE;
    }

    strncpy(s_url, url, sizeof(s_url) - 1);
    s_url[sizeof(s_url) - 1] = '\0';
    s_sha256_check = (sha256_hex != NULL);
    if (s_sha256_check) {
        memcpy(s_sha256_expected, sha256_hex, 64);
        s_sha256_expected[64] = '\0';
    }

    s_in_progress = true;
    if (xTaskCreate(ota_task, "ota_task", OTA_TASK_STACK_SIZE, NULL, OTA_TASK_PRIORITY, NULL) != pdPASS) {
        s_in_progress = false;
        ESP_LOGE(TAG, "Kunde inte skapa OTA-task");
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}