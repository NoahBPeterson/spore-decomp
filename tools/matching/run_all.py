#!/usr/bin/env python3
"""Recompile every source in match/manifest.txt and verify each listed function byte-for-byte.

usage: run_all.py [--filter substr] [-v]
Prints a tally; exit 0 iff every listed function matches.
"""
import argparse, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
OUT = os.path.join(ROOT, "work", "match")
DEFAULT_FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
INCLUDE = "/I" + "Z:" + os.path.join(ROOT, "match", "include").replace("/", "\\")

def winpath(p):
    return "Z:" + p.replace("/", "\\")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--filter", default=""); ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    rows = []
    for line in open(os.path.join(ROOT, "match", "manifest.txt")):
        line = line.split("#", 1)[0].split()
        if len(line) >= 3 and a.filter in " ".join(line):
            rows.append((line[0], line[1], line[2], line[3:] or DEFAULT_FLAGS))
    os.makedirs(OUT, exist_ok=True)
    built = {}
    ok = 0
    for src, sym, va, flags in rows:
        key = (src, tuple(flags))
        if key not in built:
            obj = os.path.join(OUT, src.replace("/", "_").rsplit(".", 1)[0] + "_" +
                               "".join(f.strip("/") for f in flags).replace(":", "") + ".obj")
            r = subprocess.run([os.path.join(ROOT, "tools", "matching", "cl.sh"), "/nologo", "/c", *flags, INCLUDE,
                                "/Fo" + winpath(obj), winpath(os.path.join(ROOT, "match", src))],
                               capture_output=True, text=True)
            if r.returncode != 0:
                print("COMPILE FAIL %s:\n%s" % (src, r.stdout + r.stderr))
            built[key] = obj if r.returncode == 0 else None
        obj = built[key]
        if obj is None:
            print("FAIL   %-28s %s (no object)" % (sym, va)); continue
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "cmpobj.py"),
                            IMAGE, obj, sym, va] + ([] if a.v else ["--quiet"]),
                           capture_output=True, text=True)
        if r.returncode == 0:
            ok += 1
            print("MATCH  %-28s %s" % (sym, va))
        else:
            print("DIFF   %-28s %s\n%s" % (sym, va, r.stdout.rstrip()))
    print("\n%d / %d functions byte-exact" % (ok, len(rows)))
    return 0 if ok == len(rows) else 1

if __name__ == "__main__":
    sys.exit(main())
