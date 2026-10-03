#!/usr/bin/env python3
"""Byte-exact verifier for 32-bit x86: compare one function in a COFF .obj against the
original image at a VA, masking relocated bytes on both sides.

usage: cmpobj.py <image> <obj> <symbol> <va-hex> [--len N] [--quiet]

- Our side: bytes covered by IMAGE_REL_I386_DIR32/DIR32NB/REL32/SECREL relocations are masked.
- Original side: bytes covered by base relocations (.reloc, absolute addresses) are masked.
- Length defaults to the size of the symbol's COMDAT section (compile with /Gy).
Exit 0 iff all unmasked bytes are identical.
"""
import argparse, struct, sys
import pefile

REL_SIZES = {0x06: 4, 0x07: 4, 0x14: 4, 0x0B: 4, 0x0A: 2}  # DIR32, DIR32NB, REL32, SECREL, SECTION

def parse_coff(path):
    d = open(path, "rb").read()
    machine, nsec, _, symptr, nsym, optsz, _ = struct.unpack_from("<HHIIIHH", d, 0)
    if machine != 0x14C:
        raise SystemExit("not an x86 COFF object")
    strtab = symptr + nsym * 18
    def name_of(raw):
        if raw[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            return d[strtab + off: d.index(b"\0", strtab + off)].decode()
        return raw.split(b"\0")[0].decode()
    secs = []
    for i in range(nsec):
        o = 20 + optsz + 40 * i
        raw = d[o:o + 8]
        size, ptr, relptr, _, nrel = struct.unpack_from("<IIIIH", d, o + 16)
        nm = raw.split(b"\0")[0].decode()
        if nm.startswith("/"):
            off = int(nm[1:]); nm = d[strtab + off: d.index(b"\0", strtab + off)].decode()
        relocs = [struct.unpack_from("<IIH", d, relptr + 10 * k) for k in range(nrel)]
        secs.append({"name": nm, "data": d[ptr:ptr + size] if ptr else b"\0" * size, "relocs": relocs})
    syms = {}
    i = 0
    while i < nsym:
        o = symptr + 18 * i
        value, secno, typ, cls, naux = struct.unpack_from("<IhHBB", d, o + 8)
        nm = name_of(d[o:o + 8])
        if secno > 0 and cls in (2, 3) and (typ >> 4) == 2:  # function symbols
            syms.setdefault(nm, (secno - 1, value))
        i += 1 + naux
    return secs, syms

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("image"); ap.add_argument("obj"); ap.add_argument("symbol"); ap.add_argument("va")
    ap.add_argument("--len", type=int); ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    secs, syms = parse_coff(a.obj)
    if a.symbol not in syms:
        cands = [s for s in syms if a.symbol in s]
        if len(cands) != 1:
            raise SystemExit("symbol %r not found; candidates: %s" % (a.symbol, ", ".join(sorted(syms))))
        a.symbol = cands[0]
    si, off = syms[a.symbol]
    sec = secs[si]
    length = a.len or (len(sec["data"]) - off)
    mine = sec["data"][off:off + length]
    mask_mine = set()
    for vaddr, _sym, typ in sec["relocs"]:
        n = REL_SIZES.get(typ, 4)
        for k in range(n):
            if off <= vaddr + k < off + length:
                mask_mine.add(vaddr + k - off)

    pe = pefile.PE(a.image, fast_load=True)
    pe.parse_data_directories([pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_BASERELOC"]])
    va = int(a.va, 16)
    rva = va - pe.OPTIONAL_HEADER.ImageBase
    orig = pe.get_data(rva, length)
    mask_orig = set()
    for blk in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
        if blk.struct.VirtualAddress + 0x1000 <= rva or blk.struct.VirtualAddress >= rva + length:
            continue
        for e in blk.entries:
            if e.type == 3 and rva - 3 <= e.rva < rva + length:
                for k in range(4):
                    if 0 <= e.rva + k - rva < length:
                        mask_orig.add(e.rva + k - rva)
    mask = mask_mine | mask_orig
    diffs = [i for i in range(length) if i not in mask and orig[i] != mine[i]]
    ok = not diffs and len(mine) == length
    if not a.quiet or not ok:
        print("%s @ %08x len %d: %s (%d diff bytes, %d masked)" % (
            a.symbol, va, length, "MATCH" if ok else "DIFF", len(diffs), len(mask)))
    if not ok and not a.quiet:
        def row(b, m):
            return " ".join("..".format() if i in m else "%02x" % b[i] for i in range(len(b)))
        print(" orig:", row(orig, mask))
        print(" mine:", row(mine, mask))
        print(" diff@", diffs[:32])
    return 0 if ok else 1

if __name__ == "__main__":
    sys.exit(main())
