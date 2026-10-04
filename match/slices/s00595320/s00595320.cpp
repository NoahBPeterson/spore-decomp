// slice s00595320 — collectable-item serializers and fixed hash map helpers; shared EASTL subset (from slice s00593840) — SP::cCollectableItems (retail layout) and the EASTL containers it instantiates:
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

// ---------------------------------------------------------------------------------------------
namespace SP {
// NM 0x00595320: same template as s0057bfb0 0x0057C770: short-circuit chain/stack slots differ
// @ 0x00595320 ??$WriteTypedValue@_N
template bool WriteTypedValue<bool>(IXmlWriter*, const char*, const bool&, const wchar_t*);
// NM 0x005954f0: same template as s0057bfb0 0x0057C770: short-circuit chain/stack slots differ
// @ 0x005954f0 ??$WriteTypedValue@_J
template bool WriteTypedValue<__int64>(IXmlWriter*, const char*, const __int64&, const wchar_t*);
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

// NM 0x00595870: copy_backward/GetNewCapacity codegen differs (original spills new capacity to the stack)
// @ 0x00595870 ?DoInsertValue@?$fixed_vector_base@_K
template void eastl::fixed_vector_base<uint64_t>::DoInsertValue(uint64_t*, const uint64_t&);
// @ 0x005962b0 ?clear@?$fixed_vector_base@_K
template void eastl::fixed_vector_base<uint64_t>::clear();

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

// @ 0x005956c0
void ReadItemFlagMap(ISerializer* s, ItemFlagMap& map)
{
    map.clear();
    int32_t count = 0;
    EA::IO::IStream* stream = s->GetStreamHolder()->GetStream();
    EA::IO::ReadInt32(stream, &count, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        uint64_t key;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::ReadUint64(stream, &key, 1, 0);
        s->EndItem();
        bool value;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::ReadBool8(stream, &value, 1);
        s->EndItem();
        eastl::pair<uint64_t, bool> entry;
        entry.first = key;
        entry.second = value;
        ItemFlagMap::insert_return_type result = map.DoInsertValue(entry, eastl::true_type());
        if (!result.second)
            result.first->second = value;
    }
    s->EndItem();
}

// NM 0x005957d0: 64-bit element copy loads high dword first in original
// @ 0x005957d0
void WriteItemList(ISerializer* s, eastl::list<ItemId>& items)
{
    uint32_t count = (uint32_t)items.size();
    EA::IO::IStream* stream = s->GetStreamHolder()->GetStream();
    EA::IO::WriteUint32(stream, &count, 1, 0);
    for (eastl::ListNodeBase* p = items.mNode.mpNext; p != &items.mNode; p = p->mpNext) {
        uint64_t id = *(const uint64_t*)&((eastl::ListNode<ItemId>*)p)->mValue;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::WriteUint64(stream, &id, 1, 0);
    }
    s->EndItem();
}

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


} // namespace SP
// hash_map::operator[] instances
// NM 0x00595d40: value_type temporary construction order differs
// @ 0x00595d40 ??$index@UcStaticItemInfo
template SP::cStaticItemInfo& SP::StaticInfoMap::index<SP::cStaticItemInfo>(const uint64_t&);
// NM 0x00595eb0: value_type temporary construction order differs
// @ 0x00595eb0 ??$index@E@
template uint8_t& SP::ItemStatusMap::index<uint8_t>(const uint64_t&);
// NM 0x00595ff0: value_type temporary construction order differs
// @ 0x00595ff0 ??$index@_K@
template uint64_t& SP::ItemRowMap::index<uint64_t>(const uint64_t&);
namespace SP {

// fixed_hash_map constructor pattern: node pool inside the object, embedded bucket buffer,
// max load factor 10000, rehash to fit.
struct fixed_pool_base {
    void* mpHead;
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);  // 0x00921260
};
uint32_t GetPrevBucketCountOnly(uint32_t n);   // 0x00921340
struct prime_rehash_policy_ex {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_ex() {}
    prime_rehash_policy_ex(float f) : mfMaxLoadFactor(f), mfGrowthFactor(2.0f), mnNextResize(0) {}
    uint32_t GetBucketCount(uint32_t nElementCount) const;   // 0x009213C0
};

template <int kNodeSize, int kNodeCount, int kBucketCount, int kPoolOffset>
struct fixed_hash_map_storage {
    uint32_t mHashCodeBase;
    void** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy_ex mRehashPolicy;
    struct alloc_t { void* mpHead; void* mpNext; void* mpPoolBegin; void* mpCapacity; uint32_t mnNodeSize; void* mpBucketBuffer; } mAllocator;
    void* mBucketBuffer[kBucketCount + 1];   // +0x34

    struct fixed_allocator_type {
        fixed_pool_base mPool;
        void* mpPoolBegin;
        void* mpCapacity;
        uint32_t mnNodeSize;
        void* mpBucketBuffer;
        fixed_allocator_type(void* pNodeBuffer, void* pBucketBuffer)
        {
            mPool.mpHead = 0;
            mPool.init(pNodeBuffer, kNodeSize * kNodeCount, kNodeSize, 8, 0);
            mpPoolBegin = pNodeBuffer;
            mpCapacity = (char*)pNodeBuffer + kNodeSize * kNodeCount;
            mnNodeSize = kNodeSize;
            mpBucketBuffer = pBucketBuffer;
        }
    };
    void BaseConstruct(uint32_t nBucketCount, const uint32_t& hash, const uint32_t& h2, uint32_t h3, const uint32_t& eq, const uint32_t& ex, const fixed_allocator_type& a);
    void DoRehash(uint32_t n);
    fixed_hash_map_storage(const uint32_t& hashFunction, uint32_t predicate);
};

