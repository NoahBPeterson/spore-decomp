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

Byte-exact functions are not spliced (same bytes). `--verify-exact N` lays N of them out *at
their original address* through the same path and diffs them: 109 of 111 identical in the first
run; the two others are callees the resolver tied to a different address than the binary used
(the same choice the emulator ran with).

Known limits: a `jmp` hook breaks code that jumps into the first five bytes of a function from
elsewhere (shared tails; rare). Functions whose original has a custom register ABI can only be
hooked by a replacement with the same ABI, which our C++ cannot express; they stay original.

## Status (2026-10-12)

**Milestone:** `build.py --hook pass` hooks 1,730 PASS-verdict functions (357 KB of our code) and
the game boots to its UI every time: 3/3 boots to 120 s and a 300 s session, no exception, a
rendered window (window brightness and CPU share equal to the no-hook baseline). Getting there took twelve
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
- Black screen bisected to one hook: the rw::audio list pop-front leaf 0x1141200 (s01140b70)
  returned nothing where the original returns the popped node in eax; voice allocation got the
  list pointer and the audio core never started. Fixed. Along the way the bisect exposed
  `Sound::UpdatePropertiesFromPrimitives` 0xa1cf60 (crash at 0x645edd when alone), parked in
  `tools/hybrid/known_bad.txt` pending a frame-slot review.

Tools: `boottest.sh <exe> [secs] [tag]` boots one exe and prints `ALIVE (cpu P%)|CRASH|DIALOG|GONE`
with the first exception; `hookbisect.py [--fault <hexprefix>|wild] [--cands F] [--always F]
[--exclude @F]` bisects unattended (fault-targeted, pair search with one half pinned).
