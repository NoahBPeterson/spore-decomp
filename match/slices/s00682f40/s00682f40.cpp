// Slice s00682f40: continuation of the UTFKernel-era serialization factory
// (vector<Obj1800>/vector<ObjA> inserts, int-keyed rbtree maps, node-chain
// free, abstract reader/writer loaders, and the SP::cPropertyList constructor).
//
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE). Out-of-slice callees are
// externs; relocation targets are masked by the verifier.
#include "types.h"
#include <intrin.h>

static inline void** VT(void* p) { return *(void***)p; }
inline void* operator new(uint32_t, void* p) { return p; }

struct IWrt {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void vC(); virtual void vD();
    virtual void Write(const void* p, int n);
};
struct IRd {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void Read(void* p, int n);
};

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag_13ebb38[];
extern "C" char  g_fileEASTL_13ebc58[];
extern "C" void __cdecl WriteUint32(void*, void*, int, int);      // 0x093aa70
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void* __cdecl RBTreeIncrement(void*);                  // 0x0921580
extern "C" void* __cdecl RBTreeDecrement(void*);                  // 0x09215c0
extern "C" void  __cdecl RBTreeInsert(void*, void*, void*, int);  // 0x09216a0
extern "C" void  __cdecl UninitCopy(void**, void*, void*, void*, void*); // 0x0681ca0
extern "C" void  __cdecl FreeNodes681480(void* self, void* root); // 0x0681480
extern "C" void* __cdecl CreateNode1700(const void* pair);        // 0x06826c0
extern "C" void* __cdecl CreateNodeZ(const void* pair);           // 0x0683480
extern "C" void  __cdecl CopyBackward1800(void*, void*, void*);   // 0x0681e40
extern "C" void* __cdecl MoveBackN1800(void*, void*, void*);      // 0x0681d20
extern "C" void  __cdecl Destroy1800(void*, void*, void*);        // 0x0680bf0
extern "C" void  __cdecl CopyBackwardA(void*, void*, void*);      // 0x0681e80
extern "C" void* __cdecl MoveBackNA(void*, void*, void*);         // 0x0681db0
extern "C" void  __cdecl DestroyA(void*, void*, void*);           // 0x0680800
extern "C" void  __cdecl Obj1700Ctor(void*, const void*);         // 0x0681700

// 0x00681800 / 0x00681B50 are __thiscall: `this` arrives in ecx.
struct Obj1800CtorT { void ctor(const void* src); };               // 0x0681800
struct ObjB50AssignT { void assign(const void* src); };            // 0x0681b50

extern "C" void  __cdecl ObjACtor(void*, const void*);            // 0x0681a10
struct ObjACtorT { void ctor(const void* src); };                  // 0x0681a10 (thiscall)
struct ObjAAssignT { void assign(const void* src); };              // 0x0681c40 (thiscall)
extern "C" void  __cdecl ObjB50Assign(void*, const void*);        // 0x0681b50
extern "C" void  __cdecl ObjAAssign(void*, const void*);          // 0x0681c40
extern "C" void  __cdecl LoadEntries(void*, void*, IRd*);         // 0x06812c0
extern "C" void  __cdecl ReadCStringKey(void*, void*, IRd*);      // 0x0680560
// The reader helpers take their owner in ecx (thiscall).
struct LoadEntriesT { void load(void* out, IRd* r); };             // 0x06812c0
struct ReadStrKeyT  { void read(void* out, IRd* r); };             // 0x0680560
extern "C" void  __cdecl Insert1800At(void*, void*, IRd*);        // 0x0680890
extern "C" void  __cdecl VecU32Insert(void*, void*, void*);       // 0x04558a0
extern "C" void  __cdecl MyCopy(void*, const void*);              // 0x06830f0
extern "C" void* __cdecl CreateNodeMy(const void* pair);          // 0x0683480

