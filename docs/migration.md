# Module migration: from slices to a source tree

Design (2026-10-12) for Phase B of `docs/PLAN.md` "Roadmap to completion". Status: step 1
(`modmap.py`) and step 2 (`headers.py`) implemented and measured on the pilot, see "modmap: what
was built" and "headers: what was built"; steps 3–4 (`rewrite.py`, the 33 pilot slices, `gate.py`)
are specified step by step in **`docs/migration-runbook.md`** for Sonnet agents and run by the saved
workflow `.claude/workflows/migration-pilot.js`.

## What we are turning into what

**Input.** 2,558 slices under `match/slices/<id>/`: one TU each, private stub structs, `FUN_`
prototypes, `// @ 0x` markers, three bookkeeping files (manifest = byte-exact, nonmatching =
equivalent, partial). 978k lines. `tools/matching/layout_census.py` finds 10,500 struct names with a
data-member body, 2,787 declared in more than one slice, **2,306 with conflicting bodies**.

**Output.** `src/game/<module>/`: one directory per original object file, real class names, one
canonical header per class, functions in retail address order, the same three bookkeeping files
per module. Every function keeps its `// @ 0x` marker. Byte-exact functions stay byte-exact
(`run_all` on the module manifest), equivalent ones keep or improve their strict verdict, and the
hybrid boots with the module's objects spliced in place of the slice objects.

The migrated code is original-faithful C++03 for the VC9 toolchain, like the slices. It is not the
portable layer: `src/resource/` (milestone 1, C++17) stays what it is (possibly renamed
`src/portable/` once `src/game/` exists); stage 3 (portability) comes after the tree is complete.
Decided with the user 2026-10-12.

## Data we have, measured

| source | what | numbers |
|---|---|---|
| `work/devbuild/symbols.json` | 2008 dev build: every function with name, size, **object file** | 145,306 functions |
| `work/devbuild/modules.json` | the 2,647 object files and their section contributions | 2,647 `.obj` |
| `work/devbuild/types.json` | every struct/class/enum of the dev build: members with offsets, sizes, bases, vfptr | 18,464 structs |
| `symbols/pdb_names.json` | retail VA → dev name (xmatch, `docs/xmatch.md`) | 10,007 named |
| anchors = named retail functions whose name is in exactly one dev object | module membership known | 9,444 → 1,019 modules |
| `symbols/pdb_vtables.json` | retail vtable VA → class | |
| `work/claude/layouts/census.json` | per struct name: each distinct body and the slices using it | 10,500 names |
| `work/hybrid/cov0.json`, `cov2.json` | functions executed on the boot path / an interactive session | 44,690 / 46,743 |

Retail `.text` is module-major: walking the anchors by address, 81.6% of consecutive pairs are in
the same object file and most objects form one contiguous run (median 1 run; the worst, an editor
base class, 16). Interpolating between two anchors of the same module assigns a module to 24,690
retail functions (27%) directly; the rest sit in gaps between runs of different modules or inside
unnamed stretches. That gap is the first problem the pipeline has to solve.

## Pipeline

Four tools under `tools/migrate/`, each with a JSON artifact under `work/migrate/` and a metric
printed at the end, so every step can be judged before the next one runs.

### 1. `modmap.py` — retail function → object file

Builds `work/migrate/modmap.json`: `{va: {"module": ..., "how": ..., "confidence": ...}}` plus the
runs, the gaps between them, per-module totals, conflicts and the metric.

Signals, applied in order, each only to functions still unassigned (design list; the implemented
rules and their measurements are in "modmap: what was built" below):
1. **anchor**: named, unique dev object.
2. **interpolation**: between two consecutive anchors of the same module, in dev order.
3. **class membership** (`vtable`): the function sits in the vtable of a class whose anchored
   methods are all in one module.
4. **call graph**: every assigned direct caller and callee agrees on one module, the module's
   code is adjacent, and the function is not a shared helper.
5. **gap split**: inside a gap between run A and run B, align the retail function sizes with the
   dev object's remaining functions (A's tail, B's head).
