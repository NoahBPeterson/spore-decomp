#!/usr/bin/env python3
"""check: does one function compile to the retail bytes?  The same verdict as the pull-request check.

  .venv/bin/python tools/contrib/check.py 0x00529690 [--flags "/O2 /MD ..."]

Compiles the function's source file with its flags (tools/contrib/task.py shows them) and compares the function with
its retail fingerprint (tools/ci/fingerprint.py): MATCH, or why not.  No game files needed for the verdict.  With
work/SporeApp.analysis.bin (made from your own copy of the game by tools/contrib/make_image.py) it also prints an
instruction diff of your build against the original.

On MATCH it prints the manifest line to add (and the nonmatching.txt line to remove) in your pull request.
"""
import argparse, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(ROOT, "tools", "difftest"),
                os.path.join(ROOT, "tools", "matching"), os.path.join(ROOT, "tools", "ci")]
import task as T            # noqa: E402
import slice as S           # noqa: E402
import fingerprint as F     # noqa: E402
import asm_audit            # noqa: E402
from coff import Coff       # noqa: E402

IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")


def G_manifests():
    import gate
    return gate.all_manifests()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va")
    ap.add_argument("--flags", help="override the flags (space-separated)")
    a = ap.parse_args()
    va = int(a.va, 16)
    fp = T.fingerprints().get(va)
    if not fp:
        print("0x%08x has no fingerprint: not a known function start" % va)
        return 2
    src, ident = T.locate(va)
    if not src:
        print("no source file has a `// @ 0x%08x` marker yet" % va)
        return 2
    flags, how = S.choose_flags(ident, va, a.flags.split() if a.flags else None)
    obj, log = S.compile_obj(src, flags)
    if not obj:
        print("COMPILE FAILED (%s, flags %s)\n%s" % (os.path.relpath(src, ROOT), " ".join(flags), (log or "").strip()[-3000:]))
        return 1
    sym, why = S.find_symbol(Coff(obj), ident, va, src, orig_size=fp["size"])
    secs, syms = F.parse_coff(obj)
    if sym is None:
        # no marker: the symbol a manifest row names (the pull-request check finds functions the same way)
        import run_all as R
        named = [r[1] for r in R.read_rows(G_manifests(), "") if r[2] == va]
        sym = next((R.resolve(syms, n) for n in named if R.resolve(syms, n)), None) or sym
    if isinstance(sym, list):
        print("the marker matches several functions: %s" % ", ".join(sym))
        return 1
    if sym is None:
        print("no compiled function found for the marker: %s" % why)
        return 1
    data, rel = F.extract(secs, syms, sym)
    verdict = F.check(fp, data, rel)
    asm = asm_audit.transcribed(src).get("%08x" % va)
    if asm and verdict == "PASS":
        verdict = "assembly transcription, not decompiled (%s): write it as C++" % asm
    print("%s  0x%08x  %s  [%s]" % ("MATCH" if verdict == "PASS" else "NO MATCH", va, sym, " ".join(flags)))
    if verdict != "PASS":
        print("  " + verdict)
        if os.path.exists(IMAGE):
            print("\ninstruction diff (original | yours):")
            sys.stdout.flush()
            subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "cmpdis.py"), obj, sym, "%08x" % va])
        else:
            print("  (for an instruction diff, make work/SporeApp.analysis.bin from your own game: tools/contrib/make_image.py)")
        return 1
    if any(r[2] == va for r in S.manifest_rows(ident)):
        print("(already a manifest row: nothing to add)")
        return 0
    rel_src = os.path.relpath(src, os.path.join(ROOT, "match")).replace(os.sep, "/")
    d = os.path.relpath(S.slice_dir(ident), ROOT)
    print("\nadd to %s/manifest.txt:\n  %s  %s  %08x  %s" % (d, rel_src, sym, va, " ".join(flags)))
    print("and remove the 0x%08x line from %s/nonmatching.txt (or partial.txt) if it is there" % (va, d))
    return 0


if __name__ == "__main__":
    sys.exit(main())
