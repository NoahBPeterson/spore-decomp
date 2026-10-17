# Hybrid binary: running the game with our code in it

The hybrid is `SporeApp.exe` rebuilt from the decrypted analysis image with our compiled
functions spliced in. It is the first artifact of the project that can be *launched*, and the
test for everything that is not byte-exact: an "equivalent" function is one the game runs with.

Builder: `tools/hybrid/build.py`. Output: `work/hybrid/SporeApp.hybrid.exe` (+ `.hooks.json`).

## Running it (macOS, CrossOver)

The Steam copy lives in the CrossOver bottle `Steam`
(`~/Library/Application Support/CrossOver/Bottles/Steam/drive_c/Program Files (x86)/Steam/steamapps/common/Spore`).
The hybrid needs the Steam client running in that bottle (`steam_api.dll` → `steamclient.dll`;
the game calls `SteamAPI_Init` and `SteamApps()->BIsSubscribedApp`), the game's `Data/` next to
its `SporeBin/`, and a `steam_appid.txt` (`17390`) beside the exe because it is not launched by
Steam.

```sh
S="$HOME/Library/Application Support/CrossOver/Bottles/Steam/drive_c/Program Files (x86)/Steam/steamapps/common/Spore"
.venv/bin/python tools/hybrid/build.py --hook pass
cp work/hybrid/SporeApp.hybrid.exe "$S/SporeBin/SporeApp_hybrid.exe"; printf 17390 > "$S/SporeBin/steam_appid.txt"
cd "$S/SporeBin" && ~/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/bin/wine --bottle Steam \
    --cx-app 'C:\Program Files (x86)\Steam\steamapps\common\Spore\SporeBin\SporeApp_hybrid.exe'
```

Boots to the main galaxy menu (Apple M1 Pro, CrossOver 26.3, wined3d). Only these two extra files
are added to the Steam install; nothing in it is modified.

Wine notes:
- `--cx-app` wants a Windows path. Redirect wine's output to a file, never a pipe: the Windows
  services it starts inherit the pipe and the caller blocks until the session ends.
- Tracing is `CX_DEBUGMSG` (CrossOver), not `WINEDEBUG`. `+file` output is huge; to watch one API
  with no slowdown use the relay filter: `reg add 'HKCU\Software\Wine\Debug' /v RelayInclude /d
  'kernel32.GetFileAttributesW;user32.MessageBoxA'` and `CX_DEBUGMSG=-all,+relay` (delete the key
  afterwards). Matching log lines on an API name also matches the `RelayInclude` echo line; match
  `Call user32.MessageBoxA`.
- The game's own fatal errors are `MessageBoxA(... "Alert")` with a number: `[1004]` data dir,
  `[2000]` configuration script.

## Stage 1: runnable image

`tools/steamstub_analysis_image.py` leaves the entry point on the SteamStub stub so the image
cannot run. `build.py` moves it to the real OEP (`0x011E11A0`: a plain VC9 CRT start, no stolen
bytes), drops the Authenticode directory, clears `DYNAMIC_BASE` (our spliced code uses absolute
addresses with no base-relocation entries), refreshes the checksum, and applies `PATCHES`.
Every other byte of `.rdata/.data/.rsrc/.reloc/.bind` is identical to the Steam file.

### Runtime patch: registry string length (`0x6ab908`)

Without it the game dies on most launches with "Could not find the Data directory, we cannot run.
[1004]", and sometimes with the config-script error instead; a run slowed down by heavy tracing
usually survives. Cause, found with the relay trace above: `SP::cAppSystem::SetupDirectories`
(`0x7e7d00`) reads `HKLM\Software\Electronic Arts\SPORE\DataDir` through `FUN_006ab840`, which
builds the string with `wstring::assign(buf, cbData - 1)`: a byte count used as a character count,
so the string carries about as many uninitialised stack wchars as real ones after its terminator.
`SetupDirectories` then strips quotes with `find(L'"', 1)` + `assign(begin + 1, begin + pos)`;
when the garbage holds a quote the drive letter goes (`C:\...\Data` → `:\...\Data`), the path is
no longer absolute, and `EA::IO::FullPath` turns it into `//Program Files (x86)/.../Data/`.
Every registry string (Locale, PlayerDir, ...) gets the same garbage tail; Windows just happens to
leave benign bytes there. The patch makes the length `cbData / 2 - 1` through a 13-byte detour in
the `int3` padding after the function. Our decompiled source of `FUN_006ab840` must keep the bug
(byte-exact); the fix lives only in the hybrid.

