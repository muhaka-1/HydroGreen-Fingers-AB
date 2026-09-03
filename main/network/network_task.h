#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// NETWORK TASK TEMPLATE (ANSVAR: IOT ENGINEER)
// ============================================================================

/**
 * @brief FreeRTOS Task på Core 0 för att konsumera sensor_queue och publicera till MQTT.
 */
void network_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // NETWORK_TASK_H
