# spore-decomp

A clean-room-style behavioral reimplementation of Spore's `SporeApp.exe`, built for
portability. Every reimplemented function is annotated with the original address it
mirrors (`@ 0x00XXXXXX`) and verified against the original code by differential tests.

**This repository contains no game code or data.** The binary-derived analysis
artifacts live in `work/` (git-ignored), are produced locally from your own copy of the
game, and must not be distributed.

## Layout
- `src/` — portable C++17 reimplementation (currently `resource/`: DBPF, RefPack, name hash)
- `tests/` — unit tests, plus corpus tests over your installed `Data/` when `SPORE_DATA` is set
- `tools/steamstub_analysis_image.py` — makes a non-runnable, decrypted analysis image
- `tools/ghidra/` — PyGhidra scripts (discovery, naming, decompile, xrefs)
- `tools/difftest/` — Unicorn harness that calls original functions by address
- `symbols/names.txt` — recovered names with provenance
- `docs/` — plan and file-format notes

## Setup
```sh
python3 -m venv .venv && .venv/bin/pip install pefile capstone pycryptodome unicorn
.venv/bin/python tools/steamstub_analysis_image.py "<Spore>/SporeBin/SporeApp.exe" \
    work/SporeApp.analysis.bin work/SporeApp.analysis.json
cmake -S . -B build -G Ninja && cmake --build build
SPORE_DATA="<Spore>/Data" ctest --test-dir build --output-on-failure
```
Ghidra project setup (about 20 min): see `docs/PLAN.md`.

## License
Released under the **GNU General Public License v3.0** — see [`LICENSE`](LICENSE).
Third-party components and the status of binary-derived artifacts are described in
[`THIRD_PARTY.md`](THIRD_PARTY.md).
