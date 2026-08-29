# SECURITY POLICY

## Scope

This repository is a **research scaffold**, not a production system. Policy command authentication is formally specified using **ChaCha20-Poly1305 AEAD** (RFC 8439) implemented via mbedTLS (`common/include/cldt/cldt_auth.h`, `common/src/cldt_auth.c`):

- **Key Isolation:** 256-bit pre-shared keys are stored exclusively in Non-Volatile Storage (NVS) on the ESP32 gateway/endpoints and in git-ignored `.env` on the host. Keys are never committed to manifests or Git history.
- **Nonce Derivation:** Every command uses a unique 12-byte network-order nonce derived from `run_id` (64-bit) and strictly monotonic `policy_epoch` (32-bit), preventing nonce reuse and replay attacks.
- **Verification:** The 16-byte Poly1305 tag covers frame header bytes 0–51 as Associated Authenticated Data (AAD) and the 80-byte policy payload.
- **Known-Answer Verification:** RFC 8439 §2.8.2 standard test vectors are integrated for testing before hardware actuation.

## Reporting a Vulnerability

If you find a security issue in this repository:

1. **Do not open a public issue.**
2. Email `reinathankurniawan@gmail.com` with a description of the vulnerability, affected files, and reproduction steps.
3. Allow up to 7 days for an initial response.

This project does not have a bug bounty program.

## What Is Not a Security Issue

- Test skeletons that return skip code 77 (this is intentional scaffold behavior).
- Functions that return `CLDT_ERR_NOT_IMPLEMENTED` (these are declared unfinished interfaces).
- The absence of TLS or mTLS in the broker adapter (implementation has not started).
