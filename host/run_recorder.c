#include "run_recorder.h"

cldt_status_t cldt_run_recorder_open(
    cldt_run_recorder_t *recorder,
    const char *results_root,
    const cldt_experiment_config_t *config,
    const char *original_manifest,
    size_t original_manifest_bytes)
{
    (void)recorder;
    (void)results_root;
    (void)config;
    (void)original_manifest;
    (void)original_manifest_bytes;

    /*
     * IMPLEMENTATION TODO:
     * 1. Reject a template config, unsafe path component, empty manifest, or
     *    pre-existing target directory. Derive the directory name from a stable
     *    run identifier plus timestamp, never from unchecked user input.
     * 2. Create the directory atomically, copy the original manifest byte-for-
     *    byte, write its SHA-256 and a versions placeholder that will resolve
     *    source/binary identities plus the selected control_profile, then fsync
     *    metadata before accepting observations.
     * 3. Open events.ndjson in append-only mode and leave finalized false. If any
     *    step fails, roll back only the newly created empty directory.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_run_recorder_append(
    cldt_run_recorder_t *recorder,
    const char *topic,
    const uint8_t *payload,
    size_t payload_bytes,
    uint64_t received_host_us)
{
    (void)recorder;
    (void)topic;
    (void)payload;
    (void)payload_bytes;
    (void)received_host_us;

    /*
     * IMPLEMENTATION TODO: require an open non-finalized recorder, validate a
     * bounded topic and payload length, encode binary payload safely (for example
     * base64), escape all JSON strings, and append exactly one newline-terminated
     * record containing host receive time. Flush according to a documented
     * durability policy and increment records_written only after a successful
     * write. Do not parse, reorder, or discard raw evidence in this layer.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_run_recorder_finalize(
    cldt_run_recorder_t *recorder,
    const char *status,
    const char *reason)
{
    (void)recorder;
    (void)status;
    (void)reason;

    /*
     * IMPLEMENTATION TODO: accept only a fixed status vocabulary and predefined
     * exclusion reasons, write one small run-status.json atomically, flush and
     * close the event stream, then set finalized true. A second finalize call
     * must fail without changing files. Never reopen or rewrite events.ndjson
     * during finalization, even when the run is invalid or interrupted.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
