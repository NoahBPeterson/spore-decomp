// Slice s00553cc0: EASTL template instances used by SP::Pollen (cAssetDirectory / cAssetMetadata):
// vector<string>/vector<string16> members, string16 trim, vector_set<uint32_t>, hashtable node/bucket helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);

namespace EA {
namespace Allocator {
class ZoneObject {
public:
    virtual ~ZoneObject();
    static void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0);  // 0x00926020
    static void operator delete(void* p);
};
}
namespace Thread {
template <class T> class AtomicInt {
public:
    AtomicInt(T x = 0) { SetValue(x); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
    volatile T mValue;
};
struct MutexParameters;
class Mutex {
public:
    Mutex(const MutexParameters* pParameters = 0, bool bDefaultParameters = true);   // 0x009222A0
    ~Mutex();                                                                          // 0x00922130
    int Lock(const void* pTimeoutAbsolute);                                            // 0x009221B0
    int Unlock();                                                                      // 0x00922270
    uint32_t mData[0x30 / 4];
};
}
template <class T, class C, int B> class RefCounted : public T {
public:
    RefCounted() : mRefCount(0) {}
    virtual int AddRef();
    virtual int Release();
    C mRefCount;
};
class Stopwatch {
public:
    Stopwatch(int units, bool bStartImmediately = false);   // 0x0093A560
    static uint64_t GetStopwatchCycle() {
        int64_t nReturnValue;
        QueryPerformanceCounter(&nReturnValue);
        const uint64_t nCycle = (uint64_t)nReturnValue;
        return nCycle;
    }
    bool IsRunning() const { return mnStartTime != 0; }
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
};
class LimitStopwatch : public Stopwatch {
public:
    LimitStopwatch(int units, uint32_t nLimit = 0, bool bStartImmediately = false) : Stopwatch(units, false) {
        SetTimeLimit(nLimit, bStartImmediately);
    }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);   // 0x0093A480
    bool IsTimeUp() const { return (int64_t)(mnEndTime - GetStopwatchCycle()) < 0; }
    uint64_t mnEndTime;
};
namespace Messaging {
class IHandler {
public:
    virtual ~IHandler() {}
    virtual bool HandleMessage(uint32_t messageId, void* pMessage) = 0;
};
class IServer {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void AddHandler(IHandler* pHandler, uint32_t messageId);                     // 0x24
    virtual void v10();
    virtual void RemoveHandler(IHandler* pHandler, uint32_t messageId, int priority);    // 0x2c
};
IServer* GetServer();   // 0x00883860
}
namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator==(const Key& a, const Key& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
struct ResourceKey : public Key {
    ResourceKey(uint64_t instance, uint32_t type, uint32_t group) { mInstance = (uint32_t)instance; mType = type; mGroup = group; }
};
class ResourceObject {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void* Cast(uint32_t typeId);
};
template <class T> class ResourcePtr {
public:
    ResourcePtr() : mpObject(0) {}
    ~ResourcePtr() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* mpObject;
};
class Factory : public RefCounted<Allocator::ZoneObject, Thread::AtomicInt<int>, 1> {
public:
    virtual uint32_t GetSupportedTypes(uint32_t* pTypes, uint32_t count) const = 0;
};
class IResourceManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key& key, ResourceObject** ppResource, int, int, int, int);   // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void RegisterFactory(bool bRegister, Factory* pFactory, uint32_t group);  // 0x44
};
IResourceManager* GetManager();   // 0x0067DCD0
}
}
using EA::ResourceMan::Key;

