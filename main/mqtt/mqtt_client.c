#include "mqtt_client.h"
#include "esp_log.h"

static const char *TAG = "MQTT_CLIENT";

esp_err_t mqtt_client_module_start(void) {
    // TODO: Mohammad implementerar esp_mqtt_client_init och start
    ESP_LOGI(TAG, "MQTT Klient ansluter till %s (Placeholder för Mohammad)", MQTT_BROKER_URI);
    return ESP_OK;
}

esp_err_t mqtt_client_module_publish(const char *topic, const char *payload) {
    // TODO: Mohammad implementerar esp_mqtt_client_publish
    ESP_LOGI(TAG, "[MQTT PUB -> %s]: %s", topic, payload);
    return ESP_OK;
}
