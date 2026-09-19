#ifndef MQTT_TASK_H
#define MQTT_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief FreeRTOS MQTT task.
 *
 * Consumes sensor telemetry from s_sensor_queue
 * and publishes it through MQTT.
 */
void mqtt_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_TASK_H */