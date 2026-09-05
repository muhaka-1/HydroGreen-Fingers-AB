#include "ota_manager.h"
#include "esp_log.h"
#include "esp_ota_ops.h"

static const char *TAG = "OTA_MANAGER";

esp_err_t ota_manager_init(void) {
    const esp_partition_t *running = esp_ota_get_running_partition();
    ESP_LOGI(TAG, "Körande partition: %s vid offset 0x%lx (Placeholder för Jemi)",
             running ? running->label : "okänd", running ? (unsigned long)running->address : 0);
    return ESP_OK;
}

esp_err_t ota_manager_write_chunk(const uint8_t *data, size_t length) {
    // TODO: Jemi implementerar esp_ota_write()
    return ESP_OK;
}

esp_err_t ota_manager_finish(void) {
    // TODO: Jemi implementerar esp_ota_end() och esp_ota_set_boot_partition()
    ESP_LOGI(TAG, "OTA uppdatering slutförd.");
    return ESP_OK;
}
