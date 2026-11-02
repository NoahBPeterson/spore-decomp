#!/bin/bash
# usage: tools/migrate/commit_obj.sh <batch> <module e.g. Spui/SPUIPieMenu>  -> verify and commit one landed object
# the repo (or worktree) this script is in: land_par.py runs it in worktrees
cd "$(dirname "$0")/../.." || exit 1
B=$1; M=$2
[ -f src/game/$M.cpp ] || { echo "no TU for $M"; exit 1; }
# LAND_GATED=1: land.py's gate ran run_all and the asm audit on exactly these files a moment ago
if [ -n "$LAND_GATED" ]; then out="gated by land.py: $(wc -l < src/game/$M/manifest.txt | tr -d ' ') manifest line(s)"
else out=$(.venv/bin/python tools/matching/run_all.py --manifest src/game/$M/manifest.txt 2>&1 | tail -1); fi
echo "$M: $out"
[ -n "$LAND_GATED" ] || echo "$out" | awk '{ if ($1 != $3) exit 1 }' || { echo "NOT ALL MATCH: not committed"; exit 1; }
if git cat-file -e HEAD:src/game/$M.cpp 2>/dev/null; then
  gone=$(comm -23 <(git show HEAD:src/game/$M.cpp | rg "^// @ 0x" | sort) <(rg "^// @ 0x" src/game/$M.cpp | sort))
  new=$(comm -13 <(git show HEAD:src/game/$M.cpp | rg "^// @ 0x" | sort) <(rg "^// @ 0x" src/game/$M.cpp | sort) | wc -l | tr -d ' ')
  echo "new functions in TU: $new"
  if [ -n "$gone" ] && [ -z "$FORCE" ]; then echo "FUNCTIONS REMOVED from the TU (not committed; FORCE=1 to override):"; echo "$gone"; exit 1; fi
fi
[ -n "$LAND_GATED" ] || .venv/bin/python tools/matching/asm_audit.py --all-rows src/game/$M.cpp >/dev/null 2>&1 || { echo "ASM AUDIT FAILED: not committed"; .venv/bin/python tools/matching/asm_audit.py --all-rows src/game/$M.cpp | head -5; exit 1; }
sl=$(python3 -c "
import json; print(' '.join(sorted({'symbols/slices/%s.txt' % e['id'] for e in json.load(open('work/batches/$B.json')) if e['module'] == '$M'})))")
files=""
# a new (untracked) symbols file is also a change: git diff --quiet says "no diff" for it, so it was never added
for f in $sl; do [ -e $f ] || continue; { git ls-files --error-unmatch -- $f >/dev/null 2>&1 && git diff --quiet -- $f; } || files="$files $f"; done
n=$(echo $sl | wc -w | tr -d ' ')
# generated class headers the TU includes (tools/migrate/headers.py writes them during rewrite.py; mig22 committed
# two modules without nSPBehaviorTree/decider_state.h, 2026-10-25)
git add src/game/$M.cpp src/game/$M $files src/game/include && git commit -q -m "$B: land $(basename $M) from $n slice(s)

$out (run_all on src/game/$M/manifest.txt); asm audit clean.

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
Claude-Session: https://claude.ai/code/session_01HQNkE9tHZBnQ1E5EfZAo8H" && git log --oneline -1
