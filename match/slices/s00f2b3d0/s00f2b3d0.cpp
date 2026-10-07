// Slice s00f2b3d0: EASTL container internals (vector/hashtable instantiations for
// EA::ResourceMan::Key and a ~0x188-byte element type).  Optimized module:
//   /O2 /MD /Gy /EHsc /TP
//
// FUN_00f2b3d0..FUN_00f2c330 are template instantiations of eastl::vector,
// eastl::hashtable and the range algorithms over a 0x188-byte element.  The exact
// element/allocator types are not recovered here; the two self-contained functions
// (FUN_00f2bd10, FUN_00f2bcb0) are reconstructed, the rest are skeletons.
#include "types.h"
void operator_delete__(void*);                     // 0x00f47380
void FUN_00dfaaf0(void*, void*);


// ---------------------------------------------------------------------------
// @ 0x00f2bd10  Constructor of a 0x188-byte container with a 0x154-byte inline
// buffer at +0x30 (begin/end/capacity at +0x18/+0x1c/+0x20).
// ---------------------------------------------------------------------------
struct Container188 {
    int f0; int f4; int f8; int fc;
    char f10; int f14; void* b18; void* e1c; void* c20; int f24; int f28; int f2c;
    char buf[0x154];
    int f184;
    Container188();
};

// @ 0x00f2bd10
Container188::Container188() {
    int neg = -1;
    f0 = 0;
    fc = 0;
    f4 = neg;
    f8 = neg;
    f10 = 1;
    f14 = 0;
    f2c = 0;
    b18 = buf;
    e1c = b18;
    c20 = (char*)b18 + 0x154;
    f184 = neg;
}

// ---------------------------------------------------------------------------
// @ 0x00f2bcb0  Range destructor/relocate over a contiguous array of 0x188-byte
// elements: destroys the member vector at +0x18 and frees its buffer.
// ---------------------------------------------------------------------------
struct Big188 {
    char pad0[0x18];
    void* f18;
    void* f1c;
    char pad1[0x188 - 0x20];
};

// @ 0x00f2bcb0
char* FUN_00f2bcb0(Big188* first, Big188* last, char* out) {
    while (first != last) {
        FUN_00dfaaf0(first->f18, first->f1c);
        void* q = first->f18;
        if (q != 0 && *(int*)((char*)q - 4) != 0) {
            operator_delete__(q);
        }
        first = (Big188*)((char*)first + 0x188);
        out += 0x188;
    }
    return out;
}

void __cdecl SortKeys(struct Key* first, struct Key* last);               // @ 0x4f6b70
struct Key* __cdecl UniqueKeys(struct Key* first, struct Key* last);      // @ 0x4f6830
// ---------------------------------------------------------------------------
// Resource-collection helpers (an asset-set object whose Collect() gathers a pointer vector of
// reference records; the functions below resolve / mark / export those references).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

struct Key { uint32_t a, b, c; };                 // EA::ResourceMan::Key (instance, type, group order as stored)
struct Ref {                                      // asset reference record
    Key key;                                      // +0x00
    uint32_t f0c;                                 // +0x0c
    uint32_t idLo, idHi;                          // +0x10 / +0x14  (64-bit id; -1 = none)
};
struct IdPair { uint32_t lo, hi; };

