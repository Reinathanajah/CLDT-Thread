#include "coordinator.h"

cldt_status_t cldt_coordinator_init(
    cldt_coordinator_t *coordinator,
    const cldt_experiment_config_t *config,
    const cldt_control_profile_t *control_profile)
{
    (void)coordinator;
    (void)config;
    (void)control_profile;

    /*
     * IMPLEMENTATION TODO:
     * 1. Require a ready, cross-field-validated config and a valid resolved
     *    control profile. Compare the profile ID with config.control_profile
     *    using bounded strings; reject mismatch before opening a recorder or
     *    broker. The caller is responsible for checking the profile digest
     *    against the canonical registry document before this function is called.
     * 2. Copy config and profile only after validation. Record the profile ID,
     *    calibration ID, and digest beside the frozen manifest; initialize the
     *    fidelity gate and edge proposal limits from that immutable selection.
     * 3. Initialize recorder, model, estimator, fidelity gate, policy baseline,
     *    and broker in that order. Each successful step needs a paired rollback
     *    action so a later failure leaves no partial run marked valid.
     * 4. Do not open a network adapter before the immutable run directory,
     *    manifest digest, and control-profile identity exist.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_coordinator_run(cldt_coordinator_t *coordinator)
{
    (void)coordinator;

    /*
     * IMPLEMENTATION TODO: implement one bounded event loop with this strict
     * sequence for each accepted observation: record raw bytes first; validate
     * run/digest identity; update physical model state; score only completed
     * prior horizons; evaluate the fidelity gate; and only then consider a new
     * bounded proposal. Sleep or poll with a deadline so policy expiry, phase
     * transitions, and stop requests are never starved by broker traffic.
     * Finalize through the recorder with complete, invalid, or interrupted status.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

void cldt_coordinator_request_stop(cldt_coordinator_t *coordinator)
{
    (void)coordinator;

    /*
     * IMPLEMENTATION TODO: make this function only set an atomic or signal-safe
     * stop flag. The main loop owns broker close, final counter requests, metric
     * reconciliation, and recorder finalization because those operations may
     * allocate, block, or fail. A signal handler must never write evidence or
     * publish a fallback command directly.
     */
}