6. **instantiation rule**: template instantiations and compiler-generated members go with the
   module that owns the class in their name.

Leftovers go to `src/game/_unassigned/<address-range>/` with their slice bookkeeping, so nothing
is lost; the metric is the assigned share by count and by size, the hold-out precision, and the
number of conflicts. Target before the pilot was >70% by size with <1% conflicts; measured 48%
by size at ~96.5% precision (below).

#### modmap: what was built (2026-10-12)

`tools/migrate/modmap.py` holds the data (`Ctx`), the first two signals and the metric; the other
signals are plug-in files `tools/migrate/sig_<name>.py` with `apply(ctx)`, run in the order
`anchor, interp, vtable, callgraph, gapsplit, inst`. Every signal assigns through `ctx.set()`,
which keeps the higher-confidence module and records the disagreement under `conflicts`.

**Precision is measured by hold-out** (as in xmatch): `--holdout 0.2 --seed N` hides a fifth of
the unique anchors, runs the signals, and scores where the hidden anchors landed. About 3% of
the anchors are themselves wrong names (mostly xmatch's callee-single method), so ~97% is the
ceiling for any signal. Three seeds: recall 78–81%, precision 96.1–96.7%.

| signal (tier) | rule | functions | KB | hold-out precision |
|---|---|---:|---:|---|
| anchor | unique dev object via `pdb_names.json` → `symbols.json` | 9,234 | 3,426 | truth set |
| anchor-comdat (0.5) | name present in >1 dev object (COMDAT; retail may keep another copy) | 549 | 227 | |
| anchor-sandwiched (0.6) | lone anchor of X between two anchors of M: demoted, M spans it | 44 | 19 | |
| interp (0.9) | between consecutive same-module anchors whose dev counterparts ascend | 14,002 | 3,079 | 96.6–97.2% |
| interp-wide (0.6) | same, but retail gap count > 2× dev count + 4 | 843 | 211 | 81–88% |
| vtable (0.8) | slot of a vtable whose class is owned by one module (≥2 anchored methods, ≥90% agree) | 964 | 178 | 97–99% |
| vtable-refvote / vote tiers (0.4–0.5) | other slots of the same vtable agree | 3,429 | 325 | 87–100%, small samples |
| callgraph (0.8) | ≥2 assigned neighbours agree, module adjacent (≤5 functions), not shared | 291 | 58 | 91–100% (pooled 95.5%) |
| callgraph-weak (0.5) | one neighbour, or adjacency ≤10 | 646 | 135 | 89–92% |
| gapsplit-same (0.8) | gap between two anchors of one module that interp refused (out of dev order), count fits | 611 | 219 | 94–97% |
| gapsplit-tail / head (0.8) | ≥5 retail sizes align with the dev object's remaining functions | 229 | 59 | 97–100%, small samples |
| gapsplit-short / same-wide (0.5) | 3–4 aligned, or count up to 2× | 266 | 66 | 90–100% |
| inst (0.7) | instantiation follows its class's owner | 0 | 0 | never fires: the low-confidence named functions are `$E` initialisers or have no owner |
| **total** | | **31,295 = 34.6%** | **8,041 = 48.2%** | 359 conflicts |

Facts learned on the way, each of which changed a rule:
- Dev order is **ascending in retail too**, strictly: no chain of three or more same-module anchor
  pairs descends throughout. But 266 of the 781 multi-anchor chains have at least one pair out
  of order (functions moved within a file in 16 years of edits, or misnamed anchors), so
  interpolation requires ascending dev order per pair and the 432 out-of-order pairs are left to
  `gapsplit-same`, which checks the count against the dev object before spanning them.
- 210 unique-by-name anchors sit alone inside another module's run, more than half cross-
  directory: inline members and instantiations the dev linker happened to keep in one object.
  They are demoted and spanned.
- Retail keeps only ~15–20% as many functions per object as the dev build (inline accessors and
  template instances were emitted as functions by VC7.1), so a raw count comparison cannot bound
  a gap; `gapsplit` first filters the dev side to plausible survivors (size ≥ 32, no template
  name, unique to the module, not already claimed).
- 71% of the unassigned functions have **no direct caller** (virtual methods), which caps the call
  graph signal; the vtable signal is the one that reaches them. Retail has no RTTI; vtables come
  from `work/xmatch/tables.json` (4,731) plus a cached scan of `.text` for the constructors that
  store each vtable address (`work/migrate/vtable_cache.json`).
- A call-graph vote for a module whose code is not adjacent is right only 9% of the time: the
  locality test is the decisive filter, not the vote.

What is left (59,172 functions, 8.65 MB, 2,552 gaps): the ten largest gaps hold 2.1 MB and lie
between a run and an anchorless region (e.g. 0x10cd3e0–0x1123580, 805 functions, between an
editor base class and the resource factory; 0x13b64c0–0x13cbf20, 2,867 functions after the
RenderWare null driver: library code). They need a new anchor source rather than more
propagation: pairing retail vtables with dev vtables by class name and reading the module of each
dev slot (resolved through the incremental-link thunks) would handle inherited slots exactly and
reach classes with 0–1 anchors; address-order interpolation over `.rdata` vtables would add ~260
vtables; indirect-call edges would raise the call graph's reach. None of this blocks the pilot.

### 2. `headers.py` — canonical headers from the dev PDB

For each class a module needs (its own classes plus every type its functions touch), emit
`src/game/<module>/<Class>.h` (nested/namespaced names flattened to a path) from `types.json`:
members at their exact offsets (explicit padding where the PDB has holes), bases, `vfptr`,
`// 0x` vtable address and slot-ordered virtual declarations from `pdb_vtables.json` +
`symbols/vtable_names.txt`, method declarations for every function assigned to the class (with
`// 0x` addresses so the resolver can bind them), `static_assert`-equivalent size checks
(`sizeof` checks via a template trick; VC9 has no `static_assert`).

Dev ≠ retail. The 2008 PDB is not the shipped build: `SP::cString` is 0x14 in retail vs 0x1c dev.
Resolution order for a layout: (1) `tools/migrate/layout_overrides.json` (hand-confirmed retail
deltas, starting with the ones in Papercuts); (2) census bodies that are *byte-exact in retail*:
if a slice compiled byte-exact with a given view of the struct, that view is retail-correct for
the members it names; (3) the dev PDB. Where (2) and (3) disagree, the tool prints the conflict
and the retail evidence wins, with a note in the header. ModAPI (`work/ext/Spore-ModAPI`) is read
only to cross-check names; it is not a layout source ([memory: layouts from dev PDB]).

Globals: `src/game/<module>/globals.h` with `extern` declarations and `// 0x` addresses (the
difftest resolver and the hybrid splicer already bind by address). Vtables and RTTI stay original
until Phase D; headers describe them, nothing emits them.

Metric: classes emitted, classes with a dev/retail conflict, classes with no PDB type at all (slice
stub only — those are kept as `*_slice.h` with a TODO).

#### headers: what was built (2026-10-12)

`tools/migrate/headers.py --module SUBSTR` writes `work/migrate/headers/<module>/<Ns>/<Class>.h`
for every class that has a method in the module (template instantiations and `eastl::`/`std::`
classes are skipped: they belong to shared headers). Inputs: `work/devbuild/types.json`
(layouts), `symbols.json` publics demangled with `llvm-undname` (full method signatures),
`work/xmatch/tables.json` + `symbols/pdb_vtables.json` (retail/dev vtables), `modmap.json`
(retail addresses), `work/migrate/retail_leaf_sizes.json` (retail sizes of library leaf types,
measured by `tools/migrate/leafsizes.py`, Sonnet agent, from byte-exact slices and disassembly),
`work/migrate/sliceviews.json` (every slice struct view with computed offsets and its byte-exact
users, `tools/migrate/sliceviews.py`, Sonnet agent) and `tools/migrate/layout_overrides.json`
(hand-confirmed structural deltas).

How a header is produced:
1. **Re-layout.** The dev members are laid out again with retail sizes for leaf types, natural
   alignment bounded by what the dev offset proves (EA's headers pack 8-byte members at 4:
   `EA::Variant` is 0x14 with an `__int64` inside; `EAMutexData` keeps 8, which the dev size
   shows), the dev build's own padding holes, empty-base optimisation, unions by overlapping dev
   offsets, bases in address order (the PDB lists them in declaration order; MSVC puts the
   polymorphic ones first). `--selftest` re-lays all 18,464 dev structs with dev sizes: 18,446
   reproduce the PDB exactly; the 18 that do not are packed SDK structs, unnamed unions and
   `std::iostream`'s virtual bases.
2. **Leaf sizes.** What actually changed between 2008 and 2024, measured: `EASTLCoreAllocator`
   dropped its name pointer (0xc → 8, so hash tables and trees using it *shrink* by 4); every
   `eastl::VectorBase` has an 8-byte allocator slot (vectors 0x10 → 0x14, 12 bytes for
   `fixed_vector` with overflow); strings, lists, hash tables and trees on `eastl::allocator` are
   unchanged; `EA::IO::FileStream` gained a cached size word (0x228 → 0x22c); `SP::cString` lost
   two members (0x1c → 0x14). Only the vector rule is a family rule; the rest are exact names.
3. **Structural deltas** that no leaf explains go in `tools/migrate/layout_overrides.json` as `insert` /
   `remove` / `append` on the dev member list, with an evidence string that is printed in the
   header: DatabasePackedFile's extra word at +0x2e0, `PFDatabaseHeader` 0x20 → 0x28,
   `PFIndexModifiable`'s embedded 0x20-byte pool allocator at +8, `cPropertyList` without the
   dev-only `mDescriptions` (0x54 → 0x38), `PFRecordRead` +8 (unexplained, appended).
4. **Evidence.** Exact-backed slice views sharing ≥3 member names with the PDB and small offset
   shifts are candidates; the one whose named members agree most with the re-laid offsets is
   *the* evidence; the others are reported as agreeing or not; views that share the member prefix
   and then diverge are another class under the same short name and are rejected with a note. A
   view **confirms** a member (`exact:<slice>`) or is reported as a conflict; it never moves one:
   slice member names are guesses (one DatabasePackedFile view calls the file starting offset
   `mpStream`; the disassembly says the real `mpStream` is one word later, where the re-laid
   layout puts it). Unnamed dev members between two confirmed ones are paired in order with the
   view's members of the same size (`exact-renamed`).
5. **Vtable and methods.** Paired vtables give every slot a name and signature from the dev slot;
   otherwise the dev vtable's slots are listed with retail addresses from the name map and the
   retail vtable is located only when a candidate has the same slot count and ≥2 agreeing slots
   (a derived class's vtable would otherwise win). Non-virtual methods come from the dev publics
   with `// 0x<retail va>` or `// dev only`.
6. A size check is emitted only when every member is exact-backed; otherwise the expected size
   is a comment.

Pilot result: `DatabasePackedFile` re-lays to 0x388 with 20 of 30 members confirmed by slice
s008d81d0 and the rest consistent with the disassembly (`mpStream` 0x260, `mMutex` 0x270,
`mpIndex` 0x2d0, `mpManager` 0x380); the remaining "conflicts" are the slice's off-by-one names.
`PFIndexModifiable` 0x4c, `cPropertyList` 0x38, `PFRecordRead` 0x70 via overrides;
`cDirectPropertyList` (re-laid 0x54, slices say 0x40) and `cPropertyManager` (18 unverified
members, 8 conflicts: the Factory subobject and embedded list moved) still need overrides.
Across all of UTFSpore_Win32 (272 classes, 2.3 s): 23 fully exact-backed, 36 partly, 213 re-laid
only, 95 member conflicts to look at.

Later the same day: headers moved to one include root `src/game/include/<Ns>/<Class>.h` (a TU of
one module includes classes of many); the closure of a module's classes (bases, by-value members,
pointees one hop) is emitted too; nested classes are defined inside their owner; namespace-level
enums get their own headers; the template library types are hand-written in
`src/game/include/eastl/*.h` and `EA/*.h` with the measured retail layouts; each generated class is
wrapped in `#pragma pack(push, 4|8)` from the packing the engine inferred (without it VC9 re-aligned
8-byte members). `tools/migrate/sizeprobe_pilot.cpp` checks the result under VC9: DatabasePackedFile
0x388 with `mpStream` 0x260, `mMutex` 0x270, `mOpenRecordMultiMap` 0x2e8, `mHeader` 0x308,
`mActiveHoleTable` 0x33c, `mpManager` 0x380; PFRecordRead 0x70; cPropertyList 0x38; the record
multimap 0x20. Still open: `cDirectPropertyList` and `cPropertyManager` overrides, `globals.h`.

### 3. `rewrite.py` — slice TUs → module TUs

Per module, for each slice that holds at least one of its functions:
1. Parse the slice TU into: preamble (includes, typedefs), struct/class definitions (the census
   extractor), extern declarations with `// 0x` addresses, functions with `// @ 0x` markers.
2. Drop every struct definition that has a canonical header; `#include` the headers instead.
   Members the slice invented (`field_0x1c`, `pad[0x10]`) are renamed to the canonical member at
   the same offset when the offset and size agree (`rename map`, written to
   `work/migrate/renames_<module>.json` for review); unknown names fail loudly.
3. Replace `FUN_xxxxxxxx` with the real name where `modmap`/`names.txt` has one; keep the address
   annotation either way.
4. Emit each function into `src/game/<module>/<dev object stem>.cpp` in retail address order;
   functions of *other* modules found in the same slice go to their own module's TU (a slice
   often mixes neighbours); file-local helpers (`static`) follow the first function that uses them.
