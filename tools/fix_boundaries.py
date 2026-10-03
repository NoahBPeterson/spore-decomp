#!/usr/bin/env python3
"""Validate weak function starts and find missing ones by linear sweep between strong starts.

Strong start = has a CALL reference or a pointer from outside .text (work/index/evidence.csv).
Between consecutive strong starts, decode linearly; a padding start is an address X that is
16-byte aligned and preceded by >=1 int3 bytes that follow a terminating instruction
(ret / ret n / jmp) on a decoded instruction boundary. Weak functions that are not padding
starts are deleted; padding starts that are not functions are created.
Writes work/index/boundary_fix.json and prints counts.
"""
import csv, json, os
import pefile, capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
t = pe.sections[0]; text = t.get_data(); base = pe.OPTIONAL_HEADER.ImageBase + t.VirtualAddress
end_text = base + t.Misc_VirtualSize
rows = list(csv.DictReader(open(os.path.join(ROOT, "work/index/evidence.csv"))))
allf = set(int(r["address"], 16) for r in rows)
strong = sorted(int(r["address"], 16) for r in rows if int(r["code_refs"]) or int(r["data_refs"]))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.skipdata = True

TERM = {"ret", "retn", "jmp", "int3"}
padstarts = set()
for i, s in enumerate(strong):
    e = strong[i + 1] if i + 1 < len(strong) else end_text
    if not (base <= s < end_text):
        continue
    lim = min(e, end_text)
    data = text[s - base: lim - base]
    last_term_end = None
    for ins in md.disasm(data, s):
        a, n = ins.address, ins.size
        if ins.mnemonic in ("ret", "retn", "jmp") :
            last_term_end = a + n
        elif ins.mnemonic == "int3":
            pass
        else:
            if last_term_end is not None and a > last_term_end and a % 16 == 0 and \
                    all(b == 0xCC for b in text[last_term_end - base: a - base]):
                padstarts.add(a)
            last_term_end = None
        if ins.mnemonic not in ("ret", "retn", "jmp", "int3"):
            last_term_end = None if ins.mnemonic != "int3" else last_term_end

strong_set = set(strong)
weak = allf - strong_set
delete = sorted(a for a in weak if a not in padstarts and base <= a < end_text)
create = sorted(a for a in padstarts if a not in allf)
json.dump({"delete": ["%08x" % a for a in delete], "create": ["%08x" % a for a in create]},
          open(os.path.join(ROOT, "work/index/boundary_fix.json"), "w"))
print("strong %d, weak %d, weak confirmed by padding %d, delete %d, create %d" % (
    len(strong), len(weak), len(weak & padstarts), len(delete), len(create)))
