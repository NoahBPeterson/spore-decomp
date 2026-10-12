#!/usr/bin/env python3
"""Retail sizes of the library leaf types that dev classes are built from.

Phase B (docs/migration.md, "2. headers.py") re-lays dev-PDB classes member by member with retail
sizes for leaf types (eastl containers, allocators, strings, mutexes ...).  The dev PDB sizes are
in work/devbuild/types.json; the retail sizes come from the slices under match/slices/.

This script produces the MEASURABLE part of work/migrate/retail_leaf_sizes.json:

  * dev sizes / member lists of every family member from types.json;
  * retail sizes of the slice-private struct views of each family: every body in
    work/claude/layouts/census.json whose struct name matches a family pattern is laid out with a
    small C layout evaluator (natural alignment, VC rules), and tallied by how many slices that
    use the body contain at least one BYTE-EXACT function (manifest.txt).  A body used by a
    byte-exact slice is retail-correct for the members that slice touches; the majority size over
    such bodies is the "measured_by_slices" figure;
  * the two validations (DatabasePackedFile::mpStream at 0x260, eastl::vector 0x14).

The curated parts (stride / sizeof evidence read from code, member names, rules for template
instantiations, ModAPI cross-check) live in CURATED below, each entry carrying its evidence
strings; the script merges them with what it measures and checks that the two agree.

Usage:  python3 tools/migrate/leafsizes.py            # writes work/migrate/retail_leaf_sizes.json
        python3 tools/migrate/leafsizes.py --probe 'vector|Vec'   # list bodies matching a regex
"""
import argparse, collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CENSUS = os.path.join(ROOT, "work", "claude", "layouts", "census.json")
TYPES = os.path.join(ROOT, "work", "devbuild", "types.json")
OUT = os.path.join(ROOT, "work", "migrate", "retail_leaf_sizes.json")

# ---------------------------------------------------------------------------------------------
# A small C layout evaluator for census bodies (normalised data-member lists)
# ---------------------------------------------------------------------------------------------
PRIM = {
    "char": (1, 1), "signed char": (1, 1), "unsigned char": (1, 1), "bool": (1, 1), "BOOL": (4, 4),
    "int8_t": (1, 1), "uint8_t": (1, 1), "u8": (1, 1), "byte": (1, 1), "BYTE": (1, 1), "i8": (1, 1),
    "short": (2, 2), "unsigned short": (2, 2), "int16_t": (2, 2), "uint16_t": (2, 2), "u16": (2, 2),
    "wchar_t": (2, 2), "char16": (2, 2), "WORD": (2, 2), "i16": (2, 2),
    "int": (4, 4), "unsigned": (4, 4), "unsigned int": (4, 4), "long": (4, 4), "unsigned long": (4, 4),
    "int32_t": (4, 4), "uint32_t": (4, 4), "u32": (4, 4), "i32": (4, 4), "uint": (4, 4), "DWORD": (4, 4),
    "size_t": (4, 4), "size_type": (4, 4), "float": (4, 4), "HANDLE": (4, 4), "intptr_t": (4, 4),
    "uintptr_t": (4, 4), "ptrdiff_t": (4, 4), "ulong": (4, 4), "UINT": (4, 4), "LONG": (4, 4),
    "double": (8, 8), "int64_t": (8, 8), "uint64_t": (8, 8), "u64": (8, 8), "__int64": (8, 8),
    "unsigned __int64": (8, 8), "long long": (8, 8), "unsigned long long": (8, 8), "i64": (8, 8),
}
MEMBER = re.compile(r"^(?P<ty>.+?[\s\*&])(?P<nm>[A-Za-z_]\w*)\s*(?P<arr>(\[[^\]]*\])*)\s*(=.*)?$")


