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
#include <intrin.h>

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
extern "C" void   FUN_00811ad0(void *layout, int f);        // 0x00811ad0 cSPUILayout::Shutdown
extern "C" bool   FUN_00810070(void *layout);               // 0x00810070 cSPUILayout::IsVisible
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" bool   FUN_008120d0(void *layout, void *key, bool b, int c); // 0x008120d0 cSPUILayout::Init
extern "C" void* FUN_008105b0(); // 0x008105b0 FindWindowByID
extern "C" void   FUN_00810570(void *o);                     // 0x00810570
extern "C" void  *FUN_00810000(void *o);                     // 0x00810000 cConnectionDialog ctor
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" bool   FUN_008121b0(void *layout, void *parent, bool b, u32 id); // 0x008121b0 SetParentWin
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
void __fastcall FUN_00e0a640(void* sub);             // 0x00e0a640
void __fastcall FUN_00e0a390(void* sub);             // 0x00e0a390
void __fastcall FUN_00e0a400(void* sub);             // 0x00e0a400
extern "C" void FUN_00e186d0(); // 0x00e186d0 OnNotify
void __fastcall FUN_00e18bb0(void* win);             // 0x00e18bb0 Construct
void __fastcall FUN_00e18980(void* win);             // 0x00e18980 DestroyMembers
void __fastcall FUN_00e18a30(void* win);             // 0x00e18a30 ShutdownA
void __cdecl    FUN_00571db0(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00571db0
extern "C" bool FUN_00e0a4c0(); // 0x00e0a4c0
extern "C" void FUN_00663860(); // 0x00663860 feed AddWindow
void* __cdecl   FUN_00f473a0(int size, const char* name, int a, int b, int c, int d); // operator_new
extern "C" void* FUN_00e36650(); // 0x00e36650
#pragma pack(push, 1)
struct Vec3_s0107 {
    uint32_t x, y, z;
    Vec3_s0107() {}
    Vec3_s0107(const Vec3_s0107& o) : x(o.x), y(o.y), z(o.z) {}
};
#pragma pack(pop)
void  __cdecl    FUN_00e36b30(); // 0x00e36b30
extern "C" void  FUN_00662920();                     // 0x00662920
extern "C" void  FUN_006b54b0();                     // 0x006b54b0 cString::Load
void  __fastcall FUN_006b54c0(void* str);            // 0x006b54c0 cString::c_str
void  __fastcall FUN_006b54d0(void* str);            // 0x006b54d0 cString ctor
void  __fastcall FUN_006b5060(void* str);            // 0x006b5060 cString ctor
extern "C" void* FUN_00663040();                     // 0x00663040 cSPUIFeedList ctor
void  __fastcall FUN_00e364d0(void* tooltip);        // 0x00e364d0 cUITimedTooltip ctor
void  __fastcall FUN_00e36480(void* tooltip);        // 0x00e36480 cUITimedTooltip ctor
class cToolSub {
public:
    void FUN_00e0a5c0();                                 // 0x00e0a5c0

    uint8_t mPayload[0x74];                              // +0x00 .. +0x73
};
class cUITimedTooltip {
public:
    void UpdateTimeoutA();                               // 0x00e36540
    void Shutdown();                                     // 0x00e36500
    void* Init();                                        // 0x00e36550

    uint8_t mPayload[0x8c];                              // +0x00 .. +0x8b
};
class cToolWindow : public UTFWin::InteractiveWinProc {
public:
    void FUN_0107ac20();
    void FUN_0107ac90(int a1, int a2, int a3, int a4);
    void FUN_0107adf0();
    void FUN_0107ae40(void* pWin);
    cToolWindow* FUN_0107ae70();
    void FUN_0107af00();
    void ShutdownCard();                                 // 0x00e18810

    uint8_t          pad004[0x14];                       // +0x004 .. +0x017
    void*            mpLayout;                           // +0x018
    uint8_t          pad01c[0x24];                       // +0x01c .. +0x03f
    bool             mFlag40;                            // +0x040
    uint8_t          pad041[3];                          // +0x041 .. +0x043
    cToolSub         mSub44;                             // +0x044 .. +0x0b7
    cUITimedTooltip  mTooltip;                           // +0x0b8 .. +0x143
    FeedList*        mpFeedList;                         // +0x144
    uint8_t          pad148[0x8c];                       // +0x148 .. +0x1d3 (cString, f_lineY, handle block)

    float   LineY() { return *(float*)((char*)this + 0x118); }
    void*   Layout() { return mpLayout; }
    void*   Handler() { return *(void**)((char*)this + 0x130); }
    void    SetHandler(void* h) { *(void**)((char*)this + 0x130) = h; }
    uint32_t HandlerArg(int n) { return *(uint32_t*)((char*)this + 0x130 + n * 4); }
    void    SetLineY(float v) { *(float*)((char*)this + 0x118) = v; }
    void*   CStr() { return (char*)this + 0x11c; }
    void*   Sub() { return (char*)this + 0x44; }
    void*   Tooltip() { return (char*)this + 0xb8; }
};
// ---- items of slice s0107a510 end

// ---- items of slice s0107b260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
class cSPMission {
public:
    uint8_t mnPad00[0x17c];       // +0x000
    cSPMission* mpParentMission;  // +0x17c
};
class cPropertyValue {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    uint8_t mnPad04[0x0e];       // +0x004
    uint16_t mnType;             // +0x012
    float* GetFloat();           // 0x0041ea70
    int32_t* GetInt();           // 0x0041e990
};
class cPropertyList {
public:
    VSLOT(0)
    virtual void Release();                                            // +0x04
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    virtual bool FindProperty(uint32_t nKey, cPropertyValue** ppValue); // +0x24
};
class cPropertyManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void GetProperty(uint32_t nKey, uint32_t nId,
                             cPropertyList** ppProperty); // +0x2c
};
cPropertyManager* PropertyManager(); // 0x0067de30
void GetToolAvailability(cPropertyList* pProperty, uint32_t* pnTool,
                         uint32_t* pnAvailability); // 0x0107b120
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
class cMissionCard {
public:
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    uint8_t mnPad04[0x178];         // +0x004
    cSPMission* mpParentMission;    // +0x17c
};
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
class cUIMissionCardPanel_s0107_b260 {
public:
    virtual bool OnMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x00e18600
    uint8_t mnPad04[0x138];      // +0x004
    cMissionCard* mpSelectedMission; // +0x13c
};
class cToolsMessage : public cUIMissionCardPanel_s0107_b260 {
public:
    bool OnMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107bc30
};
// ---- items of slice s0107b260 end

