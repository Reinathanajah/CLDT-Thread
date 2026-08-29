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

    if (limits->minimum_samples == 0 ||
        limits->passing_windows_to_trust == 0) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    // TODO: validate that maximum_p95_relative_error is in (0, 1]
    // TODO: validate that minimum_interval_coverage is in [0, 1]
    // TODO: validate maximum_observation_age_ms and maximum_model_lag_ms are nonzero

    gate->state = CLDT_GATE_COLD;
    gate->reason = CLDT_GATE_REASON_TOO_FEW_SAMPLES;
    gate->consecutive_passing_windows = 0;
    gate->state_entered_host_us = now_host_us;
    gate->transitions = 0;

    return CLDT_OK;
}

// Returns true if the fidelity sample passes all configured limits.
static bool evaluate_sample_against_limits(
    const cldt_fidelity_limits_t *limits,
    const cldt_fidelity_sample_t *sample,
    uint64_t now_host_us,
    cldt_gate_reason_t *fail_reason)
{
    if (sample->sample_count < limits->minimum_samples) {
        *fail_reason = CLDT_GATE_REASON_TOO_FEW_SAMPLES;
        return false;
    }

    uint64_t observation_age_us = now_host_us - sample->newest_observation_host_us;
    uint64_t max_age_us = (uint64_t)limits->maximum_observation_age_ms * 1000U;
    if (observation_age_us > max_age_us) {
        *fail_reason = CLDT_GATE_REASON_STALE_OBSERVATION;
        return false;
    }

    uint64_t max_lag_us = (uint64_t)limits->maximum_model_lag_ms * 1000U;
    if (sample->model_lag_us > max_lag_us) {
        *fail_reason = CLDT_GATE_REASON_MODEL_LAG;
        return false;
    }

    if (sample->relative_p95_error > limits->maximum_p95_relative_error) {
        *fail_reason = CLDT_GATE_REASON_RESIDUAL;
        return false;
    }

    if (sample->prediction_interval_coverage < limits->minimum_interval_coverage) {
        *fail_reason = CLDT_GATE_REASON_COVERAGE;
        return false;
    }

    if (sample->clock_uncertainty_us > limits->maximum_clock_uncertainty_us) {
        *fail_reason = CLDT_GATE_REASON_CLOCK_UNCERTAINTY;
        return false;
    }

    if (!sample->inside_calibrated_region) {
        *fail_reason = CLDT_GATE_REASON_OUT_OF_REGION;
        return false;
    }

    // TODO: integrate Kalman covariance diagonal (P[2][2] for critical_pdr)
    // as an additional check: if Kalman uncertainty exceeds a configured
    // threshold, fail with CLDT_GATE_REASON_MODEL_LAG or a new reason code.
    // This replaces the heuristic residual check with a principled Bayesian
    // uncertainty bound from the estimator's covariance matrix.

    *fail_reason = CLDT_GATE_REASON_NONE;
    return true;
}

// Transitions the gate state and records metadata.
static void transition_to(
    cldt_fidelity_gate_t *gate,
    cldt_gate_state_t new_state,
    cldt_gate_reason_t reason,
    uint64_t now_host_us)
{
    if (gate->state != new_state || gate->reason != reason) {
        gate->state = new_state;
        gate->reason = reason;
        gate->state_entered_host_us = now_host_us;
        gate->transitions++;
    }
}

cldt_status_t cldt_fidelity_gate_evaluate(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    const cldt_fidelity_sample_t *sample,
    uint64_t now_host_us,
    bool *actuation_allowed)
{
    if (!gate || !limits || !sample || !actuation_allowed) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    *actuation_allowed = false;

    cldt_gate_reason_t fail_reason = CLDT_GATE_REASON_NONE;
    bool passing = evaluate_sample_against_limits(limits, sample, now_host_us, &fail_reason);

    if (!passing) {
        // Any hard failure immediately enters ABSTAIN.
        gate->consecutive_passing_windows = 0;
        transition_to(gate, CLDT_GATE_ABSTAIN, fail_reason, now_host_us);
        return CLDT_OK;
    }

    // Sample passed all checks.
    gate->consecutive_passing_windows++;

    switch (gate->state) {
    case CLDT_GATE_COLD:
        // First passing sample moves COLD to OBSERVE.
        transition_to(gate, CLDT_GATE_OBSERVE, CLDT_GATE_REASON_NONE, now_host_us);
        break;

    case CLDT_GATE_OBSERVE:
        // Enough consecutive passes move OBSERVE to TRUSTED.
        if (gate->consecutive_passing_windows >= limits->passing_windows_to_trust) {
            transition_to(gate, CLDT_GATE_TRUSTED, CLDT_GATE_REASON_NONE, now_host_us);
            *actuation_allowed = true;
        }
        break;

    case CLDT_GATE_TRUSTED:
        *actuation_allowed = true;
        break;

    case CLDT_GATE_ABSTAIN:
        // Recovery from ABSTAIN passes through OBSERVE first.
        // A single clean sample does not re-enable control.
        gate->consecutive_passing_windows = 1;
        transition_to(gate, CLDT_GATE_OBSERVE, CLDT_GATE_REASON_NONE, now_host_us);
        break;

    default:
        return CLDT_ERR_WRONG_STATE;
    }

    // TODO: record gate state transition as a trace event for the
    // gate characterization plot (state vs time).
    // TODO: record the Kalman covariance diagonal values alongside
    // the gate state for post-hoc analysis.

    return CLDT_OK;
}

void cldt_fidelity_gate_invalidate(
    cldt_fidelity_gate_t *gate,
    cldt_gate_reason_t reason,
    uint64_t now_host_us)
{
    if (!gate) {
        return;
    }

    gate->consecutive_passing_windows = 0;
    transition_to(gate, CLDT_GATE_COLD, reason, now_host_us);

    // TODO: emit a trace record for the invalidation event so
    // the gate characterization plot shows forced resets.
}
