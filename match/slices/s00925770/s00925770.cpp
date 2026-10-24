// EA::Trace helper/allocator tail end (0x00925770..0x00926350). Many small EAThread/EASTL helpers;
// the simple ones are byte-exact, the larger allocator internals are skeletons (see partial.txt).
#include <windows.h>
#include <stddef.h>
#include <string.h>

namespace EA { namespace Trace {

// @ 0x00925770  AutoOSGlobalPtr<EATracerPtr,...>::Create
extern "C" void* __cdecl eanew(int, int, int, const char*, int, int, int, int);
extern void* __fastcall ctor_00925540(void*);
void* CreateTracerPtr() {
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) return ctor_00925540(p);
    return 0;
}
// @ 0x00925BC0
extern void* __fastcall ctor_00925b00(void*);
void* CreateHelperTablePtr() {
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) return ctor_00925b00(p);
    return 0;
}

// @ 0x00925CB0  ICoreAllocator::GetDefaultAllocator
extern void* g_01668eac;
extern void* g_0154df84;
extern char  g_0154df88;
extern void* g_0154df8c;
extern void* g_0154df90;
extern void* g_016c8b44;
__declspec(noinline) void* GetDefaultAllocatorX() {
    if (!g_01668eac) {
        if (!g_0154df84) {
            g_0154df84 = g_016c8b44;
            g_0154df88 = 0;
            g_0154df8c = 0;
            g_0154df90 = 0;
        }
        g_01668eac = (void*)0x0154df80;
    }
    return g_01668eac;
}

// @ 0x00926020  ZoneObject::operator_new
void* ZoneObject_new(int a1, int a2, int a3) {
    void* alloc = GetDefaultAllocatorX();
    int* r = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))(*(void***)alloc)[1])
        (alloc, a1 + 8, a2, a3, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}
// @ 0x00926060  ZoneObject::operator_delete
void ZoneObject_delete(void* p) {
    if (p) {
        void* base = (char*)p - 8;
        ((void (__thiscall*)(void*, int))(*(void***)*(void**)base)[3])(base, 0);
    }
}

// @ 0x00925BF0
void FUN_00925bf0(unsigned a1, unsigned a2, int a3) {
    void* obj = *(void**)(a3 + 4);
    void** vt = *(void***)obj;
    int r = ((int (__thiscall*)(void*, unsigned, int, int))vt[2])(obj, a1, 0, 0);
    unsigned* out = (unsigned*)a2;
    if (out) *out = (r != 0) ? a1 : 0;
}
// @ 0x00925C20
void FUN_00925c20(unsigned a1, int a2) {
    void* obj = *(void**)(a2 + 4);
    void** vt = *(void***)obj;
    ((void (__thiscall*)(void*, unsigned, int))vt[3])(obj, a1, 0);
}
// @ 0x00925DA0
struct C25da0 { void F(unsigned a2, unsigned a3, unsigned a4); };
void C25da0::F(unsigned a2, unsigned a3, unsigned a4) {
    ((void (__thiscall*)(void*, unsigned, unsigned, unsigned, int, int))(*(void***)this)[1])(
        this, a2, a3, a4, 0, 0);
}

// @ 0x00925E40
struct C25e40 { int w[5]; void F(int* p, int unused); };
void C25e40::F(int* p, int unused) {
    (void)unused;
    int old = w[2];
    w[2] = (int)p;
    *p = old;
    --w[4];
}
// @ 0x00925E60
extern void FUN_00925d60();
struct HashHolder { void FUN_00925e60() { *(void**)this = (void*)0x0143e104; FUN_00925d60(); } };
void FUN_00925e60_hash(HashHolder* h) { h->FUN_00925e60(); }

// @ 0x00926100
void* FUN_00926100(void* p) {
    if (p) { *(void**)((char*)p + 0x18) = 0; InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION*)p, 10); return p; }
    return 0;
}
// @ 0x00926120
int FUN_00926120(void* p) {
    EnterCriticalSection((CRITICAL_SECTION*)p);
    ++*(int*)((char*)p + 0x18);
    return *(int*)((char*)p + 0x18);
}
// @ 0x00926140
int FUN_00926140(void* p) {
    --*(int*)((char*)p + 0x18);
    int n = *(int*)((char*)p + 0x18);
    LeaveCriticalSection((CRITICAL_SECTION*)p);
    return n;
}
// @ 0x00926340
void FUN_00926340(void* p) { DeleteCriticalSection((CRITICAL_SECTION*)p); }

