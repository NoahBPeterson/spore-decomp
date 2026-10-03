#!/usr/bin/env python3
"""Group small undone functions by normalized instruction pattern.

usage: patterns.py [--max-len 48] [--top 40] [--write work/patterns.json]
Normalization: immediates and displacements -> N, absolute addresses -> A, branch targets -> rel offsets.
"""
import argparse, collections, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile, capstone
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ap = argparse.ArgumentParser()
ap.add_argument("--max-len", type=int, default=48); ap.add_argument("--top", type=int, default=40)
ap.add_argument("--write")
a = ap.parse_args()
pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
slices = json.load(open(os.path.join(ROOT, "work/slices.json")))
groups = collections.defaultdict(list)
for s in slices:
    for f in s["functions"]:
        va = int(f["va"], 16)
        code = pe.get_data(va - 0x400000, min(f["size"], a.max_len + 16))
        n = len(code)
        while n and code[n - 1] == 0xCC: n -= 1
        if n > a.max_len or n == 0: continue
        code = code[:n]
        toks = []
        for i in md.disasm(code, va):
            ops = i.op_str
            if i.mnemonic.startswith("j") or i.mnemonic == "call":
                if re.fullmatch(r"0x[0-9a-f]+", ops):
                    t = int(ops, 16) - va
                    ops = "+%d" % t if 0 <= t < n else "EXT"
            ops = re.sub(r"0x[0-9a-f]{6,8}", "A", ops)
            ops = re.sub(r"0x[0-9a-f]+|\b\d+\b", "N", ops)
            toks.append("%s %s" % (i.mnemonic, ops))
        groups[" ; ".join(toks)].append(f["va"])
order = sorted(groups.items(), key=lambda kv: -len(kv[1]))
covered = 0
for k, v in order[:a.top]:
    covered += len(v)
    print("%5d  %s" % (len(v), k[:150]))
print("groups %d, functions %d, top-%d cover %d" % (len(groups), sum(len(v) for v in groups.values()), a.top, covered))
if a.write:
    json.dump([{"pattern": k, "vas": v} for k, v in order], open(a.write, "w"))
