## Summary

Brief description of what this PR changes and why.

## Checklist

- [ ] Host build passes: `cmake -S . -B build -DCLDT_BUILD_TESTS=ON && cmake --build build --parallel`
- [ ] Tests run: `ctest --test-dir build --output-on-failure`
- [ ] All experiment manifests pass schema validation
- [ ] No secrets, credentials, or private network details in committed files
- [ ] No upstream dependency source code added to the repository
- [ ] Documentation updated if interfaces or manifests changed
- [ ] Current-scope changes remain inside the frozen four-board, one-action boundary
- [ ] Future ideas are placed in `FUTURE_PROJECTION.md` and do not alter the current BOM or acceptance criteria
- [ ] Any new hardware/model/action states the deliverable it replaces and its entry/stop gates

## Type

- [ ] `fix:` Bug fix
- [ ] `feat:` New interface or implementation
- [ ] `docs:` Documentation only
- [ ] `chore:` Build, CI, or tooling change
- [ ] `experiment:` Manifest or schema change