// =====================================================================
// stubs
// =====================================================================
struct S8 {
    char* mpBegin; char* mpEnd; char* mpCap;
    S8() {}
    void Init(int n);                           // 0x0475ab0
    __forceinline S8(const S8& x) {
        mpBegin = 0; mpEnd = 0; mpCap = 0;
        char* xEnd = x.mpEnd; char* xBegin = x.mpBegin;
        int n = xEnd - xBegin;
        Init(n + 1);
        MemcpyT(mpBegin, xBegin, (uint32_t)n);
        mpEnd = mpBegin - xBegin + xEnd;
        *mpEnd = 0;
    }
    ~S8() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};

struct Buf {
    char* mpBegin; char* mpEnd; char* mpCap; uint32_t mAlloc;
    ~Buf() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};

struct V20 {
    char* mpBegin; char* mpEnd; char* mpCap; void* mAlloc[2];
    ~V20() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_dealloc(mpBegin); }
};

// int-keyed tree free helper (MapC2-like)
struct MapC2 {
    uint32_t pad0; void* mpAnchor; void* mpBegin; void* mpRoot;
    ~MapC2() { FreeNodes(mpRoot); }
    void FreeNodes(void* p);            // 0x0681480 (out-of-slice)
};

// node freed by 0x00683160: {right,next, buffer @0x14, map @0x24}
struct NodeF {
    NodeF* mpRight;     // +0x00
    NodeF* mpNext;      // +0x04
    uint32_t pad[3];    // +0x08
    Buf mBuf;           // +0x14
    MapC2 mMap;         // +0x24
};
struct ClsF { void FreeChain(NodeF* p); };

// value object with S8 + a member at +0x10 copied by 0x6830f0
struct MY { char* b; char* e; char* c; void* a[2]; MY(const MY&); ~MY(); };
struct ObjY {
    S8 mStr;
    uint32_t padC;
    MY m;               // +0x10
    ObjY(const ObjY& o);
};
struct NodeY { NodeY* r; NodeY* l; NodeY* p; uint32_t col; int key; ObjY val; };
struct MapY {
    uint32_t pad0; NodeY* anchor; NodeY* begin; NodeY* root; uint32_t col;
    uint32_t size; uint32_t alloc;
    NodeY* CreateNode(const int* key);          // 0x0683480 (out-of-slice)
    void InsertPair(NodeY** out, NodeY* pos, int* key, char b);
    void InsertUnique(void* pair, const int* key, int flag);
};

// value: S8 + M5a0 (0x24) node 0x38  -- Map1 from slice 16
struct M5a0 { char* b; char* e; char* c; void* a[2]; M5a0(){} M5a0(const M5a0&); ~M5a0(); };
struct ObjC30 { S8 mStr; uint32_t padC; M5a0 mVec; ObjC30(const ObjC30&); };
struct Node1 { Node1* r; Node1* l; Node1* p; uint32_t col; int key; ObjC30 val; };
struct Map1 {
    uint32_t pad0; Node1* anchor; Node1* begin; Node1* root; uint32_t col;
    uint32_t size; uint32_t alloc;
    void InsertHint(Node1** out, Node1* hint, int* key, char flag);
    void InsertUnique(void* pair, const int* key);
    ObjC30* operator[](int key);
};

struct VV12 { char* b; char* e; char* c; ~VV12(); VV12(){} VV12(const VV12& o); };

