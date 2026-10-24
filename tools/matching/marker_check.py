#!/usr/bin/env python3
"""marker_check.py <slice-source>... [--total] — find `// @ 0x<va>` markers that bind to the wrong function.

chk.py and equiv.py bind each marker to the first function definition after it (tools/difftest/slice.py
_def_name_after: up to 80 lines on, past types and declarations). When something else is defined in between, the
VA silently binds to that: in part1 (2026-10-24) two "equivalence FAILs" were a marker above GetAnimation's support
types, which bound 0059dc70 to an inline Property::GetItemCount, and a marker on an Init declaration that bound
005ec7c0 to the next function. A wrong binding can as easily make a buggy function look equivalent.

A marker after code on the same line (`void Init();  // @ 0x005ec7c0`) is always reported. For each column-0
marker of a slice source (match/slices/<id>/<id>.c*) this compares the bound definition's name with
the slice's own name for the VA (symbols/slices/<id>.txt) and reports "<file>:<line> <va> bound to X, expected Y"
when the base identifiers differ (constructors/destructors compare by class name). VAs without a symbols entry, and
markers whose name the binder cannot read, are not judged. --total prints "<files with a mismatch> <mismatches>".
The symbols files mix real names, stand-ins and descriptions, so this is a REPORT (about half of the hits on the
2026-10-24 tree were stand-in spellings): commit_slice.sh prints the count before/after, it does not refuse.
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
from slice import _def_name_after, slice_symbol_name, base_ident  # noqa: E402

MARK = re.compile(r"^// @ 0x([0-9a-fA-F]+)\s*$")
TRAIL = re.compile(r"^\s*[^/\s].*?//\s*@\s*0x([0-9a-fA-F]{5,8})\b")


def ident(name):
    """Base identifier of a mangled ('?f@C@@...') or qualified ('C::f', 'C::~C') name."""
    if name.startswith("?") or name.startswith("_"):
        return base_ident(name)
    last = name.split("::")[-1].lstrip("~")
    return last


def _norm(x):
    x = re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}$", "", x)        # per-slice rename suffix (cFoo_s0055_beb0)
    x = re.sub(r"_?(?:ctor|dtor|Ctor|Dtor)$", "", x)         # stand-in spellings of constructors/destructors
    return re.sub(r"[^0-9a-z]", "", x.lower())


def same(g, w):
    """Equal, or one name embeds the other (stand-in spellings: Hashtable_DoRehash for Hashtable::DoRehash)."""
    a, b = _norm(g), _norm(w)
    return a == b or (min(len(a), len(b)) >= 4 and (a.endswith(b) or b.endswith(a)))


def mismatches(path):
    sid = os.path.basename(os.path.dirname(path))
    try:
        lines = open(path, errors="replace").read().split("\n")
    except OSError:
        return []
    own = set()
    for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
        try:
            for r in open(os.path.join(os.path.dirname(path), f), errors="replace"):
                p = r.split("#", 1)[0].split()
                v = p[2] if f == "manifest.txt" and len(p) > 2 else (p[0] if p else "")
                if re.fullmatch(r"(0x)?[0-9a-fA-F]{5,8}", v):
                    own.add(int(v, 16))
        except OSError:
            pass
    out = []
    for i, l in enumerate(lines):
        t = TRAIL.match(l)
        if t and int(t.group(1), 16) in own:
            # the binders match a marker anywhere on a line, so one of the slice's OWN VAs after code (a declaration)
            # binds to the next definition; address notes on declarations of callees are fine
            out.append((i + 1, "%08x" % int(t.group(1), 16), "(marker after code on this line)", l.strip()[:60]))
            continue
        m = MARK.match(l)
        if not m:
            continue
        va = int(m.group(1), 16)
        want = slice_symbol_name(sid, va)
        got = _def_name_after(lines, i)
        if not want or not got:
            continue
        if not want.startswith(("?", "_")):
            # symbols/slices files also hold descriptions ("erase entries matching an id"); judge only a leading
            # qualified identifier followed by nothing, a signature or whitespace + '(' / '->'
            mm = re.match(r"([A-Za-z_][\w]*(?:::~?[A-Za-z_]\w*)*)(?=\s*(?:\(|->|$))", want)
            if not mm:
                continue
            want = mm.group(1)
        w, g = ident(want), ident(got)
        if want.startswith(("??0", "??1")) and "::" in got:
            g = got.split("::")[-2] if len(got.split("::")) > 1 else g     # ctor/dtor: compare class names
        placeholder = ("FUN_", "LAB_", "thunk_", "fn_", "sub_")
        if not w or w.startswith(placeholder) or g.startswith(placeholder) or g in ("__declspec", "__asm", "if", "for", "while", "switch", "return", "sizeof"):
            continue        # placeholder names, or a binder that could not read the definition, decide nothing
        if want.startswith(("??_G", "??_E", "?A0x", "?A?$", "??_7")) or "`" in want:
            continue        # compiler-generated (deleting dtors, vtables) or anonymous names: no source of their own
        if not same(g, w):
            out.append((i + 1, "%08x" % va, got, want))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    total = "--total" in sys.argv
    n = files = 0
    for p in args:
        b = mismatches(p)
        files += bool(b)
        n += len(b)
        if not total:
            for ln, va, got, want in b:
                print("%s:%d %s bound to %s, expected %s" % (p, ln, va, got, want[:80]))
    if total:
        print(files, n)
    return 1 if n else 0


if __name__ == "__main__":
    sys.exit(main())
