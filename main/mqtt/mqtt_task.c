#include "mqtt_task.h"
#include "wifi_manager.h"
#include "hydro_mqtt_client.h"
#include "json_serializer.h"
#include "sensor_types.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MQTT_TASK";

void mqtt_task(void *pvParameters)
{
    ESP_LOGI(
        TAG,
        "MQTT Task startad på FreeRTOS Core %d",
        xPortGetCoreID()
    );

    esp_err_t wifi_err = wifi_manager_init();

    if (wifi_err != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "Wi-Fi kunde inte initieras: %s",
            esp_err_to_name(wifi_err)
        );

        vTaskDelete(NULL);
        return;
    }

    if (!wifi_manager_is_connected())
    {
        ESP_LOGE(
            TAG,
            "Wi-Fi är inte anslutet - MQTT startas inte"
        );

        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(
        TAG,
        "Wi-Fi är anslutet. Startar MQTT..."
    );

    esp_err_t mqtt_err = mqtt_client_module_start();

    if (mqtt_err != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "MQTT kunde inte startas: %s",
            esp_err_to_name(mqtt_err)
        );

        vTaskDelete(NULL);
        return;
    }

    // Vänta på MQTT connection event
    while (!mqtt_client_module_is_connected())
    {
        ESP_LOGI(
            TAG,
            "Väntar på MQTT broker..."
        );

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    ESP_LOGI(
        TAG,
        "MQTT är anslutet - publicerar testmeddelande"
    );

    const char *payload =
        "{\"device\":\"microhydros-01\",\"status\":\"online\"}";

    mqtt_client_module_publish(
        MQTT_TOPIC_STATUS,
        payload
    );

    while (1) {
         vTaskDelay(pdMS_TO_TICKS(1000));
         /*
        // Väntar på att sensor_task ska posta telemetridata i kön
        if (s_sensor_queue != NULL && xQueueReceive(s_sensor_queue, &received_data, portMAX_DELAY) == pdPASS) {
            if (serialize_telemetry_json(&received_data, payload_buffer, sizeof(payload_buffer))) {
                ESP_LOGI(TAG, "Mottog paket från SensorTask: %s", payload_buffer);
                mqtt_client_module_publish(MQTT_TOPIC_TELEMETRY, payload_buffer);
            }
        }*/
    }
}
