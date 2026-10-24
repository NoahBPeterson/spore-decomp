"""Layout-driven inputs for equiv.py: build a consistent `this` object from the dev PDB's class layout.

The stock generator hands a function random "pointer soup": every dword of `this` is random, so an eastl::vector's
mpBegin/mpEnd/mpCapacity never describe an array, a list anchor never points at itself, and loops over members
run zero or garbage iterations (WEAK verdicts at a median 33% coverage, 2026-10-23). Mount & Blade's
work/match/struct_equiv.py showed the fix for one mesh class by hand; this does it for any class the dev PDB
describes (work/devbuild/types.json):

  vector / fixed_vector / basic_string  mpBegin..mpEnd over a real array of 0-6 elements, mpCapacity >= mpEnd
  list (ListNodeBase anchor)            empty: mpNext = mpPrev = &anchor
  rbtree (map/set anchor)               empty: left = right = &anchor, parent = 0, size 0
  pointer / AutoRefCount to a class     an object of that class (depth-limited), sometimes null
  float / double / bool / int / enum    sane values (floats in [-10, 10], bools 0/1, small ints)
  vfptr                                 left as soup, so virtual calls still become fake methods

Both the original and our code read the same memory, so an input built from a layout that does not match retail
(dev and retail layouts differ for some classes) only lowers coverage; it cannot make a mismatch disappear.
The class comes from the dev-PDB name of the function's retail address (work/migrate/modmap.json,
symbols/pdb_names.json), falling back to the class in our mangled symbol (slices often use stand-in names).
"""
import json, os, re, struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PRIM_SIZE = {"char": 1, "uchar": 1, "bool": 1, "short": 2, "ushort": 2, "wchar_t": 2, "int": 4, "uint": 4, "long": 4,
             "ulong": 4, "float": 4, "double": 8, "int64": 8, "uint64": 8, "void": 1}
FIRST_ALLOC_SLOT = 3000            # pool slots for arrays and pointed-to objects (soup pointers rarely land here)
MAX_DEPTH = 2

_types = None
_names = None


def types():
    global _types
    if _types is None:
        _types = json.load(open(os.path.join(ROOT, "work/devbuild/types.json")))["structs"]
    return _types


def retail_names():
    """retail VA (8 hex) -> dev-PDB qualified function name."""
    global _names
    if _names is None:
        _names = {}
        for p, key in (("work/migrate/modmap.json", "functions"), ("symbols/pdb_names.json", None)):
            try:
                d = json.load(open(os.path.join(ROOT, p)))
            except (OSError, ValueError):
                continue
            d = d[key] if key else d
            for va, m in d.items():
                if isinstance(m, dict) and m.get("name"):
                    _names.setdefault(va.lower().zfill(8), m["name"])
    return _names


def _strip_tmpl(n):
    out, depth = [], 0
    for ch in n:
        depth += ch == "<"
        if depth == 0:
            out.append(ch)
        depth -= ch == ">"
    return "".join(out)


def find_struct(name):
    """Exact name, or a unique struct whose name ends with ::<name> (a stand-in may drop the namespace)."""
    T = types()
    if name in T:
        return name
    short = "::" + name.split("::")[-1]
    c = [k for k in T if k.endswith(short) and "<" not in k]
    return c[0] if len(c) == 1 else None


def class_of(va, sym):
    """Qualified dev-PDB class of the function at retail `va` (int), else of our mangled symbol's scope."""
    n = retail_names().get("%08x" % va)
    if n and "::" in n:
        cls = n.rsplit("::", 1)[0]
        if _strip_tmpl(cls) == cls or cls in types():
            hit = find_struct(cls)
            if hit:
                return hit
    if sym and sym.startswith("?") and "@@" in sym and not sym.startswith("??"):
        parts = sym[1:].split("@@", 1)[0].split("@")
        if len(parts) >= 2 and all(p and not p.startswith(("?", "$")) for p in parts[1:]):
            return find_struct("::".join(reversed(parts[1:])))
    return None


def type_size(t):
    k, _, rest = t.partition(":")
    if k == "prim":
        return PRIM_SIZE.get(rest, 4)
    if k in ("ptr", "enum"):
        return 4
    if k == "struct":
        return types().get(rest, {}).get("size", 4) or 4
    if k == "arr":
        n, esz, _ = rest.split(":", 2)
        return int(n) * int(esz)
    return 4


def _members(name):
    """[(offset, type, size, member name)] including base classes, by offset."""
    T = types()
    s = T.get(name)
    if not s:
        return []
    out = []
    for bt, boff, _bsz in s.get("bases", []) or []:
        if bt.startswith("struct:"):
            out += [(boff + o, t, sz, n) for o, t, sz, n in _members(bt[7:])]
    for m in s.get("members", []):
        out.append((m[1], m[2], m[5] if len(m) > 5 and m[5] is not None else type_size(m[2]), m[0]))
    return sorted(out)


