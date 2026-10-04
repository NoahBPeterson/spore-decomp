// slice s00593840 — SP::cCollectableItems (retail layout) and the EASTL containers it instantiates:
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

// @ 0x00594b10 ?push_back@
template <typename T>
void list<T>::push_back(const T& value)
{
    DoInsertValue(&mNode, value);
}

// @ 0x005945b0 ?remove@
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

    node_type** DoAllocateBuckets(uint32_t n);
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

// @ 0x00594290 ??$fill_n@
template <typename OutputIterator, typename Size, typename T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value)
{
    for (; n-- > 0; ++first)
        *first = value;
    return first;
}

// NM 0x00594260: value halves loaded after the destination pointers (original loads value first)
// @ 0x00594260 ??$fill@
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

// NM 0x00593ba0: register assignment of first/last swapped in adjacent_find/unique
// @ 0x00593ba0 ??$unique@
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

// @ 0x00595000 ??$reverse_impl@
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

// Value types of the hash maps used below (node sizes 0x2C, 0x14, 0xE4, 0x0C).
struct cStaticItemInfo { uint64_t first; uint32_t mData[8]; };           // 0x28 value
struct cItemSetRow     { ItemId first; uint32_t mData[2]; };           // 0x10 value
struct cItemBig        { ItemId first; uint32_t mData[54]; };          // 0xE0 value
struct cItemSmall      { uint32_t first; uint32_t mData; };            // 0x08 value

typedef eastl::hashtable<cStaticItemInfo, eastl::fixed_hashtable_allocator> StaticInfoMap;
typedef eastl::hashtable<cItemSetRow, eastl::fixed_hashtable_allocator> ItemSetRowMap;
typedef eastl::hashtable<cItemBig, eastl::fixed_hashtable_allocator> BigItemMap;
typedef eastl::hashtable<cItemSmall, eastl::fixed_hashtable_allocator> SmallItemMap;

// @ 0x00593d60 ?DoRehash@?$hashtable@UcStaticItemInfo
template void StaticInfoMap::DoRehash(uint32_t);
// @ 0x00593e70 ?DoRehash@?$hashtable@UcItemSetRow
template void ItemSetRowMap::DoRehash(uint32_t);
// @ 0x00594030 ?DoRehash@?$hashtable@UcItemBig
template void BigItemMap::DoRehash(uint32_t);
// @ 0x00594150 ?DoRehash@?$hashtable@UcItemSmall
template void SmallItemMap::DoRehash(uint32_t);

// NM 0x005948d0: node size loaded into eax instead of ecx before the overflow allocation
// @ 0x005948d0 ?DoAllocateNode@?$hashtable@UcStaticItemInfo
template StaticInfoMap::node_type* StaticInfoMap::DoAllocateNode(const cStaticItemInfo&);
// NM 0x00594920: node size loaded into eax instead of ecx before the overflow allocation
// @ 0x00594920 ?DoAllocateNode@?$hashtable@UcItemSetRow
template ItemSetRowMap::node_type* ItemSetRowMap::DoAllocateNode(const cItemSetRow&);
// NM 0x00594980: node size loaded into eax instead of ecx before the overflow allocation
// @ 0x00594980 ?DoAllocateNode@?$hashtable@UcItemSmall
template SmallItemMap::node_type* SmallItemMap::DoAllocateNode(const cItemSmall&);

// @ 0x005949d0 ??$find@_K@?$hashtable@UcStaticItemInfo
template StaticInfoMap::iterator StaticInfoMap::find<uint64_t>(const uint64_t&);

// Non-fixed map<ItemId,{uint32,uint32}> (node 0x18)
struct cItemPair { uint64_t first; uint32_t mData[2]; };
typedef eastl::hashtable<cItemPair, eastl::allocator> ItemPairMap;
// NM 0x00594b60: scheduling of the bucket/element-count stores at the end differs
// @ 0x00594b60 ?DoInsertValue@?$hashtable@UcItemPair
template ItemPairMap::insert_return_type ItemPairMap::DoInsertValue(const cItemPair&, eastl::true_type);

