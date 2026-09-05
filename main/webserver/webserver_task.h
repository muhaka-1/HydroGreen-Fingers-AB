#ifndef WEBSERVER_TASK_H
#define WEBSERVER_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: FreeRTOS WebServer Task (Ansvar: Emil / Web & UI Engineer)
// ============================================================================

/**
 * @brief FreeRTOS Task för att hantera webbserverns livscykel.
 */
void webserver_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // WEBSERVER_TASK_H
