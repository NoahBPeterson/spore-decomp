#!/usr/bin/env python3
"""Project status: per-function coverage at each fidelity tier. Writes docs/STATUS.md."""
import csv, glob, os, re, subprocess
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)

funcs = {}
for f in glob.glob(W("work/decomp_all/index_*.csv")):
    for addr, name, size, status, lines in csv.reader(open(f)):
        funcs[int(addr, 16)] = dict(name=name, size=int(size), status=status)
total = len(funcs)
decomp = sum(1 for v in funcs.values() if v["status"] == "ok")

lib = {}
for line in open(W("symbols/lib_names.txt")):
    p = line.split("#", 1)[0].split()
    if len(p) >= 2:
        lib[int(p[0], 16)] = (p[1].split("::")[0].replace("lib_", ""), p[1])
lib_in_funcs = {a: v for a, v in lib.items() if a in funcs}

exact = set()
import re as _re
nonmatching = set(); partial = set()
_PARTIAL = _re.compile(r"approx|stub|partial|omit|skeleton|incomplete|placeholder|loose|thin|structural|sketch", _re.I)
for f in glob.glob(W("match/slices/*/nonmatching.txt")) + glob.glob(W("match/slices/*/partial.txt")):
    for line in open(f):
        p = line.split("#", 1)[0].split()
        if p:
            va = int(p[0], 16)
            (partial if (f.endswith("partial.txt") or _PARTIAL.search(line)) else nonmatching).add(va)
clones = set()
if os.path.exists(W("match/clones.txt")):
    for line in open(W("match/clones.txt")):
        p = line.split("#", 1)[0].split()
        if len(p) >= 3:
            clones.add(int(p[2], 16))
# C++ static-initializer table (__xc_a..__xc_z), the range passed to _initterm at 0x011E0F98.
import struct as _st
_img = open(W("work/SporeApp.analysis.bin"), "rb").read()
def _rva_off(rva):
    e = _st.unpack_from("<I", _img, 0x3C)[0]; n = _st.unpack_from("<H", _img, e + 6)[0]
    o = e + 24 + _st.unpack_from("<H", _img, e + 20)[0]
    for i in range(n):
        vs, va, rs, rp = _st.unpack_from("<IIII", _img, o + 40 * i + 8)
        if va <= rva < va + max(vs, rs):
            return rp + rva - va
XC_A, XC_Z = 0x013CC80C, 0x013EB098
xcu = set()
for a in range(XC_A, XC_Z, 4):
    v = _st.unpack_from("<I", _img, _rva_off(a - 0x400000))[0]
    if v:
        xcu.add(v)
synth = set(); synth_orig = set(); synth_shape = set()
for f in glob.glob(W("match/synth/*.manifest")):
    for line in open(f):
        p = line.split("#", 1)[0].split()
        if len(p) >= 3:
            va = int(p[2], 16)
            synth.add(va)
            (synth_shape if (va in xcu and not p[1].startswith("??__E")) else synth_orig).add(va)
for line in [l for m in [W("match/manifest.txt")] + glob.glob(W("match/slices/*/manifest.txt")) for l in open(m)]:
    p = line.split("#", 1)[0].split()
    if len(p) >= 3:
        exact.add(int(p[2], 16))

named = set()
for line in (l for f in glob.glob(W("symbols/*.txt")) for l in open(f)):
    p = line.split("#", 1)[0].split()
    if p:
        named.add(int(p[0], 16))
named |= set(lib_in_funcs)
if os.path.exists(W("symbols/pdb_names.json")):
    import json as _j
    named |= set(int(k, 16) for k in _j.load(open(W("symbols/pdb_names.json"))))

# ---- kind of each function: "global" (static initializers / atexit destructors / compiler stubs),
# "class" (member functions and template instantiations), "func" (free functions). Cached.
import json as _json
_KC = W("work/kinds.json")
try:
    kinds = {int(k, 16): v for k, v in _json.load(open(_KC)).items()}
    if set(kinds) != set(funcs): raise ValueError
except Exception:
    import capstone as _cs
    _md = _cs.Cs(_cs.CS_ARCH_X86, _cs.CS_MODE_32); _md.detail = True
    _ECX = {_cs.x86.X86_REG_ECX, _cs.x86.X86_REG_CX, _cs.x86.X86_REG_CL, _cs.x86.X86_REG_CH}
    _classes = set()
    try:
        _classes = set(_json.load(open(W("work/devbuild/types.json")))["structs"])
    except Exception:
        pass
    def _reads_ecx_first(va):
        o = _rva_off(va - 0x400000)
        for ins in _md.disasm(_img[o:o + 96], va):
            r, w = ins.regs_access()
            if ins.mnemonic in ("xor", "sub") and len(ins.operands) == 2 and ins.op_str.split(",")[0].strip() == ins.op_str.split(",")[1].strip():
                r = ()  # xor ecx,ecx is a write
            if any(x in _ECX for x in r): return True
            if any(x in _ECX for x in w): return False
            if ins.mnemonic in ("call", "ret", "jmp") or ins.mnemonic.startswith("j"): return False
        return False
    kinds = {}
    for a, v in funcs.items():
        nm = v["name"]
        o = _rva_off(a - 0x400000)
        first = _img[o:o + 1] if o is not None else b""
        if a in xcu or "__F" in nm or "dynamic atexit destructor" in nm or "dynamic initializer" in nm or (first == b"\xe9" and v["size"] <= 8):
            kinds[a] = "global"
        elif "<" in nm or "::".join(nm.split("::")[:-1]) in _classes or (o is not None and _reads_ecx_first(a)):
            kinds[a] = "class"
        else:
            kinds[a] = "func"
    _json.dump({"%08x" % k: v for k, v in kinds.items()}, open(_KC, "w"))

