// Slice s004e2f20: EASTL template instantiations: hashtable node/bucket management for the
// fixed_hash_map<uint32_t, PartLayout>, Key->cSpeciesProfile* and uint32_t->cSpeciesArchetype maps,
// vector<AutoRefCount<T>>::DoInsertValue and vector<FunctionalMatch::Constraint> internals.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// Reproduces dead /Od stack slots left by inlined helpers whose locals the original never used.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

inline void* operator new(unsigned int, void* p) { return p; }

typedef char* va_list;
#define va_start(ap, v) (ap = (va_list)&v + ((sizeof(v) + 3) & ~3))
#define va_end(ap) (ap = (va_list)0)

void EASTLFree(void* p);                                                         // 0x00F47380
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
#pragma intrinsic(memcpy)

namespace EA {
template <class T> class RefCountTemplate {
public:
    virtual ~RefCountTemplate();
    int AddRef() { return mnRefCount++ + 1; }
    int Release();   // 0x00453540
    T mnRefCount;
};
template <class T> class AutoRefCount {
public:
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x);   // 0x004E4350
    T* mpObject;
};
namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator==(const Key& a, const Key& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
struct KeyHash { uint32_t operator()(const Key& k) const { return k.mInstance ^ k.mGroup; } };
} }
using EA::ResourceMan::Key;

namespace eastl {

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

template <class T> inline void destruct(T*, T*) {}   // trivial destructor: nothing to do
template <class T> inline T* copy_memcpy(T* first, T* last, T* result)
{
    return (T*)((last - first) * sizeof(T) + (char*)memcpy(result, first, (char*)last - (char*)first));
}
template <class T> inline T* uninitialized_copy_ptr(T* first, T* last, T* result)
{
    const bool bA = true;
    T* p = copy_memcpy(first, last, result);
    const bool bB = true;
    return p;
}

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValue(T* position, const T& value);
    void reserve(uint32_t n);
    void push_back(const T& value);
};

template <class T> struct equal_to { bool operator()(const T& a, const T& b) const { return a == b; } };
template <class T> struct hash { uint32_t operator()(T val) const { return (uint32_t)val; } };
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

template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
    hashtable_iterator& operator++() { this->increment(); return *this; }
};
// A const_iterator in the retail build has no user copy constructor (plain 8-byte copy on return).
template <class Node> struct hashtable_const_iterator : public hashtable_iterator_base<Node> {
    hashtable_const_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_const_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
};
template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b) { return a.mpNode != b.mpNode; }

template <class Node> struct insert_return_type {
    hashtable_iterator<Node> first;
    bool second;
};

struct allocator {
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};

// fixed_hash_map node pool
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
    // fixed_hash_map<uint32_t, PartLayout, 32, 33>: 32 nodes of 0x1C bytes
    __forceinline fixed_pool_with_overflow(void* pMemory) {
        mpHead = 0;
        init(pMemory, 0x380, 0x1c, 4, 0);
        mpPoolBegin = pMemory;
        mpCapacity = (char*)pMemory + 0x380;
        mnNodeSize = 0x1c;
    }
    void* allocate();   // 0x004CE850
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};
struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);
    void* allocate(uint32_t n, int flags = 0) {
        ScratchSlots<3>();
        if (n == 0x1c)   // sizeof(node_type)
            return mPool.allocate();
        return mpBucketBuffer;
    }
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

// @ 0x004E2F20 ??0fixed_hashtable_allocator@eastl@@QAE@ABU01@@Z
fixed_hashtable_allocator::fixed_hashtable_allocator(const fixed_hashtable_allocator& x)
    : mPool(x.mPool.mpHead), mpBucketBuffer(x.mpBucketBuffer)
{
}

void* allocate_memory(fixed_hashtable_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);  // 0x004E43C0
void* allocate_memory(allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);                  // 0x0042DEE0

template <class K, class V> struct pair {
    K first;
    V second;
    pair(const K& x, const V& y) : first(x), second(y) {}
};

template <class K, class V> struct hash_node {
    pair<K, V> mValue;
    hash_node* mpNext;
};

