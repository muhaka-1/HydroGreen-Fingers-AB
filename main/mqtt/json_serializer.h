#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "sensor_types.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: JSON Serializer (Ansvar: Mohammad / IoT & Cloud Engineer)
// ============================================================================

/**
 * @brief Serialiserar sensor_telemetry_t till en standardiserad JSON-sträng.
 */
bool serialize_telemetry_json(const sensor_telemetry_t *data, char *output_buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif // JSON_SERIALIZER_H
