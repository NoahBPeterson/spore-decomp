// Slice 0x004F6630..0x004F7658: unoptimized (/Od /Ob1 /MD /Gy /TP, no EH) EASTL code:
//   - vector<Elem16, sp_vector_allocator>::reserve and copy constructor
//   - map<uint32_t, vector<Elem16>>::operator[] and DoInsertValue(position, value, true_type)
//   - unique / adjacent_find over ResourceMan::Key
//   - eastl::sort<Key*> internals: quick_sort_impl, insertion_sort, insertion_sort_simple,
//     median, get_partition, partial_sort
//   - basic_string<wchar_t>::find(c, pos)
//   - two "pick the entry with the lowest priority" searches over 16-byte records
// ScratchSlots<N>() reproduces the unused stack slots that the original's inlined EASTL helpers
// left in each /Od frame (needed for byte-identical frame offsets).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }

void* __cdecl EASTL_Allocate(void* alloc, size_t n, size_t align, size_t offset);  // 0x0042DEE0
void  __cdecl EASTL_allocator_deallocate(void* p);                                 // 0x00F47380

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct sp_vector_allocator { const char* mpName; };

namespace EA { namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator<(const Key& a, const Key& b)
{
    if (a.mInstance != b.mInstance) return a.mInstance < b.mInstance;
    if (a.mGroup != b.mGroup) return a.mGroup < b.mGroup;
    return a.mType < b.mType;
}
inline bool operator==(const Key& a, const Key& b)
{
    return (a.mInstance == b.mInstance) && (a.mType == b.mType) && (a.mGroup == b.mGroup);
}
} }
using EA::ResourceMan::Key;

// ---------------------------------------------------------------------------
// vector<Elem16>
// ---------------------------------------------------------------------------
struct Elem16 { uint32_t mData[4]; };

Elem16* __cdecl uninitialized_copy_ptr(Elem16* first, Elem16* last, Elem16* dest);   // 0x004FDCB0
Elem16* __cdecl uninitialized_copy_ptr2(Elem16* first, Elem16* last, Elem16* dest);  // 0x00427270

struct Elem16Vector {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t mExtra;

    Elem16Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Elem16Vector(const Elem16Vector& x);
    ~Elem16Vector() {
        for (Elem16* p = mpBegin; p < mpEnd; ++p) {}
        ScratchSlots<3>();
        DoFreeBase();
    }
    void DoFreeBase();                                 // ~VectorBase, 0x00554B10
    void reserve(size_t n);

