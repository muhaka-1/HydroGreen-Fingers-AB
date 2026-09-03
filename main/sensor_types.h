#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// TYPDEFINITIONER FÖR SENSORDATA & TELEMETRI
// ============================================================================
typedef struct {
    float temp_inside_c;        // Lufttemperatur inne i odlingen (°C)
    float humidity_inside_pct;  // Relativ luftfuktighet inne i odlingen (% RH)
    float pressure_hpa;         // Lufttryck (hPa)
    float temp_water_c;         // Vattentemperatur i näringslösningen (°C)
    float temp_outside_c;       // Omgivande utomhustemperatur (°C)

    bool bme280_valid;          // Statusflagga för BME280/SHT31
    bool ds18b20_water_valid;   // Statusflagga för DS18B20 Vatten
    bool ds18b20_out_valid;     // Statusflagga för DS18B20 Ute

    uint32_t uptime_seconds;    // Systemets drifttid i sekunder
    char alarm_code[32];        // Larmkod, t.ex. "NONE", "ALARM_WATER_OVERHEAT"
} sensor_telemetry_t;

// Global FreeRTOS-kö för att skicka mätdata från sensor_task till network_task
extern QueueHandle_t s_sensor_queue;

#ifdef __cplusplus
}
#endif

#endif // SENSOR_TYPES_H
