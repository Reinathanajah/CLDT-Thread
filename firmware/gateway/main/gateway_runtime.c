#include "gateway_runtime.h"

esp_err_t cldt_gateway_runtime_init(cldt_gateway_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: reject a null runtime, clear state, load gateway node
     * identity, initialize the sole policy guard with its compiled safe policy,
     * and create all queues, event groups, trace storage, timer, and task stacks
     * statically. A new gateway boot has no resumable command-forwarding run;
     * remote actuation remains disarmed until a newly ledger-reserved run is
     * admitted.
     * Choose queue lengths from measured producer rates and document each owner.
     * Do not start Thread, Wi-Fi, BLE, broker, or any task here. An initialization
     * failure must leave the device in BOOT with no partially live project task.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_gateway_runtime_start(cldt_gateway_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: require successful init and all external prerequisites
     * (provisioning, RCP, Thread attach, backhaul readiness as required), start
     * supervisor first, verify admission of a newly ledger-reserved run, bind the
     * guard to it, then start aggregator and publisher under supervisor control.
     * Never resume authenticated command forwarding for a pre-reboot run. Give
     * each task a narrow ownership contract and measure stack margin before
     * choosing final priority/core affinity. If a later task fails, supervisor
     * stops earlier tasks in reverse order and emits a fault record rather than
     * continuing half-up.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_gateway_runtime_request_stop(cldt_gateway_runtime_t *runtime)
{
    (void)runtime;

    /*
     * IMPLEMENTATION TODO: set a supervisor event or task notification only. The
     * supervisor must stop manifest admission, command forwarding, and periodic
     * publication in a defined sequence, then request final endpoint counters and
     * emit final gateway status. Direct vTaskDelete from a caller would bypass
     * queue ownership and make accounting loss impossible to diagnose.
     */
    return ESP_ERR_NOT_SUPPORTED;
}
