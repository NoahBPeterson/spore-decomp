// Unoptimized EASTL-style containers and a message class (module built /Od /Ob1 /arch:SSE).
#include "types.h"
#include <intrin.h>

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void __cdecl FreeBlock(void* p);        // EASTL_allocator_deallocate (0x00f47380)

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// ---------------------------------------------------------------------------
// vector<Item24>::push_back
// ---------------------------------------------------------------------------
struct Item24Base {
    uint8_t data[0x14];
    Item24Base(const Item24Base& o) throw();     // 0x0042ad20
};
struct ItemFlag {
    uint8_t v;
    ItemFlag() {}
    ItemFlag(const ItemFlag& o) : v(o.v) {}
};
struct Item24 : Item24Base {
    ItemFlag flag;
    uint8_t pad[3];
    Item24(const Item24& o) throw() : Item24Base(o) { flag = o.flag; }
};

struct Item24Vec {
    Item24* mBegin;
    Item24* mEnd;
    Item24* mCap;
    void DoInsertValue(Item24* pos, const Item24& v);   // 0x00426e30
    void push_back(const Item24& v);
};

// @ 0x004215f0
void Item24Vec::push_back(const Item24& v)
{
    if (mEnd < mCap) {
        ::new(mEnd++) Item24(v);
        ScratchSlots<15>();
    } else {
        DoInsertValue(mEnd, v);
    }
}

// ---------------------------------------------------------------------------
// vector<Quad> (16-byte trivially copyable elements)::operator=
// ---------------------------------------------------------------------------
struct Quad { uint32_t a, b, c, d; };

struct QuadVec {
    Quad* mBegin;
    Quad* mEnd;
    Quad* mCap;
    Quad* DoAllocateAndCopy(uint32_t n, const Quad* first, const Quad* last);   // 0x00427210
    static void __cdecl UninitCopy(const Quad* first, const Quad* last, Quad* dest);   // 0x00427270

    static void DoFree(Quad* p, uint32_t n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                FreeBlock(q);
            }
        }
    }
    static Quad* DoCopy(const Quad* first, const Quad* last, Quad* dest)
    {
        bool b2 = false, b0 = false, bPod = false;
        Quad* out = dest;
        const Quad* pSrc = first;
        for (; pSrc != last; ++out, ++pSrc)
            *out = *pSrc;
        return out;
    }
    void DestroyFrom(Quad* q) { for (; q < mEnd; ++q) { } }
    QuadVec& assign(const QuadVec& x);
};

