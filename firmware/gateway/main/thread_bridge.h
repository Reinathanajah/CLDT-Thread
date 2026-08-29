#ifndef CLDT_GATEWAY_THREAD_BRIDGE_H
#define CLDT_GATEWAY_THREAD_BRIDGE_H

#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*cldt_thread_frame_fn)(
    void *context,
    const uint8_t *datagram,
    size_t datagram_bytes,
    const uint8_t source_ipv6[16],
    int8_t rssi_dbm,
    uint64_t received_local_us);

typedef struct {
    cldt_thread_frame_fn on_frame;
    void *callback_context;
    uint16_t listen_port;
} cldt_thread_bridge_config_t;

/* Attaches the project UDP adapter after the upstream border router is ready. */
esp_err_t cldt_thread_bridge_init(const cldt_thread_bridge_config_t *config);

esp_err_t cldt_thread_bridge_send(
    const uint8_t destination_ipv6[16],
    const uint8_t *datagram,
    size_t datagram_bytes);

/* Captures current role/partition/neighbor state into caller-owned output. */
esp_err_t cldt_thread_bridge_snapshot(
    uint8_t *output,
    size_t output_capacity,
    size_t *output_bytes);

#ifdef __cplusplus
}
#endif

#endif
