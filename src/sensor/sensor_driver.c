/**
 * @brief Read raw temperature from the sensor hardware.
 * @version 1.0
 * @req REQ-0010
 * @emits EVENT:SENSOR_DATA_READY
 */
int Sensor_ReadTemperature(void) {
    int raw = hw_read_adc(TEMP_CHANNEL);
    event_post(EVENT_SENSOR_DATA_READY, raw);
    return raw;
}

/**
 * @brief Read raw humidity from the sensor hardware.
 * @version 1.0
 * @req REQ-0011
 * @emits EVENT:SENSOR_DATA_READY
 */
int Sensor_ReadHumidity(void) {
    int raw = hw_read_adc(HUMIDITY_CHANNEL);
    event_post(EVENT_SENSOR_DATA_READY, raw);
    return raw;
}

/**
 * @brief Calibrate sensor with factory offsets.
 * @version 1.0
 * @req REQ-0012
 * @ext controller::Controller_GetCalibration
 */
void Sensor_Calibrate(void) {
    calibration_t cal = Controller_GetCalibration();
    apply_offset(cal.temp_offset, cal.humidity_offset);
}
