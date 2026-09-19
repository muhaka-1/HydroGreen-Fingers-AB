#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * WIFI CONFIGURATION
 * ========================================================================== */

/*
 * Wokwi default network.
 *
 * For real hardware, change these values or move them
 * to a secure configuration system.
 */
#define WIFI_SSID_DEFAULT "Wokwi-GUEST"
#define WIFI_PASS_DEFAULT ""

/* ============================================================================
 * PUBLIC API
 * ========================================================================== */

/**
 * @brief Initialize Wi-Fi in station mode.
 */
esp_err_t wifi_manager_init(void);

/**
 * @brief Check whether Wi-Fi is connected.
 */
bool wifi_manager_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_MANAGER_H */