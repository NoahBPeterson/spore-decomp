// EASTL fixed_hash_map<uint32_t, TextureSet> internals + two constructors
// (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE, no /EHsc).
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
extern "C" void* __cdecl memset(void*, int, unsigned int);

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

// ---- intrusive ref-counted resource pointer ----
struct RefCounted {
    void* vtbl;
    uint32_t pad;
    volatile long mRefCount;           // +8
    void Release();                    // 0x00402420 AtomicRefCounted::Release
    void AddRef() { _InterlockedIncrement(&mRefCount); }
};

template <typename T>
struct intrusive_ptr {
    T* mp;
    intrusive_ptr() : mp(0) {}
    // @ 0x00506f80 ??0?$intrusive_ptr
    intrusive_ptr(const intrusive_ptr& x)
    {
        mp = x.mp;
        if (mp)
            mp->AddRef();
    }
    ~intrusive_ptr() { if (mp) mp->Release(); }
    intrusive_ptr& operator=(T* p)
    {
        if (p != mp) {
            T* const pTemp = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
typedef intrusive_ptr<RefCounted> RefPtr;
// emitted out of line in the original (target of the `vector copy constructor iterator' helper)
template intrusive_ptr<RefCounted>::intrusive_ptr(const intrusive_ptr<RefCounted>& x);



// three textures (diffuse/...); implicit copy-ctor and destructor
struct TextureSetData {
    RefPtr mTextures[3];
};
struct TextureSet : TextureSetData {
    TextureSet() {}
    TextureSet(const TextureSet& x);
};
// @ 0x00506f10 ??0TextureSet
TextureSet::TextureSet(const TextureSet& x) : TextureSetData(x) {}


namespace eastl {

struct allocator {};
struct true_type {};

template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy(float fMaxLoadFactor = 1.f) : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.f), mnNextResize(0) {}
    uint32_t GetNextBucketCount(uint32_t nBucketCountHint) const;   // 0x00921360
    uint32_t GetBucketCount(uint32_t nElementCount) const;          // 0x009213c0
};

uint32_t __cdecl GetPrimeBucketCount(uint32_t n);                  // 0x00921340

struct Link { Link* mpNext; };

struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    fixed_pool_base() : mpHead(0) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};

// fixed_pool_with_overflow: 0x14 bytes
struct fixed_pool_with_overflow : fixed_pool_base {
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10

    __forceinline fixed_pool_with_overflow(void* pMemory)
    {
        init(pMemory, 0x280, 0x14, 4, 0);
        mpPoolBegin = pMemory;
        mpPoolEnd = (char*)pMemory + 0x280;
        mnNodeSize = 0x14;
    }
    void* allocate();                                  // 0x004ce850
    void deallocate(void* p)
    {
        if ((p >= mpPoolBegin) && (p < mpPoolEnd)) {
            ((Link*)p)->mpNext = mpHead;
            mpHead = ((Link*)p);
        } else
            overflow_deallocate(p, mnNodeSize);
    }
    static void overflow_deallocate(void* p, uint32_t /*n*/) { delete[] (char*)p; }
};

struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;   // +0
    void* mpBucketBuffer;             // +0x14

    fixed_hashtable_allocator(void* pNodeBuffer, void* pBucketBuffer) : mPool(pNodeBuffer), mpBucketBuffer(pBucketBuffer) {}
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);   // 0x00506fc0

    void* allocate(uint32_t n)
    {
        if (n == 0x14)
            return mPool.allocate();
        return mpBucketBuffer;
    }
    template <int kSlots>
    void* allocate_slots(uint32_t n)
    {
        ScratchSlots<kSlots>();
        if (n == 0x14)
            return mPool.allocate();
        return mpBucketBuffer;
    }
    void deallocate(void* p, uint32_t)
    {
        if (p != mpBucketBuffer)
            mPool.deallocate(p);
    }
};

// @ 0x00506fc0 ??0fixed_hashtable_allocator
fixed_hashtable_allocator::fixed_hashtable_allocator(const fixed_hashtable_allocator& x)
    : mPool(x.mPool.mpHead), mpBucketBuffer(x.mpBucketBuffer)
{
}

