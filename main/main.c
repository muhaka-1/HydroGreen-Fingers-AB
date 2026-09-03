/**
 * ============================================================================
 * PROJEKT: MicroHydros - Småskalig Hydroponisk Miljöövervakning
 * KURS: Projekt 1 (IoT- och embeddedutvecklare, Jensen YH)
 * SPRÅK: Ren C (ESP-IDF v5.5.1 / FreeRTOS Dual-Core Architecture)
 * 
 * ARBETSFÖRDELNING:
 * - Malek Chahin (Lead Embedded): FreeRTOS sensor_task (Core 1), BME280 I2C, DS18B20 1-Wire, Alarms
 * - IoT Engineer (Network & Cloud): FreeRTOS network_task (Core 0), Wi-Fi Manager, MQTT Client, cJSON
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

#include "sensor_types.h"
#include "sensors/sensor_task.h"
#include "network/network_task.h"

static const char *TAG = "MAIN_SYSTEM";

// Global FreeRTOS-kö för att transportera telemetridata mellan Core 1 och Core 0
QueueHandle_t s_sensor_queue = NULL;

void app_main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    esp_rom_printf("\r\n\r\n==================================================\r\n");
    esp_rom_printf("   HYDROGREEN MICROHYDROS IoT FIRMWARE v1.0 (C)   \r\n");
    esp_rom_printf("==================================================\r\n\r\n");

    ESP_LOGI(TAG, "Initierar MicroHydros system och NVS...");

    // 1. Initialisera NVS (Non-Volatile Storage för Wi-Fi stacken)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        ret = nvs_flash_init();
    }
    ESP_LOGI(TAG, "NVS status: %s", esp_err_to_name(ret));

    // 2. Skapa FreeRTOS Queue för kommunikation mellan Core 1 (Sensor) och Core 0 (Network)
    s_sensor_queue = xQueueCreate(10, sizeof(sensor_telemetry_t));
    if (s_sensor_queue == NULL) {
        ESP_LOGE(TAG, "Kritiskt fel: Kunde inte skapa FreeRTOS sensor queue!");
        return;
    }
    ESP_LOGI(TAG, "FreeRTOS sensor queue skapad (Kapacitet: 10 paket)");

    // 3. Initiera Sensorhårdvara (I2C, 1-Wire, GPIO)
    init_sensor_hardware();

    // 4. Starta SensorTask på FreeRTOS Core 1 (Malek Chahin)
    xTaskCreatePinnedToCore(
        sensor_task,
        "sensor_task",
        4096,
        NULL,
        2, // Högre prioritet för hårdvaruprovtagning
        NULL,
        1  // Core 1
    );
    ESP_LOGI(TAG, "SensorTask startad på Core 1 (Ansvar: Malek Chahin).");

    // 5. Starta NetworkTask på FreeRTOS Core 0 (IoT Engineer)
    xTaskCreatePinnedToCore(
        network_task,
        "network_task",
        4096,
        NULL,
        1, // Lägre prioritet
        NULL,
        0  // Core 0
    );
    ESP_LOGI(TAG, "NetworkTask startad på Core 0 (Ansvar: IoT Engineer).");

    ESP_LOGI(TAG, "Systemet har startat båda FreeRTOS-tasks!");
}
