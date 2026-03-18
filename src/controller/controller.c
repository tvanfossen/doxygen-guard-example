/**
 * @brief Handle incoming sensor data and decide on control action.
 * @version 1.0
 * @req REQ-0010
 * @req REQ-0011
 * @handles EVENT:SENSOR_DATA_READY
 * @emits EVENT:CONTROL_ACTION
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
 * @req REQ-0020
 * @handles EVENT:CONTROL_ACTION
 * @ext comm::Comm_SendStatus
 */
void Controller_ReportStatus(int action) {
    status_t status = build_status(action);
    Comm_SendStatus(&status);
}
