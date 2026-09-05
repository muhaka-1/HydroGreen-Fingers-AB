#ifndef MQTT_CLIENT_MODULE_H
#define MQTT_CLIENT_MODULE_H

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: MQTT Client (Ansvar: Mohammad / IoT & Cloud Engineer)
// ============================================================================

#define MQTT_BROKER_URI        "mqtt://broker.hivemq.com:1883"
#define MQTT_TOPIC_TELEMETRY   "hydrogreen/microhydros/telemetry"
#define MQTT_TOPIC_STATUS      "hydrogreen/microhydros/status"

/**
 * @brief Startar och ansluter MQTT-klienten till broker.hivemq.com.
 */
esp_err_t mqtt_client_module_start(void);

/**
 * @brief Publicerar ett telemetrimeddelande till MQTT-brokern.
 * @param topic MQTT Topic
 * @param payload JSON-sträng som ska skickas
 */
esp_err_t mqtt_client_module_publish(const char *topic, const char *payload);

#ifdef __cplusplus
}
#endif

#endif // MQTT_CLIENT_MODULE_H
