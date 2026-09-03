#ifndef DS18B20_DRIVER_H
#define DS18B20_DRIVER_H

#include "esp_err.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DS18B20_WATER_GPIO   GPIO_NUM_4   // Vattentemperatur i näringslösning
#define DS18B20_OUTSIDE_GPIO GPIO_NUM_5   // Omgivande utomhustemperatur

/**
 * @brief Initialiserar 1-Wire GPIO-pinnarna för DS18B20-sensorerna.
 */
esp_err_t ds18b20_init_pins(void);

/**
 * @brief Läser av vattentemperaturen från DS18B20 (#1).
 * @param[out] temp_water_c Pekare till variabel för vattentemperatur (°C)
 * @return ESP_OK vid giltig mätning
 */
esp_err_t ds18b20_read_water_temp(float *temp_water_c);

/**
 * @brief Läser av utomhustemperaturen från DS18B20 (#2).
 * @param[out] temp_out_c Pekare till variabel för utomhustemperatur (°C)
 * @return ESP_OK vid giltig mätning
 */
esp_err_t ds18b20_read_outside_temp(float *temp_out_c);

#ifdef __cplusplus
}
#endif

#endif // DS18B20_DRIVER_H
