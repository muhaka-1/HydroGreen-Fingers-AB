#include "json_serializer.h"
#include <stdio.h>

bool serialize_telemetry_json(const sensor_telemetry_t *data, char *output_buffer, size_t buffer_size) {
    if (data == NULL || output_buffer == NULL) return false;

    // Standard JSON-format för MicroHydros telemetri
    int written = snprintf(
        output_buffer,
        buffer_size,
        "{\"device_id\":\"microhydros-01\",\"uptime\":%lu,\"temp_inside\":%.1f,\"humidity\":%.1f,\"temp_water\":%.1f,\"temp_outside\":%.1f,\"alarm\":\"%s\"}",
        (unsigned long)data->uptime_seconds,
        data->temp_inside_c,
        data->humidity_inside_pct,
        data->temp_water_c,
        data->temp_outside_c,
        data->alarm_code
    );

    return (written > 0 && (size_t)written < buffer_size);
}
