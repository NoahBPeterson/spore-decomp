#!/usr/bin/env python3
"""Function card: everything an agent needs to decompile/match one function.

usage: card.py <va-hex> [<va-hex> ...] [--no-decomp]
Prints: bounds, annotated original disassembly (call targets named, imports resolved,
string literals shown), and the Ghidra decompile.
"""
import bisect, csv, glob, os, re, struct, sys
import pefile, capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import imgcache

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
IMAGE = W("work/SporeApp.analysis.bin")
DECOMP = W("work/decomp_all2") if glob.glob(W("work/decomp_all2/index_*.csv")) else W("work/decomp_all")

_pe = None
def pe():
    global _pe
    if _pe is None:
        _pe = pefile.PE(IMAGE, fast_load=True)  # data reads only; imports come from imgcache
    return _pe

def load_funcs():
    starts, names = [], {}
    for f in glob.glob(W("work/decomp_all/index_*.csv")) + glob.glob(os.path.join(DECOMP, "index_*.csv")):
        for row in csv.reader(open(f)):
            a = int(row[0], 16)
            starts.append(a)
            names[a] = row[1]
    for f in glob.glob(W("symbols/*.txt")) + glob.glob(W("symbols/slices/*.txt")):
        for line in open(f):
            p = line.split("#", 1)[0].split()
            if len(p) >= 2:
                try:
                    names[int(p[0], 16)] = p[1]
                except ValueError:
                    continue  # malformed symbol line (non-hex address): skip
    starts = sorted(set(starts))
    return starts, names

def imports():
    return imgcache.imports(IMAGE)

def string_at(va):
    p = pe(); base = p.OPTIONAL_HEADER.ImageBase
    try:
        b = p.get_data(va - base, 96)
    except Exception:
        return None
    s = b.split(b"\0")[0]
    if len(s) >= 3 and all(32 <= c < 127 for c in s):
        return '"%s"' % s.decode()
    w = b.split(b"\0\0")[0]
    if len(w) >= 6 and len(w) % 2 == 1:
        w = w + b"\0"
    try:
        ws = b[:len(w)].decode("utf-16le")
        if len(ws) >= 3 and all(32 <= ord(c) < 127 for c in ws):
            return 'L"%s"' % ws
    except Exception:
        pass
    return None

def bounds(va, starts):
    i = bisect.bisect_right(starts, va)
    end = starts[i] if i < len(starts) else va + 0x1000
    p = pe(); base = p.OPTIONAL_HEADER.ImageBase
    data = p.get_data(va - base, end - va)
    n = len(data)
    while n > 0 and data[n - 1] == 0xCC:
        n -= 1
    return data[:n]

def decomp_text(va):
    for d in (DECOMP, W("work/decomp_all")):
        t = _decomp_text(d, va)
        if t:
            return t
    return None

def _decomp_text(DECOMP, va):
    path = os.path.join(DECOMP, "c", "%04x0000.c" % (va >> 16))
    if not os.path.exists(path):
        return None
    txt = open(path).read()
    m = re.search(r"/\* ==== [^\n]* @ %08x ==== \*/\n" % va, txt)
    if not m:
        return None
    nxt = txt.find("/* ==== ", m.end())
    return txt[m.end(): nxt if nxt != -1 else len(txt)].strip()

def card(va, starts, names, imps, with_decomp=True):
    code = bounds(va, starts)
    out = ["### %08x %s  (%d bytes)" % (va, names.get(va, "FUN_%08x" % va), len(code)), "```"]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = False
    for ins in md.disasm(code, va):
        note = []
        for m in re.finditer(r"0x([0-9a-f]{5,8})", ins.op_str):
            v = int(m.group(1), 16)
            if v in imps:
                note.append(imps[v])
            elif v in names:
                note.append(names[v])
            else:
                s = string_at(v) if 0x1000000 <= v < 0x1700000 else None
                if s:
                    note.append(s[:70])
        out.append("  %08x  %-24s %-6s %s%s" % (ins.address, ins.bytes.hex(), ins.mnemonic, ins.op_str,
                                                ("   ; " + ", ".join(note)) if note else ""))
    out.append("```")
    if with_decomp:
        d = decomp_text(va)
        if d:
            out += ["Ghidra decompile:", "```c", d, "```"]
    return "\n".join(out)

if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    starts, names = load_funcs()
    imps = imports()
    for a in args:
        print(card(int(a, 16), starts, names, imps, "--no-decomp" not in sys.argv))
        print()
