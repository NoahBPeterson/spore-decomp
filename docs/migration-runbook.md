# Migration pilot runbook: slices → `src/game/`, step by step

Written 2026-10-12 for Sonnet 5.5 agents running in a workflow (`.claude/workflows/migration-pilot.js`).
Everything here was verified in the session that wrote it; where a fact is a guess it says so.
Read `docs/migration.md` first for the design and the measurements, then this file for the exact
procedure. Steps 1 and 2 of the pipeline (module map, headers) are done; this runbook is step 3
(`rewrite.py` + the pilot slices) and step 4 (the hybrid gate, §4). §3 is the design `rewrite.py`
was built to; §7 is the tool as built and what the first slices taught, and wins where they differ.

## 0. Ground rules for every agent

- Repo: `/Users/noahpeterson/Documents/Projects/spore-decomp`, branch `main`. Never commit. Never
  run anything in the background. Search with `rg`. Scratch files go under the scratchpad directory
  named in your prompt, never in `work/batches/`.
- Several agents share the machine. `run_all.py` serialises itself on `work/run_all.lock`: when
  another run holds it, it prints "waiting for another run_all.py" and waits (module manifests take
  2-17 s). Never kill a compile or a `run_all` you did not start. One compile loop per agent.
- Do not modify `match/slices/**` in this phase. The slices are the source of truth until a module's
  functions have landed in `src/game/` **and** verified; deleting slices is a later, separate step.
- `tools/migrate/headers.py` output under `src/game/include/` is generated: never hand-edit a
  generated header. Fix the generator, `tools/migrate/layout_overrides.json`, or the hand-written
  template headers (`src/game/include/eastl/*.h`, `src/game/include/EA/*.h` that say
  "Hand-maintained"), then regenerate.
- Every rule you discover goes into code or a file an agent reads, not into your head: rename rules
  into `tools/migrate/rewrite.py` or the per-slice `work/migrate/renames_<slice>.json`; layout facts
  into `layout_overrides.json` with an `evidence` string; toolchain surprises into
  `docs/Papercuts.md` in the existing one-line format.
- Report numbers only after reading what produced them. A counter you did not inspect is not a result.

## 1. State you start from

| artifact | what | how to rebuild |
|---|---|---|
| `work/migrate/modmap.json` | retail VA → dev object file, how, confidence, dev name | `python3 tools/migrate/modmap.py` (6 s) |
| `work/migrate/sliceviews.json` | every struct view in every slice with computed member offsets and byte-exact users | `python3 tools/migrate/sliceviews.py` (16 s) |
| `work/migrate/retail_leaf_sizes.json` | retail sizes of library leaf types with evidence | `python3 tools/migrate/leafsizes.py` |
| `tools/migrate/layout_overrides.json` | hand-confirmed structural deltas dev → retail (in git) | edit by hand, with evidence |
| `src/game/include/**` | generated class headers + hand-written template headers | `python3 tools/migrate/headers.py --module DatabasePackedFile` and `--module SPProperty` (2 s each) |
| `tools/migrate/sizeprobe_pilot.cpp` | compile-time probe of sizes/offsets under VC9 | see §2 |

Verified under VC9 (2026-10-12): `EA::ResourceMan::DatabasePackedFile` is 0x388 with `mpStream`
0x260, `mMutex` 0x270, `mOpenRecordMultiMap` 0x2e8, `mHeader` 0x308, `mActiveHoleTable` 0x33c,
`mpManager` 0x380; `PFRecordRead` 0x70; `PFIndexModifiable` 0x4c; `SP::cPropertyList` 0x38; the
record multimap 0x20; `eastl::vector<T>` 0x14. Not yet right: `SP::cDirectPropertyList` compiles to
0x54 while the byte-exact slices say 0x40 (`mpConfig` at 0x3c) and `SP::cPropertyManager` has 8
member conflicts (Factory subobject and the embedded list moved). Both need overrides (§6).

The pilot: 7 dev object files, 435 retail functions, 33 slices. List them:

```sh
python3 tools/migrate/modmap.py --quiet --module DatabasePackedFile   # 4 modules, functions with slice status
python3 tools/migrate/modmap.py --quiet --module SPProperty           # 3 modules
# slice of a function: the directory whose <id>.cpp contains the marker "// @ 0x<va>"
rg -l "// @ 0x008d81d0" match/slices/*/*.cpp
```

The first slice to migrate is **`match/slices/s008d81d0`**: 33 functions, all
`EA::ResourceMan::DatabasePackedFile` methods, 21 byte-exact (its `manifest.txt`), 12 equivalent
(`nonmatching.txt`), 1 partial. Its struct view agrees with the generated header on 20 of 30
members and its remaining "conflicts" are the slice's own names being one slot off (§5).

## 2. Toolchain: how to compile and verify

- Compiler: `tools/matching/cl.sh <cl flags>` runs VC9 under Wine. Paths are `Z:` + the absolute
  path with backslashes. Include root for the new tree: `/IZ:\...\src\game\include`.
- Quick compile of one TU (what `headers.py` development used):
  ```sh
  S=<scratchpad>/t; mkdir -p $S
  tools/matching/cl.sh /nologo /c /TP /W3 "/IZ:$(pwd | tr '/' '\\')\\src\\game\\include" \
     "/FoZ:$(echo $S | tr '/' '\\')\\t.obj" "Z:$(echo $S | tr '/' '\\')\\t.cpp"
  ```
- Size/offset probe: `tools/migrate/sizeprobe_pilot.cpp` uses `char (*name)[sizeof(T)] = 1;`
  so the error message prints the number: run it with the command above and read the
  `cannot convert from 'int' to 'char (*)[N]'` lines in order. Add a line per class you touch.
- Interpreter: `run_all.py`, `cmpdis.py` and `tools/difftest/*.py` import `pefile`/`capstone`/`unicorn`, which exist only in
  the repo venv: run them as `.venv/bin/python tools/...` (plain `python3` is Homebrew's and lacks them; `headers.py`
  and `rewrite.py` are stdlib-only and run under either).
