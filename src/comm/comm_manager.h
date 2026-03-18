/**
 * @brief Send device status over MQTT.
 * @version 1.0
 */
void Comm_SendStatus(const status_t *status);

/**
 * @brief Handle incoming remote command.
 * @version 1.0
 */
void Comm_OnRemoteCommand(const command_t *cmd);
