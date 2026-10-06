// Slice s00a22220 - EA::Audio container rehash / refcount / list / subscription helpers.
#include "types.h"
#include <intrin.h>

typedef unsigned char u8;
typedef unsigned int  u32;

extern int g_166d9f4;     // global audio system pointer
extern int g_166d9fc;     // worker thread id

void __cdecl op_delete(void*);            // operator_delete__ (0x00f47380)

// ---------------------------------------------------------------------------
// Fixed-pool hash table rehash (two flavours differing in the chain-link offset)
// ---------------------------------------------------------------------------
struct HNode28 { u32 key; u32 pad; HNode28* next; };   // next at +8
struct HNode20 { u32 key; HNode20* next; };            // next at +4

struct HTable28 {
    u32       pad0;
    HNode28** buckets;     // +4
    u32       bucketCount; // +8
    u32       pad0c[4];
    void*     freeList;    // +0x1c
    u32       pad20;
    void*     poolBegin;   // +0x24
    void*     poolEnd;     // +0x28
    u32       pad2c;
    void*     inlineBuckets; // +0x30
    HNode28** AllocBuckets(u32 n);      // 00a221b0
    void      Rehash(u32 n);
};

struct HTable20 {
    u32       pad0;
    HNode20** buckets;     // +4
    u32       bucketCount; // +8
    u32       pad0c[4];
    void*     freeList;    // +0x1c
    u32       pad20;
    void*     poolBegin;   // +0x24
    void*     poolEnd;     // +0x28
    u32       pad2c;
    void*     inlineBuckets; // +0x30
    HNode20** AllocBuckets(u32 n);      // 00a22300
    void      Rehash(u32 n);
};

// @ 0x00a22220
void HTable28::Rehash(u32 n)
{
    HNode28** nb = AllocBuckets(n);
    for (u32 i = 0; i < bucketCount; ++i) {
        HNode28* p = buckets[i];
        while (p != 0) {
            u32 h = p->key % n;
            buckets[i] = p->next;
            p->next = nb[h];
            nb[h] = p;
            p = buckets[i];
        }
    }
    HNode28** old = buckets;
    if (bucketCount > 1 && old != (HNode28**)inlineBuckets) {
        if ((void*)old >= poolBegin && (void*)old < poolEnd) {
            *(void**)old = freeList;
            freeList = old;
            buckets = nb;
            bucketCount = n;
            return;
        }
        op_delete(old);
    }
    buckets = nb;
    bucketCount = n;
}

// @ 0x00a22370
void HTable20::Rehash(u32 n)
{
    HNode20** nb = AllocBuckets(n);
    for (u32 i = 0; i < bucketCount; ++i) {
        HNode20* p = buckets[i];
        while (p != 0) {
            u32 h = p->key % n;
            buckets[i] = p->next;
            p->next = nb[h];
            nb[h] = p;
            p = buckets[i];
        }
    }
    HNode20** old = buckets;
    if (bucketCount > 1 && old != (HNode20**)inlineBuckets) {
        if ((void*)old >= poolBegin && (void*)old < poolEnd) {
            *(void**)old = freeList;
            freeList = old;
            buckets = nb;
            bucketCount = n;
            return;
        }
        op_delete(old);
    }
    buckets = nb;
    bucketCount = n;
}

// ---------------------------------------------------------------------------
// Pool-backed circular list: free every node
// ---------------------------------------------------------------------------
struct PoolList {
    void*  head;        // +0  (circular, this is the anchor)
    u32    pad4;
    void*  freeList;    // +8
    u32    padc;
    void*  poolBegin;   // +0x10
    void*  poolEnd;     // +0x14
    void   FreeNodes(); // 00a222c0
};

// @ 0x00a222c0
void PoolList::FreeNodes()
{
    void** n = (void**)head;
    while (n != (void**)this) {
        void** cur = n;
        n = (void**)*n;
        if ((void*)cur < poolBegin || (void*)cur >= poolEnd) {
            op_delete(cur);
        } else {
            *cur = freeList;
            freeList = cur;
        }
    }
}

