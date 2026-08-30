#include "estimator.h"

cldt_status_t cldt_estimator_init(cldt_estimator_t *estimator)
{
    (void)estimator;

    /*
     * IMPLEMENTATION TODO: reject a null estimator, clear accepted/rejected
     * observation counts, last-observation time, residual mean, and residual M2
     * using a numerically stable initial state. Estimator selection and tuning
     * belong in a documented calibration block, not hidden in init.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_estimator_observe(
    cldt_estimator_t *estimator,
    cldt_twin_model_t *model,
    const cldt_trace_record_t *record,
    uint64_t received_host_us)
{
    (void)estimator;
    (void)model;
    (void)record;
    (void)received_host_us;

    /*
     * IMPLEMENTATION TODO: verify every pointer and host receive time, reject
     * records that predate the accepted sequence/boot state or violate the
     * configured observation-age limit, and increment rejected_observations
     * without modifying the model. For accepted records, update only fitted
     * parameters permitted by the calibration plan and record the receive time.
     * Do not learn from held-out runs when evaluating the primary comparison.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_estimator_score_prediction(
    cldt_estimator_t *estimator,
    const cldt_prediction_t *prediction,
    const cldt_metrics_t *observed,
    cldt_fidelity_sample_t *output)
{
    (void)estimator;
    (void)prediction;
    (void)observed;
    (void)output;

    /*
     * IMPLEMENTATION TODO: require that observed metrics are complete and refer
     * to the same run, policy epoch, and horizon as prediction. Compute residual
     * and interval coverage with a documented formula, update online statistics
     * only once per scored horizon, and populate every fidelity-sample field,
     * including model variant/revision and exact horizon identity.
     * A missing, stale, or unreconciled observation must produce a gate-relevant
     * failure signal rather than a favorable residual.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
