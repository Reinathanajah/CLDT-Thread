#include "gateway_provisioning.h"

esp_err_t cldt_gateway_provisioning_load(
    cldt_gateway_credentials_t *output,
    bool *is_provisioned)
{
    (void)output;
    (void)is_provisioned;

    /*
     * IMPLEMENTATION TODO: initialize the approved NVS namespace, read only
     * project-owned keys into bounded temporary buffers, validate lengths and
     * NUL termination before copying to output, and report provisioned false for
     * incomplete data. Never print SSID, passphrase, broker URI credentials, or
     * command key. Zero temporary secret buffers on every error and success path.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_gateway_provisioning_start_ble(void)
{
    /*
     * IMPLEMENTATION TODO: expose only the characteristics needed to provision
     * gateway identity, Wi-Fi credentials, broker endpoint, and command trust
     * material; require explicit local physical presence before advertising; and
     * use authenticated pairing or a documented secure enrollment procedure. Bound
     * every write length, reject reads of secrets, and persist only after complete
     * validation. BLE is provisioning-only and never carries measured telemetry.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_gateway_provisioning_stop_ble(void)
{
    /*
     * IMPLEMENTATION TODO: stop advertising and GATT service, disconnect active
     * clients, zero temporary pairing and credential buffers, release NimBLE
     * resources as required by ESP-IDF, and emit only a non-sensitive state
     * transition. Require this operation before a measured run so BLE coexistence
     * cannot become an undocumented 2.4 GHz treatment variable.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_gateway_provisioning_erase(void)
{
    /*
     * IMPLEMENTATION TODO: sample a designated physical button with debounce and
     * a long-press confirmation window, visibly indicate pending erase without
     * exposing secrets, delete only the project's NVS namespace, zero in-memory
     * copies, and reboot into unprovisioned state. MQTT, HTTP, and BLE must never
     * be able to invoke this operation remotely.
     */
    return ESP_ERR_NOT_SUPPORTED;
}
