/** @module Comm Manager */
/**
 * @brief Dispatch WiFi and MQTT events to update connectivity state.
 * @version 1.0
 * @req REQ-0020
 */
void Shadow_OnConnectivityEvent(uint64_t ev, void *data) {
    switch (ev) {
    case EVENT_WIFI_DISCONNECTED:
        set_wifi_connected(false);
        break;
    case EVENT_WIFI_CONNECTED:
        set_wifi_connected(true);
        break;
    case EVENT_MQTT_CONNACK:
        handle_mqtt_connack();
        break;
    case EVENT_MQTT_CLOSE:
        set_mqtt_connected(false);
        break;
    }
}

/**
 * @brief Register shadow event handlers with the event bus.
 * @version 1.0
 * @req REQ-0020
 */
void Shadow_Initialize(void) {
    Event_register(
        EVENT_WIFI_DISCONNECTED | EVENT_WIFI_CONNECTED |
        EVENT_MQTT_CONNACK | EVENT_MQTT_CLOSE,
        Shadow_OnConnectivityEvent
    );
}

/**
 * @brief Schedule config topic publish to cloud with short delay.
 * @version 1.1
 * @req REQ-0020
 * @assumes REQ-0030
 */
void Shadow_ScheduleConfigPublish(void) {
    timer_set(&config_publish_timer, CONFIG_PUBLISH_DELAY_MS,
              send_config_to_cloud, NULL);
}
