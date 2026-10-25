// src/game/SPGonzago/SPUITools.cpp -- migrated from slice(s) s0107b260, s0107a510, s00e17c10, s004b5690 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUITools.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cSPMission.h"
#include "SP/cInputStrategy.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPPlanetaryArtifact.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, uint32_t n);                     // 0x11e0744 (static CRT memmove)

// ---- items of slice s004b5690 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
void __cdecl EASTL_allocator_deallocate(void* p);                                                // 0xf47380
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, uint32_t n);                     // 0x11e0744 (static CRT memmove)
namespace eastl {
template <typename T, T v> struct integral_constant { static const T value = v; };
}
namespace eastl {
typedef integral_constant<bool, true>  true_type;
}
namespace eastl {
typedef integral_constant<bool, false> false_type;
}
namespace eastl {
struct input_iterator_tag { input_iterator_tag() {} };
}
namespace eastl {
struct forward_iterator_tag : public input_iterator_tag { forward_iterator_tag() {} };
}
namespace eastl {
struct bidirectional_iterator_tag : public forward_iterator_tag { bidirectional_iterator_tag() {} };
}
namespace eastl {
struct random_access_iterator_tag : public bidirectional_iterator_tag { random_access_iterator_tag() {} };
}
namespace eastl {
template <typename T> struct has_trivial_relocate : public false_type {};
}
namespace eastl {
template <typename It> struct Iterator_traits_ref;
}
namespace eastl {
template <typename T> struct Iterator_traits_ref<T*> { typedef T& type; typedef T value_type; };
}
namespace eastl {
template <typename T> struct Iterator_traits_ref<const T*> { typedef const T& type; typedef T value_type; };
}
namespace eastl {
struct sp_vector_allocator_s004b_5690 {
    uint32_t mFlags;
    void deallocate(void* p, uint32_t n)
    {
        if (((uint32_t*)p)[-1]) {
            void* pBlock = p;
            EASTL_allocator_deallocate(pBlock);
        }
    }
};
}
namespace eastl {
void* __cdecl allocate_memory(sp_vector_allocator_s004b_5690& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0
}
namespace eastl {
template <typename T> struct has_trivial_assign : public false_type {};
}
namespace eastl {
template <typename T> struct is_integral : public false_type {};
}
namespace eastl {
class fixed_vector_allocator { public:
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
}
namespace eastl {
void* __cdecl allocate_memory(fixed_vector_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);
}
namespace eastl {
template <typename Iterator>
class generic_iterator { public:
    Iterator mIterator;
    explicit generic_iterator(const Iterator& x) : mIterator(x) {}
    typename Iterator_traits_ref<Iterator>::type operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    const Iterator& base() const { return mIterator; }
};
}
namespace eastl {
template <typename IteratorL, typename IteratorR>
inline bool operator!=(const generic_iterator<IteratorL>& lhs, const generic_iterator<IteratorR>& rhs)
{
    return lhs.base() != rhs.base();
}
}
namespace eastl {
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
}
namespace eastl {
template <typename T>
inline T* copy(const T* first, const T* last, T* result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_impl<bHasTrivialCopy>::do_copy(first, last, result);
}
}
namespace eastl {
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
}
namespace eastl {
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
}
namespace eastl {
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
}
namespace eastl {
template <typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl<bHasTrivialCopy>::do_copy(first, last, resultEnd);
}
}
namespace eastl {
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
}
namespace eastl {
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
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate_start(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_start(first, last, dest);
}
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_commit(first, last, dest);
}
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate(T* first, T* last, T* dest)
{
    T* result = uninitialized_relocate_start(first, last, dest);
    uninitialized_relocate_commit(first, last, dest);
    return result;
}
}
namespace eastl {
template <typename T, typename Allocator>
struct VectorBase_s004b_5690 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    ~VectorBase_s004b_5690();                                                   // 0x455290 (for Entry32)
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
}
namespace eastl {
template <typename T, typename Allocator>
class vector_s004b_5690 : public VectorBase_s004b_5690<T, Allocator> { public:
    typedef VectorBase_s004b_5690<T, Allocator> base_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    using base_type::mAllocator;

