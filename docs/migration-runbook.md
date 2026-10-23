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
| `src/game/include/**` | generated class headers + hand-written template headers | `python3 tools/migrate/headers.py --module-substr DatabasePackedFile` and `--module-substr SPProperty` (2 s each); one object: `--module <ObjStem>` (exact since fix pass 3) |
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

## 8. Round structure from round 2 on (2026-10-12, after round 1)

Round 1 ran six module agents at once and it worked, but three things were shared by writers: `rewrite.py`
(one agent edited it while five ran it), the header tree (a layout override ripples into every TU), and
`run_all` (fixed: it now waits for its lock). A round is therefore:

1. **Freeze.** `tools/migrate/rewrite.py`, `headers.py`, `layout_overrides.json` and every file under
   `src/game/include/` are read-only for the landing agents. Nothing in the fan-out edits them.
2. **Fan out, one agent per object file**, slices of the object in VA order. Per slice the mechanical
   protocol is §8a. A landing agent may write only: the object's TU and bookkeeping files under
   `src/game/<dir>/<obj>/`, `work/migrate/renames_<slice>.json` (`manual` section), `symbols/slices/<slice>.txt`,
   its scratchpad, and its report. Anything else it needs becomes a **request** in the report (rule for the
   tool, header evidence, modmap correction), never an edit.
