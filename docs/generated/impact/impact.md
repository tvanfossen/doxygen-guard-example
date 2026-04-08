## Change Impact Report

| REQ | Name | Functions Changed |
|-----|------|-------------------|
| REQ-0020 | Remote Status Reporting | Shadow_ScheduleConfigPublish |
| REQ-0030 | Control Loop Processing | Controller_OnSensorData, MsgBus_ProcessQueue |
| REQ-0040 | OTA Firmware Update | OTA_OnUpdateAvailable, OTA_OnDownloadComplete |
| REQ-0060 | Device Provisioning | Provision_Start, Provision_OnJoinResult, Provision_OnCertInstalled |
| REQ-0100 | Start Clean Command | handle_cmd_request, send_cmd_response, execute_clean, on_product_status, on_cycle_complete |
| REQ-0101 | Device Setting Change | handle_shadow_delta, send_cmd_response, apply_setting |
| REQ-0102 | Dock Command | execute_dock, on_product_status |
| REQ-0103 | Error Reporting | on_error_report |
| REQ-PROD-003 | Over-the-Air Firmware Update | OTA_OnUpdateAvailable |

**Total: 9 requirement(s) affected, 20 function(s) changed**