namespace eastl {
void EASTLFree(void* p);   // 0x00F47380
}
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00F473A0
namespace eastl {
struct allocator {
    allocator() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("EASTL", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
void* allocate_memory(allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x0042DEE0
extern "C" void* memset(void* p, int c, unsigned int n);
template <class T> struct equal_to { equal_to() {} bool operator()(const T& a, const T& b) const { return a == b; } };
template <class T> struct hash { uint32_t operator()(T val) const { return (uint32_t)val; } };
template <> struct hash<Key> { uint32_t operator()(const Key& k) const { return k.mInstance ^ k.mGroup; } };
template <class P> struct use_first { const typename P::first_type& operator()(const P& x) const { return x.first; } };
template <class K> struct use_self { const K& operator()(const K& x) const { return x; } };
struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
struct default_ranged_hash {};
struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
struct true_type {};

template <class V> struct hash_node {
    V mValue;
    hash_node* mpNext;
};
template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base<Node>(x.mpNode, x.mpBucket) {}
};
template <class Node> struct hashtable_const_iterator : public hashtable_iterator_base<Node> {
    hashtable_const_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_const_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
};
template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b) { return a.mpNode != b.mpNode; }
template <class Node> struct insert_return_type {
    hashtable_iterator<Node> first;
    bool second;
};

template <class T1, class T2> struct pair {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
    template <class U, class V> pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
};
template <class T1, class T2> inline pair<T1, T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }

template <class K, class V, class EK> class hashtable {
public:
    typedef V value_type;
    typedef hash_node<V> node_type;
    typedef hashtable_iterator<node_type> iterator;
    typedef hashtable_const_iterator<node_type> const_iterator;
    hashtable(uint32_t nBucketCount, const hash<K>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to<K>& eq, const EK& ek, const allocator& a);
    ~hashtable() {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode, sizeof(node_type)); }
    node_type* DoAllocateNode(const value_type& value) {
        node_type* const pNode = (node_type*)allocate_memory(mAllocator, sizeof(node_type), __alignof(V), 0);
        ::new (&pNode->mValue) value_type(value);
        pNode->mpNext = 0;
        return pNode;
    }
    node_type** DoAllocateBuckets(uint32_t n);
    uint32_t bucket_index(const node_type* pNode, uint32_t nBucketCount) const {
        return m_h2((uint32_t)m_h1(m_extract(pNode->mValue)), nBucketCount);
    }
    void DoRehash(uint32_t nNewBucketCount) {
        node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
        node_type* pNode;
        for (uint32_t i = 0; i < mnBucketCount; ++i) {
            while ((pNode = mpBucketArray[i]) != 0) {
                const uint32_t nNewBucketIndex = (uint32_t)bucket_index(pNode, nNewBucketCount);
                mpBucketArray[i] = pNode->mpNext;
                pNode->mpNext = pBucketArray[nNewBucketIndex];
                pBucketArray[nNewBucketIndex] = pNode;
            }
        }
        DoFreeBuckets(mpBucketArray, mnBucketCount);
        mnBucketCount = nNewBucketCount;
        mpBucketArray = pBucketArray;
    }
    void DoFreeNodes(node_type** pNodeArray, uint32_t n);
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    const_iterator end() const { return const_iterator(mpBucketArray + mnBucketCount); }
    const_iterator find(const K& k) const {
        const uint32_t c = (uint32_t)m_h1(k);
        const uint32_t n = c % mnBucketCount;
        node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? const_iterator(pNode, mpBucketArray + n) : const_iterator(mpBucketArray + mnBucketCount);
    }
    iterator find(const K& k) {
        const uint32_t c = (uint32_t)m_h1(k);
        const uint32_t n = c % mnBucketCount;
        node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
    }
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (m_equal(k, m_extract(pNode->mValue)))
                return pNode;
        }
        return 0;
    }
    insert_return_type<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);

    EK m_extract;
    equal_to<K> m_equal;
    hash<K> m_h1;
    mod_range_hashing m_h2;
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    allocator mAllocator;
};
template <class K, class T> class hash_map : public hashtable<K, pair<const K, T>, use_first<pair<const K, T> > > {
public:
    typedef hashtable<K, pair<const K, T>, use_first<pair<const K, T> > > base_type;
    typedef pair<const K, T> value_type;
    explicit hash_map(const allocator& a = allocator())
        : base_type(0, hash<K>(), mod_range_hashing(), default_ranged_hash(), equal_to<K>(), use_first<value_type>(), a) {}
    typedef typename base_type::iterator iterator;
    T& operator[](const K& key) {
        iterator itHashtable(base_type::find(key));
        if (itHashtable != base_type::end())
            return itHashtable.mpNode->mValue.second;
        return base_type::insert(value_type(key, T())).first.mpNode->mValue.second;
    }
};
template <class K> class hash_set : public hashtable<K, K, use_self<K> > {
public:
    explicit hash_set(const allocator& a = allocator())
        : hashtable<K, K, use_self<K> >(0, hash<K>(), mod_range_hashing(), default_ranged_hash(), equal_to<K>(), use_self<K>(), a) {}
};
}

