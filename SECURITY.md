# SECURITY POLICY

## Scope

This repository is a **research scaffold**, not a production system. Policy command authentication is specified to use **ChaCha20-Poly1305 AEAD** (RFC 8439) with an mbedTLS backend (`common/include/cldt/cldt_auth.h`, `common/src/cldt_auth.c`). At the current scaffold stage, the interface is defined and implementation stubs return `CLDT_ERR_NOT_IMPLEMENTED`.

- **Key Isolation:** On ESP32 gateway and endpoint devices, the 256-bit pre-shared key must be stored in Non-Volatile Storage (NVS) or an equivalent protected persistent secret store. Host-side keys must be supplied from a git-ignored environment file or secret source. Keys must never be committed to manifests or Git history.
- **Wire Representation & Authentication:** Policy commands use an **authenticated plaintext** format on the wire (no payload confidentiality is claimed). The ChaCha20-Poly1305 invocation authenticates the frame by supplying the header (bytes 0–51) concatenated with the policy payload (bytes 72–151) as Associated Authenticated Data (AAD, 132 bytes total) with zero plaintext/ciphertext length, producing the 16-byte Poly1305 tag (bytes 56–71).
- **Nonce Invariant:** The nonce input tuple must never repeat under the same authentication key. The normative design derives a 12-byte network-order nonce from `run_id` (64-bit) and `policy_epoch` (32-bit); this requires that `run_id` is unique per pre-shared key and `policy_epoch` is strictly monotonic within a run.
- **Replay Protection:** Replay and validity rejection is enforced by the complete stateful validation contract: matching `run_id`, active `boot_id`, strictly monotonic epoch (`policy_epoch > applied_epoch`), non-expired TTL, and local gateway/endpoint limits. Nonce uniqueness alone does not provide replay protection.
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
