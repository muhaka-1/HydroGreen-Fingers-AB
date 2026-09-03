#include "json_payload.h"
#include <stdio.h>

bool serialize_telemetry_json(const sensor_telemetry_t *data, char *output_buffer, size_t buffer_size) {
    if (data == NULL || output_buffer == NULL) return false;

    // TODO: IoT Engineer implementerar cJSON-serialisering här
    snprintf(output_buffer, buffer_size,
             "{\"temp_inside\":%.2f,\"humidity\":%.2f,\"temp_water\":%.2f,\"temp_outside\":%.2f,\"alarm\":\"%s\"}",
             data->temp_inside_c, data->humidity_inside_pct, data->temp_water_c, data->temp_outside_c, data->alarm_code);
    return true;
}
