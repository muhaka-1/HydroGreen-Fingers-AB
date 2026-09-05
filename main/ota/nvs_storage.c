#include "nvs_storage.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <string.h>

static const char *TAG = "NVS_STORAGE";

esp_err_t nvs_storage_save_string(const char *key, const char *value) {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) return err;

    err = nvs_set_str(my_handle, key, value);
    if (err == ESP_OK) {
        err = nvs_commit(my_handle);
    }
    nvs_close(my_handle);
    ESP_LOGI(TAG, "Sparade NVS [%s] = %s", key, value);
    return err;
}

esp_err_t nvs_storage_read_string(const char *key, char *out_val, size_t max_len) {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err != ESP_OK) return err;

    err = nvs_get_str(my_handle, key, out_val, &max_len);
    nvs_close(my_handle);
    return err;
}
