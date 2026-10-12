#!/usr/bin/env python3
"""headers: canonical class headers for a module, from the dev PDB types re-laid to retail sizes.

Phase B step 2 of docs/migration.md.  For every class a module owns (classes with a method in
the module per work/migrate/modmap.json) plus the bases and embedded types they need, write
<out>/<module>/<Namespace>/<Class>.h with:

  - data members at their RETAIL offsets.  The 2008 dev PDB (work/devbuild/types.json) gives the
    member order and dev offsets; retail offsets are recomputed by re-laying the members with
    retail sizes for the leaf types that changed (work/migrate/retail_leaf_sizes.json, measured
    from byte-exact slices: dev eastl::allocator is 4 bytes, retail 8, so every container grew by
    a word), natural alignment, and the dev build's own deliberate holes.  Layout resolution
    order: tools/migrate/layout_overrides.json (hand-confirmed retail layouts) > exact-backed slice
    views (work/migrate/sliceviews.json, members a byte-exact function touches) > re-laid dev PDB.
    Disagreements between the evidence and the re-laid PDB are printed and noted in the header.
  - the retail vtable address and the virtual functions in slot order, named by pairing the
    retail vtable (work/xmatch/tables.json ret_vt) with the dev vtable (dev_vt, through
    symbols/pdb_vtables.json) slot by slot, with full signatures demangled from the dev publics.
  - method declarations for every function of the class, with `// 0x<retail va>` where the
    module map knows the retail address.
  - a VC9-compatible size check (typedef char ...[(sizeof(T) == N) ? 1 : -1]) when the retail
    size is confirmed by evidence, else a comment with the re-laid size.

Metric: classes emitted; classes whose retail layout is confirmed / re-laid only; members whose
evidence disagrees with the re-laid PDB; classes with no PDB type (slice stub only).

usage: headers.py --module SUBSTR [--out work/migrate/headers] [--class NAME ...] [--selftest]
  --selftest   re-lay every dev struct with DEV leaf sizes and report the ones that do not
               reproduce the PDB offsets (validates the layout engine; nothing written)
"""
import argparse, collections, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
W = lambda *p: os.path.join(ROOT, *p)
UNDNAME = "/opt/homebrew/opt/llvm/bin/llvm-undname"

PRIM_SIZE = {"void": 0, "HRESULT": 4, "char": 1, "uchar": 1, "wchar_t": 2, "char16_t": 2, "char32_t": 4,
             "short": 2, "ushort": 2, "long": 4, "ulong": 4, "int": 4, "uint": 4, "longlong": 8, "ulonglong": 8,
             "float": 4, "double": 8, "bool": 1}
# Natural alignment up to 8, but a member's alignment is bounded by what its dev offset proves (an
# 8-byte member at a 4-aligned dev offset was packed at 4: EA::Variant is 0x14 with an __int64
# inside) and taken as 4 at offset 0, where the dev offset proves nothing.  --selftest measures it.
MAX_ALIGN = int(os.environ.get("HDR_MAX_ALIGN", "8"))
LIBRARY_NS = {"eastl", "std", "stdext"}   # template instantiations: shared headers, not per-module classes
PRIM_CPP = {"uchar": "unsigned char", "ushort": "unsigned short", "uint": "unsigned int", "ulong": "unsigned long",
            "longlong": "__int64", "ulonglong": "unsigned __int64"}


# ---- type descriptors -------------------------------------------------------------------------
def cpp_type(d, name=None):
    """C++ declarator text for a typedesc; `name` is the declarator name (arrays need it)."""
    if d.startswith("arr:"):
        _, n, _es, inner = d.split(":", 3)
        base, suffix = cpp_type(inner, None), "[%s]" % n
        if base.endswith("]"):          # nested arrays: int[3][4]
            m = re.match(r"^(.*?)((\[\d+\])+)$", base)
            base, suffix = m.group(1), suffix + m.group(2)
        return (base + " " + name + suffix) if name else base + suffix
    if d.startswith("blob:"):
        _b, n, txt = d.split(":", 2)
        if txt and not txt.startswith("eastl::") and not txt.startswith("EA::"):
            t = txt
        else:
            return "unsigned char %s[%s]" % (name or "blob", n) if name else "unsigned char[%s]" % n
    elif d.startswith("prim:"):
        t = PRIM_CPP.get(d[5:], d[5:])
    elif d.startswith("ptr:"):
        inner = d[4:]
        if inner == "func":
            t = "void (*)()"
        else:
            t = cpp_type(inner, None) + "*"
    elif d.startswith("struct:"):
        t = d[7:]
    elif d.startswith("enum:"):
        t = d[5:]
    elif d == "func":
        t = "void ()"
    else:
        t = "int /* ? */"
    return (t + " " + name) if name else t


