#!/usr/bin/env python3
"""Read a COFF .obj and print, per function: frame size, `this` home slot, and the slot of the
first `mov dword ptr [ebp-X], <reg>` store (used to see which /Od name lands highest).
usage: objslots.py <obj> [symsubstr]
"""
import sys, os, struct, re
sys.path.insert(0, "/Users/noahpeterson/Documents/Projects/spore-decomp/tools/matching")
from cmpobj import parse_coff
import capstone

def funcs(obj, want=None):
    secs, syms = parse_coff(obj)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for name, (si, off) in sorted(syms.items(), key=lambda kv: kv[1]):
        if want and want not in name:
            continue
        code = secs[si]["data"][off:]
        frame = this = first = None
        stores = []
        for ins in md.disasm(code, 0):
            o = ins.op_str
            if ins.mnemonic == "sub" and o.startswith("esp, "):
                frame = int(o.split(",")[1], 0)
            m = re.match(r"dword ptr \[ebp - (0x[0-9a-f]+|\d+)\], (ecx|eax|edx)$", o)
            if m:
                k = int(m.group(1), 0)
                if m.group(2) == "ecx" and this is None:
                    this = k
                elif m.group(2) != "ecx" and first is None:
                    first = k
                stores.append((k, m.group(2)))
            if ins.mnemonic == "ret":
                break
        print("%-42s frame=%-6s this=%-6s firststore=%s  stores=%s" %
              (name[:42], "0x%x" % frame if frame else "-", "-0x%x" % this if this else "-",
               "-0x%x" % first if first else "-", " ".join("-0x%x:%s" % s for s in stores[:14])))

if __name__ == "__main__":
    funcs(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None)
