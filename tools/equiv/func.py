"""The two sides of an equivalence check (tools/equiv/LAYERS.md): the retail function and our build of it.

Func.relocs maps the offset of each 4-byte relocated field to a token:
  retail:      ("abs", target)                    target = absolute address, or the destination of a rel32 call/jmp
  ours (obj):  ("sym", name, coff_type, addend)   a COFF relocation (type 6 DIR32, 7 DIR32NB, 0x14 REL32)
  ours (DLL):  ("abs", target)                    an /LTCG build is linked, so its fields are addresses in the DLL
Layers compare tokens through one consistent bijection (the same trust the byte-match check places in relocations).
"""
import os, struct, sys
from dataclasses import dataclass, field

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
for _d in ("tools/matching", "tools/contrib", "tools/ci", "tools/difftest"):
    _p = os.path.join(ROOT, _d)
    if _p not in sys.path:
        sys.path.append(_p)
IMAGE = os.path.join(ROOT, "work", "SporeApp.analysis.bin")

import capstone  # noqa: E402

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_pe = None


@dataclass
class Func:
    va: int                      # where the code sits (ours: its own base; layers place it as they need)
    code: bytes
    relocs: dict = field(default_factory=dict)
    name: str = ""
    side: str = ""               # "retail" or "ours"
    meta: dict = field(default_factory=dict)   # ours: src, flags, obj or dll path, symbol


def image():
    global _pe
    if _pe is None:
        import pefile
        if not os.path.exists(IMAGE):
            raise SystemExit("needs work/SporeApp.analysis.bin (tools/contrib/make_image.py, from your own game)")
        _pe = pefile.PE(IMAGE, fast_load=True)
    return _pe


def _rel32_targets(code, base):
    out = {}
    for i in MD.disasm(code, base):
        b = i.bytes
        if (b[0] in (0xE8, 0xE9) and i.size == 5) or (b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and i.size == 6):
            out[i.address - base + i.size - 4] = int(i.op_str, 16)
    return out


def tokens_abs(code, base, relset):
    """relocated 4-byte fields -> ("abs", target): the destination of a rel32 call/jmp, else the raw value"""
    rel32 = _rel32_targets(code, base)
    out = {}
    for o in sorted(relset):
        if o + 3 in relset and all(o - k not in out for k in (1, 2, 3)):
            out[o] = ("abs", rel32[o]) if o in rel32 else ("abs", struct.unpack_from("<I", code, o)[0])
    return out


def retail_func(va):
    import task
    import fingerprint as F
    fp = task.fingerprint(va)
    if not fp:
        raise SystemExit("0x%08x has no fingerprint" % va)
    pe = image()
    code = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, fp["size"])
    return Func(va, code, tokens_abs(code, va, F.unpack_mask(fp["mask"])), "0x%08x" % va, "retail",
                {"fingerprint": fp["sha256"], "size": fp["size"]})


def coff_names(path):
    d = open(path, "rb").read()
    _, nsec, _, symptr, nsym, _, _ = struct.unpack_from("<HHIIIHH", d, 0)
    strtab = symptr + nsym * 18
    names, i = {}, 0
    while i < nsym:
        o = symptr + 18 * i
        raw = d[o:o + 8]
        if raw[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            nm = d[strtab + off: d.index(b"\0", strtab + off)].decode("latin-1")
        else:
            nm = raw.split(b"\0")[0].decode("latin-1")
        value, secno = struct.unpack_from("<IH", d, o + 8)
        names[i] = (nm, value, secno)
        i += 1 + d[o + 17]
    return names


def obj_func(obj, sym, size=None):
    import fingerprint as F
    secs, syms = F.parse_coff(obj)
    data, _rel = F.extract(secs, syms, sym)
    if size:
        data = data[:size]
    si, off = syms[sym]
    names = coff_names(obj)
    toks = {}
    for v, symi, typ in secs[si]["relocs"]:
        if off <= v < off + len(data) and typ in (0x06, 0x07, 0x14):
            nm, value, secno = names.get(symi, ("?%d" % symi, 0, 0))
            addend = struct.unpack_from("<I", data, v - off)[0]
            if nm.startswith("."):          # a section symbol: name the place by section and offset
                nm = "%s#%d+%x" % (nm, secno, value)
            toks[v - off] = ("sym", nm, typ, addend)
    return Func(0, data, toks, sym, "ours", {"obj": obj, "symbol": sym})


def ret64(symbol):
    """True when the decorated name returns a 64-bit integer (__int64 / unsigned __int64: edx:eax)."""
    import re
    return bool(symbol) and re.search(r"@@(?:Y[A-Z]|[A-Z][A-D][A-Z])_[JK]", symbol) is not None


def our_func(va, flags=None):
    """Build our function the way the byte-match check does (an /LTCG build when it has a stub file)."""
    import task as T
    import slice as S
    import ltcg
    from coff import Coff
    fp = T.fingerprint(va)
    src, ident = T.locate(va)
    if not src:
        raise SystemExit("0x%08x: no source file has its // @ marker" % va)
    fl, _ = S.choose_flags(ident, va, flags)
    obj, log = S.compile_obj(src, fl)
    if not obj:
        raise SystemExit("COMPILE FAILED\n" + (log or "")[-2000:])
    sym, why = S.find_symbol(Coff(obj), ident, va, src, orig_size=fp["size"])
    if not isinstance(sym, str):
        raise SystemExit("0x%08x: compiled function not found: %s" % (va, why))
    meta = {"src": os.path.relpath(src, ROOT), "flags": fl, "symbol": sym, "ret64": ret64(sym)}
    stubs = ltcg.stubs_file(ident, va)
    if stubs:
        import tempfile
        keep = tempfile.mkdtemp(prefix="prove_ltcg_", dir=os.path.join(ROOT, "work"))
        data, rel, log = ltcg.build(src, fl, stubs, sym, fp["size"], keep=keep)
        if data is None:
            raise SystemExit(log)
        m = ltcg.read_map(os.path.join(keep, "ltcg.map"))
        base = m[sym]
        nxt = min([v for v in m.values() if v > base] or [base + len(data)])
        data, rel = ltcg.cut(os.path.join(keep, "ltcg.dll"), base, nxt - base)   # our own extent, not retail's
        n = len(data.rstrip(b"\xcc"))
        data, rel = data[:n], {o for o in rel if o < n}
        f = Func(base, data, tokens_abs(data, base, rel), sym, "ours", dict(meta, dll=os.path.join(keep, "ltcg.dll"),
                                                                             stubs=os.path.relpath(stubs, ROOT)))
        return f
    f = obj_func(obj, sym)
    f.meta.update(meta)
    return f


def build_hash(f):
    """sha256 of the code with every relocated field zeroed, plus the relocated offsets: what an equivalence proof
    is about. A change of our bytes (other than which symbol a relocation names) invalidates the proof."""
    import hashlib
    import json
    b = bytearray(f.code)
    for o in f.relocs:
        b[o:o + 4] = b"\0\0\0\0"
    return hashlib.sha256(bytes(b) + json.dumps(sorted(f.relocs)).encode()).hexdigest()


def bundle_path(row_file, va):
    """equivalent/<va>.json next to the equivalent.txt that lists the function"""
    return os.path.join(os.path.dirname(row_file), "equivalent", "%08x.json" % va)
