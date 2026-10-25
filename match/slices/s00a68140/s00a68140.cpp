// Slice s00a68140 - EA::Audio::Eapd / Random helpers.
#include "types.h"
#include <intrin.h>
#include <new>

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

// ---- hash node shared by the group table and the pool ----------------------
struct GEntry {                            // object passed in: key at +0x2c
    char pad0[0x2c];
    unsigned mKey;                         // +0x2c
    unsigned mA;                           // +0x30
    unsigned mB;                           // +0x34
    char pad1[0x40 - 0x38];
    GEntry* mNext;                         // +0x40
};
struct Group {                             // value pair second: {key, head}, 8 bytes
    unsigned x;                            // +0x00
    GEntry*  head;                         // +0x04
    Group(GEntry* p);                      // 0x00a646f0 thiscall ret 4: x = p->0x34, head = p
    Group(const Group& g) : x(g.x), head(g.head) {}
    ~Group();                              // 0x00a64710
    bool RemoveEntry(GEntry* p);           // 0x00a64750 thiscall ret 4
    bool IsEmpty() const;                  // 0x00a647a0
    bool OpA(unsigned x);                  // 0x00a648f0 thiscall ret 4
    bool OpB();                            // 0x00a64950 thiscall
    bool Push(GEntry* p);                  // 0x00a64730 thiscall ret 4
};
struct HNode { HNode* next; Group value; HNode* chain; };
struct HIter { HNode* node; HNode** bucket; };

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
struct GTable {
    unsigned pad0;
    HNode** mBuckets;                      // +0x04
    unsigned mBucketCount;                 // +0x08
    unsigned mElems;                       // +0x0c
    char padE[0x1c - 0x10];
    SubObj mSub;                           // +0x1c
    char padA[0x28 - 0x1d];
    IAlloc mAlloc;                         // +0x28
    char pad1[0x38 - 0x28 - 4];
    HNode* mBegin;                         // +0x38
    HNode* mEnd;                           // +0x3c
    HNode* mFree;                          // +0x40
    unsigned mCount;                       // +0x44
    unsigned mHigh;                        // +0x48
    char pad2[0x50 - 0x4c];
    HNode* mSpecial;                       // +0x50
    HIter find(const unsigned& key);       // 0x00685f30 thiscall sret ret 8
    HIter erase(HIter it);                 // va 0xa68430 thiscall sret ret 0xc
};

// @ 0xa68430
HIter GTable::erase(HIter it)
{
    HIter r;
    r.node = it.node->chain;
    r.bucket = it.bucket;
    while (!r.node) {
        ++r.bucket;
        r.node = *r.bucket;
    }
    HNode* node = it.node;
    HNode* p = *it.bucket;
    if (p == node) {
        *it.bucket = p->chain;
    } else {
        HNode* q = p->chain;
        while (q != node) {
            p = q;
            q = q->chain;
        }
        p->chain = q->chain;
    }
    node->value.~Group();
    int delta = -1;
    if (node != mSpecial) {
        mCount += delta;
        if (node >= mBegin && node < mEnd) {
            node->next = mFree;
            mFree = node;
            mElems += delta;
            return r;
        }
        mAlloc.Free(node);
    }
    mElems += delta;
    return r;
}
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
    HIter it = t->find(a);
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
    HIter it = t->find(a);
    if (t->mBuckets[t->mBucketCount] != it.node)
        r = it.node->value.OpB();
    return r;
}