5. Write the module's `manifest.txt` / `nonmatching.txt` / `partial.txt` from the slice rows, with
   the source column pointing at the new TU. (`run_all.py` resolves sources under `match/`; it gets
   a one-line change to accept `src/` paths.)
6. Verify: `run_all --manifest src/game/<module>/manifest.txt` must report every row byte-exact;
   `equiv.py` on every nonmatching row must return the previous verdict or better. A function that
   loses byte-exactness is the signal that a layout or a rename is wrong; the tool reports it and
   leaves the slice untouched until the header is fixed. Slices are deleted only when every one of
   their functions has landed and verified.

Metric per module: functions moved, byte-exact before/after, verdicts before/after, structs
replaced, renames applied, unresolved stubs.

### 4. `gate.py` — the hybrid per module

`build.py --hook-manifest src/game/<module>/nonmatching.txt` (a small extension: rows give source,
symbol, VA; the splicer already consumes any COFF through `equiv.prepare`) builds a hybrid with the
module's equivalent functions spliced; `boottest.sh` 120 s ×2 with the scene metric and the crash
detector; optionally `--coverage` once per module to record which of its functions the boot path
exercises. No human in the loop: a module that fails the gate is debugged with the fault address
first (`docs/hybrid.md`, "read the fault address first; bisect second"), and only its own hooks
are candidates.

