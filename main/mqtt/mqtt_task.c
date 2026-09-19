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

    // ============================================================
    // 1. Initiera Wi-Fi
    // ============================================================

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

    // Vänta tills Wi-Fi har fått IP
    while (!wifi_manager_is_connected())
    {
        ESP_LOGI(TAG, "Väntar på Wi-Fi...");

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    ESP_LOGI(
        TAG,
        "Wi-Fi är anslutet. Startar MQTT..."
    );

    // ============================================================
    // 2. Starta MQTT
    // ============================================================

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

    // Vänta på MQTT connection
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
        "MQTT anslutet!"
    );

    // ============================================================
    // 3. Publicera online-status
    // ============================================================

    const char *status_payload =
        "{\"device\":\"microhydros-01\",\"status\":\"online\"}";

    mqtt_client_module_publish(
        MQTT_TOPIC_STATUS,
        status_payload
    );

    ESP_LOGI(
        TAG,
        "Online-status publicerad"
    );

    // ============================================================
    // 4. Förbered sensor-data och JSON-buffer
    // ============================================================

    sensor_telemetry_t received_data;

    char payload_buffer[512];

    // ============================================================
    // 5. Huvudloop
    //    SensorTask -> Queue -> JSON -> MQTT
    // ============================================================

    while (1)
    {
        // --------------------------------------------------------
        // Kontrollera MQTT-anslutning
        // --------------------------------------------------------

        if (!mqtt_client_module_is_connected())
        {
            ESP_LOGW(
                TAG,
                "MQTT inte anslutet - väntar på reconnect..."
            );

            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        // --------------------------------------------------------
        // Hämta sensordata från FreeRTOS Queue
        // --------------------------------------------------------

        if (s_sensor_queue != NULL)
        {
            if (xQueueReceive(
                    s_sensor_queue,
                    &received_data,
                    pdMS_TO_TICKS(1000)
                ) == pdPASS)
            {
                // ------------------------------------------------
                // Serialisera sensordata till JSON
                // ------------------------------------------------

                bool json_ok = serialize_telemetry_json(
                    &received_data,
                    payload_buffer,
                    sizeof(payload_buffer)
                );

                if (!json_ok)
                {
                    ESP_LOGE(
                        TAG,
                        "Kunde inte skapa telemetry JSON"
                    );

                    continue;
                }

                // ------------------------------------------------
                // Logga JSON
                // ------------------------------------------------

                ESP_LOGI(
                    TAG,
                    "Telemetry JSON: %s",
                    payload_buffer
                );

                // ------------------------------------------------
                // Publicera till MQTT
                // ------------------------------------------------

                esp_err_t publish_err = mqtt_client_module_publish(
                    MQTT_TOPIC_TELEMETRY,
                    payload_buffer
                );

                if (publish_err == ESP_OK)
                {
                    ESP_LOGI(
                        TAG,
                        "Telemetry publicerad"
                    );
                }
                else
                {
                    ESP_LOGW(
                        TAG,
                        "Telemetry kunde inte publiceras: %s",
                        esp_err_to_name(publish_err)
                    );
                }
            }
        }
        else
        {
            ESP_LOGE(
                TAG,
                "s_sensor_queue är NULL!"
            );

            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}