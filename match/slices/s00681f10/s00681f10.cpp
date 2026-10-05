// Slice s00681f10: SP/EA serialization container code, continuation of the
// UTFKernel-era module begun in s00680c30 (0x00680c30..0x00681e80).
// These are members of the same serialization factory: int-keyed EASTL
// rbtree maps and vector<...> serializers built on the abstract reader/writer
// interfaces (vtable slot 0x30 = Read, 0x38 = Write).
//
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE). Out-of-slice callees are
// externs; relocation targets are masked by the verifier.
#include "types.h"

inline void* operator new(uint32_t, void* p) { return p; }

// ---- abstract streams (vtable slots) ----
struct IWrt {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void vC(); virtual void vD();
    virtual void Write(const void* p, int n);       // slot 14 (0x38)
};
struct IRd {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void Read(void* p, int n);              // slot 12 (0x30)
};

// ---- out-of-slice callees ----
extern "C" void* MemcpyT(void* dst, const void* src, uint32_t n);        // 0x011e0744
extern "C" void  EASTL_dealloc(void* p);                                 // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t n, void* tag, uint32_t a, uint32_t b,
                              const char* file, uint32_t line);          // 0x0f473a0
extern "C" char  g_allocTag[];                                           // 0x013ebc58 "App"
extern "C" char  g_fileEASTL[];                                          // 0x013ebb38 allocator.h
extern "C" void __cdecl WriteUint32(void* s, void* p, int n, int flags); // 0x093aa70
extern "C" void __cdecl ReadInt32(void* s, void* p, int n, int flags);   // 0x093a780
extern "C" void __cdecl WriteByte(void* s, void* p, int n);              // 0x093a9a0
extern "C" void* __cdecl RBTreeIncrement(void* node);                    // 0x0921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                    // 0x09215c0
extern "C" void  __cdecl RBTreeInsert(void* nodeNew, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" void  __cdecl RangeInitialize(void* s, int n);                // 0x0475ab0
extern "C" void  __cdecl StringResize(void* s, int n);                   // 0x047bf30
extern "C" void  __cdecl UninitCopy(void** out, void* first, void* last, void* dst, void* last2); // 0x0681ca0
extern "C" void  __cdecl Obj1700Ctor(void* dst, const void* src);        // 0x0681700
extern "C" void  __cdecl Obj1800Ctor(void* dst, const void* src);        // 0x0681800
extern "C" void  __cdecl ObjACtor(void* dst, const void* src);           // 0x0681a10
extern "C" void  __cdecl ObjC30Ctor(void* dst, const void* src);         // 0x0680c30
extern "C" void  __cdecl M5a0Ctor(void* dst, const void* src);           // 0x0680a50
extern "C" void  __cdecl M5a0Dtor(void* p);                              // 0x0680730
extern "C" void  __cdecl VV12Dtor(void* p);                              // 0x0681160
extern "C" void* __cdecl CreateNode1(const void* pair);                  // 0x06811d0 (value ObjC30)
extern "C" void* __cdecl CreateNode2(const void* pair);                  // 0x06826c0 (value Obj1700)
extern "C" void  __cdecl FreeNodesC2(void* self, void* root);            // 0x0681480
extern "C" void  __cdecl SaveVec390(void* self, void* v, IWrt* w);       // 0x0680390
extern "C" void  __cdecl SaveObj500(void* self, void* o, IWrt* w);       // 0x0680500
extern "C" void  __cdecl SaveObj5c0(void* self, void* o, IWrt* w);       // 0x06805c0
extern "C" void  __cdecl LoadEntries(void* self, void* out, IRd* r);     // 0x06812c0

struct PairOut2 { void* first; bool second; };

// =====================================================================
// stub classes (layouts read from the disassembly)
// =====================================================================

// 12-byte byte string (EASTL guard (cap - begin) > 1)
struct S8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    S8() {}
    void Init(int n);                           // 0x0475ab0 RangeInitialize
    __forceinline S8(const S8& x) {
        mpBegin = 0; mpEnd = 0; mpCap = 0;
        char* xEnd = x.mpEnd;
        char* xBegin = x.mpBegin;
        int n = xEnd - xBegin;
        Init(n + 1);
        MemcpyT(mpBegin, xBegin, (uint32_t)n);
        mpEnd = mpBegin - xBegin + xEnd;
        *mpEnd = 0;
    }
    ~S8() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};