class Types:
    def __init__(self, leaf=None, overrides=None, retail_rules=True):
        self.retail_rules = retail_rules     # False: re-lay with dev sizes only (--selftest)
        t = json.load(open(W("work/devbuild/types.json")))
        self.structs = t["structs"]
        self.enums = t["enums"]
        self.leaf = leaf or {}            # exact dev type name -> {"retail_size", "align", "members"?}
        self.overrides = overrides or {}  # class name -> {"size", "members": [[name, offset, size]], ...}
        self._cache = {}

    # size/alignment of a typedesc under a size mode: "dev" or "retail"
    def size_align(self, d, mode):
        if d.startswith("blob:"):
            n = int(d.split(":", 2)[1])
            return n, 4
        if d.startswith("prim:"):
            s = PRIM_SIZE.get(d[5:], 4)
            return s, max(1, min(s, MAX_ALIGN))
        if d.startswith("ptr:"):
            return 4, 4
        if d.startswith("arr:"):
            _, n, es, inner = d.split(":", 3)
            s, a = self.size_align(inner, mode)
            if s == 0:
                s = int(es)
            return s * int(n), a
        if d.startswith("enum:"):
            e = self.enums.get(d[5:])
            s = e["size"] if e else 4
            return s, s
        if d.startswith("struct:"):
            L = self.layout(d[7:], mode)
            if L is None:
                return None, 4
            return L["size"], L["align"]
        if d == "func":
            return 0, 1
        return None, 4

    def layout(self, name, mode):
        """{'size','align','members':[{name,offset,size,type,union}], 'bases':[...], 'vptr':bool,
        'source': 'pdb'|'leaf'|'override'|'missing'} for a struct under a size mode."""
        key = (name, mode)
        if key in self._cache:
            return self._cache[key]
        self._cache[key] = None   # recursion guard
        s = self.structs.get(name)
        L = None
        if mode == "retail" and name in self.overrides and "members" in self.overrides[name]:
            o = self.overrides[name]
            L = dict(size=o["size"], align=o.get("align", 4), bases=[], vptr=False, source="override",
                     members=[dict(name=m[0], offset=m[1], size=m[2], type=(m[3] if len(m) > 3 else None), union=False)
                              for m in o.get("members", [])])
        elif mode == "retail" and name in self.leaf and self.leaf[name].get("retail_size") is not None:
            o = self.leaf[name]
            L = dict(size=o["retail_size"], align=o.get("align") or 4, bases=[], vptr=False, source="leaf",
                     members=[dict(name=m[0], offset=m[1], size=m[2], type=(m[3] if len(m) > 3 else None), union=False)
                              for m in o.get("members", [])])
        elif s is None:
            L = None
        else:
            L = self._relayout(name, s, mode)
        self._cache[key] = L
        return L

    def _relayout(self, name, s, mode):
        if mode == "retail":
            s = self._apply_overrides(name, s)
        members, bases = [], []
        align = 1
        cursor = 0
        vptr = bool(s["vfptr"])
        # EA's headers pack at 4 (EA::Variant is 0x14 with an __int64 inside) while library types
        # such as EAMutexData (unsigned __int64 mData[4], 0x30) keep /Zp8; the dev size tells which
        pack8 = self.structs[name]["size"] % 8 == 0 if name in self.structs else s["size"] % 8 == 0
        # vptr first when the class introduces one and its first base does not start at 0
        if vptr and (not s["bases"] or s["bases"][0][1] > 0):
            cursor = 4
            align = 4
        dev_prev_end = cursor
        # the PDB lists bases in declaration order; MSVC lays them out with the vptr-carrying
        # ones first, so walk them in dev address order and keep that order in retail
        for bdesc, boff, bsize in sorted(s["bases"], key=lambda b: b[1]):
            bname = bdesc.split(":", 1)[1]
            BL = self.layout(bname, mode)
            bs, ba = (BL["size"], BL["align"]) if BL else (bsize, 4)
            bs_struct = self.structs.get(bname)
            empty = bs_struct is not None and not bs_struct["members"] and not bs_struct["vfptr"] and bsize <= 1 \
                and all(self.structs.get(b[0].split(":", 1)[1], {}).get("members") == [] for b in bs_struct["bases"])
            if mode == "dev":
                off = boff
            else:
                off = (cursor + ba - 1) // ba * ba
                extra = boff - ((dev_prev_end + ba - 1) // ba * ba)   # deliberate hole in dev
                if extra > 0:
                    off += extra
            bases.append(dict(name=bname, offset=off, size=bs, dev_offset=boff, empty=empty))
            if empty:        # empty base optimisation: occupies no storage of its own
                cursor = max(cursor, off)
                dev_prev_end = max(dev_prev_end, boff)
                continue
            cursor = max(cursor, off + bs)
            dev_prev_end = max(dev_prev_end, boff + bsize)
            align = max(align, ba)
        # members; a member at the same dev offset as the previous one overlaps it (anonymous union)
        dev_members = s["members"]
        last_dev_off = None
        union_start = None
        for i, m in enumerate(dev_members):
            mname, doff, d, bitpos, bitlen, dsize = m
            ms, ma = self.size_align(d, mode)
            if ms is None:
                ms, ma = dsize, 4
            # the dev offset bounds the alignment: an 8-byte member the dev build put at a
            # 4-aligned offset was packed at 4 (EA code is /Zp4-like: EA::Variant is 0x14 with an
            # __int64 inside), and the retail build packed it the same way
            ma = min(ma, (doff & -doff) if doff else (8 if pack8 else 4))
            if not pack8:
                ma = min(ma, 4)
            overlap = bool(members) and doff < dev_prev_end
            if mode == "dev":
                off = doff
            elif overlap:
                # union member or bitfield: map through the placed member whose dev storage holds it
                anchor = max((x for x in members if x["dev_offset"] <= doff), key=lambda x: x["dev_offset"])
                off = anchor["offset"] + (doff - anchor["dev_offset"])
            else:
                off = (cursor + ma - 1) // ma * ma
                extra = doff - ((dev_prev_end + ma - 1) // ma * ma)
                if extra > 0 and not bitlen:
                    off += extra
            members.append(dict(name=mname, offset=off, size=ms, type=d, union=False, bitpos=bitpos, bitlen=bitlen,
                                dev_offset=doff))
            if overlap and not bitlen:
                for x in members:
                    if x["dev_offset"] == doff:
                        x["union"] = True
            cursor = max(cursor, off + ms)
            dev_prev_end = max(dev_prev_end, doff + dsize)
            last_dev_off = doff
            align = max(align, ma)
        if not pack8:
            align = min(align, 4)
        if mode == "dev":
            size = s["size"]
        else:
            if cursor == 0:
                size = s["size"]  # empty class (1 byte), or a class the PDB left without members
            else:
                size = (cursor + align - 1) // align * align
                # a trailing hole the dev build kept (reserved space), measured on the original
                # record (overrides shift the dev offsets and sizes)
                orig = self.structs.get(name, s)
                orig_end = max([b[1] + b[2] for b in orig["bases"]] + [m[1] + (m[5] or 0) for m in orig["members"]] +
                               [4 if orig["vfptr"] else 0])
                dev_tail = orig["size"] - ((orig_end + align - 1) // align * align)
                if dev_tail > 0:
                    size += dev_tail
        return dict(size=size, align=align, members=members, bases=bases, vptr=vptr, source="pdb", kind=s["kind"])

    def _apply_overrides(self, name, s):
        """Structural retail deltas from tools/migrate/layout_overrides.json, applied to a copy of the
        dev record before re-layout: {"insert": [{"after": member|null, "name", "type"(C text),
        "size", "align"?}], "remove": [member names], "append": [{"name","size","type"?}],
        "evidence": "..."}; and the vector rule: a retail VectorBase's allocator slot is 8 bytes
        for every allocator (12 for fixed_vector_allocator with overflow), measured in
        tools/migrate/leafsizes.py."""
        o = self.overrides.get(name)
        mem = [list(m) for m in s["members"]]
        if self.retail_rules and name.startswith("eastl::VectorBase<"):
            for m in mem:
                if m[0] == "mAllocator" and m[2].startswith("struct:"):
                    an = m[2][7:]
                    slot = 12 if (an.startswith("eastl::fixed_vector_allocator<") and an.rstrip(">").rstrip().endswith(",1")) \
                        else 8
                    m[2] = "blob:%d:%s" % (slot, an)
                    m[5] = slot
        if not o or "size" in o and "members" in o:
            return dict(s, members=mem) if mem != s["members"] else s
        for r in o.get("remove", []):
            mem = [m for m in mem if m[0] != r]
        for ins in o.get("insert", []):
            k = 0
            if ins.get("after"):
                k = next((i + 1 for i, m in enumerate(mem) if m[0] == ins["after"]), len(mem))
            # dev offset: right after the predecessor, so the re-layout places it there; the members
            # after it keep their dev offsets and are pushed by the normal alignment rules
            doff = (mem[k - 1][1] + (mem[k - 1][5] or 4)) if k else 0
            mem.insert(k, [ins["name"], doff, "blob:%d:%s" % (ins["size"], ins.get("type", "")), None, None, ins["size"]])
            for m in mem[k + 1:]:
                m[1] += ins["size"]    # keep the dev gaps after the insertion point intact
        for ap in o.get("append", []):
            last = mem[-1] if mem else [None, 0, "", None, None, 0]
            mem.append([ap["name"], last[1] + (last[5] or 4), "blob:%d:%s" % (ap["size"], ap.get("type", "")),
                        None, None, ap["size"]])
        s2 = dict(s, members=mem)
        if o.get("append") or o.get("insert") or o.get("remove"):
            s2["size"] = max(s["size"] + sum(a["size"] for a in o.get("append", [])) +
                             sum(i["size"] for i in o.get("insert", [])) -
                             sum(m[5] for m in s["members"] if m[0] in o.get("remove", [])), 1)
        return s2

    def selftest(self):
        bad = []
        T0 = Types(retail_rules=False)       # the engine alone: dev sizes, no leaf table, no overrides
        for name, s in self.structs.items():
            L = self.layout(name, "dev")
            if not L or (not s["members"] and not s["bases"]):
                continue
            R = T0.layout(name, "retail")
            if R["size"] != s["size"] or any(a["offset"] != b["offset"] for a, b in zip(R["members"], L["members"])):
                bad.append((name, s["size"], R["size"],
                            [(a["name"], b["offset"], a["offset"]) for a, b in zip(R["members"], L["members"])
                             if a["offset"] != b["offset"]][:3]))
        return bad


# ---- demangling -------------------------------------------------------------------------------
class Undname:
    def __init__(self):
        self.path = W("work/migrate/undname_cache.json")
        self.cache = json.load(open(self.path)) if os.path.exists(self.path) else {}

    def many(self, names):
        todo = [n for n in dict.fromkeys(names) if n not in self.cache]
        if todo and os.path.exists(UNDNAME):
            out = subprocess.run([UNDNAME], input="\n".join(todo) + "\n", capture_output=True, text=True).stdout
            lines = [l for l in out.splitlines()]
            # llvm-undname prints "<mangled>\n<demangled>\n\n" per name
            i = 0
            while i + 1 < len(lines):
                if lines[i] in todo or lines[i].strip() in todo:
                    self.cache[lines[i].strip()] = lines[i + 1].strip()
                    i += 2
                else:
                    i += 1
            os.makedirs(os.path.dirname(self.path), exist_ok=True)
            json.dump(self.cache, open(self.path, "w"))
        return {n: self.cache.get(n) for n in names}


CC = ("__thiscall", "__cdecl", "__stdcall", "__fastcall", "__clrcall")


def split_qual(q):
    """'A::B<C::D>::f' -> ('A::B<C::D>', 'f') splitting at the last :: outside <>."""
    depth = 0
    for i in range(len(q) - 1, 0, -1):
        c = q[i]
        if c == ">":
            depth += 1
        elif c == "<":
            depth -= 1
        elif depth == 0 and q[i] == ":" and q[i - 1] == ":":
            return q[:i - 1], q[i + 1:]
    return "", q


def parse_decl(dm):
    """Parse llvm-undname output for a function into a dict, or None.
    'public: virtual bool __thiscall SP::cPropertyList::GetProperty(unsigned int, class EA::Variant const *&) const'"""
    if dm is None or "(" not in dm or "`vftable'" in dm:
        return None
    d = dict(access=None, virtual=False, static=False, const=False)
    m = re.match(r"^(public|protected|private): ", dm)
    if m:
        d["access"] = m.group(1)
        dm = dm[m.end():]
    for kw in ("virtual ", "static "):
        if dm.startswith(kw):
            d[kw.strip()] = True
            dm = dm[len(kw):]
    cc = None
    for c in CC:
        k = dm.find(" " + c + " ")
        if k >= 0 or dm.startswith(c + " "):
            cc = c
            break
    if cc is None:
        return None
    k = dm.find(cc + " ")
    ret = dm[:k].strip()
    rest = dm[k + len(cc) + 1:]
    p = rest.find("(")
    qual = rest[:p]
    tail = rest[p:]
    # params up to the matching paren
    depth = 0
    for i, ch in enumerate(tail):
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                params = tail[1:i]
                after = tail[i + 1:]
                break
    else:
        return None
    d["const"] = after.strip().startswith("const")
    cls, meth = split_qual(qual)
    d.update(ret=ret, cc=cc, cls=cls, name=meth, params=("" if params.strip() == "void" else params.strip()))
    # strip elaborated-type keywords the demangler adds
    d["ret"] = re.sub(r"\b(class|struct|union|enum) ", "", d["ret"])
    d["params"] = re.sub(r"\b(class|struct|union|enum) ", "", d["params"])
    return d


# ---- data -------------------------------------------------------------------------------------
class Data:
    def __init__(self):
        self.modmap = json.load(open(W("work/migrate/modmap.json")))
        s = json.load(open(W("work/devbuild/symbols.json")))
        self.dev_fn = {f["va"]: f for f in s["functions"]}
        self.pub = {}
        for p in s["publics"]:
            if p["code"] and p["name"].startswith("?"):
                self.pub.setdefault(p["va"], p["name"])
        self.thunks = {int(k, 16): v for k, v in s["thunks"].items()}
        self.pdb_names = json.load(open(W("symbols/pdb_names.json")))
        t = json.load(open(W("work/xmatch/tables.json")))
        self.ret_vt, self.dev_vt = t["ret_vt"], t["dev_vt"]
        self.pdb_vtables = json.load(open(W("symbols/pdb_vtables.json")))
        self.und = Undname()
        self.leaf = {}
        p = W("work/migrate/retail_leaf_sizes.json")
        if os.path.exists(p):
            raw = json.load(open(p))
            for e in (raw if isinstance(raw, list) else raw.get("entries") or raw.get("types") or raw.get("leaves") or []):
                if isinstance(e, dict) and e.get("name") and e.get("retail_size") is not None and \
                        e.get("confidence", "measured") != "unknown":
                    self.leaf[e["name"]] = e
        self.views = None
        p = W("work/migrate/sliceviews.json")
        if os.path.exists(p):
            self.views = json.load(open(p))
        p = W("tools/migrate/layout_overrides.json")   # hand-curated evidence: lives in the repo
        self.overrides = json.load(open(p)) if os.path.exists(p) else {}
        self.types = Types(self.leaf, self.overrides)

    def dev_target(self, hexva):
        va = int(hexva, 16)
        return self.thunks.get(va, va)

    def module_functions(self, substr):
        out = collections.defaultdict(list)
        for va, e in self.modmap["functions"].items():
            if substr.lower() in e["module"].lower():
                out[e["module"]].append((int(va, 16), e))
        return out

    def class_of_name(self, name):
        cls, _m = split_qual(name)
        return cls

    def retail_vtables_for(self, cls):
        """[(retail vt va or None, dev vt va, mangled, demangled)] for a class: paired vtables from
        symbols/pdb_vtables.json first; otherwise the dev vtables of the class by name, with the retail
        vtable located by slot agreement (>= 2 dev slots whose retail counterparts sit at the same
        index) when possible."""
        out = []
        seen_dev = set()
        if not hasattr(self, "_pdb_vt_dm"):
            self._pdb_vt_dm = self.und.many([e["name"] for e in self.pdb_vtables.values()])
        for rva, e in self.pdb_vtables.items():
            dm = self._pdb_vt_dm.get(e["name"])
            if dm and dm.startswith("const " + cls + "::`vftable'"):
                out.append((rva, e["dev"], e["name"], dm))
                seen_dev.add(e["dev"])
        if not hasattr(self, "_dev_vt_names"):
            names = [v["name"] for v in self.dev_vt.values()]
            dms = self.und.many(names)
            self._dev_vt_names = {dva: dms.get(v["name"]) for dva, v in self.dev_vt.items()}
            self._dev2ret = {}
            for rva, e in self.pdb_names.items():
                self._dev2ret.setdefault(int(e["dev"], 16), rva)
            self._slot_index = collections.defaultdict(list)   # retail fn va -> [(vt va, k)]
            for rva, slots in self.ret_vt.items():
                for k, f in enumerate(slots):
                    self._slot_index[f].append((rva, k))
            self._vtbl_names = {}
            for line in open(W("symbols/vtable_names.txt")):
                p = line.split("#", 1)[0].split()
                if len(p) >= 2 and p[1].startswith("vtbl_"):
                    self._vtbl_names.setdefault(p[1][5:].split("::")[-1], []).append(p[0])
        for dva, dm in self._dev_vt_names.items():
            if dva in seen_dev or not dm or not dm.startswith("const " + cls + "::`vftable'"):
                continue
            dslots = self.dev_vt[dva]["slots"]
            votes = collections.Counter()
            for k, hs in enumerate(dslots):
                r = self._dev2ret.get(self.dev_target(hs))
                if r:
                    for vt, kk in self._slot_index.get(r, []):
                        if kk == k:
                            votes[vt] += 1
            # candidates: retail vtables not already paired with another class, with the dev
            # slot count (a derived class's vtable shares the inherited slots and would win a
            # plain vote), ranked by agreeing slots; symbols/vtable_names.txt (vtbl_<Class> lines
            # from tools/vtable_names.py, ModAPI names on the binary's addresses) breaks ties
            paired = set(self.pdb_vtables)
            named = set(c for c in self._vtbl_names.get(cls.split("::")[-1], []) if c in self.ret_vt)
            cands = [(v, c in named, c) for c, v in votes.items()
                     if c not in paired and len(self.ret_vt[c]) == len(dslots) and v >= 2]
            cands += [(0, True, c) for c in named if c not in paired and c not in votes and len(self.ret_vt[c]) == len(dslots)]
            cands.sort(reverse=True)
            rva, how = None, None
            if cands and (cands[0][0] >= 2 or cands[0][1]):
                v, nm, rva = cands[0]
                how = "%d of %d slots agree%s" % (v, len(dslots), ", named in symbols/vtable_names.txt" if nm else "")
            out.append((rva, dva, self.dev_vt[dva]["name"], dm + (" (%s)" % how if rva else " (retail vtable not located)")))
        return out


# ---- emission ---------------------------------------------------------------------------------
def flat(name):
    return re.sub(r"[^A-Za-z0-9_]+", "_", name).strip("_")


def header_path(out, module, cls):
    parts = re.split(r"::", re.sub(r"<.*>", "", cls))
    return os.path.join(out, module.replace(".obj", ""), *parts[:-1], parts[-1] + ".h")


def evidence_for(data, cls, relaid):
    """Exact-backed slice views of a class, selected and merged against the re-laid dev layout.

    A view is accepted when it shares at least 3 member names with the dev layout and the offset
    shifts of the shared members are non-negative, non-decreasing and at most 0x40 each: the shape
    that inserted members or grown leaf types produce.  A view that shares the member prefix but
    then diverges wildly is another class under the same short name (DatabasePackedFile has one
    with a 1076-byte file member) and is rejected with a note.

    Returns (members, notes): members = {dev member name: (offset, size, slice)} plus retail-only
    members as {"+<name>": (offset, size, slice, type text)}; notes = list of strings."""
    members, notes = {}, []
    if not data.views:
        return members, notes
    short = cls.split("::")[-1]
    idx = data.views.get("by_name", {})
    views = data.views.get("defs") or data.views.get("views") or []
    cands = []
    for n, ids in idx.items():
        if n == short or n.endswith("::" + short) or n == cls:
            cands += [views[i] for i in ids]
    dev_off = {m["name"]: m["offset"] for m in relaid["members"]}
    dev_names = set(dev_off)
    accepted = []
    for v in cands:
        if not v.get("exact_users"):
            continue
        vm = [m for m in v.get("members", []) if not m.get("pad") and m.get("offset") is not None]
        shared = [(m["name"], m["offset"] - dev_off[m["name"]]) for m in vm if m["name"] in dev_names]
        if len(shared) < 3:
            continue
        shifts = [d for _n, d in shared]
        # inserted members shift what follows by a few words; a dev padding hole can absorb a
        # shift again, so the sequence need not be monotone, only small and non-negative
        ok = all(-8 <= d <= 0x40 for d in shifts) and len(set(shifts)) <= 4
        if not ok:
            notes.append("view %s (size 0x%x, %d shared members) rejected: shifts %s" % (
                v["slice"], v.get("size") or 0, len(shared), sorted(set(shifts))[:8]))
            continue
        agree = sum(1 for _n, d in shared if d == 0)
        accepted.append((agree, len(shared), len(v["exact_users"]), v, vm, shifts))
    if not accepted:
        return members, notes
    # one view is the evidence (the slices invent different names for the same unnamed members,
    # so merging views would double them): the one whose named members agree most with the
    # re-laid offsets, then the one sharing the most names, then the most byte-exact users.
    accepted.sort(key=lambda x: (-x[0], -x[1], -x[2]))
    agree, n_shared, n_users, v, vm, shifts = accepted[0]
    notes.append("view %s is the evidence: %d of %d shared members agree with the re-laid offsets, %d byte-exact users, "
                 "shifts %s, declared size 0x%x" % (v["slice"], agree, n_shared, n_users, sorted(set(shifts)), v.get("size") or 0))
    for m in vm:
        key = m["name"] if m["name"] in dev_names else "+" + m["name"]
        members[key] = (m["offset"], m.get("size"), v["slice"], m.get("type"))
    for _a2, n2, u2, v2, vm2, sh2 in accepted[1:]:
        dis = [(m["name"], m["offset"]) for m in vm2 if m["name"] in members and members[m["name"]][0] != m["offset"]]
        notes.append("view %s agrees (%d shared)%s" % (v2["slice"], n2, "" if not dis else
                     "; disagrees on " + ", ".join("%s 0x%x" % d for d in dis[:4])))
    return members, notes


def merge_layout(relaid, ev):
    """Final member list.  Dev members whose name a view has take the view's offset
    ('exact:<slice>').  Between two such anchors, dev members and the view's extra members are
    paired positionally when their counts agree: the slice invented a name for a member the PDB
    names ('exact-renamed:<slice> (slice: <name>)').  Otherwise the dev members stay at their
    re-laid offsets ('relaid', or 'relaid?collides:<view member>' when a view member overlaps
    them) and the view members are added as 'retail-only:<slice>'."""
    dev = relaid["members"]
    extra = sorted([(e[0], k[1:], e) for k, e in ev.items() if k.startswith("+")])
    out = []
    # segment dev members by anchors (members with evidence)
    segs = []       # (dev members without evidence in this span, lower bound offset, upper bound offset)
    span = []
    lo = 0
    for m in dev:
        if m["name"] in ev:
            if span:
                segs.append((span, lo, ev[m["name"]][0]))
                span = []
            lo = ev[m["name"]][0] + (m["size"] or 0)
        else:
            span.append(m)
    if span:
        segs.append((span, lo, 1 << 30))
    renamed = {}
    used = set()
    for span, slo, shi in segs:
        cand = [x for x in extra if slo <= x[0] < shi and id(x) not in used]
        if not cand:
            continue
        # order-preserving alignment of the span's dev members with the view's extra members:
        # a pair scores when the view member sits at the dev member's re-laid offset or a little
        # after it (inserted members push things down, never up) and the sizes agree
        n, k = len(span), len(cand)
        best = [[0] * (k + 1) for _ in range(n + 1)]
        choice = [[None] * (k + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(k - 1, -1, -1):
                best[i][j], choice[i][j] = best[i + 1][j], "skip-dev"
                if best[i][j + 1] > best[i][j]:
                    best[i][j], choice[i][j] = best[i][j + 1], "skip-view"
                m, x = span[i], cand[j]
                delta = x[0] - m["offset"]
                if 0 <= delta <= 0x10 and (x[2][1] is None or x[2][1] == m["size"]):
                    sc = 2 if delta == 0 else 1
                    if best[i + 1][j + 1] + sc > best[i][j]:
                        best[i][j], choice[i][j] = best[i + 1][j + 1] + sc, "pair"
        i = j = 0
        while i < n and j < k:
            c = choice[i][j]
            if c == "pair":
                renamed[span[i]["name"]] = cand[j]
                used.add(id(cand[j]))
                i += 1
                j += 1
            elif c == "skip-dev":
                i += 1
            else:
                j += 1
    # A slice's member NAMES are guesses (one DatabasePackedFile view names 0x25c "mpStream" where
    # the re-laid layout, confirmed by disassembly, has the file starting offset), so evidence
    # confirms a re-laid offset or is reported as a conflict; it never moves a member.  Structural
    # deltas go through layout_overrides.json, after which the view agrees.
    conflicts = []
    for m in dev:
        x = dict(m)
        if m["name"] in ev:
            if ev[m["name"]][0] == m["offset"]:
                x["prov"] = "exact:" + ev[m["name"]][2]
            else:
                x["prov"] = "relaid!view:%s has 0x%x" % (ev[m["name"]][2], ev[m["name"]][0])
                conflicts.append((m["name"], m["offset"], ev[m["name"]][0]))
        elif m["name"] in renamed:
            off, vname, e = renamed[m["name"]]
            x["prov"] = ("exact-renamed:%s (slice: %s)" % (e[2], vname)) if off == m["offset"] else \
                ("relaid!view:%s has %s at 0x%x" % (e[2], vname, off))
        else:
            x["prov"] = "relaid"
        out.append(x)
    occupied = [(m["offset"], m["offset"] + (m["size"] or 0)) for m in out]
    for x in extra:
        if id(x) in used:
            continue
        off, vname, e = x
        free = not any(a <= off < b for a, b in occupied)
        if free:
            out.append(dict(name=vname, offset=off, size=e[1] or 4, type=None, type_text=e[3], union=False,
                            bitlen=None, dev_offset=None, prov="retail-only:" + e[2]))
        else:
            conflicts.append((vname, None, off))
    out.sort(key=lambda x: (x["offset"], 0 if x["prov"].startswith("exact") else 1))
    merge_layout.conflicts = conflicts
    return out


def emit_class(data, module, cls, retail_fns, report, out_dir):
    T = data.types
    L = T.layout(cls, "retail")
    D = T.layout(cls, "dev")
    s = T.structs.get(cls)
    lines = []
    guard = "GAME_%s_H" % flat(cls).upper()
    lines += ["// %s -- generated by tools/migrate/headers.py from the dev PDB, re-laid to retail sizes." % cls,
              "// Module: %s.  Do not hand-edit members; fix tools/migrate/layout_overrides.json or the leaf table." % module,
              "#ifndef %s" % guard, "#define %s" % guard, '#include "game/types.h"', ""]
    if s is None:
        lines += ["// No type record in the dev PDB for %s: slice stub only (TODO)." % cls]
        report["no_pdb"] += 1
        lines += ["#endif", ""]
        return lines
    ev, notes = evidence_for(data, cls, L)
    merged = merge_layout(L, ev)
    mconf = merge_layout.conflicts
    added = [m for m in merged if m["prov"].startswith("retail-only")]
    unverified = [m for m in merged if m["prov"].startswith("relaid")]
    override = cls in data.overrides
    confirmed = bool(ev) and not unverified and not added
    report["classes"] += 1
    report["confirmed" if confirmed else ("evidence" if ev else "relaid")] += 1
    report["conflicts"] += len(mconf)
    report["added"] += len(added)
    report["overridden"] += override
    retail_size = L["size"]
    for c in mconf:
        notes.append("conflict: %s re-laid 0x%x, view has 0x%x" % (c[0], c[1], c[2]) if c[1] is not None else
                     "conflict: view member %s at 0x%x overlaps a re-laid member" % (c[0], c[2]))
    if override:
        notes.append("override applied: " + (data.overrides[cls].get("evidence") or "(no evidence string)"))

    # namespaces
    ns = cls.split("::")[:-1]
    short = cls.split("::")[-1]
    ns_open = [p for p in ns if "<" not in p]
    for p in ns_open:
        lines.append("namespace %s {" % p)
    lines.append("")
    # forward declarations of referenced class types
    refs = set()
    for m in L["members"]:
        d = m["type"] or ""
        while d.startswith(("ptr:", "arr:")):
            d = d.split(":", 1)[1] if d.startswith("ptr:") else d.split(":", 3)[3]
        if d.startswith("struct:"):
            refs.add(d[7:])
    for b in L["bases"]:
        refs.add(b["name"])
    lines.append("// Types used (defined elsewhere): " + ", ".join(sorted(refs)) if refs else "// No type references.")
    lines.append("")
    # class head
    bases = ", ".join("public %s /* +0x%x */" % (b["name"], b["offset"]) for b in L["bases"])
    kind = s["kind"] if s["kind"] in ("struct", "class", "union") else "class"
    lines.append("// dev size 0x%x -> retail size 0x%x (%s)" % (
        s["size"], retail_size, "override" if override else
        ("all %d members exact-backed" % len(merged) if confirmed else
         ("%d members exact-backed, %d conflicts, %d retail-only, %d unverified" % (
             sum(1 for m in merged if m["prov"].startswith("exact")), len(mconf), len(added), len(unverified)) if ev
          else "re-laid from the PDB, unverified in retail"))))
    for n in notes:
        lines.append("// evidence: " + n)
    lines.append("%s %s%s {" % (kind, short, (" : " + bases) if bases else ""))
    lines.append(" public:")
    # vtable
    vts = data.retail_vtables_for(cls)
    virtuals = []
    # demangle every slot's public name in one llvm-undname call
    slot_names = []
    for _rva, dva, _mangled, _dm in vts:
        for hs in data.dev_vt.get(dva, {}).get("slots", []):
            mn = data.pub.get(data.dev_target(hs))
            if mn:
                slot_names.append(mn)
    data.und.many(slot_names)
    for rva, dva, mangled, dm in vts:
        rslots = data.ret_vt.get(rva, []) if rva else []
        dslots = data.dev_vt.get(dva, {}).get("slots", [])
        if not rslots:   # retail addresses of the slot functions from the name map, where known
            rslots = [data._dev2ret.get(data.dev_target(hs)) for hs in dslots]
        lines.append("  // vtable %s (%s): %d retail slots, %d dev slots" % (
            ("0x" + rva) if rva else "retail address unknown", dm.split("`vftable'")[1] or "primary", len(rslots), len(dslots)))
        n = max(len(rslots), len(dslots))
        for k in range(n):
            r = rslots[k] if k < len(rslots) else None
            dt = data.dev_target(dslots[k]) if k < len(dslots) else None
            mangled_m = data.pub.get(dt) if dt else None
            dm_m = data.und.many([mangled_m])[mangled_m] if mangled_m else None
            decl = parse_decl(dm_m)
            if decl and decl["cls"] != cls:
                inherited = decl["cls"]
            else:
                inherited = None
            txt = None
            if decl:
                nm = decl["name"]
                if nm.startswith("`scalar deleting dtor'") or nm.startswith("`vector deleting dtor'"):
                    txt = "virtual ~%s();" % short
                else:
                    txt = "virtual %s %s(%s)%s;" % (decl["ret"], nm, decl["params"], " const" if decl["const"] else "")
            rname = data.pdb_names.get(r, {}).get("name") if r else None
            note = "// slot %d%s%s" % (k, (", 0x%s" % r) if r else ", (no retail slot)",
                                       (", inherited from " + inherited) if inherited else "")
            if txt is None:
                txt = "// virtual ? slot_%d();  %s" % (k, ("retail " + rname) if rname else "unnamed")
                lines.append("  %s  %s" % (txt, note))
            else:
                lines.append("  %-70s %s" % (txt, note))
            virtuals.append((k, r, dt))
        lines.append("")
    # methods: dev publics of this class with retail addresses from the module map
    if not hasattr(data, "_methods_by_class"):
        data._methods_by_class = collections.defaultdict(list)
        for dva, mangled in data.pub.items():
            f = data.dev_fn.get(dva)
            if f:
                c, _m = split_qual(f["name"])
                data._methods_by_class[c].append((dva, mangled, f))
    dev_methods = data._methods_by_class.get(cls, [])
    dm_all = data.und.many([m for _d, m, _f in dev_methods])
    retail_by_dev = {}
    for va, e in retail_fns:
        if e.get("dev"):
            retail_by_dev[int(e["dev"], 16)] = (va, e)
    vslots = {dt for _k, _r, dt in virtuals if dt}
    rows = []
    for dva, mangled, f in sorted(dev_methods, key=lambda x: x[0]):
        decl = parse_decl(dm_all.get(mangled))
        if not decl or dva in vslots:
            continue
        nm = decl["name"]
        if nm.startswith("`"):
            continue
        if nm == "~" + short and any(l.startswith("  virtual ~") for l in lines):
            r = retail_by_dev.get(dva)
            for i, l in enumerate(lines):
                if l.startswith("  virtual ~"):
                    lines[i] = l + (", dtor body 0x%08x" % r[0] if r else ", dtor body dev only")
            continue
        if nm == short or nm.startswith(short + "<"):
            txt = "%s(%s);" % (short, decl["params"])
        elif nm == "~" + short:
            txt = "~%s();" % short
        else:
            txt = "%s%s %s(%s)%s;" % ("static " if decl["static"] else ("virtual " if decl["virtual"] else ""),
                                     decl["ret"], nm, decl["params"], " const" if decl["const"] else "")
        r = retail_by_dev.get(dva)
        rows.append((r[0] if r else None, txt, decl["access"], f["name"]))
    rows.sort(key=lambda x: (x[0] is None, x[0] or 0))
    for r, txt, access, dname in rows:
        lines.append("  %-70s // %s%s" % (txt, ("0x%08x" % r) if r else "dev only", (", " + access) if access and access != "public" else ""))
    if rows:
        lines.append("")
    # data members
    lines.append(" public:  // data (retail offsets)")
    in_union = False
    for m in merged:
        if m["union"] and not in_union:
            lines.append("  union {")
            in_union = True
        if not m["union"] and in_union:
            lines.append("  };")
            in_union = False
        if m["type"]:
            decl = cpp_type(m["type"], m["name"])
        elif m.get("type_text"):
            decl = "%s %s" % (m["type_text"], m["name"])
        else:
            decl = "unsigned char %s[0x%x]" % (m["name"], m["size"] or 0)
        if m.get("bitlen"):
            decl += " : %d" % m["bitlen"]
        note = "// 0x%03x" % m["offset"]
        if m.get("dev_offset") is not None and m["offset"] != m["dev_offset"]:
            note += " (dev 0x%03x)" % m["dev_offset"]
        note += " " + m["prov"]
        lines.append("  %s%-60s %s" % ("  " if in_union else "", decl + ";", note))
    if in_union:
        lines.append("  };")
    lines.append("};")
    if confirmed:
        lines.append("typedef char sizeof_check_%s[(sizeof(%s) == 0x%x) ? 1 : -1];" % (flat(cls), short, retail_size))
    else:
        lines.append("// sizeof(%s) expected 0x%x (unverified)" % (short, retail_size))
    lines.append("")
    for p in reversed(ns_open):
        lines.append("}  // namespace %s" % p)
    lines += ["", "#endif  // %s" % guard, ""]
    return lines


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--module", help="module key substring, e.g. DatabasePackedFile or SPProperty")
    ap.add_argument("--class", dest="classes", action="append", help="emit only these classes")
    ap.add_argument("--out", default=W("work/migrate/headers"))
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--show", help="print the retail layout of one class and exit")
    a = ap.parse_args()
    data = Data()
    T = data.types
    if a.selftest:
        bad = T.selftest()
        print("selftest: %d of %d structs do not re-lay to their PDB offsets with dev sizes" % (len(bad), len(T.structs)))
        for b in bad[:25]:
            print("  %s dev 0x%x relaid 0x%x %s" % b)
        return
    if a.show:
        for mode in ("dev", "retail"):
            L = T.layout(a.show, mode)
            print("== %s %s: size 0x%x align %d (%s)" % (a.show, mode, L["size"], L["align"], L["source"]))
            for b in L["bases"]:
                print("   base %-50s 0x%03x (0x%x)" % (b["name"], b["offset"], b["size"]))
            for m in L["members"]:
                print("   0x%03x %4d %-30s %s" % (m["offset"], m["size"] or 0, m["name"], cpp_type(m["type"] or "?")))
        return
    if not a.module:
        ap.error("--module is required")
    print("leaf table: %d types; slice views: %s; overrides: %d classes" % (
        len(data.leaf), "yes" if data.views else "none", len(data.overrides)))
    mods = data.module_functions(a.module)
    report = collections.Counter()
    for module, fns in sorted(mods.items()):
        classes = collections.defaultdict(list)
        for va, e in fns:
            if e.get("name"):
                c = data.class_of_name(e["name"])
                if c and (c.split("::")[0] in LIBRARY_NS or "<" in c):
                    report["library_instantiations"] += 1
                elif c and c in T.structs:
                    classes[c].append((va, e))
                elif c:
                    report["name_without_type"] += 1
        want = [c for c in classes if not a.classes or c in a.classes]
        print("== %s: %d functions, %d classes with a PDB type" % (module, len(fns), len(want)))
        for cls in sorted(want):
            lines = emit_class(data, module, cls, classes[cls], report, a.out)
            path = header_path(a.out, module, cls)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as f:
                f.write("\n".join(lines))
            L = T.layout(cls, "retail")
            print("   %-55s %3d fns  retail 0x%-4x  -> %s" % (cls, len(classes[cls]), L["size"] if L else 0,
                                                              os.path.relpath(path, ROOT)))
    print("classes %d: fully exact-backed %d, partly %d, re-laid only %d, with overrides %d; member conflicts %d, "
          "retail-only %d; no PDB type %d, names without type %d, template instantiations skipped %d" % (
              report["classes"], report["confirmed"], report["evidence"], report["relaid"], report["overridden"],
              report["conflicts"], report["added"], report["no_pdb"], report["name_without_type"],
              report["library_instantiations"]))


if __name__ == "__main__":
    main()