struct Pod16 { uint32_t w[4]; };
struct ObjA {
    Pod16 m0; V20 mF0; V20 mF1; V20 mF2; V20 mF3;
    ObjA(const ObjA&); ~ObjA() {}
};
struct Obj1800 {
    uint32_t w0[24]; uint32_t flag; uint8_t pad64[0x10];
    V20 mF0; V20 mF1; V20 mF2; V20 mF3;
    Obj1800(const Obj1800&); ~Obj1800() {}
};
struct Node2 { Node2* r; Node2* l; Node2* p; uint32_t col; int key; struct Obj1700* v; };
struct Obj1700 { S8 mStr; uint32_t padC; V20 mF0; V20 mF1; Obj1700(const Obj1700&); ~Obj1700() {} };
struct Node2v { Node2v* r; Node2v* l; Node2v* p; uint32_t col; int key; unsigned char val[0x38]; };
// Pair stored in a Map2 node: the int key followed by the Obj1700 value.
// The original builds `value` by copy-constructing from a source template whose S8 is the
// EASTL empty 16-bit string (begin == end == gEmptyString16, cap = gEmptyString16 + 1) and
// whose two 0x14-byte vectors are empty.
extern "C" uint16_t g_empty1600;        // 0x01667bac  eastl::gEmptyString16
// Raw image of the keyed pair: `int key` followed by the 0x38-byte Obj1700 value.
struct Keyed1700 {
    int mKey;
    unsigned char mValue[0x38];
    explicit Keyed1700(int k);
};
Keyed1700::Keyed1700(int k) {
    // Build the empty source template on the stack: an Obj1700 whose S8 is the EASTL empty
    // 16-bit string and whose two 0x14-byte vectors are empty; then copy-construct the value.
    __declspec(align(4)) unsigned char tmpl[0x38];
    for (int i = 0; i < 0x38; ++i) tmpl[i] = 0;
    *(uint16_t**)(tmpl + 0x00) = &g_empty1600;
    *(uint16_t**)(tmpl + 0x04) = &g_empty1600;
    *(uint16_t**)(tmpl + 0x08) = &g_empty1600 + 1;
    new (mValue) Obj1700(*(const Obj1700*)tmpl);
    mKey = k;
}
struct Map2 {
    uint32_t pad0; Node2v* anchor; Node2v* begin; Node2v* root; uint32_t col;
    uint32_t size; uint32_t alloc;
    Node2v* CreateNode(const Keyed1700* pair);                                // 0x06826c0 (out-of-slice)
    void InsertPair(Node2v** out, Node2v* pos, int* key, char flag);          // 0x06828a0 (out-of-slice)
    void InsertUnique(void* pair, const int* key, int flag);                  // 0x0682900 (out-of-slice)
    Node2v** InsertHint(Node2v** out, Node2v* hint, const Keyed1700* pair, char flag);
    Obj1700* operator[](const int* key);
};

// =====================================================================
// vector<Obj1800>::insert(pos, value)  [thiscall, ret 8]
// =====================================================================
struct Vec1800 {
    Obj1800* begin; Obj1800* end; Obj1800* cap;
    void insert(Obj1800* pos, const Obj1800& x);
};
// @ 0x00682f40
void Vec1800::insert(Obj1800* pos, const Obj1800& x) {
    Obj1800* end = this->end;
    if (end != this->cap) {
        // If the source element lives inside the vector it will move: skip past it.
        const Obj1800* src = &x;
        if (src >= pos && src < end)
            src = (const Obj1800*)((const char*)src + 0xc4);
        if (end)
            ((Obj1800CtorT*)end)->ctor((const char*)end - 0xc4);
        CopyBackward1800(pos, (char*)this->end - 0xc4, this->end);
        ((ObjB50AssignT*)pos)->assign(src);
        this->end = (Obj1800*)((char*)this->end + 0xc4);
        return;
    }

    // Grow: double the old capacity (or 1 when empty).
    int count = (int)((char*)end - (char*)this->begin) / 0xc4;
    int cap = (count == 0) ? 1 : count * 2;
    char* buf = cap ? (char*)EASTL_alloc6((uint32_t)cap * 0xc4, g_allocTag_13ebb38, 0, 0, g_fileEASTL_13ebc58, 0xd1)
                    : (char*)0;

    Obj1800* oldBegin = this->begin;
    char* mid = (char*)MoveBackN1800(oldBegin, pos, buf);
    Destroy1800(oldBegin, pos, buf);
    if (mid)
        ((Obj1800CtorT*)mid)->ctor((const char*)&x);
    Obj1800* oldEnd = this->end;
    char* newEnd = (char*)MoveBackN1800(pos, oldEnd, mid + 0xc4);
    Destroy1800(pos, oldEnd, mid + 0xc4);
    if (oldBegin && ((int*)oldBegin)[-1])
        EASTL_dealloc(oldBegin);
    this->begin = (Obj1800*)buf;
    this->end = (Obj1800*)newEnd;
    this->cap = (Obj1800*)(buf + cap * 0xc4);
}

// =====================================================================
// @ 0x00683160  free node chain (MapC2 + buffer)
// =====================================================================
void ClsF::FreeChain(NodeF* p) {
    while (p) {
        FreeChain(p->mpRight);
        NodeF* next = p->mpNext;
        p->~NodeF();
        EASTL_dealloc(p);
        p = next;
    }
}