// @ 0x00925F30
struct C25f30 { void F(int a2, int a3, int a4); };
void C25f30::F(int a2, int a3, int a4) {
    int* p = (int*)this;
    p[1] = a2;
    p[5] = a4;
    p[2] = 0; p[3] = 0; p[4] = 0;
    p[6] = a3;
    *p = 0x0143e104;
    p[7] = 0;
}

}} // namespace EA::Trace


// ================================================================== completed (formerly skeletons)
#include <new>
#include <intrin.h>
namespace EA { namespace Trace {

struct Mutex {
    char d[0x30];
    Mutex* Init(const char* name, bool b);    // 0x009222a0 (Mutex::Mutex)
    void Destroy();                           // 0x00922130 (~Mutex)
    void Lock(const void* ctx);               // 0x009221b0
    int  Unlock();                            // 0x00922270
};

class TraceHelper { public:
    char pad0;
    bool mIsFiltered;
    bool mIsFilterEvaluated;
    char pad3[0x1d];
    void* mTracer;
};

TraceHelper** __cdecl vec_move(void* dst, void* src, int bytes);                                    // 0x011e0744
void* __cdecl eastl_new(unsigned size, const char* name, int, int, const char* file, int line);    // 0x00f473a0
void __cdecl eastl_delete(void* p);                                                                // 0x00f47380

struct HelperVec {
    TraceHelper** mpBegin;
    TraceHelper** mpEnd;
    TraceHelper** mpCapacity;
    void DoInsertValue(TraceHelper** pos, TraceHelper* const* val);   // 0x009257e0
    __forceinline TraceHelper** find(TraceHelper* v) {
        TraceHelper** last = mpEnd; TraceHelper** first = mpBegin;
        while (first != last && *first != v) ++first;
        return first;
    }
    __forceinline void erase(TraceHelper** it) {
        TraceHelper** next = it + 1;
        if (next < mpEnd) vec_move(it, next, (int)((char*)mpEnd - (char*)next));
        --mpEnd;
    }
    __forceinline void Zero() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void Reserve(int n);                                              // 0x009256a0
    inline void push_back(TraceHelper* v) {
        if (mpEnd < mpCapacity) {
            TraceHelper** e = mpEnd++;
            if (e) *e = v;
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
};

// 0x009257e0
// @ 0x009257e0
void HelperVec::DoInsertValue(TraceHelper** pos, TraceHelper* const* val) {
    if (mpEnd != mpCapacity) {
        TraceHelper** e0 = mpEnd;
        TraceHelper* const* v = val;
        if (v >= pos && v < e0) ++v;
        if (e0) *e0 = e0[-1];
        TraceHelper** last = mpEnd - 1;
        size_t bytes = (size_t)((char*)last - (char*)pos);
        memmove(mpEnd - (last - pos), pos, bytes);
        *pos = *v;
        ++mpEnd;
        return;
    }
    unsigned cap = (unsigned)(mpEnd - mpBegin);
    cap = (cap > 0u) ? cap * 2 : 1;
    TraceHelper** buf = cap ? (TraceHelper**)eastl_new(cap * 4, "EATrace", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    int off = (int)((char*)pos - (char*)mpBegin);
    TraceHelper** p = vec_move(buf, mpBegin, off);
    p = p + (off >> 2);
    if (p) *p = *val;
    int tail = (int)((char*)mpEnd - (char*)pos);
    TraceHelper** e = vec_move(p + 1, pos, tail);
    e = e + (tail >> 2);
    if (mpBegin && ((int*)mpBegin)[-1]) eastl_delete(mpBegin);
    mpBegin = buf;
    mpEnd = e;
    mpCapacity = buf + cap;
}

class TraceHelperTable { public:
    virtual void AddRef();
    virtual void Release();
    void* mTracer;
    HelperVec mVec;
    char pad14[0xc];
    Mutex mMutex;
    long mFlag;
    char pad54[4];
    void RegisterHelper(TraceHelper* h);      // 0x00925b50
    void UnregisterHelper(TraceHelper* h);    // 0x00925960
};

// 0x00925b50
// @ 0x00925b50
void TraceHelperTable::RegisterHelper(TraceHelper* h) {
    mMutex.Lock((const void*)0x143dffc);
    h->mTracer = mTracer;
    h->mIsFiltered = true;
    h->mIsFilterEvaluated = false;
    mVec.push_back(h);
    mMutex.Unlock();
}

// 0x00925960
// @ 0x00925960
void TraceHelperTable::UnregisterHelper(TraceHelper* h) {
    mMutex.Lock((const void*)0x143dffc);
    h->mTracer = 0;
    h->mIsFiltered = true;
    h->mIsFilterEvaluated = false;
    TraceHelper** it = mVec.find(h);
    if (it != mVec.mpEnd) mVec.erase(it);
    mMutex.Unlock();
}

// 0x009258f0  EATraceHelperTablePtr::EATraceHelperTablePtr
// @ 0x009258f0
TraceHelperTable* CreateHelperTable() {
    TraceHelperTable* t = (TraceHelperTable*)eastl_new(0x58, "EATrace/TraceHelperTable", 0, 0, 0, 0);
    if (t) {
        *(void**)t = (void*)0x143e050;
        t->mTracer = 0;
        t->mVec.Zero();
        t->mMutex.Init(0, true);
        _InterlockedExchange(&t->mFlag, 0);
        t->mVec.Reserve(0x1000);
        return t;
    }
    return 0;
}

struct HelperTablePtr {
    int w0, w4, w8, wc;
    TraceHelperTable* mpTable;
    HelperTablePtr* Init();                   // 0x00925b00
    __forceinline void setTable(TraceHelperTable* n) {
        TraceHelperTable* old = mpTable;
        if (n != old) {
            if (n) n->AddRef();
            mpTable = n;
            if (old) old->Release();
        }
    }
};
// @ 0x00925b00
HelperTablePtr* HelperTablePtr::Init() {
    w4 = w0 = 0;
    mpTable = 0;
    setTable(CreateHelperTable());
    return this;
}

// ---- 0x009257a0  TempTraceHelperMap::~TempTraceHelperMap and 0x009259d0 ctor
extern const float g_01485720;
extern const float g_01470f1c;
struct TempMapHT {
    void* vt;
    void* mpBuckets;
    unsigned mBucketCount;
    unsigned mElementCount;
    float mMaxLoad;
    float mGrowth;
    volatile int mNextResize;
    int   w1c;
    char  mbEnable;
    void DoFreeNodes(void* buckets, unsigned n);   // 0x007611f0
    __forceinline void Clear() {
        DoFreeNodes(mpBuckets, mBucketCount);
        mElementCount = 0;
        if (mBucketCount > 1) eastl_delete(mpBuckets);
    }
};
class TempTraceHelperMap { public:
    Mutex mMutex;
    TempMapHT ht;
    TempTraceHelperMap* Init();                    // 0x009259d0
    void Destroy();                                // 0x009257a0 (~TempTraceHelperMap)
    void ReleaseHelpers();                         // 0x009255f0
};
// @ 0x009257a0
void TempTraceHelperMap::Destroy() {
    ReleaseHelpers();
    ht.Clear();
    mMutex.Destroy();
}
// @ 0x009259d0
TempTraceHelperMap* TempTraceHelperMap::Init() {
    mMutex.Init(0, true);
    ht.mMaxLoad = g_01485720;
    ht.mGrowth = g_01470f1c;
    ht.mNextResize = 0;
    ht.mBucketCount = 1;
    ht.mpBuckets = (void*)0x154df28;
    ht.mElementCount = 0;
    ht.mNextResize = 0;
    ht.mbEnable = 1;
    return this;
}

// ---- 0x00925a30  TraceHashtable ctor (fixed-pool backed)
extern const float g_013f0620;
struct FixedPool {
    void* mpHead;
    int   w4;
    void* mBuf;
    void* mBufEnd;
    int   mNodeSize;
    void* mAlloc;
    void init(void* buf, unsigned size, unsigned nodeSize, unsigned align, unsigned off);   // 0x00921260
};
struct RehashPolicy {
    float mMaxLoad, mGrowth;
    int   mNextResize;
    unsigned GetBucketCount(unsigned n);       // 0x009213c0
};
unsigned __cdecl policy_prime(unsigned n);     // 0x00921340
struct TraceHashtable {
    int w0, w4;
    unsigned mBucketCount;
    unsigned mElementCount;
    RehashPolicy mPolicy;
    char pad1c[0x18];
    char mNodes[1];
    TraceHashtable* Init(unsigned a1, unsigned a2);
    void Init7(unsigned b, unsigned a1, const unsigned& r1, const unsigned& r2, unsigned v, const unsigned& r3, FixedPool* pool);  // 0x00925490
    void DoRehash(unsigned n);                 // 0x00925370
};
// @ 0x00925a30
TraceHashtable* TraceHashtable::Init(unsigned a1, unsigned a2) {
    char* self = (char*)this;
    union { FixedPool pool; RehashPolicy tmp; } u;
    FixedPool& pool = u.pool;
    {
        pool.mpHead = 0;
        char* buf = self + 0x138;
        pool.init(buf, 0x2f4, 0xc, 4, 0);
        pool.mBuf = buf;
        char* alloc = self + 0x34;
        buf += 0x2f4;
        pool.mBufEnd = buf;
        pool.mNodeSize = 0xc;
        pool.mAlloc = alloc;
        unsigned nb = policy_prime(0x40);
        Init7(nb, a1, a2, a2, a2, a2, &pool);
    }
    RehashPolicy& tmp = u.tmp;
    tmp.mMaxLoad = g_013f0620;
    tmp.mGrowth = g_01470f1c;
    tmp.mNextResize = 0;
    *(int*)&mPolicy.mMaxLoad = *(int*)&tmp.mMaxLoad;
    *(int*)&mPolicy.mGrowth = *(int*)&tmp.mGrowth;
    mPolicy.mNextResize = tmp.mNextResize;
    unsigned n = tmp.GetBucketCount(mElementCount);
    if (n > mBucketCount) DoRehash(n);
    return this;
}

// ---- 0x00925f90 / 0x00925fe0
struct ICoreAlloc {
    virtual void v0();
    virtual void* Alloc(unsigned size, int a, int b, int c, int d);
};
struct ZoneAllocWrap {
    int w0;
    ICoreAlloc* mpFallback;
    int w8, wc, w10;
    unsigned mLimit;
    int w18;
    int mFallbackCount;
    void* Inner(unsigned size, int a, int b, int c, int d);    // 0x00925dc0
    void* Alloc(unsigned size, int a, int b);                  // 0x00925f90
};
// @ 0x00925f90
void* ZoneAllocWrap::Alloc(unsigned size, int a, int b) {
    if (size <= mLimit) return Inner(size, a, b, 0, 0);
    ++mFallbackCount;
    return mpFallback->Alloc(size, a, b, 0, 0);
}
// @ 0x00925fe0
void* ZoneAlloc_Named(int size, ICoreAlloc* alloc, int flags) {
    if (!alloc) alloc = (ICoreAlloc*)GetDefaultAllocatorX();
    int* r = (int*)alloc->Alloc(size + 8, flags, 0, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}

}} // namespace EA::Trace

// ================================================================== allocator wrappers (completed)
namespace EA { namespace Trace {

struct F9289f0 { void m(int, int, int, int, const char *, int); };              // 0x009289f0
struct F928a30 { void m(int, int, int, int, int, int, const char *, int); };    // 0x00928a30
struct F9276c0 { void m(int); };                                                // 0x009276c0
struct F9289e0 { void m(); };                                                   // 0x009289e0

// @ 0x00925c40
struct C25c40 { void* f0; void* f4; void F(int p1, int p2, int p3); };
void C25c40::F(int p1, int p2, int p3) {
    ((F9289f0 *)f4)->m(p1, p3, 0, p2,
        "..\\..\\UTFKernel\\MemoryMan\\source\\CoreAllocatorGeneral.cpp", 0x2a);
}

// @ 0x00925c70
struct C25c70 { void* f0; void* f4; void F(int p1, int p2, int p3, int p4, int p5); };
void C25c70::F(int p1, int p2, int p3, int p4, int p5) {
    ((F928a30 *)f4)->m(p1, p4, p5, p3, 0, p2,
        "..\\..\\UTFKernel\\MemoryMan\\source\\CoreAllocatorGeneral.cpp", 0x31);
}

// @ 0x00925ca0
struct C25ca0 { void* f0; void* f4; void F(int p1, int p2); };
void C25ca0::F(int p1, int p2) {
    (void)p2;
    ((F9276c0 *)f4)->m(p1);
}

// @ 0x00925cf0
struct C25cf0 { void* vt; void* f4; char f8; void* fC; void* f10; void F(); };
void C25cf0::F() {
    vt = (void *)0x143e0e4;
    if (f8 != 0) {
        if (fC != 0) {
            ((void (__cdecl *)(void *, void *, void *))fC)(this, f4, f10);
            vt = (void *)0x1403934;
            return;
        }
        void *p = f4;
        if (p) {
            ((F9289e0 *)p)->m();
            eastl_delete(p);
        }
    }
    vt = (void *)0x1403934;
}

// @ 0x00925d60
struct C25d60 { void* vt; void* f4; void* f8; void* fC; void F(); };
void C25d60::F() {
    void *p = fC;
    vt = (void *)0x143e0f4;
    while (p != 0) {
        fC = *(void **)p;
        ((void (__thiscall *)(void *, void *, int))(*(void ***)f4)[3])(f4, p, 0);
        p = fC;
    }
    f8 = 0;
    fC = 0;
    vt = (void *)0x1403934;
}

// @ 0x00925dc0
struct C25dc0 {
    void* vt; void* f4; void* f8; void* fC; unsigned f10; unsigned f14; int f18;
    void *F(unsigned size, int p3, int p4, int p5, int p6);
};
void *C25dc0::F(unsigned size, int p3, int p4, int p5, int p6) {
    if (size > f14) {
        if (f14 == 0)
            f14 = size;
        else
            return 0;
    }
    if (f8 == 0) {
        void *r = ((void *(__thiscall *)(void *, unsigned, int, int, int, int))(*(void ***)f4)[1])
            (f4, (f18 + 1) * (int)size, p3, p4, p5, p6);
        *(void **)r = fC;
        fC = r;
        unsigned i = 0;
        r = (char *)r + size;
        while (i < (unsigned)f18) {
            *(void **)r = f8;
            f8 = r;
            ++i;
            r = (char *)r + size;
        }
    }
    void *p = f8;
    ++f10;
    f8 = *(void **)p;
    return p;
}

// @ 0x00925e70
struct C25e70 {
    void* vt; void* f4; void* f8; void* fC; unsigned f10; unsigned f14; int f18; int f1c;
    void *F(unsigned size, int p3, int p4, int p5, int p6);
};
void *C25e70::F(unsigned size, int p3, int p4, int p5, int p6) {
    if (size <= f14)
        return ((C25dc0 *)this)->F(size, p3, p4, p5, p6);
    ++f1c;
    return ((void *(__thiscall *)(void *, unsigned, int, int, int, int))(*(void ***)f4)[1])
        (f4, size, p3, p4, p5, p6);
}

// @ 0x00925eb0
struct C25eb0 {
    void* vt; void* f4; void* f8; void* fC; unsigned f10; unsigned f14; int f18; int f1c;
    void F(void *p, unsigned n);
};
void C25eb0::F(void *p, unsigned n) {
    unsigned u = f14;
    if (n <= u) {
        void *q = fC;
        int span = f18 * (int)u;
        if (q != 0) {
            for (;;) {
                char *lo = (char *)q + u * 4;
                if (p >= (void *)lo) {
                    char *hi = lo + span * 4;
                    if (p < (void *)hi) break;
                }
                q = *(void **)q;
                if (q == 0) return;
            }
            void *old = f8;
            f8 = p;
            *(void **)p = old;
            --f10;
        }
        return;
    }
    --f1c;
    ((void (__thiscall *)(void *, void *, unsigned))(*(void ***)f4)[3])(f4, p, n);
}

// @ 0x00926080
extern unsigned int g_1668eb4;
extern void *g_1668eb0;
void *FUN_00926080(SIZE_T size) {
    if ((g_1668eb4 & 1) == 0) {
        g_1668eb4 = g_1668eb4 | 1;
        g_1668eb0 = GetProcessHeap();
    }
    return HeapAlloc((HANDLE)g_1668eb0, 0, size);
}

// @ 0x009260c0
extern unsigned int g_1668ebc;
extern void *g_1668eb8;
void FUN_009260c0(void *p) {
    if ((g_1668ebc & 1) == 0) {
        g_1668ebc = g_1668ebc | 1;
        g_1668eb8 = GetProcessHeap();
    }
    HeapFree((HANDLE)g_1668eb8, 0, p);
}

}} // namespace EA::Trace

// ================================================================== EA::Trace chained hash table
namespace EA { namespace Trace {

void  FUN_00926160(unsigned size);                 // 0x00926160  allocator wrapper (EA alloc)
void  FUN_00f47410(void* p);                       // 0x00f47410  allocator lockup (EA free)

// A chained hash table with its own lock section, a pluggable alloc/free pair and an optional
// case-insensitive byte-key compare.  Member names follow the offsets the original uses.
struct C26190 {
    void*    mpLock;              // 0x00  points at mCS once the section is built
    int      mPad04;              // 0x04
    char     mCS[0x20];           // 0x08  CRITICAL_SECTION
    void*  (*mpAlloc)(unsigned);  // 0x28
    void   (*mpFree)(void*);      // 0x2c
    void*    mpNode0;             // 0x30
    void*    mpNodes;             // 0x34
    void**   mpBuckets;           // 0x38
    unsigned mBlockSize;          // 0x3c
    unsigned mBytesUsed;          // 0x40
    unsigned mBucketCount;        // 0x44
    unsigned mElementCount;       // 0x48
    char     mCaseSensitive;      // 0x4c
    char     mFlag;               // 0x4d
    struct Node { Node* mpNext; unsigned mHash; void* mpValue; };
    int     Hash(const char* s);
    bool    Equal(const char* a, const char* b, unsigned len);
    void*   Find(unsigned hash);
    C26190* Init(unsigned size, unsigned bucketCount, char caseSensitive, char flag, char useHeap);
};

// @ 0x00926160
void FUN_00926160(unsigned size) {
    ((F9289f0*)g_016c8b44)->m(size, 0, 0, 0x143e114, (const char*)0x143e12c, 0x9a);
}

// FNV-1 hash of a byte key, optionally folded to lower case.
// @ 0x00926190
int C26190::Hash(const char* s) {
    unsigned h = 0x811c9dc5u;
    if (mCaseSensitive) {
        const char* p = s;
        int c = *p;
        while (c != 0) {
            h = (h * 0x1000193u) ^ (unsigned)c;
            c = *++p;
        }
    } else {
        int c = *s;
        while (c != 0) {
            unsigned d = (unsigned)(c - 'A');
            if (d < 26u) c = d + 'a';
            h = (h * 0x1000193u) ^ (unsigned)c;
            c = *++s;
        }
    }
    return (int)h;
}

// Key equality: the length must match, then bytes (or case-folded bytes) must be equal.
// @ 0x009261f0
bool C26190::Equal(const char* a, const char* b, unsigned len) {
    unsigned n = 0;
    while (b[n] != 0) ++n;
    if (len != n) return false;
    if (mCaseSensitive) return memcmp(a, b, len) == 0;
    for (unsigned i = 0; i < len; ++i) {
        int ca = a[i];
        unsigned da = (unsigned)(ca - 'A');
        if (da < 26u) ca = da + 'a';
        int cb = b[i];
        unsigned db = (unsigned)(cb - 'A');
        if (db < 26u) cb = db + 'a';
        if (ca != cb) return false;
    }
    return true;
}

// Walk the chain for the bucket the hash falls in and return the stored value.
// @ 0x00926300
void* C26190::Find(unsigned hash) {
    Node* n = (Node*)mpBuckets[hash % mBucketCount];
    while (n != 0) {
        if (hash == n->mHash) return n->mpValue;
        n = n->mpNext;
    }
    return (void*)0x13ec47c;
}

// Allocate the first node block, split the bucket array out of it and zero the buckets.
// @ 0x00926350
C26190* C26190::Init(unsigned size, unsigned bucketCount, char caseSensitive, char flag, char useHeap) {
    mBlockSize = size;
    mpLock = 0;
    mElementCount = 0;
    mBucketCount = bucketCount;
    mCaseSensitive = caseSensitive;
    mFlag = flag;
    if (useHeap) {
        mpAlloc = (void* (*)(unsigned))&FUN_00926080;
        mpFree = &FUN_009260c0;
    } else {
        mpAlloc = (void* (*)(unsigned))&FUN_00926160;
        mpFree = &FUN_00f47410;
    }
    mpLock = FUN_00926100(mCS);
    void* nodes = mpAlloc(mBlockSize);
    mpNodes = nodes;
    mpNode0 = nodes;
    *(int*)nodes = 0;
    mBytesUsed = 4;
    mpBuckets = (void**)((int*)mpNodes + 1);
    memset(mpBuckets, 0, mBucketCount * 4);
    mBytesUsed += mBucketCount * 4;
    return this;
}

}} // namespace EA::Trace
