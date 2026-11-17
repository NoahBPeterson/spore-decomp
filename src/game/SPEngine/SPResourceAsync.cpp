// src/game/SPEngine/SPResourceAsync.cpp -- migrated from slice(s) s006ae940, s006ad5c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPResourceAsync.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAsyncResourceRequest.h"
#include "SP/cJob.h"
#include "SP/cJobManager.h"
#include <intrin.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void ea_dealloc(void*);          // 0x00f47380
extern void FUN_006ae090(void*);            // 0x006ae090 callback thunk
extern void* vtbl_14093bc;
extern void* vtbl_13effb8;
extern void* vtbl_13eb938;
extern void* vtbl_13ef094;
extern void* vtbl_14094b4;
extern void* vtbl_14094b0;
extern void* vtbl_13fa72c;
extern "C" void* ea_eastl_alloc(unsigned size, void* zone, int, int, const char* file, int line); // 0xf473a0

// ---- items of slice s006ad5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Job {
    void f();   // 0x690120
};
struct AsyncJobStatus {
    SP::tJobStatus GetStatus() const; // 0x0068f970; reads status under the job-manager lock
};
extern "C" void ea_dealloc(void*);          // 0x00f47380
extern void FUN_006ae090(void*);            // 0x006ae090 callback thunk
struct Releasable { virtual void s0(); virtual void Release(); };
struct ObjX {
    void fn();             // FUN_006926b0
};
struct IfaceX {
    virtual void slot0();
};
struct Self {
    ObjX* mC;              // +0xc
    bool Get(void** out);
};
struct RBNode { RBNode* left; RBNode* right; char pad[0x1c - 8]; Releasable* mgr; };
struct RBTree {
    char pad[0x18];
    RBNode* freeList;    // 0x18
    char pad2[4];        // 0x1c
    RBNode* poolBegin;   // 0x20
    RBNode* poolEnd;     // 0x24
    void DoNukeSubtree(RBNode* n);
};
extern void* vtbl_14093bc;
extern void* vtbl_13effb8;
extern void* vtbl_13eb938;
extern void* vtbl_13ef094;
extern void* vtbl_14094b4;
extern void* vtbl_14094b0;
extern void* vtbl_13fa72c;
extern "C" void* ea_eastl_alloc(unsigned size, void* zone, int, int, const char* file, int line); // 0xf473a0
struct Job0   { void GetStatus(); };        // 0x690120
struct Job2   { void Add(); };              // FUN_0068f950
// ---- items of slice s006ad5c0 end

// ---- items of slice s006ae940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_14094d0;
extern void* vtbl_14094cc;
struct XRBTree { void DoNukeSubtree(void* n); };
struct Mutex2 { void dtor(); };   // EA::Thread::Mutex::~Mutex (0x922130)
// the 0x006aebd0 object: two bases (vtables 0x13eb938 / 0x13ef094 restored on exit), the mutex at +0x10 and the
// tree at +0x40, nuked from its root at +0x4c
struct RCacheB0 { virtual void Slot0(); ~RCacheB0() {} };
struct RCacheB1 { virtual void Slot0(); ~RCacheB1() {} };
struct RCacheMutex { char mData[0x30]; ~RCacheMutex(); };   // 0x922130
struct RCacheTree {
    void* mAnchor[3];
    void* mpRoot;          // +0x0c
    void* mRest[2];
    void DoNukeSubtree(void* n);
    ~RCacheTree() { DoNukeSubtree(mpRoot); }
};
struct RCacheObj_6aebd0 : RCacheB0, RCacheB1 {
    char pad08[8];
    RCacheMutex mMutex;    // +0x10
    RCacheTree  mTree;     // +0x40
    ~RCacheObj_6aebd0();
};
// ---- items of slice s006ae940 end

// @ 0x006ae060
void * SP::cAsyncResourceRequest::AsInterface(EA::COM::InterfaceId iid)
{
    if (iid == 0x3a11b3f || iid == 0xae9cb0fa || iid == 0xee3f516e ||
        iid == 0x3a212ac)
        return this;
    return 0;
}

// @ 0x006ae0d0
unsigned char __fastcall FUN_006ae0d0(void** self)
{
    unsigned char r =
        ((unsigned char(__thiscall*)(void*))(*(void***)self[2])[8])(self[2]);
    ((void(__thiscall*)(void*))(*(void***)self)[1])(self);
    return r;
}

