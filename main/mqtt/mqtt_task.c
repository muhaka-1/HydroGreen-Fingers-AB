#include "mqtt_task.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "json_serializer.h"
#include "sensor_types.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MQTT_TASK";

void mqtt_task(void *pvParameters) {
    ESP_LOGI(TAG, "MQTT Task startad på FreeRTOS Core %d (Prioritet: 1)", xPortGetCoreID());

    // 1. Initialisera Wi-Fi
    wifi_manager_init();

    // 2. Starta MQTT
    mqtt_client_module_start();

    sensor_telemetry_t received_data;
    char payload_buffer[256];

    while (1) {
        // Väntar på att sensor_task ska posta telemetridata i kön
        if (s_sensor_queue != NULL && xQueueReceive(s_sensor_queue, &received_data, portMAX_DELAY) == pdPASS) {
            if (serialize_telemetry_json(&received_data, payload_buffer, sizeof(payload_buffer))) {
                ESP_LOGI(TAG, "Mottog paket från SensorTask: %s", payload_buffer);
                mqtt_client_module_publish(MQTT_TOPIC_TELEMETRY, payload_buffer);
            }
        }
    }
}
