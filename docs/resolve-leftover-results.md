# Resolving the 304 "unresolved reference" functions — results

Companion to `docs/handoff-resolve-unresolved-refs.md` (the brief). Tool: `tools/matching/resolve_leftover.py`.

## Outcome

| | functions |
|---|---:|
| blocked by unresolved references at the start | 304 |
| unblocked by mapping `__except_list` to 0 in the checker (SEH chain head, §4.A of the brief) | 27 |
| unblocked by alignment-derived `// 0x<VA>` annotations (two rounds, 83 slice files, 0 byte-exact regressions) | 134 |
| **now testable** | **161** |
| **still blocked** | **143** |

Of the 143 still blocked, 95 are one symbol away. By the reason for the last blockers
(bucket letters are used in `work/claude/resolve_leftover/report.md`, one row per function):

| bucket | functions whose remaining blockers are all of this kind | what it means | what would fix it |
|---|---:|---|---|
| D | 96 | no alignment candidate: the original's call/data reference sequence does not pair with ours at the symbol's position (18 of these have call counts far apart, i.e. the source is structurally unlike the original) | better source, not better symbol data |
| M | 14 | the symbol *does* align to an original callee, but our declaration's calling convention / argument count disagrees with the callee's `ret N` (typically a free `cdecl` wrapper declared for what is really a `thiscall` method, e.g. `WAssign` → `eastl::basic_string<wchar_t>::assign` at 0x00423650) | fix the declaration in the slice, then the annotation applies |
| C | 9 | the same invented name is used by several functions of one slice but they align to *different* originals (one annotation per slice cannot serve both) | split the name per instantiation in the source |
| E | 6 | structural: `___rdtsc` (the original executes `rdtsc` inline; add `#pragma intrinsic(__rdtsc)`), `_isspace` (the original inlines the ctype-table lookup; there is no call to point at) | source change |
| P | 5 | a plausible candidate exists (tier 4: aligned only, long gap, no corroboration) and was deliberately not applied | human/agent confirmation, then annotate |
| S | 4 | annotation mechanism limits: a declaration already carries a *different* (dead) address, `??$` member templates (`DoAssignFromIterator<It>`) and template `operator=` cannot be keyed by the resolver, template arguments that are not identifiers (`fixed_vector<E,16>` → `E$0BAA`) | resolver/source work; see `apply.json` notes |
| mixed | 9 | combinations of the above | — |

So the honest ratio asked for in the brief is: **161 of 304 recovered; 143 remain, of which 6 are structural
(rdtsc/ctype inlining), 0 are SEH (fixed in the checker), 14 are wrong declarations in our source, ~105 are
alignment failures where the original gives no usable signal (mostly sources whose structure differs from the
original), and the rest are small mechanism limits.** None of the leftovers would be helped by more PDB
coverage: the invented names (`Callee::f`, `g_vtblA`, `CPlayerInventory::f5cae30`, `EAVec<I>::DoInsertValue`)
exist only in our sources, so symbol databases can never name them. The original *function* names them.

## Method (why the exact-name approach had stalled)

After the exact-name pass, almost every leftover was a name the decompiling agent made up. The only thing that
identifies such a symbol is the original function itself: its sequence of call and data references, aligned
against the sequence our compiled function produces. The checker's resolver already had this alignment
(`Resolver.align`) but only trusted 1-reference gaps. The tool reuses the same alignment and adds corroboration:

| evidence | meaning |
|---|---|
| `hex-name` | the identifier carries the candidate's address (`f5cae30` ↔ 0x005cae30, `Fn_ef30` ↔ 0x0065ef30, `Fun0066_0ad0` ↔ 0x00660ad0) |
| `align-1gap` / `align-weak`, `gap:N`, `positional` | the resolver's own alignment; the gap length; whole-sequence positional agreement |
| `arity-ok` / `arity-MISMATCH` | the original callee's `ret N` vs the stack bytes our mangled declaration implies; a mismatch vetoes |
| `db-name` | the candidate's name in `symbols/` shares our identifier (`GetCreature` ↔ `cSPEditorAnimatedCreatureManager::GetCreature`) |
| `db-name-unique` | nothing aligned, but exactly one original reference of that kind carries our identifier (strict equality) |
| `sibling-ann` | another slice already annotates this identifier+scope with the candidate |
| `slice-consensus` | other blocked functions of the same slice align the symbol to the same address |

