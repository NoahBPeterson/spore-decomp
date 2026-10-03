#!/usr/bin/env python3
"""disasm.py <image> <va-hex> [len]  — print original instructions (stops at ret+int3 padding)."""
import sys, pefile, capstone
pe = pefile.PE(sys.argv[1], fast_load=True)
va = int(sys.argv[2], 16); n = int(sys.argv[3]) if len(sys.argv) > 3 else 0x400
data = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, n)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for i in md.disasm(data, va):
    print("  %08x  %-22s %s %s" % (i.address, i.bytes.hex(), i.mnemonic, i.op_str))
    if len(sys.argv) <= 3 and i.mnemonic == "ret" and data[i.address - va + i.size:i.address - va + i.size + 1] in (b"\xcc", b""):
        break
