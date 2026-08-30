#ifndef CLDT_HOST_EXPERIMENT_CONFIG_H
#define CLDT_HOST_EXPERIMENT_CONFIG_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This is the executable subset of a manifest, not a mirror of every planning
 * field in JSON. A state == "template" document is intentionally incomplete and
 * must never be converted into this structure. Parse only a completed
 * state == "ready" manifest after JSON Schema validation.
 */
#define CLDT_MAX_MANIFEST_NODES 4U
#define CLDT_MAX_WORKLOADS 4U
#define CLDT_CONFIG_DIGEST_BYTES 32U
#define CLDT_MANIFEST_ID_BYTES 65U
#define CLDT_MANIFEST_TEXT_BYTES 161U

typedef enum {
    CLDT_TREATMENT_BASELINE = 0,
    CLDT_TREATMENT_PREDICTION,
    CLDT_TREATMENT_GATED_CONTROL,
    CLDT_TREATMENT_SAFETY,
    CLDT_TREATMENT_SMP,
    CLDT_TREATMENT_POWER
} cldt_treatment_mode_t;

typedef enum {
    CLDT_ACTION_NONE = 0,
    CLDT_ACTION_BULK_RATE_REDUCE,
    /* Reserved for explicitly admitted future phases; rejected by v1 control. */
    CLDT_ACTION_PHASE_STAGGER,
    CLDT_ACTION_POWER_PROFILE
} cldt_candidate_action_t;

typedef enum {
    CLDT_SCENARIO_NONE = 0,
    CLDT_SCENARIO_LOAD_STEP,
    CLDT_SCENARIO_OBSERVATION_PAUSE,
    CLDT_SCENARIO_ENDPOINT_RESTART,
    CLDT_SCENARIO_TOPOLOGY_SHIFT
} cldt_scenario_kind_t;

/*
 * Labels remain strings until provisioning maps them to physical numeric node
 * IDs. Do not hash labels ad hoc: an implementation must reject an unknown
 * label or use one documented collision-checked mapping.
 */
typedef struct {
    char label[CLDT_MANIFEST_ID_BYTES];
    cldt_node_role_t role;
} cldt_manifest_node_t;

typedef struct {
    char id[CLDT_MANIFEST_ID_BYTES];
    char source_label[CLDT_MANIFEST_ID_BYTES];
    cldt_traffic_class_t traffic_class;
    uint32_t period_ms;
    uint16_t payload_bytes;
    uint32_t deadline_ms;
    uint16_t burst_packets;
} cldt_workload_config_t;

typedef struct {
    /*
     * run_id is assigned by the launcher only after parsing and cross-field
     * validation. It is never taken from a template. Before assignment, the
     * launcher reserves a nonzero cryptographically generated value in the
     * durable global run ledger and binds a non-secret command-key identity only
     * for an actuated run. The parser leaves it zero; the coordinator rejects zero.
     */
    char experiment_id[CLDT_MANIFEST_ID_BYTES];
    cldt_run_id_t run_id;
    /* Nonzero identity of the launcher process; assigned beside run_id. */
    cldt_boot_id_t command_authority_boot_id;
    uint32_t seed;

    cldt_manifest_node_t nodes[CLDT_MAX_MANIFEST_NODES];
    size_t node_count;
    uint8_t thread_channel;
    char placement[CLDT_MANIFEST_TEXT_BYTES];
    char firmware_reference[CLDT_MANIFEST_TEXT_BYTES];

    uint32_t warmup_s;
    uint32_t measurement_s;
    uint32_t cooldown_s;
    uint16_t repetitions;

    cldt_workload_config_t workloads[CLDT_MAX_WORKLOADS];
    size_t workload_count;

    cldt_scenario_kind_t scenario;
    uint32_t scenario_at_s;
    uint32_t scenario_duration_s;
    char scenario_target[CLDT_MANIFEST_TEXT_BYTES];

    cldt_treatment_mode_t treatment_mode;
    cldt_candidate_action_t candidate_action;
    /*
     * Identifier selected by treatment.control_profile. Parsing preserves this
     * bounded name only; the host registry must resolve it to a
     * cldt_control_profile_t, verify its digest, and record both identities in
     * the evidence bundle before coordinator initialization.
     */
    char control_profile[CLDT_MANIFEST_TEXT_BYTES];
    bool host_model_enabled;
    bool remote_actuation_enabled;

    bool counter_reconciliation_required;
    double minimum_critical_on_time_pdr;
    char negative_case[CLDT_MANIFEST_TEXT_BYTES];
    uint8_t canonical_digest[CLDT_CONFIG_DIGEST_BYTES];
} cldt_experiment_config_t;

/*
 * Parses exactly one UTF-8 ready manifest from caller-owned bytes.
 *
 * Implementation sequence:
 * - validate JSON syntax and schema first;
 * - reject state == "template" before allocating or opening I/O;
 * - copy bounded fields, preserving a precise error path;
 * - calculate canonical_digest after full validation and leave run_id plus
 *   command_authority_boot_id zero for the launcher's separate assignment step.
 *
 * The parser must reject unknown runtime fields, duplicate object keys, secrets,
 * and any null value that a ready manifest is required to replace.
 */
cldt_status_t cldt_experiment_config_parse(
    const char *json,
    size_t json_bytes,
    cldt_experiment_config_t *output);

/*
 * Performs deterministic cross-field validation after parsing.
 *
 * It verifies node/stream references, rate and deadline feasibility, scenario
 * timing, treatment permissions, and compiled safety ceilings. It must not make
 * network calls, create a directory, or mutate output state.
 */
cldt_status_t cldt_experiment_config_validate(
    const cldt_experiment_config_t *config);

#ifdef __cplusplus
}
#endif

#endif