bytes_total = sum(v["size"] for v in funcs.values())
def pct(n, d): return "%.2f%%" % (100.0 * n / d) if d else "-"
by_lib = {}
for tag, _ in lib_in_funcs.values():
    by_lib[tag] = by_lib.get(tag, 0) + 1
lib_bytes = sum(funcs[a]["size"] for a in lib_in_funcs)

game = set(funcs) - set(lib_in_funcs)          # third-party library code excluded (freebies)
G = len(game)
def row(label, items):
    n = len(items & game)
    return "| %s | %d | %s |" % (label, n, pct(n, G))
has_src = (exact | clones | nonmatching | synth)
byte_exact = (exact | clones | synth) & game
equiv = (nonmatching - byte_exact) & game
part = (partial - byte_exact - equiv) & game
nosrc = game - byte_exact - equiv - part
K = lambda k: set(a for a in game if kinds.get(a) == k)
KF, KC, KG = K("func"), K("class"), K("global")
shape = (synth_shape - synth_orig - exact - clones) & game
GB = sum(funcs[a]["size"] for a in game)
def comp_rows():
    rows, rest = [], set(game)
    comps = _json.load(open(W("symbols/components.json")))
    for name, ranges in comps.items():
        if name.startswith("_"): continue
        items = set(a for a in game if any(int(lo, 16) <= a < int(hi, 16) for lo, hi in ranges))
        rest -= items
        rows.append((name, items))
    rows.append(("Spore + EA framework (everything else)", rest))
    out = []
    for name, items in rows:
        b = sum(funcs[a]["size"] for a in items); src = items & (byte_exact | equiv)
        bs = sum(funcs[a]["size"] for a in src)
        out.append("| %s | %d | %d (%s) | %.2f MB | %s |" % (name, len(items), len(src), pct(len(src), len(items)), b / 2**20, pct(bs, b)))
    return out
def r(label, items, note=""):
    b = sum(funcs[a]["size"] for a in items)
    return "| %s | %d | %s | %.2f MB | %s | %s |" % (label, len(items), pct(len(items), G), b / 2**20, pct(b, GB), note)
out = ["# Status", "",
       "Generated by `tools/status.py`. Denominator = game functions only: all %d functions in the" % total,
       "Ghidra project minus %d third-party library functions (OpenSSL, libpng, zlib, libjpeg, CRT)," % len(lib_in_funcs),
       "which are excluded as freebies (built byte-exact from upstream source).", "",
       "Byte-exact = our source, compiled with the original compiler, gives the identical bytes (relocations masked).",
       "Equivalent = complete compilable source with the same behavior, not (yet) byte-identical.", "",
       "| Tier | Functions | Share (by count) | Code size | Share (by size) | Notes |", "|---|---:|---:|---:|---:|---|",
       r("Functions, byte-exact", byte_exact & KF, "free (non-member) functions"),
       r("Classes, templates, byte-exact", byte_exact & KC, "member functions and template instantiations"),
       r("Globals, other code, byte-exact", byte_exact & KG, "static initializers/destructors of globals, compiler stubs; %d of these written as a plain function rather than `T g = ...;` (shape-only)" % len(shape & KG)),
       r("Functions, equivalent but not exact", equiv & KF),
       r("Classes, templates, equivalent", equiv & KC),
       r("Globals, other code, equivalent", equiv & KG),
       r("Other: partial source", part, "incomplete or approximate source, not counted as decompiled"),
       r("Other: no source yet", nosrc, "Ghidra pseudocode only (readable, not compilable)"),
       r("**Total with compilable source**", byte_exact | equiv),
       r("Game functions (denominator)", game),
       "", "| Component | Functions | With compilable source | Code size | With source (by size) |", "|---|---:|---:|---:|---:|"] + comp_rows() + [
       "", "Kind is from the name (template arguments, recovered class) or, for unnamed functions, from the calling",
       "convention (reads ECX = `this` before writing it).",
       "Checked against PDB-named functions, that heuristic labels 79% of member functions as class code and 88% of",
       "free functions as functions, so for unnamed code the split between the first two kinds is approximate.",
       "Kind totals: functions %d, classes/templates %d, globals/other %d." % (len(KF), len(KC), len(KG)),
       "", "Named (recovered real names, incl. high-confidence dev-PDB matches): %d (%s). This is orthogonal to the tiers." % (len(named & game), pct(len(named & game), G)),
       "", "Excluded third-party library functions: %d (%s)" % (len(lib_in_funcs), ", ".join("%s %d" % kv for kv in sorted(by_lib.items()))), ""]
open(W("docs/STATUS.md"), "w").write("\n".join(out))
print("\n".join(out))
