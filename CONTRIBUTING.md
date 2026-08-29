# CONTRIBUTING

This repository is a research scaffold for a hardware-in-the-loop digital twin study. Contributions are welcome when they respect the evidence-first discipline described below.

## Build Prerequisites

- Git
- CMake 3.20 or newer
- A C11 compiler (GCC, Clang, or MSVC)
- Python 3.12 or newer (for manifest validation and `host/analysis/reproduce.py`)
- ESP-IDF v5.2 or newer (for firmware targets; requires `CONFIG_MBEDTLS_CHACHAPOLY_C=y`)

## Host Build And Reproduction

```bash
cmake -S . -B build -DCLDT_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

At the scaffold stage, all four test executables return skip code 77. A green build proves interface consistency, not a working digital twin.

To run the analysis and evidence reproduction pipeline against a run directory:

```bash
python host/analysis/reproduce.py results/sample_run/
```

## Manifest Validation

Install the schema validator and check all experiment files:

```bash
python -m pip install "jsonschema==4.26.0"
python -c "
import json, pathlib
from jsonschema import Draft202012Validator
schema = json.loads(pathlib.Path('schemas/experiment.schema.json').read_text())
Draft202012Validator.check_schema(schema)
v = Draft202012Validator(schema)
for p in sorted(pathlib.Path('experiments').glob('*.json')):
    errors = sorted(v.iter_errors(json.loads(p.read_text())), key=lambda e: list(e.path))
    print(f'{p.name}: {\"FAIL\" if errors else \"OK\"}')"
```

## Rules

1. **Do not commit secrets.** Wi-Fi credentials, broker passwords, and private keys belong in `.env` files (which are git-ignored) or a local secrets directory.
2. **Do not vendor upstream dependencies.** ESP-IDF, OpenThread, and Mosquitto are external. Pin and record their versions when building; do not copy their source trees into this repository.
3. **Do not modify prior run evidence.** Raw experiment data is append-only. Derived analysis may be regenerated, but raw traces and terminal status files must not be edited or deleted.
4. **One change per commit.** Separate build fixes, documentation changes, manifest updates, and code changes into distinct commits with conventional prefixes (`fix:`, `docs:`, `feat:`, `chore:`).
5. **Validate before pushing.** Every strict JSON manifest in `experiments/` must pass schema validation. The CI workflow enforces this automatically.

## Code Style

The `.editorconfig` file defines formatting:

- C/H files: 4-space indentation, UTF-8, LF line endings
- JSON/YAML files: 2-space indentation
- Makefiles: tab indentation

Use the compiler warnings enabled in the CMake files (`-Wall -Wextra -Wpedantic -Wconversion` or `/W4` on MSVC). Do not suppress warnings without a documented reason.

## Experiment Changes

When modifying an experiment manifest:

1. Edit the JSONC authoring companion in `experiments/authoring/` first.
2. Copy only completed values into the strict JSON counterpart in `experiments/`.
3. Keep `experiment_id` identical between the JSONC and JSON files.
4. Set `state` to `ready` only when every field has a concrete value and `_todo` is empty.
