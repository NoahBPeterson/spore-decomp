#!/usr/bin/env python3
"""samecode: does a landed function compile to the same code in its module TU as in its slice?

The migration gate for equivalent (nonmatching) rows: a function that rewrite.py landed verbatim keeps its
equivalence verdict only if the module TU gives the same machine code as the slice did.  Both sides are
compiled the way the strict sweep runs them (tools/difftest/sweep_nonmatching.py): the module row with the
module's own flags (slice.choose_flags on the module id, plus /Isrc/game/include), the slice row with the
slice's.  The function's bytes are compared with relocation fields masked, and the relocation targets by
name, with rewrite.py's renamed-stub suffix (`Foo_s004a_b690` -> `Foo`) and string-literal labels (`$SG123`)
normalised.  Same code = the old verdict carries over; anything else needs an equiv.py run.

usage: samecode.py src/game/<dir>/<Obj>.cpp [va ...] [--base REF]   (default: every row of the module's nonmatching.txt)
       --base REF: a function already in the TU at git REF is compared with the TU at REF instead of its slice (it was
       gated when it landed; since then src/game may have fixed it, so the slice is no longer its baseline).  This skips
       an equiv.py run per old row on every landing (2026-11-14: 23 runs, ~17 min, to land 2 functions in SPPlayer)
       prints one line per VA: SAME / DIFF <what> / ERROR <why>; exit 1 if any row is not SAME
"""
import glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
import slice as S                                   # noqa: E402
from coff import Coff                               # noqa: E402

STUB_SUFFIX = re.compile(r"_s[0-9a-f]{4}_[0-9a-f]{4}")
SG = re.compile(r"\$SG\d+")


def norm(name):
    return SG.sub("$SG", STUB_SUFFIX.sub("", name or ""))


def slice_of(va):
    """(slice, source file) whose source carries the `// @ 0x<va>` marker: one whose manifest/nonmatching/partial rows list va,
    else the first by id (0x0109f040: s0108d0b0 carries a copy of the marker without the definition, s0109e8e0 owns it).
    The file, not <slice>.cpp: a slice whose main source has migrated can keep a flag variant (s007f9550_od.cpp)."""
    pat = re.compile(r"(?mi)^// @ 0x0*%x\b" % va)
    found = []
    for f in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "s*", "*.c*"))):
        if os.path.isfile(f) and pat.search(open(f, errors="replace").read()):
            found.append((os.path.basename(os.path.dirname(f)), f))
    for sid, f in found:
        d = S.slice_dir(sid)
        if any(va in {r[0] for r in S.read_rows(os.path.join(d, n))} for n in ("nonmatching.txt", "partial.txt")) or \
                any(r[2] == va for r in S.manifest_rows(sid)):
            return sid, f
    return found[0] if found else (None, None)


_objs = {}


def code(ident, va, src):
    """(masked bytes, [(offset, normalised target)]) of the function at va in ident's compiled source."""
    flags, _how = S.choose_flags(ident, va)
    if src.replace(os.sep, "/").split("/src/game/")[-1] != src and \
            not any(f.rstrip("/").endswith("src/game/include") for f in flags if f.startswith("/I")):
        flags = list(flags) + ["/Isrc/game/include"]
    key = (src, tuple(flags))
    if key not in _objs:
        obj, log = S.compile_obj(src, flags)
        _objs[key] = (Coff(obj) if obj else None, log)
    coff, log = _objs[key]
    if coff is None:
        raise RuntimeError("compile failed: " + ((log or "").strip().splitlines() or ["?"])[-1][:160])
    sym, how = S.find_symbol(coff, ident, va, src)
    if isinstance(sym, list):
        sym = sym[0] if len(sym) == 1 else None
    if sym is None:
        raise RuntimeError("symbol not found: %s" % how)
    sec, lo, hi = coff.func_extent(coff.by_name[sym])
    data = bytearray(sec.data[lo:hi])
    rel = []
    for off, si, _typ in sec.relocs:
        if lo <= off < hi:
            data[off - lo:off - lo + 4] = b"\0\0\0\0"
            rel.append((off - lo, norm(coff.syms[si].name)))
    return bytes(data), sorted(rel)


def module_id(tu):
    stem = os.path.splitext(os.path.basename(tu))[0]
    d = os.path.basename(os.path.dirname(tu))
    return stem if S.module_dir(stem) else "%s/%s" % (d, stem)


def main():
    argv = sys.argv[1:]
    base = None
    if "--base" in argv:
        i = argv.index("--base")
        base = argv[i + 1]
        del argv[i:i + 2]
    tu = os.path.abspath(argv[0])
    rows = os.path.join(os.path.splitext(tu)[0], "nonmatching.txt")
    vas = [int(v, 16) for v in argv[1:]] or [va for va, _d, _r in S.read_rows(rows)]
    mid = module_id(tu)
    bad = 0
    old_tu, old_vas = None, set()
    if base:
        import subprocess
        rel = os.path.relpath(tu, ROOT)
        r = subprocess.run(["git", "show", "%s:%s" % (base, rel)], cwd=ROOT, capture_output=True, text=True)
        if r.returncode == 0:
            old_vas = {int(v, 16) for v in re.findall(r"(?mi)^// @ 0x([0-9a-f]+)", r.stdout)}
            # beside the TU, so its relative includes resolve the same way; the symbol lookup is by the marker
            old_tu = os.path.join(os.path.dirname(tu), "_base_%d_%s" % (os.getpid(), os.path.basename(tu)))
            open(old_tu, "w").write(r.stdout)
    try:
        bad = run_rows(vas, mid, tu, old_tu, old_vas)
    finally:
        if old_tu and os.path.exists(old_tu):
            os.remove(old_tu)
    sys.exit(1 if bad else 0)


def run_rows(vas, mid, tu, old_tu, old_vas):
    bad = 0
    for va in vas:
        if va in old_vas:
            try:
                a, b = code(mid, va, tu), code(mid, va, old_tu)
            except RuntimeError as e:
                a, b = None, e
            if a == b:
                print("%08x SAME (base)" % va)
                continue
        sid, ssrc = slice_of(va)
        try:
            if not sid:
                raise RuntimeError("no slice carries the marker")
            a = code(mid, va, tu)
            b = code(sid, va, ssrc)
        except RuntimeError as e:
            print("%08x ERROR %s" % (va, e))
            bad += 1
            continue
        if a == b:
            print("%08x SAME (%s)" % (va, sid))
            continue
        bad += 1
        if a[0] != b[0]:
            what = "bytes (%d vs %d)" % (len(a[0]), len(b[0]))
        else:
            what = "relocation targets: " + ", ".join("%s/%s" % (x[1], y[1]) for x, y in zip(a[1], b[1]) if x != y)[:200]
        print("%08x DIFF %s (%s)" % (va, what, sid))
    return bad


if __name__ == "__main__":
    main()