// @ 0x00594410 ?begin@?$hashtable@UcItemSetRow
template ItemSetRowMap::iterator ItemSetRowMap::begin();

// @ 0x005939d0 ??$distance@
template int eastl::distance<ItemSetRowMap::iterator>(ItemSetRowMap::iterator, ItemSetRowMap::iterator);

template void eastl::list<ItemId>::push_back(const ItemId&);
template void eastl::list<ItemId>::remove(const ItemId&);

struct ItemIdIter {
    typedef ItemId value_type;
    ItemId* p;
    ItemIdIter& operator++() { ++p; return *this; }
    ItemIdIter& operator--() { --p; return *this; }
    ItemId& operator*() const { return *p; }
    bool operator!=(const ItemIdIter& x) const { return p != x.p; }
    bool operator<(const ItemIdIter& x) const { return p < x.p; }
};
template void eastl::reverse_impl<ItemId>(ItemId*, ItemId*);
template ItemId* eastl::unique<ItemId*>(ItemId*, ItemId*);
template void eastl::fill<ItemId*, ItemId>(ItemId*, ItemId*, const ItemId&);
template eastl::generic_iterator<ItemId> eastl::fill_n<eastl::generic_iterator<ItemId>, uint32_t, ItemId>(eastl::generic_iterator<ItemId>, uint32_t, const ItemId&);

// ---------------------------------------------------------------------------------------------
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

struct VarListEntry;
extern VarListEntry gCollectableItemsVarList[];    // 0x0150D5E8

class cVarListSerializer {
public:
    uint32_t mData[0xa14 / 4];
    cVarListSerializer(void* object, VarListEntry* list, uint32_t count);   // 0x00692F90
    bool Serialize(ISerializer* s);                                         // 0x00692900
};

// @ 0x00593840
bool HashBytes(const void* data, uint32_t length)
{
    extern bool HashBytesImpl(const void* data, uint32_t length, int mode);   // 0x0093A6C0
    return HashBytesImpl(data, length, 1);
}

// @ 0x00593960
void SplitItemId(uint64_t id, uint32_t* pHi, uint32_t* pLo)
{
    *pHi = (uint32_t)(id >> 32);
    *pLo = (uint32_t)id;
}

// @ 0x00593980
uint64_t MakeItemId(uint32_t hi, uint32_t lo)
{
    return ((uint64_t)hi << 32) | (uint64_t)lo;
}

// Hash-map value types inside cCollectableItems
struct cItemStatus {
    uint64_t first;
    bool mbUnlocked : 1;   // bit 0
    bool mbNew      : 1;   // bit 1
    bool mbHidden   : 1;   // bit 2
    uint8_t pad[7];
};
struct cItemLevel { uint64_t first; int mLevel; uint32_t pad; };

typedef eastl::hashtable<cItemStatus, eastl::fixed_hashtable_allocator> ItemStatusMap;
typedef eastl::hashtable<cItemLevel, eastl::fixed_hashtable_allocator> ItemLevelMap;

struct ItemVector { uint64_t* mpBegin; uint64_t* mpEnd; uint64_t* mpCapacity; uint32_t mAlloc[2]; };
struct cItemSetNode {      // rbtree node of map<ItemId, vector<ItemId>>
    cItemSetNode* mpNodeRight;
    cItemSetNode* mpNodeLeft;
    cItemSetNode* mpNodeParent;
    char mColor;
    uint64_t mKey;         // +0x10
    ItemVector mValue;     // +0x18
};
extern "C++" cItemSetNode* RBTreeIncrement(const cItemSetNode* pNode);   // 0x00921580

