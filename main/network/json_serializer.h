#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "sensor_types.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Serialize sensor telemetry into JSON.
 */
bool serialize_telemetry_json(
    const sensor_telemetry_t *data,
    char *output_buffer,
    size_t buffer_size
);

#ifdef __cplusplus
}
#endif

#endif /* JSON_SERIALIZER_H */