// 20-byte vector with an 8-byte (header-word) allocator
struct V20 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    ~V20() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_dealloc(mpBegin); }
};

// M5a0: vector of 0x48-byte entries (cString at entry+0x28), 20 bytes
struct M5a0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    M5a0() {}
    M5a0(const M5a0& o);                        // 0x0680a50 (out-of-slice)
    ~M5a0();                                    // 0x0680730
};

// vector of 0xc4-byte elements (Obj1800), 12 bytes
struct VV12 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    ~VV12();                                    // 0x0681160
    VV12() {}
    VV12(const VV12& o);                        // 0x0682740 (below)
};

struct ObjC30 {
    S8 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    M5a0 mVec;                                  // +0x10
    ObjC30(const ObjC30& o);                    // 0x0680c30 (out-of-slice)
};

struct Obj1700 {
    S8 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    V20 mF0;                                    // +0x10
    V20 mF1;                                    // +0x24
    Obj1700(const Obj1700& o);                  // 0x0681700 (out-of-slice)
};

struct Obj2A10 {
    S8 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    uint8_t b10, b11, b12, b13, b14;            // +0x10
    uint8_t pad15[3];                           // +0x15
    uint32_t w18, w1c, w20, w24;                // +0x18
    M5a0 mM;                                    // +0x28
    VV12 mVec;                                  // +0x3c
    Obj2A10(const Obj2A10& o);                  // 0x0682a10 (below)
    // implicit ~Obj2A10() is generated inline (calls ~VV12, ~M5a0, ~S8)
};

struct Pod16 { uint32_t w[4]; };
struct ObjA {
    Pod16 m0;                                   // +0x00
    V20 mF0;                                    // +0x10
    V20 mF1;                                    // +0x24
    V20 mF2;                                    // +0x38
    V20 mF3;                                    // +0x4c
    ObjA(const ObjA& o);                        // 0x0681a10 (out-of-slice)
};

struct Obj1800 {
    uint32_t w0[24];                            // +0x00 (0x60)
    uint32_t mFlag;                             // +0x60
    uint8_t pad64[0x74 - 0x64];
    V20 mF0;                                    // +0x74
    V20 mF1;                                    // +0x88
    V20 mF2;                                    // +0x9c
    V20 mF3;                                    // +0xb0
    Obj1800(const Obj1800& o);                  // 0x0681800 (out-of-slice)
};

// rbtree node with value Obj1700 (node size 0x4c)
struct Node2 {
    Node2* mpRight;                             // +0x00
    Node2* mpLeft;                              // +0x04
    Node2* mpParent;                            // +0x08
    uint32_t mColor;                            // +0x0c
    int mKey;                                   // +0x10
    Obj1700 mVal;                               // +0x14
};

struct Map2 {
    uint32_t pad0;                              // +0x00
    Node2* mpAnchor;                            // +0x04
    Node2* mpBegin;                             // +0x08
    Node2* mpRoot;                              // +0x0c
    uint32_t mColor;                            // +0x10
    uint32_t mnSize;                            // +0x14
    uint32_t mAlloc;                            // +0x18
    Node2* Clone(Node2* src, Node2* parent);                // 0x0682be0 (below)
    void InsertHint(Node2** out, Node2* hint, int* key, char flag); // 0x06828a0 (below)
    void InsertUnique(PairOut2* out, const int* key);       // 0x0682900 (below)
};

