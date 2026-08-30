#ifndef CLDT_HOST_FIDELITY_GATE_H
#define CLDT_HOST_FIDELITY_GATE_H

#include <stdbool.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CLDT_GATE_REASON_NONE = 0,
    CLDT_GATE_REASON_TOO_FEW_SAMPLES,
    CLDT_GATE_REASON_STALE_OBSERVATION,
    CLDT_GATE_REASON_MODEL_LAG,
    CLDT_GATE_REASON_RESIDUAL,
    CLDT_GATE_REASON_COVERAGE,
    CLDT_GATE_REASON_CLOCK_UNCERTAINTY,
    CLDT_GATE_REASON_OBSERVATION_INTEGRITY,
    CLDT_GATE_REASON_OUT_OF_REGION,
    CLDT_GATE_REASON_MODEL_CHANGED
} cldt_gate_reason_t;

typedef struct {
    /* All time values use host monotonic time; error limits are dimensionless. */
    uint32_t minimum_samples;
    uint32_t maximum_observation_age_ms;
    uint32_t maximum_model_lag_ms;
    uint32_t maximum_clock_uncertainty_us;
    double maximum_p95_relative_error;
    double maximum_pdr_error_points;
    double minimum_interval_coverage;
    uint16_t passing_windows_to_trust;
} cldt_fidelity_limits_t;

typedef struct {
    /* The gate owns trust state only; it never creates, serializes, or applies policy. */
    cldt_gate_state_t state;
    cldt_gate_reason_t reason;
    cldt_model_variant_t bound_model_variant;
    uint64_t bound_model_revision;
    uint16_t consecutive_passing_windows;
    uint64_t state_entered_host_us;
    uint64_t transitions;
} cldt_fidelity_gate_t;

/*
 * Initializes a fail-closed gate. A successfully initialized gate starts COLD,
 * so callers must observe and score enough physical evidence before requesting
 * actuation. Limits are immutable for a run; changing them requires invalidation.
 */
cldt_status_t cldt_fidelity_gate_init(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    cldt_model_variant_t model_variant,
    uint64_t model_revision,
    uint64_t now_host_us);

/*
 * One hard failure leaves TRUSTED immediately; recovery requires hysteresis.
 * actuation_allowed is an output derived from state, never an input that can
 * force a favorable decision. Caller records state/reason alongside any policy.
 */
cldt_status_t cldt_fidelity_gate_evaluate(
    cldt_fidelity_gate_t *gate,
    const cldt_fidelity_limits_t *limits,
    const cldt_fidelity_sample_t *sample,
    uint64_t now_host_us,
    bool *actuation_allowed);

/* Forces a new evidence-collection epoch after run/model identity changes. */
void cldt_fidelity_gate_invalidate(
    cldt_fidelity_gate_t *gate,
    cldt_gate_reason_t reason,
    uint64_t now_host_us);

#ifdef __cplusplus
}
#endif

#endif
