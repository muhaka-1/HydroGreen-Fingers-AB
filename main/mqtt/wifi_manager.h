#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: Wi-Fi Manager
// Ansvar: Mohammad / IoT & Cloud Engineer
// ============================================================================

#define WIFI_SSID_DEFAULT "Tele2Internet_B5596"
#define WIFI_PASS_DEFAULT "B648nLhA5a5"

esp_err_t wifi_manager_init(void);

bool wifi_manager_is_connected(void);

#ifdef __cplusplus
} 
#endif

#endif // WIFI_MANAGER_H