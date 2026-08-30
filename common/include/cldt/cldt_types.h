#ifndef CLDT_TYPES_H
#define CLDT_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_PROTOCOL_MAGIC UINT16_C(0x434C)
#define CLDT_PROTOCOL_VERSION UINT8_C(1)
#define CLDT_WIRE_HEADER_BYTES UINT16_C(72)
#define CLDT_MAX_PAYLOAD_BYTES UINT16_C(256)
#define CLDT_AUTH_TAG_BYTES 16U
#define CLDT_TRACE_DETAIL_BYTES 24U
#define CLDT_POLICY_STREAM_COUNT 4U
#define CLDT_COMMAND_AUTHORITY_NODE_ID UINT32_C(0)

typedef uint32_t cldt_node_id_t;
typedef uint64_t cldt_run_id_t;
typedef uint32_t cldt_boot_id_t;
typedef uint32_t cldt_sequence_t;
typedef uint32_t cldt_policy_epoch_t;

typedef enum {
    CLDT_NODE_GATEWAY_HOST = 0,
    CLDT_NODE_RADIO_COPROCESSOR,
    CLDT_NODE_ROUTER_ENDPOINT,
    CLDT_NODE_LOW_POWER_ENDPOINT
} cldt_node_role_t;

typedef enum {
    CLDT_TRAFFIC_CONTROL = 0,
    CLDT_TRAFFIC_CRITICAL,
    CLDT_TRAFFIC_TELEMETRY,
    CLDT_TRAFFIC_BULK,
    CLDT_TRAFFIC_COUNT
} cldt_traffic_class_t;

typedef enum {
    CLDT_FRAME_OBSERVATION = 0,
    CLDT_FRAME_COMMAND,
    CLDT_FRAME_ACKNOWLEDGEMENT,
    CLDT_FRAME_CLOCK_SYNC,
    CLDT_FRAME_HEALTH
} cldt_frame_kind_t;

typedef enum {
    CLDT_EVENT_TASK_RELEASE = 0,
    CLDT_EVENT_TASK_START,
    CLDT_EVENT_TASK_FINISH,
    CLDT_EVENT_TASK_BLOCK,
    CLDT_EVENT_QUEUE_ENQUEUE,
    CLDT_EVENT_QUEUE_DEQUEUE,
    CLDT_EVENT_QUEUE_REJECT,
    CLDT_EVENT_POOL_EXHAUSTION,
    CLDT_EVENT_MESSAGE_SEND,
    CLDT_EVENT_MESSAGE_ACK,
    CLDT_EVENT_MESSAGE_EXPIRE,
    CLDT_EVENT_MESSAGE_COALESCE,
    CLDT_EVENT_MESSAGE_DROP,
    CLDT_EVENT_MESSAGE_DUPLICATE,
    CLDT_EVENT_LINK_CHANGE,
    CLDT_EVENT_POWER_SAMPLE,
    CLDT_EVENT_POLICY_APPLY,
    CLDT_EVENT_POLICY_REJECT,
    CLDT_EVENT_POLICY_FALLBACK,
    CLDT_EVENT_HEALTH,
    CLDT_EVENT_COUNT
} cldt_event_kind_t;

typedef enum {
    CLDT_GATE_COLD = 0,
    CLDT_GATE_OBSERVE,
    CLDT_GATE_TRUSTED,
    CLDT_GATE_ABSTAIN
} cldt_gate_state_t;

typedef enum {
    CLDT_MODEL_NAIVE = 0,
    CLDT_MODEL_NETWORK_ONLY,
    CLDT_MODEL_CROSS_LAYER,
    CLDT_MODEL_VARIANT_COUNT
} cldt_model_variant_t;

/*
 * In-memory metadata. It is not a packed wire structure. Encoding and decoding
 * must be performed field by field through cldt_protocol.h.
 *
 * Identity is frame-kind specific. For observations, acknowledgements, health,
 * and trace-bearing frames, node_id/boot_id identify the emitting device. A
 * version 1 command is one global policy datagram for every endpoint admitted
 * to the run: node_id is CLDT_COMMAND_AUTHORITY_NODE_ID and boot_id identifies
 * the host coordinator process that issued it, not a destination. The gateway
 * guards and forwards those identical bytes. Version 1 does not define
 * different authenticated command bytes per endpoint.
 */
typedef struct {
    cldt_frame_kind_t kind;
    cldt_traffic_class_t traffic_class;
    uint16_t flags;
    uint8_t hop_limit;
    cldt_node_id_t node_id;
    cldt_boot_id_t boot_id;
    cldt_sequence_t sequence;
    cldt_policy_epoch_t policy_epoch;
    cldt_run_id_t run_id;
    uint64_t transmit_local_us;
    uint64_t deadline_local_us;
} cldt_frame_meta_t;

/*
 * Decoder output borrows payload memory from the input byte buffer. The caller
 * must keep that buffer alive and unchanged while this view is in use.
 */
typedef struct {
    cldt_frame_meta_t meta;
    const uint8_t *payload;
    uint16_t payload_bytes;
    uint32_t crc32c;
    uint8_t authentication_tag[CLDT_AUTH_TAG_BYTES];
} cldt_frame_view_t;

typedef struct {
    cldt_event_kind_t kind;
    /* Every work-item event carries its class; HEALTH may use CLDT_TRAFFIC_COUNT. */
    cldt_traffic_class_t traffic_class;
    cldt_node_id_t node_id;
    cldt_boot_id_t boot_id;
    cldt_sequence_t sequence;
    cldt_policy_epoch_t policy_epoch;
    cldt_run_id_t run_id;
    uint64_t local_time_us;
    /*
     * Work-item events repeat the item's release and absolute deadline in the
     * same local monotonic clock domain as local_time_us. Non-work-item events
     * store zero in both fields. This permits stateless aggregate timing while
     * preserving raw timestamps for a separate per-item lifecycle audit.
     */
    uint64_t release_local_us;
    uint64_t deadline_local_us;
    uint32_t task_id;
    int8_t core_id;
    uint16_t queue_depth;
    int16_t link_rssi_dbm;
    uint32_t time_uncertainty_us;
    /* Fixed-size auxiliary bytes; each event kind documents its own encoding. */
    uint8_t detail[CLDT_TRACE_DETAIL_BYTES];
} cldt_trace_record_t;

typedef struct {
    uint32_t release_period_ms[CLDT_POLICY_STREAM_COUNT];
    uint32_t phase_offset_ms[CLDT_POLICY_STREAM_COUNT];
    uint16_t burst_limit[CLDT_POLICY_STREAM_COUNT];
    uint16_t batch_size[CLDT_POLICY_STREAM_COUNT];
    uint32_t token_rate_milli_pps[CLDT_POLICY_STREAM_COUNT];
    cldt_policy_epoch_t epoch;
    uint64_t issued_gateway_us;
    uint32_t ttl_ms;
} cldt_policy_t;

typedef struct {
    cldt_model_variant_t model_variant;
    uint64_t model_revision;
    uint64_t horizon_start_host_us;
    uint64_t horizon_end_host_us;
    uint64_t evaluated_host_us;
    uint64_t newest_observation_host_us;
    uint32_t sample_count;
    uint32_t model_lag_us;
    uint32_t clock_uncertainty_us;
    double relative_p95_error;
    double pdr_error_points;
    double prediction_interval_coverage;
    /* False when required horizon evidence is missing, stale, or unreconciled. */
    bool observation_integrity_valid;
    bool inside_calibrated_region;
} cldt_fidelity_sample_t;

#ifdef __cplusplus
}
#endif

#endif
