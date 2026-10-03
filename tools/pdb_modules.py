#!/usr/bin/env python3
"""List modules (object files) and their code contributions from a PDB's DBI stream.
usage: pdb_modules.py <pdb> <out.json>"""
import json, struct, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from msf import MSF

m = MSF(sys.argv[1])
dbi = m.stream(3)
(sig, ver, age, gsi, build, psi, dllver, symrec, rbld, modsz, sczsz, smapsz, srcsz, tsmsz, mfc,
 dbgsz, ecsz, flags, machine) = struct.unpack_from("<iIIHHHHHHiiiiiIiiHH", dbi, 0)
o = 64; end = o + modsz; mods = []
while o < end:
    sym_stream, sym_bytes = struct.unpack_from("<HI", dbi, o + 34)
    names = dbi[o + 64:].split(b"\0", 2)
    mods.append({"index": len(mods), "module": names[0].decode("latin-1"), "obj": names[1].decode("latin-1"),
                 "sym_stream": sym_stream, "sym_bytes": sym_bytes, "contribs": []})
    o += 64 + len(names[0]) + 1 + len(names[1]) + 1
    o = (o + 3) & ~3
# section contributions
o = end
scver = struct.unpack_from("<I", dbi, o)[0]; o += 4
entsz = 28 if scver == 0xeffe0000 + 19970605 else 32
while o + entsz <= end + sczsz:
    sec, _, off, size, ch, mi = struct.unpack_from("<HHiiIH", dbi, o)
    if mi < len(mods) and (ch & 0x20):   # IMAGE_SCN_CNT_CODE
        mods[mi]["contribs"].append([sec, off, size])
    o += entsz
json.dump(mods, open(sys.argv[2], "w"))
code = [x for x in mods if x["contribs"]]
print("modules %d, with code %d" % (len(mods), len(code)))
for x in code[:5]:
    print(" ", x["module"], len(x["contribs"]), "contribs")
