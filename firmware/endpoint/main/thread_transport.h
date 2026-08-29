#ifndef CLDT_ENDPOINT_THREAD_TRANSPORT_H
#define CLDT_ENDPOINT_THREAD_TRANSPORT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*cldt_endpoint_command_fn)(
    void *context,
    const uint8_t *datagram,
    size_t datagram_bytes,
    uint64_t received_local_us);

typedef struct {
    uint16_t local_port;
    uint16_t gateway_port;
    uint8_t gateway_ipv6[16];
    cldt_endpoint_command_fn on_command;
    void *callback_context;
} cldt_thread_transport_config_t;

esp_err_t cldt_thread_transport_init(
    const cldt_thread_transport_config_t *config);

/* Caller retains slot ownership until the completion result is returned. */
esp_err_t cldt_thread_transport_send(
    const uint8_t *datagram,
    size_t datagram_bytes,
    uint32_t timeout_ms);

esp_err_t cldt_thread_transport_get_link(
    int8_t *rssi_dbm,
    uint8_t *link_quality,
    uint8_t *thread_role,
    uint32_t *partition_id);

esp_err_t cldt_thread_transport_stop(void);

#ifdef __cplusplus
}
#endif

#endif
