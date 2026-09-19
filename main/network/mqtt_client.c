#include "mqtt_client.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include <string.h>

static const char *TAG = "MQTT_CLIENT";

static esp_mqtt_client_handle_t s_mqtt_client = NULL;
static volatile bool s_mqtt_connected = false;

/* ============================================================================
 * MQTT EVENT HANDLER
 * ========================================================================== */

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

            s_mqtt_connected = true;

            ESP_LOGI(
                TAG,
                "MQTT connected to %s",
                MQTT_BROKER_URI
            );

            esp_mqtt_client_publish(
                s_mqtt_client,
                MQTT_TOPIC_STATUS,
                "{\"status\":\"online\",\"device_id\":\"microhydros-01\"}",
                0,
                1,
                1
            );

            break;

        case MQTT_EVENT_DISCONNECTED:

            s_mqtt_connected = false;

            ESP_LOGW(
                TAG,
                "MQTT disconnected"
            );

            break;

        case MQTT_EVENT_ERROR:

            s_mqtt_connected = false;

            ESP_LOGE(
                TAG,
                "MQTT error"
            );

            break;

        default:

            break;
    }
}

/* ============================================================================
 * MQTT START
 * ========================================================================== */

esp_err_t mqtt_client_module_start(void)
{
    if (s_mqtt_client != NULL)
    {
        ESP_LOGW(
            TAG,
            "MQTT client already initialized"
        );

        return ESP_OK;
    }

    ESP_LOGI(
        TAG,
        "Starting MQTT client: %s",
        MQTT_BROKER_URI
    );

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER_URI,

        .credentials.client_id = MQTT_CLIENT_ID,

        .session.keepalive = 30,
        .session.disable_clean_session = false,

        .network.reconnect_timeout_ms = 5000,
        .network.timeout_ms = 10000,
    };

    s_mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    if (s_mqtt_client == NULL)
    {
        ESP_LOGE(
            TAG,
            "Failed to initialize MQTT client"
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
            "Failed to register MQTT event handler: %s",
            esp_err_to_name(err)
        );

        return err;
    }

    err = esp_mqtt_client_start(s_mqtt_client);

    if (err != ESP_OK)
    {
        ESP_LOGE(
            TAG,
            "Failed to start MQTT client: %s",
            esp_err_to_name(err)
        );

        return err;
    }

    ESP_LOGI(
        TAG,
        "MQTT client started"
    );

    return ESP_OK;
}

/* ============================================================================
 * MQTT PUBLISH
 * ========================================================================== */

esp_err_t mqtt_client_module_publish(
    const char *topic,
    const char *payload)
{
    if (topic == NULL || payload == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if (s_mqtt_client == NULL)
    {
        ESP_LOGW(
            TAG,
            "MQTT client is not initialized"
        );

        return ESP_ERR_INVALID_STATE;
    }

    if (!s_mqtt_connected)
    {
        ESP_LOGW(
            TAG,
            "MQTT not connected - message skipped"
        );

        return ESP_ERR_INVALID_STATE;
    }

    int message_id = esp_mqtt_client_publish(
        s_mqtt_client,
        topic,
        payload,
        0,
        1,
        0
    );

    if (message_id < 0)
    {
        ESP_LOGE(
            TAG,
            "MQTT publish failed: topic=%s",
            topic
        );

        return ESP_FAIL;
    }

    ESP_LOGI(
        TAG,
        "MQTT published: topic=%s message_id=%d",
        topic,
        message_id
    );

    return ESP_OK;
}

/* ============================================================================
 * MQTT CONNECTION STATUS
 * ========================================================================== */

bool mqtt_client_module_is_connected(void)
{
    return s_mqtt_connected;
}