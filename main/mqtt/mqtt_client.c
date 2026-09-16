
#include "hydro_mqtt_client.h"

#include "mqtt_client.h"
#include "esp_log.h"
#include "esp_event.h"

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

            s_mqtt_connected = true;

            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            ESP_LOGI(TAG, "MQTT connected successfully");

            break;


        case MQTT_EVENT_DISCONNECTED:

            s_mqtt_connected = false;

            ESP_LOGW(TAG, "MQTT_EVENT_DISCONNECTED");

            break;


        case MQTT_EVENT_ERROR:

            ESP_LOGE(TAG, "MQTT_EVENT_ERROR");

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
    ESP_LOGI(
        TAG,
        "MQTT Klient ansluter till %s",
        MQTT_BROKER_URI
    );


    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
        .credentials.client_id = MQTT_CLIENT_ID,
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


