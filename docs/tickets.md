# Equivalence "UNSUPPORTED" backlog

Tracked work to make more decompiled functions *testable* by `tools/difftest/equiv.py`.
An UNSUPPORTED verdict means the checker **could not run the comparison** — it is not evidence the
code is wrong, just untested. Turning these into PASS/WEAK/FAIL is where the real correctness signal
comes from.

Counts are from all `work/difftest/*.json` result files (snapshot 2026-10-09).

| # | cause | count | status | fix idea |
|---|---|---:|---|---|
| 1 | unresolved references (our calls/globals have no `// 0x<VA>`) | 774 fns / 368 slices | **631 testable** (470 exact-name `29f93a0f` + 161 alignment `ccacc2d7`); 143 remain | Remaining 143: 6 structural (inline `rdtsc`/ctype), 14 wrong decls (thiscall declared as free `cdecl`, e.g. `WAssign`), ~105 alignment-failure/no-signal (source structurally unlike original), rest mechanism limits; 0 SEH (fixed in checker). Names are agent-invented, so more symbol data won't help. See `docs/resolve-leftover-results.md`; tool `tools/matching/resolve_leftover.py`; per-fn table `work/claude/resolve_leftover/report.md` |
| 2 | inputs discarded — `fault(read)` | 672 | todo | random inputs can't build a valid object graph (manager/object deref). Add a **seed corpus of real objects** / pointer-soup seeding for pointer-to-object args |
| 3 | our symbol not found | 669 | todo | checker can't find our emitted symbol: fix mangling/`thiscall` signature mismatches, force emission (avoid it being inlined away), accept a `sym=` hint in the marker |
| 4 | original reads `ecx`/`eax` at entry, our decl passes nothing | 259 | needs analysis | custom/LTCG **register ABI** or a guessed signature. Model the register argument, or fix the signature |
| 5 | inputs discarded — `fake-arity` | 169 | todo | generated function-pointer call has wrong arity; refine the fake-call generator |
| 6 | inputs discarded — `fault(write)` | 150 | todo | same as #2 for stores through pointers |
| 7 | harness/emulator faults (`UC_ERR_FETCH/READ/WRITE_UNMAPPED`) | 59 | partially real | the checker now reports these as **FAIL** ("ours faults where the original returned") — triage as real bugs; also harden the emulator's fault recovery |
| 8 | our code stores the address of its own copy (object/vtable/constant) | 96 | todo | map the symbol to the image address (vtable/RO-data), or mark it image-owned |
| 9 | compile failed | 71 | todo | slice does not compile under the checker's flags — fix the slice (often a flag/decl mismatch) |
| 10 | inputs discarded — `fault(pool-limit)` / other | ~40 | todo | raise pool size or add more slots for large-object functions |

Notes:
- The old `harness error: 'Comparer' object has no attribute 'last_kind'` (44, from `wave2_*`) is
  **fixed** — confirmed by re-running; those now produce real verdicts.
- `unsup1` earlier made ~530 functions testable by exactly this kind of annotation work — that is the
  proven playbook for #1 and #3.
- #1's tail (143) needs **source fixes, not symbol data**: the leftover names (`Callee::f`, `g_vtblA`,
  `CPlayerInventory::f5cae30`, `EAVec<I>::DoInsertValue`) are invented by the decompiler; only the original
  *function's* call/data alignment identifies them (that is how the 161 were freed). 14 are the same
  `thiscall`-declared-as-free-`cdecl` defect as bucket M; the 161's **38 FAILs + 13 "reads ecx"** are now
  concrete work items for the decompiling agents.
- Checker gained 4 small fixes (`ccacc2d7`): `__except_list`→0 (SEH chain head), `extern "C"` annotation ignores
  enclosing namespace, template ctor/dtor ident keying, and sibling-slice headers included by relative path are
  scanned for annotations (129 slices include a sibling header — re-baseline equiv verdicts if annotations there change).
- Effort order: **#1 (largely done — tail needs source fixes) → #3 → #2 → #4 → #8 → rest**. #1 and #3 are
  tooling/annotation and cheap; #2 and #6 need harness work (seed corpora); #4 is diagnosis.

# Project-wide tickets

Policy and release items that are not equivalence work. Numbered P1, P2, ... so they never collide with
the backlog table above.

| # | ticket | status | detail |
|---|---|---|---|
| P1 | **Ownership check and distribution policy** (added 2026-10-12) | standing rule | SteamStub (Valve's DRM wrapper on the Steam exe) cannot be re-applied by this project: only the publisher can wrap a build through the Steamworks backend. What *can* be preserved is the game's own ownership check, which lives in the game code, not the stub: `SteamAPI_Init` and `SteamApps()->BIsSubscribedApp` through `steam_api.dll` (the hybrid already needs a running Steam client that owns app 17390, see `docs/hybrid.md`). Rules: (1) every migrated module keeps the Steam ownership calls verbatim; no slice, module or portable build may stub, skip or short-circuit them, and a boot without a logged-in owning Steam account must still fail the same way the retail exe does; (2) the project never ships binaries, the decrypted analysis image, the hybrid exe, or game data; it ships source and tools, and a user produces every binary-derived artifact locally from their own Steam copy (`work/` stays git-ignored, `README.md`, `THIRD_PARTY.md`); (3) the portable build (stage 3) reads `Data/` from the user's own Steam install and keeps rule (1) through `steam_api.dll`. Check before any release: `rg -n "SteamAPI_Init|BIsSubscribedApp" src/ match/` must show the calls present and un-bypassed. |