class cCollectableItems {
public:
    void* vtbl0;
    void* vtbl4;
    uint32_t mRefCount;
    bool mbUnknownItemsAreUnlocked;     // +0x0c
    char pad_d[0x14 - 0xd];
    struct { cItemSetNode* mpNodeRight; cItemSetNode* mpNodeLeft; cItemSetNode* mpNodeParent; char mColor; } mItemSetAnchor;  // +0x14
    char pad_24[0x148c - 0x24];
    StaticInfoMap mStaticItemInfos;     // +0x148c
    char pad_14c4[0x4d00 - 0x148c - sizeof(StaticInfoMap)];
    ItemStatusMap mItemStatusInfos;     // +0x4d00
    char pad_4d38[0x6d70 - 0x4d00 - sizeof(ItemStatusMap)];
    int mUnlockPoints;                  // +0x6d70
    uint32_t mDefaultItemGroupId;       // +0x6d74
    char pad_6d78[0x6d8c - 0x6d78];
    ItemLevelMap mItemLevels;           // +0x6d8c

    bool Write(ISerializer* s);
    void AddUnlockPoints(int n);
    uint64_t GetDefaultItemGroupId();
    void ClearNewFlags();
    bool AreAllUnlockedHidden();
    int CountUnlocked();
    uint64_t GetItemCategory(uint64_t id);
    bool IsItemVisible(uint64_t id);
    bool IsItemUnlocked(uint64_t id);
    bool IsItemNew(uint64_t id);
    bool IsKnownItem(uint64_t id);
    bool FindBestItem(uint64_t* out);
};

// NM 0x00593890: version store scheduled before the GetStreamHolder call
// @ 0x00593890
bool cCollectableItems::Write(ISerializer* s)
{
    ISerializerStream* holder = s->GetStreamHolder();
    uint32_t version = 0x03A3AA3A;
    EA::IO::IStream* stream = holder->GetStream();
    EA::IO::WriteUint32(stream, &version, 1, 0);
    cVarListSerializer serializer(this, gCollectableItemsVarList, 0x01A80D26);
    return serializer.Serialize(s);
}

// @ 0x005939b0
void cCollectableItems::AddUnlockPoints(int n)
{
    mUnlockPoints += n;
}

// @ 0x005939c0
uint64_t cCollectableItems::GetDefaultItemGroupId()
{
    return mDefaultItemGroupId;
}

// @ 0x005942e0
void cCollectableItems::ClearNewFlags()
{
    for (ItemStatusMap::iterator it = mItemStatusInfos.begin(), itEnd = mItemStatusInfos.end(); it != itEnd; ++it)
        it->mbNew = false;
}

// @ 0x00594330
bool cCollectableItems::AreAllUnlockedHidden()
{
    int unlocked = 0;
    int visible = 0;
    for (ItemStatusMap::iterator it = mItemStatusInfos.begin(), itEnd = mItemStatusInfos.end(); it != itEnd; ++it) {
        unlocked += it->mbUnlocked;
        visible += !it->mbHidden;
    }
    return unlocked == visible;
}

// @ 0x005943b0
int cCollectableItems::CountUnlocked()
{
    int count = 0;
    for (ItemStatusMap::iterator it = mItemStatusInfos.begin(), itEnd = mItemStatusInfos.end(); it != itEnd; ++it) {
        if (it->mbUnlocked)
            ++count;
    }
    return count;
}

// NM 0x00595040: result kept in edi:ebx in original; register allocation differs
// @ 0x00595040
uint64_t cCollectableItems::GetItemCategory(uint64_t id)
{
    uint64_t category = (uint64_t)-1;
    const StaticInfoMap::iterator& it = mStaticItemInfos.find(id);
    if (it != mStaticItemInfos.end()) {
        const cStaticItemInfo& info = *it.operator->();
        category = ((((uint64_t)info.mData[2] << 16) | (int64_t)(int32_t)info.mData[5]) << 16) | (int64_t)(int32_t)info.mData[4];
    }
    return category;
}

