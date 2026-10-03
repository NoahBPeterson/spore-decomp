#!/usr/bin/env python3
"""Instruction-level diff of one function: original image vs compiled object.

usage: cmpdis.py <obj> <symbol-substring> <va-hex>
Disassembles both, normalizes branch/call targets and relocated operands, prints a unified diff.
"""
import difflib, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile, capstone
from cmpobj import parse_coff

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
obj, sym, va = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
secs, syms = parse_coff(obj)
c = [s for s in syms if s == sym] or [s for s in syms if sym in s and not s.startswith(("__ehhandler", "__unwindfunclet"))]
if len(c) != 1:
    sys.exit("ambiguous/not found: %s" % ", ".join(c) if c else "not found")
si, off = syms[c[0]]
mine = secs[si]["data"][off:]
pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
orig = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, len(mine) + 64)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

def norm(code, base, limit):
    out = []
    for i in md.disasm(code, base):
        if i.address - base >= limit:
            break
        ops = i.op_str
        if i.mnemonic.startswith("j") or i.mnemonic == "call":
            if re.fullmatch(r"0x[0-9a-f]+", ops):
                t = int(ops, 16) - base
                ops = "<+%#x>" % t if 0 <= t < limit else "<ext>"
        ops = re.sub(r"0x[0-9a-f]{6,8}", "<addr>", ops)
        out.append("%s %s" % (i.mnemonic, ops))
        if i.mnemonic == "ret" and i.address - base + i.size >= limit:
            break
    return out

a = norm(orig, va, len(mine)); b = norm(mine, 0, len(mine))
d = list(difflib.unified_diff(a, b, "original", "mine", lineterm="", n=2))
print("\n".join(d) if d else "instruction streams identical (after normalization)")
