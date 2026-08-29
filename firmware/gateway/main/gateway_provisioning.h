#ifndef CLDT_GATEWAY_PROVISIONING_H
#define CLDT_GATEWAY_PROVISIONING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_WIFI_SSID_MAX_BYTES 32U
#define CLDT_WIFI_PASSPHRASE_MAX_BYTES 64U
#define CLDT_BROKER_URI_MAX_BYTES 128U
#define CLDT_COMMAND_KEY_BYTES 32U

typedef struct {
    char wifi_ssid[CLDT_WIFI_SSID_MAX_BYTES + 1U];
    char wifi_passphrase[CLDT_WIFI_PASSPHRASE_MAX_BYTES + 1U];
    char broker_uri[CLDT_BROKER_URI_MAX_BYTES];
    uint8_t command_key[CLDT_COMMAND_KEY_BYTES];
    uint32_t node_id;
} cldt_gateway_credentials_t;

/* Loads validated credentials from encrypted/protected NVS where available. */
esp_err_t cldt_gateway_provisioning_load(
    cldt_gateway_credentials_t *output,
    bool *is_provisioned);

/*
 * Runs a temporary authenticated BLE GATT service. The implementation must
 * require physical presence, bound every characteristic, and stop advertising
 * before a measured run begins.
 */
esp_err_t cldt_gateway_provisioning_start_ble(void);

esp_err_t cldt_gateway_provisioning_stop_ble(void);

/* Erasure must require a deliberate local action; never expose it over MQTT. */
esp_err_t cldt_gateway_provisioning_erase(void);

#ifdef __cplusplus
}
#endif

#endif