3. **Verify in the foreground.** `run_all --manifest` then `equiv.py` on the nonmatching rows, as normal
   commands with a timeout (a module's equiv batch takes 3-4 minutes; the Bash limit is 10). Do not start
   them in the background and poll: a workflow agent cannot idle until a background task finishes, so the
   polling burns its turns.
4. **Fix pass (one agent, or me):** apply the requests: rules into `rewrite.py` (with the slice that needed
   them as the test), overrides into `layout_overrides.json` with evidence, regenerate headers, re-run every
   touched manifest, re-run the slices whose plan changed (`rewrite.py <slice> --apply` is idempotent for a
   TU that only holds that slice's functions; otherwise merge in VA order).
5. **Gate:** `tools/hybrid/build.py --hook-manifest` on the PASS rows (and only PASS rows until ticket M1 in
   `docs/tickets.md` is fixed), two boots, `SCENE_MIN=6`, no game window left open.

### 8a. Landing a slice: the mechanical protocol (written so a smaller model can follow it)

Inputs: `<slice>`, `<module>` (e.g. `UTFSpore_Win32/DatabasePackedFile`), the module's manifest dir
`src/game/<module>/`. Interpreter: `.venv/bin/python` for `run_all`, `equiv`, `cmpdis`; `python3` is fine for
`rewrite.py`.

1. `python3 tools/migrate/rewrite.py <slice> --module <ObjStem>` (plan). Read the printed plan and
   `work/migrate/renames_<slice>.json` `auto`: every function with `unmapped`/`demoted` notes needs either a
   `manual` entry (`methods`, `method_names`, `members`, `class_map`, `exclude`, `edits`, each with a `why`) or
   is left verbatim. Do not touch `auto`.
2. `python3 tools/migrate/rewrite.py <slice> --module <ObjStem> --apply`.
3. `.venv/bin/python tools/matching/run_all.py --manifest src/game/<module>/manifest.txt -v`. Every row must
   print MATCH. A DIFF: run `.venv/bin/python tools/matching/cmpdis.py` on that VA (docs/matching.md), write
   the first differing instruction and the member/slot it touches into the report as a header request, and
   revert the slice (`git checkout -- src/game/<module>/` if the TU only had this slice's functions; else
   add the DIFF rows to `manual` `leave_in_slice` {va: why} in the renames file and re-apply). Never edit a header; never
   change a function body's logic to make bytes match.
4. `.venv/bin/python tools/difftest/equiv.py <slice> <va...> --src src/game/<module>.cpp --flags "<slice flags> /Isrc/game/include"`
   for every row in the module's `nonmatching.txt` and `partial.txt` that came from this slice. Verdict class
   must not get worse (PASS > WEAK > FAIL > UNSUPPORTED); a regression means a `manual` `leave_in_slice` {va: why} entry for that row (re-apply) and a
   report line with both verdicts.
5. Report (per slice): rows MATCH/DIFF, verdict before -> after per nonmatching row, functions left in the
   slice and why, manual entries added, requests (tool rule / header evidence / modmap) with the evidence.

What a landing agent must NOT do: edit `rewrite.py`, `headers.py`, `layout_overrides.json`, anything under
`src/game/include/` or `match/slices/`; commit; run anything in the background; kill a compile.

### 8b. Open header-owner items for round 2

- `PFIndexModifiable_v2` and `PFHoleTable_v2` for the second family: two slice views disagree
  (`s006bc1b0` says 0x4c with 6 members, `s006bfda0` says 0x34); the byte-exact users decide. Generate with
  `tools/migrate/retail_class_header.py` once the view is chosen.
- Move the ten 0x6b-family functions out of `DatabasePackedFile.cpp` into `DatabasePackedFile_v2.cpp`
  (`rewrite.py s006bb1c0 --module DatabasePackedFile_v2 --apply` after the class_map points at the `_v2` header).
- `SP::cDirectPropertyList` (0x40 vs 0x54) and `SP::cPropertyManager` overrides (§6) are still open.
- Virtual slot signatures in `DatabasePackedFile_v2.h` are `void()` placeholders; each migrated caller fixes
  the slot it calls (evidence: the call's argument pushes).
- `EA/SharedLibrary.h` and `EA/SharedLibraryRegistry.h` (generated 2026-10-12 for a round-2 candidate) do not
  compile standalone: they use `eastl::pair` outside a map and the generator's include closure only brings
  `eastl/map.h` in for map/multimap members. Fix in `headers.py` (a `pair` family include), then
  `EASharedLibrary.obj` (26 functions, 3 slices) is landable.

### 8c. Fix pass after round 2 (2026-10-13): what changed for landing agents

- `rewrite.py --scratch` defaults to `work/migrate/scratch_<slice>`. The module's three bookkeeping files only ever hold
  rows of functions the module TU defines, one row per function (manifest > nonmatching > partial): a function left in
  the slice (`leave_in_slice`, `exclude`, a DIFF held back) gets **no** row; do not add one by hand. `opencode_drain.py`
  counts the VAs of the renames file's `leave_in_slice`/`exclude` as settled.
- New tool rules (each tested on the slice named in the code): `extern "C" { ... }` blocks are split per declaration;
  the callee name skips `__declspec(...)` and keywords; an extern goes before the slice's typedefs only when a stub's
  inline body needs it and it names no slice struct/typedef/macro (`va_list` users go after `<stdarg.h>`); a converted
  variadic body gets the slice's `<stdarg.h>`; `va_list ap` last parameter vs canonical `...` -> `va_start` in the body;
  a `void *` slice parameter/member with a typed canonical pointer gets a cast on assignment; an integer slice parameter
  with a canonical pointer type gets a local integer copy; a free `__cdecl` function with an explicit `Cls* pThis` whose dev
  function is a `__cdecl` method becomes that method; manual `methods` accepts a canonical method with more parameters
  than the slice stub (named `a<n>`); duplicate `#include`s are dropped; compiler errors are attributed case-insensitively.
- A retail function that ends `call [vtbl+N] / pop / ret` with no `al` write after the call is not `void`: the callee's
  bool passes through in `al` (XmlTextWriter::WriteName 0x901930: the header keeps `bool`, the body `return WriteText(..)`).
  Check the callers (`test al,al` after the call) before asking for a `void` override.
- Headers: a member whose type is a template no hand header defines is emitted as an opaque byte array of its retail size
  (a pointer as `void*`) with the type in a comment; a method whose signature cannot be declared (file-local type, a
  reference to another class's nested type, an undefined template) is a comment, or `virtual void slot_N_Name();` for a
  virtual (slot order kept). New hand templates: `EA/RefCountVTemplate.h`, `EA/RefCountTemplate.h`,
  `EA/COM/RefCountTemplate.h`, `eastl/deque.h`, `EA/ArgScript/cCommandStateT.h`, `EA/Messaging/MessageBasic.h`,
  `EA/RectT.h`, `SP/cRwResource.h` (all unverified in retail: the first byte-exact user confirms them); `eastl::pair`
  comes from `eastl/map.h`. Every nested enum of a class is emitted; anonymous PDB enums are emitted unnamed; a closure
  class gets its owner module's retail addresses (headers no longer depend on which module's run wrote them last).
- Round 3 objects whose headers compile standalone: `work/claude/round3_ready.json` (11); not ready (rw templates):
  `work/claude/round3_not_ready.json`.

### 8d. Fix pass 2 (2026-10-13, after the round-2 landings): what changed for landing agents

All eight round-2 objects were re-landed from scratch with the rules below (`rewrite.py <slice> --module <ObjStem> --apply`,
slices in batch order, module TU and bookkeeping deleted first): 268 of the 271 batch functions are in the TUs (round 2: 181),
every manifest row MATCH, byte-exact rows per module at least the slices' count except INetFileCache (18 of 19: the library
instantiation `eastl::operator==<char>` 0x555020 stays in s00554c30, `leave_in_slice` with the reason).

- **Run with `--batch mig2`** (or the round's batch): functions of the slice that the batch does not list for the module stay in
  the slice without hand-written `leave_in_slice` rows (manual entries still win).
- Slice parsing: a legend of consecutive `// @ 0x` lines is one boundary (s00688dd0); every leading declaration between a marker
  and its function is hoisted (several lines, `static const` tables, class/union/template-class definitions, `#define`s;
  s007ada40, s007aea30); a leading `#pragma` stays with its function; a class with several bases is a struct item named after
  itself (s007ada40 DxtSurface); a function template in a namespace is not a class item (s004e01d0); an explicit instantiation
  under the marker of its template (`template void eastl::vector<..>::reserve(uint32_t);`, s004e01d0 0x4e0880) is emitted after
  the definition; `Job& Job::operator=(...)` is a method named `operator=` (s00942ff0 0x9436b0).
- Verbatim functions keep their scope: one the slice defined inside `namespace X {` is emitted inside it (s00947d50), a method of a
  namespaced stub defined at global scope gets the qualifier (s00942290; `using namespace` items are no longer emitted), and the
  class may carry the `_sNNNN_NNNN` rename. Renamed stub constructors/destructors keep matching names after a demotion.
- Stubs of a class that has ANY canonical header (also a typedef such as `eastl::string8` in `eastl/string.h`) are renamed for the
  verbatim functions, so a later slice may include the header (Expression: round 2 hand-edited the TU for this).
- Prototypes: one function declared twice with different linkage (`extern "C"` vs C++), `dllimport`, parameter names or return
  type is emitted once (the module TU's declaration; a `dllimport` spelling replaces a plain one); a `throw()` difference keeps
  both (codegen depends on it, see Papercuts). Intrinsics (`_Interlocked*`) declared by the slice are dropped when `<intrin.h>` is
  in the TU. A stub's inline body that calls a free function of the slice gets that function's prototype (s00942ff0 JobVecBlob).
  Free operators used through operator syntax (`name == "pi"`, s0083d3d0/e1c0/f140) and the `operator new` a kept stub's body
  uses (s007e4260) are emitted.
- Converted bodies: compile-error repairs before demotion: an int returned/assigned where the canonical type is an enum gets the
  enum cast (s0083a9f0 tArgError, s00942290 JobResult); a pointer argument where the callee takes a pointer to it (or the
  reverse) after a slice `T**` parameter became `T*&` gets `&`/`*` (s0083e1c0 DiscardWhiteSpace). Function-pointer parameters
  are named inside the declarator (s0068f670 ContinueJob, s009413d0 SetNotificationTarget). A slice struct mapped to a canonical
  class without a generated header keeps its stub (s00947d50 IniFile).
- Implicit special members the slice lists as `// @ 0xVA  S copy constructor (implicit)` (copy assignment, destructor) get a
  forcing function under `#pragma auto_inline(off)` (s00942290 Cookie40: 0x942ce0/0x942d70 byte-exact); rows bind to the
  member's own name. A function without a row in its slice's bookkeeping takes the row another slice has (s006907e0 0x68f950);
  a C-linkage manifest symbol (`_FUN_0068a2e0`) binds. A run that emits nothing prunes its old blocks (s004e01d0).
- New `manual` keys: `edits` entries with `"verbatim": true` apply to the slice text of a verbatim function (s00948de0 0x949620);
  `pragmas` {va: {lead, after, why}} puts preprocessor lines around one function (s0083e1c0 0x83e9d0 `#pragma inline_depth(0)`).
- Headers (`layout_overrides.json`, each with its evidence): `EA::Internet::HTTPClient` without msUserName/msUserPassword (0x168),
  `SP::cJobManager` with the lock-depth int at 0x38 and the 0x2c-byte retail block after mThreads (0x1e4), `EA::Internet::INetFileCache`
  with the open-stream list at 0x28 (mDataMap 0x34). A `remove` now moves the later members up. `eastl/string.h` declares
  `append(p, e)`, `assign(p)`, `sprintf`; `eastl/map.h` has `unary_function`/`binary_function`. A class's header lists the
  retail functions of every module (not only the writing run's), except functions moved to a synthetic object (`_v2`).
- Round 4 objects whose headers compile standalone: `work/claude/round4_ready.json` (8); not ready: `work/claude/round4_not_ready.json`.

### 8e. Fix pass 3 (2026-10-13, after the round-3 landings): what changed

- **`headers.py --module` is exact** (fix pass 3): `--module Manager` is `UTFSpore_Win32/Manager.obj` only (stem, `stem.obj` or
  `dir/stem`, case-insensitive). `--module-substr X` is the old substring behaviour (the pilot sets: `--module-substr
  DatabasePackedFile`, `--module-substr SPProperty`). `rewrite.py --module` is unchanged (still a substring).
- **`opencode_drain.py --max-nudges N`** (default 3): a range that would get a further nudge is logged `ABANDONED r<k> <sid> ...
  unsettled: <slice>:<va> ...` and counted as done; a restart re-reads nudge counts and abandoned ranges from the drain log.
- **`opencode_drain.py --stall S`** (default 7200, added 2026-10-16): an unfinished range whose settled-function count has
  not moved for S seconds is interrupted, logged `STALLED` + `ABANDONED`, and counted as done, so one slow session cannot
  hold the drain (and whatever is queued behind it) open all night. Round 5's ealog_imp session did exactly that.
- **Queue groups** (added 2026-10-21): a group file with `"queue": true, "workers": N` (no `"ranges"`) and
  `"prompt": "wave_prompt_queue.txt"` gives every session the whole batch as a shared queue: the session runs
  `tools/matching/claim.py <batch> <worker>`, which re-prints the slice it holds until all its VAs are in
  manifest/nonmatching/partial and then claims the next unclaimed slice in batch order (claims in
  `work/opencode/claims_<batch>.json`; `claim.py <batch> --status` lists them). `opencode_sup.py` and `opencode_drain.py`
  treat range k as worker k; a worker is done once the queue is empty and its slices are settled, and a worker that
  settles more functions after a nudge gets a fresh nudge count. Why: with fixed ranges gold4 had 28 sessions busy at
  23:00 and 5 at 03:00, because sessions with easy ranges stopped early. Build queue batches largest slice first, so
  the long slices start early and the short ones fill the gaps at the end.
- **Check every new batch's module make-up** (added 2026-10-23): `tools/module_progress.py --batch <batch>` lists each
  module's functions in the batch next to its unrecorded functions and marks a module with 100+ unrecorded functions
  and none offered. A substring filter on "SPGonzago" kept the whole game module out of gold2-gold5 unnoticed.
- Hand templates (all "Hand-maintained", layout from the dev PDB, sizes VC9-probed, unverified in retail):
  `rw/math/fpu/VectorTemplates.h` (+`Matrix44Template` 0x40, `QuaternionTemplate` 0x10), `rw/BaseResourceTemplates.h`
  (`BaseResourceDescriptors<4>` 0x20, `BaseResources<4>` 0x10, `BaseResourceDescriptorType<T>`), `rw/math/vpu/VecFloatRef.h` (4),
  `__m128.h` (= `<xmmintrin.h>`), `rw/HashContainer.h` (0xc), `rw/SimpleVector.h` (0x20), `SP/cEltArrayRefT.h` (0x10),
  `eastl/list.h` `intrusive_list_base` / `intrusive_list<T>` (8), `EA/Messaging/MessageBasicRC.h` (`MessageRC` 8,
  `EA::Messaging::MessageBasicRC<5>` 0x38, `SP::MessageBasicRC<5>` 0x40 with `mRCFlags` at 0x38). `game/typedefs.h` declares
  `nSPCreatureAnim::anim_handle_t`.
- Generator rules: anonymous unions are split into their alternatives (anonymous structs; a class-typed alternative is wrapped,
  which is how VC9 accepts checkerlib's `vector_3 rows[3]` in a union: C2621 otherwise); union membership is by byte overlap;
  the PDB's merged `__unnamed` records and file-local (`` `anonymous-namespace' ``) classes get no header (members opaque, own
  PDB size); a class-nested enum member pulls its owner's header (`SP/cBufferDraw.h`); enums inside template arguments and
  global-namespace enums get their headers; base-class enums keep their type in overrides (C2555); smart-pointer members
  (`AutoRefCount<T>`, `COM::AutoRefCount<T>`, `IntrusivePtr<T>`) forward-declare T instead of including it (include cycles:
  cBuilding -> cCity -> cBuildingCityHall); nested classes are emitted in by-value dependency order; an opaque member that holds
  an `__m128` keeps `__declspec(align(16))`; conversion operators with elaborated types; retail-only slice members with slice
  typedefs (`u8`) or slice-local types become C types / opaque bytes; an `insert` override with no `after` goes behind the bases.
- Overrides: `EA::Thread::Mutex` constructor default arguments (`= 0, = true`, retail 0x9368f0/0x8de8e0 `push 1; push 0; call
  0x9222a0`); `cSPUILayout` key at +8, collection at +0x14, size 0x18 (Init 0x8120d0, IsVisible 0x810070, ~cSPUILayout 0x811fe0).
- rewrite.py / rewrite_stubs.py rules: a declarator list `extern char a, b, c;` names every declarator (SPUILayout's vtbl_/DAT_
  globals); a `} }` closing a namespace opened before the first marker and namespace blocks of declarations are hoisted to the
  preamble (s00538e90); a slice without manifest.txt lands (s00ed74f0); `operator()(...)` and `` `anonymous namespace' `` in
  demangled arity; a function at the header's `dtor body` address is the destructor, one at a virtual destructor's slot-0
  address (the scalar deleting destructor) stays verbatim instead of being shape-guessed; converted bodies include the headers of
  every canonical class they name; a kept item's explicit `operator new[](n)` keeps the operator new declarations; a free function
  defined later in VA order than a caller gets a forward prototype (`forward_protos`); `--batch` also takes a VA the batch lists
  for the module under a slice whose bookkeeping has no row for it, when this slice has one (mig3 0x4f6510, 0x4f6720).

### 8f. Fix pass 4 (2026-10-14, after the round-4 landings): what changed

All 12 mig4 objects were re-landed from scratch in batch order with the rules below (`--batch mig4`), and EASharedLibrary
with `--batch mig3`: 387 of the 408 mig4 functions are in the TUs (round 4: 297), 213 byte-exact rows (round 4: 161; the
slices: 214, the missing one is 0x628340, whose modmap anchor is wrong), 21 held back (16 equiv regressions with a
`leave_in_slice` why, 4 SkinnerPaintRender bodies that need `nSPSkinner::cRTTBuffer::Setup/Set/Tri`, 1 `exclude`).
Every manifest under src/game is green (514 of 514 rows). Equiv was re-measured on every changed nonmatching row: no
verdict regression (0x741b10 FAIL -> UNSUPPORTED was put back in its slice).

- rewrite.py / rewrite_stubs.py rules (each names its test slice in the code): stubs a slice defines inside `namespace N`
  are qualified `N::` in global-scope items and verbatim functions that follow the slice's `using namespace N;` (s0059c4c0,
  s009ba4c0, s009b5ce0); the return type of a verbatim method defined at global scope is qualified (s0059c4c0); an explicit
  instantiation under its own marker is a chunk (`InstChunk`, s0059b4b0); a function this slice declares in a namespace that
  hides another slice's global overload is renamed (C2664 repair, s0059c4c0 RBTreeIncrement); a prototype the TU already
  declares with another non-canonical return type is renamed for the verbatim functions (s0063ba50 GetConfigManager,
  s0051a350 GetPaintSystem); an `extern "C"` prototype of a function the TU defines with C++ linkage is dropped (s00767ee0
  UnionDestroy); externs naming class templates / forward-declared stubs go after the stubs, and stub renames reach the
  externs (s0063ba50, s0063d9e0); `template <.., class A = allocator<T> >` item names (s0063caf0); `struct
  __declspec(align(4)) X` item names (s0046f2a0); anonymous enums declare their enumerators (s009c32c0); operator new/delete
  are never renamed, and one the TU (or `<new>`) already has is not emitted (s004680c0, s005c4500); a global `::Name` is
  renamed with its stub (s004680c0); empty `F_<va>() {}` placeholders over a `??0/??4/??1` row become implicit-member
  forcing functions (s00469bb0); a namespace opened right after the marker wraps the function (s0046e450, s004629e0);
  a helper template right after the marker and `extern "C" { .. }` blocks are preamble (s00624fb0, s00764df0); banner
  markers (a VA marked twice) are not boundaries, the manifest's function name decides which copy (s0073f320, s00741210);
  banner VAs must name the function they are used for; indented `// @ 0xVA` over an in-class declaration count;
  toplevel_defs descends into namespaces (s0073a110); a markerless one-row slice marks the function its leading comment names
  (s00741b10); free functions the slice defines elsewhere get prototypes (`held_callee_protos`, s00766fa0); C2373 renames; a
  slice `typedef char va_list` gets `#define _VA_LIST_DEFINED` before every include (round 4 had hand-written it,
  s00b1fd50); out-of-class template members bind their row by `>::name(` (s0059c4c0 0x59c740).
- `tools/migrate/module_flags.json` {obj: {drop, add, evidence}}: per-object compile flags (EASharedLibrary drops /EHsc).
- Headers: `eastl/vector.h` declares an out-of-line `~vector()` and `erase(first, last)` (retail 0x5c7f10 / 0x5c2170);
  `layout_overrides.json` `SP::cPlayModeSubModeMovie` (two string16[260] tables, -mForceEnableVideoUpload, two bools,
  0x2360); `insert`/`append` accept a typed `desc`; headers.py: unknown class names and nested-type references/by-value
  uses make a declaration UNDECLARABLE, enum arrays pull the enum, pointer arrays are not by-value, pointer-to-array
  declarators.
- Round 6 objects whose headers compile standalone: `work/claude/round6_ready.json` (16); not ready:
  `work/claude/round6_not_ready.json` (template bases with no hand template: `SAP<2>`, `EA::SingletonBase`,
  `rw::core::thread::AtomicInt`; `encoding.h`; `eastl::vector_set`).

### 8g. Fix pass 5 (2026-10-16 .. 10-18, after the round-5 landings, batch mig5): what changed

All 16 mig5 objects were re-landed from scratch in batch order with the rules below (`--batch mig5`, flag-variant TUs
with `--variant _od/_o2`). Of the 1,268 mig5 functions, 1,219 are in the TUs and 49 are held back (round 5 before the
fix pass: 116 held). 578 rows are byte-exact in the module TUs (round 5: 534; the slices themselves have 580), 641 are
nonmatching/partial rows with an equiv verdict, and 1,162 rows are verbatim slice text. Every manifest under src/game is
green. Equiv was run on both sides (slice source and module TU, `scratch_fixpass5/eqcmp.py`) for every changed
nonmatching row: no real regression is left. Three ACM rows (0x7cbd60, 0x7cbdc0, 0x7cc3c0) are slice FAIL and module
UNSUPPORTED (unresolved template members); they stay in the TU because the slice verdict is already a mismatch.

Modules still below their slice-exact count: SPAppModeEditorBase 82/83 (0x57eda0, an inline member of the slice's
basic_string stub template), SPAppConfigManager 20/24 (0x7caac0/0x7cab00 bind another slice's do_copy; the 0x7cb480/
0x7cb510 explicit instantiations break the TU), SPUIBehavior 56/58 (0x7fb0e0/0x7fb220, DIFF 25/26 bytes, not only
inlining), ealog_imp 25/26 (0x9242f0 ??_G LogReporter: the canonical destructor is out of line).

Why held (49): compile errors in the module TU (stub/prototype clash, arity) 15; the layout guard (the slice's view of
the class disagrees with the canonical header) 9; equiv regressions 9; tool limits (marker binding, instantiations) 6;
byte-exact in the slice but DIFF in the module TU 5; the rest single cases. Every held VA has a `leave_in_slice` why.
Why verbatim (1,162 of 1,219 landed): no canonical class 398, a free function without a dev function 280, the converted
body did not compile 214, no unique canonical method 188, other 82. Tables: `scratch_fixpass5/causes2.py`.

- rewrite.py / rewrite_stubs.py rules (each comment names its test slice):
  - Stubs and names: a global stub is renamed when a canonical `NS::Name` exists and the slice's code lives in NS
    (s00575270); items are found through suffix-qualified spellings (`Editor::X`, s0057bfb0) and renamed that way
    (`qualified_only`, s007cb590); a slice class X where the TU has `namespace X` is renamed, and a slice
    `namespace X` against a global class X goes through `rename_namespace` (s00591fa0); forward declarations are
    never clash-renamed (s005598b0); a clash rename keeps the canonical spelling when the stub is class-mapped
    (s007ca950).
  - Preamble: operator new/delete dedup drops only definitions (s0057bfb0); merge_preamble keeps prototypes whose TU copy
    comes later and re-emits items that exist only after this slice's section (s007ca950); `forward_protos` covers
    functions inside `namespace X {` (s0057bfb0); hoist_decls moves an empty unqualified placeholder before the marker's
    function to the preamble, never a `X::X() {}` (s00705660); extern "C" prototypes in a namespace are hoisted to global
    only when they carry an address comment (s0058be50; an unrestricted version broke s004057b0);
    `placement_new_guard` (`#define __PLACEMENT_NEW_INLINE` + placement delete) when a slice defines placement new.
  - Return-type clashes (`ret_clash`): renamed stubs, qualified non-canonical returns, namespaced vs global prototypes,
    local-stub vs canonical returns; skipped when a converted function of the slice calls the function (s00584300).
  - Chunks: template-aware parameter split (s005580e0); InstChunks with explicit template arguments and an owner, bound
    with the `_sNNNN_NNNN` suffix (s0074c260, s007ca950); out-of-class template member definitions are skipped in the
    clash loop (s007cb590); pruning in apply touches only this slice's batch VAs (s007ca950).
  - Layouts: `refuse_foreign_layouts` lands a slice-exact function verbatim with the renamed stub instead of skipping it,
    and the checked apply verifies it (s0057ae10, s00585330, s00585d40, s005718f0, s0057d710).
  - Rows and symbols: implicit-member markers with the comment on the next line and scalar deleting destructors
    (s004186c0); a stale slice symbol is not used once the class is renamed (s00576140); **a verbatim out-of-class member
    with no class binding must bind a symbol of its own qualifier** (the bare name had bound another class's method:
    0x58d430 got cEditorAddDNACheat::Execute, 0x7cae30..0x7cb270 the neighbouring command class; the binding compile
    at /O2 drops unreferenced anonymous-namespace definitions). The six wrong lines were removed from
    symbols/slices; equiv binds those rows by name.
  - Compile repair: C2040 renames the stub, C2733 renames this slice's prototype (s00694210); `unsigned` normalises like
    `unsigned int` (s0074c260); named enums declare their name and enumerators (s005580e0).
  - CLI: `--variant _od` runs a flag-variant TU with its own block id and rename suffix; `parse_slice` falls back to the
    single `<sid>_*.cpp` (s007f9550); one-line stub structs are expanded so their methods get annotations (s0075de80).
- `tools/migrate/module_flags.json`: SPEditors/SPAppModeEditorBase.obj drops /EHsc (82/82 rows byte-exact without it).
- Equiv resolver data: a renamed class's vtable can be mapped in symbols/slices (`0143dd7c
  ??_7LogFormatterFancy_s0092_34f0@Trace@EA@@6B@`); that turned 0x9244d0 from UNSUPPORTED into PASS. When a module
  row reports "our code stores the address of its own copy of an object/vtable", look for this first.
- Carry-overs: s0075de80 (SPGraphicsRenderer, `--batch mig4`) lands 0x75e090..0x75e3b0, all PASS in the module TU;
  SkinnerPaintRender 0x517430/0x5183c0/0x518bf0/0x518cf0 land (WEAK/WEAK/UNSUPPORTED/UNSUPPORTED, the same as the
  slice); ealog 0x924170/0x924bd0 were re-measured and still regress (unresolved inline interface ctor/dtor
  references), so they stay held; 0x628340 keeps its exclude. 0x936420 IsLoaded (int-width body, bool caller) is still held, but the spelling is now known: `bool IsLoaded() { return mHandle != 0 || mHandlerBegin != mHandlerEnd; }` compiles at /O2 to `xor eax,eax; ret` / `mov eax,1; ret` (the `if (..) return false; return true;` form gives `xor al,al`). Landing it needs the slice body changed to that bool spelling (and its manifest symbol to `_N`), which is slice work.
- Headers (round 7): `headers.py` writes arrays of function pointers as `void (*name[N])()` (encoding.h);
  `eastl::vector_set` maps to the hand `eastl/vector_map.h`; new hand templates `rw/core/thread/AtomicInt.h` and
  `EA/SingletonBase.h` (dev evidence in each header, unverified in retail). AudioSystem, SPPollinatorTransactions and
  SPGraphicsEffectsRenderer now compile, and so do 22 more objects: `work/claude/round7_ready.json` lists 25 new
  objects (1,520 landable functions) plus 4 follow-up landings into existing TUs (`existing_tu: true`, leave_in_slice
  VAs removed). Not ready (`work/claude/round7_not_ready.json`): SPCellGame (`SAP<2>`, and most of its slices are
  in-progress work) and SPPlanetModel (needs a hand `SP::cTerrainMap<T>`). The candidates come from
  `scratch_fixpass5/r7_cands.py`: slice rows with a modmap module, not yet migrated, slice not in a running wave.
- Follow-up: per-object compile flags. Each slice's flags come from its own matching, but one set fits whole objects
  (OTDB 42/42 with `/Od /Ob1 ... /fp:fast`, AMEB without /EHsc, EMU 21/23 with one /Od set). Normalising each module to
  one flag set through module_flags.json is open.

### 8h. Fix pass 6, part A (2026-10-18, after round 7, batch mig7): data safety and speed

Round 7 (29 objects, commits 60a260fb..46e5d89a) is landed, byte-exact and asm-clean. Its 29 reports
(`work/claude/mig7_reports/`) and the plan built from them (`work/claude/fixpass6_plan.md`) drive this pass. Part A:

- **No more silent data loss on re-apply.** `prune_unemitted` (a run that emits nothing) now prunes only the VAs the
  batch lists for this slice; before, it deleted every earlier-landed block and the items section of the slice
  (EditorManipulationUtilities fell to 0/24; AppModeEditorBase and ThumbnailManager were hit too). A function that only
  failed to compile in this run keeps its earlier block, in `apply` as well (`failed_vas`); only a deliberate hold
  (`leave_in_slice`, `exclude`, asm, layout guard) removes a landed function. The items section stays while any block
  of the slice remains.
- **Auto-union.** With `--batch`, the slice's functions already in the module TU join the batch (note `union`), except
  VAs the batch gives to another slice. Hand-made union batch files are no longer needed. On mig7 this covers 41
  slices; re-applying s00575270 with `--batch mig7` (3 listed VAs) keeps the 5 mig5 functions and 82/82 rows.
- **Conversion guard** (`conversion_loses_behaviour`): a slice constructor or destructor is never converted into a plain
  method or the other special member, and a converted body is never empty when the slice's had statements; the function
  lands verbatim with a "conversion refused" note. s006068c0 0x606f30 (`cAuthMessage::~cAuthMessage() {}`, the scalar
  deleting destructor) had become an empty `slot_22`; equiv said FAIL before and after, so only a structural check
  catches this class of damage. A plain function becoming a ctor/dtor stays allowed (report 05).
- **Atomic shared files.** `headers.dump_json_atomic` (temp file + `os.replace`) for the Undname cache (which also merges
  concurrent additions and treats a truncated file as empty), the vtable cache, modmap output and `od_name_rank.json`.
- **No-marker slices** exit 0 with "no reconstructed functions" (was an IndexError in `parse_slice`).
- **Probe fix and cache.** The VC9 layout probe reads each offset from a compile error, and cl stops at 100 errors
  (C1003). Paths that do not compile add errors of their own, so chunks stopped early and the nodes after the cap were
  reported as "does not compile" (s00627d50: 9 of 16 chunks capped); which nodes were lost depended on chunk
  composition. Unreached nodes are now requeued (a chunk that reached nothing is retried in halves). With results
  independent of chunking, they are cached per class in `work/migrate/probe_cache/` keyed by class + a fingerprint of
  `src/game/include` (any header change invalidates; `RW_NO_PROBE_CACHE=1` bypasses). A dry run of s006068c0 went from
  11.4 s to 2.4 s; a dry sweep of all 253 mig7 entries (6 parallel) from 393 s uncached to 118 s; an apply from 38 s to
  28 s. The cached sweep's output is identical to the uncached one for all 253 entries; versus the pre-fix probe, one
  layout-guard message gained a member (s0048c0f0, same decision).
- Known cosmetic: each re-apply adds blank lines to the TU (s00575270: +153 blank lines, no other change). Part C.

### 8i. Fix pass 6, part B (2026-10-18): class and method guesses need an anchor

- **Method shape+name** (`choose_decl`): a candidate whose retail address differs from the function's is never chosen, and the
  names must be equal up to case and underscores (`name_key`). On the mig7 sweep, 276 shape+name decisions included opposites
  (SetUIDisabled -> SetUIEnabled, SetTabIndentOff -> On, getIdentity -> setIdentity) and unrelated slots (Init -> AsInterface,
  a destructor -> AddRef, PostGetAssetFeed -> dev-only Login). Those functions now stay unconverted (verbatim).
- **Class maps from retail address comments** (`map_from_methods_va`): a vote is anchored only when the retail method's name
  equals the slice's and is not a name whose bodies the linker folds across classes (`FOLDED_NAMES`: AddRef, Release, new,
  delete, AsInterface, ...); placeholder names (`FUN_`, `Fn`, `f`) and generated-header owners do not anchor. A class whose
  name corresponds (`class_anchor`) wins; otherwise exactly one anchored class is needed. A slice struct named exactly like
  another canonical class is not mapped elsewhere (`namesake`: cJob is not SP::cJobManager).
- **Class maps from vtable slot shape** (`map_from_slots`): need a name anchor, no namesake, and named slots that do not
  disagree more than they agree (`slot_clash`). Every three-slot refcounted interface used to map to
  EA::Audio::FactoryBinarySampleData.
- Not done on purpose: a general vtable-name guard for all maps (it refused correct main classes such as cSPSwatch, whose slice
  virtual names are guesses; calls are mapped by slot index and the byte-exact check catches a wrong slot order), and mapping
  a struct by a unique same-named canonical class (it added ~230 maps; out of scope).
- `rewrite.py` without `--quiet` now also prints the methods of other mapped structs with their reasons, and
  `work/claude/night_sweep.sh` + `night_cmp.py` diff two dry sweeps of the mig7 entries.
- Header item found: EA::UTFWin::CustomWinProc's header notes only 2 of 32 retail slots agree with the dev vtable.

### 8j. Fix pass 6, parts C/F so far (2026-10-18 night, during wave mig8): what changed for landing agents

- **Second sources** (C7): a slice dir with another `<slice>*.cpp` (s0062da00_ui.cpp, s00634490b.cpp) is a variant source. A plain
  run prints `VARIANT SOURCE: ... run the same commands with --variant X` for the batch functions that live there; run steps 1-5
  again with that `--variant`. A function without a manifest row belongs to the source whose marker defines it. Slice-named
  local headers (`s00634490_ui.h`) are expanded like `sXXXXXXXX.h`.
- **`#if 0` blocks** in slice text and headers are dropped (s007de7d0: a disabled annotation struct became a second FloatVec).
- **Stub member definitions** (C13): `bool F_ec20::f(..) {..}` is no stub item of its own (the clash loop renamed `f` in the
  declaration only: C2039; also SwatchStrategies' `inline void cMWModel::Release()` holds). Holds whose reason is the clash loop
  can be deleted from the renames file and the entry re-applied.
- **using-directives**: one inside a namespace block declares nothing (s0056df80: `SP::Traits::eastl::`, C3083); a verbatim
  definition after a dropped `using namespace N;` gets `N::` in its parameter list too (0x7e67a0 `CommandLine`, C2065).
- **Crashes fixed**: `proto_key` on `__declspec(thread)` variables; the variant hint KeyError.
- **run_all --manifest** (F26) uses its own object dir, lock and results file per manifest: module runs no longer wait.
- **Reports**: name them `work/migrate/report_<slice>_<Obj>.md` (one slice can feed several objects).
- Agents: start every shell command with `cd <repo root> &&` (the session's working directory can move).
- **`#pragma` restores stay with their function** (571d681d): a slice's `#pragma inline_depth(0)` .. function ..
  `#pragma inline_depth()` lost its restore to the preamble, so every later function of the module TU compiled without
  inlining. That was the main cause of "byte-exact in the slice, DIFF in the module TU" drops (s005d61b0: 9 -> 21 exact).
- **Explicit instantiations** that reach the preamble outside their `namespace X {` block are wrapped in it again (s004e01d0).
- **A second definition under one VA** (two classes' folded `HandleResult`) goes to the preamble instead of crashing qual_of.
- **A namespace after a marker** is the function's own only when the function is its first item (s004b8af0).
- **Holds on re-apply**: never add `leave_in_slice` for a function already in the TU (a hold removes it), and an equiv
  UNSUPPORTED caused by an unresolved callee or a compile error of the module TU in the harness is not a regression.
- **A namespaced stub hoisted by `using NS::X;`** over a canonical *global* class X (`SP::cSPColorRGB` vs `cSPColorRGB.h`)
  is renamed, and the using-declaration with it (C2874; SPEditorColorPicker).
- **`virtual ::IDrawable*`**: a keyword before `::` is the global scope, so the global item counts as used and is kept
  (C2039 in a kept stub; SPEditorColorPicker).
- **An explicit instantiation of a template the slice defines** is dropped when that template is not landed in the TU
  (C2143; SPEditorPaintLikeThis s005c0c00, 20 functions).
- **`// Name (0xVA)` banners** give a definition its VA when the name matches (an anonymous-namespace helper was silently
  never emitted; Parser SubstituteParameters).
