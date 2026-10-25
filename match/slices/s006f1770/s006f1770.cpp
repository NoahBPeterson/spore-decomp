// Slice s006f1770 — SP::cEffectsRenderer particle-set / hash-table helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>

extern "C" void FUN_00a7bca0(int, int);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EAAllocate(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
void* ZoneObjectNew(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00926020
bool FUN_006ac0a0(unsigned int flags, void* holder); // 0x006ac0a0

extern "C" void* FUN_0067dcd0();   // 0x0067dcd0 GetManager
extern "C" void* FUN_0067dd60();   // 0x0067dd60
extern "C" void* FUN_0067dd70();   // 0x0067dd70 SP::MaterialManager
extern "C" void* FUN_0067ddf0();   // 0x0067ddf0

extern unsigned gTypeTable[];      // 0x0140b568
extern unsigned gKeyHigh;          // 0x01533f68

#pragma intrinsic(_InterlockedDecrement, _InterlockedExchange, _InterlockedIncrement, _InterlockedExchangeAdd)

static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct IVt {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

// A richer interface used via raw vtable slot indices.
struct IVt2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool s9(unsigned key);
};

// An object with >= 11 virtual slots (used via raw indices).
struct IVt3 {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3();
    virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7();
    virtual void t8(); virtual void t9();
    virtual void* slot10(unsigned key);
};

// Objects whose first virtual slot is AddRef (no arguments).
struct RefObj0 {
    virtual void AddRef();
    long mRefCount;                    // +0x04
};

// Objects whose first virtual slot destroys them with a flag.
struct RefObjA {
    virtual void Destroy(int flags);
    long mRefCount;                    // +0x04
};

// The resource sub-object handed out by the renderer lookup.
struct ResSub {
    virtual void s0();                 // AddRef
    virtual void s1();                 // Release
    virtual void s2();                 // AddRef (lookup result)
    virtual void s3();                 // Release (cleared from the list)
};

// Base of a looked-up resource: slot +0x04 releases it.
struct ResBase {
    virtual void b0();
    virtual void b1();                 // +0x04 : Release
    char     pad08[0x18 - 0x04];
    ResSub   mSub;                     // +0x18
};

// A resource reference returned by the resource-manager lookups.
struct ResRef {
    virtual void q0();
    virtual void q1();                 // Release
};

// Scoped holders matching the reference-counted temporaries in the original.
struct ResGuard {
    ResBase* mpRes;
    ResGuard() : mpRes(0) {}
    ~ResGuard() { if (mpRes) mpRes->b1(); }
    ResBase* get() const { return mpRes; }
    ResBase** addr() { return &mpRes; }
};
struct RefGuard {
    ResRef* mpRef;
    RefGuard() : mpRef(0) {}
    ~RefGuard() { if (mpRef) mpRef->q1(); }
    ResRef* get() const { return mpRef; }
    ResRef** addr() { return &mpRef; }
    void reset()
    {
        ResRef* p = mpRef;
        if (p)
        {
            mpRef = 0;
            p->q1();
        }
    }
};

// The "Swarm" object allocated by ResourceInfoInit.
struct SwarmObj {
    virtual void w0();
    virtual void AddRef();
    virtual void Release();
    SwarmObj* Init();                  // 0x00a7bb80
};
struct SwarmGuard {
    SwarmObj* mpObj;
    SwarmGuard(SwarmObj* p) : mpObj(p) { if (p) p->AddRef(); }
    ~SwarmGuard() { if (mpObj) mpObj->Release(); }
    SwarmObj* get() const { return mpObj; }
};

// Resource-manager interface, slots named by offset.
struct ResKey3 { unsigned instance, type, group; };
struct ResMgr {
    virtual void r00();
    virtual void r01();
    virtual void r02();
    virtual bool Lookup(ResKey3* key, ResBase** out, int a, int b, int c, int d);      // +0x0c
    virtual bool Lookup2(ResKey3* key, ResRef** out1, ResRef** out2,
                         int a, int b, int c, int d, int e);                             // +0x10
    virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08();
    virtual void r09(); virtual void r10(); virtual void r11(); virtual void r12();
    virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16();
    virtual void AddSwarm(int flags, SwarmObj* p, int extra);                            // +0x44
    virtual int  GetSwarmType(unsigned id, int arg);                                     // +0x48
};

// Material / model helper vtables used for the fallback lookups.
struct MaterialVt {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9();
    virtual void* LookupDesc(unsigned key);                                              // +0x28
};
struct KeyedVt {
    virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3();
    virtual void k4(); virtual void k5(); virtual void k6(); virtual void k7();
    virtual void k8();
    virtual bool Contains(unsigned key);                                                 // +0x24
};

// An allocation made by Alloc18: two words, a reference and a link.
struct Node18 {
    unsigned m0;                       // +0x00
    unsigned m4;                       // +0x04
    RefObj0* mpRef;                    // +0x08
    unsigned mPad0c;                   // +0x0c
    Node18* mpNext;                    // +0x10
    unsigned mPad14;                   // +0x14
    Node18(const Node18& src);
};

// An allocation made by Alloc10.
struct Node10 {
    unsigned m0;                       // +0x00
    unsigned m4;                       // +0x04
    RefObj0* mpRef;                    // +0x08
    Node10* mpNext;                    // +0x0c
    Node10(const Node10& src);
};

// ---- eastl hashtables ------------------------------------------------------
// The value stored in the four-byte-key table; destroying it releases mRef.
struct HtValue {
    unsigned  mKey;                    // +0x00
    void*     mValue;                  // +0x04
    RefObjA*  mpRef;                   // +0x08
    ~HtValue();
};

// Four-byte-key table (find at 0x00685f30, insert at 0x006f21b0).
struct HtNode  { unsigned mKey; void* mValue; void* mRef; HtNode* mpNext; };
struct HtIter  { HtNode* node; HtNode** bucket; };
struct HInsertResult { HtNode* node; HtNode** bucket; bool inserted; char pad[3]; };
struct HtTable {
    unsigned   mHash;                  // +0x00
    HtNode**   mBuckets;               // +0x04
    unsigned   mBucketCount;           // +0x08
    unsigned   mElementCount;          // +0x0c
    HtIter find(const unsigned& key);                                   // 0x00685f30
    HInsertResult insert(const HtValue& value, bool flag);              // 0x006f21b0
    void FreeBuckets(unsigned buckets, unsigned count);
    __declspec(noinline) unsigned* FindOrInsert2(const unsigned* key);
};

// Eight-byte-key table at renderer+0xa8 (find at 0x00a7bf40, insert at 0x006f1e50).
struct Key8 { unsigned lo, hi; };
union Key8Bits { unsigned long long q; Key8 k; };
struct HtValueB {
    Key8      mKey;                    // +0x00
    ResSub*   mpRef;                   // +0x08
    ~HtValueB();
};
struct HtNodeB { unsigned mKeyLo, mKeyHi; void* mValue; unsigned mPad0c; HtNodeB* mpNext; };
struct HtIterB { HtNodeB* node; HtNodeB** bucket; };
struct HInsertResultB { HtNodeB* node; HtNodeB** bucket; bool inserted; char pad[3]; };
struct HtTableB {
    unsigned   mHash;                  // +0x00
    HtNodeB**  mBuckets;               // +0x04
    unsigned   mBucketCount;           // +0x08
    unsigned   mElementCount;          // +0x0c
    char       mPolicy[0x10];          // +0x10
    HtIterB findA(const Key8& key);                                     // 0x00a7bf40
    HInsertResultB insertA(const HtValueB& value, bool flag);           // 0x006f1e50
    __declspec(noinline) ResSub** FindOrInsert(const Key8* key);
};

inline HtValue::~HtValue()
{
    RefObjA* p = mpRef;
    if (p)
    {
        if (_InterlockedDecrement(&p->mRefCount) == 0)
        {
            _InterlockedExchange(&p->mRefCount, 1);
            if (p) p->Destroy(1);
        }
    }
}

inline HtValueB::~HtValueB()
{
    if (mpRef)
        mpRef->s1();
}

Node18::Node18(const Node18& src)
{
    m0 = src.m0;
    m4 = src.m4;
    mpRef = src.mpRef;
    if (mpRef)
        mpRef->AddRef();
}

Node10::Node10(const Node10& src)
{
    m0 = src.m0;
    m4 = src.m4;
    mpRef = src.mpRef;
    if (mpRef)
        _InterlockedIncrement(&mpRef->mRefCount);
}

// A vertex-descriptor stream entry and its owning descriptor.
struct VdStream { int type; int a; int b; };
struct VtxDesc  { char pad[0xc]; unsigned short count; char pad2[0x20 - 0xe]; VdStream streams[1]; };
struct VdState  { VtxDesc* GetVertexDescriptor(); };   // 0x011edcd0 thiscall (ecx = state)

// ---- particle-set storage (slice 006f1770) ---------------------------------
// Each particle-set entry is 0xC0 bytes; entries 4..8 hold a wide-string view.
struct StrSlot {
    wchar_t* mpBegin;                  // +0x00
    wchar_t* mpEnd;                    // +0x04
    wchar_t* mpCap;                    // +0x08
    void assign(const wchar_t* begin, const wchar_t* end);   // 0x006ebd20
};
struct PSetElem {
    int      f00;                      // +0x00
    StrSlot  mStr;                     // +0x04
    char     pad0c[0xa0 - 0x10];
    int      ma0;                      // +0xa0
    int      ma4;                      // +0xa4
    float    ma8;                      // +0xa8
    char     padac[0xc0 - 0xac];
};
struct PSetVec {                       // +0x224
    PSetElem* begin; PSetElem* end; PSetElem* cap;
    void PushBack();                   // 0x006f16c0 thiscall
};
struct IndexVec {                      // +0x238
    int* begin; int* end; int* cap;
};

static __forceinline int WStrLen(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p) ++p;
    return (int)(p - s);
}

struct PSetOwner {
    char     pad0[0x224];
    PSetVec  mVec;                     // +0x224
    char     pad22c[0x238 - 0x230];
    IndexVec mFree;                    // +0x238
    __declspec(noinline) bool AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out); // 0x006f1770
};

