/** @module Controller */
/**
 * @brief Initialize controller event handlers.
 * @version 1.0
 * @req REQ-0030
 */
void Controller_Init(void) {
    Event_register(EVENT_SENSOR_DATA_READY, Controller_OnSensorData);
    Event_register(EVENT_CONTROL_ACTION, Controller_ReportStatus);
}

/**
 * @brief Handle incoming sensor data and decide on control action.
 * @version 1.0
 * @req REQ-0030
 * @triggers THRESHOLD_CHECK
 */
void Controller_OnSensorData(int sensor_value) {
    if (sensor_value > threshold) {
        event_post(EVENT_CONTROL_ACTION, ACTION_COOL);
    }
}

/**
 * @brief Return current calibration offsets.
 * @version 1.0
 * @req REQ-0012
 */
calibration_t Controller_GetCalibration(void) {
    return current_calibration;
}

/**
 * @brief Send control state to remote via comm manager.
 * @version 1.0
 * @req REQ-0030
 * @req REQ-PROD-002
 */
void Controller_ReportStatus(int action) {
    status_t status = build_status(action);
    Comm_SendStatus(&status);
}
