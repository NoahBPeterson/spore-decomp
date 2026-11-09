#!/usr/bin/env python3
"""The contribution gate: compile manifests and check every row against the retail fingerprints
(tools/ci/fingerprint.py).  No retail binary needed.

For each manifest, every distinct (source, flags) is compiled once with tools/matching/cl.sh (VC9 SP1, or VC 2003
1.01 for /vc71), then every row must:
  - have a fingerprint,
  - not be an assembly transcription (tools/matching/asm_audit.py),
  - match its fingerprint (size, relocations on masked offsets, hash of the masked bytes).

usage: gate.py MANIFEST... [--fingerprints tools/ci/fingerprints.jsonl] [--jobs 4] [--json out.json]
exit 0 iff every row passes
"""
import argparse, json, os, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import run_all as R             # noqa: E402
import asm_audit                # noqa: E402
import fingerprint as F         # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("manifests", nargs="+")
    ap.add_argument("--fingerprints", default=os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"))
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--json")
    a = ap.parse_args()
    fps = {}
    for line in open(a.fingerprints):
        d = json.loads(line)
        fps[int(d["va"], 16)] = d
    R.OBJ_DIR = os.path.join(ROOT, "work", "ci", "obj")
    os.makedirs(R.OBJ_DIR, exist_ok=True)

    rows = R.read_rows([os.path.abspath(m) for m in a.manifests], "")
    keys = sorted({(r[0], r[3]) for r in rows})
    objs = {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for key, obj, log in ex.map(R.compile_one, keys):
            objs[key] = obj
            if obj is None:
                print("COMPILE FAILED %s\n%s" % (key[0], log.strip()[-1500:]))
    coffs, out, ok = {}, [], 0
    for src, sym, va, flags in rows:
        obj = objs.get((src, flags))
        if obj is None:
            st = "compile failed"
        elif va not in fps:
            st = "no fingerprint for this address"
        else:
            if obj not in coffs:
                coffs[obj] = F.parse_coff(obj)
            secs, syms = coffs[obj]
            name = R.resolve(syms, sym)
            if name is None:
                st = "symbol %s not found in the object" % sym
            else:
                st = F.check(fps[va], *F.extract(secs, syms, name))
            asm = asm_audit.transcribed(os.path.join(ROOT, "match", src)).get("%08x" % va)
            if asm and st == "PASS":
                st = "assembly transcription, not decompiled (%s)" % asm
        ok += st == "PASS"
        out.append({"va": "%08x" % va, "src": src, "result": st})
        print("%-5s %08x  %s%s" % ("PASS" if st == "PASS" else "FAIL", va, src, "" if st == "PASS" else "  " + st))
    print("\n%d / %d functions match the retail fingerprints" % (ok, len(rows)))
    if a.json:
        json.dump(out, open(a.json, "w"), indent=1)
    return 0 if ok == len(rows) else 1


if __name__ == "__main__":
    sys.exit(main())
