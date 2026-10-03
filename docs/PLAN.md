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

## Milestones

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
