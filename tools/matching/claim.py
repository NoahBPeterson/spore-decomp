#!/usr/bin/env python3
"""claim.py <batch> <worker>  — take slices from a batch's shared queue, one at a time.

Prints "slice <id>" and "functions <VAs>" like slice_info.py. While the worker's current slice still has VAs in none of
manifest.txt / nonmatching.txt / partial.txt, it prints that slice again (with the count still unrecorded), so a session
that lost its context or was re-prompted resumes where it was. Once the slice is settled it claims the next unclaimed
slice in batch order. Prints "NO SLICE" (exit 1) when the queue is empty and the worker's slice is settled.

Queue waves (2026-10-21): with fixed ranges per session the wave's length was set by its slowest ranges (gold4: 28
sessions busy at 23:00, 5 at 03:00); with a shared queue a session that finishes early takes more work instead of
stopping. Claims live in work/opencode/claims_<batch>.json (not work/batches/, which holds batches only), guarded by
a lock file; `claim.py <batch> --status` prints them.
"""
import fcntl, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)


def claims_path(batch):
    return W("work/opencode", "claims_%s.json" % batch)


def load_claims(batch):
    """{"claims": {index (str): worker (str)}}; missing file = nothing claimed."""
    p = claims_path(batch)
    return json.load(open(p)) if os.path.exists(p) else {"claims": {}}


def unrecorded(entry):
    """VAs of a slice entry that are in none of its manifest (VA = 3rd column), nonmatching or partial rows.
    A rework entry ("rework": true, batch part1 on: functions that are already partial) is settled per VA once the
    VA is in manifest.txt or nonmatching.txt, or the session logged "<va> <verdict> <reason>" in
    work/match/scratch_<id>_fixlog.txt (it could not be completed); a partial.txt row alone does not count.
    VAs in the entry's "fail" list (or "asm": a nonmatching row whose source is an __asm transcription) (equivalence FAILs folded into a rework batch, 2026-10-24) already have a
    nonmatching.txt row, so they settle only by a manifest row or a fixlog line."""
    want = {v.lower().lstrip("0") for v in entry["vas"]}
    fail = {v.lower().lstrip("0") for v in entry.get("fail", []) + entry.get("asm", [])}
    seen = set()
    files = (("manifest.txt", 2), ("nonmatching.txt", 0)) if entry.get("rework") else \
        (("manifest.txt", 2), ("nonmatching.txt", 0), ("partial.txt", 0))
    if entry.get("rework"):
        fl = W("work/match", "scratch_%s_fixlog.txt" % entry["id"])
        if os.path.exists(fl):
            for l in open(fl, errors="replace"):
                p = l.split()
                if len(p) >= 2 and re.fullmatch(r"(0x)?[0-9a-fA-F]{6,8}", p[0]):
                    seen.add((p[0][2:] if p[0].lower().startswith("0x") else p[0]).lower().lstrip("0"))
    for f, col in files:
        p = W("match/slices", entry["id"], f)
        if not os.path.exists(p):
            continue
        for l in open(p, errors="replace"):
            parts = l.split("#", 1)[0].split() if l[:1] not in " \t" else []
            if len(parts) > col:
                va = (lambda v: (v[2:] if v.startswith("0x") else v).lstrip("0"))(parts[col].lower())
                if f == "manifest.txt" or va not in fail:
                    seen.add(va)
    return sorted(want - seen)


def held(claims, worker):
    """Batch indices the worker has claimed, in claim order (= batch order)."""
    return sorted(int(i) for i, w in claims["claims"].items() if w == str(worker))


def worker_progress(batch, recs, worker, unsettled=None):
    """(functions, settled, slices left in the queue) over the slices the worker has claimed, for opencode_sup.py and
    opencode_drain.py; `unsettled` (a list) gets '<slice>:<n> unrecorded' for each unsettled claimed slice."""
    c = load_claims(batch)
    tot = done = 0
    for i in held(c, worker):
        u = len(unrecorded(recs[i]))
        tot += len(recs[i]["vas"])
        done += len(recs[i]["vas"]) - u
        if u and unsettled is not None:
            unsettled.append("%s:%d unrecorded" % (recs[i]["id"], u))
    return tot, done, len(recs) - len(c["claims"])


def print_fails(e):
    """Equivalence FAILs folded into a rework entry: the replay command, and the src/game unit holding a migrated copy."""
    for v in e.get("asm", []):
        print("inline assembly %s: its source is an __asm/_emit transcription, which is forbidden. Rewrite it as plain "
              "C++ (check it with chk.py and equiv.py), or log \"%s FAIL-KEPT <why>\" if you cannot" % (v, v))
    for v in e.get("fail", []):
        print("equivalence FAIL %s: replay with .venv/bin/python tools/difftest/equiv.py %s %s --replay "
              "work/difftest/fail_inputs/%s_%s.pkl -v" % (v, e["id"], v, e["id"], v))
        if e.get("fail_src", {}).get(v):
            print("  %s also lives in %s (the hybrid build's copy): fix it there too and check it with "
                  "equiv.py %s %s --src %s" % (v, e["fail_src"][v], e["id"], v, e["fail_src"][v]))


def main():
    batch, worker = sys.argv[1], sys.argv[2]
    recs = json.load(open(W("work/batches", batch + ".json")))
    if worker == "--status":
        c = load_claims(batch)["claims"]
        for i in sorted(map(int, c)):
            print("%3d %-10s worker %-4s unrecorded %d" % (i, recs[i]["id"], c[str(i)], len(unrecorded(recs[i]))))
        print("claimed %d of %d" % (len(c), len(recs)))
        return 0
    if not re.fullmatch(r"\d+", worker):
        sys.exit("worker must be a number (the session's worker index)")
    os.makedirs(W("work/opencode"), exist_ok=True)
    with open(claims_path(batch) + ".lock", "w") as lk:
        fcntl.flock(lk, fcntl.LOCK_EX)
        c = load_claims(batch)
        mine = held(c, worker)
        if mine and unrecorded(recs[mine[-1]]):
            i = mine[-1]
            print("slice", recs[i]["id"])
            print("functions", " ".join(recs[i]["vas"]))
            print_fails(recs[i])
            print("(you already hold this slice: %d of its %d functions are not yet in manifest/nonmatching/partial; "
                  "finish it before claiming another)" % (len(unrecorded(recs[i])), len(recs[i]["vas"])))
            return 0
        free = [i for i in range(len(recs)) if str(i) not in c["claims"]]
        if not free:
            print("NO SLICE")
            return 1
        i = free[0]
        c["claims"][str(i)] = str(worker)
        tmp = claims_path(batch) + ".tmp"
        json.dump(c, open(tmp, "w"), indent=1)
        os.replace(tmp, claims_path(batch))
    print("slice", recs[i]["id"])
    print("functions", " ".join(recs[i]["vas"]))
    print_fails(recs[i])
    print("(queue: %d slices left after this one)" % (len(free) - 1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
