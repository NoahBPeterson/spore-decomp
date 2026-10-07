// Slice s00a24e10 - EA::Audio::System helpers (timers, lookups, per-primitive dispatch).
#include "types.h"
#include <intrin.h>
#include <new>

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);
void  operator delete(void* p, const char* name, int a, int b, int c, int d);
void  operator_delete__(void* p);                // 0x00f47380

extern const char g_lockName[];   // 0x01452970

// ---- refcounted base -------------------------------------------------------
struct Obj {
    virtual void AddRef();
    virtual void Release();
    virtual void Free();
};

struct TObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

struct ARC {
    Obj* p;
    ARC() : p(0) {}
    ARC(Obj* o) : p(o) { if (p) p->AddRef(); }
    ARC& assign(Obj* o);        // 0x00b5f950 (out of line)
    ~ARC() { if (p) p->Release(); }
};

// ---- stopwatch-based scoped timer (ctor 0x00a248a0) --------------------------
struct Stopwatch {
    char  pad[0x14];
    float coeff;
    __int64 GetElapsedTimeFloat();    // 0x0093a3a0
};

struct ScopedTimer {
    Stopwatch sw;
    float*    acc;
    int       pad;
    ScopedTimer(float* a);            // 0x00a248a0
    ~ScopedTimer()
    {
        *acc = (float)sw.GetElapsedTimeFloat() * sw.coeff + *acc;
    }
};

struct Mutex {
    void Lock(const char* name);      // 0x009221b0
    void Unlock();                    // 0x00922270
};

struct MutexGuard {
    Mutex* m;
    MutexGuard(Mutex* mm, const char* n) : m(mm) { m->Lock(n); }
    ~MutexGuard() { m->Unlock(); }
};

// ---- hash table stubs ----------------------------------------------------------
struct HNode { unsigned key; Obj* val; HNode* next; };
struct HNodeF { unsigned key; float val; };

struct HIter {
    HNode** node;
    HNode** bucket;
    HIter() {}
    HIter(const HIter& o) { node = o.node; bucket = o.bucket; }
};

struct HT {
    int      pad;
    HNode**  mBuckets;
    unsigned mBucketCount;
    HIter    find(const unsigned& key);   // 0x00645ed0
};

struct Prim {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void Update(int a, float b, int c);   // slot 3
};

struct PNode { unsigned key; Prim* val; PNode* next; };

struct PIter { PNode* node; PNode** bucket; PIter() {} PIter(const PIter& o) { node = o.node; bucket = o.bucket; } };
struct PIt {
    PNode*  node;
    PNode** bucket;
    PIt(PNode* n, PNode** b) : node(n), bucket(b) {}
    void IncrBucket() { ++bucket; while (*bucket == 0) ++bucket; node = *bucket; }
    void Incr() { node = node->next; while (node == 0) { ++bucket; node = *bucket; } }
};
struct PHT {
    int      pad;
    PNode**  mBuckets;
    unsigned mBucketCount;
    PIter    find(const unsigned& key);   // 0x00645ed0
    PNode*   end() { return mBuckets[mBucketCount]; }
    PNode*   begin(PNode*** bucketOut)
    {
        PNode** b = mBuckets;
        PNode* n = *b;
        if (n == 0) {
            ++b;
            while (*b == 0) ++b;
            n = *b;
        }
        *bucketOut = b;
        return n;
    }
};

// ---- the 0x28-byte property list (cPropertyList derived) -----------------------
__forceinline void Zero(int* p) { _InterlockedExchange((volatile long*)p, 0); }
struct PropBase : Obj {
    int rc;
    int f8, fc, f10;
    __forceinline PropBase() { Zero(&rc); f8 = 0; fc = 0; f10 = 0; }
};

struct PropList : PropBase {
    int  f14;
    int* mpData;
    int  f1c, f20;
    __forceinline PropList() { f14 = -1; mpData = 0; f1c = 0; f20 = 0; }
    virtual void AddRef();
    virtual void Release();
};

// ---- vtable stubs ----------------------------------------------------------
struct SysBase {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08();
    virtual bool CreateObject(const char* key, Obj* out, int c, int id);   // slot 9 (+0x24)
};

struct Str16 {
    wchar_t* b; wchar_t* e; wchar_t* cap; int alloc;
    ~Str16() { if ((int)(((char*)cap - (char*)b) & ~1) > 2 && b) operator_delete__(b); }
};
Str16 ConvertToString16(const char* s, int n);   // 0x0093c5a0
struct StrOut { int a, b, c; };
typedef void (__cdecl* StringFn)(StrOut*, int, int, int, int, int);
extern StringFn g_pfnString;                     // 0x0154c464

