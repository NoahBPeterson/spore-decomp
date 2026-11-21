#!/usr/bin/env python3
"""ga_map: map every function of Spore's SporeApp.exe onto Galactic Adventures' SporebinEP1/SporeApp.exe.

The current PC release ships both executables (both built 2024-09-30). This project rebuilds SporeBin's. Galactic
Adventures' shares almost all of its functions byte for byte, at other addresses. Its addresses are the ones
Spore-ModAPI uses: ModAPI's "March 2017" column also serves the 2024 Galactic Adventures build ("Addresses didn't
shift in the oct2024 version", Spore-ModAPI #78). So this map is what carries our addresses to ModAPI, and later
starts the Galactic Adventures decompilation.

  .venv/bin/python tools/ga_map.py [GA exe] [out.json]
      GA exe   default work/gog/gog_ep1.exe. GOG's is used as it is. Steam's is SteamStub-protected: pass the
               decrypted image tools/steamstub_analysis_image.py makes from it.
      out      default work/ga_map.json (game addresses only, no code; stays in work/ until we decide otherwise)

Base functions come from the retail fingerprints (tools/ci/fingerprints.jsonl), their bytes from
work/SporeApp.analysis.bin (tools/contrib/make_image.py). A function is compared with its relocated dwords and its
outward call/jmp/jcc rel32 displacements zeroed ("normalized"), since those differ between the two executables
even when the code is the same.

How a base function is placed, in order ("how" in the output):
  unique  its normalized bytes occur once in each executable, at a detected GA function start
  dup     several identical functions on both sides: the candidate at the address the neighbouring unique pairs'
          shift predicts, else the only candidate whose outward calls land on the mapped addresses of the callees
  scan    found byte-identical (normalized) near the predicted address, where no GA function start was detected
  similar no identical copy: the function in the same gap between mapped neighbours whose instruction sequence
          is most alike (difflib ratio >= 0.5, given as "ratio"); changed in Galactic Adventures
Then every outward call of an identical pair is checked: the GA call must land on the GA address of the base
callee. Identical pairs with a call that does not are dropped from the map and counted.
GA function starts are the entry point, every call target and every relocated pointer from outside .text into
.text (vtables, function tables).

2026-11-15 (GOG gog_ep1.exe, 23 s): 90,124 of 90,482 base functions identical (unique 42,454, dup 39,736, scan 7,934;
15.63 of 15.81 MB), 187 dropped by the call check, 177 similar, 181 unplaced (17 KB), 2,724 GA starts unpaired
(123 KB, the code only Galactic Adventures has). Checked against ModAPI: 2,500 of its 2,658 addresses land on mapped
functions, 150 are global variables, 2 are GA-only functions. Where names disagree, the ones read were ModAPI's own
synonyms (cGameModeManager is the debug database's SP::cApp), identical small functions the linker folded, or a wrong
guess in symbols/pdb_names.json (0x0117ca60 is SSL_CTX_new there, as ModAPI and our source say, not AddStat).
"""
import bisect, collections, difflib, hashlib, json, os, struct, sys

import capstone
import pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
BASE_IMG = W("work", "SporeApp.analysis.bin")
GA_DEFAULT = W("work", "gog", "gog_ep1.exe")
OUT_DEFAULT = W("work", "ga_map.json")
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
BRANCH = ("call", "jmp", "ja", "jae", "jb", "jbe", "je", "jne", "jg", "jge", "jl", "jle", "jo", "jno", "js", "jns",
          "jp", "jnp")


