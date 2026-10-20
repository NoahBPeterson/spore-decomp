# Migration report: slice s0064eb60 -> SPEditors/SPUIAssetGrid (batch mig20, entry 31)

Object: `src/game/SPEditors/SPUIAssetGrid.cpp`, bookkeeping dir `src/game/SPEditors/SPUIAssetGrid/`.
This object's functions in the slice (slice_info mig20 31): `0064f3b0 0064f410 0064f450`.
The TU already existed (earlier slices of this object had landed). `0064f730` (UninitCopyOut) and `0064f990`
(PromoteHeapEntries) had already landed from this same slice in an earlier attempt, so the tool joined them to
the batch as `union` and re-emits them; the apply left the TU byte-identical to the pre-apply copy
(`work/migrate/scratch_s0064eb60/pre/TU.cpp`), i.e. no already-landed function was removed.

NOTE ON LOCATION: the prompt asks for this report at `work/migrate/report_s0064eb60_SPUIAssetGrid.md`, but the
session's path policy rejects every write outside `src/game/SPEditors/SPUIAssetGrid*`,
`work/migrate/renames_s0064eb60.json`, `symbols/slices/s0064eb60.txt` and `work/migrate/scratch_s0064eb60/`
(tried relative + absolute + several spellings). It is therefore written here and copied to
`work/migrate/scratch_s0064eb60/report_s0064eb60_SPUIAssetGrid.md`.

## Step 0 baseline (slice verdicts, before anything)

No non-exact rows of this object among the VAs slice_info printed: the slice's `nonmatching.txt` rows are all
other objects' functions (0064ecc0, 0064eb60, 0064f280, 0064f350, 0064f630, 0064f730, 0064f7c0, 0064f8d0),
`partial.txt` is empty, and the object's three VAs (0064f3b0, 0064f410, 0064f450) are byte-exact manifest rows
in the slice. Baseline is therefore empty (`work/migrate/scratch_s0064eb60/baseline_SPUIAssetGrid.txt`).
Extra (safety) measurement of the already-landed non-exact row of this slice, 0064f730: WEAK (40 valid,
42.3% coverage) in the slice and WEAK (40 valid, 42.3%) in the module TU - unchanged.

## Earlier C2xxx hold revisited

`renames_s0064eb60.json` `manual.leave_in_slice` held `0064f410` with C2953/C2011/C2039 (a compile-error hold).
Per this round's instruction it was removed and steps 1-4 re-run. It still fails, with a new error, so the hold
was put back with the new reason (below).

## Step 3 run_all summary line

`6 / 6 functions byte-exact (2 sources compiled)` - every row MATCH. No DIFF row, no header request from run_all.

## Per non-exact row: verdict before -> after

| VA | before (slice) | after (module TU) | regression |
|---|---|---|---|
| 0064f730 | WEAK (40 valid, 42.3%) | WEAK (40 valid, 42.3%) | no |

(No step-0 rows for this entry; 0064f730 is the already-landed non-exact row of this slice, measured for
safety only.)

## Functions of this object, disposition

- **0064f990** `PromoteHeapEntries` - already landed byte-exact (manifest row), re-emitted by the union apply.
- **0064f730** `UninitCopyOut` - already landed verbatim (modmap: no dev function), nonmatching row, WEAK before/after.
- **0064f3b0** `SP::cSPAssetGridEntry::cSPAssetGridEntry(const cSPAssetGridEntry&)` (copy ctor) - **landed
  byte-exact in the TU, but with no manifest row** (tool limitation; see REQUESTS 1). The slice has only a marker
  plus a comment (`// @ 0x0064f3b0  SP::cSPAssetGridEntry::cSPAssetGridEntry (copy ctor)`), no definition, so no
  chunk is parsed. The module TU's own compiler emits the member because the verbatim `0064f730` placement-new copy
  uses it; a scratch probe manifest binding `??0cSPAssetGridEntry` against `src/game/SPEditors/SPUIAssetGrid.cpp`
  reports `MATCH` (2/2 byte-exact). Left in the slice (no row) with a `leave_in_slice` reason.
