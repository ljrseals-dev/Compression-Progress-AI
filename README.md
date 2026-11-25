# Compression Progress AI – C++20 Educational Implementations

This repository implements the four core prompts from the analysis of Jürgen Schmidhuber’s “Driven by Compression Progress” paper (arXiv:0812.4360) as educational C++20 programs.

The programs demonstrate the fundamental loop:
1. Store raw sensory/history data (“the data is holy”).
2. Attempt compression / pattern discovery.
3. Measure progress (reduction in description length or prediction residual).
4. Propose the next action that maximizes expected further progress.
5. Stay grounded – never invent data.

These are **simulators**, not full LLMs. They use simple string history, run-length / dictionary-style compression proxies, and explicit progress metrics so you can see the logic clearly and extend them.

## Structure

```
src/
  sensory_compression_tutor.cpp   # Prompt 1
  emergency_multimodal_grounder.cpp # Prompt 2
  cross_sense_pattern_hunter.cpp  # Prompt 3
  anti_overthinking_filter.cpp    # Prompt 4
books/                            # Public-domain reference works
examples/                         # Sample sensory logs
```

## Build (C++20)

```bash
# Requires a C++20 compiler (g++ 10+, clang 10+)
mkdir build && cd build
cmake ..   # or simply:
g++ -std=c++20 -O2 -o ../bin/tutor ../src/sensory_compression_tutor.cpp
# similarly for the others
```

Or use the provided Makefile.

## Public-domain books included (or linked)

All selected works are free of copyright restrictions in the United States (pre-1931 or U.S. federal government works).

1. **U.S. Army FM 21-76 Survival (1957 edition)** – full OCR text in `books/survival_1957.txt`. Classic public-domain survival manual used for emergency knowledge base examples.
2. **The Senses and the Mind** (Project Gutenberg #46078) – source: https://www.gutenberg.org/ebooks/46078
3. **The Sense of Taste** by H.L. Hollingworth (Project Gutenberg #59082) – source: https://www.gutenberg.org/ebooks/59082
4. **The World I Live In** by Helen Keller (Project Gutenberg #27683) – source: https://www.gutenberg.org/ebooks/27683 (profound exploration of senses without sight/hearing)
5. **Popular Education** by Ira Mayhew (Project Gutenberg #27742) – chapter on the education of the five senses.

Full modern downloads of the Gutenberg titles can be obtained when the site is available; the survival manual text is included.

## How the programs illustrate the theory

- **Tutor**: Interactive loop that stores observations, reports a crude compression ratio / residual, and suggests the next sensory probe that should yield the largest expected progress.
- **Emergency Grounder**: Loads survival knowledge, accepts multi-modal text logs, keeps a compressed model of the current situation, and refuses ungrounded claims.
- **Cross-Sense Hunter**: Takes multiple modality streams and looks for joint regularities that reduce total description length.
- **Anti-Overthinking Filter**: Forces minimal sufficient explanations and discards long monologues that do not reduce residual uncertainty.

## License

Code: MIT  
Books: Public domain (U.S.) as indicated by source.

Reference paper: Schmidhuber, J. (2009). Driven by Compression Progress… arXiv:0812.4360

