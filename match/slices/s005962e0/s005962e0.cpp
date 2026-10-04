// slice s005962e0 — cCollectableItems queries (retail layout); shared EASTL subset (from slices s00593840/s00595320) — SP::cCollectableItems (retail layout) and the EASTL containers it instantiates:
// fixed_hash_map rehash/node allocation, hashtable find/insert, list<uint64>, serializer helpers.
#include "types.h"
#include <string.h>

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA { namespace IO {
class IStream;
bool ReadInt32(IStream* s, int32_t* p, uint32_t n, int endian);           // 0x0093A780
bool ReadUint64(IStream* s, uint64_t* p, uint32_t n, int endian);         // 0x0093A800
bool WriteUint32(IStream* s, const uint32_t* p, uint32_t n, int endian);  // 0x0093AA70
bool WriteUint64(IStream* s, const uint64_t* p, uint32_t n, int endian);  // 0x0093AB10
bool WriteBool8(IStream* s, const bool* p, uint32_t n);                   // 0x0093A9A0
}}

struct ItemId {   // two 32-bit halves of an item id; compared field-wise
    uint32_t lo, hi;
    bool operator==(const ItemId& x) const { return lo == x.lo && hi == x.hi; }
};
inline uint32_t HashOf(const ItemId& k) { return k.lo; }
inline uint32_t HashOf(uint32_t k) { return k; }
inline uint32_t HashOf(uint64_t k) { return (uint32_t)k; }

namespace eastl {

struct allocator {
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { operator delete[](p); }
};

struct ListNodeBase {
    ListNodeBase* mpNext;
    ListNodeBase* mpPrev;
    void insert(ListNodeBase* pNext)
    {
        mpNext = pNext;
        mpPrev = pNext->mpPrev;
        pNext->mpPrev->mpNext = this;
        pNext->mpPrev = this;
    }
    void remove()
    {
        mpPrev->mpNext = mpNext;
        mpNext->mpPrev = mpPrev;
    }
};

template <typename T>
struct ListNode : public ListNodeBase {
    T mValue;
};

template <typename T>
class list {
public:
    typedef ListNode<T> node_type;
    ListNodeBase mNode;
    allocator mAllocator;

    size_t size() const
    {
        size_t n = 0;
        for (const ListNodeBase* p = mNode.mpNext; p != &mNode; p = p->mpNext)
            ++n;
        return n;
    }
    void push_back(const T& value);
    void remove(const T& value);
    void clear()
    {
        node_type* p = (node_type*)mNode.mpNext;
        while (p != (node_type*)&mNode) {
            node_type* const pTemp = p;
            p = (node_type*)p->mpNext;
            mAllocator.deallocate(pTemp);
        }
        mNode.mpNext = &mNode;
        mNode.mpPrev = &mNode;
    }
    node_type* DoCreateNode(const T& value)
    {
        node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
        ::new (&pNode->mValue) T(value);
        return pNode;
    }
    void DoInsertValue(ListNodeBase* pNode, const T& value)
    {
        node_type* const pNodeNew = DoCreateNode(value);
        pNodeNew->insert(pNode);
    }
    void DoErase(ListNodeBase* pNode)
    {
        pNode->remove();
        mAllocator.deallocate(pNode);
    }
};

// see s00593840: 0x00594b10 ?push_back@
template <typename T>
void list<T>::push_back(const T& value)
{
    DoInsertValue(&mNode, value);
}

// see s00593840: 0x005945b0 ?remove@
template <typename T>
void list<T>::remove(const T& value)
{
    ListNodeBase* current = mNode.mpNext;
    while (current != &mNode) {
        if (!(((node_type*)current)->mValue == value))
            current = current->mpNext;
        else {
            current = current->mpNext;
            DoErase(current->mpPrev);
        }
    }
}

template <typename T, typename Node>
struct hashtable_iterator {
    Node*  mpNode;
    Node** mpBucket;
    hashtable_iterator() {}
    hashtable_iterator(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    explicit hashtable_iterator(Node** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    hashtable_iterator& operator++() { increment(); return *this; }
    bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
    bool operator==(const hashtable_iterator& x) const { return mpNode == x.mpNode; }
    T* operator->() const { return &mpNode->mValue; }
};

struct true_type {};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    struct RehashResult { bool first; uint32_t second; };
    RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);  // 0x00921440
};

// fixed_hashtable_allocator: node pool + embedded bucket buffer
struct fixed_hashtable_allocator {
    struct Link { Link* mpNext; };
    Link* mpHead;              // +0x00
    Link* mpNext;              // +0x04
    void* mpPoolBegin;         // +0x08
    void* mpCapacity;          // +0x0c
    size_t mnNodeSize;         // +0x10
    void* mpBucketBuffer;      // +0x14
    void* allocate(size_t)
    {
        Link* pLink = mpHead;
        if (pLink)
            mpHead = pLink->mpNext;
        else
            pLink = (Link*)operator new[](mnNodeSize, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
        return pLink;
    }
    void deallocate(void* p)
    {
        if (p != mpBucketBuffer) {
            if ((p >= mpPoolBegin) && (p < mpCapacity)) {
                ((Link*)p)->mpNext = mpHead;
                mpHead = (Link*)p;
            } else
                operator delete[](p);
        }
    }
};

template <typename K, typename V>
struct pair {
    K first;
    V second;
};

template <typename Value>
struct hash_node {
    Value mValue;
    hash_node* mpNext;
};

template <typename Value, typename Allocator, typename HashCode = uint32_t>
class hashtable {
public:
    typedef Value value_type;
    typedef hash_node<Value> node_type;
    typedef hashtable_iterator<Value, node_type> iterator;
    struct insert_return_type { iterator first; bool second; insert_return_type() {} insert_return_type(const iterator& i, bool b) : first(i), second(b) {} };

