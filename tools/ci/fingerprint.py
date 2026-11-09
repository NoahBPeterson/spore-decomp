#!/usr/bin/env python3
"""Function fingerprints: a byte-exact check against the retail SporeApp.exe without the retail binary.

A fingerprint is made once by a maintainer, from the retail image (make_fingerprints.py):
  size    the retail function's length (to the next function, trailing int3 padding dropped)
  mask    byte offsets the compiler emits as relocations: the retail .reloc fixups, every 4-byte immediate or
          displacement holding an address in the image or read through fs: (thread-local storage), and the 4-byte
          displacement of every call/jmp/jcc rel32 that leaves the function or targets its own start
  sha256  of the retail bytes with the masked offsets zeroed
Fingerprints hold no names and no code bytes.

The check (gate.py, CI) compiles the function, cuts it out of the object file together with the EH funclets and local
labels the compiler places after it, and requires: the same size, every relocation on a masked offset, the same hash.
Agreement with run_all.py on 79,169 manifest rows (2026-11-09, work/claude/fpcheck_all.py): never passes a row that
run_all.py fails; fails ~0.4% that run_all.py passes, about half of them because run_all.py accepts a constant
modelled as an address (0x0042fc40: push 0x2458018 written as &g_Table2458018).
"""
import hashlib, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
from cmpobj import parse_coff, REL_SIZES     # noqa: E402

# symbols that belong to the function before them: EH funclets and local labels ($LN12@f, jump tables)
FUNCLET = ("__ehhandler$", "__unwindfunclet$", "__catch$", "__tryend$", "$")


def mhash(data, mask):
    b = bytearray(data)
    for i in mask:
        if i < len(b):
            b[i] = 0
    return hashlib.sha256(bytes(b)).hexdigest()


def pack_mask(mask):
    """sorted offsets -> [[start, length], ...]"""
    out = []
    for i in sorted(mask):
        if out and out[-1][0] + out[-1][1] == i:
            out[-1][1] += 1
        else:
            out.append([i, 1])
    return out


def unpack_mask(runs):
    return {s + k for s, n in runs for k in range(n)}


# ---- maintainer side (needs the retail image) ----

def _disasm():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


def image_range(orig):
    """[lo, hi) of the loaded image: the end of the last section (the analysis image's SizeOfImage is smaller)."""
    ends = [s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData) for s in orig.pe.sections]
    return orig.base, orig.base + max(ends)


def retail_sizes(orig, starts):
    """retail size of each function in starts (sorted VAs): up to the next start, cut at a ret directly followed by
    push ebp; mov ebp, esp (a function no list knows, 137 byte-exact rows), trailing int3 padding dropped"""
    md, s = _disasm(), {}
    for va, nxt in zip(starts, starts[1:]):
        if nxt - va <= 0x100000:
            d = bytes(orig.bytes_and_mask(va, nxt - va)[0])
            for ins in md.disasm(d, va):
                e = ins.address - va + ins.size
                if ins.mnemonic == "ret" and d[e:e + 3] == b"\x55\x8b\xec":
                    d = d[:e]
                    break
            s[va] = len(d.rstrip(b"\xcc"))
    return s


def make(orig, va, size, md=None, rng=None):
    md = md or _disasm()
    lo, hi = rng or image_range(orig)
    data, mask = orig.bytes_and_mask(va, size)
    mask = set(mask)
    for ins in md.disasm(bytes(data), va):
        b = ins.bytes
        fs = 0x64 in ins.prefix
        for o, n in ((ins.disp_offset, ins.disp_size), (ins.imm_offset, ins.imm_size)):
            if o and n == 4:
                v = int.from_bytes(b[o:o + 4], "little")
                # an address in the image is a relocation even where retail .reloc does not list it (260 rows); fs:[n]
                # is __tls_array, an absolute symbol (6 rows)
                if lo <= v < hi or (fs and o == ins.disp_offset):
                    a = ins.address - va + o
                    mask |= {a, a + 1, a + 2, a + 3}
        if (b[0] in (0xE8, 0xE9) and ins.size == 5) or (b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and ins.size == 6):
            # a call or jump that leaves the function, or goes to its own start (self-recursion: 495 rows)
            if not va < int(ins.op_str, 16) < va + size:
                o = ins.address - va + ins.size - 4
                mask |= {o, o + 1, o + 2, o + 3}
    return {"va": "%08x" % va, "size": size, "mask": pack_mask(mask), "sha256": mhash(data, mask)}


# ---- check side (CI: object file only) ----

def extract(obj_secs, syms, name):
    """(bytes, relocated offsets) of function `name` and its trailing funclets/labels"""
    si, off = syms[name]
    sec = obj_secs[si]
    after = sorted(o for nm, (s_, o) in syms.items() if s_ == si and o > off and not nm.startswith(FUNCLET))
    data = sec["data"][off:after[0] if after else len(sec["data"])].rstrip(b"\xcc")
    n = len(data)
    rel = {v + k - off for v, _s, t in sec["relocs"] for k in range(REL_SIZES.get(t, 4)) if off <= v + k < off + n}
    return data, rel


def check(fp, data, rel):
    """'PASS' or why not"""
    if len(data) != fp["size"]:
        return "size %d, retail %d" % (len(data), fp["size"])
    mask = unpack_mask(fp["mask"])
    stray = sorted(rel - mask)
    if stray:
        return "relocation at offset %s where the retail bytes are fixed" % ",".join(map(str, stray[:4]))
    return "PASS" if mhash(data, mask) == fp["sha256"] else "bytes differ"
