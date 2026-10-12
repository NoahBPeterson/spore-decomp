# Module migration: from slices to a source tree

Design (2026-10-12) for Phase B of `docs/PLAN.md` "Roadmap to completion". Status: design; nothing
under `tools/migrate/` exists yet.

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

Builds `work/migrate/modmap.json`: `{va: {"module": ..., "how": ..., "confidence": ...}}`.

Signals, applied in order, each only to functions still unassigned:
1. **anchor** (9,444): named, unique dev object.
2. **interpolation** (→ 27%): between two anchors of the same module, in the same run.
3. **class membership**: the function's class (from `symbols/names.txt`, vtable slot names, or a
   `this`-type recovered by a slice) has all its anchored methods in one module.
4. **call graph**: every direct caller and callee (from the Ghidra xref dump) is in one module and
   the function is not a known shared helper (EASTL instantiation, CRT, operator new) — static
   helpers and private methods live with their callers.
5. **order/size alignment**: inside a gap between run A and run B, align the retail function-size
   sequence against the dev objects' function sequences (A's tail, B's head): the dev PDB has the
   order and sizes of every function, and link order is preserved within an object. This is the
   same idea as xmatch's callee alignment applied to layout; it also yields *names* for unnamed
   retail functions, which feeds back into step 1.
6. **template/instantiation rule**: EASTL/`eastl::` instantiations, `$E` static initialisers and
   compiler-generated `??_G`/`??_E` go with the module that owns the class they are instantiated
   for (from the mangled name), else with the module that calls them.

Leftovers go to `src/game/_unassigned/<address-range>/` with their slice bookkeeping, so nothing
is lost; the metric is the assigned share by count and by size, and the number of conflicts
(two signals disagree). Target before the pilot: >70% by size with <1% conflicts.

### 2. `headers.py` — canonical headers from the dev PDB

For each class a module needs (its own classes plus every type its functions touch), emit
`src/game/<module>/<Class>.h` (nested/namespaced names flattened to a path) from `types.json`:
members at their exact offsets (explicit padding where the PDB has holes), bases, `vfptr`,
`// 0x` vtable address and slot-ordered virtual declarations from `pdb_vtables.json` +
`symbols/vtable_names.txt`, method declarations for every function assigned to the class (with
`// 0x` addresses so the resolver can bind them), `static_assert`-equivalent size checks
(`sizeof` checks via a template trick; VC9 has no `static_assert`).

Dev ≠ retail. The 2008 PDB is not the shipped build: `SP::cString` is 0x14 in retail vs 0x1c dev.
Resolution order for a layout: (1) `work/migrate/layout_overrides.json` (hand-confirmed retail
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

## Pilot: DBPF + property lists

Object files: `UTFSpore_Win32/DatabasePackedFile.obj`, `DatabasePackedFileIndex.obj`,
`DatabasePackedFileRecord.obj`, `DatabasePackedFileUtil.obj`; `SPEngine/SPPropertyList.obj`,
`SPPropertyManager.obj`, `SPPropertyHelpers.obj`. Anchored ranges today: **306 functions**
(148 byte-exact, 91 equivalent, 63 partial, 4 without source), 150 of them named, spread over
**22 slices** and 19 retail runs (0x59ecc0, 0x6a07d0–0x6aaa10, 0x6bbdd0–0x6bfa00, 0x8d81d0–0x8dd430,
0x93a2e0, 0xa21dc0), with gaps of up to 56 unassigned functions next to them that `modmap` steps
3–5 must settle. Dev types exist for all of it: `EA::ResourceMan::DatabasePackedFile`, `Key`,
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

1. `modmap.py` with signals 1–2 and the metric (half a day); then 3–6, measured one at a time.
2. `headers.py` for the pilot's classes only, diffed by hand against `match/include/Resource/*`
   and the byte-exact slices' views (a day).
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
