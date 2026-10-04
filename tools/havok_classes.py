#!/usr/bin/env python3
"""Extract Havok 3.1.0 class reflection (hkClass / hkClassMember / hkClassEnum) from the retail exe.

usage: havok_classes.py <out.json> <out.h>
Havok registers its serializable classes with static initializers like
    hkClass g("hkCollidable", &hkCdBodyClass, 0x24, 0,0, 0,0, members, 3, 0);
i.e. pushes of (defaults, numMembers, members, numEnums, enums, numIfaces, ifaces, size, parent, name),
`mov ecx, <hkClass object>`, `call hkClass::hkClass` (0x010802b0). The member tables in .rdata give real member
names, types and byte offsets for exactly the Havok version Spore ships (3.1.0). Record formats (3.1.0):
  hkClassMember (20 bytes): name*, class*, enum*, u8 type, u8 subtype, i16 cArraySize, u16 flags, u16 offset
  hkClassEnum: name*, items*, numItems;  item: int value, name*
The header is generated as an explicit-offset layout reference (members placed with padding).
"""
import json, os, struct, sys
import capstone, pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CTOR = 0x010802B0
RANGES = [(0x0107D740, 0x0112C500), (0x013B3530, 0x013CC000)]
TYPES = ["void", "bool", "char", "int8", "uint8", "int16", "uint16", "int32", "uint32", "int64", "uint64",
         "real", "vector4", "quaternion", "matrix3", "rotation", "qstransform", "matrix4", "transform", "zero",
         "pointer", "functionpointer", "array", "inplacearray", "enum", "struct", "simplearray",
         "homogeneousarray", "variant", "cstring", "ulong", "flags"]
CT = {"bool": "hkBool", "char": "char", "int8": "hkInt8", "uint8": "hkUint8", "int16": "hkInt16", "uint16": "hkUint16",
      "int32": "hkInt32", "uint32": "hkUint32", "int64": "hkInt64", "uint64": "hkUint64", "real": "hkReal",
      "vector4": "hkVector4", "quaternion": "hkQuaternion", "matrix3": "hkMatrix3", "rotation": "hkRotation",
      "qstransform": "hkQsTransform", "matrix4": "hkMatrix4", "transform": "hkTransform", "cstring": "const char*",
      "ulong": "hkUlong", "functionpointer": "void*", "variant": "hkVariant"}
SIZES = {"bool": 1, "char": 1, "int8": 1, "uint8": 1, "int16": 2, "uint16": 2, "int32": 4, "uint32": 4, "int64": 8,
         "uint64": 8, "real": 4, "vector4": 16, "quaternion": 16, "matrix3": 48, "rotation": 48, "qstransform": 48,
         "matrix4": 64, "transform": 64, "pointer": 4, "functionpointer": 4, "array": 12, "cstring": 4, "ulong": 4,
         "simplearray": 8, "variant": 8, "zero": 0}