def num(s):
    s = s.strip()
    if re.fullmatch(r"0[xX][0-9a-fA-F]+", s):
        return int(s, 16)
    if re.fullmatch(r"\d+", s):
        return int(s)
    m = re.fullmatch(r"\(?\s*(0[xX][0-9a-fA-F]+|\d+)\s*\)?\s*([-+*/])\s*\(?\s*(0[xX][0-9a-fA-F]+|\d+)\s*\)?", s)
    if m:
        a, op, b = int(m.group(1), 0), m.group(2), int(m.group(3), 0)
        return {"-": a - b, "+": a + b, "*": a * b, "/": a // b if b else None}[op]
    return None


class Census:
    def __init__(self):
        self.c = json.load(open(CENSUS))
        self.exact = {}
        for mf in glob.glob(os.path.join(ROOT, "match", "slices", "*", "manifest.txt")):
            sid = os.path.basename(os.path.dirname(mf))
            n = sum(1 for l in open(mf, errors="replace") if l.strip() and not l.startswith("#"))
            self.exact[sid] = n
        self._memo = {}

    def n_exact(self, slices):
        return sum(1 for s in slices if self.exact.get(s, 0) > 0)

    def body_for(self, name, sid):
        """the body of `name` visible in slice `sid` (any hash listing that slice)."""
        for h, b in self.c.get(name, {}).items():
            if sid in b["slices"]:
                return h, b
        return None, None

    def layout(self, name, h, sid, depth=0):
        """(size, align, [(member, offset, size)]) or None when some member type is unknown."""
        key = (name, h, sid)
        if key in self._memo:
            return self._memo[key]
        self._memo[key] = None
        if depth > 6:
            return None
        b = self.c[name][h]
        off, al, mem = 0, 1, []
        for line in b["members"]:
            line = line.strip()
            if not line or ":" in line.split("[")[0].split("=")[0].replace("::", ""):
                self._memo[key] = None      # bitfield: skip
                return None
            for decl in self._split(line):
                m = MEMBER.match(decl)
                if not m:
                    return None
                ty, nm, arr = m.group("ty").strip(), m.group("nm"), m.group("arr")
                ty = re.sub(r"\b(const|volatile|struct|class|union|mutable)\b", "", ty).strip()
                ty = re.sub(r"\s+", " ", ty)
                if "*" in ty or "&" in ty or ty.startswith("void(") or "(*" in decl:
                    sz, a = 4, 4
                elif ty in PRIM:
                    sz, a = PRIM[ty]
                else:
                    base = ty.split("<")[0].strip()
                    if "<" in ty or base not in self.c:
                        return None
                    h2, b2 = self.body_for(base, sid)
                    if b2 is None:
                        return None
                    r = self.layout(base, h2, sid, depth + 1)
                    if r is None:
                        return None
                    sz, a = r[0], r[1]
                cnt = 1
                for dim in re.findall(r"\[([^\]]*)\]", arr):
                    v = num(dim)
                    if v is None:
                        return None
                    cnt *= v
                off = (off + a - 1) // a * a
                mem.append((nm, off, sz * cnt))
                off += sz * cnt
                al = max(al, a)
        size = (off + al - 1) // al * al
        r = (size, al, mem)
        self._memo[key] = r
        return r

    @staticmethod
    def _split(line):
        # 'uint32_t a, b' -> two declarations; leave template commas alone
        m = re.match(r"^([A-Za-z_][\w: ]*?[\s\*])([A-Za-z_]\w*(\[[^\]]*\])*(\s*,\s*\**[A-Za-z_]\w*(\[[^\]]*\])*)+)$", line)
        if m and "<" not in line:
            ty = m.group(1)
            return [ty + p.strip() for p in m.group(2).split(",")]
        return [line]

    def probe(self, pattern, exact_only=False):
        """[(name, hash, size, n_slices, n_exact_slices, members)] for struct names matching."""
        rx = re.compile(pattern)
        out = []
        for name, bodies in self.c.items():
            if not rx.search(name):
                continue
            for h, b in bodies.items():
                # evaluate against the first slice that sees the body (nested types resolved there)
                res = None
                for sid in b["slices"]:
                    res = self.layout(name, h, sid)
                    if res:
                        break
                ne = self.n_exact(b["slices"])
                if exact_only and not ne:
                    continue
                out.append((name, h, res[0] if res else None, len(b["slices"]), ne, b["members"], res[2] if res else None))
        return out




# ---------------------------------------------------------------------------------------------
# Dev-type access and the retail re-layout engine
# ---------------------------------------------------------------------------------------------
class Dev:
    def __init__(self):
        self.t = json.load(open(TYPES))["structs"]
        self._al = {}

    def size(self, name):
        return self.t[name]["size"]

    def desc_size_align(self, desc, msize=None):
        """(size, align) of a typedesc in the DEV build."""
        if desc.startswith("ptr:") or desc == "func":
            return 4, 4
        if desc.startswith("struct:"):
            n = desc[7:]
            return self.size(n), self.align(n)
        if desc.startswith("arr:"):
            _, cnt, esz, rest = desc.split(":", 3)
            a = self.desc_size_align(rest, int(esz))[1]
            return int(cnt) * int(esz), a
        sz = msize or 4
        return sz, min(sz, 8) if sz in (1, 2, 4, 8) else 4

    def align(self, name):
        if name in self._al:
            return self._al[name]
        self._al[name] = 1
        s = self.t.get(name)
        a = 1
        if s:
            if s.get("vfptr"):
                a = 4
            for m in s["members"]:
                a = max(a, self.desc_size_align(m[2], m[5])[1])
            for b in s["bases"]:
                a = max(a, self.desc_size_align(b[0], b[2])[1])
        self._al[name] = a
        return a


ALLOC_VEC = re.compile(r"^(eastl::allocator|eastl::sp_vector_allocator|SP::SP_STL_\w+)$")
CORE_ALLOC = "EA::Allocator::EASTLCoreAllocator"
FIXED_VALUES = {            # retail sizes taken straight from byte-exact evidence (see CURATED)
    "EA::IO::FileStream": (0x22C, 4),
    "SP::cString": (0x14, 4),
}


class Retail:
    """Re-lay dev classes with retail leaf sizes."""

    def __init__(self, dev):
        self.d = dev
        self._memo = {}
        self._aff = {}

    # -- allocators ------------------------------------------------------------------------
    def alloc_in_vector(self, name):
        """retail size of the allocator slot of a VectorBase<T, name>; None if unknown."""
        if name == CORE_ALLOC or ALLOC_VEC.match(name):
            return 8
        m = re.match(r"^eastl::fixed_vector_allocator<[^>]*,(\d+)>$", name)
        if m and m.group(1) == "1":                 # overflow allocator (eastl::allocator -> 8) + pool pointer
            return 12
        return None

    def delta(self, name):
        """retail size minus dev size contributed by allocator-hosting leaf types inside `name`
        (None = contains something whose retail size is unknown)."""
        if name == CORE_ALLOC:
            return -4
        s = self.d.t.get(name)
        if s is None:
            return 0
        m = re.match(r"^eastl::VectorBase<", name)
        if m:
            a = [x for x in s["members"] if x[0] == "mAllocator"]
            an = a[0][2][7:] if a else None
            r = self.alloc_in_vector(an) if an else None
            return None if r is None else r - self.d.size(an)
        tot = 0
        for desc in [b[0] for b in s["bases"]] + [x[2] for x in s["members"] if x[2].startswith("struct:")]:
            if not desc.startswith("struct:"):
                continue
            child = desc[7:]
            if not (child.startswith("eastl::") or child == CORE_ALLOC or child.startswith("EA::Allocator::")):
                continue
            dd = self.delta(child)
            if dd is None:
                return None
            tot += dd
        return tot

    # -- sizes -----------------------------------------------------------------------------
    def size_align(self, name):
        if name in FIXED_VALUES:
            return FIXED_VALUES[name]
        if name.startswith("eastl::") or name == CORE_ALLOC:
            dl = self.delta(name)
            if dl is None:
                return None, self.d.align(name)
            if re.match(r"^eastl::basic_string<", name):       # dev 0x10 incl. 4-byte allocator word
                m = re.search(r",([^<>]*)>$", name)
                a = m.group(1) if m else ""
                return (0xC + (8 if a == CORE_ALLOC else 4)), 4
            return self.d.size(name) + dl, self.d.align(name)
        if not self.affected(name):                 # nothing inside changes size: keep the dev layout
            return self.d.size(name), self.d.align(name)
        lay = self.layout(name)
        return (lay["size"], lay["align"]) if lay else (None, self.d.align(name))

    def affected(self, name):
        """True when a type contains (by value) something whose retail size differs from dev."""
        if name in self._aff:
            return self._aff[name]
        self._aff[name] = False
        s = self.d.t.get(name)
        r = False
        if name in FIXED_VALUES or name == CORE_ALLOC:
            r = True
        elif s is not None and name.startswith("eastl::"):
            dl = self.delta(name)
            r = dl is None or dl != 0
        elif s is not None:
            for desc in [b[0] for b in s["bases"]] + [m[2] for m in s["members"]]:
                while desc.startswith("arr:"):
                    desc = desc.split(":", 3)[3]
                if desc.startswith("struct:") and self.affected(desc[7:]):
                    r = True
                    break
        self._aff[name] = r
        return r

    def desc_size_align(self, desc, msize):
        if desc.startswith("struct:"):
            return self.size_align(desc[7:])
        if desc.startswith("arr:"):
            _, cnt, esz, rest = desc.split(":", 3)
            sz, a = self.desc_size_align(rest, int(esz))
            return (None if sz is None else sz * int(cnt)), a
        return self.d.desc_size_align(desc, msize)

    def layout(self, name):
        if name in self._memo:
            return self._memo[name]
        self._memo[name] = None
        s = self.d.t[name]
        items = [(b[1], "base:" + b[0], b[0], b[2], None, None) for b in s["bases"]]
        items += [(m[1], m[0], m[2], m[5], m[3], m[4]) for m in s["members"]]
        items.sort(key=lambda x: x[0])
        cur = 4 if (s.get("vfptr") and not s["bases"]) else 0
        placed = []              # (dev_off, new_off, new_size)
        out = []
        maxal = 4 if s.get("vfptr") else 1
        unknown = []
        for dev_off, nm, desc, msz, bitpos, bitlen in items:
            sz, al = self.desc_size_align(desc, msz)
            if sz is None:
                unknown.append(nm)
                sz = msz
            overl = [p for p in placed if p[0] <= dev_off < p[0] + max(p[3], 1) and (p[0] != dev_off or p[3] > 0)]
            if bitlen is not None or (overl and dev_off != items[0][0]):
                p = overl[-1] if overl else placed[-1]
                new = p[1] + (dev_off - p[0])            # union / bit-field sibling: same relative place
                cur = max(cur, new + (0 if bitlen is not None else sz))
            else:
                new = (cur + al - 1) // al * al
                cur = new + sz
            placed.append((dev_off, new, sz, msz))
            maxal = max(maxal, al)
            out.append({"name": nm, "dev_off": dev_off, "retail_off": new, "retail_size": sz, "dev_size": msz})
        size = (cur + maxal - 1) // maxal * maxal
        lay = {"size": size, "align": maxal, "members": out, "unknown": unknown}
        self._memo[name] = lay
        return lay


# ---------------------------------------------------------------------------------------------
# The curated table: every entry carries its evidence.  `match` is a regex over DEV type names
# that the entry covers (family rule), `probe` a regex over slice-private struct names whose
# census bodies are tallied as "slice_views" (sanity check, not the source of truth).
# ---------------------------------------------------------------------------------------------
EX = "(byte-exact slice)"
CURATED = [
    dict(name="EA::Allocator::EASTLCoreAllocator", match=r"^EA::Allocator::EASTLCoreAllocator$", probe=r"^(CoreAllocatorAdapter|EASTLCoreAllocator|EASTLICoreAllocator)$",
         retail_size=8, align=4,
         members=[["mpCoreAllocator", 0, 4], ["mnFlags", 4, 4]], confidence="measured",
         rule="retail drops the dev-only mpName (EASTL_NAME_ENABLED is on in the dev build only): CoreAllocatorAdapter<ICoreAllocator> = {mpCoreAllocator, mnFlags}",
         evidence=[
             "s008884b0: byte-exact eastl::VectorBase<Node*,EASTLCoreAllocator>(n, alloc) at 0x888620 copies the allocator as 2 words ([eax],[eax+4]) into this+0xc/+0x10, so the vector is 0x14 (dev 0x18)",
             "s008884b0: byte-exact vector<basic_string<wchar_t,EASTLCoreAllocator>>::DoDestroyValues (0x888940) steps `add esi,0x14` per string, string = 3 ptrs + 8-byte allocator (core allocator ptr at +0xc is used for the free call)",
             "s008d81d0: byte-exact DatabasePackedFile functions place mMap (multimap, EASTLCoreAllocator) at +0x2e8 and mHeaderBlock at +0x308: the map is 0x20 (dev rbtree 0x24)",
             "work/decomp_all/c/008d0000.c FUN_008db730 (PFIndexModifiable ctor, called by byte-exact CreateIndex 0x8d8360 which allocates 0x4c): writes mAllocator.mpCoreAllocator and mAllocator.mnFlags as two consecutive words; hashtable<..,EASTLCoreAllocator> is 0x24 (dev 0x28)",
             "work/ext/EAWebKitSupportPackages/EASTLEAWebKit/local/include/EASTL/core_allocator_adapter.h:98-102: {mpCoreAllocator, mnFlags, #if EASTL_NAME_ENABLED mpName} (the slice s008884b0 compiles against these headers and is byte-exact)",
         ]),
    dict(name="eastl::allocator (and SP::SP_STL_* tag allocators, eastl::sp_vector_allocator)", match=r"^(eastl::allocator|eastl::sp_vector_allocator|SP::SP_STL_\w+)$",
         probe=r"^(allocator|sp_vector_allocator|vector_allocator|container_allocator|EASTLAllocator)$",
         retail_size=4, align=4, retail_size_by_container={"basic_string": 4, "hashtable": 4, "rbtree": 4, "list": 4, "vector/VectorBase": 8},
         members=[["mpName (dev only)", 0, 4]], confidence="measured",
         rule="no retail data members in string/hashtable/rbtree/list contexts, so the container lays out exactly as in dev (the allocator is a 4-byte tail word, padding if empty); inside eastl::vector/VectorBase the allocator slot is 8 bytes (all retail vectors are 0x14) and the two words are never written by the vector/allocator constructors (copy ctor 0x429360 is `mov eax,ecx; ret`), so the generator should name them mAllocator[2] / {mpName, mFlags} (names are the slices' guess)",
         evidence=[
             "s006aa3f0: byte-exact RegisterPropertyNameLocal (0x6aa5e0) + RegisterPropertyName use cPropertyManager maps at 0x94, 0xb4, ... 0x128, 0x148 and mLCName at 0x168: hash_map<..,eastl::allocator> stride 0x20 (= dev), string 0x10",
             "s006a11b0: byte-exact cPropertyList ctors (0x6a1b90, 0x6a1c40): vector_map<uint,Variant,less,eastl::allocator,vector<pair,eastl::allocator>> at +0x18 is 0x18 long (compare byte at +0x2c, mParent at +0x30, dev 0x2c): the vector<..,eastl::allocator> is 0x14",
             "s00609790: CookieHandler eastl::list<CookiePtr> at +0x14, next member at +0x20 -> list is 0xc (= dev)",
             "s008d81d0: HoleSet (eastl::set<HoleRecord,less,eastl::allocator>) is 0x1c inside the 0x20 PFHoleTable (= dev)",
             "s00a39ce0: hashtable<uint,pair<uint,string>,SP_STL_Sound> = 0x1c + 4-byte allocator tail (mPad34), equal to dev",
             "s004604f0: byte-exact (/Od) clear-state ctor 0x460f80 constructs vectors every 0x14 bytes and calls the empty allocator copy ctor 0x429360 on this+0xc",
             "docs/matching.md:212 and docs/Papercuts.md:191: strings are 16 bytes incl. a 4-byte allocator",
         ]),
    dict(dev_size=0x10, name="eastl::basic_string<char|wchar_t, A>", match=r"^eastl::basic_string<", probe=r"^(basic_string|string8|string16|string|WString|WStr|wstring|String8|StrKey|basic_string8|basic_string16)$",
         retail_size=0x10, align=4,
         members=[["mpBegin", 0, 4], ["mpEnd", 4, 4], ["mpCapacity", 8, 4], ["mAllocator", 0xC, 4]], confidence="measured",
         rule="size = 0xC + retail allocator word: eastl::allocator -> 4 (0x10, = dev); EASTLCoreAllocator -> 8 (0x14, dev 0x18). Character type does not matter",
         evidence=[
             "s008d81d0: DatabasePackedFile::mPath (wchar_t, eastl::allocator) at +0x20, mFile at +0x30 -> 0x10; the 0x25c/0x260 anchors of byte-exact ReadAt/GetSize/Lock only add up with 0x10",
             "s006aa3f0: byte-exact RegisterPropertyNameLocal: mLCName string at +0x168 directly after a 0x20 hash_map",
             "s008884b0: byte-exact vector<basic_string<wchar_t,EASTLCoreAllocator>> ~vector/DoDestroyValues, stride 0x14 (disassembly of 0x888940: add esi,0x14; 0x8891a0 divides by 0x14 via imul 0x66666667)",
             "docs/matching.md:212; docs/Papercuts.md:191",
         ]),
    dict(dev_size=0x10, name="eastl::vector / eastl::VectorBase<T,A>", match=r"^eastl::(vector|VectorBase)<", probe=r"^(vector|VectorBase|sp_vector|SpVector|SPVector|SpVec|Vec|SimpleVector|UIntVector|ResourceKeyVectorBase)$",
         retail_size=0x14, align=4,
         members=[["mpBegin", 0, 4], ["mpEnd", 4, 4], ["mpCapacity", 8, 4], ["mAllocator", 0xC, 8]], confidence="measured",
         rule="size = 0xC + 8 for every allocator in the pilot and in the slices seen (eastl::allocator, sp_vector_allocator, SP_STL_*, EASTLCoreAllocator); with fixed_vector_allocator<..,1> the slot is 12 (see fixed_vector). Dev: 0xC + sizeof(A): 0x10, EASTLCoreAllocator 0x18. Extra word: the vector's allocator is 8 bytes; the slices call the words {mpName, mFlags}, but for sp_vector_allocator no code reads or writes them (allocator copy ctor 0x429360 is empty), for EASTLCoreAllocator they are {mpCoreAllocator, mnFlags}",
         evidence=[
             "s004604f0: byte-exact /Od ctor 0x460f80 lays seven vectors at +0x0, +0x14, +0x28 ... with the allocator sub-object at this+0xc",
             "s008884b0: byte-exact VectorBase<Node*,EASTLCoreAllocator>::VectorBase(n,alloc) 0x888620: allocator = two words at +0xc/+0x10; vector<String> dtor stride math",
             "s006aa3f0: byte-exact cPropertyManager: mGroupIDs vector<uint,sp_vector_allocator> at 0x114, next member (hash_map) at 0x128 = 0x114 + 0x14",
             "s00844270: cArguments (three vector<..,sp_vector_allocator> + 2 ints) is 0x44 in a byte-exact slice, dev 0x38 (3*0x10+8)",
             "s00401b80, s00f78a60, s00a9f170, s00d60ce0, s00725e40 (comments: 'EASTL vectors are 0x14 bytes here, 0x10 in the 2008 PDB'); 24+ slices define sp_vector_allocator as 8 bytes",
         ]),
    dict(dev_size=0x14, name="eastl::fixed_vector<T,N,bOverflow> (header part)", match=r"^eastl::fixed_vector<", probe=r"^(fixed_vector|FixedVecHdr|FixedVector|fixed_vector_base|fixed_vector_allocator)$",
         retail_size=None, align=4, dev_header="0x14 with overflow (vector 0xC + overflow allocator 4 + pool ptr 4), 0x10 without",
         members=[["mpBegin", 0, 4], ["mpEnd", 4, 4], ["mpCapacity", 8, 4], ["mOverflowAllocator", 0xC, 4], ["mpPoolBegin", 0x10, 4],
                  ["(extra word, never written by the ctor)", 0x14, 4], ["mBuffer", 0x18, "N*sizeof(T); offset = align(0x18, alignof(T))"]],
         confidence="measured",
         rule="WITH overflow (bOverflow=1, eastl::allocator overflow): header 0x18 (dev 0x14), buffer at +0x18, total = 0x18 + N*sizeof(T) (fixed_vector<T*,8> = 0x38). WITHOUT overflow (bOverflow=0): retail header not measured -> unknown (dev 0x10)",
         evidence=[
             "retail bytes 0x41cfe0 (ctor used by s00532f80) and 0x533360 (ctor used by s00447150): `add eax,0x18` = buffer; mpBegin=mpEnd=this+0x18; mpPoolBegin stored at this+0x10; mpCapacity = begin + N*4 (add ecx,0x20 for N=8); nothing writes +0x14",
             "docs/Papercuts.md:333: s00447150 local fixed_vector<T*,8> is 0x38 bytes, ctor sets mpBegin to the inline buffer at +0x18",
             "s0041d490 (24 exact functions): 'FixedVecHdr' {b,e,c, PoolAlloc, pad} = 0x18",
             "s00532f80's private view (3 ptrs + 8-byte fixed_vector_allocator, buffer 'right after') is misleading: the ctor it reproduces puts the buffer at +0x18",
         ]),
    dict(dev_size=0x20, name="eastl::hashtable / hash_map / hash_set / hash_multimap (hashtable<K,V,A,...>)", match=r"^eastl::(hashtable|hash_map|hash_set|hash_multimap|hash_multiset)<", probe=r"^(hashtable|Hashtable|HashTable|HashMap|HashMapBase|hash_map)$",
         retail_size=None, align=4,
         members=[["mHashCodeBase (empty functors)", 0, 4], ["mpBucketArray", 4, 4], ["mnBucketCount", 8, 4], ["mnElementCount", 0xC, 4], ["mRehashPolicy (prime_rehash_policy: mfMaxLoadFactor, mfGrowthFactor, mnNextResize)", 0x10, 0xC], ["mAllocator", 0x1C, "4 (eastl::allocator) | 8 (EASTLCoreAllocator)"]],
         confidence="measured",
         rule="with eastl::allocator: 0x20 (= dev). With EA::Allocator::EASTLCoreAllocator: 0x24 (dev 0x28): mAllocator at +0x1C is {mpCoreAllocator, mnFlags} (8 bytes). Field order is the dev order (bucket array at +4); the ctor FUN_008db730 writes mfMaxLoadFactor=1.0, mfGrowthFactor=2.0, allocator, mnElementCount, mnNextResize, mnBucketCount=1, mpBucketArray=&shared empty array. prime_rehash_policy is 0xC in retail",
         evidence=[
             "s006aa3f0: byte-exact RegisterPropertyNameLocal: eastl::allocator hash_maps are 0x20 apart (0x128, 0x148 -> 0x168)",
             "s008d81d0 + work/decomp_all/c/008d0000.c FUN_008db730: PFIndexModifiable (alloc 0x4c in byte-exact CreateIndex): hash_map<Key,PFRecordInfo,..,EASTLCoreAllocator> = 0x24 (bucket array at +0x2c, count +0x30, 0x4c end) with the embedded pool allocator (0x20 bytes at +0x8) structural, not leaf",
             "s008884b0: byte-exact DoFreeNodes/DoRehash of hashtable<uint,pair<..>,EASTLCoreAllocator>",
             "s004cd1b0, s004e01d0, s004e2f20 ...: prime_rehash_policy {float,float,uint32} = 0xC in 18 byte-exact slices",
         ]),
    dict(dev_size=0x1C, name="eastl::rbtree / map / multimap / set / multiset", match=r"^eastl::(rbtree|map|multimap|set|multiset)<", probe=r"^(rbtree|RBTree|RbTree|map|RecMap|RbTreeData)$",
         retail_size=None, align=4,
         members=[["mCompare (empty, padded)", 0, 4], ["mAnchor (rbtree_node_base: right,left,parent,color)", 4, 0x10], ["mnSize", 0x14, 4], ["mAllocator", 0x18, "4 (eastl::allocator) | 8 (EASTLCoreAllocator)"]],
         confidence="measured",
         rule="with eastl::allocator: 0x1c (= dev). With EASTLCoreAllocator: 0x20 (dev 0x24). rbtree_node_base is 0x10 (44 slices, 26 with exact functions)",
         evidence=[
             "s008d81d0: RecMap {cmp, anchor 0x10, mnSize, mpAlloc, mnFlags} at +0x2e8 up to mHeaderBlock +0x308 in byte-exact functions = 0x20 for multimap<Key,PFRecordBase*,less,EASTLCoreAllocator>",
             "s008d81d0: HoleSet = 0x20 PFHoleTable (extent + set<HoleRecord,less,eastl::allocator> 0x1c)",
             "s008de020: Manager mDatabaseList at +0x2c where dev has the set<ChangeNotificationInfo,..,EASTLCoreAllocator> end at 0x30 (set 0x20 instead of 0x24)",
         ]),
    dict(dev_size=0x14, name="eastl::vector_map / vector_set", match=r"^eastl::(vector_map|vector_set)<", probe=r"^(vector_map|vector_set)$",
         retail_size=None, align=4, confidence="measured",
         rule="= retail vector (0x14) + the comparator byte padded to 4 -> 0x18 for vector_map<K,V,less,eastl::allocator,vector<..,eastl::allocator>> (dev 0x14). Fixed-vector-backed instantiations: fixed_vector rule + comparator",
         members=[["(base) vector", 0, 0x14], ["mCompare", 0x14, 4]],
         evidence=["s006a11b0: byte-exact cPropertyList ctors: mPropertyMap at +0x18, mCompare byte at +0x2c, mParent +0x30, mModificationCount +0x34 (class 0x38 without the dev-only mDescriptions)",
                   "work/ext Spore-ModAPI PropertyList ASSERT_SIZE 0x38 (cross-check only)"]),
    dict(dev_size=0xC, name="eastl::list<T,A>", match=r"^eastl::(list|ListBase)<", probe=r"^(list|ListBase)$",
         retail_size=0xC, align=4, members=[["mNode (mpNext,mpPrev)", 0, 8], ["mAllocator", 8, 4]], confidence="measured",
         rule="0xC with eastl::allocator (= dev); node = {mpNext, mpPrev, value}; EASTLCoreAllocator-lists and fixed_node_pool lists not measured",
         evidence=["s00609790 (32 exact functions): CookieHandler eastl::list<CookiePtr> at +0x14, mNumCookies at +0x20",
                   "s00fdeac0 / s00fe0f40 / s00fe0570 (no exact functions): list<ResourceKey> at +0x170, list<bool> at +0x17c"]),
    dict(dev_size=8, name="eastl::intrusive_list / intrusive_list_node", match=r"^eastl::intrusive_list", probe=r"^(intrusive_list|intrusive_list_base|intrusive_list_node|IntrusiveList|IntrusiveListHead)$",
         retail_size=8, align=4, members=[["mpNext", 0, 4], ["mpPrev", 4, 4]], confidence="measured",
         rule="anchor/node = two pointers",
         evidence=["s00691680, s00999110, s00f78a60: IntrusiveList anchors 8 bytes; 'intrusive_list_node' views in 3 slices (2 with exact functions)"]),
    dict(dev_size=0x2C, name="eastl::deque<T,A,N>", match=r"^eastl::(deque|DequeBase)<", probe=r"^(deque|DequeBase|Deque|DequeIterator)$",
         retail_size=None, align=4, confidence="unknown",
         rule="DequeIterator is 0x10 (11 exact slices); the DequeBase views without allocator are 0x28 in exact slices but none shows the tail allocator word; dev 0x2c = 0x28 + 4. Not measured",
         members=[["mpPtrArray", 0, 4], ["mnPtrArraySize", 4, 4], ["mItBegin", 8, 0x10], ["mItEnd", 0x18, 0x10], ["mAllocator (dev 4)", 0x28, "unknown"]],
         evidence=["slice_views only (no enclosing-offset evidence found)"]),
    dict(name="EA::AutoRefCount<T> / EA::COM::AutoRefCount<T> / EA::IntrusivePtr / eastl::intrusive_ptr", match=r"^(EA::AutoRefCount<|EA::COM::AutoRefCount<|EA::IntrusivePtr<|eastl::intrusive_ptr<)", probe=r"^(AutoRef|AutoRefCount|IntrusivePtr|intrusive_ptr|RefPtr)$",
         retail_size=4, align=4, members=[["mp", 0, 4]], confidence="measured", rule="one pointer",
         evidence=["s008d81d0: byte-exact GetSize/Reset call through DatabasePackedFile+0x260 (AutoRef { IStream* p })", "AutoRefCount: 272 slice uses (census), all single-pointer bodies"]),
    dict(dev_size=0x14, name="EA::Variant", match=r"^EA::Variant(::(Generic|Pointer))?$", probe=r"^(Variant|EVariant|EA_Variant)$", retail_size=0x14, align=4,
         members=[["mData (union, 16 bytes)", 0, 0x10], ["mFlags", 0x10, 2], ["mTypeId", 0x12, 2]], confidence="measured",
         rule="same as dev",
         evidence=["s006a11b0: byte-exact cPropertyList::DeepAdd/GetProperty use pair<uint,Variant> with 0x18 stride (key 4 + Variant 0x14), eastl::lower_bound 0x612db0 'a 0x18-stride instance'", "ModAPI PropertyList / Property.h sizes (cross-check only)"]),
    dict(name="SP::cString", match=r"^SP::cString$", probe=r"^(cString|CString)$", retail_size=0x14, align=4,
         members=[["mpTableResource", 0, 4], ["mpLocalString", 4, 4], ["mpSourceCStr", 8, 4], ["mPlaceholderId", 0xC, 4], ["mbHasTokens", 0x10, 1], ["mField11 (role unknown)", 0x11, 1]], confidence="measured",
         rule="dev's mTableId/mInstanceId (0x14/0x18) do not exist in retail; the last two bytes after mPlaceholderId are two bools",
         evidence=["docs/Papercuts.md:347: s00ee16f0/s00ee4390 frame only fits 0x14", "s006b47a0 (13 exact functions): member view of the 0x14 body", "census: cString body 'uint32_t pad[5]' in 23 slices with exact functions (s0059e360, s005cb060, ...)", "docs/migration.md:139"]),
    dict(name="EA::Thread::Mutex / EAMutexData", match=r"^(EA::Thread::Mutex|EAMutexData)$", probe=r"^(Mutex|Mutex2|EAMutex|EAMutexData)$", retail_size=0x30, align=8,
         members=[["mData", 0, 0x20], ["mnLockCount", 0x20, 4], ["mbIntraProcess", 0x24, 1], ["mThreadId", 0x28, 4]], confidence="measured",
         rule="same as dev (alignment 8 because of unsigned __int64 mData[4]; this absorbs the +4 FileStream growth in DatabasePackedFile)",
         evidence=["s008d81d0: byte-exact Lock/ReadAt use mMutex at +0x270 and mFileMutex at +0x2a0 (0x30 apart), mpIndex +0x2d0", "ModAPI Mutex.h ASSERT_SIZE 0x30 (cross-check only)"]),
    dict(name="EA::Thread::Futex", match=r"^EA::Thread::Futex$", probe=r"^(Futex|AutoFutex)$", dev_size=None, retail_size=0x18, align=4,
         members=[["mCS (CRITICAL_SECTION)", 0, 0x18]], confidence="inferred",
         rule="dev PDB has no EA::Thread::Futex type (only FutexFactory); retail Futex is a Win32 CRITICAL_SECTION (6 words)",
         evidence=["s0060a720 (21 exact), s0060b730 (21), s0060c780 (16): Futex { uint32_t mCS[6] } views"]),
    dict(name="EA::IO::FileStream", match=r"^EA::IO::FileStream$", probe=r"^(FileStream|FileStream_)$", retail_size=0x22C, align=4,
         members=[["(vptr IStream)", 0, 4], ["mhFile", 4, 4], ["mpPath16[260]", 8, 0x208], ["mnRefCount", 0x210, 4], ["mnAccessFlags", 0x214, 4], ["mnCD", 0x218, 4], ["mnSharing", 0x21C, 4], ["mnUsageHints", 0x220, 4], ["mnLastError", 0x224, 4], ["mnSize (retail only: cached size, -1 unknown, -2 lazy)", 0x228, 4]],
         confidence="measured", rule="dev 0x228 + the cached-size word mnSize at +0x228",
         evidence=["s00931460 (28 exact functions): ctor 0x931da0 and GetSize 0x931b70 set/read mnSize at +0x228", "work/decomp_all/c/008d0000.c FUN_008dcea0 (PFRecordWrite ctor): FileStream at +0x48, mbTriedToCreateFile at +0x274, openCount +0x278; byte-exact CreateRecordWrite allocates 0x27c (dev 0x278)", "s007c2ab0 / s00632780: views of 0x22c", "ModAPI FileStream ASSERT_SIZE 0x22C (cross-check only)"]),
    dict(name="EA::ResourceMan::Key / ResourceKey", match=r"^EA::ResourceMan::Key$", probe=r"^(Key|ResourceKey)$", retail_size=0xC, align=4,
         members=[["mInstance", 0, 4], ["mType", 4, 4], ["mGroup", 8, 4]], confidence="measured", rule="same as dev",
         evidence=["s008de020: ReadKey (byte-exact family) writes mType/mGroup/mInstance at +4/+8/+0", "census: ResourceKey 174 slice uses"]),
    dict(name="EA::ResourceMan::Resource", match=r"^EA::ResourceMan::Resource$", probe=r"^(Resource|ResourceBase|cResourceBase)$", retail_size=0x14, align=4,
         members=[["(vptr IUnknown32)", 0, 4], ["mRefCount", 4, 4], ["mKey", 8, 0xC]], confidence="measured", rule="same as dev",
         evidence=["s006a11b0: byte-exact cPropertyList ctors (0x6a1b90/0x6a1c40) init the resource base; cResourceBase view has mKeyGroup/mReleaseCallback", "ModAPI ResourceObject ASSERT_SIZE 0x14 (cross-check only)"]),
    dict(name="SP::cResourceBase", match=r"^SP::cResourceBase$", probe=r"^(cResourceBase)$", retail_size=0x18, align=4,
         members=[["(base) EA::ResourceMan::Resource", 0, 0x14], ["mReleaseCallback", 0x14, 4]], confidence="measured", rule="same as dev",
         evidence=["s006a11b0: byte-exact cPropertyList ctors: cResourceBase ends at +0x18 where mPropertyMap starts (dev 0x18 too)"]),
    dict(name="EA::IO::MemoryStream", match=r"^EA::IO::MemoryStream$", probe=r"^(MemoryStream|MemStream)$", retail_size=0x24, align=4,
         members=[["(vptr IStream)", 0, 4], ["mpSharedPointer", 4, 4], ["mnRefCount", 8, 4], ["mnSize", 0xC, 4], ["mnCapacity", 0x10, 4], ["mnPosition", 0x14, 4], ["mbResizeEnabled", 0x18, 1], ["mfResizeFactor", 0x1C, 4], ["mnResizeIncrement", 0x20, 4]],
         confidence="measured", rule="same as dev",
         evidence=["work/decomp_all/c/008d0000.c FUN_008dcea0 (PFRecordWrite ctor): MemoryStream at +0x24, FileStream at +0x48 (0x24 apart)", "s006c0db0 / s006bfda0: MemoryStream view 0x24 (ba3f667e6f); ModAPI MemoryStream ASSERT_SIZE 0x24 (cross-check only)"]),
    dict(name="eastl::rbtree_node_base", match=r"^eastl::rbtree_node_base$", probe=r"^(rbtree_node_base)$", retail_size=0x10, align=4,
         members=[["mpNodeRight", 0, 4], ["mpNodeLeft", 4, 4], ["mpNodeParent", 8, 4], ["mColor", 0xC, 1]], confidence="measured", rule="same as dev",
         evidence=["census: rbtree_node_base 44 slices, 26 with exact functions; s008d81d0 RbAnchor {right,left,parent,color} = 0x10 inside the 0x20 RecMap"]),
    dict(name="EA::Allocator::ZoneObject / EA::COM::IUnknown32 / EA::IO::IStream / interfaces", match=r"^(EA::Allocator::ZoneObject|EA::COM::IUnknown32|EA::COM::IRefCount|EA::IO::IStream|EA::Messaging::IHandler|EA::Messaging::IHandlerRC|SP::cIPropertyManager|EA::ArgScript::cState)$", probe=r"^(ZoneObject|cZoneObject)$",
         retail_size=4, align=4, members=[["vftable", 0, 4]], confidence="measured", rule="one vptr each (cState: mStateID? view 'cState {uint32_t mStateID}')",
         evidence=["s008d81d0: DBase {vt0, vt4, mRefCount@8} = ZoneObject + IUnknown32 + AtomicInt = 0xc"]),
    dict(dev_size=8, name="EA::RefCounted<ZoneObject,AtomicInt<int>,1> / EA::ResourceMan::Record / Factory", match=r"^(EA::RefCounted<EA::Allocator::ZoneObject,EA::Thread::AtomicInt<int>,1>|EA::ResourceMan::Record|EA::ResourceMan::Factory)$", probe=r"^(RefCounted|DefaultRefCounted)$",
         retail_size=8, align=4, members=[["(vptr)", 0, 4], ["mRefCount", 4, 4]], confidence="measured", rule="vptr + int refcount",
         evidence=["work/decomp_all/c/008d0000.c FUN_008dcea0 (PFRecordWrite ctor, called by byte-exact CreateRecordWrite): param_1[0]=vtbl, param_1[1]=0 refcount, param_1[2]=record type (PFRecordBase members start at +8)"]),
    dict(name="EA::Thread::AtomicInt<int>", match=r"^EA::Thread::AtomicInt<(int|unsigned int)>$", probe=r"^AtomicInt$", retail_size=4, align=4, members=[["mValue", 0, 4]], confidence="measured", rule="same as dev",
         evidence=["census AtomicInt bodies: 11 slices (9 with exact functions), all 4 bytes"]),
    dict(name="eastl::prime_rehash_policy", match=r"^eastl::prime_rehash_policy$", probe=r"^(prime_rehash_policy|RehashPolicy)$", retail_size=0xC, align=4,
         members=[["mfMaxLoadFactor", 0, 4], ["mfGrowthFactor", 4, 4], ["mnNextResize", 8, 4]], confidence="measured", rule="same as dev",
         evidence=["census: prime_rehash_policy 22 slices, 18 with exact functions, all 0xC"]),
    dict(dev_size=1, name="eastl functors/tag structs (hash<>, equal_to<>, less<>, use_first<>, mod_range_hashing, binary_function<>, map_value_compare<>, hash_code_base<>, rehash_base<>, rb_base<>)",
         match=r"^eastl::(hash|equal_to|less|use_first|use_self|mod_range_hashing|binary_function|map_value_compare|rehash_base|rb_base|default_ranged_hash|hash_code_base)(<|$)", probe=r"^(hash|equal_to|less)$", retail_size=1, align=1, confidence="inferred",
         rule="empty classes (size 1); they only appear as bases (EBO) or padded tail members of the container families above, which already account for them. eastl::hash_code_base<...> is 4 in dev (padded functor set) and in the hashtable views (first word of the hashtable)",
         evidence=["s006aa3f0 / hash maps: first word of every retail hash_map is padding (MapNameToID views 'char pad0[4]; void** mpBucketArray')"]),
    dict(name="EA::ResourceMan::PFRecordInfo", match=r"^EA::ResourceMan::PFRecordInfo$", probe=r"^(PFRecordInfo|IdxEntry)$", retail_size=0x10, align=4,
         members=[["mnPosition", 0, 4], ["mnSize", 4, 4], ["mnSizeDecompressed", 8, 4], ["mnCompressionType", 0xC, 2], ["mbCommitted", 0xE, 1]], confidence="measured", rule="same as dev",
         evidence=["s008d81d0: IdxEntry {pos,size,usize,short flags,char compressed} = 0x10 (2 slices, exact)", "ModAPI RecordInfo ASSERT_SIZE 0x10 (cross-check only)"]),
    dict(name="EA::ResourceMan::PFHoleTable", match=r"^EA::ResourceMan::PFHoleTable$", probe=r"^(HoleSet|PFHoleTable)$", retail_size=0x20, align=4,
         members=[["mExtent", 0, 4], ["mHoles (set<HoleRecord,less,eastl::allocator>)", 4, 0x1C]], confidence="measured", rule="same as dev (retail DBPF views call the 0x20 object HoleSet and put the extent/ratio words before it)",
         evidence=["s008d81d0: HoleSet {int, 0x1c} = 0x20; mActive at +0x334 {mExtent, mRatio} then HoleSet at +0x33c, second HoleSet at +0x35c"]),
]

# Things that are NOT leaf types but changed between dev and retail (the generator needs them as
# class-level deltas, listed here so nobody mistakes them for leaf shifts).
STRUCTURAL_DELTAS = [
    {"class": "EA::ResourceMan::PFDatabaseHeader", "dev": 0x20, "retail": 0x28, "evidence": "s008d81d0: PFHeader {uint32_t f[10]} in 2 slices (exact); DatabasePackedFile mbHeaderHasChanged 0x328 -> 0x330"},
    {"class": "EA::ResourceMan::DatabasePackedFile", "what": "retail has one extra 4-byte word between mnUserVersionMinor (+0x2dc) and mfMinRatioToUseCompression (+0x2e4); slices call it mbEnableCompression at +0x2e0", "evidence": "s008d81d0 members at 0x2e0 (bool) / 0x2e4 (float) / 0x2e8 (map); ModAPI DatabasePackedFile ASSERT_SIZE 0x388 (cross-check only)"},
    {"class": "EA::ResourceMan::PFIndexModifiable", "dev": 0x30, "retail": 0x4c, "what": "retail embeds a 0x20-byte pool allocator at +0x8 before the hash_map (mItemsMap at +0x28)", "evidence": "work/decomp_all/c/008d0000.c FUN_008db730: FUN_00925f30(param_2,0x80,0x20), mAllocator.mpCoreAllocator = &this->mAllocator; byte-exact CreateIndex allocates 0x4c"},
    {"class": "EA::ResourceMan::PFRecordRead", "dev": 0x68, "retail": 0x70, "what": "+8 not explained by any leaf type (StreamSub has mpReadBuffer/mnBufferOffset/field44 extras)", "evidence": "s008d81d0 byte-exact CreateRecordRead* allocate 0x70"},
    {"class": "EA::ResourceMan::PFRecordWrite", "dev": 0x278, "retail": 0x27C, "what": "fully explained by FileStream +4", "evidence": "s008d81d0 byte-exact CreateRecordWrite allocates 0x27c"},
    {"class": "SP::cPropertyList", "dev": 0x54, "retail": 0x38, "what": "dev-only mDescriptions hash_map (0x20) at +0x34 is absent in retail; the rest is explained by vector_map +4", "evidence": "s006a11b0 header comment + byte-exact ctors"},
    {"class": "SP::cPropertyManager", "what": "Factory subobject at +4 and embedded property list at +0x3c shift everything by +4 / +0x20; leaf deltas inside: mGroupIDs vector +4", "evidence": "s006aa3f0 (3 exact), docs/migration.md"},
    {"class": "EA::ResourceMan::Manager", "what": "retail has +0x10 more before mpCompressorArray (+0x9c retail vs 0x9c dev even though sets/hash_maps shrank by 4 each) and +0x20 before mNameMutex (+0x148 vs 0x128): structural, unexplained by leaf sizes", "evidence": "s008de020 (6 exact functions)"},
]

MODAPI_SAYS = {   # work/ext/Spore-ModAPI ASSERT_SIZE lines; cross-check ONLY, never a source
    "EA::IO::FileStream": 0x22C, "EA::Thread::Mutex": 0x30, "EA::IO::MemoryStream": 0x24, "SP::cPropertyList (App::PropertyList)": 0x38,
    "EA::ResourceMan::DatabasePackedFile": 0x388, "EA::ResourceMan::PFRecordWrite": 0x27C, "EA::ResourceMan::PFRecordRead": 0x70,
    "EA::ResourceMan::Database": 0xC, "EA::ResourceMan::PFRecordInfo (RecordInfo)": 0x10, "EA::ResourceMan::Resource (ResourceObject)": 0x14,
    "EA::ResourceMan::Key (ResourceKey)": 0xC, "SP::cString (LocalizedString)": 0x14, "eastl::fixed_string<char16_t,32>": 0x54,
    "App::cPropManager (SP::cPropertyManager)": 0x1EC,
}

PILOT_ROOTS = r"^(EA::ResourceMan::(DatabasePackedFile|PFIndexModifiable|PFIndex|PFRecordInfo|PFHoleTable|PFRecordRead|PFRecordWrite|PFRecordBase|Database|Manager|PFDatabaseHeader)|SP::(cPropertyList|cDirectPropertyList|cPropertyManager))$"


def pilot_closure(dev):
    seen = {}

    def visit(n, depth):
        if n in seen or n not in dev.t:
            return
        seen[n] = depth
        s = dev.t[n]
        for desc in [m[2] for m in s["members"]] + [b[0] for b in s["bases"]]:
            d = desc
            while d.startswith("arr:"):
                d = d.split(":", 3)[3]
            if d.startswith("struct:"):
                visit(d[7:], depth + 1)
    for r in [n for n in dev.t if re.match(PILOT_ROOTS, n)]:
        visit(r, 0)
    return seen


def build(cen):
    dev = Dev()
    ret = Retail(dev)
    closure = pilot_closure(dev)
    entries = []
    for e in CURATED:
        rx = re.compile(e["match"])
        dev_names = sorted(n for n in dev.t if rx.search(n))
        pil = [n for n in dev_names if n in closure]
        row = {"name": e["name"], "dev_size": None, "retail_size": e.get("retail_size"), "align": e["align"],
               "members": e.get("members"), "evidence": e["evidence"], "confidence": e["confidence"], "rule": e.get("rule", "")}
        if "retail_size_by_container" in e:
            row["retail_size_by_container"] = e["retail_size_by_container"]
        if "dev_header" in e:
            row["dev_header"] = e["dev_header"]
        if dev_names:
            sizes = sorted({dev.size(n) for n in dev_names})
            row["dev_size"] = sizes[0] if len(sizes) == 1 else e.get("dev_size")
            row["dev_size_note"] = None if len(sizes) == 1 else "dev_size is the canonical instantiation (eastl::allocator / smallest); container sizes vary with the element/buffer/allocator, see dev_sizes_seen"
            row["dev_sizes_seen"] = sizes if len(sizes) > 1 else None
        elif "dev_size" in e:
            row["dev_size"] = e["dev_size"]
        row["dev_instantiations_total"] = len(dev_names)
        # retail size per pilot instantiation computed by the rules in Retail (family -> concrete)
        inst = []
        for n in pil:
            if n.startswith("eastl::") or n == CORE_ALLOC:
                sz, _ = ret.size_align(n)
                inst.append({"dev_type": n, "dev_size": dev.size(n), "retail_size": sz})
        if inst:
            row["pilot_instantiations"] = inst
        # slice views
        views = collections.defaultdict(lambda: [0, 0, []])
        for name, h, sz, ns, ne, mem, _ in cen.probe(e["probe"]):
            if sz is None:
                continue
            v = views[sz]
            v[0] += 1
            v[1] += ne
            if len(v[2]) < 3 and ne:
                v[2].append("%s/%s" % (name, h))
        row["slice_views"] = {hex(k): {"bodies": v[0], "exact_slices": v[1], "examples": v[2]} for k, v in sorted(views.items(), key=lambda kv: -kv[1][1])[:6]}
        if row["retail_size"] is None and not (e["confidence"] == "unknown"):
            row["retail_size_rule"] = "per instantiation (see rule / pilot_instantiations)"
        if e["confidence"] == "unknown":
            row["retail_size"] = None
        entries.append(row)

    # ---- validations ---------------------------------------------------------------------
    val = {}
    dbpf = "EA::ResourceMan::DatabasePackedFile"
    lay = ret.layout(dbpf)
    by = {m["name"]: m for m in lay["members"]}
    exp = {"mpStream": 0x260, "mMutex": 0x270, "mFileMutex": 0x2A0, "mpIndex": 0x2D0, "mnUserVersionMinor": 0x2DC}
    val["DatabasePackedFile"] = {
        "mpStream": {"dev": dev.t[dbpf]["members"][[m[0] for m in dev.t[dbpf]["members"]].index("mpStream")][1], "recomputed": by["mpStream"]["retail_off"], "expected": 0x260,
                     "ok": by["mpStream"]["retail_off"] == 0x260,
                     "why": "mFile (EA::IO::FileStream) grows 0x228 -> 0x22c (mnSize); mPath string stays 0x10"},
        "other_members_checked_against_byte_exact_slice_s008d81d0": {k: {"recomputed": by[k]["retail_off"], "expected": v, "ok": by[k]["retail_off"] == v} for k, v in exp.items()},
        "members_after_the_structural_deltas_listed_in_structural_deltas": {k: by[k]["retail_off"] for k in ("mOpenRecordMultiMap", "mHeader", "mbHeaderHasChanged", "mpManager")},
        "recomputed_class_size": lay["size"], "dev_class_size": dev.size(dbpf), "unknown_leaf_members": lay["unknown"],
    }
    vecs = {n: ret.size_align(n)[0] for n in dev.t if n.startswith("eastl::vector<") and n in closure}
    allvec = {n: ret.size_align(n)[0] for n in dev.t if re.match(r"^eastl::vector<", n)}
    val["vector"] = {
        "pilot_vector_instantiations": [{"dev_type": n, "dev_size": dev.size(n), "recomputed_retail": s} for n, s in sorted(vecs.items())],
        "all_dev_vector_instantiations": len(allvec),
        "retail_size_histogram_over_all_dev_vectors": dict(collections.Counter(hex(s) if s is not None else "unknown" for s in allvec.values())),
        "ok_pilot": all(s in (0x14,) for n, s in vecs.items() if "EASTLCoreAllocator" not in n and "pair<EA::COM" not in n),
        "note": "EASTLCoreAllocator vector<pair<AutoRefCount<Cache>,int>> is 0x14 as well (0xC + 8)",
    }
    # more cross-checks against byte-exact slices
    def rs(n):
        return ret.size_align(n)[0]
    cp = ret.layout("SP::cPropertyList")
    cpm = {m["name"]: m["retail_off"] for m in cp["members"]}
    cargs = ret.layout("EA::ArgScript::cArguments")
    rec = [n for n in dev.t if n.startswith("eastl::multimap<EA::ResourceMan::Key,EA::ResourceMan::PFRecordBase")][0]
    val["cross_checks"] = {
        "SP::cPropertyList.mParent (retail +0x30 in s006a11b0 exact ctors)": {"recomputed": cpm.get("mParent"), "ok": cpm.get("mParent") == 0x30},
        "SP::cPropertyList.mModificationCount (+0x34)": {"recomputed": cpm.get("mModificationCount"), "ok": cpm.get("mModificationCount") == 0x34},
        "EA::ArgScript::cArguments size (0x44 in byte-exact s00844270)": {"recomputed": cargs["size"], "ok": cargs["size"] == 0x44},
        "multimap<Key,PFRecordBase*,less,EASTLCoreAllocator> (0x20 in s008d81d0)": {"recomputed": rs(rec), "ok": rs(rec) == 0x20},
        "hash_map<Key,PFRecordInfo,..,EASTLCoreAllocator> (0x24: PFIndexModifiable 0x4c - 0x28)": {"recomputed": rs([n for n in dev.t if n.startswith("eastl::hash_map<EA::ResourceMan::Key,EA::ResourceMan::PFRecordInfo")][0]), "ok": rs([n for n in dev.t if n.startswith("eastl::hash_map<EA::ResourceMan::Key,EA::ResourceMan::PFRecordInfo")][0]) == 0x24},
        "hash_map<uint,string<char>,..,eastl::allocator> (0x20 in s006aa3f0)": {"recomputed": rs([n for n in dev.t if n.startswith("eastl::hash_map<unsigned int,eastl::basic_string<char,eastl::allocator>")][0]), "ok": rs([n for n in dev.t if n.startswith("eastl::hash_map<unsigned int,eastl::basic_string<char,eastl::allocator>")][0]) == 0x20},
        "EA::ResourceMan::PFRecordWrite size (0x27c byte-exact alloc)": {"recomputed": ret.layout("EA::ResourceMan::PFRecordWrite")["size"], "ok": ret.layout("EA::ResourceMan::PFRecordWrite")["size"] == 0x27C},
        "EA::ResourceMan::PFHoleTable size (0x20)": {"recomputed": ret.layout("EA::ResourceMan::PFHoleTable")["size"], "ok": ret.layout("EA::ResourceMan::PFHoleTable")["size"] == 0x20},
    }

    # ---- which pilot members still have unknown leaf sizes --------------------------------
    unknown = []
    covered = [re.compile(e["match"]) for e in CURATED]
    for n, depth in sorted(closure.items(), key=lambda kv: (kv[1], kv[0])):
        if n.startswith(("eastl::", "EA::Allocator::", "EA::Thread::", "EA::IO::", "EA::COM::", "EA::Messaging::", "EA::AutoRefCount", "EA::Variant", "EA::RefCounted")) or n in ("EAMutexData", "SP::cString", "EA::ResourceMan::Key", "EA::ResourceMan::Resource", "SP::cResourceBase"):
            if not any(r.search(n) for r in covered):
                unknown.append({"type": n, "dev_size": dev.size(n), "why": "no table entry"})
                continue
            sz, _ = ret.size_align(n) if (n.startswith("eastl::") or n == CORE_ALLOC) else (1, 1)
            if sz is None:
                unknown.append({"type": n, "dev_size": dev.size(n), "why": "family entry exists but retail size of this instantiation unknown (allocator variant not measured)"})
    # pilot classes whose layout still has unknown members
    cls_unknown = {}
    for n in closure:
        if re.match(PILOT_ROOTS, n):
            lay = ret.layout(n)
            cls_unknown[n] = {"relaid_size": lay["size"], "dev_size": dev.size(n), "members_with_unknown_leaf": lay["unknown"]}
    out = {
        "format": {
            "entries": "list of {name, dev_size, retail_size (int, or null where the rule per instantiation applies/unknown), align, members [[name, offset, size]], evidence [..], confidence measured|inferred|unknown, rule, pilot_instantiations, slice_views}",
            "slice_views": "retail sizes of the slice-private struct bodies matching the family, tallied by size: bodies and the number of slices (with >=1 byte-exact function) using them. Partial views (private stubs that omit members) are expected, so this is a sanity check, not the source of truth",
            "how_to_use": "retail size of a dev template instantiation = apply `rule`; tools/migrate/leafsizes.py Retail.size_align() implements the rules and Retail.layout() re-lays a class member by member",
        },
        "generator": "tools/migrate/leafsizes.py",
        "entries": entries,
        "structural_deltas_not_leaf": STRUCTURAL_DELTAS,
        "validation": val,
        "pilot_unknown_leaf_instantiations": unknown,
        "pilot_class_relayout_summary": cls_unknown,
        "pilot_dev_closure_size": len(closure),
        "modapi_says": MODAPI_SAYS,
    }
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    json.dump(out, open(OUT, "w"), indent=1)
    ok = all(v.get("ok", True) for v in val["cross_checks"].values()) and val["DatabasePackedFile"]["mpStream"]["ok"] and val["vector"]["ok_pilot"]
    print("entries: %d  pilot closure: %d types  unknown leaf instantiations: %d" % (len(entries), len(closure), len(unknown)))
    print("mpStream: dev 0x%x -> retail 0x%x (expected 0x260)" % (val["DatabasePackedFile"]["mpStream"]["dev"], val["DatabasePackedFile"]["mpStream"]["recomputed"]))
    print("vector histogram over all dev vectors:", val["vector"]["retail_size_histogram_over_all_dev_vectors"])
    for k, v in val["cross_checks"].items():
        print("  %-80s %s %s" % (k, hex(v["recomputed"]) if isinstance(v["recomputed"], int) else v["recomputed"], "ok" if v["ok"] else "MISMATCH"))
    print("wrote", OUT)
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--probe")
    ap.add_argument("--exact-only", action="store_true")
    a = ap.parse_args()
    cen = Census()
    if a.probe:
        for name, h, sz, ns, ne, mem, _ in sorted(cen.probe(a.probe, a.exact_only), key=lambda r: (r[0], -r[4])):
            print("%-24s %s size=%-6s slices=%-3d exact_slices=%-3d %s" % (name, h, hex(sz) if sz is not None else "?", ns, ne, "; ".join(mem)[:150]))
        return 0
    return build(cen)


if __name__ == "__main__":
    sys.exit(main())