// A vector of four-byte entries with an out-of-line slow insert path.
struct PtrVec {
    ResSub** begin; ResSub** end; ResSub** cap;      // +0x00/+0x04/+0x08
    void DoInsertValue(ResSub** pos, ResSub* const& v);   // 0x006ec4a0
    void push_back(ResSub* v) { if (end < cap) *end++ = v; else DoInsertValue(end, v); }
    void erase(ResSub** first, ResSub** last)
    {
        memcpy(first, last, (char*)end - (char*)last);
        end = end - (last - first);
    }
    void clear() { erase(begin, end); }
};
struct IntVec {
    int* begin; int* end; int* cap;
    void erase(int* first, int* last)
    {
        memcpy(first, last, (char*)end - (char*)last);
        end = end - (last - first);
    }
    void clear() { erase(begin, end); }
};

// The model object held at renderer+0x5c.
struct BigVt {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7();
};
struct SubVt {
    virtual void u0(); virtual void u1();
};
struct Model5c {
    virtual void c0();
    virtual void c1();
    char     pad8[0x5c - 0x04];
    void*    mp5c;                     // +0x5c
    void*    mp60;                     // +0x60
    void*    mp64;                     // +0x64
    void*    mp68;                     // +0x68
    BigVt*   mp6c;                     // +0x6c
};