// @ 0x004b6000
template void eastl::vector_s004b_5690<EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>, eastl::sp_vector_allocator_s004b_5690>::DoInsertValue(EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>*, const EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690>&)
;

// @ 0x00e18600
char cPanelMsg0c::OnMessage(u32 msg, void *arg)
{
    cUIMissionCardPanel *self = static_cast<cUIMissionCardPanel *>(this);
    char visible = 0;
    if (msg != 0x65ff54a || m_layout == 0) {
        return visible;
    }
    if (*(u32 *)((u8 *)arg + 0x10) != 0x40464100) {
        return visible;
    }
    void *mission = *(void **)((u8 *)arg + 0x18);
    u32 key = m_field10;
    void *cur = ((void *(__thiscall *)(void *, u32))self->m_vtbl00[0x30 / 4])(self, key);
    if (mission != cur) {
        return visible;
    }
    u32 saved14 = (u32)(unsigned long)m_field14;
    void *layout = m_layout;
    u32 savedCard = (u32)(unsigned long)m_card;
    u32 r570 = (u32)(unsigned long)((void *(__thiscall *)(void *))FUN_00810570)(layout);
    visible = ((bool (__thiscall *)(void *))FUN_00810070)(layout) ? 1 : 0;
    if (visible) {
        ((void (__thiscall *)(void *))self->m_vtbl00[0x20 / 4])(self);
    }
    ((void (__thiscall *)(void *))self->m_vtbl00[0x14 / 4])(self);
    ((void (__thiscall *)(void *, u32, u32, u32, u32))self->m_vtbl00[0x10 / 4])(
        self, key, saved14, r570, savedCard);
    if (visible) {
        ((void (__thiscall *)(void *, u32))self->m_vtbl00[0x1c / 4])(self, 0);
    }
    return 1;
}

