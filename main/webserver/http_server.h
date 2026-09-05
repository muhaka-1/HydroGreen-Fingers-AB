#ifndef HTTP_SERVER_MODULE_H
#define HTTP_SERVER_MODULE_H

#include "esp_err.h"
#include "esp_http_server.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// MODUL: HTTP Server & REST API (Ansvar: Emil / Web & UI Engineer)
// ============================================================================

/**
 * @brief Startar den inbyggda HTTP-webbservern på port 80.
 * @return Hanterare för HTTP-servern, eller NULL vid fel.
 */
httpd_handle_t start_webserver(void);

/**
 * @brief Stoppar webbservern.
 */
void stop_webserver(httpd_handle_t server);

#ifdef __cplusplus
}
#endif

#endif // HTTP_SERVER_MODULE_H
