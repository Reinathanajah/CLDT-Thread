#ifndef CLDT_HOST_TWIN_MODEL_H
#define CLDT_HOST_TWIN_MODEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"
#include "experiment_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_MODEL_MAX_NODES 8U

typedef struct {
    uint32_t queue_depth[CLDT_MODEL_MAX_NODES][CLDT_TRAFFIC_COUNT];
    uint32_t service_time_us[CLDT_MODEL_MAX_NODES][CLDT_TRAFFIC_COUNT];
    uint32_t link_rtt_us[CLDT_MODEL_MAX_NODES];
    double link_delivery_probability[CLDT_MODEL_MAX_NODES];
    uint64_t modeled_time_us;
    uint64_t model_revision;
    bool calibrated;
} cldt_twin_model_t;

typedef struct {
    uint64_t horizon_end_us;
    double predicted_pdr;
    uint32_t predicted_p50_rtt_us;
    uint32_t predicted_p95_rtt_us;
    double predicted_deadline_miss_ratio;
    uint64_t predicted_energy_uj;
    double lower_interval;
    double upper_interval;
} cldt_prediction_t;

cldt_status_t cldt_twin_model_init(
    cldt_twin_model_t *model,
    const cldt_experiment_config_t *config);

/* Updates state from one physical trace without performing policy selection. */
cldt_status_t cldt_twin_model_observe(
    cldt_twin_model_t *model,
    const cldt_trace_record_t *record);

/* Runs a side-effect-free what-if horizon under one candidate policy. */
cldt_status_t cldt_twin_model_predict(
    const cldt_twin_model_t *model,
    const cldt_policy_t *candidate,
    uint32_t horizon_ms,
    cldt_prediction_t *output);

#ifdef __cplusplus
}
#endif

#endif