// @ 0xa68740
bool GroupOwner::RemoveGroupEntry(GEntry* p)
{
    GTable* t = mTable;
    unsigned key = p->mKey;
    HIter it = t->find(key);
    HNode* node = it.node;
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
struct GroupPair {                         // pair<Symbol const, Group>
    unsigned key;
    Group    grp;
    GroupPair(unsigned k, const Group& g) : key(k), grp(g) {}
};
struct GPair2 { bool Push(GEntry* p); };   // 0x00a64730 thiscall ret 4 (this = node+4)
struct GNode2 { GNode2* next; GPair2 value; };
struct GIter2 { GNode2* node; GNode2** bucket; };
struct InsResult { GNode2* node; GNode2** bucket; bool ok; };
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
// Members are external stubs (their constructors/destructors are separate functions in the original).
extern "C" {
    extern char g_vtbl_1403934[];          // 0x01403934
    extern char g_vtbl_1454fac[];          // 0x01454fac
    extern char g_vtbl_14557f8[];          // 0x014557f8
    extern char g_vtbl_1455808[];          // 0x01455808
    extern char g_vtbl_145581c[];          // 0x0145581c
    extern char g_vtbl_1455828[];          // 0x01455828
    extern char g_vtbl_14557d8[];          // 0x014557d8
    extern char g_vtbl_1455890[];          // 0x01455890  "EAPd/CreateSingleton"
    extern char g_vtbl_1455688[];          // 0x01455688  "EAPd/InputManager"
    extern float g_0p05;                   // 0x01455768
}

// A pair of allocator wrapper sub-objects at +0x04 and +0x10 of the system. Each one is
// { vtable, raw allocator, debug name }; only the primary vtable pointer is reset by the destructor.
class AllocA {
public:
    AllocA(int d) : mpVtbl(g_vtbl_1454fac), mData(d), mpName(g_vtbl_145581c) {}
    ~AllocA() { mpVtbl = g_vtbl_1403934; }
    void*       mpVtbl;                    // +0x00
    int         mData;                     // +0x04
    const char* mpName;                    // +0x08
};
class AllocB {
public:
    AllocB() : mpVtbl(g_vtbl_1454fac), mData(0), mpName(g_vtbl_1455808) {}
    ~AllocB() { mpVtbl = g_vtbl_1403934; }
    void*       mpVtbl;                    // +0x00
    int         mData;                     // +0x04
    const char* mpName;                    // +0x08
};

class AssetManagerExt {
public:
    AssetManagerExt(AllocA&);              // 0x00a63c90 thiscall ret 4
    ~AssetManagerExt();                    // 0x00a63d20
    virtual void v0();
    virtual bool OnX(unsigned char v);     // +4
    virtual void v2();
    void Setup(int v);                     // 0x00a63490 ret 4
    char pad[0x5c];
};
class SymMgrSub {
public:
    char pad[0x54];
    ~SymMgrSub();                          // 0x00a672e0
};
class SymMgrBase {
public:
    virtual ~SymMgrBase();                 // 0x00a66830
};
class SymbolManagerExt : public SymMgrBase {
public:
    SymbolManagerExt();                    // 0x00a67810
    bool Init(int a, int b, int c, AllocA& alloc, AllocB& overflow, int d);  // 0x00a67670 ret 0x18
    char    padBase[0x2c - 4];
    SymMgrSub m2c;                         // +0x2c
    SymMgrSub m80;                         // +0x80
    char    padEnd[4];                     // up to 0xd8
};
class InstanceManagerExt {
public:
    InstanceManagerExt(AllocA&, AssetManagerExt&);   // 0x00a66780 thiscall ret 8
    ~InstanceManagerExt();                 // 0x00a66670
    bool Init(int a, AllocA& alloc, AllocB& overflow);   // 0x00a65f90 ret 0xc
    char pad[0xec];
};
class CallbackManagerExt {
public:
    CallbackManagerExt();                  // 0x00a64470
    ~CallbackManagerExt();                 // 0x00a683b0
    bool Init(int a, AllocA& alloc, AllocB& overflow);   // 0x00a64390 ret 0xc
    char pad[0x54];
};
class FixedInputMapExt : public EapdAssets {
public:
    FixedInputMapExt(const char*);         // 0x00a68b50
    ~FixedInputMapExt();                   // 0x00a687f0
};
class TaskListExt {
public:
    TaskListExt(int arg)
        : mNext(this), mPrev(this), mpVtbl(g_vtbl_1454fac), mArg(arg), mpVtbl2(g_vtbl_14557f8) {}
    ~TaskListExt();                        // 0x00a67e80
    TaskListExt* mNext;                    // +0x00
    TaskListExt* mPrev;                    // +0x04
    void*        mpVtbl;                   // +0x08
    int          mArg;                     // +0x0c
    void*        mpVtbl2;                  // +0x10
};
class InputManagerBaseS {
public:
    InputManagerBaseS(void* pSub) : mpSub(pSub), m8(0), mC(0) {}
    virtual ~InputManagerBaseS() {}        // vtable 0x1455648
    virtual void OnAdd(void*);             // +4
    virtual void OnRemove(void*);          // +8
    void* mpSub;                           // +0x04
    int   m8;                              // +0x08
    int   mC;                              // +0x0c
};
class FixedInputManagerS : public InputManagerBaseS {
public:
    FixedInputManagerS();
    FixedInputMapExt mFixedInputMap;       // +0x10
};
// @ 0xa68bf0
FixedInputManagerS::FixedInputManagerS()
    : InputManagerBaseS((char*)this + 0x10),
      mFixedInputMap("EAPd/InputManager")
{
}
// @ 0xa68aa0 removed: the compiler's implicit definition is byte-exact (manifest row added manually)

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
    char                padm[0x2f8 - 0x2f4];
    int                 m2f8;              // +0x2f8
    char                padm2[0x300 - 0x2fc];
    double              m300;              // +0x300
    double              m308;              // +0x308
    float               m310;              // +0x310
    float               m314;              // +0x314
    float               m318;              // +0x318
    TaskListExt         mTasks;            // +0x31c
    ~EapdSystemFull();                     // va 0xa68dd0
};
// @ 0xa68dd0
EapdSystemFull::~EapdSystemFull()
{
}

