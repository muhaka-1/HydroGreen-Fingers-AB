idf_component_register(
    SRCS 
        "main.c"
        # 1. Malek Chahin (Lead Embedded & Sensors)
        "sensors/bme280_driver.c"
        "sensors/ds18b20_driver.c"
        "sensors/alarm_limits.c"
        "sensors/sensor_task.c"
        # 2. Mohammad (IoT & Cloud Engineer)
        "mqtt/wifi_manager.c"
        "mqtt/mqtt_client.c"
        "mqtt/json_serializer.c"
        "mqtt/mqtt_task.c"
        # 3. Emil (Web & UI Engineer)
        "webserver/http_server.c"
        "webserver/webserver_task.c"
        # 4. Jemi (DevOps & Security Engineer)
        "ota/ota_manager.c"
        "ota/nvs_storage.c"
        # 5. Simon (QA & Test Automation Lead)
        "testing/sensor_mocks.c"
        "testing/test_runner.c"
    INCLUDE_DIRS 
        "."
        "sensors"
        "mqtt"
        "webserver"
        "ota"
        "testing"
    REQUIRES 
        nvs_flash 
        driver 
        esp_timer 
        esp_event
        esp_http_server
        app_update
        mqtt
        esp_wifi
        esp_netif
)
