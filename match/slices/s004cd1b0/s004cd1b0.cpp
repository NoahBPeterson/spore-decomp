// Slice s004cd1b0: EASTL template instantiations used by the creature-editor skin code
// (fixed_hash_map<uint32_t, ...> internals, vector resize/erase/push_back for several element types).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// Reproduces dead /Od stack slots left by inlined helpers whose locals the original never used.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

inline void* operator new(unsigned int, void* p) { return p; }

void EASTLFree(void* p);                                             // 0x00F47380
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset); // 0x0042DEE0

namespace eastl {

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

struct Vec4 { float x, y, z, w; };

// ---------------------------------------------------------------------------
// vector<T>: only what these instantiations need
// ---------------------------------------------------------------------------
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last);
    void DoInsertValues(T* position, uint32_t n, const T& value);
    void DoInsertValue(T* position, const T& value);
    void insert(T* position, uint32_t n, const T& value) { DoInsertValues(position, n, value); }
    void resize(uint32_t n);
    void resize(uint32_t n, const T& value);
    void push_back(const T& value);
    void push_back();
    void DoFree();
    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    ~vector();
};

// @ 0x004CD3C0 sym=?resize@?$vector@PAX@
template <> void vector<void*>::resize(uint32_t n)
{
    if (n > size())
        insert(mpEnd, n - size(), (void*)0);
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<4>();
}

template <class T1, class T2> struct pair {
    T1 first;
    T2 second;
    pair() : first(T1()), second(T2()) {}
};
typedef pair<int, int> IntFloat;   // pair of two 32-bit integers

// @ 0x004CD440 sym=?resize@?$vector@U?$pair@HH@
template <> void vector<IntFloat>::resize(uint32_t n)
{
    if (n > size())
        insert(mpEnd, n - size(), IntFloat());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<6>();
}

// 0x38-byte POD record
struct Rec38 {
    uint32_t data[14];
    Rec38() {}
    Rec38(const Rec38& x);                            // 0x0047BB70
};

// @ 0x004CD4C0 sym=?push_back@?$vector@URec38@
template <> void vector<Rec38>::push_back()
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Rec38;
    else
        DoInsertValue(mpEnd, Rec38());
}

// A fixed_vector<uint32_t, N> member inside a 0x34-byte element.
struct FixedU32Vector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    sp_vector_allocator mAllocator;
    FixedU32Vector();                                 // 0x004CE9D0
    ~FixedU32Vector() {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p)
            ;
        ScratchSlots<3>();
        DoFree();
    }
    void DoFree();                                    // 0x004C0B80
};

struct Elem34 {
    uint32_t mHeader[3];
    FixedU32Vector mValues;                           // 0x0C
    uint32_t mPad[5];
    Elem34() { ScratchSlots<3>(); }
    Elem34& operator=(const Elem34& x) { ScratchSlots<5>(); return Assign(x); }
    Elem34& Assign(const Elem34& x);                  // 0x004D1030
    static void operator delete(void* p) { EASTLFree(p); }
};

template <class T> __forceinline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

// @ 0x004CD530 sym=??1?$vector@UElem34@
template <> vector<Elem34>::~vector()
{
    destruct(mpBegin, mpEnd);
    ScratchSlots<3>();
    DoFree();
}

// @ 0x004CD5B0 sym=?resize@?$vector@UElem34@
template <> void vector<Elem34>::resize(uint32_t n)
{
    if (n > size())
        insert(mpEnd, n - size(), Elem34());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<17>();
}

// @ 0x004CD710 sym=?resize@?$vector@UVec4@
template <> void vector<Vec4>::resize(uint32_t n, const Vec4& value)
{
    if (n > size())
        insert(mpEnd, n - size(), value);
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<5>();
}

struct Word32 { uint32_t mValue; };   // 4-byte POD element

// @ 0x004CD790 sym=?resize@?$vector@UWord32@
template <> void vector<Word32>::resize(uint32_t n)
{
    if (n > size())
        insert(mpEnd, n - size(), Word32());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<6>();
}

// @ 0x004CD810 sym=?push_back@?$vector@M@
template <> void vector<float>::push_back(const float& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) float(value);
    else
        DoInsertValue(mpEnd, value);
}