// Model created by CreateResource.
struct Model98 {
    virtual void n0();
    Model98* Init();                   // 0x006ebf50
    void UpdateFromResource(void* res); // 0x006edbc0
    void LoadFrom(void* res);          // 0x006e7410
};

// The renderer that owns all of the tables.
struct EffectsRenderer {
    char        pad0[0x0c];
    KeyedVt*    mpKeyed;               // +0x0c
    char        pad10[0x3c - 0x10];
    HtTable     mTable3c;              // +0x3c
    char        pad4c[0x50 - 0x4c];
    ResMgr*     mpManager;             // +0x50
    void*       mpField54;             // +0x54
    MaterialVt* mpMaterial;            // +0x58
    Model5c*    mpModel;               // +0x5c
    PtrVec      mObjVec;               // +0x60
    char        pad6c[0x74 - 0x6c];
    IntVec      mFreeVec;              // +0x74
    char        pad80[0x88 - 0x80];
    HtTable     mTable88;              // +0x88

    __declspec(noinline) bool ResourceInfoInit();                      // 0x006f1860
    __declspec(noinline) bool LookupAndUse(unsigned a, unsigned b, ResSub** out, unsigned index); // 0x006f1b60
    __declspec(noinline) bool CreateResource(unsigned a, unsigned b, Model98** out); // 0x006f1c40
    __declspec(noinline) int  ClassifyVertexDesc(unsigned key, unsigned unused, unsigned a); // 0x006f1f20
    __declspec(noinline) int  ContainsKey(unsigned key);               // 0x006f2000
    __declspec(noinline) void* FindEntry(unsigned key, unsigned unused); // 0x006f2050
    __declspec(noinline) bool InsertEntry(unsigned index, unsigned b, unsigned c, int* out); // 0x006f2310
    __declspec(noinline) bool ClearAll();                              // 0x006f2620
};