// =====================================================================
// vector<ObjA>::insert(pos, value)  [thiscall, ret 8]
// =====================================================================
struct VecA {
    ObjA* begin; ObjA* end; ObjA* cap;
    void insert(ObjA* pos, const ObjA& x);
};
// @ 0x006831f0
void VecA::insert(ObjA* pos, const ObjA& x) {
    ObjA* end = this->end;
    if (end != this->cap) {
        // If the source element lives inside the vector it will move: skip past it.
        const ObjA* src = &x;
        if (src >= pos && src < end)
            src = (const ObjA*)((const char*)src + 0x60);
        if (end)
            ((ObjACtorT*)end)->ctor((const char*)end - 0x60);
        CopyBackwardA(pos, (char*)this->end - 0x60, this->end);
        ((ObjAAssignT*)pos)->assign(src);
        this->end = (ObjA*)((char*)this->end + 0x60);
        return;
    }

    // Grow: double the old capacity (or 1 when empty).
    int count = (int)((char*)end - (char*)this->begin) / 0x60;
    int cap = (count == 0) ? 1 : count * 2;
    char* buf = cap ? (char*)EASTL_alloc6((uint32_t)cap * 0x60, g_allocTag_13ebb38, 0, 0, g_fileEASTL_13ebc58, 0xd1)
                    : (char*)0;

    ObjA* oldBegin = this->begin;
    char* mid = (char*)MoveBackNA(oldBegin, pos, buf);
    DestroyA(oldBegin, pos, buf);
    if (mid)
        ((ObjACtorT*)mid)->ctor((const char*)&x);
    ObjA* oldEnd = this->end;
    char* newEnd = (char*)MoveBackNA(pos, oldEnd, mid + 0x60);
    DestroyA(pos, oldEnd, mid + 0x60);
    if (oldBegin && ((int*)oldBegin)[-1])
        EASTL_dealloc(oldBegin);
    this->begin = (ObjA*)buf;
    this->end = (ObjA*)newEnd;
    this->cap = (ObjA*)(buf + cap * 0x60);
}

// =====================================================================
// @ 0x00683390  Map2 insert-with-hint (value Obj1700)
// =====================================================================
Node2v** Map2::InsertHint(Node2v** out, Node2v* hint, const Keyed1700* pair, char flag) {
    (void)flag;
    Node2v* hdr = (Node2v*)&anchor;
    if (hint == begin || hint == hdr) {
        if (size == 0 || pair->mKey <= begin->key)
            goto UNIQUE;
        {
            int bIns = (begin == hdr || pair->mKey < begin->key) ? 0 : 1;
            Node2v* n = CreateNode(pair);
            RBTreeInsert(n, begin, hdr, bIns);
            ++size;
            *out = n;
            return out;
        }
    } else {
        Node2v* next = (Node2v*)RBTreeIncrement(hint);
        if (pair->mKey <= hint->key || next->key <= pair->mKey)
            goto UNIQUE;
        if (hint->r == 0) {
            InsertPair(out, hint, (int*)&pair->mKey, 0);
            return out;
        }
        {
            Node2v* n = CreateNode(pair);
            RBTreeInsert(n, next, hdr, 0);
            ++size;
            *out = n;
            return out;
        }
    }
UNIQUE:
    {
        void* outPair[2];
        outPair[0] = 0;
        // The 3rd argument is a dead int scratch that the original keeps in the key's argument home:
        // only its low byte is zeroed, so the value is `key & ~0xff`. The callee ignores it; it is
        // passed because the callee pops three argument dwords (`ret 0xc`).
        uint32_t dead = (uint32_t)(uintptr_t)pair & 0xFFFFFF00u;
        InsertUnique(outPair, &pair->mKey, (int)dead);
        *out = (Node2v*)outPair[0];
        return out;
    }
}

