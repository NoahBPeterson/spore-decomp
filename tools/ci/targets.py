#!/usr/bin/env python3
"""Do a matched function's names point where retail points? (issue #458)

The fingerprint masks every address operand, so a function can match while a call reaches the wrong function or a load
reads the wrong global. Fingerprints also carry the retail bytes behind the mask ("masked": addresses only, no
instructions), so CI can compare each relocation's symbol with the address retail uses at that spot, without the game.

A name is checked against the address it claims itself, never against other uses of the name (stand-in names are
per slice, and the linker folds identical code, so "every use agrees" would misfire):
  hex-name  an address written into the identifier (FUN_00abcdef, g_15b7458, vtbl_13eb938): it must be the target
  symbols   the exact mangled name on one address in symbols/*.txt, symbols/slices/*.txt or a manifest row
A name carrying the checked function's own address (a placeholder like U_01351e60_5_30) is no evidence. Anything
else is not checked (imports, CRT helpers, data local to the object, names with no recorded address).

Per relocation: agree, disagree, or reordered (the function uses exactly the expected addresses at swapped places:
independent stores in another order, same behaviour). tools/ci/target_audit.py is the fuller maintainer version
(more name evidence, needs the game image).
"""
import glob, os, re, struct, sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "difftest"), os.path.join(ROOT, "tools", "matching")]
from coff import Coff, REL_DIR32, REL_REL32          # noqa: E402

# the hex run must end the identifier or be followed by '_' (FUN_00abcdef, g_01582df8_x); one followed by a letter is
# part of a word (resolve.py's HEX_RE)
HEX_RE = re.compile(r"(?<![0-9A-Fa-f])(?:0x)?([0-9A-Fa-f]{6,8})(?![0-9A-Za-z])")
IMAGE_LO, IMAGE_HI = 0x00401000, 0x02000000
_INDEX = None


def ident(name):
    """the identifier a symbol is named by: '?g_15b7458@@3PADA' -> 'g_15b7458', '_FUN_00abcdef' -> 'FUN_00abcdef'"""
    if name.startswith("??_"):           # a special name: ??_7C9990@@6B@ is C9990's vtable, not address 0x7c9990
        return name[4:].split("@", 1)[0]
    if name.startswith("??"):            # ??0Foo (constructor), ??1Foo (destructor), ??2 (operator new) ...
        return name[3:].split("@", 1)[0]
    if name.startswith("?"):
        n = name[1:]
        if n.startswith("$"):           # a template: ?$name@args@@...
            n = n[1:]
        return n.split("@", 1)[0]
    n = name.lstrip("_@")
    return re.sub(r"@\d+$", "", n)


def hex_claim(name, own):
    for m in HEX_RE.finditer(ident(name)):
        s = m.group(1)
        if not re.search(r"\d", s):
            continue
        va = int(s, 16)
        if IMAGE_LO <= va < IMAGE_HI and va != own:
            return va
    return None


def index():
    """exact mangled name -> {va}: symbols/*.txt, symbols/slices/*.txt and every manifest row"""
    global _INDEX
    if _INDEX is None:
        idx = defaultdict(set)
        for f in glob.glob(os.path.join(ROOT, "symbols", "*.txt")) + glob.glob(os.path.join(ROOT, "symbols", "slices", "*.txt")):
            for line in open(f, encoding="utf-8", errors="replace"):
                p = line.split("#", 1)[0].split(None, 1)
                if len(p) == 2 and p[1].strip().startswith(("?", "_", "@")):
                    try:
                        idx[p[1].strip()].add(int(p[0], 16))
                    except ValueError:
                        pass
        mans = ([os.path.join(ROOT, "match", "manifest.txt"), os.path.join(ROOT, "match", "clones.txt")]
                + glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt"))
                + glob.glob(os.path.join(ROOT, "match", "synth", "*.manifest"))
                + glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True))
        for f in mans:
            if not os.path.exists(f):
                continue
            for line in open(f, encoding="utf-8", errors="replace"):
                p = line.split("#", 1)[0].split()
                if len(p) >= 3 and p[1].startswith(("?", "_", "@")) and re.fullmatch(r"[0-9a-fA-F]{8}", p[2]):
                    idx[p[1]].add(int(p[2], 16))
        _INDEX = idx
    return _INDEX


def claim(name, own):
    """(address the name claims, how) or (None, None)"""
    va = hex_claim(name, own)
    if va is not None:
        return va, "hex-name"
    vas = index().get(name)
    if vas and len(vas) == 1:
        va = next(iter(vas))
        if va != own:
            return va, "symbols"
    return None, None


def masked_bytes(fp):
    """{offset: retail byte} behind the fingerprint's mask, or None for a fingerprint without them"""
    hx = fp.get("masked")
    if hx is None:
        return None
    offs = []
    for start, n in fp["mask"]:
        offs.extend(range(start, start + n))
    raw = bytes.fromhex(hx)
    return dict(zip(offs, raw))


def check(fp, obj, fname):
    """[(offset, symbol, verdict, claimed, retail, how)] for function `fname` of object `obj` at fp's address.
    None when the fingerprint has no masked bytes or the function is not in the object."""
    mb = masked_bytes(fp)
    if mb is None:
        return None
    coff = Coff(obj)
    fsym = coff.by_name.get(fname)
    if fsym is None or not fsym.defined:
        return None
    va = int(fp["va"], 16)
    sec = coff.sections[fsym.secno - 1]
    lo, hi = fsym.value, fsym.value + fp["size"]
    out = []
    for off, si, typ in sec.relocs:
        o = off - lo
        if not lo <= off < hi or typ not in (REL_DIR32, REL_REL32) or not all(o + k in mb for k in range(4)):
            continue
        s = coff.syms[si]
        want, how = claim(s.name, va)
        if want is None:
            continue
        ours = struct.unpack_from("<I", sec.data, off)[0]           # the addend our object stores in the field
        field = int.from_bytes(bytes(mb[o + k] for k in range(4)), "little")
        if typ == REL_DIR32:
            actual = (field - ours) & 0xFFFFFFFF
        else:   # REL32: target = S + A - (P + 4)
            disp = field - (1 << 32) if field & 0x80000000 else field
            actual = (va + o + 4 + disp - ours) & 0xFFFFFFFF
        out.append((o, s.name, "agree" if want == actual else "disagree", want, actual, how))
    bad = [x for x in out if x[2] == "disagree"]
    if bad and sorted(x[3] for x in bad) == sorted(x[4] for x in bad):
        out = [x[:2] + ("reordered",) + x[3:] if x[2] == "disagree" else x for x in out]
    return out


def describe(findings):
    """one line per disagreement, for the check's output"""
    return ["+%d %s: the name says 0x%08x (%s), retail uses 0x%08x" % (o, n, w, how, a)
            for o, n, v, w, a, how in findings if v == "disagree"]
