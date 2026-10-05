// Slice s00680c30: SP serialization container code around 0x680000 (UTFKernel-era
// module compiled /O2, no SSE): byte-buffer string + int keys, vector<N48> insert /
// operator=, rbtree map insert helpers, serializer/deserializer methods and
// vector<float> copy ctors / operator= / copy_backward.
//
// Out-of-slice callees are externs; relocation targets are masked by the verifier.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// ---- out-of-slice callees / globals ----
extern "C" void* MemcpyT(void* dst, const void* src, uint32_t n);        // 0x011e0744 (memcpy thunk)
extern "C" void EASTL_dealloc(void* p);                                  // 0x0f47380 EASTL_allocator_deallocate
extern "C" void* EASTL_alloc6(uint32_t n, void* tag, uint32_t a, uint32_t b,
                              const char* file, uint32_t line);          // 0x0f473a0 EASTL_allocator_allocate
extern "C" char g_allocTag[];                                            // 0x013ebc58 "App"
extern "C" char g_fileEASTL[];                                           // 0x013ebb38 allocator.h path
extern "C" void __cdecl WriteUint32(void* s, void* p, int n, int flags); // 0x093aa70
extern "C" void __cdecl ReadInt32(void* s, void* p, int n, int flags);   // 0x093a780
extern "C" void* __cdecl RBTreeIncrement(void* node);                    // 0x0921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                    // 0x09215c0
extern "C" void __cdecl RBTreeInsert(void* nodeNew, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" void __cdecl MoveBack_300(void* first, void* last, void* destLast); // 0x00680300
extern "C" void* __cdecl CopyN_270(void* first, void* last, void* dest); // 0x00680270
extern "C" void* __cdecl CopyN_1a0(void* first, void* last, void* dest); // 0x006801a0
extern "C" void  __cdecl CopyN_230(void* first, void* last, void* dest); // 0x00680230
extern "C" void  __cdecl CtorN_420(void** pv, void* first, void* last, void* dest, void* last2); // 0x00680420

// ---- stub classes (layouts observed in the disassembly) ----

// byte string, EASTL shape: guard is (cap - begin) > 1 && begin
struct S8 {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    void Init(int n);                       // 0x00475ab0 RangeInitialize
    ~S8() {
        if ((int)(mpEndCap - mpBegin) > 1 && mpBegin)
            EASTL_dealloc(mpBegin);
    }
    __forceinline S8(const S8& x) {
        mpBegin = 0;
        mpEnd = 0;
        mpEndCap = 0;
        char* xEnd = x.mpEnd;
        char* xBegin = x.mpBegin;
        int n = xEnd - xBegin;
        Init(n + 1);
        MemcpyT(mpBegin, xBegin, (uint32_t)n);
        mpEnd = mpBegin - xBegin + xEnd;
        *mpEnd = 0;
    }
};

// element of the 0x48-stride vector
struct N48 {
    uint32_t v[18];
    N48(const N48&);                        // 0x00680130-ish construct helpers
    ~N48();
};

// shared-buffer string / vector guard: p && p[-1] (header word in front)
struct SStrA {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    ~SStrA() {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_dealloc(mpBegin);
    }
};

// plain buffer guard: (cap - begin) > 1 && begin
struct SStrB {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    ~SStrB() {
        if ((int)(mpEndCap - mpBegin) > 1 && mpBegin)
            EASTL_dealloc(mpBegin);
    }
};

// helper receiving this in ecx on a raw node
struct NC0 { void Fix(NC0* prev); };        // 0x006800c0

// vector of N48
struct V48 {
    N48* mpBegin;
    N48* mpEnd;
    N48* mpEndCap;
    N48* ReallocN7a0(int n, N48* first, N48* last);   // 0x006807a0
    void Destroy3f0(N48* first, N48* last);           // 0x006803f0
    void insert(N48* pos, const N48& x);              // 0x00680cc0 (below)
    V48& operator=(const V48* other);                 // 0x00680e70 (below)
};

// float vector with 8-byte (2-word) allocator
struct VF {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    void* mTag[2];
    void Reserve(int n, void* tag);                   // 0x004aa350
    VF& operator=(const VF& x);                       // 0x0050d4e0
    ~VF();
    __forceinline VF(const VF& x) {
        Reserve((int)(x.mpEnd - x.mpBegin) >> 2, (void*)x.mTag);
        int n = (int)(x.mpEnd - x.mpBegin);
        mpEnd = (char*)((uint32_t*)MemcpyT(mpBegin, x.mpBegin, (uint32_t)n) + (n >> 2));
    }
};

struct Pod16 { uint32_t w[4]; };
struct Pod60 { uint32_t w[24]; };

// member whose copy ctor is 0x00680a50 (value object at obj+0x10)
struct M5a0 {
    char c;
    M5a0() {}
    M5a0(const M5a0& x);                    // 0x00680a50
    ~M5a0();
};

// value object copied by 0x00680c30 / 0x00680fc0's map nodes
struct ObjC30 {
    S8 mStr;                                // +0x00
    char pad[4];
    M5a0 mM;                                // +0x10
    ObjC30(const ObjC30& other);            // 0x00680c30 (below)
};

// rbtree node: { right, left, pad2, key, value }
struct RNode {
    RNode* mpRight;                         // +0
    RNode* mpLeft;                          // +4
    uint32_t pad[2];                        // +8
    int mKey;                               // +0x10
    ObjC30 mVal;                            // +0x14
};

// out params for InsertUnique (pair of ptr + bool)
struct PairOut { RNode* first; bool second; };

struct RAnchor {
    uint32_t pad;
    RNode* mpBegin;                         // +8 from map start
    RNode* mpRoot;                          // +0xc
    RNode* mpParent;                        // +0x10
};

struct MapV {
    char pad0[4];
    RAnchor mAnchor;                        // +4
    int mnSize;                             // +0x14
    RNode* CreateNode(const int* key);      // 0x006811d0
    void InsertPair(RNode** pOut, RNode* pos, int* key, bool bAllowEquiv); // 0x00681590 (below)
    void InsertUnique(PairOut* pOut, const int* key);                     // 0x006815f0 (below)
};

// stream interfaces (vtable slots)
struct IRd12 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void Read(void* p, int n);      // slot 12 (0x30)
};
struct IWrt14 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void vC(); virtual void vD();
    virtual void Write(const void* p, int n);   // slot 14 (0x38)
};