__declspec(noinline) void __stdcall Forward1840(int a, int b);
// ---- 0x006f1840 -------------------------------------------------------------
// @ 0x006f1840
void __stdcall Forward1840(int a, int b)
{
    FUN_00a7bca0(a, b);
}

// ---- 0x006f1950 -------------------------------------------------------------
struct VtStub1950 {
    virtual void v0();
    virtual int  v1(int, int, int);
};
struct Owner1950 {
    char pad0[0x60];
    VtStub1950** mArray;   // +0x60
    __declspec(noinline) int Call(int idx, int a, int b, int c);
};
// @ 0x006f1950
int Owner1950::Call(int idx, int a, int b, int c)
{
    mArray[idx]->v1(a, b, c);
    return 1;
}
// ---- 0x006f1770 -------------------------------------------------------------
// @ 0x006f1770
bool PSetOwner::AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out)
{
    int* begin = mFree.begin;
    if (mFree.end != begin)
    {
        *out = (unsigned)mFree.end[-1];
        mFree.end -= 1;
    }
    else
    {
        *out = (unsigned)(mVec.end - mVec.begin);
        mVec.PushBack();
    }
    PSetElem* e = &mVec.begin[*out];
    StrSlot* s = &e->mStr;
    if (s->mpBegin != name)
    {
        if (s->mpBegin != s->mpEnd)
        {
            s->mpBegin[0] = 0;
            s->mpEnd = s->mpBegin;
        }
        s->assign(name, name + WStrLen(name));
    }
    e->ma0 = b;
    e->ma4 = c;
    e->ma8 = d;
    return true;
}

// ---- 0x006f1860 -------------------------------------------------------------
// @ 0x006f1860
bool EffectsRenderer::ResourceInfoInit()
{
    mpManager = (ResMgr*)FUN_0067dcd0();
    mpField54 = FUN_0067dd60();
    mpMaterial = (MaterialVt*)FUN_0067dd70();
    if (!mpManager)
        return true;
    if (mpManager->GetSwarmType(0xea5118b0, -1))
        return true;

    SwarmObj* raw = (SwarmObj*)ZoneObjectNew(8, "Swarm", 0, 0, 0, 0);
    SwarmObj* p = raw ? raw->Init() : 0;
    SwarmGuard guard(p);
    mpManager->AddSwarm(1, guard.get(), 0);
    return true;
}

