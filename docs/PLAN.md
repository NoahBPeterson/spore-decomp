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
2. **Instruction-exact matching.** Compile per-function with the original toolchain
   (VS2008 SP1 `cl.exe` 15.00.30729, run under wine; flags still to be recovered from
   codegen: likely `/O2 /Oy- /GS /EHsc /MD`). Diff each function's bytes against the
   image with relocations masked, and track a `matched` percentage per subsystem.
3. **Portability.** Swap the Win32/D3D9/DirectInput/DirectSound/WinSock layers for
   platform abstractions (SDL3 + a GL/Vulkan or bgfx renderer) behind the same
   interfaces. The tests from stage 1 gate every change.

## Milestones

| # | Subsystem | Status |
|---|-----------|--------|
| 0 | Triage, SteamStub analysis image, Ghidra project | done (analysis running) |
| 1 | Resources: DBPF container, RefPack, name hash | portable impl + corpus tests pass (108,918 entries / 70,149 compressed). Next: map to exe functions |
| 1b | `.prop` property lists, locale `.locale` tables, config `.txt` | todo |
| 2 | Whole-binary map: library identification (EASTL, zlib, Lua, …), ModAPI type import, subsystem tagging | todo |
| 3 | Boot path: CRT → WinMain → App framework → config → window/device | todo |
| 4+ | Game layers (editors, simulator, UI/UTFWin, audio, RenderWare 4 graphics) | todo |

## Tooling

- `tools/ghidra/run.sh <script.py> args…` runs a PyGhidra script against the cached
  project (no re-analysis).
- `build/dbpf_tool list|extract …` inspects packages.
- `ctest --test-dir build` runs the unit tests (plus the corpus tests when `SPORE_DATA` is set).
