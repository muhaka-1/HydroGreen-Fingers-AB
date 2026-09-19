#include "mqtt_task.h"

#include "wifi_manager.h"
#include "mqtt_client.h"
#include "json_serializer.h"

#include "sensor_types.h"

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MQTT_TASK";

/* ============================================================================
 * MQTT TASK
 * ========================================================================== */

void mqtt_task(void *pvParameters)
{
    (void)pvParameters;

    ESP_LOGI(
        TAG,
        "MQTT Task started on Core %d",
        xPortGetCoreID()
    );

    /* ------------------------------------------------------------------------
     * 1. Initialize Wi-Fi
     * ---------------------------------------------------------------------- */

    esp_err_t wifi_result =
        wifi_manager_init();

    if (wifi_result != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "Wi-Fi initialization failed: %s",
            esp_err_to_name(wifi_result)
        );

        /*
         * Do not terminate the task.
         * Wi-Fi manager will continue reconnect attempts.
         */
    }

    /* ------------------------------------------------------------------------
     * 2. Start MQTT
     * ---------------------------------------------------------------------- */

    esp_err_t mqtt_result =
        mqtt_client_module_start();

    if (mqtt_result != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "MQTT initialization failed: %s",
            esp_err_to_name(mqtt_result)
        );
    }

    /* ------------------------------------------------------------------------
     * 3. Telemetry buffer
     * ---------------------------------------------------------------------- */

    sensor_telemetry_t received_data;

    char payload_buffer[512];

    /* ------------------------------------------------------------------------
     * 4. Main MQTT loop
     * ---------------------------------------------------------------------- */

    while (1)
    {
        if (s_sensor_queue == NULL)
        {
            ESP_LOGW(
                TAG,
                "Sensor queue is NULL"
            );

            vTaskDelay(
                pdMS_TO_TICKS(1000)
            );

            continue;
        }

        /*
         * Wait for sensor telemetry.
         */
        if (xQueueReceive(
                s_sensor_queue,
                &received_data,
                portMAX_DELAY) == pdPASS)
        {
            /*
             * Serialize sensor data to JSON.
             */
            bool serialized =
                serialize_telemetry_json(
                    &received_data,
                    payload_buffer,
                    sizeof(payload_buffer)
                );

            if (!serialized)
            {
                ESP_LOGE(
                    TAG,
                    "Failed to serialize telemetry"
                );

                continue;
            }

            ESP_LOGI(
                TAG,
                "Telemetry ready: %s",
                payload_buffer
            );

            /*
             * Publish telemetry.
             */
            esp_err_t publish_result =
                mqtt_client_module_publish(
                    MQTT_TOPIC_TELEMETRY,
                    payload_buffer
                );

            if (publish_result != ESP_OK)
            {
                ESP_LOGW(
                    TAG,
                    "Telemetry publish failed: %s",
                    esp_err_to_name(publish_result)
                );
            }
        }
    }
}