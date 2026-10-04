// Slice s005646b0: EASTL container instantiations (rbtree / vector / vector_set / vector_map / deque)
// and a few SP::FunctionalMatch helpers. Module is /Od /Ob1 (no /EHsc), so the EASTL inline
// layers are reproduced with their real structure; ScratchSlots<N> reproduces the stack slots left
// behind by inlined EASTL helpers whose locals were optimized out of the source here.
typedef unsigned int size_t;
typedef unsigned int uint32_t;
inline void* operator new(size_t, void* p) { return p; }
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace eastl {
  class allocator {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };

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

  template<class K, class V, class Compare, class ExtractKey>
  class rbtree {
  public:
    typedef rbtree_node<V> node_type; typedef rbtree_iterator<V> iterator; typedef K key_type; typedef unsigned size_type;
    typedef rbtree_iterator<V, const V*> const_iterator;
    Compare          mCompare;
    rbtree_node_base mAnchor;
    size_type        mnSize;
    allocator        mAllocator;

    rbtree(const allocator& a);                                         // 0x4b5980
    iterator end() { return iterator((node_type*)&mAnchor); }
    iterator find(const key_type& key);
    const_iterator lower_bound(const key_type& key);
    const_iterator upper_bound(const key_type& key);
    size_type erase(const key_type& key);
    iterator erase(iterator position);
    void clear();
    void reset();
    void DoNukeSubtree(node_type* pNode);
    void DoFreeNode(node_type* pNode);
    pair<const_iterator, const_iterator> equal_range(const key_type& key);
  };

  template<class K, class V, class C, class E>
  typename rbtree<K,V,C,E>::iterator rbtree<K,V,C,E>::find(const key_type& key)
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

  template<class K, class V, class C, class E>
  inline void rbtree<K,V,C,E>::DoFreeNode(node_type* pNode)
  {
    pNode->~node_type();
    mAllocator.deallocate(pNode, sizeof(node_type));
  }

  template<class K, class V, class C, class E>
  inline typename rbtree<K,V,C,E>::iterator rbtree<K,V,C,E>::erase(iterator position)
  {
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
  }

  template<class K, class V, class C, class E>
  typename rbtree<K,V,C,E>::size_type rbtree<K,V,C,E>::erase(const key_type& key)
  {
    const iterator it(find(key));
    if(it != end())
    {
        erase(it);
        return 1;
    }
    return 0;
  }

  template<class K, class V, class C, class E>
  inline void rbtree<K,V,C,E>::reset()
  {
    mAnchor.mpNodeRight  = &mAnchor;
    mAnchor.mpNodeLeft   = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor       = 0;
    mnSize               = 0;
  }

  template<class K, class V, class C, class E>
  void rbtree<K,V,C,E>::clear()
  {
    DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
    reset();
  }

  template<class K, class V, class C, class E>
  pair<typename rbtree<K,V,C,E>::const_iterator, typename rbtree<K,V,C,E>::const_iterator>
  rbtree<K,V,C,E>::equal_range(const key_type& key)
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

// ---------------------------------------------------------------------- element types
struct VecSetMember { uint32_t d[7]; ~VecSetMember(); };     // dtor 0x564470
struct VecPairMember { uint32_t d[9]; ~VecPairMember(); };   // dtor 0x553fb0
// 0x50-byte record: a key block, then two containers.
struct Record50 {
    unsigned __int64 mKey[2]; // 8-byte aligned (vector allocations use alignment 8)
    VecSetMember  mSet;      // +0x10
    VecPairMember mPairs;    // +0x2c
    Record50();              // 0x5658c0
};
struct Pod50 { uint32_t d[20]; };
struct Pod10 { uint32_t d[4]; };
struct Pod8 { uint32_t a, b; };

struct ConstraintTail { uint32_t d[5]; ~ConstraintTail(); }; // dtor 0x4e1780
// 0x28-byte element with a destructible tail at +0x14.
struct Elem28 {
    uint32_t       mHead[5];
    ConstraintTail mTail;    // +0x14
    Elem28(const Elem28&);              // 0x565920
    Elem28& operator=(const Elem28&);   // 0x567a10
};

typedef rbtree<int, int, less<int>, use_self<int> > IntTree;
typedef rbtree<uint32_t, uint32_t, less<uint32_t>, use_self<uint32_t> > UIntTree;
typedef rbtree<float, float, less<float>, use_self<float> > FloatTree;

// @ 0x005646b0 odn sym=??1?$vector@URecord50@@
template vector<Record50>::~vector();
// @ 0x00564720 odn sym=?reserve@?$vector@UPod50@@
template void vector<Pod50>::reserve(unsigned);
// @ 0x00564820 odn sym=?push_back@?$vector@URecord50@@Vallocator@eastl@@@eastl@@QAEXXZ
template void vector<Record50>::push_back();
// @ 0x005648c0 odn sym=?erase@?$rbtree@IIU?$less@I@eastl@@U?$use_self@I@2@@eastl@@QAEIABI
template UIntTree::size_type UIntTree::erase(const uint32_t&);
// @ 0x00564960 odn sym=?insert@?$vector_set@I
template pair<vector_set<uint32_t>::iterator, bool> vector_set<uint32_t>::insert(const uint32_t&);
// @ 0x00564a10 odn
template uint32_t& vector_map<uint32_t, uint32_t>::operator[](const uint32_t&);
// @ 0x00564ab0 odn sym=?find@?$rbtree@HH
template IntTree::iterator IntTree::find(const int&);
// @ 0x00564b50 odn sym=?find@?$rbtree@II
template UIntTree::iterator UIntTree::find(const uint32_t&);
// @ 0x00564bf0 odnsf sym=?find@?$rbtree@MM
template FloatTree::iterator FloatTree::find(const float&);
// @ 0x00564cb0 odn sym=??0?$multiset@
template multiset<uint32_t, uint32_t>::multiset(const allocator&);
// @ 0x00564cd0 odn sym=?clear@?$rbtree@II
template void UIntTree::clear();
// @ 0x00564d20 odn sym=?equal_range@?$rbtree@II
template pair<UIntTree::const_iterator, UIntTree::const_iterator> UIntTree::equal_range(const uint32_t&);
// @ 0x00564d80 odn sym=?push_back@?$vector@UElem28@@Vallocator@eastl@@@eastl@@QAEXABUElem28
template void vector<Elem28>::push_back(const Elem28&);
// @ 0x00564df0 odn sym=?erase@?$vector@UElem28
template vector<Elem28>::iterator vector<Elem28>::erase(Elem28*);

struct MapValueU { uint32_t first; vector<uint32_t> second; };
// @ 0x00564f50 odn sym=??C?$rbtree_iterator@UMapValueU
template<> MapValueU* rbtree_iterator<MapValueU, const MapValueU*>::operator->() const { return &mpNode->mValue; }

// @ 0x00564fd0 odn sym=??1?$vectorI@UPod10
template vectorI<Pod10>::~vectorI();
// @ 0x00565040 odn sym=?insert@?$vector_multiset@I
template pair<vector_multiset<uint32_t>::iterator, bool> vector_multiset<uint32_t>::insert(const uint32_t&);

// ---------------------------------------------------------------------- set-merging helpers
typedef rbtree_iterator<MapValueU, const MapValueU*> MapIter;
struct UIntRangeMap {
    pair<MapIter, MapIter> FindRange(uint32_t a, uint32_t b);   // 0x5659e0
    pair<MapIter, MapIter> FindRange(float a, float b);         // 0x565a30
};
struct UIntVector : public vector<uint32_t> {
    void clear() { erase(mpBegin, mpEnd); }
    iterator erase(iterator first, iterator last);              // 0x4769b0
    void reserve(size_type n);                                  // 0x565f50
    void swap(UIntVector& x);                                   // 0x565df0
};
struct SetMerger {
    char       pad0[0x15c];
    UIntVector mTemp;        // +0x15c
    void UnionRange(UIntVector* out, uint32_t a, uint32_t b, UIntRangeMap* map);
    void UnionRange(UIntVector* out, float a, float b, UIntRangeMap* map);
};

// @ 0x005650b0 odn sym=?UnionRange@SetMerger@@QAEXPAUUIntVector@@IIPAUUIntRangeMap@@@Z
void SetMerger::UnionRange(UIntVector* out, uint32_t a, uint32_t b, UIntRangeMap* map)
{
    pair<MapIter, MapIter> range = map->FindRange(a, b);
    for(MapIter it(range.first); it != range.second; ++it)
    {
        UIntVector& alloc = (UIntVector&)it->second;
        uint32_t* count = alloc.mpBegin;
        uint32_t* t2 = alloc.mpEnd;
        uint32_t* t38 = out->mpBegin;
        uint32_t* res = out->mpEnd;
        mTemp.clear();
        mTemp.reserve(alloc.size() + out->size());
        eastl::set_union(out->begin(), out->end(), alloc.begin(), alloc.end(), eastl::inserter(mTemp, mTemp.begin()));
        out->swap(mTemp);
    }
}

// @ 0x00565210 odn sym=?UnionRange@SetMerger@@QAEXPAUUIntVector@@MMPAUUIntRangeMap@@@Z
void SetMerger::UnionRange(UIntVector* out, float a, float b, UIntRangeMap* map)
{
    pair<MapIter, MapIter> range = map->FindRange(a, b);
    for(MapIter it(range.first); it != range.second; ++it)
    {
        UIntVector& alloc = (UIntVector&)it->second;
        uint32_t* count = alloc.mpBegin;
        uint32_t* t2 = alloc.mpEnd;
        uint32_t* t38 = out->mpBegin;
        uint32_t* res = out->mpEnd;
        mTemp.clear();
        mTemp.reserve(alloc.size() + out->size());
        eastl::set_union(out->begin(), out->end(), alloc.begin(), alloc.end(), eastl::inserter(mTemp, mTemp.begin()));
        out->swap(mTemp);
    }
}

struct UIntVectorI : public vector<uint32_t> {
    iterator insert(iterator position, const uint32_t& value);  // 0x566060
};
// @ 0x00565380 odn sym=??$set_intersection@PAIPAIV?$insert_iterator
template insert_iterator<UIntVectorI> eastl::set_intersection(uint32_t*, uint32_t*, uint32_t*, uint32_t*, insert_iterator<UIntVectorI>);
// @ 0x00565410 odn sym=??$set_difference@PAIPAIV?$insert_iterator
template insert_iterator<UIntVectorI> eastl::set_difference(uint32_t*, uint32_t*, uint32_t*, uint32_t*, insert_iterator<UIntVectorI>);

// ---------------------------------------------------------------------- SP::FunctionalMatch helpers
namespace SP { namespace FunctionalMatch {
  enum eType { kInteger = 48342877, kFloat = 48343039, kTerminal = 48343507 };
  // Retail Constraint is 0x24 bytes (the 2008 PDB shows 0x10): a destructible tail follows.
  struct Constraint {
    uint32_t       mParameter;  // +0x0
    eType          mType;       // +0x4
    int            mMin;        // +0x8
    int            mMax;        // +0xc
    ConstraintTail mTail;       // +0x10
    Constraint(uint32_t parameter, int value, bool flag);   // 0x558960
    bool IsTerminal() const;                                // 0x558b20
  };
  // A {current, previous} constraint cursor; its destructor clears the cursor.
  struct ConstraintCursor {
    Constraint* mpNext;
    Constraint* mpCur;
    ConstraintCursor(const ConstraintCursor& x) : mpNext(x.mpNext), mpCur(x.mpCur) {}
    Constraint* operator->() const { return mpCur; }
    Constraint& operator*() const { return *mpCur; }
    ConstraintCursor& operator++() { mpNext++; mpCur = mpNext - 1; return *this; }
    ~ConstraintCursor() { mpNext = 0; }
  };
  struct ConstraintList {
    void Add(uint32_t key, const Constraint& c);                       // 0x562280
    void AddEnd(uint32_t key, const Constraint& c);                    // 0x5623f0
    void AddRange(uint32_t key, const Constraint* p, unsigned n);      // 0x5675a0
    void AddRange(uint32_t key, ConstraintCursor c, unsigned n);       // 0x567600
    void AddFirst(uint32_t key, const Constraint* p, unsigned n);
    void AddFirst(uint32_t key, ConstraintCursor c, unsigned n);
    void Set(uint32_t key, const Constraint* p, unsigned n);
    void Set(uint32_t key, ConstraintCursor c, unsigned n);
  };

  // @ 0x00565500 odn sym=?AddFirst@ConstraintList@FunctionalMatch@SP@@QAEXIPBUConstraint@23@I@Z
  void ConstraintList::AddFirst(uint32_t key, const Constraint* p, unsigned n)
  {
    if(n > 0 && !p->IsTerminal())
    {
        Add(key, *p);
        ++p;
        --n;
    }
    AddRange(key, p, n);
  }

  // @ 0x00565560 odn sym=?AddFirst@ConstraintList@FunctionalMatch@SP@@QAEXIUConstraintCursor@23@I@Z
  void ConstraintList::AddFirst(uint32_t key, ConstraintCursor c, unsigned n)
  {
    if(n > 0 && !c->IsTerminal())
    {
        Add(key, *c);
        ++c;
        --n;
    }
    AddRange(key, c, n);
  }

  // @ 0x005655f0 odn sym=?Set@ConstraintList@FunctionalMatch@SP@@QAEXIPBUConstraint@23@I@Z
  void ConstraintList::Set(uint32_t key, const Constraint* p, unsigned n)
  {
    ScratchSlots<10>();
    Add(key, Constraint(0x54a32960, 0, true));
    AddRange(key, p, n);
    AddEnd(key, Constraint(0xcd6e902c, 0, false));
  }

  // @ 0x00565660 odn sym=?Set@ConstraintList@FunctionalMatch@SP@@QAEXIUConstraintCursor@23@I@Z
  void ConstraintList::Set(uint32_t key, ConstraintCursor c, unsigned n)
  {
    ScratchSlots<5>();
    Add(key, Constraint(0x54a32960, 0, true));
    AddRange(key, c, n);
    AddEnd(key, Constraint(0xcd6e902c, 0, false));
    ScratchSlots<5>();
  }
}}

struct Pod4 { uint32_t v; };
// @ 0x005656f0 odn sym=??1?$deque@UPod4
template deque<Pod4>::~deque();
// @ 0x00565740 odn sym=?begin@?$deque@UPod4
template deque<Pod4>::iterator deque<Pod4>::begin();