struct PtrVec {                                   // eastl::vector<Ref*>
    Ref** b; Ref** e; Ref** c;
    ~PtrVec() { if (b && ((int*)b)[-1] != 0) operator_delete__(b); }
};
struct KeyVec {                                   // eastl::vector<Key,sp_vector_allocator>
    Key* b; Key* e; Key* c;
    void DoInsertValue(Key* pos, const Key* v);                       // @ 0x4e3e10
    Key* EraseAll(Key* first, Key* last);                             // @ 0x50f740
    __forceinline void push_back(const Key& k) {
        if (e < c) { Key* p = e; e = p + 1; if (p) { *p = k; } }
        else DoInsertValue(e, &k);
    }
    __forceinline void erase(Key* first, Key* last) {
        Key* d = first; Key* s = last; Key* end = e;
        for (; s != end; ++s, ++d) *d = *s;
        e += -(last - first) * 0 + (d - last);
    }
};
struct IdVec {                                    // eastl::vector<IdPair>
    IdPair* b; IdPair* e; IdPair* c;
    void DoInsertValue(IdPair* pos, const IdPair* v);                 // @ 0x4786e0
    __forceinline void erase(IdPair* first, IdPair* last) {
        memcpy(first, last, (unsigned)((char*)e - (char*)last));
        e -= (last - first);
    }
};
struct IntVec {                                   // eastl::vector<int> kept sorted + unique
    int* b; int* e; int* c;
    void DoInsertValue(int* pos, const int* v);                       // @ 0xea9440
    __forceinline void erase(int* first, int* last) {
        memcpy(first, last, (unsigned)((char*)e - (char*)last));
        e -= (last - first);
    }
    __forceinline void insert_unique(const int& v) {
        int* pos = b;
        int n = (int)(e - b);
        while (n > 0) {
            int h = n >> 1;
            if (pos[h] < v) { pos = pos + h + 1; n = n + (-1 - h); }
            else n = h;
        }
        if (pos == e || v < *pos) {
            if (pos == e && e != c) { int* p = e; e = p + 1; if (p) *p = v; }
            else DoInsertValue(pos, &v);
        }
    }
};

struct Directory {
    bool HasLocal(uint32_t lo, uint32_t hi);                          // @ 0x54e740
    bool GetLocalKey(uint32_t lo, uint32_t hi, Key* out);             // @ 0x54e460
    void Mark(uint32_t lo, uint32_t hi, bool flag);                   // @ 0x54ed50
};
struct DirHolder { char pad[0x58]; Directory* dir; };
DirHolder* GetDirHolder();                                            // @ 0x67cb30
struct IResManager {
    virtual void _v0(); virtual void _v1(); virtual void _v2();
    virtual bool KeyExists(const Key* key, int a, int b, int c, int d, int e);   // +0x0c
};
IResManager* GetResManager();                                         // @ 0x67dcd0

bool __cdecl ResolveInPlace(Ref* r, uint32_t* f);                     // @ 0xf25a40
bool __cdecl ResolveId(uint32_t lo, uint32_t hi, Key* out);           // @ 0xf25930
void __cdecl SortIds(IdPair* first, IdPair* last);                    // @ 0xec4f00
IdPair* __cdecl UniqueIds(IdPair* first, IdPair* last);               // @ 0x593ba0

struct AssetSet {
    void Collect(PtrVec* out, uint32_t flags, int zero);              // @ 0xf2b040 (thiscall, callee pops)
    bool FUN_00f2b3d0();
    void FUN_00f2b4f0(KeyVec* out, uint32_t flags);
    void FUN_00f2b690(IdVec* out, uint32_t flags);
    void FUN_00f2b790();
    bool FUN_00f2c070(KeyVec* in, KeyVec* out);
    bool FUN_00f2c330(bool stopOnFirst, KeyVec* out);
    bool FUN_00f2bd50(void* stream, uint32_t b);
    char pad[0x78];
    uint32_t mModelType;                          // +0x78
};

