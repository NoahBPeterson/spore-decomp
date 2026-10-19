// src/game/SPAudio/eapdsystem.cpp -- migrated from slice(s) s00a68140 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdsystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

// unnamed retail callees and globals (address in the comment)
extern "C" extern float g_ten_k;                  // 0x13f0620
extern "C" extern float g_two;                    // 0x1470f1c
#include <intrin.h>

// ---- items of slice s00a68140 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);    // +0x08
    virtual void  Free(void* p);           // +0x0c
};
class PolSub   { public: int GetPoliticalID(); };                     // 0x005aacf0
class Sub240A  { public: int Get(); };                                // 0x00a1ad10
class Sub7cA   { public: void Fill(int* a, int* b, int* c); };        // 0x00a66c60 ret 0xc
class FileSub  { public: int GetFileCount(); };                       // 0x008e7f80
class Sub240B  { public: int StartTime(); };                          // 0x006c10e0
class Sub7cB   { public: void Fill(int* a, int* b, int* c); };        // 0x00a66c90 ret 0xc
class EapdInfo {
public:
    char pad[0x300];
    void GetInfoA(int* out);               // va 0xa68140
    void GetInfoB(int* out);               // va 0xa68190
};
struct LNode { LNode* next; LNode* prev; int key; };
class KeyList {
public:
    LNode* mNext;                          // +0x00
    LNode* mPrev;                          // +0x04
    IAlloc mAlloc;                         // +0x08
    void RemoveKey(const int* key);        // va 0xa68280
};
struct PoolNode { PoolNode* next; int pad4; int pad8; PoolNode* chain; };
class SubObj { public: ~SubObj(); };       // 0x00a67d30
class NodePool {
public:
    unsigned pad0;
    PoolNode** mBuckets;                   // +0x04
    unsigned mBucketCount;                 // +0x08
    unsigned mElems;                       // +0x0c
    char padA[0x1c - 0x10];
    SubObj mSub;                           // +0x1c
    char padB[0x28 - 0x1d];
    IAlloc mAlloc;                         // +0x28
    char pad1[0x34 - 0x28 - sizeof(IAlloc)];
    unsigned mSize;                        // +0x34
    PoolNode* mBegin;                      // +0x38
    PoolNode* mEnd;                        // +0x3c
    PoolNode* mFree;                       // +0x40
    unsigned mCount;                       // +0x44
    unsigned mHigh;                        // +0x48
    char pad2[4];
    PoolNode* mSpecial;                    // +0x50
    void* Allocate(const int* src);        // va 0xa682d0
    void FreeChains(PoolNode** buckets, unsigned n);   // va 0xa68330
    ~NodePool();                           // va 0xa687f0
};
class Sub4 { public: void Destroy(); };    // 0x00a64710
class AllocRef : public IAlloc {
public:
    int mA, mB;
    AllocRef(int a, int b) : mA(a), mB(b) {}
    ~AllocRef() {}
};
class EapdSingleton {
public:
    virtual void* Dtor(int flag);          // slot 0
    int pad4;
    int mA;                                // +0x08
    int mB;                                // +0x0c
    unsigned char Shutdown();              // 0x00a678d0
};
extern "C" EapdSingleton* spEapdSystem;    // 0x16758d4
struct TaskNode { TaskNode* next; TaskNode* prev; void* value; };
class TaskList {
public:
    TaskNode* mNext;                       // +0x00
    TaskNode* mPrev;                       // +0x04
    IAlloc    mAlloc;                      // +0x08
    void PushBack(void* t)
    {
        TaskNode* n = (TaskNode*)mAlloc.Alloc(0xc);
        if (&n->value)
            n->value = t;
        n->next = (TaskNode*)this;
        n->prev = mPrev;
        mPrev->next = n;
        mPrev = n;
    }
};
class EapdTasks {
public:
    char pad[0x31c];
    TaskList mTasks;                       // +0x31c
    void PushTask(void* t);                // va 0xa685a0
};
struct Vec3F { float x, y; unsigned z; unsigned Fn(unsigned a); };       // Fn: 0x9213c0
class AssetMgr {
public:
    char pad[0x30];
    unsigned mCount;                       // +0x30
    bool Open(int a, int b, int c);        // 0x00a67d90 thiscall ret 0xc
};
extern "C" extern float g_ten_k;                  // 0x13f0620
extern "C" extern float g_two;                    // 0x1470f1c
class EapdAssets {
public:
    char pad0[8];
    unsigned m8;                           // +0x08
    unsigned mC;                           // +0x0c
    Vec3F    m10;                          // +0x10
    AssetMgr mAssets;                      // +0x1c
    void Grow(unsigned n);                 // 0x00a67f60 thiscall ret 4
    bool Init(int a, int b, int c);        // va 0xa685e0
};
class IntrusiveListBase  { public: ~IntrusiveListBase() throw(); };   // 0x00620230
class IntrusiveListBase2 { public: ~IntrusiveListBase2(); };          // 0x00620230
class FixedPoolT { public: char pad[0x30]; ~FixedPoolT() throw(); };  // 0x00a531b0
class IInternalAllocator {
public:
    virtual ~IInternalAllocator() throw() {}   // vtable 0x1403934
};
class AllocatorT : public IInternalAllocator {
public:
    int pad4, pad8;
};
class FixedAllocator : public FixedPoolT, public IInternalAllocator {
};
class CallbackManager {
public:
    AllocatorT         mAllocator;         // +0x00
    FixedAllocator     mFixedAllocator;    // +0x0c
    void*              mpCallbackPool;     // +0x40
    IntrusiveListBase  mCurrentCallbacks;  // +0x44
    char               padl[8 - 1];
    IntrusiveListBase2 mNextCallbacks;     // +0x4c
    ~CallbackManager();                    // va 0xa683b0
};
class AssetManagerExt    { public: char pad[0x60];  ~AssetManagerExt(); };      // 0x00a63d20
class SymbolManagerExt   { public: char pad[0xd8];  ~SymbolManagerExt(); };     // 0x00a68af0
class InstanceManagerExt { public: char pad[0xec];  ~InstanceManagerExt(); };   // 0x00a66670
class CallbackManagerExt { public: char pad[0x54];  ~CallbackManagerExt(); };   // 0x00a683b0
class FixedInputMapExt   { public: char pad[0x54];  ~FixedInputMapExt(); };     // 0x00a687f0
class TaskListExt        { public: char pad[0x14];  ~TaskListExt(); };          // 0x00a67e80
class InputManagerBaseS {
public:
    virtual ~InputManagerBaseS() {}        // vtable 0x1455648
    char pad4[0xc];
};
class FixedInputManagerS : public InputManagerBaseS {
public:
    FixedInputMapExt mFixedInputMap;       // +0x10
};
class ISystemS {
public:
    virtual ~ISystemS() {}                 // vtable 0x1455770
};
class AllocatorS : public IInternalAllocator {
public:
    int pad4, pad8;
};
class __declspec(novtable) EapdSystemFull : public ISystemS {
public:
    AllocatorS          mAllocator;        // +0x04
    AllocatorS          mOverflowAllocator;// +0x10
    AssetManagerExt     mAssetManager;     // +0x1c
    SymbolManagerExt    mSymbolManager;    // +0x7c
    InstanceManagerExt  mInstanceManager;  // +0x154
    CallbackManagerExt  mCallbackManager;  // +0x240
    FixedInputManagerS  mGlobalInputManager; // +0x294
    char                padm[0x31c - 0x2f8];
    TaskListExt         mTasks;            // +0x31c
    ~EapdSystemFull();                     // va 0xa68dd0
};
class EapdSystem {
public:
    void  Destroy();                       // 0xa68dd0
    void* ScalarDtor(int flag);            // @ 0xa68e80
};
class IntrusiveList {
public:
    void Remove(void* p);                  // 0xa68280
};
class Outer310 {
public:
    char pad[0x31c];
    IntrusiveList mList;                   // +0x31c
    void RemoveEntry(int p);               // @ 0xa68410
};
// ---- items of slice s00a68140 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" EapdSingleton* spEapdSystem;    // 0x16758d4

