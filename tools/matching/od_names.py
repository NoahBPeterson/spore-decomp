#!/usr/bin/env python3
"""Pick local-variable names that reproduce a required /Od stack-slot order.

At /Od, cl 15.00 orders a scope's named locals by a hash of their NAMES (declaration order is only
a tie-break), so matching an /Od frame means choosing names. This tool ranks a pool of candidate
names once (one flat function of int locals, each storing a distinct constant; the slot offset of
each store gives its rank), caches it, and hands out names in slot order.

usage:
  od_names.py rank                 # (re)build work/od_name_rank.json from the built-in pool
  od_names.py pick N [--prefix p]  # N names whose slots go from highest address (ebp-4 side) down
  od_names.py order name1 name2 .. # print the given names sorted into slot order (highest first)
"""
import json, os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmpobj import parse_coff
import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CACHE = os.path.join(ROOT, "work/od_name_rank.json")
BASE = ["p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "a", "b", "c", "d", "e", "f", "g", "h", "i",
        "j", "k", "n", "m", "it", "src", "dst", "pos", "cur", "end", "first", "last", "len", "size", "count",
        "node", "next", "prev", "tmp", "val", "key", "res", "ret", "ok", "buf", "ptr", "obj", "item", "elem",
        "data", "base", "begin", "lo", "hi", "idx", "num", "cap", "pNew", "pOld", "pNode", "pEnd", "pBegin",
        "nSize", "nCount", "nIndex", "result", "value", "other", "self", "owner", "list", "iter", "where",
        "from", "to", "left", "right", "mid", "hash", "bucket", "alloc", "mem", "block", "chunk", "offset"]
POOL = BASE + ["%s%d" % (b, i) for b in ("v", "t", "n", "p") for i in range(1, 41)]

def rank():
    src = "void RankNames() {\n" + "".join("  volatile int %s = %d;\n" % (n, 1000 + i) for i, n in enumerate(POOL)) + "}\n"
    path = os.path.join(ROOT, "work/match/od_rank.cpp"); obj = path[:-4] + ".obj"
    open(path, "w").write(src)
    w = lambda p: "Z:" + p.replace("/", "\\")
    r = subprocess.run([os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", "/Od", "/Ob1", "/MD", "/Gy", "/TP",
                        "/Fo" + w(obj), w(path)], capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stdout)
    secs, syms = parse_coff(obj)
    si, off = syms["?RankNames@@YAXXZ"]
    slot = {}
    for ins in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(secs[si]["data"][off:], 0):
        m = re.match(r"dword ptr \[ebp - (0x[0-9a-f]+|\d+)\], (0x[0-9a-f]+|\d+)", ins.op_str)
        if ins.mnemonic == "mov" and m:
            slot[POOL[int(m.group(2), 0) - 1000]] = -int(m.group(1), 0)
        if ins.mnemonic == "ret":
            break
    order = sorted(slot, key=lambda n: -slot[n])  # highest address (closest to ebp) first
    json.dump({"order": order, "slot": slot}, open(CACHE, "w"), indent=0)
    print("ranked %d names; highest slot first: %s ..." % (len(order), " ".join(order[:12])))

def load():
    if not os.path.exists(CACHE):
        rank()
    return json.load(open(CACHE))

def fit(k, want):
    import random
    rnd = random.Random(k * 7919)
    combos = []
    while len(combos) < 300:
        c = rnd.sample(POOL, k)
        if c not in combos:
            combos.append(c)
    src = "".join("void Fit%d() {\n%s}\n" % (i, "".join("  volatile int %s = %d;\n" % (n, j + 1) for j, n in enumerate(c)))
                  for i, c in enumerate(combos))
    path = os.path.join(ROOT, "work/match/od_fit_%d.cpp" % k); obj = path[:-4] + ".obj"
    open(path, "w").write(src)
    w = lambda p: "Z:" + p.replace("/", "\\")
    r = subprocess.run([os.path.join(ROOT, "tools/matching/cl.sh"), "/nologo", "/c", "/Od", "/Ob1", "/MD", "/Gy", "/TP",
                        "/Fo" + w(obj), w(path)], capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stdout)
    secs, syms = parse_coff(obj)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    out = []
    for i, c in enumerate(combos):
        si, off = syms["?Fit%d@@YAXXZ" % i]
        slot = {}
        for ins in md.disasm(secs[si]["data"][off:], 0):
            m = re.match(r"dword ptr \[ebp - (0x[0-9a-f]+|\d+)\], (0x[0-9a-f]+|\d+)", ins.op_str)
            if ins.mnemonic == "mov" and m:
                slot[c[int(m.group(2), 0) - 1]] = -int(m.group(1), 0)
            if ins.mnemonic == "ret":
                break
        out.append(" ".join(sorted(c, key=lambda n: -slot[n])))
    print("# %d-local scope: each line lists names from highest slot (ebp-4 side) to lowest" % k)
    print("\n".join(out[:want]))

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "pick"
    if cmd == "fit":
        fit(int(sys.argv[2]), int(sys.argv[sys.argv.index("--n") + 1]) if "--n" in sys.argv else 40)
    elif cmd == "rank":
        rank()
    elif cmd == "pick":
        n = int(sys.argv[2]); d = load()["order"]
        step = max(1, len(d) // n)
        print(" ".join(d[i * step] for i in range(n)))
    elif cmd == "order":
        d = load()["slot"]
        unknown = [x for x in sys.argv[2:] if x not in d]
        if unknown:
            sys.exit("not in ranked pool (add to POOL and re-rank): " + " ".join(unknown))
        print(" ".join(sorted(sys.argv[2:], key=lambda x: -d[x])))