// @ 0x00f2b3d0  Resolve every collected reference; returns false if any fails.
bool AssetSet::FUN_00f2b3d0()
{
    PtrVec v; v.b = 0; v.e = 0; v.c = 0;
    Collect(&v, 0x30f0f, 0);
    uint32_t n = (uint32_t)(v.e - v.b);
    bool ok = true;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t* r = (uint32_t*)v.b[i];          // Ref fields: [0..2] key, [3] f0c, [4] idLo, [5] idHi
        if (r[3] != 0) {
            if (!ResolveInPlace((Ref*)r, &r[3])) ok = false;
            else { bool prev = ok; ok = true; if (!prev) ok = false; }
        }
        bool good = true;
        if ((r[4] & r[5]) != 0xffffffff) {
            r[0] = 0;
            if ((r[4] & r[5]) != 0xffffffff) {
                Key k; k.a = 0; k.b = 0; k.c = 0;
                if (ResolveId(r[4], r[5], &k)) {
                    r[4] = 0xffffffff; r[5] = 0xffffffff;
                    r[0] = k.a; r[1] = k.b; r[2] = k.c;
                } else good = false;
            }
        }
        r[4] = 0xffffffff; r[5] = 0xffffffff;
        if (!good || !ok) ok = false; else ok = true;
    }
    return ok;
}

// @ 0x00f2b4f0  Collect all resolved, sorted, unique keys into out.
void AssetSet::FUN_00f2b4f0(KeyVec* out, uint32_t flags)
{
    out->EraseAll(out->b, out->e);
    PtrVec v; v.b = 0; v.e = 0; v.c = 0;
    Collect(&v, flags, 0);
    uint32_t n = (uint32_t)(v.e - v.b);
    for (uint32_t i = 0; i < n; i++) {
        Ref* r = v.b[i];
        Key k = r->key;
        uint32_t lo = r->idLo, hi = r->idHi;
        uint32_t f = r->f0c;
        if (f != 0) ResolveInPlace((Ref*)&k, &f);
        bool have = true;
        if ((lo & hi) != 0xffffffff) {
            Key t; t.a = 0; t.b = 0; t.c = 0;
            if (ResolveId(lo, hi, &t)) k = t; else have = false;
        }
        if (have && k.a != 0) out->push_back(k);
    }
    SortKeys(out->b, out->e);
    Key* end = out->e;
    Key* newEnd = UniqueKeys(out->b, end);
    out->erase(newEnd, end);
}

// @ 0x00f2b690  Collect the 64-bit ids of all references, sorted and unique, into out.
void AssetSet::FUN_00f2b690(IdVec* out, uint32_t flags)
{
    out->erase(out->b, out->e);
    PtrVec v; v.b = 0; v.e = 0; v.c = 0;
    Collect(&v, flags, 0);
    uint32_t n = (uint32_t)(v.e - v.b);
    for (uint32_t i = 0; i < n; i++) {
        Ref* r = v.b[i];
        if ((r->idLo & r->idHi) != 0xffffffff) {
            IdPair* p = out->e;
            if (p < out->c) {
                out->e = p + 1;
                if (p) { p->lo = r->idLo; p->hi = r->idHi; }
            } else {
                out->DoInsertValue(p, (IdPair*)&r->idLo);
            }
        }
    }
    SortIds(out->b, out->e);
    IdPair* end = out->e;
    IdPair* newEnd = UniqueIds(out->b, end);
    out->erase(newEnd, end);
}

