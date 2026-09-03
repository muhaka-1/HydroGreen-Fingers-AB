#ifndef ALARM_LIMITS_H
#define ALARM_LIMITS_H

#include "sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// BIOLOGISKA GRÄNSVÄRDEN FÖR HYDROPONISK ODLING (HYDROGREEN FINGERS AB)
// ============================================================================
#define LIMIT_WATER_TEMP_MIN        12.0f   // För kall näringslösning skadar rötterna
#define LIMIT_WATER_TEMP_MAX        25.0f   // För varmt vatten minskar syresättningen (rotbrand)
#define LIMIT_HUMIDITY_INSIDE_MAX   85.0f   // För hög luftfuktighet gynnar mögelangrepp
#define LIMIT_TEMP_INSIDE_MIN       15.0f   // Minimi innelufttemp
#define LIMIT_TEMP_INSIDE_MAX       32.0f   // Max innelufttemp

/**
 * @brief Utvärderar telemetridata mot biologiska gränsvärden och sätter larmkoder.
 * @param[in,out] telemetry Pekare till mätstruktur som ska uppdateras med alarm_code.
 */
void evaluate_alarm_limits(sensor_telemetry_t *telemetry);

#ifdef __cplusplus
}
#endif

#endif // ALARM_LIMITS_H
