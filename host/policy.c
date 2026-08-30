#include "policy.h"

cldt_status_t cldt_policy_propose(
    const cldt_experiment_config_t *config,
    const cldt_prediction_t *prediction,
    const cldt_policy_t *current,
    const cldt_policy_limits_t *limits,
    uint64_t issued_gateway_us,
    cldt_policy_t *proposal)
{
    (void)config;
    (void)prediction;
    (void)current;
    (void)limits;
    (void)issued_gateway_us;
    (void)proposal;

    /*
     * IMPLEMENTATION TODO: begin with exactly one explainable candidate action:
     * reduce only the bulk stream rate when the prediction forecasts critical
     * service below the declared floor. Copy current policy as the baseline,
     * modify one bounded field, assign a new epoch and finite TTL, then call
     * cldt_policy_validate(). Require the prediction to carry the frozen
     * CLDT_MODEL_CROSS_LAYER variant, revision, and completed prior-horizon
     * identity. issued_gateway_us must come from a valid host-to-gateway clock
     * mapping with uncertainty inside the frozen bound; do not stamp host time
     * into a gateway-domain TTL field. Return "no proposal" when prediction is
     * absent, outside calibration, or the treatment does not permit actuation. A learned
     * controller is explicitly out of scope until this baseline is validated.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_validate(
    const cldt_policy_t *policy,
    const cldt_policy_limits_t *limits)
{
    (void)policy;
    (void)limits;

    /*
     * IMPLEMENTATION TODO: require non-null inputs, validate every period,
     * burst, batch size, token rate, epoch, and TTL, then use checked arithmetic
     * to calculate total offered rate. Preserve the critical stream's minimum
     * period and reject policy that exceeds any compiled or manifest-derived
     * ceiling. This is host-side defense in depth; the gateway repeats its own
     * checks and neither side assumes the other is trusted.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
