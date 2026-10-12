# Spore decompilation — plan

Target: `SporeBin/SporeApp.exe` (Steam, PE timestamp 2024-09-30, PDB `SporeEP1_RL`).
32-bit x86, MSVC 2008 (linker 9.0, `msvcr90.dll`), ImageBase 0x400000, `.text` 16.5 MB.

## Ground rules

- Your own copy, local only. `work/` holds everything derived from the binary (the
  decrypted analysis image, the Ghidra project, dumps) and is git-ignored. Never publish it.
- `tools/steamstub_analysis_image.py` decrypts `.text` for analysis. It deliberately
  leaves the entry point on the DRM stub, so the output image **cannot run**. The real
  OEP (VA 0x011E11A0) goes into `work/SporeApp.analysis.json`.
- Game data is never copied into the repo. Corpus tests read it in place via `SPORE_DATA`.

## Stages

1. **Behavioral source.** Reimplement the program subsystem by subsystem in portable
   C++17. Each reimplemented function records the original address it corresponds to
   (`// @ 0x00XXXXXX`). Validate with:
   - corpus tests against the shipped data (does every file parse the same way?), and
   - differential tests: run the original function and ours on the same inputs
     (harness: load the analysis image under wine/x86 emulation, call by address).
2. **Instruction-exact matching.** Compile per-function with the original toolchain,
   run under wine. SporeApp.exe's manifest binds `Microsoft.VC90.CRT` **9.0.21022.8**,
   the CRT Spore ships, so the build used **VS2008 RTM (cl 15.00.21022.08)**, not SP1.
   SP1's cl 15.00.30729 (in the free Windows SDK 7.0) is a near fallback but may differ
   on some functions. Flags still need recovering from codegen: likely `/O2 /GS /EHsc /MD`
   for most modules, with some modules unoptimized.
   The VC++ 2008 redistributable (9.0.30729.6161) provides only runtime DLLs, no compiler.
   It can still serve as runtime for wine-run test binaries. Diff each function's bytes against the
   image with relocations masked, and track a `matched` percentage per subsystem.
3. **Portability.** Swap the Win32/D3D9/DirectInput/DirectSound/WinSock layers for
   platform abstractions (SDL3 + a GL/Vulkan or bgfx renderer) behind the same
   interfaces. The tests from stage 1 gate every change.

### Course change (2026-10-11): hybrid binary, then modules

Per-function matching (stage 2) reached 61% byte-exact by count but 20% by size, and its output
is 2,558 isolated slices with private stub types and `FUN_xxxxxxxx` prototypes: proofs, not a
program. Merging them later is a rewrite that grows with every slice. So:

- **Global matching waves stop.** Byte-exactness stays the per-function gate (`run_all.py`) but is
  pursued inside the module being migrated, not binary-wide. LTCG custom-ABI functions and giant
  /O2 bodies are accepted as equivalent.
- **Hybrid binary** (`docs/hybrid.md`, `tools/hybrid/`): the decrypted original with our compiled
  functions spliced in, run under CrossOver. It boots to the main menu. Equivalent functions are
  hooked in with a `jmp`; "the game runs with it" is the acceptance test for non-byte-exact code,
  replacing the emulator's synthetic inputs.
- **Module migration**: a real tree (`src/<module>/`, shared headers) built one module at a time,
  with file boundaries from the 2008 dev PDB (`tools/pdb_modules.py`) and class layouts from
  ModAPI (`work/ext/Spore-ModAPI`). Each migrated module must keep its byte-exact functions exact
  and boot in the hybrid. Pilot: the resource/DBPF module (milestone 1 already has real source).

## Roadmap to completion (2026-10-12)

Where we stand (from `docs/STATUS.md`, the strict-equivalence shards and `tools/matching/layout_census.py`):

| | functions | by size |
|---|---:|---:|
| byte-exact | 53,790 | 20.0% |
| equivalent, not exact (9,563 strict verdicts: 2,052 PASS, 2,819 WEAK, 1,867 FAIL, 2,825 UNSUPPORTED) | 9,322 | 33.5% |
| partial source | 4,891 | 13.0% |
| no source | 20,290 | 33.4% |
| hooked into the hybrid (PASS tier, boots) | 1,730 | |