template <class K, class V, class H, class A> class hashtable {
public:
    typedef hash_node<K, V> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef hashtable_const_iterator<node_type> const_iterator;
    typedef pair<K, V> value_type;

    hashtable(uint32_t nBucketCount, const H& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to<K>& eq, const use_first<value_type>& ek, const A& allocator);
    ~hashtable();

    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const K& k);
    const_iterator find_const(const K& k);
    insert_return_type<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);
    iterator erase(iterator i);
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
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    void DoFreeNode(node_type* pNode) {
        pNode->~node_type();
        mAllocator.deallocate(pNode, sizeof(node_type));
    }
    node_type* DoAllocateNode(const value_type& value);
    void DoFreeNodes(node_type** pBucketArray, uint32_t n);
    node_type** DoAllocateBuckets(uint32_t n);
    void DoRehash(uint32_t nBucketCount);
    uint32_t get_hash_code(const K& key) const { return (uint32_t)m_h1(key); }
    uint32_t bucket_index(const K&, uint32_t c, uint32_t n) const { return (uint32_t)m_h2(c, n); }
    bool compare(const K& k, uint32_t, node_type* pNode) const { return m_equal(k, pNode->mValue.first); }
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (compare(k, c, pNode))
                return pNode;
        }
        return 0;
    }

    use_first<value_type> m_extract;   // 0x00
    equal_to<K> m_equal;               // 0x01
    H m_h1;                            // 0x02
    mod_range_hashing m_h2;            // 0x03
    node_type** mpBucketArray;         // 0x04
    uint32_t mnBucketCount;            // 0x08
    uint32_t mnElementCount;           // 0x0C
    prime_rehash_policy mRehashPolicy; // 0x10
    A mAllocator;                      // 0x1C
};

template <class K, class V, class H, class A>
typename hashtable<K, V, H, A>::iterator hashtable<K, V, H, A>::find(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}

template <class K, class V, class H, class A>
typename hashtable<K, V, H, A>::const_iterator hashtable<K, V, H, A>::find_const(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? const_iterator(pNode, mpBucketArray + n) : const_iterator(mpBucketArray + mnBucketCount);
}

template <class K, class V, class H, class A>
uint32_t hashtable<K, V, H, A>::erase(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    const uint32_t nElementCountSaved = mnElementCount;
    node_type** pBucketArray = mpBucketArray + n;
    while (*pBucketArray && !compare(k, c, *pBucketArray))
        pBucketArray = &(*pBucketArray)->mpNext;
    while (*pBucketArray && compare(k, c, *pBucketArray)) {
        node_type* const pNode = *pBucketArray;
        *pBucketArray = pNode->mpNext;
        DoFreeNode(pNode);
        --mnElementCount;
    }
    return nElementCountSaved - mnElementCount;
}

template <class K, class V, class H, class A>
typename hashtable<K, V, H, A>::iterator hashtable<K, V, H, A>::erase(iterator i)
{
    iterator iNext(i);
    ++iNext;
    node_type* pNode = i.mpNode;
    node_type* pNodeCurrent = *i.mpBucket;
    if (pNodeCurrent == pNode)
        *i.mpBucket = pNodeCurrent->mpNext;
    else {
        node_type* pNodeNext = pNodeCurrent->mpNext;
        while (pNodeNext != pNode) {
            pNodeCurrent = pNodeNext;
            pNodeNext = pNodeCurrent->mpNext;
        }
        pNodeCurrent->mpNext = pNodeNext->mpNext;
    }
    DoFreeNode(pNode);
    --mnElementCount;
    return iNext;
}

template <class K, class V, class H, class A>
hashtable<K, V, H, A>::hashtable(uint32_t nBucketCount, const H& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
                                 const equal_to<K>& eq, const use_first<value_type>& ek, const A& allocator)
    : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(allocator)
{
    if (nBucketCount < 2)
        reset();
    else {
        mnBucketCount = (uint32_t)mRehashPolicy.GetNextBucketCount((uint32_t)nBucketCount);
        mpBucketArray = DoAllocateBuckets(mnBucketCount);
    }
}

template <class K, class V, class H, class A>
hashtable<K, V, H, A>::~hashtable()
{
    clear();
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}

template <class K, class V, class H, class A>
void hashtable<K, V, H, A>::set_max_load_factor(float fMaxLoadFactor)
{
    hashtable* const pThis = this;
    pThis->rehash_policy(prime_rehash_policy(fMaxLoadFactor));
}

template <class K, class V, class H, class A> class hash_map : public hashtable<K, V, H, A> {
public:
    typedef hashtable<K, V, H, A> base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::value_type value_type;
    hash_map(uint32_t nBucketCount, const H& hashFunction, const equal_to<K>& predicate, const A& allocator)
        : base_type(nBucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), predicate,
                    use_first<value_type>(), allocator) {}
    V& operator[](const K& key);
};

