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
struct Mutex2 {                    // EA::Thread::Mutex
    void dtor();               // 0x922130
    void Lock(void* name);     // 0x9221b0
    void Unlock();             // 0x922270
};
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

// async request tree / job helpers (0x006aee60, 0x006af080, 0x006af150)
struct AsyncKey { unsigned k0; unsigned k1; unsigned k2; };   // 12 bytes
struct AsyncValue { AsyncKey key; void* obj; };              // 16 bytes (map value)
struct AsyncNode {                    // 0x20 bytes
    AsyncNode* pLeft;      // +0x00
    AsyncNode* pRight;     // +0x04
    AsyncNode* pParent;    // +0x08
    unsigned   mColor;     // +0x0c
    unsigned   k0;         // +0x10
    unsigned   k1;         // +0x14
    unsigned   k2;         // +0x18
    void*      mpValue;    // +0x1c
};
struct AsyncTree {
    unsigned   mUnk00;      // +0x00
    AsyncNode* mpRoot;      // +0x04  (header; its address is the end sentinel)
    AsyncNode* mpCurrent;   // +0x08
    unsigned   mUnk0c[2];   // +0x0c
    unsigned   mCount;      // +0x14
    AsyncNode* mpFree;      // +0x18
    unsigned   mUnk1c;      // +0x1c
    void*      mpPoolBegin; // +0x20
    void*      mpPoolEnd;   // +0x24
};
static inline bool KeyLess3(unsigned a0, unsigned a1, unsigned a2,
                            unsigned b0, unsigned b1, unsigned b2)
{
    if (a0 != b0) return a0 < b0;
    if (a2 != b2) return a2 < b2;
    return a1 < b1;
}
extern "C" void* F_926020(int, const char*, int, int, int, int);   // 0x926020 zone new
extern "C" void* F_f473a0(int, const char*, int, int, int, int);   // 0xf473a0 eastl/EA alloc
extern "C" void  F_6aec50(void);                                   // 0x6aec50 continuation
extern "C" void* F_921580(void*);                                  // 0x921580 RBTreeIncrement
extern "C" void  F_9216a0(void*, void*, void*, int);               // 0x9216a0 RBTreeInsert
extern void*     __fastcall F_6ae660(void* self, int, void*);      // 0x6ae660 allocate node
extern void      __fastcall F_6ae700(void* self, int, void*, void*, void*, int); // 0x6ae700 hint insert
extern void      __fastcall F_6ae770(void* self, int, void*, void*, int);        // 0x6ae770 lower bound
extern void      __fastcall F_6ae2a0(void* self, int, void*);      // 0x6ae2a0 AutoRefCount operator=
extern void*     __fastcall F_8dc5e0(void* self, int);             // 0x8dc5e0 PFRecordRead::GetBuffer
extern void*     __fastcall F_93bca0(void* self, int, void*, void*); // 0x93bca0 ctor
extern void*     __fastcall F_93c270(void* self, int, void*, void*, const char*); // 0x93c270 ctor
extern void      __fastcall F_93bb40(void* self, int, int, float); // 0x93bb40 SetOption
extern bool      __fastcall F_68f9f0(void* self, int, void*, void*); // 0x68f9f0 Continuation
extern void*     __fastcall F_c7f560(void* self, int, void*, void*); // 0xc7f560 lower_bound
extern void*     __fastcall F_6ae510(void* self, int, void*);      // 0x6ae510 Resource::Async ctor
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

// Construction view of the async resource request (0x006ae510): the request base, then the atomic refcount base
// (count zeroed by an interlocked exchange), each with an unwind state; the job ref member adds a reference.
struct AsyncReqBase_6ae510 { virtual void v0(); ~AsyncReqBase_6ae510() { (void)this; } };
struct AsyncRefCount_6ae510 {
    virtual void r0();
    volatile long mRefCount;                 // +0x08
    AsyncRefCount_6ae510() { volatile long* r = &mRefCount; _InterlockedExchange(r, 0); }
    ~AsyncRefCount_6ae510() { (void)this; }
};
struct AsyncJobRef_6ae510 {
    Job2* mpJob;
    AsyncJobRef_6ae510(const AsyncJobRef_6ae510& o) : mpJob(o.mpJob) { if (mpJob) mpJob->Add(); }
};
struct AsyncReqView_6ae510 : AsyncReqBase_6ae510, AsyncRefCount_6ae510 {
    AsyncJobRef_6ae510 mJob;                 // +0x0c
    AsyncReqView_6ae510(const AsyncJobRef_6ae510& job);
    virtual void v0();
};