#### rewrite: what was built (2026-10-12)

`tools/migrate/rewrite.py` is implemented and landed the first pilot slice: `s008d81d0` -> `src/game/UTFSpore_Win32/DatabasePackedFile.cpp`,
21/21 byte-exact, the 13 equivalent rows at the same or a better difftest verdict class. Procedure, rules, the manual
escape hatches (`work/migrate/renames_<slice>.json` `manual`) and the facts learned are in `docs/migration-runbook.md` section 7.
Everything the slice needed beyond the automatic rules: 6 method names, 2 callee method names, 1 class, 2 text edits, 6 new
header override entries (`tools/migrate/layout_overrides.json`: Manager `vtable_insert`, `decl_overrides` on Compression,
CompressionRefpack, PFRecordInfo and DatabasePackedFile, EASTLCoreAllocator `remove`) and 8 generator changes (list in the runbook).

## Pilot: DBPF + property lists

Object files: `UTFSpore_Win32/DatabasePackedFile.obj`, `DatabasePackedFileIndex.obj`,
`DatabasePackedFileRecord.obj`, `DatabasePackedFileUtil.obj`; `SPEngine/SPPropertyList.obj`,
`SPPropertyManager.obj`, `SPPropertyHelpers.obj`. With all six modmap signals (2026-10-12):
**435 functions**, 78.6 KB (97 byte-exact, 131 equivalent, 78 partial, 129 without source),
spread over **33 slices** and 25 retail runs (`modmap.py --module DatabasePackedFile` /
`--module SPProperty` lists them with the signal and the slice status of each). Dev types exist for all of it: `EA::ResourceMan::DatabasePackedFile`, `Key`,
`PFIndexModifiable`, `PFIndexEntry`, `PFRecordInfo`, `PFHoleTable`, `Record*`, `Database`,
`Manager`, `SP::cPropertyList`, `cDirectPropertyList`. `src/resource/` and
`match/include/Resource/DatabasePackedFile.h` already hold a behavioural model and a partial
retail layout to check the generated headers against.

