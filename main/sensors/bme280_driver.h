#ifndef BME280_DRIVER_H
#define BME280_DRIVER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_MASTER_SCL_IO           22    // GPIO 22: I2C SCL
#define I2C_MASTER_SDA_IO           21    // GPIO 21: I2C SDA
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_FREQ_HZ          100000 // 100 kHz Standard Mode
#define BME280_I2C_ADDR             0x76   // Standard I2C-adress

/**
 * @brief Initialiserar I2C-bussen för BME280 / SHT31 sensorer.
 */
esp_err_t bme280_i2c_init(void);

/**
 * @brief Läser av rådata och beräknar temperatur, luftfuktighet och lufttryck.
 * @param[out] temp_c Pekare till variabel för temperatur (°C)
 * @param[out] humidity_pct Pekare till variabel för relativ luftfuktighet (% RH)
 * @param[out] pressure_hpa Pekare till variabel för lufttryck (hPa)
 * @return ESP_OK vid lyckad avläsning, ESP_FAIL vid bussfel
 */
esp_err_t bme280_read_data(float *temp_c, float *humidity_pct, float *pressure_hpa);

#ifdef __cplusplus
}
#endif

#endif // BME280_DRIVER_H