// @ 0x00e186d0
void cUIMissionCardPanel::OnNotify(u32 a, u32 b, u32 c, u32 d)
{
    (void)c;
    (void)d;
    ((void (__thiscall *)(void *))m_vtbl00[0x14 / 4])(this);
    u32 r = ((u32 (__thiscall *)(void *, u32))m_vtbl00[0x30 / 4])(this, a);
    u32 key0 = a;
    u32 key1 = 0x510a95b;
    u32 key2 = 0x40464100;
    (void)key0;
    (void)key1;
    (void)key2;
    void *raw = operator_new(0x18, 0x13f6b3c, 0, 0, 0, 0);
    void *obj = 0;
    if (raw != 0) {
        obj = ((void *(__thiscall *)(void *))FUN_00810000)(raw);
    }
    m_field10 = a;
    m_field14 = (void *)(unsigned long)b;
    void *old = m_layout;
    if (obj != old) {
        if (obj != 0) {
            ((void (__thiscall *)(void *))(*(void ***)obj)[1])(obj);
        }
        m_layout = obj;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
    u32 k[3];
    k[0] = a;
    k[1] = 0x510a95b;
    k[2] = 0x40464100;
    if (!((bool (__thiscall *)(void *, u32 *, bool, u32))FUN_008120d0)(m_layout, k, false, 0x5b598fa)) {
        ((void (__thiscall *)(void *, u32))FUN_00811ad0)(m_layout, 1);
        if (m_layout != 0) {
            m_layout = 0;
            ((void (__thiscall *)(void *))(*(void ***)obj)[2])(obj);
        }
    }
    ((bool (__thiscall *)(void *, void *, bool, u32))FUN_008121b0)(m_layout, (void *)r, true, 0x5b598fa);
    ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 0);
    void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(
        m_layout, (int)((u32 (__thiscall *)(void *, u32))m_vtbl00[0x34 / 4])(this, a), true);
    if (w != 0) {
        ((void (__thiscall *)(void *, void *))(*(void ***)w)[0x104 / 4])(w, (u8 *)this + 8);
    }
    void *oldCard = m_card;
    if ((void *)r != oldCard) {
        if (r != 0) {
            ((void (__thiscall *)(void *))(*(void ***)r)[0])((void *)r);
        }
        m_card = (void *)r;
        if (oldCard != 0) {
            ((void (__thiscall *)(void *))(*(void ***)oldCard)[1])(oldCard);
        }
    }
}

// @ 0x00e18810
void cUIMissionCardPanel::ShutdownCard()
{
    void *card = m_card;
    if (card != 0) {
        m_card = 0;
        ((void (__thiscall *)(void *))(*(void ***)card)[1])(card);
    }
    void *lay = m_layout;
    if (lay != 0) {
        ((void (__thiscall *)(void *, int))FUN_00811ad0)(lay, 1);
        lay = m_layout;
        if (lay != 0) {
            m_layout = 0;
            ((void (__thiscall *)(void *))(*(void ***)lay)[2])(lay);
        }
    }
    m_field10 = 0xffffffff;
}

// @ 0x00e18860
void cUIMissionCardPanel::SetVisibleSlot(int v)
{
    if (m_layout != 0) {
        return ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 1);
    }
}

// @ 0x0107ac20
void cToolWindow::FUN_0107ac20()
{
    if (!mFlag40)
        return;
    void* h = Handler();
    if (h != 0) {
        SetHandler(0);
        FUN_00571db0(h, HandlerArg(1), HandlerArg(2), HandlerArg(3), HandlerArg(4));
    }
    ((void (__thiscall *)(void *, int))FUN_00662920)(mpFeedList, 0);
    FUN_00e0a640(Sub());
    mFlag40 = false;
    FUN_00e18a30(this);
}