All of that source is 2,558 isolated slices (978k lines); 2,306 struct/class names have conflicting
member layouts between slices. The dev PDB gives 2,647 object files to migrate into, by directory
(dev-build code bytes): SPGonzago 5.6 MB, SPEngine 2.5 MB, UTFSpore 2.0 MB, SPEditors 1.3 MB,
SPBake 1.1 MB, SPTerrain 0.66 MB, SPAudio 0.55 MB, SPCreatureAnim 0.52 MB, Swarm 0.51 MB,
SPUI 0.35 MB, Havok ~1.1 MB, RenderWare ~0.3 MB.

"Done" means: `SporeApp.exe` linked entirely from `src/` by the original toolchain, running the game
under Wine indistinguishably from the Steam binary (stage 3, portability, starts after that). Two gaps
separate us from it, and they are independent: **coverage** (46% of the code by size has no complete
source) and **integration** (the source we have is not one program). The hybrid is the vehicle for
both: it accepts code at function granularity today and at object-file granularity tomorrow (the
splicer consumes `.obj` files; a migrated module's objects plug in unchanged), so every step below is
gated by "the game still runs".

### Phase A — measure and harden the hybrid (now)

1. **Coverage build** (done 2026-10-12, `docs/hybrid.md` "Coverage"; boot path = 44,690 functions,
   source gap 5,109 / 1.35 MB; only 31% of the PASS hooks execute on boot). `build.py --coverage` plants a one-shot `int3` at every game function entry
   (original bytes kept in a table in `.hybd`; hooked functions get theirs at the start of our copy),
   with the PE entry point redirected to a small TU of ours that installs a vectored exception handler
   (restore byte, record `GetTickCount()` as first-hit time, resume) and a thread that flushes the
   table to a file every few seconds. One run yields the set of functions the game executes on the
   boot path, in the menu, and in each scripted scenario (load save, each editor, each stage), with
   first-hit order. This is the single most useful missing fact: it (a) tells which of our hooks were
   actually *exercised* ("boots with 1,730 hooks" says nothing about a hook that never ran),
   (b) orders the 25,000 missing functions by when the game needs them, and (c) gives per-module
   execution counts for choosing the migration order. Reported in STATUS as "hooked and executed".
2. **Harness fixes** from Papercuts, in this order: compare eax after return whatever the declared
   return type; compare fake-call arguments and `this`; check `ret N` against our object; compare
   pointer-argument contents. Re-run the strict shards; the 271 + 16 + 2 held-back PASS hooks become
   FAIL rows with a precise reason, and the WEAK tier becomes trustworthy enough to hook.
3. **Hook tiers.** WEAK (2,819) next, then FAIL per subsystem as its rows are fixed, each tier gated
   by `boottest` ×3 plus the scripted scenarios from step 1 (menu → load save → one editor → one
   stage), with `hookbisect.py` for regressions. Fixes go back into the slices through the usual gates
   (`run_all`, `equiv`), so byte-exactness never regresses.
4. **Scripted scenarios.** `boottest.sh` grows a scenario file (key/mouse input via `xdotool`-style
   automation in the Wine window, or the game's own command line/cheat console) so "runs" means more
   than the galaxy menu. Each scenario is a coverage run and a regression test.

### Phase B — the migration pipeline, then a pilot

Design, measurements and pilot inventory: `docs/migration.md` (2026-10-12).

5. **Canonical types.** One header per class under `src/<module>/`, seeded from ModAPI
   (`work/ext/Spore-ModAPI`), the dev-PDB TPI (`work/devbuild/types.json`) and the census; the
   2,306 conflicting names are the work list, resolved per module (a slice's partial view either
   matches the canonical layout or the slice is wrong, and `run_all` says which).
6. **Slice-to-module rewriter** (`tools/migrate/`): takes a PDB object file, collects the slices
   holding its functions, replaces their private stubs with the canonical headers and `FUN_`
   prototypes with real declarations, emits `src/<module>/<file>.cpp`, then re-runs `run_all` on the
   module's manifest (byte-exact must stay byte-exact) and `equiv` on the rest, and the hybrid boots
   with the module's `.obj` spliced in place of the slice objects. Globals and vtables stay at their
   original addresses (resolved by the splicer) until Phase D.
7. **Pilot: UTFSpore/Resource + Properties** (milestones 1 and 1b: DBPF, RefPack, `.prop`), because
   `src/resource` already exists with tests, ModAPI covers the types, and everything above it depends
   on it. Success = the module directory builds as one library, its manifest is byte-exact, and the
   hybrid boots with the whole module spliced.
8. **Run the pipeline bottom-up:** rest of UTFSpore (IO, App, Messaging, UTFWin, Localization) →
   SPEngine (graphics, models, materials) → SPAudio, Swarm, SPTerrain, SPCreatureAnim → SPUI,
   SPEditors, SPBake → SPGonzago (the game proper, 40% of the code) → Havok 3.1 and RenderWare last
   (least source, foreign toolchain; they stay original bytes in the hybrid longest).

### Phase C — close the coverage gap, in module order

9. The worker waves (DeepSeek, `work/opencode`) switch from address windows to **module work
   lists**: for the module being migrated, (a) the no-source and partial functions ordered by
   coverage first-hit, (b) the FAIL/UNSUPPORTED rows, (c) the mechanical fixes (`void` → real return
   type, atomics). Byte-exact remains the per-function gate; equivalence plus "runs in the hybrid" is
   accepted for LTCG custom-ABI and giant /O2 bodies, as decided on 2026-10-11.
10. Data: the 16,626 shape-only static initializers become real `T g = ...;` definitions as their
    module migrates; vtables, RTTI and string literals are emitted from the canonical headers. This
    is what Phase D needs.

### Phase D — inversion and full link

11. When the remaining original code is small (target: Havok/RW plus stragglers), flip the hybrid:
    link our tree into an exe at ImageBase 0x400000 with original sections laid out at their original
    RVAs for whatever is still not ours, then shrink that blob to zero. Original data stays at
    original addresses until this step, so the blob's absolute references never move; our linker
    decides the layout only once nothing original remains.
12. Full link, no blob: `SporeApp.exe` from `src/` only, byte-exact where we claim it, identical
    behaviour under Wine on the scenario suite. Then stage 3.

### What is highest leverage right now

The coverage build (A1). Everything after it — which hook tier to trust, which missing functions to
write first, which module to migrate first, whether a passing boot tested anything — is a guess
until we know which functions the game runs. It is one or two days of work with tools we already
have (the splicer places code and data in the image; the MSVC toolchain compiles the handler TU), and
it turns every later boot into a measurement. Second is A2 (harness fixes): the hidden-eax class
alone produced seven of the twelve defects found this week, and the harness could have caught all
seven. Third is the migration pilot (B5–B7), which proves the integration path on a module that
already has real source; the census is its issue list and must not be allowed to grow further
(agents writing new slices follow canonical headers once they exist).

### Original milestones (superseded by the roadmap above; kept for reference)

| # | Subsystem | Status |
|---|-----------|--------|
| 0 | Triage, SteamStub analysis image, Ghidra project (96,420 functions after discovery pass) | done |
| 1 | Resources: DBPF container, RefPack, name hash | DBPF read path + RefPack reimplemented from decompile (addresses annotated), unit + corpus tests pass. Differential tests vs the original code pass (hash, header verify, RefPack on 1,000 corpus entries). Next: .prop |
| 1b | `.prop` property lists, locale `.locale` tables, config `.txt` | todo |
| 2 | Whole-binary map: library identification (EASTL, zlib, Lua, …), ModAPI type import, subsystem tagging | todo |
| 3 | Boot path: CRT → WinMain → App framework → config → window/device | todo |
| 4+ | Game layers (editors, simulator, UI/UTFWin, audio, RenderWare 4 graphics) | todo |

## Tooling

- `tools/ghidra/run.sh <script.py> args…` runs a PyGhidra script against the cached
  project (no re-analysis).
- `build/dbpf_tool list|extract …` inspects packages.
- `ctest --test-dir build` runs the unit tests (plus the corpus tests when `SPORE_DATA` is set).
