// Slice s00565760: EASTL container instantiations (rbtree / vector / vector_set / vector_map / deque)
// and a few SP::FunctionalMatch helpers. Module is /Od /Ob1 (no /EHsc), so the EASTL inline
// layers are reproduced with their real structure; ScratchSlots<N> reproduces the stack slots left
// behind by inlined EASTL helpers whose locals were optimized out of the source here.
typedef unsigned int size_t;
typedef unsigned int uint32_t;
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
  };
  template<class T> inline int operator-(const DequeIterator2<T>& a, const DequeIterator2<T>& b)
  {
    return ((int)DequeIterator2<T>::kSubarraySize * ((a.mpCurrentArrayPtr - b.mpCurrentArrayPtr) - 1)) +
           (a.mpCurrent - a.mpBegin) + (b.mpEnd - b.mpCurrent);
  }
  template<class T> class deque2 {
  public:
    typedef DequeIterator2<T> iterator; typedef T value_type; typedef unsigned size_type;
    T** mpPtrArray; size_t mnPtrArraySize; iterator mItBegin; iterator mItEnd; allocator mAllocator;
    iterator end();
    size_type size();
    T& back();
    void pop_back();
    void DoPopBack();                                                  // 0x567740
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
  template<class T> class deque_multiset : public deque2<T> {
  public:
    typedef typename deque2<T>::iterator iterator;
    iterator upper_bound(const T& value);                              // 0x567860
    iterator insert(iterator position, const T& value);                // 0x5676a0
    pair<iterator, bool> insert(const T& value);
  };
  template<class T> pair<typename deque_multiset<T>::iterator, bool> deque_multiset<T>::insert(const T& value)
  {
    iterator itUB(upper_bound(value));
    ScratchSlots<2>();
    return pair<iterator, bool>(insert(itUB, value), true);
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

// ---------------------------------------------------------------------- element types
struct IntRange { int mMin; int mMax; };
struct FloatRange { float mMin; float mMax; };
struct ConstraintTail { uint32_t d[5]; ConstraintTail(const ConstraintTail&); ~ConstraintTail(); }; // copy 0x4e38d0, dtor 0x4e1780
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
    // Stand-in for the compiler-generated scalar deleting destructor (??_G, 0x4e4310), which the
    // original calls out of line (flags 0) when destroying elements in place.
    void* ScalarDeletingDtor(unsigned int flags);
  };
}}
using SP::FunctionalMatch::Constraint;

struct Elem28 {
    uint32_t   mKey;
    Constraint mConstraint;   // +0x4
    Elem28(const Elem28& x);
    Elem28& operator=(const Elem28&);   // 0x567a10
};
// @ 0x00565920 odn
Elem28::Elem28(const Elem28& x)
    : mKey((ScratchSlots<13>(), x.mKey)), mConstraint(x.mConstraint)
{
}

struct VecSetMember { uint32_t d[7]; VecSetMember(); ~VecSetMember(); };     // ctor 0x571640, dtor 0x564470
struct VecPairMember {                                                     // dtor 0x553fb0
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAlloc[2]; uint32_t mExtra[4];
    VecPairMember() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VecPairMember();
};
struct __declspec(align(8)) Record50 {
    uint32_t*     mpBegin;     // +0x0
    uint32_t*     mpEnd;       // +0x4
    uint32_t*     mpCapacity;  // +0x8
    uint32_t      mPad;        // +0xc
    VecSetMember  mSet;        // +0x10
    VecPairMember mPairs;      // +0x2c
    Record50();
    Record50(const Record50&);              // 0x5678b0
    Record50& operator=(const Record50&);   // 0x567970
};
// @ 0x005658c0 odn
Record50::Record50()
    : mpBegin((ScratchSlots<1>(), (uint32_t*)0)), mpEnd(0), mpCapacity(0)
{
}

