#!/usr/bin/env python3
"""Classify the stack slots the ORIGINAL functions use (from the image) so we know which slots are
dead (written but never read) and how much frame padding they imply, without needing a working
disassembler pipeline.  usage: origslots.py <va-hex> <length-dec>"""
import sys, os, re, pefile, capstone

ROOT = "/Users/noahpeterson/Documents/Projects/spore-decomp"
IMAGE = os.path.join(ROOT, "work/SporeApp.analysis.bin")

def slots(va, n):
    pe = pefile.PE(IMAGE, fast_load=True)
    data = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, n)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    frame = None
    write, read = {}, {}
    for ins in md.disasm(data, va):
        o = ins.op_str
        if ins.mnemonic == "sub" and o.startswith("esp, "):
            frame = int(o.split(",")[1].strip(), 0)
        for m in re.finditer(r"\[ebp - (0x[0-9a-f]+|\d+)\]", o):
            k = int(m.group(1), 0)
            if ins.mnemonic == "lea":
                write.setdefault(k, "lea")
            elif re.match(r"dword ptr \[ebp - (0x[0-9a-f]+|\d+)\], ", o) or \
                 re.match(r"byte ptr \[ebp - (0x[0-9a-f]+|\d+)\], ", o) or \
                 re.match(r"word ptr \[ebp - (0x[0-9a-f]+|\d+)\], ", o):
                write.setdefault(k, ins.mnemonic)
            else:
                read.setdefault(k, ins.mnemonic)
        if ins.mnemonic == "ret" or (ins.mnemonic == "int3" and ins.address > va):
            break
    return frame, write, read

if __name__ == "__main__":
    va = int(sys.argv[1], 16); n = int(sys.argv[2])
    frame, write, read = slots(va, n)
    dead = sorted(set(write) - set(read))
    print("frame 0x%x" % (frame or 0))
    print("written:", " ".join("-0x%x" % k for k in sorted(write)))
    print("read   :", " ".join("-0x%x" % k for k in sorted(read)))
    print("DEAD   :", " ".join("-0x%x(%s)" % (k, write[k]) for k in dead))