__declspec(noinline) Node18* __stdcall Alloc18(Node18* src);
// ---- 0x006f1a30 -------------------------------------------------------------
// @ 0x006f1a30
Node18* __stdcall Alloc18(Node18* src)
{
    Node18* p = (Node18*)EAAllocate(0x18, "Graphics", 0, 0, kAllocatorFile, 0xd1);
    Node18* q = p;
    if (q)
        new (q) Node18(*src);
    p->mpNext = 0;
    return p;
}

// ---- 0x006f1b60 -------------------------------------------------------------
// @ 0x006f1b60
bool EffectsRenderer::LookupAndUse(unsigned a, unsigned b, ResSub** out, unsigned index)
{
    ResKey3 key;
    key.instance = a;
    key.type = gTypeTable[index];
    key.group = b;

    ResGuard res;
    if (!mpManager->Lookup(&key, res.addr(), 0, 0, 0, 0))
        return false;
    *out = res.get() ? &res.get()->mSub : 0;
    (*out)->s2();
    return true;
}

// ---- 0x006f1c40 -------------------------------------------------------------
// @ 0x006f1c40
bool EffectsRenderer::CreateResource(unsigned a, unsigned b, Model98** out)
{
    ResKey3 key;
    key.instance = a;
    key.type = 0xe6bce5;
    key.group = b;

    RefGuard refA;
    RefGuard refB;
    if (!mpManager->Lookup2(&key, refB.addr(), refA.addr(), 0, 0, 0, 0, 0))
    {
        key.type = 0x2f4e681b;
        refA.reset();
        refB.reset();
        if (!mpManager->Lookup2(&key, refB.addr(), refA.addr(), 0, 0, 0, 0, 0))
            return false;
    }

    Model98* raw = (Model98*)EAAllocate(0x98, "Graphics", 0, 0, 0, 0);
    *out = raw ? raw->Init() : 0;
    if (refA.get())
    {
        FUN_006ac0a0(4, refA.get());
        (*out)->UpdateFromResource(refB.get());
    }
    else
    {
        (*out)->LoadFrom(refB.get());
    }
    return true;
}

// ---- 0x006f1df0 -------------------------------------------------------------
struct RefHolder4 {
    char pad0[4];
    RefObjA* mpRef;                    // +0x04
    __declspec(noinline) void Release();
};
// @ 0x006f1df0
void RefHolder4::Release()
{
    RefObjA* p = mpRef;
    if (p)
    {
        long n = _InterlockedDecrement(&p->mRefCount);
        if (n == 0)
        {
            _InterlockedExchange(&p->mRefCount, 1);
            if (p) p->Destroy(1);
        }
    }
}

// ---- 0x006f1e20 -------------------------------------------------------------
struct RefHolder8 {
    char pad0[8];
    RefObjA* mpRef;                    // +0x08
    __declspec(noinline) void Release();
};
// @ 0x006f1e20
void RefHolder8::Release()
{
    RefObjA* p = mpRef;
    if (p)
    {
        long n = _InterlockedDecrement(&p->mRefCount);
        if (n == 0)
        {
            _InterlockedExchange(&p->mRefCount, 1);
            if (p) p->Destroy(1);
        }
    }
}

// ---- 0x006f1f20 -------------------------------------------------------------
// @ 0x006f1f20
int EffectsRenderer::ClassifyVertexDesc(unsigned key, unsigned, unsigned a)
{
    int result = a;
    if (a == 0)
    {
        unsigned k = key;
        HtIter it = mTable88.find(k);
        HtNode* end = mTable88.mBuckets[mTable88.mBucketCount];
        void* v;
        if (it.node != end)
            v = it.node->mValue;
        else
            v = mpMaterial->LookupDesc(k);
        if (v)
        {
            void* st = *(void**)((char*)v + 4);
            if ((*(unsigned*)((char*)st + 8) & 0x100000) != 0)
            {
                const VtxDesc* vd = ((VdState*)st)->GetVertexDescriptor();
                int n = vd->count;
                char has2 = 0, has13 = 0, has5 = 0;
                for (int i = 0; i < n; i++)
                {
                    int ty = vd->streams[i].type;
                    if (ty == 2) has2 = 1;
                    if (ty == 0x13) has13 = 1;
                    else if (ty == 5) has5 = 1;
                }
                if (has2)
                {
                    if (has5)
                        result = (has13 ? 1 : 0) + 3;
                    else
                        result = 2;
                }
            }
        }
    }
    return result;
}

