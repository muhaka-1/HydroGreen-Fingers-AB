#include <stdio.h>
#include "esp_mac.h"
#include "hydro_mqtt_client.h"
#include "ota_manager.h"
#include <mqtt_client.h>
#include "esp_log.h"
#include "esp_event.h"
#include "cJSON.h"
#include <string.h>

#ifndef MQTT_TOPIC_COMMAND
#define MQTT_TOPIC_COMMAND "hydrogreen/command"
#endif

static const char *TAG = "MQTT_CLIENT";

static esp_mqtt_client_handle_t s_mqtt_client = NULL;
static bool s_mqtt_connected = false;


/* ============================================================
 * MQTT EVENT HANDLER
 * ============================================================ */

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data)
{
    esp_mqtt_event_handle_t event =
        (esp_mqtt_event_handle_t)event_data;

    switch ((esp_mqtt_event_id_t)event_id)
    {
        case MQTT_EVENT_CONNECTED:
        {
            s_mqtt_connected = true;

            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            ESP_LOGI(TAG, "MQTT connected successfully");

            /* ------------------------------------------------
             * Subscribe till command-topic
             * ------------------------------------------------ */

            int msg_id = esp_mqtt_client_subscribe(
                s_mqtt_client,
                MQTT_TOPIC_COMMAND,
                1
            );

            if (msg_id >= 0)
            {
                ESP_LOGI(
                    TAG,
                    "Subscribed to: %s",
                    MQTT_TOPIC_COMMAND
                );
            }
            else
            {
                ESP_LOGE(
                    TAG,
                    "MQTT subscribe misslyckades"
                );
            }

            break;
        }


        case MQTT_EVENT_DISCONNECTED:

            s_mqtt_connected = false;

            ESP_LOGW(
                TAG,
                "MQTT_EVENT_DISCONNECTED"
            );

            break;


        case MQTT_EVENT_DATA:
        {
            /* ------------------------------------------------
             * MQTT message received
             * ------------------------------------------------ */

            if (event == NULL)
            {
                break;
            }

            char topic[128];
            char payload[256];

            int topic_len = event->topic_len;

            if (topic_len >= sizeof(topic))
            {
                topic_len = sizeof(topic) - 1;
            }

            memcpy(
                topic,
                event->topic,
                topic_len
            );

            topic[topic_len] = '\0';


            int data_len = event->data_len;

            if (data_len >= sizeof(payload))
            {
                data_len = sizeof(payload) - 1;
            }

            memcpy(
                payload,
                event->data,
                data_len
            );

            payload[data_len] = '\0';


            ESP_LOGI(
                TAG,
                "MQTT message received"
            );

            ESP_LOGI(
                TAG,
                "Topic: %s",
                topic
            );

            ESP_LOGI(
                TAG,
                "Payload: %s",
                payload
            );


            /* ------------------------------------------------
             * Kontrollera command-topic
             * ------------------------------------------------ */

            if (strcmp(topic, MQTT_TOPIC_COMMAND) == 0)
            {
                cJSON *root = cJSON_Parse(payload);

                if (root == NULL)
                {
                    ESP_LOGW(
                        TAG,
                        "Ogiltig JSON command"
                    );

                    break;
                }

                cJSON *command =
                    cJSON_GetObjectItem(root, "command");

                if (cJSON_IsString(command))
                {
                    ESP_LOGI(
                        TAG,
                        "Command received: %s",
                        command->valuestring
                    );


                    /* ----------------------------------------
                     * STATUS command
                     * ---------------------------------------- */

                    if (strcmp(
                            command->valuestring,
                            "status"
                        ) == 0)
                    {
                        const char *status_payload =
                            "{\"device\":\"microhydros-01\",\"status\":\"online\"}";

                        esp_mqtt_client_publish(
                            s_mqtt_client,
                            MQTT_TOPIC_STATUS,
                            status_payload,
                            0,
                            1,
                            0
                        );

                        ESP_LOGI(
                            TAG,
                            "Status response published"
                        );
                    }
                    else
                    {
                        ESP_LOGW(
                            TAG,
                            "Unknown command: %s",
                            command->valuestring
                        );
                    }
                }
                else
                {
                    ESP_LOGW(
                        TAG,
                        "JSON saknar 'command'"
                    );
                }

                cJSON_Delete(root);
            }

            break;
        }


        case MQTT_EVENT_ERROR:

            ESP_LOGE(
                TAG,
                "MQTT_EVENT_ERROR"
            );

            if (event != NULL &&
                event->error_handle != NULL)
            {
                ESP_LOGE(
                    TAG,
                    "MQTT error type: %d",
                    event->error_handle->error_type
                );
            }

            break;


        default:
            break;
    }
}


/* ============================================================
 * START MQTT CLIENT
 * ============================================================ */

esp_err_t mqtt_client_module_start(void)
{
       uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    static char client_id[40];
    snprintf(client_id, sizeof(client_id), "%s-%02x%02x%02x",
             MQTT_CLIENT_ID, mac[3], mac[4], mac[5]);
    ESP_LOGI(TAG, "MQTT client ID: %s", client_id);

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
        .credentials.client_id = client_id,
    };
    

    s_mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    if (s_mqtt_client == NULL)
    {
        ESP_LOGE(
            TAG,
            "Kunde inte initiera MQTT client"
        );

        return ESP_FAIL;
    }

    esp_err_t err = esp_mqtt_client_register_event(
        s_mqtt_client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL
    );

    if (err != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "Kunde inte registrera MQTT event handler: %s",
            esp_err_to_name(err)
        );

        return err;
    }

    err = esp_mqtt_client_start(s_mqtt_client);

    if (err != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "Kunde inte starta MQTT client: %s",
            esp_err_to_name(err)
        );

        return err;
    }

    ESP_LOGI(
        TAG,
        "MQTT client startad"
    );

    return ESP_OK;
}


/* ============================================================
 * PUBLISH MQTT MESSAGE
 * ============================================================ */

esp_err_t mqtt_client_module_publish(
    const char *topic,
    const char *payload)
{
    if (s_mqtt_client == NULL)
    {
        ESP_LOGE(
            TAG,
            "MQTT client är inte initierad"
        );

        return ESP_ERR_INVALID_STATE;
    }

    if (!s_mqtt_connected)
    {
        ESP_LOGW(
            TAG,
            "MQTT är inte ansluten - publish avbruten"
        );

        return ESP_ERR_INVALID_STATE;
    }

    if (topic == NULL || payload == NULL)
    {
        ESP_LOGE(
            TAG,
            "Ogiltig MQTT topic eller payload"
        );

        return ESP_ERR_INVALID_ARG;
    }

    int msg_id = esp_mqtt_client_publish(
        s_mqtt_client,
        topic,
        payload,
        0,
        1,
        0
    );

    if (msg_id < 0)
    {
        ESP_LOGE(
            TAG,
            "MQTT publish misslyckades"
        );

        return ESP_FAIL;
    }

    ESP_LOGI(
        TAG,
        "MQTT publish successful, msg_id=%d",
        msg_id
    );

    return ESP_OK;
}


/* ============================================================
 * MQTT CONNECTION STATUS
 * ============================================================ */

bool mqtt_client_module_is_connected(void)
{
    return s_mqtt_connected;
}