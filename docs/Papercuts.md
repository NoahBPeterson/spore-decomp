# Papercuts

Shared log of friction that matching/pattern agents hit: tooling bugs, confusing instructions,
re-discovered tricks, wasted time. The orchestrator reviews this between batches and folds
fixes into tools, docs/matching.md and the agent prompts. Entries that have been addressed get
moved to "Resolved".

## How to add an entry (agents)
Append ONE entry with a single shell command so concurrent appends don't interleave:

    cat >> docs/Papercuts.md <<'PAPERCUT'
    - [<slice-or-pattern id>] <category: tooling|docs|codegen|toolchain|data> — <what cost you time>.
      Fix idea: <one line>. Time lost: ~<minutes>.
    PAPERCUT

Only log things that cost real time or that the next agent will hit too. Check whether an
existing entry already covers it; if so, don't duplicate it (you may append "+1 [<id>]" under it instead).

## Open

## Resolved
- [orchestrator] codegen/tooling: the /Od name-hash slot order (s0041dd90, s004248c0, s00426430, s0042d560, s0042a220, s0042f9d0, ~560 agent-minutes in total) is resolved by tools/matching/od_names.py fit K and documented in docs/matching.md "/Od frame layout".
- [orchestrator] tooling: cmpobj misread section numbers above 32k (signed 16-bit). Fixed in cmpobj/libmatch/libresolve.
- [orchestrator] tooling: hand-typed workflow args. Agents now resolve slices via slice_info.py / pattern_info.py.
- [orchestrator] batch 2 (32 entries, 2026-10-04): codegen lessons folded into docs/matching.md "Batch-2 lessons"; the slice-wide checker shipped as tools/matching/chk.py; scratch files go in work/match/scratch_<id>_* only (the shared scratchpad got clobbered). Still open as ideas: card.py printing callee conventions, run_all wildcard for ?A0x anonymous namespaces, a name-search tool for /Od frames.
