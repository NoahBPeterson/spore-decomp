"""CodeView type records of a /Z7 object (cl 13.10): class layouts for typed input generation.

`.debug$T` holds the TU's type records, `.debug$S` its symbols (one section per COMDAT function). equiv.py's
InputGen builds `this` and pointer arguments as objects of their declared class instead of pointer soup: a
vtable pointer is the original's vtable, nested object pointers lead to (recursively typed) objects, counts are
small and vectors are consistent (first <= last <= end).

VC7.1 specifics found while writing this (the CodeView spec describes the later C13 layout):
  * .debug$T: signature 4, then records `u16 len, u16 leaf, ...` with 32-bit type indices from 0x1000.
  * .debug$S: signature 4, then subsections `u32 type, u32 len`; a DEBUG_S_SYMBOLS (0xf1) subsection with
    length 0 means "the records run to the end of the section" (every COMDAT function's .debug$S ends that way).
  * S_GPROC32 / S_LPROC32 (0x1110 / 0x110f) name the function undecorated ("rgl::mesh::build_skin"); its
    decorated name is the symbol the SECREL relocation on the record's `off` field points at.
  * Class records carry no unique (decorated) name: vtable symbols are mangled from the qualified name here
    (`rgl::mesh` -> `??_7mesh@rgl@@6B@`); templates are not mangled (their vtable is left as soup).
  * A class used only through pointers is a forward reference (property 0x80, size 0): it resolves by name to
    the defined record, when the TU has one.

Layout entries (Field) are flattened to primitive slots, offsets relative to the object start:
  vfptr       (LF_VFUNCTAB, or a hand-declared `void* vptr` member at +0) target = candidate mangled vtable names for this subobject, best first
  ptr_class   target = the pointee's class type index (resolved)
  ptr_char    a char* (the generator points it at a short ASCII string)
  ptr_other   any other data/function pointer (left as soup)
  int         size 1/2/4/8, target = signed
  bool / enum (target = the enumerator values) / float / double
  chars       an inline char array of `size` bytes
  vector      a pointer triple (_Myfirst/_Mylast/_Myend and the project's first/last/end, begin/end/cap, also
              with a common prefix/suffix: obj_first/obj_last/obj_end):
              size 12, target = the element type index
  rglstring   rgl::string / tstring {pos, buf, cap, len}: size 16
  stdstring   std::basic_string<char>'s (_Bx, _Mysize, _Myres) at the _Bx offset: size 24
  rbtree      eastl::rbtree's anchor node {right, left, parent, color} and mnSize (src/game/include/eastl/map.h,
              the base of eastl::map/set/multimap): size 0x14 at the anchor. Found by shape, as the project's
              stand-ins name everything differently: a member whose name contains "anchor" and whose type has
              pointers at +0/+4/+8 and a 1- or 4-byte integer at +0xc (the members' names are not trusted:
              SPSimulatorUniverse's MapNode calls +0 mpLeft). target = the value_type (a pair<const K, V> for a
              map), ("node", T) when the anchor's own type T carries the key and value after +0x10 (a stand-in
              node used as the anchor), or None (a dword key, soup after it)
Padding, bitfields and virtual bases are not listed (they stay soup); a union is typed as its first member
(anonymous ones too: the first-listed of overlapping members).
"""
import struct
from collections import namedtuple

LF_MODIFIER, LF_POINTER, LF_PROCEDURE, LF_MFUNCTION = 0x1001, 0x1002, 0x1008, 0x1009
LF_ARGLIST, LF_FIELDLIST, LF_BITFIELD, LF_METHODLIST = 0x1201, 0x1203, 0x1205, 0x1206
LF_ARRAY, LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM = 0x1503, 0x1504, 0x1505, 0x1506, 0x1507
LF_BCLASS, LF_VBCLASS, LF_IVBCLASS, LF_INDEX, LF_VFUNCTAB = 0x1400, 0x1401, 0x1402, 0x1404, 0x1409
LF_ENUMERATE, LF_MEMBER, LF_STMEMBER, LF_METHOD, LF_NESTTYPE, LF_ONEMETHOD = \
    0x1502, 0x150d, 0x150e, 0x150f, 0x1510, 0x1511
