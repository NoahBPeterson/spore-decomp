// Slice s00a23360 -- EA::Audio::System helpers plus EASTL hash-table / rbtree
// instance methods and the audio resource-device stopwatch helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#include <math.h>

typedef unsigned char u8;
typedef unsigned int  u32;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);

#define EA_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// new-expression forms used by the original EA allocator wrappers.
void* operator new(unsigned int, const char*, int, int, const char*, int);
void  operator delete(void*);
void  operator_delete__(void*);              // 0x00f47380
void  operator_delete_array(void*);          // 0x00f47380

extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);

// Virtual call by vtable byte offset (slot names not recovered).
template<class R> static inline R vc(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> static inline R vc(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
template<class R, class A1, class A2> static inline R vc(void* o, int off, A1 a1, A2 a2)
{ return ((R (__thiscall*)(void*, A1, A2))(*(void***)o)[off / 4])(o, a1, a2); }
template<class R, class A1, class A2, class A3> static inline R vc(void* o, int off, A1 a1, A2 a2, A3 a3)
{ return ((R (__thiscall*)(void*, A1, A2, A3))(*(void***)o)[off / 4])(o, a1, a2, a3); }
template<class R, class A1, class A2, class A3, class A4>
static inline R vc(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4))(*(void***)o)[off / 4])(o, a1, a2, a3, a4); }

// ---------------------------------------------------------------------------
// EA::Audio::System (only the members touched by this slice; layout from the
// retail constructor at 0xa33600).
// ---------------------------------------------------------------------------
struct ISystem {
    virtual void vInit();
    virtual ~ISystem();
};

struct AutoMsg { u32 w0; u32 w1; };
struct MutexLike { u32 a, b; };

struct System : ISystem {
    u8       pad_04[4];                // +0x04
    void*    mAutoMsg;                 // +0x08 (IHandlerRC subobject)
    u8       pad_0c[0x9a - 0x0c];
    u8       mbMuted;                  // +0x9a
    u8       pad_9b[0x400 - 0x9b];
    float    s400;                     // +0x400
    u8       pad_404[0x157438 - 0x404];
    void*    listNext;                 // +0x157438
    void*    listPrev;                 // +0x15743c
    u8       pad_157440[0x15bbe4 - 0x157440];
    float    pos[3];                   // +0x15bbe4
    u8       b15bbf0;                  // +0x15bbf0

    float GetPosDist(float* p);        // 0x00a23360
    void  MuteAll(bool bMute, bool bParam); // 0x00a233b0
};

extern float g_1485720;
extern int   g_16e61a8;
extern const char g_lockName[];   // 0x01452970

void __cdecl sub_112c600();                     // 0x0112c600
void __cdecl sub_112c620();                     // 0x0112c620
struct MuteParams { double d0; float fParam; float fMute; float f3; };
struct PluginIface { void Call112ccc0(int a, void* b); };    // 0x0112ccc0 (thiscall)
struct VoiceContainer { void* FindPlugin(u32 id); };         // 0x00a34230

// @ 0x00a23360
float System::GetPosDist(float* p)
{
    float result;
    if (b15bbf0) {
        double dx = pos[0] - p[0];
        double dy = pos[1] - p[1];
        double dz = pos[2] - p[2];
        double d = dx * dx;
        d = d + dz * dz;
        d = d + dy * dy;
        result = (float)sqrt(d);
    } else {
        result = 0.0f;
    }
    return result;
}