struct RbIter { int* n; RbIter() {} RbIter(const RbIter& o) { n = o.n; } };
struct RbTree {
    char pad[0x14];
    int  size;      // tree object at owner+4: size at owner+0x18
    RbIter find(const unsigned& key);    // 0x00e5c780
};
void RBTreeIncrement(void* n);                 // 0x00921580
void RBTreeErase(void* n, void* anchor);       // 0x00921880

struct Obj30 {
    Obj* Init();                       // 0x00a22cf0
};
struct Obj30b {
    Obj* Init();                       // 0x00a22cf0 (identical code folded)
};

// ============================================================================
// 00a24e10 / 00a24f50: object with an Obj* vector (+0x14/+0x18), mutex (+0x28)
// ============================================================================
struct Tracker {
    char   pad0[0x14];
    TObj**  mBegin;      // +0x14
    TObj**  mEnd;        // +0x18
    char   pad1[0x28 - 0x1c];
    Mutex  mMutex;      // +0x28
    char   pad2[0x58 - 0x28 - 4];
    float  mElapsed;    // +0x58
    // ScopedTimer anchor value lives at +0x5c (arg to timer ctor)
    char   pad3[4];

    void  Remove(TObj* o);               // 00a24e10
    void  Process(TObj* o);              // 00a24f50
    TObj*  Find(TObj* o);                 // 00a24970
};

// @ 0x00a24e10
void Tracker::Remove(TObj* o)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    MutexGuard guard(&mMutex, g_lockName);
    mElapsed = (float)timer.sw.GetElapsedTimeFloat() * timer.sw.coeff + mElapsed;
    TObj** it = mBegin;
    for (; it != mEnd; ++it) {
        if (o == *it) {
            TObj* old = *it;
            TObj* nw = mEnd[-1];
            if (nw != old) {
                if (nw) nw->AddRef();
                *it = nw;
                if (old) old->Release();
            }
            mEnd -= 1;
            TObj* last = *mEnd;
            if (last) last->Release();
            return;
        }
    }
}

// @ 0x00a24f50
void Tracker::Process(TObj* o)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    TObj* f = Find(o);
    if (f) {
        ((void (__thiscall*)(TObj*))(*(void***)f)[9])(f);
        Remove(o);
    }
}

// ============================================================================
// 00a25000: refcount decrement of an rbtree entry
// ============================================================================
struct RcMap {
    char   pad[4];
    RbTree mTree;      // +4
    void Release(unsigned key);         // 00a25000
};

// @ 0x00a25000
void RcMap::Release(unsigned key)
{
    RbIter it = mTree.find(key);
    int* node = it.n;
    if ((int*)((char*)this + 8) != node) {
        if ((*(volatile int*)&node[5] += -1) == 0) {
            mTree.size += -1;
            RBTreeIncrement(node);
            RBTreeErase(node, (char*)&mTree + 4);
            operator_delete__(node);
        }
    }
}

// ============================================================================
// 00a25050: scalar deleting destructor of a resource with a heap array at +0x18
// ============================================================================
struct ResBase {
    int pad[1];
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual ~ResBase() throw() {}
};

struct ResDerived : ResBase {
    int  pad2[4];
    int* mpData;       // +0x18
    ResDerived();
    virtual ~ResDerived() throw();
};
ResDerived::ResDerived() {}
ResDerived::~ResDerived() throw() { _ReadWriteBarrier(); if (mpData && mpData[-1]) operator_delete__(mpData); }

// ============================================================================
// 00a25090 / 00a25190: factories creating a refcounted object and registering it
// ============================================================================
struct Factory {
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
    virtual void f08();
    virtual bool Create(const char* a, Obj* o, int c, int d);   // +0x24
    bool MakeProps(const char* a, Obj** out, int c, int d);     // 00a25090
    bool MakeAudio(const char* a, ARC* out, int c, int id);     // 00a25190
};

// @ 0x00a25090
bool Factory::MakeProps(const char* a, Obj** out, int c, int d)
{
    bool ok = false;
    if (out != 0 && a != 0) {
        void* m = operator new(0x2c, "audio", 0, 0, 0, 0);
        PropList* pl = m ? new (m) PropList() : 0;
        ARC ref(pl);
        if (Create(a, pl, c, d)) {
            pl->AddRef();
            *out = pl;
            ok = true;
        }
    }
    return ok;
}

