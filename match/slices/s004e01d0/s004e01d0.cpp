// Slice s004e01d0: EASTL hash_map / vector template instantiations used by SP::cSPEditorSpeciesManager
// and the editor (fixed_hash_map<uint32_t, ...> internals, Key->cSpeciesProfile* map, AutoRefCount vectors).
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
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};
struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    fixed_hashtable_allocator(void* pNodeBuffer, uint32_t nodeBufferSize, uint32_t nodeSize, void* pBucketBuffer) {
        mPool.mpHead = 0;
        mPool.init(pNodeBuffer, nodeBufferSize, nodeSize, 4, 0);
        mPool.mpPoolBegin = pNodeBuffer;
        mPool.mpCapacity = (char*)pNodeBuffer + nodeBufferSize;
        mPool.mnNodeSize = nodeSize;
        mpBucketBuffer = pBucketBuffer;
    }
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);   // 0x004E2F20
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
    void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode, sizeof(node_type)); }
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

} // namespace eastl

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
class cTextureInstance;
class cEditorEvent : public EA::RefCountTemplate<int> {
public:
    uint32_t mSubType;   // 0x08
    uint32_t mType;      // 0x0C
    uint32_t pad10[0x29];
    uint32_t mValue;     // 0xB4
};
}

namespace eastl {
typedef hashtable<uint32_t, PartLayout, hash<uint32_t>, fixed_hashtable_allocator> PartLayoutTable;
typedef hash_map<uint32_t, PartLayout, hash<uint32_t>, fixed_hashtable_allocator> PartLayoutMap;
typedef hash_map<Key, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash, allocator> SpeciesMap;
typedef hash_map<uint32_t, SP::cSpeciesArchetype, hash<uint32_t>, allocator> ArchetypeMap;

class fixed_hash_map_PartLayout : public PartLayoutMap {
public:
    fixed_hash_map_PartLayout(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate);
    void* mBucketBuffer[34];          // 0x34
    char mNodeBuffer[0x380];          // 0xBC
};
}

// @ 0x004E0370 ??0fixed_hash_map_PartLayout@eastl@@
eastl::fixed_hash_map_PartLayout::fixed_hash_map_PartLayout(const hash<uint32_t>& hashFunction, const equal_to<uint32_t>& predicate)
    : PartLayoutMap(prime_rehash_policy::GetPrevBucketCountOnly(33), hashFunction, predicate,
                    fixed_hashtable_allocator(mNodeBuffer, 0x380, 0x1c, mBucketBuffer))
{
    ScratchSlots<5>();
    set_max_load_factor(10000.f);
}

namespace eastl {
// @ 0x004E0400 ??A?$hash_map@IUPartLayout@@
// @ 0x004E0700 ??0?$hash_map@IUPartLayout@@
template class hash_map<uint32_t, PartLayout, hash<uint32_t>, fixed_hashtable_allocator>;
// @ 0x004E0750 ?set_max_load_factor@?$hashtable@IUPartLayout@@
// @ 0x004E0990 ??0?$hashtable@IUPartLayout@@
// @ 0x004E0A60 ??1?$hashtable@IUPartLayout@@
// @ 0x004E0B00 ?find_const@?$hashtable@IUPartLayout@@
// @ 0x004E0BE0 ?find@?$hashtable@IUPartLayout@@
template class hashtable<uint32_t, PartLayout, hash<uint32_t>, fixed_hashtable_allocator>;
// @ 0x004E0560 ??A?$hash_map@UKey@ResourceMan@EA@@
template class hash_map<Key, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash, allocator>;
// @ 0x004E0F80 ?find@?$hashtable@UKey@ResourceMan@EA@@
// @ 0x004E10A0 ?erase@?$hashtable@UKey@ResourceMan@EA@@PAVcSpeciesProfile@SP@@UKeyHash@23@Uallocator@eastl@@@eastl@@QAEIABUKey@
// @ 0x004E11E0 ?erase@?$hashtable@UKey@ResourceMan@EA@@PAVcSpeciesProfile@SP@@UKeyHash@23@Uallocator@eastl@@@eastl@@QAE?AU?$hashtable_iterator
template class hashtable<Key, SP::cSpeciesProfile*, EA::ResourceMan::KeyHash, allocator>;
// @ 0x004E0600 ??A?$hash_map@IVcSpeciesArchetype@SP@@
template class hash_map<uint32_t, SP::cSpeciesArchetype, hash<uint32_t>, allocator>;
}

// vector<AutoRefCount<T>>
template <class T> void eastl::vector<T>::push_back(const T& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) T(value);
    else
        DoInsertValue(mpEnd, value);
}

template <class T> void eastl::vector<T>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

// @ 0x004E0880 ?reserve@?$vector@V?$AutoRefCount@VcTextureInstance@SP@@
template void eastl::vector<EA::AutoRefCount<SP::cTextureInstance> >::reserve(uint32_t);
// @ 0x004E0E80 ?push_back@?$vector@V?$AutoRefCount@VcEditorEvent@SP@@
template void eastl::vector<EA::AutoRefCount<SP::cEditorEvent> >::push_back(const EA::AutoRefCount<SP::cEditorEvent>&);

// ---------------------------------------------------------------------------
namespace SP {
class cEditorEventQueue {
public:
    void QueueEvent(cEditorEvent* pEvent);
    uint32_t pad0[0x544 / 4];
    uint32_t mLastValue;                                          // 0x544
    uint32_t pad548[(0x6D4 - 0x548) / 4];
    eastl::vector<EA::AutoRefCount<cEditorEvent> > mEvents;       // 0x6D4
    uint32_t pad6E8[(0x73C - 0x6E8) / 4];
    eastl::vector<EA::AutoRefCount<cEditorEvent> > mLateEvents;   // 0x73C
};

// @ 0x004E01D0 ?QueueEvent@cEditorEventQueue@SP@@
void cEditorEventQueue::QueueEvent(cEditorEvent* pEvent)
{
    switch (pEvent->mType) {
    case 0: {
        EA::AutoRefCount<cEditorEvent> ref(pEvent);
        ScratchSlots<6>();
        mEvents.push_back(ref);
        break;
    }
    case 1: {
        EA::AutoRefCount<cEditorEvent> ref(pEvent);
        ScratchSlots<6>();
        mEvents.push_back(ref);
        break;
    }
    case 2: {
        if (pEvent->mSubType == 0xe)
            mLastValue = pEvent->mValue;
        EA::AutoRefCount<cEditorEvent> ref(pEvent);
        ScratchSlots<3>();
        mEvents.push_back(ref);
        break;
    }
    case 3: {
        EA::AutoRefCount<cEditorEvent> ref(pEvent);
        ScratchSlots<2>();
        mLateEvents.push_back(ref);
        break;
    }
    }
}

class string {
public:
    string& sprintf(const char* pFormat, ...);
    void sprintf_va_list(const char* pFormat, va_list arguments);   // 0x004234B0
};

// @ 0x004E0850 ?sprintf@string@SP@@
string& string::sprintf(const char* pFormat, ...)
{
    va_list arguments;
    va_start(arguments, pFormat);
    sprintf_va_list(pFormat, arguments);
    va_end(arguments);
    return *this;
}
} // namespace SP
#pragma pack(pop)
