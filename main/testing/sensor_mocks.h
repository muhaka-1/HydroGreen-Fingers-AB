#ifndef SENSOR_MOCKS_H
#define SENSOR_MOCKS_H

#include "sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: Test Mocks & Fault Injection (Ansvar: Simon / QA & Test Automation)
// ============================================================================

/**
 * @brief Simulerar ett extremt överhettningstillstånd för att testa larmfunktioner.
 */
void mock_simulate_overheat_condition(sensor_telemetry_t *data);

/**
 * @brief Simulerar ett sensorbortfall (timeout / frånkopplad sensor).
 */
void mock_simulate_sensor_disconnect(sensor_telemetry_t *data);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_MOCKS_H
