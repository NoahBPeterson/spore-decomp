#!/usr/bin/env python3
"""Find byte-exact occurrences of compiled library functions in the original image.

usage: libmatch.py <image> <out.csv> <obj or dir> [...]
For every function in the COFF objects: mask relocated bytes, anchor on the longest
unmasked run, search .text, verify the full masked compare. Functions shorter than
MIN_LEN are skipped (too ambiguous). Writes: name,obj,va,len,status (unique|multi).
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile
from cmpobj import parse_coff, REL_SIZES

MIN_LEN = 16

def functions(obj):
    secs, _ = parse_coff(obj)
    # re-walk symbols to get all function symbols per section (parse_coff keeps the first per name)
    import struct
    d = open(obj, "rb").read()
    _, nsec, _, symptr, nsym, optsz, _ = struct.unpack_from("<HHIIIHH", d, 0)
    strtab = symptr + nsym * 18
    per = {}
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
        if secno > 0 and (typ >> 4) == 2 and cls in (2, 3):
            per.setdefault(secno - 1, []).append((value, nm))
        i += 1 + naux
    for si, lst in per.items():
        lst.sort()
        sec = secs[si]
        for k, (off, nm) in enumerate(lst):
            end = lst[k + 1][0] if k + 1 < len(lst) else len(sec["data"])
            code = sec["data"][off:end]
            # strip trailing int3/nop padding inside non-COMDAT .text
            while code and code[-1] in (0xCC,) and k + 1 < len(lst):
                code = code[:-1]
            mask = set()
            for va, _s, t in sec["relocs"]:
                for b in range(REL_SIZES.get(t, 4)):
                    if off <= va + b < end:
                        mask.add(va + b - off)
            yield nm, code, mask

def main():
    image, out = sys.argv[1], sys.argv[2]
    objs = []
    for a in sys.argv[3:]:
        if os.path.isdir(a):
            for root, _, files in os.walk(a):
                objs += [os.path.join(root, f) for f in files if f.endswith(".obj")]
        else:
            objs.append(a)
    pe = pefile.PE(image, fast_load=True)
    t = pe.sections[0]
    text = t.get_data()
    base = pe.OPTIONAL_HEADER.ImageBase + t.VirtualAddress
    rows, tried = [], 0
    for obj in sorted(objs):
        for nm, code, mask in functions(obj):
            if len(code) < MIN_LEN:
                continue
            tried += 1
            # longest unmasked run as anchor
            best, cur, start = (0, 0), 0, 0
            for i in range(len(code) + 1):
                if i < len(code) and i not in mask:
                    if cur == 0:
                        start = i
                    cur += 1
                    if cur > best[1]:
                        best = (start, cur)
                else:
                    cur = 0
            a_off, a_len = best
            a_len = min(a_len, 48)
            if a_len < 6:
                continue
            anchor = code[a_off:a_off + a_len]
            hits = []
            p = text.find(anchor)
            while p != -1:
                s = p - a_off
                if s >= 0 and all(text[s + i] == code[i] for i in range(len(code)) if i not in mask):
                    hits.append(base + s)
                p = text.find(anchor, p + 1)
            if hits:
                status = "unique" if len(hits) == 1 else "multi"
                for h in hits:
                    rows.append((nm, os.path.basename(obj), h, len(code), status))
    with open(out, "w") as fh:
        fh.write("name,obj,va,len,status\n")
        for r in rows:
            fh.write("%s,%s,%08x,%d,%s\n" % r)
    names = set(r[0] for r in rows)
    print("tried %d functions, matched %d (%d placements)" % (tried, len(names), len(rows)))

if __name__ == "__main__":
    main()
