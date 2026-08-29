#include "fidelity_gate.h"

cldt_status_t cldt_fidelity_gate_init(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    uint64_t now_host_us)
{
    (void)gate;
    (void)limits;
    (void)now_host_us;

    /*
     * IMPLEMENTATION TODO: reject null pointers and nonsensical limits, set the
     * state to COLD, reason to TOO_FEW_SAMPLES, consecutive passes to zero, and
     * state_entered_host_us to now_host_us. All thresholds must come from a
     * versioned calibration decision, not from a favorable test trace. No host
     * command is allowed while this state has not reached TRUSTED.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_fidelity_gate_evaluate(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    const cldt_fidelity_sample_t *sample,
    uint64_t now_host_us,
    bool *actuation_allowed)
{
    (void)gate;
    (void)limits;
    (void)sample;
    (void)now_host_us;
    (void)actuation_allowed;

    /*
     * IMPLEMENTATION TODO:
     * 1. Evaluate sample count, age, model lag, residual, interval coverage,
     *    clock uncertainty, and calibrated-region membership in a fixed order.
     * 2. Any hard failure immediately enters ABSTAIN and sets actuation_allowed
     *    false. Record the first failing reason rather than replacing it with a
     *    generic value.
     * 3. A passing sample moves COLD to OBSERVE; only the configured number of
     *    consecutive passing windows moves OBSERVE to TRUSTED.
     * 4. Recovery from ABSTAIN must pass through OBSERVE. This asymmetric rule
     *    prevents a single clean sample from re-enabling control after drift.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

void cldt_fidelity_gate_invalidate(
    cldt_fidelity_gate_t *gate,
    cldt_gate_reason_t reason,
    uint64_t now_host_us)
{
    (void)gate;
    (void)reason;
    (void)now_host_us;

    /*
     * IMPLEMENTATION TODO: use this for a new run, changed model revision, or
     * explicit reset. Clear pass history, set the supplied reason, transition to
     * COLD, timestamp the transition, and increment the transition counter only
     * when state or reason actually changes. It is intentionally void because
     * callers must not ignore a safety invalidation merely to handle an error.
     */
}
