#!/usr/bin/env python3
"""Dump one function's exact instruction stream from a COFF .obj as `orig`-style text, so it can be
diffed against `cmpdis.py` output line for line and the slot/register flow compared by eye.

usage: objdump.py <obj> <symbol> [max-insns]
"""
import sys, os
sys.path.insert(0, "/Users/noahpeterson/Documents/Projects/spore-decomp/tools/matching")
from cmpobj import parse_coff
import capstone

def main(obj, sym, n=400):
    secs, syms = parse_coff(obj)
    if sym not in syms:
        cands = [k for k in syms if sym in k]
        print("no exact symbol; candidates:", cands[:5]); return
    si, off = syms[sym]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for i, ins in enumerate(md.disasm(secs[si]["data"][off:], 0)):
        print("%4d  %-8s %s" % (i, ins.mnemonic, ins.op_str))
        if i >= n or ins.mnemonic == "ret":
            break

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], int(sys.argv[3]) if len(sys.argv) > 3 else 400)