struct Pod8 { uint32_t a, b; };
typedef pair<uint32_t, uint32_t> UIntPair;

// @ 0x00565760 odn sym=?end@?$deque2@UPod8
template deque2<Pod8>::iterator deque2<Pod8>::end();
// @ 0x00565780 odn sym=?size@?$deque2@UPod8
template deque2<Pod8>::size_type deque2<Pod8>::size();
// @ 0x005657e0 odn sym=?back@?$deque2@UPod8
template Pod8& deque2<Pod8>::back();
// @ 0x00565810 odn sym=?pop_back@?$deque2@UPod8
template void deque2<Pod8>::pop_back();
// @ 0x00565850 odn sym=?insert@?$deque_multiset@UPod8@@@eastl@@QAE?AU?$pair
template pair<deque_multiset<Pod8>::iterator, bool> deque_multiset<Pod8>::insert(const Pod8&);
// @ 0x005658b0 odn sym=??D?$DequeIterator2@UPod8
template Pod8& DequeIterator2<Pod8>::operator*() const;

// ---------------------------------------------------------------------- key -> uint-vector multimaps
struct MapValueU { typedef uint32_t first_type; uint32_t first; vector2<uint32_t> second; ~MapValueU() { ScratchSlots<4>(); } };
typedef rbtree_iterator<MapValueU, const MapValueU*> MapIter;
typedef rbtree<uint32_t, MapValueU, less<uint32_t>, use_first<MapValueU>, MapIter> UIntVecTree;
struct MapValueF { typedef float first_type; float first; vector2<uint32_t> second; };
typedef rbtree_iterator<MapValueF, const MapValueF*> MapIterF;
typedef rbtree<float, MapValueF, less<float>, use_first<MapValueF>, MapIterF> FloatVecTree;

struct UIntRangeMap : public UIntVecTree {
    pair<MapIter, MapIter> FindRange(uint32_t a, uint32_t b);
};
struct FloatRangeMap : public FloatVecTree {
    pair<MapIterF, MapIterF> FindRange(float a, float b);
};
// @ 0x005659e0 odn
pair<MapIter, MapIter> UIntRangeMap::FindRange(uint32_t a, uint32_t b)
{
    uint32_t unusedA, unusedB;
    {
        const MapIter itUpper(lower_bound(b));
        const MapIter itLower(lower_bound(a));
        return pair<MapIter, MapIter>(itLower, itUpper);
    }
}
// @ 0x00565a30 odn
pair<MapIterF, MapIterF> FloatRangeMap::FindRange(float a, float b)
{
    uint32_t unusedA, unusedB;
    {
        const MapIterF itUpper(lower_bound(b));
        const MapIterF itLower(lower_bound(a));
        return pair<MapIterF, MapIterF>(itLower, itUpper);
    }
}

// insert_iterator<vector_set<uint>>::operator= (out-of-line copy)
struct UIntVectorSet;
template<> class insert_iterator<UIntVectorSet>;
struct UIntVectorSet : public vector<uint32_t> {
    iterator insert(iterator position, const uint32_t& value);    // 0x566060
};
template<> class insert_iterator<UIntVectorSet> {
public:
    UIntVectorSet&           container;
    UIntVectorSet::iterator  it;
    insert_iterator& operator=(const uint32_t& value);
};
// @ 0x00565a80 odn sym=??4?$insert_iterator@UUIntVectorSet
insert_iterator<UIntVectorSet>& insert_iterator<UIntVectorSet>::operator=(const uint32_t& value)
{
    ScratchSlots<16>();
    it = container.insert(it, value);
    ++it;
    return *this;
}

