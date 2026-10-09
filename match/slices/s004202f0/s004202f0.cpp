// Slice s004202f0: small helpers of a pool/set container module (8-slot pool of 0x2c-byte
// entries, EASTL-style vector push_back/reserve helpers, a hash-set find).
// Built without optimization: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <intrin.h>
#include <new>

void EASTL_allocator_deallocate(void* p); // 0x00f47380

struct AtomicRefCounted {
    void* vtable;
    int pad;
    long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();   // 0x00402420
};

struct ThreadedObject { void Release(); };  // Resource::ThreadedObject::Release, 0x00404f90

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(const intrusive_ptr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
};

// 16-byte key with an out-of-line copy constructor (0x00420050)
struct Key16 {
    unsigned int w[4];
    Key16(const Key16& o);
};

struct Slot {
    Key16* Lookup(void* pTemp, Key16 key);   // 0x00425600
};
struct SlotIter {
    int p;
    void Advance();                          // 0x004258f0
};

struct RangeIter {
    int mpBucket;
    Key16 mKey;
    int mA;
    int mB;
    RangeIter(const SlotIter& it, const Key16& key, int a, int b) : mpBucket(it.p), mKey(key), mA(a), mB(b) {}
    RangeIter(const void* a, const void* b, const void* c, int n);   // 0x004258b0
};

struct Scratch16 { unsigned int w[4]; int Compute(); };   // 0x00503630

struct HashSet {
    char pad[0x160];
    RangeIter MakeEnd();                     // 0x00420350
    RangeIter MakeIter();                    // 0x004202f0
    RangeIter Build(SlotIter it, Key16 key, int a, int b);  // 0x00420390
};

// @ 0x004202f0
RangeIter HashSet::MakeIter()
{
    return RangeIter(MakeEnd());
}

// @ 0x00420350
RangeIter HashSet::MakeEnd()
{
    Scratch16 tmp;
    int size = tmp.Compute();
    return RangeIter(pad + 0x160, this, pad + 0x160, size);
}

// @ 0x00420390
// Not byte-exact (9 bytes differ): extra 4-byte frame slot and arg-copy scheduling.
RangeIter HashSet::Build(SlotIter it, Key16 key, int a, int b)
{
    if (it.p == b)
        return RangeIter(it, key, a, b);
    unsigned int tmp[5];
    key = *((Slot*)it.p)->Lookup(tmp, key);
    it.Advance();
    return RangeIter(it, key, a, b);
}

// ---------------------------------------------------------------------------
// A pool of 8 entries of 0x2c bytes each.
struct PoolEntry {
    char data[0x2c];
    void Reset();           // 0x004256e0
    int  Size();            // 0x00425450
    void SetA(int v);       // 0x00425530
    void SetB(int v);       // 0x004254c0
    bool IsEmpty();         // 0x00425430
    void Activate();        // 0x004255a0
    int  Process();         // 0x00501e20
};

struct Pool {
    PoolEntry e[8];

    void ResetAll();
    int TotalSize();
    void SetA(int v, int index);
    void SetB(int v, int index);
    bool AllEmpty();
    void ActivateFirstNonEmpty();
    int ProcessFirstNonEmpty();
};

// @ 0x00420440
void Pool::ResetAll()
{
    for (int i = 0; i < 8; i++)
        e[i].Reset();
}

// @ 0x00420480
int Pool::TotalSize()
{
    int total = 0;
    for (int i = 0; i < 8; i++)
        total += e[i].Size();
    return total;
}

// @ 0x004204d0
void Pool::SetA(int v, int index)
{
    e[index].SetA(v);
}

// @ 0x004204f0
void Pool::SetB(int v, int index)
{
    e[index].SetB(v);
}

// @ 0x00420510
bool Pool::AllEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty())
            return false;
    }
    return true;
}

// @ 0x00420560
void Pool::ActivateFirstNonEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty()) {
            e[i].Activate();
            return;
        }
    }
}

