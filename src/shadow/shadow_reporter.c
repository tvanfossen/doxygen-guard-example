/** @participant IoT Library */

/**
 * @brief Forward MCU product status to cloud shadow.
 * @version 1.0
 * @req REQ-0100
 * @req REQ-0102
 * @receives DURABLE:product_status
 * @calls cloud::CloudMgr_Publish
 * @loop "as product status changes"
 */
void on_product_status(const product_status_t *status) {
    shadow_report_t report = format_shadow(status);
    CloudMgr_Publish("shadow/reported", &report, sizeof(report));
}

/**
 * @brief Forward clean cycle summary to cloud.
 * @version 1.0
 * @req REQ-0100
 * @receives DURABLE:cycle_complete
 * @calls cloud::CloudMgr_Publish
 * @group "cycle summary"
 */
void on_cycle_complete(const cycle_summary_t *summary) {
    summary_report_t report = format_summary(summary);
    CloudMgr_Publish("mapping/runcomplete", &report, sizeof(report));
}

/**
 * @brief Forward error notification to cloud.
 * @version 1.0
 * @req REQ-0103
 * @receives DURABLE:error_report
 * @calls cloud::CloudMgr_Publish
 */
void on_error_report(const error_info_t *error) {
    CloudMgr_Publish("device/error", error, sizeof(*error));
}