// @ 0x00a233b0
void System::MuteAll(bool bMute, bool bParam)
{
    if (mbMuted == bMute)
        return;

    // Walk the intrusive list anchored at &listNext (link parked at +0x10).
    u8* head = (u8*)listNext;
    u8* anchor = (u8*)&listNext;
    u8* it = head ? head - 0x10 : 0;
    u8* end = anchor ? anchor - 0x10 : 0;
    while (it != end) {
        bool bFlag = false;
        void* obj = vc<void*>(it, 0x30);
        if (vc<bool>(obj, 0x24, (u32)0x9d554d95, &bFlag) && bFlag)
            vc<void>(it, 0x1c, bMute, 0, 0.0f, (void*)1);
        u8* nxt = *(u8**)(it + 0x10);
        it = nxt ? nxt - 0x10 : 0;
    }

    void* container = vc<void*>(this, 0x17c, (u32)0xf1cc1687);
    if (!container)
        return;
    mbMuted = bMute;
    void* vcp = (u8*)container + 0x10;
    void* plugin = ((VoiceContainer*)vcp)->FindPlugin(0x47614630);
    if (plugin) {
        MuteParams params;
        params.d0 = 0.0;
        params.fParam = bParam ? 0.0f : s400;
        params.fMute = bMute ? 0.0f : g_1485720;
        params.f3 = 0.0f;
        if (g_16e61a8)
            sub_112c600();
        ((PluginIface*)plugin)->Call112ccc0(0, &params);
    } else {
        void* plugin2 = ((VoiceContainer*)vcp)->FindPlugin(0x44616330);
        if (!plugin2)
            return;
        if (g_16e61a8)
            sub_112c600();
        ((PluginIface*)plugin2)->Call112ccc0(bMute ? 5 : 3, 0);
    }
    if (g_16e61a8)
        sub_112c620();
}

// ---------------------------------------------------------------------------
// EASTL hashtable<int, pair<const int, RefCounted*> > (buckets at +4).
// Node: { int key; void* value; Node* next; } (0x0c bytes).
// ---------------------------------------------------------------------------
struct EHNode { int key; void* value; EHNode* next; };
struct EInsertRes;
struct ERehashInfo { int bNeed; u32 nNew; };
struct AllocStub { void RehashRequired(ERehashInfo* out, u32 nBuckets, u32 nElems, int extra); }; // 0x00921440
struct EInsertRes { EHNode* node; EHNode** bucket; bool inserted; u8 pad[3]; };

struct EHTable {
    void*    allocatorTag;   // +0
    EHNode** mpBuckets;      // +4
    u32      mnBucketCount;  // +8
    u32      mnElementCount; // +0x0c
    AllocStub* mAllocator;   // +0x10
    void     DoRehash(u32 n);                      // 0x00902000
    EInsertRes* DoInsertKey(EInsertRes* out, const int* pkey, u32 unused); // 0x00a23830
};

// @ 0x00a23830
EInsertRes* EHTable::DoInsertKey(EInsertRes* out, const int* pkey, u32 unused)
{
    (void)unused;
    int key = *pkey;
    u32 bucket = (u32)key % mnBucketCount;
    EHNode** pb = &mpBuckets[bucket];
    EHNode* p = *pb;
    while (p) {
        if (p->key == key) {
            out->node = p;
            out->bucket = pb;
            out->inserted = false;
            return out;
        }
        p = p->next;
    }
    ERehashInfo ri;
    mAllocator->RehashRequired(&ri, mnBucketCount, mnElementCount, 1);
    EHNode* n = (EHNode*)operator new(0x0c, "EASTL", 0, 0, EA_FILE, 0xd1);
    if (n) {
        n->key = *(int*)((char*)pkey);
        void* v = *(void**)((char*)pkey + 4);
        n->value = v;
        if (v)
            *(int*)((char*)v + 4) += 1;
    }
    n->next = 0;
    if (ri.bNeed) {
        bucket = (u32)key % ri.nNew;
        DoRehash(ri.nNew);
    }
    n->next = mpBuckets[bucket];
    mpBuckets[bucket] = n;
    mnElementCount += 1;
    out->node = n;
    out->bucket = &mpBuckets[bucket];
    out->inserted = true;
    return out;
}

// ---------------------------------------------------------------------------
// vector<RefCounted*> destruction (begin at +0, end at +4).
// ---------------------------------------------------------------------------
struct RefCounted { virtual void v00(); virtual void Release(); };

