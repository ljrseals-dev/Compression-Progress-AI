# Public-domain reference books

## Included locally

1. **`survival_1957.txt`** — OCR text of U.S. Army Field Manual FM 21-76, *Survival* (1957 edition). U.S. federal government work; public domain in the United States. Used by the Emergency Grounder demo.

## Downloaded and committed Project Gutenberg books

The complete plain-text files below are now present in this directory. The source text, including Project Gutenberg headers, license notices, and end markers, was preserved. Original Gutenberg catalog pages identify these editions as public domain in the United States.

| Title | Gutenberg | Local file | Source size (bytes) |
|---|---:|---|---:|
| *The Senses and the Mind* — Anonymous | [46078](https://www.gutenberg.org/ebooks/46078) | [the_senses_and_the_mind_46078.txt](the_senses_and_the_mind_46078.txt) | 304,060 |
| *The Sense of Taste* — Harry L. Hollingworth and Albert T. Poffenberger | [59082](https://www.gutenberg.org/ebooks/59082) | [the_sense_of_taste_59082.txt](the_sense_of_taste_59082.txt) | 307,436 |
| *The World I Live In* — Helen Keller | [27683](https://www.gutenberg.org/ebooks/27683) | [the_world_i_live_in_27683.txt](the_world_i_live_in_27683.txt) | 174,328 |
| *Popular Education* — Ira Mayhew | [27742](https://www.gutenberg.org/ebooks/27742) | [popular_education_27742.txt](popular_education_27742.txt) | 905,573 |
| *Miller's Mind Training for Children*, Book 1 — *The Senses and Faculties* | [54814](https://www.gutenberg.org/ebooks/54814) | [millers_mind_training_book_1_54814.txt](millers_mind_training_book_1_54814.txt) | 164,887 |
| *Miller's Mind Training for Children*, Book 2 — *Training the Memory* | [55508](https://www.gutenberg.org/ebooks/55508) | [millers_mind_training_book_2_55508.txt](millers_mind_training_book_2_55508.txt) | 178,337 |
| *Miller's Mind Training for Children*, Book 3 — *Helps in School* | [55509](https://www.gutenberg.org/ebooks/55509) | [millers_mind_training_book_3_55509.txt](millers_mind_training_book_3_55509.txt) | 156,668 |

**Retrieval route:** direct Gutenberg downloads were unavailable from the execution environment. Complete UTF-8 texts were retrieved from the corresponding public GITenberg GitHub mirrors, which track Project Gutenberg eBook text and metadata. Examples: [The Sense of Taste mirror](https://github.com/GITenberg/The-Sense-of-Taste_59082), [The World I Live In mirror](https://github.com/GITenberg/The-World-I-Live-In_27683), [Popular Education mirror](https://github.com/GITenberg/Popular-EducationFor-the-use-of-Parents-and-Teachers-and-for-Young-Persons-of-Both-Sexes_27742). The other mirror repositories follow the same GITenberg naming convention; Gutenberg catalog IDs above are the canonical work references.

## Additional candidate not yet downloaded

- *What You Should Know About Your Sensations* — Grace Kinckle Adams, [Project Gutenberg #78983](https://www.gutenberg.org/ebooks/78983). A useful compact sensory-perception text. Its catalog record and HTML reading text were found, but a complete plain-text mirror was not available through the current retrieval route, so it is not represented as a local file.

## Wayback Machine fallback

For the four original titles, Wayback history can be checked if a future mirror/source becomes unavailable:

- [PG 46078 text history](https://web.archive.org/web/*/https://www.gutenberg.org/cache/epub/46078/pg46078.txt)
- [PG 59082 text history](https://web.archive.org/web/*/https://www.gutenberg.org/cache/epub/59082/pg59082.txt)
- [PG 27683 text history](https://web.archive.org/web/*/https://www.gutenberg.org/cache/epub/27683/pg27683.txt)
- [PG 27742 text history](https://web.archive.org/web/*/https://www.gutenberg.org/cache/epub/27742/pg27742.txt)

These are wildcard history searches, not a claim that a particular snapshot is available.

## Integrity verification

Each of the seven committed files was fetched back from the integration branch and checked for both the Project Gutenberg start marker and end marker. The GitHub blob SHA-1 values below identify the exact committed blobs (they are Git object IDs, **not SHA-256 checksums**).

| Local file | Git blob SHA-1 |
|---|---|
| `the_senses_and_the_mind_46078.txt` | `8754d0e9069995607e19a8884e72c91bdf2abc13` |
| `the_sense_of_taste_59082.txt` | `b8f7a31fa989c1953db52fff1c1d7d3fcd11079c` |
| `the_world_i_live_in_27683.txt` | `00db624a577debf72caf66c05bb88635bddb6477` |
| `popular_education_27742.txt` | `a1078d5880322e064f8b4962c530ba8dfbb7f131` |
| `millers_mind_training_book_1_54814.txt` | `f4ee7bfd425e9072884d4cc2ce6447d244c5b1ac` |
| `millers_mind_training_book_2_55508.txt` | `7b6385c299025cf5e1c3dfad15805bb9706445f2` |
| `millers_mind_training_book_3_55509.txt` | `a3f812c7f616f60b9997b41b77baccc71198b7cc` |

## Suggested compression test coverage

- **Input sizes:** short excerpts, medium books, and the long *Popular Education* corpus.
- **Vocabulary diversity:** sensory perception, taste, touch, sight, hearing, smell, memory, education, and narrative prose.
- **Robustness:** compare raw text with separately normalized derivatives; do not silently alter originals.
- **Regression:** pin corpus file hashes, then compare compressed size/ratio, runtime, and semantic-loss measures across versions.

Keep source texts immutable. Put cleaned or normalized test fixtures in separate derived files and document each transformation. These are text corpora for the host repository's text/sensory experiments, not audio inputs for the neural audio compressor.

Project Gutenberg: https://www.gutenberg.org/
GITenberg mirrors: https://github.com/GITenberg
Internet Archive: https://archive.org/
Wayback Machine: https://web.archive.org/