## Stage 2: splicing

`--hook pass` (or a file of `<slice> <va>` lines) selects functions. For each, the equivalence
harness's `prepare()` compiles the slice (cached), finds our function and resolves every
relocation of the sections it needs to an original address (callees by name, hex name or `// 0x`
annotation, imports to IAT slots, CRT helpers, literals found in `.rdata`) or marks the section as
local. The local sections go into two new PE sections, `.hybx` (code + read-only data) and
`.hybd` (writable), relocated with the same arithmetic the emulator uses, and the first five
bytes of the original function become `jmp ours`. Functions with unresolved references, or
shorter than five bytes, are skipped and listed.

`--hook-manifest src/game/<dir>/<Stem>/nonmatching.txt ...` (migration gate, runbook section 4 step 4) hooks the
functions of migrated module TUs instead: the TU is `src/game/<dir>/<Stem>.cpp`, the originating slice comes from
`work/migrate/rewrite_*.json` `functions_moved`, flags are the slice's plus `/Isrc/game/include`, and everything after
`equiv.prepare` is the normal path. By default only rows whose latest strict verdict is PASS are hooked
(`--manifest-verdicts all` hooks every row). The 2026-10-12 pilot gate hooked all 72 buildable rows first and crashed
at once: `PFIndexModifiable` ctor 0x8db730 called the embedded pool constructor 0x925f30 with no `this`/arguments (jump to
eip=3 from the tail-jump in CreateIndex) and its destructor 0x8db7b0 called `DoFreeNodes` 0x8dac90 as a cdecl with ecx unset
(fault at 0x8dacb3); neither row had a PASS verdict, the harness does not compare callee arguments. With the PASS rule: 27
hooks, 2/2 boots ALIVE at 120 s, scene 21.0 and 9.5.

Byte-exact functions are not spliced (same bytes). `--verify-exact N` lays N of them out *at
their original address* through the same path and diffs them: 109 of 111 identical in the first
run; the two others are callees the resolver tied to a different address than the binary used
(the same choice the emulator ran with).

Known limits: a `jmp` hook breaks code that jumps into the first five bytes of a function from
elsewhere (shared tails; rare). Functions whose original has a custom register ABI can only be
hooked by a replacement with the same ABI, which our C++ cannot express; they stay original.

## Status (2026-10-12)

**Milestone:** `build.py --hook pass` hooks 1,561 PASS-verdict functions and the game boots to its
UI every time: 3/3 boots to 120 s and a 300 s session, no exception, the galaxy renders behind the
menu and the audio is clean (the 1,730-hook build of the morning booted too, but with a black 3D
scene and crackling audio: two more defects, below, found with coverage + bisects in the afternoon). Getting there took twelve
source-level defects found and fixed in "PASS" functions, plus three builder rules and one
resolver fix, all listed below. The remaining PASS functions are held back by the builder's
static rules (271 "void but the original returns in eax", 16 "clobbers the callee's eax", 13
atomicity, 7 unplaceable symbols) or parked in `known_bad.txt` (1); each is source work, not a
blocker.

History of the campaign:

- Stage 1 boots to the main menu every time (4/4 after the registry patch).
- Hooking every PASS function (2,036 of 2,046; 10 skipped for unplaceable `type_info` /
  deleting-destructor symbols) crashes nondeterministically: 4 crashes at 15–50 s and 1 clean
  100 s boot from the *same binary*, always an access violation at `0x6ada72` in `FUN_006ada20`
  (resource-cache resize/GC, a partial we do not hook) reading a null array pointer out of a heap
  object. Excluding the three slices around it changed nothing.
- A static audit found one systematic cause: PASS functions whose source does
  `++*(volatile long*)p` where the original does `lock xadd` (`0x0070eb30`, `0x006df280`,
  `0x00833400`). The single-threaded harness cannot see atomicity. `build.py` now refuses hooks
  whose locked-instruction count differs ("atomicity mismatch"); `docs/matching.md` tells agents
  to use `_Interlocked*` intrinsics. Excluding those alone still crashed 3/3.
