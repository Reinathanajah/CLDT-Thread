#include "twin_model.h"

cldt_status_t cldt_twin_model_init(
    cldt_twin_model_t *model,
    const cldt_experiment_config_t *config)
{
    (void)model;
    (void)config;

    /*
     * IMPLEMENTATION TODO: reject a null model or unvalidated configuration,
     * reset every node/class state deterministically, record the starting model
     * revision, and leave calibrated false until the estimator admits evidence.
     * Initialize only state needed to predict the declared primary metric. Do
     * not introduce a broad simulator, dashboard state, or policy state here.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_twin_model_observe(
    cldt_twin_model_t *model,
    const cldt_trace_record_t *record)
{
    (void)model;
    (void)record;

    /*
     * IMPLEMENTATION TODO: validate the physical record, use node ID plus boot
     * ID and sequence to reject duplicates or old observations, and update only
     * the state fields justified by that event kind. Advance modeled_time_us
     * monotonically; an out-of-order record may be retained by the recorder but
     * must not roll model state backward. Increment model_revision only when a
     * logical state change is accepted and record enough context to audit it.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_twin_model_predict(
    const cldt_twin_model_t *model,
    const cldt_policy_t *candidate,
    uint32_t horizon_ms,
    cldt_prediction_t *output)
{
    (void)model;
    (void)candidate;
    (void)horizon_ms;
    (void)output;

    /*
     * IMPLEMENTATION TODO: require a calibrated model, a validated candidate,
     * and a bounded nonzero horizon. Copy the live model to local scratch state,
     * evolve only that copy, and write a prediction containing horizon end,
     * service outcome, and uncertainty interval. The prediction must identify
     * the model revision it used so the estimator can score it against the same
     * future window. Never select or transmit policy from this function.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
