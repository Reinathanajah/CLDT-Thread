#include "thread_transport.h"

esp_err_t cldt_thread_transport_init(
    const cldt_thread_transport_config_t *config)
{
    (void)config;

    /*
     * IMPLEMENTATION TODO: validate ports, gateway IPv6 address, callback, and
     * context; start the supported ESP-IDF OpenThread integration; commission or
     * attach using provisioned Thread credentials; wait for an attached state;
     * then bind one project UDP socket. Copy callback configuration into owned
     * state. On any failure, close the socket and unwind OpenThread in reverse
     * order; do not invent a parallel mesh implementation.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_thread_transport_send(
    const uint8_t *datagram,
    size_t datagram_bytes,
    uint32_t timeout_ms)
{
    (void)datagram;
    (void)datagram_bytes;
    (void)timeout_ms;

    /*
     * IMPLEMENTATION TODO: reject null/oversized datagrams and zero or excessive
     * timeout values; transmit one whole UDP datagram; then return a precise send
     * outcome to the transport owner. UDP send success is not delivery success:
     * delivery acknowledgement and retry policy must be handled by the workload
     * state machine so counters distinguish sent, acknowledged, expired, and
     * dropped work. Never hold an OpenThread lock while waiting on a queue.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_thread_transport_get_link(
    int8_t *rssi_dbm,
    uint8_t *link_quality,
    uint8_t *thread_role,
    uint32_t *partition_id)
{
    (void)rssi_dbm;
    (void)link_quality;
    (void)thread_role;
    (void)partition_id;

    /*
     * IMPLEMENTATION TODO: require all output pointers, acquire the OpenThread
     * API lock only long enough to read current RSSI, link quality, role, and
     * partition ID, copy scalar values, then release it before returning. A
     * detached or unavailable role is a valid observable state and should return
     * a clear status or sentinel, not stale data from a previous attachment.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_thread_transport_stop(void)
{
    /*
     * IMPLEMENTATION TODO: reject new sends, unregister receive callbacks, close
     * the project UDP socket, then stop/deinitialize OpenThread as prescribed by
     * ESP-IDF. Clear internal callback state only after no callback can execute.
     * This order prevents a late OpenThread callback from dereferencing endpoint
     * runtime state that the supervisor has already reclaimed.
     */
    return ESP_ERR_NOT_SUPPORTED;
}
