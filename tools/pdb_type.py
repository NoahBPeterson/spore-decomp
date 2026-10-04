#!/usr/bin/env python3
"""Print dev-PDB (2008 dev build) struct/class/enum layouts as C++ declarations with offsets.

usage: pdb_type.py <name or substring> [--exact] [--max 5]
Layouts are from the 2008 dev build; retail (2024) may have changed a few fields, so check offsets
against the disassembly. Members are listed with their byte offsets as comments.
"""
import argparse, json, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ap = argparse.ArgumentParser()
ap.add_argument("name"); ap.add_argument("--exact", action="store_true"); ap.add_argument("--max", type=int, default=5)
a = ap.parse_args()
T = json.load(open(os.path.join(ROOT, "work/devbuild/types.json")))


def ctype(d):
    if d.startswith("prim:"): return {"uchar": "unsigned char", "ushort": "unsigned short", "uint": "unsigned int",
                                       "ulong": "unsigned long", "longlong": "__int64", "ulonglong": "unsigned __int64"}.get(d[5:], d[5:])
    if d.startswith("ptr:"): return ctype(d[4:]) + "*"
    if d.startswith("struct:"): return d[7:]
    if d.startswith("enum:"): return d[5:]
    if d.startswith("arr:"):
        _, n, _, inner = d.split(":", 3); return "%s[%s]" % (ctype(inner), n)
    return "void" if d == "func" else "/*?*/int"


def show(name, s):
    bases = ", ".join("public " + b[0].split(":", 1)[1] for b in s["bases"])
    print("%s %s%s {  // size 0x%x" % (s["kind"], name, (" : " + bases) if bases else "", s["size"]))
    if s["vfptr"] and not s["bases"]:
        print("    void** vftable;  // +0x0")
    for n, off, d, bp, bl, sz in sorted(s["members"], key=lambda m: (m[1], m[3] or 0)):
        t = ctype(d)
        if t.endswith("]"):
            base, arr = t.split("[", 1); decl = "%s %s[%s" % (base, n, arr)
        else:
            decl = "%s %s" % (t, n)
        print("    %s%s;  // +0x%x" % (decl, (" : %d" % bl) if bl is not None else "", off))
    print("};")


hits = [k for k in T["structs"] if ((k == a.name or k.split("::")[-1] == a.name) if a.exact else a.name.lower() in k.lower())]
hits.sort(key=lambda k: (k != a.name, len(k)))
for k in hits[:a.max]:
    show(k, T["structs"][k]); print()
ehits = [k for k in T["enums"] if (k == a.name if a.exact else a.name.lower() in k.lower())][:a.max]
for k in ehits:
    print("enum %s {" % k)
    for n, v in T["enums"][k]["values"]:
        print("    %s = %d," % (n, v))
    print("};\n")
if len(hits) > a.max:
    print("// %d more matches; refine the name or use --exact" % (len(hits) - a.max))
if not hits and not ehits:
    print("no type matching %r" % a.name)