// =====================================================================
// @ 0x00683500  MapY insert (create 0x683480)
// =====================================================================
void MapY::InsertPair(NodeY** out, NodeY* pos, int* key, char flag) {
    int bIns;
    if (flag == 0 && pos != (NodeY*)&anchor && *key >= pos->key) bIns = 1;
    else bIns = 0;
    NodeY* n = CreateNode(key);
    RBTreeInsert(n, pos, (NodeY*)&anchor, bIns);
    NodeY** o = out;
    ++size;
    *o = n;
}

// =====================================================================
// @ 0x00683560  MapY insert_unique (create 0x683480)
// =====================================================================
void MapY::InsertUnique(void* pairOut, const int* key, int flag) {
    (void)flag;
    NodeY* hdr = (NodeY*)&anchor;
    NodeY* pos = hdr;
    int bLess = 1;
    NodeY* n = root;
    if (n) {
        do { pos = n; bLess = (*key < n->key); n = bLess ? n->l : n->r; } while (n);
    }
    NodeY* found = pos;
    if (bLess) {
        if (pos == begin) {
            int bIns = (pos != hdr && *key >= pos->key) ? 1 : 0;
            NodeY* nn = CreateNode(key);
            RBTreeInsert(nn, pos, hdr, bIns);
            ++size;
            ((void**)pairOut)[0] = nn;
            *((uint8_t*)pairOut + 4) = 1;
            return;
        }
        pos = (NodeY*)RBTreeDecrement(pos);
    }
    if (pos->key >= *key) {
        ((void**)pairOut)[0] = pos;
        *((uint8_t*)pairOut + 4) = 0;
        return;
    }
    {
        int bIns = (found != hdr && *key >= found->key) ? 1 : 0;
        NodeY* nn = CreateNode(key);
        RBTreeInsert(nn, found, hdr, bIns);
        ++size;
        ((void**)pairOut)[0] = nn;
        *((uint8_t*)pairOut + 4) = 1;
    }
}

// =====================================================================
// @ 0x00683670  ObjY copy ctor (S8 + MY at +0x10)
// =====================================================================
ObjY::ObjY(const ObjY& o) : mStr(o.mStr), m(o.m) {}

// =====================================================================
// @ 0x00683700  load vector<Obj1800> from a reader
// =====================================================================
// Element image as the reader fills it: a 4-byte head then four 0x14-byte string/vector
// fields at +0x04/+0x18/+0x2c/+0x40, a u32 at +0x54, three ints, a LoadEntries vector and
// four u32 vectors (all offset-compatible with Obj1800).
struct Elem1800 {
    uint32_t          head;      // +0x00
    S8                str0;      // +0x04
    S8                str1;      // +0x18
    S8                str2;      // +0x2c
    S8                str3;      // +0x40
    uint32_t          u54;      // +0x54
    uint32_t          i58;      // +0x58
    uint32_t          i5c;      // +0x5c
    uint32_t          i60;      // +0x60
    V20               entries;   // +0x64
    V20               vU32_0;    // +0x78
    V20               vU32_1;    // +0x8c
    V20               vU32_2;    // +0xa0
    V20               vU32_3;    // +0xb4
};
extern "C" void  __cdecl Elem1800Ctor_stk(void*);             // 0x0680890 (stack form)
struct Elem1800CtorT { void ctor(); };                         // 0x0680890 (thiscall)
extern "C" void  __cdecl Elem1800TailDtor(void*);             // 0x0680730
// 0x00683700 / 0x00683AB0 take their owner in ecx: `this` = the reader helper.
struct ObjLoaderT {
    void load1800(void* vec, IRd* r);      // 0x0683700
    void loadA(void* vec, IRd* r);         // 0x0683AB0
};