- Byte-exact verification: `.venv/bin/python tools/matching/run_all.py --manifest <file> -v`. Manifest rows
  are `source symbol va flags` where **`source` is relative to `match/`**, so a TU under `src/game/`
  is written `../src/game/UTFSpore_Win32/DatabasePackedFile.cpp`. Flags are the slice's flags plus
  `/Isrc/game/include` (relative `/I` paths are resolved against the repo root by `resolve_flags`).
  The symbol column is the decorated name; `run_all` also accepts a unique substring. Output:
  per-row `MATCH`/`DIFF n bytes`/`COMPILE FAIL`; exit 0 only when every row matches.
- Equivalence of non-exact functions: `tools/difftest/equiv.py` (read its docstring for the CLI;
  `tools/difftest/batch.py` runs a shard spec; the slice's `nonmatching.txt` rows record the
  previous verdict, e.g. "difftest WEAK (211 valid...)" or "PASS 400/400"). The acceptance rule is
  verdict class not worse than before; `UNSUPPORTED` after `PASS` is a regression to fix.

## 3. `tools/migrate/rewrite.py`: the design it implements

Usage: `rewrite.py <slice-id> [--apply] [--module SUBSTR] [--quiet]`. Without `--apply` it prints
the plan and writes `work/migrate/renames_<slice>.json`; with `--apply` it writes the module TU(s)
and manifests. Reuse `tools/migrate/headers.py` as a library (`from headers import Data, Types,
split_qual, parse_decl`): `Data()` loads the modmap, dev symbols/publics, vtables, the demangler
cache; `Data.types.layout(cls, "retail")` gives the canonical members with offsets;
`Data.retail_vtables_for(cls)` + `Data.dev_vt[dva]["slots"]` + `Data.pub` give slot → method name.

1. **Split the slice TU**: preamble (everything before the first `// @ 0x` marker), then one chunk
   per marker up to the next marker. The function's VA is the marker; its retail class and dev
   name come from `modmap.json["functions"][va]["name"]` (e.g.
   `EA::ResourceMan::DatabasePackedFile::Lock`); the slice's class name is what precedes `::` in the
   definition line (`DatabasePackedFile::Lock`). Record `class_map[slice class] = canonical class`.
   Target module = `modmap.json["functions"][va]["module"]` (`UTFSpore_Win32/DatabasePackedFile.obj`
   → TU `src/game/UTFSpore_Win32/DatabasePackedFile.cpp`). A slice may hold functions of several
   modules: each goes to its own TU.
2. **Map the slice's other structs to canonical classes**, in this order of evidence, and write the
   result to the renames file for review:
   1. a method declared in the slice struct with a retail address comment (`// 0x8dbf20`): look the
      VA up in `symbols/pdb_names.json` → `Class::Method` → the class (this named `Refpack` →
      `EA::CompressionRefpack`, `Mutex` → `EA::Thread::Mutex`, `RecMap::find` → the multimap);
   2. vtable slot names declared in the slice struct vs the canonical class's slot names from
      `retail_vtables_for` (this names `Index` → `EA::ResourceMan::PFIndex`, `IAlloc` →
      `EA::Allocator::ICoreAllocator`, `IStream` → `EA::IO::IStream`);
   3. the type of the canonical member at the same offset in the mapped owner (`mFile` is
      `EA::IO::FileStream`, `mpStream` is `EA::COM::AutoRefCount<EA::IO::IStream>`, `mMutex` is
      `EA::Thread::Mutex`, `mActiveHoleTable` is `PFHoleTable`);
   4. same short name in the owner's namespace (`Key` → `EA::ResourceMan::Key`, `PFRecordWrite`,
      `PFRecordRead`, `PFIndexModifiable`).
   Anything unmapped stays as a slice-local definition in the TU, flagged `// TODO(rewrite): local
   stub`, and counted in the report.
3. **Member rename map by offset**: flatten both sides to `(offset, size) → path`. Slice side from
   `sliceviews.json` (`defs` of this slice; nested by-value members expand to dotted paths, e.g.
   `mActive.mHoles` = 0x33c). Canonical side from `layout(cls, "retail")` with by-value struct
   members expanded one level. Pair by offset and size; a slice member whose span covers several
   canonical members (the slice's `mActive`, 40 bytes at 0x334 = `mnHoleUsageFlags` +
   `mfHoleCompactionMinimumRatio` + `mActiveHoleTable`) is split: each sub-path maps separately.
   Rewrite member accesses in function bodies by longest dotted-path match on identifier tokens
   (`mActive.mHoles.Alloc(` → `mActiveHoleTable.Allocate(`). Members used as a bare identifier
   inside a method of the mapped class are the class's members; qualify nothing else.
4. **Method renames on mapped classes**: slice method name → canonical method, by retail address
   when the slice comments one (pdb_names), else by arity + name similarity against the canonical
   class's dev methods (`Data._methods_by_class`); unmatched ones are listed in the renames file
   under `"unmatched_methods"` and left as-is (they still compile if declared in the TU).
5. **Virtual-call thunks → calls**. The slices spell virtual calls as
   `((TFb1)(*(void***)EXPR)[0x74 / 4])(EXPR, args)` (typedefs `TF*`, `TFi*`, `TFb*`, `TFc*` in the
   preamble). Replace with `EXPR->Method(args)` (`Method(args)` when EXPR is `this`), Method =
   slot `0x74/4` of the canonical class of EXPR: `this` → the function's class; a member → that
   member's canonical type; a cast `(void*)mgr` → the canonical type of the member it came from
   (`mpManager` is `EA::ResourceMan::Manager*`). The slot table for the class is
   `retail_vtables_for` + the dev slots; for a pure interface (`PFIndex`, `IStream`,
   `ICoreAllocator`) the names come from an implementer, which `headers.py`'s
   `Data.implementer_slot(cls, k, qualifier)` already does. Keep the original line in a trailing
   comment when the slot is unnamed. A thiscall through a secondary base (`this` adjusted) is not
   expected in the pilot; if it appears, leave the thunk and flag it.
6. **Externs with addresses** (`extern "C" void* __cdecl X(...); // 0x925fe0`): resolve the VA in
   pdb_names; when it is a method (`EA::Allocator::ZoneObject::operator new`), declare nothing
   (the header has it) and rewrite the call to the qualified name; when unnamed, keep the extern
   in a `// unnamed retail callees` block with its address. Globals (`extern const int
   kTimeoutNone[]; // 0x1436788`) likewise; `symbols/pdb_globals.json` names some.
