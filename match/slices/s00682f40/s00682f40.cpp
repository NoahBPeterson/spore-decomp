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
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
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
extern "C" void  __cdecl Destroy1800(void*, void*);               // 0x0680bf0
extern "C" void  __cdecl CopyBackwardA(void*, void*, void*);      // 0x0681e80
extern "C" void* __cdecl MoveBackNA(void*, void*, void*);         // 0x0681db0
extern "C" void  __cdecl DestroyA(void*, void*);                  // 0x0680800
extern "C" void  __cdecl Obj1700Ctor(void*, const void*);         // 0x0681700
extern "C" void  __cdecl Obj1800Ctor(void*, const void*);         // 0x0681800
extern "C" void  __cdecl ObjACtor(void*, const void*);            // 0x0681a10
extern "C" void  __cdecl ObjB50Assign(void*, const void*);        // 0x0681b50
extern "C" void  __cdecl ObjAAssign(void*, const void*);          // 0x0681c40
extern "C" void  __cdecl LoadEntries(void*, void*, IRd*);         // 0x06812c0
extern "C" void  __cdecl ReadCStringKey(void*, void*, IRd*);      // 0x0680560
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
    void InsertUnique(void* pair, const int* key);
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
struct Node2v { Node2v* r; Node2v* l; Node2v* p; uint32_t col; int key; Obj1700 val; };
struct Map2 {
    uint32_t pad0; Node2v* anchor; Node2v* begin; Node2v* root; uint32_t col;
    uint32_t size; uint32_t alloc;
    void InsertHint(Node2v** out, Node2v* hint, int* key, char flag);
    void InsertUnique(void* pair, const int* key);
    Obj1700* operator[](int key);
};