// @ 0x005072a0
void* allocate_memory(fixed_hashtable_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset)
{
    ScratchSlots<1>();
    if (alignment <= 8)
        return a.allocate_slots<2>(n);            // EASTLAlloc(a, n)
    return a.allocate_slots<3>(n);                // EASTLAllocAligned(a, n, alignment, alignmentOffset)
}

struct mod_range_hashing {};
struct default_ranged_hash {};
template <typename T> struct use_first {};
template <typename T> struct hash {};
template <typename T> struct equal_to {};

extern void* gpEmptyBucketArray[2];

typedef pair<uint32_t, TextureSet> value_type;

struct node_type {
    value_type mValue;     // +0 (key), +4 (TextureSet)
    node_type* mpNext;     // +0x10
};

struct insert_return_type {
    node_type* mpNode;
    node_type** mpBucket;
    bool second;
    insert_return_type() : mpNode(0), mpBucket(0), second(false) {}
};

struct hashtable;

template <typename Hashtable>
struct rehash_base {
    void set_max_load_factor(float fMaxLoadFactor);
};

struct hashtable : rehash_base<hashtable> {
    uint32_t mHashCodeBase;                  // +0
    node_type** mpBucketArray;               // +4
    uint32_t mnBucketCount;                  // +8
    uint32_t mnElementCount;                 // +0xc
    prime_rehash_policy mRehashPolicy;       // +0x10
    fixed_hashtable_allocator mAllocator;    // +0x1c

    hashtable(uint32_t nBucketCount, const hash<uint32_t>& h1, const mod_range_hashing& h2,
              const default_ranged_hash& h, const equal_to<uint32_t>& eq, const use_first<value_type>& ek,
              const fixed_hashtable_allocator& allocator);

    void reset()
    {
        mnBucketCount = 1;
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }

    uint32_t bucket_index(const node_type* pNode, uint32_t nBucketCount) const
    {
        const uint32_t c = pNode->mValue.first;
        return c % nBucketCount;
    }
    node_type** DoAllocateBuckets(uint32_t n);
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n)
    {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    node_type* DoAllocateNode(const value_type& value);
    void DoFreeNode(node_type* pNode);
    void DoFreeNodes(node_type** pNodeArray, uint32_t n);
    void DoRehash(uint32_t nNewBucketCount);
    void clear();
    void rehash_policy(const prime_rehash_policy& rehashPolicy)
    {
        mRehashPolicy = rehashPolicy;
        const uint32_t nBuckets = rehashPolicy.GetBucketCount(mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }
    insert_return_type DoInsertValue(const value_type& value, true_type);   // 0x00506d70
    insert_return_type insert(const value_type& value) { return DoInsertValue(value_type(value), true_type()); }
};

// @ 0x00506b80 set_max_load_factor
template <>
void rehash_base<hashtable>::set_max_load_factor(float fMaxLoadFactor)
{
    hashtable* const pThis = static_cast<hashtable*>(this);
    pThis->rehash_policy(prime_rehash_policy(fMaxLoadFactor));
}

// @ 0x00506c00
hashtable::hashtable(uint32_t nBucketCount, const hash<uint32_t>& h1, const mod_range_hashing& h2,
                     const default_ranged_hash& h, const equal_to<uint32_t>& eq, const use_first<value_type>& ek,
                     const fixed_hashtable_allocator& allocator)
    : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(allocator)
{
    ScratchSlots<1>();
    if (nBucketCount < 2)
        reset();
    else {
        mnBucketCount = mRehashPolicy.GetNextBucketCount(nBucketCount);
        mpBucketArray = DoAllocateBuckets(mnBucketCount);
    }
}

// @ 0x00506cd0
void hashtable::clear()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}

// @ 0x00507030
node_type* hashtable::DoAllocateNode(const value_type& value)
{
    ScratchSlots<1>();
    node_type* const pNode = (node_type*)allocate_memory(mAllocator, sizeof(node_type), 4, 0);
    ScratchSlots<1>();
    ::new(&pNode->mValue) value_type(value);
    ScratchSlots<2>();
    pNode->mpNext = 0;
    return pNode;
}

