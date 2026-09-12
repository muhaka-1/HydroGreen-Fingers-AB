#include "ota_manager.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_err.h"
#include "esp_check.h"

static const char *TAG = "OTA_MANAGER";
static const esp_partition_t *update_partition = NULL;
static esp_ota_handle update_handle = 0;

esp_err_t ota_manager_init(void) {
	
	const esp_partition_t *running = esp_ota_get_running_partition();
	ESP_LOGI(TAG, "Körande partition: %s vid offset 0x%lx",
		running ? running->label : "okänd", running ? (unsigned long)running->address : 0);

	update_partition = esp_ota_get_next_update_partition(NULL);
	if (update_partition == NULL) {
		ESP_LOGE(TAG, "Ingen giltig OTA-partition för uppdatering av firmware.");
		return ESP_FAIL;
	}

	ESP_LOGI(TAG, "Uppdatering till partition %s vid offest 0x%lx", update_partition -> label, (unsigned long)update_partition -> address);

	esp_err_t err = esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &update_handle):
	if (err != ESP_OK) {
		ESP_LOGE(TAG, "esp_ota_begin: %s", esp_err_to_name(err));
		return err;
	}
	
	ESP_LOGI(TAG, "OTA-sessionen startad.");
  	return ESP_OK;
}

esp_err_t ota_manager_write_chunk(const uint8_t *data, size_t length) {
	
	if (update_handle == 0) {
		ESP_LOGE(TAG, "Update_handle saknas.");
		return ESP_ERR_INVALID_STATE;
	}

	if (data == NULL || length == 0) {
		ESP_LOGI(TAG, "Ingen ny firmware hittad.");
		return ESP_OK;
	}

	esp_err_t err = esp_ota_write(update_handle, data, length);
	if (err != ESP_OK) {
		ESP_LOGE(TAG, "esp_ota_write: %s", esp_err_to_name(err));
		return err;
	}

	ESP_LOGI(TAG, "%zu bytes skrevs till OTA-partitionen.", length);
    	return ESP_OK;
}

esp_err_t ota_manager_finish(void) {

	if (update_handle == 0) {
		ESP_LOGE("Ingen aktiv OTA-session.");
		return ESP_ERR_INVALID_STATE;
	}

	if (esp_ota_end(update_handle) != ESP_OK || esp_ota_set_boot_partition(update_partition) != ESP_OK) {
		ESP_LOGE(TAG, "Validering eller partitionsbyte misslyckades.\n");
		return ESP_FAIL;
	}

	ESP_LOGI(TAG, "OTA uppdatering slutförd.");
	return ESP_OK;
}