// @ 0x006ae510
AsyncReqView_6ae510::AsyncReqView_6ae510(const AsyncJobRef_6ae510& job)
    : mJob(job)
{
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

// Node allocation of the resource-key map (0x006ae660): pop the pool's free list or allocate a node, then copy the
// value (three key words and a resource ref that is AddRef'd) into it.
struct ResRefObj_6ae660 { virtual void AddRef(); };
struct ResKeyValue_6ae660 {
    uint32_t mInstance, mType, mGroup;
    ResRefObj_6ae660* mpResource;
    ResKeyValue_6ae660(const ResKeyValue_6ae660& o)
        : mInstance(o.mInstance), mType(o.mType), mGroup(o.mGroup), mpResource(o.mpResource) {
        if (mpResource) mpResource->AddRef();
    }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct ResKeyNode_6ae660 { char mLinks[0x10]; ResKeyValue_6ae660 mValue; };
struct ResKeyPool_6ae660 {
    char pad[0x18];
    void* mpHead;                     // +0x18
    char pad1c[0xc];
    unsigned mnNodeSize;              // +0x28
    ResKeyNode_6ae660* AllocNode(const ResKeyValue_6ae660& value);
};
inline ResKeyNode_6ae660* ResKeyPoolTake_6ae660(ResKeyPool_6ae660* pool)
{
    ResKeyNode_6ae660* n = (ResKeyNode_6ae660*)pool->mpHead;
    if (n)
        pool->mpHead = *(void**)n;
    else
        n = (ResKeyNode_6ae660*)ea_eastl_alloc(pool->mnNodeSize, "EASTL", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    return n;
}

// @ 0x006ae660
ResKeyNode_6ae660* ResKeyPool_6ae660::AllocNode(const ResKeyValue_6ae660& value)
{
    ResKeyNode_6ae660* n = ResKeyPoolTake_6ae660(this);
    new (&n->mValue) ResKeyValue_6ae660(value);
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
AsyncNode** __fastcall FUN_006aec60(void* self, int, AsyncNode** out, AsyncNode* hint,
                                    AsyncKey* key, int flag)
{
    AsyncTree* tree = (AsyncTree*)self;
    AsyncNode* root = tree->mpRoot;
    if (hint == root || hint == (AsyncNode*)&tree->mpRoot) {
        if (tree->mCount != 0 &&
            KeyLess3(root->k0, root->k1, root->k2, key->k0, key->k1, key->k2)) {
            F_6ae700(tree, 0, out, root, key, 0);
            return out;
        }
        AsyncNode* it;
        F_6ae770(tree, 0, &it, key, (int)((unsigned)key & 0xFFFFFF00u));
        *out = it;
        return out;
    }
    AsyncNode* next = (AsyncNode*)F_921580(hint);
    if (KeyLess3(hint->k0, hint->k1, hint->k2, key->k0, key->k1, key->k2) &&
        KeyLess3(key->k0, key->k1, key->k2, next->k0, next->k1, next->k2)) {
        if (hint->pLeft != 0) {
            AsyncNode* n = (AsyncNode*)F_6ae660(tree, 0, key);
            F_9216a0(n, next, &tree->mpRoot, 0);
            tree->mCount = tree->mCount + 1;
            *out = n;
            return out;
        }
        F_6ae700(tree, 0, out, hint, key, 0);
        return out;
    }
    AsyncNode* it;
    F_6ae770(tree, 0, &it, key, (int)((unsigned)key & 0xFFFFFF00u));
    *out = it;
    return out;
}

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

// 006aee60  build the memory stream for a finished async request
// @ 0x006aee60
char __fastcall FUN_006aee60(void* self, int, void* job)
{
    void* local = 0;                                  // AutoRef<> the shared buffer object
    void* data  = *(void**)((char*)self + 0x10);
    void* obj   = *(void**)((char*)data + 8);         // AsyncData::mpObject
    obj = ((void*(__fastcall*)(void*, int))(*(void***)obj)[6])(obj, 0);   // object payload
    void* arg = ((void*(__fastcall*)(void*, int))(*(void***)obj)[7])(obj, 0);
    unsigned type = ((unsigned(__fastcall*)(void*, int))(*(void***)obj)[3])(obj, 0);
    if (type == 0x347223d2u)
        F_6ae2a0(&local, 0, *(void**)((char*)obj + 4));
    if (local == 0) {
        type = ((unsigned(__fastcall*)(void*, int))(*(void***)obj)[3])(obj, 0);
        if (type == 0x12e4a891u) {
            void* b = F_8dc5e0((char*)obj - 0x20, 0);
            F_6ae2a0(&local, 0, b);
        }
        if (local == 0) {
            if (((unsigned(__fastcall*)(void*, int))(*(void***)obj)[5])(obj, 0) == 0) {
                void* mem = F_926020(0x18, "App/AsyncRequest/SharedPointer", 0, 0, 0, 0);
                void* made = mem ? F_93bca0(mem, 0, arg, (void*)"App/AsyncRequest/SharedPointer") : 0;
                F_6ae2a0(&local, 0, made);
                if (arg != 0) {
                    void* p = *(void**)((char*)local + 0x10);
                    if (((void*(__fastcall*)(void*, int, void*, void*))
                             (*(void***)obj)[12])(obj, 0, p, arg) != arg)
                        F_6ae2a0(&local, 0, 0);
                }
            }
        }
    }
    if (local != 0) {
        void* mem2 = F_f473a0(0x24, "App/AsyncRequest/MemoryStream", 0, 0, 0, 0);
        void* s = mem2 ? F_93c270(mem2, 0, local, arg, "App/SimpleAsync/StreamToMemory") : 0;
        void* d = *(void**)((char*)self + 0x10);
        void* old = *(void**)((char*)d + 0x0c);       // AsyncData::mpStream
        if (s != old) {
            if (s)
                ((void(__fastcall*)(void*, int))(*(void***)s)[1])(s, 0);
            *(void**)((char*)d + 0x0c) = s;
            if (old)
                ((void(__fastcall*)(void*, int))(*(void***)old)[2])(old, 0);
        }
        void* stream = *(void**)((char*)self + 0x10);
        stream = *(void**)((char*)stream + 0x0c);
        F_93bb40(stream, 0, 1, 0.0f);
        stream = *(void**)((char*)self + 0x10);
        stream = *(void**)((char*)stream + 0x0c);
        F_93bb40(stream, 0, 4, 1.0f);
    }
    *(int*)((char*)job + 0x18) = 1;                   // cJob::mThreadAffinity
    char r = F_68f9f0(job, 0, (void*)&F_6aec50, self) ? 1 : 0;
    if (local) {
        volatile long* rc = (volatile long*)((char*)local + 8);
        long n = _InterlockedExchangeAdd(rc, -1);
        if (n == 1) {
            _InterlockedExchange(rc, 1);
            void* recv = (char*)local + 4;
            if (*(void**)recv)
                (*(void(__fastcall**)(void*, int))(*(void***)recv))(recv, 1);
        }
    }
    return r;
}

// 006af080  fixed_map find-or-emplace, returns pointer to the mapped value
// @ 0x006af080
void** __fastcall FUN_006af080(void* self, int, AsyncKey* key)
{
    AsyncNode* it;
    F_c7f560(self, 0, &it, key);
    AsyncNode* node = it;
    if (it == (AsyncNode*)((char*)self + 4) ||
        KeyLess3(key->k0, key->k1, key->k2, it->k0, it->k1, it->k2)) {
        AsyncValue kv;
        kv.key = *key;
        kv.obj = 0;
        FUN_006aec60(self, 0, &node, it, (AsyncKey*)&kv, (int)((unsigned)it & 0xFFFFFF00u));
    }
    return (void**)((char*)node + 0x1c);
}

// 006af150  cAsyncResourceManager::AllocateRequest
// @ 0x006af150
char __fastcall FUN_006af150(void* self, int, AsyncKey* key, void** out, void* ctorArg)
{
    Mutex2* mutex = (Mutex2*)((char*)self + 0x10);
    mutex->Lock((void*)0x1409448);
    void* obj = 0;
    void* mem = F_f473a0(0x10, "Resource/Async", 0, 0, 0, 0);
    if (mem) obj = F_6ae510(mem, 0, ctorArg);
    if (obj)
        ((void(__fastcall*)(void*, int))(*(void***)obj)[0])(obj, 0);      // AddRef
    void* temp = obj;
    void** slot = (void**)FUN_006af080((char*)self + 0x40, 0, key);
    void* old = *slot;
    if (obj != old) {
        if (obj)
            ((void(__fastcall*)(void*, int))(*(void***)obj)[0])(obj, 0);
        *slot = obj;
        if (old)
            ((void(__fastcall*)(void*, int))(*(void***)old)[1])(old, 0);
    }
    if (out) {
        temp = 0;
        *out = obj;
    }
    if (temp)
        ((void(__fastcall*)(void*, int))(*(void***)temp)[1])(temp, 0);
    mutex->Unlock();
    return 1;
}

// @ 0x006af260
void FUN_006af260()
{}