// =====================================================================
// @ 0x00682f40  vector<Obj1800>::insert(pos, value)  [thiscall, ret 8]
// =====================================================================
struct Vec1800 { Obj1800* begin; Obj1800* end; Obj1800* cap; };
void Vec1800Insert(Vec1800* self, Obj1800* pos, const Obj1800& x) {
    Obj1800* end = self->end;
    if (end != self->cap) {
        Obj1800* xAdj = (Obj1800*)&x;
        if (xAdj >= pos && xAdj < end) xAdj = (Obj1800*)((char*)xAdj + 0xc4);
        if (end) Obj1800Ctor((char*)end - 0xc4, (char*)end - 0xc4);
        CopyBackward1800(pos, (char*)self->end - 0xc4, self->end);
        ObjB50Assign(pos, xAdj);
        self->end = (Obj1800*)((char*)self->end + 0xc4);
    } else {
        int n = (int)((char*)end - (char*)self->begin) / 0xc4;
        int cap;
        if (n == 0) cap = 1;
        else { cap = n * 2; if (cap == 0) cap = 0; }
        char* p = cap ? (char*)EASTL_alloc6((uint32_t)cap * 0xc4, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
        char* mid = (char*)MoveBackN1800(self->begin, (char*)&x, p);
        Destroy1800(self->begin, (char*)&x);
        char* e = (char*)self->end;
        char* mid2 = (char*)MoveBackN1800((void*)&x, e, mid + 0xc4);
        Destroy1800((void*)&x, e);
        if (self->begin && ((int*)self->begin)[-1]) EASTL_dealloc(self->begin);
        self->end = (Obj1800*)mid2;
        self->begin = (Obj1800*)p;
        self->cap = (Obj1800*)(p + cap * 0xc4);
    }
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
// @ 0x006831f0  vector<ObjA>::insert(pos, value)  [thiscall, ret 8]
// =====================================================================
struct VecA { ObjA* begin; ObjA* end; ObjA* cap; };
void VecAInsert(VecA* self, ObjA* pos, const ObjA& x) {
    ObjA* end = self->end;
    if (end != self->cap) {
        ObjA* xAdj = (ObjA*)&x;
        if (xAdj >= pos && xAdj < end) xAdj = (ObjA*)((char*)xAdj + 0x60);
        if (end) ObjACtor((char*)end - 0x60, (char*)end - 0x60);
        CopyBackwardA(pos, (char*)self->end - 0x60, self->end);
        ObjAAssign(pos, xAdj);
        self->end = (ObjA*)((char*)self->end + 0x60);
    } else {
        int n = (int)((char*)end - (char*)self->begin) / 0x60;
        int cap;
        if (n == 0) cap = 1;
        else { cap = n * 2; if (cap == 0) cap = 0; }
        char* p = cap ? (char*)EASTL_alloc6((uint32_t)cap * 0x60, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
        char* mid = (char*)MoveBackNA(self->begin, (char*)&x, p);
        DestroyA(self->begin, (char*)&x);
        char* e = (char*)self->end;
        char* mid2 = (char*)MoveBackNA((void*)&x, e, mid + 0x60);
        DestroyA((void*)&x, e);
        if (self->begin && ((int*)self->begin)[-1]) EASTL_dealloc(self->begin);
        self->end = (ObjA*)mid2;
        self->begin = (ObjA*)p;
        self->cap = (ObjA*)(p + cap * 0x60);
    }
}

// =====================================================================
// @ 0x00683390  Map2 insert-with-hint (value Obj1700)
// =====================================================================
void Map2::InsertHint(Node2v** out, Node2v* hint, int* key, char flag) {
    (void)flag;
    Node2v* hdr = (Node2v*)&anchor;
    if (hint == begin || hint == hdr) {
        if (size == 0 || *key <= begin->key)
            goto UNIQUE;
        {
            int bIns = (begin == hdr || *key < begin->key) ? 0 : 1;
            Node2v* n = (Node2v*)CreateNode1700(key);
            RBTreeInsert(n, begin, hdr, bIns);
            ++size;
            *out = n;
            return;
        }
    } else {
        Node2v* next = (Node2v*)RBTreeIncrement(hint);
        if (*key <= hint->key || next->key <= *key)
            goto UNIQUE;
        if (hint->r == 0) {
            void* n = CreateNode1700(key);
            RBTreeInsert(n, hint, hdr, 0);
            ++size;
            *out = (Node2v*)n;
            return;
        }
        {
            Node2v* n = (Node2v*)CreateNode1700(key);
            RBTreeInsert(n, next, hdr, 1);
            ++size;
            *out = n;
            return;
        }
    }
UNIQUE:
    {
        void* pair[2];
        pair[0] = 0;
        InsertUnique(pair, key);
        *out = (Node2v*)pair[0];
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
void MapY::InsertUnique(void* pairOut, const int* key) {
    NodeY* hdr = (NodeY*)&anchor;
    NodeY* pos = hdr;
    int bLess = 1;
    NodeY* n = root;
    if (n) {
        do { pos = n; bLess = (*key < n->key); n = bLess ? n->r : n->l; } while (n);
    }
    NodeY* found = pos;
    if (bLess) {
        if (pos == begin) {
            int bIns = (pos != hdr && *key >= pos->key) ? 1 : 0;
            NodeY* nn = (NodeY*)CreateNodeZ(key);
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
        NodeY* nn = (NodeY*)CreateNodeZ(key);
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
// @ 0x00683700  load vector<Obj1800> (partial)
// =====================================================================
extern "C" void LoadObj1800(void* self, void* vec, IRd* r) {
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        // (full body not reconstructed; see partial.txt)
        (void)r;
    }
}

// =====================================================================
// @ 0x00683ab0  load vector<ObjA> (partial)
// =====================================================================
extern "C" void LoadObjA(void* self, void* vec, IRd* r) {
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        (void)r;
    }
}

// =====================================================================
// @ 0x00683d10  Map2 operator[] -> &value
// =====================================================================
Obj1700* Map2::operator[](int key) {
    Node2v* hdr = (Node2v*)&anchor;
    Node2v* pos = hdr;
    Node2v* cur = root;
    while (cur) {
        if (cur->key < key) { pos = cur; cur = cur->r; }
        else cur = cur->l;
    }
    if (pos == hdr || pos->key < key) {
        int tmp[10];
        tmp[0] = key;
        Node2v* n = (Node2v*)CreateNode1700(tmp);
        Node2v** out = &n;
        InsertHint(out, pos, tmp, 0);
        return &(*out)->val;
    }
    return &pos->val;
}

// =====================================================================
// @ 0x00683e90  SP::cPropertyList constructor
// =====================================================================
struct ListHdr { ListHdr* next; ListHdr* prev; };
struct cPropertyList {
    void* vtbl;                         // +0x00
    volatile int mRef;                  // +0x04
    uint32_t f08, f0c, f10, f14;
    ListHdr m18;                        // +0x18
    ListHdr m1c;                        // +0x1c .. placeholder
    uint32_t f20, f24;
    uint8_t f28;
    uint32_t f2c, f30, f34;
    ListHdr m38;                        // +0x38
    uint8_t f44;
    uint32_t f48, f4c, f50;
    ListHdr m54;                        // +0x54
    uint32_t f58, f5c;
    uint8_t f60;
    uint32_t f64, f68;
    uint32_t f6c, f70, f74;
    cPropertyList();
};
cPropertyList::cPropertyList() {
    vtbl = 0;
    mRef = 0;
    f08 = 0; f0c = 0; f10 = 0; f14 = 0;
    f20 = 0; f24 = 0; f28 = 0; f2c = 0;
    f30 = 0; f34 = 0;
    m38.next = 0; m38.prev = 0; f44 = 0;
    f48 = 0; f4c = 0; f50 = 0;
    m54.next = 0; m54.prev = 0; f58 = 0; f5c = 0;
    f60 = 0; f64 = 0; f68 = 0;
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
