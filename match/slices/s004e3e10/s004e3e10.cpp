// Slice 0x004E3E10..0x004E5041: unoptimized (/Od /Ob1 /MD /Gy /TP, no EH) EASTL container code.
// ScratchSlots<N>() reproduces the unused stack slots that the original's inlined EASTL helpers
// left in each /Od frame (needed for byte-identical frame offsets).
//   - vector<ResourceMan::Key, sp_vector_allocator>::DoInsertValue
//   - map<Key, KeyValue> (rbtree) lower_bound / insert(hint) / DoInsertValue / DoAllocateNode / DoNuke
//   - vector<TreeItem> (a 0x24-byte record that owns a vector of its own type) operator= and the
//     copy / uninitialized_copy / uninitialized_fill_n helpers it uses
//   - intrusive_ptr<DefaultRefCounted>::operator=
//   - fixed node allocator allocate(n, alignment)
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }

void* __cdecl EASTL_Allocate(void* alloc, size_t n, size_t align, size_t offset);  // 0x0042DEE0
void  __cdecl EASTL_allocator_deallocate(void* p);                                 // 0x00F47380

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

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
} }
using EA::ResourceMan::Key;

// ---------------------------------------------------------------------------
// vector<Key, sp_vector_allocator>
// ---------------------------------------------------------------------------
struct sp_vector_allocator { const char* mpName; };

Key* __cdecl uninitialized_copy_Key(Key* first, Key* last, Key* dest);  // 0x0050F8B0

