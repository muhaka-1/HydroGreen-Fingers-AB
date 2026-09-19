#include "json_serializer.h"

#include <stdio.h>

bool serialize_telemetry_json(
    const sensor_telemetry_t *data,
    char *output_buffer,
    size_t buffer_size)
{
    if (data == NULL ||
        output_buffer == NULL ||
        buffer_size == 0)
    {
        return false;
    }

    int written = snprintf(
        output_buffer,
        buffer_size,

        "{"
        "\"device_id\":\"microhydros-01\","
        "\"uptime_seconds\":%lu,"

        "\"temperature_inside_c\":%.2f,"
        "\"humidity_inside_pct\":%.2f,"
        "\"pressure_hpa\":%.2f,"

        "\"temperature_water_c\":%.2f,"
        "\"temperature_outside_c\":%.2f,"

        "\"bme280_valid\":%s,"
        "\"ds18b20_water_valid\":%s,"
        "\"ds18b20_out_valid\":%s,"

        "\"alarm\":\"%s\""
        "}",

        (unsigned long)data->uptime_seconds,

        data->temp_inside_c,
        data->humidity_inside_pct,
        data->pressure_hpa,

        data->temp_water_c,
        data->temp_outside_c,

        data->bme280_valid ? "true" : "false",
        data->ds18b20_water_valid ? "true" : "false",
        data->ds18b20_out_valid ? "true" : "false",

        data->alarm_code
    );

    if (written <= 0)
    {
        return false;
    }

    return (size_t)written < buffer_size;
}