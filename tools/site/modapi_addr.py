#!/usr/bin/env python3
"""Map Spore-ModAPI's function addresses onto this build (SporeApp.exe of 2024-09-30), for module attribution.

ModAPI (github.com/Spore-Community/Spore-ModAPI, SourceCode/DLL/Addresses*.cpp) names about 2,600 functions as
`DefineAddress(Name, SelectAddress(<disk>, <March 2017 Steam>))` inside `namespace Addresses(<Class>)`.  Our build is a
later relink of the 2017 Steam code, so its addresses differ by a piecewise-constant shift.  The shift is learned from
name anchors: ModAPI functions whose `Class::Name` matches exactly one function named through the development build's
debug database (symbols/pdb_names.json).  A ModAPI address is then mapped when

  bracket:  the anchors just below and just above it have the same shift, and that shift lands on a function start, or
  support:  among the shifts of anchors within 0x40000, one lands this address and at least four other ModAPI
            addresses within 0x2000 on function starts, two more than any other shift.

Leave-one-out over the 149 anchors (2026-11-14): bracket 82 right / 5 wrong, support 119 / 12.

Maintainer tool input: a copy of ModAPI's SourceCode/DLL in work/modapi/DLL (not in the repository).

  .venv/bin/python tools/site/modapi_addr.py [DLL dir]     prints the counts
"""
import bisect, collections, glob, gzip, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DLL = os.path.join(ROOT, "work", "modapi", "DLL")


def rows(dll=DLL):
    out = []
    for f in sorted(glob.glob(os.path.join(dll, "Addresses*.cpp"))):
        cur = None
        for line in open(f, errors="replace"):
            m = re.search(r"namespace Addresses\((\w+)\)", line)
            if m:
                cur = m.group(1)
            m = re.search(r"DefineAddress\((\w+),\s*SelectAddress\(\s*(0x[0-9A-Fa-f]+)\s*,\s*(0x[0-9A-Fa-f]+)", line)
            if m:
                out.append(dict(file=os.path.basename(f)[len("Addresses"):-len(".cpp")], ns=cur, name=m.group(1),
                                steam=int(m.group(3), 16)))
    return out


def _norm(s):
    return re.sub(r"^c", "", (s or "").lower())


def mapping(fstarts, dll=DLL):
    """{our va: (ModAPI file category, ModAPI class)} for every ModAPI function placed on one of `fstarts`."""
    R = rows(dll)
    if not R:
        return {}
    named = collections.defaultdict(list)
    for va, e in json.load(open(os.path.join(ROOT, "symbols", "pdb_names.json"))).items():
        parts = (e.get("name") or "").split("::")
        if len(parts) >= 2:
            named[(_norm(parts[-2]), _norm(parts[-1]))].append(int(va, 16))
    anch = sorted((r["steam"], c[0]) for r in R for c in [named.get((_norm(r["ns"]), _norm(r["name"])))]
                  if c and len(c) == 1)
    keys = [a for a, _ in anch]
    allm = sorted({r["steam"] for r in R})

    def bracket(a):
        i = bisect.bisect_left(keys, a)
        if 0 < i < len(anch):
            o1, o2 = anch[i - 1][1] - anch[i - 1][0], anch[i][1] - anch[i][0]
            if o1 == o2 and a + o1 in fstarts:
                return a + o1
        return None

    def support(a, W=0x2000, Rr=0x40000, minsup=4, margin=2):
        lo, hi = bisect.bisect_left(keys, a - Rr), bisect.bisect_right(keys, a + Rr)
        nb = allm[bisect.bisect_left(allm, a - W):bisect.bisect_right(allm, a + W)]
        sc = sorted(((sum(1 for b in nb if b + o in fstarts), o) for o in {anch[j][1] - anch[j][0] for j in range(lo, hi)}
                     if a + o in fstarts), reverse=True)
        if not sc or sc[0][0] < minsup or (len(sc) > 1 and sc[0][0] - sc[1][0] < margin):
            return None
        return a + sc[0][1]

    out = {}
    for r in R:
        h = bracket(r["steam"]) or support(r["steam"])
        if h is not None:
            out[h] = (r["file"], r["ns"])
    return out


if __name__ == "__main__":
    fs = {int(d["va"], 16) for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt"))}
    m = mapping(fs, sys.argv[1] if len(sys.argv) > 1 else DLL)
    print("%d ModAPI rows, %d placed on this build" % (len(rows(sys.argv[1] if len(sys.argv) > 1 else DLL)), len(m)))