template <int kNodeSize, int kNodeCount, int kBucketCount, int kPoolOffset>
fixed_hash_map_storage<kNodeSize, kNodeCount, kBucketCount, kPoolOffset>::fixed_hash_map_storage(const uint32_t& hashFunction, uint32_t predicate)
{
    fixed_allocator_type allocator((char*)this + kPoolOffset, mBucketBuffer);
    BaseConstruct(GetPrevBucketCountOnly(kBucketCount), hashFunction, predicate, predicate, predicate, predicate, allocator);
    mRehashPolicy = prime_rehash_policy_ex(10000.0f);
    const uint32_t nBuckets = mRehashPolicy.GetBucketCount(mnElementCount);
    if (nBuckets > mnBucketCount)
        DoRehash(nBuckets);
}

// PARTIAL 0x00595c60: fixed_hash_map ctor modelled with a stub base constructor (argument list approximate)
// @ 0x00595c60 ??0?$fixed_hash_map_storage@$0DA@$0BAA@$0BAB@
template struct fixed_hash_map_storage<0x30, 0x100, 0x101, 0x43c>;
// PARTIAL 0x00595dd0: fixed_hash_map ctor modelled with a stub base constructor (argument list approximate)
// @ 0x00595dd0 ??0?$fixed_hash_map_storage@$0BI@$0BAA@$0BAB@
template struct fixed_hash_map_storage<0x18, 0x100, 0x101, 0x43c>;
// PARTIAL 0x00595f20: fixed_hash_map ctor modelled with a stub base constructor (argument list approximate)
// @ 0x00595f20 ??0?$fixed_hash_map_storage@$0BI@$0EA@$0EB@
template struct fixed_hash_map_storage<0x18, 0x40, 0x41, 0x13c>;
// PARTIAL 0x00596060: fixed_hash_map ctor modelled with a stub base constructor (argument list approximate)
// @ 0x00596060 ??0?$fixed_hash_map_storage@$0M@$07$08@
template struct fixed_hash_map_storage<0xc, 8, 9, 0x5c>;
// PARTIAL 0x005961e0: fixed_hash_map ctor modelled with a stub base constructor (argument list approximate)
// @ 0x005961e0 ??0?$fixed_hash_map_storage@$0BI@$03$04@
template struct fixed_hash_map_storage<0x18, 4, 5, 0x4c>;

// Container holding a fixed hash map at +4; its destructor frees nodes and buckets.
struct cItemFlagMapHolder {
    void* vtbl;
    ItemFlagMap mMap;   // +0x4
    void Destroy();
};

// @ 0x00596190
void cItemFlagMapHolder::Destroy()
{
    mMap.reset_buckets();
}

// Resource with item rows (0x1D8-byte records)
struct cItemRow { uint64_t mItemId; uint32_t mParentIndex; uint32_t pad; char data[0x1d8 - 0x10]; };
class cItemTable {
public:
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x98 - 4];
    cItemRow* mRowsBegin;   // +0x98
    cItemRow* mRowsEnd;     // +0x9c
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
class cResourceManager {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2();
    virtual bool GetResource(const ResourceKey& key, EA::AutoRefCount<cItemTable>* pResource, int, int, int, int);
};
cResourceManager* GetManager();   // 0x0067DCD0

typedef eastl::hashtable<map_pair<uint64_t, int>, eastl::allocator> ItemCountMap;

class cCollectableItems {
public:
    char pad_0[0x148c];
    StaticInfoMap mStaticItemInfos;   // +0x148c
    char pad_14c0[0x6d8c - 0x148c - sizeof(StaticInfoMap)];
    ItemCountMap mItemLevels;         // +0x6d8c
    void RebuildItemLevels(const ResourceKey& key);
};

// NM 0x00595a90: register allocation and AutoRefCount temporaries differ
// @ 0x00595a90
void cCollectableItems::RebuildItemLevels(const ResourceKey& key)
{
    ItemCountMap& levels = mItemLevels;
    levels.DoFreeNodes(levels.mpBucketArray, levels.mnBucketCount);
    levels.mnElementCount = 0;

    EA::AutoRefCount<cItemTable> table;
    if (GetManager()->GetResource(key, &table, 0, 0, 0, 0)) {
        EA::AutoRefCount<cItemTable> rows(table);
        const uint32_t count = (uint32_t)(rows->mRowsEnd - rows->mRowsBegin);
        for (uint32_t i = 0; i < count; ++i) {
            const cItemRow& row = rows->mRowsBegin[i];
            const uint64_t id = row.mItemId;
            if (mStaticItemInfos.find(id) != mStaticItemInfos.end()) {
                if (row.mParentIndex >= count || rows->mRowsBegin[row.mParentIndex].mItemId != row.mItemId || i < row.mParentIndex) {
                    ItemCountMap::iterator it = levels.find(id);
                    if (it != levels.end())
                        ++it->second;
                    else
                        levels.DoInsertValue(map_pair<uint64_t, int>(id, 1), eastl::true_type());
                }
            }
        }
    }
}

} // namespace SP
