#ifndef MQTT_CLIENT_MODULE_H
#define MQTT_CLIENT_MODULE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MQTT CLIENT MODULE TEMPLATE (ANSVAR: IOT ENGINEER)
// ============================================================================

/**
 * @brief Startar och ansluter MQTT-klienten till broker (t.ex. broker.hivemq.com).
 */
esp_err_t mqtt_client_module_start(void);

/**
 * @brief Publicerar ett telemetrimeddelande till MQTT-brokern.
 */
esp_err_t mqtt_client_module_publish(const char *topic, const char *payload);

#ifdef __cplusplus
}
#endif

#endif // MQTT_CLIENT_MODULE_H
