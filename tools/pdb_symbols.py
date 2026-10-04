#!/usr/bin/env python3
"""Dump function/global symbols from a PDB without Ghidra.

usage: pdb_symbols.py <pdb> <exe> <out.json>
Reads S_PUB32 from the DBI symbol-record stream and S_GPROC32/S_LPROC32 (with code size) from
every module stream. Addresses are converted to VAs using the exe's section table.
Output: {"functions": [{va, size, name, module}], "publics": [{va, name, code}], "globals": [...],
         "thunks": {thunk_va: target_va}}  (ILT jmp stubs; vtables and calls point at these in /INCREMENTAL builds)
"""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from msf import MSF
import pefile

S_PUB32, S_GPROC32, S_LPROC32, S_GDATA32, S_LDATA32 = 0x110E, 0x1110, 0x110F, 0x110D, 0x110C
S_TRAMPOLINE = 0x112C  # "* Linker *" module: incremental-link thunk -> target

def records(buf, start=0):
    o = start
    while o + 4 <= len(buf):
        ln, kind = struct.unpack_from("<HH", buf, o)
        if ln < 2:
            break
        yield kind, buf[o + 4:o + 2 + ln]
        o += 2 + ln

def cstr(b, off):
    return b[off:b.index(b"\0", off)].decode("latin-1")

pdb, exe, out = sys.argv[1:4]
m = MSF(pdb)
pe = pefile.PE(exe, fast_load=True)
base = pe.OPTIONAL_HEADER.ImageBase
secva = [s.VirtualAddress for s in pe.sections]
va = lambda seg, off: base + secva[seg - 1] + off if 1 <= seg <= len(secva) else None

dbi = m.stream(3)
symrec = struct.unpack_from("<H", dbi, 20)[0]
publics = []
for kind, r in records(m.stream(symrec)):
    if kind == S_PUB32:
        flags, off, seg = struct.unpack_from("<IIH", r, 0)
        a = va(seg, off)
        if a:
            publics.append({"va": a, "name": cstr(r, 10), "code": bool(flags & 2)})

mods = json.load(open(os.path.join(os.path.dirname(out), "modules.json"))) if os.path.exists(
    os.path.join(os.path.dirname(out), "modules.json")) else []
funcs, globs, thunks = [], [], {}
for mod in mods:
    s = mod["sym_stream"]
    if s == 0xFFFF or s >= len(m.sizes):
        continue
    buf = m.stream(s)[:mod["sym_bytes"]]
    for kind, r in records(buf, 4):   # module symbols start after a 4-byte signature
        if kind in (S_GPROC32, S_LPROC32):
            # parent, end, next, len, dbgstart, dbgend, typind, off, seg, flags, name
            ln, typ, off, seg = struct.unpack_from("<I", r, 12)[0], struct.unpack_from("<I", r, 24)[0], \
                struct.unpack_from("<I", r, 28)[0], struct.unpack_from("<H", r, 32)[0]
            a = va(seg, off)
            if a:
                funcs.append({"va": a, "size": ln, "name": cstr(r, 35), "module": mod["module"],
                              "local": kind == S_LPROC32})
        elif kind == S_TRAMPOLINE:
            ttype, cb, othunk, otarget, sthunk, starget = struct.unpack_from("<HHIIHH", r, 0)
            a, t = va(sthunk, othunk), va(starget, otarget)
            if a and t:
                thunks["%08x" % a] = t
        elif kind in (S_GDATA32, S_LDATA32):
            typ, off, seg = struct.unpack_from("<IIH", r, 0)
            a = va(seg, off)
            if a:
                globs.append({"va": a, "name": cstr(r, 10), "module": mod["module"]})
json.dump({"functions": funcs, "publics": publics, "globals": globs, "thunks": thunks}, open(out, "w"))
print("functions %d (from module streams), publics %d (%d code), module globals %d, ILT thunks %d" % (
    len(funcs), len(publics), sum(p["code"] for p in publics), len(globs), len(thunks)))
