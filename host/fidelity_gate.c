#include "fidelity_gate.h"
#include <string.h>

cldt_status_t cldt_fidelity_gate_init(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    uint64_t now_host_us)
{
    if (!gate || !limits) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    gate->state = CLDT_GATE_COLD;
    gate->reason = CLDT_GATE_REASON_TOO_FEW_SAMPLES;
    
    return CLDT_OK;
}

cldt_status_t cldt_fidelity_gate_evaluate(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    const cldt_fidelity_sample_t *sample,
    uint64_t now_host_us,
    bool *actuation_allowed)
{
    // TODO: 4 states: COLD, OBSERVE, TRUSTED, ABSTAIN
    // TODO: COLD -> OBSERVE: first passing sample
    // TODO: OBSERVE -> TRUSTED: consecutive_passing_windows >= limits->passing_windows_to_trust
    // TODO: Any state -> ABSTAIN: any hard failure (immediately, first failing reason recorded)
    // TODO: ABSTAIN -> OBSERVE: first passing sample after failure (asymmetric hysteresis - single clean sample does NOT re-enable control)
    // TODO: OBSERVE -> OBSERVE: passing but not enough consecutive windows yet
    // TODO: TRUSTED -> TRUSTED: passing, actuation_allowed = true
    // TODO: Evaluation order (fixed): sample_count, observation_age, model_lag, residual, interval_coverage, clock_uncertainty, calibrated_region
    // TODO: Observation age: (now_host_us - sample->newest_observation_host_us) > limits->maximum_observation_age_ms * 1000
    // TODO: Kalman covariance integration: check P[2][2] (critical_pdr variance) against configured threshold. If Kalman uncertainty exceeds threshold, set ABSTAIN with reason CLDT_GATE_REASON_MODEL_LAG
    // TODO: Gate characterization plot data: record (timestamp, gate_state, reason, consecutive_passes, P[2][2]) per evaluation for post-hoc analysis
    
    return CLDT_ERR_NOT_IMPLEMENTED;
}

void cldt_fidelity_gate_invalidate(
    cldt_fidelity_gate_t *gate,
    cldt_gate_reason_t reason,
    uint64_t now_host_us)
{
    if (!gate) {
        return;
    }
    
    // TODO: Invalidate: reset to COLD, clear consecutive_passing_windows, timestamp transition
}