// @ 0x0107ac90
void cToolWindow::FUN_0107ac90(int a1, int a2, int a3, int a4)
{
    ((void (__thiscall *)(void *, int, int, int, int))FUN_00e186d0)(this, a1, a2, a3, a4);
    mFlag40 = false;
    uint32_t key[3] = { 0, 0, 0 };
    ((bool (__thiscall *)(void *, void *, uint32_t *))FUN_00e0a4c0)(Sub(),
        ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(Layout(), 0x5f00928, true), key);
    void* tooltip = Tooltip();
    ((void (__thiscall *)(void *, Vec3_s0107, uint32_t, int, int))FUN_00e36b30)(
        tooltip, *(Vec3_s0107*)0x015b9768, 0x5fd4ce0, 200, 0xfa);
    void* obj = ((void *(__thiscall *)(void *, uint32_t, bool))FUN_00e36650)(tooltip, 0x51a37b8, true);
    float* r = (float*)((void*(__thiscall*)(void*)) (*(void***)obj)[0x38 / 4])(obj);
    SetLineY(r[2] - r[0]);
    ((void (__thiscall *)(void *, uint32_t, uint32_t, int))FUN_006b54b0)(CStr(), 0x2db6dad3, 0x65672cb, 0);
    void* mem = FUN_00f473a0(0x6c, "UI/cSPUIFeedList", 0, 0, 0, 0);
    FeedList* created;
    if (mem != 0)
        created = (FeedList*)((void *(__thiscall *)(void *))FUN_00663040)(mem);
    else
        created = 0;
    void* old = mpFeedList;
    if (created != (FeedList*)old) {
        if (created != 0)
            ((void(__thiscall*)(void*)) (*(void***)created)[0 / 4])(created);
        mpFeedList = created;
        if (old != 0)
            ((void(__thiscall*)(void*)) (*(void***)old)[4 / 4])(old);
    }
    FeedList* feed = mpFeedList;
    ((void (__thiscall *)(void *, void *, uint32_t, uint32_t, uint32_t))FUN_00663860)(
        feed, ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(Layout(), 0x5f00660, true),
        0x1caa6cd5, 0, 0);
    ((void (__thiscall *)(void *, int))FUN_00662920)(mpFeedList, 0);
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
cToolWindow* cToolWindow::FUN_0107ae70()
{
    FUN_00e18bb0(this);
    *(void**)this = (void*)0x0149c67c;
    *((void**)this + 2) = (void*)0x0149c660;
    *((void**)this + 3) = (void*)0x0149c658;
    mFlag40 = false;
    FUN_00e0a390(Sub());
    FUN_00e36480(Tooltip());
    FUN_006b5060(CStr());
    *((void**)this + 0x4c) = 0;
    *((void**)this + 0x4d) = 0;
    *((void**)this + 0x4e) = 0;
    *((void**)this + 0x4f) = 0;
    *((void**)this + 0x50) = 0;
    *((void**)this + 0x51) = 0;
    *((void**)this + 0x52) = 0;
    return this;
}

// @ 0x0107af00
void cToolWindow::FUN_0107af00()
{
    *(void**)this = (void*)0x0149c67c;
    *((void**)this + 2) = (void*)0x0149c660;
    *((void**)this + 3) = (void*)0x0149c658;
    _ReadWriteBarrier();
    void* p = *((void**)this + 0x52);
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    p = *((void**)this + 0x51);
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    void* h = Handler();
    if (h != 0) {
        SetHandler(0);
        FUN_00571db0(h, HandlerArg(1), HandlerArg(2), HandlerArg(3), HandlerArg(4));
    }
    FUN_006b54c0(CStr());
    FUN_00e364d0(Tooltip());
    FUN_00e0a400(Sub());
    FUN_00e18980(this);
}

struct ListNode_s0107_afa0 {
    ListNode_s0107_afa0* mpNext;   // +0x00
    ListNode_s0107_afa0* mpPrev;   // +0x04
    uint32_t mnId;                 // +0x08
};
struct Elem_s0107_afa0 {
    uint8_t mnPad00[0xa0];         // +0x000
    void* mpVtA0;                  // +0x0a0
    uint8_t mnPadA4[0xd8];         // +0x0a4
    uint32_t mn17c;                // +0x17c
};
struct Widget_s0107_afa0 {
    uint8_t mnPad00[0x14];         // +0x000
    uint32_t mn14;                 // +0x014
    uint8_t mnPad18[0x1c];         // +0x018
    ListNode_s0107_afa0 mHead;     // +0x034
    uint8_t mnPad3c[0x108];        // +0x03c
    void* mp144;                   // +0x144
    void* mp148;                   // +0x148
    void FUN_0107afa0();
};
extern "C" void* FUN_00662a20();    // 0x00662a20
extern "C" uint32_t FUN_00664600(); // 0x00664600
extern "C" void* FUN_00664610();    // 0x00664610
extern "C" void  FUN_00666630();    // 0x00666630
extern "C" void  FUN_00662c10();    // 0x00662c10
extern "C" void* FUN_00b3d3f0();    // 0x00b3d3f0 NounManager
extern "C" void  FUN_00e30e20();    // 0x00e30e20
// @ 0x0107afa0
void __thiscall Widget_s0107_afa0::FUN_0107afa0()
{
    void* src = ((void* (__thiscall*)(void*, int))FUN_00662a20)(mp144, 0);
    if (src == 0)
        return;
    uint32_t n = ((uint32_t (__thiscall*)(void*))FUN_00664600)(src);
    for (uint32_t i = 0; i < n; ++i) {
        Elem_s0107_afa0* e = ((Elem_s0107_afa0* (__thiscall*)(void*, uint32_t))FUN_00664610)(src, i);
        int count = 0;
        void* arr = 0;
        bool changed = false;
        ((void (__thiscall*)(void*, int*, void**))FUN_00666630)(src, &count, &arr);
        for (int j = 0; j < count; ++j) {
            int id = *((int*)((char*)arr + j * 12));
            ListNode_s0107_afa0* head = &mHead;
            ListNode_s0107_afa0* node = head->mpNext;
            while (node != head) {
                if (node->mnId == (uint32_t)id)
                    break;
                node = node->mpNext;
            }
            if (node != head) {
                uint32_t v = e->mn17c;
                changed = true;
                cNounManager* mgr = (cNounManager*)FUN_00b3d3f0();
                ((void (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, int, int))FUN_00e30e20)(
                    mgr->mpSelection, (uint32_t)id, v, 0xf45f7d78, 0, 0);
            }
        }
        void* old = mp148;
        if (mp148 == 0 && src != old) {
            if (src != 0)
                ((void (__thiscall*)(void*))(*(void***)src)[0 / 4])(src);
            mp148 = src;
            if (old != 0)
                ((void (__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
        }
        if (changed) {
            ((void (__thiscall*)(void*, uint32_t))(*(void***)e->mpVtA0)[0x50 / 4])(e->mpVtA0, e->mn17c);
            uint32_t v = e->mn17c;
            cNounManager* mgr = (cNounManager*)FUN_00b3d3f0();
            ((void (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, int, int))FUN_00e30e20)(
                mgr->mpSelection, v, mn14, 0x2c765c39, 0, 0);
        }
    }
    ((void (__thiscall*)(void*, void*))FUN_00662c10)(mp144, mp148);
}

extern "C" void*  FUN_01002bd0();   // 0x01002bd0 SpaceGameGet
extern "C" void*  FUN_00a1ad60();   // 0x00a1ad60 GetPlayerInventory
extern "C" uint32_t FUN_00b3d3d0(); // 0x00b3d3d0
extern "C" bool   FUN_00ff3d10();   // 0x00ff3d10
extern "C" bool   FUN_0104cbc0();   // 0x0104cbc0
extern "C" uint32_t FUN_00a02d30(); // 0x00a02d30
extern "C" bool   FUN_0103bef0();   // 0x0103bef0
extern "C" void   FUN_00407190();   // 0x00407190
namespace SP {
struct Key_s0107_b120 {
    int a;
    int b;
    int c;
    Key_s0107_b120() {}
    Key_s0107_b120(const Key_s0107_b120& o) : a(o.a), b(o.b), c(o.c) {}
};
// @ 0x0107b120
bool __cdecl FUN_0107b120(void* pTool, uint32_t* pnTool, uint32_t* pnAvailability)
{
    void* game = FUN_01002bd0();
    void* inv = ((void* (__thiscall*)(void*))FUN_00a1ad60)(game);
    uint32_t player = FUN_00b3d3d0();
    if (pTool == 0 || inv == 0 || player == 0)
        return false;

    *pnAvailability = 0xffffffff;
    typedef void* (__thiscall* Vt68_s0107)(void*, void*);
    Vt68_s0107 fn = (Vt68_s0107)(*(void***)inv)[0x68 / 4];
    Key_s0107_b120 key;
    key.a = *((int*)pTool + 2);
    key.b = 0;
    key.c = 0;
    void* obj = fn(inv, &key);
    if (obj != 0) {
        *pnTool = 3;
        if (!((bool (__thiscall*)(void*))FUN_0104cbc0)(obj))
            goto done_s0107_b120;
        *pnAvailability = ((uint32_t (__thiscall*)(void*))FUN_00a02d30)(obj);
        return true;
    }
    if (((bool (__thiscall*)(void*, void*))FUN_00ff3d10)(inv, &key)) {
        *pnTool = 3;
        return true;
    }
    if (((bool (__thiscall*)(void*, uint32_t))(*(void***)pTool)[0x1c / 4])(pTool, 0x588ba0e)) {
        bool flag;
        ((void (__cdecl*)(void*, uint32_t, bool*))FUN_00407190)(pTool, 0x588ba0e, &flag);
        if (flag) {
            *pnTool = 0;
            return true;
        }
    } else {
        bool r = ((bool (__thiscall*)(uint32_t, Key_s0107_b120))FUN_0103bef0)(player, key);
        *pnTool = (r ? 1u : 0u) + 1u;
    }
done_s0107_b120:
    return true;
}
}  // namespace SP

// @ 0x0107b260
bool cSPUITools_s0107_b260::PopulateSelected(cUIObject* pObject)
{
    cPropertyList* pProperty = 0;
    uint32_t nTool = 0;
    uint32_t nAvailability = 0;

    cPropertyManager* pManager = PropertyManager();
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    nTool = pObject->GetTypeId();
    pManager->GetProperty(0x30608f0b, nTool, &pProperty);
    GetToolAvailability(pProperty, &nTool, &nAvailability);
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    return nAvailability != 0;
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

// @ 0x0107b760
void cSPUITools_s0107_b260::PopulateRight()
{
    cPropertyList* pProperty = 0;
    uint32_t nTool = 0;
    uint32_t nAvailability = 0;

    cPropertyManager* pManager = PropertyManager();
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    pManager->GetProperty(0x30608f0b, nTool, &pProperty);
    GetToolAvailability(pProperty, &nTool, &nAvailability);
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
}

// @ 0x0107bb00
void cSPUITools_s0107_b260::Open(uint32_t nSlot)
{
    (void)nSlot;
}

// @ 0x0107bc30
bool cToolsMessage::OnMessage(uint32_t nMessage, cToolsEvent* pEvent)
{
    if (nMessage == 0xb3d53f95) {
        NounManager()->mpSelection->Select(mpSelectedMission->mpParentMission);

        cMissionCard* pNewCard = (cMissionCard*)pEvent->mpCard;
        cMissionCard* pOldCard = mpSelectedMission;
        if (pNewCard != pOldCard) {
            if (pNewCard != 0)
                pNewCard->AddRef();
            mpSelectedMission = pNewCard;
            if (pOldCard != 0)
                pOldCard->Release();
        }
        ((cSPUITools_s0107_b260*)((char*)this - 0xc))->PopulateRight();
        return true;
    }
    return cUIMissionCardPanel_s0107_b260::OnMessage(nMessage, pEvent);
}
