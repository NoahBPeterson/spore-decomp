#!/bin/sh
# Re-verify everything, propagate clones, refresh status. Run between fan-out batches.
cd "$(dirname "$0")/.."
.venv/bin/python tools/matching/run_all.py > work/run_all.log 2>&1; tail -1 work/run_all.log
grep -E "^(DIFF|FAIL|COMPILE FAIL)" work/run_all.log | head -20
.venv/bin/python tools/matching/propagate.py
.venv/bin/python tools/status.py | sed -n 9,20p
