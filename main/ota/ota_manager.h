#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: OTA Firmware Update (Ansvar: Jemi / DevOps & Security Engineer)
//
// Flöde:  MQTT-kommando {"command":"ota","url":"https://...","sha256":"<hex>"}
//         -> ota_manager_start_update() -> OTA-task laddar ner via HTTPS
//         -> ota_manager_write_chunk() -> ota_manager_finish() -> omstart
//         -> efter omstart: ota_manager_mark_valid() (rollback-skydd)
// ============================================================================

#define OTA_MAX_URL_LEN        200
#define OTA_TASK_STACK_SIZE    8192
#define OTA_TASK_PRIORITY      3          // Högre än sensor_task (2)
#define OTA_URL_REQUIRED_PREFIX "https://" // Kräv TLS - broker är publik!
#define OTA_TOPIC_STATUS_STATE  "ota"

/** @brief Initierar OTA-subsystemet, loggar partition och firmware-version. */
esp_err_t ota_manager_init(void);

/**
 * @brief Markerar nuvarande firmware som giltig (avbryter rollback).
 *        Anropa när Wi-Fi + MQTT fungerar efter uppstart.
 */
esp_err_t ota_manager_mark_valid(void);

/**
 * @brief Startar OTA-uppdatering i en egen task (icke-blockerande).
 * @param url            HTTPS-URL till firmware .bin
 * @param sha256_hex     Valfri förväntad SHA-256 (64 hex-tecken), eller NULL
 * @return ESP_OK om tasken startades, ESP_ERR_INVALID_STATE om OTA redan pågår,
 *         ESP_ERR_INVALID_ARG vid ogiltig URL
 */
esp_err_t ota_manager_start_update(const char *url, const char *sha256_hex);

/** @brief true medan en uppdatering pågår. */
bool ota_manager_in_progress(void);

/** @brief Startar en OTA-session (esp_ota_begin mot nästa partition). */
esp_err_t ota_manager_begin(void);

/** @brief Skriver en inkommande firmware-dataström till OTA-flashpartitionen. */
esp_err_t ota_manager_write_chunk(const uint8_t *data, size_t length);

/** @brief Slutför OTA, validerar image och sätter boot-partition. */
esp_err_t ota_manager_finish(void);

/** @brief Avbryter pågående OTA-session utan att ändra boot-partition. */
void ota_manager_abort(void);

#ifdef __cplusplus
}
#endif

#endif // OTA_MANAGER_H