// rbtree node with value ObjC30 (node size 0x38)
struct Node1 {
    Node1* mpRight;
    Node1* mpLeft;
    Node1* mpParent;
    uint32_t mColor;
    int mKey;                                   // +0x10
    ObjC30 mVal;                                // +0x14
};
struct Map1 {
    uint32_t pad0;
    Node1* mpAnchor;                            // +0x04
    Node1* mpBegin;                             // +0x08
    Node1* mpRoot;                              // +0x0c
    uint32_t mColor;                            // +0x10
    uint32_t mnSize;                            // +0x14
    uint32_t mAlloc;                            // +0x18
    void InsertHint(Node1** out, Node1* hint, int* key, char flag); // 0x06825d0 (below)
    void InsertUnique(PairOut2* out, const int* key);               // 0x06815f0 (out-of-slice)
    ObjC30* operator[](int key);                // 0x0682af0 (below)
};

// rbtree node with value Obj2A10 (node size 0x60)
struct Node3 {
    Node3* mpRight;
    Node3* mpLeft;
    Node3* mpParent;
    uint32_t mColor;
    int mKey;                                   // +0x10
    Obj2A10 mVal;                               // +0x14
};
struct Map3 {
    uint32_t pad0;
    Node3* mpAnchor;
    Node3* mpBegin;
    Node3* mpRoot;
    uint32_t mColor;
    uint32_t mnSize;
    uint32_t mAlloc;
    void FreeNodes(Node3* p);                   // 0x0682800 (below)
};

// guarded EASTL byte buffer: (cap - begin) > 1 && begin
struct Buf {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    ~Buf() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};

// map whose destructor frees the node chain via out-of-slice 0x0681480
struct MapC2 {
    uint32_t pad0;                              // +0x00
    void* mpAnchor;                             // +0x04
    void* mpBegin;                              // +0x08
    void* mpRoot;                               // +0x0c
    ~MapC2() { FreeNodes(mpRoot); }
    void FreeNodes(void* p);                    // 0x0681480 (out-of-slice)
};

// class destroyed by 0x00682060: buffer at +0, rbtree map at +0x10
struct Cls60 {
    Buf mVec;                                   // +0x00
    MapC2 mMap;                                 // +0x10
    ~Cls60();
};

// =====================================================================
// @ 0x00681f10  write map<int, Obj1700>
// =====================================================================
void WriteMap1700(Map2* map, IWrt* w, void* self) {
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    Node2* anchor = (Node2*)&map->mpAnchor;
    for (Node2* p = map->mpBegin; p != anchor; p = (Node2*)RBTreeIncrement(p)) {
        int key = p->mKey;
        Obj1700 tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mStr.mpBegin, len);
        SaveVec390(self, &tmp.mF0, w);
        SaveVec390(self, &tmp.mF1, w);
    }
}

// =====================================================================
// @ 0x00682060  destroy { buffer, rbtree } at this
// =====================================================================
Cls60::~Cls60() {}

// =====================================================================
// @ 0x006820c0  write vector<Obj1800> (stride 0xc4)
// =====================================================================
void WriteVec1800(Obj1800* first, Obj1800* last, IWrt* w, void* self) {
    int n = (int)((char*)last - (char*)first) / 0xc4;
    w->Write(&n, 4);
    for (Obj1800* p = first; p != last; p = (Obj1800*)((char*)p + 0xc4)) {
        Obj1800 tmp(*p);
        SaveObj500(self, &tmp.w0[0], w);
        SaveObj500(self, &tmp.w0[4], w);
        SaveObj500(self, &tmp.w0[8], w);
        SaveObj500(self, &tmp.w0[12], w);
        int v = 0;
        w->Write(&v, 4);
        WriteUint32(w, &v, 1, 0);
        WriteUint32(w, &v, 1, 0);
        WriteUint32(w, &v, 1, 0);
        SaveObj5c0(self, &tmp.mFlag, w);
    }
}

// =====================================================================
// @ 0x006823f0  write vector<ObjA> (stride 0x60)
// =====================================================================
void WriteVecA(ObjA* first, ObjA* last, IWrt* w, void* self) {
    int n = (int)((char*)last - (char*)first) / 0x60;
    w->Write(&n, 4);
    for (ObjA* p = first; p != last; p = (ObjA*)((char*)p + 0x60)) {
        ObjA tmp(*p);
        w->Write(&tmp.m0.w[0], 4);
        w->Write(&tmp.m0.w[1], 4);
        w->Write(&tmp.m0.w[2], 4);
        int len = (int)(tmp.mF0.mpEnd - tmp.mF0.mpBegin);
        w->Write(&len, 4);
        for (int i = 0; i < len; ++i)
            w->Write(tmp.mF0.mpBegin + i * 4, 4);
    }
}

