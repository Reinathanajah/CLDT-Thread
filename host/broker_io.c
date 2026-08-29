#include "broker_io.h"

cldt_status_t cldt_broker_io_open(
    cldt_broker_io_t *io,
    const char *host,
    uint16_t port,
    cldt_broker_message_fn callback,
    void *callback_context)
{
    (void)io;
    (void)host;
    (void)port;
    (void)callback;
    (void)callback_context;

    /*
     * IMPLEMENTATION TODO: validate host, port, callback, and context; create a
     * libmosquitto (or equally maintained) client with explicit protocol version,
     * TLS configuration when used, and a stable reconnect state machine. Subscribe
     * only to the private experiment namespace. The callback must enqueue or
     * return quickly; it must not update the model or write files directly.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_broker_io_poll(cldt_broker_io_t *io, uint32_t timeout_ms)
{
    (void)io;
    (void)timeout_ms;

    /*
     * IMPLEMENTATION TODO: validate io and cap timeout_ms to a small documented
     * value so coordinator deadlines are observed even during a quiet broker.
     * Translate broker reconnect, protocol, and backpressure conditions into
     * explicit CLDT statuses. Retained command delivery is a safety event, not a
     * convenient reconnect feature. Poll must never spin indefinitely.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_broker_io_publish(
    cldt_broker_io_t *io,
    const char *topic,
    const uint8_t *payload,
    size_t payload_bytes,
    uint8_t qos,
    bool retained)
{
    (void)io;
    (void)topic;
    (void)payload;
    (void)payload_bytes;
    (void)qos;
    (void)retained;

    /*
     * IMPLEMENTATION TODO: reject null/oversized input and out-of-range QoS;
     * require QoS 1 for durable observations as selected by the final design;
     * reject retained payloads on command topics; and expose publish queue or
     * reconnect pressure to the coordinator. The broker adapter must not invent
     * retries that extend a policy past its TTL.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

void cldt_broker_io_close(cldt_broker_io_t *io)
{
    (void)io;

    /*
     * IMPLEMENTATION TODO: unsubscribe, disconnect with a bounded deadline,
     * destroy only the native client owned by io, clear callbacks and connected
     * state, and leave raw run files to the recorder. Closing the broker must be
     * safe after a partial open and must not make a disconnected run look valid.
     */
}
