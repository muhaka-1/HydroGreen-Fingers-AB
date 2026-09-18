#include "http_server.h"
#include "web_dashboard_html.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "HTTP_SERVER";

static esp_err_t root_get_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, WEB_DASHBOARD_HTML, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t api_sensors_get_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "application/json");
    const char *mock_json = "{\"temp_inside\":23.2,\"humidity\":65.4,\"temp_water\":20.4,\"temp_outside\":19.8,\"alarm\":\"NORMAL\"}";
    return httpd_resp_send(req, mock_json, HTTPD_RESP_USE_STRLEN);
}

httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;
    httpd_handle_t server = NULL;

    ESP_LOGI(TAG, "Startar inbyggd HTTP-server på port %d", config.server_port);

    httpd_uri_t root_uri = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = root_get_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t api_uri = {
        .uri       = "/api/sensors",
        .method    = HTTP_GET,
        .handler   = api_sensors_get_handler,
        .user_ctx  = NULL
    };

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &root_uri);
        httpd_register_uri_handler(server, &api_uri);
        ESP_LOGI(TAG, "HTTP Server startad! Endpoints: GET / och GET /api/sensors");
        return server;
    }

    ESP_LOGE(TAG, "Kunde inte starta HTTP Server");
    return NULL;
}

void stop_webserver(httpd_handle_t server) {
    if (server) {
        httpd_stop(server);
    }
}