// @ 0x00f2b790  Mark references whose local key exists but whose companion resource does not.
void AssetSet::FUN_00f2b790()
{
    PtrVec v; v.b = 0; v.e = 0; v.c = 0;
    Collect(&v, 0x20004, 0);
    if (v.b != v.e) {
        uint32_t n = (uint32_t)(v.e - v.b);
        for (uint32_t i = 0; i < n; i++) {
            Ref* r = v.b[i];
            if ((r->idLo & r->idHi) != 0xffffffff) {
                Key k; k.a = 0; k.b = 0; k.c = 0;
                if (!GetDirHolder()->dir->HasLocal(r->idLo, r->idHi)) {
                    if (GetDirHolder()->dir->GetLocalKey(r->idLo, r->idHi, &k)) {
                        Key k2; k2.a = k.a; k2.b = 0x30bdee3; k2.c = k.c;
                        if (GetResManager()->KeyExists(&k, 0, 0, 0, 0, 0)) {
                            if (!GetResManager()->KeyExists(&k2, 0, 0, 0, 0, 0)) {
                                GetDirHolder()->dir->Mark(r->idLo, r->idHi, true);
                            }
                        }
                    }
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Stream reader that builds a sorted, unique int set (@ 0xf2b8d0) and the vector helpers.
// ---------------------------------------------------------------------------
struct IStreamHandle { virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
                       virtual void _v4(); virtual void _v5(); virtual void* GetHandle(); };      // +0x18
struct IReader {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6();
    virtual void EndChunk();                                          // +0x1c
    virtual IStreamHandle* GetStream();                               // +0x20
};
int __cdecl ReadInt32(void* h, int* out, int count, int endian);      // @ 0x93a780 (EA::IO::ReadInt32)

// @ 0x00f2b8d0
void FUN_00f2b8d0(IReader* reader, IntVec* out)
{
    out->erase(out->b, out->e);
    uint32_t count = 0;
    void* h0 = reader->GetStream()->GetHandle();
    ReadInt32(h0, (int*)&count, 1, 0);
    for (uint32_t i = 0; i < count; i++) {
        int v;
        void* h1 = reader->GetStream()->GetHandle();
        ReadInt32(h1, &v, 1, 0);
        reader->EndChunk();
        out->insert_unique(v);
    }
    reader->EndChunk();
}

// @ 0x00f2ba80  insert(first, last) into a sorted-unique int vector.
struct IntSet : IntVec {
    void insert(const int* first, const int* last);
};
void IntSet::insert(const int* first, const int* last)
{
    for (; first != last; ++first) insert_unique(*first);
}

// 0x00f2b9f0 (KeyMap::operator[]) map[key]: returns the value slot for key, inserting a zero value if absent.
struct KeyPair { Key first; Key second; };
struct KeyMap {
    KeyPair* b; KeyPair* e; KeyPair* c;
    char alloc[8];
    bool flag;                                    // +0x14
    KeyPair* Insert(KeyPair* pos, const KeyPair* v);                  // @ 0xf2afc0 (thiscall)
    void Reserve(uint32_t n);                                         // @ 0xf28140
    Key* Lookup(const Key& k);                                       // operator[]
};
KeyPair* __cdecl LowerBound(KeyPair* first, KeyPair* last, const Key* k, bool flag);   // @ 0xf27fc0

inline bool KeyLess(const Key& x, const Key& y)
{
    if (x.a != y.a) return x.a < y.a;
    if (x.c != y.c) return x.c < y.c;
    return x.b < y.b;
}

// @ 0x00f2b9f0
Key* KeyMap::Lookup(const Key& k)
{
    KeyPair* end = e;
    KeyPair* it = LowerBound(b, end, &k, flag);
    if (it == end || KeyLess(k, it->first)) {
        KeyPair p;
        p.first = k;
        p.second.a = 0; p.second.b = 0; p.second.c = 0;
        it = Insert(it, &p);
    }
    return &it->second;
}

// @ 0x00f2bbd0  Destroy a range of 0x238-byte entries; returns dest advanced past them.
struct VecOfBuf { char pad0[0x1c]; void* buf; char pad1[0x34 - 0x20]; };
struct Entry238 {
    uint32_t flags;                               // +0x00 (bit 31: entry unused / already destroyed)
    char pad0[0x2c - 4];
    VecOfBuf* subBegin;                           // +0x2c
    VecOfBuf* subEnd;                             // +0x30
    char pad1[0x210 - 0x34];
    void* buf;                                    // +0x210
    char pad2[0x238 - 0x214];
};
// @ 0x00f2bbd0
Entry238* FUN_00f2bbd0(Entry238* first, Entry238* last, Entry238* dest)
{
    for (; first != last; ++first) {
        if (!((first->flags >> 31) & 1)) {
            void* p = first->buf;
            if (p && ((int*)p)[-1] != 0) operator_delete__(p);
            VecOfBuf* end = first->subEnd;
            for (VecOfBuf* s = first->subBegin; s < end; s++) {
                void* q = s->buf;
                if (q && ((int*)q)[-1] != 0) operator_delete__(q);
            }
            void* sb = first->subBegin;
            if (sb && ((int*)sb)[-1] != 0) operator_delete__(sb);
        }
        ++dest;
    }
    return dest;
}

// ---------------------------------------------------------------------------
// 0x00f2bd50: Write the asset list of a model as XML.
// ---------------------------------------------------------------------------
struct WAlloc { char c; WAlloc() { c = 0; } };
struct WString {
    wchar_t* b; wchar_t* e; wchar_t* c; WAlloc a;
    WString(WAlloc al, const wchar_t* fmt, ...);                      // @ 0x473020 (cdecl, this pushed)
    ~WString() { if ((c - b) > 1 && b) operator_delete__(b); }
};
struct XmlTextWriter {
    virtual void _v0(); virtual void _v1();
    virtual bool StartElement(const wchar_t* name);                   // +0x08  0x00901b30
    virtual bool EndElement(const wchar_t* name);                     // +0x0c  0x00901b90
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual bool WriteText(const wchar_t* text);                      // +0x20  0x009018a0
    XmlTextWriter(uint32_t stream, int zero);                         // @ 0x901a10
    ~XmlTextWriter();                                                 // @ 0x901a50
    void Attach(void* stream, uint32_t flag);                         // @ 0x901d30 (IStream*, bool)
    bool WriteXmlHeader();                                            // @ 0x901960
};
struct XmlSink {
    const void* vtbl;
    char w[sizeof(void*)];
};
extern const void* PTR_FUN_0148c67c;
bool __cdecl WriteAssetBody(void* sink, int zero, AssetSet* self);    // @ 0xf28380

// @ 0x00f2bd50
bool AssetSet::FUN_00f2bd50(void* a, uint32_t b)
{
    struct Sink {
        const void* vtbl; XmlTextWriter w;
        Sink(uint32_t s) : vtbl(&PTR_FUN_0148c67c), w(s, 0) {}
    } sink(b);
    sink.w.Attach(a, b);
    bool hdr = sink.w.WriteXmlHeader();
    WString typeStr(WAlloc(), L"0x%08x", mModelType);
    WString verStr(WAlloc(), L"0x%08x", 0x11);
    bool ok;
    if (!hdr) ok = false;
    else ok = sink.w.StartElement(L"sporemodel")
           && sink.w.StartElement(L"properties")
           && sink.w.StartElement(L"modeltype")
           && sink.w.WriteText(typeStr.b)
           && sink.w.EndElement(L"modeltype")
           && sink.w.StartElement(L"version")
           && sink.w.WriteText(verStr.b)
           && sink.w.EndElement(L"version")
           && sink.w.EndElement(L"properties")
           && sink.w.StartElement(L"assets");
    IdVec ids; ids.b = 0; ids.e = 0; ids.c = 0;
    FUN_00f2b690(&ids, 0xf00);
    uint32_t n = (uint32_t)(ids.e - ids.b);
    for (uint32_t i = 0; i < n; i++) {
        if (ok) ok = sink.w.StartElement(L"asset"); else ok = false;
        WString idStr(WAlloc(), L"%I64d", ids.b[i].lo, ids.b[i].hi);
        if (ok) ok = sink.w.WriteText(idStr.b) && sink.w.EndElement(L"asset"); else ok = false;
    }
    if (ids.b && ((int*)ids.b)[-1] != 0) operator_delete__(ids.b);
    bool result = false;
    if (ok && sink.w.EndElement(L"assets") && WriteAssetBody(&sink, 0, this) && sink.w.EndElement(L"sporemodel"))
        result = true;
    sink.vtbl = &PTR_FUN_0148c67c;
    sink.w.~XmlTextWriter();
    return result;
}

// ---------------------------------------------------------------------------
// 0x00f2c070 / 0x00f2c330
// ---------------------------------------------------------------------------
struct IAssetBrowser { bool Resolve(Key key, Key* out, int mode, bool flag); };   // @ 0x646370
IAssetBrowser* GetAssetBrowser();                                                    // @ 0x401030
struct NamespaceHolder { char pad[0x44]; uint32_t f44; };
NamespaceHolder* GetNamespace();                                                     // @ 0x5f7930
int __cdecl GetKeyKind(Key* k);                                                      // @ 0x552300

// @ 0x00f2c070
bool AssetSet::FUN_00f2c070(KeyVec* in, KeyVec* out)
{
    KeyMap map; map.b = 0; map.e = 0; map.c = 0;
    map.Reserve((uint32_t)(in->e - in->b));
    for (uint32_t i = 0; i < (uint32_t)(in->e - in->b); i++) {
        Key* kp = &in->b[i];
        Key res; res.a = 0; res.b = 0; res.c = 0;
        if (GetAssetBrowser()->Resolve(*kp, &res, -1, true)) {
            *map.Lookup(*kp) = res;
            if (out) out->push_back(res);
        }
    }
    if (map.b == map.e) {
        if (map.b) operator_delete__(map.b);
        return false;
    }
    PtrVec v; v.b = 0; v.e = 0; v.c = 0;
    Collect(&v, 0x30f0f, 0);
    uint32_t n = (uint32_t)(v.e - v.b);
    for (uint32_t i = 0; i < n; i++) {
        Ref* r = v.b[i];
        Key k = r->key;
        uint32_t lo = r->idLo, hi = r->idHi;
        uint32_t f = r->f0c;
        if (f != 0) ResolveInPlace((Ref*)&k, &f);
        bool have = true;
        if ((lo & hi) != 0xffffffff) {
            Key t; t.a = 0; t.b = 0; t.c = 0;
            if (ResolveId(lo, hi, &t)) k = t; else have = false;
        }
        if (have && k.a != 0) {
            KeyPair* it = LowerBound(map.b, map.e, &k, map.flag);
            if (it != map.e) {
                bool lt = k.a < it->first.a;
                if (k.a == it->first.a) {
                    lt = k.c < it->first.c;
                    if (k.c == it->first.c) lt = k.b < it->first.b;
                }
                if (!lt && it != it + 1) {
                    r->key = it->second;
                    r->f0c = GetNamespace()->f44;
                    r->idLo = 0xffffffff; r->idHi = 0xffffffff;
                }
            }
        }
    }
    if (map.b) operator_delete__(map.b);
    return true;
}

// @ 0x00f2c330
bool AssetSet::FUN_00f2c330(bool stopOnFirst, KeyVec* out)
{
    KeyVec keys; keys.b = 0; keys.e = 0; keys.c = 0;
    FUN_00f2b4f0(&keys, 2);
    uint32_t n = (uint32_t)(keys.e - keys.b);
    KeyVec sel; sel.b = 0; sel.e = 0; sel.c = 0;
    Key* p = keys.b;
    for (uint32_t i = 0; i < n; i++, p++) {
        if (GetKeyKind(p) == 2) {
            if (stopOnFirst) {
                if (sel.b && ((int*)sel.b)[-1] != 0) operator_delete__(sel.b);
                if (keys.b && ((int*)keys.b)[-1] != 0) operator_delete__(keys.b);
                return true;
            }
            sel.push_back(*p);
        }
    }
    bool r = FUN_00f2c070(&sel, out);
    if (sel.b && ((int*)sel.b)[-1] != 0) operator_delete__(sel.b);
    if (keys.b && ((int*)keys.b)[-1] != 0) operator_delete__(keys.b);
    return r;
}
