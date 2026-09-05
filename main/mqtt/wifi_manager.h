#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: Wi-Fi Manager (Ansvar: Mohammad / IoT & Cloud Engineer)
// ============================================================================

#define WIFI_SSID_DEFAULT      "Wokwi-GUEST"
#define WIFI_PASS_DEFAULT      ""

/**
 * @brief Initialiserar Wi-Fi stacken i station-läge (STA).
 * @return ESP_OK vid lyckad anslutning, annars felkod.
 */
esp_err_t wifi_manager_init(void);

/**
 * @brief Returnerar om enheten är ansluten till Wi-Fi och har fått en IP.
 */
bool wifi_manager_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif // WIFI_MANAGER_H