// =====================================================================
// @ 0x006825d0  Map1 insert with hint
// =====================================================================
void Map1::InsertHint(Node1** out, Node1* hint, int* key, char flag) {
    Node1* anchor = (Node1*)&mpAnchor;
    if (hint == mpBegin || hint == anchor) {
        if (mnSize != 0 && *key > mpBegin->mKey) {
            int bIns = (mpBegin == anchor || *key < mpBegin->mKey) ? 0 : 1;
            Node1* nNew = (Node1*)CreateNode1(key);
            RBTreeInsert(nNew, mpBegin, anchor, bIns);
            ++mnSize;
            *out = nNew;
            return;
        }
    } else {
        Node1* next = (Node1*)RBTreeIncrement(hint);
        if (*key > hint->mKey && next->mKey > *key) {
            if (hint->mpRight == 0) {
                Node1* nNew = (Node1*)CreateNode1(key);
                RBTreeInsert(nNew, hint, anchor, 0);
                ++mnSize;
                *out = nNew;
                return;
            }
            Node1* nNew = (Node1*)CreateNode1(key);
            RBTreeInsert(nNew, next, anchor, 1);
            ++mnSize;
            *out = nNew;
            return;
        }
    }
    PairOut2 pair;
    pair.first = 0;
    InsertUnique(&pair, key);
    *out = (Node1*)pair.first;
}

// =====================================================================
// @ 0x00682740  copy-construct vector<Obj1800> (stride 0xc4)
// =====================================================================
VV12::VV12(const VV12& o) {
    int n = (int)(o.mpEnd - o.mpBegin) / 0xc4;
    char* p = n ? (char*)EASTL_alloc6((uint32_t)n * 0xc4, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
    mpBegin = p;
    mpEnd = p;
    mpCap = p + n * 0xc4;
    UninitCopy((void**)&mpEnd, o.mpBegin, o.mpEnd, p, (void*)&o);
}

// =====================================================================
// @ 0x00682800  free Map3 node chain
// =====================================================================
void Map3::FreeNodes(Node3* p) {
    while (p) {
        FreeNodes(p->mpRight);
        Node3* next = p->mpLeft;
        p->mVal.~Obj2A10();
        EASTL_dealloc(p);
        p = next;
    }
}

// =====================================================================
// @ 0x006828a0  Map2 insert with hint
// =====================================================================
void Map2::InsertHint(Node2** out, Node2* hint, int* key, char flag) {
    Node2* anchor = (Node2*)&mpAnchor;
    int bIns;
    if (flag == 0 && hint != anchor && hint->mKey <= *key)
        bIns = 1;
    else
        bIns = 0;
    Node2* nNew = (Node2*)CreateNode2(key);
    RBTreeInsert(nNew, hint, anchor, bIns);
    ++mnSize;
    *out = nNew;
}

// =====================================================================
// @ 0x00682900  Map2 insert-unique with hint -> pair<iter,bool>
// =====================================================================
void Map2::InsertUnique(PairOut2* pairOut, const int* key) {
    Node2* anchor = (Node2*)&mpAnchor;
    Node2* pos = anchor;
    int bLess = 1;
    Node2* n = mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpRight : n->mpLeft;
        } while (n);
    }
    Node2* found = pos;
    if (bLess) {
        if (pos == mpBegin) {
            int bIns = (pos != anchor && *key >= pos->mKey) ? 1 : 0;
            Node2* nNew = (Node2*)CreateNode2(key);
            RBTreeInsert(nNew, pos, anchor, bIns);
            ++mnSize;
            pairOut->first = nNew;
            pairOut->second = true;
            return;
        }
        pos = (Node2*)RBTreeDecrement(pos);
    }
    if (pos->mKey >= *key) {
        pairOut->first = pos;
        pairOut->second = false;
        return;
    }
    {
        int bIns = (found != anchor && *key >= found->mKey) ? 1 : 0;
        Node2* nNew = (Node2*)CreateNode2(key);
        RBTreeInsert(nNew, found, anchor, bIns);
        ++mnSize;
        pairOut->first = nNew;
        pairOut->second = true;
    }
}