- Second cause, found from the fault address rather than the bisect: every crash in the bisected
  branch was at `0x7f8e0020`, which is `machine.BUILTIN_ADDR["_fabs"]`: the resolver sends CRT
  functions the image lacks (`fabs`, `sqrt`, `sin`, `cos`) to emulator-only helper stubs, and
  `cFeatureVector::add` (`0x571790`) calls `fabs`. `build.py` now carries copies of those
  seven-byte x87 stubs in `.hybx` and redirects the relocations there. Lesson for the bisect: a
  crash whose *trigger* is random (here: the first call of `add`, anywhere from 15 s to past
  100 s) defeats "three clean boots"; the bisect ended with four candidates whose halves each
  booted clean. Read the fault address first; bisect second.

- Third and fourth causes (2026-10-11/12), both "our declaration says `void`, the original returns
  a value in eax": `uninitialized_copy` 0x99efa0 (eax unwritten on empty ranges, callers stored it
  as a vector end), `rbtree::find` 0xe5c780 (iterator through a hidden return pointer, eax = 0 on
  not-found), `ArenaSelf::initRange` 0x11e29c0 (returns `this`; LTCG callers kept using eax, the
  next hash lookup divided by a count read from garbage: `EXCEPTION_INT_DIVIDE_BY_ZERO` at
  0x11e2b4c). All three fixed in source and re-verified. `build.py` now also refuses hooks whose
  original writes eax before every `ret` in one of those shapes (125 of the PASS set).
- Fifth: the resolver sent `cPropertyList::GetProperty`'s `eastl::lower_bound` to another
  instantiation by qualified name (0x7c8160 instead of 0x612db0). Fixed in `resolve.py`: a
  name-only callee match must be among the original's own call targets.
- Detector lessons: CrossOver's crash dialog keeps the crashed process alive, so "still running"
  is not "alive"; `boottest.sh` now reads the trace for exceptions whatever the process state, kills
  stale `winedbg` dialogs first, and reports the game's CPU share (0% with a window = hung; a
  black screen with no crash was seen 2026-10-12 and is the next target after the current crash).
  Several bisect "good" verdicts before this fix were crash dialogs.
- Sixth and seventh (2026-10-12), both in `cTextureManager` (s007a8a50): the generator call used
  `((void**)gen)[1]`, the object's second field (an incrementing ID), instead of vtable slot 1, so
  the game called through the ID (`call edx` to 0x28f6xxxx, creeping upward run to run); and
  `RegisterGameTexture` passed `(a, b, 0, 0)` where the original forwards the generated key
  `(buf[0], buf[2], a, b)`. The harness normalises both pointer loads to the same class and compares
  no arguments for a callee-cleanup fake call. Both fixed in source. Also `FUN_00706ab0` (16-byte
  copy, s00706170), a fifth `void`-hides-eax instance (the original loads its arguments through
  `ebp`, which the static rule now also covers).
- Eighth: `Pool_AllocGlobal` 0x928ad0 (s00927be0) is `StackAllocator`'s allocation callback and
  returns the block in eax, which the original keeps from `LockedAlloc` while computing `*out` in
  edx; ours computed `*out` in eax. `AllocateNewBlock` wrote through the result (0x928be9). Fixed;
  `build.py` now also refuses a void wrapper whose original preserves its last callee's eax while
  ours writes eax afterwards.
- Ninth: two hooks with a different `ret N` from the original (0x56fe60, 0x75c9d0: `ret 4` vs
  `ret`), a calling-convention mismatch that unbalances the caller's stack; `build.py` now
  refuses those. Tenth: `MemoryStream::Clear`'s `SharedRelease` (s0093b9e0) called the shared
  block's second-base virtual with the vptr value as `this` instead of the base subobject at +4
  (crash at 0x93bd97). Fixed. Eleventh: the UTFWin crash at 0x959bd7 was
  `WindowMgr::PostAPC` (s009579f0) building its APC record with the tag at +0x10 instead of +8;
  the handler called through the record read garbage. Fixed (`APCData.lead[8]`).