Why this module: it is the bottom of the dependency graph (everything loads through it), half of
it is byte-exact already, it has differential tests against the shipped data (milestone 1), and
its classes are small enough that header generation and the rename map get exercised without the
UI or simulator type zoo.

Success criteria: the seven object directories build as one library; every previously byte-exact
function byte-exact; no equivalence verdict worse than before; the hybrid boots with every
equivalent function of the module spliced; the census count for the module's classes drops to one
body each; the 22 slices are gone.

## Order of work

1. `modmap.py` with signals 1–2 and the metric; then 3–6, measured one at a time. **Done
   2026-10-12** (34.6% of functions, 48.2% by size, ~96.5% hold-out precision).
2. `headers.py` for the pilot's classes only, diffed by hand against `match/include/Resource/*`
   and the byte-exact slices' views (a day). **Generator done 2026-10-12**; the hand diff is the
   `relaid` lines of the pilot headers.
3. `rewrite.py` on one slice of the pilot, then all 22; fix what breaks (two to three days —
   this is where the real surprises are).
4. `gate.py`; pilot boot.
5. Second module without hand-holding (candidate: `UTFSpore_Win32/EALocale.obj` + `Expression.obj`,
   or `SPEngine/SPAppConfigManager.obj`), to measure the per-module cost before planning the rest.

