#include "webserver_task.h"
#include "http_server.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "WEBSERVER_TASK";

void webserver_task(void *pvParameters) {
    ESP_LOGI(TAG, "WebserverTask startad på FreeRTOS Core %d", xPortGetCoreID());

    // Vänta en stund för att nätverksstacken ska initieras
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Starta den inbyggda webbservern
    httpd_handle_t server = start_webserver();
    if (server == NULL) {
        ESP_LOGE(TAG, "Webserver kunte inte startas, avslutar task");
        vTaskDelete(NULL);
        return;
    }

    while (1) {
        // Håll liv i tasken och hantera eventuell diagnostik
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

}
