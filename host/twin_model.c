#include "twin_model.h"

cldt_status_t cldt_twin_model_init(
    cldt_twin_model_t *model,
    const cldt_experiment_config_t *config,
    cldt_model_variant_t variant)
{
    (void)model;
    (void)config;
    (void)variant;

    /*
     * IMPLEMENTATION TODO: reject a null model, unvalidated configuration, or
     * invalid variant; reset every node/class state deterministically, record the
     * starting model revision, and leave calibrated false until the estimator
     * admits evidence. Initialize only state permitted by the variant's frozen
     * feature allowlist and needed to predict the declared primary metric. Do
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
     * The naive, network-only, and cross-layer instances receive the same
     * eligible horizon boundaries but update only from their declared features.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_twin_model_predict(
    const cldt_twin_model_t *model,
    const cldt_policy_t *candidate,
    uint64_t issued_host_us,
    uint64_t horizon_start_host_us,
    uint64_t horizon_end_host_us,
    cldt_prediction_t *output)
{
    (void)model;
    (void)candidate;
    (void)issued_host_us;
    (void)horizon_start_host_us;
    (void)horizon_end_host_us;
    (void)output;

    /*
     * IMPLEMENTATION TODO: require a calibrated model, a validated candidate,
     * and issued <= horizon_start < horizon_end with overflow-safe duration
     * bounds. Copy the live model to local scratch state,
     * evolve only that copy, and write a prediction containing horizon end,
     * service outcome, and uncertainty interval. Populate variant, model
     * revision, issuance time, and exact start/end boundaries so the estimator
     * can score all variants against the same future window without leakage.
     * Never select or transmit policy from this function.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
