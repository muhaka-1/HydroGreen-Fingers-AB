#include "sensor_mocks.h"
#include <string.h>

void mock_simulate_overheat_condition(sensor_telemetry_t *data) {
    if (!data) return;
    data->temp_water_c = 28.5f; // Över maxgränsen 25.0 °C
    strncpy(data->alarm_code, "ALARM_WATER_OVERHEAT", sizeof(data->alarm_code) - 1);
}

void mock_simulate_sensor_disconnect(sensor_telemetry_t *data) {
    if (!data) return;
    data->bme280_valid = false;
    data->ds18b20_water_valid = false;
    strncpy(data->alarm_code, "ERR_SENSOR_DISCONNECTED", sizeof(data->alarm_code) - 1);
}