// @ 0x004205b0
int Pool::ProcessFirstNonEmpty()
{
    for (int i = 0; i < 8; i++) {
        if (!e[i].IsEmpty())
            return e[i].Process();
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Vectors
struct VecBase { void Free(); };   // 0x00425990 / 0x004c0b80 (container teardown)

struct RefVector {
    intrusive_ptr<AtomicRefCounted>* mpBegin;
    intrusive_ptr<AtomicRefCounted>* mpEnd;
    intrusive_ptr<AtomicRefCounted>* mpCapacity;
    void Destroy();   // 0x00425990
    void DoPushBack(intrusive_ptr<AtomicRefCounted>* pos, const intrusive_ptr<AtomicRefCounted>* v);  // 0x00425a80
    ~RefVector();
    void push_back(const intrusive_ptr<AtomicRefCounted>& v);
};

// @ 0x00420600
RefVector::~RefVector()
{
    typedef intrusive_ptr<AtomicRefCounted> Ref;
    Ref* last = mpEnd;
    Ref* first;
    int unusedTemp[3];   // reproduces the original frame size (inlined helper temporaries)
    for (first = mpBegin; first < last; ++first)
        first->~Ref();
    Destroy();
}

// @ 0x00420660
void RefVector::push_back(const intrusive_ptr<AtomicRefCounted>& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) intrusive_ptr<AtomicRefCounted>(v);
    else
        DoPushBack(mpEnd, &v);
}

struct Triple { int a, b, c; };

struct TripleVector {
    char pad0[4];
    Triple* mpEnd;
    Triple* mpCapacity;
    void DoPushBack(Triple* pos, const Triple* v);  // 0x00425d30
    void push_back(const Triple& v);
};

// @ 0x004206f0
void TripleVector::push_back(const Triple& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Triple(v);
    else
        DoPushBack(mpEnd, &v);
}

struct BigElem {
    char data[0x38];
    BigElem(int arg);   // 0x0040ce80
};

struct BigVector {
    char pad0[4];
    BigElem* mpEnd;
    BigElem* mpCapacity;
    void DoPushBack(BigElem* pos, int arg);  // 0x00425f90
    void emplace_back(int arg);
};

// @ 0x00420770
// Inlined helper with a 0x38-byte local that is never used (reproduces the original frame).
inline void UnusedTemp() { unsigned int p[14]; }

void BigVector::emplace_back(int arg)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) BigElem(arg);
    else
        DoPushBack(mpEnd, arg);
    UnusedTemp();
}

void* memcpy(void*, const void*, unsigned int);
void* AllocateAligned(void* allocator, unsigned int size, unsigned int align, unsigned int offset);  // 0x0042dee0

inline void FreeBlock(void* p) { EASTL_allocator_deallocate(p); }
inline void Marker() { const bool b2 = true; }

// Fixed-buffer-capable vector of pointers (allocator at +0xc, fixed buffer pointer at +0x10).
struct PtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    char allocator[4];
    void* mpFixed;
    void reserve(unsigned int n);   // 0x004207e0
    void DoFree(void** p, unsigned int n) { if (p && p != mpFixed) { void* q = p; FreeBlock(q); } }
};

inline void** MovePointers(void** first, void** last, void** dst)
{
    const bool bTrivial = true;
    return (void**)memcpy(dst, first, (char*)last - (char*)first) + (last - first);
}

// @ 0x004207e0
// Not byte-exact (~28 bytes differ): stack slot placement of two inline-local bools.
void PtrVector::reserve(unsigned int n)
{
    if (n > (unsigned int)(mpCapacity - mpBegin)) {
        void** pNew = n ? (void**)AllocateAligned(allocator, n * 4, 4, 0) : 0;
        void** result = MovePointers(mpBegin, mpEnd, pNew);
        Marker();
        DoFree(mpBegin, mpCapacity - mpBegin);
        unsigned int count = mpEnd - mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + count;
        mpCapacity = mpBegin + n;
    }
}

// ---------------------------------------------------------------------------
// More container helpers

// @ 0x004208f0
struct RangeFreeVector {
    char* mpBegin;
    char* mpEnd;
    void DoFreeRange(char* first, char* last);   // 0x004769b0
    void FreeRange();
};
void RangeFreeVector::FreeRange()
{
    int unusedTemp[4];   // reproduces the original frame size
    DoFreeRange(mpBegin, mpEnd);
}

// @ 0x00420920
// Not byte-exact (9 bytes differ): frame slot offsets of the two unused 12-byte regions.
struct ThreadedRefVector {
    ThreadedObject** mpBegin;
    ThreadedObject** mpEnd;
    void Destroy();   // 0x004c0b80
    ~ThreadedRefVector();
    void DestroyNoRelease();
};
ThreadedRefVector::~ThreadedRefVector()
{
    typedef intrusive_ptr<ThreadedObject> Ref;
    int unusedTemp[3];   // reproduces the original frame size
    Ref* last = (Ref*)mpEnd;
    Ref* first;
    int unusedTemp2[3];
    for (first = (Ref*)mpBegin; first < last; ++first)
        first->~Ref();
    Destroy();
}

// @ 0x00420980
struct RangeOpVector {
    char* mpBegin;
    char* mpEnd;
    void DoRange(char* first, char* last);   // 0x00426280
    void Run();
};
void RangeOpVector::Run()
{
    int unusedTemp[15];   // reproduces the original frame size
    DoRange(mpBegin, mpEnd);
}

