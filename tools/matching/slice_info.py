#!/usr/bin/env python3
"""slice_info.py <batch> <index>  — print the slice id and its function VAs (one per line)."""
import json, os, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
b = json.load(open(os.path.join(ROOT, "work/batches", sys.argv[1] + ".json")))
i = int(sys.argv[2])
if i >= len(b):
    print("NO SLICE"); sys.exit(1)
print("slice", b[i]["id"])
print("functions", " ".join(b[i]["vas"]))