    inline Elem16* DoAllocate(size_t n) {
        return n ? (Elem16*)EASTL_Allocate(&mAllocator, n * sizeof(Elem16), 4, 0) : 0;
    }
    inline void deallocate(void* p, size_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
    inline void DoFree(Elem16* p, size_t n) {
        if (p)
            deallocate(p, n * sizeof(Elem16));
    }
};

// @ 0x004F6630
void Elem16Vector::reserve(size_t n)
{
    if (n > (size_t)(mpCapacity - mpBegin)) {
        Elem16* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        ScratchSlots<8>();
        DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

// @ 0x004F6CC0
Elem16Vector::Elem16Vector(const Elem16Vector& x)
{
    const size_t n = (size_t)(x.mpEnd - x.mpBegin);
    ScratchSlots<11>();
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = uninitialized_copy_ptr2(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------------------
// map<uint32_t, vector<Elem16>>
// ---------------------------------------------------------------------------
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct value_type {
    uint32_t first;
    Elem16Vector second;
    value_type(const uint32_t& a, const Elem16Vector& b) : first(a), second(b) {}
};
struct Node : rbtree_node_base {
    value_type mValue;
};

struct MapIterator {
    Node* mpNode;
    MapIterator(rbtree_node_base* pNode);              // 0x00566C50
    MapIterator(const MapIterator& x);                 // 0x005673E0
    MapIterator& operator--();                         // 0x00422C50
    value_type& operator*() const;                     // 0x00564F50
};
inline bool operator==(const MapIterator& a, const MapIterator& b) { return a.mpNode == b.mpNode; }

struct true_type {};

struct InsertResult {
    MapIterator first;
    bool second;
};

struct less_uint {
    bool operator()(const uint32_t& a, const uint32_t& b) const { return a < b; }
};
struct use_first {
    const uint32_t& operator()(const value_type& x) const { return x.first; }
};

struct UIntMap {
    less_uint mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    sp_vector_allocator mAllocator;

    MapIterator lower_bound(const uint32_t& key);      // 0x004B5E90
    MapIterator end() { return MapIterator(&mAnchor); }
    InsertResult insert(MapIterator position, const value_type& value);  // 0x004F6B30
    MapIterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const value_type& value, bool bForceToLeft);  // 0x004F7180
    InsertResult DoInsertValue(const value_type& value, true_type);    // 0x004F76C0
    MapIterator DoInsertValue(MapIterator position, const value_type& value, true_type);
    InsertResult insert_unique(const value_type& value) { return DoInsertValue(value, true_type()); }
    Elem16Vector& operator[](const uint32_t& key);
};

// @ 0x004F6720
Elem16Vector& UIntMap::operator[](const uint32_t& key)
{
    MapIterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, (*itLower).first)) {
        itLower = insert(itLower, value_type(key, Elem16Vector())).first;
    }
    return (*itLower).second;
}

// @ 0x004F6D60
MapIterator UIntMap::DoInsertValue(MapIterator position, const value_type& value, true_type)
{
    use_first extractKey;
    if ((position.mpNode != mAnchor.mpNodeRight) && (position.mpNode != &mAnchor)) {
        MapIterator itNext(position);
        --itNext;
        if (mCompare(extractKey(position.mpNode->mValue), extractKey(value)) &&
            mCompare(extractKey(value), extractKey(itNext.mpNode->mValue))) {
            if (position.mpNode->mpNodeRight)
                return DoInsertValueImpl(itNext.mpNode, value, true);
            return DoInsertValueImpl(position.mpNode, value, false);
        }
        return insert_unique(value).first;
    }
    if (mnSize && mCompare(extractKey(((Node*)mAnchor.mpNodeRight)->mValue), extractKey(value)))
        return DoInsertValueImpl(mAnchor.mpNodeRight, value, false);
    return insert_unique(value).first;
}

// ---------------------------------------------------------------------------
// unique / adjacent_find over Key
// ---------------------------------------------------------------------------
// @ 0x004F6C30
Key* adjacent_find(Key* first, Key* last)
{
    if (first != last) {
        Key* i = first;
        for (++i; i != last; ++i) {
            if (*first == *i)
                return first;
            first = i;
        }
    }
    return last;
}

// @ 0x004F6830
Key* unique(Key* first, Key* last)
{
    first = adjacent_find(first, last);
    if (first != last) {
        Key* dest(first);
        ScratchSlots<1>();
        for (++first; first != last; ++first) {
            if (!(*dest == *first))
                *++dest = *first;
        }
        return ++dest;
    }
    return last;
}

// ---------------------------------------------------------------------------
// lowest-priority search over 16-byte records
// ---------------------------------------------------------------------------
struct PriorityEntry {
    uint32_t mType;
    uint32_t mField4;
    uint32_t mGroup;
    int      mId;
};

struct PriorityInfo {
    uint32_t mField0;
    int mPriority;
};
struct PriorityManager {
    PriorityInfo* Find(int id);                        // 0x007DB5E0
};
PriorityManager* GetPriorityManager();                 // 0x0067DEA0

struct GroupTypeKey {
    uint32_t mGroup;
    uint32_t mType;
    GroupTypeKey(uint32_t group, uint32_t type) : mGroup(group), mType(type) {}
};
struct TypeKey {
    uint32_t mType;
    TypeKey(uint32_t type) : mType(type) {}
};
inline bool operator==(const PriorityEntry& e, const TypeKey& k) { return e.mType == k.mType; }
inline bool operator==(const PriorityEntry& e, const GroupTypeKey& k) { return (e.mGroup == k.mGroup) && (e.mType == k.mType); }

template <class T>
inline PriorityEntry* find(PriorityEntry* first, PriorityEntry* last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// @ 0x004F68F0
int FindLowestPriority(PriorityEntry* first, PriorityEntry* last, uint32_t group, uint32_t type)
{
    int minPriority = 0x7FFFFFFF;
    int bestId = -1;
    PriorityEntry* cur = first;
    for (;;) {
        cur = find(cur, last, GroupTypeKey(group, type));
        if (cur != last) {
            const int id = cur->mId;
            PriorityInfo* const pInfo = GetPriorityManager() ? GetPriorityManager()->Find(id) : 0;
            if (pInfo) {
                const int priority = pInfo->mPriority;
                if (priority < minPriority) {
                    minPriority = priority;
                    bestId = id;
                }
            }
            ++cur;
        } else
            break;
    }
    return bestId;
}

// @ 0x004F69E0
int FindLowestPriority(PriorityEntry* first, PriorityEntry* last, uint32_t type)
{
    int minPriority = 0x7FFFFFFF;
    int bestId = -1;
    PriorityEntry* cur = first;
    for (;;) {
        cur = find(cur, last, TypeKey(type));
        if (cur != last) {
            const int id = cur->mId;
            PriorityInfo* const pInfo = GetPriorityManager() ? GetPriorityManager()->Find(id) : 0;
            if (pInfo) {
                const int priority = pInfo->mPriority;
                if (priority < minPriority) {
                    minPriority = priority;
                    bestId = id;
                }
            }
            ++cur;
        } else
            break;
    }
    return bestId;
}

// ---------------------------------------------------------------------------
// basic_string<wchar_t>::find
// ---------------------------------------------------------------------------
inline const wchar_t* find(const wchar_t* first, const wchar_t* last, const wchar_t& value)
{
    while ((first != last) && (*first != value))
        ++first;
    return first;
}

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    sp_vector_allocator mAllocator;
    size_t find(wchar_t c, size_t position) const;
};

// @ 0x004F6AB0
size_t string16::find(wchar_t c, size_t position) const
{
    if (position < (size_t)(mpEnd - mpBegin)) {
        const wchar_t* const pResult = ::find(mpBegin + position, mpEnd, c);
        if (pResult != mpEnd)
            return (size_t)(pResult - mpBegin);
    }
    return (size_t)-1;
}

// ---------------------------------------------------------------------------
// eastl::sort<Key*>
// ---------------------------------------------------------------------------
static const int kQuickSortLimit = 28;

inline int Log2(int n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}

void make_heap(Key* first, Key* last);                                                  // 0x004F7800
void adjust_heap(Key* first, int topPosition, int heapSize, int position, Key value);   // 0x004F7890
void sort_heap(Key* first, Key* last);                                                  // 0x004F79D0

// @ 0x004F7210
const Key& median(const Key& a, const Key& b, const Key& c)
{
    if (a < b) {
        if (b < c)
            return b;
        else if (a < c)
            return c;
        else
            return a;
    } else if (a < c)
        return a;
    else if (b < c)
        return c;
    return b;
}

inline void swap(Key& a, Key& b)
{
    const Key temp(a);
    a = b;
    b = temp;
}
inline void iter_swap(Key* a, Key* b) { swap(*a, *b); }

// @ 0x004F7420
Key* get_partition(Key* first, Key* last, Key pivotValue)
{
    for (;; ++first) {
        while (*first < pivotValue)
            ++first;
        --last;
        while (pivotValue < *last)
            --last;
        if (first >= last)
            return first;
        iter_swap(first, last);
    }
}

// @ 0x004F7550
void partial_sort(Key* first, Key* middle, Key* last)
{
    make_heap(first, middle);
    for (Key* i = middle; i < last; ++i) {
        if (*i < *first) {
            const Key temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp);
        }
    }
    sort_heap(first, middle);
    ScratchSlots<3>();
}

// @ 0x004F6EC0
void quick_sort_impl(Key* first, Key* last, int kRecursionCount)
{
    while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
        Key* const position(get_partition(first, last, median(*first, *(first + (last - first) / 2), *(last - 1))));
        quick_sort_impl(position, last, --kRecursionCount);
        last = position;
        ScratchSlots<13>();
    }
    if (kRecursionCount == 0)
        partial_sort(first, last, last);
}

// @ 0x004F6F80
void insertion_sort(Key* first, Key* last)
{
    if (first != last) {
        Key* iCurrent;
        Key* iNext;
        Key* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const Key temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (temp < *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x004F7090
void insertion_sort_simple(Key* first, Key* last)
{
    for (Key* current = first; current != last; ++current) {
        Key* end(current);
        Key* prev(current);
        const Key value(*current);
        for (--prev; value < *prev; --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// @ 0x004F6B70
void sort(Key* first, Key* last)
{
    if (first != last) {
        quick_sort_impl(first, last, 2 * Log2((int)(last - first)));
        if ((last - first) > kQuickSortLimit) {
            insertion_sort(first, first + kQuickSortLimit);
            insertion_sort_simple(first + kQuickSortLimit, last);
        } else
            insertion_sort(first, last);
    }
    ScratchSlots<18>();
}
