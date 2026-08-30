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
    
    // Key retrieval belongs to a platform provisioning adapter. This portable
    // context receives bounded key bytes only through cldt_auth_load_key().
    // TODO: sdkconfig requires: CONFIG_MBEDTLS_CHACHAPOLY_C=y, CONFIG_MBEDTLS_CHACHA20_C=y, CONFIG_MBEDTLS_POLY1305_C=y
    return CLDT_OK;
}

cldt_status_t cldt_auth_load_key(cldt_auth_context_t *ctx, const uint8_t key[CLDT_AUTH_KEY_BYTES]) {
    (void)ctx;
    (void)key;

    // TODO: implement key loading logic
    return CLDT_ERR_NOT_IMPLEMENTED;
}

void cldt_auth_build_nonce(cldt_run_id_t run_id, cldt_policy_epoch_t epoch, uint8_t nonce[CLDT_AUTH_NONCE_BYTES]) {
    (void)run_id;
    (void)epoch;
    (void)nonce;

    // TODO: Nonce construction: run_id 8 bytes big-endian at nonce[0..7], epoch 4 bytes big-endian at nonce[8..11]
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
    (void)ctx;
    (void)run_id;
    (void)epoch;
    (void)aad;
    (void)aad_len;
    (void)payload;
    (void)payload_len;
    (void)tag;

    // TODO: Sign flow: mbedtls_chachapoly_context ctx; mbedtls_chachapoly_init(&ctx); mbedtls_chachapoly_setkey(&ctx, key); mbedtls_chachapoly_encrypt_and_tag(&ctx, payload_len, nonce, aad, aad_len, payload, ciphertext_out, tag); mbedtls_chachapoly_free(&ctx)
    // TODO: Choose context lifetime/storage after measuring the pinned mbedTLS
    // version and the task/host stack budget.
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
    (void)ctx;
    (void)run_id;
    (void)epoch;
    (void)aad;
    (void)aad_len;
    (void)payload;
    (void)payload_len;
    (void)tag;

    // TODO: Verify flow: mbedtls_chachapoly_auth_decrypt returns 0 on success.
    // Map MBEDTLS_ERR_CHACHAPOLY_AUTH_FAILED to CLDT_ERR_AUTHENTICATION and
    // preserve other failures separately.
    // TODO: RFC 8439 Section 2.8.2 test vectors: Key=808182...9e9f, Nonce=07000000...4647, Tag=1ae10b594f09e26a7e902ecbd0600691
    return CLDT_ERR_NOT_IMPLEMENTED;
}

static cldt_status_t auth_calculate_tag_wrapper(
    void *context,
    const uint8_t *bytes,
    size_t byte_count,
    uint8_t output_tag[CLDT_AUTH_TAG_BYTES])
{
    (void)context;
    (void)bytes;
    (void)byte_count;
    (void)output_tag;

    // TODO: Callback wrapper: extract run_id from wire bytes at CLDT_WIRE_RUN_ID_OFFSET (24), epoch at CLDT_WIRE_POLICY_EPOCH_OFFSET (20), both in network byte order
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_authenticator_t cldt_auth_as_authenticator(cldt_auth_context_t *ctx) {
    cldt_authenticator_t auth;
    memset(&auth, 0, sizeof(auth));
    auth.calculate_tag = auth_calculate_tag_wrapper;
    auth.context = ctx;
    return auth;
}
