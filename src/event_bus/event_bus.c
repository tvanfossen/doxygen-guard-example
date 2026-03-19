/**
 * @brief Register an event handler for a bitmask of events.
 * @version 1.0
 * @req REQ-0050
 * @utility
 */
void Event_register(uint64_t event_mask, event_handler_fn handler) {
    for (int i = 0; i < MAX_HANDLERS; i++) {
        if (handler_table[i].handler == NULL) {
            handler_table[i].mask = event_mask;
            handler_table[i].handler = handler;
            return;
        }
    }
}

/**
 * @brief Post an event to all registered handlers matching the event bit.
 * @version 1.0
 * @req REQ-0050
 * @emits EVENT:DISPATCH_COMPLETE
 */
void Event_post(uint64_t event, void *data) {
    for (int i = 0; i < MAX_HANDLERS; i++) {
        if (handler_table[i].handler && (handler_table[i].mask & event)) {
            handler_table[i].handler(event, data);
        }
    }
    event_post(EVENT_DISPATCH_COMPLETE, 0);
}
