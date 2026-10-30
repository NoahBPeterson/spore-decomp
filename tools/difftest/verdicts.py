#!/usr/bin/env python3
"""verdicts.py: equivalence evidence for the equivalent-but-not-exact functions, from sweep results.

usage: verdicts.py --from DIR [DIR ...]      # write docs/equiv_verdicts.json + one docs/equiv_history.json point
       verdicts.py --backfill DIR [DIR ...]  # one history point per sweep directory (time = its newest result)
       verdicts.py                           # print the current breakdown

A sweep directory holds equiv.py --json results named <id>_<va>.json (tools/difftest/sweep_nonmatching.py --out DIR).
With --from, every current src module nonmatching row takes the newest result measured for that row's own module
(the module whose compiled object defines the VA; sweep_nonmatching.rows keeps one row per VA, from its defining
module); rows without a result count as "not run". A switch function with a complete case sweep
(work/difftest/cases/<module>_<va>.json, tools/difftest/case_sweep.py) takes its verdict from that instead: FAIL
when a case FAILs, PASS when every case PASSes, WEAK otherwise. Categories (each row exactly one):
  pass        PASS / PASS-FP: outputs matched on every valid input and every control-flow edge (each branch's taken
              and fall-through side, each jump-table target) of both sides was exercised
  weak        WEAK / WEAK-FP: outputs matched, but some edges never ran (instruction coverage can still be 100%)
  fail        FAIL: a mismatch on some input (the row's note says whether it is a harness artifact)
  inputs      UNSUPPORTED because random inputs were mostly invalid (virtual calls on soup objects, faults, ...)
  harness     UNSUPPORTED for a harness reason (resolution audit, own copies of constants, unresolved symbols, ...)
  comdat      no callable symbol, but the enclosing COMDAT is byte-identical (tools/difftest/comdat_check.py:
              cmpobj over the parent's COMDAT range, so the fragment's bytes are covered) - verified statically,
              never executed
  comdatdiff  no callable symbol and the enclosing COMDAT differs: the fragment sits inside a parent that does NOT
              match, so its bytes are not verified either
  funclet     no callable symbol and no COMDAT verdict yet (not yet run through comdat_check.py)
  not_run     no result (timeout, crash, or never swept)
"""
import argparse, datetime, glob, json, os, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
CUR = os.path.join(ROOT, "docs", "equiv_verdicts.json")
HIST = os.path.join(ROOT, "docs", "equiv_history.json")
CATS = ("pass", "weak", "fail", "inputs", "harness", "comdat", "comdatdiff", "funclet", "not_run")


def load(path):
    try:
        d = json.load(open(path))
    except (OSError, ValueError):
        return None
    d = d[0] if isinstance(d, list) and d else d
    return d if isinstance(d, dict) else None


def category(d):
    v = (d or {}).get("verdict")
    if isinstance(v, str) and v.startswith("BYTE-EXACT-COMDAT"):
        return "comdat"
    if isinstance(v, str) and v.startswith("COMDAT-DIFFERS"):
        return "comdatdiff"
    if v in ("PASS", "PASS-FP"):
        return "pass"
    if v in ("WEAK", "WEAK-FP"):
        return "weak"
    if v == "FAIL":
        return "fail"
    if v == "UNSUPPORTED":
        r = d.get("reason", "")
        if r.startswith("our symbol not found"):
            return "funclet"
        if r.startswith("only ") and "inputs valid" in r:
            return "inputs"
        return "harness"
    return "not_run"


CASES_DIR = os.path.join(ROOT, "work", "difftest", "cases")


def case_sweep(module, va):
    """A switch function's case-by-case verdict (tools/difftest/case_sweep.py), or None: FAIL when a case FAILs,
    PASS when every case PASSes, WEAK otherwise (UNREACHED/ERROR cases count as not covered). Results marked
    stale (measured on other code) are left out; a sweep that has not recorded every case is not used."""
    path = os.path.join(CASES_DIR, "%s_%s.json" % (module, va))
    try:
        doc = json.load(open(path))
    except (OSError, ValueError):
        return None
    cases = {k: c for k, c in doc.get("cases", {}).items() if not c.get("stale")}
    total = doc.get("total") or len(cases)
    if not cases or len(cases) < total:
        return None
    # Alternate runs of some cases under other input options (<module>_<va>.<tag>.json, e.g. operand hints): each
    # is a complete comparison of the same code, so a case takes the strongest evidence across files -- a FAIL in
    # any file is a FAIL, else a PASS in any file is a PASS
    alts = 0
    for alt in sorted(glob.glob(os.path.join(CASES_DIR, "%s_%s.*.json" % (module, va)))):
        try:
            ad = json.load(open(alt))
        except (OSError, ValueError):
            continue
        for k, c in ad.get("cases", {}).items():
            if c.get("stale") or k not in cases:
                continue
            rank = {"FAIL": 2, "PASS": 1}
            if rank.get(c.get("verdict"), 0) > rank.get(cases[k].get("verdict"), 0):
                cases[k] = c
                alts += 1
    n = {}
    for c in cases.values():
        n[c.get("verdict")] = n.get(c.get("verdict"), 0) + 1
    v = "FAIL" if n.get("FAIL") else "PASS" if n.get("PASS") == total else "WEAK"
    older = sum(1 for c in cases.values() if c.get("older_harness"))
    reason = "case sweep (%s): %s of %d cases%s%s" % (
        os.path.relpath(path, ROOT), ", ".join("%s %d" % kv for kv in sorted(n.items())), total,
        "; %d measured by an older harness on the same code" % older if older else "",
        "; %d taken from alternate runs" % alts if alts else "")
    return {"verdict": v, "reason": reason, "cases": n, "when": doc.get("when")}


