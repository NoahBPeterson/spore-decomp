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

Per relocation: agree, folded (retail uses a byte-identical copy of the named function, by the fingerprints),
disagree, or reordered (the function uses exactly the expected addresses at swapped places:
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
    if name.startswith("??"):
        # a special member (??0 constructor, ??1 destructor, ??2 operator new, ??_7 vtable ...): what follows is its
        # CLASS name, and a hex run there is a stand-in class's tag (Obj_6af960), not this symbol's address
        return ""
    if name.startswith("?"):
        n = name[1:]
        if n.startswith("$"):           # a template: ?$name@args@@...
            n = n[1:]
        return n.split("@", 1)[0]
    n = name.lstrip("_@")
    return re.sub(r"@\d+$", "", n)


def hex_claim(name, own):
    """the address an identifier claims for itself: only a hex run that ENDS it (FUN_00abcdef, g_15b7458). One followed
    by more text is a placeholder naming something else's address (H_572810_4: helper 4 of function 0x572810;
    vt_4610c0_a: a vtable used by 0x4610c0), not the object's own."""
    i = ident(name)
    if i.lower().startswith("thunk_"):  # thunk_FUN_00e823a0 jumps TO 0x00e823a0; the thunk lives elsewhere
        return None
    for m in HEX_RE.finditer(i):
        s = m.group(1)
        if not re.search(r"\d", s) or m.end() != len(i):
            continue
        va = int(s, 16)
        if IMAGE_LO <= va < IMAGE_HI and va != own:
            return va
    return None


def _read_symbols(path, idx):
    for line in open(path, encoding="utf-8", errors="replace"):
        p = line.split("#", 1)[0].split(None, 1)
        if len(p) == 2 and p[1].strip().startswith(("?", "_", "@")):
            try:
                idx[p[1].strip()].add(int(p[0], 16))
            except ValueError:
                pass


def _read_manifest(path, idx):
    if not os.path.exists(path):
        return
    for line in open(path, encoding="utf-8", errors="replace"):
        p = line.split("#", 1)[0].split()
        if len(p) >= 3 and p[1].startswith(("?", "_", "@")) and re.fullmatch(r"[0-9a-fA-F]{8}", p[2]):
            idx[p[1]].add(int(p[2], 16))


def index(sid=None):
    """exact mangled name -> {va}. Global: symbols/*.txt and the src/game manifests. Per slice: that slice's
    symbols/slices/<sid>.txt and manifest. Other slices' records are not used: stand-in names (Elem, Obj, Base) are
    per slice, so another slice's `Elem` says nothing about this one's."""
    global _INDEX
    if _INDEX is None:
        idx = defaultdict(set)
        for f in glob.glob(os.path.join(ROOT, "symbols", "*.txt")):
            _read_symbols(f, idx)
        for f in glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True):
            _read_manifest(f, idx)
        _INDEX = (idx, {})
    glob_idx, per = _INDEX
    if not sid:
        return glob_idx
    if sid not in per:
        idx = defaultdict(set)
        f = os.path.join(ROOT, "symbols", "slices", sid + ".txt")
        if os.path.exists(f):
            _read_symbols(f, idx)
        _read_manifest(os.path.join(ROOT, "match", "slices", sid, "manifest.txt"), idx)
        per[sid] = idx
    return per[sid]


def claim(name, own, sid=None):
    """(address the name claims, how) or (None, None)"""
    va = hex_claim(name, own)
    if va is not None:
        return va, "hex-name"
    vas = set(index().get(name, ())) | set(index(sid).get(name, ()) if sid else ())
    if len(vas) == 1:
        va = next(iter(vas))
        if va != own:
            return va, "symbols"
    return None, None


def slice_of(src):
    """the slice id of a row's source ('slices/s00425240/s00425240.cpp', or an absolute path under match/slices/)"""
    m = re.search(r"(?:^|/)slices/(s[0-9a-f]{8})/", (src or "").replace("\\", "/"))
    return m.group(1) if m else None


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


def same_function(fps, a, b):
    """retail functions a and b are byte-identical copies (same size, hash and addresses): a name pointing at one where
    retail uses the other is fine (the linker kept separate copies of the same code)"""
    x, y = fps.get(a), fps.get(b)
    return bool(x and y and x["size"] == y["size"] and x["sha256"] == y["sha256"] and x.get("masked") == y.get("masked")
                and x["mask"] == y["mask"])


def check(fp, obj, fname, fps=None, src=None):
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
        want, how = claim(s.name, va, slice_of(src))
        if want is None:
            continue
        ours = struct.unpack_from("<I", sec.data, off)[0]           # the addend our object stores in the field
        field = int.from_bytes(bytes(mb[o + k] for k in range(4)), "little")
        if typ == REL_DIR32:
            actual = (field - ours) & 0xFFFFFFFF
        else:   # REL32: target = S + A - (P + 4)
            disp = field - (1 << 32) if field & 0x80000000 else field
            actual = (va + o + 4 + disp - ours) & 0xFFFFFFFF
        verdict = "agree" if want == actual else "folded" if fps and same_function(fps, want, actual) else "disagree"
        out.append((o, s.name, verdict, want, actual, how))
    bad = [x for x in out if x[2] == "disagree"]
    if bad and sorted(x[3] for x in bad) == sorted(x[4] for x in bad):
        out = [x[:2] + ("reordered",) + x[3:] if x[2] == "disagree" else x for x in out]
    return out


def describe(findings):
    """one line per disagreement, for the check's output"""
    return ["+%d %s: the name says 0x%08x (%s), retail uses 0x%08x" % (o, n, w, how, a)
            for o, n, v, w, a, how in findings if v == "disagree"]
