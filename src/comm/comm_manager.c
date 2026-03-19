/**
 * @brief Send device status over MQTT.
 * @version 1.0
 * @req REQ-0020
 * @emits EVENT:COMM_TX_COMPLETE
 */
void Comm_SendStatus(const status_t *status) {
    mqtt_publish(STATUS_TOPIC, status, sizeof(*status));
    event_post(EVENT_COMM_TX_COMPLETE, 0);
}

/**
 * @brief Handle incoming remote command.
 * @version 1.0
 * @req REQ-0021
 * @req REQ-PROD-002
 * @handles EVENT:COMM_RX_RECEIVED
 * @emits EVENT:CONTROL_ACTION
 */
void Comm_OnRemoteCommand(const command_t *cmd) {
    int action = parse_command(cmd);
    event_post(EVENT_CONTROL_ACTION, action);
}

/**
 * @brief Initiate firmware download from cloud URL.
 * @version 1.0
 * @req REQ-0041
 * @req REQ-PROD-003
 * @handles EVENT:COMM_DOWNLOAD_START
 * @emits EVENT:COMM_CHUNK_RECEIVED
 * @emits EVENT:COMM_DOWNLOAD_COMPLETE
 */
void Comm_DownloadFirmware(const char *url) {
    http_stream_t stream = http_get(url);
    while (http_has_data(&stream)) {
        event_post(EVENT_COMM_CHUNK_RECEIVED, http_read(&stream));
    }
    event_post(EVENT_COMM_DOWNLOAD_COMPLETE, 0);
}
