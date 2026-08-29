# SECURITY POLICY

## Scope

This repository is a **research scaffold**, not a production system. The authentication interface (`cldt_authenticator_t`) is defined but not yet implemented. No cryptographic claim is made at the current scaffold stage.

The project plans to use a maintained platform cryptographic primitive for command authentication before any remote actuation is enabled. The implementation must:

- Document the covered bytes and tag verification procedure.
- Keep secrets out of manifests, source files, and Git history.
- Include known-answer tests before the authenticator is trusted in a physical run.

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
