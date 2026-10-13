#!/usr/bin/env python3
"""Retail address intervals per dev object file, for migration progress (docs/migration.md).

An object's functions are contiguous in retail .text (dev order ascends in retail; measured in
work/devbuild: within each linker zone every object is one segment, 5 order resets in 3,225
segments, all at zone boundaries). Retail splits ~4% of anchored objects into two or three real
intervals (DatabasePackedFile.obj: 47 functions near 0x6bbdd0 and 123 near 0x8d81d0), so an object
is a SET of intervals, each contiguous. Inside an interval everything belongs to the object: the
measured exceptions are single misnamed anchors and tiny dev objects that retail merged into
their neighbour, and both are reported as "foreign", never silently counted.

This gives a per-object denominator that is a count of real retail functions ("functions in the
interval"), not of modmap labels: an unassigned virtual inside the interval keeps the object open
until someone writes it. The only uncertainty is where an interval ends inside the gap before the
next object; that is reported as the bounding gap (upper bound), never folded into the count.

Interval = modmap runs of the same module merged when at most MERGE_MAX functions lie between
them (measured separations between same-object runs are 1-4 functions: a sandwiched anchor, an
unassigned function, or a merged tiny object).

  python3 tools/migrate/intervals.py --module DatabasePackedFile      # intervals of matching objects
  python3 tools/migrate/intervals.py --summary                          # distribution over all objects
"""
import bisect, collections, csv, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
MERGE_MAX = 8


def retail_functions():
    """{va: size} for every function in the Ghidra project (same source as tools/status.py)."""
    funcs = {}
    for f in glob.glob(W("work/decomp_all/index_*.csv")):
        for addr, name, size, status, lines in csv.reader(open(f)):
            funcs[int(addr, 16)] = int(size)
    return funcs


def compute(modmap, funcs):
    """-> {module: [interval]}; interval = dict(lo, hi, n, anchors, runs, foreign, unassigned,
    gap_before, gap_after). lo/hi are function VAs (inclusive); n counts retail functions in
    [lo, hi]; foreign = functions modmap assigns to another module; unassigned = functions modmap
    does not assign; gap_before/gap_after = unassigned functions contiguous outside the interval
    (the upper bound on where the object really ends)."""
    allva = sorted(funcs)
    assign = {int(va, 16): v["module"] for va, v in modmap["functions"].items()}
    runs = sorted(modmap["runs"], key=lambda r: int(r["lo"], 16))
    by_mod = collections.defaultdict(list)
    for r in runs:
        by_mod[r["module"]].append((int(r["lo"], 16), int(r["hi"], 16), r["anchors"]))
    out = {}
    for mod, rs in by_mod.items():
        merged = []
        for lo, hi, anchors in rs:
            if merged:
                plo, phi, pa, pr = merged[-1]
                between = bisect.bisect_left(allva, lo) - bisect.bisect_right(allva, phi)
                if between <= MERGE_MAX:
                    merged[-1] = (plo, hi, pa + anchors, pr + 1)
                    continue
            merged.append((lo, hi, anchors, 1))
        ivs = []
        for lo, hi, anchors, nruns in merged:
            i, j = bisect.bisect_left(allva, lo), bisect.bisect_right(allva, hi)
            inside = allva[i:j]
            foreign = sum(1 for v in inside if assign.get(v) not in (None, mod))
            unassigned = sum(1 for v in inside if v not in assign)
            gb = 0
            k = i - 1
            while k >= 0 and allva[k] not in assign:
                gb += 1; k -= 1
            ga = 0
            k = j
            while k < len(allva) and allva[k] not in assign:
                ga += 1; k += 1
            ivs.append(dict(lo=lo, hi=hi, n=len(inside), size=sum(funcs[v] for v in inside), anchors=anchors,
                            runs=nruns, foreign=foreign, unassigned=unassigned, gap_before=gb, gap_after=ga))
        out[mod] = ivs
    return out


def load(root=ROOT):
    """Intervals from work/migrate/modmap.json, or None when modmap has not been built."""
    p = os.path.join(root, "work/migrate/modmap.json")
    if not os.path.exists(p):
        return None
    return compute(json.load(open(p)), retail_functions())


def main(argv):
    ivs = load()
    if ivs is None:
        print("work/migrate/modmap.json missing: run tools/migrate/modmap.py first"); return 1
    if "--summary" in argv:
        strong = {m: [i for i in v if i["anchors"] >= 2] for m, v in ivs.items()}
        dist = collections.Counter(min(len(v), 4) for v in strong.values())
        print("objects:", len(ivs), " intervals with >=2 anchors per object:",
              " ".join("%d:%d" % kv for kv in sorted(dist.items())), "(4 = 4 or more)")
        n = sum(i["n"] for v in ivs.values() for i in v)
        f = sum(i["foreign"] for v in ivs.values() for i in v)
        u = sum(i["unassigned"] for v in ivs.values() for i in v)
        print("functions inside intervals: %d  foreign: %d  unassigned: %d" % (n, f, u))
        return 0
    pat = argv[argv.index("--module") + 1] if "--module" in argv else ""
    for mod in sorted(m for m in ivs if pat in m):
        print(mod)
        for i in ivs[mod]:
            print("  %08x-%08x  n=%-4d anchors=%-3d runs=%d foreign=%d unassigned=%d  gap before/after=%d/%d%s" % (
                i["lo"], i["hi"], i["n"], i["anchors"], i["runs"], i["foreign"], i["unassigned"],
                i["gap_before"], i["gap_after"], "" if i["anchors"] else "  (no anchor: weak)"))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
