#!/usr/bin/env python3
"""Emit per-object no-source worklists: the functions of an object file that have no
committed source anywhere (not a byte-exact slice, nonmatching, partial, synth, or a
migrated module), ordered by hybrid coverage (most-executed first), then size.

usage: worklist.py [ObjectSubstr ...]        # default: the six low-coverage targets
       worklist.py --all --min-bytes 64      # every object, small functions dropped
Writes work/migrate/worklists/<object>.txt (object slug, path-safe).

Columns: va  bytes  cov2  cov0  how  conf  symbol  dev_va
"""
import argparse, collections, csv, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
OUT = W("work/migrate/worklists")

DEFAULT = ["SPCellGame", "SPAnimalBehaviorTrees", "SPTribeBehaviorTrees",
           "SPCreatureBase", "SPTerrainSphere", "SPAudio"]


def norm(s):
    s = str(s).strip()
    if s.startswith("0x"):
        return int(s, 16)
    if re.fullmatch(r"[0-9a-fA-F]{6,8}", s):
        return int(s, 16)
    return int(s)


def committed_source():
    """VAs that already have committed source, by any route."""
    have = set()

    def lines(path, col):
        for line in open(path, errors="ignore"):
            p = line.split("#", 1)[0].split()
            if len(p) > col:
                try:
                    have.add(norm(p[col]))
                except ValueError:
                    pass

    for f in glob.glob(W("match/slices/*/manifest.txt")):
        lines(f, 2)
    for f in glob.glob(W("match/slices/*/nonmatching.txt")) + glob.glob(W("match/slices/*/partial.txt")):
        lines(f, 0)
    for f in glob.glob(W("match/synth/*.manifest")):
        lines(f, 2)
    if os.path.exists(W("match/manifest.txt")):
        lines(W("match/manifest.txt"), 2)
    if os.path.exists(W("match/clones.txt")):
        lines(W("match/clones.txt"), 2)
    for f in glob.glob(W("src/game/**/manifest.txt"), recursive=True):
        lines(f, 2)
    for f in glob.glob(W("src/game/**/nonmatching.txt"), recursive=True) + \
             glob.glob(W("src/game/**/partial.txt"), recursive=True):
        lines(f, 0)
    return have


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objects", nargs="*", default=None)
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--min-bytes", type=int, default=0)
    ap.add_argument("--min-cov", type=int, default=0, help="drop functions executed fewer than this many times (cov2)")
    a = ap.parse_args()

    have = committed_source()
    mod = json.load(open(W("work/migrate/modmap.json")))
    fns = mod["functions"]
    cov2 = json.load(open(W("work/hybrid/cov2.json"))) if os.path.exists(W("work/hybrid/cov2.json")) else {}
    cov0 = json.load(open(W("work/hybrid/cov0.json"))) if os.path.exists(W("work/hybrid/cov0.json")) else {}

    by_obj = collections.defaultdict(list)
    for k, d in fns.items():
        try:
            va = norm(k)
        except ValueError:
            continue
        if d.get("size", 0) < a.min_bytes:
            continue
        if va in have:
            continue
        c2 = cov2.get("%08x" % va, 0) + cov2.get("%x" % va, 0)
        if c2 < a.min_cov:
            continue
        by_obj[d.get("module", "") or "(no module)"].append(va)

    os.makedirs(OUT, exist_ok=True)
    want = None if a.all else (a.objects or DEFAULT)
    written = []
    for obj, vas in sorted(by_obj.items()):
        if want is not None and not any(w in obj for w in want):
            continue
        vas.sort(key=lambda v: (-(cov2.get("%08x" % v, 0) + cov2.get("%x" % v, 0)), v))
        slug = obj.replace("/", "_").replace(".obj", "")
        path = os.path.join(OUT, slug + ".txt")
        with open(path, "w") as fh:
            fh.write("# %s  no-source worklist  (%d functions)\n" % (obj, len(vas)))
            fh.write("# va        bytes  cov2   cov0   how              conf  symbol  dev_va\n")
            for va in vas:
                d = fns.get("%08x" % va) or fns.get(hex(va)[2:]) or {}
                name = d.get("name") or ("FUN_%08x" % va)
                fh.write("%08x  %6d  %5d  %5d  %-16s  %.1f  %s  %s\n" % (
                    va, d.get("size", 0),
                    cov2.get("%08x" % va, 0) + cov2.get("%x" % va, 0),
                    cov0.get("%08x" % va, 0) + cov0.get("%x" % va, 0),
                    d.get("how", "?"), d.get("confidence", 0.0), name, d.get("dev") or "-"))
        written.append((obj, len(vas), path))
    for obj, n, path in written:
        print("%6d  %s  -> %s" % (n, obj, os.path.relpath(path, ROOT)))
    print("total %d objects, %d functions" % (len(written), sum(n for _, n, _ in written)))


if __name__ == "__main__":
    main()
