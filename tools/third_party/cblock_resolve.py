#!/usr/bin/env python3
"""Classify the 748 `lib_cblock::` functions (symbols/lib_names.txt) against the freshly built library objects.

usage: cblock_resolve.py [--out third_party/cblock_resolution.csv]
Writes va,lib,function,status,evidence. Never edits symbols/lib_names.txt.
status: exact-unique    byte-identical (relocations masked) to exactly one library function
        exact-ambiguous byte-identical to several library functions (identical bodies / aliases)
        exact-by-data   tiny `mov eax,<static>; ret` getter named from the nid/version of the struct it returns
        import-thunk    `jmp [data pointer]` stub (not library source)
        near            NOT byte-identical; nearest library function by instruction-sequence similarity
        unresolved      nothing similar
"""
import argparse, csv, collections, difflib, os, re, struct, subprocess, sys, tempfile
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
import pefile, capstone
from libresolve import obj_functions

IMG = os.path.join(ROOT, "work", "SporeApp.analysis.bin")
OBJ = os.path.join(ROOT, "work", "third_party", "obj")
LIBS = ["openssl", "libjpeg", "libpng", "zlib", "crt_msvcrt", "crt_msvcprt"]
LIBDIR = {"crt_msvcrt": os.path.join(ROOT, "work", "oss", "obj", "crt_msvcrt"),  # static CRT objects, not rebuilt here
          "crt_msvcprt": os.path.join(ROOT, "work", "oss", "obj", "crt_msvcprt")}
def libdir(l):
    return LIBDIR.get(l, os.path.join(OBJ, l))
def libname(l):
    return "crt" if l.startswith("crt") else l