// @ 0x004209b0
struct TrivialVector {
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    void Destroy();   // 0x004c0b80
    ~TrivialVector();
};
TrivialVector::~TrivialVector()
{
    unsigned int* p;
    int unusedTemp[3];   // reproduces the original frame size
    for (p = mpBegin; p < mpEnd; ++p) {
    }
    Destroy();
}

// 0x004209f0 / 0x00420ab0 / 0x00420b10: a small-buffer array (0x20 bytes)
extern const float kOne;    // 0x01485720
extern const float kTwo;    // 0x01470f1c
extern unsigned int g_EmptyBuffer[];   // 0x0154df28

struct BufferParams {
    float growth;       // +0x10
    float scale;        // +0x14
    int   offset;       // +0x18
    unsigned int AllocateCapacity(unsigned int n);   // 0x00921360 (thiscall on the params block)
};
inline void InitParams(BufferParams* p) { p->growth = kOne; p->scale = kTwo; p->offset = 0; }

struct Pad24 { unsigned int w[6]; };

struct SmallBuffer {
    unsigned int pad0;
    unsigned int* mpData;     // +4
    unsigned int mnCapacity;  // +8
    unsigned int mnCount;     // +0xc
    BufferParams mParams;     // +0x10
    unsigned int pad1c;       // +0x1c
    SmallBuffer(unsigned int n, Pad24 unused);   // 0x004209f0
    ~SmallBuffer();                              // 0x00420ab0
    SmallBuffer& operator=(const SmallBuffer& o);  // 0x00420b10
    void DestroyRange(unsigned int* p, unsigned int n);   // 0x0042ac80
    void DoFree(unsigned int* p, unsigned int n) { if (n > 1) { void* q = p; FreeBlock(q); } }
    void Swap(SmallBuffer& o);                    // 0x00426430
    SmallBuffer(const SmallBuffer& o);            // 0x00426320
    unsigned int* Allocate(unsigned int n);       // 0x00567260
};

// @ 0x004209f0
SmallBuffer::SmallBuffer(unsigned int n, Pad24 unused)
    : mnCapacity(0), mnCount(0)
{
    InitParams(&mParams);
    if (n < 2) {
        mnCapacity = 1;
        mpData = g_EmptyBuffer;
        mnCount = 0;
        mParams.offset = 0;
    } else {
        mnCapacity = mParams.AllocateCapacity(n);
        mpData = Allocate(mnCapacity);
    }
}

// @ 0x00420ab0
SmallBuffer::~SmallBuffer()
{
    DestroyRange(mpData, mnCapacity);
    mnCount = 0;
    DoFree(mpData, mnCapacity);
}

// @ 0x00420b10
SmallBuffer& SmallBuffer::operator=(const SmallBuffer& o)
{
    if (this != &o) {
        SmallBuffer tmp(o);
        int pad[3];   // unused; reproduces the original frame size
        Swap(tmp);
    }
    return *this;
}

struct HashNode {
    int key;
    int value;
    HashNode* next;
};
struct HashIter {
    HashNode* mpNode;
    HashNode** mpBucket;
    HashIter(HashNode* node, HashNode** bucket) : mpNode(node), mpBucket(bucket) {}
};
struct FieldSetHash { unsigned int operator()(int key) const; };    // 0x00401bf0
struct FieldSetEqualTo { bool operator()(int a, int b) const; };    // 0x00401ca0
struct FieldHashSet {
    char mEmpty0;
    FieldSetEqualTo mEqual;   // +1
    FieldSetHash mHash;       // +2
    HashNode** mpBuckets;     // +4
    unsigned int mnBuckets;   // +8

    unsigned int GetHashCode(int k) const { return mHash(k); }
    int GetKey(const HashNode* n) const { return n->key; }
    bool Compare(int k, int nodeKey) const { return mEqual(k, nodeKey); }
    HashNode* FindNode(HashNode* pNode, const int& k, unsigned int code) const
    {
        for (; pNode; pNode = pNode->next) {
            if (Compare(k, GetKey(pNode)))
                return pNode;
        }
        return 0;
    }
    static HashIter EndIter(HashNode** b) { return HashIter(*b, b); }
    static HashIter CopyIter(const HashIter& r) { return HashIter(r.mpNode, r.mpBucket); }
    HashIter find(const int& key);
};

// @ 0x00420b50
HashIter FieldHashSet::find(const int& key)
{
    unsigned int hash = GetHashCode(key);
    unsigned int idx = hash % mnBuckets;
    HashNode* pFound = FindNode(mpBuckets[idx], key, hash);
    return CopyIter(pFound ? HashIter(pFound, mpBuckets + idx) : EndIter(mpBuckets + mnBuckets));
}
