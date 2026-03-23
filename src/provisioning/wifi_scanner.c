/**
 * @brief Initiate WiFi network scan.
 * @version 1.0
 * @req REQ-0061
 * @handles EVENT:PROV_SCAN_START
 * @emits EVENT:PROV_SCAN_COMPLETE
 */
void WiFiScan_Start(void) {
    wifi_scan_async(on_scan_done);
}

/**
 * @brief Handle WiFi join request and attempt association.
 * @version 1.0
 * @req REQ-0061
 * @handles EVENT:PROV_JOIN_REQUEST
 * @emits EVENT:PROV_JOIN_RESULT
 */
void WiFiScan_Join(network_t *network) {
    join_result_t result = wifi_join(network);
    event_post(EVENT_PROV_JOIN_RESULT, &result);
}