// @ 0x006ae0f0
unsigned char __fastcall FUN_006ae0f0(void** self)
{
    unsigned char r =
        ((unsigned char(__thiscall*)(void*))(*(void***)self[2])[9])(self[2]);
    ((void(__thiscall*)(void*))(*(void***)self)[2])(self);
    return r;
}

// @ 0x006ae110
void __fastcall FUN_006ae110(void** p)
{
    Job* q = (Job*)*p;
    if (q)
        q->f();
}

struct Base_6ae210_0 { virtual void v0(); ~Base_6ae210_0() {} };
struct Base_6ae210_1 { virtual void v1(); ~Base_6ae210_1() {} };
struct IRefRel_6ae120 { virtual void v0(); virtual void v1(); virtual void Release(); };
struct RefPtr_6ae120 {
    IRefRel_6ae120* p;
    ~RefPtr_6ae120() { if (p) p->Release(); }
};
struct __declspec(novtable) Holder_6ae120 : Base_6ae210_0, Base_6ae210_1 {
    void* m8;
    RefPtr_6ae120 mc;
    RefPtr_6ae120 m10;
    ~Holder_6ae120();
};

// @ 0x006ae120
Holder_6ae120::~Holder_6ae120()
{
}

struct Base_6ae190 { virtual void v0(); ~Base_6ae190() {} };
struct __declspec(novtable) Holder_6ae190 : Base_6ae190 {
    void* m4;
    RefPtr_6ae120 m8;
    RefPtr_6ae120 mc;
    ~Holder_6ae190();
};

// @ 0x006ae190
Holder_6ae190::~Holder_6ae190()
{
}

struct Node_6ae210 : Base_6ae210_0, Base_6ae210_1 {
    void* m8;
    Job0* mpJob;
    ~Node_6ae210();
};

// @ 0x006ae210
Node_6ae210::~Node_6ae210()
{
    if (mpJob)
        mpJob->GetStatus();
}

// @ 0x006ae280
bool SP::cAsyncResourceRequest::IsComplete()
{
    AsyncJobStatus* job;
    memcpy(&job, mFutureResource, sizeof(job));
    if (job) {
        switch (job->GetStatus()) {
        case SP::kJobStatusFinished:
        case SP::kJobStatusFailed:
            return true;
        default:
            return false;
        }
    }
    return true;
}

// @ 0x006ae2a0
void* __fastcall FUN_006ae2a0(void* self, int unused, void* p)
{
    (void)unused;
    int* old = *(int**)self;
    if (p != old) {
        if (p)
            _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
        *(void**)self = p;
        if (old) {
            volatile long* rc = (volatile long*)((char*)old + 8);
            long n = _InterlockedExchangeAdd(rc, -1);
            if (n == 1) {
                _InterlockedExchange(rc, 1);
                void* recv = (char*)old + 4;
                if (*(void**)recv)
                    (*(void(__thiscall**)(void*, int))(*(void***)recv))(recv, 1);
            }
        }
    }
    return self;
}

// @ 0x006ae2f0
bool FUN_006ae2f0(char* p1, void* p2)
{
    void (*oldFn)(void*);
    void* oldObj;
    if (p2) {
        (*(void(__thiscall**)(void*))(*(void***)p2))(p2);
        oldFn = *(void(**)(void*))(p1 + 0x24);
        oldObj = *(void**)(p1 + 0x20);
        *(void**)(p1 + 0x20) = p2;
        *(void(**)(void*))(p1 + 0x24) = &FUN_006ae090;
        if (oldFn)
            oldFn(oldObj);
        return true;
    } else {
        oldFn = *(void(**)(void*))(p1 + 0x24);
        oldObj = *(void**)(p1 + 0x20);
        *(void**)(p1 + 0x20) = 0;
        *(void(**)(void*))(p1 + 0x24) = 0;
        if (oldFn)
            oldFn(oldObj);
        return true;
    }
}

// @ 0x006ae3f0
void FUN_006ae3f0()
{}

