#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// WIFI MANAGER TEMPLATE (ANSVAR: IOT ENGINEER)
// ============================================================================

/**
 * @brief Initialiserar Wi-Fi i station-läge (Wokwi-GUEST eller lokalt Wi-Fi).
 */
esp_err_t wifi_manager_init(void);

#ifdef __cplusplus
}
#endif

#endif // WIFI_MANAGER_H
