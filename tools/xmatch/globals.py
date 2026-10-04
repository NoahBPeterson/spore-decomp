#!/usr/bin/env python3
"""Name retail globals from matched function pairs (dev PDB globals -> retail addresses).

usage: globals.py <matches.json> <out.json> [hows, comma-separated; default: all high-confidence methods]
For each matched pair, both functions are disassembled and their absolute data operands (in .data/.rdata,
non-string) are listed in instruction order with the mnemonic. When the two lists have the same length and
mnemonics, operand k on one side corresponds to operand k on the other. A dev address is resolved to the
containing PDB global (+offset); the retail label goes at retail_addr - offset. A retail address is named
only when every vote agrees (and the name isn't claimed by another address).
Output: {retail_va: {"name", "dev", "votes"}}
"""
import bisect, collections, json, os, re, sys
import capstone, pefile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
HIGH = "anchor,callee-scored,callee-single,gap-align,xcu-align,vtable-slot"


class Img:
    def __init__(self, path, funcs):
        pe = pefile.PE(path, fast_load=True)
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.img = pe.get_memory_mapped_image()
        self.data = [(self.base + s.VirtualAddress, self.base + s.VirtualAddress + s.Misc_VirtualSize)
                     for s in pe.sections if s.Name.rstrip(b"\0") in (b".data", b".rdata")]
        self.funcs = funcs
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def operands(self, va):
        size = self.funcs.get(va, 0)
        code = self.img[va - self.base:va - self.base + min(size, 0x4000)]
        out = []
        for ins in self.md.disasm(code, va):
            if ins.mnemonic == "call" or ins.mnemonic.startswith("j"):
                continue
            for m in re.finditer(r"0x([0-9a-f]+)", ins.op_str):
                v = int(m.group(1), 16)
                if any(lo <= v < hi for lo, hi in self.data):
                    out.append((ins.mnemonic, v))
        return out


def main(matchp, outp, hows=HIGH):
    hows = set(hows.split(","))
    matches = json.load(open(matchp))
    retf = json.load(open(W("work/xmatch/retail.json")))
    devf = json.load(open(W("work/xmatch/dev.json")))
    R = Img(W("work/SporeApp.analysis.bin"), {int(k, 16): v["size"] for k, v in retf.items()})
    D = Img(W("work/devbuild/SporeBin/SporeApp.exe"), {int(k, 16): v["size"] for k, v in devf.items()})
    syms = json.load(open(W("work/devbuild/symbols.json")))
    gl = {}
    for g in syms["globals"]:
        gl.setdefault(g["va"], g["name"])
    for p in syms["publics"]:
        if not p["code"] and not p["name"].startswith(("??_C@", "__real@", "??_7")):
            gl.setdefault(p["va"], p["name"])
    gvas = sorted(gl)

    def resolve(v):
        i = bisect.bisect_right(gvas, v) - 1
        if i < 0 or v - gvas[i] > 0x1000:
            return None
        return gl[gvas[i]], v - gvas[i]

    votes = collections.defaultdict(collections.Counter)
    for r, m in matches.items():
        if m["how"] not in hows:
            continue
        ro, do = R.operands(int(r, 16)), D.operands(int(m["dev"], 16))
        if not ro or len(ro) != len(do) or any(a[0] != b[0] for a, b in zip(ro, do)):
            continue
        for (_, rv), (_, dv) in zip(ro, do):
            g = resolve(dv)
            if g:
                votes[rv - g[1]][g[0]] += 1
    out, claimed = {}, collections.Counter()
    for rv, c in votes.items():
        if len(c) == 1:
            claimed[next(iter(c))] += 1
    for rv, c in votes.items():
        if len(c) == 1:
            name, n = next(iter(c.items()))
            if claimed[name] == 1:
                out["%08x" % rv] = {"name": name, "votes": n}
    json.dump(out, open(outp, "w"), indent=0)
    print("globals named: %d (addresses with votes %d, conflicting %d)" % (
        len(out), len(votes), sum(1 for c in votes.values() if len(c) > 1)))


if __name__ == "__main__":
    main(*sys.argv[1:4])