// @ 0x005070a0
node_type** hashtable::DoAllocateBuckets(uint32_t n)
{
    ScratchSlots<3>();
    node_type** const pBucketArray = (node_type**)mAllocator.allocate((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = (node_type*)(uint32_t)~0;
    return pBucketArray;
}

// @ 0x00507110 DoRehash
void hashtable::DoRehash(uint32_t nNewBucketCount)
{
    node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    node_type* pNode;
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        while ((pNode = mpBucketArray[i]) != 0) {
            const uint32_t nNewBucketIndex = bucket_index(pNode, nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

// @ 0x00507230
void hashtable::DoFreeNodes(node_type** pNodeArray, uint32_t n)
{
    ScratchSlots<1>();
    for (uint32_t i = 0; i < n; ++i) {
        ScratchSlots<1>();
        node_type* pNode = pNodeArray[i];
        while (pNode) {
            node_type* const pTempNode = pNode;
            pNode = pNode->mpNext;
            ScratchSlots<3>();
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}

// @ 0x005072f0
void hashtable::DoFreeNode(node_type* pNode)
{
    pNode->~node_type();
    mAllocator.deallocate(pNode, sizeof(node_type));
}

struct hash_map_base : hashtable {
    hash_map_base(uint32_t nBucketCount, const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate,
                  const fixed_hashtable_allocator& allocator);
};

// @ 0x00506b30
hash_map_base::hash_map_base(uint32_t nBucketCount, const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate,
                             const fixed_hashtable_allocator& allocator)
    : hashtable(nBucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), predicate,
                use_first<value_type>(), allocator)
{
}

// fixed_hash_map<uint32_t, TextureSet, 0x20>: buckets at +0x34, node buffer at +0xbc (0x280 bytes)
struct fixed_hash_map : hash_map_base {
    void* mBucketBuffer[0x22];        // +0x34
    uint8_t mNodeBuffer[0x280];       // +0xbc

    fixed_hash_map(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate);
};

// @ 0x00506aa0 ??0fixed_hash_map
fixed_hash_map::fixed_hash_map(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate)
    : hash_map_base(GetPrimeBucketCount(0x21), hashFunction, predicate, fixed_hashtable_allocator(mNodeBuffer, mBucketBuffer))
{
    ScratchSlots<6>();
    set_max_load_factor(10000.f);
}

} // namespace eastl

// @ 0x00506a40 ??1TextureSetData
// TextureSet::~TextureSet: compiler-generated (array destructor of mTextures), emitted by DoFreeNode

// TextureSet::TextureSet(const TextureSet&): compiler-generated (array copy), emitted by DoAllocateNode

// ---- owner of the texture-set map ----
struct ResourceTypeID {
    uint32_t mLow : 8;
    uint32_t mGroup : 8;
    uint32_t mType : 8;
    uint32_t mPad : 6;
    uint32_t mFlags : 2;
};

inline ResourceTypeID MakeResourceTypeID(uint32_t type, uint32_t group)
{
    ResourceTypeID id;
    *(uint32_t*)&id = 0;
    id.mFlags = 1;
    id.mType = type;
    id.mGroup = group;
    return id;
}

struct cResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual RefCounted* GetResource(uint32_t instanceID, ResourceTypeID typeID, int flags);   // slot 8
    virtual void v9();
    virtual bool HasResource(uint32_t instanceID, ResourceTypeID typeID);                    // slot 10
};
cResourceManager* __cdecl ResourceManager();                     // 0x0067dd60
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, uint32_t flags);   // 0x00932e80
extern const char* const kTextureSuffixes[3];                    // 0x013f1870 ("-diffuse", ...)

struct TextureRegistry {
    void Find(uint32_t name, uint32_t a, int* pIndex, uint32_t b, uint32_t c, uint32_t d);   // 0x0050bff0
};
struct RegistryOwner { uint32_t pad[4]; TextureRegistry* mpRegistry; };   // +0x10
RegistryOwner* __cdecl GetRegistryOwner();                       // 0x00401080
inline RegistryOwner* RegistryOwnerInstance() { return GetRegistryOwner(); }
inline TextureRegistry* GetTextureRegistry() { return RegistryOwnerInstance()->mpRegistry; }

struct ResourceKey { uint32_t mInstance; uint32_t mType; uint32_t mGroup; };

struct TextureSink {
    void Add(const ResourceKey& key, TextureSet* pTextures, int index, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00512400
};

struct TextureCache {
    uint32_t pad0[2];
    TextureSink* mpSink;                    // +8
    uint32_t pad1[(0x3c - 0xc) / 4];
    eastl::fixed_hash_map mTextureSets;     // +0x3c

    void AddTextures(const ResourceKey& key, uint32_t name, uint32_t a, uint32_t b, uint32_t c, int index);
};

// @ 0x00506760 AddTextures
void TextureCache::AddTextures(const ResourceKey& key, uint32_t name, uint32_t a, uint32_t b, uint32_t c, int index)
{
    TextureRegistry* const pRegistry = GetTextureRegistry();
    if (index == -1)
        pRegistry->Find(name, 0, &index, 0, 0, 0);
    const uint32_t instanceID = key.mInstance;
    eastl::insert_return_type result;
    result = mTextureSets.insert(eastl::value_type(instanceID, TextureSet()));
    TextureSet* const pTextures = &result.mpNode->mValue.second;
    if (result.second == true) {
        cResourceManager* const pResourceManager = ResourceManager();
        for (int i = 0; i < 3; i++) {
            const uint32_t textureID = FNVHash(kTextureSuffixes[i], instanceID, 0);
            const ResourceTypeID typeID = MakeResourceTypeID(0x6a, 0x21);
            if (pResourceManager->HasResource(textureID, typeID))
                pTextures->mTextures[i] = pResourceManager->GetResource(textureID, typeID, 4);
        }
    }
    mpSink->Add(key, pTextures, index, name, a, b, c);
}

// ---- 0x00507380: constructor of a Simulator::cCreatureAbility-derived object ----
namespace Simulator {
struct cCreatureAbilityBase {
    virtual ~cCreatureAbilityBase();
    uint32_t mRefCount;                         // +4
    cCreatureAbilityBase() : mRefCount(0) {}
};
}

struct DefaultAllocator { DefaultAllocator() {} };

// 0x14-byte container whose base constructor is out of line
struct ListBase {
    uint32_t mData[5];
    ListBase(const DefaultAllocator& allocator);            // 0x00540470
};
struct List : ListBase {
    List(const DefaultAllocator& allocator = DefaultAllocator()) : ListBase(allocator) {}
};

// same layout, distinct allocator type (the original keeps this temp out of the shared temp area)
struct OtherAllocator { OtherAllocator() {} };
struct ListBase2 {
    uint32_t mData[5];
    ListBase2(const OtherAllocator& allocator);             // 0x00540470
};
struct List2 : ListBase2 {
    List2(const OtherAllocator& allocator = OtherAllocator()) : ListBase2(allocator) {}
};

struct BoundingBox {
    float mMin[3], mMax[3];
    void Reset();                                           // 0x00409c00
    BoundingBox() { Reset(); }
};

struct VectorAllocator {
    uint32_t mData[2];
    VectorAllocator(const DefaultAllocator& allocator);     // 0x00429360
};
struct Vector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VectorAllocator mAllocator;
    Vector(const DefaultAllocator& allocator = DefaultAllocator())
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
};

struct cAbilityData : Simulator::cCreatureAbilityBase {
    List mList0;   // +0x8
    List mList1;   // +0x1c
    List mList2;   // +0x30
    List mList3;   // +0x44
    List mList4;   // +0x58
    List mList5;   // +0x6c
    List mList6;   // +0x80
    List mList7;   // +0x94
    List mList8;   // +0xa8
    List mList9;   // +0xbc
    List2 mList10; // +0xd0
    List mList11;  // +0xe4
    List mList12;  // +0xf8
    uint32_t mUnk10c;         // +0x10c
    List mList13;  // +0x110
    List mList14;  // +0x124
    List mList15;  // +0x138
    BoundingBox mBounds;        // +0x14c
    uint32_t mCount;            // +0x164
    Vector mVecA;               // +0x168
    Vector mVecB;               // +0x17c
    Vector mVecC;               // +0x190
    List mListD;                // +0x1a4
    Vector mVecD;               // +0x1b8

    cAbilityData();
    virtual ~cAbilityData();
    void Init();                // 0x00508400
};

// @ 0x00507380 ??0cAbilityData
cAbilityData::cAbilityData()
    : mCount(0)
{
    Init();
}
