// Small container/smart-pointer helpers from the startup/resource area (0x0041CB40..0x0041D420):
// a 3x3 row copy, intrusive smart pointers, hash_map operator[] instantiations and
// fixed-capacity vector constructors.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, locals in memory).
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};

struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);
};

// @ 0x0041CB40
Matrix3& Matrix3::Assign(const Matrix3& m)
{
    row0 = Vector3(m.row0);
    row1 = Vector3(m.row1);
    row2 = Vector3(m.row2);
    return *this;
}

// ---- intrusive reference counted objects --------------------------------------------------
struct VirtualRefObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct VirtualRefPtr {
    VirtualRefObject* mp;
    VirtualRefPtr() : mp(0) {}
    VirtualRefPtr(VirtualRefObject* p);
    VirtualRefPtr(const VirtualRefPtr& o) { mp = o.mp; if (mp) mp->AddRef(); }
    ~VirtualRefPtr() { if (mp) mp->Release(); }
};

// @ 0x0041CC20
VirtualRefPtr::VirtualRefPtr(VirtualRefObject* p)
{
    mp = p;
    if (mp)
        mp->AddRef();
}

struct DefaultRefCounted {
    int mVtbl;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};

struct TargetPtr {
    DefaultRefCounted* mp;
    TargetPtr& Assign(DefaultRefCounted* p);
    TargetPtr& Init(DefaultRefCounted* p);
};