// @ 0x006ae4c0
bool Self::Get(void** out)
{
    ObjX* p = *(ObjX**)((char*)this + 0xc);
    if (p) {
        p->fn();
        IfaceX* q = *(IfaceX**)(*(int*)((char*)this + 0xc) + 0x20);
        if (q)
            q->slot0();
        *out = q;
        return q != 0;
    }
    IfaceX* q = 0;
    *out = q;
    return q != 0;
}

// @ 0x006ae510
void* __fastcall FUN_006ae510(void* self, int unused, void* arg)
{
    (void)unused;
    *(void**)self = &vtbl_13fa72c;
    *(void**)((char*)self + 4) = &vtbl_13ef094;
    *(void**)((char*)self + 8) = 0;
    *(void**)self = &vtbl_14094b4;
    *(void**)((char*)self + 4) = &vtbl_14094b0;
    int v = *(int*)arg;
    *(int*)((char*)self + 0xc) = v;
    if (v)
        ((Job2*)v)->Add();
    return self;
}

// @ 0x006ae590
void FUN_006ae590()
{}

// @ 0x006ae600
void RBTree::DoNukeSubtree(RBNode* n)
{
    while (n) {
        DoNukeSubtree(n->left);
        RBNode* next = n->right;
        Releasable* mgr = (Releasable*)n->mgr;
        if (mgr)
            mgr->Release();
        if (n < poolBegin || n >= poolEnd) {
            ea_dealloc(n);
        } else {
            n->left = freeList;
            freeList = n;
        }
        n = next;
    }
}

// @ 0x006ae660
void* __fastcall FUN_006ae660(void* self, void* val)
{
    void* n = *(void**)((char*)self + 0x18);
    if (n)
        *(void**)((char*)self + 0x18) = *(void**)n;
    else
        n = ea_eastl_alloc(*(unsigned*)((char*)self + 0x28), &vtbl_14093bc, 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    void* d = (char*)n + 0x10;
    if (d) {
        *(void**)d = *(void**)val;
        *(void**)((char*)d + 4) = *(void**)((char*)val + 4);
        *(void**)((char*)d + 8) = *(void**)((char*)val + 8);
        *(void**)((char*)d + 0xc) = *(void**)((char*)val + 0xc);
        void* r = *(void**)((char*)d + 0xc);
        if (r)
            (*(void(__thiscall**)(void*))(*(void***)r))(r);
    }
    return n;
}

// @ 0x006ae880
void FUN_006ae880()
{}

// @ 0x006ae940
void FUN_006ae940()
{}

// @ 0x006aea90
void FUN_006aea90()
{}

// @ 0x006aebd0
RCacheObj_6aebd0::~RCacheObj_6aebd0()
{
}

// @ 0x006aec60
void FUN_006aec60()
{}

// cAsyncResourceManager::cAsyncResourceManager(): the retail build inlines the two base-class vptr stores and
// emits the member ctors (Mutex, eastl::fixed_map) with an EH frame that unwinds the constructed members.
struct CtorBase1 {                                   // EA::COM::IUnknown32 / EA::ResourceMan::IAsync
    virtual void slot_0();
    virtual void slot_1();
    virtual ~CtorBase1();
    CtorBase1() {}
};
struct CtorBase2 {                                   // EA::RefCountTemplate<EA::Thread::AtomicInt<int> >
    virtual ~CtorBase2();
    int mRefCount;                                   // +0x8
    int mPad;                                        // +0xc
    CtorBase2() { volatile long* rc = (volatile long*)&mRefCount; _InterlockedExchange(rc, 0); }
};
struct CtorMutex {
    __int64 mAlign;
    CtorMutex(const void* params = 0, bool b = true);  // 0x9222a0 EA::Thread::Mutex::Mutex
    ~CtorMutex();                                      // 0x922130 EA::Thread::Mutex::~Mutex
    unsigned int mData[0x28 / 4];
};
struct CtorMap {
    CtorMap();                                         // 0x6aea30 eastl::fixed_map ctor
    ~CtorMap();
    unsigned int mData[0x84c / 4];
};
struct CtorResMgr : CtorBase1, CtorBase2 {
    CtorMutex mMutex;                                  // +0x10
    CtorMap mMap;                                      // +0x40
    CtorResMgr();
};

// @ 0x006aedc0
CtorResMgr::CtorResMgr()
{
}

// @ 0x006af260
void FUN_006af260()
{}