inline Key* copy_backward_impl(Key* first, Key* last, Key* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

inline Key* copy_backward(Key* first, Key* last, Key* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}

struct KeyVector {
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCapacity;
    sp_vector_allocator mAllocator;

    inline Key* DoAllocate(size_t n) {
        uint32_t reserved[16];
        return n ? (Key*)EASTL_Allocate(&mAllocator, n * sizeof(Key), 4, 0) : 0;
    }
    inline void deallocate(void* p, size_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
    inline void DoFree(Key* p, size_t n) {
        if (p)
            deallocate(p, n * sizeof(Key));
    }
    void DoInsertValue(Key* position, const Key& value);
};

// @ 0x004E3E10
void KeyVector::DoInsertValue(Key* position, const Key& value)
{
    if (mpEnd != mpCapacity) {
        const Key* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) Key(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Key* const pNewData = DoAllocate(nNewSize);
        Key* pNewEnd = uninitialized_copy_Key(mpBegin, position, pNewData);
        ::new(pNewEnd) Key(value);
        ++pNewEnd;
        pNewEnd = uninitialized_copy_Key(position, mpEnd, pNewEnd);
        DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// map<Key, KeyValue>
// ---------------------------------------------------------------------------
struct PtrVectorBase {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    sp_vector_allocator mAllocator;
    ~PtrVectorBase();                                  // 0x00425990
};
struct KeyValue : PtrVectorBase {                    // a pointer vector plus one extra word
    uint32_t mExtra;
    KeyValue(const KeyValue& x);                       // 0x0050D440
    ~KeyValue() {
        for (void** p = mpBegin; p < mpEnd; ++p) {}
        ScratchSlots<3>();
    }
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct value_type {
    Key first;
    KeyValue second;
};
struct Node : rbtree_node_base {
    value_type mValue;
};

rbtree_node_base* __cdecl RBTreeDecrement(const rbtree_node_base* pNode);  // 0x009215C0

struct MapIterator {
    Node* mpNode;
    MapIterator(Node* pNode);                          // 0x00566C50
    MapIterator(const MapIterator& x);                 // 0x005673E0
    MapIterator& operator--();                         // 0x00422C50
};

struct true_type {};

struct InsertResult {
    MapIterator first;
    bool second;
    InsertResult(const MapIterator& a, const bool& b) : first(a), second(b) {}
};

struct use_first {
    const Key& operator()(const value_type& x) const { return x.first; }
};

struct less_Key {
    bool operator()(const Key& a, const Key& b) const { return a < b; }
};

struct KeyMap {
    less_Key mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    sp_vector_allocator mAllocator;

    MapIterator lower_bound(const Key& key);
    void DoNuke(Node* pNode);
    Node* DoAllocateNode(const value_type& value);
    MapIterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const value_type& value, bool bForceToLeft);  // 0x004E4C30
    InsertResult DoInsertValue(const value_type& value, true_type);
    MapIterator DoInsertValue(MapIterator position, const value_type& value, true_type);
    InsertResult insert_unique(const value_type& value) { return DoInsertValue(value, true_type()); }

    inline void DoFreeNode(Node* pNode) {
        pNode->~Node();
        Deallocate(pNode);
    }
    static inline void Deallocate(void* p) { void* q = p; EASTL_allocator_deallocate(q); }
};

// @ 0x004E40B0
MapIterator KeyMap::lower_bound(const Key& key)
{
    use_first extractKey;
    Node* pCurrent = (Node*)mAnchor.mpNodeParent;
    Node* pRangeEnd = (Node*)&mAnchor;
    while (pCurrent) {
        if (!mCompare(extractKey(pCurrent->mValue), key)) {
            pRangeEnd = pCurrent;
            pCurrent = (Node*)pCurrent->mpNodeLeft;
        } else
            pCurrent = (Node*)pCurrent->mpNodeRight;
    }
    return MapIterator(pRangeEnd);
}

// @ 0x004E4170
void KeyMap::DoNuke(Node* pNode)
{
    while (pNode) {
        DoNuke((Node*)pNode->mpNodeRight);
        Node* const pNodeLeft = (Node*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x004E4D10
Node* KeyMap::DoAllocateNode(const value_type& value)
{
    Node* const pNode = (Node*)EASTL_Allocate(&mAllocator, sizeof(Node), 4, 0);
    ::new(&pNode->mValue) value_type(value);
    ScratchSlots<18>();
    return pNode;
}

// @ 0x004E4D80
InsertResult KeyMap::DoInsertValue(const value_type& value, true_type)
{
    use_first extractKey;
    Node* pCurrent = (Node*)mAnchor.mpNodeParent;
    Node* pLowerBound = (Node*)&mAnchor;
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = mCompare(extractKey(value), extractKey(pCurrent->mValue));
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node*)pCurrent->mpNodeRight;
    }
    Node* const pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != (Node*)mAnchor.mpNodeLeft)
            pLowerBound = (Node*)RBTreeDecrement(pLowerBound);
        else {
            MapIterator itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult(itResult, true);
        }
    }
    if (mCompare(extractKey(pLowerBound->mValue), extractKey(value))) {
        MapIterator itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult(itResult, true);
    }
    return InsertResult(MapIterator(pLowerBound), false);
}

// @ 0x004E47A0
MapIterator KeyMap::DoInsertValue(MapIterator position, const value_type& value, true_type)
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
// intrusive_ptr<DefaultRefCounted>
// ---------------------------------------------------------------------------
struct DefaultRefCounted {
    void* mpVtable;
    int mnRefCount;
    int AddRef() { ScratchSlots<3>(); return mnRefCount++ + 1; }
    int Release();                                     // 0x00453540
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr& operator=(const intrusive_ptr& ip) { return operator=(ip.mpObject); }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

// @ 0x004E4350
template intrusive_ptr<DefaultRefCounted>& intrusive_ptr<DefaultRefCounted>::operator=(const intrusive_ptr&);

// ---------------------------------------------------------------------------
// fixed node allocator
// ---------------------------------------------------------------------------
struct FixedNodeAllocator {
    uint32_t mPool[5];
    void* mpOverflow;                                  // +0x14
    void* PoolAllocate();                              // 0x004CE850 (fixed_pool_with_overflow::allocate)
    void* allocate(size_t n) {
        ScratchSlots<3>();
        if (n == 0x1C)
            return PoolAllocate();
        return mpOverflow;
    }
    void* allocate(size_t n, size_t alignment, size_t offset) {
        ScratchSlots<3>();
        if (n == 0x1C)
            return PoolAllocate();
        return mpOverflow;
    }
};

// @ 0x004E43C0
void* allocate_memory(FixedNodeAllocator& a, size_t n, size_t alignment)
{
    if (alignment <= 8)
        return a.allocate(n);
    return a.allocate(n, alignment, 0);
}

// ---------------------------------------------------------------------------
// vector<TreeItem>
// ---------------------------------------------------------------------------
struct TreeItem;

struct false_type { false_type() {} };

template <class It> struct generic_iterator {
    It mIterator;
    generic_iterator(const It& x) : mIterator(x) {}
    TreeItem& operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    It base() const { return mIterator; }
};
template <class It>
inline bool operator!=(const generic_iterator<It>& a, const generic_iterator<It>& b) { return a.mIterator != b.mIterator; }

typedef generic_iterator<TreeItem*> TreeItemIter;

// eastl::uninitialized_copy_ptr instance that cl did not inline into vector::operator= (0x004E46C0)
TreeItem* __cdecl uninitialized_copy_ptr_out(TreeItem* first, TreeItem* last, TreeItem* result);

struct TreeItemVector {
    TreeItem* mpBegin;
    TreeItem* mpEnd;
    TreeItem* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t mExtra;

    TreeItemVector(const TreeItemVector& x);           // 0x004E38D0
    ~TreeItemVector();                                 // 0x004E1780
    TreeItemVector& operator=(const TreeItemVector& x);
    TreeItem* DoAllocateAndCopy(size_t n, TreeItem* first, TreeItem* last);

    inline TreeItem* DoAllocate(size_t n) {
        return n ? (TreeItem*)EASTL_Allocate(&mAllocator, n * 0x24, 0, 0) : 0;
    }
    inline void deallocate(void* p, size_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
    inline void DoFree(TreeItem* p, size_t n) {
        if (p)
            deallocate(p, n * 0x24);
    }
};

struct Value64 { uint64_t mBits; };

#pragma pack(push, 4)
struct TreeItem {
    uint32_t mA;
    uint32_t mB;
    union {
        Value64 mValue;
        Value64 mValueAlt;
    };
    TreeItemVector mChildren;

    ~TreeItem() { ScratchSlots<5>(); }
    void* DeletingDtor(unsigned int flags);           // = ??_GTreeItem (0x004E4310)
};
#pragma pack(pop)

inline void* address_of(TreeItem* p) { void* r = p; return r; }

inline void destruct(TreeItem* first, TreeItem* last)
{
    for (; first < last; ++first)
        first->~TreeItem();
}

// Same loop, but through the out-of-line scalar deleting destructor (cl declined to inline it here).
inline void destruct_outofline(TreeItem* first, TreeItem* last)
{
    for (; first < last; ++first)
        first->DeletingDtor(0);
}

#pragma inline_depth(0)
// Not inlined: makes cl emit the scalar deleting destructor ??_GTreeItem (0x004E4310) out of line.
void DestroyTreeItem(TreeItem* p) { p->~TreeItem(); }
#pragma inline_depth()

// @ 0x004E4FD0
TreeItem* copy_impl(TreeItem* first, TreeItem* last, TreeItem* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

inline TreeItem* copy(TreeItem* first, TreeItem* last, TreeItem* result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_impl(first, last, result);
}

// @ 0x004E4F60
TreeItem* copy_backward_impl(TreeItem* first, TreeItem* last, TreeItem* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

// @ 0x004E4AD0
TreeItemIter uninitialized_copy_impl(TreeItemIter first, TreeItemIter last, TreeItemIter dest, false_type)
{
    TreeItemIter currentDest(dest);
    for (; first != last; ++first, ++currentDest) {
        ::new(&*currentDest) TreeItem(*first);
        ScratchSlots<9>();
    }
    return currentDest;
}

inline TreeItem* uninitialized_copy_ptr(TreeItem* first, TreeItem* last, TreeItem* result)
{
    char unused;
    const TreeItemIter i(uninitialized_copy_impl(TreeItemIter(first), TreeItemIter(last), TreeItemIter(result), false_type()));
    ScratchSlots<5>();
    return i.base();
}


// @ 0x004E4A40
TreeItem* TreeItemVector::DoAllocateAndCopy(size_t n, TreeItem* first, TreeItem* last)
{
    TreeItem* const p = DoAllocate(n);
    uninitialized_copy_ptr(first, last, p);
    return p;
}

// @ 0x004E4B90
TreeItem* uninitialized_copy_TreeItem(TreeItem* first, TreeItem* last, TreeItem* result)
{
    for (; first != last; ++first, ++result) {
        ::new(result) TreeItem(*first);
        ScratchSlots<13>();
    }
    return result;
}

// @ 0x004E4700
void uninitialized_fill_n(TreeItem* first, size_t n, const TreeItem& value)
{
    TreeItem* currentDest = first;
    for (; n > 0; --n, ++currentDest) {
        ::new(address_of(currentDest)) TreeItem(value);
        ScratchSlots<13>();
    }
}

// @ 0x004E4410
TreeItemVector& TreeItemVector::operator=(const TreeItemVector& x)
{
    if (&x != this) {
        const size_t n = (size_t)(x.mpEnd - x.mpBegin);
        if (n > (size_t)(mpCapacity - mpBegin)) {
            TreeItem* const pNewData = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            ScratchSlots<4>();
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > (size_t)(mpEnd - mpBegin)) {
            copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr_out(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<12>();
        } else {
            TreeItem* const position = copy(x.mpBegin, x.mpEnd, mpBegin);
            ScratchSlots<4>();
            destruct_outofline(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
