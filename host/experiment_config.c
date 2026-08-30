#include "experiment_config.h"

cldt_status_t cldt_experiment_config_parse(
    const char *json,
    size_t json_bytes,
    cldt_experiment_config_t *output)
{
    (void)json;
    (void)json_bytes;
    (void)output;

    /*
     * IMPLEMENTATION TODO:
     * 1. Use a maintained JSON parser with a bounded input limit; parse exactly
     *    one UTF-8 document and reject duplicate keys rather than accepting a
     *    library-specific last-key-wins behavior.
     * 2. Validate against schemas/experiment.schema.json before conversion.
     *    This runtime parser accepts only state == "ready"; a template is a
     *    planning artifact and must never start a physical run.
     * 3. Copy strings into fixed, NUL-terminated fields only after checking the
     *    destination capacity. Require a non-empty control_profile for a ready
     *    run and preserve JSON Pointer-like error paths for the operator instead
     *    of returning a generic parse failure.
     * 4. Compute the canonical manifest digest from the original validated bytes
     *    using one documented canonicalization rule; do not include credentials.
     *    Leave output.run_id and output.command_authority_boot_id zero. The
     *    launcher assigns them only after a separate durable global-ledger
     *    reservation; parsing must not silently create nonce state or require a
     *    command key for a shadow-only run.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_experiment_config_validate(
    const cldt_experiment_config_t *config)
{
    (void)config;

    /*
     * IMPLEMENTATION TODO: validate cross-field relationships that schema shape
     * checks cannot prove: every stream source must name an endpoint, deadlines
     * must be compatible with their period, aggregate offered load must fit the
     * compiled safety ceiling, scenario time must lie inside measurement time,
     * and remote actuation must be disabled for non-control treatments. Version
     * one accepts only NONE or BULK_RATE_REDUCE and rejects the reserved phase
     * and power actions even though planning templates can name them. Reject a
     * configuration before any adapter or run directory is opened. Keep this
     * function deterministic so the same manifest has the same outcome on host
     * and in future gateway subset validation.
     */
    return CLDT_ERR_NOT_IMPLEMENTED;
}
