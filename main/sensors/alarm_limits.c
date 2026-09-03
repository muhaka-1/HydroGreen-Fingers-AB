#include "alarm_limits.h"
#include <string.h>

void evaluate_alarm_limits(sensor_telemetry_t *telemetry) {
    if (telemetry == NULL) return;

    if (telemetry->temp_water_c > LIMIT_WATER_TEMP_MAX) {
        strncpy(telemetry->alarm_code, "ALARM_WATER_OVERHEAT", sizeof(telemetry->alarm_code) - 1);
    } else if (telemetry->temp_water_c < LIMIT_WATER_TEMP_MIN) {
        strncpy(telemetry->alarm_code, "ALARM_WATER_COLD", sizeof(telemetry->alarm_code) - 1);
    } else if (telemetry->humidity_inside_pct > LIMIT_HUMIDITY_INSIDE_MAX) {
        strncpy(telemetry->alarm_code, "ALARM_HIGH_HUMIDITY", sizeof(telemetry->alarm_code) - 1);
    } else if (telemetry->temp_inside_c < LIMIT_TEMP_INSIDE_MIN || telemetry->temp_inside_c > LIMIT_TEMP_INSIDE_MAX) {
        strncpy(telemetry->alarm_code, "ALARM_TEMP_AIR_OUT_OF_RANGE", sizeof(telemetry->alarm_code) - 1);
    } else {
        strncpy(telemetry->alarm_code, "NONE", sizeof(telemetry->alarm_code) - 1);
    }
}