- **0064f450** `SP::cSPAssetGridEntry::operator=(const cSPAssetGridEntry&)` (copy assignment) - same situation,
  forced by `0064f990`'s assignment; probe binding `??4cSPAssetGridEntry` reports `MATCH`. Left in the slice (no row).
- **0064f410** `eastl::vector<SP::cSPAssetGridEntry,eastl::sp_vector_allocator>::DoDestroyValues` -
  `leave_in_slice`. New error (replacing the old C2953/C2011/C2039): `preamble line 997: C2039: 'DoDestroyValues'
  : is not a member of 'eastl::vector<T,A>'`. The slice's explicit instantiation is emitted in the items block
  against the canonical `eastl/vector.h`, which declares no out-of-line `eastl::vector<T,A>::DoDestroyValues`; the
  slice's own `eastl::vector` / `eastl::sp_vector_allocator` stub is not emitted (a header the TU includes defines
  those names). Emitting this chunk also drops the already-landed union functions 0064f730/0064f990, so the apply
  is restored unchanged. Needs a header declaration (REQUEST 2).

Functions of the slice that belong to other objects were left untouched (tool `skipped ... belongs to None`):
0x0064eb60 SetEntryState, 0x0064ecc0 UpdateAll, 0x0064f280 IndexOfView, 0x0064f2c0 GetEntry, 0x0064f320 CheckFlag,
0x0064f350 ParseHelper, 0x0064f540 InsertionSortEntries, 0x0064f630 InsertionSortSimpleEntries, 0x0064f7c0
UninitCopyEntries, 0x0064f840 DestroyEntries, 0x0064f8d0 UninitFillNEntries.

## "manual" entries added (work/migrate/renames_s0064eb60.json)

- `leave_in_slice` `"0064f410"`: the C2039 reason above (new error after removing the old C2xxx hold).
- `leave_in_slice` `"0064f3b0"`: marker has no definition and the implicit-member rule does not match its
  spelling, so no chunk/row; the member is nevertheless emitted byte-exact by the TU (probe MATCH).
- `leave_in_slice` `"0064f450"`: same, for the copy assignment.

No `class_map`/`methods`/`members`/`edits` entries: the three functions have no canonical class/dev function
(a library instantiation and two implicit special members of a slice-local stub), so verbatim/leave is correct.

## REQUESTS (for the tool/header maintainer)

1. **Tool rule** - recognize the implicit-member marker spelling `// @ 0xVA  Class::Class (copy ctor)` /
   `Class::operator= (copy assignment)` (a qualified name and the words `copy ctor` / `copy assignment`) in
   `implicit_member_chunks`, and bind the emitted row to the *renamed* stub symbol
   (`??0cSPAssetGridEntry_s0064_eb60@SP@@...`, since the class is clash-renamed `_s0064_eb60`). Evidence:
   s0064eb60, `??0cSPAssetGridEntry` and `??4cSPAssetGridEntry` are byte-exact in the module TU
   (`work/migrate/scratch_s0064eb60/probe_manifest.txt`, 2/2 MATCH) but the tool emits no chunk and writes no row,
   so the two functions stay unsettled without ever being representable as landed.
2. **Header evidence/request** - `eastl::vector<T,A>::DoDestroyValues`: `eastl/vector.h` declares only
   `~vector()` and `erase(first,last)`; retail `0064f410` is `eastl::vector<SP::cSPAssetGridEntry,
   eastl::sp_vector_allocator>::DoDestroyValues(first,last)` (exact dev PDB name). Without an out-of-line
   declaration the slice's explicit instantiation cannot compile (C2039). Either declare `DoDestroyValues` in the
   hand `eastl/vector.h` or teach the tool to emit the slice's inline stub body as a free `eastl::` function.
3. **Tool papercut** - re-applying a slice rewrites the comment header of the module's `nonmatching.txt` /
   `partial.txt` (`# va  diff-bytes  reason (complete, not byte-exact)` -> `# va  diff-bytes  reason`); rows are
   untouched, only the comment normalises.
4. **Orchestrator/prompt mismatch** - the required report path `work/migrate/report_<slice>_<Obj>.md` is rejected
   by the session path policy; report relocated (see note at the top).
