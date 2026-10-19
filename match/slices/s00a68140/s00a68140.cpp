// Slice s00a68140 - EA::Audio::Eapd / Random helpers.
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
class RefObj {
public:
    virtual void ScalarDtor(int flag);   // +0x00
    int          mnRefCount;             // +0x04
};

// @ 0xa69150
class SizeHolder {
public:
    char pad[4];
    int  mnSize;                         // +0x04
    bool AddSize(int a, int b);
};
bool SizeHolder::AddSize(int a, int b)
{
    mnSize += b;
    return true;
}

// @ 0xa69180
class TableHolder {
public:
    char pad[0xc];
    int** mTable;                        // +0x0c
    int GetA(int a, int b);
};
int TableHolder::GetA(int a, int b)
{
    int* p = *(int**)((char*)mTable + b * 0x14);
    return p[a];
}

// @ 0xa691a0
class TableHolder2 {
public:
    char pad[0x20];
    int** mTable;                        // +0x20
    int GetB(int a, int b);
};
int TableHolder2::GetB(int a, int b)
{
    int* p = *(int**)((char*)mTable + b * 0x14);
    return p[a];
}

// ---------------------------------------------------------------------------
// EA::Random::RandomLinearCongruential
// ---------------------------------------------------------------------------
extern "C" {
    extern float g_2p328e10;   // 0x14558a8
    extern float g_0p5;        // 0x1471064
    extern float g_1p0;        // 0x1485720
}

class RandomLinearCongruential {
public:
    uint32_t mnSeed;                       // +0x00
    uint32_t RandomUint32Uniform(uint32_t range);  // @ 0xa68fb0
    float    RandomFloat();                        // @ 0xa68fe0
    float    RandomFloatSSE();                     // @ 0xa69020
};

uint32_t RandomLinearCongruential::RandomUint32Uniform(uint32_t range)
{
    uint64_t l = (uint64_t)mnSeed * 0x41c64e6dULL + 0x3039;
    mnSeed = (uint32_t)l;
    uint32_t u = (uint32_t)(l >> 16);
    return (uint32_t)(((uint64_t)u * range) >> 32);
}

float RandomLinearCongruential::RandomFloat()
{
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    int s = (int)mnSeed * 0x278dde6d;
    mnSeed = (uint32_t)s;
    float f = (float)s * g_2p328e10 + g_0p5;
    return (g_1p0 <= f) ? 0.0f : f;
}

float RandomLinearCongruential::RandomFloatSSE()
{
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    int s = (int)mnSeed * 0x278dde6d;
    float f = (float)s * g_2p328e10 + g_0p5;
    mnSeed = (uint32_t)s;
    if (g_1p0 <= f)
        return 0.0f;
    return f;
}

// @ 0xa69070  forward intrusive_ptr assignment
void AssignPtrs(RefObj** first, RefObj** last, RefObj** src)
{
    for (; first != last; ++first) {
        RefObj* p = *src;
        RefObj* q = *first;
        if (p != q) {
            if (p)
                p->mnRefCount++;
            *first = p;
            if (q) {
                int n = (*(volatile int*)&q->mnRefCount += -1);
                if (n == 0) {
                    q->mnRefCount = 1;
                    q->ScalarDtor(1);
                }
            }
        }
    }
}

// @ 0xa690d0  backward intrusive_ptr assignment
RefObj** AssignPtrsRev(RefObj** first, RefObj** last, RefObj** dst)
{
    if (last == first)
        return dst;
    do {
        RefObj* p = *--last;
        RefObj* q = *--dst;
        if (p != q) {
            if (p)
                p->mnRefCount++;
            *dst = p;
            if (q) {
                int n = (*(volatile int*)&q->mnRefCount += -1);
                if (n == 0) {
                    q->mnRefCount = 1;
                    q->ScalarDtor(1);
                }
            }
        }
    } while (last != first);
    return dst;
}


// ---------------------------------------------------------------------------
// Allocator interface used by the pools / lists (vtable slots 2 and 3)
// ---------------------------------------------------------------------------
class IAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);    // +0x08
    virtual void  Free(void* p);           // +0x0c
};

// ---- 0xa68140 / 0xa68190: info getters ------------------------------------
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

