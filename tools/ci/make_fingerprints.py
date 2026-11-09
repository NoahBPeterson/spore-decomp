#!/usr/bin/env python3
"""Write fingerprints (tools/ci/fingerprint.py) of retail functions.  Maintainers only: needs the retail image
(work/SporeApp.analysis.bin), the function lists in work/ and the manifests.

usage: make_fingerprints.py [--vas FILE] [--out tools/ci/fingerprints.jsonl]
       --vas: one hex VA per line (default: every known function start)
"""
import argparse, csv, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import run_all as R             # noqa: E402
import fingerprint as F         # noqa: E402


def starts():
    """every function start we know: the Ghidra index, the module map, and every manifest/nonmatching row (the index
    alone misses some: 652 byte-exact rows ran into the next function)"""
    s = set()
    for f in glob.glob(os.path.join(ROOT, "work", "decomp_all", "index_*.csv")):
        for row in csv.reader(open(f)):
            if len(row) >= 3 and row[2].isdigit():
                s.add(int(row[0], 16))
    s |= {int(v, 16) for v in json.load(open(os.path.join(ROOT, "work", "migrate", "modmap.json")))["functions"]}
    for f in [g for d in ("match", os.path.join("src", "game")) for n in ("manifest.txt", "nonmatching.txt", "partial.txt")
              for g in glob.glob(os.path.join(ROOT, d, "**", n), recursive=True)]:
        for line in open(f, errors="replace"):
            for tok in line.split("#", 1)[0].split()[:3]:
                if len(tok) == 8:
                    try:
                        s.add(int(tok, 16))
                    except ValueError:
                        pass
    return sorted(s)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vas")
    ap.add_argument("--out", default=os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"))
    a = ap.parse_args()
    orig = R.Original()
    st = starts()
    sizes = F.retail_sizes(orig, st)
    want = [int(l.split()[0], 16) for l in open(a.vas) if l.strip()] if a.vas else st
    md, rng = F._disasm(), F.image_range(orig)
    n = 0
    with open(a.out, "w") as f:
        for va in sorted(set(want)):
            if va in sizes:
                f.write(json.dumps(F.make(orig, va, sizes[va], md, rng), separators=(",", ":")) + "\n")
                n += 1
    print("%d fingerprints -> %s (%d VAs had no size)" % (n, os.path.relpath(a.out, ROOT), len(set(want)) - n))


if __name__ == "__main__":
    main()