// =====================================================================
// @ 0x00682a10  Obj2A10 copy ctor
// =====================================================================
Obj2A10::Obj2A10(const Obj2A10& o)
    : mStr(o.mStr), b10(o.b10), b11(o.b11), b12(o.b12), b13(o.b13), b14(o.b14),
      w18(o.w18), w1c(o.w1c), w20(o.w20), w24(o.w24), mM(o.mM), mVec(o.mVec) {}

// =====================================================================
// @ 0x00682af0  Map1 operator[] -> &value
// =====================================================================
ObjC30* Map1::operator[](int key) {
    Node1* anchor = (Node1*)&mpAnchor;
    Node1* pos = anchor;
    Node1* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) {
            pos = cur;
            cur = cur->mpLeft;
        } else {
            cur = cur->mpRight;
        }
    }
    if (pos == anchor || pos->mKey < key) {
        int tmp[10];
        tmp[0] = key;
        Node1* nNew = (Node1*)CreateNode1(tmp);
        Node1** out = &nNew;
        InsertHint(out, pos, tmp, 0);
        return &(*out)->mVal;
    }
    return &pos->mVal;
}

// =====================================================================
// @ 0x00682be0  clone Map2 tree (eastl rbtree copy)
// =====================================================================
Node2* Map2::Clone(Node2* src, Node2* parent) {
    Node2* dst = (Node2*)CreateNode2(&src->mKey);
    dst->mpRight = 0;
    dst->mpLeft = 0;
    dst->mpParent = parent;
    dst->mColor = src->mColor;
    if (src->mpRight)
        dst->mpRight = Clone(src->mpRight, dst);
    Node2* cur = dst;
    for (Node2* sib = src->mpLeft; sib != 0; sib = sib->mpLeft) {
        Node2* n = (Node2*)CreateNode2(&sib->mKey);
        n->mpRight = 0;
        n->mpLeft = 0;
        n->mpParent = cur;
        n->mColor = sib->mColor;
        cur->mpLeft = n;
        if (sib->mpRight)
            n->mpRight = Clone(sib->mpRight, n);
        cur = n;
    }
    return dst;
}

// =====================================================================
// @ 0x00682ca0  write Map3<int, Obj2A10>
// =====================================================================
void WriteMap2A10(Map3* map, IWrt* w, void* self) {
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    Node3* anchor = (Node3*)&map->mpAnchor;
    for (Node3* p = map->mpBegin; p != anchor; p = (Node3*)RBTreeIncrement(p)) {
        int key = p->mKey;
        Obj2A10 tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mStr.mpBegin, len);
        WriteByte(w, &tmp.b10, 1);
        WriteByte(w, &tmp.b11, 1);
        WriteByte(w, &tmp.b12, 1);
        WriteByte(w, &tmp.b13, 1);
        WriteByte(w, &tmp.b14, 1);
        w->Write(&tmp.w18, 4);
        WriteUint32(w, &tmp.w18, 1, 0);
        WriteUint32(w, &tmp.w18, 1, 0);
        WriteUint32(w, &tmp.w18, 1, 0);
        SaveObj5c0(self, &tmp.mM, w);
        WriteVec1800((Obj1800*)tmp.mVec.mpBegin, (Obj1800*)tmp.mVec.mpEnd, w, self);
    }
}

// =====================================================================
// @ 0x00682e90  load Map1<int, ObjC30>
// =====================================================================
void LoadMap1(Map1* map, IRd* r, void* self) {
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        ObjC30* val = map->operator[](key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            StringResize(&val->mStr, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        LoadEntries(self, &val->mVec, r);
    }
}
