# Contributing: rebuild Spore one function at a time

This project rebuilds Spore's `SporeApp.exe` (the 2008 PC game) as readable C++ that compiles to exactly the same
machine code as the shipped game. A function counts when its compiled bytes are identical to the retail function's.
"Almost" counts as zero.

This guide is for people and for AI agents. Everything here runs from the repo; no game files are needed until you
want instruction-level diffs.

## How a match is checked

Every pull request is checked by the **Byte-match check** (`.github/workflows/byte-match.yml`). It compiles the files
your change can affect with the original compilers and compares every function listed in a `manifest.txt` with a
**retail fingerprint** (`tools/ci/fingerprints.jsonl.gz`): the function's size, which byte positions hold addresses,
and a SHA-256 of the rest. Fingerprints contain no code and no names; the check never sees the game.

The check passes when every affected function matches its fingerprint (apart from the long-standing ones in
`tools/ci/known_failures.txt`) and no function that matched before has been dropped. You can run the same check
locally (below) before you open the pull request.

## Setup (once)

1. Python 3.10+:
   `python3 -m venv .venv && .venv/bin/pip install pefile capstone pycryptodome`
2. Wine (any recent version; on Windows the compilers run directly) and `msitools` (`msiextract`).
3. The compilers, from Microsoft's own installers (about 120 MB, nothing is installed, every file is hash-checked):
   `sh tools/ci/setup_toolchain.sh`
   This gives Visual C++ 2008 SP1 (cl 15.00.30729.01) for most of the game and the Visual C++ Toolkit 2003 1.01
   (cl 13.10.3077) for Havok and RenderWare code (rows with the `/vc71` flag).
4. Optional, for instruction diffs: your own copy of Spore (Steam). Build the analysis image from it:
   `.venv/bin/python tools/contrib/make_image.py "<Spore>/SporeBin/SporeApp.exe"` (must print `IMAGE OK`).
   The image is game code. It stays in `work/`, which git ignores. Never commit, upload or share it.

## The loop

1. **Pick a function.** `.venv/bin/python tools/contrib/task.py --list --max-size 128` lists functions that already
   have complete C++ source whose bytes still differ, smallest first, with the note left by whoever worked on it last.
   Small functions are the place to start.
2. **Read its context.** `.venv/bin/python tools/contrib/task.py 0x00529690` prints its source file, status, compiler
   flags, retail size, includes and current source.
3. **Say you are on it.** Open a draft pull request early, titled with the address (`0x00529690: ...`), so others can
   see the function is taken.
4. **Write, build, compare.** Edit the source, then `.venv/bin/python tools/contrib/check.py 0x00529690`. It prints
   `MATCH`, the compiler errors, or what differs (with the image from setup step 4, an instruction diff).
5. **On MATCH**, `check.py` prints the `manifest.txt` line to add. Add it, remove the function's line from
   `nonmatching.txt` (or `partial.txt`), and mark the pull request ready. Fill in the template, including the model or
   tool that wrote the code.
6. **Stuck?** Leave the function better than you found it: update its `nonmatching.txt` note with what you tried and
   what still differs, and open the pull request anyway. Notes are how the next person (or agent) starts ahead.

## Everything else is fair game

To match your function you may change **any other function, source file, header, constructor, class layout, struct
member, global declaration or include** in the contribution paths (`src/game/`, `match/slices/`, `match/include/`).
Fix a wrong member offset, add a missing field, replace a local stand-in struct (`Foo_s0052_88f0`) with the real class
header, reorder declarations, split or merge files: all welcome. The only condition is the check itself: every
function that matched before must still match.

Headers under `src/game/include/` were generated from the developers' debug database and say "do not hand-edit". You
may still edit them; say what you changed and why in the pull request, and maintainers will carry confirmed layout fixes
into the generator's inputs so they are not lost.

## Rules

- Write real, readable C++ that compiles to the original bytes, with the class and member names the headers give you.
- No inline assembly, `__declspec(naked)`, `_emit` or raw bytes: the check rejects assembly transcriptions.
- Do not write a constant as the address of a made-up global (`&g_Table2458018` for `0x2458018`): the check sees the
  relocation and fails it.
- Only `src/game/`, `match/slices/` and `match/include/` can change in a contribution. Changes to `tools/`, `.github/`
  or the fingerprints need a maintainer; put them in a separate pull request.
- Never commit game files, the analysis image, disassembly or dumps of game code.
- The open-source libraries the game links (jpeg, libpng, OpenSSL, EA's EABase/EASTL/EAText/EAWebKit) are out of scope:
  they are rebuilt from their published sources, not decompiled.

## Where to read more

- `docs/codegen.md`: how the 2008 and 2003 compilers turn source into the shapes you see in a diff, and which source
  choices move them. Read it once; it saves many builds.
- `docs/matching.md`: matching workflow, flags, and the `/vc71` code.
- `tools/ci/fingerprint.py`: exactly what the check compares.
