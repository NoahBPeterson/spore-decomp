#!/usr/bin/env python3
"""Tests for tools/equiv/ddec_layer.py (needs the game image, wine for our builds, docker with the STOKE image).

    .venv/bin/python tools/equiv/test_ddec_layer.py            # all cases, prints a table
    .venv/bin/python tools/equiv/test_ddec_layer.py raster     # only the cases whose name contains "raster"

Cases:
  raster-L2-learn     Raster::Initialize 0x011efeb0 (loop, two calls; ours differs by test ebx,0x40 -> test bl,0x40):
                      must be proved at L2.
  raster-L2-hints     the same with the hints of the first run: must be proved, without learning.
  raster-L2-badhints  the hints with one invariant changed: must not be proved.
  raster-neg-*        the prototype's wrong variants of our code (test mask 0x41, a dropped store, the wrong argument
                      pushed for FormatGetDepth, loop counter starting at 2, loop running until 2): must not be proved.
  pitch-L1 / pitch-L2 D3D9GetStreamedMipLevelPitch 0x011efe30 (no loop, one call) against a copy of retail whose last
                      two instructions are swapped as in the LTCG build of ltcg.md section 7 (shl edx,4; mov eax,edx
                      -> mov eax,edx; shl eax,4): eax is the same, edx differs at return. Expected: L1 proved,
                      L2 not proved.
  loop-*              two loop functions from work/scratch/equiv_rename/reg300_re.jsonl that the rename layer rejects,
                      at L1 and L2 (reported, no expectation).
Game bytes never leave work/: the table shows only statuses, times and the layer's messages.
"""
import os
import sys
import time
from dataclasses import replace

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import func  # noqa: E402
import ddec_layer  # noqa: E402

RASTER, PITCH = 0x011efeb0, 0x011efe30
LOOPS = [0x0070f570, 0x007aceb0]

NEGATIVES = [  # name, bytes in our code, replacement (from work/scratch/equiv_ddec/mutate.py)
    ("mask41", "f6c340", "f6c341"),
    ("dropstore", "885613", "909090"),
    ("wrongarg", "33d250", "33d253"),
    ("loopinit", "b101", "b102"),
    ("loopexit", "83f80175f7", "83f80275f7"),
]


def mutated(f, old, new):
    old, new = bytes.fromhex(old), bytes.fromhex(new)
    assert f.code.count(old) == 1, "pattern %s occurs %d times" % (old.hex(), f.code.count(old))
    return replace(f, code=f.code.replace(old, new))


def bad_hints(h):
    """Change the constant of the first equality invariant (or turn the first consequent into false)."""
    import copy
    h = copy.deepcopy(h)
    for s in h["segs"]:
        for c in s["cuts"]:
            for a, cs in c["inv"].items():
                for k, x in enumerate(cs):
                    if x.endswith(" = 0x0"):
                        cs[k] = x[:-1] + "1"
                        return h
    return None


def main(sel=None):
    rows = []

    def run(name, retail, ours, level, expect, hints=None, timeout=900):
        if sel and sel not in name:
            return None
        r = ddec_layer.prove(retail, ours, level, hints, timeout)
        ok = expect == "report" or (r["status"] == "proved") == (expect == "proved")
        rows.append((name, level, r["status"], r["seconds"], "ok" if ok else "UNEXPECTED (want %s)" % expect,
                     r["detail"]))
        print("%-20s %-3s %-8s %7.1fs %s  %s" % rows[-1], flush=True)
        if r["status"] == "proved" and hints is None:
            import json
            size = len(json.dumps(r["hints"]))
            budget = 2048 + len(retail.code)
            print("  hints: %d bytes (bundle budget %d)" % (size, budget), flush=True)
        return r

    retail, ours = func.retail_func(RASTER), func.our_func(RASTER)
    first = run("raster-L2-learn", retail, ours, "L2", "proved")
    if first and first["status"] == "proved":
        run("raster-L2-hints", retail, ours, "L2", "proved", first["hints"])
        bad = bad_hints(first["hints"])
        if bad:
            run("raster-L2-badhints", retail, ours, "L2", "not proved", bad)
    for nm, old, new in NEGATIVES:
        run("raster-neg-" + nm, retail, mutated(ours, old, new), "L2", "not proved")

    pr = func.retail_func(PITCH)
    var = replace(mutated(pr, "c1e2048bc2", "8bc2c1e004"), side="ours", name="pitch-swapped")
    run("pitch-L1", pr, var, "L1", "proved")
    run("pitch-L2", pr, var, "L2", "not proved")

    for va in LOOPS:
        try:
            r, o = func.retail_func(va), func.our_func(va)
        except SystemExit as e:
            print("loop-%08x: cannot build ours: %s" % (va, e))
            continue
        for lv in ("L1", "L2"):
            run("loop-%08x" % va, r, o, lv, "report")

    print("\n%-20s %-3s %-8s %8s  %s" % ("case", "lvl", "status", "seconds", "check"))
    for n, lv, st, sec, ok, _ in rows:
        print("%-20s %-3s %-8s %7.1fs  %s" % (n, lv, st, sec, ok))
    return 0 if all(r[4] == "ok" for r in rows) else 1


if __name__ == "__main__":
    t = time.time()
    rc = main(sys.argv[1] if len(sys.argv) > 1 else None)
    print("total %.0f s" % (time.time() - t))
    sys.exit(rc)
