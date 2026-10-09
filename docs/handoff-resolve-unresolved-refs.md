# Handoff — resolve the 304 "unresolved reference" functions

**For:** a strong reasoning/coding agent (Fable 5.1)
**From:** the Spore decomp orchestration session
**Repo:** `spore-decomp` (byte-exact decompilation of `SporeApp.exe`, 32-bit x86, MSVC 2008 SP1)
**Status:** 470 of 774 done; 304 remain. This document is self-contained.

---

## 0. TL;DR (what we want you to do)

The equivalence checker refuses to test a rebuilt function when one of the outside
symbols it calls/reads has **no known address in the original binary** → it reports
`UNSUPPORTED … unresolved reference(s)`. We fix that by writing the address as a
`// 0x<VA>` comment on the declaration, in the slice's own source.

- **774** functions were blocked this way.
- **470** were fixed by a *straight exact-name lookup* (committed as `29f93a0f`).
- **304** remain. Your job: **work out how many of the 304 are genuinely
  un-addressable vs. merely un-matched, and build the resolver that recovers the
  recoverable ones.**

Deliverable: a tool (see §5) that proposes and applies slice-local address
annotations, plus a short written verdict on the rest (why each is unresolvable).
Hard constraint: **it must never break byte-exactness** (see §6).

---

## 1. Background — what the checker does and what the error means

`tools/difftest/equiv.py <slice_id> <va> [<va>…]` takes a recompiled function and the
original function from `SporeApp.analysis.bin`, runs both on N generated inputs, and
compares the return value + memory effects.

To run *our* code, the checker must turn every external symbol our source references
into a concrete address in the original image:
- our code calls `operator new[]`, `Vector3::operator*`, an EA allocator, a global, etc.;
- the checker needs to know *which original address* that call/global corresponds to;
- that mapping is recorded as a `// 0x00f473a0` comment on the declaration line.

If a reference has **no annotation and can't be resolved another way**, the checker
can't place the call, so it refuses to run: `UNSUPPORTED … N unresolved reference(s): <sym>`.
This is a **testability** verdict, not a correctness verdict.

### The annotation mechanism (exact details)

