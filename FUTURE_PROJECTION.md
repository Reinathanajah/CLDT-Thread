# FUTURE PROJECTION

> **Status: non-normative roadmap.** This document does not expand the current
> six-week implementation scope, hardware purchase list, experiment acceptance
> criteria, or claim surface. The current authorities remain [README.md](README.md),
> [DESIGN.md](DESIGN.md), [EXPERIMENTS.md](EXPERIMENTS.md), and
> [hardware/BOM.md](hardware/BOM.md). Sections labeled **Projection** do not
> become current implementation or procurement merely because they appear here.

## Purpose

CLDT-Thread is intentionally designed so that a small, completed physical study
can become the foundation for later work without pretending that later work has
already been built. This document summarizes the already-authorized depth
strategy and then records credible next steps, their scientific purpose, and the
evidence gate that must be passed before each one is adopted.

The governing rule is simple:

> A future component is admitted only when it answers a new research question,
> does not weaken the existing evidence chain, and has an explicit validation and
> removal criterion.

The roadmap is therefore a sequence of decisions, not a feature backlog.

## Frozen Version-One Boundary

The current implementation target remains:

- one ESP32-S3 gateway and edge policy guard;
- one dedicated ESP32-C6 OpenThread RCP using upstream firmware;
- two ESP32-C6 workload endpoints;
- UART Spinel for initial bring-up;
- synthetic deadline-sensitive and bulk application workloads;
- append-only host evidence and item-level reconciliation;
- naive, network-only, and cross-layer shadow-model comparisons;
- one four-state fail-closed fidelity gate (`COLD`, `OBSERVE`, `TRUSTED`,
  `ABSTAIN`) with explicit observation-integrity and calibrated-region inputs;
- one authenticated, expiring, bounded bulk-rate action; and
- local fallback plus stale, restart, and replay rejection evidence.

The current budget does not reserve hardware for the later phases below. A
future phase requires a new procurement decision and a revised manifest; it may
not be smuggled into a current run as an undocumented substitution.

## Version-One Depth Strategy Already In Scope

The following work is not a platform expansion. It is how the current four-board
question becomes credible. It remains ordered behind bring-up, recording, and
reconciliation gates in the six-week plan.

### Observation Integrity And Typed Diagnostics

Every scored horizon retains source presence, freshness, clock uncertainty,
run/model identity, and reconciliation status. Generated work, queue admission,
transport submission, MAC attempts, gateway receipt, and application acceptance
are typed stages rather than numbers forced into false equality. Missing or
contradictory evidence is a gate failure, never a favorable residual.

### Calibration-Envelope-Aware Abstention

Build a transparent support envelope from calibration-only values such as
offered load, queue occupancy, observation age, parent link quality, RSSI, MAC
retry/CCA rates, and observed role/parent/partition identity. Freeze its
normalization, categorical-state rules, and threshold before held-out scoring.

Compare three decisions on identical horizons:

1. Always trust.
2. Residual/freshness gating without region detection.
3. Residual/freshness gating with the calibrated-region check.

Report false trust, trusted-horizon fraction, selective prediction error,
false abstention in-domain, abstention latency, and requalification latency. A
gate that abstains everywhere is safe but not useful.

### Feature-Group Ablation

Using the same frozen runs and model family, compare network-only inputs with
incremental MAC, queue, and RTOS feature groups. This identifies which layer
contributes evidence instead of crediting every collected field equally.

### Deterministic Replay And Fault Injection

Replay archived frames and trace records through the portable decoder,
reconciliation logic, estimator, and gate while injecting one declared fault at
a time: truncation, corruption, duplication, reordering, expiry, missing
  terminal events, boot-ID change, durable replay-state loss, wrong run, and
  stale observation. Replay output is verification evidence; it is not a
  substitute for physical results.

### Bounded Topology Diagnostics

The existing nodes record role, RLOC16, parent, partition, RSSI/link quality, and
available MAC/MLE evidence at a cadence whose overhead is measured. A movement
is called a topology shift only if topology evidence actually changes; otherwise
it remains a placement or link-context shift.

## Admission Gate For Post-Core Expansion

No projected phase begins until all of the following exist for the current
system:

1. Repeatable cold-boot S3-to-RCP bring-up and a stable physical Thread baseline.
2. A run directory whose raw events pass item-level audit and aggregate
   reconciliation.
3. A one-command reproduction path that fails nonzero on incomplete or invalid
   evidence.
4. A frozen shadow model scored on held-out horizons.
5. Demonstrated gate abstention, command expiry, local fallback, and
   restart/replay rejection.
6. A written limitation statement that scopes every result to the measured
   hardware, placement, channel, workload, and software revisions.

Until those gates pass, additional hardware or optional comparisons are
integration risk rather than additional evidence.

## Projection A: Optional Studies On Existing Hardware

### Existing-AP Coexistence Pilot

A laptop may generate a predeclared Wi-Fi workload through the existing private
access point while the Thread channel, AP channel, positions, direction, rate,
and duration remain fixed. This is an optional controlled-context pilot, not a
jammer and not a new primary claim. A dedicated ESP32-C3 is unnecessary until a
laptop/AP workload is shown to be insufficiently repeatable.

### SMP/Unicore Comparison

The existing `smp-comparison` manifest may be admitted after the core safety
chain is complete. It pairs SMP and `CONFIG_FREERTOS_UNICORE` gateway builds from
the same source revision under identical topology and workload, with randomized
or alternated order and task/core plus queue evidence. It is dropped immediately
if maintaining two builds threatens final physical repetitions or reproduction.

## Projection B: Independent IEEE 802.15.4 Observation