// ---- 0xa68cb0 / 0xa68890 / 0xa68e90: system implementation and singleton --
struct EapdInitArgs {
    int m00;                               // +0x00
    int m04;                               // +0x04
    int m08;                               // +0x08
    int m0c;                               // +0x0c
    int m10;                               // +0x10
    int m14;                               // +0x14
    unsigned char m18;                     // +0x18
    char pad19[3];
    int m1c;                               // +0x1c
    unsigned char m20;                     // +0x20
    char pad21[3];
    int m24;                               // +0x24
    int m28;                               // +0x28
    int m2c;                               // +0x2c
    int m30;                               // +0x30
    int m34;                               // +0x34
    int m38;                               // +0x38
    int m3c;                               // +0x3c
};

// The allocator adapter is { vtable, raw allocator, debug name }: Alloc forwards to the raw
// allocator through interface slot 1, Free releases through interface slot 3.
class AllocRefC {
public:
    AllocRefC(void* raw, const char* name)
        : mpVtbl(g_vtbl_1454fac), mpRaw(raw), mpName(name) {}
    void* Alloc(unsigned size)
    {
        return ((void* (__thiscall*)(void*, unsigned))(*(void***)&mpVtbl)[2])(&mpVtbl, size);
    }
    void Free(void* p)
    {
        ((void (__thiscall*)(void*, void*))(*(void***)&mpVtbl)[3])(&mpVtbl, p);
    }
    void*       mpVtbl;                    // +0x00
    void*       mpRaw;                     // +0x04
    const char* mpName;                    // +0x08
};