    uint32_t            mHashCodeBase;     // +0x00 (empty functor bases)
    node_type**         mpBucketArray;     // +0x04
    uint32_t            mnBucketCount;     // +0x08
    uint32_t            mnElementCount;    // +0x0c
    prime_rehash_policy mRehashPolicy;     // +0x10
    Allocator           mAllocator;        // +0x1c

    static uint32_t hash_of(const Value& v) { return HashOf(v.first); }

    iterator begin()
    {
        iterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }

    template <typename Key>
    __declspec(noinline) iterator find(const Key& k)
    {
        const uint32_t n = HashOf(k) % mnBucketCount;
        node_type* const pNode = DoFindNode(mpBucketArray[n], k);
        return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
    }
    template <typename Key>
    node_type* DoFindNode(node_type* pNode, const Key& k)
    {
        for (; pNode; pNode = pNode->mpNext) {
            if (k == pNode->mValue.first)
                return pNode;
        }
        return 0;
    }

    template <typename Mapped>
    Mapped& index(const uint64_t& k)
    {
        const iterator it = find(k);
        if (it != end())
            return (*it.operator->()).second;
        return (*DoInsertValue(value_type(k, Mapped()), true_type()).first.operator->()).second;
    }
    node_type** DoAllocateBuckets(uint32_t n);
    void DoFreeNodes(node_type** pBucketArray, uint32_t n);
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void reset_buckets()   // body of ~hashtable()
    {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n)
    {
        if (n > 1)
            mAllocator.deallocate(pBucketArray);
    }
    void DoRehash(uint32_t nNewBucketCount);
    node_type* DoAllocateNode(const Value& value);
    insert_return_type DoInsertValue(const Value& value, true_type);
};

template <typename Value, typename Allocator, typename HashCode>
void hashtable<Value, Allocator, HashCode>::DoRehash(uint32_t nNewBucketCount)
{
    node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        node_type* pNode;
        while ((pNode = mpBucketArray[i]) != 0) {
            const uint32_t nNewBucketIndex = hash_of(pNode->mValue) % nNewBucketCount;
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
}

template <typename Value, typename Allocator, typename HashCode>
typename hashtable<Value, Allocator, HashCode>::node_type*
hashtable<Value, Allocator, HashCode>::DoAllocateNode(const Value& value)
{
    node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
    ::new (&pNode->mValue) Value(value);
    pNode->mpNext = 0;
    return pNode;
}

template <typename Value, typename Allocator, typename HashCode>
typename hashtable<Value, Allocator, HashCode>::insert_return_type
hashtable<Value, Allocator, HashCode>::DoInsertValue(const Value& value, true_type)
{
    const uint32_t c = hash_of(value);
    uint32_t n = c % mnBucketCount;
    node_type* const pNode = DoFindNode(mpBucketArray[n], value.first);
    insert_return_type result;
    if (pNode == 0) {
        const prime_rehash_policy::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        node_type* const pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;
        result.first = iterator(pNodeNew, mpBucketArray + n);
        result.second = true;
        return result;
    }
    result.first = iterator(pNode, mpBucketArray + n);
    result.second = false;
    return result;
}

// Iterator distance (0x005939D0)
template <typename Iterator>
int distance(Iterator first, Iterator last)
{
    int n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template <typename T>
struct generic_iterator {
    T* mpNode;
    generic_iterator() {}
    explicit generic_iterator(T* p) : mpNode(p) {}
    generic_iterator& operator++() { ++mpNode; return *this; }
    T& operator*() const { return *mpNode; }
};

// see s00593840: 0x00594290 ??$fill_n@
template <typename OutputIterator, typename Size, typename T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value)
{
    for (; n-- > 0; ++first)
        *first = value;
    return first;
}

// (s00593840 note) 0x00594260: value halves loaded after the destination pointers (original loads value first)
// see s00593840: 0x00594260 ??$fill@
template <typename ForwardIterator, typename T>
inline void fill_imp(ForwardIterator first, ForwardIterator last, const T value)
{
    for (; first != last; ++first)
        *first = value;
}

template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
    fill_imp(first, last, value);
}

template <typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{
    if (first != last) {
        ForwardIterator i = first;
        for (++i; i != last; ++i) {
            if (*first == *i)
                return first;
            first = i;
        }
    }
    return last;
}

// (s00593840 note) 0x00593ba0: register assignment of first/last swapped in adjacent_find/unique
// see s00593840: 0x00593ba0 ??$unique@
template <typename ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last)
{
    first = adjacent_find(first, last);
    if (first != last) {
        ForwardIterator i(first);
        for (++i; i != last; ++i) {
            if (!(*first == *i))
                *++first = *i;
        }
        ++first;
    }
    return first;
}

// see s00593840: 0x00595000 ??$reverse_impl@
template <typename T>
inline void iter_swap(T* a, T* b)
{
    const T temp(*a);
    *a = *b;
    *b = temp;
}

template <typename T>
void reverse_impl(T* first, T* last)
{
    for (; first < --last; ++first)
        eastl::iter_swap(first, last);
}

} // namespace eastl

