#!/usr/bin/env python3
"""Emit the next N not-yet-attempted slices as compact JSON for the matching workflow.

usage: next_batch.py N [--order addr|size|size-desc|bfs] [--min-bytes 0] [--max-bytes 99999] [--min-funcs 0] [--write name]
A slice counts as attempted once match/slices/<id>/ exists.

Orders:
  addr       ascending first address (default)
  size       smallest slice first
  size-desc  largest slice first
  bfs        breadth-first call distance from the entry point; each slice is ranked by the
             earliest (smallest-depth) function it contains. Requires work/bfs_rank.json,
             produced by tools/matching/callgraph.py.  Unreachable slices sort last unless
             --reachable-only is given.
"""
import argparse, json, os
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
ap = argparse.ArgumentParser()
ap.add_argument("n", type=int); ap.add_argument("--order", default="addr",
                choices=["addr", "size", "size-desc", "bfs"])
ap.add_argument("--min-bytes", type=int, default=0); ap.add_argument("--max-bytes", type=int, default=99999)
ap.add_argument("--min-funcs", type=int, default=0, help="skip slices with fewer functions (amortizes agent setup)")
ap.add_argument("--reachable-only", action="store_true", help="with --order bfs, drop slices with no reachable function")
ap.add_argument("--write", help="freeze the batch to work/batches/<name>.json")
a = ap.parse_args()
slices = json.load(open(W("work/slices.json")))
todo = [s for s in slices if not os.path.isdir(W("match/slices", s["id"]))
        and a.min_bytes <= s["bytes"] <= a.max_bytes and len(s["functions"]) >= a.min_funcs]
if a.order == "size":
    todo.sort(key=lambda s: s["bytes"])
elif a.order == "size-desc":
    todo.sort(key=lambda s: s["bytes"], reverse=True)
elif a.order == "bfs":
    bf = W("work/bfs_rank.json")
    if not os.path.exists(bf):
        raise SystemExit("missing %s - run: .venv/bin/python tools/matching/callgraph.py" % bf)
    rank = json.load(open(bf))["rank"]

    def bfs_rank(s):
        rs = [rank.get(f["va"]) for f in s["functions"]]
        rs = [r for r in rs if r is not None]
        return min(rs) if rs else None

    if a.reachable_only:
        todo = [s for s in todo if bfs_rank(s) is not None]
    todo.sort(key=lambda s: (bfs_rank(s) is None, bfs_rank(s) if bfs_rank(s) is not None else 0, s["id"]))
batch = todo[:a.n]
data = [{"id": s["id"], "vas": [f["va"] for f in s["functions"]]} for s in batch]
if a.write:
    json.dump(data, open(os.path.join(ROOT, "work/batches", a.write + ".json"), "w"))
    print("wrote batch %s: %d slices, %d functions" % (a.write, len(data), sum(len(d["vas"]) for d in data)))
else:
    print(json.dumps(data))
