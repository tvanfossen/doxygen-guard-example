/**
 * @brief Enqueue an inbound event from the MCU for async processing.
 * @version 1.0
 * @req REQ-0030
 * @emits EVENT:MSG_QUEUED
 */
void MsgBus_QueueInbound(msg_event_t event_id) {
    msg_t msg = { .event_id = event_id };
    queue_send(&inbound_queue, &msg);
    event_post(EVENT_MSG_QUEUED, 0);
}

/**
 * @brief Dequeue and dispatch inbound events to registered callbacks.
 * @version 1.0
 * @req REQ-0030
 * @handles EVENT:MSG_QUEUED
 * @ext comm::Comm_SendStatus
 * @triggers MSG_DISPATCH_CYCLE
 */
void MsgBus_ProcessQueue(void) {
    msg_t msg;
    while (queue_receive(&inbound_queue, &msg)) {
        if (msg.event_id == MSG_EVENT_STATUS_REQUEST) {
            status_t status = build_current_status();
            Comm_SendStatus(&status);
        } else if (my_eventCb) {
            my_eventCb(msg.event_id, NULL);
        }
    }
}

/**
 * @brief Register the MCU event callback for message dispatch.
 * @version 1.0
 * @req REQ-0030
 * @utility
 */
void MsgBus_RegisterCallback(msg_event_cb callback) {
    my_eventCb = callback;
}

/**
 * @brief Register transport-layer callbacks for outbound data.
 * @version 1.0
 * @req REQ-0030
 * @utility
 */
void MsgBus_RegisterTransportCbs(transport_data_cb data_cb, transport_state_cb state_cb) {
    s_transport_data_cb = data_cb;
    s_transport_state_cb = state_cb;
}
