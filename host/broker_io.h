#ifndef CLDT_HOST_BROKER_IO_H
#define CLDT_HOST_BROKER_IO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*cldt_broker_message_fn)(
    void *context,
    const char *topic,
    const uint8_t *payload,
    size_t payload_bytes,
    uint64_t received_host_us,
    bool retained);

typedef struct {
    void *native_client;
    cldt_broker_message_fn on_message;
    void *callback_context;
    bool connected;
} cldt_broker_io_t;

cldt_status_t cldt_broker_io_open(
    cldt_broker_io_t *io,
    const char *host,
    uint16_t port,
    cldt_broker_message_fn callback,
    void *callback_context);

cldt_status_t cldt_broker_io_poll(cldt_broker_io_t *io, uint32_t timeout_ms);

cldt_status_t cldt_broker_io_publish(
    cldt_broker_io_t *io,
    const char *topic,
    const uint8_t *payload,
    size_t payload_bytes,
    uint8_t qos,
    bool retained);

void cldt_broker_io_close(cldt_broker_io_t *io);

#ifdef __cplusplus
}
#endif

#endif
