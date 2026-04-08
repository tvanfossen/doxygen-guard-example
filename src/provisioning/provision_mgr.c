/** @participant Provisioning Manager */
/**
 * @brief Initialize provisioning manager event handlers.
 * @version 1.0
 * @req REQ-0060
 */
void Provision_Init(void) {
    Event_register(EVENT_FACTORY_RESET_COMPLETE, Provision_Start);
    Event_register(EVENT_PROV_SCAN_COMPLETE, Provision_OnScanComplete);
    Event_register(EVENT_PROV_JOIN_RESULT, Provision_OnJoinResult);
    Event_register(EVENT_PROV_CERT_INSTALLED, Provision_OnCertInstalled);
}

/**
 * @brief Begin device provisioning after factory reset.
 * @version 1.0
 * @req REQ-0060
 * @note PROV_STATE_INIT
 */
void Provision_Start(void) {
    prov_state = PROV_SCANNING;
    event_post(EVENT_PROV_SCAN_START, NULL);
}

/**
 * @brief Handle scan results and attempt network join.
 * @version 1.0
 * @req REQ-0060
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
 * @note PROV_RETRY_CHECK
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
 * @note PROV_STATE_READY
 */
void Provision_OnCertInstalled(void) {
    prov_state = PROV_COMPLETE;
    Comm_SendStatus(&prov_status);
    event_post(EVENT_PROV_COMPLETE, NULL);
}