7. **Emit the TU**: header comment with the object file and the source slices; `#include` of the
   headers of every mapped class (path = `include_path(cls)` from headers.py) and of
   `game/types.h`; the kept local stubs and unnamed externs; the functions in VA order with their
   `// @ 0x` markers. One TU per module; when the module TU already exists (a later slice of the
   same module), append functions in VA order and merge the stub/extern blocks (dedupe by text).
8. **Bookkeeping**: `src/game/<dir>/<obj>/manifest.txt`, `nonmatching.txt`, `partial.txt` with the
   slice rows, source column `../src/game/<dir>/<obj>.cpp`, flags + `/Isrc/game/include`. Write
   `work/migrate/rewrite_<slice>.json` with: functions moved, structs replaced, renames applied,
   stubs kept, thunks converted/left.
9. **Verify** (§2): `run_all --manifest` on the module manifest must report every row `MATCH`;
   then equiv on the nonmatching rows. A `DIFF` after the rewrite is the signal that a header is
   wrong (wrong offset, wrong virtual slot, wrong size of an embedded type) or that a rename changed
   semantics; diagnose with `tools/matching/cmpdis.py`/`chk.py` (see `docs/matching.md`) and fix the
   header source (override / leaf table / hand template header), regenerate, recompile. Do not
   "fix" by editing the generated header or by changing the function body's logic.

### Worked example: `s008d81d0` → `EA::ResourceMan::DatabasePackedFile`

Slice name → canonical (derived in the session; use it as the acceptance test for steps 2–5):

| slice | canonical | note |
|---|---|---|
| `DatabasePackedFile` (0x384) | `EA::ResourceMan::DatabasePackedFile` (0x388) | main class |
| `mpStream` (long, 0x25c) | `mnFileStartingOffset` | the slice's names 0x258–0x26c are one slot off; the header is right (disassembly + FileStream 0x22c) |
| `mpMemoryLocation.p` (0x260) | `mpStream.mpObject` | `EA::COM::AutoRefCount<EA::IO::IStream>` |
| `mpMemoryBase` (0x264) | `mpMemoryLocation` | `void*` |
| `mnMemorySize` (0x268), `mnMemoryPosition` (0x26c) | `mnMemorySize`, `mnMemoryOffset` | |
| `mMap` (RecMap, 0x2e8) | `mOpenRecordMultiMap` | `eastl::multimap<Key, PFRecordBase*, less<Key>, EASTLCoreAllocator>`; `.mnSize`, `.mAnchor.mpNodeLeft`, `.find(key)` (iterator sret; retail 0xa21dc0 is the rbtree `find` instantiation) |
| `mHeaderBlock.f[0..9]` (PFHeader) | `mHeader` (`PFDatabaseHeader`, 0x28) | f[0] `mnUserVersionMajor`, f[1] `mnUserVersionMinor`, f[2..3] `mnCreationTime` (int64), f[4..5] `mnUpdatedTime` (int64), f[6] `mnIndexRecordType`, f[7] `mnIndexRecordPosition`, f[8] `mnIndexRecordEntryCount`, f[9] `mnIndexRecordSize` |
| `mbFlag330` | `mbHeaderHasChanged` | |
| `mActive.mExtent`, `mActive.mRatio`, `mActive.mHoles` | `mnHoleUsageFlags`, `mfHoleCompactionMinimumRatio`, `mActiveHoleTable` | |
| `mHoleB` | `mDelayedHoleTable` | |
| `HoleSet::{Reset, AddHole, Alloc, GetTotalSize, mField0}` | `PFHoleTable::{Reset(uint), Free(long,uint), Allocate(uint), GetBytesFree(), mExtent}` | retail 0x8db3a0 / 0x8dc000 / 0x8dbf20 / 0x8dae40 are unnamed in pdb_names; the tool writes their decorated names to `symbols/slices/<slice>.txt` so the difftest resolver binds them |
| `mpManager` (uint32) | `mpManager` (`Manager*`) | the `(void*)mgr` casts go away |
| `Index` | `EA::ResourceMan::PFIndex` | slots 1 IsModifiable, 3 GetSize, 7 GetKeyList, 8 GetKeysSortedByPosition, 10 FindRecord, 12 DeleteRecord(key, info&) ("GetEntry"), 13 ReadFromMemory ("Op34"), 14 WriteToMemory ("Serialize"), 16 ValidateFreeSpace ("VerifyRange"); slot 4 (`Op10`) is `Clear` |
| `IStream` | `EA::IO::IStream` | slots per `src/game/include/EA/IO/IStream.h` (named from FileStream) |
| `IAlloc` | `EA::Allocator::ICoreAllocator` | slots 2 Alloc, 3 Free |
| `Refpack` | `EA::CompressionRefpack` | `IsValidHeader` = `ValidateCompressedData` (0x92cad0), `DecompressData` (0x92ca60) |
| `Mutex::Lock/Unlock` | `EA::Thread::Mutex::Lock(const ThreadTime&)`/`Unlock()` | 0x9221b0 / 0x922270; `kTimeoutNone` (0x1436788) is the `EA::Thread::kTimeoutNone` constant, unnamed in pdb_globals |
| `ICoreAllocator_Alloc_Named(size, alloc, name)` + `p->Init(...)` | `EA::Allocator::ZoneObject::operator new(size, alloc, name)` (0x925fe0) then the constructor | the tool emits `return new (mpAllocator, "Resource/PFRecordWrite") PFRecordWrite(a, b, c, this);` (byte-exact in s008d81d0; the two-step form the design proposed was not needed); `PFRecordWrite::Init` (0x8dcea0) and `InitData` (0x8dd0d0) are the two constructors, `PFRecordRead::Init/Init2` (0x8dcc80/0x8dcdc0) likewise, `PFIndexModifiable::Init` (0x8db730) its constructor |
| `DBase/DBase1` | `EA::ResourceMan::Database` | two vptrs + `mRefCount` (`AtomicInt<int>`) |