// vector<unsigned int> (sp allocator), used by 0x00681250
struct VU32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpEndCap;
    void DoIns_4558a0(uint32_t* pos, int* val);   // 0x004558a0
};

// 20-byte string object read by FUN_00680560 (sp allocator)
struct S16 {
    void* f0;
    void* f4;
    void* f8;
    void* fC;
    void* f10;
    S16() { f0 = 0; f4 = 0; f8 = 0; fC = 0; f10 = 0; }
};

// SP::cString (light view)
struct SPString {
    char pad[0x14];
    int mTableId;                           // +0x14
    int mInstanceId;                        // +0x18
    int mX;                                 // +0x1c
    SPString();                             // 0x006b5060
    void Load(int a, int b, int c);         // 0x006b54b0
    const char* c_str();                    // 0x006b5240
};

// RAII thing used in the serializer loop (dtor = FUN_00680730)
struct Thing {
    char pad[0x14];
    Thing() {}
    ~Thing();                               // 0x00680730
};

// method-owner for 0x00680fc0
struct WF80 {
    void __thiscall Make5c0(Thing* t, IWrt14* w);   // 0x006805c0
};

// class destroyed by 0x00681400
struct T28 { ~T28(); };                     // 0x00680730
struct T1160 { ~T1160(); };                 // 0x00681160
struct Cls1400 {
    SStrB mVec;                             // +0x00 (inline dtor)
    char pad0[0x28 - 12];
    T28 m28;                                // +0x28
    char pad1[0x3c - 0x28 - 1];
    T1160 m3c;                              // +0x3c
    ~Cls1400();
};

// node chain freed by 0x00681480
struct Node1480 {
    Node1480* mpDown;                       // +0
    void* mpNext;                           // +4
    char pad0[0xC];
    SStrB m14;                              // +0x14
    char padM[4];
    SStrA m24;                              // +0x24
    char pad1[8];
    SStrA m38;                              // +0x38
};
struct MapC2 {
    void FreeNodes(Node1480* p);            // 0x00681480 (below)
};