// @ 0x00683700
void ObjLoaderT::load1800(void* vec, IRd* r) {
    void* self = this;
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        Elem1800 elem;
        ((Elem1800CtorT*)&elem)->ctor();
        ((ReadStrKeyT*)self)->read(&elem.str0, r);
        ((ReadStrKeyT*)self)->read(&elem.str1, r);
        ((ReadStrKeyT*)self)->read(&elem.str2, r);
        ((ReadStrKeyT*)self)->read(&elem.str3, r);
        r->Read(&elem.u54, 4);
        ReadInt32(r, &elem.i58, 1, 0);
        ReadInt32(r, &elem.i5c, 1, 0);
        ReadInt32(r, &elem.i60, 1, 0);
        ((LoadEntriesT*)self)->load(&elem.entries, r);
        int n;
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.vU32_0.mpEnd = v;
            elem.vU32_0.mpEnd = (char*)elem.vU32_0.mpEnd + 4;
        }
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.vU32_1.mpEnd = v;
            elem.vU32_1.mpEnd = (char*)elem.vU32_1.mpEnd + 4;
        }
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.vU32_2.mpEnd = v;
            elem.vU32_2.mpEnd = (char*)elem.vU32_2.mpEnd + 4;
        }
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.vU32_3.mpEnd = v;
            elem.vU32_3.mpEnd = (char*)elem.vU32_3.mpEnd + 4;
        }

        // push_back into the destination vector<Obj1800>
        {
            Obj1800** v = (Obj1800**)vec;
            Obj1800* end = v[1];
            if (end < v[2]) {
                v[1] = (Obj1800*)((char*)end + 0xc4);
                if (end)
                    ((Obj1800CtorT*)end)->ctor(&elem);
            } else {
                ((Vec1800*)vec)->insert(end, *(Obj1800*)&elem);
            }
        }
        Elem1800TailDtor(&elem);
    }
}

// =====================================================================
// @ 0x00683ab0  load vector<ObjA> from a reader
// =====================================================================
void ObjLoaderT::loadA(void* vec, IRd* r) {
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        __declspec(align(4)) unsigned char elemBuf[0x60];
        ObjA& elem = *(ObjA*)elemBuf;
        // Zero the four 0x14-byte vector headers (begin/end/cap) before filling them.
        elem.mF0.mpBegin = 0; elem.mF0.mpEnd = 0; elem.mF0.mpCap = 0;
        elem.mF1.mpBegin = 0; elem.mF1.mpEnd = 0; elem.mF1.mpCap = 0;
        elem.mF2.mpBegin = 0; elem.mF2.mpEnd = 0; elem.mF2.mpCap = 0;
        elem.mF3.mpBegin = 0; elem.mF3.mpEnd = 0; elem.mF3.mpCap = 0;

        uint32_t scratch = 0;
        r->Read(&elem.m0.w[1], 4);
        r->Read(&elem.m0.w[3], 4);
        r->Read(&elem.mF0.mpBegin, 4);
        r->Read(&scratch, 4);
        (void)scratch;

        int n;
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.mF1.mpEnd = v;
            elem.mF1.mpEnd = (char*)elem.mF1.mpEnd + 4;
        }
        r->Read(&n, 4);
        for (int j = 0; j < n; ++j) {
            uint32_t v;
            r->Read(&v, 4);
            *(uint32_t*)elem.mF2.mpEnd = v;
            elem.mF2.mpEnd = (char*)elem.mF2.mpEnd + 4;
        }

        // push_back into the destination vector<ObjA>
        {
            ObjA** v = (ObjA**)vec;
            ObjA* end = v[1];
            if (end < v[2]) {
                v[1] = (ObjA*)((char*)end + 0x60);
                if (end)
                    ((ObjACtorT*)end)->ctor(&elem);
            } else {
                ((VecA*)vec)->insert(end, elem);
            }
        }
    }
}

// =====================================================================
// @ 0x00683d10  Map2 operator[] -> &value
// =====================================================================
Obj1700* Map2::operator[](const int* key) {
    Node2v* hdr = (Node2v*)&anchor;
    Node2v* pos = hdr;
    Node2v* cur = root;
    while (cur) {
        if (cur->key < *key) { pos = cur; cur = cur->r; }
        else cur = cur->l;
    }
    if (pos == hdr || pos->key < *key) {
        Keyed1700 p(*key);
        Node2v* n = 0;
        Node2v** out = &n;
        InsertHint(out, pos, &p, 0);
        return (Obj1700*)(*out)->val;
    }
    return (Obj1700*)pos->val;
}