- With those eleven fixed, 1,738 hooks run for 120 s without an exception at ~104% CPU, but the
  window is **black** (the rendering path is broken somewhere, no crash). `winshot.py` captures
  the game's own window through the window server (works when other windows cover it) and
  measures it; `boottest.sh` now appends "black screen" to ALIVE verdicts, and `hookbisect.py`
  treats that as bad in a plain bisect.
- Windowed mode (2026-10-12): `OptionFullScreen 0` / `OptionScreenSize 6` in the bottle's
  `users/crossover/AppData/Roaming/SPORE/Preferences/Preferences.prop` (plain text; the game rewrites
  it on exit). The window is 1168x758 and `winshot.py` captures it fine.
- Oracle lesson (2026-10-12): the first "galaxy renders" metric measured the centre of the window,
  and the registration dialog that pops up over a *black* scene in some runs read brighter than the
  real galaxy. A whole bisect ran on it and "found" a pair effect that did not exist, while the user
  reported "no universe" on every boot. Rule: before a bisect trusts a new detector, check its value
  on one run the user has judged by eye, in both the good and the bad state; and prefer a region no
  UI can cover (`scene` now reads the left-edge strip below the menu).
- No galaxy (2026-10-12 afternoon, windowed mode; the user noticed, no detector had): bisected in
  16 unattended boots over the 542 hooks that coverage showed executing on the boot path, with a
  window-edge brightness oracle. `cViewer::SetRaster` 0x7c4be0 (s007c4be0) declared the renderer
  virtual `v20(int* out, int a, int b)` where the original pushes `(handle[0], handle[1], &rect)`:
  the raster handle went in as the output pointer. Fixed in source; PASS before and after (fake-call
  arguments are not compared).
- Crackling audio (same day): no Wine-side signal (DirectSound underruns identical to the baseline),
  so the bisect ran with the user as the oracle (`hookbisect.py --ask`: the game stays up until the
  answer file appears). 15 steps narrowed it to `InterpRamp` 0x114e780 (s0114da70) + the release
  thunk 0x94ea90, with each alone judged clean on a short listen. The static finding is on
  InterpRamp: it writes **xmm3**, which the original never touches (xmm0-2, xmm7); an LTCG caller
  keeps a live value there. Semantically the two are identical instruction for instruction. New
  rule, `regfootprint.py` and `build.py` "register footprint": ours must not write any register the
  original does not (callee-saved pops excluded); it holds back 169 of the 1,730 hooks (50 ecx, 43
  edx, 38 xmm, 15 x87, ...). Those need codegen the C source cannot force; they stay original until
  module migration, or get a per-function asm shim.
  2026-10-16: `build.py --caller-deps` (default on since 10-17; `--no-caller-deps` restores the plain rule) keeps such a hook, and one refused for a dropped eax
  result, when `tools/difftest/callerdeps.py` finds that no caller of the original reads the register after
  the call (SAFE; DEPENDS and UNKNOWN keep the rule; x87 `st` is always UNKNOWN). Kept hooks are listed
  under `waived` in the `.hooks.json` sidecar, so a bisect can drop them as a group.
- 2026-10-17 re-check: every old PASS/WEAK/UNSUPPORTED verdict (4,335 rows) re-ran under the
  2026-10-12 harness at FPCW 0x007F (`rebaseline.py`; verdicts in
  `work/difftest/recheck_shard_20261016.json`, which `build.py` reads last). 418 now FAIL: 210
  register-only and SAFE by `callerdeps.py`, 119 DEPENDS, 37 UNKNOWN, 52 wrong value; the real ones
  are the DeepSeek fix batch `rck1` (`work/claude/rck1_plan.md`). The strict PASS set went from
  2,046 to 1,491. A first build crashed at 5 s in `DoInsertValue` 0x4e3e10: `rebaseline.py` had
  omitted `--require-all`, so a 74%-coverage PASS let in `PFIndexModifiable::GetFiles` 0x8dbcf0,
  which calls the vector method `__cdecl` without `this` on the vector-full branch the harness never
  ran (same bug in 0x8dbdb0; both in `rck1`). With the strict rule restored: `--hook pass` hooks
  1,321 and boots ALIVE 120 s (scene 9.0); with `--caller-deps`, 1,373 (52 waived), ALIVE 110 s
  (scene 21.4). Rule: a re-run of verdicts that feed `--hook pass` must use the flags of the run it
  replaces.
