#ifndef CLDT_CONTROL_PROFILE_H
#define CLDT_CONTROL_PROFILE_H

#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * A ready manifest names one immutable control profile. The profile is resolved
 * by the host before a run starts, then its ID and digest are archived with the
 * evidence. It contains only safety-relevant selection values shared across
 * host and edge boundaries; it is not a generic configuration database.
 */
#define CLDT_CONTROL_PROFILE_ID_BYTES 65U
#define CLDT_CONTROL_PROFILE_DIGEST_BYTES 32U

typedef struct {
    /*
     * profile_id identifies the exact safety selection named by
     * treatment.control_profile in a ready manifest. calibration_id identifies
     * the separately versioned model-calibration evidence that supplies
     * residual and interval limits to the host fidelity gate.
     */
    char profile_id[CLDT_CONTROL_PROFILE_ID_BYTES];
    char calibration_id[CLDT_CONTROL_PROFILE_ID_BYTES];
    /* Version one permits actuation only from the frozen cross-layer candidate. */
    cldt_model_variant_t actuation_model_variant;

    /*
     * resolved_digest is the digest of the canonical, fully resolved profile
     * document. It prevents the same human-readable ID from silently referring
     * to different values in two evidence bundles. Digest calculation belongs
     * to the host registry/parser, not this portable validation function.
     */
    uint8_t resolved_digest[CLDT_CONTROL_PROFILE_DIGEST_BYTES];

    /* Host-side freshness and hysteresis inputs. */
    uint32_t maximum_observation_age_ms;
    uint16_t passing_windows_to_trust;

    /* Edge-side policy bounds. Compiled gateway/endpoints may be stricter. */
    uint32_t maximum_policy_ttl_ms;
    uint32_t maximum_total_rate_pps;
    uint32_t minimum_critical_period_ms;
    uint16_t maximum_bulk_burst_packets;
} cldt_control_profile_t;

/*
 * Validates only intrinsic profile shape and arithmetic safety. It performs no
 * file I/O, cryptographic digest calculation, model fitting, or device query.
 *
 * The later implementation must reject null/empty/non-terminated identifiers,
 * an all-zero digest, zero time/rate limits, and relationships that would make
 * a policy impossible to evaluate safely. It must leave caller-owned profile
 * bytes unchanged and return CLDT_ERR_NOT_IMPLEMENTED until those checks exist.
 */
cldt_status_t cldt_control_profile_validate(
    const cldt_control_profile_t *profile);

#ifdef __cplusplus
}
#endif

#endif
