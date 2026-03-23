/**
 * @brief Begin device provisioning after factory reset.
 * @version 1.0
 * @req REQ-0060
 * @handles EVENT:FACTORY_RESET_COMPLETE
 * @emits EVENT:PROV_SCAN_START
 * @triggers PROV_STATE_INIT
 */
void Provision_Start(void) {
    prov_state = PROV_SCANNING;
    event_post(EVENT_PROV_SCAN_START, NULL);
}

/**
 * @brief Handle scan results and attempt network join.
 * @version 1.0
 * @req REQ-0060
 * @handles EVENT:PROV_SCAN_COMPLETE
 * @emits EVENT:PROV_JOIN_REQUEST
 * @emits EVENT:PROV_FAILED
 */
void Provision_OnScanComplete(scan_result_t *results, int count) {
    if (count > 0) {
        network_t *best = select_best_network(results, count);
        event_post(EVENT_PROV_JOIN_REQUEST, best);
    } else {
        event_post(EVENT_PROV_FAILED, NULL);
    }
}

/**
 * @brief Handle network join result with retry logic.
 * @version 1.0
 * @req REQ-0060
 * @handles EVENT:PROV_JOIN_RESULT
 * @emits EVENT:PROV_CERT_REQUEST
 * @emits EVENT:PROV_SCAN_START
 * @triggers PROV_RETRY_CHECK
 */
void Provision_OnJoinResult(join_result_t *result) {
    if (result->success) {
        event_post(EVENT_PROV_CERT_REQUEST, NULL);
    } else {
        if (retry_count < MAX_RETRIES) {
            retry_count++;
            event_post(EVENT_PROV_SCAN_START, NULL);
        }
    }
}

/**
 * @brief Handle certificate provisioning and finalize.
 * @version 1.0
 * @req REQ-0060
 * @handles EVENT:PROV_CERT_INSTALLED
 * @ext comm::Comm_SendStatus
 * @emits EVENT:PROV_COMPLETE
 * @triggers PROV_STATE_READY
 */
void Provision_OnCertInstalled(void) {
    prov_state = PROV_COMPLETE;
    Comm_SendStatus(&prov_status);
    event_post(EVENT_PROV_COMPLETE, NULL);
}
