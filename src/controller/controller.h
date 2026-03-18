/**
 * @brief Handle incoming sensor data and decide on control action.
 * @version 1.0
 */
void Controller_OnSensorData(int sensor_value);

/**
 * @brief Return current calibration offsets.
 * @version 1.0
 */
calibration_t Controller_GetCalibration(void);

/**
 * @brief Send control state to remote via comm manager.
 * @version 1.0
 */
void Controller_ReportStatus(int action);
