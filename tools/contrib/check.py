#!/usr/bin/env python3
"""check: does one function compile to the retail bytes?  The same verdict as the pull-request check.

  .venv/bin/python tools/contrib/check.py 0x00529690 [--flags "/O2 /MD ..."]

Compiles the function's source file with its flags (tools/contrib/task.py shows them) and compares the function with
its retail fingerprint (tools/ci/fingerprint.py): MATCH, or why not.  No game files needed for the verdict.  With
work/SporeApp.analysis.bin (made from your own copy of the game by tools/contrib/make_image.py) it also prints an
instruction diff of your build against the original.

On MATCH it records the result: it adds the function's manifest.txt line and removes its nonmatching.txt /
partial.txt line, so the files are ready for your pull request.  --dry-run only prints what it would change.
"""
import argparse, os, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(ROOT, "tools", "difftest"),
                os.path.join(ROOT, "tools", "matching"), os.path.join(ROOT, "tools", "ci")]
import task as T            # noqa: E402
import slice as S           # noqa: E402
import fingerprint as F     # noqa: E402
import asm_audit            # noqa: E402
import ltcg                 # noqa: E402
from coff import Coff       # noqa: E402

IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")


def G_manifests():
    import gate
    return gate.all_manifests()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va")
    ap.add_argument("--flags", help="override the flags (space-separated)")
    ap.add_argument("--dry-run", action="store_true", help="on MATCH, print the bookkeeping changes instead of making them")
    a = ap.parse_args()
    va = int(a.va, 16)
    fp = T.fingerprint(va)
    if not fp:
        print("0x%08x has no fingerprint: not a known function start" % va)
        return 2
    src, ident = T.locate(va)
    if not src:
        print("no source file has a `// @ 0x%08x` marker yet" % va)
        return 2
    flags, how = S.choose_flags(ident, va, a.flags or None)
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
    stubs = ltcg.stubs_file(ident, va)
    raw, how_built = None, ""
    if stubs:
        # built as RenderWare 4's core was: /GL objects linked with /LTCG against the function's stub callees
        data, rel, log = ltcg.build(src, flags, stubs, sym, fp["size"])
        if data is None:
            print(log)
            return 1
        how_built = " + /GL, link /LTCG with %s" % os.path.relpath(stubs, ROOT)
        raw =os.path.join(ROOT, "work", "ltcg_%08x.bin" % va)
        open(raw, "wb").write(data)
    else:
        data, rel = F.extract(secs, syms, sym)
    verdict = F.check(fp, data, rel)
    asm = asm_audit.transcribed(src).get("%08x" % va)
    if asm and verdict == "PASS":
        verdict = "assembly transcription, not decompiled (%s): write it as C++" % asm
    print("%s  0x%08x  %s  [%s]%s" % ("MATCH" if verdict == "PASS" else "NO MATCH", va, sym, " ".join(flags), how_built))
    if verdict != "PASS":
        print("  " + verdict)
        if os.path.exists(IMAGE):
            print("\ninstruction diff (original | yours):")
            sys.stdout.flush()
            what = ["--raw", raw] if raw else [obj, sym]
            subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "cmpdis.py"), *what, "%08x" % va])
        else:
            print("  (for an instruction diff, make work/SporeApp.analysis.bin from your own game: tools/contrib/make_image.py)")
        return 1
    if any(r[2] == va for r in S.manifest_rows(ident)):
        print("(already a manifest row: nothing to add)")
        return 0
    rel_src = os.path.relpath(src, os.path.join(ROOT, "match")).replace(os.sep, "/")
    d = S.slice_dir(ident)
    line = "%s  %s  %08x  %s" % (rel_src, sym, va, " ".join(flags))
    manifest = os.path.join(d, "manifest.txt")
    if not os.path.exists(manifest):
        import glob
        hits = glob.glob(os.path.join(ROOT, "src", "**", ident + ".manifest.txt"), recursive=True)
        manifest = hits[0] if len(hits) == 1 else manifest
    if a.dry_run:
        print("\nwould add to %s:\n  %s" % (os.path.relpath(manifest, ROOT), line))
        for path in note_files(va):
            print("and remove the %08x line from %s" % (va, os.path.relpath(path, ROOT)))
        return 0
    text = open(manifest).read() if os.path.exists(manifest) else ""
    with open(manifest, "a") as f:
        f.write(("" if not text or text.endswith("\n") else "\n") + line + "\n")
    print("\nrecorded: added to %s:\n  %s" % (os.path.relpath(manifest, ROOT), line))
    # every note for this function, not only the one beside the source: a migrated function's original slice keeps
    # its own nonmatching.txt line otherwise (217 stale notes on 2026-11-10)
    for path in note_files(va):
        lines = open(path, encoding="utf-8", errors="replace").readlines()
        keep = [l for l in lines if not _is_row(l, va)]
        if len(keep) != len(lines):
            open(path, "w", encoding="utf-8").writelines(keep)
            print("removed its line from %s" % os.path.relpath(path, ROOT))
    return 0


def note_files(va):
    """Every nonmatching.txt / partial.txt (slices and src/game) with a line for va."""
    import glob
    out, key = [], "%08x" % va
    for path in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "*.txt")) +
                       glob.glob(os.path.join(ROOT, "src", "game", "**", "*.txt"), recursive=True)):
        if os.path.basename(path) not in ("nonmatching.txt", "partial.txt"):
            continue
        text = open(path, encoding="utf-8", errors="replace").read()
        if key in text.lower() and any(_is_row(l, va) for l in text.splitlines()):
            out.append(path)
    return out


def _is_row(line, va):
    p = line.split(None, 1)
    if not p or line.lstrip().startswith("#"):
        return False
    try:
        return int(p[0], 16) == va
    except ValueError:
        return False

if __name__ == "__main__":
    sys.exit(main())