// node chain freed by 0x00681500
struct Node15 {
    Node15* mpDown;                         // +0
    void* mpNext;                           // +4
    char pad0[0x14 - 8];
    SStrB m14;                              // +0x14
    char pad1[0x24 - 0x14 - 12];
    T28 m24;                                // +0x24
};
struct MapC0 {
    void FreeChain2(Node15* p);             // 0x00681500 (below)
};

// container receiving entries in 0x006812c0
struct ContC {
    void __thiscall AddEntry10e0(void* p);  // 0x006810e0
};

// big value object copied by 0x00681800
struct Obj1800 {
    Pod60 m0;                               // +0x00
    M5a0 mM;                                // +0x60
    char pad[0x74 - 0x60 - 1];
    VF mF0;                                 // +0x74
    VF mF1;                                 // +0x88
    VF mF2;                                 // +0x9c
    VF mF3;                                 // +0xb0
    Obj1800(const Obj1800& other);          // 0x00681800 (below)
};

// object copied by 0x00681700
struct Obj1700 {
    S8 mStr;                                // +0x00
    VF mF0;                                 // +0x10
    VF mF1;                                 // +0x24
    Obj1700(const Obj1700& other);          // 0x00681700 (below)
};

// { 4 dwords + 4 float vectors }: copy ctor 0x00681a10, operator= 0x00681c40
struct ObjA {
    Pod16 m0;                               // +0x00
    VF mF0;                                 // +0x10
    VF mF1;                                 // +0x24
    VF mF2;                                 // +0x38
    VF mF3;                                 // +0x4c
    ObjA(const ObjA& other);                // 0x00681a10 (below)
    ObjA& operator=(const ObjA& x);         // 0x00681c40 (below)
};

// { 0x60 bytes + vector<N48> + 4 float vectors }: operator= 0x00681b50
struct ObjB50 {
    Pod60 m0;                               // +0x00
    V48 mV48;                               // +0x60
    VF mF0;                                 // +0x74
    VF mF1;                                 // +0x88
    VF mF2;                                 // +0x9c
    VF mF3;                                 // +0xb0
    ObjB50& operator=(const ObjB50& x);     // 0x00681b50 (below)
};

// object loaded by 0x006812c0
struct MapC0b {
    void __thiscall ReadKey(S16* out, IRd12* s);    // 0x00680560
    void __thiscall LoadEntries(ContC* out, IRd12* s);  // 0x006812c0 (below)
};

inline void CopyVecF(VF* d, const VF* s) {
    int bytes = (char*)s->mpEnd - (char*)s->mpBegin;
    d->Reserve(bytes >> 2, (void*)s->mTag);
    d->mpEnd = (char*)MemcpyT(d->mpBegin, s->mpBegin, (uint32_t)bytes) + (bytes >> 2);
}

// @ 0x00680c30
__declspec(noinline)
ObjC30::ObjC30(const ObjC30& other)
    : mStr(other.mStr), mM(other.mM) {}

