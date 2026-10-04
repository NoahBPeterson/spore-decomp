// Slice s00569690: EASTL instantiations (vector<Vector3>::operator=, rbtree node creation / subtree
// copy, deque<Pod8> push/init/iterator helpers, the deque copy / copy_backward chain) plus two
// game helpers that weight parts by their bounding-box volume.
// Module is /Od /Ob1 /arch:SSE /fp:fast (no /EHsc). ScratchSlots<N> reproduces stack slots left
// behind by inlined EASTL helpers whose locals were optimized out of the source here.
typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef int ptrdiff_t;
inline void* operator new(size_t, void* p) { return p; }
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3 { float x, y, z; };

namespace eastl {
  class allocator {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };

  struct true_type {};
  struct false_type {};
  template<class T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
  template<class P> struct use_first { const typename P::first_type& operator()(const P& x) const { return x.first; } };
  template<class T1, class T2> struct pair {
    typedef T1 first_type; typedef T2 second_type;
    T1 first; T2 second;
  };

  // ------------------------------------------------------------------ vector
  template<class T, class A = allocator> class vector {
  public:
    typedef vector<T, A> this_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type;
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }
    this_type& operator=(const this_type& x);
    pointer DoRealloc(size_type n, const T* first, const T* last);      // 0x56a140
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
    void DoFree(pointer p, size_type n)
    {
        if(p)
            mAllocator.deallocate(p, n);
    }
  };

  template<class II, class OI> OI uninitialized_copy_ptr(II first, II last, OI result); // 0x50eb40

  struct copy_impl_generic {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        for(; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
  };
  template<class II, class OI> inline OI copy_ptr(II first, II last, OI result)
  {
    const bool bOutputIsReverse = false;
    const bool bInputIsReverse = false;
    const bool bHasTrivialCopy = false;
    return copy_impl_generic::do_copy(first, last, result);
  }

  template<class T, class A>
  typename vector<T,A>::this_type& vector<T,A>::operator=(const this_type& x)
  {
    if(&x != this)
    {
        const size_type n = x.size();
        if(n > capacity())
        {
            pointer const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();   // reserved frame of the declined inline DoRealloc
            DoDestroyValues(mpBegin, mpEnd);
            DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
            mpBegin    = pNewData;
            mpCapacity = mpBegin + n;
        }
        else if(n > size())
        {
            eastl::copy_ptr(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            eastl::uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<11>();  // reserved frame of the declined inline uninitialized_copy_ptr
        }
        else
        {
            iterator const position = eastl::copy_ptr(x.mpBegin, x.mpEnd, mpBegin);
            DoDestroyValues(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
  }

  // ------------------------------------------------------------------ rbtree
  struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
  };
  template<class V> struct rbtree_node : public rbtree_node_base { V mValue; };

  template<class K, class V, class Compare, class ExtractKey>
  class rbtree {
  public:
    typedef rbtree_node<V> node_type; typedef V value_type; typedef K key_type; typedef unsigned size_type;
    Compare          mCompare;
    rbtree_node_base mAnchor;     // +0x4
    size_type        mnSize;      // +0x14
    allocator        mAllocator;  // +0x18

    node_type* DoAllocateNode() { return (node_type*)mAllocator.allocate(sizeof(node_type), 4, 0); }
    node_type* DoCreateNode(const value_type& value);
    node_type* DoCloneNode(const node_type* pNodeSource, node_type* pNodeParent);
    node_type* DoCopySubtree(const node_type* pNodeSource, node_type* pNodeDest);
  };

  template<class K, class V, class C, class E>
  typename rbtree<K,V,C,E>::node_type* rbtree<K,V,C,E>::DoCreateNode(const value_type& value)
  {
    node_type* const pNode = DoAllocateNode();
    ::new(&pNode->mValue) value_type(value);
    return pNode;
  }

  template<class K, class V, class C, class E>
  typename rbtree<K,V,C,E>::node_type* rbtree<K,V,C,E>::DoCloneNode(const node_type* pNodeSource, node_type* pNodeParent)
  {
    node_type* const pNode = DoCreateNode(pNodeSource->mValue);
    pNode->mpNodeRight  = 0;
    pNode->mpNodeLeft   = 0;
    pNode->mpNodeParent = pNodeParent;
    pNode->mColor       = pNodeSource->mColor;
    return pNode;
  }

  template<class K, class V, class C, class E>
  typename rbtree<K,V,C,E>::node_type* rbtree<K,V,C,E>::DoCopySubtree(const node_type* pNodeSource, node_type* pNodeDest)
  {
    node_type* const pNewNodeRoot = DoCloneNode(pNodeSource, pNodeDest);

    if(pNodeSource->mpNodeRight)
        pNewNodeRoot->mpNodeRight = DoCopySubtree((const node_type*)pNodeSource->mpNodeRight, pNewNodeRoot);

    node_type* pNewNodeLeft;
    for(pNodeSource = (node_type*)pNodeSource->mpNodeLeft, pNodeDest = pNewNodeRoot;
        pNodeSource;
        pNodeSource = (node_type*)pNodeSource->mpNodeLeft, pNodeDest = pNewNodeLeft)
    {
        pNewNodeLeft = DoCloneNode(pNodeSource, pNodeDest);
        pNodeDest->mpNodeLeft = pNewNodeLeft;
        if(pNodeSource->mpNodeRight)
            pNewNodeLeft->mpNodeRight = DoCopySubtree((const node_type*)pNodeSource->mpNodeRight, pNewNodeLeft);
    }
    return pNewNodeRoot;
  }

  // ------------------------------------------------------------------ intrusive_ptr
  template<class T> class intrusive_ptr {
  public:
    T* mpObject;
    intrusive_ptr(const intrusive_ptr& ip) : mpObject(ip.mpObject)
    {
        if(mpObject)
            mpObject->AddRef();
    }
  };

  // ------------------------------------------------------------------ deque
  template<class T> struct DequeIterator {
    enum { kDequeSubarraySize = 32 };
    typedef DequeIterator<T> this_type; typedef ptrdiff_t difference_type;
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator(const DequeIterator& x);                                 // 0x420050
    T& operator*() const;                                                  // 0x5658b0
    DequeIterator& operator++();                                           // 0x5677f0
    DequeIterator& operator--();                                           // 0x5692d0
    DequeIterator& operator+=(difference_type n);
    void SetSubarray(T** pCurrentArrayPtr);                                // 0x569340
    this_type copy(const this_type& first, const this_type& last, false_type);
    void copy_backward(const this_type& first, const this_type& last, false_type);
  };
  template<class T> inline bool operator!=(const DequeIterator<T>& a, const DequeIterator<T>& b) { return a.mpCurrent != b.mpCurrent; }
  template<class T> inline ptrdiff_t operator-(const DequeIterator<T>& a, const DequeIterator<T>& b)
  {
    return ((ptrdiff_t)DequeIterator<T>::kDequeSubarraySize * ((a.mpCurrentArrayPtr - b.mpCurrentArrayPtr) - 1)) +
           (a.mpCurrent - a.mpBegin) + (b.mpEnd - b.mpCurrent);
  }

  // 4-byte allocator for this deque (the derived container keeps its comparator at +0x2c).
  struct deque_allocator {
    const char* mpName;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
  };

  template<class T> class DequeBase {
  public:
    typedef T value_type; typedef unsigned size_type; typedef ptrdiff_t difference_type;
    typedef DequeIterator<T> iterator;
    enum { kMinPtrArraySize = 8, kDequeSubarraySize = 32 };
    enum Side { kSideFront, kSideBack };
    T**             mpPtrArray;      // +0x0
    size_type       mnPtrArraySize;  // +0x4
    iterator        mItBegin;        // +0x8
    iterator        mItEnd;          // +0x18
    deque_allocator mAllocator;      // +0x28

    T*  DoAllocateSubarray();                                              // 0x4ab320
    T** DoAllocatePtrArray(size_type n);
    void DoReallocPtrArray(size_type nAdditionalCapacity, Side allocationSide); // 0x503470
    void DoInit(size_type n);
    void DoPushFront(const value_type& value);
    void DoPushBack(const value_type& value);
  };

  template<class T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }

  template<class T> T** DequeBase<T>::DoAllocatePtrArray(size_type n)
  {
    return (T**)mAllocator.allocate(n * sizeof(T*), 4, 0);
  }

  template<class T> void DequeBase<T>::DoInit(size_type n)
  {
    const size_type nNewPtrArraySize = (size_type)((n / kDequeSubarraySize) + 1);
    const size_type kMinPtrArraySize_ = kMinPtrArraySize;

    mnPtrArraySize = eastl::max_alt(kMinPtrArraySize_, (nNewPtrArraySize + 2));
    mpPtrArray     = DoAllocatePtrArray(mnPtrArraySize);

    value_type** const pPtrArrayBegin = (mpPtrArray + ((mnPtrArraySize - nNewPtrArraySize) / 2));
    value_type** const pPtrArrayEnd   = pPtrArrayBegin + nNewPtrArraySize;
    value_type**       pPtrArrayCurrent = pPtrArrayBegin;

    while(pPtrArrayCurrent < pPtrArrayEnd)
        *pPtrArrayCurrent++ = DoAllocateSubarray();

    mItBegin.SetSubarray(pPtrArrayBegin);
    mItBegin.mpCurrent = mItBegin.mpBegin;

    mItEnd.SetSubarray(pPtrArrayEnd - 1);
    mItEnd.mpCurrent = mItEnd.mpBegin + (difference_type)(n % kDequeSubarraySize);
  }

  template<class T> void DequeBase<T>::DoPushFront(const value_type& value)
  {
    const value_type valueSaved(value);

    if(mItBegin.mpCurrentArrayPtr == mpPtrArray)
        DoReallocPtrArray(1, kSideFront);

    mItBegin.mpCurrentArrayPtr[-1] = DoAllocateSubarray();
    mItBegin.SetSubarray(mItBegin.mpCurrentArrayPtr - 1);
    mItBegin.mpCurrent = mItBegin.mpEnd - 1;
    ::new(mItBegin.mpCurrent) value_type(valueSaved);
  }

  template<class T> void DequeBase<T>::DoPushBack(const value_type& value)
  {
    const value_type valueSaved(value);

    if(((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1) >= (difference_type)mnPtrArraySize)
        DoReallocPtrArray(1, kSideBack);

    mItEnd.mpCurrentArrayPtr[1] = DoAllocateSubarray();
    ::new(mItEnd.mpCurrent) value_type(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
  }

  template<class T> DequeIterator<T>& DequeIterator<T>::operator+=(difference_type n)
  {
    const difference_type subarrayPosition = (mpCurrent - mpBegin) + n;

    if((size_t)subarrayPosition < (size_t)kDequeSubarraySize)
        mpCurrent += n;
    else
    {
        const difference_type subarrayIndex = (((16777216 + subarrayPosition) / (difference_type)kDequeSubarraySize)) - (16777216 / (difference_type)kDequeSubarraySize);
        SetSubarray(mpCurrentArrayPtr + subarrayIndex);
        mpCurrent = mpBegin + (subarrayPosition - (subarrayIndex * (difference_type)kDequeSubarraySize));
    }
    return *this;
  }

  // distance() for random-access iterators (the iterator-category tag layer is elided; it leaves one slot)
  template<class RI> inline ptrdiff_t distance_impl(RI first, RI last)
  {
    return last - first;
  }
  template<class I> ptrdiff_t distance(I first, I last)
  {
    ScratchSlots<1>();
    return eastl::distance_impl(first, last);
  }

  // copy chain (generic, non-trivial iterators)
  template<class II, class OI> inline OI copy_chooser(II first, II last, OI result);
  template<bool bInputIsReverseIterator, bool bOutputIsReverseIterator> struct copy_impl {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        return eastl::copy_chooser(first, last, result);
    }
  };
  template<class II, class OI> inline OI copy(II first, II last, OI result)
  {
    const bool bOutputIsReverseIterator = false;
    const bool bInputIsReverseIterator  = false;
    return eastl::copy_impl<false, false>::do_copy(first, last, result);
  }
  struct copy_loop {
    template<class II, class OI> static OI do_copy(II first, II last, OI result)
    {
        for(; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
  };
  template<class II, class OI> inline OI copy_chooser(II first, II last, OI result)
  {
    const bool bHasTrivialCopy = false;
    return copy_loop::do_copy(first, last, result);
  }

  template<class BI1, class BI2> inline BI2 copy_backward_chooser(BI1 first, BI1 last, BI2 resultEnd);
  template<bool bInputIsReverseIterator, bool bOutputIsReverseIterator> struct copy_backward_impl {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        return eastl::copy_backward_chooser(first, last, resultEnd);
    }
  };
  template<class BI1, class BI2> inline BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool bOutputIsReverseIterator = false;
    const bool bInputIsReverseIterator  = false;
    return eastl::copy_backward_impl<false, false>::do_copy(first, last, resultEnd);
  }
  struct copy_backward_loop {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        while(last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
  };
  template<class BI1, class BI2> inline BI2 copy_backward_chooser(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool bHasTrivialCopy = false;
    return copy_backward_loop::do_copy(first, last, resultEnd);
  }

  template<class T> DequeIterator<T> DequeIterator<T>::copy(const this_type& first, const this_type& last, false_type)
  {
    return eastl::copy(first, last, *this);
  }
  template<class T> void DequeIterator<T>::copy_backward(const this_type& first, const this_type& last, false_type)
  {
    eastl::copy_backward(first, last, *this);
  }
}
using namespace eastl;

// ---------------------------------------------------------------------- value types
struct UIntVectorBase { uint32_t d[6]; UIntVectorBase(const UIntVectorBase&); };   // copy 0x50d440
struct UIntVector : UIntVectorBase {
    UIntVector(const UIntVector& x) : UIntVectorBase((ScratchSlots<18>(), x)) {}
};
struct X568110Base { uint32_t d[7]; X568110Base(const X568110Base&); };   // copy 0x568110
struct X568110 : X568110Base { X568110(const X568110& x) : X568110Base((ScratchSlots<2>(), x)) {} };
struct X568320Base { uint32_t d[7]; X568320Base(const X568320Base&); };   // copy 0x568320
struct X568320 : X568320Base { X568320(const X568320& x) : X568320Base((ScratchSlots<2>(), x)) {} };
struct RefCounted {
    virtual ~RefCounted();
    virtual int AddRef();
    virtual int Release();
};

typedef pair<uint32_t, UIntVector> PairUV;
typedef pair<float, UIntVector> PairFV;
typedef pair<uint32_t, X568110> PairA;
typedef pair<uint32_t, X568320> PairC;
typedef pair<uint32_t, intrusive_ptr<RefCounted> > PairR;
typedef rbtree<uint32_t, PairUV, less<uint32_t>, use_first<PairUV> > TreeUV;
typedef rbtree<float, PairFV, less<float>, use_first<PairFV> > TreeFV;
typedef rbtree<uint32_t, PairA, less<uint32_t>, use_first<PairA> > TreeA;
typedef rbtree<uint32_t, PairC, less<uint32_t>, use_first<PairC> > TreeC;
typedef rbtree<uint32_t, PairR, less<uint32_t>, use_first<PairR> > TreeR;

// @ 0x00569690 sym=??4?$vector@UVector3
template vector<Vector3>& vector<Vector3>::operator=(const vector<Vector3>&);

// @ 0x00569980 sym=?DoCreateNode@?$rbtree@IU?$pair@IUUIntVector
template TreeUV::node_type* TreeUV::DoCreateNode(const PairUV&);
// @ 0x005699f0 sym=?DoCopySubtree@?$rbtree@IU?$pair@IUUIntVector
template TreeUV::node_type* TreeUV::DoCopySubtree(const TreeUV::node_type*, TreeUV::node_type*);
// @ 0x0056a1a0 sym=?DoCloneNode@?$rbtree@IU?$pair@IUUIntVector
template TreeUV::node_type* TreeUV::DoCloneNode(const TreeUV::node_type*, TreeUV::node_type*);
// @ 0x00569aa0 sym=?DoCreateNode@?$rbtree@IU?$pair@IUX568110
template TreeA::node_type* TreeA::DoCreateNode(const PairA&);
// @ 0x00569b10 sym=?DoCreateNode@?$rbtree@MU?$pair@MUUIntVector
template TreeFV::node_type* TreeFV::DoCreateNode(const PairFV&);
// @ 0x00569b80 sym=?DoCopySubtree@?$rbtree@MU?$pair@MUUIntVector
template TreeFV::node_type* TreeFV::DoCopySubtree(const TreeFV::node_type*, TreeFV::node_type*);
// @ 0x0056a1f0 sym=?DoCloneNode@?$rbtree@MU?$pair@MUUIntVector
template TreeFV::node_type* TreeFV::DoCloneNode(const TreeFV::node_type*, TreeFV::node_type*);
// @ 0x00569c30 sym=?DoCreateNode@?$rbtree@IU?$pair@IUX568320
template TreeC::node_type* TreeC::DoCreateNode(const PairC&);
// @ 0x00569ca0 sym=?DoCreateNode@?$rbtree@IU?$pair@IV?$intrusive_ptr
template TreeR::node_type* TreeR::DoCreateNode(const PairR&);

// ---------------------------------------------------------------------- deque<Pod8>
struct Pod8 { uint32_t a, b; };
typedef DequeIterator<Pod8> Pod8Iter;
// @ 0x00569d20 sym=?DoPushFront@?$DequeBase@UPod8
template void DequeBase<Pod8>::DoPushFront(const Pod8&);
// @ 0x00569dc0 sym=?DoPushBack@?$DequeBase@UPod8
template void DequeBase<Pod8>::DoPushBack(const Pod8&);
// @ 0x00569f90 sym=?DoInit@?$DequeBase@UPod8
template void DequeBase<Pod8>::DoInit(unsigned);
// @ 0x0056a240 sym=?DoAllocatePtrArray@?$DequeBase@UPod8
template Pod8** DequeBase<Pod8>::DoAllocatePtrArray(unsigned);
// @ 0x0056a270 sym=??Y?$DequeIterator@UPod8
template Pod8Iter& Pod8Iter::operator+=(ptrdiff_t);
// @ 0x0056a090 sym=??$distance@U?$DequeIterator@UPod8
template ptrdiff_t eastl::distance(Pod8Iter, Pod8Iter);
// @ 0x00569ef0 sym=?copy@?$DequeIterator@UPod8
template Pod8Iter Pod8Iter::copy(const Pod8Iter&, const Pod8Iter&, false_type);
// @ 0x00569f40 sym=?copy_backward@?$DequeIterator@UPod8
template void Pod8Iter::copy_backward(const Pod8Iter&, const Pod8Iter&, false_type);
// @ 0x0056a300 sym=??$copy@U?$DequeIterator@UPod8
template Pod8Iter eastl::copy(Pod8Iter, Pod8Iter, Pod8Iter);
// @ 0x0056a350 sym=??$copy_backward@U?$DequeIterator@UPod8
template Pod8Iter eastl::copy_backward(Pod8Iter, Pod8Iter, Pod8Iter);
// @ 0x0056a3a0 sym=??$do_copy@U?$DequeIterator@UPod8@@@eastl@@U12@@?$copy_impl
template Pod8Iter eastl::copy_impl<false, false>::do_copy(Pod8Iter, Pod8Iter, Pod8Iter);
// @ 0x0056a3f0 sym=??$do_copy@U?$DequeIterator@UPod8@@@eastl@@U12@@?$copy_backward_impl
template Pod8Iter eastl::copy_backward_impl<false, false>::do_copy(Pod8Iter, Pod8Iter, Pod8Iter);
// @ 0x0056a440 sym=??$copy_chooser@U?$DequeIterator@UPod8
template Pod8Iter eastl::copy_chooser(Pod8Iter, Pod8Iter, Pod8Iter);
// @ 0x0056a4d0 sym=??$copy_backward_chooser@U?$DequeIterator@UPod8
template Pod8Iter eastl::copy_backward_chooser(Pod8Iter, Pod8Iter, Pod8Iter);

// ---------------------------------------------------------------------- part volume weights
struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
    BoundingBox();                       // 0x409c00 (min = +FLT_MAX, max = -FLT_MAX)
    Vector3 GetExtents() const;          // 0x4935f0
};
struct IModelQuery {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual bool GetBounds(uint32_t instance, uint32_t group, const void* pTransform, uint32_t flags,
                           Vector3& lower, Vector3& upper);   // +0x54
};
IModelQuery* GetModelQuery();             // 0x401010

struct Part {                             // 0x1d8 bytes
    uint32_t mGroup;                      // +0x0
    uint32_t mInstance;                   // +0x4
    uint32_t pad08[2];
    float    mScale;                      // +0x10
    uint32_t pad14[31];
    uint32_t mFlags;                      // +0x90
    uint32_t mTransform[81];              // +0x94
};
struct FloatVector {
    float* mpBegin; float* mpEnd; float* mpCapacity; uint32_t mAllocator[2];
    void resize(unsigned n);              // 0x4afc80
};
// @ 0x0056a710 sym=?GetPartVolume@@
bool GetPartVolume(const Part* pPart, float* pVolume)
{
    BoundingBox bbox;
    ScratchSlots<13>();
    if(GetModelQuery()->GetBounds(pPart->mInstance, pPart->mGroup, &pPart->mTransform, pPart->mFlags, bbox.lower, bbox.upper))
    {
        const Vector3 extents = bbox.GetExtents();
        const float scale = pPart->mScale;
        *pVolume = scale * scale * scale * extents.x * extents.y * extents.z;
        return true;
    }
    return false;
}

struct Parts { Part* mpBegin; Part* mpEnd; unsigned size() const { return (unsigned)(mpEnd - mpBegin); } };
struct Creature { uint32_t pad[38]; Parts mParts; };   // mParts at +0x98

// @ 0x0056a5f0 sym=?GetPartVolumePercentages@@
void GetPartVolumePercentages(const Creature* pCreature, FloatVector* pPercentages)
{
    // local names chosen for the /Od slot order: t21 = part iterator, pEnd = parts end,
    // n21 = output iterator, t27 = output end, v8 = total weighted volume
    float v8 = 0.0f;
    pPercentages->resize(pCreature->mParts.size());
    ScratchSlots<20>();
    const Part* t21 = pCreature->mParts.mpBegin;
    const Part* const pEnd = pCreature->mParts.mpEnd;
    float* n21 = pPercentages->mpBegin;
    float* const t27 = pPercentages->mpEnd;
    for(; t21 != pEnd; ++t21, ++n21)
    {
        const Part* t14 = t21;
        float tmp;   // volume
        if(GetPartVolume(t14, &tmp))
        {
            v8 += tmp * t14->mScale;
            *n21 = tmp * t14->mScale;
        }
        else
            *n21 = 0.0f;
    }
    for(n21 = pPercentages->mpBegin; n21 != t27; ++n21)
        *n21 = *n21 * 100.0f / v8;
}
