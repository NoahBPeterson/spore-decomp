// slice s00597230 — cCollectableItems unlock logic, construction/destruction and container helpers (retail layout); shared EASTL subset (from slices s00593840/s00595320) — SP::cCollectableItems (retail layout) and the EASTL containers it instantiates:
// fixed_hash_map rehash/node allocation, hashtable find/insert, list<uint64>, serializer helpers.
#include "types.h"
#include <string.h>

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void  operator delete[](void* p); // 0x00f47380
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



struct cItemSetEntry {
    cItemSetEntry* mpNodeRight;
    cItemSetEntry* mpNodeLeft;
    cItemSetEntry* mpNodeParent;
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
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};


struct cItemDataRow { char pad_0[0x84]; uint32_t mIdHigh; uint32_t mIdLow; };   // 0x8C bytes
inline uint64_t MakeItemIdInline(uint32_t hi, uint32_t lo) { return ((uint64_t)hi << 32) | (uint64_t)lo; }

// ---------------------------------------------------------------------------------------------
// map<uint64_t, fixed_vector<uint64_t,4>> with a fixed node pool (rbtree at cCollectableItems+0x10)
struct cItemSetValue {
    uint64_t first;                      // +0x10 in node
    struct fixed_vec4 {
        uint64_t* mpBegin;               // +0x18
        uint64_t* mpEnd;
        uint64_t* mpCapacity;
        eastl::allocator mOverflowAllocator;
        uint64_t* mpPoolBegin;           // +0x28
        uint64_t mBuffer[4];             // +0x30
        fixed_vec4() { mpBegin = mpEnd = mpPoolBegin = mBuffer; mpCapacity = mBuffer + 4; }
        ~fixed_vec4() { if (mpBegin && mpBegin != mpPoolBegin) mOverflowAllocator.deallocate(mpBegin); }
        void DoAssignFromIterator(const uint64_t* first, const uint64_t* last, const void* tag);   // 0x005972F0
    } second;
    cItemSetValue(const cItemSetValue& x) : first(x.first), second()
    {
        second.DoAssignFromIterator(x.second.mpBegin, x.second.mpEnd, &x);
    }
};
struct cItemSetTreeNode {
    cItemSetTreeNode* mpNodeRight;
    cItemSetTreeNode* mpNodeLeft;
    cItemSetTreeNode* mpNodeParent;
    char mColor;
    cItemSetValue mValue;                // +0x10
};
void RBTreeInsert(cItemSetTreeNode* pNode, cItemSetTreeNode* pNodeParent, void* pNodeAnchor, int insertionSide);   // 0x009216A0

struct cItemSetIterator {
    cItemSetTreeNode* mpNode;
    explicit cItemSetIterator(cItemSetTreeNode* p) : mpNode(p) {}
};

struct cItemSetRBTree {
    uint32_t mCompare;                                       // +0x0
    struct { cItemSetTreeNode* mpNodeRight; cItemSetTreeNode* mpNodeLeft; cItemSetTreeNode* mpNodeParent; char mColor; } mAnchor;   // +0x4
    uint32_t mnSize;                                         // +0x14
    struct pool_t { void* mpHead; void* mpNext; void* mpPoolBegin; void* mpCapacity; uint32_t mnNodeSize; } mAllocator;   // +0x18
    void DoNukeSubtree(cItemSetTreeNode* pNode);
    cItemSetTreeNode* DoCreateNode(const cItemSetValue& value);
    cItemSetIterator DoInsertValueImpl(cItemSetTreeNode* pNodeParent, const cItemSetValue& value, bool bForceToLeft);
    void DoFreeNode(cItemSetTreeNode* pNode)
    {
        pNode->mValue.second.~fixed_vec4();
        if (pNode >= mAllocator.mpPoolBegin && pNode < mAllocator.mpCapacity) {
            *(void**)pNode = mAllocator.mpHead;
            mAllocator.mpHead = pNode;
        } else
            operator delete[](pNode);
    }
};