namespace eastl {
template <class K, class V, class EK>
typename hashtable<K, V, EK>::node_type** hashtable<K, V, EK>::DoAllocateBuckets(uint32_t n)
{
    node_type** const pBucketArray = (node_type**)mAllocator.allocate((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = reinterpret_cast<node_type*>((uint32_t)~0);
    return pBucketArray;
}

template <class K, class V, class EK>
void hashtable<K, V, EK>::DoFreeNodes(node_type** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        node_type* pNode = pNodeArray[i];
        while (pNode) {
            node_type* const pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}
}
extern "C" unsigned int strlen(const char*);
extern "C" int memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(strlen, memcmp)

namespace EA { namespace DateTime {
class DateTime {
public:
    DateTime(int timeFrame) { Set(timeFrame); }
    void Set(int timeFrame);   // 0x0092E3D0
    int64_t mnSeconds;
};
} }

namespace eastl {
extern wchar_t gEmptyString;   // 0x01667BAC
template <class T> struct char_traits_len;
template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    enum { npos = 0xFFFFFFFF };
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    void AllocateSelf() {
        mpBegin = (T*)&gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    static uint32_t CharStrlen(const wchar_t* p) {
        const wchar_t* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        ScratchSlots<2>();
        return (uint32_t)(pCurrent - p);
    }
    uint32_t find_first_not_of(const T* p, uint32_t position, uint32_t n) const;   // 0x00547900
    uint32_t find_last_not_of(const T* p, uint32_t position, uint32_t n) const;    // 0x00547970
    uint32_t find_first_not_of(const T* p, uint32_t position = 0) const { return find_first_not_of(p, position, (uint32_t)CharStrlen(p)); }
    uint32_t find_last_not_of(const T* p, uint32_t position = npos) const { return find_last_not_of(p, position, (uint32_t)CharStrlen(p)); }
    basic_string& erase(uint32_t position = 0, uint32_t n = npos);                  // 0x004228E0
    void ltrim() {
        const T array[] = { ' ', '\t', 0 };
        erase(0, find_first_not_of(array));
    }
    void rtrim() {
        const T array[] = { ' ', '\t', 0 };
        erase(find_last_not_of(array) + 1);
    }
    basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string() { DeallocateSelf(); }
    static uint32_t CharStrlen(const char* p) { return strlen(p); }
    void RangeInitialize(const T* pBegin, const T* pEnd);   // 0x0047D390
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, uint32_t n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    const T* data() const { return mpBegin; }
    const T* c_str() const { return mpBegin; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    basic_string& operator=(const basic_string& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    basic_string& assign(const T* p, uint32_t n) { return assign(p, p + n); }
    T* erase(T* pBegin, T* pEnd);                            // 0x0042E2F0
    basic_string& append(uint32_t n, T c);                   // 0x0042D2E0
    void resize(uint32_t n, T c);
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

// 0x00554FB0
template <class T> inline bool operator==(const basic_string<T>& a, const basic_string<T>& b)
{
    return ((a.size() == b.size()) && (memcmp(a.data(), b.data(), (unsigned int)a.size()) == 0));
}
template <class T> bool operator==(const basic_string<T>& a, const T* p);   // 0x00555020

template <class InputIterator, class OutputIterator>
inline OutputIterator copy_impl(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
template <class BidirectionalIterator1, class BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward_impl(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
template <class BidirectionalIterator1, class BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 resultEnd)
{
    const bool elem = false;
    const bool h = false;
    const bool p33 = false;
    return copy_backward_impl(first, last, resultEnd);
}
template <class T> struct iterator_value;
template <class T> struct iterator_value<T*> { typedef T type; };
extern "C" void* memmove(void* dst, const void* src, unsigned int n);
// Trivially copyable element types are moved with memmove (0x011E0744, a direct call).
template <class T> struct has_trivial_assign { enum { value = 0 }; };
template <> struct has_trivial_assign<uint32_t> { enum { value = 1 }; };
template <bool bTrivial> struct copy_chooser {
    template <class InputIterator, class OutputIterator>
    static OutputIterator do_copy(InputIterator first, InputIterator last, OutputIterator result) { return copy_impl(first, last, result); }
};
template <> struct copy_chooser<true> {
    template <class T>
    static T* do_copy(const T* first, const T* last, T* result) {
        memmove(result, first, (unsigned int)((const char*)last - (const char*)first));
        return result + (last - first);
    }
};
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    // (local names chosen to reproduce the /Od slot order)
    const bool elem = false;
    const bool h = false;
    const bool p33 = has_trivial_assign<typename iterator_value<OutputIterator>::type>::value != 0;
    return copy_chooser<has_trivial_assign<typename iterator_value<OutputIterator>::type>::value != 0>::do_copy(first, last, result);
}

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    static void FreeBlock(void* p) { void* const pMemory = p; EASTLFree(pMemory); }
    void deallocate(void* p, uint32_t) {
        if (*((uint32_t*)p - 1))
            FreeBlock(p);
    }
};
// Allocator of vector_set's underlying vector (8 bytes, no block header).
struct vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
template <class A> inline void EASTLFreeN(A& a, void* p, uint32_t n) { a.deallocate(p, n); }

template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class T, class A> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    ~VectorBase() {
        if (mpBegin)
            EASTLFreeN(mAllocator, mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(T));
    }
    T* DoAllocate(uint32_t n) { return n ? (T*)allocate_memory(*(allocator*)&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t n) {
        if (p)
            EASTLFreeN(mAllocator, p, n * sizeof(T));
    }
};

// Moves [first, last) into raw memory at dest and destroys the sources.
template <class T> T* uninitialized_relocate_ptr(T* first, T* last, T* dest);   // 0x005554E0 (string)

template <class T, class A = sp_vector_allocator> struct vector : public VectorBase<T, A> {
    typedef VectorBase<T, A> base_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T value_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    ~vector() { eastl::destruct(mpBegin, mpEnd); }
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    const_iterator begin() const { return mpBegin; }
    const_iterator end() const { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void resize(uint32_t n) {
        if (n > (uint32_t)(mpEnd - mpBegin))
            insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }
    void insert(iterator position, uint32_t n, const value_type& value) { ScratchSlots<1>(); DoInsertValues(position, n, value); }
    void DoInsertValues(iterator position, uint32_t n, const value_type& value);   // 0x00555540
    void DoInsertValue(iterator position, const value_type& value);
    uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    iterator erase(iterator position) {
        if ((position + 1) < mpEnd)
            eastl::copy(position + 1, mpEnd, position);
        --mpEnd;
        mpEnd->~T();
        return position;
    }
    iterator erase(iterator first, iterator last) {
        iterator const position = eastl::copy(last, mpEnd, first);
        eastl::destruct(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

template <class T, class A>
void vector<T, A>::DoInsertValue(iterator position, const value_type& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) value_type(*(mpEnd - 1));
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        T* const pNewData = base_type::DoAllocate(nNewSize);
        ScratchSlots<20>();
        T* pNewEnd = eastl::uninitialized_relocate_ptr(mpBegin, position, pNewData);
        ::new (pNewEnd) value_type(value);
        pNewEnd = eastl::uninitialized_relocate_ptr(position, mpEnd, ++pNewEnd);
        base_type::DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

template <class T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
template <class T1, class T2> struct pair2 { T1 first; T2 second; };

template <class ForwardIterator, class T, class Compare>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare);   // 0x00555A20

template <class Key, class Compare = less<Key> >
struct vector_set : public vector<Key, vector_allocator> {
    typedef vector<Key, vector_allocator> base_type;
    typedef Key* iterator;
    typedef Key value_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    Compare mCompare;   // 0x14

    pair<iterator, bool> insert(const value_type& value) {
        const iterator itLB(eastl::lower_bound(base_type::begin(), base_type::end(), value, mCompare));
        if ((itLB != base_type::end()) && !mCompare(value, *itLB))
            return pair<iterator, bool>(itLB, false);
        ScratchSlots<3>();
        return pair<iterator, bool>(insert(itLB, value), true);
    }
    iterator insert(iterator position, const value_type& value);    // 0x00554F20
    pair<iterator, iterator> equal_range(const Key& k);             // 0x00555980
    iterator find(const Key& k) {
        ScratchSlots<5>();   // dead slots of the declined inline equal_range
        const pair<iterator, iterator> pairIts(equal_range(k));
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    uint32_t erase(const Key& k) {
        const iterator it(find(k));
        if (it != base_type::end()) {
            base_type::erase(it);
            return 1;
        }
        return 0;
    }
};

template <class InputIterator, class T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

}

// ---------------------------------------------------------------------------------------------
// @ 0x00553CC0 vector<string>::push_back
// @ 0x00553D60 vector<string>::erase(iterator)
// @ 0x00554760 vector<string>::erase(iterator, iterator)
// @ 0x00554820 vector<string>::DoInsertValue
template struct eastl::vector<eastl::string>;
// @ 0x00553E00 vector<string16>::~vector
// @ 0x00553E60 vector<string16>::resize
// @ 0x00553F10 vector<string16>::push_back
// @ 0x00554B60 vector<string16>::erase(iterator, iterator)
template struct eastl::vector<eastl::string16>;
// @ 0x00554B10 VectorBase<string16>::~VectorBase
template struct eastl::VectorBase<eastl::string16, eastl::sp_vector_allocator>;
// @ 0x00553FB0 vector<uint32_t>::~vector
template struct eastl::vector<uint32_t, eastl::vector_allocator>;
// @ 0x00554020 vector_set<uint32_t>::insert(const value_type&)
// @ 0x005540D0 vector_set<uint32_t>::erase(const key_type&)
template struct eastl::vector_set<uint32_t>;
// @ 0x00554170 string16::ltrim
// @ 0x005541E0 string16::rtrim
template void eastl::basic_string<wchar_t>::ltrim();
template void eastl::basic_string<wchar_t>::rtrim();
// @ 0x00554250 hashtable<uint64_t, Key>::DoAllocateNode
// @ 0x005542D0 hashtable<uint64_t, Key>::DoRehash
// @ 0x005543A0 hashtable<uint64_t, Key>::DoFreeNodes
// @ 0x00554410 hashtable<uint64_t, Key>::DoAllocateBuckets
template class eastl::hashtable<uint64_t, eastl::pair<const uint64_t, Key>, eastl::use_first<eastl::pair<const uint64_t, Key> > >;
// @ 0x00554480 hashtable<Key, uint64_t>::DoRehash
template class eastl::hashtable<Key, eastl::pair<const Key, uint64_t>, eastl::use_first<eastl::pair<const Key, uint64_t> > >;
// @ 0x00554560 hashtable<uint64_t> (hash_set)::DoAllocateNode
template class eastl::hashtable<uint64_t, uint64_t, eastl::use_self<uint64_t> >;
