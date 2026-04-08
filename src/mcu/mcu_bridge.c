/** @participant IoT Library */

/**
 * @brief Execute clean command — send drive settings to MCU.
 * @version 1.0
 * @req REQ-0100
 * @receives EVENT_CLEAN_CMD
 * @calls mcu::DurableEventCb
 */
void execute_clean(const clean_params_t *params) {
    drive_info_t info = {
        .fan = params->fan_speed,
        .brush = params->brush_mode,
        .water = params->water_level,
    };
    DurableEventCb(DURABLE_IN_EVENT_SET_DRIVE, &info);
}

/**
 * @brief Execute dock command — send return-to-base to MCU.
 * @version 1.0
 * @req REQ-0102
 * @receives EVENT_DOCK_CMD
 * @calls mcu::DurableEventCb
 */
void execute_dock(void) {
    DurableEventCb(DURABLE_IN_EVENT_DOCK, NULL);
}

/**
 * @brief Apply setting change to MCU configuration.
 * @version 1.0
 * @req REQ-0101
 * @receives EVENT_SETTING_CHANGE
 * @calls mcu::DurableEventCb
 * @calls cloud::CloudMgr_Publish
 */
void apply_setting(const setting_t *setting) {
    config_update_t update = { .key = setting->key, .value = setting->value };
    DurableEventCb(DURABLE_IN_EVENT_CONFIG, &update);
    CloudMgr_Publish("shadow/reported", &update, sizeof(update));
}
