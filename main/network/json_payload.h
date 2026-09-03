#ifndef JSON_PAYLOAD_H
#define JSON_PAYLOAD_H

#include "sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// JSON SERIALIZER TEMPLATE (ANSVAR: IOT ENGINEER)
// ============================================================================

/**
 * @brief Serialiserar sensor_telemetry_t till en formaterad JSON-sträng (cJSON).
 * @param[in] data Mätdata från sensor_queue.
 * @param[out] output_buffer Målbuffer för JSON-strängen.
 * @param[in] buffer_size Storlek på målbuffer.
 * @return true om serialiseringen lyckades, annars false.
 */
bool serialize_telemetry_json(const sensor_telemetry_t *data, char *output_buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif // JSON_PAYLOAD_H
