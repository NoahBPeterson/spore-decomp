// Slice s004b5690: EASTL vector / rbtree template instances (unoptimized module, x87 floats).
// Module flags: /Od /Ob1 /MD /Gy /TP (no /arch, no /EHsc).
// At /Od the stack-slot order of locals (incl. those of inlined EASTL helpers) depends on the
// identifiers, so some local names were chosen to reproduce the original frame layouts.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

void __cdecl EASTL_allocator_deallocate(void* p);                                                // 0xf47380
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, uint32_t n);                     // 0x11e0744 (static CRT memmove)

// ---------------------------------------------------------------------------------------------
// Mini-EASTL (2008-era) pieces used by the vector instances below.
// ---------------------------------------------------------------------------------------------
inline void operator delete(void* p) { EASTL_allocator_deallocate(p); }

namespace eastl {
template <typename T, T v> struct integral_constant { static const T value = v; };
typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;
struct input_iterator_tag { input_iterator_tag() {} };
struct forward_iterator_tag : public input_iterator_tag { forward_iterator_tag() {} };
struct bidirectional_iterator_tag : public forward_iterator_tag { bidirectional_iterator_tag() {} };
struct random_access_iterator_tag : public bidirectional_iterator_tag { random_access_iterator_tag() {} };
template <typename T> struct has_trivial_relocate : public false_type {};
template <typename It> struct Iterator_traits_ref;
template <typename T> struct Iterator_traits_ref<T*> { typedef T& type; typedef T value_type; };
template <typename T> struct Iterator_traits_ref<const T*> { typedef const T& type; typedef T value_type; };

struct sp_vector_allocator {
    uint32_t mFlags;
    void deallocate(void* p, uint32_t n)
    {
        if (((uint32_t*)p)[-1]) {
            void* pBlock = p;
            EASTL_allocator_deallocate(pBlock);
        }
    }
};
void* __cdecl allocate_memory(sp_vector_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0

template <typename T> struct has_trivial_assign : public false_type {};
template <typename T> struct is_integral : public false_type {};

struct fixed_vector_allocator {
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p, uint32_t n)
    {
        if (p != mpPoolBegin) {
            void* pBlock = p;
            EASTL_allocator_deallocate(pBlock);
        }
    }
};
void* __cdecl allocate_memory(fixed_vector_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);

template <typename Iterator>
struct generic_iterator {
    Iterator mIterator;
    explicit generic_iterator(const Iterator& x) : mIterator(x) {}
    typename Iterator_traits_ref<Iterator>::type operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    const Iterator& base() const { return mIterator; }
};
template <typename IteratorL, typename IteratorR>
inline bool operator!=(const generic_iterator<IteratorL>& lhs, const generic_iterator<IteratorR>& rhs)
{
    return lhs.base() != rhs.base();
}

template <bool bHasTrivialCopy>
struct copy_impl
{
    template <typename T>
    static T* do_copy(const T* first, const T* last, T* result)
    {
        for (; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
};
template <typename T>
inline T* copy(const T* first, const T* last, T* result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_impl<bHasTrivialCopy>::do_copy(first, last, result);
}

namespace Internal {
template <typename T, typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest, false_type)
{
    ForwardIterator currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new(&*currentDest) T(*first);
    ScratchSlots<4>();
    return currentDest;
}
}

template <typename First, typename Last, typename Result>
Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    typedef typename Iterator_traits_ref<Result>::value_type value_type;
    const generic_iterator<Result> i(Internal::uninitialized_copy_impl<value_type>(generic_iterator<First>(first),
                                                                                   generic_iterator<Last>(last),
                                                                                   generic_iterator<Result>(result),
                                                                                   has_trivial_assign<value_type>()));
    return i.base();
}

template <bool bHasTrivialCopy>
struct copy_backward_impl
{
    template <typename T>
    static T* do_copy(T* first, T* last, T* resultEnd)
    {
        while (last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
};

template <typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl<bHasTrivialCopy>::do_copy(first, last, resultEnd);
}

template <bool hasTrivialRelocate>
struct uninitialized_relocate_impl
{
    template <typename T>
    static T* do_move_start(T* first, T* last, T* dest)
    {
        for (; first != last; ++first, ++dest)
            ::new(dest) T(*first);
        return dest;
    }
    template <typename T>
    static T* do_move_commit(T* first, T* last, T* dest)
    {
        for (; first != last; ++first, ++dest)
            (*first).~T();
        return dest;
    }
};
template <>
struct uninitialized_relocate_impl<true>
{
    template <typename T>
    static T* do_move_start(T* first, T* last, T* dest)
    {
        return (T*)((last - first) * sizeof(T) + (char*)memmove_nd(dest, first, (uint32_t)((char*)last - (char*)first)));
    }
    template <typename T>
    static T* do_move_commit(T* first, T* last, T* dest)
    {
        return dest;
    }
};

template <typename T>
inline T* uninitialized_relocate_start(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_start(first, last, dest);
}
template <typename T>
inline T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_commit(first, last, dest);
}
template <typename T>
inline T* uninitialized_relocate(T* first, T* last, T* dest)
{
    T* result = uninitialized_relocate_start(first, last, dest);
    uninitialized_relocate_commit(first, last, dest);
    return result;
}

template <typename T, typename Allocator>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    ~VectorBase();                                                   // 0x455290 (for Entry32)
    T* DoAllocate(uint32_t n)
    {
        return n ? (T*)allocate_memory(mAllocator, n * sizeof(T), 4, 0) : 0;
    }
    void DoFree(T* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    uint32_t GetNewCapacity(uint32_t currentCapacity)
    {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
};

template <typename T, typename Allocator>
struct vector : public VectorBase<T, Allocator> {
    typedef VectorBase<T, Allocator> base_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    using base_type::mAllocator;

    ~vector() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* erase(T* first, T* last);                                      // 0x4b5570 (Entry32)
    T* DoRealloc(uint32_t n, const T* first, const T* last);          // 0x4b74d0 (Entry32)
    const T* begin() const { return mpBegin; }
    const T* end() const { return mpEnd; }
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) { DoAssign(first, last, is_integral<InputIterator>()); }
    template <typename InputIterator>
    void DoAssign(InputIterator first, InputIterator last, const false_type&) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    void DoAssignFromIterator(const T* first, const T* last, input_iterator_tag);   // 0x4b7290 (Entry32)
    static void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    void DoInsertValue(T* position, const T& value);
};

template <typename T, typename Allocator>
void vector<T, Allocator>::DoAssignFromIterator(const T* first, const T* last, input_iterator_tag)
{
    const uint32_t n = (uint32_t)(last - first);
    ScratchSlots<10>();     // unused slots of inlined helpers in the original
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoRealloc(n, first, last);
        DoDestroyValues(mpBegin, mpEnd);
        this->DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        T* const pNewEnd = eastl::copy(first, last, mpBegin);
        DoDestroyValues(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
    } else {
        const T* position = first + (mpEnd - mpBegin);
        eastl::copy(first, position, mpBegin);
        mpEnd = eastl::uninitialized_copy_ptr(position, last, mpEnd);
    }
    ScratchSlots<16>();
}

template <typename T, typename Allocator>
void vector<T, Allocator>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) T(*(mpEnd - 1));
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = this->GetNewCapacity(nPrevSize);
        T* const pNewData = this->DoAllocate(nNewSize);
        T* pNewEnd = eastl::uninitialized_relocate(mpBegin, position, pNewData);
        ::new(pNewEnd) T(value);
        pNewEnd = eastl::uninitialized_relocate(position, mpEnd, ++pNewEnd);
        this->DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
} // namespace eastl