// Dead slots of the inlined insert path (one more when mapped_type is a class).
template <class V> struct OperatorIndexSlots { enum { N = 13 }; };
template <class V> struct OperatorIndexSlots<V*> { enum { N = 12 }; };

template <class K, class V, class H, class A>
V& hash_map<K, V, H, A>::operator[](const K& key)
{
    ScratchSlots<OperatorIndexSlots<V>::N>();
    iterator it = base_type::find(key);
    if (it != base_type::end())
        return (*it.mpNode).mValue.second;
    return (*base_type::insert(value_type(key, V())).first.mpNode).mValue.second;
}


template <class K, class V, class H, class A>
typename hashtable<K, V, H, A>::node_type* hashtable<K, V, H, A>::DoAllocateNode(const value_type& value)
{
    node_type* const pNode = (node_type*)allocate_memory(mAllocator, sizeof(node_type), 4, 0);
    ::new (&pNode->mValue) value_type(value);
    pNode->mpNext = 0;
    return pNode;
}

// The fixed-pool DoFreeNode is an inline cl declines to expand in DoFreeNodes; its frame is still reserved.
template <class A> struct FreeNodeSlots { static void Reserve() {} };
template <> struct FreeNodeSlots<fixed_hashtable_allocator> { static void Reserve() { ScratchSlots<3>(); } };

