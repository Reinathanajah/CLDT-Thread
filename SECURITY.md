# SECURITY POLICY

## Scope

This repository is a **research scaffold**, not a production system. Policy command authentication is specified to use **ChaCha20-Poly1305 AEAD** (RFC 8439) with an mbedTLS backend (`common/include/cldt/cldt_auth.h`, `common/src/cldt_auth.c`). At the current scaffold stage, the interface is defined and implementation stubs return `CLDT_ERR_NOT_IMPLEMENTED`.

- **Key Isolation:** 256-bit pre-shared keys are stored in Non-Volatile Storage (NVS) on the ESP32 gateway/endpoints and in git-ignored `.env` on the host. Keys are never committed to manifests or Git history.
- **Nonce Invariant:** The tuple used to derive an AEAD nonce must never repeat under the same pre-shared key. The normative design uses a 12-byte network-order nonce formed by `run_id` (64-bit) and `policy_epoch` (32-bit); this requires that `run_id` is unique per key and `policy_epoch` is strictly monotonic within a run.
- **Replay Protection:** Replay and validity protection is enforced by the complete stateful validation contract: matching `run_id`, active `boot_id`, strictly monotonic epoch (`policy_epoch > applied_epoch`), non-expired TTL, and local gateway/endpoint limits.
- **Wire Representation:** Under the v1 wire format, policy command payload bytes (bytes 72–151) remain in plaintext on the wire and are authenticated alongside header AAD (bytes 0–51) by the 16-byte Poly1305 tag (bytes 56–71). If full payload ciphertext confidentiality is required in a future revision, the wire layout decision must be frozen before implementation.
- **Known-Answer Verification:** RFC 8439 §2.8.2 known-answer test vectors must pass unit testing before authenticated hardware actuation is enabled.

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
