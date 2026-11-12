#!/usr/bin/env python3
"""Re-verify existing non-byte-exact functions with prove.py, so contributors can focus on the ones that are neither
byte-exact nor equivalent (maintainers; needs the game image).

  .venv/bin/python tools/equiv/sweep.py [--layers rename] [--timeout 60] [--max-size 4096] [--jobs 4] [--record]
                                        [--out work/equiv_sweep.jsonl] [--limit N]

Candidates: every function with a nonmatching.txt or partial.txt line, plus tools/ci/known_failures.txt rows, that
is not byte-exact, not already proven equivalent and not claimed by an open pull request; smallest first (small
functions are the cheapest to prove and the most numerous). Results are appended to --out as one JSON line per
function (resumable: functions already in the file are skipped). --record writes equivalent.txt rows for the
EQUIVALENT ones. A REFUTED function means its source computes something else: its note should say so.
"""
import argparse, glob, json, os, sys, time
from concurrent.futures import ProcessPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "equiv"), os.path.join(ROOT, "tools", "contrib"),
                os.path.join(ROOT, "tools", "difftest"), os.path.join(ROOT, "tools", "matching")]


def candidates(max_size):
    import task as T
    import slice as S
    import run_all as R
    done = {r[2] for r in R.read_rows(R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**",
                                                                                     "manifest.txt"), recursive=True)), "")}
    known = {int(l.split()[0], 16) for l in open(os.path.join(ROOT, "tools", "ci", "known_failures.txt"))
             if l.strip() and not l.startswith("#")}
    vas = set(known)
    for name in ("nonmatching.txt", "partial.txt"):
        for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", name)) + \
                glob.glob(os.path.join(ROOT, "src", "game", "**", name), recursive=True):
            vas |= {va for va, _d, _r in S.read_rows(f)}
    eq = set(T.equivalent())
    cl = T.claims() or {}
    live = {va for va, c in cl.items() if not T.stale(c)}
    fps = T.fingerprints()
    have = T.marked()                       # only functions that have source (a // @ marker)
    out = [(fps[v]["size"], v) for v in vas if v in fps and v in have and fps[v]["size"] <= max_size
           and (v not in done or v in known) and v not in eq and v not in live]
    return [v for _s, v in sorted(out)]


def one(va, layers, timeout, record):
    import io
    import contextlib
    import prove
    buf = io.StringIO()
    t = time.time()
    try:
        with contextlib.redirect_stdout(buf):
            res = prove.run(va, layers, timeout, log=lambda s: buf.write(s + "\n"))
            if record and res["verdict"] == "EQUIVALENT":
                prove.record(va, res)
    except SystemExit as e:
        res = {"verdict": "ERROR", "detail": str(e)[-300:]}
    except Exception as e:          # one broken function must not stop the sweep
        res = {"verdict": "ERROR", "detail": "%s: %s" % (type(e).__name__, str(e)[-300:])}
    return {"va": "%08x" % va, "verdict": res["verdict"], "layer": res.get("layer"), "level": res.get("level"),
            "detail": (res.get("detail") or "")[:300], "seconds": round(time.time() - t, 1)}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--layers", default="rename")
    ap.add_argument("--timeout", type=float, default=60.0)
    ap.add_argument("--max-size", type=int, default=4096)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--record", action="store_true")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "equiv_sweep.jsonl"))
    a = ap.parse_args()
    layers = [x if x == "rename" or x.endswith("_layer") else x + "_layer" for x in a.layers.split(",")]
    seen = set()
    if os.path.exists(a.out):
        seen = {json.loads(l)["va"] for l in open(a.out) if l.strip()}
    todo = [v for v in candidates(a.max_size) if "%08x" % v not in seen][:a.limit]
    print("%d functions to check (%d already in %s)" % (len(todo), len(seen), os.path.relpath(a.out, ROOT)))
    counts = {}
    with open(a.out, "a") as out, ProcessPoolExecutor(a.jobs) as ex:
        futs = [ex.submit(one, v, layers, a.timeout, a.record) for v in todo]
        for k, f in enumerate(as_completed(futs), 1):
            r = f.result()
            out.write(json.dumps(r) + "\n")
            out.flush()
            counts[r["verdict"]] = counts.get(r["verdict"], 0) + 1
            if k % 25 == 0 or k == len(futs):
                print("%d/%d  %s" % (k, len(futs), "  ".join("%s %d" % kv for kv in sorted(counts.items()))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