// @ 0x00597230
void cItemSetRBTree::DoNukeSubtree(cItemSetTreeNode* pNode)
{
    while (pNode) {
        DoNukeSubtree(pNode->mpNodeRight);
        cItemSetTreeNode* const pNodeLeft = pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// NM 0x00598260: pool-pop and value copy-construction scheduling differ
// @ 0x00598260 ?DoCreateNode@cItemSetRBTree
cItemSetTreeNode* cItemSetRBTree::DoCreateNode(const cItemSetValue& value)
{
    cItemSetTreeNode* pNode = (cItemSetTreeNode*)mAllocator.mpHead;
    if (pNode)
        mAllocator.mpHead = *(void**)pNode;
    else
        pNode = (cItemSetTreeNode*)operator new[](mAllocator.mnNodeSize, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    ::new (&pNode->mValue) cItemSetValue(value);
    return pNode;
}

// @ 0x005982e0
cItemSetIterator cItemSetRBTree::DoInsertValueImpl(cItemSetTreeNode* pNodeParent, const cItemSetValue& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (cItemSetTreeNode*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    cItemSetTreeNode* const pNodeNew = DoCreateNode(value);
    RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return cItemSetIterator(pNodeNew);
}

// fixed_hash_map<uint32_t, uint64_t, 4> used as the mapped type of the summary map
struct SetBitsMap {
    uint32_t mHashCodeBase;
    struct node_type { uint32_t first; uint32_t pad; uint64_t second; node_type* mpNext; };
    node_type** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    float mfMaxLoadFactor, mfGrowthFactor; uint32_t mnNextResize;
    eastl::fixed_hashtable_allocator mAllocator;      // +0x1c
    char mStorage[0xdc - 0x34];
    SetBitsMap(const uint8_t& hashFunction, const uint8_t& predicate);   // 0x005961E0
    SetBitsMap(const SetBitsMap& x);                                     // 0x005965E0
    void DoFreeNodes(node_type** p, uint32_t n);                         // 0x005941F0
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n)
    {
        if (n > 1)
            mAllocator.deallocate(pBucketArray);
    }
    struct insert_return_type { node_type* mpNode; node_type** mpBucket; bool second; };
    insert_return_type DoInsertValue(const node_type& value, bool tag);  // 0x00594E20
    ~SetBitsMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    node_type* find_node(uint32_t k, node_type*** ppBucket)
    {
        const uint32_t n = k % mnBucketCount;
        for (node_type* p = mpBucketArray[n]; p; p = p->mpNext)
            if (k == p->first) { *ppBucket = mpBucketArray + n; return p; }
        *ppBucket = mpBucketArray + mnBucketCount;
        return *ppBucket[0];
    }
};

// hash_map<uint32_t, SetBitsMap> (node: key, map at +4, next at +0xE0)
struct SummaryValue {
    uint32_t first;
    SetBitsMap second;
    SummaryValue(uint32_t k, const SetBitsMap& m) : first(k), second(m) {}
};
struct SummaryNode { SummaryValue mValue; SummaryNode* mpNext; };
struct SummaryMap {
    uint32_t mHashCodeBase;
    SummaryNode** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    float mfMaxLoadFactor, mfGrowthFactor; uint32_t mnNextResize;
    eastl::fixed_hashtable_allocator mAllocator;      // +0x1c
    SummaryNode* DoAllocateNode(const SummaryValue& value);
    void DoFreeNode(SummaryNode* pNode);
    void DoFreeNodes(SummaryNode** pBucketArray, uint32_t n);
    SetBitsMap& operator[](const uint32_t& key);
    void find(SummaryNode** result, const uint32_t& key);                                 // 0x00594EE0
    struct insert_return_type { SummaryNode* mpNode; SummaryNode** mpBucket; bool second; };
    insert_return_type DoInsertValue(const SummaryValue& value, bool tag);               // 0x00597590
};

// NM 0x00597290: value copy uses edx instead of ecx for the key
// @ 0x00597290
SummaryNode* SummaryMap::DoAllocateNode(const SummaryValue& value)
{
    SummaryNode* const pNode = (SummaryNode*)mAllocator.allocate(sizeof(SummaryNode));
    ::new (&pNode->mValue) SummaryValue(value);
    pNode->mpNext = 0;
    return pNode;
}

// @ 0x00597650
void SummaryMap::DoFreeNode(SummaryNode* pNode)
{
    pNode->mValue.~SummaryValue();
    mAllocator.deallocate(pNode);
}

// @ 0x00597b30
void SummaryMap::DoFreeNodes(SummaryNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        SummaryNode* pNode = pNodeArray[i];
        while (pNode) {
            SummaryNode* const pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}

// NM 0x00597d00: temporary fixed_hash_map construction/destruction order differs
// @ 0x00597d00
SetBitsMap& SummaryMap::operator[](const uint32_t& key)
{
    SummaryNode* it;
    find(&it, key);
    if (it != mpBucketArray[mnBucketCount])
        return it->mValue.second;
    uint8_t hashFunction, predicate;
    insert_return_type result = DoInsertValue(SummaryValue(key, SetBitsMap(predicate, hashFunction)), false);
    return result.mpNode->mValue.second;
}

// fixed_vector<uint64_t> helpers
struct fixed_vector_u64 : public eastl::fixed_vector_base<uint64_t> {
    void DoInsertValues(uint64_t* position, size_t n, const uint64_t& value);   // 0x005966E0
    void resize(size_t n, const uint64_t& value);
};

// @ 0x00597530
void fixed_vector_u64::resize(size_t n, const uint64_t& value)
{
    if (n > (size_t)(mpEnd - mpBegin))
        DoInsertValues(mpEnd, n - (size_t)(mpEnd - mpBegin), value);
    else
        erase(mpBegin + n, mpEnd);
}

class cItemDataResource {
public:
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x98 - 4];
    cItemDataRow* mRowsBegin;   // +0x98
    cItemDataRow* mRowsEnd;     // +0x9c
};
void GetItemDataResource(const void* key, cItemDataResource** ppResource);   // 0x004BAFC0

struct RandomLinearCongruential { uint32_t RandomUint32Uniform(uint32_t nLimit); };   // 0x00A68FB0
extern RandomLinearCongruential sMathRandom;                                          // 0x01601760

typedef eastl::hashtable<map_pair<uint64_t, int>, eastl::allocator> ItemCountMap;

class cCollectableItems {
public:
    virtual void _v0();
    void* vtbl4;
    uint32_t mRefCount;                   // +0x8
    bool mbUnknownItemsAreUnlocked;       // +0xc
    char pad_d[3];
    cItemSetRBTree mItemSets;             // +0x10
    char pad_tree[0x148c - 0x10 - sizeof(cItemSetRBTree)];
    StaticInfoMap mStaticItemInfos;       // +0x148c
    char pad_14c0[0x4d00 - 0x148c - sizeof(StaticInfoMap)];
    ItemStatusMap mItemStatusInfos;       // +0x4d00
    char pad_4d3c[0x6d5c - 0x4d00 - sizeof(ItemStatusMap)];
    sp_vector<int> mNumUnlocksPerLevel;   // +0x6d5c
    int mUnlockPoints;                    // +0x6d70
    uint32_t mDefaultItemGroupId;         // +0x6d74
    float mFindPercentageLevelMultiplier; // +0x6d78
    float mGlobalFindPercentageMultiplier;// +0x6d7c
    eastl::list<ItemId> mNewItems;        // +0x6d80
    ItemCountMap mItemLevels;             // +0x6d8c

    bool IsItemUnlocked(uint64_t id);                         // 0x00595110
    uint64_t GetItemCategory(uint64_t id);                    // 0x00595040
    bool UnlockItem(uint64_t id, int cost);                   // 0x00596DA0
    void GetSets(fixed_vector_u64& out, int state, int maxLevel, cItemDataResource* table);   // 0x00596BE0
    bool CountSetItems(uint64_t setId, int* pUnlocked, int* pAvailable, int maxLevel, bool* pAllAtLevel);   // 0x00596A30
    bool UnlockFirstItemInSet(uint64_t id, int cost);
    bool UnlockItems(fixed_vector_u64& items, int cost);
    bool UnlockItemsFromSet(fixed_vector_u64& out, uint64_t setId, int maxLevel);
    bool UnlockItemFromRowType(fixed_vector_u64& out, int state, int maxLevel, int unused, const void* resourceKey);
    void Reset();
    ~cCollectableItems();
    cCollectableItems();
    void BuildSetSummary(SummaryMap& summary, int maxLevel, const void* resourceKey);
};

// NM 0x005973a0: rbtree find call/result handling differs
// @ 0x005973a0
bool cCollectableItems::UnlockFirstItemInSet(uint64_t id, int cost)
{
    bool result = false;
    uint64_t setId = GetItemCategory(id);
    cItemSetEntry* node;
    ((cItemSetTree*)&mItemSets)->find(&node, setId);
    if (node != (cItemSetEntry*)&mItemSets.mAnchor)
        return UnlockItem(node->mpBegin[0], cost);
    return result;
}

// NM 0x00597410: result-flag bookkeeping and inlined push_back differ
// @ 0x00597410
bool cCollectableItems::UnlockItems(fixed_vector_u64& items, int cost)
{
    bool result = false;
    const uint32_t count = (uint32_t)(items.mpEnd - items.mpBegin);
    if (count) {
        for (int i = 0; i < (int)count; ++i) {
            const uint64_t item = items.mpBegin[i];
            if (!IsItemUnlocked(item)) {
                const int points = mUnlockPoints - cost;
                if (!cost || points >= 0) {
                    mUnlockPoints = points;
                    mItemStatusInfos.index<uint8_t>(item) |= 3;
                    mNewItems.push_back(*(const ItemId*)&item);
                    result = (result || i == 0);
                    continue;
                }
            }
            result = false;
        }
    }
    return result;
}

// NM 0x005976d0: register allocation and erase/push_back inlining differ
// @ 0x005976d0
bool cCollectableItems::UnlockItemsFromSet(fixed_vector_u64& out, uint64_t setId, int maxLevel)
{
    cItemSetEntry* node;
    ((cItemSetTree*)&mItemSets)->find(&node, setId);
    if (node == (cItemSetEntry*)&mItemSets.mAnchor)
        return false;
    const int count = (int)(node->mpEnd - node->mpBegin);
    bool sameLevel = true;
    int lastLevel = -1;
    for (int i = 0; i < count; ++i) {
        uint64_t item = node->mpBegin[i];
        cStaticItemInfo& info = mStaticItemInfos.index<cStaticItemInfo>(item);
        if (!IsItemUnlocked(item) && (maxLevel == -1 || info.mRowIndex < maxLevel)) {
            sameLevel &= (lastLevel == -1 || lastLevel == info.mRowIndex);
            lastLevel = info.mRowIndex;
            if (out.mpEnd < out.mpCapacity)
                ::new (out.mpEnd++) uint64_t(item);
            else
                out.DoInsertValue(out.mpEnd, item);
        }
    }
    const int n = (int)(out.mpEnd - out.mpBegin);
    if (n > 1) {
        if (!sameLevel)
            eastl::reverse_impl((ItemId*)out.mpBegin, (ItemId*)out.mpEnd);   // called with maxLevel as an unused third argument
        else if (maxLevel == 1) {
            const uint32_t pick = sMathRandom.RandomUint32Uniform(n);
            uint64_t chosen = out.mpBegin[pick];
            out.erase(out.mpBegin, out.mpEnd);
            if (out.mpEnd < out.mpCapacity)
                ::new (out.mpEnd++) uint64_t(chosen);
            else
                out.DoInsertValue(out.mpEnd, chosen);
        } else {
            int i = 0;
            for (uint64_t* p = out.mpBegin; p != out.mpEnd; ++i) {
                if (i < maxLevel)
                    ++p;
                else {
                    if (p + 1 < out.mpEnd)
                        memcpy(p, p + 1, (size_t)((char*)out.mpEnd - (char*)(p + 1)));
                    --out.mpEnd;
                }
            }
        }
    }
    return UnlockItems(out, 0);
}

// NM 0x00597910: fixed_vector<uint64,64> local modelled by hand; frame layout differs
// @ 0x00597910
bool cCollectableItems::UnlockItemFromRowType(fixed_vector_u64& out, int state, int maxLevel, int unused, const void* resourceKey)
{
    out.erase(out.mpBegin, out.mpEnd);
    cItemDataResource* table = 0;
    if (resourceKey)
        GetItemDataResource(resourceKey, &table);
    bool result;
    struct { fixed_vector_u64 v; uint64_t buffer[64]; } sets;
    sets.v.mpBegin = sets.v.mpEnd = sets.buffer;
    sets.v.mpCapacity = sets.buffer + 64;
    sets.v.mpPoolBegin = sets.buffer;
    GetSets(sets.v, state, maxLevel, table);
    const int n = (int)(sets.v.mpEnd - sets.v.mpBegin);
    if (n > 0) {
        const uint32_t pick = sMathRandom.RandomUint32Uniform(n - 1);
        result = UnlockItemsFromSet(out, sets.v.mpBegin[pick], maxLevel);
    } else
        result = false;
    sets.v.DoFree(sets.v.mpBegin);
    if (table)
        table->Release();
    return result;
}

// NM 0x00597a20: container clear sequence scheduling differs
// @ 0x00597a20
void cCollectableItems::Reset()
{
    mNumUnlocksPerLevel.clear();
    mStaticItemInfos.DoFreeNodes(mStaticItemInfos.mpBucketArray, mStaticItemInfos.mnBucketCount);
    mStaticItemInfos.mnElementCount = 0;
    mItemSets.DoNukeSubtree(mItemSets.mAnchor.mpNodeParent);
    mItemSets.mAnchor.mpNodeRight = (cItemSetTreeNode*)&mItemSets.mAnchor;
    mItemSets.mAnchor.mpNodeLeft = (cItemSetTreeNode*)&mItemSets.mAnchor;
    mItemSets.mAnchor.mpNodeParent = 0;
    mItemSets.mAnchor.mColor = 0;
    mItemSets.mnSize = 0;
    mItemStatusInfos.clear();
    mItemLevels.clear();
}

// NM 0x00597b80: member destruction modelled explicitly; vtable stores and order differ
// @ 0x00597b80
cCollectableItems::~cCollectableItems()
{
    mItemLevels.reset_buckets();
    mNewItems.clear();
    if (mNumUnlocksPerLevel.mpBegin && ((int*)mNumUnlocksPerLevel.mpBegin)[-1] != 0)
        operator delete[](mNumUnlocksPerLevel.mpBegin);
    mItemStatusInfos.reset_buckets();
    mStaticItemInfos.reset_buckets();
    mItemSets.DoNukeSubtree(mItemSets.mAnchor.mpNodeParent);
}

void ConstructItemSetTree(cItemSetRBTree* tree);   // 0x00597AD0
struct FixedMapCtorArgs { uint8_t a, b; };
void ConstructStaticInfoMap(StaticInfoMap* map, const uint8_t& h, const uint8_t& e);   // 0x00595C60
void ConstructItemStatusMap(ItemStatusMap* map, const uint8_t& h, const uint8_t& e);   // 0x00595DD0
extern uint32_t gpEmptyBucketArray[2];   // 0x0154DF28

// PARTIAL 0x00597e00: constructor member initialisers modelled with explicit helper calls; base-class vtables simplified
// @ 0x00597e00
cCollectableItems::cCollectableItems()
{
    mRefCount = 0;
    mbUnknownItemsAreUnlocked = true;
    ConstructItemSetTree(&mItemSets);
    uint8_t h, e;
    ConstructStaticInfoMap(&mStaticItemInfos, e, h);
    ConstructItemStatusMap(&mItemStatusInfos, e, h);
    mNumUnlocksPerLevel.mpBegin = 0;
    mNumUnlocksPerLevel.mpEnd = 0;
    mNumUnlocksPerLevel.mpCapacity = 0;
    mUnlockPoints = 0;
    mDefaultItemGroupId = 0;
    mFindPercentageLevelMultiplier = 1.0f;
    mGlobalFindPercentageMultiplier = 1.0f;
    mNewItems.mNode.mpNext = &mNewItems.mNode;
    mNewItems.mNode.mpPrev = &mNewItems.mNode;
    mItemLevels.mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mItemLevels.mRehashPolicy.mfGrowthFactor = 2.0f;
    mItemLevels.mnElementCount = 0;
    mItemLevels.mRehashPolicy.mnNextResize = 0;
    mItemLevels.mnBucketCount = 1;
    mItemLevels.mpBucketArray = (ItemCountMap::node_type**)gpEmptyBucketArray;
}

// fixed_hash_map<uint64_t, uint64_t, 64> local used by BuildSetSummary
struct FoundItemsMap {
    ItemRowMap mMap;
    char mStorage[0x7f8 - sizeof(ItemRowMap)];
    FoundItemsMap(const uint8_t& h, const uint8_t& e);   // 0x00595F20
    ~FoundItemsMap() { mMap.reset_buckets(); }
};

// NM 0x00597f00: summary loop: duplicate find calls and 64-bit shifts schedule differently
// @ 0x00597f00
void cCollectableItems::BuildSetSummary(SummaryMap& summary, int maxLevel, const void* resourceKey)
{
    uint8_t flag;
    FoundItemsMap found(flag, flag);
    if (resourceKey) {
        cItemDataResource* table = 0;
        GetItemDataResource(resourceKey, &table);
        if (table) {
            uint32_t n = (uint32_t)(table->mRowsEnd - table->mRowsBegin);
            for (uint32_t off = 0; n; off += sizeof(cItemDataRow), --n) {
                const cItemDataRow& row = *(const cItemDataRow*)((const char*)table->mRowsBegin + off);
                uint64_t category = GetItemCategory(MakeItemIdInline(row.mIdHigh, row.mIdLow));
                found.mMap.index<uint64_t>(category) = 1;
            }
            if (table)
                table->Release();
        }
    }
    for (cItemSetEntry* node = (cItemSetEntry*)mItemSets.mAnchor.mpNodeLeft; node != (cItemSetEntry*)&mItemSets.mAnchor; node = RBTreeIncrement(node)) {
        const uint64_t setId = node->mKey;
        const uint32_t hi = (uint32_t)(setId >> 32);
        const uint32_t level = (uint32_t)setId & 0xFFFF;
        const uint32_t index = (uint32_t)(setId >> 16) & 0xFFFF;
        SetBitsMap& bitsMap = summary[hi];
        SetBitsMap::node_type** pBucket;
        bool isNew = bitsMap.find_node(index, &pBucket) == bitsMap.mpBucketArray[bitsMap.mnBucketCount];
        SetBitsMap::node_type* pNode = bitsMap.find_node(index, &pBucket);
        if (pNode == bitsMap.mpBucketArray[bitsMap.mnBucketCount]) {
            SetBitsMap::node_type value;
            value.first = index;
            value.second = 0;
            pNode = bitsMap.DoInsertValue(value, false).mpNode;
        }
        uint64_t& bits = pNode->second;
        if (isNew)
            bits = 0;
        if (found.mMap.find(setId) != found.mMap.end())
            bits |= (uint64_t)1 << (level + 0x30);
        bool allAtLevel = true;
        int available = 0;
        int unlocked = 0;
        CountSetItems(setId, &unlocked, &available, maxLevel, &allAtLevel);
        if (allAtLevel)
            bits |= (uint64_t)1 << level;
        if (available > 0)
            bits |= (uint64_t)1 << (unlocked > 0 ? level + 0x10 : level + 0x20);
    }
}

} // namespace SP
// --- equivalence checker address annotations
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