- Parser: `source_annotations()` in `tools/difftest/resolve.py` (line ~218).
  It reads `// 0x…` comments on declaration lines and `// @ 0x…` markers ("the next
  definition has this address"). Accepted VA range is **`0x401000 ≤ VA < 0x1900000`**.
- Matching: `Resolver.by_annotation()` (`resolve.py` ~line 601) keys annotations by
  **identifier + scope**, not by raw mangled name. So `Foo::bar` needs `bar` declared
  in a scope named `Foo`. For an out-of-slice class, the 470-pass used a dummy block:
  ```cpp
  namespace __equiv_ann {
  struct Foo { void bar(); /* 0x004adc40 */ };
  }
  ```
- Other resolution paths in `resolve.py` you should reuse rather than reinvent:
  `by_symbols()` (mangled → `db.mangled`, via `symbols/pdb_names.json` etc.),
  `by_crt()` (`crt_helpers()`, for CRT thunks in `lib_names.txt`), `by_hex_name()`
  (address embedded in the symbol name).
- Flags/knobs: `tools/difftest/resolve.py` is the resolver; `tools/difftest/equiv.py`
  is the CLI; `DIFFTEST_MAX_PROCS` gates a **machine-wide** flock slot pool at
  `/tmp/difftest-slots-<uid>/` (set it to your shard count; too low starves shards).

---

## 2. Where everything lives

| What | Path |
|---|---|
| Blocked-function worklist (774 entries: `{slice, va, symbols[]}`) | `work/opencode/unsup_unresolved.json` |
| Fix log (470 `{slice, va, fixed, resolved_symbols, unresolved_left, verdict_after}`) | `work/opencode/unsup_unresolved_progress.jsonl` |
| Clean list of the ~479 distinct leftover symbols (with counts) | `work/opencode/unsup_leftover_symbols.txt` |
| Resolver / annotation parser | `tools/difftest/resolve.py` |
| Checker CLI | `tools/difftest/equiv.py` |
| Byte-exact re-verify for a slice | `tools/matching/run_all.py --manifest match/slices/<id>/manifest.txt -v` |

Symbol databases (all in `symbols/`):

| File | Format | Meaning |
|---|---|---|
| `names.txt` | `VA  name  # provenance` | hand/xref-derived names (`dc`=read from decompile, `str`=string xref, `vt`=vtable) |
| `lib_names.txt` | `VA lib_<m>::<mangled>  # provenance` | symbols in 3rd-party libs we rebuilt byte-exact from upstream; provenance often says `… byte-exact from upstream …` |
| `havok_names.txt` | `VA ?mangled  # havok identical-code` | Havok 3.1.0; **retail code instruction-identical to a dev-build** |
| `key_globals.txt` | `VA name  # hash …` | named globals |
| `vtable_names.txt` | `VA Class::Class  # vt` | vftables |
| `pdb_names.json` / `pdb_globals.json` / `pdb_vtables.json` | JSON name→data | from a **dev PDB** |
| `slices/<id>.txt` | `VA mangled  # evidence` | per-slice named symbols |
| `renderware4_core.txt` | ranges | RW4 core is equivalence-only |

> Note the key fact behind the "identical-code" tags: **MSVC link-time code folding
> (`/OPT:ICF`) makes many distinct mangled names share one address.** So one address can
> legitimately answer for several names. This is both an opportunity and a trap (§6).

---

## 3. How the 470 were fixed (the proven method)

For each missing reference the subagent found the address from, in order:
1. `symbols/names.txt`, `symbols/lib_names.txt`, `symbols/havok_names.txt`,
   `symbols/pdb_globals.json`, `symbols/slices/*.txt` — exact mangled-name lookup;
2. a **sibling slice** whose source already carried the same `// 0x…` annotation
   (this is how `operator new[]` got `0x00f473a0`, e.g.
   `match/slices/s007b55f0/s007b55f0.cpp:9`);
3. appended the comment to the declaration line, or emitted an `__equiv_ann` dummy
   struct when the class lived in another slice's header.

It then re-verified every touched slice with `run_all` (all byte-exact) and reverted any
that failed to compile. Do the same. **Edits only ever under `match/slices/`.**

---

## 4. The 304 that remain — honest categorization

First, the structural trap:

### 4.0 It is *all-or-nothing per function*
A function is unblocked only when **every** reference is resolved. Bottleneck counts:

| refs still missing | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|--:|--:|--:|--:|--:|--:|--:|
| functions | 109 | 89 | 43 | 29 | 28 | 5 | 1 |

So **109 are one symbol from being testable.** Resolving a shared symbol can unblock
several at once.

### 4.A `__except_list` — 28 functions (structurally not a pointer)
Not a call or a global. It is MSVC's name for the SEH registration chain, which lives in
the CPU **`FS` segment register** (`mov eax, fs:[0]`), not at any address in the image.
There is no VA to write; the accepted range `0x401000..0x1900000` cannot even express 0.
Two options: (a) teach the emulator/checker to model the SEH chain, or (b) explicitly
declare these 28 out-of-scope. Do **not** try to annotate them with `0x0`.

### 4.B Name-form mismatch — plausibly recoverable (verify!)
Our source uses a C name; the DB has the C++-mangled name (or vice-versa). Example —
`_EASTL_allocator_deallocate` (leftover) vs `symbols/names.txt:67 00f47380 EASTL_allocator_deallocate`.
Also `?EASTL_allocator_deallocate@@YAXPAX@Z`. A normalizer (`_X` ↔ `?X@@`, leading-underscore
stripping, `undname`) should bridge this family. CRT intrinsics (`_isspace`, `___rdtsc`) may
resolve through `by_crt`/`lib_names.txt`; check.

### 4.C Template-instantiation mismatch — **needs care, may be unrecoverable**
Our source references one instantiation; the DB holds *different* instantiations of the
same template. Example: leftover `?DoInsertValue@?$EAVec@I@@…`; `lib_names.txt` has 114
`DoInsertValue*` lines but **none is the `EAVec<I>` instantiation**. Same pattern for
`hkPointerMapBase` (we have `?$hkPointerMapBase@K@@…`, source says non-template
`hkPointerMapBase`) and `DoFreeNodes` (we have several `hashtable<…>` instantiations, not
that one). ⚠️ A naive base-name match gives 114 false candidates here — **do not** trust it.
You need demangled *signature* comparison, and for many of these the answer may still be
"not in our data."

### 4.D Genuinely absent from every DB
Zero candidates in any form. Examples: `?g_hkThreadMemoryTls@@3KA`,
`?g_hkMonitorStreamCurrentTls@@3KA`, `?g_vtblEditor@@3PAXA`, `?gVtA@@3HA`,
`?GetMessageServer@@YAPAXXZ`, `?SlotMessageDestruct@@YAXPAX@Z`,
`?s_classMemberTypeProperties@@3QBUhkClassMemberTypeProperties@@B`,
`?f5cae30@CPlayerInventory@@QAEPAU1@XZ`. These need **new symbol sources** (more PDB
coverage, pattern/xref mining, or manual analysis) — the resolver can only *report* them.

### 4.E Parser noise — not real references
Some tokens in the worklist are scrape artifacts: short hex fragments (`dca0`, `a70`),
`_gensym`, `annotation-ambiguous`, `member]`, `special`. Filter these in whatever you
build; they are not symbols.

> **Correction to earlier messaging:** these were described as "no address anywhere".
> That was too strong. §4.B is likely recoverable; §4.C is uncertain; §4.D is truly absent;
> §4.A is structural. The real ratio is what we want you to establish.

Top leftovers (full list: `work/opencode/unsup_leftover_symbols.txt`):

| count | symbol | bucket |
|--:|---|---|
| 28 | `__except_list` | A (SEH) |
| 10 | `??_V@YAXPAX@Z` (operator delete[]) | B/C (addr known elsewhere: `0x00f47380`) |
| 7 | `??_U@YAPAXIPBDHI0H@Z` (operator new[]) | B/C (addr known: `0x00f473a0`) |
| 7 | `?DoInsertValue@?$EAVec@I@@QAEXPAIABI@Z` | C |
| 6 | `?DoInsertValue@?$EAVec@UVec3@@@@…` | C |
| 6 | `?g_hkThreadMemoryTls@@3KA` | D (Havok) |
| 5 | `_EASTL_allocator_deallocate` | B (→ `0x00f47380`) |
| 4 | `??2@YAPAXIPBDHI0H@Z` (operator new) | B/C |
| 4 | `?g_vtblA@@3PAXA` / `B` / `CreatureAbility` / `Editor` | D (globals) |
| 4 | `?SlotMessageDestruct@@YAXPAX@Z` | D |
| 4 | `?MainArguments@ArgScript@EA@@…`, `?f@Callee@@QAEXXZ` | ? |

---

## 5. Proposed approach (the ask)

Build `tools/matching/resolve_leftover.py` (or extend `resolve.py`), roughly:

1. **Get authoritative current leftovers.** The worklist is the *pre-fix* snapshot. Run
   `equiv.py` over the 304 `(slice, va)` pairs and parse the actual
   `N unresolved reference(s): …` list. (Parallelize; respect `DIFFTEST_MAX_PROCS`.)
2. **Resolve each symbol**, in order, and record which strategy fired:
   - exact mangled in `db.mangled` (`by_symbols`);
   - C↔C++ name normalization + `undname` (for §4.B);
   - CRT helper (`by_crt`) for `_isspace`, `___rdtsc`, `__ftol*`, etc.;
   - **demangled-signature** match for template instantiations (§4.C) — compare template
     name **and** argument types, not just the base name;
   - code-folding map: if the DB says `# havok identical-code` / `lib_*` / `# dc`, several
     names can share one VA — use that deliberately, but only where provenance supports it;
   - address embedded in the name (`by_hex_name`).
3. **Apply** as slice-local `// 0x<VA>` annotations (declaration line, or `__equiv_ann`
   dummy struct for out-of-slice classes).
4. **Verify**: `run_all` on each touched slice must stay **fully byte-exact** (auto-revert
   otherwise); then `equiv` should flip `unresolved reference` → a real verdict.
5. **Report**: per-symbol outcome (resolved via X / close-match-only / absent / noise) and
   a final count of newly-testable functions. Commit under a clear message.

Acceptance criteria:
- byte-exactness unchanged everywhere (§6);
- no edits outside `match/slices/`;
- a written table of what got unblocked and what's left, with the reason for each leftover.

---

## 6. Gotchas / constraints

- **Never break byte-exactness.** After any edit, `run_all … -v` must report
  `N / N functions byte-exact`. The 470-pass verified all 264 touched slices.
- **`/OPT:ICF` folding**: one address legitimately answers for multiple mangled names.
  Base-name-only matching is unsafe (§4.C, the 114 false hits).
- **`__except_list` has no VA** (§4.A) — it is not `0x0`.
- **VA must be in `0x401000 ≤ VA < 0x1900000`** or the annotation is silently ignored.
- **Annotations key on ident+scope**, not raw mangled name (`by_annotation`). A class
  method declared in another slice needs the `__equiv_ann` dummy-struct trick.
- **Only edit `match/slices/<id>/`** — never `symbols/` headers other slices depend on.
- **No `sed -i` / `perl -i` / bare `python` / writes to `/tmp`** in this repo's agent
  workflow; use exact-string edits and compile-check with auto-revert.
- `DIFFTEST_MAX_PROCS` is a **machine-wide** semaphore; set it to your shard count.

---

## 7. Concrete examples to start from

```
# name-form mismatch (B)
leftover : _EASTL_allocator_deallocate
DB       : symbols/names.txt:67   00f47380  EASTL_allocator_deallocate   # dc
           also ?EASTL_allocator_deallocate@@YAXPAX@Z (3 fns)
           and  ??_V@YAXPAX@Z  → 0x00f47380 (operator delete[])

# operator new[] (B/C) — address already in sibling source
match/slices/s007b55f0/s007b55f0.cpp:9
    void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0

# template mismatch (C) — 114 base-name hits, NOT the right instantiation
leftover : ?DoInsertValue@?$EAVec@I@@QAEXPAIABI@Z
DB       : lib_names.txt has ?DoInsertValue*@?$hashtable@… / @?$rbtree@… only

# globally absent (D)
leftover : ?g_hkThreadMemoryTls@@3KA
DB       : havok_names.txt has hkThreadMemory *methods* + pdb_globals.json
           ?s_threadMemoryInstance@hkThreadMemory@@…  — but not this global
```

---

## 8. Reproduction / verification commands

```sh
# current, authoritative blockers for one function
.venv/bin/python tools/difftest/equiv.py <slice_id> <va>          # e.g. s007d76d0 007d8470

# byte-exact regression for a slice (must be N/N)
.venv/bin/python tools/matching/run_all.py --manifest match/slices/<id>/manifest.txt -v

# the worklist + fix log
jq '.[0]' work/opencode/unsup_unresolved.json
grep fixed work/opencode/unsup_unresolved_progress.jsonl | wc -l

# distinct leftover symbols, with counts
less work/opencode/unsup_leftover_symbols.txt
```

---

## 9. Definition of done

1. A resolver that unblocks every *recoverable* leftover, verified byte-exact-safe.
2. For everything still blocked, a one-line reason each, bucketed A–E (§4).
3. A number: "X of the 304 recovered; Y remain, of which Z are structural (SEH) and W are
   absent from our data." That number decides whether we invest in SEH modelling, new
   symbol extraction, or declare the remainder out-of-scope.
