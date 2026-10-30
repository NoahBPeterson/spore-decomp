#!/usr/bin/env python3
"""Rewrite Ghidra's indirect-call casts in the whole-program decompilation into named forms.

usage: .venv/bin/python tools/decomp_vcalls.py [--src work/decomp_all] [--out work/decomp_all2]

Ghidra prints a virtual call as `(**(code **)(*p + 0x8))(...)`. Turning that by hand into a typed call is where
fix-wave agents added or dropped a `*` (FAIL triage 2026-10-30: about 70 read-fault FAILs carried an extra
dereference copied from this spelling). The rewrite names what the cast means instead:

  (**(code **)(*O + off))   ->  VCALL(O, off /* slot n */)   the function in O's vtable at byte offset off
  (**(code **)(*O))         ->  VCALL(O, 0 /* slot 0 */)
  (**(code **)(E))          ->  FNPTR(E)                     a function pointer stored at address E (not a vtable)

O is the object whose first dword is the vtable pointer. In source this is the project's VFN macro:
VCALL(p, 0x8)(args) is `VFN(p, 0x8, T)(p, args)` for a __thiscall T -- Ghidra often leaves `this` (p, passed in
ecx) out of the argument list when it does not know the callee's convention, so check the original's ecx.
Function pointer casts typed by Ghidra (`_func_int_int **`) are rewritten the same way. The output keeps the
dump's layout (one /* ==== NAME @ va ==== */ block per function); tools/matching/card.py reads work/decomp_all2
first when it exists.
"""
import argparse, glob, os, re, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEAD = re.compile(r"\(\*\*\((?:code|_func_\w+) \*\*\)")
HEADER = ("/* tools/decomp_vcalls.py: VCALL(O, off) = the function at byte offset off of O's vtable (slot off/4),\n"
          "   called as VFN(O, off, T)(O, ...) when T is __thiscall (Ghidra may omit O, the ecx argument).\n"
          "   FNPTR(E) = the function pointer stored at address E. */\n\n")


def close_paren(s, i):
    """Index of the ')' matching the '(' at s[i], or -1."""
    depth = 0
    for k in range(i, len(s)):
        c = s[k]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return k
    return -1


def top_level_plus(e):
    """Index of the last ' + ' outside parentheses/brackets in e, or -1."""
    depth, last = 0, -1
    for k, c in enumerate(e):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0 and e.startswith(" + ", k):
            last = k
    return last


def strip_parens(e):
    e = e.strip()
    while e.startswith("(") and close_paren(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


VFT = re.compile(r"^(?:\((?:u?int|undefined4)\))?(.+)(\.|->)vftable$")


def name_call(e):
    """The replacement for (**(code **)(e)), or None to leave it."""
    e = strip_parens(re.sub(r"\s+", " ", e))      # Ghidra wraps long expressions across lines
    k = top_level_plus(e)
    left, off = (strip_parens(e[:k]), e[k + 3:].strip()) if k >= 0 else (e, "0")
    left = re.sub(r"^\((?:u?int|undefined4)\)(?=\*)", "", left)   # (int)*O: the cast of the loaded vtable pointer
    if not re.fullmatch(r"0x[0-9a-fA-F]+|\d+", off):
        return "FNPTR(%s)" % e
    n = int(off, 0)
    slot = lambda obj: "VCALL(%s, %s /* slot %d */)" % (obj, off, n // 4) if n % 4 == 0 else None
    mv = VFT.match(left)
    if mv:                                  # Ghidra typed the class: X.vftable / P->vftable
        obj = mv.group(1)
        return slot(obj if mv.group(2) == "->" else "&(%s)" % obj)   # P->vftable: P; X.vftable: &X
    if left.startswith("*"):                # *O + off; **(T **)(Y) + off is the object *(T **)(Y)
        return slot(strip_parens(left[1:]))
    return "FNPTR(%s)" % e


def rewrite(text):
    out, pos, n_v, n_f = [], 0, 0, 0
    for m in HEAD.finditer(text):
        start = m.start()
        if start < pos:
            continue
        end = close_paren(text, start)       # the ')' closing (**(code **)E)
        if end < 0:
            continue
        e = text[m.end():end]
        rep = name_call(rewrite(e)[0])       # nested casts inside E first
        if rep is None:
            continue
        out.append(text[pos:start])
        out.append(rep)
        pos = end + 1
        if rep.startswith("VCALL"):
            n_v += 1
        else:
            n_f += 1
    out.append(text[pos:])
    return "".join(out), n_v, n_f


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default=os.path.join(ROOT, "work", "decomp_all"))
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "decomp_all2"))
    a = ap.parse_args()
    os.makedirs(os.path.join(a.out, "c"), exist_ok=True)
    for f in glob.glob(os.path.join(a.src, "index_*.csv")):
        shutil.copy(f, a.out)
    tv = tf = left = 0
    for f in sorted(glob.glob(os.path.join(a.src, "c", "*.c"))):
        text, nv, nf = rewrite(open(f, errors="replace").read())
        tv, tf = tv + nv, tf + nf
        left += len(HEAD.findall(text))
        with open(os.path.join(a.out, "c", os.path.basename(f)), "w") as g:
            g.write(HEADER + text)
    print("VCALL %d, FNPTR %d, left as Ghidra wrote them %d -> %s" % (tv, tf, left, os.path.relpath(a.out, ROOT)))


if __name__ == "__main__":
    main()
