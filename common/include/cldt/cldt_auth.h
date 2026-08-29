#ifndef CLDT_AUTH_H
#define CLDT_AUTH_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"
#include "cldt/cldt_protocol.h"

#define CLDT_AUTH_KEY_BYTES 32
#define CLDT_AUTH_NONCE_BYTES 12

typedef struct {
    uint8_t key[CLDT_AUTH_KEY_BYTES];
    bool key_loaded;
} cldt_auth_context_t;

cldt_status_t cldt_auth_init(cldt_auth_context_t *ctx);
cldt_status_t cldt_auth_load_key(cldt_auth_context_t *ctx, const uint8_t key[CLDT_AUTH_KEY_BYTES]);
void cldt_auth_build_nonce(cldt_run_id_t run_id, cldt_policy_epoch_t epoch, uint8_t nonce[CLDT_AUTH_NONCE_BYTES]);
cldt_status_t cldt_auth_sign(cldt_auth_context_t *ctx, cldt_run_id_t run_id, cldt_policy_epoch_t epoch, const uint8_t *aad, size_t aad_len, const uint8_t *payload, size_t payload_len, uint8_t tag[CLDT_AUTH_TAG_BYTES]);
cldt_status_t cldt_auth_verify(cldt_auth_context_t *ctx, cldt_run_id_t run_id, cldt_policy_epoch_t epoch, const uint8_t *aad, size_t aad_len, const uint8_t *payload, size_t payload_len, const uint8_t tag[CLDT_AUTH_TAG_BYTES]);
cldt_authenticator_t cldt_auth_as_authenticator(cldt_auth_context_t *ctx);

#endif // CLDT_AUTH_H
