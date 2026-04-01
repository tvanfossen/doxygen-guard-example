/** @module Sensor Driver */
/**
 * @brief Read raw temperature from the sensor hardware.
 * @version 1.0
 * @req REQ-0010
 * @req REQ-PROD-001
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
 * @req REQ-PROD-001
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
 */
void Sensor_Calibrate(void) {
    calibration_t cal = Controller_GetCalibration();
    apply_offset(cal.temp_offset, cal.humidity_offset);
}