S_LPROC32, S_GPROC32 = 0x110f, 0x1110
REL_SECREL = 0x0B
PROP_FWDREF = 0x80

Field = namedtuple("Field", "off kind size target name")

# basic (non-pointer) primitive types: ti & 0xff -> (kind, size, signed)
_PRIM = {
    0x10: ("int", 1, True), 0x20: ("int", 1, False), 0x70: ("int", 1, True), 0x68: ("int", 1, True),
    0x69: ("int", 1, False), 0x11: ("int", 2, True), 0x21: ("int", 2, False), 0x72: ("int", 2, True),
    0x73: ("int", 2, False), 0x71: ("int", 2, False), 0x12: ("int", 4, True), 0x22: ("int", 4, False),
    0x74: ("int", 4, True), 0x75: ("int", 4, False), 0x13: ("int", 8, True), 0x23: ("int", 8, False),
    0x76: ("int", 8, True), 0x77: ("int", 8, False), 0x30: ("bool", 1, False), 0x31: ("bool", 2, False),
    0x32: ("bool", 4, False), 0x40: ("float", 4, True), 0x41: ("double", 8, True), 0x42: ("soup", 10, True),
}
_CHARS = (0x10, 0x20, 0x70, 0x68, 0x69)
# pointer triples of a vector: (first, last, end) member names
VECTOR_NAMES = {("_Myfirst", "_Mylast", "_Myend"), ("first", "last", "end"), ("begin", "end", "cap"),
                ("begin", "end", "capacity"), ("_First", "_Last", "_End"), ("start", "finish", "end_of_storage")}


VTABLE_MEMBERS = ("vptr", "vtbl", "vtable", "_vfptr", "vfptr", "vft", "vt", "_vtbl", "__vfptr")


def vector_names(a, b, c):
    """The member names of a vector's pointer triple, also with a common prefix / suffix (obj_first, obj_last,
    obj_end; first_items, ...)."""
    for x, y, z in VECTOR_NAMES:
        i = a.find(x)
        while i >= 0:
            pre, suf = a[:i], a[i + len(x):]
            if b == pre + y + suf and c == pre + z + suf:
                return True
            i = a.find(x, i + 1)
    return False


def numeric(b, o):
    """(value, next offset) of a numeric leaf at b[o]."""
    v = struct.unpack_from("<H", b, o)[0]
    if v < 0x8000:
        return v, o + 2
    fmt = {0x8000: "<b", 0x8001: "<h", 0x8002: "<H", 0x8003: "<i", 0x8004: "<I", 0x8009: "<q", 0x800a: "<Q"}[v]
    return struct.unpack_from(fmt, b, o + 2)[0], o + 2 + struct.calcsize(fmt)


def cstr(b, o):
    e = b.index(b"\0", o)
    return b[o:e].decode("latin-1"), e + 1


def mangle_class(qual):
    """`rgl::mesh` -> `mesh@rgl@@` (the class part of a decorated name), or None for templates / unnamed."""
    if not qual or "<" in qual or "__unnamed" in qual or "`" in qual:
        return None
    return "".join(p + "@" for p in reversed(qual.split("::"))) + "@"


def vtable_name(complete, base=None):
    """`??_7D@@6B@` (primary) or `??_7D@@6BB@@@` (the vtable of D's B subobject)."""
    c = mangle_class(complete)
    if c is None:
        return None
    if base is None:
        return "??_7%s6B@" % c
    b = mangle_class(base)
    return "??_7%s6B%s@" % (c, b) if b else None


