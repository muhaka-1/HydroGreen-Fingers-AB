idf_component_register(
    SRCS 
        "main.c"
        # Malek Chahin (Lead Embedded & Sensors)
        "sensors/bme280_driver.c"
        "sensors/ds18b20_driver.c"
        "sensors/alarm_limits.c"
        "sensors/sensor_task.c"
        # IoT Engineer (Network & Cloud Templates)
        "network/wifi_manager.c"
        "network/mqtt_client.c"
        "network/json_payload.c"
        "network/network_task.c"
    INCLUDE_DIRS 
        "."
        "sensors"
        "network"
    REQUIRES 
        nvs_flash 
        driver 
        esp_timer 
        esp_event
)
