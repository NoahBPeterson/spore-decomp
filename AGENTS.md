# Contributing: rebuild Spore one function at a time

This project rebuilds Spore's `SporeApp.exe` (the 2008 PC game) as readable C++ that compiles to exactly the same
machine code as the shipped game. A function counts when its compiled bytes are identical to the retail function's.
"Almost" counts as zero.

This guide is for people and for AI agents. You need your own copy of Spore (Steam) for the instruction
diffs that show what still differs; everything else runs from the repo.

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
2. Wine (any recent version) and `msitools` (`msiextract`), on macOS or Linux. On Windows, use WSL.
3. The compilers, from Microsoft's own installers (about 120 MB, nothing is installed, every file is hash-checked):
   `sh tools/ci/setup_toolchain.sh`
   This gives Visual C++ 2008 SP1 (cl 15.00.30729.01) for most of the game and the Visual C++ Toolkit 2003 1.01
   (cl 13.10.3077) for Havok and RenderWare code (rows with the `/vc71` flag).
4. Your own copy of Spore (Steam). Build the analysis image from it, so `check.py` can show an instruction diff
   (without it you only learn that bytes differ, not which):
   `.venv/bin/python tools/contrib/make_image.py "<Spore>/SporeBin/SporeApp.exe"` (must print `IMAGE OK`).
   The image is game code. It stays in `work/`, which git ignores. Never commit, upload or share it.

## The loop

1. **Pick a function.** `.venv/bin/python tools/contrib/task.py --list --max-size 256` lists functions that already
   have complete C++ source whose bytes still differ, **closest to a match first** (fewest differing bytes, then
   smallest), with the note left by whoever worked on it last. Hundreds are only 1 to 4 bytes off: start there.
   (`--by size` sorts smallest first instead.)
2. **Read its context.** `.venv/bin/python tools/contrib/task.py 0x00529690` prints its source file, status, compiler
   flags, retail size, includes and current source.
3. **Say you are on it.** Open a draft pull request early, titled with the address (`0x00529690: ...`), so others can
   see the function is taken.
4. **Write, build, compare.** Edit the source, then `.venv/bin/python tools/contrib/check.py 0x00529690`. It prints
   `MATCH`, the compiler errors, or an instruction diff against the original. Before inventing source shapes, look
   up the difference in `docs/codegen.md`: most residual diffs are a known lever (`__restrict`, a single-expression
   virtual call, `_ReadWriteBarrier()`, declaration order, ...).
5. **On MATCH**, `check.py` records it for you: it adds the function's `manifest.txt` line and removes its
   `nonmatching.txt` (or `partial.txt`) line. Mark the pull request ready and fill in the template, including the
   model or tool that wrote the code. (`--dry-run` prints those changes instead of making them.) Once a pull request
   is marked ready, do not add commits to it; put new work in a new pull request.
6. **Stuck?** After six to eight levers from `docs/codegen.md` without a match, stop and move on. Leave the function
   better than you found it: update its `nonmatching.txt` note with what you tried and
   what still differs, and open the pull request anyway. Notes are how the next person (or agent) starts ahead.

Keep experiments (test files, notes, listings) in `work/scratch/`: `work/` is ignored by git, so nothing there ends
up in your pull request by accident.

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
