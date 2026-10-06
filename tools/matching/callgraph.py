#!/usr/bin/env python3
"""Build a direct-call graph of the executable and rank functions breadth-first from the entry point.

usage: callgraph.py [--root 0xVA] [--out work/bfs_rank.json]

Disassembles every function (using the decomp index for starts and the analysis PE for bytes),
collects direct `call`/`jmp` targets that land inside .text, maps each to its containing function,
and BFS-orders functions by call distance from the root.

Root defaults to the unpacked OEP in work/SporeApp.analysis.json (the PE "entry point" is the
packer stub in .bind, which is outside the decompiled .text range).  Writes:
  { "root": "0x..", "total": N, "reachable": M, "edges": E,
    "rank": {"<va-hex>": <depth>, ...},          # reachable functions only
    "order": ["<va-hex>", ...] }                 # BFS discovery order
"""
import argparse, bisect, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import capstone
from card import load_funcs, pe

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)

ap = argparse.ArgumentParser()
ap.add_argument("--root", help="root VA in hex (default: OEP from work/SporeApp.analysis.json)")
ap.add_argument("--out", default=W("work/bfs_rank.json"))
a = ap.parse_args()

p = pe()
base = p.OPTIONAL_HEADER.ImageBase
text = next(s for s in p.sections if s.Name.rstrip(b"\0") == b".text")
text_lo = base + text.VirtualAddress
text_hi = text_lo + text.Misc_VirtualSize
data = p.get_data(text.VirtualAddress, text.Misc_VirtualSize)

if a.root:
    root = int(a.root, 16)
else:
    aj = json.load(open(W("work/SporeApp.analysis.json")))
    root = aj["oep_va"]

starts, _ = load_funcs()
starts = [s for s in starts if text_lo <= s < text_hi]

def containing(va):
    """Index into `starts` of the function containing va, or None if outside the known range."""
    if not (text_lo <= va < text_hi):
        return None
    i = bisect.bisect_right(starts, va) - 1
    return i if i >= 0 else None

def fn_bytes(i):
    va = starts[i]
    nxt = starts[i + 1] if i + 1 < len(starts) else text_hi
    n = min(nxt - va, text_hi - va)
    b = data[va - text_lo: va - text_lo + n]
    # trim trailing int3 padding
    while b and b[-1] == 0xCC:
        b = b[:-1]
    return va, b

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = False

start_index = {va: i for i, va in enumerate(starts)}
_imm = re.compile(r"0x([0-9a-fA-F]{4,8})")

# Data sections whose contents we dereference: code that references a vtable/function-pointer
# table in .rdata/.data gets edges to the function addresses stored there (virtual dispatch).
DATA = [(base + s.VirtualAddress, base + s.VirtualAddress + s.Misc_VirtualSize)
        for s in p.sections if s.Name.rstrip(b"\0") in (b".rdata", b".data")]

def in_data(t):
    return any(lo <= t < hi for lo, hi in DATA)

def data_funcs(t, window=64):
    """Function starts stored as dwords in the window at data address t."""
    b = p.get_data(t - base, window)
    out = []
    for k in range(0, len(b) - 3, 4):
        j = start_index.get(int.from_bytes(b[k:k + 4], "little"))
        if j is not None:
            out.append(j)
    return out

adj = [set() for _ in starts]
edges = 0
for i in range(len(starts)):
    va, code = fn_bytes(i)
    if not code:
        continue
    for ins in md.disasm(code, va):
        # Any immediate that resolves onto a function start is an edge.  This includes
        # direct call/jmp targets and address-taken references (callback registrations,
        # function-pointer tables).  Immediates that point at data are dereferenced once
        # so that vtable slots count too - this is what makes breadth-first traversal
        # usable on a C++ binary where most dispatch is virtual.
        for m in _imm.finditer(ins.op_str):
            t = int(m.group(1), 16)
            j = start_index.get(t, containing(t))
            if j is not None:
                if j != i:
                    adj[i].add(j)
                    edges += 1
            elif in_data(t):
                for j in data_funcs(t):
                    if j != i:
                        adj[i].add(j)
                        edges += 1

if containing(root) is None:
    print("root 0x%08x is outside .text / function range" % root)
    sys.exit(1)
root_fn = containing(root)

# BFS
rank = {root_fn: 0}
order = [root_fn]
q = [root_fn]
head = 0
while head < len(q):
    i = q[head]; head += 1
    d = rank[i]
    for j in sorted(adj[i]):
        if j not in rank:
            rank[j] = d + 1
            order.append(j)
            q.append(j)

out = {
    "root": "0x%08x" % root,
    "root_fn": "0x%08x" % starts[root_fn],
    "total": len(starts),
    "reachable": len(rank),
    "edges": edges,
    "rank": {"%08x" % starts[v]: d for v, d in rank.items()},
    "order": ["%08x" % starts[v] for v in order],
}
json.dump(out, open(a.out, "w"))
print("functions %d, reachable from 0x%08x: %d (%.1f%%), direct edges %d"
      % (len(starts), root, len(rank), 100.0 * len(rank) / len(starts), edges))
print("depth histogram (top 12):")
from collections import Counter
for d, c in sorted(Counter(rank.values()).items())[:12]:
    print("  depth %-4d %d" % (d, c))
print("wrote", a.out)
