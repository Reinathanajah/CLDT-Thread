#include "cldt/cldt_auth.h"
#include <string.h>

#ifdef ESP_PLATFORM
#include "mbedtls/chachapoly.h"
#else
// TODO: link host-side mbedtls and include "mbedtls/chachapoly.h"
#endif

cldt_status_t cldt_auth_init(cldt_auth_context_t *ctx) {
    if (!ctx) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }
    memset(ctx->key, 0, CLDT_AUTH_KEY_BYTES);
    ctx->key_loaded = false;
    return CLDT_OK;
}

cldt_status_t cldt_auth_load_key(cldt_auth_context_t *ctx, const uint8_t key[CLDT_AUTH_KEY_BYTES]) {
    if (!ctx || !key) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }
    memcpy(ctx->key, key, CLDT_AUTH_KEY_BYTES);
    ctx->key_loaded = true;
    return CLDT_OK;
}

void cldt_auth_build_nonce(cldt_run_id_t run_id, cldt_policy_epoch_t epoch, uint8_t nonce[CLDT_AUTH_NONCE_BYTES]) {
    // 8-byte run_id in network byte order (big-endian)
    nonce[0] = (uint8_t)(run_id >> 56);
    nonce[1] = (uint8_t)(run_id >> 48);
    nonce[2] = (uint8_t)(run_id >> 40);
    nonce[3] = (uint8_t)(run_id >> 32);
    nonce[4] = (uint8_t)(run_id >> 24);
    nonce[5] = (uint8_t)(run_id >> 16);
    nonce[6] = (uint8_t)(run_id >> 8);
    nonce[7] = (uint8_t)(run_id);

    // 4-byte epoch in network byte order (big-endian)
    nonce[8]  = (uint8_t)(epoch >> 24);
    nonce[9]  = (uint8_t)(epoch >> 16);
    nonce[10] = (uint8_t)(epoch >> 8);
    nonce[11] = (uint8_t)(epoch);
}

cldt_status_t cldt_auth_sign(
    cldt_auth_context_t *ctx,
    cldt_run_id_t run_id,
    cldt_policy_epoch_t epoch,
    const uint8_t *aad,
    size_t aad_len,
    const uint8_t *payload,
    size_t payload_len,
    uint8_t tag[CLDT_AUTH_TAG_BYTES])
{
    if (!ctx || !ctx->key_loaded || !tag) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }
    if (!payload && payload_len > 0) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    uint8_t nonce[CLDT_AUTH_NONCE_BYTES];
    cldt_auth_build_nonce(run_id, epoch, nonce);

    // TODO: mbedtls_chachapoly_context chachapoly_ctx;
    // TODO: mbedtls_chachapoly_init(&chachapoly_ctx);
    // TODO: mbedtls_chachapoly_setkey(&chachapoly_ctx, ctx->key);
    // TODO: call mbedtls_chachapoly_encrypt_and_tag with nonce, aad, payload
    // TODO: copy the 16-byte tag output into tag[]
    // TODO: mbedtls_chachapoly_free(&chachapoly_ctx);
    // TODO: return CLDT_ERR_AUTHENTICATION on mbedtls error

    (void)aad;
    (void)aad_len;
    (void)payload;
    (void)payload_len;
    (void)nonce;

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_auth_verify(
    cldt_auth_context_t *ctx,
    cldt_run_id_t run_id,
    cldt_policy_epoch_t epoch,
    const uint8_t *aad,
    size_t aad_len,
    const uint8_t *payload,
    size_t payload_len,
    const uint8_t tag[CLDT_AUTH_TAG_BYTES])
{
    if (!ctx || !ctx->key_loaded || !tag) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }
    if (!payload && payload_len > 0) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    uint8_t nonce[CLDT_AUTH_NONCE_BYTES];
    cldt_auth_build_nonce(run_id, epoch, nonce);

    // TODO: mbedtls_chachapoly_context chachapoly_ctx;
    // TODO: mbedtls_chachapoly_init(&chachapoly_ctx);
    // TODO: mbedtls_chachapoly_setkey(&chachapoly_ctx, ctx->key);
    // TODO: call mbedtls_chachapoly_auth_decrypt with nonce, aad, payload, tag
    // TODO: return CLDT_ERR_AUTHENTICATION if tag verification fails (ret != 0)
    // TODO: mbedtls_chachapoly_free(&chachapoly_ctx);

    (void)aad;
    (void)aad_len;
    (void)payload;
    (void)payload_len;
    (void)nonce;

    return CLDT_ERR_NOT_IMPLEMENTED;
}

// Callback wrapper that matches the cldt_authenticate_fn signature
// in cldt_protocol.h: (void *context, const uint8_t *bytes, size_t byte_count,
// uint8_t output_tag[CLDT_AUTH_TAG_BYTES])
static cldt_status_t auth_calculate_tag_wrapper(
    void *context,
    const uint8_t *bytes,
    size_t byte_count,
    uint8_t output_tag[CLDT_AUTH_TAG_BYTES])
{
    // TODO: extract run_id and epoch from the frame bytes at their wire offsets
    // TODO: call cldt_auth_sign with the extracted parameters
    // TODO: use CLDT_WIRE_RUN_ID_OFFSET and CLDT_WIRE_POLICY_EPOCH_OFFSET

    (void)context;
    (void)bytes;
    (void)byte_count;
    (void)output_tag;
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_authenticator_t cldt_auth_as_authenticator(cldt_auth_context_t *ctx) {
    cldt_authenticator_t auth;
    auth.calculate_tag = auth_calculate_tag_wrapper;
    auth.context = ctx;
    return auth;
}
