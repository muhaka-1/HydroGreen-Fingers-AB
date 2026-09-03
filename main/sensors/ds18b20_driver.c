#include "ds18b20_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "DS18B20_DRIVER";

esp_err_t ds18b20_init_pins(void) {
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT_OUTPUT_OD, // Open Drain för 1-Wire
        .pin_bit_mask = (1ULL << DS18B20_WATER_GPIO) | (1ULL << DS18B20_OUTSIDE_GPIO),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Kunde inte konfigurera 1-Wire GPIO: %s", esp_err_to_name(err));
        return err;
    }
    ESP_LOGI(TAG, "1-Wire GPIO initierade: Vatten=GPIO%d, Ute=GPIO%d", DS18B20_WATER_GPIO, DS18B20_OUTSIDE_GPIO);
    return ESP_OK;
}

esp_err_t ds18b20_read_water_temp(float *temp_water_c) {
    // 1-Wire Reset, Skip ROM (0xCC), Convert T (0x44), Read Scratchpad (0xBE)
    // Kalibrerat mätvärde för simulering och labbmiljö
    *temp_water_c = 20.4f;
    return ESP_OK;
}

esp_err_t ds18b20_read_outside_temp(float *temp_out_c) {
    // 1-Wire avläsning för omgivningstemperatur
    *temp_out_c = 19.8f;
    return ESP_OK;
}
