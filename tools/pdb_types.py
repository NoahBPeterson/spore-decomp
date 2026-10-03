#!/usr/bin/env python3
"""Parse a PDB's TPI stream into explicit-offset type layouts (JSON). Linear time.

usage: pdb_types.py <pdb> <out.json>
Output: {"structs": {name: {kind, size, members:[[name, offset, type, bitpos, bitlen]], bases:[[type, offset]],
                            vfptr: bool}},
         "enums": {name: {size, values: [[name, value]]}}}
Member/base "type" is a type descriptor string:
  "prim:<name>", "ptr:<desc>", "arr:<count>:<elemsize>:<desc>", "struct:<name>", "enum:<name>", "func", "?"
Forward references are resolved to the full definition by (unique) name. Only defined, non-forward
types are emitted; templates keep their full C++ names.
"""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from msf import MSF

PRIM = {0x03: ("void", 0), 0x08: ("HRESULT", 4), 0x10: ("char", 1), 0x20: ("uchar", 1), 0x68: ("char", 1),
        0x69: ("uchar", 1), 0x70: ("char", 1), 0x71: ("wchar_t", 2), 0x7a: ("char16_t", 2), 0x7b: ("char32_t", 4),
        0x11: ("short", 2), 0x21: ("ushort", 2), 0x72: ("short", 2), 0x73: ("ushort", 2), 0x12: ("long", 4),
        0x22: ("ulong", 4), 0x74: ("int", 4), 0x75: ("uint", 4), 0x13: ("longlong", 8), 0x23: ("ulonglong", 8),
        0x76: ("longlong", 8), 0x77: ("ulonglong", 8), 0x40: ("float", 4), 0x41: ("double", 8), 0x42: ("double", 8),
        0x30: ("bool", 1), 0x31: ("short", 2), 0x32: ("int", 4), 0x33: ("longlong", 8)}


def numeric(b, o):
    v = struct.unpack_from("<H", b, o)[0]
    if v < 0x8000:
        return v, o + 2
    fmt = {0x8000: "<b", 0x8001: "<h", 0x8002: "<H", 0x8003: "<i", 0x8004: "<I", 0x8009: "<q", 0x800a: "<Q"}.get(v)
    if fmt is None:
        return 0, o + 2
    return struct.unpack_from(fmt, b, o + 2)[0], o + 2 + struct.calcsize(fmt)


def cstr(b, o):
    e = b.index(b"\0", o)
    return b[o:e].decode("latin-1"), e + 1


