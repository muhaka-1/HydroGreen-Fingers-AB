#ifndef HYDRO_MQTT_CLIENT_H
#define HYDRO_MQTT_CLIENT_H

#include <stdbool.h>
#include "esp_err.h"


#define MQTT_BROKER_URI        "mqtt://broker.hivemq.com:1883"
#define MQTT_TOPIC_TELEMETRY   "hydrogreen/microhydros/telemetry"
#define MQTT_TOPIC_STATUS      "hydrogreen/microhydros/status"
#define MQTT_CLIENT_ID         "microhydros-01"


esp_err_t mqtt_client_module_start(void);

esp_err_t mqtt_client_module_publish(
    const char *topic,
    const char *payload
);

bool mqtt_client_module_is_connected(void);


#endif /* HYDRO_MQTT_CLIENT_H */
