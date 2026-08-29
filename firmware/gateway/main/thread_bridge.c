#include "thread_bridge.h"

esp_err_t cldt_thread_bridge_init(const cldt_thread_bridge_config_t *config)
{
    (void)config;

    /*
     * IMPLEMENTATION TODO: validate callback, context, and listen port; confirm
     * the upstream border router and RCP are initialized and attached; then bind
     * one project UDP socket. The receive callback must copy or enqueue a bounded
     * datagram plus source metadata and return promptly. Do not retain pointers
     * owned by OpenThread, and make RCP/Thread detach visible to gateway runtime.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_thread_bridge_send(
    const uint8_t destination_ipv6[16],
    const uint8_t *datagram,
    size_t datagram_bytes)
{
    (void)destination_ipv6;
    (void)datagram;
    (void)datagram_bytes;

    /*
     * IMPLEMENTATION TODO: require a non-null 16-byte destination and one bounded
     * datagram, verify protocol size before taking any OpenThread API lock, send
     * exactly one datagram, and return a precise local send status. This function
     * consumes no caller buffer ownership; caller may reuse its memory after return
     * only if the upstream API has copied it. Document that behavior explicitly.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_thread_bridge_snapshot(
    uint8_t *output,
    size_t output_capacity,
    size_t *output_bytes)
{
    (void)output;
    (void)output_capacity;
    (void)output_bytes;

    /*
     * IMPLEMENTATION TODO: require output/output_bytes, acquire the OpenThread
     * lock briefly, serialize only the selected current role, partition, parent,
     * and neighbor/link fields into caller-owned bytes, then release the lock.
     * Bound every list and output length; a partial snapshot must be marked as
     * partial rather than presented as complete topology evidence.
     */
    return ESP_ERR_NOT_SUPPORTED;
}
