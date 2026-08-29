#include "policy_guard.h"

cldt_status_t cldt_policy_guard_init(
    cldt_policy_guard_t *guard,
    const cldt_control_profile_t *control_profile,
    const cldt_edge_limits_t *limits,
    const cldt_policy_t *safe_fallback)
{
    (void)guard;
    (void)control_profile;
    (void)limits;
    (void)safe_fallback;

    /*
     * IMPLEMENTATION TODO:
     * 1. Reject null arguments and validate the resolved control profile before
     *    accepting any edge limits. The caller must calculate limits by taking
     *    the stricter value of profile settings and build-time safety maxima.
     * 2. Copy the profile digest, effective limits, and safe fallback into
     *    guard-owned storage. Validate fallback with the same arithmetic used
     *    for host proposals; a fallback may never violate the effective limits.
     * 3. Set active policy to the safe fallback, clear active run and applied
     *    epoch, and begin with remote_actuation_enabled false. A failed
     *    initialization must leave no policy that could be mistaken for an
     *    accepted remote command.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_guard_accept(
    cldt_policy_guard_t *guard,
    const cldt_policy_t *proposal,
    uint64_t now_gateway_us,
    uint32_t clock_uncertainty_us,
    bool local_health_ok)
{
    (void)guard;
    (void)proposal;
    (void)now_gateway_us;
    (void)clock_uncertainty_us;
    (void)local_health_ok;

    /*
     * IMPLEMENTATION TODO: hold the short policy critical section only while
     * checking local health, active run, strictly increasing epoch, finite TTL,
     * clock uncertainty, critical-period protection, bulk burst limit, and total
     * rate. Validate the full proposal before swapping it. On any failure leave
     * active_policy and applied_epoch unchanged, return a reason code, and ensure
     * the caller emits a rejection trace/acknowledgement outside the lock.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_guard_fallback(
    cldt_policy_guard_t *guard,
    cldt_status_t reason)
{
    (void)guard;
    (void)reason;

    /*
     * IMPLEMENTATION TODO: atomically replace active_policy with the compiled
     * safe snapshot, record the supplied failure reason and local fallback epoch
     * in a traceable event, then notify endpoints through the normal bounded
     * command path. Fallback must succeed without host, broker, or model access.
     * If endpoint notification fails, retain fallback locally and report partial
     * propagation; never keep an unsafe host policy merely for consistency.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