class EapdSystemImpl {
public:
    EapdSystemImpl(AllocA& alloc, int arg);         // va 0xa68cb0 thiscall ret 8
    bool Init(EapdInitArgs* a);                     // va 0xa68890 thiscall ret 4
    void*               mpVtbl;            // +0x000
    AllocA              mAllocator;        // +0x004
    AllocB              mOverflowAllocator;// +0x010
    AssetManagerExt     mAssetManager;     // +0x01c
    SymbolManagerExt    mSymbolManager;    // +0x07c
    InstanceManagerExt  mInstanceManager;  // +0x154
    CallbackManagerExt  mCallbackManager;  // +0x240
    FixedInputManagerS  mGlobalInputManager; // +0x294
    char                padm[0x2f8 - 0x2f4];
    int                 m2f8;              // +0x2f8
    char                padm2[0x300 - 0x2fc];
    double              m300;              // +0x300
    double              m308;              // +0x308
    float               m310;              // +0x310
    float               m314;              // +0x314
    float               m318;              // +0x318
    TaskListExt         mTasks;            // +0x31c
};

extern "C" {
    void FUN_00a646e0(int p);              // cdecl, one argument
    bool FUN_00a495e0();                   // cdecl, no arguments
    void FUN_00a53300(int p);              // cdecl, one argument
}

// @ 0xa68cb0
EapdSystemImpl::EapdSystemImpl(AllocA& alloc, int arg)
    : mpVtbl(g_vtbl_1455828),
      mAllocator(alloc.mData),
      mOverflowAllocator(),
      mAssetManager(mAllocator),
      mSymbolManager(),
      mInstanceManager(mAllocator, mAssetManager),
      mCallbackManager(),
      mGlobalInputManager(),
      m2f8(arg),
      m300(0.0),
      m308(0.0),
      m310(0.0f),
      m314(0.0f),
      m318(g_0p05),
      mTasks(mAllocator.mData)
{
}

// @ 0xa68890
bool EapdSystemImpl::Init(EapdInitArgs* a)
{
    if (a->m34)
        FUN_00a646e0(a->m34);
    mOverflowAllocator.mData = a->m1c;
    bool ok = mSymbolManager.Init(a->m0c, a->m10, a->m14, mAllocator, mOverflowAllocator, a->m30);
    ok &= mCallbackManager.Init(a->m04, mAllocator, mOverflowAllocator);
    ok &= mGlobalInputManager.mFixedInputMap.Init(a->m08, (int)&mAllocator, (int)&mOverflowAllocator);
    ok &= mAssetManager.OnX(a->m20);
    ok &= mInstanceManager.Init(a->m00, mAllocator, mOverflowAllocator);
    ok &= FUN_00a495e0();
    if (ok) {
        FUN_00a53300(a->m24);
        if (a->m2c)
            mAssetManager.Setup(a->m2c);
        if (a->m38)
            mGlobalInputManager.OnAdd((void*)a->m38);
        if (a->m3c)
            mGlobalInputManager.OnRemove((void*)a->m3c);
    }
    return ok;
}

// @ 0xa68e90
extern "C" bool __cdecl CreateEapdSystem(void* pRaw, EapdInitArgs args)
{
    if (spEapdSystem)
        return false;
    if (!pRaw)
        return false;
    if (args.m18 && !args.m1c)
        args.m1c = (int)pRaw;
    AllocRefC local(pRaw, "EAPd/CreateSingleton");
    if (!args.m28)
        return false;
    void* mem = local.Alloc(0x330);
    EapdSystemImpl* sys = mem ? new (mem) EapdSystemImpl((AllocA&)local, args.m28) : 0;
    spEapdSystem = (EapdSingleton*)sys;
    bool ok = false;
    if (sys && sys->Init(&args))
        ok = true;
    if (!ok) {
        if (spEapdSystem) {
            spEapdSystem->Shutdown();
            EapdSingleton* s = spEapdSystem;
            s->Dtor(0);
            local.Free(s);
            spEapdSystem = 0;
        }
    }
    return ok;
}

// ---- 0xa681e0 forward (declared early, defined above) -----------------------

// ---- 0xa68e80 / 0xa68410: small wrappers -----------------------------------
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