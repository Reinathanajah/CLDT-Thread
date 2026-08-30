#ifndef CLDT_GATEWAY_POLICY_GUARD_H
#define CLDT_GATEWAY_POLICY_GUARD_H

#include <stdbool.h>
#include <stdint.h>

#include "cldt/cldt_control_profile.h"
#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /*
     * Effective per-run ceilings are derived from the resolved control profile
     * and capped by compiled safety maxima. A manifest cannot raise them.
     */
    uint32_t maximum_total_rate_pps;
    uint32_t minimum_critical_period_ms;
    uint16_t maximum_bulk_burst_packets;
    uint32_t maximum_policy_ttl_ms;
} cldt_edge_limits_t;

typedef struct {
    /* Only this object owns the mutable edge policy snapshot and applied epoch. */
    cldt_run_id_t active_run_id;
    cldt_boot_id_t command_authority_boot_id;
    cldt_policy_epoch_t applied_epoch;
    /*
     * Archived with every decision so a gateway trace can identify the exact
     * resolved profile even if a human-readable profile name is later reused.
     */
    uint8_t control_profile_digest[CLDT_CONTROL_PROFILE_DIGEST_BYTES];
    cldt_policy_t safe_fallback;
    cldt_policy_t active_policy;
    cldt_edge_limits_t limits;
    bool remote_actuation_enabled;
} cldt_policy_guard_t;

cldt_status_t cldt_policy_guard_init(
    cldt_policy_guard_t *guard,
    const cldt_control_profile_t *control_profile,
    const cldt_edge_limits_t *limits,
    const cldt_policy_t *safe_fallback);

/*
 * Binds the guard to one nonzero run already reserved in the global run ledger
 * and resets it to the safe policy. An actuated run is additionally bound to
 * the command-key identity. A gateway boot never resumes forwarding an old run.
 * Remote actuation remains fail-closed unless both the build maturity switch
 * and the frozen ready manifest authorize it.
 */
cldt_status_t cldt_policy_guard_begin_run(
    cldt_policy_guard_t *guard,
    cldt_run_id_t run_id,
    cldt_boot_id_t command_authority_boot_id,
    bool remote_actuation_requested);

/*
 * Validates host output independently; it does not trust the host gate state.
 * Caller supplies local time, uncertainty, and health observed at acceptance.
 * On failure, the function must leave the active policy and epoch unchanged.
 */
cldt_status_t cldt_policy_guard_accept(
    cldt_policy_guard_t *guard,
    cldt_run_id_t proposal_run_id,
    cldt_boot_id_t proposal_authority_boot_id,
    const cldt_policy_t *proposal,
    uint64_t now_gateway_us,
    uint32_t clock_uncertainty_us,
    bool local_health_ok);

/*
 * Immediately selects the compiled safe policy and records the reason. This
 * must be usable while host, broker, or model connectivity is absent.
 */
cldt_status_t cldt_policy_guard_fallback(
    cldt_policy_guard_t *guard,
    cldt_status_t reason);

/* Disarms remote control, restores fallback, and clears run/epoch after trace. */
cldt_status_t cldt_policy_guard_end_run(
    cldt_policy_guard_t *guard,
    cldt_status_t terminal_reason);

#ifdef __cplusplus
}
#endif

#endif
