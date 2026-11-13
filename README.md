# spore-decomp

Rebuilding Spore's `SporeApp.exe` (2008, PC) as readable C++ that compiles to **exactly** the retail machine code,
one function at a time, with the original compilers (Visual C++ 2008 SP1, and the Visual C++ Toolkit 2003 for Havok
and RenderWare). Every function is annotated with the original address it rebuilds (`// @ 0x00XXXXXX`).

**Spore and Galactic Adventures are effectively one program.** The current PC release (Steam and GOG, rebuilt by EA
in 2024) ships two executables, `SporeBin/SporeApp.exe` (Spore) and `SporebinEP1/SporeApp.exe` (Galactic
Adventures). Both were built from the Galactic Adventures source tree an hour apart, with the same compilers and
options: **99.75% of Spore's functions (90,260 of 90,482) are byte-identical in Galactic Adventures**, which adds
about 1% of different code (mostly creature, tribe and vehicle behavior) and 4 MB of localized icons. Steam's and GOG's
copies of each executable are identical apart from Steam's DRM section. So everything rebuilt here is Galactic
Adventures code too; the fingerprints and addresses are those of `SporeBin/SporeApp.exe`.

- **Progress:** [noahbpeterson.github.io/spore-decomp](https://noahbpeterson.github.io/spore-decomp/) (charts, modules,
  contributors), and the full tables in
  [`PROGRESS.md`](https://noahbpeterson.github.io/spore-decomp/PROGRESS.md), both rebuilt after every change.
- **Contribute:** below, then [`AGENTS.md`](AGENTS.md) for the full loop and the rules (written for people and AI
  agents alike).

**This repository contains no game code or data.** Pull requests are checked against retail *fingerprints* (sizes,
address positions and hashes, no code). Anything derived from your own copy of the game stays in `work/`, which git
ignores, and must not be distributed.

## Contribute in five minutes

Over 23,000 functions already have complete C++ source whose compiled bytes still differ from the original, about
500 of them by only one to four bytes. Pick one, change the source until its bytes are identical, and open a pull
request.

You need Python 3.10+, Wine and `msitools` (macOS or Linux; on Windows, use WSL), and your own copy of Spore (Steam or GOG).

```sh
python3 -m venv .venv && .venv/bin/pip install pefile capstone pycryptodome
sh tools/ci/setup_toolchain.sh             # the original compilers, from Microsoft's installers, hash-checked
sh tools/ci/setup_oss.sh                   # the open-source libraries some functions compile from, hash-checked
.venv/bin/python tools/contrib/make_image.py "<Spore>/SporeBin/SporeApp.exe"   # Steam or GOG; must print IMAGE OK

.venv/bin/python tools/contrib/task.py --list          # fewest tries first, your own order; claimed ones hidden
.venv/bin/python tools/contrib/task.py 0x00ee9260      # one function: its file, flags, note and source
.venv/bin/python tools/contrib/check.py 0x00ee9260     # MATCH, or an instruction diff against the original
```

On `MATCH`, `check.py` updates the bookkeeping files itself; open a pull request with your change. One function (or a
few) per pull request, using the template.

**If you are an AI agent:** read [`AGENTS.md`](AGENTS.md) first and follow it. The short version:
- Only `src/game/`, `match/slices/` and `match/include/` may change. Never commit anything from `work/`.
- No inline assembly (`__asm`, `_emit`, `__declspec(naked)`, raw bytes) and no constants written as addresses of
  invented globals: the check rejects these. A maintainer can approve a short helper when you ask for it with an
  `asm-override: <why>` line in the pull request body (AGENTS.md, Rules).
- Before trying new source shapes, look up the difference in [`docs/codegen.md`](docs/codegen.md). After six to eight
  levers without a match, move on. Code changes are merged only when they add a new byte-exact function; what you
  tried can go in as a notes-only pull request (the function's `nonmatching.txt` line).
- Once a pull request is marked ready, do not add commits to it; put new work in a new pull request.

Every pull request runs the **Byte-match check**. It compiles every function your change can affect and compares
it with the retail fingerprints, and it fails if anything that matched before stops matching. You can run the same
check locally:
`.venv/bin/python tools/ci/gate.py <manifest.txt ...> --known tools/ci/known_failures.txt`.

## Layout
- `src/game/`: the rebuilt game, one source file per original object file, plus generated class headers in
  `src/game/include/`
- `match/slices/`: functions still being decompiled or not yet moved into `src/game/`
- `tools/contrib/`: the contributor tools (`task.py`, `check.py`, `make_image.py`); `tools/ci/`: the pull-request check
- `docs/codegen.md`: how the 2008 and 2003 compilers turn source into the shapes you see in a diff
- `src/resource/`: portable C++17 reimplementation of the file formats (DBPF, RefPack, name hash)
- `tests/`: unit tests, plus corpus tests over your installed `Data/` when `SPORE_DATA` is set
- `tools/difftest/`: Unicorn harness that calls original functions by address
- `tools/ghidra/`: PyGhidra scripts (discovery, naming, decompile, xrefs)
- `symbols/names.txt`: recovered names with provenance

## Other development tasks
Building the file-format library and its tests:
```sh
cmake -S . -B build -G Ninja && cmake --build build
SPORE_DATA="<Spore>/Data" ctest --test-dir build --output-on-failure
```
Equivalence testing (`tools/difftest/`) also needs `pip install unicorn`. Ghidra project setup (about 20 min): see
`docs/PLAN.md`.

## License
Released under the **GNU General Public License, version 2** (GPL-2.0-only); see [`LICENSE`](LICENSE).
Third-party components and the status of binary-derived artifacts are described in
[`THIRD_PARTY.md`](THIRD_PARTY.md).