// ---- 0x006f2050 -------------------------------------------------------------
// @ 0x006f2050
void* EffectsRenderer::FindEntry(unsigned key, unsigned)
{
    HtTable* t = &mTable88;
    unsigned k = key;
    HtIter it = t->find(k);
    if (it.node != t->mBuckets[t->mBucketCount])
        return (char*)it.node + 4;
    return 0;
}

// ---- 0x006f2000 -------------------------------------------------------------
// @ 0x006f2000
int EffectsRenderer::ContainsKey(unsigned key)
{
    HtTable* t = &mTable3c;
    HtNode* end = t->mBuckets[t->mBucketCount];
    if (t->find(key).node == end)
    {
        if (!mpKeyed->Contains(key))
            return 0;
    }
    return 1;
}

__declspec(noinline) Node10* __stdcall Alloc10(Node10* src);
// ---- 0x006f20a0 -------------------------------------------------------------
// @ 0x006f20a0
Node10* __stdcall Alloc10(Node10* src)
{
    Node10* p = (Node10*)EAAllocate(0x10, "Graphics", 0, 0, kAllocatorFile, 0xd1);
    if (p)
        new (p) Node10(*src);
    p->mpNext = 0;
    return p;
}

// ---- 0x006f20f0 -------------------------------------------------------------
// @ 0x006f20f0
ResSub** HtTableB::FindOrInsert(const Key8* key)
{
    HtIterB it = findA(*key);
    if (it.node != mBuckets[mBucketCount])
        return (ResSub**)((char*)it.node + 8);
    HtValueB v;
    v.mKey = *key;
    v.mpRef = 0;
    HInsertResultB r = insertA(v, false);
    return (ResSub**)((char*)r.node + 8);
}

// ---- 0x006f2270 -------------------------------------------------------------
struct HashNode {
    char pad0[8];
    IVt* mpAt8;      // +0x08
    void* pC;        // +0x0c
    HashNode* mpNext;// +0x10
};
__declspec(noinline) void __stdcall FreeBucketList(HashNode** table, unsigned int count);
// @ 0x006f2270
void __stdcall FreeBucketList(HashNode** table, unsigned int count)
{
    HashNode* cur = 0;
    for (unsigned int i = 0; i < count; ++i) {
        HashNode* n = table[i];
        while (n) {
            cur = n;
            n = n->mpNext;
            IVt* p = cur->mpAt8;
            if (p)
                p->v0();
            EASTL_allocator_deallocate(cur);
        }
        table[i] = 0;
    }
}

// Fixed-capacity vector with an inline push_back (slow path out of line), as EASTL.
template<class T>
struct evec2 {
    T* mpBegin; T* mpEnd; T* mpCapacity; char mAllocator[4];
    void push_back(const T& v) { if (mpEnd < mpCapacity) ::new(mpEnd++) T(v); else DoInsertValue(mpEnd, v); }
    void DoInsertValue(T* pos, const T& v);
};

struct Owner23d0 {
    char pad0[0x60];
    IVt** mpAt60;    // +0x60
    IVt** mpAt64;    // +0x64
    char pad1[0x74 - 0x68];
    evec2<int> mVec74;   // +0x74
    __declspec(noinline) void Remove(int index);
};
// @ 0x006f23d0
void Owner23d0::Remove(int index)
{
    if (index < 0)
        return;
    if (index >= (int)(mpAt64 - mpAt60))
        return;
    mVec74.push_back(index);
    mpAt60[index]->v3();
    mpAt60[index] = 0;
}

