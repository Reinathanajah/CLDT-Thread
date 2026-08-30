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
     * 3. Set active policy to the safe fallback, clear active run, command
     *    authority boot ID, and applied epoch, and begin with
     *    remote_actuation_enabled false. A failed
     *    initialization must leave no policy that could be mistaken for an
     *    accepted remote command.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_guard_begin_run(
    cldt_policy_guard_t *guard,
    cldt_run_id_t run_id,
    cldt_boot_id_t command_authority_boot_id,
    bool remote_actuation_requested)
{
    (void)guard;
    (void)run_id;
    (void)command_authority_boot_id;
    (void)remote_actuation_requested;

    /*
     * IMPLEMENTATION TODO: require an initialized guard, nonzero run ID, no
     * active run, a nonzero command_authority_boot_id, and admission evidence
     * that the host reserved this ID in the durable global run ledger. If remote
     * actuation is requested, also require its binding to the active command-key
     * identity. A fresh gateway boot must refuse to resume forwarding an old
     * run. Only after that uniqueness boundary is proven may the guard restore
     * fallback, reset applied_epoch, and bind run_id plus command authority.
     * Enable remote acceptance only when requested by the frozen ready manifest
     * and CONFIG_CLDT_GATEWAY_REMOTE_ACTUATION is enabled; otherwise keep the run
     * shadow-only. Trace the resulting mode.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_guard_accept(
    cldt_policy_guard_t *guard,
    cldt_run_id_t proposal_run_id,
    cldt_boot_id_t proposal_authority_boot_id,
    const cldt_policy_t *proposal,
    uint64_t now_gateway_us,
    uint32_t clock_uncertainty_us,
    bool local_health_ok)
{
    (void)guard;
    (void)proposal_run_id;
    (void)proposal_authority_boot_id;
    (void)proposal;
    (void)now_gateway_us;
    (void)clock_uncertainty_us;
    (void)local_health_ok;

    /*
     * IMPLEMENTATION TODO: hold the short policy critical section only while
     * checking remote_actuation_enabled, local health, exact proposal_run_id and
     * proposal_authority_boot_id equality with the commissioned run authority,
     * strictly increasing epoch, finite TTL, clock
     * uncertainty, critical-period protection, bulk burst limit, and total rate.
     * Validate the full proposal before swapping it. On any failure leave the
     * active policy and epoch unchanged, return a reason code, and ensure the
     * caller emits a rejection trace/acknowledgement outside the lock. On
     * success the caller forwards the retained authenticated datagram byte for
     * byte; it must not re-encode different bytes under the accepted nonce.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_policy_guard_end_run(
    cldt_policy_guard_t *guard,
    cldt_status_t terminal_reason)
{
    (void)guard;
    (void)terminal_reason;

    /*
     * IMPLEMENTATION TODO: disarm remote acceptance first, atomically restore
     * the safe policy, emit the final policy/epoch/run/authority record, then
     * clear the active run, command authority, and applied epoch. Never clear
     * identity before the terminal trace is durable enough for the gateway's
     * evidence path.
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
     * safe snapshot and record the supplied failure reason and current accepted
     * epoch in a traceable event. Retain active_run_id and applied_epoch so a
     * later requalified command must still advance strictly. Stop forwarding
     * new proposals. Endpoints return to their own compiled safe policy when
     * the last accepted finite command
     * expires; version one must not synthesize a second command under the host's
     * nonce space. Fallback must succeed without host, broker, or model access.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
