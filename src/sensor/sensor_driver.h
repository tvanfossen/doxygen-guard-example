/**
 * @brief Read raw temperature from the sensor hardware.
 * @version 1.0
 */
int Sensor_ReadTemperature(void);

/**
 * @brief Read raw humidity from the sensor hardware.
 * @version 1.0
 */
int Sensor_ReadHumidity(void);

/**
 * @brief Calibrate sensor with factory offsets.
 * @version 1.0
 */
void Sensor_Calibrate(void);