// @ 0x00421670
QuadVec& QuadVec::assign(const QuadVec& x)
{
    if (&x != this) {
        uint32_t n = x.mEnd - x.mBegin;
        Quad* pNew;
        Quad* result;
        uint32_t spare[9];
        if (n > (uint32_t)(mCap - mBegin)) {
            pNew = DoAllocateAndCopy(n, x.mBegin, x.mEnd);
            for (Quad* it2 = mBegin; it2 < mEnd; ++it2) { }
            DoFree(mBegin, mCap - mBegin);
            mBegin = pNew;
            mCap = mBegin + n;
        } else if (n > (uint32_t)(mEnd - mBegin)) {
            DoCopy(x.mBegin, x.mBegin + (mEnd - mBegin), mBegin);
            UninitCopy(x.mBegin + (mEnd - mBegin), x.mEnd, mEnd);
            ScratchSlots<11>();
        } else {
            result = DoCopy(x.mBegin, x.mEnd, mBegin);
            DestroyFrom(result);
        }
        mEnd = mBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// hash_map<uint32_t, ...>: find / insert
// ---------------------------------------------------------------------------
struct HashNode {
    uint32_t key;
    uint32_t value;
    HashNode* next;
};

struct HashIter {
    HashNode* node;
    HashNode** bucket;
    HashIter(HashNode* n, HashNode** b) : node(n), bucket(b) {}
    HashIter(const HashIter& o) { HashNode** b = o.bucket; HashNode* nd = o.node; node = nd; bucket = b; }
};

struct HashInsertResult {
    HashIter it;
    bool inserted;
    HashInsertResult(const HashIter& a, const bool& b) : it(a), inserted(b) {}
};

struct RehashResult { bool needed; uint32_t newBuckets; };

struct RehashPolicy {
    uint32_t pad;
    void GetRehashRequired(RehashResult* out, uint32_t buckets, uint32_t elems, uint32_t add);   // 0x00921440
};

struct HashTable {
    uint32_t pad0;
    HashNode** mBuckets;
    uint32_t mBucketCount;
    uint32_t mElementCount;
    RehashPolicy mPolicy;

    HashNode* AllocateNode(const uint32_t* key);         // 0x00567200
    void DoRehash(uint32_t n);                           // 0x00427320

    static uint32_t HashInner(uint32_t v) { return v; }
    static uint32_t HashCode(const uint32_t& v) { return HashInner(v); }
    static bool Equal(uint32_t a, uint32_t b) { return a == b; }
    HashIter end() { HashNode** b = mBuckets + mBucketCount; HashNode* nd = *b; return HashIter(nd, b); }
    HashNode* DoFindNode(HashNode* n, const uint32_t* key)
    {
        for (; n; n = n->next)
            if (Equal(*key, n->key))
                return n;
        return 0;
    }
    HashIter find(const uint32_t* key);
    HashInsertResult insert(const uint32_t* key, uint32_t unused);
};

// @ 0x00421950
HashIter HashTable::find(const uint32_t* key)
{
    uint32_t hash = HashCode(*key);
    uint32_t n = hash % mBucketCount;
    HashNode* pNode = DoFindNode(mBuckets[n], key);
    return pNode ? HashIter(pNode, mBuckets + n) : end();
}

// @ 0x00421a50
HashInsertResult HashTable::insert(const uint32_t* key, uint32_t unused)
{
    const uint32_t* k = key;
    uint32_t hash = HashCode(*k);
    uint32_t n = hash % mBucketCount;
    HashNode* pNode = DoFindNode(mBuckets[n], k);
    if (!pNode) {
        RehashResult r;
        mPolicy.GetRehashRequired(&r, mBucketCount, mElementCount, 1);
        HashNode* nn = AllocateNode(key);
        if (r.needed) {
            n = hash % r.newBuckets;
            DoRehash(r.newBuckets);
        }
        nn->next = mBuckets[n];
        mBuckets[n] = nn;
        mElementCount += 1;
        return HashInsertResult(HashIter(nn, mBuckets + n), true);
    }
    return HashInsertResult(HashIter(pNode, mBuckets + n), false);
}

// ---------------------------------------------------------------------------
// vector<IPtr>::resize
// ---------------------------------------------------------------------------
struct Counted {
    virtual void AddRef();
    virtual void Release();
};

struct IPtr {
    Counted* p;
    IPtr() : p(0) {}
    ~IPtr() { if (p) p->Release(); }
};

struct IPtrVec {
    IPtr* mBegin;
    IPtr* mEnd;
    IPtr* mCap;
    void InsertFill(IPtr* pos, uint32_t n, const IPtr& v) throw();   // 0x0042aeb0
    void erase(IPtr* first, IPtr* last);                             // 0x00533500
    void insertN(IPtr* pos, uint32_t c, const IPtr& v) { InsertFill(pos, c, v); }
    void resize(uint32_t n);
};

// @ 0x00421bf0
void IPtrVec::resize(uint32_t n)
{
    if (n > (uint32_t)(mEnd - mBegin)) {
        IPtr hold;
        insertN(mEnd, n - (mEnd - mBegin), hold);
        ScratchSlots<7>();
    } else {
        erase(mBegin + n, mEnd);
    }
}

// ---------------------------------------------------------------------------
// Destructors of three vector<T> instantiations (explicit element destruction loop, then the
// base storage release). Element destructors are out of line.
// ---------------------------------------------------------------------------
struct Elem32 { uint32_t d[8]; ~Elem32(); };      // 0x20-byte element, dtor at 0x005477e0
struct Elem56 { uint32_t d[14]; ~Elem56(); };     // 0x38-byte element, dtor at 0x00429480
struct Elem24 { uint32_t d[6]; void Destruct(uint32_t flags); };   // 0x18-byte element, deleting-dtor style at 0x00429410

struct Elem32Vec {
    Elem32* mBegin;
    Elem32* mEnd;
    Elem32* mCap;
    void Free();                                   // 0x004273f0
    static void DestroyRange(Elem32* f, Elem32* l) { ScratchSlots<4>(); for (; f < l; ++f) f->~Elem32(); }
    ~Elem32Vec();
};

// @ 0x00421d70
Elem32Vec::~Elem32Vec()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

struct Elem56Vec {
    Elem56* mBegin;
    Elem56* mEnd;
    Elem56* mCap;
    void Free();                                   // 0x00427440
    static void DestroyRange(Elem56* f, Elem56* l) { ScratchSlots<9>(); for (; f < l; ++f) f->~Elem56(); }
    ~Elem56Vec();
};

// @ 0x00421dd0
Elem56Vec::~Elem56Vec()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

struct Elem24Vec2 {
    Elem24* mBegin;
    Elem24* mEnd;
    Elem24* mCap;
    void Free();                                   // 0x004fd940
    static void DestroyRange(Elem24* f, Elem24* l) { ScratchSlots<3>(); for (; f < l; ++f) f->Destruct(0); }
    ~Elem24Vec2();
};

// @ 0x00421e30
Elem24Vec2::~Elem24Vec2()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------
struct Holder {
    uint32_t pad[3];
    uint32_t mValue;
    void Apply(uint32_t a, uint32_t b);      // 0x0083c7f0
    void Set(uint32_t a, uint32_t b);
};
// @ 0x00421e80
void Holder::Set(uint32_t a, uint32_t b)
{
    mValue = b;
    Apply(a, b);
}

struct Unknown { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Query(uint32_t iid); };

// @ 0x00421eb0
void* __cdecl QueryA(Unknown** ref)
{
    void* result;
    Unknown* p = *ref;
    Unknown* pTmp;
    Unknown* pCast;
    if (p) {
        pCast = pTmp;
        pCast = *ref;
        result = pCast->Query(0x3c609f8);
    } else {
        result = 0;
    }
    return result;
}

// @ 0x00421f60
void* __cdecl QueryB(Unknown** ref)
{
    void* result;
    Unknown* p = *ref;
    Unknown* pTmp;
    Unknown* pCast;
    if (p) {
        pCast = pTmp;
        pCast = *ref;
        result = pCast->Query(0x30bdee3);
    } else {
        result = 0;
    }
    return result;
}

struct Tmp16 { uint32_t w[4]; };
struct SubObj { void Erase(Tmp16* out, int a); };       // 0x00425380
struct Resetter {
    uint32_t mFirst;
    SubObj mSub;
    uint32_t pad[4];
    uint32_t mLast;
    void Finish();                                       // 0x004258f0
    Resetter* Reset();
};
// @ 0x00421f00
Resetter* Resetter::Reset()
{
    if (mFirst == mLast)
        return this;
    Tmp16 t;
    mSub.Erase(&t, 0);
    Finish();
    return this;
}

void __cdecl ThunkTarget();                              // 0x00427600
struct Thunk {
    void (__cdecl *mFn)();
    uint32_t mArg;
    void Init(uint32_t arg);
};
// @ 0x00421f40
void Thunk::Init(uint32_t arg)
{
    mFn = ThunkTarget;
    mArg = arg;
}

// ---------------------------------------------------------------------------
// Message with a table of up to 32 listener slots. The class hierarchy (cLocaleChangeMessage /
// UI::BehaviorMessage / a third derived class) is not recovered, so this is written over a raw
// layout with the vtable addresses of the three classes the constructor walks through.
// ---------------------------------------------------------------------------
extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844

struct Listener { virtual void v0(); virtual void Release(); };
struct Slot { Listener* listener; uint32_t extra; };
struct MessageHeader { uint32_t data[10]; uint32_t arg; };

struct SlotMessage {
    const void* vptr;          // +0x00
    volatile long refCount;    // +0x04
    uint32_t body[0x2c];       // +0x08 .. : 32 slots of 8 bytes; arg lives at +0x30, listener mask at +0x38

    SlotMessage* Construct(uint32_t arg);
    void Destruct();
};

// @ 0x00421c80
SlotMessage* SlotMessage::Construct(uint32_t arg)
{
    MessageHeader* pHdr = (MessageHeader*)((char*)this + 8);
    pHdr->arg = arg;
    vptr = vtbl_App_cLocaleChangeMessage;
    vptr = vtbl_UI_BehaviorMessage;
    volatile long* pRefCount = &refCount;
    _InterlockedExchange(pRefCount, 0);
    vptr = vtbl_UI_BehaviorMessage;
    vptr = vtbl_SlotMessage;
    body[12] = 0;
    return this;
}

// @ 0x00421cf0
void SlotMessage::Destruct()
{
    vptr = vtbl_SlotMessage;
    for (int i = 0; i < 32; i++) {
        if (((1 << i) & body[12]) && ((Slot*)body)[i].listener)
            ((Slot*)body)[i].listener->Release();
    }
    vptr = vtbl_UI_BehaviorMessage;
    vptr = vtbl_App_cLocaleChangeMessage;
}