// ---- 0x006f2310 -------------------------------------------------------------
// @ 0x006f2310
bool EffectsRenderer::InsertEntry(unsigned index, unsigned b, unsigned c, int* out)
{
    if ((b & c) == 0xffffffff)
        return false;
    ResSub* obj = 0;
    if (!LookupAndUse(b, c, &obj, index))
        return false;
    if (!obj)
        return false;

    if (mFreeVec.begin != mFreeVec.end)
    {
        int slot = mFreeVec.end[-1];
        mFreeVec.end -= 1;
        mObjVec.begin[slot] = obj;
        *out = slot;
        return true;
    }
    mObjVec.push_back(obj);
    *out = (int)(mObjVec.end - mObjVec.begin) - 1;
    return true;
}

// ---- 0x006f2430 -------------------------------------------------------------
struct BucketNode {
    unsigned mKey;                     // +0x00
    unsigned mValue;                   // +0x04
    RefObjA* mpRef;                    // +0x08
    BucketNode* mpNext;                // +0x0c
};
__declspec(noinline) void __stdcall FreeBucketList2(BucketNode** table, unsigned int count);
// @ 0x006f2430
void __stdcall FreeBucketList2(BucketNode** table, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i)
    {
        BucketNode* n = table[i];
        while (n)
        {
            BucketNode* cur = n;
            n = n->mpNext;
            RefObjA* p = cur->mpRef;
            if (p)
            {
                long refs = _InterlockedDecrement(&p->mRefCount);
                if (refs == 0)
                {
                    _InterlockedExchange(&p->mRefCount, 1);
                    if (p) p->Destroy(1);
                }
            }
            EASTL_allocator_deallocate(cur);
        }
        table[i] = 0;
    }
}
__declspec(noinline) void __cdecl AssignByKey(unsigned key, ResSub* value);
// ---- 0x006f24a0 -------------------------------------------------------------
// @ 0x006f24a0
void __cdecl AssignByKey(unsigned key, ResSub* value)
{
    Key8Bits kb;
    kb.q = (unsigned long long)key | ((unsigned long long)gKeyHigh << 32);
    HtTableB& t = *(HtTableB*)((char*)FUN_0067ddf0() + 0xa8);
    ResSub** slot = t.FindOrInsert(&kb.k);
    ResSub* old = *slot;
    if (value != old)
    {
        if (value)
            value->s0();
        *slot = value;
        if (old)
            return old->s1();
    }
}

// ---- 0x006f2510 -------------------------------------------------------------
// @ 0x006f2510
unsigned* HtTable::FindOrInsert2(const unsigned* key)
{
    HtIter it = find(*key);
    if (it.node != mBuckets[mBucketCount])
        return (unsigned*)it.node + 1;
    HtValue v;
    v.mKey = *key;
    v.mValue = 0;
    v.mpRef = 0;
    HInsertResult r = insert(v, false);
    return (unsigned*)r.node + 1;
}

// ---- 0x006f2620 -------------------------------------------------------------
// @ 0x006f2620
bool EffectsRenderer::ClearAll()
{
    int n = (int)(mObjVec.end - mObjVec.begin);
    for (int i = 0; i < n; ++i)
    {
        if (mObjVec.begin[i])
            mObjVec.begin[i]->s3();
    }
    mObjVec.clear();
    mFreeVec.clear();

    HtTable* t = &mTable88;
    t->FreeBuckets((unsigned)t->mBuckets, t->mBucketCount);
    t->mElementCount = 0;

    Model5c* m = mpModel;
    if (m)
    {
        BigVt* p6c = m->mp6c;
        m->mp5c = 0;
        m->mp60 = 0;
        m->mp64 = 0;
        m->mp68 = 0;
        if (p6c)
        {
            p6c->b7();
            BigVt* p6cNow = m->mp6c;
            if (p6cNow)
            {
                SubVt* sub = (SubVt*)((char*)p6cNow + 4);
                m->mp6c = 0;
                sub->u1();
            }
        }
        Model5c* model = mpModel;
        if (model)
        {
            mpModel = 0;
            model->c1();
        }
    }
    mpManager = 0;
    mpField54 = 0;
    mpMaterial = 0;
    return true;
}