class Image:
    def __init__(self, path):
        pe = pefile.PE(path)
        self.img = pe.get_memory_mapped_image()
        self.base = pe.OPTIONAL_HEADER.ImageBase
        t = [s for s in pe.sections if s.Name.startswith(b".text")][0]
        self.lo = self.base + t.VirtualAddress
        self.hi = self.lo + t.Misc_VirtualSize
        self.entry = self.base + pe.OPTIONAL_HEADER.AddressOfEntryPoint
        self.rel = set()
        for b in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
            for e in b.entries:
                if e.type == 3:
                    self.rel.add(e.rva + self.base)
        self.sha256 = hashlib.sha256(open(path, "rb").read()).hexdigest()

    def bytes(self, va, n):
        return bytes(self.img[va - self.base: va - self.base + n])

    def norm(self, va, size):
        """(normalized bytes, mnemonics, [(offset of rel32, target)] of outward branches)"""
        raw = self.bytes(va, size)
        b = bytearray(raw)
        for o in range(size):
            if va + o in self.rel:
                b[o:o + 4] = b"\0\0\0\0"
        mn, out = [], []
        for a, sz, m, ops in MD.disasm_lite(raw, va):
            mn.append(m)
            if m in BRANCH and sz >= 5 and ops.startswith("0x"):
                t = int(ops, 16)
                if not (va <= t < va + size):
                    o = a - va + sz - 4
                    b[o:o + 4] = b"\0\0\0\0"
                    out.append((o, t))
        return bytes(b[:size]), mn, out


def ga_starts(g):
    s = {g.entry}
    for r in g.rel:
        if not (g.lo <= r < g.hi):
            v = struct.unpack_from("<I", g.img, r - g.base)[0]
            if g.lo <= v < g.hi:
                s.add(v)
    code = g.bytes(g.lo, g.hi - g.lo)
    off = 0
    while off < len(code):
        n = 0
        for a, sz, m, ops in MD.disasm_lite(code[off:off + 65536], g.lo + off):
            n += sz
            if m == "call" and ops.startswith("0x"):
                t = int(ops, 16)
                if g.lo <= t < g.hi:
                    s.add(t)
        off += n if n else 1
    return sorted(s)


