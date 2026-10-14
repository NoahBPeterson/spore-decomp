#!/usr/bin/env python3
"""Compile a scratch file of candidate functions and rank each against an original VA.

usage: try_variants.py <file.cpp> <va-hex> [cl flags...]
Every function symbol in the object is compared; prints diff-byte counts, best first.
"""
import os, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmpobj import parse_coff
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src, va = sys.argv[1], int(sys.argv[2], 16)
flags = sys.argv[3:] or ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
os.makedirs(os.path.join(ROOT, "work", "match", "variants"), exist_ok=True)
obj = os.path.join(ROOT, "work", "match", "variants",
                   os.path.abspath(src).replace(ROOT, "").strip("/").replace("/", "_") + ".obj")
w = lambda p: "Z:" + os.path.abspath(p).replace("/", "\\")
r = subprocess.run([os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", *flags, "/I" + w(os.path.join(ROOT, "match", "include")), "/Fo" + w(obj), w(src)],
                   capture_output=True, text=True)
if r.returncode:
    sys.exit(r.stdout + r.stderr)
secs, syms = parse_coff(obj)
pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
res = []
for name, (si, off) in syms.items():
    sec = secs[si]
    # The window is this function's extent: up to the next symbol in the same section (one function per
    # section under /Gy, which /O1 /O2 /Ox imply; /Od without /Gy packs the TU into one .text), minus the
    # int3 alignment padding cl puts before the next function. Scoring to end-of-section let the following
    # functions' bytes pollute the ranking (docs/tickets.md P3).
    nxt = min([o for s, o in syms.values() if s == si and o > off] + [len(sec["data"])])
    mine = sec["data"][off:nxt]
    if nxt < len(sec["data"]):
        mine = mine.rstrip(b"\xcc") or mine
    mask = {v + k - off for v, _, t in sec["relocs"] for k in range(4)}
    orig = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, len(mine))
    d = sum(1 for i in range(len(mine)) if i not in mask and mine[i] != orig[i])
    res.append((d, len(mine), name))
best = min(res)[2] if res else None
for d, n, name in sorted(res):
    print("%4d diff / %3d bytes  %s%s" % (d, n, name, "   <== MATCH" if d == 0 else ""))
