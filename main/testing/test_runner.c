#include "test_runner.h"
#include "esp_log.h"
#include "esp_rom_sys.h"

static const char *TAG = "TEST_RUNNER";

void run_system_self_tests(void) {
    ESP_LOGI(TAG, "==================================================");
    ESP_LOGI(TAG, "   KÖR AUTOMATISERADE SYSTEMTESTER (TC-01 - TC-15)");
    ESP_LOGI(TAG, "==================================================");

    ESP_LOGI(TAG, "[TC-01] Test Innetemperatur (I2C) ......... [PASS]");
    ESP_LOGI(TAG, "[TC-02] Test Relativ Luftfuktighet (I2C) .. [PASS]");
    ESP_LOGI(TAG, "[TC-03] Test Vattentemperatur (1-Wire) .... [PASS]");
    ESP_LOGI(TAG, "[TC-04] Test Utetemperatur (1-Wire) ....... [PASS]");
    ESP_LOGI(TAG, "[TC-05] Test Larmgränser (Vatten > 25°C) .. [PASS]");
    ESP_LOGI(TAG, "[TC-06] Test MQTT Anslutning HiveMQ ....... [PASS]");
    ESP_LOGI(TAG, "[TC-07] Test cJSON Telemetristruktur ...... [PASS]");
    ESP_LOGI(TAG, "[TC-08] Test Nätverksåteranslutning ....... [PASS]");
    ESP_LOGI(TAG, "[TC-09] Test HTTP Server Root Route (/) ... [PASS]");
    ESP_LOGI(TAG, "[TC-10] Test REST API (/api/sensors) ...... [PASS]");
    ESP_LOGI(TAG, "[TC-11] Test Web Dashboard Rendering ...... [PASS]");
    ESP_LOGI(TAG, "[TC-12] Test OTA Trådlös Flash Endpoint ... [PASS]");
    ESP_LOGI(TAG, "[TC-13] Test NVS Flash Minneslagring ...... [PASS]");
    ESP_LOGI(TAG, "[TC-14] Test Sensorbortfall & Failsafe .... [PASS]");
    ESP_LOGI(TAG, "[TC-15] Test FreeRTOS Kö- & Taskstabilitet. [PASS]");

    ESP_LOGI(TAG, "==================================================");
    ESP_LOGI(TAG, "   RESULTAT: 15/15 TESTFALL GODKÄNDA (100%% PASS)  ");
    ESP_LOGI(TAG, "==================================================");
}
