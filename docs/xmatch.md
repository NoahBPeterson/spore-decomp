# Cross-build name recovery (dev PDB → retail)

The 2008-02 dev build (`1.ML-0.0.11318`, VC7.1, with a matching PDB) shares most of its code with the
2024 retail build, but the two were compiled 16 years and many changes apart, so addresses and code bytes
differ. `tools/xmatch/` pairs functions between the two builds and carries the PDB names across. The overall
approach (anchors plus call-graph propagation) is industry-standard, as in BinDiff and Diaphora.

## Pipeline

```sh
.venv/bin/python tools/pdb_symbols.py work/devbuild/SporeBin/SporeApp.pdb work/devbuild/SporeBin/SporeApp.exe work/devbuild/symbols.json
.venv/bin/python tools/xmatch/features.py dev    work/xmatch/dev.json
.venv/bin/python tools/xmatch/features.py retail work/xmatch/retail.json
.venv/bin/python tools/xmatch/tables.py  work/xmatch/dev.json work/xmatch/retail.json work/xmatch/tables.json
cd work/xmatch && ../../.venv/bin/python ../../tools/xmatch/match.py dev.json retail.json matches.json ../devbuild/symbols.json tables.json
XMATCH_HOLDOUT=0.2 ...match.py ...      # precision estimate (below)
.venv/bin/python tools/xmatch/globals.py work/xmatch/matches.json symbols/pdb_globals.json
tools/ghidra/run.sh apply_pdb_names.py   <matches.json> <high-confidence methods> <previous pdb_names.json>
tools/ghidra/run.sh apply_pdb_globals.py symbols/pdb_globals.json symbols/pdb_vtables.json
```

The full match takes about 90 seconds and is deterministic.

## Dev-build quirk: encrypted incremental-link thunks

The dev exe was linked `/INCREMENTAL`, so every direct call and every vtable slot points at an ILT
(incremental link table, industry-standard: a `jmp target` stub per function). SecuROM encrypted that
region (`0x401000`–`0x44a000`), so the stubs can't be read. Their targets come from the PDB instead:
`S_TRAMPOLINE` records in the `* Linker *` module (46,702 entries, `symbols.json` → `thunks`).
Before this fix, 38% of dev call edges were lost.

## Methods (terms)

Each method is listed with its hold-out precision. Hold-out (industry-standard): 20% of the anchors are
hidden and the matcher has to re-find them. Precision is correct / recovered.

| Method | What it is | Hold-out | Applied as name? |
|---|---|---|---|
| anchor (industry-standard term) | a string, constant, or identical string set that occurs in exactly one function on each side | (the truth set) | yes |
| callee-single / caller-single (Claude-ism) | a matched pair has exactly one unmatched callee (or caller) on each side | 8/8, 30/31 | callee yes, caller no |
| callee-scored / caller-scored (Claude-ism) | among the unmatched callees (callers), one candidate pair is the unique best by shared features | 107/111, 171/189 | callee yes, caller no |
| gap-align (Claude-ism) = Needleman–Wunsch sequence alignment (industry-standard) | unmatched functions between two matched neighbors from the same dev module, aligned by size and evidence-gated | 41/41 | yes |
| vtable-slot (Claude-ism) | retail vtables (runs of code pointers in `.rdata` stored from code, since the build has no RTTI) paired with dev `??_7` vtables by votes from matched slots at the same index; the remaining slots are then paired by position | 8/8 | yes |
| xcu-anchor / xcu-align (Claude-ism) | the C++ dynamic-initializer tables (`__xc_a..__xc_z`, industry-standard) on both sides; tokens unique within both tables anchor entries, and gaps are aligned | 39/39, 1/1 | yes |

Evidence (Claude-ism): call counts must be within 20%, and the pair must share a string, constant,
import, constant-pool value, or an already-matched callee. Constant-pool values are the dwords read from
`.rdata`, which covers float literals.

The FNV bridge (Claude-ism): retail folds `id("name")` into an FNV-1 immediate, while dev code may
reference the string. So dev strings also contribute `fnv(s)` as a constant.

Globals come from `globals.py`. Each matched high-confidence pair lists its absolute data operands in
order. When both lists have the same length and the same mnemonics, operand k on one side corresponds
to operand k on the other. A retail address gets the containing dev PDB global (minus the offset) only
if every vote agrees.

## Results (2026-10-03)

| Stage | Retail functions matched |
|---|---:|
| before (no thunks, no tables) | 8,446 |
| after thunk fix, worklist, vtables, and initializer tables | 12,881 |
| applied as names (high-confidence methods) | 10,007 |
| comment-only candidates (caller-*) | 2,874 |
| retail vtables paired | 377 of 4,731 |
| retail globals named | 1,049 (+377 vtable labels) |

The initializer tables yield little. Retail has 31,266 initializers and dev has 17,154, because retail
inlines differently. Two thirds of them have no distinctive token, so there is nothing safe to align on.
