#!/bin/sh
# usage: tools/opencode_verify_group.sh <batch>...  re-run run_all.py on every slice manifest of the batches,
# waiting out the shared run_all lock; prints "<batch> <slice> <run_all summary>".
cd "$(dirname "$0")/.."
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
done