// ---------------------------------------------------------------------------------------------


namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
extern char    gEmptyString8[1];

template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };

template <typename T>
inline size_t CharStrlen(const T* p) { const T* q = p; while (*q) ++q; return (size_t)(q - p); }
template <>
inline size_t CharStrlen<char>(const char* p) { return strlen(p); }

template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}

template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string(const basic_string& x);
    struct CtorDoNotInitialize {};
    basic_string(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string() { DeallocateSelf(); }

    basic_string& operator=(const basic_string& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string& assign(const T* pBegin, const T* pEnd);
    basic_string& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};

typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

} // namespace eastl

// Typed value -> XML element writers
namespace EA {
eastl::string16 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
eastl::string16 ConvertToString16(const eastl::string& s);           // 0x0093C6D0
}

namespace SP {

class IXmlWriter {
public:
    virtual bool BeginElement(const wchar_t* name) = 0;
    virtual bool EndElement(const wchar_t* name) = 0;
    virtual bool WriteAttribute(const wchar_t* name, const wchar_t* value) = 0;
    virtual bool WriteCharacters(const wchar_t* text) = 0;
};

template <typename T>
struct cTypedValueToStringT {
    static bool sbWriteType;
    static void Write(eastl::string& out, const T& value);
};

template <typename T>
bool WriteTypedValue(IXmlWriter* writer, const char* name, const T& value, const wchar_t* typeName)
{
    bool result = true;
    eastl::string str;
    cTypedValueToStringT<T>::Write(str, value);
    if (!str.empty()) {
        eastl::string16 name16(name ? EA::ConvertToString16(name) : eastl::string16());
        eastl::string16 text(EA::ConvertToString16(str));
        const wchar_t* element = name16.empty() ? typeName : name16.c_str();
        if (writer->BeginElement(element) &&
            (name16.empty() || !cTypedValueToStringT<T>::sbWriteType || writer->WriteAttribute(L"type", typeName)) &&
            writer->WriteCharacters(text.c_str()) &&
            writer->EndElement(element))
            result = true;
        else
            result = false;
    }
    return result;
}



} // namespace SP

