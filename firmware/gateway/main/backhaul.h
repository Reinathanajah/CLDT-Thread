#ifndef CLDT_GATEWAY_BACKHAUL_H
#define CLDT_GATEWAY_BACKHAUL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#include "cldt/cldt_types.h"
#include "gateway_provisioning.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*cldt_backhaul_command_fn)(
    void *context,
    const uint8_t *payload,
    size_t payload_bytes,
    bool retained,
    uint64_t received_local_us);

typedef struct {
    const cldt_gateway_credentials_t *credentials;
    cldt_backhaul_command_fn on_command;
    void *callback_context;
} cldt_backhaul_config_t;

esp_err_t cldt_backhaul_init(const cldt_backhaul_config_t *config);
esp_err_t cldt_backhaul_start(void);

/* Publishes immutable observation bytes; caller retains ownership. */
esp_err_t cldt_backhaul_publish_observation(
    cldt_run_id_t run_id,
    cldt_node_id_t node_id,
    const uint8_t *payload,
    size_t payload_bytes);

/* Starts a local-only HTTP endpoint for a pending manifest, never telemetry. */
esp_err_t cldt_backhaul_start_manifest_server(void);

esp_err_t cldt_backhaul_stop(void);

#ifdef __cplusplus
}
#endif

#endif
