/**
 * @brief Request and install device certificate from provisioning server.
 * @version 1.0
 * @req REQ-0062
 * @handles EVENT:PROV_CERT_REQUEST
 * @emits EVENT:PROV_CERT_INSTALLED
 */
void Cert_Provision(void) {
    cert_t cert = https_fetch_cert(PROV_SERVER_URL);
    flash_write_cert(&cert);
    event_post(EVENT_PROV_CERT_INSTALLED, NULL);
}
