#!/usr/bin/env python3
"""Target audit (issue #458): does each masked address in a matched function point at the right thing?

The fingerprint check masks every address operand, so a function can match while a call reaches the wrong function
or a load reads the wrong global. This compares, for every relocation inside a byte-exact function, the address
the symbol's NAME says it should be with the address the retail function actually uses at that spot.

Maintainer tool: it needs the analysis image (work/SporeApp.analysis.bin, tools/contrib/make_image.py).

Name evidence only, never the retail instruction stream (that would make the audit agree with itself):
  import    __imp_X / a direct call to an import thunk
  crt       C runtime helpers from symbols/lib_names.txt
  hex-name  an address written into the name: FUN_00abcdef, g_156dc20, ..._0167a6d0
  annotation a '// 0x...' comment on the declaration (or a '// @ 0x' marker) in the row's own source
  symbols   the exact mangled name in symbols/*.txt or a src/game manifest, or in this slice's own symbols file or
            manifest (unique); another slice's record of a stand-in name (Elem, Obj) is not evidence
  qualified the demangled qualified name in symbols/ (unique, and our object has no overload of it)
RenderWare 4 rows built with /GL + link /LTCG against stub callees (gate.ltcg_stubs) are skipped: their linked
layout is not the plain object's.

Per relocation:
  agree       retail uses the expected address
  folded      retail uses a different function that is byte-identical to the expected one (the linker folded
              identical copies); not an error
  thunk       retail calls a one-instruction `jmp` to the expected function; not an error
  disagree    retail uses a different address
  reordered   the function uses exactly the expected addresses, at swapped places (independent stores in another
              order): same behaviour, byte-exact only because addresses are masked
  weak        a qualified-name, import or CRT match disagrees (another instantiation of the same template, or
              another copy of a CRT routine)
  unresolved  no name evidence (string literals and other data local to the object are listed apart as local)

usage: target_audit.py MANIFEST... [--va 00abcdef ...] [--jobs 4] [--show agree]
"""
import argparse, os, re, struct, sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "ci"), os.path.join(ROOT, "tools", "matching"),
                os.path.join(ROOT, "tools", "difftest")]
import run_all as RA                                  # noqa: E402
import fingerprint as F                               # noqa: E402
import gate                                           # noqa: E402
import resolve as RS                                  # noqa: E402
from coff import Coff, REL_DIR32, REL_REL32          # noqa: E402
from resaudit import same_code                        # noqa: E402
import targets as TG                                  # noqa: E402

VA_RE = re.compile(r"^[0-9a-fA-F]{8}$")


class Expect:
    def __init__(self, img):
        self.img = img
        self.res = RS.Resolver(img, RS.SymbolDB(img))

    def __call__(self, name, own=None, annots=(), quals=None, sid=None):
        """(expected address, method) or (None, None). `own`: the audited function's address; a name carrying it
        (U_01351e60_5_30, a placeholder for an unknown callee of 0x01351e60) is no evidence of its own target."""
        r = self.res
        want_func = not RS.mangled_is_data(name)
        va = r.by_import(name)
        if va:
            return va, "import"
        va = r.by_crt(name)
        if va:
            return va, "crt"
        va = TG.hex_claim(name, own)          # an address that ends the name (not H_572810_4-style placeholders)
        if va and r.plausible(va, want_func):
            return va, "hex-name"
        if annots:
            va, how = r.by_annotation(name, annots, want_func)
            if va and va != own:     # the row's own '// @ 0x' marker names the function being defined
                return va, "annotation"
        # recorded names: global records and this slice's own (stand-ins like Elem are per slice), as CI does
        vas = {v for v in set(TG.index().get(name, ())) | set(TG.index(sid).get(name, ()) if sid else ())
               if r.plausible(v, want_func)}
        if len(vas) == 1:
            return next(iter(vas)), "symbols"
        if len(vas) > 1:
            return None, "ambiguous"
        q = RS.demangle_qual(name)
        if q and "::" in q and quals is not None and quals.get(q, 0) == 1:
            vas = {v for v in r.db.qual.get(q, ()) if r.plausible(v, want_func)}
            if len(vas) == 1:
                return next(iter(vas)), "qualified"
            if len(vas) > 1:
                return None, "ambiguous"
        return None, None


