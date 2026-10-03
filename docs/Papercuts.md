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
- [orchestrator] tooling: cmpobj misread section numbers above 32k (signed 16-bit). Fixed in cmpobj/libmatch/libresolve.
- [orchestrator] tooling: hand-typed workflow args. Agents now resolve slices via slice_info.py / pattern_info.py.