// ---- element types ----
struct Vec3f {
    float x, y, z;
    Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Element28 {
    uint32_t d[7];
    Element28(const Element28& x);                                   // 0x440ff0
};
struct Entry32 {
    uint32_t mKey;
    Element28 mValue;
};
// fixed_vector<Entry32, 8>-like container: vector header followed by its inline buffer.
struct EntryFixedVector : public eastl::vector<Entry32, eastl::fixed_vector_allocator> {
    uint32_t mBuffer[(0x118 - 0x14) / 4];
    EntryFixedVector(const EntryFixedVector& x);                     // 0x4b62a0
    EntryFixedVector& operator=(const EntryFixedVector& x)
    {
        ScratchSlots<6>();
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};

struct Flag { bool mbValue; };
struct Record11c {
    EntryFixedVector mEntries;
    Flag mFlag;
    Record11c(const Record11c& x) : mEntries(x.mEntries), mFlag(x.mFlag) { ScratchSlots<5>(); }
    Record11c& operator=(const Record11c& x);
};

// @ 0x4b6340
Record11c& Record11c::operator=(const Record11c& x)
{
    mEntries = x.mEntries;
    Flag flag = x.mFlag;
    mFlag = flag;
    return *this;
}


namespace SP {
struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
};
}
namespace EA {
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
}
namespace eastl { template<> struct has_trivial_relocate<EA::AutoRefCount<SP::cPropertyList> > : public true_type {}; }


// ---------------------------------------------------------------------------------------------
// rbtree pieces
// ---------------------------------------------------------------------------------------------
namespace eastl {
template <typename T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
template <typename T> struct use_self { const T& operator()(const T& x) const { return x; } };
template <typename Pair> struct use_first { const typename Pair::first_type& operator()(const Pair& x) const { return x.first; } };
template <typename T1, typename T2> struct pair {
    typedef T1 first_type;
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
template <typename Value> struct rbtree_node : public rbtree_node_base {
    Value mValue;
};

template <typename Value>
struct rbtree_iterator {
    typedef rbtree_node<Value> node_type;
    node_type* mpNode;
    explicit rbtree_iterator(const node_type* pNode);                // 0x566c50
    rbtree_iterator(const rbtree_iterator& x);                       // 0x5673e0
    rbtree_iterator& operator++();                                   // 0x422c50
    Value& operator*() const { return mpNode->mValue; }
};

rbtree_node_base* __cdecl RBTreeDecrement(const rbtree_node_base* pNode);                                     // 0x9215c0
void __cdecl RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, int insertionSide);  // 0x9216a0

enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };

struct allocator {
    void deallocate(void* p, uint32_t n) { void* pBlock = p; EASTL_allocator_deallocate(pBlock); }
};
void* __cdecl allocate_memory(allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0

template <typename Key, typename Value, typename Compare, typename ExtractKey>
class rbtree {
public:
    typedef rbtree_node<Value> node_type;
    typedef rbtree_iterator<Value> iterator;
    typedef Value value_type;
    typedef Key key_type;
    typedef ExtractKey extract_key;
    typedef allocator allocator_type;
    typedef eastl::pair<iterator, bool> insert_return_type;

    Compare mCompare;
    rbtree_node_base mAnchor;
    uint32_t mnSize;
    allocator_type mAllocator;

    rbtree(const allocator_type& allocator);
    void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = kRBTreeColorRed;
        mnSize = 0;
    }
    enum { kRBTreeColorRed = 0 };

    iterator lower_bound(const key_type& key);
    iterator DoInsertValue(iterator position, const value_type& value, true_type);
    insert_return_type DoInsertValue(const value_type& value, true_type);
    insert_return_type insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    iterator DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft);
    node_type* DoCreateNode(const value_type& value);
    node_type* DoAllocateNode() { return (node_type*)allocate_memory(mAllocator, sizeof(node_type), 4, 0); }
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        ScratchSlots<9>();
        mAllocator.deallocate(pNode, sizeof(node_type));
    }
    void DoNuke(node_type* pNode);
};

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::insert_return_type rbtree<K, V, C, E>::DoInsertValue(const value_type& value, true_type)
{
    extract_key extractKey;
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    node_type* pLowerBound = (node_type*)&mAnchor;
    node_type* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = mCompare(extractKey(value), extractKey(pCurrent->mValue));
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (node_type*)mAnchor.mpNodeLeft)
            pLowerBound = (node_type*)RBTreeDecrement(pLowerBound);
        else {
            const iterator itResult(DoInsertValueImpl(pLowerBound, value, false));
            return insert_return_type(itResult, true);
        }
    }

    if (mCompare(extractKey(pLowerBound->mValue), extractKey(value))) {
        const iterator itResult(DoInsertValueImpl(pParent, value, false));
        return insert_return_type(itResult, true);
    }

    return insert_return_type(iterator(pLowerBound), false);
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator rbtree<K, V, C, E>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
{
    RBTreeSide side;
    extract_key extractKey;

    if (bForceToLeft || (pNodeParent == &mAnchor) || mCompare(extractKey(value), extractKey(pNodeParent->mValue)))
        side = kRBTreeSideLeft;
    else
        side = kRBTreeSideRight;

    node_type* const pNodeNew = DoCreateNode(value);
    RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
    mnSize++;

    return iterator(pNodeNew);
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::node_type* rbtree<K, V, C, E>::DoCreateNode(const value_type& value)
{
    node_type* const pNode = DoAllocateNode();
    ::new(&pNode->mValue) value_type(value);
    return pNode;
}

template <typename K, typename V, typename C, typename E>
rbtree<K, V, C, E>::rbtree(const allocator_type& allocator)
    : mAnchor(), mnSize(0)
{
    reset();
}

template <typename K, typename V, typename C, typename E>
void rbtree<K, V, C, E>::DoNuke(node_type* pNode)
{
    while (pNode) {
        DoNuke((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator rbtree<K, V, C, E>::lower_bound(const key_type& key)
{
    extract_key extractKey;
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while (pCurrent) {
        if (!mCompare(extractKey(pCurrent->mValue), key)) {
            pRangeEnd = pCurrent;
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        } else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator(pRangeEnd);
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator rbtree<K, V, C, E>::DoInsertValue(iterator position, const value_type& value, true_type)
{
    extract_key extractKey;
    if ((position.mpNode != mAnchor.mpNodeRight) && (position.mpNode != &mAnchor)) {
        iterator itNext(position);
        ++itNext;
        if (mCompare(extractKey(*position), extractKey(value))) {
            if (mCompare(extractKey(value), extractKey(*itNext))) {
                if (position.mpNode->mpNodeRight)
                    return DoInsertValueImpl(itNext.mpNode, value, true);
                return DoInsertValueImpl(position.mpNode, value, false);
            }
        }
        return insert(value).first;
    }
    if (mnSize && mCompare(extractKey(((node_type*)mAnchor.mpNodeRight)->mValue), extractKey(value)))
        return DoInsertValueImpl((node_type*)mAnchor.mpNodeRight, value, false);
    return insert(value).first;
}
} // namespace eastl

// Tree whose mapped value (node +0x14) has a non-trivial destructor (0x4b5610).
struct NukeMapped { ~NukeMapped(); uint32_t d[3]; };
typedef eastl::pair<const uint32_t, NukeMapped> NukePair;
typedef eastl::rbtree<uint32_t, NukePair, eastl::less<uint32_t>, eastl::use_first<NukePair> > NukeTree;

// Key16: 16-byte key with an out-of-line operator< (0x4b52b0).
struct Key16 {
    float x, y, z, w;
    Key16(const Key16& k) : x(k.x), y(k.y), z(k.z), w(k.w) {}
    bool operator<(const Key16& k) const;                            // 0x4b52b0
};
typedef eastl::rbtree<Key16, Key16, eastl::less<Key16>, eastl::use_self<Key16> > Key16Tree;

// uint32_t-keyed maps.
struct Mapped0 { uint32_t d[4]; };
struct Mapped14 { uint32_t d[5]; Mapped14(const Mapped14& x); };   // copy ctor 0x4b63b0
struct Pair14 {
    typedef uint32_t first_type;
    const uint32_t first;
    Mapped14 second;
    Pair14(const Pair14& p) : first(p.first), second(p.second) { ScratchSlots<13>(); }
};
typedef eastl::rbtree<uint32_t, Pair14, eastl::less<uint32_t>, eastl::use_first<Pair14> > UIntTree14;
struct Pair28 {
    typedef Element28 first_type;
    Element28 first;
    uint32_t second;
    Pair28(const Pair28& p) : first(p.first), second(p.second) { ScratchSlots<4>(); }
};
typedef eastl::rbtree<Element28, Pair28, eastl::less<Element28>, eastl::use_first<Pair28> > Elem28Tree;
struct Mapped1 { uint32_t d[7]; };
typedef eastl::pair<const uint32_t, Mapped0> Pair0;
typedef eastl::pair<const uint32_t, Mapped1> Pair1;
typedef eastl::rbtree<uint32_t, Pair0, eastl::less<uint32_t>, eastl::use_first<Pair0> > UIntTree0;
typedef eastl::rbtree<uint32_t, Pair1, eastl::less<uint32_t>, eastl::use_first<Pair1> > UIntTree1;

// @ 0x4b5ad0
template void eastl::vector<Vec3f, eastl::sp_vector_allocator>::DoInsertValue(Vec3f*, const Vec3f&);
// @ 0x4b5690
template void eastl::vector<Record11c, eastl::sp_vector_allocator>::DoInsertValue(Record11c*, const Record11c&);
// @ 0x4b64b0
template Record11c* eastl::uninitialized_relocate(Record11c*, Record11c*, Record11c*);
// @ 0x4b66b0
template Vec3f* eastl::uninitialized_relocate(Vec3f*, Vec3f*, Vec3f*);
// @ 0x4b6000
template void eastl::vector<EA::AutoRefCount<SP::cPropertyList>, eastl::sp_vector_allocator>::DoInsertValue(EA::AutoRefCount<SP::cPropertyList>*, const EA::AutoRefCount<SP::cPropertyList>&);
// @ 0x4b5980
template eastl::rbtree<Key16, Key16, eastl::less<Key16>, eastl::use_self<Key16> >::rbtree(const eastl::allocator&);
// @ 0x4b5a20
template void Key16Tree::reset();
// @ 0x4b5a60
template void NukeTree::DoNuke(NukeTree::node_type*);
// @ 0x4b5e90
template UIntTree0::iterator UIntTree0::lower_bound(const uint32_t&);
// @ 0x4b5f40
template Key16Tree::iterator Key16Tree::lower_bound(const Key16&);
// @ 0x4b6550
template UIntTree0::iterator UIntTree0::DoInsertValue(UIntTree0::iterator, const Pair0&, eastl::true_type);
// @ 0x4b6710
template UIntTree1::iterator UIntTree1::DoInsertValue(UIntTree1::iterator, const Pair1&, eastl::true_type);

// ---------------------------------------------------------------------------------------------
// Destroy a range of owning pointers to polymorphic objects.
// ---------------------------------------------------------------------------------------------
struct Deletable {
    virtual void _v0();
    virtual void Destroy();
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct DeletablePtr {
    Deletable* p;
    ~DeletablePtr() { if (p) p->Destroy(); }
    static void operator delete(void* q) { EASTL_allocator_deallocate(q); }
};
struct DeletablePtrRange {
    void DestroyRange(DeletablePtr* first, DeletablePtr* last);
};

// @ 0x4b5fb0
void DeletablePtrRange::DestroyRange(DeletablePtr* first, DeletablePtr* last)
{
    for (; first < last; ++first)
        first->~DeletablePtr();
}

// ---------------------------------------------------------------------------------------------
// EA::Variant assignment from a string
// ---------------------------------------------------------------------------------------------
namespace EA {
struct string8 { char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator;
    string8& assign(const char* first, const char* last); };                       // 0x454cb0
struct Variant {
    string8 mString;
    uint16_t mFlags;
    uint16_t mType;
    void Destruct(bool b);                                                          // 0x93db80
    void Construct(int type, int kind, const void* p, int size, bool b);            // 0x93dd80
    Variant& operator=(const string8& s);
};

// @ 0x4b5dd0
Variant& Variant::operator=(const string8& s)
{
    if (mFlags & 4)
        Destruct(true);
    if (false) {
        if (&s != &mString)
            mString.assign(s.mpBegin, s.mpEnd);
        mType = 0x12;
        mFlags = (mFlags & 2) | 9;
    } else
        Construct(0x12, 9, &s, 0x10, true);
    return *this;
}
}

