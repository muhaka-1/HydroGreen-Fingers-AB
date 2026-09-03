#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STATUS_LED_GPIO         GPIO_NUM_2    // Status-LED på GPIO 2
#define SENSOR_SAMPLE_RATE_MS   3000          // 3 sekunders provtagningsintervall

/**
 * @brief FreeRTOS Task för kontinuerlig sensorprovtagning, larmvalidering och köhantering.
 * @param pvParameters FreeRTOS task parametrar
 */
void sensor_task(void *pvParameters);

/**
 * @brief Initierar all sensorhårdvara och tillhörande GPIO/I2C/1-Wire.
 */
esp_err_t init_sensor_hardware(void);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_TASK_H
