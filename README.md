# spore-decomp

Rebuilding Spore's `SporeApp.exe` (2008, PC) as readable C++ that compiles to **exactly** the retail machine code,
one function at a time, with the original compilers (Visual C++ 2008 SP1, and the Visual C++ Toolkit 2003 for Havok
and RenderWare). Every function is annotated with the original address it rebuilds (`// @ 0x00XXXXXX`).

- **Help out:** [`AGENTS.md`](AGENTS.md) — setup, the work loop, and the rules (for people and AI agents alike).
- **Progress:** [`PROGRESS.md`](PROGRESS.md) — byte-exact functions and bytes, updated on every merge.
- Every pull request is checked byte for byte against retail fingerprints (no game files involved).

**This repository contains no game code or data.** The binary-derived analysis
artifacts live in `work/` (git-ignored), are produced locally from your own copy of the
game, and must not be distributed.

## Layout
- `src/game/` — the rebuilt game: one source file per original object file, plus generated class headers in `src/game/include/`
- `match/slices/` — functions still being decompiled or not yet moved into `src/game/`
- `tools/contrib/` — the contributor tools (`task.py`, `check.py`, `make_image.py`); `tools/ci/` — the pull-request check
- `src/resource/` — portable C++17 reimplementation of the file formats (DBPF, RefPack, name hash)
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
Released under the **GNU General Public License, version 2** (GPL-2.0-only) — see [`LICENSE`](LICENSE).
Third-party components and the status of binary-derived artifacts are described in
[`THIRD_PARTY.md`](THIRD_PARTY.md).
