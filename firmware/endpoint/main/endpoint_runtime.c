#include "endpoint_runtime.h"

esp_err_t cldt_endpoint_runtime_init(cldt_endpoint_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: reject a null runtime, clear caller-owned state, load
     * immutable board identity and role, generate a boot ID that changes after a
     * reset, and create every steady-state queue, trace buffer, event group, and
     * task storage statically. Initialize the compiled safe policy and leave the
     * state at BOOT. No radio attach, workload release, or dynamic allocation is
     * permitted here. Fail before changing externally visible state on any error.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_endpoint_runtime_start(cldt_endpoint_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: require successful initialization, then start the
     * supervisor task first. It owns transitions through commissioning, attach,
     * idle, running, fallback, and fault. Start transport, workload, trace, and
     * optional power tasks only after the supervisor reports their prerequisites;
     * if any task creation fails, notify supervisor to unwind already started
     * components. Do not start release timers merely because Thread attached.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_endpoint_runtime_receive_command(
    cldt_endpoint_runtime_t *runtime,
    const uint8_t *datagram,
    size_t datagram_bytes,
    uint64_t received_local_us)
{
    (void)runtime;
    (void)datagram;
    (void)datagram_bytes;
    (void)received_local_us;

    /*
     * IMPLEMENTATION TODO:
     * 1. Copy or retain the datagram only for the duration required by the
     *    decoder; reject oversized input before queueing work.
     * 2. Decode and authenticate it, validate run ID, boot context, epoch, TTL,
     *    and endpoint-local limits. A host decision is not local authorization.
     * 3. Apply one immutable policy snapshot only at a workload release boundary.
     *    A duplicate accepted epoch must be acknowledged as duplicate, never
     *    applied twice.
     * 4. Emit a trace record and an acknowledgement for every accept or reject
     *    reason. On ambiguity, preserve the safe policy and enter FALLBACK.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_endpoint_runtime_request_stop(cldt_endpoint_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: request a supervisor-owned stop, block new workload
     * releases, let producer and transport finish or explicitly expire queued
     * work, request final counters, and reconcile before changing state to IDLE.
     * A stopped endpoint must retain its safe policy and remain able to report
     * health. Do not delete a task from an arbitrary caller or discard evidence
     * merely to make shutdown appear fast.
     */
    return ESP_ERR_NOT_SUPPORTED;
}