// @ 0x00565ac0 odn sym=?insert@?$vector2@M
template vector2<float>::iterator vector2<float>::insert(float*, const float&);
template<> inline void vector2<Constraint>::DoDestroyValues(pointer first, pointer last)
{
    for(; first < last; ++first)
        first->ScalarDeletingDtor(0);
}
// @ 0x00565b50 odn sym=?erase@?$vector2@UConstraint
template vector2<Constraint>::iterator vector2<Constraint>::erase(Constraint*, Constraint*);
// @ 0x00565c80 odn sym=?insert@?$vector2@U?$pair@II
template vector2<UIntPair>::iterator vector2<UIntPair>::insert(UIntPair*, const UIntPair&);
// @ 0x00565d20 odn sym=?insert@?$vector_map2@II
template vector_map2<uint32_t, uint32_t>::iterator vector_map2<uint32_t, uint32_t>::insert(UIntPair*, const UIntPair&);
// @ 0x00565df0 odn sym=?swap@?$vector2@I
template void vector2<uint32_t>::swap(vector2<uint32_t>&);
// @ 0x00565f50 odn sym=?reserve@?$vector2@I
template void vector2<uint32_t>::reserve(unsigned);
// @ 0x00566060 odn sym=?insert@?$vector_set2@I
template vector_set2<uint32_t>::iterator vector_set2<uint32_t>::insert(uint32_t*, const uint32_t&);

// ---------------------------------------------------------------------- vector<Record50>
template<> inline void vector2<Record50>::DoFree(pointer p, size_type n)
{
    if(p && ((int*)p)[-1])
        mAllocator.deallocate(p, n);
}
// @ 0x005660e0 odn sym=?erase@?$vector2@URecord50
template<> vector2<Record50>::iterator vector2<Record50>::erase(iterator first, iterator last)
{
    iterator const position = eastl::copy(last, mpEnd, first);
    ScratchSlots<8>();
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

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

// @ 0x005661b0 odn sym=?DoInsertValue@?$vector2@URecord50
template<> void vector2<Record50>::DoInsertValue(iterator position, const value_type& value)
{
    if(mpEnd != mpCapacity)
    {
        const Record50* pValue = &value;
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
        pointer n16 = eastl::uninitialized_copy_ptr2(mpBegin, position, other);
        ::new(n16) value_type(value);
        n16 = eastl::uninitialized_copy_ptr2(position, mpEnd, ++n16);
        ScratchSlots<27>();
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin    = other;
        mpEnd      = n16;
        mpCapacity = other + n26;
    }
}
// @ 0x00566490 odn sym=??$uninitialized_copy_ptr2@URecord50
template Record50* eastl::uninitialized_copy_ptr2(Record50*, Record50*, Record50*);

// ---------------------------------------------------------------------- rbtree out-of-line members
typedef rbtree<uint32_t, uint32_t, less<uint32_t>, use_self<uint32_t> > UIntTree;
typedef rbtree_iterator<int, const int*> IntIterC;
typedef rbtree<int, int, less<int>, use_self<int>, IntIterC> IntTreeC;
typedef rbtree_iterator<float, const float*> FloatIterC;
typedef rbtree<float, float, less<float>, use_self<float>, FloatIterC> FloatTreeC;

// @ 0x00566510 odn sym=?erase@?$rbtree@IIU?$less@I@eastl@@U?$use_self@I@2@U?$rbtree_iterator@I
template UIntTree::iterator UIntTree::erase(UIntTree::iterator);
// @ 0x00566570 odn sym=?erase@?$rbtree@IUMapValueU
template UIntVecTree::iterator UIntVecTree::erase(UIntVecTree::iterator);
// @ 0x00566600 odn sym=?DoInsertKey@?$rbtree@HH
template pair<IntTreeC::iterator, bool> IntTreeC::DoInsertKey(const int&, true_type);
// @ 0x00566880 odnsf sym=?lower_bound@?$rbtree@MM
template FloatTreeC::iterator FloatTreeC::lower_bound(const float&);
// @ 0x00566900 odn sym=?DoNukeSubtree@?$rbtree@IUMapValueU
template void UIntVecTree::DoNukeSubtree(UIntVecTree::node_type*);
