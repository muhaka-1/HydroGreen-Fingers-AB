#include "mqtt_client.h"
#include "esp_log.h"

static const char *TAG = "MQTT_CLIENT";

esp_err_t mqtt_client_module_start(void) {
    // TODO: IoT Engineer implementerar esp-mqtt anslutning och event handlers här
    ESP_LOGI(TAG, "mqtt_client_module_start() anropad (Placeholder för IoT Engineer)");
    return ESP_OK;
}

esp_err_t mqtt_client_module_publish(const char *topic, const char *payload) {
    // TODO: IoT Engineer implementerar publicering till broker
    return ESP_OK;
}
