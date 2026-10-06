#!/usr/bin/env python3
"""Recompile every manifested source and verify each listed function byte-for-byte.

usage: run_all.py [--filter substr] [-v] [--manifest path] [--jobs N]

Manifests: match/manifest.txt, match/slices/*/manifest.txt, match/clones.txt, match/synth/*.manifest.
Each distinct (source, flags) pair is compiled once, in parallel, into its own object file; every
function is then compared in-process (relocations masked on both sides). Only one run_all may run
at a time (work/run_all.lock). Results are written to work/verify_results.json.
Exit 0 iff every listed function matches.
"""
import argparse, bisect, fcntl, glob, json, os, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile
from cmpobj import parse_coff, REL_SIZES
import imgcache

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
OUT = os.path.join(ROOT, "work", "match")
DEFAULT_FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
INCLUDE = "/I" + "Z:" + os.path.join(ROOT, "match", "include").replace("/", "\\")


def winpath(p):
    return "Z:" + p.replace("/", "\\")


def obj_path(src, flags):
    return os.path.join(OUT, src.replace("/", "_").rsplit(".", 1)[0] + "_" +
                        "".join(f.strip("/") for f in flags).replace(":", "") + ".obj")


def manifests(only=None):
    if only:
        return [only]
    m = [os.path.join(ROOT, "match", "manifest.txt")]
    m += sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt")))
    if os.path.exists(os.path.join(ROOT, "match", "clones.txt")):
        m.append(os.path.join(ROOT, "match", "clones.txt"))
    m += sorted(glob.glob(os.path.join(ROOT, "match", "synth", "*.manifest")))
    return m


def read_rows(paths, filt):
    rows = []
    for m in paths:
        for line in open(m):
            p = line.split("#", 1)[0].split()
            if len(p) >= 3 and filt in " ".join(p):
                rows.append((p[0], p[1], int(p[2], 16), tuple(p[3:]) or tuple(DEFAULT_FLAGS)))
    return rows


def compile_one(key):
    src, flags = key
    obj = obj_path(src, list(flags))
    r = subprocess.run([os.path.join(ROOT, "tools", "matching", "cl.sh"), "/nologo", "/c", *flags, INCLUDE,
                        "/Fo" + winpath(obj), winpath(os.path.join(ROOT, "match", src))],
                       capture_output=True, text=True)
    return key, (obj if r.returncode == 0 else None), (r.stdout + r.stderr)[-2000:]


class Original:
    def __init__(self):
        pe = pefile.PE(IMAGE, fast_load=True)
        self.pe, self.base = pe, pe.OPTIONAL_HEADER.ImageBase
        self.relocs = imgcache.relocs(IMAGE)  # sorted HIGHLOW reloc RVAs, cached (was ~1.6 s per run)

    def bytes_and_mask(self, va, n):
        rva = va - self.base
        data = self.pe.get_data(rva, n)
        mask = set()
        i = bisect.bisect_left(self.relocs, rva - 3)
        while i < len(self.relocs) and self.relocs[i] < rva + n:
            for k in range(4):
                j = self.relocs[i] + k - rva
                if 0 <= j < n:
                    mask.add(j)
            i += 1
        return data, mask


def resolve(syms, sym):
    if sym in syms:
        return sym
    c = [s for s in syms if sym in s and not s.startswith(("__ehhandler", "__unwindfunclet", "__catch", "__tryend"))]
    return c[0] if len(c) == 1 else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--filter", default=""); ap.add_argument("-v", action="store_true")
    ap.add_argument("--manifest"); ap.add_argument("--jobs", type=int, default=6)
    a = ap.parse_args()
    os.makedirs(OUT, exist_ok=True)
    lock = open(os.path.join(ROOT, "work", "run_all.lock"), "w")
    try:
        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        sys.exit("another run_all.py is already running (work/run_all.lock)")

    rows = read_rows(manifests(a.manifest), a.filter)
    keys = sorted(set((r[0], r[3]) for r in rows))
    objs = {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, (key, obj, log) in enumerate(ex.map(compile_one, keys)):
            objs[key] = obj
            if obj is None:
                print("COMPILE FAIL %s %s\n%s" % (key[0], " ".join(key[1]), log))
            if a.v and i % 25 == 0:
                print("compiled %d/%d" % (i + 1, len(keys)), flush=True)

    orig = Original()
    coff_cache = {}
    results, ok = {}, 0
    for src, sym, va, flags in rows:
        obj = objs.get((src, flags))
        status = "FAIL no object"
        if obj:
            if obj not in coff_cache:
                secs_, syms_ = parse_coff(obj)
                starts = {}
                for si_, off_ in syms_.values():
                    starts.setdefault(si_, set()).add(off_)
                coff_cache[obj] = (secs_, syms_, {k: sorted(v) for k, v in starts.items()})
            secs, syms, starts = coff_cache[obj]
            name = resolve(syms, sym)
            if name is None:
                status = "FAIL symbol %s not found/ambiguous" % sym
            else:
                si, off = syms[name]
                sec = secs[si]
                nxt = [o for o in starts.get(si, []) if o > off]
                mine = sec["data"][off:nxt[0] if nxt else len(sec["data"])]
                if nxt:  # strip int3 padding between functions in a shared section
                    mine = mine.rstrip(b"\xcc")
                n = len(mine)
                theirs, mask_o = orig.bytes_and_mask(va, n)
                mask = set(mask_o)
                for v, _s, t in sec["relocs"]:
                    for k in range(REL_SIZES.get(t, 4)):
                        if off <= v + k < off + n:
                            mask.add(v + k - off)
                diffs = [i for i in range(n) if i not in mask and theirs[i] != mine[i]]
                status = "MATCH" if not diffs else "DIFF %d bytes" % len(diffs)
        results["%08x" % va] = {"src": src, "sym": sym, "status": status}
        if status == "MATCH":
            ok += 1
            if a.v:
                print("MATCH  %-40s %08x" % (sym[:40], va))
        else:
            print("%-6s %-40s %08x  %s" % (status.split()[0], sym[:40], va, status))
    json.dump(results, open(os.path.join(ROOT, "work", "verify_results.json"), "w"))
    print("\n%d / %d functions byte-exact (%d sources compiled)" % (ok, len(rows), len(keys)))
    return 0 if ok == len(rows) else 1


if __name__ == "__main__":
    sys.exit(main())
