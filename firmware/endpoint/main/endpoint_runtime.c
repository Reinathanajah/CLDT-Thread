#include "endpoint_runtime.h"

esp_err_t cldt_endpoint_runtime_init(cldt_endpoint_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: reject a null runtime, clear caller-owned state, load
     * immutable board identity and role, generate a boot ID that changes after a
     * reset, and load the integrity-checked durable replay record containing the
     * enrolled run, coordinator boot identity, and highest accepted epoch. A
     * missing or corrupt record leaves
     * replay_state_valid false: retain the compiled safe policy and require an
     * explicitly commissioned new unique run before remote apply. Create every
     * steady-state queue, trace buffer, event group, and task storage statically
     * and leave the state at BOOT. No radio attach, workload release, or dynamic
     * allocation is permitted here. Fail before changing externally visible
     * state on any error.
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
     * 2. Decode and authenticate it; require coordinator authority node ID 0 and
     *    the coordinator boot/session identity commissioned for this run, the
     *    enrolled run ID, a valid durable replay state, a strictly newer epoch,
     *    a live TTL, and endpoint-local limits. Map received_local_us into the
     *    gateway monotonic domain through the validated clock-sync state and
     *    reject excessive uncertainty; never compare unrelated local clocks.
     *    The command boot ID identifies the coordinator process, not this
     *    endpoint and not replay state. A host decision is not local authorization.
     * 3. Atomically persist the new (run_id, coordinator_boot_id, highest_epoch)
     *    before publishing
     *    one immutable policy snapshot at a workload release boundary. If the
     *    durable write fails, reject and retain the safe policy. A duplicate
     *    accepted epoch must be acknowledged as duplicate, never applied twice.
     * 4. Emit a trace record and an acknowledgement for every accept or reject
     *    reason. On missing/corrupt replay state or any ambiguity, preserve the
     *    safe policy, enter FALLBACK, and require a newly commissioned run.
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