def main(ga_path=GA_DEFAULT, outp=OUT_DEFAULT):
    b, g = Image(BASE_IMG), Image(ga_path)
    fps = sorted((int(d["va"], 16), d["size"]) for d in map(json.loads, open(W("tools", "ci", "fingerprints.jsonl"), "rt")))
    base = {va: (sz,) + b.norm(va, sz) for va, sz in fps}
    S = ga_starts(g)
    ga = {}
    for k, va in enumerate(S):
        end = S[k + 1] if k + 1 < len(S) else g.hi
        raw = g.bytes(va, end - va)
        sz = len(raw.rstrip(b"\xcc")) or len(raw)
        ga[va] = (sz,) + g.norm(va, sz)
    print("base functions %d, GA function starts %d" % (len(base), len(ga)), flush=True)

    bh, gh = collections.defaultdict(list), collections.defaultdict(list)
    for va, f in base.items():
        bh[f[1]].append(va)
    for va, f in ga.items():
        gh[f[1]].append(va)

    pairs = {}                                         # base va -> [ga va, how, ratio]
    for h, bl in bh.items():
        if len(bl) == 1 and len(gh.get(h, ())) == 1:
            pairs[bl[0]] = [gh[h][0], "unique", None]
    keys = sorted(pairs)

    def shifts(va):
        i = bisect.bisect_left(keys, va)
        return [pairs[keys[j]][0] - keys[j] for j in (i - 1, i) if 0 <= j < len(keys)]

    def calls_ok(bva, gva):
        """None if no outward call can be checked, else whether every checkable one agrees"""
        seen = False
        for (o, t), (o2, t2) in zip(base[bva][3], ga[gva][3] if gva in ga else g.norm(gva, base[bva][0])[2]):
            if o != o2:
                return False
            if t in pairs:
                seen = True
                if pairs[t][0] != t2:
                    return False
        return True if seen else None

    # duplicates: shift first, then calls; repeat while it places more (each placement adds call evidence)
    for _ in range(4):
        before = len(pairs)
        taken = {p[0] for p in pairs.values()}
        for h, bl in bh.items():
            gl = [x for x in gh.get(h, ()) if x not in taken]
            if not gl or (len(bl) == 1 and len(gl) == 1 and bl[0] in pairs):
                continue
            for bva in bl:
                if bva in pairs:
                    continue
                pick = [x for x in gl if x - bva in shifts(bva)]
                if len(pick) != 1:
                    ok = [x for x in gl if calls_ok(bva, x)]
                    pick = ok if len(ok) == 1 else []
                if pick:
                    pairs[bva] = [pick[0], "dup", None]
                    gl.remove(pick[0])
                    taken.add(pick[0])
        keys = sorted(pairs)
        if len(pairs) == before:
            break

    # scan: identical code where no GA start was found, at or near the predicted address
    taken = {p[0] for p in pairs.values()}
    for bva in sorted(set(base) - set(pairs)):
        sz, nb, _mn, _out = base[bva]
        cand = set()
        for d in shifts(bva):
            p = bva + d
            if p not in taken and g.norm(p, sz)[0] == nb:
                cand.add(p)
        if not cand and sz >= 16:
            for d in set(shifts(bva)):
                lo = bva + d - 0x2000
                region = g.bytes(lo, 0x4000 + sz)
                key = nb[:8] if 0 not in nb[:8] else None
                if key is None:
                    continue
                p = region.find(key)
                while p != -1:
                    if lo + p not in taken and g.norm(lo + p, sz)[0] == nb:
                        cand.add(lo + p)
                    p = region.find(key, p + 1)
        if len(cand) == 1:
            pairs[bva] = [cand.pop(), "scan", None]
            taken.add(pairs[bva][0])
    keys = sorted(pairs)

    # call-graph check of identical pairs
    bad = [bva for bva, p in pairs.items() if calls_ok(bva, p[0]) is False]
    for bva in bad:
        del pairs[bva]
    keys = sorted(pairs)
    checked = sum(1 for bva, p in pairs.items() if calls_ok(bva, p[0]))

    # similar: changed functions, paired in order inside each gap between mapped neighbours
    taken = {p[0] for p in pairs.values()}
    gsorted = sorted(ga)
    bvs = [v for v, _ in fps]
    for i0, i1 in zip([None] + keys, keys + [None]):
        bl = [v for v in fps_between(bvs, i0, i1) if v not in pairs]
        if not bl:
            continue
        glo = pairs[i0][0] if i0 is not None else g.lo
        ghi = pairs[i1][0] if i1 is not None else g.hi
        gl = [v for v in gsorted[bisect.bisect_right(gsorted, glo):bisect.bisect_left(gsorted, ghi)] if v not in taken]
        for bva in bl:
            a = base[bva][2]
            best, bj = 0.0, None
            for gva in gl[:40]:
                c = ga[gva][2]
                if not a or not c or max(len(a), len(c)) > 3 * min(len(a), len(c)):
                    continue
                r = difflib.SequenceMatcher(None, a, c, autojunk=False).ratio()
                if r > best:
                    best, bj = r, gva
            if bj is not None and best >= 0.5:
                pairs[bva] = [bj, "similar", round(best, 3)]
                gl.remove(bj)
                taken.add(bj)

    ga_only = sorted(v for v in ga if v not in taken)
    how = collections.Counter(p[1] for p in pairs.values())
    nbytes = lambda vs: sum(base[v][0] for v in vs)
    summary = {
        "base_functions": len(base), "base_bytes": nbytes(base),
        "identical": sum(how[k] for k in ("unique", "dup", "scan")),
        "identical_bytes": nbytes(v for v, p in pairs.items() if p[1] != "similar"),
        "by_how": dict(how), "dropped_by_call_check": len(bad), "identical_with_checked_calls": checked,
        "unplaced_base": len(base) - len(pairs), "unplaced_base_bytes": nbytes(set(base) - set(pairs)),
        "ga_only_starts": len(ga_only), "ga_only_bytes": sum(ga[v][0] for v in ga_only),
    }
    json.dump({"base_sha256": b.sha256, "ga_sha256": g.sha256, "summary": summary,
               "pairs": {"%08x" % k: ["%08x" % p[0], p[1]] + ([p[2]] if p[2] is not None else []) for k, p in sorted(pairs.items())},
               "ga_only": ["%08x" % v for v in ga_only]}, open(outp, "w"), indent=0)
    print(json.dumps(summary, indent=1))
    if summary["identical"] < len(base) // 2:
        print("WARNING: under half the functions are identical; is the GA code section still SteamStub-encrypted?")
    print("wrote", outp)


def fps_between(vs, lo, hi):
    i = 0 if lo is None else bisect.bisect_right(vs, lo)
    j = len(vs) if hi is None else bisect.bisect_left(vs, hi)
    return vs[i:j]


if __name__ == "__main__":
    main(*sys.argv[1:3])
