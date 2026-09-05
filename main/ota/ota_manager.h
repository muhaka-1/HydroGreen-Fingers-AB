#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: OTA Firmware Update (Ansvar: Jemi / DevOps & Security Engineer)
// ============================================================================

/**
 * @brief Initierar OTA-subsystemet och kontrollerar aktuell körande partition.
 */
esp_err_t ota_manager_init(void);

/**
 * @brief Skriver en inkommande firmware-dataström till OTA-flashpartitionen.
 */
esp_err_t ota_manager_write_chunk(const uint8_t *data, size_t length);

/**
 * @brief Slutför OTA-uppdateringen och validerar den nya firmware-imagen.
 */
esp_err_t ota_manager_finish(void);

#ifdef __cplusplus
}
#endif

#endif // OTA_MANAGER_H
