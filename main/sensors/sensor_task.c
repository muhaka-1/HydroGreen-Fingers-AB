#include "sensor_task.h"
#include "bme280_driver.h"
#include "ds18b20_driver.h"
#include "alarm_limits.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "driver/gpio.h"

static const char *TAG = "SENSOR_TASK";

esp_err_t init_sensor_hardware(void) {
    // 1. Konfigurera Status-LED
    gpio_reset_pin(STATUS_LED_GPIO);
    gpio_set_direction(STATUS_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(STATUS_LED_GPIO, 1);

    // 2. Initiera I2C för BME280 / SHT31
    esp_err_t i2c_err = bme280_i2c_init();
    if (i2c_err != ESP_OK) {
        ESP_LOGW(TAG, "Varning: I2C-bussen svarar inte (%s), fortsätter med felsäkra värden", esp_err_to_name(i2c_err));
    }

    // 3. Initiera 1-Wire för DS18B20
    esp_err_t ds_err = ds18b20_init_pins();
    if (ds_err != ESP_OK) {
        ESP_LOGW(TAG, "Varning: 1-Wire GPIO kunde inte initieras (%s)", esp_err_to_name(ds_err));
    }

    ESP_LOGI(TAG, "Sensorhårdvara initierad!");
    return ESP_OK;
}

void sensor_task(void *pvParameters) {
    ESP_LOGI(TAG, "SensorTask startad på FreeRTOS Core %d (Prioritet: 2)", xPortGetCoreID());
    sensor_telemetry_t data;

    while (1) {
        // 1. Läs Inomhusklimat via I2C (BME280 / SHT31)
        esp_err_t err_bme = bme280_read_data(&data.temp_inside_c, &data.humidity_inside_pct, &data.pressure_hpa);
        data.bme280_valid = (err_bme == ESP_OK);

        // 2. Läs Vattentemperatur i näringslösning via 1-Wire (DS18B20 #1)
        esp_err_t err_water = ds18b20_read_water_temp(&data.temp_water_c);
        data.ds18b20_water_valid = (err_water == ESP_OK);

        // 3. Läs Utomhustemperatur via 1-Wire (DS18B20 #2)
        esp_err_t err_out = ds18b20_read_outside_temp(&data.temp_outside_c);
        data.ds18b20_out_valid = (err_out == ESP_OK);

        // 4. Drifttid och larmgränser
        data.uptime_seconds = (uint32_t)(esp_timer_get_time() / 1000000ULL);
        evaluate_alarm_limits(&data);

        // 5. Skriv ut diagnostik direkt till serieporten
        ESP_LOGI(TAG, "[Mätning] Inne: %.1f°C (%.1f%% RH) | Vatten: %.1f°C | Ute: %.1f°C | Larm: %s",
                 data.temp_inside_c, data.humidity_inside_pct, data.temp_water_c, data.temp_outside_c, data.alarm_code);
        esp_rom_printf("[SENSOR_TASK] Inne: %.1f C (%.1f%% RH) | Vatten: %.1f C | Ute: %.1f C | Larm: %s\r\n",
                       data.temp_inside_c, data.humidity_inside_pct, data.temp_water_c, data.temp_outside_c, data.alarm_code);

        // 6. Skicka telemetripaket till FreeRTOS-kön (för network_task)
        if (s_sensor_queue != NULL) {
            if (xQueueSend(s_sensor_queue, &data, pdMS_TO_TICKS(100)) != pdPASS) {
                ESP_LOGW(TAG, "SensorQueue full, hoppar över telemetripaket.");
            }
        }

        // Heartbeat LED-puls
        gpio_set_level(STATUS_LED_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(STATUS_LED_GPIO, 0);

        // Mätintervall
        vTaskDelay(pdMS_TO_TICKS(SENSOR_SAMPLE_RATE_MS - 100));
    }
}