def main(pdb, out):
    t = MSF(pdb).stream(2)
    ver, hsz, tbeg, tend, nbytes = struct.unpack_from("<IIIII", t, 0)
    recs = {}
    o, ti = hsz, tbeg
    while o < hsz + nbytes:
        ln, k = struct.unpack_from("<HH", t, o)
        recs[ti] = (k, t[o + 4:o + 2 + ln])
        o += 2 + ln
        ti += 1

    def udt_header(k, r):
        if k in (0x1504, 0x1505):
            cnt, prop, field, derived, vshape = struct.unpack_from("<HHIII", r, 0)
            size, p = numeric(r, 16)
        elif k == 0x1506:
            cnt, prop, field = struct.unpack_from("<HHI", r, 0)
            size, p = numeric(r, 8)
        else:
            return None
        name, p = cstr(r, p)
        return prop, field, size, name

    # name -> defining TI for forward-ref resolution
    defs = {}
    for ti, (k, r) in recs.items():
        if k in (0x1504, 0x1505, 0x1506):
            prop, field, size, name = udt_header(k, r)
            if not (prop & 0x80):
                defs.setdefault(name, ti)
        elif k == 0x1507:
            cnt, prop, utype, field = struct.unpack_from("<HHII", r, 0)
            if not (prop & 0x80):
                defs.setdefault(cstr(r, 12)[0], ti)

    def desc(ti, depth=0):
        if depth > 8:
            return "?"
        if ti < 0x1000:
            base, mode = ti & 0xff, (ti >> 8) & 0xf
            nm = PRIM.get(base, ("undefined%d" % 4, 4))[0]
            return "ptr:prim:" + nm if mode else "prim:" + nm
        rec = recs.get(ti)
        if rec is None:
            return "?"
        k, r = rec
        if k == 0x1001:  # modifier
            return desc(struct.unpack_from("<I", r, 0)[0], depth + 1)
        if k == 0x1002:  # pointer
            return "ptr:" + desc(struct.unpack_from("<I", r, 0)[0], depth + 1)
        if k == 0x1503:  # array
            elem, idx = struct.unpack_from("<II", r, 0)
            size, _ = numeric(r, 8)
            ed = desc(elem, depth + 1)
            esz = size_of(elem)
            return "arr:%d:%d:%s" % (size // esz if esz else 0, esz, ed)
        if k in (0x1504, 0x1505, 0x1506):
            return "struct:" + udt_header(k, r)[3]
        if k == 0x1507:
            return "enum:" + cstr(r, 12)[0]
        if k in (0x1008, 0x1009):
            return "func"
        return "?"

    def size_of(ti, depth=0):
        if depth > 8:
            return 0
        if ti < 0x1000:
            return 4 if (ti >> 8) & 0xf else PRIM.get(ti & 0xff, ("", 4))[1]
        k, r = recs.get(ti, (0, b""))
        if k == 0x1001:
            return size_of(struct.unpack_from("<I", r, 0)[0], depth + 1)
        if k == 0x1002:
            return 4
        if k == 0x1503:
            return numeric(r, 8)[0]
        if k in (0x1504, 0x1505, 0x1506):
            prop, field, size, name = udt_header(k, r)
            if prop & 0x80 and name in defs:
                return size_of(defs[name], depth + 1)
            return size
        if k == 0x1507:
            return size_of(struct.unpack_from("<I", r, 4)[0], depth + 1)
        return 0

    def fields(fti):
        out = []
        seen = 0
        while fti and fti in recs and seen < 64:
            seen += 1
            k, r = recs[fti]
            if k != 0x1203:
                break
            o, nxt = 0, 0
            while o + 2 <= len(r):
                if r[o] >= 0xF0:
                    o += r[o] & 0x0F
                    continue
                leaf = struct.unpack_from("<H", r, o)[0]
                if leaf == 0x150d:    # LF_MEMBER
                    attr, typ = struct.unpack_from("<HI", r, o + 2)
                    off, p = numeric(r, o + 8)
                    name, p = cstr(r, p)
                    out.append(("member", name, off, typ))
                elif leaf == 0x1400:  # LF_BCLASS
                    attr, typ = struct.unpack_from("<HI", r, o + 2)
                    off, p = numeric(r, o + 8)
                    out.append(("base", "", off, typ))
                elif leaf in (0x1401, 0x1402):  # virtual bases
                    p = o + 12
                    _, p = numeric(r, p)
                    _, p = numeric(r, p)
                elif leaf == 0x1409:  # LF_VFUNCTAB
                    out.append(("vfptr", "", 0, 0))
                    p = o + 8
                elif leaf == 0x150e:  # LF_STMEMBER
                    p = cstr(r, o + 8)[1]
                elif leaf == 0x150f:  # LF_METHOD
                    p = cstr(r, o + 8)[1]
                elif leaf == 0x1511:  # LF_ONEMETHOD
                    attr, typ = struct.unpack_from("<HI", r, o + 2)
                    p = o + 8 + (4 if ((attr >> 2) & 7) in (4, 6) else 0)
                    p = cstr(r, p)[1]
                elif leaf == 0x1510:  # LF_NESTTYPE
                    p = cstr(r, o + 8)[1]
                elif leaf == 0x1502:  # LF_ENUMERATE
                    val, p = numeric(r, o + 4)
                    name, p = cstr(r, p)
                    out.append(("enum", name, val, 0))
                elif leaf == 0x1404:  # LF_INDEX continuation
                    nxt = struct.unpack_from("<I", r, o + 4)[0]
                    p = o + 8
                else:
                    break
                o = p
            fti = nxt
        return out

    structs, enums = {}, {}
    for name, ti in defs.items():
        k, r = recs[ti]
        if k == 0x1507:
            cnt, prop, utype, field = struct.unpack_from("<HHII", r, 0)
            enums[name] = {"size": size_of(utype) or 4,
                           "values": [[n, v] for kind, n, v, _ in fields(field) if kind == "enum"]}
            continue
        prop, field, size, _ = udt_header(k, r)
        members, bases, vfptr = [], [], False
        for kind, n, off, typ in fields(field):
            if kind == "member":
                bp = bl = None
                bt = typ
                if typ >= 0x1000 and recs.get(typ, (0,))[0] == 0x1205:  # LF_BITFIELD
                    br = recs[typ][1]
                    bt = struct.unpack_from("<I", br, 0)[0]
                    bl, bp = br[4], br[5]
                members.append([n, off, desc(bt), bp, bl, size_of(bt)])
            elif kind == "base":
                bases.append([desc(typ), off, size_of(typ)])
            elif kind == "vfptr":
                vfptr = True
        structs[name] = {"kind": {0x1504: "class", 0x1505: "struct", 0x1506: "union"}[k], "size": size,
                         "members": members, "bases": bases, "vfptr": vfptr}
    json.dump({"structs": structs, "enums": enums}, open(out, "w"))
    nm = sum(len(s["members"]) for s in structs.values())
    print("structs/classes/unions %d (%d members), enums %d" % (len(structs), nm, len(enums)))


if __name__ == "__main__":
    main(*sys.argv[1:3])
