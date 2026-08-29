#ifndef CLDT_HOST_POLICY_H
#define CLDT_HOST_POLICY_H

#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"
#include "experiment_config.h"
#include "twin_model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t maximum_total_rate_pps;
    uint32_t minimum_critical_period_ms;
    uint16_t maximum_bulk_burst_packets;
    uint16_t maximum_batch_size;
} cldt_policy_limits_t;

/* Produces a proposal only. Applying policy is a separate edge responsibility. */
cldt_status_t cldt_policy_propose(
    const cldt_experiment_config_t *config,
    const cldt_prediction_t *prediction,
    const cldt_policy_t *current,
    const cldt_policy_limits_t *limits,
    uint64_t now_host_us,
    cldt_policy_t *proposal);

/* Checks aggregate and per-stream bounds before serialization. */
cldt_status_t cldt_policy_validate(
    const cldt_policy_t *policy,
    const cldt_policy_limits_t *limits);

#ifdef __cplusplus
}
#endif

#endif