    ~vector_s004b_5690() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
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
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
};
}
namespace eastl {
template <typename T, typename Allocator>
void vector_s004b_5690<T, Allocator>::DoAssignFromIterator(const T* first, const T* last, input_iterator_tag)
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
}
namespace eastl {
template <typename T, typename Allocator>
void vector_s004b_5690<T, Allocator>::DoInsertValue(T* position, const T& value)
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
}
namespace SP {
class cPropertyList_s004b_5690 { public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace EA {
template<class T> class AutoRefCount_s004b_5690 { public:
    T* mpObject;
    AutoRefCount_s004b_5690(const AutoRefCount_s004b_5690& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004b_5690& operator=(const AutoRefCount_s004b_5690& x) { return operator=(x.mpObject); }
    AutoRefCount_s004b_5690& operator=(T* pObject) {
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
namespace eastl {
 template<> struct has_trivial_relocate<EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690> > : public true_type {}; 
}
namespace eastl {
template <typename T> struct less_s004b_5690 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
template <typename Pair> struct use_first_s004b_5690 { const typename Pair::first_type& operator()(const Pair& x) const { return x.first; } };
}
namespace eastl {
template <typename T1, typename T2> struct pair_s004b_5690 {
    typedef T1 first_type;
    T1 first;
    T2 second;
    pair_s004b_5690(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
struct rbtree_node_base_s004b_5690 {
    rbtree_node_base_s004b_5690* mpNodeRight;
    rbtree_node_base_s004b_5690* mpNodeLeft;
    rbtree_node_base_s004b_5690* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template <typename Value> struct rbtree_node_s004b_5690 : public rbtree_node_base_s004b_5690 {
    Value mValue;
};
}
namespace eastl {
template <typename Value>
struct rbtree_iterator_s004b_5690 {
    typedef rbtree_node_s004b_5690<Value> node_type;
    node_type* mpNode;
    explicit rbtree_iterator_s004b_5690(const node_type* pNode);                // 0x566c50
    rbtree_iterator_s004b_5690(const rbtree_iterator_s004b_5690& x);                       // 0x5673e0
    rbtree_iterator_s004b_5690& operator++();                                   // 0x422c50
    Value& operator*() const { return mpNode->mValue; }
};
}
namespace eastl {
rbtree_node_base_s004b_5690* __cdecl RBTreeDecrement(const rbtree_node_base_s004b_5690* pNode);                                     // 0x9215c0
}
namespace eastl {
void __cdecl RBTreeInsert(rbtree_node_base_s004b_5690* pNode, rbtree_node_base_s004b_5690* pNodeParent, rbtree_node_base_s004b_5690* pNodeAnchor, int insertionSide);  // 0x9216a0
}
namespace eastl {
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
}
namespace eastl {
class allocator_s004b_5690 { public:
    void deallocate(void* p, uint32_t n) { void* pBlock = p; EASTL_allocator_deallocate(pBlock); }
};
}
namespace eastl {
void* __cdecl allocate_memory(allocator_s004b_5690& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0
}
namespace eastl {
template <typename Key, typename Value, typename Compare, typename ExtractKey>
class rbtree_s004b_5690 {
public:
    typedef rbtree_node_s004b_5690<Value> node_type;
    typedef rbtree_iterator_s004b_5690<Value> iterator;
    typedef Value value_type;
    typedef Key key_type;
    typedef ExtractKey extract_key;
    typedef allocator_s004b_5690 allocator_type;
    typedef eastl::pair_s004b_5690<iterator, bool> insert_return_type;

    Compare mCompare;
    rbtree_node_base_s004b_5690 mAnchor;
    uint32_t mnSize;
    allocator_type mAllocator;

    rbtree_s004b_5690(const allocator_type& allocator_s004b_5690);
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
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::insert_return_type rbtree_s004b_5690<K, V, C, E>::DoInsertValue(const value_type& value, true_type)
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
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
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
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::node_type* rbtree_s004b_5690<K, V, C, E>::DoCreateNode(const value_type& value)
{
    node_type* const pNode = DoAllocateNode();
    ::new(&pNode->mValue) value_type(value);
    return pNode;
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
rbtree_s004b_5690<K, V, C, E>::rbtree_s004b_5690(const allocator_type& allocator_s004b_5690)
    : mAnchor(), mnSize(0)
{
    reset();
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::lower_bound(const key_type& key)
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
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::DoInsertValue(iterator position, const value_type& value, true_type)
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
}
struct NukeMapped { ~NukeMapped(); uint32_t d[3]; };
typedef eastl::pair_s004b_5690<const uint32_t, NukeMapped> NukePair;
typedef eastl::rbtree_s004b_5690<uint32_t, NukePair, eastl::less_s004b_5690<uint32_t>, eastl::use_first_s004b_5690<NukePair> > NukeTree;
template void NukeTree::DoNuke(NukeTree::node_type*);
// ---- items of slice s004b5690 end

// ---- items of slice s00e17c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void   FUN_00810590(void *layout, int v, int f); // 0x00810590 cSPUILayout::SetVisibility
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void   FUN_00e30990(void *o, u32 arg);           // 0x00e30990
struct cPanelHead0c {               // +0x00
    void **m_vtbl00;                // +0x00
    void  *m_sub04;                 // +0x04
    void  *m_slotVtbl08;            // +0x08
};
struct cPanelMsg0c {                // +0x0c  (OnMessage's this)
    void  *m_slotVtbl0c;            // +0x0c
    u32    m_field10;               // +0x10
    void  *m_field14;               // +0x14
    void  *m_layout;                // +0x18
    void  *m_card;                  // +0x1c

    char   OnMessage(u32 msg, void *arg); // 0x00e18600
};
struct cPanelMsg24 {                // +0x20
    void  *m_handlerObj;            // +0x20
};
struct cPanelHandler24 {            // +0x24  (HandleMessage's this)
    void  *m_handlerArg1;           // +0x24

    char   HandleMessage(u32 msg, void *arg); // 0x00e18380
};
struct cUIMissionCardPanel : cPanelHead0c, cPanelMsg0c, cPanelMsg24, cPanelHandler24 {
    union {                 // +0x28: message-handler view / card-vector view
        struct {
            void *m_handlerArg2; // +0x28
            u32   m_handlerN;    // +0x2c
            void *m_handlerArg4; // +0x30
        };
        struct {
            void **m_vec28;      // +0x28 vector begin
            void **m_vec2c;      // +0x2c vector end
            union {              // +0x30: vector capacity / layout object
                void **m_vec30;
                void  *m_visObj;
            };
        };
    };
    void *m_treeBegin34;    // +0x34
    void *m_curMission;     // +0x38
    void *m_field3c;        // +0x3c
    void *m_treeBase40;     // +0x40
    u8    m_pad44[0x14];
    void *m_field58;        // +0x58
    void *m_field5c;        // +0x5c
    u8    m_pad60[0x14];
    void *m_tree74;         // +0x74

    void SetVisibleSlot(int v);          // 0x00e18860
    void ShutdownCard();                 // 0x00e18810
    void ClearTree();                    // 0x00e18a90
    void *FindMission(u32 id);           // 0x00e18b10
    bool  ShouldShow(u32 id);            // 0x00e18c70
    void  ForEach(u32 a, u32 b);         // 0x00e18ac0
    void  Refresh();                     // 0x00e17df0
    void  UpdateCardDetails(void *mission); // 0x00e17e40
    void  ShutdownA();                   // 0x00e18a30
    void  ShutdownB();                   // 0x00e18b50
    void  SetSlotAndMission(u32 slot); // 0x00e18cb0
    void *InitHints(void *param);        // 0x00e188b0
    void  DestroyMembers();              // 0x00e18980
    void *Construct();                   // 0x00e18bb0
    bool  RemoveMissionCard(void *mission); // 0x00e17fb0
    void *AddMissionCard(u32 mission);   // 0x00e18150
    void *SetupMissionCard(void *mission, u32 a, u32 b, char c); // 0x00e18200
    void  RefreshFromMissionList();      // 0x00e184d0
    void  OnNotify(u32 a, u32 b, u32 c, u32 d); // 0x00e186d0
};
void cUIMissionCardPanel::ForEach(u32 a, u32 b)
{
    if (m_field58 != 0) {
        FUN_00e30990(m_field58, b);
    }
    void *node = m_treeBase40;
    void *base = (u8 *)this + 0x3c;
    while (node != base) {
        void *obj = *(void **)((u8 *)node + 0x14);
        ((void (__thiscall *)(void *, u32))(*(void ***)obj)[0x18 / 4])(obj, b);
        node = FUN_00921580(node);
    }
}
// ---- items of slice s00e17c10 end

// ---- items of slice s0107a510 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cSPUITools {
public:
    void GetToolAvailability();
};
}
namespace UTFWin {
class InteractiveWinProc {
public:
    virtual void v000();                                 // +0x00
    void OnWinProcAdd(void* pWin);                       // 0x010829f0
};  // namespace UTFWin
}
class FeedList {
public:
    virtual void v000();                                 // +0x00
    virtual void Release();                              // +0x04
    void FUN_006628d0();                                 // 0x006628d0
    void FUN_00663350(void* pWin);                       // 0x00663350
};
class cToolSub {
public:
    void FUN_00e0a5c0();                                 // 0x00e0a5c0

    uint8_t mPayload[0x74];                              // +0x00 .. +0x73
};
class cUITimedTooltip {
public:
    void UpdateTimeoutA();                               // 0x00e36540
    void Shutdown();                                     // 0x00e36500

    uint8_t mPayload[0x8c];                              // +0x00 .. +0x8b
};
class cToolWindow : public UTFWin::InteractiveWinProc {
public:
    void FUN_0107adf0();
    void FUN_0107ae40(void* pWin);
    void ShutdownCard();                                 // 0x00e18810

    uint8_t          pad004[0x3c];                       // +0x004 .. +0x03f
    bool             mFlag40;                            // +0x040
    uint8_t          pad041[3];                          // +0x041 .. +0x043
    cToolSub         mSub44;                             // +0x044 .. +0x0b7
    cUITimedTooltip  mTooltip;                           // +0x0b8 .. +0x143
    FeedList*        mpFeedList;                         // +0x144
};
// ---- items of slice s0107a510 end

// ---- items of slice s0107b260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
class cUIObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void* GetItem();       // +0x1c
    virtual uint32_t GetTypeId();  // +0x20
};
class cToolsEvent {
public:
    cUIObject* mpObject;         // +0x00
    uint32_t mnPad04;            // +0x04
    uint32_t mnType;             // +0x08
    uint32_t mnPad0c;            // +0x0c
    void* mpCard;                // +0x10
};
class cLeftPanel {
public:
    void Reset();                // 0x00e36620
};
class cSelectionManager {
public:
    void Select(void* pObject);  // 0x00e30a60
};
class cNounManager {
public:
    uint8_t mnPad00[0x5c];          // +0x000
    cSelectionManager* mpSelection; // +0x05c
};
cNounManager* NounManager();        // 0x00b3d3f0
class cSPUITools_s0107_b260 {
public:
    __declspec(noinline) bool PopulateSelected(cUIObject* pObject); // 0x0107b260
    __declspec(noinline) void PopulateRight();                      // 0x0107b760
    void Open(uint32_t nSlot);                                      // 0x0107bb00
};
class cToolsPanelLeft {
public:
    uint8_t mnPad00[0xb0];       // +0x000
    cLeftPanel mLeftPanel;       // +0x0b0
    bool PopulateLeft(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107b6f0
};
// ---- items of slice s0107b260 end

// @ 0x004b6000
template void eastl::vector_s004b_5690<EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>, eastl::sp_vector_allocator_s004b_5690>::DoInsertValue(EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>*, const EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>&)
;

// @ 0x00e18860
void cUIMissionCardPanel::SetVisibleSlot(int v)
{
    if (m_layout != 0) {
        return ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 1);
    }
}

// @ 0x0107ac20
void __cdecl FUN_0107ac20()
{
}

// @ 0x0107ac90
void __cdecl FUN_0107ac90()
{
}

// @ 0x0107adf0
void __thiscall cToolWindow::FUN_0107adf0()
{
    if (mpFeedList) {
        mpFeedList->FUN_006628d0();
        FeedList* pOld = mpFeedList;
        if (pOld) {
            mpFeedList = 0;
            pOld->Release();
        }
    }
    mSub44.FUN_00e0a5c0();
    mTooltip.Shutdown();
    ShutdownCard();
}

// @ 0x0107ae40
void __thiscall cToolWindow::FUN_0107ae40(void* pWin)
{
    OnWinProcAdd(pWin);
    if (mFlag40) {
        mTooltip.UpdateTimeoutA();
        mpFeedList->FUN_00663350(pWin);
    }
}

// @ 0x0107ae70
void __cdecl FUN_0107ae70()
{
}

// @ 0x0107af00
void __cdecl FUN_0107af00()
{
}

// @ 0x0107afa0
void __cdecl FUN_0107afa0()
{
}

// @ 0x0107b120
void __thiscall SP::cSPUITools::GetToolAvailability()
{
}

// @ 0x0107b6f0
bool cToolsPanelLeft::PopulateLeft(uint32_t nMessage, cToolsEvent* pEvent)
{
    (void)nMessage;
    switch (pEvent->mnType) {
    case 0x1b:
        if (pEvent->mpObject->GetTypeId() == 0x51aff90) {
            cSelectionManager* pSelection = NounManager()->mpSelection;
            void* pItem = pEvent->mpObject->GetItem();
            pSelection->Select(pItem);
            ((cSPUITools_s0107_b260*)((char*)this - 8))->PopulateSelected(pEvent->mpObject);
        }
        break;
    case 0x1c:
        mLeftPanel.Reset();
        break;
    default:
        break;
    }
    return false;
}