// ---------------------------------------------------------------------------
// vector::erase / DoInsertValue
// ---------------------------------------------------------------------------
template <class In, class Out>
__forceinline Out copy_impl(In first, In last, Out result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

template <class In, class Out>
__forceinline Out copy(In first, In last, Out result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_impl(first, last, result);
}

Vec4* copy(Vec4* first, Vec4* last, Vec4* result);   // 0x00424770 (out of line)

// @ 0x004CE110 sym=?erase@?$vector@UElem34@
template <> Elem34* vector<Elem34>::erase(Elem34* first, Elem34* last)
{
    Elem34* const position = eastl::copy(last, mpEnd, first);
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x004CE200 sym=?erase@?$vector@UVec4@
template <> Vec4* vector<Vec4>::erase(Vec4* first, Vec4* last)
{
    Vec4* const position = eastl::copy(last, mpEnd, first);
    ScratchSlots<3>();
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x004CE270 sym=?erase@?$vector@UWord32@
template <> Word32* vector<Word32>::erase(Word32* first, Word32* last)
{
    Word32* const position = eastl::copy(last, mpEnd, first);
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

template <class Bi1, class Bi2>
__forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 result)
{
    while (last != first)
        *--result = *--last;
    return result;
}

template <class Bi1, class Bi2>
__forceinline Bi2 copy_backward(Bi1 first, Bi1 last, Bi2 result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, result);
}

Rec38* uninitialized_copy_ptr(Rec38* first, Rec38* last, Rec38* result);   // 0x004C1D80

// @ 0x004CDE80 sym=?DoInsertValue@?$vector@URec38@
template <> void vector<Rec38>::DoInsertValue(Rec38* position, const Rec38& value)
{
    if (mpEnd != mpCapacity) {
        const Rec38* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Rec38(*(mpEnd - 1));
        ScratchSlots<2>();
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = uint32_t(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Rec38* const pNewData = DoAllocate(nNewSize);
        Rec38* pNewEnd = eastl::uninitialized_copy_ptr(mpBegin, position, pNewData);
        ::new (pNewEnd) Rec38(value);
        pNewEnd = eastl::uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots<30>();   // eastl::destruct(mpBegin, mpEnd): trivial for Rec38
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// fixed_hash_map<uint32_t, MappedPair, 16 nodes, 17 buckets> internals
// ---------------------------------------------------------------------------
extern void* gpEmptyBucketArray[2];                  // 0x0154DF28

struct Link { Link* mpNext; };

struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};

struct fixed_pool_with_overflow : public fixed_pool_base {
    void* mpPoolBegin;
    void* mpCapacity;
    uint32_t mnNodeSize;
    __forceinline fixed_pool_with_overflow(void* pMemory) {
        mpHead = 0;
        init(pMemory, 0x100, 0x10, 4, 0);
        mpPoolBegin = pMemory;
        mpCapacity = (char*)pMemory + 0x100;
        mnNodeSize = 0x10;
    }
    void deallocate(void* p) {
        if ((p >= mpPoolBegin) && (p < mpCapacity)) {
            ((Link*)p)->mpNext = mpHead;
            mpHead = (Link*)p;
        } else
            OverflowFree(p, mnNodeSize);
    }
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};

struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    fixed_hashtable_allocator(void* pNodeBuffer, void* pBucketBuffer) : mPool(pNodeBuffer), mpBucketBuffer(pBucketBuffer) {}
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);
    void deallocate(void* p, uint32_t) {
        if (p != mpBucketBuffer) {
            if ((p >= mPool.mpPoolBegin) && (p < mPool.mpCapacity)) {
                ((Link*)p)->mpNext = mPool.mpHead;
                mPool.mpHead = (Link*)p;
            } else
                fixed_pool_with_overflow::OverflowFree(p, mPool.mnNodeSize);
        }
    }
};

// @ 0x004CDE10
fixed_hashtable_allocator::fixed_hashtable_allocator(const fixed_hashtable_allocator& x)
    : mPool(x.mPool.mpHead), mpBucketBuffer(x.mpBucketBuffer)
{
}

struct MappedPair {
    int mIndex;
    float mWeight;
    MappedPair() : mIndex(-1), mWeight(-1.0f) {}
};

struct HashNode {
    uint32_t mKey;
    MappedPair mValue;
    HashNode* mpNext;
};

template <class T> struct hash { uint32_t operator()(T val) const { return (uint32_t)val; } };
template <class T> struct equal_to { bool operator()(const T& a, const T& b) const { return a == b; } };
struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
struct default_ranged_hash {};
template <class P> struct use_first {};
struct true_type {};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy(float fMaxLoadFactor = 1.f) : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.f), mnNextResize(0) {}
    static uint32_t GetPrevBucketCountOnly(uint32_t nBucketCountHint);   // 0x00921340
    uint32_t GetNextBucketCount(uint32_t nBucketCountHint) const;        // 0x00921360
    uint32_t GetBucketCount(uint32_t nElementCount) const;               // 0x009213C0
};