class TypeTable:
    def __init__(self, data):
        self.recs = {}
        if len(data) < 4 or struct.unpack_from("<I", data, 0)[0] != 4:
            return
        o, ti = 4, 0x1000
        while o + 4 <= len(data):
            ln, lf = struct.unpack_from("<HH", data, o)
            self.recs[ti] = (lf, data[o + 4:o + 2 + ln])
            o += 2 + ln
            ti += 1
        self.defined = {}           # class/struct/union/enum name -> defining type index
        for t, (lf, b) in self.recs.items():
            if lf in (LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM):
                info = self.info(t)
                if info and not info["prop"] & PROP_FWDREF and info["name"] not in self.defined:
                    self.defined[info["name"]] = t
        self._layouts = {}

    # ---- records
    def info(self, ti):
        """Header of a class/struct/union/enum record: {leaf, count, prop, field, size, name, ...}."""
        r = self.recs.get(ti)
        if r is None:
            return None
        lf, b = r
        if lf in (LF_CLASS, LF_STRUCTURE):
            count, prop, field, derived, vshape = struct.unpack_from("<HHIII", b, 0)
            size, o = numeric(b, 16)
            name, _ = cstr(b, o)
            return dict(leaf=lf, count=count, prop=prop, field=field, vshape=vshape, size=size, name=name)
        if lf == LF_UNION:
            count, prop, field = struct.unpack_from("<HHI", b, 0)
            size, o = numeric(b, 8)
            name, _ = cstr(b, o)
            return dict(leaf=lf, count=count, prop=prop, field=field, size=size, name=name)
        if lf == LF_ENUM:
            count, prop, utype, field = struct.unpack_from("<HHII", b, 0)
            name, _ = cstr(b, 12)
            return dict(leaf=lf, count=count, prop=prop, field=field, utype=utype, name=name,
                        size=self.sizeof(utype))
        return None

    def strip(self, ti):
        """Through LF_MODIFIER (const/volatile) and class forward references to the defining record."""
        for _ in range(16):
            r = self.recs.get(ti)
            if r is None:
                return ti
            lf, b = r
            if lf == LF_MODIFIER:
                ti = struct.unpack_from("<I", b, 0)[0]
                continue
            if lf in (LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM):
                info = self.info(ti)
                if info["prop"] & PROP_FWDREF:
                    return self.defined.get(info["name"], ti)
            return ti
        return ti

    def leaf(self, ti):
        r = self.recs.get(ti)
        return r[0] if r else None

    def name(self, ti):
        info = self.info(self.strip(ti))
        return info["name"] if info else None

    def is_class(self, ti):
        return self.leaf(self.strip(ti)) in (LF_CLASS, LF_STRUCTURE)

    def sizeof(self, ti):
        ti = self.strip(ti)
        if ti < 0x1000:
            if (ti >> 8) & 7:
                return 4
            return _PRIM.get(ti & 0xff, ("soup", 0, False))[1]
        lf, b = self.recs[ti]
        if lf == LF_POINTER:
            attr = struct.unpack_from("<I", b, 4)[0]
            return (attr >> 13) & 0x3f or 4
        if lf == LF_ARRAY:
            return numeric(b, 8)[0]
        if lf in (LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM):
            return self.info(ti)["size"]
        if lf == LF_BITFIELD:
            return self.sizeof(struct.unpack_from("<I", b, 0)[0])
        return 0

    def fields(self, flti):
        """Subrecords of a field list (following LF_INDEX continuations): [(leaf, dict)]."""
        out, seen = [], set()
        while flti and flti not in seen:
            seen.add(flti)
            r = self.recs.get(flti)
            if r is None or r[0] != LF_FIELDLIST:
                break
            b, o, flti = r[1], 0, None
            while o + 2 <= len(b):
                if b[o] >= 0xf0:                        # LF_PAD
                    o += b[o] & 0x0f or 1
                    continue
                sl = struct.unpack_from("<H", b, o)[0]
                o += 2
                if sl == LF_MEMBER:
                    attr, typ = struct.unpack_from("<HI", b, o)
                    off, o = numeric(b, o + 6)
                    nm, o = cstr(b, o)
                    out.append((sl, dict(attr=attr, type=typ, off=off, name=nm)))
                elif sl == LF_BCLASS:
                    attr, typ = struct.unpack_from("<HI", b, o)
                    off, o = numeric(b, o + 6)
                    out.append((sl, dict(attr=attr, type=typ, off=off)))
                elif sl in (LF_VBCLASS, LF_IVBCLASS):
                    attr, typ, vbp = struct.unpack_from("<HII", b, o)
                    _vbpoff, o = numeric(b, o + 10)
                    _vboff, o = numeric(b, o)
                    out.append((sl, dict(attr=attr, type=typ, vbptype=vbp)))
                elif sl == LF_VFUNCTAB:
                    typ = struct.unpack_from("<I", b, o + 2)[0]
                    o += 6
                    out.append((sl, dict(type=typ)))
                elif sl == LF_STMEMBER:
                    attr, typ = struct.unpack_from("<HI", b, o)
                    nm, o = cstr(b, o + 6)
                    out.append((sl, dict(attr=attr, type=typ, name=nm)))
                elif sl == LF_METHOD:
                    cnt, ml = struct.unpack_from("<HI", b, o)
                    nm, o = cstr(b, o + 6)
                    out.append((sl, dict(count=cnt, mlist=ml, name=nm)))
                elif sl == LF_NESTTYPE:
                    typ = struct.unpack_from("<I", b, o + 2)[0]
                    nm, o = cstr(b, o + 6)
                    out.append((sl, dict(type=typ, name=nm)))
                elif sl == LF_ONEMETHOD:
                    attr, typ = struct.unpack_from("<HI", b, o)
                    o += 6
                    if ((attr >> 2) & 7) in (4, 6):     # introducing virtual: a vtable offset follows
                        o += 4
                    nm, o = cstr(b, o)
                    out.append((sl, dict(attr=attr, type=typ, name=nm)))
                elif sl == LF_ENUMERATE:
                    attr = struct.unpack_from("<H", b, o)[0]
                    val, o = numeric(b, o + 2)
                    nm, o = cstr(b, o)
                    out.append((sl, dict(value=val, name=nm)))
                elif sl == LF_INDEX:
                    flti = struct.unpack_from("<I", b, o + 2)[0]
                    o += 6
                else:
                    raise ValueError("unknown field-list subleaf %#x in %#x" % (sl, flti))
        return out

    def enum_values(self, ti):
        info = self.info(self.strip(ti))
        return [d["value"] for sl, d in self.fields(info["field"]) if sl == LF_ENUMERATE] if info else []

    def pointee(self, ti):
        """The pointed-to type of an LF_POINTER (any mode: pointer or reference), else None."""
        ti = self.strip(ti)
        if ti < 0x1000:
            return (ti & 0xff) if (ti >> 8) & 7 else None
        r = self.recs.get(ti)
        if r and r[0] == LF_POINTER:
            attr = struct.unpack_from("<I", r[1], 4)[0]
            if (attr >> 5) & 7 in (0, 1):            # pointer / lvalue reference (not pointer to member)
                return struct.unpack_from("<I", r[1], 0)[0]
        return None

    def scalar(self, ti):
        """(kind, size, target) of a non-aggregate type, or None for classes/unions/arrays."""
        ti = self.strip(ti)
        if ti < 0x1000:
            if (ti >> 8) & 7:
                return ("ptr_char", 4, None) if (ti & 0xff) in _CHARS else ("ptr_other", 4, ti & 0xff)
            k, sz, sg = _PRIM.get(ti & 0xff, ("soup", 0, False))
            return (k, sz, sg) if k == "int" else (k, sz, None)
        lf, b = self.recs[ti]
        if lf == LF_POINTER:
            p = self.pointee(ti)
            if p is None:
                return ("ptr_other", self.sizeof(ti), None)
            p = self.strip(p)
            if p < 0x1000 and (p & 0xff) in _CHARS and not (p >> 8) & 7:
                return ("ptr_char", 4, None)
            if self.is_class(p) and self.sizeof(p):
                return ("ptr_class", 4, p)
            return ("ptr_other", 4, p)
        if lf == LF_ENUM:
            return ("enum", self.sizeof(ti), tuple(self.enum_values(ti)))
        if lf == LF_BITFIELD:
            return None
        return None

    # ---- layouts
    def layout(self, ti, limit=4096):
        """Flattened [Field] of a class (see the module doc), sorted by offset; cached."""
        ti = self.strip(ti)
        if ti in self._layouts:
            return self._layouts[ti]
        out = []
        info = self.info(ti)
        if info and info["leaf"] in (LF_CLASS, LF_STRUCTURE) and not info["prop"] & PROP_FWDREF:
            self._flatten(ti, 0, info["name"], None, out, limit, 0)
        dedup, seen = [], set()
        for f in sorted(out, key=lambda f: f.off):
            if f.off not in seen:
                seen.add(f.off)
                dedup.append(f)
        self._layouts[ti] = dedup
        return dedup

    def _flatten(self, ti, base, complete, sub, out, limit, depth):
        """Fields of class ti placed at `base`. `complete` is the class whose vtables the vfptrs hold and `sub`
        the direct base of it this subobject belongs to (None: the primary, offset-0 chain)."""
        if depth > 12 or len(out) >= limit:
            return
        info = self.info(ti)
        if info is None or info["prop"] & PROP_FWDREF:
            return
        fl = self.fields(info["field"])
        members = [d for sl, d in fl if sl == LF_MEMBER]
        nm = info["name"]
        names = [d["name"] for d in members]
        if self._is_rglstring(members):
            out.append(Field(base, "rglstring", 16, None, nm))
            return
        if {"_Bx", "_Mysize", "_Myres"} <= set(names):
            bx = next(d for d in members if d["name"] == "_Bx")
            if self.sizeof(bx["type"]) == 16 and nm.startswith("std::basic_string<char,"):
                out.append(Field(base + bx["off"], "stdstring", 24, None, nm))
                for d in members:
                    if d["off"] < bx["off"]:
                        self._member(d, base, out, limit, depth)
                return
        for sl, d in fl:
            if sl == LF_BCLASS:
                bti = self.strip(d["type"])
                bsub = sub
                if bsub is None and base + d["off"] != 0 and d["off"] != 0:
                    bsub = self.name(bti)
                self._flatten(bti, base + d["off"], complete, bsub, out, limit, depth + 1)
            elif sl == LF_VFUNCTAB:
                # the complete class's vtable for this subobject first; then the subobject's / introducing
                # class's own (a base vtable: calls reach the base's methods, the same on both sides)
                cands = []
                for c in (vtable_name(complete, sub), sub and vtable_name(sub), vtable_name(nm)):
                    if c and c not in cands:
                        cands.append(c)
                out.append(Field(base, "vfptr", 4, tuple(cands), nm))
        tree = self._rbtree(fl, members)
        if tree is not None:
            anchor, val = tree
            out.append(Field(base + anchor, "rbtree", 0x14, val, nm))
            members = [d for d in members if not anchor <= d["off"] < anchor + 0x14]
        vec = self._vector_triples(members)
        tail = {o + k for o in vec for k in (4, 8)}     # _Mylast / _Myend of a triple
        # an anonymous union's members are listed as members of the enclosing class at overlapping offsets
        # (the project spells one field two ways: Troop::inv / items): the first-listed alternative is typed,
        # a member overlapping an earlier one is not
        kept = []
        for d in members:
            if self.leaf(self.strip(d["type"])) == LF_BITFIELD:
                continue
            a, b = d["off"], d["off"] + max(1, self.sizeof(d["type"]))
            if any(a < e and c < b for c, e in kept):
                continue
            kept.append((a, b))
            if d["off"] in vec:
                out.append(Field(base + d["off"], "vector", 12, vec[d["off"]], d["name"]))
            elif d["off"] == 0 and d["name"] in VTABLE_MEMBERS and self.sizeof(d["type"]) == 4 and \
                    self.pointee(d["type"]) is not None:
                # a hand-declared vtable pointer (`void* vptr;` in a class written without virtuals)
                cands = [c for c in (vtable_name(complete, sub), vtable_name(nm)) if c]
                out.append(Field(base, "vfptr", 4, tuple(dict.fromkeys(cands)), nm))
            elif d["off"] not in tail:
                self._member(d, base, out, limit, depth)

    def _member(self, d, base, out, limit, depth):
        off = base + d["off"]
        t = self.strip(d["type"])
        if self.leaf(t) == LF_BITFIELD:
            return
        if self.is_class(t):
            self._flatten(t, off, self.name(t), None, out, limit, depth + 1)
            return
        if self.leaf(t) == LF_UNION:                     # its first member
            info = self.info(t)
            first = [x for sl, x in self.fields(info["field"]) if sl == LF_MEMBER] if info else []
            if first and depth < 12:
                self._member(dict(first[0], off=d["off"] + first[0]["off"]), base, out, limit, depth + 1)
            return
        if self.leaf(t) == LF_ARRAY:
            self._array(t, off, d["name"], out, limit, depth)
            return
        s = self.scalar(t)
        if s and s[0] != "soup":
            out.append(Field(off, s[0], s[1], s[2], d["name"]))

    def _array(self, t, off, name, out, limit, depth):
        b = self.recs[t][1]
        elem = self.strip(struct.unpack_from("<I", b, 0)[0])
        total = numeric(b, 8)[0]
        esz = self.sizeof(elem)
        if not esz or not total:
            return
        if elem < 0x1000 and (elem & 0xff) in _CHARS and not (elem >> 8) & 7:
            out.append(Field(off, "chars", total, None, name))
            return
        n = min(total // esz, 256)
        for i in range(n):
            if len(out) >= limit:
                return
            if self.is_class(elem):
                self._flatten(elem, off + i * esz, self.name(elem), None, out, limit, depth + 1)
            elif self.leaf(elem) == LF_ARRAY:
                self._array(elem, off + i * esz, name, out, limit, depth + 1)
            else:
                s = self.scalar(elem)
                if s and s[0] != "soup":
                    out.append(Field(off + i * esz, s[0], s[1], s[2], "%s[%d]" % (name, i)))

    def is_rbnode(self, ti):
        """ti is an rbtree node by shape: pointers at +0/+4/+8 and a 1- or 4-byte integer (the color) at +0xc."""
        ti = self.strip(ti)
        info = self.info(ti)
        if info is None or not self.is_class(ti) or self.sizeof(ti) < 0x10:
            return False
        flat, todo = {}, [(ti, 0)]
        while todo:                                     # own members and base classes' (rbtree_node : base)
            t, b = todo.pop()
            inf = self.info(self.strip(t))
            if inf is None:
                continue
            for sl, d in self.fields(inf["field"]):
                if sl == LF_MEMBER:
                    flat.setdefault(b + d["off"], d["type"])
                elif sl == LF_BCLASS:
                    todo.append((d["type"], b + d["off"]))
        if any(o not in flat or self.pointee(flat[o]) is None or self.sizeof(flat[o]) != 4 for o in (0, 4, 8)):
            return False
        c = flat.get(0xc)
        sc = self.scalar(c) if c is not None else None
        return bool(sc and sc[0] in ("int", "bool", "enum") and sc[1] in (1, 4))

    def _rbtree(self, fl, members):
        """(anchor offset, target) of an rbtree's own members (see the module doc), else None."""
        a = next((d for d in members if "anchor" in d["name"].lower() and self.is_rbnode(d["type"])), None)
        if a is None:
            return None
        val = next((d["type"] for sl, d in fl if sl == LF_NESTTYPE and d["name"] == "value_type"), None)
        if val is not None:
            val = self.strip(val)
            if not (self.is_class(val) and self.sizeof(val)) and not self.scalar(val):
                val = None                              # declared but never instantiated in this TU
        if val is None and self.sizeof(a["type"]) > 0x10:
            val = ("node", self.strip(a["type"]))
        return a["off"], val

    def _is_rglstring(self, members):
        sig = [(d["name"], d["off"]) for d in members]
        if sig != [("pos", 0), ("buf", 4), ("cap", 8), ("len", 12)]:
            return False
        return self.scalar(members[1]["type"])[0] == "ptr_char"

    def _vector_triples(self, members):
        """{offset of first: element type} for each (first, last, end) pointer triple among the members."""
        out = {}
        for i in range(len(members) - 2):
            a, b, c = members[i:i + 3]
            if not vector_names(a["name"], b["name"], c["name"]):
                continue
            if not (b["off"] == a["off"] + 4 and c["off"] == a["off"] + 8):
                continue
            pa, pb, pc = (self.pointee(x["type"]) for x in (a, b, c))
            if pa is None or pa != pb or pa != pc:
                continue
            pa = self.strip(pa)
            if pa < 0x1000 and (pa & 0xff) == 0x03 and not (pa >> 8) & 7:
                continue                                # void*: element size unknown
            if self.sizeof(pa):
                out[a["off"]] = pa
        return out

    # ---- functions
    def func(self, ti):
        """{ret, cls, this, args: [type index], conv} of an LF_MFUNCTION / LF_PROCEDURE, or None."""
        r = self.recs.get(ti)
        if r is None:
            return None
        lf, b = r
        if lf == LF_MFUNCTION:
            ret, cls, this, cc, _fa, n, al = struct.unpack_from("<IIIBBHI", b, 0)
        elif lf == LF_PROCEDURE:
            ret, cc, _fa, n, al = struct.unpack_from("<IBBHI", b, 0)
            cls = this = 0
        else:
            return None
        args = []
        ra = self.recs.get(al)
        if ra and ra[0] == LF_ARGLIST:
            cnt = struct.unpack_from("<I", ra[1], 0)[0]
            args = list(struct.unpack_from("<%dI" % cnt, ra[1], 4))
        return dict(ret=ret, cls=cls, this=this, args=args, conv=cc)


def data_type(name):
    """The class a decorated global variable is (`?g@@3UFoo@rgl@@A` -> ("obj", "rgl::Foo")) or points to
    (`?g_game@@3PAVGame@@A` -> ("ptr", "Game")); None for anything else (templates, arrays, scalars)."""
    if not name.startswith("?") or "@@3" not in name or "?$" in name:
        return None
    head, rest = name[1:].split("@@3", 1)
    table = head.split("@")                     # back-reference table: the variable's name and scopes
    kind = "obj"
    if rest[:1] in ("P", "Q", "R", "S") and rest[1:2] in ("A", "B", "C", "D"):
        kind, rest = "ptr", rest[2:]
    if rest[:1] not in ("U", "V"):
        return None
    frags, i, s = [], 1, rest
    while i < len(s) and s[i] != "@":
        if s[i].isdigit():
            k = int(s[i])
            if k >= len(table):
                return None
            frags.append(table[k])
            i += 1
            continue
        j = s.find("@", i)
        if j < 0:
            return None
        frags.append(s[i:j])
        table.append(s[i:j])
        i = j + 1
    if not frags or s[i + 1:] not in ("A", "B", "C", "D"):
        return None
    return kind, "::".join(reversed(frags))


def proc_types(coff):
    """{decorated function name: function type index} from the object's S_GPROC32 / S_LPROC32 records."""
    out = {}
    for s in coff.sections:
        if s.name != ".debug$S" or len(s.data) < 4 or struct.unpack_from("<I", s.data, 0)[0] != 4:
            continue
        d = s.data
        rel = {off: si for off, si, typ in s.relocs if typ == REL_SECREL}
        o = 4
        while o + 8 <= len(d):
            st, sl = struct.unpack_from("<II", d, o)
            body = o + 8
            end = len(d) if (st == 0xf1 and sl == 0) else body + sl
            if st == 0xf1:
                p = body
                while p + 4 <= end:
                    rl, rk = struct.unpack_from("<HH", d, p)
                    if rl < 2:
                        break
                    if rk in (S_GPROC32, S_LPROC32) and p + 39 <= end:
                        typind = struct.unpack_from("<I", d, p + 28)[0]
                        si = rel.get(p + 32)
                        if si is not None and si in coff.syms:
                            out.setdefault(coff.syms[si].name, typind)
                    p += 2 + rl
            o = (end + 3) & ~3
    return out


def load(coff):
    """(TypeTable, proc_types) of a /Z7 object; an empty table when it has no .debug$T."""
    data = b""
    for s in coff.sections:
        if s.name == ".debug$T":
            data = s.data
            break
    return TypeTable(data), proc_types(coff)
