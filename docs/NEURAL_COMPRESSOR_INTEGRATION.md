# Neural Compressor Integration Audit

## Target

`ljrseals-dev/Compression-Progress-AI`

## Source

`ljrseals-dev/Neural-Compressor-Script`

## Audit finding

The neural source repository currently contains a README, LICENSE, image assets, and a single `training.train.py` file. The training script imports modules that are not present in the repository:

- `model.blocks` (`ParameterProbe`, `build_model`)
- `model.losses` (`CompressorLoss`, `curve_loss`, `param_loss`, `smoothness_loss`)
- `training.dataset` (`SyntheticCompressorDataset`, `collate`)

The training entry point therefore is not independently runnable from the tracked files in its repository as audited. No complete model definition, dataset implementation, loss implementation, trained weights, or supported inference/export API was found in the source tree.

## Host architecture observed

Compression Progress AI currently contains four separate C++20 educational programs:

- `sensory_compression_tutor.cpp`
- `emergency_multimodal_grounder.cpp`
- `cross_sense_pattern_hunter.cpp`
- `anti_overthinking_filter.cpp`

The existing programs use heuristic/string compression proxies. No common compressor interface or neural inference integration point was found in the audited source files.

## Integration guardrails

1. Preserve the four existing demos and their current behavior.
2. Treat the existing compression/progress calculations as the baseline; do not silently replace them with neural output.
3. Neural inference must be optional and explicitly enabled; the baseline path must work without Python, PyTorch, model weights, or neural runtime dependencies.
4. Validate all neural outputs for finite values, expected dimensions, and allowed ranges before accepting them.
5. If loading, inference, or validation fails, fall back to the baseline behavior and report the fallback reason.
6. Keep training separate from host runtime inference. Do not invoke training during normal host execution.
7. Measure neural/hybrid changes against the baseline with reproducible inputs and report whether compression-progress metrics actually improve.
8. Do not claim neural functionality, model weights, tests, or end-to-end integration are implemented until the missing source dependencies and a usable inference/export artifact are supplied and verified.

## Proposed integration sequence

- **Phase 0 — Audit (this document):** Confirm host and neural source layout; record missing neural package files.
- **Phase 1 — Recover complete neural source:** Obtain the model blocks, losses, dataset implementation, dependencies, and license/usage constraints; verify training starts.
- **Phase 2 — Define host contract:** Introduce a small optional neural backend interface with explicit input/output shape, versioned model metadata, and fallback behavior.
- **Phase 3 — Implement inference adapter:** Prefer a documented portable export format/runtime or an isolated Python inference service only if the runtime requirements are accepted. Keep the C++ baseline dependency-free.
- **Phase 4 — Validate and benchmark:** Add deterministic tests for malformed outputs, unavailable backend, fallback, repeatability, and baseline-vs-neural metrics.
- **Phase 5 — Review:** Cross-audit source, build, tests, docs, and changed files before merge.

## Current status

**Audit groundwork only.** This branch contains integration audit documentation. It does not yet implement neural compression or add neural runtime dependencies.
