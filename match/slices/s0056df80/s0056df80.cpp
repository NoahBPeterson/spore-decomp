// Slice s0056df80: SP::Traits classifier registry, the cRigBlockTag / cTextureTag classifier factories,
// and the EASTL containers behind them: cRigBlockTag's hash_map<BlockKey, vector_set<uint32_t>>,
// cTextureTag's vector_map<uint32_t, vector_set<uint32_t>>, the classifier-factory vector_map and
// a vector_map keyed by an 8-byte id with an out-of-line operator<.
// Module is /Od /Ob1 /arch:SSE /fp:fast (no /EHsc). ScratchSlots<N> reproduces stack slots left
// behind by inlined EASTL helpers whose locals were optimized out of the source here.
typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef int ptrdiff_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line); // 0xf473a0
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template<> inline void ScratchSlots<0>() {}
// Stack slots a function reserves once for a declined inline copy constructor of T
// (e.g. the vector copy constructors 0x50d440 / 0x56b020, which are called out of line).
template<class T> struct declined_copy_slots { enum { value = 0 }; };

namespace eastl {
  class allocator {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
  // The hash_map's allocator carries no state in this build (1 byte, padded).
  class hash_allocator {
  public:
    hash_allocator() {}
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };

  struct true_type {};
  template<class T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
  template<class T> struct equal_to { bool operator()(const T& a, const T& b) const { return a == b; } };
  template<class P> struct use_first { const typename P::first_type& operator()(const P& x) const { return x.first; } };
  template<class T1, class T2> struct pair {
    typedef T1 first_type; typedef T2 second_type;
    T1 first; T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
    template<class U, class V> pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
  };
}
template<class T1, class T2> struct declined_copy_slots<eastl::pair<T1, T2> > { enum { value = declined_copy_slots<T2>::value }; };
namespace eastl {

  // ------------------------------------------------------------------ basic_string
  template<class T, class A> class basic_string {
  public:
    T* mpBegin; T* mpEnd; T* mpCapacity;
    struct { const char* mpName; } mAllocator;
    basic_string(const basic_string& x);
    void RangeInitialize(const T* pBegin, const T* pEnd);              // 0x423820
  };
  template<class T, class A> basic_string<T,A>::basic_string(const basic_string& x)
    : mpBegin(0), mpEnd(0), mpCapacity(0)
  {
    RangeInitialize(x.mpBegin, x.mpEnd);
  }

  // ------------------------------------------------------------------ vector
  template<class T, class A = allocator> struct VectorBase {
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase()
    {
        if(mpBegin)
            EASTLFree(mpBegin, (size_t)(mpCapacity - mpBegin) * sizeof(T));
    }
    void EASTLFree(T* p, size_t n) { mAllocator.deallocate(p, n); }
  };
  template<class T, class A = allocator> class vector : public VectorBase<T, A> {
  public:
    typedef VectorBase<T, A> base_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type; typedef vector<T, A> this_type;
    using base_type::mpBegin; using base_type::mpEnd; using base_type::mpCapacity; using base_type::mAllocator;
    vector() {}
    vector(const this_type& x);
    ~vector();
    this_type& operator=(const this_type& x);
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    iterator insert(iterator position, const value_type& value);
    void DoInsertValue(iterator position, const value_type& value);
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
    pointer DoAllocate(size_type n) { return n ? (pointer)mAllocator.allocate(n * sizeof(T), 4, 0) : 0; }
    void DoFree(pointer p, size_type n)
    {
        if(p)
            mAllocator.deallocate(p, n);
    }
  };

  template<class T, class A> vector<T,A>::~vector()
  {
    ScratchSlots<4>();
    DoDestroyValues(mpBegin, mpEnd);
  }

  template<class T, class A> typename vector<T,A>::iterator vector<T,A>::insert(iterator position, const value_type& value)
  {
    const ptrdiff_t n = position - mpBegin;
    if((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) value_type((ScratchSlots<declined_copy_slots<T>::value>(), value));
    return mpBegin + n;
  }

  template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* result);   // 0x5702c0

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
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    return copy_backward_impl::do_copy(first, last, resultEnd);
  }

