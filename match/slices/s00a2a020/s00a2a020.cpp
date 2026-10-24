// Slice s00a2a020 -- EA::Audio EASTL fixed_hash_map/set constructors,
// hashtable/rbtree teardown helpers and small audio vector helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int  u32;

void* operator new(unsigned int);
void  operator_delete__(void*);          // 0x00f47380

// --- unresolved externals referenced by the originals -----------------------
unsigned int __cdecl FUN_00921340(unsigned int);                 // 0x00921340
unsigned int __stdcall FUN_009213c0(unsigned int);               // 0x009213c0
void __cdecl FUN_00a136f0(void*, void*, void*);                  // 0x00a136f0

struct FixedPoolBase {
    void* mpHead;          // +0x0  (free list head; set by init)
    void* pad0[4];         // +0x4  .. +0x13 (init fills mpNext/mpCapacity/nodeSize)
    void* mpBucketArray;   // +0x14 bucket array of the owning hash map
    void* pad1[2];         // +0x18 .. +0x1f
    void init(void* base, u32 size, u32 nodeSize, u32 align, u32 flags);  // 0x00921260
};

struct HashHead {
    void* pad0[2];           // +0x00 .. +0x07
    u32   mnBucketCount;     // +0x08
    u32   mnElementCount;    // +0x0c
    float mfMaxLoadFactor;   // +0x10
    float mfGrowthFactor;    // +0x14
    u32   mnNextResize;      // +0x18
    u32   pad1[6];           // +0x1c .. +0x33
    void* mpBucketArray;     // +0x34
};

struct RehashPolicy {
    float mfMaxLoadFactor;   // +0x0
    float mfGrowthFactor;    // +0x4
    u32   mnNextResize;      // +0x8
    u32 get_next_bucket_size(u32 n);   // 0x009213c0
};

