# Benchmark Readiness and Optimization Audit — 2026-11-25

## Scope

- Four C++20 educational demos in `ljrseals-dev/Compression-Progress-AI`.
- Neural training entry point in the separate `ljrseals-dev/Neural-Compressor-Script` repository.
- Preserve the four C++ demos as the frozen comparison baseline. Do not silently change their behavior.

## Frozen baseline reference

| Field | Recorded value |
|---|---|
| Baseline commit | `07a3044ee28a056d8d5051d99600ad7d3cc4a231` (Compression-Progress-AI `main` at audit time) |
| Compiler command in Makefile | `g++ -std=c++20 -Wall -O2` |
| Demo output capture | **Not recorded yet** |
| Benchmark execution | **Not run in this audit** |

The four source files are unchanged on the integration branch relative to this baseline commit. The Makefile builds `tutor`, `grounder`, `hunter`, and `filter` independently.

## Finding 1 — Neural training is not independently runnable

The tracked neural entry point imports modules absent from `Neural-Compressor-Script`:

| Import | Status |
|---|---|
| `model.blocks` | Missing |
| `model.losses` | Missing |
| `training.dataset` | Missing |

The entry point is stored as root-level `training.train.py`, while its usage examples invoke `python -m training.train`. Those paths do not match. In addition, `ROOT = Path(__file__).resolve().parents[1]` resolves to the parent of the repository when the script is at the root, not the repository root.

No training run, trained weights, or neural performance result is claimed. Any temporary implementation of the missing imports must be explicitly labeled **non-reproducible scaffold** and must not be described as a trained model.

## Finding 2 — C++ demos are heuristic proxies

The four programs are educational text/string heuristics. They are not real compression codecs and do not implement a learned compressor. Their proxy scores are not interchangeable with compressed byte counts, bitrate, reconstruction quality, or audio quality.

## Static optimization and correctness observations

These observations are from source inspection only; they are not measured performance results.

### `src/sensory_compression_tutor.cpp`

- Tokenization uses `std::isalnum(c)` and `std::tolower(c)` directly on `char`. Negative signed-char values can cause undefined behavior. Convert through `unsigned char` before calling the ctype functions.
- The tokenizer does not flush the final token after the loop, so an observation ending in an alphanumeric token can omit that token from the unique-token set.
- Unique-token insertion uses a vector plus linear search, making accumulation increasingly expensive as vocabulary grows. A hash set or sorted-token pass can reduce lookup cost, but should be introduced only in an optimized variant so baseline outputs remain comparable.

### `src/emergency_multimodal_grounder.cpp`

- `tolower` is called on plain `char`; use an `unsigned char` conversion to avoid undefined behavior for non-ASCII bytes.
- `contains_any` compares only the first up-to-eight characters of the query. An empty query therefore matches every string because searching for an empty substring succeeds. Define and test empty-query behavior explicitly.
- Repeated calls to `load_knowledge` append to the existing knowledge vector; decide whether loading should replace or append and test that contract.

### `src/cross_sense_pattern_hunter.cpp`

- Token normalization uses plain-char `tolower`; use an `unsigned char` conversion.
- The tokenizer splits only on whitespace, unlike the tutor's punctuation-aware tokenizer. Treat this as a semantic difference in the baseline; do not compare their token counts as if they shared one tokenizer.
- Recomputing all modality costs after every insertion is acceptable for a small demo but scales poorly as modality text grows. An optimized variant can cache per-modality token sets and update the joint set incrementally.

### `src/anti_overthinking_filter.cpp`

- Token normalization uses plain-char `tolower`; use an `unsigned char` conversion.
- `unique_token_count` uses a vector and linear membership checks. A hash set can reduce the cost for large candidate answers.
- The density value is unique whitespace-delimited tokens divided by character count; it is a heuristic, not a validated measure of information content. Keep the metric name and interpretation explicit in benchmark output.

## Benchmark protocol required before optimization claims

1. Freeze baseline source at commit `07a3044ee28a056d8d5051d99600ad7d3cc4a231`; record compiler version, OS/CPU, exact flags, and build command.
2. Capture deterministic stdin fixtures and stdout/stderr for each demo. Record SHA-256 of each fixture and output.
3. Use identical fixtures for baseline and optimized variants. Include short, medium, and large text inputs; include the seven committed book corpora as text stress fixtures where a demo accepts text.
4. Perform one warm-up and at least five measured repetitions per case. Report median wall time, throughput (input bytes/s), peak RSS when available, exit status, and output equivalence.
5. Report proxy-specific values separately. Do not call proxy score changes a compression-ratio improvement.
6. Keep baseline binaries/source untouched. Place optimizations on a separate branch or behind an explicit build target.
7. Neural-vs-C++ comparisons remain blocked until the neural dependencies are restored and both systems can process the same defined task, input, and metric.

## Optimization order

1. Fix ctype safety and the tutor's final-token omission in a separate optimized variant; add regression cases for ASCII, UTF-8 byte sequences, punctuation, and trailing tokens.
2. Replace linear unique-token membership with an appropriate set/container and benchmark crossover points.
3. Cache cross-sense modality tokenization rather than rebuilding every set on each update.
4. Define empty-query and repeated-knowledge-load behavior for the grounder and cover both with tests.
5. Revisit the density heuristic only as a separately evaluated algorithm change; do not tune it against its own benchmark score.

## Status

- [x] Audit findings recorded.
- [x] Baseline commit and Makefile compiler flags identified.
- [ ] Capture and hash baseline demo outputs.
- [ ] Build and execute the four baseline demos in a controlled environment.
- [ ] Implement optimized variants separately.
- [ ] Run before/after benchmarks and correctness comparisons.
- [ ] Restore the missing neural modules and repair the neural entry-point layout.
- [ ] Run reproducible neural training and evaluate on a held-out set.

**Current result:** benchmark readiness audit only. No performance numbers, test passes, neural training, or optimization wins are claimed.
