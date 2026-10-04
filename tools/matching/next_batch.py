#!/usr/bin/env python3
"""Emit the next N not-yet-attempted slices as compact JSON for the matching workflow.

usage: next_batch.py N [--order size|addr] [--min-bytes 0] [--max-bytes 99999] [--min-funcs 0] [--write name]
A slice counts as attempted once match/slices/<id>/ exists.
"""
import argparse, json, os
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ap = argparse.ArgumentParser()
ap.add_argument("n", type=int); ap.add_argument("--order", default="addr")
ap.add_argument("--min-bytes", type=int, default=0); ap.add_argument("--max-bytes", type=int, default=99999)
ap.add_argument("--min-funcs", type=int, default=0, help="skip slices with fewer functions (amortizes agent setup)")
ap.add_argument("--write", help="freeze the batch to work/batches/<name>.json")
a = ap.parse_args()
slices = json.load(open(os.path.join(ROOT, "work/slices.json")))
todo = [s for s in slices if not os.path.isdir(os.path.join(ROOT, "match/slices", s["id"]))
        and a.min_bytes <= s["bytes"] <= a.max_bytes and len(s["functions"]) >= a.min_funcs]
if a.order == "size":
    todo.sort(key=lambda s: s["bytes"])
batch = todo[:a.n]
data = [{"id": s["id"], "vas": [f["va"] for f in s["functions"]]} for s in batch]
if a.write:
    json.dump(data, open(os.path.join(ROOT, "work/batches", a.write + ".json"), "w"))
    print("wrote batch %s: %d slices, %d functions" % (a.write, len(data), sum(len(d["vas"]) for d in data)))
else:
    print(json.dumps(data))