def _container_kind(name):
    base = name.split("<", 1)[0]
    if base in ("eastl::vector", "eastl::fixed_vector", "eastl::basic_string", "eastl::fixed_string",
                "eastl::VectorBase", "eastl::vector_map", "eastl::vector_set", "eastl::vector_multimap"):
        return "vector"
    if base in ("eastl::list", "eastl::fixed_list", "eastl::ListBase", "eastl::intrusive_list"):
        return "list"
    if base in ("eastl::map", "eastl::set", "eastl::multimap", "eastl::multiset", "eastl::rbtree",
                "eastl::fixed_map", "eastl::fixed_set"):
        return "rbtree"
    return None


class Builder:
    def __init__(self, rng, fin):
        self.rng, self.fin = rng, fin
        self.mem = {}                     # byte address -> byte
        self.next_slot = FIRST_ALLOC_SLOT

    def alloc(self, pool_base, slot_size):
        a = pool_base + self.next_slot * slot_size
        self.next_slot += 1
        return a

    def put(self, a, data):
        for i, b in enumerate(data):
            self.mem[a + i] = b

    def scalar(self, a, t, size):
        r = self.rng
        k, _, rest = t.partition(":")
        if k == "prim":
            if rest == "float":
                self.put(a, struct.pack("<f", r.uniform(-10, 10)))
            elif rest == "double":
                self.put(a, struct.pack("<d", r.uniform(-10, 10)))
            elif rest == "bool":
                self.put(a, bytes([r.randrange(2)]))
            elif size == 1:
                self.put(a, bytes([r.randrange(4)]))
            elif size == 2:
                self.put(a, struct.pack("<H", r.randrange(9)))
            elif size == 8:
                self.put(a, struct.pack("<Q", r.randrange(9)))
            else:
                self.put(a, struct.pack("<I", self.fin(r.choice((0, 1, 2, 3, 4, 5, 8, r.randrange(100))))))
        elif k == "enum":
            self.put(a, struct.pack("<I", r.randrange(5)))

    def value(self, a, t, size, depth, ctx):
        k, _, rest = t.partition(":")
        if k == "struct":
            self.struct(a, rest, depth, ctx)
        elif k == "ptr":
            self.pointer(a, rest, depth, ctx)
        elif k == "arr":
            n, esz, et = rest.split(":", 2)
            for i in range(min(int(n), 64)):
                self.value(a + i * int(esz), et, int(esz), depth, ctx)
        else:
            self.scalar(a, t, size)

    def pointer(self, a, target, depth, ctx):
        r = self.rng
        if r.random() < 0.1:
            self.put(a, struct.pack("<I", 0))
            return
        if target.startswith("struct:") and depth < MAX_DEPTH and target[7:] in types():
            o = self.alloc(*ctx)
            self.struct(o, target[7:], depth + 1, ctx)
            self.put(a, struct.pack("<I", o))
        else:
            self.put(a, struct.pack("<I", self.alloc(*ctx)))     # soup object

    def struct(self, a, name, depth, ctx):
        s = types().get(name)
        if s is None:
            return
        kind = _container_kind(name)
        mem = _members(name)
        if kind == "vector":
            beg = next((m for m in mem if m[3] == "mpBegin"), None)
            if beg and beg[1].startswith("ptr:"):
                et = beg[1][4:]
                esz = max(1, type_size(et))
                n = self.rng.choice((0, 1, 1, 2, 2, 3, 4, 6))
                n = min(n, 0x8000 // esz)
                arr = self.alloc(*ctx)
                for i in range(n):
                    self.value(arr + i * esz, et, esz, depth + 1, ctx)
                if name.startswith("eastl::basic_string"):
                    self.put(arr + n * esz, bytes(esz))          # terminator
                cap = n + self.rng.choice((0, 0, 1, 4))
                self.put(a + beg[0], struct.pack("<III", arr, arr + n * esz, arr + cap * esz))
                for o, t, sz, mn in mem:
                    if o >= beg[0] + 12:
                        self.value(a + o, t, sz, depth, ctx)
                return
        if kind == "list":
            # empty list: the anchor node's next/prev point at itself
            self.put(a, struct.pack("<II", a, a))
            for o, t, sz, mn in mem:
                if o >= 8 and t.startswith("prim"):
                    self.put(a + o, struct.pack("<I", 0)[:sz])
            return
        if kind == "rbtree":
            anc = next((m for m in mem if m[3] in ("mAnchor",)), None)
            if anc is not None:
                b = a + anc[0]
                # rbtree_node_base: mpNodeRight, mpNodeLeft, mpNodeParent, mColor
                self.put(b, struct.pack("<IIII", b, b, 0, 0))
                for o, t, sz, mn in mem:
                    if mn == "mnSize":
                        self.put(a + o, struct.pack("<I", 0))
                return
        for o, t, sz, mn in mem:
            if o == 0 and s.get("vfptr"):
                continue
            self.value(a + o, t, sz, depth, ctx)

    def dwords(self):
        """{dword address: value} covering every written byte; unwritten bytes of a touched dword are zero."""
        out = {}
        for a, b in self.mem.items():
            d = a & ~3
            out[d] = out.get(d, 0) | (b << (8 * (a - d)))
        return out


def build_this(rng, fin, cls, this_addr, pool_base, slot_size):
    """pool_over dwords for a `this` object of class `cls` at `this_addr` (and everything it points to)."""
    b = Builder(rng, fin)
    b.struct(this_addr, cls, 0, (pool_base, slot_size))
    return b.dwords()
