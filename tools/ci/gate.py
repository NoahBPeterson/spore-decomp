#!/usr/bin/env python3
"""The contribution gate: compile manifests and check every row against the retail fingerprints
(tools/ci/fingerprint.py).  No retail binary needed.

For each manifest, every distinct (source, flags) is compiled once with tools/matching/cl.sh (VC9 SP1, or VC 2003
1.01 for /vc71), then every row must:
  - have a fingerprint,
  - not be an assembly transcription (tools/matching/asm_audit.py),
  - match its fingerprint (size, relocations on masked offsets, hash of the masked bytes).

A row listed in --known (VA per line, default tools/ci/known_failures.txt: rows run_all.py counted byte-exact before the
fingerprint check existed but that fail it) is reported without failing the check.  --keep FILE (VAs) requires each of
those functions to still be a manifest row somewhere: a pull request may not drop a match.

usage: gate.py MANIFEST... [--fingerprints tools/ci/fingerprints.jsonl.gz] [--known FILE] [--keep FILE] [--jobs 4]
               [--json out.json] [--summary out.md]
exit 0 iff every row passes (or is known) and nothing in --keep went missing
"""
import argparse, glob, gzip, json, os, sys
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
    ap.add_argument("--fingerprints", default=os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"))
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--known", default=os.path.join(ROOT, "tools", "ci", "known_failures.txt"))
    ap.add_argument("--keep")
    ap.add_argument("--json")
    ap.add_argument("--summary")
    a = ap.parse_args()
    known = {int(l.split()[0], 16) for l in open(a.known) if l.strip() and not l.startswith("#")} \
        if a.known and os.path.exists(a.known) else set()
    fps = {}
    for line in (gzip.open(a.fingerprints, "rt") if a.fingerprints.endswith(".gz") else open(a.fingerprints)):
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
        tag = "PASS" if st == "PASS" else "KNOWN" if va in known else "FAIL"
        out.append({"va": "%08x" % va, "src": src, "result": st, "tag": tag})
        print("%-5s %08x  %s%s" % (tag, va, src, "" if st == "PASS" else "  " + st))
    fails = [r for r in out if r["tag"] == "FAIL"]
    nknown = sum(r["tag"] == "KNOWN" for r in out)
    print("\n%d / %d functions match the retail fingerprints (%d known failures, %d new failures)" % (
        ok, len(rows), nknown, len(fails)))
    lost = []
    if a.keep:
        now = {r[2] for r in R.read_rows(all_manifests(), "")}
        lost = sorted(v for v in (int(l.split()[0], 16) for l in open(a.keep) if l.strip()) if v not in now)
        for v in lost:
            print("DROPPED %08x: byte-exact on the base branch, no manifest lists it now" % v)
    if a.json:
        json.dump(out, open(a.json, "w"), indent=1)
    if a.summary:
        with open(a.summary, "w") as f:
            f.write("### Byte-match check\n\n%s **%d / %d** functions match the retail fingerprints"
                    " (%d manifests; %d known failures)\n\n" % ("✅" if not fails and not lost else "❌", ok, len(rows),
                                                               len(a.manifests), nknown))
            if fails or lost:
                f.write("| function | source | why |\n|---|---|---|\n")
                for r in fails:
                    f.write("| `%s` | `%s` | %s |\n" % (r["va"], r["src"], r["result"]))
                for v in lost:
                    f.write("| `%08x` | | dropped: byte-exact on the base branch, no manifest lists it now |\n" % v)
    return 0 if not fails and not lost else 1


def all_manifests():
    return R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True))


if __name__ == "__main__":
    sys.exit(main())
