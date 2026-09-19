#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * MQTT CONFIGURATION
 * ========================================================================== */

#define MQTT_BROKER_URI        "mqtt://broker.hivemq.com:1883"

#define MQTT_TOPIC_TELEMETRY \
    "hydrogreen/microhydros/telemetry"

#define MQTT_TOPIC_STATUS \
    "hydrogreen/microhydros/status"

#define MQTT_CLIENT_ID \
    "microhydros-01"

/* ============================================================================
 * PUBLIC API
 * ========================================================================== */

/**
 * @brief Initialize and start MQTT client.
 */
esp_err_t mqtt_client_module_start(void);

/**
 * @brief Publish MQTT message.
 *
 * @param topic MQTT topic
 * @param payload Message payload
 *
 * @return ESP_OK if message was accepted for publishing.
 */
esp_err_t mqtt_client_module_publish(
    const char *topic,
    const char *payload
);

/**
 * @brief Check whether MQTT is currently connected.
 */
bool mqtt_client_module_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_CLIENT_H */