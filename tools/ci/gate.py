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
import argparse, glob, gzip, json, os, re, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import run_all as R             # noqa: E402
import asm_audit                # noqa: E402
import fingerprint as F         # noqa: E402
import ltcg                     # noqa: E402


# compiler options a manifest row may use (every option the manifests used on 2026-11-09).  Anything else is refused
# before compiling: cl's /B1 /B2 load a compiler pass from a DLL path, @file reads more options, /Fo /Fe /Fp write files
FLAG_OK = re.compile(r"^(/MD|/MT|/Gy|/TP|/TC|/O1|/O2|/Od|/Oi|/Oy-?|/Ob[0-2]|/EHsc|/EHs-|/GS-|/GR-|/arch[:=](SSE2?|IA32)"
                     r"|/fp[:=](fast|precise|strict)|/vc71|/vmg|/vmv|/nologo|/c|/wd\d{4}"
                     r"|[/-]D[A-Za-z_]\w*(=[\w.]*)?)$")


def inside(path, *dirs):
    rp = os.path.realpath(path)
    return any(rp == os.path.realpath(d) or rp.startswith(os.path.realpath(d) + os.sep) for d in dirs)


def row_problem(src, flags):
    """why a manifest row may not be compiled, or None"""
    if not inside(os.path.join(ROOT, "match", src), os.path.join(ROOT, "match"), os.path.join(ROOT, "src", "game")):
        return "source %s is outside match/ and src/game/" % src
    fl = list(flags)
    for i, f in enumerate(fl):
        if f == "-I" or f == "match/include" and i and fl[i - 1] == "-I":
            continue
        if f.startswith("/I"):
            p = f[2:]
            if not p or p.startswith(("/", "\\")) or ":" in p or ".." in p.replace("\\", "/").split("/") or \
                    not inside(os.path.join(ROOT, p), ROOT):
                return "include path %s is not a relative path inside the repo" % f
            continue
        if not FLAG_OK.match(f):
            return "compiler option %s is not allowed" % f
    return None


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

    eqfiles = [os.path.abspath(m) for m in a.manifests if os.path.basename(m) == "equivalent.txt"]
    rows, rowfile = [], {}
    for m in (os.path.abspath(m) for m in a.manifests if os.path.basename(m) != "equivalent.txt"):
        for r in R.read_rows([m], ""):
            rows.append(r)
            rowfile[(r[0], r[2])] = m
    refused = {(r[0], r[3]): row_problem(r[0], r[3]) for r in rows}
    keys = sorted(k for k, why in refused.items() if not why)
    objs = {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for key, obj, log in ex.map(R.compile_one, keys):
            objs[key] = obj
            if obj is None:
                print("COMPILE FAILED %s\n%s" % (key[0], log.strip()[-1500:]))
    coffs, out, ok = {}, [], 0
    for src, sym, va, flags in rows:
        obj = objs.get((src, flags))
        if refused[(src, flags)]:
            st = "refused: " + refused[(src, flags)]
        elif obj is None:
            st = "compile failed"
        elif va not in fps:
            st = "no fingerprint for this address"
        else:
            if obj not in coffs:
                coffs[obj] = F.parse_coff(obj)
            secs, syms = coffs[obj]
            name = R.resolve(syms, sym)
            stubs = ltcg_stubs(rowfile[(src, va)], va)
            if name is None:
                st = "symbol %s not found in the object" % sym
            elif stubs:
                # built as RenderWare 4's core was: /GL + link /LTCG against the function's stub callees
                data, rel, log = ltcg.build(os.path.join(ROOT, "match", src), list(flags),
                                            stubs, name, fps[va]["size"])
                st = F.check(fps[va], data, rel) if data is not None else "LTCG build failed: " + log[-300:]
            else:
                st = F.check(fps[va], *F.extract(secs, syms, name))
            asm = asm_audit.transcribed(os.path.join(ROOT, "match", src)).get("%08x" % va)
            if asm and st == "PASS":
                st = "assembly transcription, not decompiled (%s)" % asm
        ok += st == "PASS"
        tag = "PASS" if st == "PASS" else "KNOWN" if va in known else "FAIL"
        out.append({"va": "%08x" % va, "src": src, "result": st, "tag": tag})
        print("%-5s %08x  %s%s" % (tag, va, src, "" if st == "PASS" else "  " + st))
    neq = 0
    for path in eqfiles:
        for src, sym, va, flags in R.read_rows([path], ""):
            st = equivalent_row(path, src, va, flags, fps)
            neq += st == "EQUIV"
            tag = "EQUIV" if st == "EQUIV" else "FAIL"
            out.append({"va": "%08x" % va, "src": src, "result": st, "tag": tag, "kind": "equivalent"})
            print("%-5s %08x  %s%s" % (tag, va, src, "" if st == "EQUIV" else "  " + st))
    fails = [r for r in out if r["tag"] == "FAIL"]
    nknown = sum(r["tag"] == "KNOWN" for r in out)
    print("\n%d / %d functions match the retail fingerprints (%d known failures, %d new failures)" % (
        ok, len(rows), nknown, len(fails)))
    if eqfiles:
        print("%d proven-equivalent rows still build to their proved bytes" % neq)
    lost = []
    if a.keep:
        now = {r[2] for r in R.read_rows(all_manifests(), "")}
        lost = sorted(v for v in (int(l.split()[0], 16) for l in open(a.keep) if l.strip()) if v not in now)
        for v in lost:
            print("DROPPED %08x: byte-exact on the base branch, no manifest lists it now" % v)
    if a.json:
        json.dump(out, open(a.json, "w", encoding="utf-8"), indent=1)
    if a.summary:
        with open(a.summary, "w", encoding="utf-8") as f:
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


def ltcg_stubs(manifest, va):
    """The stub file of an /LTCG-built function (tools/matching/ltcg.py): ltcg/<va>.cpp next to its manifest."""
    p = os.path.join(os.path.dirname(manifest), "ltcg", "%08x.cpp" % va)
    return p if os.path.isfile(p) else None


def equivalent_row(path, src, va, flags, fps):
    """'EQUIV' when a proven-equivalent row (equivalent.txt, tools/contrib/prove.py) still builds to the bytes its
    proof is about, else why not. The proof itself needs the game and is re-checked by a maintainer before merging
    (prove.py --recheck); this keeps a later change from silently invalidating it."""
    sys.path[:0] = [os.path.join(ROOT, "tools", "equiv"), os.path.join(ROOT, "tools", "contrib")]
    import func as FN
    if va not in fps:
        return "no fingerprint for this address"
    bp = FN.bundle_path(path, va)
    if not os.path.isfile(bp):
        return "no proof bundle %s" % os.path.relpath(bp, ROOT)
    b = json.load(open(bp))
    if b.get("va") != "%08x" % va or b.get("retail_fp") != fps[va]["sha256"]:
        return "the proof bundle is for another function"
    why = row_problem(src, flags)
    if why:
        return "refused: " + why
    try:
        ours = FN.our_func(va, " ".join(flags))
    except SystemExit as e:
        return "build failed: %s" % str(e)[-300:]
    if FN.build_hash(ours) != b.get("build"):
        return "our build changed since the proof (rerun tools/contrib/prove.py %#x --record)" % va
    return "EQUIV"


def all_manifests():
    return R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True))


def all_equivalent():
    return sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "equivalent.txt")) +
                  glob.glob(os.path.join(ROOT, "src", "game", "**", "equivalent.txt"), recursive=True))


if __name__ == "__main__":
    sys.exit(main())