// ---------------------------------------------------------------------------
// Intrusive list of Snd objects (list node embedded at +0x10) -- merge
// ---------------------------------------------------------------------------
struct Snd;
struct SNode { SNode* next; SNode* prev; };
struct Snd {
    void** vt;
    u32    pad04[3];
    SNode  node;       // +0x10
    static Snd* FromNode(SNode* n) { return n ? (Snd*)((char*)n - 0x10) : 0; }
    bool Check();                       // 00ef6410
};
struct SIter { Snd* p; SIter() {} SIter(Snd* q) : p(q) {} };

struct SList {
    SNode anchor;
    void  merge(SList& x, bool (__cdecl* compare)(Snd*, Snd*));   // 00a22410
    void  splice(SIter pos, SList& x, SIter first, SIter last);    // 00a212b0
};

// @ 0x00a22410
void SList::merge(SList& x, bool (__cdecl* compare)(Snd*, Snd*))
{
    if (this != &x) {
        Snd* first  = Snd::FromNode(anchor.next);
        Snd* firstX = Snd::FromNode(x.anchor.next);
        Snd* last   = (Snd*)((char*)this - 0x10);
        Snd* lastX  = (Snd*)((char*)&x - 0x10);
        while (first != last && firstX != lastX) {
            if (compare(firstX, first)) {
                Snd* next = Snd::FromNode(firstX->node.next);
                if (firstX != next) {
                    Snd* nprev = Snd::FromNode(next->node.prev);
                    SNode* a = &nprev->node;
                    a->next->prev = firstX->node.prev;
                    firstX->node.prev->next = a->next;
                    Snd* pprev = Snd::FromNode(first->node.prev);
                    SNode* b = &pprev->node;
                    b->next = &firstX->node;
                    firstX->node.prev = b;
                    a->next = &first->node;
                    first->node.prev = a;
                }
                firstX = next;
            } else {
                first = Snd::FromNode(first->node.next);
            }
        }
        if (firstX != lastX) {
            splice(SIter(last), x, SIter(firstX), SIter(lastX));
        }
    }
}

// ---------------------------------------------------------------------------
// 20-byte element (4 words + intrusive-refcounted pointer)
// ---------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();
    virtual void Release();
};

inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

struct ARef {
    IRef* p;
    ARef() : p(0) {}
    ARef(const ARef& o) : p(o.p) { if (p) p->AddRef(); }
    ARef& operator=(const ARef& o)
    {
        IRef* np = o.p;
        IRef* old = p;
        if (np != old) {
            if (np) np->AddRef();
            p = np;
            if (old) old->Release();
        }
        return *this;
    }
};

struct AR {
    u32  a, b, c, d;
    ARef r;

    AR() {}
    AR(const AR& o) : a(o.a), b(o.b), c(o.c), d(o.d), r(o.r) {}
    AR& operator=(const AR& o)
    {
        a = o.a;
        b = o.b;
        c = o.c;
        d = o.d;
        r = o.r;
        return *this;
    }
};
AR& (AR::*g_arAssign)(const AR&) = &AR::operator=;

// @ 0x00a22580  AR::operator= (out of line instance via g_arAssign)

// @ 0x00a225d0   uninitialized_copy
AR* __cdecl ARUninitCopy(AR* first, AR* last, AR* dst)
{
    for (; first != last; ++first, ++dst)
        ::new((void*)dst) AR(*first);
    return dst;
}