// @ 0xa68140
void EapdInfo::GetInfoA(int* out)
{
    out[0] = ((PolSub*)(pad + 0x154))->GetPoliticalID();
    out[1] = ((Sub240A*)(pad + 0x240))->Get();
    out[2] = *(int*)(pad + 0x2e8);
    ((Sub7cA*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// @ 0xa68190
void EapdInfo::GetInfoB(int* out)
{
    out[0] = ((FileSub*)(pad + 0x154))->GetFileCount();
    out[1] = ((Sub240B*)(pad + 0x240))->StartTime();
    out[2] = *(int*)(pad + 0x2ec);
    ((Sub7cB*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// ---- 0xa68280: intrusive list remove-by-key -------------------------------
struct LNode { LNode* next; LNode* prev; int key; };
class KeyList {
public:
    LNode* mNext;                          // +0x00
    LNode* mPrev;                          // +0x04
    IAlloc mAlloc;                         // +0x08
    void RemoveKey(const int* key);        // va 0xa68280
};
// @ 0xa68280
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

// ---- pool (0xa682d0 allocate, 0xa68330 free loop) -------------------------
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

// @ 0xa682d0
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

// @ 0xa687f0
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

// @ 0xa68330
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


// ---- 0xa681e0: singleton teardown -----------------------------------------
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

// @ 0xa681e0
bool DestroyEapdSystem()                   // @ 0xa681e0
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


// ---- 0xa685a0: task list push ---------------------------------------------
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
// @ 0xa685a0
void EapdTasks::PushTask(void* t)
{
    if (t)
        mTasks.PushBack(t);
}

// ---- 0xa685e0: asset manager init -----------------------------------------
struct Vec3F { float x, y; unsigned z; unsigned Fn(unsigned a); };       // Fn: 0x9213c0
class AssetMgr {
public:
    char pad[0x30];
    unsigned mCount;                       // +0x30
    bool Open(int a, int b, int c);        // 0x00a67d90 thiscall ret 0xc
};
extern "C" {
    extern float g_ten_k;                  // 0x13f0620
    extern float g_two;                    // 0x1470f1c
}
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
// @ 0xa685e0
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

// ---- hashtable<Symbol, pair<Symbol const, Group*>> helpers ----------------
struct GEntry {                            // object passed in: key at +0x2c
    char pad0[0x2c];
    unsigned mKey;                         // +0x2c
    unsigned mA;                           // +0x30
    unsigned mB;                           // +0x34
    char pad1[0x40 - 0x38];
    GEntry* mNext;                         // +0x40
};
struct GPair {                             // pair<Symbol const, Group*> at node+4
    unsigned mKey;
    GEntry*  mHead;
    bool RemoveEntry(GEntry* p);           // 0x00a64750 thiscall ret 4
    bool IsEmpty() const;                  // 0x00a647a0
    bool OpA(unsigned x);                  // 0x00a648f0 thiscall ret 4
    bool OpB();                            // 0x00a64950 thiscall
};
struct GNode { GNode* next; GPair value; };
struct GIter { GNode* node; GNode** bucket; };
struct GTable {
    unsigned pad0;
    GNode** mBuckets;                      // +0x04
    unsigned mBucketCount;                 // +0x08
    GIter find(const unsigned& key);       // 0x00685f30 thiscall sret ret 8
    GIter erase(GIter it);                 // 0x00a68430 thiscall sret ret 0xc
};
class GListener {
public:
    virtual void v0();
    virtual void OnA(unsigned a, unsigned b);                  // +4
    virtual void OnB(unsigned a, unsigned b, unsigned c);      // +8
    virtual void OnC(unsigned a);                              // +0xc
};
class GroupOwnerL {                        // listener at +0xc
public:
    unsigned   pad0;
    GTable*    mTable;                     // +0x04
    unsigned   pad8;
    GListener* mListener;                  // +0x0c
    bool Op1(unsigned a, unsigned b);      // va 0xa68670
    bool Op2(unsigned a);                  // va 0xa686e0
};
class GroupOwner {                         // listener at +0x08
public:
    unsigned   pad0;
    GTable*    mTable;                     // +0x04
    GListener* mListener;                  // +0x08
    bool RemoveGroupEntry(GEntry* p);      // va 0xa68740
};

// @ 0xa68670
bool GroupOwnerL::Op1(unsigned a, unsigned b)
{
    bool r = false;
    if (mListener)
        mListener->OnA(a, b);
    GTable* t = mTable;
    GIter it = t->find(a);
    if (t->mBuckets[t->mBucketCount] != it.node)
        r = it.node->value.OpA(b);
    return r;
}

// @ 0xa686e0
bool GroupOwnerL::Op2(unsigned a)
{
    bool r = false;
    if (mListener)
        mListener->OnC(a);
    GTable* t = mTable;
    GIter it = t->find(a);
    if (t->mBuckets[t->mBucketCount] != it.node)
        r = it.node->value.OpB();
    return r;
}

// @ 0xa68740
bool GroupOwner::RemoveGroupEntry(GEntry* p)
{
    GTable* t = mTable;
    unsigned key = p->mKey;
    GIter it = t->find(key);
    GNode* node = it.node;
    if (t->mBuckets[t->mBucketCount] == node)
        return false;
    bool r = node->value.RemoveEntry(p);
    if (node->value.IsEmpty()) {
        if (mListener)
            mListener->OnB(p->mB, key, p->mA);
        it = mTable->erase(it);
    }
    return r;
}


// ---- 0xa683b0: CallbackManager dtor ---------------------------------------
// The pool, the first list and the allocators have nothrow destructors (EASTL style); the second list's can throw.
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
// FixedAllocator<28> : FixedPool, IInternalAllocator (size 0x34; MSVC puts the polymorphic base first)
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
// @ 0xa683b0
CallbackManager::~CallbackManager()
{
}


// ---- 0xa68990: add an entry to its group (insert a new group when absent) -
struct Group {                             // value pair second: {key, head}, 8 bytes
    unsigned x;                            // +0x00
    GEntry*  head;                         // +0x04
    Group(GEntry* p);                      // 0x00a646f0 thiscall ret 4: x = p->0x34, head = p
    Group(const Group& g) : x(g.x), head(g.head) {}
    ~Group();                              // 0x00a64710
};
struct GroupPair {                         // pair<Symbol const, Group>
    unsigned key;
    Group    grp;
    GroupPair(unsigned k, const Group& g) : key(k), grp(g) {}
};
struct InsResult { GNode* node; GNode** bucket; bool ok; };
struct GTable2 {
    unsigned pad0;
    GNode** mBuckets;                      // +0x04
    unsigned mBucketCount;                 // +0x08
    GIter find(const unsigned& key);       // 0x00685f30
    InsResult insert(const GroupPair& v, bool force);   // 0x00a684e0 thiscall sret ret 0xc
};
struct GPair2 { bool Push(GEntry* p); };   // 0x00a64730 thiscall ret 4 (this = node+4)
struct GNode2 { GNode2* next; GPair2 value; };
struct GIter2 { GNode2* node; GNode2** bucket; };
struct GTable3 {
    unsigned pad0;
    GNode2** mBuckets;                     // +0x04
    unsigned mBucketCount;                 // +0x08
    GIter2 find(const unsigned& key);      // 0x00685f30
    InsResult insert(const GroupPair& v, bool force);   // 0x00a684e0
};
class GListener2 {
public:
    virtual void v0();
    virtual void OnAdd(unsigned a, unsigned b, unsigned c);    // +4
};
class GroupOwner2 {
public:
    unsigned   pad0;
    GTable3*   mTable;                     // +0x04
    GListener2* mListener;                 // +0x08
    bool AddEntry(GEntry* p);              // va 0xa68990
};
// @ 0xa68990
bool GroupOwner2::AddEntry(GEntry* p)
{
    unsigned key = p->mKey;
    GTable3* t = mTable;
    GIter2 it = t->find(key);
    if (t->mBuckets[t->mBucketCount] != it.node)
        return it.node->value.Push(p);
    {
        Group g(p);
        GroupPair v(key, g);
        t->insert(v, false);
    }
    if (mListener)
        mListener->OnAdd(p->mB, key, p->mA);
    return true;
}


// ---- 0xa68dd0: EA::Audio::Eapd::System::~System ---------------------------
// Members are external stubs (their destructors are separate functions in the original).
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
// @ 0xa68dd0
EapdSystemFull::~EapdSystemFull()
{
}

// ---- placeholders for the remaining functions -------------------------------
extern "C" int __cdecl Placeholder_68410() { return 0; }
extern "C" int __cdecl Placeholder_68430() { return 0; }
extern "C" int __cdecl Placeholder_68890() { return 0; }
extern "C" int __cdecl Placeholder_68aa0() { return 0; }
extern "C" int __cdecl Placeholder_68af0() { return 0; }
extern "C" int __cdecl Placeholder_68bf0() { return 0; }
extern "C" int __cdecl Placeholder_68c50() { return 0; }
extern "C" int __cdecl Placeholder_68cb0() { return 0; }
class EapdSystem {
public:
    void  Destroy();                       // 0xa68dd0
    void* ScalarDtor(int flag);            // @ 0xa68e80
};
void* EapdSystem::ScalarDtor(int flag)
{
    Destroy();
    return this;
}

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
void Outer310::RemoveEntry(int p)
{
    if (p)
        mList.Remove(&p);
}
extern "C" int __cdecl Placeholder_68e90() { return 0; }