// Slice s00566970: EASTL container instantiations (rbtree / vector / vector_set / vector_map / deque)
// and a few SP::FunctionalMatch helpers. Module is /Od /Ob1 (no /EHsc), so the EASTL inline
// layers are reproduced with their real structure; ScratchSlots<N> reproduces the stack slots left
// behind by inlined EASTL helpers whose locals were optimized out of the source here.
typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned int uintptr_t;
inline void* operator new(size_t, void* p) { return p; }
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Record50;

namespace eastl {
  class allocator {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };

  struct true_type {};
  template<class T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
  template<class T> struct use_self { const T& operator()(const T& x) const { return x; } };
  template<class P> struct use_first { const typename P::first_type& operator()(const P& x) const { return x.first; } };
  template<class T1, class T2> struct pair {
    typedef T1 first_type; typedef T2 second_type;
    T1 first; T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
  };

  template<class FI, class T, class Compare> FI lower_bound(FI first, FI last, const T& value, Compare compare);
  template<class FI, class T, class Compare> FI upper_bound(FI first, FI last, const T& value, Compare compare);

  // ------------------------------------------------------------------ rbtree
  struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
  };
  template<class V> struct rbtree_node : public rbtree_node_base { V mValue; };
  void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor); // 0x921880

  template<class V, class Pointer = V*> struct rbtree_iterator {
    typedef rbtree_node<V> node_type;
    node_type* mpNode;
    rbtree_iterator();
    explicit rbtree_iterator(const node_type* pNode);                  // 0x566c50
    rbtree_iterator(const rbtree_iterator<V, const V*>& x);            // 0x5673e0 (const_iterator copy)
    rbtree_iterator& operator++();                                     // 0x422c50
    V* operator->() const;
  };
  template<class V, class P> inline bool operator==(const rbtree_iterator<V, P>& a, const rbtree_iterator<V, P>& b) { return a.mpNode == b.mpNode; }
  template<class V, class P> inline bool operator!=(const rbtree_iterator<V, P>& a, const rbtree_iterator<V, P>& b) { return a.mpNode != b.mpNode; }

  // Iter: the tree's iterator type. Some instantiations have a trivially-copyable iterator,
  // others copy through the out-of-line 0x5673e0 constructor.
  template<class K, class V, class Compare, class ExtractKey, class Iter = rbtree_iterator<V> >
  class rbtree {
  public:
    typedef rbtree_node<V> node_type; typedef Iter iterator; typedef K key_type; typedef unsigned size_type;
    typedef rbtree_iterator<V, const V*> const_iterator;
    Compare          mCompare;
    rbtree_node_base mAnchor;
    size_type        mnSize;
    allocator        mAllocator;

    rbtree(const allocator& a);                                         // 0x4b5980
    iterator end() { return iterator((node_type*)&mAnchor); }
    iterator find(const key_type& key);
    iterator lower_bound(const key_type& key);
    iterator upper_bound(const key_type& key);
    pair<iterator, bool> DoInsertKey(const key_type& key, true_type);
    iterator DoInsertKeyImpl(node_type* pNodeParent, const key_type& key, bool bForceToLeft); // 0x5681f0
    size_type erase(const key_type& key);
    iterator erase(iterator position);
    void clear();
    void reset();
    void DoNukeSubtree(node_type* pNode);
    void DoFreeNode(node_type* pNode);
    pair<const_iterator, const_iterator> equal_range(const key_type& key);
  };

  template<class K, class V, class C, class E, class I>
  typename rbtree<K,V,C,E,I>::iterator rbtree<K,V,C,E,I>::find(const key_type& key)
  {
    E extractKey;
    node_type* pCurrent  = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while(pCurrent)
    {
        if(!mCompare(extractKey(pCurrent->mValue), key))
        {
            pRangeEnd = pCurrent;
            pCurrent  = (node_type*)pCurrent->mpNodeLeft;
        }
        else
            pCurrent  = (node_type*)pCurrent->mpNodeRight;
    }
    if((pRangeEnd != &mAnchor) && !mCompare(key, extractKey(pRangeEnd->mValue)))
        return iterator(pRangeEnd);
    return iterator((node_type*)&mAnchor);
  }

  template<class K, class V, class C, class E, class I>
  inline void rbtree<K,V,C,E,I>::DoFreeNode(node_type* pNode)
  {
    pNode->~node_type();
    mAllocator.deallocate(pNode, sizeof(node_type));
  }

  template<class K, class V, class C, class E, class I>
  inline typename rbtree<K,V,C,E,I>::iterator rbtree<K,V,C,E,I>::erase(iterator position)
  {
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
  }

  template<class K, class V, class C, class E, class I>
  typename rbtree<K,V,C,E,I>::size_type rbtree<K,V,C,E,I>::erase(const key_type& key)
  {
    const iterator it(find(key));
    if(it != end())
    {
        erase(it);
        return 1;
    }
    return 0;
  }

  template<class K, class V, class C, class E, class I>
  inline void rbtree<K,V,C,E,I>::reset()
  {
    mAnchor.mpNodeRight  = &mAnchor;
    mAnchor.mpNodeLeft   = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor       = 0;
    mnSize               = 0;
  }

  template<class K, class V, class C, class E, class I>
  void rbtree<K,V,C,E,I>::clear()
  {
    DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
    reset();
  }

  template<class K, class V, class C, class E, class I>
  pair<typename rbtree<K,V,C,E,I>::const_iterator, typename rbtree<K,V,C,E,I>::const_iterator>
  rbtree<K,V,C,E,I>::equal_range(const key_type& key)
  {
    return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
  }

  template<class K, class V, class C = less<K> >
  class multiset : public rbtree<K, V, C, use_self<K> > {
  public:
    typedef rbtree<K, V, C, use_self<K> > base_type;
    multiset(const allocator& a);
  };
  template<class K, class V, class C>
  multiset<K,V,C>::multiset(const allocator& a) : base_type(a) {}

  // ------------------------------------------------------------------ vector
  template<class T, class A> struct VectorBase {
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;
    ~VectorBase();                                                      // 0x566430 (T50)
  };
  template<class T, class A = allocator> class vector : public VectorBase<T, A> {
  public:
    typedef VectorBase<T, A> base_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef const T& const_reference; typedef unsigned size_type;
    using base_type::mpBegin; using base_type::mpEnd; using base_type::mpCapacity; using base_type::mAllocator;
    ~vector();
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    void reserve(size_type n);
    void push_back();
    void push_back(const value_type& value);
    iterator erase(iterator position);
    iterator insert(iterator position, const value_type& value);
    void DoDestroyValues(pointer first, pointer last);
    void DoInsertValue(iterator position, const value_type& value);
    pointer DoAllocate(size_type n);
    void DoFree(pointer p, size_type n);
  };

  template<class T, class A> inline void vector<T,A>::DoDestroyValues(pointer first, pointer last)
  {
    for(; first < last; ++first)
        first->~value_type();
  }

  template<class T, class A> inline typename vector<T,A>::pointer vector<T,A>::DoAllocate(size_type n)
  {
    return n ? (pointer)mAllocator.allocate(n * sizeof(T), 8, 0) : 0;
  }

  template<class T, class A> inline void vector<T,A>::DoFree(pointer p, size_type n)
  {
    if(p && ((int*)p)[-1])
        mAllocator.deallocate(p, n);
  }

  template<class IIt, class FIt> FIt uninitialized_copy_ptr(IIt first, IIt last, FIt dest); // 0x566490

  template<class T, class A> void vector<T,A>::reserve(size_type n)
  {
    if(n > size_type(mpCapacity - mpBegin))
    {
        ScratchSlots<18>();
        pointer const pNewData = DoAllocate(n);
        eastl::uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        const size_type nPrevSize = (size_type)(mpEnd - mpBegin);
        mpBegin    = pNewData;
        mpEnd      = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
  }

  template<class T, class A> void vector<T,A>::push_back()
  {
    if(mpEnd < mpCapacity)
        ::new(mpEnd++) value_type();
    else
        DoInsertValue(mpEnd, value_type());
    ScratchSlots<12>();
  }

  template<class T, class A> void vector<T,A>::push_back(const value_type& value)
  {
    if(mpEnd < mpCapacity)
        ::new(mpEnd++) value_type(value);
    else
        DoInsertValue(mpEnd, value);
    ScratchSlots<15>();
  }

  // Generic (non-memmove) copy path. The three const bools are EASTL's compile-time
  // dispatch flags (all false for these iterator/value types); names chosen for /Od slot order.
  struct copy_impl {
    template<class IIt, class OIt> static OIt do_copy(IIt first, IIt last, OIt result)
    {
        for(; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
  };
  // Dead slots of the (elided) iterator-category dispatch layer; their count depends on the output iterator.
  template<class OIt> struct copy_pad { enum { N = 2 }; };
  template<class C> class insert_iterator;
  template<class C> struct copy_pad<insert_iterator<C> > { enum { N = 16 }; };
  template<> struct copy_pad< ::Record50*> { enum { N = 4 }; };
  template<class IIt, class OIt> inline OIt copy(IIt first, IIt last, OIt result)
  {
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    ScratchSlots<copy_pad<OIt>::N>();
    return copy_impl::do_copy(first, last, result);
  }

  template<class T, class A> typename vector<T,A>::iterator vector<T,A>::erase(iterator position)
  {
    if((position + 1) < mpEnd)
        eastl::copy(position + 1, mpEnd, position);
    --mpEnd;
    ScratchSlots<5>();
    mpEnd->~value_type();
    return position;
  }

  template<class T, class A> vector<T,A>::~vector()
  {
    ScratchSlots<8>();
    DoDestroyValues(mpBegin, mpEnd);
    ScratchSlots<3>();
  }

  // vector whose base destructor is inline (trivial 16-byte elements)
  template<class T, class A> struct VectorBaseI {
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;
    ~VectorBaseI()
    {
        if(mpBegin)
            EASTLFree(mpBegin, (size_t)(mpCapacity - mpBegin) * sizeof(T));
    }
    void EASTLFree(T* p, size_t n) { mAllocator.deallocate(p, n); }
  };
  template<class T, class A = allocator> class vectorI : public VectorBaseI<T, A> {
  public:
    typedef VectorBaseI<T, A> base_type; typedef T* pointer; typedef T value_type;
    using base_type::mpBegin; using base_type::mpEnd;
    ~vectorI() { DoDestroyValues(mpBegin, mpEnd); }
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
  };

  // ------------------------------------------------------------------ vector_set / vector_map
  template<class K, class C = less<K>, class A = allocator, class RAC = vector<K, A> >
  class vector_set : public RAC {
  public:
    typedef RAC base_type; typedef K value_type; typedef typename RAC::iterator iterator;
    C        mCompare;      // +0x14 (allocator is 8 bytes)
    using base_type::begin; using base_type::end;
    iterator lower_bound(const value_type& k) { return eastl::lower_bound(begin(), end(), k, mCompare); }
    iterator upper_bound(const value_type& k) { return eastl::upper_bound(begin(), end(), k, mCompare); }
    pair<iterator, bool> insert(const value_type& value);
  };

  template<class K, class C, class A, class RAC>
  pair<typename vector_set<K,C,A,RAC>::iterator, bool> vector_set<K,C,A,RAC>::insert(const value_type& value)
  {
    const iterator itLB(lower_bound(value));
    if((itLB != end()) && !mCompare(value, *itLB))
        return pair<iterator, bool>(itLB, false);
    ScratchSlots<3>();
    return pair<iterator, bool>(base_type::insert(itLB, value), true);
  }

  template<class K, class C = less<K>, class A = allocator, class RAC = vector<K, A> >
  class vector_multiset : public RAC {
  public:
    typedef RAC base_type; typedef K value_type; typedef typename RAC::iterator iterator;
    C        mCompare;      // +0x14 (allocator is 8 bytes)
    using base_type::begin; using base_type::end;
    iterator upper_bound(const value_type& k) { return eastl::upper_bound(begin(), end(), k, mCompare); }
    pair<iterator, bool> insert(const value_type& value);
  };

  template<class K, class C, class A, class RAC>
  pair<typename vector_multiset<K,C,A,RAC>::iterator, bool> vector_multiset<K,C,A,RAC>::insert(const value_type& value)
  {
    const iterator itUB(upper_bound(value));
    ScratchSlots<3>();
    return pair<iterator, bool>(base_type::insert(itUB, value), true);
  }

  template<class Key, class T, class Compare = less<Key>, class Allocator = allocator,
           class RAC = vector<pair<Key, T>, Allocator> >
  class vector_map : public RAC {
  public:
    typedef RAC base_type; typedef pair<Key, T> value_type; typedef typename RAC::iterator iterator;
    typedef Key key_type; typedef T mapped_type; typedef Compare key_compare;
    class value_compare { public: Compare c;
      bool operator()(const value_type& a, const value_type& b) const { return c(a.first, b.first); } };
    value_compare mValueCompare;  // +0x14
    using base_type::begin; using base_type::end;
    key_compare key_comp() const { return mValueCompare.c; }
    iterator lower_bound(const key_type& k) { return eastl::lower_bound(begin(), end(), k, mValueCompare); }
    iterator insert(iterator position, const value_type& value);
    mapped_type& operator[](const key_type& k);
  };

  template<class K, class T, class C, class A, class RAC>
  typename vector_map<K,T,C,A,RAC>::mapped_type& vector_map<K,T,C,A,RAC>::operator[](const key_type& k)
  {
    iterator itLB(lower_bound(k));
    if((itLB == end()) || key_comp()(k, (*itLB).first))
        itLB = insert(itLB, value_type(k, mapped_type()));
    return (*itLB).second;
  }

  // ------------------------------------------------------------------ insert_iterator + set algorithms
  template<class Container> class insert_iterator {
  public:
    typedef typename Container::iterator iterator_type;
    Container&    container;
    iterator_type it;
    insert_iterator(Container& x, iterator_type itNew) : container(x), it(itNew) {}
    insert_iterator& operator=(const typename Container::value_type& value)
    {
        it = container.insert(it, value);
        ++it;
        return *this;
    }
    insert_iterator& operator*() { return *this; }
    insert_iterator& operator++() { return *this; }
    insert_iterator& operator++(int) { return *this; }
  };
  template<class Container> inline insert_iterator<Container> inserter(Container& x, typename Container::iterator i)
  { return insert_iterator<Container>(x, i); }

  template<class I1, class I2, class O>
  O set_intersection(I1 first1, I1 last1, I2 first2, I2 last2, O result)
  {
    ScratchSlots<13>();
    while((first1 != last1) && (first2 != last2))
    {
        if(*first1 < *first2)
            ++first1;
        else if(*first2 < *first1)
            ++first2;
        else
        {
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
  }

  template<class I1, class I2, class O>
  O set_difference(I1 first1, I1 last1, I2 first2, I2 last2, O result)
  {
    ScratchSlots<7>();
    while((first1 != last1) && (first2 != last2))
    {
        if(*first1 < *first2)
        {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first2 < *first1)
            ++first2;
        else
        {
            ++first1;
            ++first2;
        }
    }
    return eastl::copy(first1, last1, result);
  }

  template<class I1, class I2, class O>
  O set_union(I1 first1, I1 last1, I2 first2, I2 last2, O result);   // 0x567400

  // ------------------------------------------------------------------ deque
  template<class T> struct DequeIterator {
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator(const DequeIterator& x);                              // 0x420050
    DequeIterator& operator++();                                        // 0x5677f0
  };
  template<class T> inline bool operator!=(const DequeIterator<T>& a, const DequeIterator<T>& b) { return a.mpCurrent != b.mpCurrent; }
  template<class T> struct DequeBase {
    T** mpPtrArray; size_t mnPtrArraySize; DequeIterator<T> mItBegin; DequeIterator<T> mItEnd; allocator mAllocator;
    ~DequeBase();                                                       // 0x501ef0
  };
  template<class T> class deque : public DequeBase<T> {
  public:
    typedef DequeIterator<T> iterator; typedef T value_type;
    using DequeBase<T>::mItBegin; using DequeBase<T>::mItEnd;
    ~deque();
    iterator begin();
  };
  template<class T> deque<T>::~deque()
  {
    for(iterator itCurrent(mItBegin); itCurrent != mItEnd; ++itCurrent)
        itCurrent.mpCurrent->~value_type();
  }
  template<class T> typename deque<T>::iterator deque<T>::begin() { return mItBegin; }
}
using namespace eastl;

// ---------------------------------------------------------------------- additional EASTL members
extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t n);
namespace eastl {
  template<class T> inline void swap(T& a, T& b) { T temp(a); a = b; b = temp; }
  void* RBTreeDecrement(const rbtree_node_base* pNode);    // 0x9215c0

  template<class K, class V, class C, class E, class I>
  typename rbtree<K,V,C,E,I>::iterator rbtree<K,V,C,E,I>::lower_bound(const key_type& key)
  {
    E extractKey;
    node_type* pCurrent  = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while(pCurrent)
    {
        if(!mCompare(extractKey(pCurrent->mValue), key))
        {
            pRangeEnd = pCurrent;
            pCurrent  = (node_type*)pCurrent->mpNodeLeft;
        }
        else
            pCurrent  = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator(pRangeEnd);
  }

  template<class K, class V, class C, class E, class I>
  void rbtree<K,V,C,E,I>::DoNukeSubtree(node_type* pNode)
  {
    while(pNode)
    {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
    ScratchSlots<2>();   // dead slots of the inlined node destructor (these trees free nodes out of line)
  }

  template<class K, class V, class C, class E, class I>
  pair<typename rbtree<K,V,C,E,I>::iterator, bool> rbtree<K,V,C,E,I>::DoInsertKey(const key_type& key, true_type)
  {
    E extractKey;
    node_type* pCurrent    = (node_type*)mAnchor.mpNodeParent;
    node_type* pLowerBound = (node_type*)&mAnchor;
    node_type* pParent;
    bool bValueLessThanNode = true;

    while(pCurrent)
    {
        bValueLessThanNode = mCompare(key, extractKey(pCurrent->mValue));
        pLowerBound        = pCurrent;
        if(bValueLessThanNode)
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if(bValueLessThanNode)
    {
        if(pLowerBound != (node_type*)mAnchor.mpNodeLeft)
            pLowerBound = (node_type*)RBTreeDecrement(pLowerBound);
        else
        {
            const iterator itResult(DoInsertKeyImpl(pLowerBound, key, false));
            return pair<iterator, bool>(itResult, true);
        }
    }

    if(mCompare(extractKey(pLowerBound->mValue), key))
    {
        const iterator itResult(DoInsertKeyImpl(pParent, key, false));
        return pair<iterator, bool>(itResult, true);
    }

    return pair<iterator, bool>(iterator(pLowerBound), false);
  }

  // ------------------------------------------------------------------ deque extras
  template<class T> struct DequeIterator2 {
    enum { kSubarraySize = 32 };
    struct Decrement {};
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator2(const DequeIterator2& x);                           // 0x420050
    DequeIterator2(const DequeIterator2& x, Decrement);                // 0x5677a0
    T& operator*() const;                                              // 0x5658b0
    DequeIterator2& operator++();
    void SetSubarray(T** pCurrentArrayPtr);                            // 0x569340
  };
  template<class T> inline int operator-(const DequeIterator2<T>& a, const DequeIterator2<T>& b)
  {
    return ((int)DequeIterator2<T>::kSubarraySize * ((a.mpCurrentArrayPtr - b.mpCurrentArrayPtr) - 1)) +
           (a.mpCurrent - a.mpBegin) + (b.mpEnd - b.mpCurrent);
  }
  template<class T> class deque2 {
  public:
    typedef DequeIterator2<T> iterator; typedef T value_type; typedef unsigned size_type;
    T** mpPtrArray; size_t mnPtrArraySize; iterator mItBegin; iterator mItEnd;
    uint32_t mAllocator;   // 4 bytes here: the derived set's comparator sits at +0x2c
    iterator begin();                                                  // 0x565740
    iterator end();                                                    // 0x565760
    size_type size();
    T& back();
    void pop_back();
    void push_back(const value_type& value);                           // 0x568f70
    void push_front(const value_type& value);                          // 0x568f00
    iterator insert(iterator position, const value_type& value);
    iterator DoInsertValue(iterator position, const value_type& value); // 0x568ff0
    void DoPopBack();
    void DoFreeSubarray(T* p);                                         // 0x569260
  };
  template<class T> typename deque2<T>::iterator deque2<T>::end() { return mItEnd; }
  template<class T> typename deque2<T>::size_type deque2<T>::size() { return (size_type)(mItEnd - mItBegin); }
  template<class T> T& deque2<T>::back() { return *iterator(mItEnd, typename iterator::Decrement()); }
  template<class T> void deque2<T>::pop_back()
  {
    if(mItEnd.mpCurrent != mItEnd.mpBegin)
        --mItEnd.mpCurrent;
    else
        DoPopBack();
  }
  template<class T> T& DequeIterator2<T>::operator*() const { return *mpCurrent; }

  // A sorted container on top of a deque (insert keeps order; duplicates allowed).
  template<class T, class Compare = less<T> > class deque_multiset : public deque2<T> {
  public:
    typedef deque2<T> base_type; typedef typename deque2<T>::iterator iterator;
    Compare  mCompare;      // +0x2c
    using base_type::begin; using base_type::end;
    iterator upper_bound(const T& value);
    pair<iterator, bool> insert(const T& value);
  };
  template<class FI, class T, class Compare> FI upper_bound(FI first, FI last, const T& value, Compare compare); // 0x569380
  template<class T, class C> typename deque_multiset<T,C>::iterator deque_multiset<T,C>::upper_bound(const T& value)
  {
    return eastl::upper_bound(begin(), end(), value, mCompare);
  }
  template<class T, class C> pair<typename deque_multiset<T,C>::iterator, bool> deque_multiset<T,C>::insert(const T& value)
  {
    iterator itUB(upper_bound(value));
    ScratchSlots<2>();
    return pair<iterator, bool>(base_type::insert(itUB, value), true);
  }
  template<class T> typename deque2<T>::iterator deque2<T>::insert(iterator position, const value_type& value)
  {
    if(position.mpCurrent == mItEnd.mpCurrent)
    {
        push_back(value);
        return iterator(mItEnd, typename iterator::Decrement());
    }
    else if(position.mpCurrent == mItBegin.mpCurrent)
    {
        push_front(value);
        return mItBegin;
    }
    return DoInsertValue(position, value);
  }
  template<class T> void deque2<T>::DoPopBack()
  {
    DoFreeSubarray(mItEnd.mpBegin);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr - 1);
    mItEnd.mpCurrent = mItEnd.mpEnd - 1;
  }

  // ------------------------------------------------------------------ vector extras
  template<class T, class A = allocator> class vector2 : public VectorBase<T, A> {
  public:
    typedef VectorBase<T, A> base_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type; typedef vector2<T, A> this_type;
    using base_type::mpBegin; using base_type::mpEnd; using base_type::mpCapacity; using base_type::mAllocator;
    vector2(const this_type& x);                                       // 0x50d440
    ~vector2();                                                        // 0x553fb0
    this_type& operator=(const this_type& x);                          // 0x54afe0
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    iterator insert(iterator position, const value_type& value);
    iterator erase(iterator first, iterator last);
    void swap(this_type& x);
    void reserve(size_type n);
    void DoInsertValue(iterator position, const value_type& value);
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
    pointer DoAllocate(size_type n) { return n ? (pointer)mAllocator.allocate(n * sizeof(T), __alignof(T), 0) : 0; }
    void DoFree(pointer p, size_type n)
    {
        if(p)
            mAllocator.deallocate(p, n);
    }
  };

  template<class T, class A> typename vector2<T,A>::iterator vector2<T,A>::insert(iterator position, const value_type& value)
  {
    const int n = position - mpBegin;
    if((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) value_type(value);
    return mpBegin + n;
  }

  // Out-of-line element-range copy (generic assignment loop) used by some erase() instantiations.
  template<class IIt, class OIt> OIt copy_range(IIt first, IIt last, OIt result); // 0x4e4fd0
  template<class IIt, class OIt> inline OIt copy_call(IIt first, IIt last, OIt result)
  {
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    return copy_range(first, last, result);
  }

  template<class T, class A> typename vector2<T,A>::iterator vector2<T,A>::erase(iterator first, iterator last)
  {
    iterator const position = eastl::copy_call(last, mpEnd, first);
    ScratchSlots<4>();
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
    return first;
  }

  template<class T, class A> void vector2<T,A>::swap(this_type& x)
  {
    if(0)       // allocator-equality test, compiled out in this configuration
    {
        eastl::swap(mpBegin,    x.mpBegin);
        eastl::swap(mpEnd,      x.mpEnd);
        eastl::swap(mpCapacity, x.mpCapacity);
    }
    else if(1)
    {
        eastl::swap(mpBegin,    x.mpBegin);
        eastl::swap(mpEnd,      x.mpEnd);
        eastl::swap(mpCapacity, x.mpCapacity);
    }
    else
    {
        const this_type temp(*this);
        *this = x;
        x     = temp;
    }
    ScratchSlots<21>();
  }

  template<class T> inline void destruct_trivial(T*, T*) { const bool bHasTrivialDestructor = true; }
  template<class T> inline T* uninitialized_copy_memcpy(T* first, T* last, T* result)
  {
    const bool bHasTrivialCopy = true;
    return (last - first) + (T*)memcpy(result, first, (size_t)((char*)last - (char*)first));
  }
  template<class T> inline T* uninitialized_copy_trivial(T* first, T* last, T* result)
  {
    return uninitialized_copy_memcpy(first, last, result);
  }

  template<class T, class A> void vector2<T,A>::reserve(size_type n)
  {
    if(n > size_type(mpCapacity - mpBegin))
    {
        // (named for /Od slot order: p12 = previous size, p15 = new block, v18 = new end; K=3 -> use 3-name set)
        pointer const p15 = DoAllocate(n);
        pointer v18 = eastl::uninitialized_copy_trivial(mpBegin, mpEnd, p15);
        { const bool bHasTrivialDestructor = true; }   // DoDestroyValues is empty for this type
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        const size_type p12 = (size_type)(mpEnd - mpBegin);
        mpBegin    = p15;
        mpEnd      = p15 + p12;
        mpCapacity = mpBegin + n;
    }
  }

  // vector_set / vector_map hint inserts
  template<class K, class C = less<K>, class A = allocator, class RAC = vector<K, A> >
  class vector_set2 : public RAC {
  public:
    typedef RAC base_type; typedef K value_type; typedef typename RAC::iterator iterator;
    C mCompare;   // +0x14
    using base_type::begin; using base_type::end;
    pair<iterator, bool> insert(const value_type& value);                 // 0x554020
    iterator insert(iterator position, const value_type& value);
  };
  template<class K, class C, class A, class RAC>
  typename vector_set2<K,C,A,RAC>::iterator vector_set2<K,C,A,RAC>::insert(iterator position, const value_type& value)
  {
    if((position == end()) || mCompare(value, *position))
    {
        if((position == begin()) || mCompare(*(position - 1), value))
            return base_type::insert(position, value);                     // 0x554f20
    }
    ScratchSlots<12>();
    return insert(value).first;
  }

  template<class Key, class T, class Compare = less<Key>, class Allocator = allocator,
           class RAC = vector2<pair<Key, T>, Allocator> >
  class vector_map2 : public RAC {
  public:
    typedef RAC base_type; typedef pair<Key, T> value_type; typedef typename RAC::iterator iterator;
    class value_compare { public: Compare c;
      bool operator()(const value_type& a, const value_type& b) const { return c(a.first, b.first); } };
    value_compare mValueCompare;  // +0x14
    using base_type::begin; using base_type::end;
    iterator insert(iterator position, const value_type& value);
  };
  template<class K, class T, class C, class A, class RAC>
  typename vector_map2<K,T,C,A,RAC>::iterator vector_map2<K,T,C,A,RAC>::insert(iterator position, const value_type& value)
  {
    iterator itLB;
    if((position != end()) && mValueCompare(value, *position))
        itLB = eastl::lower_bound(begin(), position, value, mValueCompare);
    else
        itLB = eastl::lower_bound(position, end(), value, mValueCompare);
    if((itLB == end()) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    ScratchSlots<3>();
    return itLB;
  }

  // 0x50-byte record vector members (uninitialized copy goes through a relocating helper)
  template<class T> void uninitialized_copy_finish(T* first, T* last, T* result); // 0x5680a0
  template<class T> inline T* uninitialized_copy_impl(T* first, T* last, T* dest)
  {
    ScratchSlots<3>();
    for(; first != last; ++first, ++dest)
        ::new(dest) T(*first);
    return dest;
  }
  template<class T> T* uninitialized_copy_ptr2(T* first, T* last, T* result)
  {
    const bool bHasTrivialCopy = false;
    T* const currentDest = uninitialized_copy_impl(first, last, result);
    ScratchSlots<11>();
    uninitialized_copy_finish(first, last, result);
    return currentDest;
  }
}
using namespace eastl;

// ---------------------------------------------------------------------- additional EASTL members
extern "C" void* __cdecl memset(void* dst, int c, size_t n);
void* operator new[](size_t n, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line); // 0xf473a0
namespace eastl {
  struct false_type {};
  void* RBTreeDecrement(const rbtree_node_base* pNode);    // 0x9215c0

  template<class K, class V, class C, class E, class I>
  typename rbtree<K,V,C,E,I>::iterator rbtree<K,V,C,E,I>::upper_bound(const key_type& key)
  {
    E extractKey;
    node_type* pCurrent  = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while(pCurrent)
    {
        if(mCompare(key, extractKey(pCurrent->mValue)))
        {
            pRangeEnd = pCurrent;
            pCurrent  = (node_type*)pCurrent->mpNodeLeft;
        }
        else
            pCurrent  = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator(pRangeEnd);
  }

  // Non-unique-key insert (multimap / multiset).
  template<class K, class V, class C, class E, class I>
  class rbtree_multi : public rbtree<K, V, C, E, I> {
  public:
    typedef rbtree<K, V, C, E, I> base_type; typedef typename base_type::node_type node_type;
    typedef typename base_type::iterator iterator; typedef K key_type;
    using base_type::mAnchor; using base_type::mCompare;
    iterator DoInsertKey(const key_type& key, false_type);
  };
  template<class K, class V, class C, class E, class I>
  typename rbtree_multi<K,V,C,E,I>::iterator rbtree_multi<K,V,C,E,I>::DoInsertKey(const key_type& key, false_type)
  {
    node_type* pCurrent  = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    E extractKey;
    while(pCurrent)
    {
        pRangeEnd = pCurrent;
        if(mCompare(key, extractKey(pCurrent->mValue)))
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return this->DoInsertKeyImpl(pRangeEnd, key, false);   // 0x5685f0
  }

  // lower_bound without a comparator
  template<class FI, class T> FI lower_bound(FI first, FI last, const T& value)
  {
    int d = (int)(last - first);
    while(d > 0)
    {
        FI  i  = first;
        int d2 = d >> 1;
        i += d2;
        if(*i < value)
        {
            first = ++i;
            d -= d2 + 1;
        }
        else
            d = d2;
    }
    ScratchSlots<1>();
    return first;
  }

  // ------------------------------------------------------------------ hashtable node / bucket allocation
  template<class V> struct hash_node { V mValue; hash_node* mpNext; };
  template<class V> class hashtable {
  public:
    typedef hash_node<V> node_type; typedef V value_type; typedef unsigned size_type;
    uint32_t  mPad[7];          // buckets, sizes, rehash policy...
    allocator mAllocator;       // +0x1c
    node_type* DoAllocateNode(const value_type& value);
    node_type** DoAllocateBuckets(size_type n);
  };
  template<class V> typename hashtable<V>::node_type* hashtable<V>::DoAllocateNode(const value_type& value)
  {
    node_type* const pNode = (node_type*)EASTL_Allocate(&mAllocator, sizeof(node_type), __alignof(value_type), 0);
    ::new(&pNode->mValue) value_type(value);
    pNode->mpNext = 0;
    return pNode;
  }
  inline void* AllocateBucketMemory(size_t n)
  {
    void* const p = ::operator new[](n, "Editor", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\hashtable.h", 0xd1);
    return p;
  }
  template<class V> typename hashtable<V>::node_type** hashtable<V>::DoAllocateBuckets(size_type n)
  {
    node_type** const pBucketArray = (node_type**)AllocateBucketMemory((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = reinterpret_cast<node_type*>((uintptr_t)~0);
    return pBucketArray;
  }

  // ------------------------------------------------------------------ deque members
  template<class T> DequeIterator2<T>& DequeIterator2<T>::operator++()
  {
    if(++mpCurrent == mpEnd)
    {
        mpBegin   = *++mpCurrentArrayPtr;
        mpEnd     = mpBegin + kSubarraySize;
        mpCurrent = mpBegin;
    }
    return *this;
  }
}
using namespace eastl;

// ---------------------------------------------------------------------- element types
struct IntRange { int mMin; int mMax; };
struct FloatRange { float mMin; float mMax; };
struct ConstraintTail {                                   // copy 0x4e38d0, assign 0x4e4410, dtor 0x4e1780
    uint32_t d[5];
    ConstraintTail(const ConstraintTail&);
    ConstraintTail& operator=(const ConstraintTail&);
    ~ConstraintTail();
};
struct ConstraintBuilder { bool IsFull() const; };       // 0x526430 (identical-code-folded symbol)
namespace SP { namespace FunctionalMatch {
  // Retail layout (0x24): the 2008 PDB's 0x10-byte struct plus a destructible tail.
  struct Constraint {
    uint32_t mParameter;          // +0x0
    int      mType;               // +0x4
    union {
      IntRange   mIntVal;         // +0x8
      FloatRange mFloatVal;       // +0x8
    };
    ConstraintTail mTail;         // +0x10
    bool IsTerminal() const;      // 0x558b20
  };
  struct ConstraintCursor {
    Constraint* mpNext;
    Constraint* mpCur;
    ConstraintCursor(const ConstraintCursor& x) : mpNext(x.mpNext), mpCur(x.mpCur) {}
    ~ConstraintCursor() { mpNext = 0; }
    Constraint* operator->() const { return mpCur; }
    Constraint& operator*() const { return *mpCur; }
    ConstraintCursor& operator++() { mpNext++; mpCur = mpNext - 1; return *this; }
  };
  struct ConstraintList {
    void AddEnd(ConstraintBuilder* pBuilder, const Constraint& c);              // 0x5623f0
    void AddRange(ConstraintBuilder* pBuilder, const Constraint* p, unsigned n);
    void AddRange(ConstraintBuilder* pBuilder, ConstraintCursor c, unsigned n);
  };

  // @ 0x005675a0 odn sym=?AddRange@ConstraintList@FunctionalMatch@SP@@QAEXPAUConstraintBuilder@@PBUConstraint@23@I@Z
  void ConstraintList::AddRange(ConstraintBuilder* pBuilder, const Constraint* p, unsigned n)
  {
    for(; !pBuilder->IsFull() && n > 0 && !p->IsTerminal(); ++p, --n)
        AddEnd(pBuilder, *p);
  }

  // @ 0x00567600 odn sym=?AddRange@ConstraintList@FunctionalMatch@SP@@QAEXPAUConstraintBuilder@@UConstraintCursor@23@I@Z
  void ConstraintList::AddRange(ConstraintBuilder* pBuilder, ConstraintCursor c, unsigned n)
  {
    for(; !pBuilder->IsFull() && n > 0 && !c->IsTerminal(); ++c, --n)
        AddEnd(pBuilder, *c);
  }
}}
using SP::FunctionalMatch::Constraint;

struct Elem28 {
    uint32_t   mKey;
    Constraint mConstraint;   // +0x4
    Elem28(const Elem28& x);              // 0x565920
    Elem28& operator=(const Elem28& x);
};
// @ 0x00567a10 odn sym=??4Elem28@@
Elem28& Elem28::operator=(const Elem28& x)
{
    mKey = x.mKey;
    mConstraint = x.mConstraint;
    return *this;
}

// 0x50-byte record (8-byte aligned: it ends with a 64-bit field).
struct Triple { uint32_t* a; uint32_t* b; uint32_t* c; };
struct SubSet {                                  // copy 0x565be0, assign 0x569690
    uint32_t d[5];
    SubSet(const SubSet&);
    SubSet& operator=(const SubSet&);
};
struct Flag { bool mValue; };
struct SetMember {
    SubSet mSub;      // +0x0
    Flag   mFlag;     // +0x14
    float  mWeight;   // +0x18
    SetMember& operator=(const SetMember& x) { mSub = x.mSub; Flag f = x.mFlag; mFlag = f; mWeight = x.mWeight; return *this; }
};
struct VecBase {                                 // copy 0x50d440, assign 0x54afe0
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAlloc[2]; uint32_t mExtra[2];
    VecBase(const VecBase&);
    VecBase& operator=(const VecBase&);
};
struct VecMember : VecBase {
    VecMember& operator=(const VecMember& x) { VecBase::operator=(x); return *this; }
};
struct Record50 {
    Triple           mRange;    // +0x0
    uint32_t         mCount;    // +0xc
    SetMember        mSet;      // +0x10
    VecMember        mVec;      // +0x2c
    unsigned __int64 mStamp;    // +0x48
    Record50(const Record50& x);
    Record50& operator=(const Record50& x);
};
// @ 0x005678b0 odn sym=??0Record50@@
Record50::Record50(const Record50& x)
    : mRange((ScratchSlots<12>(), x.mRange)), mCount(x.mCount), mSet(x.mSet),
      mVec((ScratchSlots<18>(), x.mVec)), mStamp(x.mStamp)
{
}
// @ 0x00567970 odn sym=??4Record50@@
Record50& Record50::operator=(const Record50& x)
{
    mRange = x.mRange;
    mCount = x.mCount;
    mSet   = x.mSet;
    ScratchSlots<1>();
    mVec   = x.mVec;
    mStamp = x.mStamp;
    return *this;
}

// ---------------------------------------------------------------------- vectors
template<> inline void vector2<Elem28>::DoFree(pointer p, size_type n)
{
    if(p && ((int*)p)[-1])
        mAllocator.deallocate(p, n);
}
template<class T> T* uninitialized_copy_ptr3(T* first, T* last, T* result);   // 0x568680
struct copy_backward_impl {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        while(last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
};
template<class BI1, class BI2> inline BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd)
{
    uint32_t unusedA, unusedB;
    {
        const bool cap = false;
        const bool count = false;
        const bool p24 = false;
        ScratchSlots<2>();
        return copy_backward_impl::do_copy(first, last, resultEnd);
    }
}
// @ 0x00566df0 odn sym=?DoInsertValue@?$vector2@UElem28
template<> void vector2<Elem28>::DoInsertValue(iterator position, const value_type& value)
{
    if(mpEnd != mpCapacity)
    {
        const Elem28* pValue = &value;
        if((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) value_type(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    }
    else
    {
        // names chosen for /Od slot order: t2 = previous size, n26 = new size, other = new data, n16 = new end
        const size_type t2 = size_type(mpEnd - mpBegin);
        const size_type n26 = (t2 > 0) ? (2 * t2) : 1;
        pointer const   other = DoAllocate(n26);
        pointer n16 = uninitialized_copy_ptr3(mpBegin, position, other);
        ::new(n16) value_type(value);
        n16 = uninitialized_copy_ptr3(position, mpEnd, ++n16);
        ScratchSlots<28>();
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin    = other;
        mpEnd      = n16;
        mpCapacity = other + n26;
    }
}

// @ 0x00566da0 odn sym=?DoDestroyValues@?$vector2@UElem28
template<> void vector2<Elem28>::DoDestroyValues(pointer first, pointer last)
{
    for(; first < last; ++first)
    {
        ScratchSlots<5>();
        first->~value_type();
    }
}
// @ 0x00567350 odn sym=?insert@?$vector2@I
template vector2<uint32_t>::iterator vector2<uint32_t>::insert(uint32_t*, const uint32_t&);
// @ 0x00567190 odn sym=??$lower_bound@PAII@eastl
template uint32_t* eastl::lower_bound(uint32_t*, uint32_t*, const uint32_t&);

// ---------------------------------------------------------------------- trees
struct X568110Base { uint32_t d[4]; X568110Base(const X568110Base&); };   // copy 0x568110
struct X568110 : X568110Base {};   // implicit (inlined) copy ctor
struct X568320Base { uint32_t d[4]; X568320Base(const X568320Base&); };   // copy 0x568320
struct X568320 : X568320Base {};
struct UIntVector : vector2<uint32_t> {};   // implicit copy ctor calls vector2's (0x50d440)
typedef pair<uint32_t, X568110> PairA;
typedef pair<uint32_t, UIntVector> PairB;
typedef pair<uint32_t, X568320> PairC;
// @ 0x005670d0 odn sym=??0?$pair@IUX568110
template<> pair<uint32_t, X568110>::pair(const uint32_t& x, const X568110& y)
    : first((ScratchSlots<2>(), x)), second(y) {}
// @ 0x00567110 odn sym=??0?$pair@IUUIntVector
template<> pair<uint32_t, UIntVector>::pair(const uint32_t& x, const UIntVector& y)
    : first((ScratchSlots<18>(), x)), second(y) {}
// @ 0x00567150 odn sym=??0?$pair@IUX568320
template<> pair<uint32_t, X568320>::pair(const uint32_t& x, const X568320& y)
    : first((ScratchSlots<2>(), x)), second(y) {}

typedef rbtree_iterator<float, const float*> FloatIterC;
typedef rbtree<float, float, less<float>, use_self<float>, FloatIterC> FloatTreeC;
typedef rbtree<uint32_t, uint32_t, less<uint32_t>, use_self<uint32_t> > UIntTree;
typedef rbtree<uint32_t, PairA, less<uint32_t>, use_first<PairA> > TreeA;
typedef rbtree<uint32_t, PairC, less<uint32_t>, use_first<PairC> > TreeC;
typedef rbtree_multi<uint32_t, uint32_t, less<uint32_t>, use_self<uint32_t>, rbtree_iterator<uint32_t> > UIntMultiTree;

template<> void TreeA::DoFreeNode(node_type* pNode);   // 0x5684b0 (out of line)
template<> void TreeC::DoFreeNode(node_type* pNode);   // 0x568590 (out of line)

// @ 0x00566970 odnsf sym=?DoInsertKey@?$rbtree@MM
template pair<FloatTreeC::iterator, bool> FloatTreeC::DoInsertKey(const float&, true_type);
// @ 0x00566ad0 odn sym=?DoNukeSubtree@?$rbtree@IU?$pair@IUX568110
template void TreeA::DoNukeSubtree(TreeA::node_type*);
// @ 0x00566c70 odn sym=?upper_bound@?$rbtree@II
template UIntTree::iterator UIntTree::upper_bound(const uint32_t&);
// @ 0x00566ce0 odn sym=?DoNukeSubtree@?$rbtree@IU?$pair@IUX568320
template void TreeC::DoNukeSubtree(TreeC::node_type*);
// @ 0x00566d20 odn sym=?DoInsertKey@?$rbtree_multi@II
template UIntMultiTree::iterator UIntMultiTree::DoInsertKey(const uint32_t&, false_type);

// ---------------------------------------------------------------------- hashtable
typedef pair<uint32_t, uint32_t> UIntPair;
// @ 0x00567200 odn sym=?DoAllocateNode@?$hashtable
template hashtable<UIntPair>::node_type* hashtable<UIntPair>::DoAllocateNode(const UIntPair&);
// @ 0x00567260 odn sym=?DoAllocateBuckets@?$hashtable
template hashtable<UIntPair>::node_type** hashtable<UIntPair>::DoAllocateBuckets(unsigned);

// ---------------------------------------------------------------------- deque
struct Pod8 { uint32_t a, b; };
// @ 0x005676a0 odn sym=?insert@?$deque2@UPod8
template deque2<Pod8>::iterator deque2<Pod8>::insert(deque2<Pod8>::iterator, const Pod8&);
// @ 0x00567740 odn sym=?DoPopBack@?$deque2@UPod8
template void deque2<Pod8>::DoPopBack();
// @ 0x005677f0 odn sym=??E?$DequeIterator2@UPod8
template DequeIterator2<Pod8>& DequeIterator2<Pod8>::operator++();
// @ 0x00567860 odn sym=?upper_bound@?$deque_multiset@UPod8
template deque_multiset<Pod8>::iterator deque_multiset<Pod8>::upper_bound(const Pod8&);

// ---------------------------------------------------------------------- rbtree_iterator members
// @ 0x00566c50 odn sym=??0?$rbtree_iterator@IPAI@eastl@@QAE@PBU?$rbtree_node
template<> rbtree_iterator<uint32_t>::rbtree_iterator(const node_type* pNode)
    : mpNode(const_cast<node_type*>(pNode)) {}
// @ 0x005673e0 odn sym=??0?$rbtree_iterator@IPBI@eastl@@QAE@ABU01@@Z
template<> rbtree_iterator<uint32_t, const uint32_t*>::rbtree_iterator(const rbtree_iterator<uint32_t, const uint32_t*>& x)
    : mpNode(x.mpNode) {}

// ---------------------------------------------------------------------- set_union
namespace eastl {
  template<int Pad, class IIt, class OIt> inline OIt copy_padded(IIt first, IIt last, OIt result)
  {
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    ScratchSlots<Pad>();
    return copy_impl::do_copy(first, last, result);
  }
  template<class I1, class I2, class O>
  O set_union(I1 first1, I1 last1, I2 first2, I2 last2, O result)
  {
    ScratchSlots<8>();
    while((first1 != last1) && (first2 != last2))
    {
        if(*first1 < *first2)
        {
            *result = *first1;
            ++first1;
        }
        else if(*first2 < *first1)
        {
            *result = *first2;
            ++first2;
        }
        else
        {
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return eastl::copy_padded<7>(first2, last2, eastl::copy_padded<4>(first1, last1, result));
  }
}
struct UIntVectorSet : public vector<uint32_t> {
    iterator insert(iterator position, const uint32_t& value);    // 0x566060
};
// @ 0x00567400 odn sym=??$set_union@PAIPAIV?$insert_iterator
template insert_iterator<UIntVectorSet> eastl::set_union(uint32_t*, uint32_t*, uint32_t*, uint32_t*, insert_iterator<UIntVectorSet>);

// The pair constructors and DoDestroyValues above are specializations of members defined in-class,
// which cl treats as inline: reference them from an emitter with inlining disabled so they are emitted.
#pragma inline_depth(0)
void EmitOutOfLineMembers(void* p, const uint32_t& k, const X568110& a, const UIntVector& b,
                          const X568320& c, vector2<Elem28>& v, Elem28* first, Elem28* last)
{
    ::new(p) PairA(k, a);
    ::new(p) PairB(k, b);
    ::new(p) PairC(k, c);
    v.DoDestroyValues(first, last);
}
#pragma inline_depth()