struct HashBase {
    void ctorA(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23570
    void ctorB(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23620
    void ctorC(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23780
    void ctorD(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23c70
    void ctorE(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23e40
    void ctorF(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23f50
    void ctorG(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23990
    void ctorH(u32, void*, void*, void*, u32, void*, void*);   // 0x00a24160
    void rehashA(u32);                                          // 0x00a22220
    void rehashB(u32);                                          // 0x00a22370
    void DoFreeNodes(void*, void*);                             // 0x00a1b6c0
};

template<class R> static inline R vc0(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> static inline R vc(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }

// ---------------------------------------------------------------------------
// 0x00a2a020  EA::Audio::System::ConnectSubmixTree
// ---------------------------------------------------------------------------
struct Submix {
    void* vftable;                       // +0
    void  DisconnectFromSubmix();        // 0x00a21390
    bool  ConnectToSubmix(Submix* o);    // 0x00a27ed0
};
struct SysLike { void* vftable; bool ConnectSubmixTree(); };

// @ 0x00a2a020
bool SysLike::ConnectSubmixTree()
{
    Submix* first = vc<Submix*>(this, 0x17c, (u32)0xf1cc1687);
    Submix** it  = *(Submix***)((char*)this + 0x119ba4);
    Submix** end = *(Submix***)((char*)this + 0x119ba8);
    int fail = 0;
    for (; it != end; ++it) {
        Submix* s = *it;
        if (s)
            ((void (__thiscall*)(void*))(*(void***)s)[0])(s);
        u32 id;
        char* nb = *(char**)((char*)s + 0x978);
        if (nb == *(char**)((char*)s + 0x97c) || nb == 0)
            id = 0xf1cc1687;
        else
            id = vc<u32>(this, 0xf4, nb);
        Submix* found = vc<Submix*>(this, 0x17c, id);
        if (found == 0) {
            ++fail;
        } else {
            ((void (__thiscall*)(void*))(*(void***)found)[0])(found);
            if (s != first) {
                s->DisconnectFromSubmix();
                if (!s->ConnectToSubmix(found))
                    ++fail;
            }
            ((void (__thiscall*)(void*))(*(void***)found)[1])(found);
        }
        if (s)
            ((void (__thiscall*)(void*))(*(void***)s)[1])(s);
    }
    return fail == 0;
}

// ---------------------------------------------------------------------------
// 0x00a2a150  hashtable operator[]-style helper
// ---------------------------------------------------------------------------
struct HashFindStub { void find(void* sret, const void* key); };   // 0x00645ed0
struct BoolTag { bool b; };                                        // 1-byte by-value tag
struct SmallStubs {
    int  GetOrInsert(int* key);
    void Insert(void* sret, const int* key, BoolTag tag);          // 0x00a136f0
    void Dtor();
    void DestroyBuckets(int param_2, u32 param_3);
    int  EraseRange(int param_2, int param_3);
    int* VecIntInsert(int* param_2, int* param_3);
};

// @ 0x00a2a150
int SmallStubs::GetOrInsert(int* key)
{
    int local_20;
    ((HashFindStub*)this)->find(&local_20, key);
    int endBucket = *(int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    if (local_20 != endBucket)
        return local_20 + 4;
    int local_18[3];
    int k = *key;
    local_18[0] = 0; local_18[1] = 0; local_18[2] = 0;
    BoolTag tag;
    tag.b = false;
    Insert(local_18, &k, tag);
    return local_18[0] + 4;
}

// ---------------------------------------------------------------------------
// fixed_hash_map / fixed_hash_set constructors
// ---------------------------------------------------------------------------
struct FixedMap {
    int a210(void* a2, void* a3);
    int a310(void* a2, void* a3);
    int a410(void* a2, void* a3);
    int a570(void* a2, void* a3);
    int a670(void* a2, void* a3);
    int a770(void* a2, void* a3);
    int a870(void* a2, void* a3);
    int a970(void* a2, void* a3);
};

#define FIXED_CTOR(NAME, POOLOFF, POOLSIZE, NODE, MAXARG, CTOR, REHASH)          \
int FixedMap::NAME(void* a2, void* a3)                                           \
{                                                                                \
    HashHead& h = *(HashHead*)this;                                              \
    FixedPoolBase fb;                                                            \
    fb.mpHead = 0;                                                               \
    fb.init((char*)this + (POOLOFF), (POOLSIZE), (NODE), 4, 0);                  \
    fb.mpBucketArray = (char*)this + 0x34;                                       \
    u32 v = FUN_00921340(MAXARG);                                                \
    ((HashBase*)this)->CTOR(v, a2, (void*)&a3, (void*)&a3, (u32)(size_t)a3,     \
                            (void*)&a3, &fb);                                    \
    RehashPolicy pol;                                                            \
    pol.mfMaxLoadFactor = 10000.0f;                                              \
    pol.mfGrowthFactor  = 2.0f;                                                  \
    pol.mnNextResize    = 0;                                                     \
    h.mfMaxLoadFactor = pol.mfMaxLoadFactor;                                     \
    h.mfGrowthFactor  = pol.mfGrowthFactor;                                      \
    h.mnNextResize    = 0;                                                       \
    u32 u = pol.get_next_bucket_size(h.mnElementCount);                          \
    if (h.mnBucketCount < u)                                                     \
        ((HashBase*)this)->REHASH(u);                                            \
    return (int)this;                                                            \
}

FIXED_CTOR(a210, 0x35c,  0x960,   0xc, 0xc9,  ctorA, rehashA)   // @ 0x00a2a210
FIXED_CTOR(a310, 0x3ebc, 0x75300, 0xc, 0xfa1, ctorB, rehashA)   // @ 0x00a2a310
FIXED_CTOR(a410, 0x64,   0x78,    0xc, 0xb,   ctorC, rehashA)   // @ 0x00a2a410
FIXED_CTOR(a570, 0xfdc,  0x1f40,  8,   0x3e9, ctorD, rehashB)   // @ 0x00a2a570
FIXED_CTOR(a670, 0x1cc,  0x320,   8,   0x65,  ctorE, rehashB)   // @ 0x00a2a670
FIXED_CTOR(a770, 0xfdc,  0x1d4c0, 0xc, 0x3e9, ctorF, rehashA)   // @ 0x00a2a770
FIXED_CTOR(a870, 0x1cc,  0x4b0,   0xc, 0x65,  ctorG, rehashA)   // @ 0x00a2a870
#undef FIXED_CTOR

// @ 0x00a2a970
int FixedMap::a970(void* a2, void* a3)
{
    HashHead& h = *(HashHead*)this;
    FixedPoolBase fb;
    fb.mpHead = 0;
    fb.init((char*)this + 0x104, 0x190, 8, 4, 0);
    fb.mpBucketArray = (char*)this + 0x34;
    u32 v = FUN_00921340(0x33);
    ((HashBase*)this)->ctorH(v, a2, (void*)&a3, (void*)&a3, (u32)(size_t)a3,
                             (void*)&a3, &fb);
    RehashPolicy pol;
    pol.mfMaxLoadFactor = 10000.0f;
    pol.mfGrowthFactor  = 2.0f;
    pol.mnNextResize    = 0;
    h.mfMaxLoadFactor = pol.mfMaxLoadFactor;
    h.mfGrowthFactor  = pol.mfGrowthFactor;
    h.mnNextResize    = 0;
    u32 u = pol.get_next_bucket_size(h.mnElementCount);
    if (h.mnBucketCount < u)
        ((HashBase*)this)->rehashB(u);
    return (int)this;
}

// ---------------------------------------------------------------------------
// 0x00a2aa70  hashtable destructor
// ---------------------------------------------------------------------------
void SmallStubs::Dtor()
{
    char* hb = (char*)this + 4;
    HashBase* h = (HashBase*)hb;
    h->DoFreeNodes(*(void**)(hb + 4), *(void**)(hb + 8));
    void* p = *(void**)(hb + 4);
    *(void**)(hb + 0xc) = 0;
    if (*(u32*)(hb + 8) > 1 && p != *(void**)(hb + 0x30)) {
        if (p < *(void**)(hb + 0x24) || p >= *(void**)(hb + 0x28)) {
            operator_delete__(p);
        } else {
            *(void**)p = *(void**)(hb + 0x1c);
            *(void**)(hb + 0x1c) = p;
            return;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00a2ab40  eastl::vector<12-byte>::push_back(default)
// ---------------------------------------------------------------------------
struct E12 { u32 a, b, c; };
struct Vec12 {
    void* mpBegin;   // +0
    E12*  mpEnd;     // +4
    E12*  mpCap;     // +8
    void pushEmpty();
    void DoInsertValue(E12* pos, void* val);   // 0x00a27910
};

// @ 0x00a2ab40
void Vec12::pushEmpty()
{
    E12* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e) {
            e->a = 0; e->b = 0; e->c = 0;
            return;
        }
    } else {
        E12 tmp = {0, 0, 0};
        DoInsertValue(e, &tmp);
    }
}

// ---------------------------------------------------------------------------
// 0x00a2ab80  eastl::vector<18-byte>::push_back(default)
// ---------------------------------------------------------------------------
struct E18 { int a; int b; float f; int c; int d; int e; };
struct Vec18 {
    void* mpBegin;   // +0
    E18*  mpEnd;     // +4
    E18*  mpCap;     // +8
    void pushEmpty();
    void DoInsertValue(E18* pos, E18* val);   // 0x00a27a40
};

void Vec18::pushEmpty()
{
    E18* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e) {
            e->a = 0; e->b = 0; e->f = 0.0f;
            e->c = 0; e->d = 0; e->e = 0;
        }
    } else {
        E18 tmp;
        tmp.a = 0; tmp.b = 0; tmp.f = 0.0f;
        tmp.c = 0; tmp.d = 0; tmp.e = 0;
        DoInsertValue(e, &tmp);
    }
}

// ---------------------------------------------------------------------------
// 0x00a2abe0  eastl::vector<tInstrumentZone>::push_back
// ---------------------------------------------------------------------------
struct Zone { u32 d[0xb]; };
struct ZoneVec {
    void* mpBegin;   // +0
    u8*   mpEnd;     // +4
    u8*   mpCap;     // +8
    void push_back(const Zone* v);
    void DoInsertValue(u8* pos, const Zone* val);   // 0x00a27b90
};

void ZoneVec::push_back(const Zone* v)
{
    u8* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 0x2c;
        if (e)
            *(Zone*)e = *v;
    } else {
        DoInsertValue(e, v);
    }
}

// ---------------------------------------------------------------------------
// 0x00a2ac20  eastl::vector<int>::insert
// ---------------------------------------------------------------------------
// @ 0x00a2ac20
int* SmallStubs::VecIntInsert(int* param_2, int* param_3)
{
    int* self = (int*)this;
    int* piVar1 = (int*)self[1];
    if (piVar1 != (int*)self[2]) {
        if (param_2 <= param_3 && param_3 < piVar1)
            param_3 = param_3 + 1;
        if (piVar1 != 0) {
            int* piVar2 = (int*)piVar1[-1];
            *piVar1 = (int)piVar2;
            if (piVar2 != 0)
                ((void (__thiscall*)(void*))(*(void***)piVar2)[1])(piVar2);
        }
        memmove(param_2, (char*)self[1] - 4, (char*)self[1] - (char*)param_2);
        param_3 = (int*)*param_3;
        piVar1 = (int*)*param_2;
        if (param_3 != piVar1) {
            if (param_3 != 0)
                ((void (__thiscall*)(void*))(*(void***)param_3)[1])(param_3);
            *param_2 = (int)param_3;
            if (piVar1 != 0)
                ((void (__thiscall*)(void*))(*(void***)piVar1)[2])(piVar1);
        }
        self[1] = self[1] + 4;
        return param_2;
    }
    int local_14 = (int)piVar1 - *self >> 2;
    if (local_14 == 0) {
        local_14 = 1;
    } else {
        local_14 = local_14 * 2;
    }
    void* local_18 = 0;
    if (local_14 != 0)
        local_18 = operator new(local_14 * 4);
    int size = (int)param_2 - *self;
    char* pv = (char*)local_18 + size;
    if (pv != 0) {
        int* q = (int*)*param_3;
        *(int*)pv = (int)q;
        if (q != 0)
            ((void (__thiscall*)(void*))(*(void***)q)[1])(q);
    }
    int iVar3 = self[1];
    memmove((char*)pv + 4, param_2, iVar3 - (int)param_2);
    self[1] = (int)(pv + 4 + (iVar3 - (int)param_2));
    *self = (int)local_18;
    self[2] = (int)((char*)local_18 + local_14 * 4);
    return (int*)pv;
}

// ---------------------------------------------------------------------------
// 0x00a2add0  destroy an array of hash-bucket chains
// ---------------------------------------------------------------------------
struct RBTreeStub { void DoNukeSubtree(void*); };   // 0x009a9600

// @ 0x00a2add0
void SmallStubs::DestroyBuckets(int param_2, u32 param_3)
{
    for (u32 i = 0; i < param_3; i++) {
        void* puVar1 = *(void**)(param_2 + i * 4);
        while (puVar1) {
            void* puVar4 = puVar1;
            puVar1 = *(void**)((char*)puVar4 + 0x24);
            void* puVar3 = *(void**)((char*)puVar4 + 0x14);
            while (puVar3) {
                ((RBTreeStub*)((char*)puVar4 + 8))->DoNukeSubtree(*(void**)puVar3);
                void* next = *(void**)((char*)puVar3 + 4);
                operator_delete__(puVar3);
                puVar3 = next;
            }
            if (puVar4 != *(void**)((char*)this + 0x30)) {
                if (puVar4 < *(void**)((char*)this + 0x24) ||
                    *(void**)((char*)this + 0x28) <= puVar4) {
                    operator_delete__(puVar4);
                } else {
                    *(void**)puVar4 = *(void**)((char*)this + 0x1c);
                    *(void**)((char*)this + 0x1c) = puVar4;
                }
            }
        }
        *(void**)(param_2 + i * 4) = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00a2ae90  erase a range of 0x14-byte ref-counted elements
// ---------------------------------------------------------------------------
void* ARCopy(void* a, void* b, void* c);   // 0x00a22730

// @ 0x00a2ae90
int SmallStubs::EraseRange(int param_2, int param_3)
{
    u32 u = (u32)(size_t)ARCopy((void*)param_3,
                              *(void**)((char*)this + 4), (void*)param_2);
    u32 end = *(u32*)((char*)this + 4);
    if (u < end) {
        void** p = (void**)(u + 0x10);
        int n = (int)(((end - u) - 1) / 0x14) + 1;
        do {
            if (*p != 0)
                ((void (__thiscall*)(void*))(*(void***)*p)[1])(*p);
            p += 5;
            --n;
        } while (n);
    }
    *(int*)((char*)this + 4) -= ((param_3 - param_2) / 0x14) * 0x14;
    return param_2;
}