  template<class T, class A> void vector<T,A>::DoInsertValue(iterator position, const value_type& value)
  {
    if(mpEnd != mpCapacity)
    {
        const T* pValue = &value;
        if((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) value_type(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        ScratchSlots<1>();
        *position = *pValue;
        ++mpEnd;
    }
    else
    {
        const size_type nPrevSize = size_type(mpEnd - mpBegin);
        const size_type nNewSize  = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        pointer const   pNewData  = DoAllocate(nNewSize);
        pointer pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        ScratchSlots<8>();
        ::new(pNewEnd) value_type(value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots<12>();
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
  }

  // ------------------------------------------------------------------ lower_bound
  template<class FI, class T, class Compare>
  FI lower_bound(FI first, FI last, const T& value, Compare compare)
  {
    int d = (int)(last - first);
    while(d > 0)
    {
        FI  i  = first;
        int d2 = d >> 1;
        i += d2;
        if(compare(*i, value))
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

  // ------------------------------------------------------------------ vector_set / vector_map
  template<class K, class C = less<K>, class A = allocator, class RAC = vector<K, A> >
  class vector_set : public RAC {
  public:
    C mCompare;   // +0x14
    vector_set(const vector_set& x) : RAC(x) {}
    vector_set& operator=(const vector_set& x) { RAC::operator=(x); return *this; }
  };

  template<class Key, class T, class Compare = less<Key>, class Allocator = allocator,
           class RAC = vector<pair<Key, T>, Allocator> >
  class vector_map : public RAC {
  public:
    typedef RAC base_type; typedef Key key_type; typedef pair<Key, T> value_type;
    typedef typename RAC::iterator iterator;
    class value_compare {
    public:
      Compare mCompare;
      bool operator()(const value_type& a, const value_type& b) const { return mCompare(a.first, b.first); }
      bool operator()(const value_type& a, const Key& b) const { return mCompare(a.first, b); }
      bool operator()(const Key& a, const value_type& b) const { return mCompare(a, b.first); }
    };
    value_compare mValueCompare;   // +0x14
    vector_map() { ScratchSlots<1>(); }
    using base_type::begin; using base_type::end;
    iterator lower_bound(const key_type& k) { return eastl::lower_bound(begin(), end(), k, mValueCompare); }
    pair<iterator, bool> insert(const value_type& value);
    pair<iterator, iterator> equal_range(const key_type& k);
  };

  template<class K, class T, class C, class A, class RAC>
  pair<typename vector_map<K,T,C,A,RAC>::iterator, bool> vector_map<K,T,C,A,RAC>::insert(const value_type& value)
  {
    const iterator itLB(eastl::lower_bound(begin(), end(), value, mValueCompare));
    if((itLB != end()) && !mValueCompare(value, *itLB))
        return pair<iterator, bool>(itLB, false);
    ScratchSlots<5>();
    return pair<iterator, bool>(base_type::insert(itLB, value), true);
  }

  template<class K, class T, class C, class A, class RAC>
  pair<typename vector_map<K,T,C,A,RAC>::iterator, typename vector_map<K,T,C,A,RAC>::iterator>
  vector_map<K,T,C,A,RAC>::equal_range(const key_type& k)
  {
    const iterator itLower(lower_bound(k));
    if((itLower == end()) || mValueCompare(k, *itLower))
        return pair<iterator, iterator>(itLower, itLower);
    iterator itUpper(itLower);
    return pair<iterator, iterator>(itLower, ++itUpper);
  }

  // ------------------------------------------------------------------ hashtable (unique keys)
  template<class V> struct hash_node { V mValue; hash_node* mpNext; };
  template<class V> struct hashtable_iterator_base {
    typedef hash_node<V> node_type;
    node_type*  mpNode;
    node_type** mpBucket;
    hashtable_iterator_base(node_type* pNode, node_type** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
  };
  template<class V> struct hashtable_iterator : public hashtable_iterator_base<V> {
    typedef hashtable_iterator_base<V> base_type; typedef hash_node<V> node_type;
    hashtable_iterator(node_type* pNode, node_type** pBucket) : base_type(pNode, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  };
  struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
  struct prime_rehash_policy {
    float            mfMaxLoadFactor;
    float            mfGrowthFactor;
    mutable uint32_t mnNextResize;
    pair<bool, uint32_t> GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd) const; // 0x921440
  };

  template<class K, class V, class H> class hashtable {
  public:
    typedef hash_node<V> node_type; typedef V value_type; typedef K key_type; typedef unsigned size_type;
    typedef hashtable_iterator<V> iterator; typedef uint32_t hash_code_t;
    // hash_code_base: empty function objects (+0x0..+0x3)
    use_first<V>        mExtractKey;
    equal_to<K>         mEqual;
    H                   mH1;
    mod_range_hashing   mH2;
    node_type**         mpBucketArray;    // +0x4
    size_type           mnBucketCount;    // +0x8
    size_type           mnElementCount;   // +0xc
    prime_rehash_policy mRehashPolicy;    // +0x10
    hash_allocator      mAllocator;       // +0x1c

    pair<iterator, bool> DoInsertValue(const value_type& value, true_type);
    node_type* DoAllocateNode(const value_type& value);
    node_type** DoAllocateBuckets(size_type n);                              // 0x567260
    void DoFreeBuckets(node_type** pBucketArray, size_type n)
    {
        if(n > 1)
            mAllocator.deallocate(pBucketArray, n);
    }
    void DoRehash(size_type nNewBucketCount);
    hash_code_t get_hash_code(const key_type& key) const { return (hash_code_t)mH1(key); }
    size_type bucket_index(hash_code_t c, uint32_t nBucketCount) const { return (size_type)mH2(c, nBucketCount); }
    size_type bucket_index(const node_type* pNode, uint32_t nBucketCount) const
    {
        const hash_code_t c = (hash_code_t)mH1(mExtractKey(pNode->mValue));
        return (size_type)mH2(c, nBucketCount);
    }
    node_type* DoFindNode(node_type* pNode, const key_type& k, hash_code_t c) const
    {
        for(; pNode; pNode = pNode->mpNext)
        {
            if(mEqual(k, mExtractKey(pNode->mValue)))
                return pNode;
        }
        return 0;
    }
  };

  template<class K, class V, class H>
  pair<typename hashtable<K,V,H>::iterator, bool> hashtable<K,V,H>::DoInsertValue(const value_type& value, true_type)
  {
    const key_type&   k     = mExtractKey(value);
    const hash_code_t c     = get_hash_code(k);
    size_type         n     = bucket_index(c, (uint32_t)mnBucketCount);
    node_type* const  pNode = DoFindNode(mpBucketArray[n], k, c);

    if(pNode == 0)
    {
        const pair<bool, uint32_t> bRehash = mRehashPolicy.GetRehashRequired((uint32_t)mnBucketCount, (uint32_t)mnElementCount, (uint32_t)1);
        node_type* const pNodeNew = DoAllocateNode(value);

        if(bRehash.first)
        {
            n = bucket_index(c, (uint32_t)bRehash.second);
            DoRehash(bRehash.second);
        }

        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;

        return pair<iterator, bool>(iterator(pNodeNew, mpBucketArray + n), true);
    }
    return pair<iterator, bool>(iterator(pNode, mpBucketArray + n), false);
  }

  template<class K, class V, class H>
  typename hashtable<K,V,H>::node_type* hashtable<K,V,H>::DoAllocateNode(const value_type& value)
  {
    node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type), 4, 0);
    ::new(&pNode->mValue) value_type((ScratchSlots<declined_copy_slots<V>::value>(), value));
    pNode->mpNext = 0;
    return pNode;
  }

  template<class K, class V, class H>
  void hashtable<K,V,H>::DoRehash(size_type nNewBucketCount)
  {
    node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    node_type* pNode;
    for(size_type i = 0; i < mnBucketCount; ++i)
    {
        while((pNode = mpBucketArray[i]) != 0)
        {
            const size_type nNewBucketIndex = bucket_index(pNode, (uint32_t)nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext    = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }

    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
  }

  template<class K, class T, class H> class hash_map : public hashtable<K, pair<const K, T>, H> {
  public:
    explicit hash_map(const hash_allocator& allocator = hash_allocator());  // 0x5640f0
  };
}

// ---------------------------------------------------------------------- SP::Traits
namespace EA {
  template<class T> class RefCountVTemplate {
  public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate();
    virtual int AddRef();
    virtual int Release();
    virtual int RefCount();
    T mnRefCount;   // +0x4
  };
}

namespace SP { namespace Traits {
  using namespace eastl;

  struct cID { unsigned int mnTraitClass; unsigned int mnTraitType; bool operator<(const cID& x) const; }; // 0x5715d0
  typedef vector<uint32_t> UIntVector;   // copy 0x56b020 (via vector_map<cID, UIntVector>)

  class cIClassifier : public EA::RefCountVTemplate<int> {
  public:
    cIClassifier() {}
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1c() = 0;
  };

  typedef vector_set<uint32_t> TagSet;
}}
template<> struct declined_copy_slots<SP::Traits::TagSet> { enum { value = 18 }; };      // 0x50d440
template<> struct declined_copy_slots<SP::Traits::UIntVector> { enum { value = 2 }; };   // 0x56b020
namespace SP { namespace Traits {

  class cRigBlockTag : public cIClassifier {
  public:
    struct BlockKey {
        unsigned int mnGroup;      // +0x0
        unsigned int mnInstance;   // +0x4
        bool operator==(const BlockKey& x) const { return (mnGroup == x.mnGroup) && (mnInstance == x.mnInstance); }
    };
    struct BlockKeyHash { uint32_t operator()(const BlockKey& k) const { return k.mnGroup ^ k.mnInstance; } };
    typedef hash_map<BlockKey, TagSet, BlockKeyHash> TagsMap;

    cRigBlockTag() { ScratchSlots<1>(); }
    virtual ~cRigBlockTag();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();

    TagsMap mTagsMap;   // +0x8
  };

  class cTextureTag : public cIClassifier {
  public:
    typedef vector_map<uint32_t, TagSet> TagsMap;
    cTextureTag() {}
    virtual ~cTextureTag();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();

    TagsMap mTagsMap;   // +0x8
  };

  class cIClassifierFactory {
  public:
    virtual cIClassifier* Create() = 0;
  };
  template<class T> class tClassifierFactory : public cIClassifierFactory {
  public:
    virtual cIClassifier* Create();
  };
  template<class T> cIClassifier* tClassifierFactory<T>::Create()
  {
    return new("OTDB", 0, 0, 0, 0) T;
  }

  typedef vector_map<uint32_t, cIClassifierFactory*> FactoryMap;
  // Factories of classifiers that are not identified yet (ids are their classifier hashes).
  class cClassifierFactory_0227f195 : public cIClassifierFactory {};
  class cClassifierFactory_01f71e85 : public cIClassifierFactory {};
  class cClassifierFactory_04ea801f : public cIClassifierFactory {};
  class cClassifierFactory_04eab460 : public cIClassifierFactory {};
  class cClassifierFactory_0518af1d : public cIClassifierFactory {};
  class cClassifierFactory_068375d7 : public cIClassifierFactory {};
  class cClassifierFactory_0518b883 : public cIClassifierFactory {};
  class cClassifierFactory_052b27b5 : public cIClassifierFactory {};
  class cClassifierFactory_052c812a : public cIClassifierFactory {};
  class cClassifierFactory_052c8ca5 : public cIClassifierFactory {};

  // Each returns pair(classifier id, new <factory>).
  pair<uint32_t, cClassifierFactory_0227f195*> MakeFactory_0227f195();   // 0x56e630
  pair<uint32_t, cClassifierFactory_01f71e85*> MakeFactory_01f71e85();   // 0x56e6b0
  pair<uint32_t, cClassifierFactory_04ea801f*> MakeFactory_04ea801f();   // 0x56e730
  pair<uint32_t, cClassifierFactory_04eab460*> MakeFactory_04eab460();   // 0x56e7b0
  pair<uint32_t, tClassifierFactory<cRigBlockTag>*> MakeFactory_04ebfebd();   // 0x56e830
  pair<uint32_t, tClassifierFactory<cTextureTag>*> MakeFactory_05833344();   // 0x56e8b0
  pair<uint32_t, cClassifierFactory_0518af1d*> MakeFactory_0518af1d();   // 0x56e930
  pair<uint32_t, cClassifierFactory_068375d7*> MakeFactory_068375d7();   // 0x56e9b0
  pair<uint32_t, cClassifierFactory_0518b883*> MakeFactory_0518b883();   // 0x56ea30
  pair<uint32_t, cClassifierFactory_052b27b5*> MakeFactory_052b27b5();   // 0x56eab0
  pair<uint32_t, cClassifierFactory_052c812a*> MakeFactory_052c812a();   // 0x56eb30
  pair<uint32_t, cClassifierFactory_052c8ca5*> MakeFactory_052c8ca5();   // 0x56ebb0

  struct cClassifierRegistry {
    FactoryMap mFactories;   // +0x0
    bool RegisterFactories();
  };

  // @ 0x0056df80 sym=?RegisterFactories@cClassifierRegistry@
  bool cClassifierRegistry::RegisterFactories()
  {
    mFactories.insert(MakeFactory_0227f195());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_01f71e85());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_04ea801f());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_04eab460());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_04ebfebd());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_05833344());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_0518af1d());
    ScratchSlots<4>();
    mFactories.insert(MakeFactory_068375d7());
    mFactories.insert(MakeFactory_0518b883());
    mFactories.insert(MakeFactory_052b27b5());
    mFactories.insert(MakeFactory_052c812a());
    mFactories.insert(MakeFactory_052c8ca5());
    return true;
  }

  struct cNullClassifierSource {
    void* GetClassifier();
  };
  // @ 0x0056f2b0 sym=?GetClassifier@cNullClassifierSource@
  void* cNullClassifierSource::GetClassifier()
  {
    return 0;
  }

  typedef vector_map<cID, UIntVector> IDVectorMap;
}}
using namespace eastl;
using namespace SP::Traits;

// @ 0x0056e2d0 sym=??0?$basic_string@_W
template basic_string<wchar_t, allocator>::basic_string(const basic_string<wchar_t, allocator>&);

typedef cRigBlockTag::TagsMap RigTagsMap;
typedef hashtable<cRigBlockTag::BlockKey, pair<const cRigBlockTag::BlockKey, TagSet>, cRigBlockTag::BlockKeyHash> RigTagsTable;
// @ 0x0056e320 sym=?DoInsertValue@?$hashtable
template pair<RigTagsTable::iterator, bool> RigTagsTable::DoInsertValue(const RigTagsTable::value_type&, true_type);
// @ 0x0056f4e0 sym=?DoAllocateNode@?$hashtable
template RigTagsTable::node_type* RigTagsTable::DoAllocateNode(const RigTagsTable::value_type&);
// @ 0x0056f560 sym=?DoRehash@?$hashtable
template void RigTagsTable::DoRehash(unsigned);

typedef cTextureTag::TagsMap TexTagsMap;
// @ 0x0056e4d0 sym=?insert@?$vector_map@IV?$vector_set
template pair<TexTagsMap::iterator, bool> TexTagsMap::insert(const TexTagsMap::value_type&);
// @ 0x0056fb10 sym=??$lower_bound@PAU?$pair@IV?$vector_set
template TexTagsMap::iterator eastl::lower_bound(TexTagsMap::iterator, TexTagsMap::iterator, const TexTagsMap::value_type&, TexTagsMap::value_compare);
typedef vector<pair<uint32_t, TagSet> > TexTagsVector;
// @ 0x0056f640 sym=??1?$vector@U?$pair@IV?$vector_set
template TexTagsVector::~vector();
// @ 0x0056f6d0 sym=?insert@?$vector@U?$pair@IV?$vector_set
template TexTagsVector::iterator TexTagsVector::insert(TexTagsVector::iterator, const TexTagsVector::value_type&);
// @ 0x0056f830 sym=?DoInsertValue@?$vector@U?$pair@IV?$vector_set
template void TexTagsVector::DoInsertValue(TexTagsVector::iterator, const TexTagsVector::value_type&);

// @ 0x0056e580 sym=?insert@?$vector_map@UcID
template pair<IDVectorMap::iterator, bool> IDVectorMap::insert(const IDVectorMap::value_type&);
typedef vector<pair<cID, UIntVector> > IDVectorVector;
// @ 0x0056f780 sym=?insert@?$vector@U?$pair@UcID
template IDVectorVector::iterator IDVectorVector::insert(IDVectorVector::iterator, const IDVectorVector::value_type&);

// @ 0x0056f3e0 sym=?equal_range@?$vector_map@IPAVcIClassifierFactory
template pair<FactoryMap::iterator, FactoryMap::iterator> FactoryMap::equal_range(const uint32_t&);

// @ 0x0056ee90 sym=?Create@?$tClassifierFactory@VcRigBlockTag
template cIClassifier* tClassifierFactory<cRigBlockTag>::Create();
// @ 0x0056ef30 sym=?Create@?$tClassifierFactory@VcTextureTag
template cIClassifier* tClassifierFactory<cTextureTag>::Create();