def audit_row(exp, fp, coff, fname, va, annots=(), sid=None):
    """[(offset, symbol, verdict, expected, actual, method)] for one function."""
    fsym = coff.by_name.get(fname)
    if fsym is None or not fsym.defined:
        return None
    sec = coff.sections[fsym.secno - 1]
    quals = Counter(q for q in (RS.demangle_qual(s.name) for s in coff.syms.values() if s.name.startswith("?")) if q)
    lo, hi = fsym.value, fsym.value + fp["size"]
    out = []
    for off, si, typ in sec.relocs:
        if not lo <= off < hi or typ not in (REL_DIR32, REL_REL32):
            continue
        s = coff.syms[si]
        ours = struct.unpack_from("<I", sec.data, off)[0]
        field = struct.unpack("<I", exp.img.read(va + off - lo, 4))[0]
        if typ == REL_DIR32:
            actual = (field - ours) & 0xFFFFFFFF
        else:   # REL32: target = S + A - (P + 4), A = our field
            disp = field - (1 << 32) if field & 0x80000000 else field
            actual = (va + off - lo + 4 + disp - ours) & 0xFFFFFFFF
        want, how = exp(s.name, va, annots, quals, sid)
        if want is None:
            local = s.defined and not coff.sections[s.secno - 1].is_code
            verdict = "local" if local or s.name.startswith(("$SG", "??_C@", "__real@", "__xmm@", "$")) else \
                "ambiguous" if how == "ambiguous" else "unresolved"
        elif want == actual:
            verdict = "agree"
        elif same_code(exp.img, want, actual):
            verdict = "folded"
        elif jmp_to(exp.img, actual) == want:
            verdict = "thunk"
        elif how in ("qualified", "import", "crt"):
            verdict = "weak"         # a qualified name is shared by every instantiation of a template; the CRT has
                                     # several copies of memmove/memset (import thunk and static) and of _ftol2
        else:
            verdict = "disagree"
        out.append((off - lo, s.name, verdict, want, actual, how))
    # The same addresses used in a different order (two independent stores swapped): the behaviour is the same, but
    # the bytes match only because the addresses are masked. Not a wrong target.
    bad = [x for x in out if x[2] == "disagree"]
    if bad and sorted(x[3] for x in bad) == sorted(x[4] for x in bad):
        out = [x[:2] + ("reordered",) + x[3:] if x[2] == "disagree" else x for x in out]
    return out


def jmp_to(img, va):
    """the destination of a function at va that starts with `jmp rel32`, else None"""
    try:
        b = img.read(va, 5)
    except Exception:
        return None
    if not b or len(b) < 5 or b[0] != 0xE9:
        return None
    return (va + 5 + struct.unpack("<i", bytes(b[1:5]))[0]) & 0xFFFFFFFF


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("manifests", nargs="+")
    ap.add_argument("--va", nargs="*", help="only these addresses")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--show", nargs="*", default=["disagree", "reordered", "unresolved", "ambiguous"],
                    help="verdicts to print per relocation")
    a = ap.parse_args()
    fps = {int(r["va"], 16): r for r in F_load()}
    only = {int(v, 16) for v in a.va} if a.va else None
    rows = [r for r in RA.read_rows(a.manifests, "") if (only is None or r[2] in only) and r[2] in fps]
    keys = sorted({(r[0], r[3]) for r in rows if not gate.row_problem(r[0], r[3])})
    objs = {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for key, obj, _log in ex.map(RA.compile_one, keys):
            objs[key] = obj
    exp = Expect(RS.Image())
    tot, per_fn = Counter(), Counter()
    cache, annots = {}, {}
    rowfile = {}
    for m in a.manifests:
        for r in RA.read_rows([m], ""):
            rowfile[(r[0], r[2])] = m
    for src, sym, va, flags in rows:
        if gate.ltcg_stubs(rowfile.get((src, va), ""), va):
            per_fn["skipped (LTCG build)"] += 1      # built by linking against stubs; the plain object differs
            continue
        obj = objs.get((src, flags))
        if not obj:
            per_fn["not built"] += 1
            continue
        if obj not in cache:
            cache[obj] = (Coff(obj), F.parse_coff(obj)[1])
        coff, syms = cache[obj]
        name = RA.resolve(syms, sym)
        if src not in annots:
            path = os.path.join(ROOT, "match", src)
            annots[src] = RS.source_annotations([path] + gate_headers(path))
        res = audit_row(exp, fps[va], coff, name, va, annots[src], TG.slice_of(src)) if name else None
        if res is None:
            per_fn["symbol not found"] += 1
            continue
        c = Counter(v for _o, _n, v, _w, _a, _h in res)
        tot.update(c)
        per_fn["disagree" if c["disagree"] else "reordered" if c["reordered"] else
               "unresolved" if c["unresolved"] or c["ambiguous"] else "clean"] += 1
        for o, n, v, w, act, how in res:
            if v in a.show:
                print("%08x +%-4d %-10s %s  want %s (%s) got %08x" % (va, o, v, n[:90],
                      "%08x" % w if w else "-", how or "-", act))
    print("\nfunctions: %s" % ", ".join("%s %d" % kv for kv in per_fn.most_common()))
    print("relocations: %s" % ", ".join("%s %d" % kv for kv in tot.most_common()))
    return 1 if tot["disagree"] else 0


def gate_headers(path):
    """the headers next to the source (a slice's or module's own .h files) that carry its declarations"""
    import glob
    d = os.path.dirname(path)
    stem = os.path.splitext(os.path.basename(path))[0]
    return sorted(glob.glob(os.path.join(d, "*.h")) + glob.glob(os.path.join(d, stem, "*.h")))


def F_load():
    import json
    with open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl"), "rt") as f:
        return [json.loads(l) for l in f]


if __name__ == "__main__":
    sys.exit(main())