// =====================================================================
// @ 0x00683e90  SP::cPropertyList constructor
// =====================================================================
// Intrusive doubly-linked list head: next=self, prev=self.
struct ListHead { ListHead* mpNext; ListHead* mpPrev; };
struct cPropertyList {
    void*     mpVtbl;        // +0x00  (0x13ebcdc, then the real vtable 0x1402ce8)
    int       mRef;          // +0x04  (interlocked store of 0)
    uint32_t  f08;           // +0x08
    uint32_t  f0c;           // +0x0c
    uint32_t  f10;           // +0x10
    uint32_t  f14;           // +0x14
    uint32_t  f18;           // +0x18
    ListHead  mHead1c;       // +0x1c  self-linked
    uint32_t  f24;           // +0x24
    uint8_t   f28;           // +0x28
    uint32_t  f2c;           // +0x2c
    uint32_t  f30;           // +0x30
    uint32_t  f34;           // +0x34
    ListHead  mHead38;       // +0x38  self-linked
    uint32_t  f40;           // +0x40
    uint8_t   f44;           // +0x44
    uint32_t  f48;           // +0x48
    uint32_t  f4c;           // +0x4c
    uint32_t  f50;           // +0x50
    ListHead  mHead54;       // +0x54  self-linked
    uint32_t  f5c;           // +0x5c
    uint8_t   f60;           // +0x60
    uint32_t  f64;           // +0x64
    uint32_t  f68;           // +0x68
    uint32_t  f6c;           // +0x6c
    uint32_t  f70;           // +0x70
    uint32_t  f74;           // +0x74
    cPropertyList();
};
cPropertyList::cPropertyList() {
    mpVtbl = (void*)0x13ebcdc;          // PropBaseA22 vtable (provisional)
    _InterlockedExchange((volatile long*)&mRef, 0);
    f08 = 0; f0c = 0; f10 = 0; f14 = 0;
    mpVtbl = (void*)0x1402ce8;          // cPropertyList vtable
    *(uint32_t*)&mHead1c.mpPrev = 0;    // +0x20
    f24 = 0;
    *(uint32_t*)&f28 = 0;               // +0x28 (dword)
    f24 = 0;
    f28 = 0;                            // +0x28 (byte)
    f2c = 0;
    mHead1c.mpNext = (ListHead*)((char*)this + 0x1c);
    mHead1c.mpPrev = (ListHead*)((char*)this + 0x1c);
    mHead38.mpPrev = 0;                 // +0x3c
    f40 = 0;
    *(uint32_t*)&f44 = 0;               // +0x44 (dword)
    mHead38.mpNext = (ListHead*)((char*)this + 0x38);
    mHead38.mpPrev = (ListHead*)((char*)this + 0x38);
    f40 = 0;
    f44 = 0;                            // +0x44 (byte)
    f48 = 0;
    mHead54.mpPrev = 0;                 // +0x58
    f5c = 0;
    *(uint32_t*)&f60 = 0;               // +0x60 (dword, via head+0xc)
    mHead54.mpNext = (ListHead*)((char*)this + 0x54);
    mHead54.mpPrev = (ListHead*)((char*)this + 0x54);
    f5c = 0;
    f60 = 0;                            // +0x60 (byte)
    f64 = 0;
    f6c = 0; f70 = 0; f74 = 0;
}

// =====================================================================
// @ 0x00683f10  AddRef: (interlocked_xadd(this+4, 2) + 2) >> 1
// =====================================================================
struct RefCounted {
    void* vtbl;                         // +0x00
    volatile int mRef;                  // +0x04
    int AddRef();
    int Release();
};
int RefCounted::AddRef() {
    return (int)((_InterlockedExchangeAdd((volatile long*)&mRef, 2) + 2) >> 1);
}

// =====================================================================
// @ 0x00683f30  Release
// =====================================================================
int RefCounted::Release() {
    int n = _InterlockedExchangeAdd((volatile long*)&mRef, -2) - 2;
    if (n == 0) {
        _InterlockedExchange((volatile long*)&mRef, 2);
        if (this != 0) {
            ((void (__thiscall*)(void*, int))VT(this)[2])(this, 1);
            return n;
        }
    } else if (n == 3 && *(void**)((char*)this + 0x14) != 0) {
        void* p = *(void**)((char*)this + 0x14);
        ((void (__thiscall*)(void*, void*))VT(p)[0])(p, this);
    }
    return n;
}