A Nordic nRF52840 PCA10059-compatible dongle can later provide passive
IEEE 802.15.4 capture through the Nordic sniffer and Wireshark. Its role would be
supporting observation, never an infallible ground-truth oracle. Nordic lists
the PCA10059 as supported hardware for its 802.15.4 sniffer. [Nordic nRF Sniffer
for 802.15.4](https://docs.nordicsemi.com/r/bundle/nrf5_sdk_thread_zigbee/page/nrf802154_sniffer.html)

Adoption requires a pilot that demonstrates:

- captured channel and Thread key handling are documented without committing
  secrets;
- encryption/decryption boundaries and visible identifiers are understood;
- sniffer loss, placement, and USB timestamp uncertainty are measured;
- device, gateway, and capture clocks are aligned only within an explicit
  uncertainty bound; and
- disagreement is reported as observer inconsistency rather than silently
  resolved in favor of one source.

The passive capture stream must remain optional to the primary evidence path.
If its setup or availability fails, the completed version-one experiment still
stands.

## Projection C: Physical Topology Expansion

A fourth C6 may later become a dedicated topology node, but only after the
existing two endpoints already produce stable, repeated evidence. Joining or
moving a device does not by itself prove that topology changed. Every claimed
topology regime must be supported by actual role, RLOC16, parent, child/router
table, partition, RSSI/link-quality, and MLE/MAC counter evidence.

The extra node must not double as the only emergency replacement for the RCP or
an endpoint. A board assigned to an experiment is not simultaneously a protected
spare.

OpenThread exposes topology and neighbor diagnostics, but some mesh-diagnostic
APIs require Full Thread Device and build-time configuration support. [OpenThread
Mesh Diagnostics](https://openthread.io/reference/group/api-mesh-diag)

## Projection D: Power And Energy Metrology

INA226 is a more suitable coarse observer than the earlier INA219 assumption
because it provides a 16-bit ADC, configurable averaging, and a 2.5 microvolt
shunt-voltage step. The current source remains instrument-neutral and deferred.
INA226 is still a medium-timescale power/energy monitor rather than a waveform
instrument. [TI INA226 datasheet](https://www.ti.com/lit/ds/symlink/ina226.pdf)

Before adoption, a power experiment must freeze:

- the measured rail and whether regulator, LEDs, serial interface, and sensor
  consumption are inside the boundary;
- shunt value, offset, calibration method, conversion time, averaging, and
  sampling overhead;
- mutually exclusive USB/header power wiring; and
- a companion critical-service floor.

Deep-sleep or microsecond RF-transient claims require a suitable dedicated power
profiler. They must not be inferred from INA226 averages.

## Projection E: Broader Bounded Control

Finite-horizon or multi-action policy selection is considered only after one
bulk-rate-reduction command has passed authentication, freshness, local-limit,
fallback, and post-actuation verification tests. A future controller may choose
only from a small prevalidated discrete action set; it may not synthesize
arbitrary device commands.

Entry requires:

- an identified model with validated multi-step behavior;
- frozen cost terms and service constraints selected without target-result
  leakage;
- safe evaluation in shadow mode before physical actuation;
- comparison against no-action and the existing single-action controller; and
- evidence that added control complexity improves a declared outcome.

Reinforcement learning, neural prediction, or unrestricted optimization is not
an automatic next step. Model complexity is admitted only when a simpler model
fails a predeclared requirement.

## Projection F: Simulation And Other Network Domains

An ns-3 phase would calibrate a narrowly scoped IEEE 802.15.4/6LoWPAN model
against completed hardware evidence before using it for scale exploration. It
would not be presented as full Thread equivalence without validating the missing
behavior. The ns-3 model documentation itself notes validation limitations for
the LR-WPAN model. [ns-3 Model Library](https://www.nsnam.org/docs/models/singlehtml/)

An O-RAN/FlexRIC adaptation is a separate project. It could reuse the generic
observation-model-gate-proposal pattern, but a credible implementation requires
real E2/RIC and RAN components and service-model semantics. A conceptual mapping
may appear in discussion; it must be labeled non-interoperable and must not be
counted as an O-RAN implementation.

## Projection Order And Exit Decisions

| Projection | Earliest Entry | Continue Only If | Stop Or Revert If |
|---|---|---|---|
| A: Optional existing-hardware studies | Core safety chain is complete | The paired study answers one predeclared question | It delays final repetitions or reproduction |
| B: Passive observer | Core result is already reproducible | Capture adds attributable, uncertainty-qualified evidence | Capture becomes a required but unreliable truth source |
| C: Extra topology node | Two-endpoint runs are stable | Distinct topology regimes occur and are observable | The node only adds uncontrolled variation |
| D: Power metrology | Service results are already valid | Measurement resolution and boundary support the claim | Instrument uncertainty dominates the effect |
| E: Multi-action control | Single action is proven safe | Added actions outperform simpler control under frozen rules | Weights/actions are tuned after seeing target outcomes |
| F: Simulation/domain transfer | Hardware study is complete | The new domain has its own validation plan | It is used only to add platform names |

## Claim Discipline

The roadmap does not change the claim ladder:

- traces loaded after a run: **offline model**;
- live observations updating a model: **digital shadow**;
- verified observation, bounded proposal, physical application, fallback, and
  returned outcome: **closed-loop digital twin under the tested conditions**;
- RTA-like monitor and fallback structure without certification evidence:
  **runtime-assurance-inspired**, not safety-certified;
- passive capture with measured omissions: **independent supporting observer**,
  not RF ground truth.

The strongest future project is not the one that adopts every projection. It is
the one that adopts the smallest next phase capable of answering one new,
falsifiable question.
