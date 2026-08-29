#ifndef CLDT_HOST_ESTIMATOR_H
#define CLDT_HOST_ESTIMATOR_H

#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_metrics.h"
#include "cldt/cldt_types.h"
#include "twin_model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t accepted_observations;
    uint64_t rejected_observations;
    uint64_t last_observation_host_us;
    double residual_mean;
    double residual_m2;
} cldt_estimator_t;

cldt_status_t cldt_estimator_init(cldt_estimator_t *estimator);

/* Updates model parameters, never policy or gate state. */
cldt_status_t cldt_estimator_observe(
    cldt_estimator_t *estimator,
    cldt_twin_model_t *model,
    const cldt_trace_record_t *record,
    uint64_t received_host_us);

/* Compares a prior prediction with observations from the same horizon. */
cldt_status_t cldt_estimator_score_prediction(
    cldt_estimator_t *estimator,
    const cldt_prediction_t *prediction,
    const cldt_metrics_t *observed,
    cldt_fidelity_sample_t *output);

#ifdef __cplusplus
}
#endif

#endif
