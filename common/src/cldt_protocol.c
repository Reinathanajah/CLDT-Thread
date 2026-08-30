#include "cldt/cldt_protocol.h"

size_t cldt_protocol_encoded_size(size_t payload_bytes)
{
    (void)payload_bytes;

    /*
     * IMPLEMENTATION TODO:
     * 1. Reject payload_bytes above CLDT_MAX_PAYLOAD_BYTES before adding it to
     *    CLDT_WIRE_HEADER_BYTES.
     * 2. Perform the addition with an explicit overflow check even though the
     *    current bound is small; this function is the protocol's size gate.
     * 3. Return zero for every unrepresentable input. Callers must treat zero
     *    as a validation failure, never as an empty wire frame.
     * Test with 0, CLDT_MAX_PAYLOAD_BYTES, one byte above the limit, and a
     * SIZE_MAX value. No allocation belongs in this helper.
     */
    return 0U;
}

cldt_status_t cldt_protocol_encode(
    const cldt_frame_meta_t *meta,
    const uint8_t *payload,
    size_t payload_bytes,
    const cldt_authenticator_t *authenticator,
    uint8_t *output,
    size_t output_capacity,
    size_t *output_bytes)
{
    (void)meta;
    (void)payload;
    (void)payload_bytes;
    (void)authenticator;
    (void)output;
    (void)output_capacity;
    (void)output_bytes;

    /*
     * IMPLEMENTATION TODO:
     * 1. Validate pointer combinations first: a zero-length payload may have a
     *    null payload pointer; a nonzero one may not. Require output_bytes.
     * 2. Ask cldt_protocol_encoded_size() for the exact size and reject a
     *    short output buffer without modifying it or output_bytes.
     * 3. Serialize each header field at the CLDT_WIRE_*_OFFSET declared in
     *    cldt_protocol.h and use network byte order for every multi-byte value.
     *    Write CLDT_WIRE_RESERVED_BYTES as zero. Do not cast output to a packed
     *    C structure: alignment, endianness, and compiler padding would make
     *    the wire contract unstable.
     * 4. Build the canonical integrity sequence by concatenating serialized
     *    header bytes 0-51 with the payload; the CRC and tag slots are omitted,
     *    not included as zero bytes. Calculate CRC-32C over that sequence and
     *    write it at CLDT_WIRE_CRC32C_OFFSET. When authentication is requested,
     *    supply the same sequence as ChaCha20-Poly1305 AAD with zero plaintext
     *    and write the resulting tag. Use bounded caller/stack storage or a
     *    documented scatter/gather helper; no heap allocation belongs here.
     * 5. Write output_bytes only after every validation and authenticator call
     *    succeeds. Add known-answer tests with fixed byte vectors.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_protocol_decode(
    const uint8_t *input,
    size_t input_bytes,
    const cldt_authenticator_t *authenticator,
    bool authentication_required,
    cldt_frame_view_t *output_view)
{
    (void)input;
    (void)input_bytes;
    (void)authenticator;
    (void)authentication_required;
    (void)output_view;

    /*
     * IMPLEMENTATION TODO:
     * 1. Check input and output pointers, then verify that input contains the
     *    fixed header before reading one field. Decode the payload length from
     *    bytes, validate its maximum, and require exact datagram length.
     * 2. Reject wrong magic, unsupported version, invalid enum values, trailing
     *    bytes, nonzero reserved bytes, and malformed flag combinations before
     *    publishing output_view. Read only through the declared offsets.
     * 3. Reconstruct the canonical integrity sequence (header bytes 0-51
     *    concatenated with payload), calculate CRC-32C, and compare it with the
     *    received value before publishing any view.
     * 4. If authentication_required is true, require an authenticator and
     *    verify the received tag over that same sequence as zero-plaintext AAD.
     * 5. Populate output_view only on success. Its payload is a borrowed view,
     *    so never copy a pointer into temporary decoder storage.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_protocol_validate_command(
    const cldt_frame_view_t *frame,
    cldt_run_id_t active_run_id,
    cldt_policy_epoch_t applied_epoch,
    uint64_t now_gateway_us,
    uint32_t time_uncertainty_us)
{
    (void)frame;
    (void)active_run_id;
    (void)applied_epoch;
    (void)now_gateway_us;
    (void)time_uncertainty_us;

    /*
     * IMPLEMENTATION TODO:
     * 1. Accept only CLDT_FRAME_COMMAND after cldt_protocol_decode() has
     *    verified integrity. Never let a health or observation frame enter the
     *    policy path merely because its payload happens to parse.
     * 2. Require exactly CLDT_POLICY_WIRE_BYTES, decode every field through the
     *    declared policy offsets, require frame.meta.run_id to equal the active
     *    run, require payload epoch to equal frame metadata epoch, and require
     *    that epoch to be strictly greater than applied_epoch. Endpoint callers
     *    must supply applied_epoch from a valid durable replay record rather
     *    than resetting it after reboot.
     * 3. Reject a zero or implausibly long TTL. Overflow-check conversion and
     *    addition before comparing issue time plus TTL to now_gateway_us after
     *    expanding the expiry margin by time_uncertainty_us.
     * 4. Return CLDT_ERR_MALFORMED for structural failure, CLDT_ERR_STALE for a
     *    well-formed command outside the accepted freshness window,
     *    CLDT_ERR_WRONG_RUN for another run identity, and CLDT_ERR_EXPIRED for
     *    elapsed TTL. Preserve DUPLICATE and OUT_OF_ORDER for epoch failures.
     * This helper does not persist state or apply a policy. The endpoint caller
     * must durably advance the accepted (run_id, epoch) before publishing the
     * new policy; failure to persist is a rejection and safe fallback. Test
     * duplicate epochs, time-wrap boundaries, and a command that arrives
     * exactly at the uncertainty-expanded expiry limit.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
