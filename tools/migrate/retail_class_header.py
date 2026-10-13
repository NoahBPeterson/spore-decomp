#!/usr/bin/env python3
"""Header for a RETAIL-ONLY class from a byte-exact slice view (docs/migration.md, Option A for
classes the dev PDB does not have, e.g. the second DatabasePackedFile family near 0x6bb000).

The dev PDB is the layout authority for every class it has; for a class it lacks, the best
byte-exact slice view is the only layout evidence, so this tool promotes that view to a header:
members at the view's offsets with explicit pads under #pragma pack(1), nested slice-local structs
emitted inside the class (no collision with the PDB-backed headers), the retail vtable's slots in
order (named when symbols/pdb_names.json names the slot's function in the same family, else
vfn_<k>_<va>), and an evidence block. Slice member NAMES are guesses (docs/migration.md §evidence);
offsets of members a byte-exact function touches are not. The header is then verified under VC9:
sizeof and every named member's offsetof must equal the view's.

  python3 tools/migrate/retail_class_header.py --slice s006bc1b0 --struct DatabasePackedFile \
      --vtable 0140a154 --name EA::ResourceMan::DatabasePackedFile_v2 \
      --out src/game/include/EA/ResourceMan/DatabasePackedFile_v2.h [--no-verify]
"""
import argparse, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
sys.path.insert(0, W("tools", "migrate"))

PRIM = {"uint32": "uint32_t", "int32": "int32_t", "uint16": "uint16_t", "int16": "int16_t",
        "uint8": "uint8_t", "int8": "int8_t", "uint64": "uint64_t", "int64": "int64_t",
        "ulong": "unsigned long", "uint": "unsigned int"}
BUILTIN = {"void", "bool", "char", "short", "int", "long", "float", "double", "unsigned", "signed",
           "__int64", "wchar_t"}