struct hashtable_iterator_base {
    HashNode* mpNode;
    HashNode** mpBucket;
    hashtable_iterator_base(HashNode* pNode, HashNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};

struct hashtable_iterator : public hashtable_iterator_base {
    hashtable_iterator(HashNode* pNode = 0, HashNode** pBucket = 0) : hashtable_iterator_base(pNode, pBucket) {}
    hashtable_iterator(HashNode** pBucket) : hashtable_iterator_base(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base(x.mpNode, x.mpBucket) {}
    bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
};

struct insert_return_type {
    hashtable_iterator first;
    bool second;
};

struct value_pair {
    uint32_t first;
    MappedPair second;
    value_pair(const uint32_t& x, const MappedPair& y) : first(x), second(y) {}
};

class hashtable {
public:
    typedef hashtable_iterator iterator;

    hashtable(uint32_t nBucketCount, const hash<uint32_t>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to<uint32_t>& eq, const use_first<value_pair>& ek, const fixed_hashtable_allocator& allocator);
    ~hashtable();

    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const uint32_t& k);
    insert_return_type DoInsertValue(const value_pair& value, true_type);    // 0x004CDBD0
    insert_return_type insert(const value_pair& value) { return DoInsertValue(value, true_type()); }
    void set_max_load_factor(float fMaxLoadFactor);
    void rehash_policy(const prime_rehash_policy& rehashPolicy) {
        mRehashPolicy = rehashPolicy;
        const uint32_t nBuckets = rehashPolicy.GetBucketCount((uint32_t)mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }

    void reset() {
        ScratchSlots<1>();
        mnBucketCount = 1;
        mpBucketArray = (HashNode**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeBuckets(HashNode** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(HashNode*));
    }
    void DoFreeNodes(HashNode** pBucketArray, uint32_t n);   // 0x004D0430
    HashNode** DoAllocateBuckets(uint32_t n);                 // 0x004CE7E0
    void DoRehash(uint32_t nBucketCount);                     // 0x004CE8B0
    uint32_t get_hash_code(const uint32_t& key) const { return (uint32_t)m_h1(key); }
    uint32_t bucket_index(const uint32_t&, uint32_t c, uint32_t n) const { return (uint32_t)m_h2(c, n); }
    bool compare(const uint32_t& k, uint32_t, HashNode* pNode) const { return m_equal(k, pNode->mKey); }
    HashNode* DoFindNode(HashNode* pNode, const uint32_t& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (compare(k, c, pNode))
                return pNode;
        }
        return 0;
    }

    use_first<value_pair> m_extract;                 // 0x00 (hash_code_base: empty functors)
    equal_to<uint32_t> m_equal;                      // 0x01
    hash<uint32_t> m_h1;                             // 0x02
    mod_range_hashing m_h2;                          // 0x03
    HashNode** mpBucketArray;                        // 0x04
    uint32_t mnBucketCount;                          // 0x08
    uint32_t mnElementCount;                         // 0x0C
    prime_rehash_policy mRehashPolicy;               // 0x10
    fixed_hashtable_allocator mAllocator;            // 0x1C
};

// @ 0x004CD340 sym=?set_max_load_factor@hashtable@
void hashtable::set_max_load_factor(float fMaxLoadFactor)
{
    hashtable* const pThis = this;
    pThis->rehash_policy(prime_rehash_policy(fMaxLoadFactor));
}

// @ 0x004CD960 sym=??0hashtable@eastl@@
hashtable::hashtable(uint32_t nBucketCount, const hash<uint32_t>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
                     const equal_to<uint32_t>& eq, const use_first<value_pair>& ek, const fixed_hashtable_allocator& allocator)
    : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(allocator)
{
    if (nBucketCount < 2)
        reset();
    else {
        mnBucketCount = (uint32_t)mRehashPolicy.GetNextBucketCount((uint32_t)nBucketCount);
        mpBucketArray = DoAllocateBuckets(mnBucketCount);
    }
}

// @ 0x004CDA30 sym=??1hashtable@eastl@@
hashtable::~hashtable()
{
    clear();
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}

// @ 0x004CDAD0 sym=?find@hashtable@
hashtable::iterator hashtable::find(const uint32_t& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    HashNode* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}

class hash_map : public hashtable {
public:
    hash_map(uint32_t nBucketCount, const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate,
             const fixed_hashtable_allocator& allocator);
    MappedPair& operator[](const uint32_t& key);
};

// @ 0x004CD2F0 sym=??0hash_map@eastl@@
hash_map::hash_map(uint32_t nBucketCount, const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate,
                   const fixed_hashtable_allocator& allocator)
    : hashtable(nBucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), predicate,
                use_first<value_pair>(), allocator)
{
}

// @ 0x004CD240 sym=??Ahash_map@eastl@@
MappedPair& hash_map::operator[](const uint32_t& key)
{
    ScratchSlots<13>();   // frame of the out-of-line insert() helper, reserved ahead of the end() temps
    const iterator it = find(key);
    if (it != end())
        return (*it.mpNode).mValue;
    return (*insert(value_pair(key, MappedPair())).first.mpNode).mValue;
}

class fixed_hash_map : public hash_map {
public:
    fixed_hash_map(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate);
    void* mBucketBuffer[18];                         // 0x34
    char mNodeBuffer[0x100];                         // 0x7C
};

// @ 0x004CD1B0 sym=??0fixed_hash_map@eastl@@
fixed_hash_map::fixed_hash_map(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate)
    : hash_map(prime_rehash_policy::GetPrevBucketCountOnly(17), hashFunction, predicate,
               fixed_hashtable_allocator(mNodeBuffer, mBucketBuffer))
{
    ScratchSlots<6>();
    set_max_load_factor(10000.f);
}

// ---------------------------------------------------------------------------
// fixed_vector<uint8_t, N> destructor
// ---------------------------------------------------------------------------
struct fixed_vector_u8 {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    struct allocator {
        uint32_t mOverflow;
        void* mpPoolBegin;
        void deallocate(void* p, uint32_t n) {
            if (p != mpPoolBegin)
                EASTLFreeBlock(p, n);
        }
        static void EASTLFreeBlock(void* p, uint32_t) { void* pBlock = p; EASTLFree(pBlock); }
    } mAllocator;
    ~fixed_vector_u8();
};

// @ 0x004CD880 sym=??1fixed_vector_u8@eastl@@
fixed_vector_u8::~fixed_vector_u8()
{
    destruct(mpBegin, mpEnd);
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
}

} // namespace eastl

// ---------------------------------------------------------------------------
// Vertex buffer range lock helper
// ---------------------------------------------------------------------------
struct VertexDescriptor { uint8_t pad[0xF]; uint8_t mStride; };
extern VertexDescriptor* gpActiveVertexDescriptor;   // 0x016F65A0
void* LockVertexBuffer(uint32_t handle);             // 0x011FD7E0

struct VertexRange {
    uint32_t mIndex;
    uint8_t* mpCurrent;
    uint8_t* mpData;
};

// @ 0x004CDD70
int LockVertexRange(uint32_t handle, VertexRange* range)
{
    uint8_t* data = (uint8_t*)LockVertexBuffer(handle);
    if (data) {
        range->mpData = data;
        uint8_t stride = gpActiveVertexDescriptor->mStride;
        range->mpCurrent = stride * range->mIndex + range->mpData;
        return 1;
    }
    return 0;
}

#pragma pack(pop)
