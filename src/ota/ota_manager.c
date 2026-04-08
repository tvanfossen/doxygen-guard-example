/** @participant OTA Manager */
/**
 * @brief Initialize OTA manager event handlers.
 * @version 1.0
 * @req REQ-0040
 */
void OTA_Init(void) {
    Event_register(EVENT_CLOUD_OTA_AVAILABLE, OTA_OnUpdateAvailable);
    Event_register(EVENT_COMM_CHUNK_RECEIVED, OTA_OnChunkReceived);
    Event_register(EVENT_COMM_DOWNLOAD_COMPLETE, OTA_OnDownloadComplete);
}

/**
 * @brief Handle cloud notification of available firmware update.
 * @version 1.1
 * @req REQ-0040
 * @req REQ-PROD-003
 * @after REQ-0020
 * @note OTA_STATE_CHANGE
 */
void OTA_OnUpdateAvailable(const char *version, const char *url) {
    ota_state = OTA_DOWNLOADING;
    event_post(EVENT_COMM_DOWNLOAD_START, url);
}

/**
 * @brief Process downloaded firmware chunk and write to flash.
 * @version 1.0
 * @req REQ-0040
 */
void OTA_OnChunkReceived(const uint8_t *data, size_t len) {
    event_post(EVENT_HW_FLASH_WRITE, data);
    bytes_written += len;
}

/**
 * @brief Verify firmware integrity after download completes.
 * @version 1.0
 * @req REQ-0040
 * @note OTA_VERIFY_CRC
 */
void OTA_OnDownloadComplete(void) {
    int valid = verify_crc(flash_base, bytes_written);
    status_t status = build_status(valid ? OTA_SUCCESS : OTA_FAILED);
    Comm_SendStatus(&status);
    event_post(EVENT_CLOUD_OTA_RESULT, valid);
}

/**
 * @brief Query current OTA progress for status reporting.
 * @version 1.1
 * @utility
 * @utility REQ-0040
 */
int OTA_GetProgress(void) {
    return (bytes_written * 100) / total_size;
}