_SIZES = None


def size_of(d, va):
    """The original function's size: from the result, else from work/index/functions.csv (results that stop
    before the analysis, e.g. a resolution-audit UNSUPPORTED, carry none)."""
    global _SIZES
    try:
        n = int((d or {}).get("orig_size") or 0)
    except (TypeError, ValueError):
        n = 0
    if n:
        return n
    if _SIZES is None:
        import csv
        try:   # Mount & Blade's index names the column size_bytes, Spore's size
            _SIZES = {r["address"].lower(): int(r.get("size_bytes") or r["size"]) for r in csv.DictReader(open(os.path.join(ROOT, "work", "index", "functions.csv")))}
        except OSError:
            _SIZES = {}
    return _SIZES.get(va.lower(), 0)


def summarize(items):
    """items: [(category, size)] -> {cat: count, cat_sz: bytes}."""
    out = {c: 0 for c in CATS}
    out.update({c + "_sz": 0 for c in CATS})
    for c, n in items:
        out[c] += 1
        out[c + "_sz"] += n
    return out


def add_history(point):
    try:
        hist = json.load(open(HIST))
    except (OSError, ValueError):
        hist = {}
    hist[point["when"]] = point
    with open(HIST, "w") as f:
        json.dump(dict(sorted(hist.items())), f, indent=1)
        f.write("\n")


def newest(d):
    ts = [os.path.getmtime(f) for f in glob.glob(os.path.join(d, "*.json"))]
    return datetime.datetime.fromtimestamp(max(ts)).astimezone().isoformat(timespec="seconds")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--from", dest="src", nargs="+")
    ap.add_argument("--backfill", nargs="+")
    a = ap.parse_args()
    if a.backfill:
        for d in a.backfill:
            items = []
            for f in glob.glob(os.path.join(d, "*.json")):
                if not f.endswith("tally.json"):
                    r = load(f)
                    items.append((category(r), size_of(r, os.path.basename(f)[:-5].rsplit("_", 1)[-1])))
            p = dict(summarize(items), when=newest(d), source=os.path.relpath(d, ROOT), rows=len(items))
            add_history(p)
            print(p["when"], p["source"], {c: p[c] for c in CATS})
        return 0
    if a.src:
        from sweep_nonmatching import rows
        res, src_dirs = {}, [os.path.abspath(d) for d in a.src]
        for r in rows():
            # Spore still has most rows in match/slices (Mount & Blade skipped slice rows: everything there lives in
            # a src module since its migration wave M4)
            name = "%s_%s.json" % (r["id"].replace("/", "__"), r["va"])
            # r["id"] is the module whose compiled object defines the VA (sweep_nonmatching.rows keeps one
            # row per VA, from its defining module), so only that module's results count: another module's
            # result for the same VA is a measurement of a different object and must not be reported here.
            # The row's own module file, and the NEWEST measurement across the source directories wins: the dirs hold a
            # mix of sweep generations (after2 is newer than parts of sweep), so neither the argument order nor a
            # single "current" dir is reliable.
            cands = [os.path.join(sd, name) for sd in src_dirs]
            cands = [c for c in cands if os.path.exists(c)]
            d = load(max(cands, key=os.path.getmtime)) if cands else None
            cs = case_sweep(r["id"], r["va"])
            if cs is not None:
                # a switch function swept case by case: one whole-function run never gets past its dispatch
                # (random selectors), so the case sweep is the evidence; the whole-function result keeps its size
                sz = size_of(d, r["va"])
                d = dict(d or {}, verdict=cs["verdict"], reason=cs["reason"])
                res[r["va"]] = {"module": r["id"], "file": r["file"], "verdict": cs["verdict"],
                                "category": category(d), "size": sz, "cases": cs["cases"], "source": "case-sweep"}
                continue
            res[r["va"]] = {"module": r["id"], "file": r["file"], "verdict": (d or {}).get("verdict"),
                            "category": category(d), "size": size_of(d, r["va"])}
        when = max(newest(d) for d in src_dirs)
        head = os.popen("git -C '%s' rev-parse --short HEAD" % ROOT).read().strip()
        summ = summarize((v["category"], v["size"]) for v in res.values())
        doc = {"when": when, "commit": head, "sources": [os.path.relpath(d, ROOT) for d in src_dirs],
               "summary": summ, "rows": dict(sorted(res.items()))}
        with open(CUR, "w") as f:
            json.dump(doc, f, indent=0, sort_keys=False)
            f.write("\n")
        add_history(dict(summ, when=when, source="+".join(doc["sources"]), rows=len(res)))
    doc = json.load(open(CUR))
    s = doc["summary"]
    tot = sum(s[c] for c in CATS)
    print("equivalence evidence, %d nonmatching rows (results from %s, at %s):" % (tot, ", ".join(doc["sources"]), doc["when"]))
    for c in CATS:
        print("  %-8s %5d  %5.1f%%   %7.1f KB" % (c, s[c], 100.0 * s[c] / tot if tot else 0, s[c + "_sz"] / 1024))
    return 0


if __name__ == "__main__":
    sys.exit(main())
