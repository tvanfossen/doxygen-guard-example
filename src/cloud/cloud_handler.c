/** @participant IoT Library */

/**
 * @brief Handle incoming MQTT command request from cloud.
 * @version 1.0
 * @req REQ-0100
 * @receives MQTT:cmd/req
 * @sends EVENT_CLEAN_CMD
 * @sends EVENT_DOCK_CMD
 * @note Command Dispatch
 */
void handle_cmd_request(const char *topic, const char *payload) {
    cmd_t cmd = parse_cmd_payload(payload);
    if (strcmp(cmd.state, "clean") == 0) {
        clean_params_t params = build_clean_params(&cmd);
        event_post(EVENT_CLEAN_CMD, &params);
    } else if (strcmp(cmd.state, "dock") == 0) {
        event_post(EVENT_DOCK_CMD, NULL);
    }
}

/**
 * @brief Handle incoming MQTT shadow delta from cloud.
 * @version 1.0
 * @req REQ-0101
 * @receives MQTT:shadow/desired
 * @sends EVENT_SETTING_CHANGE
 */
void handle_shadow_delta(const char *key, const char *value) {
    if (strcmp(key, "fanpower") == 0) {
        setting_t setting = { .key = key, .value = value };
        event_post(EVENT_SETTING_CHANGE, &setting);
    }
}

/**
 * @brief Send command acknowledgment back to cloud.
 * @version 1.0
 * @req REQ-0100
 * @req REQ-0101
 * @receives EVENT_CLEAN_CMD
 * @calls cloud::CloudMgr_Publish
 */
void send_cmd_response(int result_code) {
    response_t resp = build_response(result_code);
    CloudMgr_Publish("cmd/resp", &resp, sizeof(resp));
}