namespace EA { namespace IO {
bool ReadBool8(IStream* s, bool* p, uint32_t n);                          // 0x0093A6C0
}}

namespace eastl {
// fixed_vector<uint64_t, N> storage: begin/end/capacity, overflow allocator, pool begin.
template <typename T>
inline T* copy_backward(const T* first, const T* last, T* resultEnd)
{
    return (T*)memmove(resultEnd - (last - first), first, (size_t)((const char*)last - (const char*)first));
}

template <typename T>
struct fixed_vector_base {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mOverflowAllocator;
    void* mpPoolBegin;
    T* DoAllocate(size_t n) { return n ? (T*)mOverflowAllocator.allocate(n * sizeof(T)) : 0; }
    void DoFree(T* p) { if (p && p != mpPoolBegin) mOverflowAllocator.deallocate(p); }
    size_t GetNewCapacity(size_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    void DoInsertValue(T* position, const T& value);
    void clear() { erase(mpBegin, mpEnd); }
    T* erase(T* first, T* last)
    {
        T* const position = (T*)memcpy(first, last, (size_t)((char*)mpEnd - (char*)last)) ;
        mpEnd -= (last - first);
        return first;
    }
};

template <typename T>
void fixed_vector_base<T>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) T(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = GetNewCapacity(nPrevSize);
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = (T*)memcpy(pNewData, mpBegin, (size_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        ::new (pNewEnd) T(value);
        pNewEnd = (T*)memcpy(++pNewEnd, position, (size_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
} // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};
}

namespace SP {

class ISerializerStream {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5();
    virtual EA::IO::IStream* GetStream();
};

class ISerializer {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6();
    virtual void EndItem();                        // slot 7
    virtual ISerializerStream* GetStreamHolder();  // slot 8
};

typedef eastl::hashtable<eastl::pair<uint64_t, bool>, eastl::fixed_hashtable_allocator> ItemFlagMap;

// Static item info (mapped value of the 0x2C-byte nodes)
struct cStaticItemInfo {
    int   mRowIndex;        // -1
    float mFindChance;      // 0
    uint32_t mCategory;     // 0
    int   mLevel;           // -1
    int   mSetIndex;        // -1
    int   mSubCategory;     // (left uninitialised)
    uint32_t mFlags;        // 0
    cStaticItemInfo() : mRowIndex(-1), mFindChance(0.0f), mCategory(0), mLevel(-1), mSetIndex(-1), mFlags(0) {}
};

template <typename K, typename V>
struct map_pair {
    typedef V second_type;
    K first;
    V second;
    map_pair(const K& k, const V& v) : first(k), second(v) {}
};

typedef eastl::hashtable<map_pair<uint64_t, cStaticItemInfo>, eastl::fixed_hashtable_allocator> StaticInfoMap;
typedef eastl::hashtable<map_pair<uint64_t, uint8_t>, eastl::fixed_hashtable_allocator> ItemStatusMap;
typedef eastl::hashtable<map_pair<uint64_t, int>, eastl::fixed_hashtable_allocator> ItemLevelMap;
typedef eastl::hashtable<map_pair<uint64_t, uint64_t>, eastl::fixed_hashtable_allocator> ItemRowMap;



// ---------------------------------------------------------------------------------------------
struct cItemSetNode {      // rbtree node of map<uint64_t, vector<uint64_t>>
    cItemSetNode* mpNodeRight;
    cItemSetNode* mpNodeLeft;
    cItemSetNode* mpNodeParent;
    char mColor;
    uint64_t mKey;                                   // +0x10
    eastl::fixed_vector_base<uint64_t>* dummy_;      // (layout helper, unused)
};
struct cItemSetEntry {
    cItemSetNode* mpNodeRight;
    cItemSetNode* mpNodeLeft;
    cItemSetNode* mpNodeParent;
    char mColor;
    uint64_t mKey;          // +0x10
    uint64_t* mpBegin;      // +0x18
    uint64_t* mpEnd;        // +0x1c
    uint64_t* mpCapacity;   // +0x20
};
cItemSetEntry* RBTreeIncrement(const cItemSetEntry* pNode);   // 0x00921580

struct cItemSetTree {      // rbtree<uint64_t, pair<const uint64_t, vector<uint64_t>>> at +0x10
    uint32_t mCompare;
    struct { cItemSetEntry* mpNodeRight; cItemSetEntry* mpNodeLeft; cItemSetEntry* mpNodeParent; char mColor; } mAnchor;   // +0x4
    uint32_t mnSize;
    cItemSetEntry* end() { return (cItemSetEntry*)&mAnchor; }
    cItemSetEntry* begin() { return mAnchor.mpNodeLeft; }
    void find(cItemSetEntry** result, const uint64_t& key);   // 0x00A05730 (returns iterator)
};

template <typename T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    void DoInsertValue(T* position, const T& value);   // 0x004786E0 / 0x0060A600
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
};

// 8-element counting map used by GetMostCommonCategory (node {key, count, next})
struct CategoryCountMap {
    uint32_t mHashCodeBase;
    struct node_type { uint32_t first; int second; node_type* mpNext; };
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    float mfMaxLoadFactor, mfGrowthFactor; uint32_t mnNextResize;
    eastl::fixed_hashtable_allocator mAllocator;     // +0x1c
    void* mBucketBuffer[10];
    char mNodeBuffer[0x60 + 4];
    CategoryCountMap(const uint8_t& hashFunction, const uint8_t& predicate);   // 0x00596060
    int& operator[](const uint32_t& key);                                      // 0x00596130
    void DoFreeNodes(node_type** pBucketArray, uint32_t n);                    // 0x00A1B6C0
    ~CategoryCountMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            mAllocator.deallocate(mpBucketArray);
    }
};

struct cItemDataRow { char pad_0[0x84]; uint32_t mIdHigh; uint32_t mIdLow; };   // 0x8C bytes
class cItemDataTable {
public:
    char pad_0[0x98];
    cItemDataRow* mRowsBegin;   // +0x98
    cItemDataRow* mRowsEnd;     // +0x9c
};

uint64_t MakeItemId(uint32_t hi, uint32_t lo);
inline uint64_t MakeItemIdInline(uint32_t hi, uint32_t lo) { return ((uint64_t)hi << 32) | (uint64_t)lo; }

class cCollectableItems {
public:
    char pad_0[0x10];
    cItemSetTree mItemSets;               // +0x10
    char pad_28[0x148c - 0x10 - sizeof(cItemSetTree)];
    StaticInfoMap mStaticItemInfos;       // +0x148c
    char pad_14c0[0x4d00 - 0x148c - sizeof(StaticInfoMap)];
    ItemStatusMap mItemStatusInfos;       // +0x4d00
    char pad_4d3c[0x6d70 - 0x4d00 - sizeof(ItemStatusMap)];
    int mUnlockPoints;                    // +0x6d70
    char pad_6d74[0x6d80 - 0x6d74];
    eastl::list<ItemId> mNewItems;        // +0x6d80

    bool IsItemUnlocked(uint64_t id);                         // 0x00595110
    uint64_t GetItemCategory(uint64_t id);                    // 0x00595040
    int GetItems(sp_vector<uint64_t>& out, const bool* pUnlocked, const int* pRowIndex);
    bool CountSetItems(uint64_t setId, int* pUnlocked, int* pAvailable, int maxLevel, bool* pAllAtLevel);
    bool IsSetInState(uint64_t setId, int state, int maxLevel);
    void GetSets(eastl::fixed_vector_base<uint64_t>& out, int state, int maxLevel, cItemDataTable* table);
    void LockItem(uint64_t id);
    bool UnlockItem(uint64_t id, int cost);
    bool ResetItem(uint64_t id);
    uint32_t GetItemFlags(uint64_t id);
    uint32_t GetMostCommonNewCategory();
    void GetItemsInCategory(sp_vector<uint64_t>& out, uint32_t category);
    bool AreAllSetsLocked(int maxLevel);
    void LockItemsBeyond(int count);
};

typedef eastl::hashtable<eastl::pair<uint64_t, bool>, eastl::fixed_hashtable_allocator> ItemFlagMap;

// NM 0x005962e0: string temporaries/flag handling and stack layout differ
// @ 0x005962e0
bool WriteItemFlagMapXml(IXmlWriter* writer, const char* name, ItemFlagMap& map)
{
    bool ok = true;
    if (map.mnElementCount) {
        eastl::string16 name16(name ? EA::ConvertToString16(name) : eastl::string16((const wchar_t*)0));
        writer->BeginElement(name16.empty() ? L"hash_map" : name16.c_str());
        for (ItemFlagMap::iterator it = map.begin(), itEnd = map.end(); it != itEnd; ++it)
            ok = ok && WriteTypedValue<bool>(writer, 0, it->second, L"uint8_t");
        writer->EndElement(name16.empty() ? L"hash_map" : name16.c_str());
    }
    return ok;
}


} // namespace SP

namespace eastl {
template <typename T>
void fixed_vector_insert_n(fixed_vector_base<T>& v, T* position, size_t n, const T& value);
}

namespace SP {
// fixed_vector<uint64_t>::DoInsertValues(position, n, value)
struct fixed_vector_u64 : public eastl::fixed_vector_base<uint64_t> {
    void DoInsertValues(uint64_t* position, size_t n, const uint64_t& value);
    uint64_t* DoRealloc(size_t n, uint64_t* pBegin, uint64_t* pEnd);
};

} // namespace SP
namespace eastl {
template <typename T>
inline generic_iterator<T> uninitialized_fill_n_ptr(T* first, size_t n, const T& value)
{
    return fill_n(generic_iterator<T>(first), n, value);
}
}
namespace SP {

// NM 0x005966e0: insert-n paths: register allocation and helper inlining differ
// @ 0x005966e0
void fixed_vector_u64::DoInsertValues(uint64_t* position, size_t n, const uint64_t& value)
{
    if (n <= (size_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const uint64_t temp = value;
            const size_t nExtra = (size_t)(mpEnd - position);
            uint64_t* const pPrevEnd = mpEnd;
            if (n < nExtra) {
                memcpy(mpEnd, mpEnd - n, n * sizeof(uint64_t));
                mpEnd += n;
                eastl::copy_backward(position, pPrevEnd - n, pPrevEnd);
                eastl::fill(position, position + n, temp);
            } else {
                eastl::uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                memcpy(mpEnd, position, (size_t)((char*)pPrevEnd - (char*)position));
                mpEnd += nExtra;
                eastl::fill(position, pPrevEnd, temp);
            }
        }
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const size_t nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        uint64_t* const pNewData = DoAllocate(nNewSize);
        uint64_t* pNewEnd = (uint64_t*)memcpy(pNewData, mpBegin, (size_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd += n;
        pNewEnd = (uint64_t*)memcpy(pNewEnd, position, (size_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x005968b0
uint64_t* fixed_vector_u64::DoRealloc(size_t n, uint64_t* pBegin, uint64_t* pEnd)
{
    uint64_t* const p = n ? (uint64_t*)mOverflowAllocator.allocate(n * sizeof(uint64_t)) : 0;
    memcpy(p, pBegin, (size_t)((char*)pEnd - (char*)pBegin));
    return p;
}

// NM 0x00596900: vector clear and filter branch layout differ
// @ 0x00596900
int cCollectableItems::GetItems(sp_vector<uint64_t>& out, const bool* pUnlocked, const int* pRowIndex)
{
    out.mpEnd = out.mpBegin + 0;
    { uint64_t* e = out.mpEnd; memcpy(out.mpBegin, e, 0); out.mpEnd -= (e - out.mpBegin); }
    for (StaticInfoMap::iterator it = mStaticItemInfos.begin(), itEnd = mStaticItemInfos.end(); it != itEnd; ++it) {
        uint64_t id = it->first;
        if (pUnlocked) {
            ItemStatusMap::iterator st = mItemStatusInfos.find(id);
            const bool unlocked = (st != mItemStatusInfos.end()) ? ((st->second & 1) != 0) : false;
            if (*pUnlocked != unlocked)
                continue;
        }
        if (pRowIndex && it->second.mRowIndex != *pRowIndex)
            continue;
        out.push_back(it->first);
    }
    return (int)out.size();
}

// NM 0x00596a30: visibility test and counter pointer handling differ
// @ 0x00596a30
bool cCollectableItems::CountSetItems(uint64_t setId, int* pUnlocked, int* pAvailable, int maxLevel, bool* pAllAtLevel)
{
    if (((uint32_t)setId & (uint32_t)(setId >> 32)) == 0xFFFFFFFF)
        return false;
    cItemSetEntry* node;
    mItemSets.find(&node, setId);
    if (node == mItemSets.end())
        return false;
    const int count = (int)(node->mpEnd - node->mpBegin);
    if (count <= 0)
        return false;
    for (int i = 0; i < count; ++i) {
        const uint64_t item = node->mpBegin[i];
        cStaticItemInfo& info = mStaticItemInfos.index<cStaticItemInfo>(item);
        if (IsItemUnlocked(item)) {
            ++*pUnlocked;
            continue;
        }
        ItemStatusMap::iterator st = mItemStatusInfos.find(item);
        if (st != mItemStatusInfos.end() && !((st->second >> 2) & 1) == false)
            continue;
        if (st != mItemStatusInfos.end()) {
            const int level = info.mRowIndex;
            if (level < maxLevel || maxLevel == -1) {
                if (pAllAtLevel)
                    *pAllAtLevel &= (maxLevel != -1 && level == maxLevel - 1);
                ++*pAvailable;
            }
        }
    }
    return true;
}

// @ 0x00596b70
bool cCollectableItems::IsSetInState(uint64_t setId, int state, int maxLevel)
{
    int unlocked = 0;
    int available = 0;
    CountSetItems(setId, &unlocked, &available, maxLevel, 0);
    if (available > 0 && (state == 2 || (unlocked > 0) == (state == 1)))
        return true;
    return false;
}

// NM 0x00596be0: push_back/unique-erase register allocation differs
// @ 0x00596be0
void cCollectableItems::GetSets(eastl::fixed_vector_base<uint64_t>& out, int state, int maxLevel, cItemDataTable* table)
{
    if (table) {
        const uint32_t count = (uint32_t)(table->mRowsEnd - table->mRowsBegin);
        for (uint32_t i = 0; i < count; ++i) {
            const cItemDataRow& row = table->mRowsBegin[i];
            uint64_t setId = GetItemCategory(MakeItemIdInline(row.mIdHigh, row.mIdLow));
            if (IsSetInState(setId, state, maxLevel)) {
                if (out.mpEnd < out.mpCapacity)
                    ::new (out.mpEnd++) uint64_t(setId);
                else
                    out.DoInsertValue(out.mpEnd, setId);
            }
        }
        out.erase((uint64_t*)eastl::unique((ItemId*)out.mpBegin, (ItemId*)out.mpEnd), out.mpEnd);
    } else {
        for (cItemSetEntry* node = mItemSets.begin(); node != mItemSets.end(); node = RBTreeIncrement(node)) {
            uint64_t setId = node->mKey;
            if (IsSetInState(setId, state, maxLevel)) {
                if (out.mpEnd < out.mpCapacity)
                    ::new (out.mpEnd++) uint64_t(setId);
                else
                    out.DoInsertValue(out.mpEnd, setId);
            }
        }
    }
}

// @ 0x00596d70
void cCollectableItems::LockItem(uint64_t id)
{
    mItemStatusInfos.index<uint8_t>(id) = 4;
    mNewItems.remove(*(ItemId*)&id);
}

// @ 0x00596da0
bool cCollectableItems::UnlockItem(uint64_t id, int cost)
{
    if (!IsItemUnlocked(id)) {
        const int points = mUnlockPoints - cost;
        if (!cost || points >= 0) {
            mUnlockPoints = points;
            mItemStatusInfos.index<uint8_t>(id) |= 3;
            mNewItems.push_back(*(ItemId*)&id);
            return true;
        }
    }
    return false;
}

// @ 0x00596e10
bool cCollectableItems::ResetItem(uint64_t id)
{
    mItemStatusInfos.index<uint8_t>(id) &= ~3;
    mNewItems.remove(*(ItemId*)&id);
    return true;
}

// @ 0x00596e40
uint32_t cCollectableItems::GetItemFlags(uint64_t id)
{
    return mStaticItemInfos.index<cStaticItemInfo>(id).mFlags;
}

// NM 0x00596e60: counting-map iteration register allocation differs
// @ 0x00596e60
uint32_t cCollectableItems::GetMostCommonNewCategory()
{
    uint8_t hashFunction, predicate;
    CategoryCountMap counts(predicate, hashFunction);
    for (StaticInfoMap::iterator it = mStaticItemInfos.begin(), itEnd = mStaticItemInfos.end(); it != itEnd; ++it) {
        uint64_t id = it->first;
        ItemStatusMap::iterator st = mItemStatusInfos.find(id);
        if (st != mItemStatusInfos.end() && (st->second & 2))
            ++counts[it->second.mCategory];
    }
    int best = 0;
    uint32_t bestCategory = 0;
    for (uint32_t b = 0; b < counts.mnBucketCount; ++b) {}
    {
        CategoryCountMap::node_type** pBucket = counts.mpBucketArray;
        CategoryCountMap::node_type* pNode = *pBucket;
        if (!pNode) { ++pBucket; while (!*pBucket) ++pBucket; pNode = *pBucket; }
        CategoryCountMap::node_type* const pEnd = counts.mpBucketArray[counts.mnBucketCount];
        while (pNode != pEnd) {
            if (pNode->second > best) {
                bestCategory = pNode->first;
                best = pNode->second;
            }
            pNode = pNode->mpNext;
            while (!pNode) pNode = *++pBucket;
        }
    }
    return bestCategory;
}

// NM 0x00596fc0: category compare reloads argument each iteration in original
// @ 0x00596fc0
void cCollectableItems::GetItemsInCategory(sp_vector<uint64_t>& out, uint32_t category)
{
    for (StaticInfoMap::iterator it = mStaticItemInfos.begin(), itEnd = mStaticItemInfos.end(); it != itEnd; ++it) {
        uint64_t id = it->first;
        if (it->second.mCategory == category)
            out.push_back(id);
    }
}

// NM 0x00597060: local slot layout of the two counters differs
// @ 0x00597060
bool cCollectableItems::AreAllSetsLocked(int maxLevel)
{
    cItemSetEntry* const end = mItemSets.end();
    for (cItemSetEntry* node = mItemSets.begin(); node != end; node = RBTreeIncrement(node)) {
        int available = 0;
        int unlocked = 0;
        CountSetItems(node->mKey, &unlocked, &available, maxLevel, 0);
        if (available > 0)
            return false;
    }
    return true;
}

// NM 0x005970d0: aligned frame (and esp,-8) and inlined operator[] differ
// @ 0x005970d0
void cCollectableItems::LockItemsBeyond(int count)
{
    if (count > 0) {
        for (cItemSetEntry* node = mItemSets.begin(); node != mItemSets.end(); node = RBTreeIncrement(node)) {
            const int n = (int)(node->mpEnd - node->mpBegin);
            int kept = 0;
            for (int i = 0; i < n; ++i) {
                const uint64_t& item = node->mpBegin[i];
                ItemStatusMap::iterator it = mItemStatusInfos.find(item);
                if (it == mItemStatusInfos.end())
                    it = mItemStatusInfos.DoInsertValue(ItemStatusMap::value_type(item, 0), eastl::true_type()).first;
                uint8_t& flags = it->second;
                if (!(flags & 1)) {
                    if (kept < count) {
                        ++kept;
                        flags = 0;
                    } else
                        flags = 4;
                }
            }
        }
    } else {
        for (ItemStatusMap::iterator it = mItemStatusInfos.begin(), itEnd = mItemStatusInfos.end(); it != itEnd; ++it) {
            if (!(it->second & 1))
                it->second = 4;
        }
    }
}

} // namespace SP

// @ 0x005965b0 ?push_back@?$sp_vector@PAX
template void SP::sp_vector<void*>::push_back(void* const&);
// PARTIAL 0x005965e0: fixed_hash_map copy constructor not reconstructed (base ctor + range insert); stub only
// @ 0x005965e0 ?CopyConstructStub
void CopyConstructStub() {}