// @ 0x00680cc0
void V48::insert(N48* pos, const N48& x) {
    N48* xAdj = (N48*)&x;
    if (mpEnd != mpEndCap) {
        if (xAdj >= pos && xAdj < mpEnd)
            xAdj = (N48*)&x + 1;
        N48* end = mpEnd;
        if (end)
            ((NC0*)end)->Fix((NC0*)(end - 1));
        end = mpEnd;
        MoveBack_300(pos, end - 1, end);
        new (pos) N48(*xAdj);
        mpEnd = end + 1;
    } else {
        int nElem = (int)(mpEnd - mpBegin) / 72;
        int nNew;
        if (nElem == 0)
            nNew = 1;
        else
            nNew = nElem * 2;
        N48* pNew = 0;
        if (nNew)
            pNew = (N48*)EASTL_alloc6((uint32_t)(nNew * 72), g_allocTag, 0, 0, g_fileEASTL, 0xd1);
        N48* begin = mpBegin;
        N48* pMid = (N48*)CopyN_1a0(begin, xAdj, pNew);
        CopyN_230(begin, xAdj, pNew);
        if (pMid)
            ((NC0*)pMid)->Fix((NC0*)&x);
        N48* const end = mpEnd;
        N48* pMid2 = (N48*)CopyN_1a0(pos, end, pNew + 1);
        CopyN_230(pos, end, pNew + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_dealloc(mpBegin);
        mpEnd = pMid2;
        mpBegin = pNew;
        mpEndCap = pNew + nNew;
    }
}

// @ 0x00680e70
V48& V48::operator=(const V48* other) {
    if (other != this) {
        uint32_t n = (uint32_t)((other->mpEnd - other->mpBegin) / 72);
        uint32_t cap = (uint32_t)((mpEndCap - mpBegin) / 72);
        if (n > cap) {
            N48* pNew = ReallocN7a0(n, other->mpBegin, other->mpEnd);
            N48* begin = mpBegin;
            Destroy3f0(begin, mpEnd);
            if (begin && ((int*)begin)[-1])
                EASTL_dealloc(begin);
            mpEndCap = pNew + n;
            mpBegin = pNew;
            mpEnd = pNew + n;
        } else {
            int m = (int)(mpEnd - mpBegin) / 72;
            N48* begin = mpBegin;
            if (m < n) {
                CopyN_270(other->mpBegin, other->mpBegin + m, begin);
                N48* pX = other->mpEnd;
                CtorN_420((void**)&pX, other->mpBegin + m, pX, mpEnd, pX);
                mpEnd = mpBegin + n;
            } else {
                N48* pEnd = (N48*)CopyN_270(other->mpBegin, other->mpEnd, begin);
                Destroy3f0(pEnd, mpEnd);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// @ 0x00680fc0
void Save_00680fc0(WF80* wthis, MapV* map, IWrt14* w) {
    int nSize = map->mnSize;
    w->Write(&nSize, 4);
    for (RNode* n = map->mAnchor.mpBegin; n != (RNode*)&map->mAnchor; n = (RNode*)RBTreeIncrement(n)) {
        int key = n->mKey;
        ObjC30 tmp(n->mVal);
        w->Write(&key, 4);
        int size = tmp.mStr.mpEnd - tmp.mStr.mpBegin;
        WriteUint32(w, &tmp.mStr.mpBegin, size, 0);
        if (size)
            w->Write(tmp.mStr.mpBegin, size);
        Thing t;
        wthis->Make5c0(&t, w);
        if ((int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin) > 1 && tmp.mStr.mpBegin)
            EASTL_dealloc(tmp.mStr.mpBegin);
    }
}

// @ 0x00681250
void __stdcall ReadVecU32(VU32* v, IRd12* s) {
    int count;
    s->Read(&count, 4);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        int value;
        ReadInt32(s, &value, 1, 0);
        uint32_t* p = v->mpEnd;
        if (p < v->mpEndCap) {
            v->mpEnd = p + 1;
            if (p)
                *p = (uint32_t)value;
        } else {
            v->DoIns_4558a0(v->mpEnd, &value);
        }
    }
}

// @ 0x006812c0
struct Key3 { int a; int b; int c; };
void MapC0b::LoadEntries(ContC* out, IRd12* s) {
    int count;
    s->Read(&count, 4);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        S16 a;
        S16 b;
        SPString str;
        str.mTableId = 0;
        str.mInstanceId = 0;
        str.mX = 0;
        ReadKey(&a, s);
        ReadKey(&b, s);
        int v1;
        ReadInt32(s, &v1, 1, 0);
        int v2;
        ReadInt32(s, &v2, 1, 0);
        str.Load(v2, v1, 0);
        str.mTableId = v2;
        str.mInstanceId = v1;
        ReadInt32(s, &str.mX, 1, 0);
        out->AddEntry10e0(&a);
        str.c_str();
    }
}

// @ 0x00681400
Cls1400::~Cls1400() {}

// @ 0x00681480
void MapC2::FreeNodes(Node1480* p) {
    while (p) {
        FreeNodes(p->mpDown);
        Node1480* next = (Node1480*)p->mpNext;
        p->m38.~SStrA();
        p->m24.~SStrA();
        p->m14.~SStrB();
        EASTL_dealloc(p);
        p = next;
    }
}

// @ 0x00681500
void MapC0::FreeChain2(Node15* p) {
    while (p) {
        FreeChain2(p->mpDown);
        Node15* next = (Node15*)p->mpNext;
        p->m24.~T28();
        p->m14.~SStrB();
        EASTL_dealloc(p);
        p = next;
    }
}

// @ 0x00681590
void MapV::InsertPair(RNode** pOut, RNode* pos, int* key, bool bAllowEquiv) {
    int bIns;
    if (!bAllowEquiv && pos != (RNode*)&mAnchor && *key >= pos->mKey)
        bIns = 1;
    else
        bIns = 0;
    RNode* nNew = CreateNode(key);
    RBTreeInsert(nNew, pos, &mAnchor, bIns);
    *pOut = nNew;
    ++mnSize;
}

// @ 0x006815f0
void MapV::InsertUnique(PairOut* pOut, const int* key) {
    RNode* pos = (RNode*)&mAnchor;
    int bLess = 1;
    RNode* n = mAnchor.mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpLeft : n->mpRight;
        } while (n);
    }
    RNode* found = pos;
    if (bLess) {
        if (pos == mAnchor.mpBegin) {
            int bIns = 0;
            if (pos != (RNode*)&mAnchor && *key >= pos->mKey)
                bIns = 1;
            RNode* nNew = CreateNode(key);
            RBTreeInsert(nNew, pos, &mAnchor, bIns);
            ++mnSize;
            pOut->first = nNew;
            pOut->second = true;
            return;
        }
        pos = (RNode*)RBTreeDecrement(pos);
    }
    if (pos->mKey >= *key) {
        pOut->first = pos;
        pOut->second = false;
        return;
    }
    {
        int bIns = 0;
        if (found != (RNode*)&mAnchor && *key >= found->mKey)
            bIns = 1;
        RNode* nNew = CreateNode(key);
        RBTreeInsert(nNew, found, &mAnchor, bIns);
        ++mnSize;
        pOut->first = nNew;
        pOut->second = true;
        return;
    }
}

// @ 0x00681700
__declspec(noinline)
Obj1700::Obj1700(const Obj1700& other)
    : mStr(other.mStr), mF0(other.mF0), mF1(other.mF1) {}

// keeps the unreferenced-in-TU copy ctors emitted (originals live in another TU)
__declspec(noinline) static Obj1700 RefKeep1700(const Obj1700& o) { return Obj1700(o); }
__declspec(noinline) static ObjA RefKeepA(const ObjA& o) { return ObjA(o); }
extern "C" void* const g_sliceRefs[] = {
    (void*)&RefKeep1700,
    (void*)&RefKeepA,
};

// @ 0x00681800
__declspec(noinline)
Obj1800::Obj1800(const Obj1800& other)
    : m0(other.m0), mM(other.mM), mF0(other.mF0), mF1(other.mF1),
      mF2(other.mF2), mF3(other.mF3) {}

// @ 0x00681a10
__declspec(noinline)
ObjA::ObjA(const ObjA& other)
    : m0(other.m0), mF0(other.mF0), mF1(other.mF1), mF2(other.mF2), mF3(other.mF3) {}

// @ 0x00681b50
ObjB50& ObjB50::operator=(const ObjB50& x) {
    m0 = x.m0;
    mV48 = &x.mV48;
    mF0 = x.mF0;
    mF1 = x.mF1;
    mF2 = x.mF2;
    mF3 = x.mF3;
    return *this;
}

// @ 0x00681c40
ObjA& ObjA::operator=(const ObjA& x) {
    m0 = x.m0;
    mF0 = x.mF0;
    mF1 = x.mF1;
    mF2 = x.mF2;
    mF3 = x.mF3;
    return *this;
}

// @ 0x00681e80
ObjA* CopyBackwardA(ObjA* srcFirst, ObjA* srcLast, ObjA* dstLast) {
    if (srcLast != srcFirst) {
        ObjA* d = dstLast;
        do {
            --srcLast;
            --d;
            *d = *srcLast;
        } while (srcLast != srcFirst);
        return d;
    }
    return dstLast;
}
