# Migration pilot runbook: slices → `src/game/`, step by step

Written 2026-10-12 for Sonnet 5.5 agents running in a workflow (`.claude/workflows/migration-pilot.js`).
Everything here was verified in the session that wrote it; where a fact is a guess it says so.
Read `docs/migration.md` first for the design and the measurements, then this file for the exact
procedure. Steps 1 and 2 of the pipeline (module map, headers) are done; this runbook is step 3
(`rewrite.py` + the pilot slices) and step 4 (`gate.py`).

## 0. Ground rules for every agent

- Repo: `/Users/noahpeterson/Documents/Projects/spore-decomp`, branch `main`. Never commit. Never
  run anything in the background. Search with `rg`. Scratch files go under the scratchpad directory
  named in your prompt, never in `work/batches/`.
- The machine is shared with a DeepSeek worker: no multi-process fan-out, one compile loop at a time.
  `run_all.py` takes a lock (`work/run_all.lock`); if it is held, wait, do not kill anything.
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
- Byte-exact verification: `python3 tools/matching/run_all.py --manifest <file> -v`. Manifest rows
  are `source symbol va flags` where **`source` is relative to `match/`**, so a TU under `src/game/`
  is written `../src/game/UTFSpore_Win32/DatabasePackedFile.cpp`. Flags are the slice's flags plus
  `/Isrc/game/include` (relative `/I` paths are resolved against the repo root by `resolve_flags`).
  The symbol column is the decorated name; `run_all` also accepts a unique substring. Output:
  per-row `MATCH`/`DIFF n bytes`/`COMPILE FAIL`; exit 0 only when every row matches.
- Equivalence of non-exact functions: `tools/difftest/equiv.py` (read its docstring for the CLI;
  `tools/difftest/batch.py` runs a shard spec; the slice's `nonmatching.txt` rows record the
  previous verdict, e.g. "difftest WEAK (211 valid...)" or "PASS 400/400"). The acceptance rule is
  verdict class not worse than before; `UNSUPPORTED` after `PASS` is a regression to fix.

## 3. `tools/migrate/rewrite.py`: what to build

Usage to implement: `rewrite.py <slice-id> [--apply] [--module SUBSTR]`. Without `--apply` it prints
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
| `HoleSet::{Reset, AddHole, Alloc, GetTotalSize, mField0}` | `PFHoleTable::{Reset(uint), Free(long,uint), Allocate(uint), GetBytesFree(), mExtent}` | retail 0x8db3a0 / 0x8dc000 / 0x8dbf20 / 0x8dae40 are unnamed in pdb_names: name them in the TU comments |
| `mpManager` (uint32) | `mpManager` (`Manager*`) | the `(void*)mgr` casts go away |
| `Index` | `EA::ResourceMan::PFIndex` | slots 1 IsModifiable, 3 GetSize, 7 GetKeyList, 8 GetKeysSortedByPosition, 10 FindRecord, 12 DeleteRecord(key, info&) ("GetEntry"), 13 ReadFromMemory ("Op34"), 14 WriteToMemory ("Serialize"), 16 ValidateFreeSpace ("VerifyRange"); slot 4 (`Op10`) is `Clear` |
| `IStream` | `EA::IO::IStream` | slots per `src/game/include/EA/IO/IStream.h` (named from FileStream) |
| `IAlloc` | `EA::Allocator::ICoreAllocator` | slots 2 Alloc, 3 Free |
| `Refpack` | `EA::CompressionRefpack` | `IsValidHeader` = `ValidateCompressedData` (0x92cad0), `DecompressData` (0x92ca60) |
| `Mutex::Lock/Unlock` | `EA::Thread::Mutex::Lock(const ThreadTime&)`/`Unlock()` | 0x9221b0 / 0x922270; `kTimeoutNone` (0x1436788) is the `EA::Thread::kTimeoutNone` constant, unnamed in pdb_globals |
| `ICoreAllocator_Alloc_Named(size, alloc, name)` + `p->Init(...)` | `EA::Allocator::ZoneObject::operator new(size, alloc, name)` (0x925fe0) then the constructor | keep the explicit two-step form for byte-exactness: `void* mem = ZoneObject::operator new(0x27c, mpAllocator, "Resource/PFRecordWrite"); if (mem) return new (mem) PFRecordWrite(a, b, c, this);` with a placement `operator new(size_t, void*)` declared in `game/types.h`; `PFRecordWrite::Init` (0x8dcea0) and `InitData` (0x8dd0d0) are the two constructors, `PFRecordRead::Init/Init2` (0x8dcc80/0x8dcdc0) likewise, `PFIndexModifiable::Init` (0x8db730) its constructor |
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

1. **Tool + first slice.** Build `rewrite.py` (§3) against `s008d81d0`; iterate until
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
   (`SCENE_MIN=6`), optionally `--coverage` once. Only one hybrid build/boot at a time on this
   machine; never leave the game window open. A failing boot is debugged from the fault address
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
- `PFHoleTable`'s four retail methods are unnamed in `pdb_names.json`; after the first slice lands,
  add them to `symbols/slices/s008d81d0.txt`-style name files so the difftest resolver binds them.
- `EA::Thread::kTimeoutNone` (0x1436788) and the Refpack vtable (0x140a0e8) are unnamed globals;
  `globals.h` generation (design §2) is not written yet; keep the slice's `extern` lines with
  addresses until it is.
