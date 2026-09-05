#ifndef MQTT_TASK_H
#define MQTT_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: FreeRTOS MQTT Task (Ansvar: Mohammad / IoT & Cloud Engineer)
// ============================================================================

/**
 * @brief FreeRTOS Task på Core 0 för att konsumera sensor_queue och publicera till MQTT.
 */
void mqtt_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // MQTT_TASK_H
