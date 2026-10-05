#!/usr/bin/env python3
"""CI check: do the freshly built third-party objects still byte-match the original image?

usage: verify.py [--image work/SporeApp.analysis.bin] [--update-baseline] [--no-crt]
Runs tools/matching/libresolve.py (libmatch + relocation-target disambiguation) over work/third_party/obj/*,
attributes each unique placement (original VA) to a library, and compares with
third_party/baseline_matches.csv (columns va,lib,name; the set of original functions proven byte-identical).
Exit 1 if any baseline function is no longer matched (regression); gains are reported, and recorded with
--update-baseline. The CRT objects are not rebuilt here (from work/oss/obj/crt_*, informational).
"""
import argparse, collections, csv, os, subprocess, sys, tempfile

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
OBJ = os.path.join(ROOT, "work", "third_party", "obj")
BASE = os.path.join(ROOT, "third_party", "baseline_matches.csv")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--image", default=os.path.join(ROOT, "work", "SporeApp.analysis.bin"))
    ap.add_argument("--update-baseline", action="store_true")
    ap.add_argument("--no-crt", action="store_true")
    a = ap.parse_args()
    dirs = {l: os.path.join(OBJ, l) for l in sorted(os.listdir(OBJ)) if os.path.isdir(os.path.join(OBJ, l))}
    if not dirs:
        sys.exit("no objects in %s; run build_faithful.py" % OBJ)
    if not a.no_crt:
        for c in ("crt_msvcrt", "crt_msvcprt"):
            p = os.path.join(ROOT, "work", "oss", "obj", c)
            if os.path.isdir(p):
                dirs["crt:" + c] = p
    owner = {}
    for lib, d in dirs.items():
        for f in os.listdir(d):
            owner[(lib.split(":")[0] == "crt", f)] = "crt" if lib.startswith("crt") else lib
    obj_lib = {}
    for lib, d in dirs.items():
        for f in os.listdir(d):
            obj_lib[f] = "crt" if lib.startswith("crt") else lib
    with tempfile.TemporaryDirectory() as t:
        out = os.path.join(t, "res.csv")
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "libresolve.py"), a.image, out]
                           + list(dirs.values()), stdout=subprocess.PIPE, text=True)
        if r.returncode:
            sys.exit("libresolve failed")
        print(r.stdout.strip())
        rows = [x for x in csv.DictReader(open(out)) if x["status"] == "unique"]
    now = {}
    for x in rows:
        now.setdefault(int(x["va"], 16), (obj_lib.get(x["obj"], "?"), x["name"], x["obj"]))
    base = {}
    if os.path.exists(BASE):
        for x in csv.DictReader(open(BASE)):
            base[int(x["va"], 16)] = (x["lib"], x["name"])
    libs = sorted({v[0] for v in now.values()} | {v[0] for v in base.values()})
    bad = 0
    print("%-10s %9s %9s %6s %6s" % ("library", "baseline", "now", "lost", "gained"))
    for lib in libs:
        b = {va for va, v in base.items() if v[0] == lib}
        n = {va for va, v in now.items() if v[0] == lib}
        lost, gained = b - n, n - b
        bad += len(lost)
        print("%-10s %9d %9d %6d %6d" % (lib, len(b), len(n), len(lost), len(gained)))
        for va in sorted(lost)[:20]:
            print("   LOST %08x %s" % (va, base[va][1]))
    print("%-10s %9d %9d" % ("total", len(base), len(now)))
    if a.update_baseline:
        with open(BASE, "w") as f:
            f.write("va,lib,name\n")
            for va in sorted(now):
                f.write("%08x,%s,%s\n" % (va, now[va][0], now[va][1]))
        print("baseline updated: %s" % BASE)
    if bad:
        print("FAIL: %d baseline functions no longer match" % bad)
        sys.exit(1)
    print("OK")

if __name__ == "__main__":
    main()
