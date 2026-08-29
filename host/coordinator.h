#ifndef CLDT_HOST_COORDINATOR_H
#define CLDT_HOST_COORDINATOR_H

#include <stdbool.h>
#include <stdint.h>

#include "broker_io.h"
#include "cldt/cldt_control_profile.h"
#include "estimator.h"
#include "experiment_config.h"
#include "fidelity_gate.h"
#include "policy.h"
#include "run_recorder.h"
#include "twin_model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    cldt_experiment_config_t config;
    /*
     * Resolved profile copied only after its ID matches config.control_profile
     * and its immutable digest has been recorded by the run recorder.
     */
    cldt_control_profile_t control_profile;
    cldt_broker_io_t broker;
    cldt_run_recorder_t recorder;
    cldt_twin_model_t twin;
    cldt_estimator_t estimator;
    cldt_fidelity_gate_t gate;
    cldt_policy_t active_policy;
    uint64_t started_host_us;
    bool stop_requested;
} cldt_coordinator_t;

cldt_status_t cldt_coordinator_init(
    cldt_coordinator_t *coordinator,
    const cldt_experiment_config_t *config,
    const cldt_control_profile_t *control_profile);

cldt_status_t cldt_coordinator_run(cldt_coordinator_t *coordinator);

void cldt_coordinator_request_stop(cldt_coordinator_t *coordinator);

#ifdef __cplusplus
}
#endif

#endif
