#ifndef NVS_STORAGE_H
#define NVS_STORAGE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: NVS Storage (Ansvar: Jemi / DevOps & Security Engineer)
// ============================================================================

/**
 * @brief Sparar en konfigurationssträng i ESP32:ans permanenta NVS-flash.
 */
esp_err_t nvs_storage_save_string(const char *key, const char *value);

/**
 * @brief Läser en konfigurationssträng från NVS-flash.
 */
esp_err_t nvs_storage_read_string(const char *key, char *out_val, size_t max_len);

#ifdef __cplusplus
}
#endif

#endif // NVS_STORAGE_H