// @ 0x005950c0
bool cCollectableItems::IsItemVisible(uint64_t id)
{
    ItemStatusMap::iterator it = mItemStatusInfos.find(id);
    if (it != mItemStatusInfos.end())
        return !it->mbHidden;
    return false;
}

// @ 0x00595110
bool cCollectableItems::IsItemUnlocked(uint64_t id)
{
    ItemStatusMap::iterator it = mItemStatusInfos.find(id);
    if (it != mItemStatusInfos.end())
        return it->mbUnlocked != 0;
    StaticInfoMap::iterator itStatic = mStaticItemInfos.find(id);
    if (itStatic != mStaticItemInfos.end())
        return false;
    return mbUnknownItemsAreUnlocked;
}

// @ 0x00595190
bool cCollectableItems::IsItemNew(uint64_t id)
{
    ItemStatusMap::iterator it = mItemStatusInfos.find(id);
    if (it != mItemStatusInfos.end())
        return it->mbNew != 0;
    StaticInfoMap::iterator itStatic = mStaticItemInfos.find(id);
    if (itStatic != mStaticItemInfos.end())
        return false;
    return false;
}

// @ 0x005951f0
bool cCollectableItems::IsKnownItem(uint64_t id)
{
    StaticInfoMap::iterator it = mStaticItemInfos.find(id);
    return it != mStaticItemInfos.end();
}

// NM 0x00595230: register allocation (this/vector end in different registers)
// @ 0x00595230
bool cCollectableItems::FindBestItem(uint64_t* out)
{
    int bestLevel = 0;
    int bestIndex = -1;
    for (cItemSetNode* node = mItemSetAnchor.mpNodeLeft; node != (cItemSetNode*)&mItemSetAnchor; node = RBTreeIncrement(node)) {
        ItemVector& items = node->mValue;
        if (IsItemUnlocked(items.mpEnd[-1])) {
            const int count = (int)(items.mpEnd - items.mpBegin);
            for (int i = 0; i < count; ++i) {
                uint64_t id = items.mpBegin[i];
                ItemLevelMap::iterator it = mItemLevels.find(id);
                if (it != mItemLevels.end()) {
                    const int level = it->mLevel;
                    if (i >= bestIndex && level >= bestLevel) {
                        *out = id;
                        bestLevel = level;
                        bestIndex = i;
                    }
                }
            }
        }
    }
    return bestLevel > 0;
}

// Serialization of hash_map<ItemId,bool> and list<ItemId>
typedef eastl::hashtable<eastl::pair<uint64_t, bool>, eastl::fixed_hashtable_allocator> ItemFlagMap;

// NM 0x00593a40: register allocation and iterator scheduling differ
// @ 0x00593a40
void WriteItemFlagMap(ISerializer* s, ItemFlagMap& map)
{
    uint32_t count = map.mnElementCount;
    EA::IO::IStream* stream = s->GetStreamHolder()->GetStream();
    EA::IO::WriteUint32(stream, &count, 1, 0);
    for (ItemFlagMap::iterator it = map.begin(); it != map.end(); ++it) {
        uint64_t key = it->first;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::WriteUint64(stream, &key, 1, 0);
        s->EndItem();
        bool value = it->second;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::WriteBool8(stream, &value, 1);
        s->EndItem();
    }
    s->EndItem();
}

// @ 0x00594c70
void ReadItemList(ISerializer* s, eastl::list<ItemId>& items)
{
    items.clear();
    int32_t count = 0;
    EA::IO::IStream* stream = s->GetStreamHolder()->GetStream();
    EA::IO::ReadInt32(stream, &count, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        ItemId id;
        stream = s->GetStreamHolder()->GetStream();
        EA::IO::ReadUint64(stream, (uint64_t*)&id, 1, 0);
        items.push_back(id);
    }
    s->EndItem();
}

} // namespace SP
