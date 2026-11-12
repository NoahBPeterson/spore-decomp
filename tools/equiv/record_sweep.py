#!/usr/bin/env python3
"""Record a sweep's results (tools/equiv/sweep.py), one function at a time (maintainers).

  .venv/bin/python tools/equiv/record_sweep.py work/equiv_sweep_rename.jsonl [--dry-run]

MATCH (byte-exact already, but still noted as not): recorded with check.py, unless it is a known failure (it passes
here but not from a clean checkout). EQUIVALENT: proved again with the layer that proved it and recorded with
prove.py --record. Functions claimed by an open pull request are skipped. Prints what it did.
"""
import argparse, json, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "equiv"), os.path.join(ROOT, "tools", "contrib")]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("results")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    import task as T
    import prove
    known = {l.split()[0] for l in open(os.path.join(ROOT, "tools", "ci", "known_failures.txt"))
             if l.strip() and not l.startswith("#")}
    live = {va for va, c in (T.claims() or {}).items() if not T.stale(c)}
    eqv = set(T.equivalent())
    rows = [json.loads(l) for l in open(a.results) if l.strip()]
    n = {"match": 0, "equivalent": 0, "skipped": 0, "failed": 0}
    for r in rows:
        va = int(r["va"], 16)
        if va in live or va in eqv:
            n["skipped"] += 1
            continue
        if r["verdict"] == "MATCH" and r["va"] not in known:
            if a.dry_run:
                print("would record MATCH %s" % r["va"])
                continue
            out = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "contrib", "check.py"), "0x" + r["va"]],
                                 capture_output=True, text=True).stdout
            ok = out.startswith("MATCH")
            n["match" if ok else "failed"] += 1
            print("%s MATCH %s" % ("recorded" if ok else "FAILED", r["va"]))
        elif r["verdict"] == "EQUIVALENT":
            if a.dry_run:
                print("would record EQUIVALENT %s (%s %s)" % (r["va"], r["layer"], r["level"]))
                continue
            try:
                res = prove.run(va, [r["layer"]], 300.0, log=lambda s: None)
            except SystemExit as e:
                res = {"verdict": "ERROR", "detail": str(e)}
            if res["verdict"] == "EQUIVALENT":
                prove.record(va, res)
                n["equivalent"] += 1
            else:
                n["failed"] += 1
                print("FAILED EQUIVALENT %s: %s" % (r["va"], res.get("verdict")))
    print(n)


if __name__ == "__main__":
    main()