template <class K, class V, class H, class A>
void hashtable<K, V, H, A>::DoFreeNodes(node_type** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        node_type* pNode = pNodeArray[i];
        while (pNode) {
            node_type* const pTempNode = pNode;
            pNode = pNode->mpNext;
            FreeNodeSlots<A>::Reserve();
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}

template <class K, class V, class H, class A>
void hashtable<K, V, H, A>::DoRehash(uint32_t nNewBucketCount)
{
    node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    node_type* pNode;
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        while ((pNode = mpBucketArray[i]) != 0) {
            const uint32_t nNewBucketIndex = (uint32_t)m_h2(m_h1(pNode->mValue.first), nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

} // namespace eastl

extern "C" void* __cdecl memset(void* p, int c, unsigned int n);
#pragma intrinsic(memset)

// Mapped types
struct PartLayout {   // 0x14-byte value of a fixed_hash_map<uint32_t, PartLayout, 32, 33>
    uint32_t mFields[3];
    float mScale;
    float mWeight;
    PartLayout() { mFields[0] = 0; mFields[1] = 0; mFields[2] = 0; mScale = 1.0f; mWeight = 1.0f; }
};

namespace SP {
class cSpeciesProfile;
class cSpeciesArchetype {
public:
    cSpeciesArchetype();                               // 0x004DA440
    cSpeciesArchetype(const cSpeciesArchetype& x);     // 0x004E1CB0
    ~cSpeciesArchetype();                              // 0x004DB1B0
    uint32_t mData[0x110];
};
class cEditorEvent : public EA::RefCountTemplate<int> {
public:
    uint32_t mSubType;
    uint32_t mType;
};
}

namespace eastl {
typedef hashtable<uint32_t, PartLayout, hash<uint32_t>, fixed_hashtable_allocator> PartLayoutTable;
typedef hashtable<Key, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash, allocator> SpeciesTable;
typedef hashtable<uint32_t, SP::cSpeciesArchetype, hash<uint32_t>, allocator> ArchetypeTable;

// The fixed-pool node free is not inlined into DoFreeNodes (0x004D0C20, shared by several maps).
template <> void PartLayoutTable::DoFreeNode(node_type* pNode);

// @ 0x004E3080 ?DoAllocateBuckets@?$hashtable@IUPartLayout@@
template <> PartLayoutTable::node_type** PartLayoutTable::DoAllocateBuckets(uint32_t n)
{
    node_type** const pBucketArray = (node_type**)mAllocator.allocate((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = (node_type*)(uint32_t)~0;
    return pBucketArray;
}

// @ 0x004E2F90 ?DoAllocateNode@?$hashtable@IUPartLayout@@
// @ 0x004E3010 ?DoFreeNodes@?$hashtable@IUPartLayout@@
// @ 0x004E30F0 ?DoRehash@?$hashtable@IUPartLayout@@
template PartLayoutTable::node_type* PartLayoutTable::DoAllocateNode(const value_type&);
template void PartLayoutTable::DoFreeNodes(node_type**, uint32_t);
template void PartLayoutTable::DoRehash(uint32_t);
// @ 0x004E3520 ?DoAllocateNode@?$hashtable@UKey@ResourceMan@EA@@
// @ 0x004E3590 ?DoFreeNodes@?$hashtable@UKey@ResourceMan@EA@@
// @ 0x004E3600 ?DoRehash@?$hashtable@UKey@ResourceMan@EA@@
template SpeciesTable::node_type* SpeciesTable::DoAllocateNode(const value_type&);
template void SpeciesTable::DoFreeNodes(node_type**, uint32_t);
template void SpeciesTable::DoRehash(uint32_t);
// @ 0x004E36E0 ?DoAllocateNode@?$hashtable@IVcSpeciesArchetype@SP@@
// @ 0x004E3760 ?DoFreeNodes@?$hashtable@IVcSpeciesArchetype@SP@@
// @ 0x004E37F0 ?DoRehash@?$hashtable@IVcSpeciesArchetype@SP@@
template ArchetypeTable::node_type* ArchetypeTable::DoAllocateNode(const value_type&);
template void ArchetypeTable::DoFreeNodes(node_type**, uint32_t);
template void ArchetypeTable::DoRehash(uint32_t);

// ---------------------------------------------------------------------------
// vector<AutoRefCount<T>>::DoInsertValue
// ---------------------------------------------------------------------------
template <class T> struct AutoRefVector : public vector<T> {
    uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    void DoInsertValue(T* position, const T& value);
};
template <class T> inline T* copy_backward_impl(T* first, T* last, T* resultEnd)
{
    ScratchSlots<2>();
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
template <class T> inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}

template <class T> void AutoRefVector<T>::DoInsertValue(T* position, const T& value)
{
    if (this->mpEnd != this->mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < this->mpEnd))
            ++pValue;
        ::new (this->mpEnd) T(*(this->mpEnd - 1));
        copy_backward(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
        ScratchSlots<2>();
    } else {
        const uint32_t nPrevSize = (uint32_t)(this->mpEnd - this->mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        T* const pNewData = this->DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_copy_ptr(this->mpBegin, position, pNewData);
        ::new (pNewEnd) T(value);
        pNewEnd = uninitialized_copy_ptr(position, this->mpEnd, ++pNewEnd);
        this->DoFree(this->mpBegin, (uint32_t)(this->mpCapacity - this->mpBegin));
        this->mpBegin = pNewData;
        this->mpEnd = pNewEnd;
        this->mpCapacity = pNewData + nNewSize;
    }
}
} // namespace eastl

namespace eastl {
// @ 0x004E3260 ?DoInsertValue@?$AutoRefVector@V?$AutoRefCount@VcEditorEvent@SP@@
template struct AutoRefVector<EA::AutoRefCount<SP::cEditorEvent> >;
}

// ---------------------------------------------------------------------------
// vector<FunctionalMatch::Constraint> internals
// ---------------------------------------------------------------------------
namespace SP { namespace FunctionalMatch { class Constraint; } }

namespace eastl {
struct false_type { false_type() {} };

template <class It> struct generic_iterator {
    It mIterator;
    generic_iterator(const It& x) : mIterator(x) {}
    It base() const { return mIterator; }
};

struct ConstraintAllocator {
    uint32_t mData[2];
    ConstraintAllocator() {}
    ConstraintAllocator(const ConstraintAllocator&) {}
};
void* allocate_memory(ConstraintAllocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x0042DEE0

typedef SP::FunctionalMatch::Constraint Constraint;

struct ConstraintVectorBase {
    Constraint* mpBegin;
    Constraint* mpEnd;
    Constraint* mpCapacity;
    ConstraintAllocator mAllocator;

    ConstraintVectorBase() {}
    ConstraintVectorBase(uint32_t n, const ConstraintAllocator& allocator);
    ~ConstraintVectorBase();   // 0x004AB0D0
    Constraint* DoAllocate(uint32_t n) { return n ? (Constraint*)allocate_memory(mAllocator, n * 0x24, 0, 0) : 0; }
    void DoFree(Constraint* p, uint32_t n) { if (p) deallocate(p, n * 0x24); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
};

struct ConstraintVector : public ConstraintVectorBase {   // eastl::vector<FunctionalMatch::Constraint>
    ConstraintVector(const ConstraintVector& x);
    ~ConstraintVector();                                       // 0x004E1780
    ConstraintVector& operator=(const ConstraintVector& x);    // 0x004E4410
    inline uint32_t size() const;
    uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    void DoDestroyValues(Constraint* first, Constraint* last);
    void DoInsertValue(Constraint* position, const Constraint& value);
};
} // namespace eastl

namespace SP { namespace FunctionalMatch {
class Constraint {
public:
    uint32_t mParameter;    // 0x00
    uint32_t mType;         // 0x04
    union {
        struct { int mMin, mMax; } mIntVal;
        struct { float mMin, mMax; } mFloatVal;
    };                      // 0x08
    eastl::ConstraintVector mSubConstraints;   // 0x10

    // Stand-in for the compiler-generated scalar deleting destructor (??_GConstraint, 0x004E4310) that
    // `p->~Constraint()` expands to; DoDestroyValues calls it out of line with flags 0.
    void* DestroyInPlace(unsigned int flags);
};
} }

namespace eastl {
inline uint32_t ConstraintVector::size() const { return (uint32_t)(mpEnd - mpBegin); }

generic_iterator<Constraint*> uninitialized_copy_impl(generic_iterator<Constraint*> first, generic_iterator<Constraint*> last,
                                                      generic_iterator<Constraint*> result, false_type);   // 0x004E4AD0
void uninitialized_fill_n_impl(generic_iterator<Constraint*> first, uint32_t n, const Constraint& value, false_type);  // 0x004E4700
Constraint* uninitialized_relocate_start(Constraint* first, Constraint* last, Constraint* dest);   // 0x004E4B90
template <> Constraint* copy_backward_impl(Constraint* first, Constraint* last, Constraint* resultEnd);   // 0x004E4F60

inline Constraint* uninitialized_copy_ptr(Constraint* first, Constraint* last, Constraint* result)
{
    false_type unusedTag;   // dead 1-byte slot in the original frame
    ScratchSlots<4>();
    const generic_iterator<Constraint*> i(uninitialized_copy_impl(generic_iterator<Constraint*>(first), generic_iterator<Constraint*>(last),
                                                                  generic_iterator<Constraint*>(result), false_type()));
    return i.base();
}

inline Constraint* uninitialized_relocate_commit_impl(Constraint* first, Constraint* last, Constraint* dest)
{
    ScratchSlots<5>();
    for (; first != last; ++first, ++dest)
        first->~Constraint();
    return dest;
}
inline Constraint* uninitialized_relocate_commit(Constraint* first, Constraint* last, Constraint* dest)
{
    const bool bHasTrivialRelocate = false;
    return uninitialized_relocate_commit_impl(first, last, dest);
}

// @ 0x004E3D90 ?uninitialized_relocate@eastl@@
Constraint* uninitialized_relocate(Constraint* first, Constraint* last, Constraint* dest)
{
    const bool bHasTrivialRelocate = false;
    Constraint* pResult = uninitialized_relocate_start(first, last, dest);
    ScratchSlots<10>();
    uninitialized_relocate_commit(first, last, dest);
    return pResult;
}

// @ 0x004E3D60 ?uninitialized_fill_n_ptr@eastl@@
void uninitialized_fill_n_ptr(Constraint* first, uint32_t n, const Constraint& value)
{
    false_type unusedTag;   // dead 1-byte slot in the original frame
    uninitialized_fill_n_impl(generic_iterator<Constraint*>(first), n, value, false_type());
}

// @ 0x004E3CF0 ??0ConstraintVectorBase@eastl@@QAE@IABUConstraintAllocator@1@@Z
ConstraintVectorBase::ConstraintVectorBase(uint32_t n, const ConstraintAllocator& allocator)
    : mAllocator(allocator)
{
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
}

// @ 0x004E38D0 ??0ConstraintVector@eastl@@QAE@ABU01@@Z
ConstraintVector::ConstraintVector(const ConstraintVector& x)
{
    const uint32_t n = x.size();
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, mpBegin);
}

// @ 0x004E39A0 ?DoDestroyValues@ConstraintVector@eastl@@
void ConstraintVector::DoDestroyValues(Constraint* first, Constraint* last)
{
    for (; first < last; ++first) {
        first->DestroyInPlace(0);   // first->~Constraint()
        ScratchSlots<4>();          // frame of the declined inline expansion
    }
}

// @ 0x004E39D0 ?DoInsertValue@ConstraintVector@eastl@@
void ConstraintVector::DoInsertValue(Constraint* position, const Constraint& value)
{
    if (mpEnd != mpCapacity) {
        const Constraint* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Constraint(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        Constraint* const pNewData = DoAllocate(nNewSize);
        Constraint* pNewEnd = uninitialized_relocate(mpBegin, position, pNewData);
        ::new (pNewEnd) Constraint(value);
        pNewEnd = uninitialized_relocate(position, mpEnd, ++pNewEnd);
        ScratchSlots<19>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
} // namespace eastl
#pragma pack(pop)
