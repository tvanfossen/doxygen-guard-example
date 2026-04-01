/** @module Cert Manager */
/**
 * @brief Initialize certificate manager event handlers.
 * @version 1.0
 * @req REQ-0062
 */
void Cert_Init(void) {
    Event_register(EVENT_PROV_CERT_REQUEST, Cert_Provision);
}

/**
 * @brief Request and install device certificate from provisioning server.
 * @version 1.0
 * @req REQ-0062
 */
void Cert_Provision(void) {
    cert_t cert = https_fetch_cert(PROV_SERVER_URL);
    flash_write_cert(&cert);
    event_post(EVENT_PROV_CERT_INSTALLED, NULL);
}
