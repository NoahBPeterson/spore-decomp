#!/bin/sh
# usage: tools/opencode_verify_group.sh <batch>...  re-run run_all.py on every slice manifest of the batches,
# waiting out the shared run_all lock; prints "<batch> <slice> <run_all summary>".
# Then runs the categorisation gate (tools/categorize_audit.py --gate): every batch target VA must be in
# exactly one of manifest/nonmatching/partial, else the batch fails (exit 1). --skip-audit to bypass.
cd "$(dirname "$0")/.."
skip_audit=0
[ "$1" = "--skip-audit" ] && { skip_audit=1; shift; }
rc=0
for b in "$@"; do
  for s in $(.venv/bin/python -c "import json,sys;print(' '.join(x['id'] for x in json.load(open('work/batches/%s.json'%sys.argv[1]))))" "$b"); do
    f=match/slices/$s/manifest.txt
    [ -f "$f" ] || { echo "$b $s no manifest"; continue; }
    for i in $(seq 1 120); do
      o=$(.venv/bin/python tools/matching/run_all.py --manifest "$f" 2>&1 | tail -1)
      case "$o" in *already*) sleep 5;; *) break;; esac
    done
    echo "$b $s $o"
  done
  if [ "$skip_audit" = 0 ]; then
    a=$(.venv/bin/python tools/categorize_audit.py --batch "$b" --gate 2>&1); st=$?
    printf '%s\n' "$a" | grep -E '^(ERROR|    (IN-MULTIPLE-FILES|TARGET-UNCATEGORISED))| slices:' || true
    if [ "$st" != 0 ]; then echo "AUDIT FAILED $b (uncategorised/double-listed target VAs)"; rc=1; fi
  fi
done
exit $rc