// @ 0x00a25190
bool Factory::MakeAudio(const char* a, ARC* out, int c, int id)
{
    bool ok = false;
    if (out != 0 && a != 0) {
        ARC tmp;
        switch (id) {
        case 0x1a527db: {
            void* m = operator new(0x30, "Audio", 0, 0, 0, 0);
            tmp.assign(m ? ((Obj30*)m)->Init() : 0);
            break;
        }
        case 0x42c9cbb: {
            void* m = operator new(0x30, "Audio", 0, 0, 0, 0);
            tmp.assign(m ? ((Obj30b*)m)->Init() : 0);
            break;
        }
        }
        Obj* o = tmp.p;
        if (o && Create(a, o, c, id)) {
            o->AddRef();
            out->p = o;
            ok = true;
        }
    }
    return ok;
}

// ============================================================================
// 00a25980: convert a UTF-8 name and forward through vtable slot 0x88
// ============================================================================
struct Namer {
    virtual void n00(); virtual void n01(); virtual void n02(); virtual void n03();
    virtual void n04(); virtual void n05(); virtual void n06(); virtual void n07();
    virtual void n08(); virtual void n09(); virtual void n0a(); virtual void n0b();
    virtual void n0c(); virtual void n0d(); virtual void n0e(); virtual void n0f();
    virtual void n10(); virtual void n11(); virtual void n12(); virtual void n13();
    virtual void n14(); virtual void n15(); virtual void n16(); virtual void n17();
    virtual void n18(); virtual void n19(); virtual void n1a(); virtual void n1b();
    virtual void n1c(); virtual void n1d(); virtual void n1e(); virtual void n1f(); virtual void n20(); virtual void n21();
    virtual void Dispatch(wchar_t* name, int a, int b, double c);   // +0x88
    void Convert(const char* s, int a, int b, double c);            // 00a25980
};

// @ 0x00a25980
void Namer::Convert(const char* s, int a, int b, double c)
{
    StrOut out = { 0, 0, 0 };
    g_pfnString(&out, (int)ConvertToString16(s, -1).b, 0, 0, 0, 0);
    Dispatch((wchar_t*)out.a, a, b, c);
}

// ============================================================================
// 00a25a40 .. 00a25bd0: lookups in System's hash tables
// ============================================================================
struct Subscription {
    void UpdateOutput(void* outputs);   // 0x00a22820
};

struct SNode { unsigned key; char val[0x1c]; SNode* next; };   // next at +0x24 (value Subscription at +4)

struct FNode { unsigned key; float val; FNode* next; };
struct GIter { void* node; void** bucket; GIter() {} GIter(const GIter& o) { node = o.node; bucket = o.bucket; } };

struct FHT {
    int      pad;
    FNode**  mBuckets;
    unsigned mBucketCount;
    GIter    find(const unsigned& key);   // 0x00645ed0 (pair<uint,float>)
    FNode*   end() { return mBuckets[mBucketCount]; }
};

// nested table node: key + embedded hash table of floats at +4
struct NNode { unsigned key; FHT inner; };
struct NHT {
    int      pad;
    NNode**  mBuckets;
    unsigned mBucketCount;
    GIter    find(const unsigned& key);   // 0x00a23b00
    NNode*   end() { return mBuckets[mBucketCount]; }
};

struct SubNode { unsigned key; char val[0x20]; SubNode* next; };
struct SubHT {
    int       pad;
    SubNode** mBuckets;
    unsigned  mBucketCount;
    SubNode*  end() { return mBuckets[mBucketCount]; }
};

struct SubIt {
    SubNode*  node;
    SubNode** bucket;
    SubIt(SubNode* n, SubNode** b) : node(n), bucket(b) {}
    void IncrBucket() { ++bucket; while (*bucket == 0) ++bucket; node = *bucket; }
    void Incr() { node = node->next; while (node == 0) { ++bucket; node = *bucket; } }
};

struct AudioSys {
    char pad0[0x3a4];
    char mOutputs[0x60];
    PHT  mPrims;                  // +0x404 (buckets +0x408, count +0x40c)
    char pad2[0x11b3c8 - 0x404 - sizeof(PHT)];
    NHT  mNested;                 // +0x11b3c8
    char pad3[0x1277b4 - 0x11b3c8 - sizeof(NHT)];
    SubHT mSubs;                  // +0x1277b4 (buckets +0x1277b8, count +0x1277bc)

    bool CallPrim(unsigned id, int a, float b, int c);       // 00a25a40
    void CallAll(int a, float b, int c);                     // 00a25aa0
    bool HasPrim(unsigned id);                               // 00a25b20
    void UpdateOutput();                                     // 00a25b60
    bool GetFloat(unsigned k1, unsigned k2, float* out);     // 00a25bd0
};