// @ 0x00a226c0   copy_backward
AR* __cdecl ARCopyBackward(AR* first, AR* last, AR* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00a22730   copy
AR* __cdecl ARCopy(AR* first, AR* last, AR* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// ---------------------------------------------------------------------------
// Driver base classes
// ---------------------------------------------------------------------------
struct RefBase {
    virtual void v0();
    volatile long rc;
    RefBase() { _InterlockedExchange(&rc, 0); }
};

struct DrvB : RefBase {
    u32   pad[0x1e];       // +8 .. +0x80
    void* mArg;            // +0x80
    u32   mPad84;
    u32   mZero;           // +0x88
    DrvB(void* arg) : mArg(arg), mZero(0) {}
    virtual void v0();
};

// @ 0x00a227a0
void ConstructDrvB(DrvB* self, void* arg)
{
    new (self) DrvB(arg);
}

// ---------------------------------------------------------------------------
// Shared pointer helpers
// ---------------------------------------------------------------------------
struct RCSub {                              // refcounted base at +4 of a shared block
    virtual void Del(int);
    volatile long rc;
    void Release()
    {
        long n = _InterlockedExchangeAdd(&rc, -1);
        if (--n == 0) {
            _InterlockedExchange(&rc, 1);
            if (this)
                this->Del(1);
        }
    }
};
struct Shared {
    u32 pad0;
    RCSub sub;
};

template<class T> struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    AutoRef(T* q) : p(q) { if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
};

// @ 0x00a227d0  ResourceDeviceDriver::~ResourceDeviceDriver
struct MutexObj { ~MutexObj(); };
struct RecVec { ~RecVec(); };
struct DDBase { virtual ~DDBase() {} };
struct ResourceDeviceDriver : DDBase {
    u32      pad[4];
    RecVec   mRecordContainer;     // +0x14
    u32      pad18[4];
    MutexObj mMutex;               // +0x28
    ResourceDeviceDriver() {}
};
ResourceDeviceDriver* MakeRDD() { return new ResourceDeviceDriver; }   // forces ~ResourceDeviceDriver 00a227d0

// ---------------------------------------------------------------------------
// Object with a refcounted member at +0x28
// ---------------------------------------------------------------------------
struct SharedBlock {                       // pointer p: sub-object at +4, refcount at +8
    u32   pad0;
    RCSub sub;
};
struct SharedRef {
    SharedBlock* p;
    void Assign(void* np);                                      // 006ae2a0
    ~SharedRef()
    {
        if (p)
            p->sub.Release();
    }
};
struct DDBase2 { virtual ~DDBase2() {} };
struct SharedHolder : DDBase2 {
    u32       pad[9];
    SharedRef mShared;    // +0x28
    SharedHolder() {}
};
SharedHolder* MakeSH() { return new SharedHolder; }   // forces ~SharedHolder 00a22b20

// @ 0x00a22b00
int __stdcall MakeKeyPair(int* out, int)
{
    if (out != 0) {
        out[0] = 0x1a527db;
        out[1] = 0x42c9cbb;
    }
    return 2;
}

// @ 0x00a22cf0
struct PropBase {
    virtual void v0();
    volatile long rc;
    PropBase() { _InterlockedExchange(&rc, 0); }
};
struct PropList : PropBase {
    u32    f08, f0c, f10, f14, f18, f1c;
    double d20;
    u32    f28;
    PropList() : f08(0), f0c(0), f10(0), d20(0.0), f14(0), f18(0), f28(0) {}
    virtual void v0();
};
void ConstructPropList(PropList* self)
{
    new (self) PropList();
}

// ---------------------------------------------------------------------------
// Subscription::UpdateOutput
// ---------------------------------------------------------------------------
struct Builder {
    void  Begin(u32 key);                      // 00a102e0
    void  AddInt(u32 key, u32 value);          // 00a103b0
    void  AddFloat(u32 key, float value);      // 00a10390
    void  Commit();                            // 00a0f940
};
struct IMix {
    virtual void m0();
    virtual void m1();
    virtual int  GetId();                       // +8
    virtual void m3();
    virtual bool Query(u32 key, float* out);    // +0x10
};
struct RBNode {
    RBNode* right;
    RBNode* left;
    RBNode* parent;
    u32     color;
    u32     key;     // +0x10
    u32     value;   // +0x14
};
RBNode* RBTreeIncrement(RBNode* n);           // 00921580

struct Subscription {
    IMix*  mpMixable;       // +0
    u32    pad4;
    RBNode anchor;          // +8 (anchor.left is begin at +0xc)
    void   UpdateOutput(Builder* b);
};

// @ 0x00a22820
void Subscription::UpdateOutput(Builder* b)
{
    RBNode* n = anchor.left;
    if (n != &anchor) {
        do {
            u32 key = n->key;
            float v;
            if (mpMixable->Query(key, &v)) {
                b->Begin(0x407c01d);
                b->AddInt(0x3475385, mpMixable->GetId());
                b->AddInt(0x34753a7, key);
                b->AddFloat(0x34753aa, v);
                b->Commit();
            }
            n = RBTreeIncrement(n);
        } while (n != &anchor);
    }
}

// ---------------------------------------------------------------------------
// Worker thread
// ---------------------------------------------------------------------------
#pragma warning(disable:4035)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
void ThreadSleep(const int*);                              // 00921df0
u32  GetThreadId_();                                       // 00921cc0

struct Stopwatch {
    unsigned __int64 mnStartTime;
    unsigned __int64 mnTotalElapsedTime;
    int   mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    Stopwatch(int units, int start);                       // 0093a560
    void Restart();                                         // 00571e80
    __int64 GetElapsedTimeFloat();                          // 0093a3a0
    void RestartInline()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
            ((u32*)&mnStartTime)[0] = (u32)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};

struct WorkerCtx {
    u32  pad[0x18];
    u8   stop;                // +0x60
    u8   pad61[3];
    u32  mode;                // +0x64
    void Init(int);           // 00922050
};

#define VCALL(T, p, off) ((T)((*(void***)(p))[(off) / 4]))

// @ 0x00a228d0
int __cdecl WorkerThread(WorkerCtx* self)
{
    g_166d9fc = GetThreadId_();
    void* sys = (void*)g_166d9f4;
    if (sys) {
        char ok = VCALL(char (__thiscall*)(void*), sys, 0x68)(sys);
        if (g_166d9f4)
            VCALL(void (__thiscall*)(void*), (void*)g_166d9f4, 0xc0)((void*)g_166d9f4);
        self->mode = (ok == 0 ? 1 : 0) + 1;
        if (g_166d9f4)
            VCALL(void (__thiscall*)(void*), (void*)g_166d9f4, 0xc4)((void*)g_166d9f4);
        self->Init(0);
        if (ok) {
            Stopwatch sw(5, 0);
            sw.Restart();
            float acc = 0.0f;
            while (self->stop == 0) {
                float dt = (float)sw.GetElapsedTimeFloat() * sw.mfStopwatchCyclesToUnitsCoefficient;
                if (0.02f <= dt) {
                    if (dt > 0.06f)
                        dt = 0.06f;
                    acc += dt;
                    sw.RestartInline();
                    VCALL(void (__thiscall*)(void*, float, float), sys, 0xd0)(sys, acc, dt);
                    VCALL(void (__thiscall*)(void*), sys, 0xd4)(sys);
                }
                float e = (float)sw.GetElapsedTimeFloat() * sw.mfStopwatchCyclesToUnitsCoefficient;
                float rem = 0.02f;
                if (!(e > 0.02f))
                    rem = 0.02f - e;
                rem *= 1000.0f;
                int ms = CeilToInt(rem);
                ThreadSleep(&ms);
            }
            VCALL(void (__thiscall*)(void*), sys, 0x6c)(sys);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// LoadShared
// ---------------------------------------------------------------------------
struct IStream_ {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void* Next();         // +0x18
};
struct IProvider {
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual u32 GetType();        // +0xc
    virtual void p4(); virtual void p5(); virtual void p6();
    virtual int GetSize();        // +0x1c
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual int Read(int buf, int size);   // +0x30
};
struct IAlloc {
    virtual void a0(); virtual void a1();
    virtual int Alloc(int size, const char* name, int flags);   // +8
};
struct SharedPtr {
    u32 pad[6];
    SharedPtr(int data, int own, IAlloc* a);                    // 0093bc40
    static void* operator new(unsigned size, const char* name, int, int, int, int);  // 00926020
    static void  operator delete(void* p, const char* name, int, int, int, int);
};
struct Item {
    u32       pad0[5];
    int       data;       // +0x14
    int       size;       // +0x18
    u32       pad1c[3];
    SharedRef mShared;    // +0x28
};
IAlloc* GetDefaultAllocator();                                  // 00925cb0

// @ 0x00a22b90
bool __stdcall LoadShared(IStream_* stream, Item* item, int, int)
{
    IProvider* p = (IProvider*)stream->Next();
    if (p->GetType() == 0x347223d2) {
        int blk = *(int*)((char*)p + 4);
        item->data = *(int*)(blk + 0x10);
        item->size = p->GetSize();
        item->mShared.Assign((void*)blk);
        return true;
    }
    IAlloc* alloc = GetDefaultAllocator();
    item->data = alloc->Alloc(p->GetSize(), "Audio", 1);
    item->size = p->GetSize();
    SharedPtr* sp = new ("Audio", 0, 0, 0, 0) SharedPtr(item->data, 1, alloc);
    item->mShared.Assign(sp);
    bool ok = p->Read(item->data, item->size) == item->size;
    if (!ok) {
        item->data = 0;
        item->size = 0;
        SharedBlock* old = item->mShared.p;
        if (old) {
            item->mShared.p = 0;
            old->sub.Release();
        }
    }
    return ok;
}

// ---------------------------------------------------------------------------
// Manager helpers (sound list at +0x157438)
// ---------------------------------------------------------------------------
struct IRC {
    virtual void AddRef();
    virtual void Release();
};
struct IZ : IRC {
    virtual void z2(); virtual bool Ready();                  // +0xc
    virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
    virtual void z8(); virtual void z9(); virtual void z10();
    virtual void SetOwner(IRC* r);                            // +0x2c
    virtual void z12(); virtual void z13(); virtual void z14(); virtual void z15();
    virtual void SetKey(int k);                               // +0x40
    virtual void z17(); virtual void z18(); virtual void z19();
    virtual void SetId(int id);                               // +0x50
};

struct Mgr {
    void** vt;
    u8   pad04[0x95 - 4];
    u8   paused;                                              // +0x95
    u8   pad96[0x157438 - 0x96];
    SNode soundList;                                          // +0x157438

    bool SetPaused(int a, bool b);                            // 00a22d50
    bool AttachEffect(int key, int id, IRC* ref, IZ** out);   // 00a22df0
    bool FindObject2(int a, IZ** out, int c);                 // 00a23090
    bool FindByName(Snd* self, Snd** out);                    // 00a23160
    bool PickBest(int a, int b, bool onlyActive, Snd** out);  // 00a231e0
    bool PickNearest(int a, int b, bool onlyActive, Snd** from, Snd** out); // 00a232a0
};

typedef bool (__thiscall* SndFlagFn)(Snd*, int, int);
typedef void (__thiscall* SndSetFn)(Snd*, bool, int, float, int);
typedef void (__thiscall* SndFn80)(Snd*, int, int);
typedef float (__thiscall* SndFloatFn)(Snd*);
typedef void (__thiscall* SndAddRef)(Snd*);

#define SVT(s, off, T) ((T)((*(void***)(s))[(off) / 4]))

// @ 0x00a22d50
bool Mgr::SetPaused(int a, bool b)
{
    if (b) {
        if (paused != 0)
            return false;
    } else {
        if (paused == 0)
            return false;
    }
    paused = b;
    Snd* s   = Snd::FromNode(soundList.next);
    Snd* end = Snd::FromNode(&soundList);
    while (s != end) {
        SVT(s, 0x1c, SndSetFn)(s, b, 0, -1.0f, 1);
        if (!s->Check())
            SVT(s, 0x80, SndFn80)(s, 3, a);
        s = Snd::FromNode(s->node.next);
    }
    return true;
}

// @ 0x00a22df0
bool Mgr::AttachEffect(int key, int id, IRC* ref, IZ** out)
{
    if (VCALL(void* (__thiscall*)(Mgr*, int), this, 0x1d4)(this, id) != 0)
        return false;
    AutoRef<IRC> r(ref);
    if (r.p == 0)
        VCALL(void (__thiscall*)(Mgr*, int, AutoRef<IRC>*, int), this, 0x138)(this, key, &r, 0x21407ee);
    AutoRef<IZ> z;
    if (!VCALL(bool (__thiscall*)(Mgr*, AutoRef<IZ>*), this, 0x1b0)(this, &z))
        return false;
    z.p->SetOwner(r.p);
    z.p->SetKey(key);
    z.p->SetId(id);
    if (!z.p->Ready())
        return false;
    if (out) {
        z.p->AddRef();
        *out = z.p;
    }
    return true;
}

struct Query {
    int a;
    u32 key;
    int c;
};

// @ 0x00a22fa0
struct ISvc {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual bool Lookup(Query* q, AutoRef<IZ>* out, int, int, int, int);   // +0xc
};
ISvc* GetSvc();                                   // 008de1a0

bool __stdcall FindObject(int a, IZ** out, int c)
{
    Query q;
    q.key = 0x2b9f662;
    q.c = c;
    q.a = a;
    AutoRef<IZ> r;
    ISvc* svc = GetSvc();
    if (r.p) {
        IZ* old = r.p;
        r.p = 0;
        old->Release();
    }
    if (!svc->Lookup(&q, &r, 0, 0, 0, 0))
        return false;
    if (out) {
        r.p->AddRef();
        *out = r.p ? (IZ*)((char*)r.p + 0x14) : 0;
    }
    return true;
}

// @ 0x00a23090
bool Mgr::FindObject2(int a, IZ** out, int c)
{
    Query q;
    q.key = 0x2b9f662;
    q.c = c;
    q.a = a;
    AutoRef<IZ> r;
    if (!VCALL(bool (__thiscall*)(Mgr*, Query*, AutoRef<IZ>*), this, 0x18c)(this, &q, &r))
        return false;
    if (out) {
        r.p->AddRef();
        *out = r.p ? (IZ*)((char*)r.p + 0x14) : 0;
    }
    return true;
}

// @ 0x00a23160
bool Mgr::FindByName(Snd* self, Snd** out)
{
    if (out == 0)
        return false;
    Snd* s   = Snd::FromNode(soundList.next);
    Snd* end = Snd::FromNode(&soundList);
    while (s != end) {
        if (s != self) {
            if (SVT(self, 0xc4, bool (__thiscall*)(Snd*, Snd*))(self, s)) {
                SVT(s, 0, SndAddRef)(s);
                *out = s;
                return true;
            }
        }
        s = Snd::FromNode(s->node.next);
    }
    return false;
}

// @ 0x00a231e0
bool Mgr::PickBest(int a, int b, bool onlyActive, Snd** out)
{
    double best = 1000000000000.0;
    Snd* found = 0;
    Snd* s   = Snd::FromNode(soundList.next);
    Snd* end = Snd::FromNode(&soundList);
    while (s != end) {
        if ((!onlyActive || !SVT(s, 0x20, SndFlagFn)(s, -1, 0)) &&
            *(int*)((char*)s + 0x38) == a && *(int*)((char*)s + 0x3c) != b) {
            double d = SVT(s, 0x4c, SndFloatFn)(s);
            if (best > d) {
                best = d;
                found = s;
            }
        }
        s = Snd::FromNode(s->node.next);
    }
    if (found && out) {
        SVT(found, 0, SndAddRef)(found);
        *out = found;
    }
    return found != 0;
}

// @ 0x00a232a0
bool Mgr::PickNearest(int a, int b, bool onlyActive, Snd** from, Snd** out)
{
    Snd* s = *from;
    Snd* found = 0;
    float best = 0.0f;
    Snd* end = Snd::FromNode(&soundList);
    while (s != end) {
        if ((!onlyActive || !SVT(s, 0x20, SndFlagFn)(s, -1, 0)) &&
            *(int*)((char*)s + 0x38) == a && *(int*)((char*)s + 0x3c) != b) {
            float d = SVT(s, 0x84, SndFloatFn)(s);
            if (d > best) {
                best = d;
                found = s;
            }
        }
        s = Snd::FromNode(s->node.next);
    }
    if (found && out) {
        SVT(found, 0, SndAddRef)(found);
        *out = found;
    }
    return found != 0;
}
