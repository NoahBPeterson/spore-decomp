#!/usr/bin/env python3
"""Re-run equiv.py over a list of (slice, va) rows and compare the verdicts with a baseline.

usage: rebaseline.py <rows.json> [--out DIR] [--workers N=3] [--fpcw HEX] [--limit N] [--nice N=10] [--tally] [--confirm]

rows.json: a list of {"slice": "s00xxxxxx", "va": "00xxxxxx", ...} (extra keys are kept in the tally).
Each row runs as `equiv.py <slice> <va> --json <out>/<slice>_<va>.json [--fpcw HEX]` in its own
process; rows whose output file exists are skipped, so the run is restartable. --tally only prints the
comparison. Baseline verdict for a row: the newest work/difftest/backlog_shard*.json entry for the same
(slice, va), else the row's "recorded" key, else '-'.

Rows always run with --require-all, like the strict baseline runs (fixed 2026-10-17: the 10-14 and
10-16 runs omitted it, so their PASS verdicts must be re-derived from coverage["all"]).

Written 2026-10-14 for the x87 control-word re-baseline (docs/tickets.md P3): the harness moved from
0x027F to 0x007F, and the rows whose original code does x87 arithmetic are re-run at the new value.
"""
import argparse, collections, glob, json, os, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
PY = W(".venv/bin/python")
ORDER = {"PASS": 3, "WEAK": 2, "FAIL": 1, "UNSUPPORTED": 0, "-": -1, None: -1}


def baseline():
    b = {}
    for f in sorted(glob.glob(W("work/difftest/backlog_shard*.json")), key=os.path.getmtime):
        for r in json.load(open(f)):
            b[(r["slice"], r["va"].lower())] = r.get("verdict")
    return b


def run_one(row, out_dir, fpcw, nice):
    out = os.path.join(out_dir, "%s_%s.json" % (row["slice"], row["va"]))
    if os.path.exists(out):
        return row, "skip"
    # --require-all: the baseline shards are strict runs (a PASS needs every original instruction executed);
    # without it a 60%-coverage run reads as PASS and looks like an improvement over the baseline's WEAK.
    cmd = [PY, W("tools/difftest/equiv.py"), row["slice"], row["va"], "--json", out, "--require-all"]
    if fpcw:
        cmd += ["--fpcw", fpcw]
    t = time.time()
    try:
        p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=1200,
                           preexec_fn=(lambda: os.nice(nice)) if nice else None)
        log = p.stdout[-4000:] + p.stderr[-2000:]
    except subprocess.TimeoutExpired:
        log = "TIMEOUT after 1200s"
    open(out[:-5] + ".log", "w").write(log)
    if not os.path.exists(out):   # crashed or timed out: record it so the row is not retried forever
        json.dump([{"slice": row["slice"], "va": row["va"], "verdict": "ERROR", "reason": log[-300:]}], open(out, "w"))
    return row, "%.0fs" % (time.time() - t)


def tally(rows, out_dir):
    base = baseline()
    trans = collections.Counter()
    worse, better = [], []
    done = 0
    for row in rows:
        out = os.path.join(out_dir, "%s_%s.json" % (row["slice"], row["va"]))
        if not os.path.exists(out):
            continue
        done += 1
        try:
            new = json.load(open(out))[0].get("verdict")
        except Exception:
            new = "ERROR"
        old = base.get((row["slice"], row["va"].lower())) or row.get("recorded") or "-"
        trans[(old, new)] += 1
        if ORDER.get(new, -1) < ORDER.get(old, -1) and old != "-":
            worse.append((row["slice"], row["va"], old, new, row.get("x87")))
        elif ORDER.get(new, -1) > ORDER.get(old, -1):
            better.append((row["slice"], row["va"], old, new))
    print("rows done: %d of %d" % (done, len(rows)))
    print("%-12s %-12s %5s" % ("before", "after", "n"))
    for (o, n), k in sorted(trans.items(), key=lambda t: -t[1]):
        print("%-12s %-12s %5d" % (o, n, k))
    print("worse (%d):" % len(worse))
    for w in worse:
        print("  %s %s %s -> %s (x87 insns %s)" % w)
    print("better: %d" % len(better))
    return worse


def confirm(worse, out_dir, workers, nice):
    """Control run at the old control word (0x027F) for every row that got worse: a row that is also
    worse there regressed for another reason (tree drift since the baseline), not because of FPCW."""
    ctl = os.path.join(out_dir, "control027f")
    os.makedirs(ctl, exist_ok=True)
    rows = [{"slice": s, "va": v} for s, v, *_ in worse]
    with ThreadPoolExecutor(workers) as ex:
        list(ex.map(lambda r: run_one(r, ctl, "027F", nice), rows))
    kinds = collections.Counter()
    print("%-10s %-9s %-12s %-12s %-12s %s" % ("slice", "va", "baseline", "at 007F", "at 027F", "cause"))
    for s, v, old, new, x in worse:
        try:
            c = json.load(open(os.path.join(ctl, "%s_%s.json" % (s, v))))[0].get("verdict")
        except Exception:
            c = "ERROR"
        cause = "precision" if ORDER.get(c, -1) > ORDER.get(new, -1) else "drift"
        kinds[cause] += 1
        print("%-10s %-9s %-12s %-12s %-12s %s" % (s, v, old, new, c, cause))
    print("causes:", dict(kinds))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rows")
    ap.add_argument("--out", default=W("work/difftest/fpcw007f"))
    ap.add_argument("--workers", type=int, default=3)
    ap.add_argument("--fpcw")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--nice", type=int, default=10)
    ap.add_argument("--tally", action="store_true")
    ap.add_argument("--confirm", action="store_true",
                    help="after the tally, control-run every row that got worse at --fpcw 027F and label it precision or drift")
    a = ap.parse_args()
    rows = json.load(open(a.rows))
    if a.limit:
        rows = rows[:a.limit]
    os.makedirs(a.out, exist_ok=True)
    if not a.tally:
        n = 0
        with ThreadPoolExecutor(a.workers) as ex:
            for row, how in ex.map(lambda r: run_one(r, a.out, a.fpcw, a.nice), rows):
                n += 1
                if how != "skip":
                    print("%s %s %s (%d/%d)" % (row["slice"], row["va"], how, n, len(rows)), flush=True)
    worse = tally(rows, a.out)
    if a.confirm and worse:
        confirm(worse, a.out, a.workers, a.nice)


if __name__ == "__main__":
    main()