def split_type(t):
    """'EA::IO::FileStream' -> ('EA::IO::FileStream', '', ''); 'uint32[2]' -> ('uint32', '', '[2]');
    'ICoreAllocator *' -> ('ICoreAllocator', '*', '')."""
    t = t.strip()
    arr = ""
    m = re.search(r"(\[[^\]]*\])+$", t)
    if m:
        arr = m.group(0)
        t = t[:m.start()].strip()
    ptr = ""
    while t.endswith("*") or t.endswith("&"):
        ptr = t[-1] + ptr
        t = t[:-1].strip()
    return t, ptr, arr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--slice", required=True); ap.add_argument("--struct", required=True)
    ap.add_argument("--vtable", help="retail vtable VA (8 hex) whose slots become the virtuals")
    ap.add_argument("--name", required=True, help="qualified C++ name for the new class")
    ap.add_argument("--out", required=True); ap.add_argument("--no-verify", action="store_true")
    a = ap.parse_args()

    views = json.load(open(W("work/migrate/sliceviews.json")))["defs"]
    defs = {d["name"]: d for d in views if d.get("slice") == a.slice}
    if a.struct not in defs:
        sys.exit("no struct %s in slice %s" % (a.struct, a.slice))
    main_def = defs[a.struct]
    nsparts = a.name.split("::")
    cls = nsparts[-1]
    namespaces = nsparts[:-1]

    pdb_names = json.load(open(W("symbols/pdb_names.json")))
    ret_vt = json.load(open(W("work/xmatch/tables.json")))["ret_vt"]
    family = re.sub(r"_v\d+$", "", cls)          # DatabasePackedFile_v2 -> DatabasePackedFile

    # --- nested slice-local structs referenced by value or pointer, emitted inside the class
    nested, order = {}, []

    def need(short):
        if short in nested or short not in defs or short == a.struct:
            return
        nested[short] = defs[short]
        for m in defs[short]["members"]:
            base, ptr, arr = split_type(m.get("type") or "")
            need(base.split("::")[-1])
        order.append(short)

    for m in main_def["members"]:
        base, ptr, arr = split_type(m.get("type") or "")
        need(base.split("::")[-1])

    unknown = set()

    def ctype(t, size):
        """C++ spelling of a slice type inside the class; (text, is_opaque)."""
        base, ptr, arr = split_type(t or "")
        short = base.split("::")[-1]
        if base in PRIM:
            base = PRIM[base]
        elif base.split(" ")[0] in BUILTIN or base.endswith("_t"):
            pass
        elif short in nested:
            base = short
        elif ptr:
            unknown.add(base)
            return "void" + ptr, False          # pointer to a type the slice never defines
        else:
            unknown.add(base)
            return None, True                  # by-value unknown: opaque bytes
        return base + (" " + ptr if ptr else "") + ("" if not arr else arr), False

    def members_lines(d, indent):
        out = []
        for m in sorted(d["members"], key=lambda m: m["offset"]):
            name, off, size, t = m["name"], m["offset"], m["size"], m.get("type") or ""
            if name.startswith("pad") or name == "data" and t.startswith("char["):
                out.append("%sunsigned char %s[0x%x];" % (indent, name if name != "data" else "mData", size))
                continue
            text, opaque = ctype(t, size)
            if opaque:
                out.append("%sunsigned char %s[0x%x];   // +0x%x %s (slice type; no definition in the slice)" % (indent, name, size, off, t))
            else:
                base, ptr, arr = split_type(text)
                decl = base + (" " + ptr if ptr else "") + " " + name + arr
                out.append("%s%s;   // +0x%x%s" % (indent, decl, off, "" if t == text else " (slice: %s)" % t))
        return out

    # --- vtable
    vlines = []
    if a.vtable:
        slots = ret_vt.get(a.vtable.lower())
        if slots is None:
            sys.exit("no retail vtable %s in work/xmatch/tables.json" % a.vtable)
        for k, va in enumerate(slots):
            e = pdb_names.get(va.lower()) or {}
            nm = e.get("name", "")
            if family in nm:
                meth = nm.split("::")[-1]
                if meth.startswith("~") or "destructor" in meth:
                    meth = "vfn_%d_%s" % (k, va)
                vlines.append("  virtual void %s();   // slot %d, retail 0x%s%s" % (
                    meth, k, va, "" if meth == nm.split("::")[-1] else " (" + nm + ")"))
            else:
                note = (" (pdb_names says %s: another class, not trusted)" % nm) if nm else ""
                vlines.append("  virtual void vfn_%d_%s();   // slot %d%s" % (k, va, k, note))

    guard = re.sub(r"[^A-Za-z0-9]", "_", a.name).upper() + "_H"
    L = ["// RETAIL-ONLY class: no dev PDB record. Generated by tools/migrate/retail_class_header.py from the",
         "// byte-exact slice view %s::%s (%d byte-exact users) and retail vtable %s (%d slots)." % (
             a.slice, a.struct, len(main_def.get("exact_users", [])), a.vtable or "-", len(vlines)),
         "// Member names are the slice's guesses; offsets are verified under VC9 by the generator.",
         "// Virtual signatures are placeholders (void()) until a function that calls the slot is migrated.",
         "#ifndef %s" % guard, "#define %s" % guard, '#include "game/types.h"', ""]
    for ns in namespaces:
        L.append("namespace %s {" % ns)
    L += ["", "#pragma pack(push, 1)", "class %s {" % cls, " public:"]
    for short in order:
        d = nested[short]
        L.append("  struct %s {   // slice-local, 0x%x bytes" % (short, d["size"]))
        L += members_lines(d, "    ")
        L.append("  };")
    L.append("")
    L += vlines
    if vlines:
        L.append("")
    body = members_lines(main_def, "  ")
    # the view's vptr slot is a data member in the slice; drop it when we emit virtuals
    if vlines and body and body[0].startswith("  void * vtbl") or (vlines and body and re.match(r"  void ?\* vtbl;", body[0])):
        body = body[1:]
    L += body
    L += ["};", "#pragma pack(pop)", ""]
    for ns in reversed(namespaces):
        L.append("}  // namespace %s" % ns)
    L += ["", "#endif", ""]
    os.makedirs(os.path.dirname(W(a.out)), exist_ok=True)
    open(W(a.out), "w").write("\n".join(L))
    print("wrote %s: %d members, %d nested structs, %d virtual slots, unknown types: %s" % (
        a.out, len(main_def["members"]), len(order), len(vlines), ", ".join(sorted(unknown)) or "none"))
    if a.no_verify:
        return 0

    # --- verify under VC9: sizeof and offsetof of every named member
    probe = ['#include "%s"' % os.path.relpath(W(a.out), W("src/game/include")), "#include <stddef.h>",
             "typedef %s T;" % a.name, "char (*size_probe)[sizeof(T)] = 1;"]
    want = {}
    for m in main_def["members"]:
        if m["name"].startswith("pad") or m["name"] == "vtbl":
            continue
        probe.append("char (*off_%s)[1 + offsetof(T, %s)] = 1;" % (m["name"], m["name"]))
        want[m["name"]] = m["offset"]
    scratch = W("work", "migrate", "headers")
    os.makedirs(scratch, exist_ok=True)
    pp = os.path.join(scratch, "probe_%s.cpp" % cls)
    open(pp, "w").write("\n".join(probe) + "\n")
    win = lambda p: "Z:" + p.replace("/", "\\")
    r = subprocess.run([W("tools/matching/cl.sh"), "/nologo", "/c", "/TP", "/W3", "/I" + win(W("src/game/include")),
                        "/Fo" + win(os.path.join(scratch, "probe_%s.obj" % cls)), win(pp)], capture_output=True, text=True)
    out = r.stdout + r.stderr
    got = {}
    for m in re.finditer(r"'char \(\*\)\[(\d+)\]'", out):
        pass
    for line in out.splitlines():
        mm = re.search(r"probe_\w+\.cpp\((\d+)\).*'char \(\*\)\[(\d+)\]'", line)
        if mm:
            got[int(mm.group(1))] = int(mm.group(2))
    bad = []
    if got.get(4) != main_def["size"]:
        bad.append("sizeof: VC9 %s, view 0x%x" % (hex(got[4]) if 4 in got else "?", main_def["size"]))
    for i, (name, off) in enumerate(want.items()):
        v = got.get(5 + i)
        if v is None or v - 1 != off:
            bad.append("%s: VC9 %s, view 0x%x" % (name, hex(v - 1) if v else "?", off))
    other = [l for l in out.splitlines() if "error" in l and "char (*)[" not in l]
    if other:
        bad += other[:5]
    if bad:
        print("VERIFY FAILED:\n  " + "\n  ".join(bad))
        return 1
    print("verified under VC9: sizeof 0x%x and %d member offsets match the view" % (main_def["size"], len(want)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