// @ 0x0041CC60
TargetPtr& TargetPtr::Assign(DefaultRefCounted* p)
{
    if (p != mp) {
        DefaultRefCounted* old = mp;
        uint32_t unused[3];   // dead locals of the original (frame size only)
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x0041CCC0
TargetPtr& TargetPtr::Init(DefaultRefCounted* p)
{
    mp = p;
    if (mp)
        mp->AddRef();
    return *this;
}

struct SharedObject {
    void AddRef();
    void Release();
};

struct SharedPtr {
    SharedObject* mp;
    SharedPtr& Assign(SharedObject* p);
};

// @ 0x0041CD10
SharedPtr& SharedPtr::Assign(SharedObject* p)
{
    if (p != mp) {
        SharedObject* old = mp;
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    return *this;
}

// ---- fixed-capacity vectors ---------------------------------------------------------------
struct FixedAllocator {
    uint32_t pad;
    void*    mpPool;
    FixedAllocator(void* pool) { mpPool = pool; }
    FixedAllocator(const FixedAllocator& a) { mpPool = a.mpPool; }
};

// Stand-in for the dead locals of an inlined helper (only the frame size is visible).
inline void InlineScratch()
{
    uint32_t unused[7];
}

struct VectorBase {
    char*          mpBegin;
    char*          mpEnd;
    char*          mpCapacity;
    FixedAllocator mAllocator;
    VectorBase(const FixedAllocator& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
};

template <int Bytes>
struct FixedVector : VectorBase {
    uint32_t       pad;
    char           mBuffer[Bytes];
    void           Reserve(uint32_t n);   // external
    FixedVector(uint32_t n);
    FixedVector() : VectorBase(FixedAllocator(mBuffer))
    {
        mpEnd = mBuffer;
        mpBegin = mpEnd;
        mpCapacity = mpBegin + Bytes;
    }
};

template <int Bytes>
FixedVector<Bytes>::FixedVector(uint32_t n) : VectorBase(FixedAllocator(mBuffer))
{
    mpEnd = mBuffer;
    mpBegin = mpEnd;
    mpCapacity = mpBegin + Bytes;
    InlineScratch();
    Reserve(n);
}

// @ 0x0041CF00 (192 bytes of storage)
template FixedVector<0xC0>::FixedVector();
// @ 0x0041CF70 (896 bytes)
template FixedVector<0x380>::FixedVector();
// @ 0x0041CFE0 (64 bytes)
template FixedVector<0x40>::FixedVector();
// @ 0x0041D050 (256 bytes); the size_t constructor at 0x0041D0C0 is instantiated with it
template FixedVector<0x100>::FixedVector();
// @ 0x0041D0C0
template FixedVector<0x100>::FixedVector(uint32_t);
// @ 0x0041D420 (384 bytes)
template FixedVector<0x180>::FixedVector();

// ---- hash_map<K, M>::operator[] instantiations ---------------------------------------------
struct InsertTag {};

// Stand-in for dead locals of inlined helpers (only the frame size is visible).
inline void InlineScratch48()
{
    uint32_t unused[12];
}

template <class K, class M>
struct HashMap {
    struct value_type {
        K first;
        M second;
        value_type(const K& k, const M& m) : first(k), second(m) {}
    };
    struct Node {
        value_type mValue;
        Node*      mpNext;
    };
    struct Iterator {
        Node*  mpNode;
        Node** mpBucket;
        Iterator() {}
        Iterator(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
        bool operator!=(const Iterator& o) const { return mpNode != o.mpNode; }
    };
    struct InsertResult {
        Iterator first;
        bool     second;
    };

    uint32_t pad;
    Node**   mpBucketArray;
    uint32_t mnBucketCount;

    Iterator     find(const K& key);
    InsertResult DoInsert(const value_type& v, InsertTag tag);
    InsertResult insert(const value_type& v) { return DoInsert(v, InsertTag()); }
    Iterator     end() { Node** b = mpBucketArray + mnBucketCount; return Iterator(*b, b); }
    M&           operator[](const K& key);
};

template <class K, class M>
M& HashMap<K, M>::operator[](const K& key)
{
    InlineScratch48();
    Iterator it = find(key);
    if (it != end())
        return it.mpNode->mValue.second;
    return insert(value_type(key, M())).first.mpNode->mValue.second;
}

struct Key8 { uint32_t a, b; };

// @ 0x0041CD60
template struct HashMap<Key8, VirtualRefPtr>;
// @ 0x0041CE60
template struct HashMap<Key8, int>;

// ---- intrusive pointer with an atomic reference count --------------------------------------
extern "C" long _InterlockedExchangeAdd(long volatile* p, long v);
#pragma intrinsic(_InterlockedExchangeAdd)

struct ThreadedObject {
    void* mVtbl;
    long  mnRefCount;
    void AddRef() { _InterlockedExchangeAdd(&mnRefCount, 1); }
    void Release();   // Resource::ThreadedObject::Release (external)
};

struct ThreadedPtr {
    ThreadedObject* mp;
    ThreadedPtr() : mp(0) {}
    ThreadedPtr(const ThreadedPtr& o) { mp = o.mp; if (mp) mp->AddRef(); }
    ~ThreadedPtr() { if (mp) mp->Release(); }
};

// @ 0x0041D1F0
template struct HashMap<ThreadedPtr, int>;
// @ 0x0041D2C0
template struct HashMap<uint32_t, float>;

// ---- fixed buffers with an extra flag word -------------------------------------------------
template <int Bytes>
struct FixedBuffer {
    char*    mpBegin;
    char*    mpEnd;
    char*    mpCapacity;
    uint32_t pad[2];
    uint32_t mFlags;       // +0x14
    char     mBuffer[Bytes];
    FixedBuffer()
    {
        uint32_t unused;   // dead local of the original (frame size only)
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        mFlags = 0;
        mpBegin = mBuffer;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + Bytes;
    }
};

// @ 0x0041D360 (512 bytes)
template FixedBuffer<0x200>::FixedBuffer();
// @ 0x0041D3C0 (160 bytes)
template FixedBuffer<0xA0>::FixedBuffer();

// ---- range assignment ----------------------------------------------------------------------
struct ConstructTag {};

struct RangeOwner {
    void* mpFirst;
    void* mpLast;
    void Destroy(void* first, void* last);                     // external
    void Construct(void* first, void* last, ConstructTag tag); // external
    void Copy(void* first, void* last) { ConstructTag tag; Construct(first, last, tag); }
    RangeOwner& Assign(const RangeOwner& o);
};

// @ 0x0041D140
RangeOwner& RangeOwner::Assign(const RangeOwner& o)
{
    uint32_t unused[4];   // dead locals of the original (frame size only)
    if (this != &o) {
        Destroy(mpFirst, mpLast);
        Copy(o.mpFirst, o.mpLast);
    }
    return *this;
}

// ---- object with a flag-heavy initializer --------------------------------------------------
struct FlagTag {};

struct FlagObject {
    void Setup(int zero, const FlagTag& f5, const FlagTag& f4, const FlagTag& f3, const FlagTag& f2, const FlagTag& f1, void* arg);   // external
    FlagObject(void* arg);
};

// @ 0x0041D1A0
FlagObject::FlagObject(void* arg)
{
    Setup(0, FlagTag(), FlagTag(), FlagTag(), FlagTag(), FlagTag(), arg);
}
