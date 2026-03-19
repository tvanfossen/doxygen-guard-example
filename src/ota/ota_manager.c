/**
 * @brief Handle cloud notification of available firmware update.
 * @version 1.0
 * @req REQ-0040
 * @req REQ-PROD-003
 * @handles EVENT:CLOUD_OTA_AVAILABLE
 * @emits EVENT:COMM_DOWNLOAD_START
 * @triggers OTA_STATE_CHANGE
 */
void OTA_OnUpdateAvailable(const char *version, const char *url) {
    ota_state = OTA_DOWNLOADING;
    event_post(EVENT_COMM_DOWNLOAD_START, url);
}

/**
 * @brief Process downloaded firmware chunk and write to flash.
 * @version 1.0
 * @req REQ-0040
 * @handles EVENT:COMM_CHUNK_RECEIVED
 * @emits EVENT:HW_FLASH_WRITE
 */
void OTA_OnChunkReceived(const uint8_t *data, size_t len) {
    event_post(EVENT_HW_FLASH_WRITE, data);
    bytes_written += len;
}

/**
 * @brief Verify firmware integrity after download completes.
 * @version 1.0
 * @req REQ-0040
 * @handles EVENT:COMM_DOWNLOAD_COMPLETE
 * @ext comm::Comm_SendStatus
 * @emits EVENT:CLOUD_OTA_RESULT
 * @triggers OTA_VERIFY_CRC
 */
void OTA_OnDownloadComplete(void) {
    int valid = verify_crc(flash_base, bytes_written);
    status_t status = build_status(valid ? OTA_SUCCESS : OTA_FAILED);
    Comm_SendStatus(&status);
    event_post(EVENT_CLOUD_OTA_RESULT, valid);
}

/**
 * @brief Query current OTA progress for status reporting.
 * @version 1.0
 * @req REQ-0040
 * @utility
 */
int OTA_GetProgress(void) {
    return (bytes_written * 100) / total_size;
}
