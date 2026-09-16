/**
 * ============================================================================
 * PROJEKT: MicroHydros - Småskalig Hydroponisk Miljöövervakning
 * KURS: Projekt 1 (IoT- och embeddedutvecklare, Jensen YH)
 * SPRÅK: Ren C (ESP-IDF v5.5.1 / FreeRTOS 5-Modulsarkitektur)
 * 
 * ARBETSFÖRDELNING I TEAMET (5 PERSONER):
 * 1. Malek Chahin (Lead Embedded): sensors/ (sensor_task, BME280, DS18B20, Alarms)
 * 2. Mohammad (IoT & Cloud):       mqtt/    (mqtt_task, Wi-Fi, MQTT HiveMQ, cJSON)
 * 3. Emil (Web & UI):              webserver/ (webserver_task, HTTP Server, Webview)
 * 4. Jemi (DevOps & Security):     ota/     (OTA Wireless Updates, NVS Storage)
 * 5. Simon (QA & Test Lead):       testing/ (Self-tests TC-01 - TC-15, Mocks)
 * ============================================================================
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "nvs_flash.h"

// Modulheaders för alla 5 teammedlemmar
#include "sensor_types.h"
#include "sensors/sensor_task.h"
#include "mqtt/mqtt_task.h"
#include "webserver/webserver_task.h"
#include "ota/ota_manager.h"
#include "testing/test_runner.h"

static const char *TAG = "MAIN_SYSTEM";

// Global FreeRTOS-kö för att transportera telemetridata mellan Core 1 och Core 0
QueueHandle_t s_sensor_queue = NULL;

void app_main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    esp_rom_printf("\r\n\r\n==================================================\r\n");
    esp_rom_printf("   HYDROGREEN MICROHYDROS IoT FIRMWARE v1.0 (C)   \r\n");
    esp_rom_printf("==================================================\r\n\r\n");

    ESP_LOGI(TAG, "Initierar MicroHydros system och NVS Flash...");

    // 1. Initialisera NVS (Non-Volatile Storage)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        ret = nvs_flash_init();
    }
    ESP_LOGI(TAG, "NVS status: %s", esp_err_to_name(ret));

    // 2. Skapa den delade FreeRTOS-kön för sensortelemetri
    s_sensor_queue = xQueueCreate(10, sizeof(sensor_telemetry_t));
    if (s_sensor_queue == NULL) {
        ESP_LOGE(TAG, "Kritiskt fel: Kunde inte skapa FreeRTOS sensor queue!");
        return;
    }
    ESP_LOGI(TAG, "FreeRTOS sensor queue skapad (Kapacitet: 10 paket)");

    // 3. Initiera OTA Subsystem (Jemi)
    ota_manager_init();

    // 4. Initiera Sensorhårdvara I2C/1-Wire (Malek Chahin)
    init_sensor_hardware();

    // 5. Kör automatiserade självtester vid boot (Simon)
    run_system_self_tests();

    /*// 6. Starta SensorTask på FreeRTOS Core 1 (Malek Chahin)
    xTaskCreatePinnedToCore(
        sensor_task,
        "sensor_task",
        4096,
        NULL,
        2, // Hög prioritet för hårdvarumätning
        NULL,
        1  // Core 1
    );
    ESP_LOGI(TAG, "[Core 1] SensorTask startad (Ansvar: Malek Chahin)");*/
    
    // 7. Starta MQTT Task på FreeRTOS Core 0 (Mohammad)
    xTaskCreatePinnedToCore(
        mqtt_task,
        "mqtt_task",
        4096,
        NULL,
        1,
        NULL,
        0  // Core 0
    );
    ESP_LOGI(TAG, "[Core 0] MQTT Task startad (Ansvar: Mohammad)");

    /*// 8. Starta Webserver Task på FreeRTOS Core 0 (Emil)
    xTaskCreatePinnedToCore(
        webserver_task,
        "webserver_task",
        4096,
        NULL,
        1,
        NULL,
        0  // Core 0
    );
    ESP_LOGI(TAG, "[Core 0] Webserver Task startad (Ansvar: Emil)");

    ESP_LOGI(TAG, "MicroHydros systemet körs med alla 5 moduler aktiva!");*/
}