- Open (2026-10-12 evening, interactive sessions, not pursued; the plan is harness fixes then module migration, with the hybrid as a per-module gate): with h25, clicking into the game crashed at 320 s in `cModelWorld::Release` 0x750580 (original code) with `this` = its own vtable + 0x10 (0x140d7a0, a vptr-as-object bug upstream, same class as SharedRelease); a second session (cov2 = h25 + coverage) crashed at 175 s at 0x9fbeff. Found statically meanwhile and fixed: 0x753fc0 (s00753270) called vtable slot 0 without `this` (the row had called the ecx difference "register allocation"). Coverage of the interactive session: 46,743 functions, 573 hooks executed (`work/hybrid/cov2.json`).
- Black screen bisected to one hook: the rw::audio list pop-front leaf 0x1141200 (s01140b70)
  returned nothing where the original returns the popped node in eax; voice allocation got the
  list pointer and the audio core never started. Fixed. Along the way the bisect exposed
  `Sound::UpdatePropertiesFromPrimitives` 0xa1cf60 (crash at 0x645edd when alone), parked in
  `tools/hybrid/known_bad.txt` pending a frame-slot review.

Tools: `boottest.sh <exe> [secs] [tag]` boots one exe and prints `ALIVE (cpu P%)|CRASH|DIALOG|GONE`
with the first exception, plus `: black screen` / `: no scene` from `winshot.py` (`SCENE_MIN`,
default 6; `CXDBG` overrides the trace channels); `hookbisect.py [--fault <hexprefix>|wild]
[--cands F] [--always F] [--exclude @F] [--skip-full] [--ask]` bisects unattended (fault-targeted,
pair search with one half pinned) or, with `--ask`, with a human oracle: the game stays up until
`work/hybrid/<tag>.answer` holds `good` or `bad`; `regfootprint.py <exe> [--all] [va..]` reports
hooks that write registers the original does not; `covread.py` decodes coverage dumps (below).

## Coverage: which functions the game runs

`build.py --coverage [--hook pass]` plants a one-shot `int3` at the entry of every function in the
Ghidra table (90,467; hooked functions get theirs at the start of our copy), keeps the original
bytes in `.hybd`, makes `.text`/`.hybx` writable, and points the PE entry at `tools/hybrid/cov.c`:
a CRT-free TU (every API through the image's own IAT slots) that installs a vectored exception
handler — restore the byte, record `GetTickCount()` as the first-hit time, resume at the same
address — plus a thread that writes the table to `spore_cov.bin` in the game's cwd every 2 s.
`boottest.sh` moves that file to `work/hybrid/<tag>.cov.bin`; `covread.py <dump> [--sidecar
X.exe.cov.json] [--hooks X.exe.hooks.json] [--tiers] [--missing OUT] [--timeline] [--top N] [--json
OUT]` decodes it (`--tiers` imports `tools/status.py` for the byte-exact/equivalent/partial/none
sets). Cost: one exception per function, ~6 s of extra start-up; a `+seh` trace of such a run is
~115 MB.

First results (2026-10-12, boot to the galaxy menu, 90 s, idle):

| | functions | code |
|---|---:|---:|
| executed | 44,690 of 90,467 | |
| of which byte-exact | 36,086 | 1.68 MB |
| equivalent (not exact) | 2,645 | 1.07 MB |
| partial | 1,274 | 0.45 MB |
| no source | 3,835 | 0.90 MB |
| library | 850 | 0.18 MB |

So the boot path's source gap is 5,109 functions / 1.35 MB (`work/hybrid/cov0_missing.txt`, in
first-hit order: 4,723 game, 323 RenderWare, 63 Havok; the largest are `cCityGameTuning::Init`,
`WinTextEdit::OnRebuild`, `Audio::System::System`, `cPollinator::Init`). Static initialisers are
the burst at 0–7 s (~30,000 functions), the main menu is reached by ~17 s, the news feed at 44 s.
With the 1,730 PASS hooks in (`cov1`), **542 hooks (31%) executed**; 426 of the 731 hooked slices
had no hook run at all. "Boots with N hooks" therefore vouches for about a third of them; the
scenario suite (load a save, editors, stages) is what makes the rest count. The hooked and
unhooked runs executed the same code apart from 363/23 functions of network timing (XHTML/OpenSSL
news feed).