// @ 0x00a25a40
bool AudioSys::CallPrim(unsigned id, int a, float b, int c)
{
    PIter it = mPrims.find(id);
    if (it.node == mPrims.end()) {
        return false;
    }
    it.node->val->Update(a, b, c);
    return true;
}

// @ 0x00a25aa0
void AudioSys::CallAll(int a, float b, int c)
{
    PIt it(*mPrims.mBuckets, mPrims.mBuckets);
    if (it.node == 0) it.IncrBucket();
    PIt end(mPrims.end(), 0);
    while (it.node != end.node) {
        it.node->val->Update(a, b, c);
        it.Incr();
    }
}

// @ 0x00a25b20
bool AudioSys::HasPrim(unsigned id)
{
    PNode* end = mPrims.end();
    return mPrims.find(id).node != end;
}

// @ 0x00a25b60
void AudioSys::UpdateOutput()
{
    SubIt it(*mSubs.mBuckets, mSubs.mBuckets);
    if (it.node == 0) it.IncrBucket();
    SubNode* end = mSubs.end();
    if (it.node != end) {
        do {
            ((Subscription*)((char*)it.node + 4))->UpdateOutput(mOutputs);
            it.Incr();
        } while (it.node != end);
    }
}

// @ 0x00a25bd0
bool AudioSys::GetFloat(unsigned k1, unsigned k2, float* out)
{
    GIter it = mNested.find(k1);
    NNode* node = (NNode*)it.node;
    if (node != mNested.end()) {
        GIter jt = node->inner.find(k2);
        if ((FNode*)jt.node != node->inner.end()) {
            *out = ((FNode*)jt.node)->val;
            return true;
        }
    }
    return false;
}

// ============================================================================
// 00a252b0: EA::Audio::System::Init
// ============================================================================
struct Server {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8();
    virtual void Register(void* handler, unsigned id);        // +0x24
};
Server* GetMessagingServer();                                  // 0x00883860

struct IHandlerRC {
    virtual void h0();
    virtual void h1();
    virtual void AddRef();       // +8
    virtual void Release();      // +0xc
};

struct ISystem0 {
    virtual void i0();
};

struct Config {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c0a();
    virtual void Get(unsigned key, int* out);                 // +0x2c
};

struct DbgObj {
    static void* operator new(unsigned size, const char* n, int a, int b, int c, int d);   // 0x00926020
    static void operator delete(void* p, const char* n, int a, int b, int c, int d);
    DbgObj();                                                                               // 0x00a19d60
    char pad[0x70];
};

struct ErrIf {
    virtual void e0(); virtual void e1(); virtual void e2();
    virtual bool Query(const void* iid, ARC* out, int a, int b, int c, int d);   // +0xc
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11();
    virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
    virtual void e16();
    virtual void Set(int a, DbgObj* o, int b);                                   // +0x44
};
ErrIf* GetObjectError();                                        // 0x008de1a0

struct CharMap {
    CharMap(int a, int b, int c, int d, int e);                  // 0x00926350
    char pad[0x50];
};

struct Queue {
    void Init(int n);                                            // 0x00a102a0
    char pad[0x50];
};

struct ThreadParams {
    int  pad0[2];
    int  priority;
    int  pad1[2];
    const char* name;
    ThreadParams();                                              // 0x00922900
};
unsigned GetDefaultAffinity();                                   // 0x00922920

struct Cond {
    char pad[0x60];
    int Wait(Mutex* m, const char* name);                        // 0x00921f80
};
struct Thread {
    char pad[8];
    void Begin(void* proc, void* arg, ThreadParams* p, unsigned aff);   // 0x00922f30
};
unsigned GetThreadId();                                          // 0x00921cc0
void TickProc(void*);                                            // 0x00a228d0

struct Ring {
    unsigned* cBegin;
    unsigned* cEnd;
    char      pad[0xfbc - 8];
    unsigned* mBegin;
    unsigned* mEnd;
    int       mSize;

    __forceinline void Push(unsigned v)
    {
        *mEnd = v;
        mEnd += 1;
        if (mEnd == cEnd) mEnd = cBegin;
        if (mEnd == mBegin) {
            mBegin += 1;
            if (mBegin == cEnd) mBegin = cBegin;
        } else {
            mSize += 1;
        }
    }
};

extern unsigned g_tid1;      // 0x0166d9f8
extern unsigned g_tid2;      // 0x0166d9fc
struct System;
extern System*  g_pSystem;   // 0x0166d9f4
extern const unsigned g_msgIds[7];   // 0x01452b6c
extern const char g_iidErr[];        // 0x01552da0

