#ifndef CLDT_PROTOCOL_H
#define CLDT_PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef cldt_status_t (*cldt_authenticate_fn)(
    void *context,
    const uint8_t *bytes,
    size_t byte_count,
    uint8_t output_tag[CLDT_AUTH_TAG_BYTES]);

typedef struct {
    cldt_authenticate_fn calculate_tag;
    void *context;
} cldt_authenticator_t;

/*
 * Version 1 frame layout. Every multi-byte integer uses network byte order.
 * The two reserved bytes are transmitted as zero and rejected when nonzero.
 * These offsets are the wire contract; sizeof(cldt_frame_meta_t) is not.
 */
#define CLDT_WIRE_MAGIC_OFFSET 0U
#define CLDT_WIRE_VERSION_OFFSET 2U
#define CLDT_WIRE_KIND_OFFSET 3U
#define CLDT_WIRE_TRAFFIC_CLASS_OFFSET 4U
#define CLDT_WIRE_FLAGS_OFFSET 5U
#define CLDT_WIRE_HOP_LIMIT_OFFSET 7U
#define CLDT_WIRE_NODE_ID_OFFSET 8U
#define CLDT_WIRE_BOOT_ID_OFFSET 12U
#define CLDT_WIRE_SEQUENCE_OFFSET 16U
#define CLDT_WIRE_POLICY_EPOCH_OFFSET 20U
#define CLDT_WIRE_RUN_ID_OFFSET 24U
#define CLDT_WIRE_TRANSMIT_LOCAL_US_OFFSET 32U
#define CLDT_WIRE_DEADLINE_LOCAL_US_OFFSET 40U
#define CLDT_WIRE_PAYLOAD_BYTES_OFFSET 48U
#define CLDT_WIRE_RESERVED_OFFSET 50U
#define CLDT_WIRE_RESERVED_BYTES 2U
#define CLDT_WIRE_CRC32C_OFFSET 52U
#define CLDT_WIRE_AUTH_TAG_OFFSET 56U

/*
 * Version 1 policy payload layout. Array elements are contiguous and encoded
 * in traffic-class order from CLDT_TRAFFIC_CONTROL through CLDT_TRAFFIC_BULK.
 * The policy epoch in this payload must equal the frame metadata epoch.
 */
#define CLDT_POLICY_WIRE_RELEASE_PERIOD_OFFSET 0U
#define CLDT_POLICY_WIRE_PHASE_OFFSET 16U
#define CLDT_POLICY_WIRE_BURST_LIMIT_OFFSET 32U
#define CLDT_POLICY_WIRE_BATCH_SIZE_OFFSET 40U
#define CLDT_POLICY_WIRE_TOKEN_RATE_OFFSET 48U
#define CLDT_POLICY_WIRE_EPOCH_OFFSET 64U
#define CLDT_POLICY_WIRE_ISSUED_GATEWAY_US_OFFSET 68U
#define CLDT_POLICY_WIRE_TTL_MS_OFFSET 76U
#define CLDT_POLICY_WIRE_BYTES 80U

#if (CLDT_WIRE_AUTH_TAG_OFFSET + CLDT_AUTH_TAG_BYTES) != CLDT_WIRE_HEADER_BYTES
#error "Version 1 frame offsets do not match CLDT_WIRE_HEADER_BYTES"
#endif

#if CLDT_POLICY_STREAM_COUNT != 4U
#error "Version 1 policy layout requires exactly four traffic classes"
#endif

#if (CLDT_POLICY_WIRE_TTL_MS_OFFSET + 4U) != CLDT_POLICY_WIRE_BYTES
#error "Version 1 policy offsets do not match CLDT_POLICY_WIRE_BYTES"
#endif

/*
 * Returns the exact output size required for this payload. Zero means the
 * payload cannot be represented by the current protocol version.
 */
size_t cldt_protocol_encoded_size(size_t payload_bytes);

/*
 * Encodes one frame into caller-owned storage. No heap allocation or I/O is
 * permitted. output_bytes is written only on success.
 */
cldt_status_t cldt_protocol_encode(
    const cldt_frame_meta_t *meta,
    const uint8_t *payload,
    size_t payload_bytes,
    const cldt_authenticator_t *authenticator,
    uint8_t *output,
    size_t output_capacity,
    size_t *output_bytes);

/*
 * Decodes and validates one complete datagram. The returned payload view
 * borrows memory from input. The function must reject trailing bytes,
 * truncation, an unsupported version, CRC failure, and required-auth failure.
 */
cldt_status_t cldt_protocol_decode(
    const uint8_t *input,
    size_t input_bytes,
    const cldt_authenticator_t *authenticator,
    bool authentication_required,
    cldt_frame_view_t *output_view);

/*
 * Applies freshness and ordering checks after successful decoding. Times are
 * in the gateway monotonic domain; uncertainty expands the rejection margin.
 * On an endpoint, applied_epoch must be the RAM mirror of a valid durable
 * replay record. The caller still owns issuer validation, durable advancement,
 * local limits, and atomic policy publication.
 */
cldt_status_t cldt_protocol_validate_command(
    const cldt_frame_view_t *frame,
    cldt_run_id_t active_run_id,
    cldt_policy_epoch_t applied_epoch,
    uint64_t now_gateway_us,
    uint32_t time_uncertainty_us);

#ifdef __cplusplus
}
#endif

#endif
