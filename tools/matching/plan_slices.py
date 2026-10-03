#!/usr/bin/env python3
"""Partition remaining functions into contiguous work slices. Writes work/slices.json.

usage: plan_slices.py [--max-bytes 2500] [--max-funcs 25] [--big 3000]
Excludes library-identified functions and anything already in a manifest or a slice's
done list. Functions larger than --big become their own slice ("big").
"""
import argparse, csv, glob, json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from card import load_funcs, bounds

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
ap = argparse.ArgumentParser()
ap.add_argument("--max-bytes", type=int, default=2500)
ap.add_argument("--max-funcs", type=int, default=25)
ap.add_argument("--big", type=int, default=3000)
a = ap.parse_args()

starts, names = load_funcs()
skip = set()
for f in glob.glob(W("work/oss/*_matches.csv")):
    for r in csv.DictReader(open(f)):
        if r["status"] == "unique":
            skip.add(int(r["va"], 16))
for m in [W("match/manifest.txt")] + glob.glob(W("match/slices/*/manifest.txt")) + glob.glob(W("match/synth/*.manifest")) + glob.glob(W("match/clones.txt")):
    for line in open(m):
        p = line.split("#", 1)[0].split()
        if len(p) >= 3:
            skip.add(int(p[2], 16))
for m in glob.glob(W("match/slices/*/nonmatching.txt")):
    for line in open(m):
        p = line.split("#", 1)[0].split()
        if p:
            skip.add(int(p[0], 16))

# functions already handed to a batch (attempted or in flight) are never re-planned
import json as _json
for bf in glob.glob(W("work/batches/*.json")) + [W("work/pilot.json")]:
    if os.path.exists(bf):
        for sl in _json.load(open(bf)):
            for v in sl.get("vas") or [f["va"] for f in sl.get("functions", [])]:
                skip.add(int(v, 16))

slices, cur, cur_bytes = [], [], 0
text_end = 0x13CC000
def flush():
    global cur, cur_bytes
    if cur:
        slices.append(cur)
    cur, cur_bytes = [], 0
for i, va in enumerate(starts):
    if va in skip or va >= text_end:
        continue  # done functions are simply left out; a slice may straddle them
    nxt = starts[i + 1] if i + 1 < len(starts) else va + 16
    size = nxt - va
    if size > a.big:
        flush(); slices.append([(va, size)]); continue
    if cur and (cur_bytes + size > a.max_bytes or len(cur) >= a.max_funcs):
        flush()
    cur.append((va, size)); cur_bytes += size
flush()
out = [{"id": "s%08x" % s[0][0], "functions": [{"va": "%08x" % v, "size": n, "name": names.get(v, "")} for v, n in s],
        "bytes": sum(n for _, n in s)} for s in slices]
json.dump(out, open(W("work/slices.json"), "w"))
print("slices:", len(out), "functions:", sum(len(s["functions"]) for s in out),
      "big:", sum(1 for s in out if len(s["functions"]) == 1 and s["bytes"] > a.big))
