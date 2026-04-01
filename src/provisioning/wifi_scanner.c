/** @module WiFi Scanner */
/**
 * @brief Initialize WiFi scanner event handlers.
 * @version 1.0
 * @req REQ-0061
 */
void WiFiScan_Init(void) {
    Event_register(EVENT_PROV_SCAN_START, WiFiScan_Start);
    Event_register(EVENT_PROV_JOIN_REQUEST, WiFiScan_Join);
}

/**
 * @brief Initiate WiFi network scan.
 * @version 1.0
 * @req REQ-0061
 */
void WiFiScan_Start(void) {
    wifi_scan_async(on_scan_done);
}

/**
 * @brief Handle WiFi join request and attempt association.
 * @version 1.0
 * @req REQ-0061
 */
void WiFiScan_Join(network_t *network) {
    join_result_t result = wifi_join(network);
    event_post(EVENT_PROV_JOIN_RESULT, &result);
}