Worker (DeepSeek) involvement: none for steps 1–4; afterwards the module work lists (missing and
partial functions of the module being migrated, in coverage order, written against the canonical
headers) replace address windows as the units of agent work (`docs/PLAN.md` Phase C).

## Risks and open questions

- **Module boundaries for unnamed code** (73% of functions). Signals 3–5 are estimates; the
  `_unassigned` directory keeps the pipeline honest. If alignment (signal 5) works as well as it
  does for xmatch's callee sequences, it also recovers thousands of names.
- **LTCG cross-module inlining**: a retail function may contain inlined bodies from another
  module's headers; irrelevant for placement (the function is where the linker put it) but the
  inlined helper must exist in a shared header for byte-exactness — already the case in slices.
- **COMDAT folding** (`match/clones.txt`): one retail body for several dev functions; the module
  map keeps all names and the manifest keeps the clone rows.
- **Layout conflicts the evidence cannot settle** (no byte-exact user of the struct): take the PDB,
  mark the header `// layout: dev PDB, unverified in retail`, and let the first byte-exact function
  that touches the field confirm it.
- **Equivalence verdicts move** when a stub becomes a real type: inputs change shape, so WEAK/PASS
  can flip to UNSUPPORTED (resolver) rather than FAIL. The gate compares verdict *classes* and
  treats UNSUPPORTED after PASS as a regression to fix, not to accept.
- **Size**: 978k lines through a parser that is "the census extractor plus regexes". It will be
  good enough for the pilot; a real C++ front end (libclang on the VC9-dialect sources) is the
  fallback if the regexes crack on the UI code.