`this` virtual-call slots used by the slice, all in the generated `DatabasePackedFile.h` vtable:
0x1c/4=7 `Close`, 0x3c/4=15 `CloseRecord`, 0x44/4=17 `Attach`, 0x64/4=25 `ReadHeaders`, 0x68/4=26
`ReadHeaderRecord`, 0x6c/4=27 `WriteEmptyHeaderRecord`, 0x70/4=28 `WriteHeaderRecord`, 0x74/4=29
`VerifyHeaderRecordIntegrity`, 0x78/4=30 `ReadIndexRecord`, 0x84/4=33 `CreateIndex`, 0x88/4=34
`DestroyIndex`, 0x8c/4=35 `MakeIndexModifiable`, 0x90/4=36 `InitializeHoleTable`. Through `mFile`:
0x3c/4=15 `SetPath`, 0x4c/4=19 `Open` (FileStream). Through the stream: slot 5 `GetState`, 8
`SetSize`, 14 `Write` (as `WriteRaw`-style bool), per `IStream.h`.

Expected codegen equivalences (why byte-exactness should survive): a virtual call through a real
declaration compiles to the same `mov eax,[ecx]; call [eax+N]` as the thunk cast; `AutoRefCount`'s
raw member access is the same load as `.p`; the rbtree `find` returning an iterator with a user
constructor uses the same hidden-pointer return as the slice's explicit out-parameter; a placement
constructor call is the same thiscall as `Init`. Where a `DIFF` appears anyway, the usual causes are
(a) the compiler now sees a `const`/`volatile` difference (the slice's `volatile long mRefCount`),
(b) a member type changed size, (c) an inline method in a hand-written template header got inlined
where the slice had a call. Check in that order.

## 4. Order of work and acceptance per phase

1. **Tool + first slice** (done 2026-10-12, §7). Build `rewrite.py` (§3) against `s008d81d0`; iterate until
   `run_all --manifest src/game/UTFSpore_Win32/DatabasePackedFile/manifest.txt` reports **21/21
   MATCH** and the 12 nonmatching rows keep their verdict class. Deliverables: the tool, the TU, the
   manifests, `work/migrate/renames_s008d81d0.json`, `rewrite_s008d81d0.json`, and a list of every
   rule you had to add by hand (these become tool defaults).
2. **The other 32 pilot slices**, grouped by target module (run modules in parallel, slices of one
   module one after another because they append to the same TU). Per slice the acceptance is the
   same: every manifest row MATCH, no verdict regression, `partial.txt` rows carried over unchanged.
   Functions a slice holds for a module outside the pilot (`modmap` says another object) stay in
   the slice for now; list them.
3. **Module build.** All seven TUs compile with the slice flags into objects; `run_all` on the union
   of the seven manifests is green; `tools/matching/layout_census.py` run on `src/game/include`
   reports one body per class name for the pilot's classes.
4. **Gate.** `tools/hybrid/build.py` gets `--hook-manifest <nonmatching.txt>` (rows: va, source,
   symbol; the splicer already accepts any COFF via `equiv.prepare`); build the hybrid with the
   module's equivalent functions, `tools/hybrid/boottest.sh` twice with the scene metric
   (`SCENE_MIN=6`), optionally `--coverage` once. One hybrid build/boot at a time (the build shares
   one compile cache and `boottest.sh` reads one game window); never leave the game window open.
   A failing boot is debugged from the fault address
   (`docs/hybrid.md`), with only the module's hooks as suspects.
5. **Report**: per module, functions moved / byte-exact before and after / verdicts before and
   after / structs replaced / renames applied / stubs kept, plus the rules added to the tool.

## 5. Facts that will save you time (all measured 2026-10-12)

- Slice member **names are guesses**; slice member **offsets** are right for the members a
  byte-exact function touches. Never move a canonical member to where a slice name says; when the
  header and a slice disagree, the disassembly decides (`tools/matching/cmpdis.py`), and the
  resolution goes into `layout_overrides.json` with evidence.
- Retail vs dev layout differences come from four sources only, so far: `EASTLCoreAllocator` 0xc →
  8; the vector allocator slot 4 → 8; `EA::IO::FileStream` +4 (`mnSize`); `SP::cString` 0x1c → 0x14;
  plus class-level structural edits (inserted members, widened times, dropped members). The
  generator handles the first four; the last kind is an override.
- EA code is packed at 4: an `__int64` member sits at a 4-byte boundary. `headers.py` infers the
  packing per type from the dev size and emits `#pragma pack(push, 4|8)` around each class. A class
  whose size VC9 computes differently from `headers.py --show <class>` is a generator bug: report it
  with the probe output, do not patch the header.
- Dev order of functions inside an object is ascending in retail too; a pair that is out of order is
  a function moved in the file since 2008 or a misnamed anchor.
- `run_all.py` resolves source paths relative to `match/`; object files are named from the source
  path with `/` → `_`, so two manifests pointing at the same TU with the same flags share one
  compile.
- `llvm-undname` lives at `/opt/homebrew/opt/llvm/bin/llvm-undname`; `work/migrate/undname_cache.json`
  caches results. `[thunk]:` entries are adjustor thunks (same method, secondary vtable).
- Pure interfaces (`PFIndex`, `IStream`, `ICoreAllocator`) have `_purecall` in every dev slot; names
  come from an implementing class's vtable with the same `{for X}` qualifier.
- `work/xmatch/tables.json` `ret_vt` (4,731 retail vtables → slot VAs) and `dev_vt` (5,005 dev
  vtables with names) are the vtable sources; `symbols/pdb_vtables.json` pairs 377 of them.

## 6. Known open items in the pilot headers

- `SP::cDirectPropertyList`: slices (exact-backed, s00587a20) say size 0x40 with `mpConfig` at 0x3c;
  the PDB re-lay gives 0x54 (`mNumDirectProps` 0x38, `mDirectProps` 0x3c, `mTempDirectVariant` 0x40).
  Resolve from the byte-exact users before migrating `SPPropertyList.obj`.
- `SP::cPropertyManager`: retail has the `Factory` subobject at +4 and the embedded `cPropertyList`
  at +0x3c, the name table at +0x148 (`docs/Papercuts.md`, slice s005e3280); the generated header
  lists 8 conflicts. Needs an override built from the byte-exact slices (s006aa3f0 has exact-backed
  hash maps at 0x94 and 0xb4).
- `EA::ResourceMan::PFRecordRead`: the +8 (0x68 → 0x70) is appended as `mUnknown68`; the byte-exact
  record functions in `DatabasePackedFileRecord.obj` will say where it really is.
- `EA::Thread::kTimeoutNone` (0x1436788) and the Refpack vtable (0x140a0e8) are unnamed globals;
  `globals.h` generation (design §2) is not written yet; `rewrite.py` keeps such externs
  (`KNOWN_EXTERNS` and anything with an address comment) until it is.

## 7. `rewrite.py` as built, and what the first slice taught (2026-10-12, s008d81d0)

`python3 tools/migrate/rewrite.py <slice-id> [--apply] [--module SUBSTR] [--quiet]` (stdlib only; `--apply` runs
`run_all` through the venv for the byte-diff counts). Result on `s008d81d0`: 34 functions to
`src/game/UTFSpore_Win32/DatabasePackedFile.cpp`, **21/21 MATCH** with
`.venv/bin/python tools/matching/run_all.py --manifest src/game/UTFSpore_Win32/DatabasePackedFile/manifest.txt -v`, the 13
equivalent rows (12 nonmatching + the partial) at the same or better equiv verdict class (Attach FAIL -> PASS):

    .venv/bin/python tools/difftest/equiv.py s008d81d0 <vas> --src src/game/UTFSpore_Win32/DatabasePackedFile.cpp \
        --flags "/O2 /MD /Gy /TP /GS- /arch:SSE /Isrc/game/include"

**Artifacts.** `work/migrate/renames_<slice>.json` = `auto` (recomputed every run: class map with the evidence for each
struct, member path map, method map, per-function decisions, notes) + `manual` (read back, wins over `auto`; edit this).
`work/migrate/rewrite_<slice>.json` = the report (functions moved/left, structs replaced, counters, notes).
`symbols/slices/<slice>.txt` = retail VA -> decorated name, for the migrated functions and for callees the slice
addresses but pdb_names does not name (PFHoleTable::Free 0x8dc000, the PFRecordWrite/PFIndexModifiable constructors, the
PFRecordRead constructor overloads): exact mangled names, so the difftest resolver binds overloads. The module TU is rebuilt
from scratch when it only holds this slice's functions, merged (VA order, preamble union) when it holds others.

**`manual` keys.** `class_map` {slice struct: canonical class}; `methods` {va or "Slice::name": canonical method name} for
slice functions whose canonical method evidence cannot settle; `method_names` {"Struct::method": canonical name} for
callee methods of other mapped structs; `members` {struct: {slice path: canonical path}}; `externs` {name: {decl, call,
why}}; `edits` [{va, find, replace, why}] exact text replacement on the rewritten body, for constructs no rule covers.
Every entry carries a `why` (in the `why` map or inline). The pilot slice needed: 6 method names (below), 2 callee
method names (`HoleSet::AddHole` = `PFHoleTable::Free`, `GetTotalSize` = `GetBytesFree`), 1 class (`RbNode`), 2 edits.

**Rules the tool applies** (all in `rewrite.py`; evidence strings are in the code): the class map of section 3 plus slot
signatures (`IdxEntry*` <-> `PFRecordInfo&` through the `Index` slot 12) and a size check on pointer-propagated
mappings; member pairing by (offset, size) against **VC9-probed** canonical offsets (`probe_classes`: one `char
(*p)[offset*65536+size+1] = 1;` per node, 90 per `cl` run because cl stops at 100 errors), with same-name-at-same-offset
as fallback, array-of-words over a canonical struct (`mHeaderBlock.f[i]` -> `((uint32_t *)&mHeader)[i]`), and a word
view for half of an int64 (`f[3]` -> `((unsigned int *)&mHeader.mnCreationTime)[1]`, adjacent `[0] = e; [1] = 0;` pairs
collapse to `mnCreationTime = e;`); method map (manual > retail address when the arity agrees > unique same name > shape
+ name similarity); thunks -> calls with `(int)`-cast arguments restored to the canonical parameter types, `&x` out
arguments -> references (the local is retyped when its type differs), literal ints -> enum casts, slot-0 delete thunks ->
`delete p`; allocation idiom -> `return new (alloc, "name") T(args);` (constructor chosen by arity, pointer arguments
cast to the constructor's parameter types); stub-vptr stores dropped with the declaration moved to the store (the
canonical constructor sets the vptr); locals the slice typed as integers but initialised from a pointer member are
retyped; externs: `KNOWN_EXTERNS` (kTimeoutNone, FindEmbeddedPackageHeader) and anything with an address comment kept.

**Facts learned (each one cost a DIFF or a compile error).**
- `pdb_names.json` is shifted by one for the three functions at 0x8d9050/0x8d90e0/0x8d9170: they are `ReadFileSpan`,
  `WriteFileSpan`, `ReadRecordRaw` (dev order, and the bodies), not `WriteFileSpan`/`ReadRecordRaw`/unnamed; `ReadFileSpan` at
  0x6bca90 and `DecompressData` at 0x6bcc10 are other functions. The method map rejects an address whose arity differs from
  the slice's (0x8d88d0 is named `InternalSetPosition(long)` but takes two arguments: it is `InternalRead`).
- Some retail signatures differ from the dev PDB: `ShouldRecordBeCompressed` returns an int in retail (`mov eax,1` /
  `xor eax,eax`; bool gives `mov al,1`); override in `layout_overrides.json` `decl_overrides`.
- The retail `ReadIndexRecord` call result is converted to bool by `test al,al / setne al`; `return Call();` of a bool
  is a tail call. `return Call() ? true : false;` compiles to the retail code (tried `(char)`, `!= 0`, `!!`, `!= false`).
- A local compressor with an inline constructor/destructor (`Decompress` 0x8d8820) needs both inline and empty in the
  headers (`decl_overrides` on `Compression` and `CompressionRefpack`), and the object is constructed where the slice
  stored its vptr (after `bool r = false;`): declaration order changes the instruction order.
- `PFRecordInfo e;` followed by five zero stores is the inline constructor `PFRecordInfo e(0,0,0,0,false)`.
- The record map's `find` result must be compared as a temporary (`find(key) == end()`); a named iterator variable makes VC9
  compare through the stack slot instead of `[eax]`.
- `Manager`'s retail vtable has three slots in front of dev slot 13 (`RegisterDatabase` is slot 20, not 17): `vtable_insert`
  in `layout_overrides.json`. The pairing of retail and dev vtable slots by index is only valid when the counts agree.
- Generator bugs found and fixed: `EASTLCoreAllocator` was laid out at 0xc (leaf-table sizes are ignored for types the PDB
  has) so every generated offset comment after a container was a word high; classes with dev functions in the object but
  no retail-named function (`PFRecordWrite`) were skipped; the closure did not follow nested classes or the members of
  one-hop pointees (`Manager`, `AtomicPointer`, `Cache`); template bases did not pull in their argument headers; function
  pointer members were declared as `void (*)() name;`; nested sibling classes were not forward-declared; `FixedAllocator`
  has a hand template now (`EA/Allocator/FixedAllocator.h`, 0x20 bytes, unverified in retail).
- `run_all.py` object names broke on `/` inside a flag (`/Isrc/game/include`): fixed.

**Not done by the tool (next agents):** constructors/destructors with real bodies (they are matched by arity but the
member-initialiser rewrite is manual), functions of rbtree/hashtable instantiations (`RecMap::erase`, `insert`: library
templates, stay in the slice), functions without a dev method (add them to the class with `extra_methods` in
`layout_overrides.json`: `{"decl": "bool Foo(int)", "va": "006bc2d0", "evidence": "..."}`, regenerate, then `methods`
{va: "Foo"}), slices whose struct views use other struct names for the same member (add `members` / `class_map`).


### 7a. SPEngine/SPPropertyHelpers.obj (s0041e730, s0069f950, s006a11b0): namespace-function slices

Result: 15/15 byte-exact in `src/game/SPEngine/SPPropertyHelpers.cpp` (s0069f950: 0x6a0920, 0x6a10c0, 0x6a1110, 0x6a1160; s006a11b0:
0x6a11b0..0x6a1490, eleven `SP::GetPropertyAs*`); s0041e730 contributes nothing (its only SPPropertyHelpers function, 0x41e920, is a
wrong xmatch anchor: manual `exclude`). Rules this module added to `rewrite.py` / the header generator:
- a definition qualified by a namespace (`bool SP::GetPropertyAsKey(...)`, no struct of that name in the slice or the dev types) is a
  namespace function like an unqualified one; its declaration is the dev public. A function without a modmap `dev` link takes the one
  same-named namespace function of the dev object file, or the manual `methods` entry `{va: "SP::Name"}` (`Data.free_decls_of`).
- manual `exclude` `{va: why}`: the function stays in the slice (modmap's module assignment is contradicted by the slice).
- struct mapping from namespace-function signatures (`map_from_function_signatures`: `cSPColorRGB* out` <-> the dev public's
  `cSPColorRGB *`), tolerant of the slice spelling a struct with its namespace (`EA::Variant`, `eastl::basic_string8`), of the
  demangler's `basic_string<char, eastl::allocator>` spacing, and of locals typed with a qualified name (`base_type` drops the qualifier
  of a name the slice itself defines; `convert_types` replaces the qualified spelling).
- union members: several canonical nodes at one (offset, size) are told apart by leaf-name similarity plus whether the canonical
  parent struct holds the slice's other members (`mpData/mnItemSize/mnItemCount` -> `mPointer.*`, not `mInt32`); `Canon` now reads the
  members of anonymous unions.
- an out-parameter `&p` for a canonical `T const **` parameter retypes the local to `T const *` (the const `GetProperty` overload).
- the slice's prototypes of the namespace functions the TU defines are dropped; `merge_preamble` compared `#include` lines after
  `mask()` blanked their file names, so no include of a later slice was ever added (fixed: includes compare by text).
- headers: classes named by a module's namespace-function signatures get headers (`signature_classes`), unscoped PDB classes are
  forward-declared in signatures, `rw::math::fpu::Vector{2,3,4}Template`/`Matrix33Template` are a hand header
  (`rw/math/fpu/VectorTemplates.h`), `SP::cString` is 0x14 in retail (override `remove`), and `EA::Variant` has nine retail-only typed
  accessors (`GetVector2/3/4`, `GetColorRGB/RGBA`, `GetKey`, `GetText`, `GetString8/16`, retail 0x6a0f70, 0xcce910, 0x6a0fa0, 0x6a0fd0,
  0x6a1000, 0x6a1030, 0x6a1090, 0x60ebf0, 0x68a4f0) as `extra_methods`.
Kept as a slice-local item: `cStringSet(const void*, cString*)` (retail 0x6b56d0, unnamed).

## 8. SPEngine/SPPropertyList.obj (s00612270, s006a11b0, s006a22a0, s006a7e40): what it added to the tool

Rules (all in `rewrite.py` / `rewrite_stubs.py` / `headers.py`; evidence in the code):
- `parse_preamble` descends into `namespace X { ... }` blocks: every inner declaration becomes its own item wrapped in its namespaces and every class gets `.ns`, so classes inside namespaces are slice structs (member maps, slot maps) and each declaration can be kept or dropped alone. `needed_items` matches qualified spellings (`EA::IO::WriteUint32`); an item defining a class/template with a canonical header (`EA::Variant`, `SP::cPropertyList`, `EA::Thread::AtomicInt`) is not emitted, the header is included, also for verbatim functions when a header the TU includes already defines the class.
- Member map: `sliceviews.json` offsets can be null (template members, unknown bases): the slice's `// +0xNN` comments and the distance to the next member give them. A slice scalar over a canonical 1-byte struct (`unsigned char mCompare` over `less<unsigned>`) becomes a typed view `(*(unsigned char *)&mPropertyMap.mCompare)`; `norm_type` treats `int*` and `int *` alike.
- Methods: virtual slot comments `// 12 (0x30)`; declared-only methods of classes the slice also defines methods of (`Clear`, `v12`, `GetPropertyValue`) are mapped by slot; calls are looked up through the slice's base classes; qualified base calls (`cPropertyList::GetPropertyA(..)`) are renamed; overloads that differ in constness are told apart by the slice definition's constness. Pointer-vs-reference: a slice method returning `T*` where the canonical one returns `T const &` -> calls become `((T *)&Call())`, `return &x;` -> `return x;`, `return p;` -> `return *(p);`; `&it->second` -> `it->second` for reference parameters.
- Constructors: the member-initialiser list is part of the body (not the signature); a base initialiser the canonical base constructors do not take is called with its default constructor; `a.b(0)` on a by-value pointer wrapper (AutoRefCount) becomes `a()`.
- `compile_symbols` binds overloads by parameter list + constness. Library template instantiations (`eastl::lower_bound<..>`) are never made into namespace functions.
- `headers.py`: VC9 reverses the slot order of an overload set (see Papercuts); the generator emits each contiguous same-name run of new virtuals in descending slot order.
- Debug aid: `RW_KEEP_DIFF=<va,...>` keeps a byte-inexact function in the TU/manifest so `run_all` + `cmpdis.py` can show the diff.
Header overrides: inline bodies for `Key()`, `Resource()`, `cResourceBase()`, `IUnknown32()`, `IRefCount()`, `Variant()`, `~Variant()`, the copy constructor of `Variant` (layout_overrides.json, each with evidence); hand templates: `AtomicInt` constructor (`xchg`), `vector_map` constructor (zeroes begin/end/capacity only) and `erase` (0x6a2cb0).

## 9. SPEngine/SPPropertyManager.obj (s006a32a0 .. s006aa3f0, nine slices): what it added to the tool

The module's slices are mostly *not* class methods: free functions, library instantiations, functions of module-local classes
(`cAppPropsCommand`, `cListPropsCheat`, the `Vec*` constructors) and stubs, written against slice-private stubs of `Variant`,
`eastl::string`, `cPropertyManager`, ... Result: 19 byte-exact rows (all MATCH, two flag sets; 0x6a39a0 was an equivalent row in the slice and is exact now), 23 nonmatching rows
with the same equiv verdict class as in the slice, 30 partial rows carried over; 72 functions in `src/game/SPEngine/SPPropertyManager.cpp`
of which 5 are converted to canonical `SP::cPropertyManager` methods (`GetSupportedTypes`, `GetPropertyGroupCount`, `GetPropertyGroupID`,
`PreloadPropertyLists`, `Shutdown`) and 67 keep the slice's text ("verbatim").
Rules (`rewrite.py` / `rewrite_stubs.py`; `rewrite.py <slice> --module SPPropertyManager --scratch <dir> [--apply]`, slices in VA order):
- **Unmarked functions get a marker**: `insert_missing_markers` finds every top-level function definition without `// @ 0xVA` and takes the
  VA from `FUN_<8 hex>` in the name, else from the slice manifest's decorated symbol (class, name), else from a `// 006a3400 ...` banner
  above it (only VAs the slice has rows for). The slice's own `sNNNN.h` is expanded in place; its `types.h` includes are dropped.
- **Whatever follows a function is preamble**: the text after a closing brace (structs, typedefs, statics, macros with `\` continuations
  - kind `define`, function-pointer globals) goes to the slice preamble; `needed_items` emits the items the emitted functions use,
  transitively, in slice order, inside `// ---- items of slice X begin/end` blocks (a re-run of the slice replaces its own block).
  A retail address comment after a wrapped namespace declaration stays on the declaration (difftest binds callees by it).
- **Verbatim fallback**: a function with no canonical declaration (no class, a namespace function in an anonymous namespace, an
  unmatched method) keeps signature and body; its local stub types are emitted. Nothing is "unmapped": `skipped` is only for other
  modules.
- **Checked apply** (`apply_checked`): write the TU, compile, read the decorated symbols, write the bookkeeping, run `run_all` on this
  slice's rows (waits for `work/run_all.lock`, never kills). Compiler errors are attributed to functions by line: a converted body that
  fails is demoted to verbatim, a verbatim one that fails (or a converted/verbatim function that was byte-exact in the slice and DIFFs now)
  is dropped and stays in the slice; a redefinition error in the preamble renames the stub instead. The TU and the bookkeeping files are
  restored when nothing works, so a failing slice never leaves a TU that does not compile.
- **Stub name conflicts**: slices invent different bodies for the same stub name; a stub the module TU already defines differently, one a
  header the TU includes defines (`SP::cString` with the slice's `GetText()`, `EA::ArgScript::cArguments` with `const char**`), or one the
  compiler reports as redefined is renamed `Name_sNNNN_NNNN` (the slice's id split in two: a 6-8 hex digit run in a symbol is read by the difftest
  resolver as an address) in that slice only; converted functions keep the canonical class.
- Flags: manifest rows without a flags column compile with run_all's defaults (`/O2 /MD /Gy /EHsc /TP`), the migrated rows spell
  them; nonmatching rows are measured and promoted with `slice.choose_flags` (what equiv uses). A nonmatching row that is byte-exact in
  the module TU moves to `manifest.txt` (0x6a39a0 `GetPropertyGroupCount`).
- `item_names`: function-pointer globals (`bool (*g_pParse)(..) = &Parse;`, a link-time reference the slice keeps) are named by the
  pointer, so they are not emitted unless used; `canonical_item_header` only claims a header that declares the class (`eastl/string.h`
  exists but has no `eastl::string`).
- `layout_overrides.json` `SP::cPropertyManager`: four insertions (retail 0x1ec, see Papercuts); the generated header now agrees with
  every exact-backed view and the VC9 probe (mPropertyNameToIDMap 0x94 ... mLCName 0x168, mFileParser 0x178, mInAppProperties 0x1e8).
Left in the slices (other modules or none): 0x6a32a0 `cExprFunction::EvalBool` (SPAppStateManager), 0x6a32c0 FNV helper (no module),
0x6a8340 / 0x6a8410 `hash_map::operator[]` instantiations (no module), 0x6a84f0 (SPPropertyList), 0x6a85b0 (SPAppStateManager), 0x6aae30
`~rbtree` (no module). Not converted (header work): `RegisterPropertyName/Local` need `hash_map::operator[]` and an inline
`basic_string::assign(const T*)` in the hand-written eastl headers; `Init`/`WriteResource` need the retail rbtree member typed and
`Record`/`Resource` complete in the TU; `CreateResource` is a stub body.

## 8. `UTFSpore_Win32/DatabasePackedFile.obj`, slices 2-8 (2026-10-12)

Order run: s006bb1c0, s006bc1b0, s006bd150, s006bde30, s008d7220, s008d91e0, s008da140, s008daff0 (`rewrite.py <slice> --module
DatabasePackedFile.obj --apply`; the substring `DatabasePackedFile.obj` keeps `DatabasePackedFileIndex.obj` out). Module result:
`.venv/bin/python tools/matching/run_all.py --manifest src/game/UTFSpore_Win32/DatabasePackedFile/manifest.txt` = 40/40 MATCH
(21 of s008d81d0 plus 19 new rows), 98 functions in the TU. Equiv verdicts of every nonmatching/partial row of s008d81d0/s008d91e0/s008da140/s008daff0
re-measured against the slice's own: none worse except the partial row 0x8da920 (UNSUPPORTED -> FAIL: the unresolved `_ReadRecordRaw` now
resolves, so the approximate body is finally executed); 0x8d85a0 Attach FAIL -> PASS, 0x6bbe20 and 0x8d81a0 AsInterface PASS -> byte-exact.

**Two copies of the packed-file code (read Papercuts "DatabasePackedFile.obj migration").** 0x6bb1c0..0x6bf4xx is a sibling class (64-bit
variant, FileStream 0x434 at +0x30, mutexes 0x478/0x4a8, 28-slot vtable 0x140a154), not `EA::ResourceMan::DatabasePackedFile` (0x388, vtable
0x14367b0, secondary 0x143679c). s006bc1b0, s006bd150 and the DatabasePackedFile functions of s006bde30 (0x6bde30 OpenRecord, 0x6be1d0) are that class:
they stay in their slices (23 + 7 + 2 functions, listed in `rewrite_<slice>_DatabasePackedFileobj.json` `functions_left_in_slice`). `0x6bbe20` AsInterface (id 0x6492c5f) also stays; the class's own AsInterface is 0x8d81a0 (it lands from s008d7220,
where the slice calls it `DatabaseDirectoryFiles::Cast`). 0x6bbdd0 `Init` is shared by both vtables and landed.

**Rules added to `rewrite.py` / `rewrite_stubs.py` / `headers.py` (evidence is in the code comments):**
- slice parsing: marker lines with a description (`// @ 0x006bb820  release stg medium member`), declarations between a marker and its function
  hoisted to the preamble, a marker over declarations only, markers above banner comments are not re-inserted, a sibling slice's header
  (`#include "../s006bc1b0/s006bc1b0.h"`), function-pointer typedefs with the calling convention first (`item_names`), `~Cls` after `::` is not a
  use of the slice's stub `Cls`, the text after a function stops at the next banner / `remaining functions`.
- class evidence: `refuse_foreign_layouts` (a function-name mapping whose slice view puts same-named members > 0x10 from the canonical offsets
  is dropped, and the functions of that class stay in the slice, `build`); a chunk the module map gives no dev function is owned by the class whose
  generated header declares its VA (`header_owners`, 0x8d81a0); a slice method address unnamed in pdb_names resolves through the headers
  (`Refpack::CompressData` 0x92c9f0 -> `EA::CompressionRefpack`); callee names from functions already in the module TUs (`tu_methods`:
  `Sync` 0x8d8b30 is `CloseOpenRecords`); an address contradiction (same name, the header puts the method at another VA) holds the function back.
- bodies: `secondary_this` (virtual of a secondary base: `(char*)this - K` -> `this`, subobject `this` / null-masked upcast ->
  `static_cast<Base*>(this)`), one-line struct accessors inlined (`HoleA()` -> `mActive.mHoles`, then mapped), function-local `typedef ... (__thiscall *Fn)`
  thunks, constructor/destructor `vtN = vtbl_X;` stores dropped, `void *` arguments cast to typed pointer parameters, prototypes without `extern`
  whose address is a static method of a canonical class (`GetDefaultAllocator` 0x925cb0 -> `EA::Allocator::ICoreAllocator::GetDefaultAllocator`).
- output: externs used by local stubs' inline bodies are declared (before the stubs), a verbatim function keeps the slice's extern spelling,
  stub methods get the `// 0xVA` of their definition in this slice (the resolver binds calls from verbatim functions), the collision rename is
  `Name_sNNNN_NNNN`, constructors of a renamed stub are renamed too, overload binding by parameter count, stale blocks/rows/names lines of functions a
  rerun no longer emits are pruned (the symbol-names line falls back to git's), nonmatching rows that match are promoted to the manifest.
- headers: `retail_vtable` accepts a list with `"for": "<base class>"` (DatabasePackedFile secondary vtable 0x143679c: AddRef 0x8dd1b0, Release 0x69d3c0,
  dtor adjustor 0x8d9490, AsInterface 0x8d81a0), `mutable` member list (DatabasePackedFile::mMutex), `EA::COM::AutoRefCount::operator=`.

**Landed as verbatim stubs (not converted, slice spelling kept, TODO(rewrite) stubs in the TU):** 0x8d93e0 `~DatabasePackedFile` (the canonical
destructor needs the member destructors of the hand-written headers: DIFF 18 bytes), 0x8d9560 GetOpenCount and 0x8d9a10 CloseRecord (multimap
`find` iterator idiom + `RBTreeIncrement`), 0x8d95f0 WriteIndexRecord, 0x8d9770 InitializeHoleTable (`PFHoleTable::Insert`/`FUN_008dc120` names), 0x8d9f80 constructor
(member-initialiser list with `FileStream(0)` ambiguous between the char/wchar_t constructors, `HoleTable(0x13, ratio)` = two members + `mActiveHoleTable`),
0x8da140 CompactDatabaseInternal, 0x8da3d0 OpenRecord, 0x8daba0 Flush (`HoleSet::FUN_008dc120`), the three RecMap instantiations (0x8d93a0 erase, 0x8d98f0 DoInsertValue,
0x8d9f20 insert), and all of s008daff0 (PFIndexModifiable 0x8db.. copy, HoleSet/rbtree/hash instantiations, sort helpers: no canonical class for the 0x8d copy of
PFIndexModifiable; the Index module's class is keyed on the 0x6b copy). Converted from these slices: CompressData 0x8d91e0, DecompressRecord 0x8d9320, CloseInternal 0x8d94a0, ShouldRecordBeCompressed(5) 0x8d9850,
SetLocation 0x8d99c0, ReadIndexRecord 0x8da750, CompactDatabase 0x8da8b0, AsInterface 0x8d81a0, Init 0x6bbdd0 (43 converted, 55 verbatim in the TU).