def main(outj, outh):
    pe = pefile.PE(os.path.join(ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def cstr(v):
        o = v - base
        if not v or not (0 <= o < len(img)):
            return None
        e = img.find(b"\0", o, o + 256)
        return img[o:e].decode("latin-1") if e > o else None

    classes = {}  # hkClass object VA -> record
    for lo, hi in RANGES:
        pushes = []
        for ins in md.disasm(img[lo - base:hi - base], lo):
            if ins.mnemonic == "push":
                try:
                    pushes.append(int(ins.op_str, 16))
                except ValueError:
                    pushes.append(None)
            elif ins.mnemonic == "mov" and ins.op_str.startswith("ecx, 0x"):
                obj = int(ins.op_str.split(",")[1], 16)
            elif ins.mnemonic == "call" and ins.op_str == hex(CTOR):
                a = pushes[-10:][::-1]  # name, parent, size, ifaces, nifaces, enums, nenums, members, nmembers, defaults
                if len(a) == 10 and all(x is not None for x in a[:3]) and cstr(a[0]):
                    classes[obj] = {"name": cstr(a[0]), "parent_obj": a[1], "size": a[2], "ifaces": a[3] or 0,
                                    "enums_at": a[5] or 0, "nenums": a[6] or 0, "members_at": a[7] or 0,
                                    "nmembers": a[8] or 0, "defaults": a[9] or 0, "init": "%08x" % ins.address}
                pushes = []
            elif ins.mnemonic in ("ret", "jmp"):
                pushes = []
    byobj = {k: v["name"] for k, v in classes.items()}

    def enum_at(v):
        if not v:
            return None
        n_, items, cnt = struct.unpack_from("<III", img, v - base)
        out = []
        for i in range(min(cnt, 512)):
            val, nm = struct.unpack_from("<iI", img, items - base + 8 * i)
            out.append([cstr(nm), val])
        return {"name": cstr(n_), "items": out}

    out = {}
    for obj, c in classes.items():
        members = []
        for i in range(c["nmembers"]):
            nm, cls, en, ty, sub, carr, flags, off = struct.unpack_from("<IIIBBhHH", img, c["members_at"] - base + 20 * i)
            m = {"name": cstr(nm), "type": TYPES[ty] if ty < len(TYPES) else ty,
                 "subtype": TYPES[sub] if sub < len(TYPES) else sub, "carray": carr, "flags": flags, "offset": off}
            if cls:
                m["class"] = byobj.get(cls, "%08x" % cls)
            if en:
                m["enum"] = enum_at(en)
            members.append(m)
        enums = []
        for i in range(c["nenums"]):
            enums.append(enum_at(c["enums_at"] + 12 * i))
        out[c["name"]] = {"object": "%08x" % obj, "parent": byobj.get(c["parent_obj"]) if c["parent_obj"] else None,
                          "size": c["size"], "members": members, "enums": enums, "init": c["init"]}
    json.dump(out, open(outj, "w"), indent=1, sort_keys=True)

    # header: explicit-offset reference layout
    L = ["// Generated by tools/havok_classes.py from Spore's own Havok 3.1.0 reflection data (hkClass tables).",
         "// Reference layouts: member names/types/offsets are authoritative; methods are not included.",
         "// Offsets assume the 32-bit layout of the shipped binary.", "#pragma once", ""]
    done = set()

    def ctype(m):
        t = m["type"]
        if t == "pointer":
            return (m.get("class") or CT.get(m["subtype"], "void")) + "*"
        if t == "struct":
            return m.get("class", "/*struct*/char")
        if t == "array":
            return "hkArray<%s>" % ((m.get("class") or CT.get(m["subtype"], "void")) + ("*" if m["subtype"] == "pointer" else ""))
        if t == "enum":
            return "hkEnum<%s, %s>" % ((m.get("enum") or {}).get("name") or "int", CT.get(m["subtype"], "hkInt32"))
        return CT.get(t, "/*%s*/hkUint32" % t)

    def emit(name):
        if name in done or name not in out:
            return
        c = out[name]
        if c["parent"]:
            emit(c["parent"])
        for m in c["members"]:
            if m["type"] == "struct" and m.get("class") in out:
                emit(m["class"])
        done.add(name)
        L.append("struct %s%s {  // size 0x%x" % (name, (" : public " + c["parent"]) if c["parent"] else "", c["size"]))
        for e in c["enums"]:
            if e:
                L.append("    enum %s { %s };" % (e["name"], ", ".join("%s = %d" % (n, v) for n, v in e["items"])))
        for m in sorted(c["members"], key=lambda m: m["offset"]):
            arr = "[%d]" % m["carray"] if m["carray"] else ""
            L.append("    %s m_%s%s;  // +0x%x %s" % (ctype(m), m["name"], arr, m["offset"], m["type"]))
        L.append("};")
        L.append("")

    for n in sorted(out):
        emit(n)
    open(outh, "w").write("\n".join(L))
    nm = sum(len(c["members"]) for c in out.values())
    print("Havok classes %d, members %d, enums %d" % (len(out), nm, sum(len(c["enums"]) for c in out.values())))


if __name__ == "__main__":
    main(*sys.argv[1:3])
