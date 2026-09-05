#include "wifi_manager.h"
#include "esp_log.h"
#include <stdbool.h>

static const char *TAG = "WIFI_MANAGER";
static bool s_is_connected = false;

esp_err_t wifi_manager_init(void) {
    // TODO: Mohammad implementerar esp_wifi_init, esp_wifi_set_config och event handlers
    ESP_LOGI(TAG, "Wi-Fi Manager initierad för SSID: %s (Placeholder för Mohammad)", WIFI_SSID_DEFAULT);
    s_is_connected = true;
    return ESP_OK;
}

bool wifi_manager_is_connected(void) {
    return s_is_connected;
}