struct System : ISystem0, IHandlerRC {
    // +8: EA::Messaging::AutoHandler
    Server*   mpServer;
    void*     mpHandler;
    const unsigned* mpIdArray;
    int       mnIdArrayCount;
    int       mnPriority;
    char      pad1c[0x20 - 0x1c];
    Thread    mTickThread;                 // +0x20
    Cond      mCondInit;                   // +0x28 (+0x28 .. +0x88)
    bool      mbExitThread;                // +0x88
    char      pad89[0x8c - 0x89];
    int       mStarted;                    // +0x8c
    char      pad90[0x94 - 0x90];
    bool      mbInitialized;               // +0x94
    char      pad95[0xb8 - 0x95];
    Mutex     mMutex;                      // +0xb8
    char      padbc[0x1f8 - 0xb8 - sizeof(Mutex)];
    ARC       mpConfiguration;             // +0x1f8
    char      pad1fc[0x214 - 0x1fc];
    Queue     q214;
    Queue     q264;
    char      pad2b4[0x304 - 0x2b4];
    Queue     q304;
    Queue     q354;
    char      pad3a4[0x119ba0 - 0x3a4];
    CharMap*  mpCharMap;                   // +0x119ba0
    char      pad119ba4[0x12c9ac - 0x119ba4];
    Ring      mExternalIdsPool;            // +0x12c9ac
    char      padring1[0x1366d4 - 0x12c9ac - sizeof(Ring)];
    Ring      mAllocatedIdsPool;           // +0x1366d4

    bool Init();                           // 00a252b0
};

// @ 0x00a252b0
bool System::Init()
{
    if (mbInitialized) return false;
    mbInitialized = true;
    g_tid1 = GetThreadId();
    MutexGuard guard(&mMutex, g_lockName);
    g_tid2 = GetThreadId();
    if (g_pSystem) ((IHandlerRC*)g_pSystem)->Release();
    IHandlerRC* h = (IHandlerRC*)((unsigned)this + 4);
    g_pSystem = this;
    h->AddRef();

    mpCharMap = new ("Audio/Char8Map", 0, 0, 0, 0) CharMap(0x20000, 0x134, 0, 1, 0);

    ErrIf* err = GetObjectError();
    if (err) {
        DbgObj* d = new ("Audio", 0, 0, 0, 0) DbgObj();
        err->Set(1, d, 0);
        ARC pObj;
        if (!err->Query(g_iidErr, &pObj, 0, 0, 0, 0) || pObj.p == 0) {
            return false;
        }
        mpConfiguration.assign((Obj*)((char*)pObj.p + 0x14));
    }

    q214.Init(5000);
    q264.Init(5000);
    q304.Init(5000);
    q354.Init(5000);

    Server* srv = GetMessagingServer();
    mpServer = srv;
    mpHandler = h;
    mpIdArray = g_msgIds;
    mnIdArrayCount = 7;
    mnPriority = 0;
    if (srv && h) {
        for (unsigned i = 0; i < 0x1c; i += 4) {
            srv->Register(h, *(const unsigned*)((const char*)g_msgIds + i));
        }
    }

    ThreadParams tp;
    tp.name = "AudioSystem";
    int prio = 0;
    ((Config*)mpConfiguration.p)->Get(0x90a770d, &prio);
    tp.priority = prio;
    mbExitThread = false;
    mStarted = 0;
    Cond* cond = &mCondInit;
    unsigned aff = GetDefaultAffinity();
    mTickThread.Begin((void*)TickProc, cond, &tp, aff);
    while (mStarted == 0) {
        if (cond->Wait(&mMutex, g_lockName) != 0) break;
    }
    bool ok = (mStarted == 1);

    for (unsigned i = 1001; i <= 2000; i += 5) {
        mExternalIdsPool.Push(i);
        mExternalIdsPool.Push(i + 1);
        mExternalIdsPool.Push(i + 2);
        mExternalIdsPool.Push(i + 3);
        mExternalIdsPool.Push(i + 4);
    }
    for (unsigned i = 1; i <= 1000; i += 5) {
        mAllocatedIdsPool.Push(i);
        mAllocatedIdsPool.Push(i + 1);
        mAllocatedIdsPool.Push(i + 2);
        mAllocatedIdsPool.Push(i + 3);
        mAllocatedIdsPool.Push(i + 4);
    }

    if (!ok) {
        if (g_pSystem) ((IHandlerRC*)g_pSystem)->Release();
        g_pSystem = 0;
    }
    return ok;
}