struct RefVec {
    RefCounted** mpBegin;   // +0
    RefCounted** mpEnd;     // +4
    void Destroy();         // 0x00a23920
};

// @ 0x00a23920
void RefVec::Destroy()
{
    RefCounted** it = mpBegin;
    RefCounted** end = mpEnd;
    for (; it < end; ++it) {
        RefCounted* p = *it;
        if (p)
            p->Release();
    }
    RefCounted** begin = mpBegin;
    if (begin) {
        if (*(int*)((char*)begin - 4) != 0)
            operator_delete__(begin);
    }
}

// ---------------------------------------------------------------------------
// fixed-pool hash table (buckets +4, count +8, size +0xc, free list +0x1c,
// pool +0x24..+0x28, inline buckets +0x30).
// Node: { int key; Node* next; }.
// ---------------------------------------------------------------------------
struct PHNode { int key; PHNode* next; };

struct PHTable {
    u32       pad0;
    PHNode**  mpBuckets;    // +4
    u32       mnBucketCount;// +8
    u32       mnElementCount;// +0xc
    u32       pad10[3];
    PHNode*   mpFreeList;   // +0x1c
    u32       pad20;
    void*     mpPoolBegin;  // +0x24
    void*     mpPoolEnd;    // +0x28
    u32       pad2c;
    void*     mpInline;     // +0x30

    int  Erase(const int* pkey);                   // 0x00a23d20
    PHNode** EraseNode(PHNode** out, PHNode* n, PHNode** pb); // 0x00a23db0
    void FreeBuckets(PHNode** buckets, u32 count); // 0x00a24480
};

// @ 0x00a23d20
int PHTable::Erase(const int* pkey)
{
    int oldCount = (int)mnElementCount;
    u32 bucket = (u32)*pkey % mnBucketCount;
    PHNode** pb = &mpBuckets[bucket];
    if (*pb) {
        PHNode* p;
        do {
            p = *pb;
            if (*pkey == p->key)
                break;
            pb = &p->next;
        } while (p->next);
        while (*pb) {
            p = *pb;
            if (*pkey != p->key)
                break;
            *pb = p->next;
            if (p != (PHNode*)mpInline) {
                if ((void*)p < mpPoolBegin || (void*)p >= mpPoolEnd) {
                    operator_delete__(p);
                } else {
                    p->key = (int)mpFreeList;
                    mpFreeList = p;
                }
            }
            mnElementCount -= 1;
        }
    }
    return oldCount - (int)mnElementCount;
}

// @ 0x00a23db0
PHNode** PHTable::EraseNode(PHNode** out, PHNode* n, PHNode** pb)
{
    PHNode* nxt = (PHNode*)out[1];
    out[1] = (PHNode*)pb;
    *out = nxt;
    while (nxt == 0) {
        out[1] = (PHNode*)((char*)out[1] + 4);
        nxt = *(PHNode**)out[1];
        *out = nxt;
    }
    PHNode* head = *pb;
    if (head == n) {
        *pb = head->next;
    } else {
        for (PHNode* q = head->next; q != n; q = q->next)
            head = q;
        head->next = n->next;
    }
    if (n != (PHNode*)mpInline) {
        if ((void*)n >= mpPoolBegin && (void*)n < mpPoolEnd) {
            n->key = (int)mpFreeList;
            mpFreeList = n;
            mnElementCount -= 1;
            return out;
        }
        operator_delete__(n);
    }
    mnElementCount -= 1;
    return out;
}