BASE = 0x400000

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "third_party", "cblock_resolution.csv"))
    ap.add_argument("--no-near", action="store_true")
    a = ap.parse_args()
    cb = [int(l.split()[0], 16) for l in open(os.path.join(ROOT, "symbols", "lib_names.txt")) if "lib_cblock" in l]
    size = {int(r["address"], 16): int(r["size"]) for r in csv.DictReader(open(os.path.join(ROOT, "work", "index", "functions.csv")))}
    pe = pefile.PE(IMG, fast_load=True)
    def rd(va, n):
        return pe.get_data(va - BASE, n)
    # relocation mask of the ORIGINAL image (absolute addresses), to mask on both sides
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_BASERELOC"]])
    origrel = set()
    for blk in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
        for e in blk.entries:
            if e.type == 3:
                for k in range(4):
                    origrel.add(e.rva + BASE + k)
    # all library functions (name, lib, obj, code, mask)
    funcs = []
    for lib in LIBS:
        d = libdir(lib)
        for f in sorted(os.listdir(d)):
            if f.endswith(".obj"):
                for gkey, nm, code, mask, rel in obj_functions(os.path.join(d, f)):
                    funcs.append((nm.lstrip("_"), libname(lib), f, code, mask))
    by_len = collections.defaultdict(list)
    for fn in funcs:
        by_len[len(fn[3])].append(fn)
    # unique placements from libresolve (relocation-target disambiguation)
    uniq = {}
    with tempfile.TemporaryDirectory() as t:
        out = os.path.join(t, "r.csv")
        subprocess.run([sys.executable, os.path.join(ROOT, "tools", "matching", "libresolve.py"), IMG, out]
                       + [libdir(l) for l in LIBS], check=True, stdout=subprocess.DEVNULL)
        for r in csv.DictReader(open(out)):
            if r["status"] == "unique":
                uniq[int(r["va"], 16)] = r
    # obj -> lib
    objlib = {}
    for lib in LIBS:
        for f in os.listdir(libdir(lib)):
            objlib[f] = libname(lib)
    # NID names for getter identification
    nids = {}
    conf = os.path.join(ROOT, "work", "third_party", "src", "openssl-0.9.8g", "crypto", "objects", "obj_mac.h")
    if os.path.exists(conf):
        for m in re.finditer(r"#define NID_(\w+)\s+(\d+)", open(conf).read()):
            nids.setdefault(int(m.group(2)), m.group(1))
    names = {f[0] for f in funcs}
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    def mn(code):
        return [i.mnemonic for i in md.disasm(code, 0)]
    near_pool = None
    rows = []
    for va in cb:
        sz = size.get(va, 0)
        code = rd(va, sz) if sz else b""
        if va in uniq:
            r = uniq[va]
            rows.append((va, objlib.get(r["obj"], "?"), r["name"].lstrip("_"), "exact-unique", "byte-identical to %s:%s" % (r["obj"], r["name"])))
            continue
        # exact match against every library function of the same size (relocs masked on both sides)
        cands = []
        if sz:
            for nm, lib, f, c2, mask in by_len.get(sz, []):
                if all(code[i] == c2[i] for i in range(sz) if i not in mask and (va + i) not in origrel):
                    cands.append((nm, lib, f))
        if cands and sz >= 16 or (cands and len(cands) <= 8 and sz >= 3):
            uniq_names = sorted({c[0] for c in cands})
            libs = sorted({c[1] for c in cands})
            st = "exact-unique" if len(uniq_names) == 1 else "exact-ambiguous"
            rows.append((va, "|".join(libs), "|".join(uniq_names[:8]) + ("|..." if len(uniq_names) > 8 else ""), st,
                         "byte-identical to %d library function(s), first %s:%s" % (len(cands), cands[0][2], cands[0][0])))
            continue
        if code[:1] == b"\xb8" and sz == 6 and code[5:6] == b"\xc3":
            tgt = struct.unpack_from("<I", code, 1)[0]
            try:
                first = struct.unpack("<I", rd(tgt, 4))[0]
            except Exception:
                first = None
            nm = nids.get(first)
            if nm and ("EVP_" + nm) in names:
                rows.append((va, "openssl", "EVP_" + nm, "exact-by-data", "returns %08x whose first field is NID %d (%s); EVP_%s exists in 0.9.8g" % (tgt, first, nm, nm)))
                continue
            rows.append((va, "openssl?", "", "unresolved", "getter returning static %08x (first dword %s); several candidates, not identifiable" % (tgt, hex(first) if first is not None else "?")))
            continue
        if code[:2] == b"\xff\x25":
            rows.append((va, "", "", "import-thunk", "jmp [%08x]: indirect jump through a data pointer" % struct.unpack_from("<I", code, 2)[0]))
            continue
        if a.no_near or sz < 16:
            rows.append((va, "", "", "unresolved", "size %d bytes; %d same-size exact candidates" % (sz, len(cands))))
            continue
        if near_pool is None:
            near_pool = [(nm, lib, f, mn(c2)) for nm, lib, f, c2, _ in funcs if len(c2) >= 16]
        m = mn(code)
        best = (0, None)
        for nm, lib, f, cm in near_pool:
            if not (0.6 * sz <= len(cm) * 4 <= 1.6 * sz * 4):
                pass
            sm = difflib.SequenceMatcher(None, m, cm, autojunk=False)
            if sm.real_quick_ratio() < best[0] or sm.quick_ratio() < max(best[0], 0.6):
                continue
            r = sm.ratio()
            if r > best[0]:
                best = (r, (nm, lib, f))
        if best[1]:
            rows.append((va, best[1][1], best[1][0], "near", "NOT byte-identical: mnemonic similarity %.2f to %s:%s (config/flags still differ)" % (best[0], best[1][2], best[1][0])))
        else:
            rows.append((va, "", "", "unresolved", "no similar library function (size %d)" % sz))
    # post-pass: tiny wrappers whose identity follows from the function they call / the data they point at
    known = {r[0]: r[2] for r in rows if r[3] in ("exact-unique", "exact-by-data") and r[2]}
    if os.path.exists(os.path.join(ROOT, "third_party", "baseline_matches.csv")):
        for r in csv.DictReader(open(os.path.join(ROOT, "third_party", "baseline_matches.csv"))):
            known.setdefault(int(r["va"], 16), r["name"].lstrip("_"))
    def cstr(va):
        try:
            b = rd(va, 64)
            return b.split(b"\0")[0].decode("ascii")
        except Exception:
            return None
    out = []
    for r in rows:
        va, lib, fnm, st, ev = r
        sz = size.get(va, 0)
        code = rd(va, sz) if sz else b""
        if st == "unresolved" and sz == 5 and code[:1] == b"\xe9":
            tgt = (va + 5 + struct.unpack_from("<i", code, 1)[0]) & 0xFFFFFFFF
            tn = known.get(tgt)
            r = (va, lib, ("jmp->" + tn) if tn else "", "thunk", "jmp %08x%s" % (tgt, " = " + tn if tn else " (target not identified)"))
        elif st == "unresolved" and sz == 14 and code[:1] == b"\x68" and code[5:6] == b"\xe8" and code[10:] == b"\x83\xc4\x04\xc3":
            it = struct.unpack_from("<I", code, 1)[0]
            tgt = (va + 10 + struct.unpack_from("<i", code, 6)[0]) & 0xFFFFFFFF
            tn = known.get(tgt, "")
            try:
                sname = cstr(struct.unpack("<I", rd(it + 24, 4))[0])  # ASN1_ITEM.sname
            except Exception:
                sname = None
            suffix = {"ASN1_item_new": "_new", "ASN1_item_free": "_free"}.get(tn)
            if sname and suffix and (sname + suffix) in names:
                r = (va, "openssl", sname + suffix, "exact-by-data", "push &%s_it; call %s: %s%s exists in 0.9.8g" % (sname, tn, sname, suffix))
            else:
                r = (va, lib, "", "unresolved", "ASN1_item wrapper (%s, item %s); wrapper name not determined" % (tn or "?", sname))
        out.append(r)
    rows = out
    with open(a.out, "w", newline="") as fh:
        w = csv.writer(fh)
        w.writerow(["va", "lib", "function", "status", "evidence"])
        for r in rows:
            w.writerow(["%08x" % r[0]] + list(r[1:]))
    c = collections.Counter(r[3] for r in rows)
    print(len(rows), dict(c))

if __name__ == "__main__":
    main()