// @ 0x00a68140
void EapdInfo::GetInfoA(int* out)
{
    out[0] = ((PolSub*)(pad + 0x154))->GetPoliticalID();
    out[1] = ((Sub240A*)(pad + 0x240))->Get();
    out[2] = *(int*)(pad + 0x2e8);
    ((Sub7cA*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// @ 0x00a68190
void EapdInfo::GetInfoB(int* out)
{
    out[0] = ((FileSub*)(pad + 0x154))->GetFileCount();
    out[1] = ((Sub240B*)(pad + 0x240))->StartTime();
    out[2] = *(int*)(pad + 0x2ec);
    ((Sub7cB*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// @ 0x00a681e0
bool DestroyEapdSystem() // @ 0xa681e0
{
    if (spEapdSystem) {
        AllocRef a(spEapdSystem->mA, spEapdSystem->mB);
        bool r = spEapdSystem->Shutdown() & 1;
        EapdSingleton* s = spEapdSystem;
        s->Dtor(0);
        IAlloc& al = a;
        al.Free(s);
        spEapdSystem = 0;
        return r;
    }
    return false;
}

// @ 0x00a68280
void KeyList::RemoveKey(const int* key)
{
    LNode* n = mNext;
    while (n != (LNode*)this) {
        int k = n->key;
        n = n->next;
        if (k == *key) {
            LNode* x = n->prev;
            x->prev->next = x->next;
            x->next->prev = x->prev;
            mAlloc.Free(x);
        }
    }
}

// @ 0x00a682d0
void* NodePool::Allocate(const int* src)
{
    int* p = (int*)mFree;
    if (p)
        mFree = *(PoolNode**)p;
    else
        p = (int*)mAlloc.Alloc(mSize);
    if (p) {
        ++mCount;
        if (mCount > mHigh)
            mHigh = mCount;
        p[0] = src[0];
        p[1] = src[1];
        p[2] = src[2];
    }
    p[3] = 0;
    return p;
}

// @ 0x00a68330
void NodePool::FreeChains(PoolNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        PoolNode* node = buckets[i];
        while (node) {
            PoolNode* cur = node;
            node = node->chain;
            ((Sub4*)((char*)cur + 4))->Destroy();
            if (cur != mSpecial) {
                --mCount;
                if (cur < mBegin || cur >= mEnd) {
                    mAlloc.Free(cur);
                } else {
                    cur->next = mFree;
                    mFree = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0x00a683b0
CallbackManager::~CallbackManager()
{
}

// @ 0x00a68410
void Outer310::RemoveEntry(int p)
{
    if (p)
        mList.Remove(&p);
}

// @ 0x00a685a0
void EapdTasks::PushTask(void* t)
{
    if (t)
        mTasks.PushBack(t);
}

// @ 0x00a685e0
bool EapdAssets::Init(int a, int b, int c)
{
    AssetMgr* am = &mAssets;
    bool r = am->Open(a, b, c);
    if (r) {
        Grow(am->mCount - 1);
        Vec3F v;
        v.x = g_ten_k;
        v.y = g_two;
        v.z = 0;
        m10 = v;
        unsigned n = v.Fn(mC);
        if (n > m8)
            Grow(n);
    }
    return r;
}

// @ 0x00a687f0
NodePool::~NodePool()
{
    FreeChains(mBuckets, mBucketCount);
    unsigned n = mBucketCount;
    PoolNode* b = (PoolNode*)mBuckets;
    mElems = 0;
    if (n > 1 && b != mSpecial) {
        --mCount;
        if (b < mBegin || b >= mEnd) {
            mAlloc.Free(b);
        } else {
            b->next = mFree;
            mFree = b;
        }
    }
}

// @ 0x00a68dd0
EapdSystemFull::~EapdSystemFull()
{
}

// @ 0x00a68e80
void* EapdSystem::ScalarDtor(int flag)
{
    Destroy();
    return this;
}
