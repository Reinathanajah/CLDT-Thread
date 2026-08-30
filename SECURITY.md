# SECURITY POLICY

## Scope

This repository is a **research scaffold**, not a production system. Policy command authentication is specified to use **ChaCha20-Poly1305 AEAD** (RFC 8439) with an mbedTLS backend (`common/include/cldt/cldt_auth.h`, `common/src/cldt_auth.c`). At the current scaffold stage, the interface is defined and implementation stubs return `CLDT_ERR_NOT_IMPLEMENTED`.

Remote actuation is disabled by maturity, not merely by configuration: it must
not be enabled until fixed authentication/CRC vectors, strict nonce/epoch rules,
gateway and endpoint rejection tests, observation-integrity failure behavior,
expiry, local fallback, and restart/replay cases all pass. A shadow-only model
does not require command keys on endpoints.

- **Key Isolation:** On ESP32 gateway and endpoint devices, the dedicated 256-bit command-authentication pre-shared key must be stored using an explicitly documented local secret mechanism; ordinary unencrypted NVS alone must not be described as protected storage. Production-strength NVS/flash encryption is outside the current scaffold claim. Host-side keys must be supplied from a git-ignored environment file or secret source. Keys must never be committed to manifests, packet captures, screenshots, or Git history. Because version 1 uses a symmetric group key, it detects network modification and unauthorized senders without that key; it does not claim origin separation from a compromised admitted device that holds the same key.
- **Wire Representation & Authentication:** Policy commands use an **authenticated plaintext** format on the wire (no payload confidentiality is claimed). The ChaCha20-Poly1305 invocation authenticates the frame by supplying the header (bytes 0–51) concatenated with the policy payload (bytes 72–151) as Associated Authenticated Data (AAD, 132 bytes total) with zero plaintext/ciphertext length, producing the 16-byte Poly1305 tag (bytes 56–71).
- **CRC Boundary:** CRC-32C covers the same canonical `header bytes 0–51 || payload` sequence for every frame. The CRC and authentication slots are omitted from that sequence; neither field recursively covers itself.
- **Nonce Invariant:** The nonce input tuple must never repeat under the same authentication key. The normative design derives a 12-byte network-order nonce from `run_id` (64-bit) and `policy_epoch` (32-bit); this requires that `run_id` is unique per command key and `policy_epoch` is strictly monotonic within a run. Before opening any run, the host must reserve a nonzero cryptographically generated ID in a durable global run ledger and collision-check it against that ledger; an actuated run also records the non-secret identity of its command key. A coordinator-process or gateway reboot cannot resume the old actuated run; it requires a newly reserved run. If ledger continuity is lost, rotate the command key before remote actuation rather than risk nonce reuse. Shadow-only operation still requires no endpoint command key.
- **Global Command And Single Epoch:** Version 1 defines one global policy datagram for all endpoints admitted to a run. The command header uses reserved coordinator node ID `0`; its boot ID identifies the host coordinator process for that run, not the gateway or an endpoint target. The gateway guards and forwards the identical authenticated datagram. An epoch identifies one immutable byte string; fan-out and retries resend those exact bytes. Different per-endpoint commands or gateway-authored emergency commands require a future key/nonce/wire contract and are outside version 1.
- **Replay Protection:** Replay and validity rejection is enforced by the complete stateful validation contract: commissioned coordinator identity, matching enrolled `run_id`, strictly monotonic epoch (`policy_epoch > highest_applied_epoch`), non-expired TTL, and local gateway/endpoint limits. Each endpoint must integrity-check its durable `(run_id, coordinator_boot_id, highest_applied_epoch)` record at boot and atomically advance the epoch **before** applying a new policy. Missing, corrupt, or unwritable replay state forces the compiled safe policy and requires explicit enrollment of a new unique run; endpoint `boot_id` is evidence of restart, not replay protection. Nonce uniqueness alone does not provide replay protection.
- **Withdrawal Boundary:** Version one does not let the gateway synthesize a second command under the coordinator's nonce space. On stale observation or backhaul failure, the gateway immediately selects its local fallback and stops forwarding proposals; each endpoint independently returns to its compiled safe policy no later than the accepted command's finite TTL. A faster authenticated revocation path requires a separately designed key/nonce contract and is deferred.
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
