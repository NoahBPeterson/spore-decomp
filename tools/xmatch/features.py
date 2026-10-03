#!/usr/bin/env python3
"""Per-function features for cross-build matching (dev 2008-02 build <-> retail 2024 build).

usage: features.py dev|retail <out.json>
Features per function: strings referenced, imports called, distinctive constants, direct call targets,
size. Computed from a linear disassembly of each function's bytes (function bounds from the PDB for
the dev build, from our Ghidra index for retail).
"""
import bisect, csv, glob, json, os, re, struct, sys
import pefile, capstone

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)


def load(which):
    if which == "dev":
        pe = pefile.PE(W("work/devbuild/SporeBin/SporeApp.exe"))
        syms = json.load(open(W("work/devbuild/symbols.json")))
        fn = {}
        for f in syms["functions"]:
            fn.setdefault(f["va"], (f["size"], f["name"]))
        starts = sorted(fn)
        return pe, [(a, fn[a][0], fn[a][1]) for a in starts]
    pe = pefile.PE(W("work/SporeApp.analysis.bin"))
    starts = set()
    for f in glob.glob(W("work/decomp_all/index_*.csv")):
        for r in csv.reader(open(f)):
            starts.add(int(r[0], 16))
    starts = sorted(starts)
    out = []
    for i, a in enumerate(starts):
        n = (starts[i + 1] if i + 1 < len(starts) else a + 64) - a
        out.append((a, min(n, 0x20000), ""))
    return pe, out


def main(which, outp):
    pe, funcs = load(which)
    base = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    secs = [(base + s.VirtualAddress, base + s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData),
             s.Name.rstrip(b"\0").decode(errors="replace"), s.Characteristics) for s in pe.sections]
    code_lo, code_hi = next((lo, hi) for lo, hi, n, c in secs if n == ".text")
    data_ranges = [(lo, hi) for lo, hi, n, c in secs if n in (".rdata", ".data")]
    imports = {}
    for e in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for i in e.imports:
            if i.name:
                imports[i.address] = i.name.decode()

    def in_data(v):
        return any(lo <= v < hi for lo, hi in data_ranges)

    def string_at(v):
        o = v - base
        if not (0 <= o < len(img)):
            return None
        b = img[o:o + 200]
        s = b.split(b"\0")[0]
        if len(s) >= 4 and all(32 <= c < 127 or c in (9, 10, 13) for c in s):
            return s.decode()
        w = b.split(b"\0\0")[0]
        if len(w) >= 8:
            try:
                ws = (w + (b"\0" if len(w) % 2 else b"")).decode("utf-16le")
                if len(ws) >= 4 and all(32 <= ord(c) < 127 for c in ws):
                    return "L:" + ws
            except Exception:
                pass
        return None

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    out = {}
    for a, size, name in funcs:
        if not (code_lo <= a < code_hi) or size <= 0:
            continue
        code = img[a - base:a - base + size]
        strs, imps, consts, calls = set(), set(), set(), []
        for ins in md.disasm(code, a):
            ops = ins.op_str
            if ins.mnemonic == "call":
                m = re.fullmatch(r"0x([0-9a-f]+)", ops)
                if m:
                    calls.append(int(m.group(1), 16))
                    continue
                m = re.search(r"\[0x([0-9a-f]+)\]", ops)
                if m and int(m.group(1), 16) in imports:
                    imps.add(imports[int(m.group(1), 16)])
                continue
            if ins.mnemonic.startswith("j"):
                m = re.search(r"\[0x([0-9a-f]+)\]", ops)
                if m and int(m.group(1), 16) in imports:
                    imps.add(imports[int(m.group(1), 16)])
                continue
            for m in re.finditer(r"0x([0-9a-f]+)", ops):
                v = int(m.group(1), 16)
                if in_data(v):
                    s = string_at(v)
                    if s:
                        strs.add(s)
                elif v >= 0x10000 and not (base <= v < base + 0x2000000) and v not in (0xFFFFFFFF, 0x7FFFFFFF, 0x80000000):
                    consts.add(v)
        out["%08x" % a] = {"size": size, "name": name, "strs": sorted(strs), "imps": sorted(imps),
                           "consts": sorted(consts), "calls": ["%08x" % c for c in calls]}
    json.dump(out, open(outp, "w"))
    print("%s: %d functions, with strings %d, with consts %d" % (
        which, len(out), sum(1 for v in out.values() if v["strs"]), sum(1 for v in out.values() if v["consts"])))


if __name__ == "__main__":
    main(*sys.argv[1:3])
