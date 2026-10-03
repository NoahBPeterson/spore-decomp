#!/usr/bin/env python3
"""Resolve ambiguous library placements by relocation-target consistency (constraint propagation).

usage: libresolve.py <image> <out.csv> <obj-dir> [...]
For every function in the objects that masked-matches 1+ places in .text, record for each
REL32/DIR32 relocation inside it the target symbol name and what the original image has there.
A placement is kept only if, for every target symbol that has a resolved address, the original
points at that address. Iterate until no change. Output rows: name,obj,va,len,status
"""
import os, struct, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile
from cmpobj import parse_coff, REL_SIZES

def obj_functions(path):
    d = open(path, "rb").read()
    secs, _ = parse_coff(path)
    _, nsec, _, symptr, nsym, optsz, _ = struct.unpack_from("<HHIIIHH", d, 0)
    strtab = symptr + nsym * 18
    symname = {}
    per = collections.defaultdict(list)
    i = 0
    while i < nsym:
        o = symptr + 18 * i
        raw = d[o:o + 8]
        if raw[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            nm = d[strtab + off:d.index(b"\0", strtab + off)].decode()
        else:
            nm = raw.split(b"\0")[0].decode()
        value, secno, typ, cls, naux = struct.unpack_from("<IhHBB", d, o + 8)
        symname[i] = (nm, cls, secno)
        if secno > 0 and (typ >> 4) == 2 and cls in (2, 3):
            per[secno - 1].append((value, nm))
        i += 1 + naux
    out = []
    for si, lst in per.items():
        lst.sort()
        sec = secs[si]
        for k, (off, nm) in enumerate(lst):
            end = lst[k + 1][0] if k + 1 < len(lst) else len(sec["data"])
            code = sec["data"][off:end]
            mask, rel = set(), []
            for va, symidx, t in sec["relocs"]:
                if off <= va < end:
                    for b in range(REL_SIZES.get(t, 4)):
                        mask.add(va + b - off)
                    tname, tcls, tsec = symname.get(symidx, ("?", 0, 0))
                    # static symbols are file-local: qualify with the object name
                    key = tname if tcls == 2 else "%s:%s" % (os.path.basename(path), tname)
                    if t in (0x14, 0x06) and not tname.startswith(("$", ".", "??_C@")):
                        rel.append((va - off, t, key))
            gkey = nm if any(c == 2 for _, c, _ in [symname[j] for j in symname if symname[j][0] == nm][:1]) else "%s:%s" % (os.path.basename(path), nm)
            out.append((gkey, nm, code, mask, rel))
    return out

def main():
    image, outp = sys.argv[1], sys.argv[2]
    objs = []
    for a in sys.argv[3:]:
        for root, _, files in os.walk(a):
            objs += [os.path.join(root, f) for f in files if f.endswith(".obj")]
    pe = pefile.PE(image, fast_load=True)
    t = pe.sections[0]; text = t.get_data()
    base = pe.OPTIONAL_HEADER.ImageBase + t.VirtualAddress
    funcs = []
    for o in sorted(objs):
        for gkey, nm, code, mask, rel in obj_functions(o):
            if len(code) < 8:
                continue
            best, cur, st = (0, 0), 0, 0
            for i in range(len(code) + 1):
                if i < len(code) and i not in mask:
                    if cur == 0: st = i
                    cur += 1
                    if cur > best[1]: best = (st, cur)
                else:
                    cur = 0
            a_off, a_len = best[0], min(best[1], 48)
            if a_len < 5:
                continue
            anchor = code[a_off:a_off + a_len]
            cands = []
            p = text.find(anchor)
            while p != -1:
                s = p - a_off
                if s >= 0 and all(text[s + i] == code[i] for i in range(len(code)) if i not in mask):
                    cands.append(s)
                p = text.find(anchor, p + 1)
            if cands:
                funcs.append([gkey, nm, os.path.basename(o), code, rel, cands])
    def target(s, off, t):
        v = struct.unpack_from("<I", text, s + off)[0]
        return (base + s + off + 4 + v) & 0xFFFFFFFF if t == 0x14 else v
    resolved = {}
    changed = True
    rounds = 0
    while changed:
        changed = False
        rounds += 1
        for f in funcs:
            gkey, nm, objn, code, rel, cands = f
            keep = []
            for s in cands:
                ok = True
                for off, t, key in rel:
                    if key in resolved and target(s, off, t) != resolved[key]:
                        ok = False; break
                if ok:
                    keep.append(s)
            if len(keep) != len(cands):
                f[5] = cands = keep; changed = True
            if len(cands) == 1 and gkey not in resolved:
                resolved[gkey] = base + cands[0]; changed = True
            # propagate: a unique placement's relocation targets resolve their symbols
            if len(cands) == 1:
                for off, t, key in rel:
                    if key not in resolved:
                        resolved[key] = target(cands[0], off, t); changed = True
    rows = []
    for gkey, nm, objn, code, rel, cands in funcs:
        st = "unique" if len(cands) == 1 else ("multi" if cands else "none")
        for s in cands[:1] if len(cands) == 1 else cands:
            rows.append((nm, objn, base + s, len(code), st))
    with open(outp, "w") as fh:
        fh.write("name,obj,va,len,status\n")
        for r in rows:
            fh.write("%s,%s,%08x,%d,%s\n" % r)
    c = collections.Counter(r[4] for r in rows)
    uniq = sum(1 for f in funcs if len(f[5]) == 1)
    print("rounds %d, functions with candidates %d, unique %d, still multi %d" % (
        rounds, len(funcs), uniq, sum(1 for f in funcs if len(f[5]) > 1)))

if __name__ == "__main__":
    main()