// @ 0x00a24480
void PHTable::FreeBuckets(PHNode** buckets, u32 count)
{
    struct FNode { u32 freeLink; void* value; FNode* next; };
    for (u32 i = 0; i < count; ++i) {
        FNode* c;
        FNode* n = (FNode*)buckets[i];
        while (n) {
            c = n;
            n = c->next;
            void* val = c->value;
            if (val)
                vc<void>(val, 4);
            if (c != (FNode*)mpInline) {
                if ((void*)c < mpPoolBegin || (void*)c >= mpPoolEnd) {
                    operator_delete__(c);
                } else {
                    c->freeLink = (u32)mpFreeList;
                    mpFreeList = (PHNode*)c;
                }
            }
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// rbtree node (0x18) and helpers.
// ---------------------------------------------------------------------------
struct RBNode {
    RBNode* left;    // +0
    RBNode* right;   // +4
    RBNode* parent;  // +8
    u8      color;   // +0xc
    u8      pad0d[3];
    u32     key0;    // +0x10
    u32     key1;    // +0x14
};

struct RBTree {
    u8      pad00[0x1c];
    void*   mpFreeList;                 // +0x1c
    u8      pad20[0x2c - 0x20];
    u32     mAllocator;                 // +0x2c
    void   Assign(void* arg);                   // 0x00a24210 (opaque rbtree assignment)
    void*  AllocNode2(const void* src);         // 0x00a243e0
    RBNode* CloneNode(RBNode* src, RBNode* parent);   // 0x00a24530
};

void __cdecl sub_00a212b0();
void __cdecl sub_00a21310();
void __cdecl sub_00a22410();

// @ 0x00a24210
void RBTree::Assign(void* arg)
{
    // Opaque eastl rbtree range-copy helper: rebuild the tree from the source range.
    (void)arg;
    sub_00a212b0();
    sub_00a21310();
    sub_00a22410();
}

// @ 0x00a243e0
void* RBTree::AllocNode2(const void* src)
{
    struct Node20 { u32 d[5]; };
    Node20* n;
    if (mpFreeList) {
        n = (Node20*)mpFreeList;
        mpFreeList = (void*)n->d[0];
    } else {
        n = (Node20*)operator new(mAllocator, "EASTL", 0, 0, EA_FILE, 0xd1);
    }
    if (n) {
        const u32* s = (const u32*)src;
        n->d[0] = s[0];
        n->d[1] = s[1];
        n->d[2] = s[2];
        void* v = (void*)s[3];
        n->d[3] = (u32)v;
        if (v)
            vc<void>((char*)v + 4, 0);
    }
    n->d[4] = 0;
    return n;
}

// @ 0x00a245e0  (free function: src, parent) -> new 0x18 node
RBNode* __stdcall RB_AllocNode(const RBNode* src, RBNode* parent)
{
    RBNode* n = (RBNode*)operator new(0x18, "EASTL", 0, 0, EA_FILE, 0xd1);
    u32* kv = (u32*)((char*)n + 0x10);
    if (kv) {
        kv[0] = src->key0;
        kv[1] = src->key1;
    }
    n->left = 0;
    n->right = 0;
    n->parent = parent;
    n->color = src->color;
    return n;
}

// @ 0x00a24530
RBNode* __thiscall RBTree::CloneNode(RBNode* src, RBNode* parent)
{
    RBNode* dst = RB_AllocNode(src, parent);
    if (src->left)
        dst->left = CloneNode(src->left, dst);
    RBNode* r = src->right;
    if (r) {
        RBNode* prev = dst;
        do {
            RBNode* n = (RBNode*)operator new(0x18, "EASTL", 0, 0, EA_FILE, 0xd1);
            if ((char*)n + 0x10) {
                n->key0 = r->key0;
                n->key1 = r->key1;
            }
            n->left = 0;
            n->right = 0;
            n->parent = prev;
            n->color = r->color;
            prev->right = n;
            if (r->left)
                n->left = CloneNode(r->left, n);
            r = r->right;
            prev = n;
        } while (r);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// uninitialized copy of 0x14-byte elements with a ref-counted tail pointer.
// ---------------------------------------------------------------------------
struct Elem20 { u32 d0, d1, d2, d3; void* ref; };

// @ 0x00a24750
Elem20* __cdecl CopyElems20(Elem20** out, Elem20* first, Elem20* last)
{
    *out = last;
    for (; first != last; first += 1) {
        Elem20* dst = *out;
        if (dst) {
            dst->d0 = first->d0;
            dst->d1 = first->d1;
            dst->d2 = first->d2;
            dst->d3 = first->d3;
            void* v = first->ref;
            dst->ref = v;
            if (v)
                vc<void>(v, 0);
        }
        *out += 1;
    }
    return *out;
}

// ---------------------------------------------------------------------------
// rw::core::filesys::DeviceDriver + audio resource-device helpers.
// ---------------------------------------------------------------------------
struct DeviceDriver { void ctor(const char* name); };           // 0x011e5d80

struct Mutex {
    u32 a;
    void ctor(int a, int b);           // 0x009222a0
    int  Lock(const char* name);       // 0x009221b0
    int  Unlock();                     // 0x00922270
};

struct MutexGuard {
    Mutex* m;
    MutexGuard(Mutex* mm, const char* n) : m(mm) { m->Lock(n); }
    ~MutexGuard() { m->Unlock(); }
};

struct Stopwatch {
    long long mnStartTime;         // +0
    long long mnTotalElapsedTime;  // +8
    int       mnUnits;             // +0x10
    float     mfCyclesToUnitsCoefficient; // +0x14
    void      ctor(int units, int b);                       // 0x0093a560
    long long GetElapsedTimeFloat();                        // 0x0093a3a0
};

struct ProfileTimer {
    Stopwatch sw;                  // +0
    void*     mpAccumulator;       // +0x18
    ProfileTimer(void* acc);       // 0x00a248a0
    void Accumulate();             // 0x00a24900
};

// scoped stopwatch: on destruction folds the elapsed time into the accumulator.
struct ScopedTimer {
    Stopwatch sw;                  // +0
    float*    acc;                 // +0x18
    ScopedTimer(float* a);         // 0x00a248a0
    ~ScopedTimer()
    {
        *acc = (float)sw.GetElapsedTimeFloat() * sw.mfCyclesToUnitsCoefficient + *acc;
    }
};

struct RDD {
    void*   vftable;               // +0
    u8      pad04[0x14 - 4];
    void**  mpBegin;               // +0x14
    void**  mpEnd;                 // +0x18
    void**  mpCapacity;            // +0x1c
    u8      pad20[0x28 - 0x20];
    Mutex   mMutex;                // +0x28
    u8      pad2c[0x58 - 0x2c];
    float   mfAccum;               // +0x58
    ProfileTimer mTimer;           // +0x5c

    void    Construct();           // 0x00a247f0
    void*   FindById(void* id);                              // 0x00a24970
    void*   FindAndCall1(void* id, void* a, void* b, void* c, void* d); // 0x00a24a90
    int     FindAndCall2(void* id, void* a, void* b, void* c, void* d); // 0x00a24b40
    long long FindAndCall3(void* id, void* a, void* b, void* c, void* d, void* e); // 0x00a24bf0
    void*   FindAndCall4(void* id);  // 0x00a24cb0
    long long FindAndCall5(void* id); // 0x00a24d60

    bool    Tick3(void* a, void* b, void* c);   // 0x00a24930
};

// @ 0x00a247f0  EA::Audio::ResourceDeviceDriver::ResourceDeviceDriver
void RDD::Construct()
{
    ((DeviceDriver*)this)->ctor("resman:");
    vftable = (void*)0x1452b00;
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mMutex.ctor(0, 1);
}

// @ 0x00a248a0
ProfileTimer::ProfileTimer(void* acc)
{
    sw.ctor(4, 0);
    mpAccumulator = acc;
    if (sw.mnUnits == 1) {
        unsigned long long t = __rdtsc();
        *(unsigned int*)&sw.mnStartTime = (unsigned int)t;
        *(unsigned int*)((char*)&sw.mnStartTime + 4) = (unsigned int)(t >> 32);
    } else {
        long long c;
        QueryPerformanceCounter(&c);
        *(unsigned int*)&sw.mnStartTime = (unsigned int)c;
        *(unsigned int*)((char*)&sw.mnStartTime + 4) = (unsigned int)(c >> 32);
    }
    *(unsigned int*)&sw.mnTotalElapsedTime = 0;
    *(unsigned int*)((char*)&sw.mnTotalElapsedTime + 4) = 0;
}

// @ 0x00a24850
u32 __cdecl ParseResman(const char* param_1, u8* param_2)
{
    if (_strnicmp(param_1, "resman:", 7) == 0)
        param_1 = param_1 + 7;
    char c = *param_1;
    while (c != 0) {
        char hi = param_1[1];
        param_1 = param_1 + 1;
        hi = (char)(hi - 0x41);
        c = (char)(c - 0x41);
        *param_2 = (u8)((hi << 4) | c);
        param_1 = param_1 + 1;
        c = *param_1;
        param_2 = param_2 + 1;
    }
    return 1;
}

// @ 0x00a24900
void ProfileTimer::Accumulate()
{
    *(float*)mpAccumulator = (float)sw.GetElapsedTimeFloat() * sw.mfCyclesToUnitsCoefficient + *(float*)mpAccumulator;
}

// @ 0x00a24930
bool __thiscall RDD::Tick3(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    ProfileTimer local((void*)((char*)this + 0x5c));
    long long e = local.sw.GetElapsedTimeFloat();
    float* acc = (float*)local.mpAccumulator;
    *acc = (float)e * local.sw.mfCyclesToUnitsCoefficient + *acc;
    return false;
}

// @ 0x00a24970
void* __thiscall RDD::FindById(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    MutexGuard guard(&mMutex, g_lockName);
    mfAccum = (float)timer.sw.GetElapsedTimeFloat() * timer.sw.mfCyclesToUnitsCoefficient + mfAccum;
    void** it = mpBegin;
    void** end = mpEnd;
    void* r;
    for (;;) {
        if (it == end)
            return 0;
        r = *it;
        if (id == r)
            break;
        ++it;
    }
    return r;
}

// @ 0x00a24a90
void* __thiscall RDD::FindAndCall1(void* id, void* a, void* b, void* c, void* d)
{
    (void)c; (void)d;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    if (p != 0 && vc<void*>(p, 0x18) != 0)
        p = vc<void*>(vc<void*>(p, 0x18), 0x30, a, b);
    else
        p = 0;
    return p;
}

// @ 0x00a24b40
int __thiscall RDD::FindAndCall2(void* id, void* a, void* b, void* c, void* d)
{
    (void)c; (void)d;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    int r;
    if (p != 0 && vc<void*>(p, 0x18) != 0)
        r = vc<bool>(vc<void*>(p, 0x18), 0x38, a, b);
    else
        r = 0;
    return r;
}

// @ 0x00a24bf0
long long __thiscall RDD::FindAndCall3(void* id, void* a, void* b, void* c, void* d, void* e)
{
    (void)b; (void)d; (void)e;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    return (p != 0 && vc<void*>(p, 0x18) != 0)
        ? vc<bool>(vc<void*>(p, 0x18), 0x28, a, c) : 0;
}

// @ 0x00a24cb0
void* __thiscall RDD::FindAndCall4(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    void* r = 0;
    if (p) {
        void* q = vc<void*>(p, 0x18);
        if (q)
            r = vc<void*>(q, 0x1c);
    }
    return r;
}

// @ 0x00a24d60
long long __thiscall RDD::FindAndCall5(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    int r = 0;
    if (p) {
        void* q = vc<void*>(p, 0x18);
        if (q)
            r = vc<int>(q, 0x24, 0);
    }
    return (long long)r;
}