Tiers (chosen per slice-symbol, both rounds): 1 = hex-name + aligned (6); 2 = aligned + corroborated (156); 3 = aligned, gap ≤ 2, arity agrees (147)
(data: gap 1); 4 = aligned only (39, reported, never applied). Every applied comment records its tier:
`// 0x004b5ad0 (equiv t2)`. One address is chosen per (slice, symbol) by majority; ties are reported as conflicts.

Two facts about the annotation mechanism made template instantiations resolvable without touching the resolver's
keying: the resolver accepts *any* scope fragment of the mangled name, and template arguments are fragments. So
`struct UVec3 { void DoInsertValue(); // 0x004b5ad0 };` inside a `namespace __equiv_annN` uniquely annotates
`EAVec<Vec3>::DoInsertValue` while `struct EAVec` would be ambiguous across instantiations. The planner simulates
`Resolver.by_annotation` on existing + planned annotations and drops anything the resolver would not pick, before
compiling.

## Checker changes (tools/difftest, all covered by `test_equiv.py`, 11/11 passing)

1. `resolve.py`: `__except_list` resolves to 0 ("seh-chain"). It is MSVC's absolute symbol for the SEH chain
   head (`fs:[0]`), exactly what the CRT defines; the machine already maps FS to an emulated TEB. 27 functions.
2. `resolve.py`: for an `extern "C"` symbol, a namespace around the declaration is ignored when matching
   annotations (`namespace rw { extern "C" const float g_pow43[32]; // 0x014cb460 }` was a dead annotation).
3. `resolve.py`: template constructors/destructors key on `vector`, not `?$vector`.
4. `equiv.py` + `slice.py`: headers a slice includes from a sibling slice directory by relative path
   (`#include "../s00908c00/s00908c00.h"`, the expat slices) are scanned for annotations too.

## How to rerun

```sh
D=work/claude/resolve_leftover/next
.venv/bin/python tools/matching/resolve_leftover.py harvest --worklist <json of {slice,va}> --dir $D   # or: harvest <slice ids>
.venv/bin/python tools/matching/resolve_leftover.py propose --dir $D
.venv/bin/python tools/matching/resolve_leftover.py apply   --dir $D --dry-run      # inspect $D/apply.json
.venv/bin/python tools/matching/resolve_leftover.py apply   --dir $D                # edits, run_all per touched slice (auto-revert), re-resolve
.venv/bin/python tools/matching/resolve_leftover.py report  --dir $D --final <later harvest.json> --rounds $D ...
```

`apply` only edits under `match/slices/`, appends comments to existing declaration lines (splitting
multi-declarator `extern` lines), or appends a `namespace __equiv_annN { struct X { ... }; }` block; it verifies
every touched slice (and every slice including a touched header) with `run_all.py` and reverts on any change in
byte-exactness. Harvest/propose are safe to run while waves are running; `apply` waits for `work/run_all.lock`.

## Verdicts of the 161 newly testable functions

Run with `equiv.py <slice> <va> --time-limit 240` (default inputs), 4 shards; per-function results in
`work/claude/resolve_leftover/final/verdicts.json`.

| verdict | all 161 | SEH-only (27) | annotations, tier ≤ 2 only (75) | annotations incl. tier 3 (54) | other (5) |
|---|---:|---:|---:|---:|---:|
| PASS | 24 | 3 | 8 | 13 | 0 |
| WEAK (equivalent on the inputs reached, coverage/validity below threshold) | 39 | 1 | 27 | 10 | 1 |
| FAIL (real behavioural mismatch to investigate) | 38 | 5 | 18 | 11 | 4 |
| UNSUPPORTED for another reason (13 × "original reads ecx at entry", 4 × stores address of its own copy, the rest no valid inputs) | 60 | 18 | 22 | 20 | 0 |

Tier-3 annotations do not fail more often than tier ≤ 2 ones, which is the sanity check on accepting
uncorroborated 2-gap alignments. The 38 FAILs and 13 "reads ecx" cases are now concrete work items for the
decompiling agents (the latter are `thiscall` methods declared as free functions, the same defect as bucket M).

## Possible further rules (not implemented)

- `Variant::Assign<T>` / `AssignArray<T>` in s008220e0 (15 symbols, one 178-call function): the DB names the
  originals `EA::Variant::operator=<T>`; matching our first parameter's type against the `<T>` in the qualified
  name would pair them. The sequences do not align because our switch emits cases in a different order.
- Float constants named by value (`g_const_zero`, `g_const_one`): match the original's `movss` source against
  `.rdata` content (0.0f / 1.0f) when the counts differ.
