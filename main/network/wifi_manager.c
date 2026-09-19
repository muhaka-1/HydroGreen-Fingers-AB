#include "wifi_manager.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include <string.h>

static const char *TAG = "WIFI_MANAGER";

/* ============================================================================
 * WIFI STATE
 * ========================================================================== */

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static EventGroupHandle_t s_wifi_event_group = NULL;

static bool s_is_connected = false;

static int s_retry_count = 0;

#define WIFI_MAX_RETRY 10

/* ============================================================================
 * WIFI EVENT HANDLER
 * ========================================================================== */

static void wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data)
{
    if (event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(
            TAG,
            "Wi-Fi station started"
        );

        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        s_is_connected = false;

        if (s_retry_count < WIFI_MAX_RETRY)
        {
            esp_wifi_connect();

            s_retry_count++;

            ESP_LOGW(
                TAG,
                "Wi-Fi reconnect attempt %d/%d",
                s_retry_count,
                WIFI_MAX_RETRY
            );
        }
        else
        {
            xEventGroupSetBits(
                s_wifi_event_group,
                WIFI_FAIL_BIT
            );

            ESP_LOGE(
                TAG,
                "Wi-Fi connection failed"
            );
        }
    }
    else if (event_base == IP_EVENT &&
             event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event =
            (ip_event_got_ip_t *)event_data;

        s_retry_count = 0;

        s_is_connected = true;

        ESP_LOGI(
            TAG,
            "Wi-Fi connected, IP: " IPSTR,
            IP2STR(&event->ip_info.ip)
        );

        xEventGroupSetBits(
            s_wifi_event_group,
            WIFI_CONNECTED_BIT
        );
    }
}

/* ============================================================================
 * WIFI INITIALIZATION
 * ========================================================================== */

esp_err_t wifi_manager_init(void)
{
    if (s_is_connected)
    {
        ESP_LOGI(
            TAG,
            "Wi-Fi already connected"
        );

        return ESP_OK;
    }

    if (s_wifi_event_group == NULL)
    {
        s_wifi_event_group = xEventGroupCreate();

        if (s_wifi_event_group == NULL)
        {
            ESP_LOGE(
                TAG,
                "Failed to create Wi-Fi event group"
            );

            return ESP_ERR_NO_MEM;
        }
    }

    ESP_ERROR_CHECK(
        esp_netif_init()
    );

    ESP_ERROR_CHECK(
        esp_event_loop_create_default()
    );

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg =
        WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(
        esp_wifi_init(&cfg)
    );

    ESP_ERROR_CHECK(
        esp_event_handler_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            NULL
        )
    );

    ESP_ERROR_CHECK(
        esp_event_handler_register(
            IP_EVENT,
            IP_EVENT_STA_GOT_IP,
            &wifi_event_handler,
            NULL
        )
    );

    wifi_config_t wifi_config = {0};

    strncpy(
        (char *)wifi_config.sta.ssid,
        WIFI_SSID_DEFAULT,
        sizeof(wifi_config.sta.ssid) - 1
    );

    strncpy(
        (char *)wifi_config.sta.password,
        WIFI_PASS_DEFAULT,
        sizeof(wifi_config.sta.password) - 1
    );

    wifi_config.sta.threshold.authmode =
        WIFI_AUTH_OPEN;

    ESP_ERROR_CHECK(
        esp_wifi_set_mode(WIFI_MODE_STA)
    );

    ESP_ERROR_CHECK(
        esp_wifi_set_config(
            WIFI_IF_STA,
            &wifi_config
        )
    );

    ESP_ERROR_CHECK(
        esp_wifi_start()
    );

    ESP_LOGI(
        TAG,
        "Wi-Fi initialization complete"
    );

    EventBits_t bits = xEventGroupWaitBits(
        s_wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        pdMS_TO_TICKS(15000)
    );

    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(
            TAG,
            "Wi-Fi connected successfully"
        );

        return ESP_OK;
    }

    ESP_LOGE(
        TAG,
        "Wi-Fi connection timeout"
    );

    return ESP_ERR_TIMEOUT;
}

/* ============================================================================
 * WIFI STATUS
 * ========================================================================== */

bool wifi_manager_is_connected(void)
{
    return s_is_connected;
}