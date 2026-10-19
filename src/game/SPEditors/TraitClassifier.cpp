// src/game/SPEditors/TraitClassifier.cpp -- migrated from slice(s) s0056fb90, s0056df80, s0056b680, s0056a7b0 by tools/migrate/rewrite.py
// Object file: SPEditors/TraitClassifier.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Traits/cFeatureVector.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t g_emptyWStr[];   // 0x01667bac

// ---- items of slice s0056a7b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void AllocateSelf(wchar_t* p, wchar_t* q);   // @ 0x00423820
};
extern wchar_t g_emptyWStr[];   // 0x01667bac
struct WStrHolder {
    uint32_t pad0;
    WStr str;
    WStrHolder* InitEmpty();   // @ 0x0056afc0
};
struct WStrSrc {
    float value;
    WStr str;
    WStrSrc* CopyInit(WStrSrc* src);   // @ 0x0056b020
};
// ---- items of slice s0056a7b0 end

// ---- items of slice s0056b680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPartCountWeight;     // 0x01473c70 (10.0f)
extern uint32_t gTextureGroup;           // 0x015e45a4
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Alloc { Alloc() {} };
struct PList {                       // cPropertyList (refcounted)
    virtual void AddRef();           // 0x00
    virtual void Release();          // 0x04
};
struct PListRefInline {
    PList* mpObject;
    PListRefInline() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PListRefInline() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer()
    {
        if (mpObject) {
            PList* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct PListRefCall {
    PList* mpObject;
    PListRefCall() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PListRefCall() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer();   // @ 0x0041d870
};
class cPropertyManager_s0056_b680 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PList** ppList);   // 0x2c
};
struct WStr_s0056_b680 {                         // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WStr_s0056_b680() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WStr_s0056_b680() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};
struct WStrSrc_s0056_b680 {                      // weight + description string (by-value arg of cFeatureVector::AddDescribed)
    float value;
    WStr_s0056_b680 str;
    WStrSrc_s0056_b680() { InitEmpty(); }
    WStrSrc_s0056_b680(WStrSrc_s0056_b680& src);            // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
};
struct Feature { uint32_t id; uint32_t value; };
struct cFeatureVector {
    float add(const Feature& f, float weight);          // @ 0x00571790
    float addDescribed(const Feature& f, WStrSrc_s0056_b680 d);    // @ 0x0056aec0
};
namespace SP {
    cPropertyManager_s0056_b680* PropertyManager();                                              // 0x0067de30
}
namespace SP {
    bool GetPropertyAsKey(PList* p, uint32_t id, uint32_t* out3);                     // 0x006a1250
}
namespace SP {
    bool GetPropertyAsString16(PList* p, uint32_t id, WStr_s0056_b680* out);                     // 0x006a1400
}
int WStr_Format(WStr_s0056_b680* s, const wchar_t* fmt, ...);                                    // 0x0041e050
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseSens);                // 0x00932f30
inline wchar_t* wfind(wchar_t* first, wchar_t* last, const char& value)
{
    while (first != last && *first != value)
        ++first;
    return first;
}
struct Block { char pad[0x1d8]; };
struct Creature {
    char pad[0x98];
    Block* mpBegin;       // +0x98
    Block* mpEnd;         // +0x9c
};
struct TextureBlock {     // element with +0xd4 key count, +0xf8 key array
    char pad[0xd4];
    uint32_t mnKeys;
    char pad2[0xf8 - 0xd8];
    uint32_t mKeys[1];
};
struct VSet {                            // eastl::vector_set<unsigned> (0x18 bytes)
    uint32_t mb, me, mc, ma, mx, my;
    VSet(const Alloc& = Alloc());        // @ 0x00540470
    VSet(const VSet& o);                 // @ 0x00564690
    ~VSet() { DoDestroyValues(); }
    void DoDestroyValues();              // @ 0x00553fb0
    struct InsRes { uint32_t* it; bool ok; InsRes() {} };
    InsRes insert(const uint32_t& v);    // @ 0x00554020
};
struct cEditorPartCount {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b680
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056b7d0
};
struct BlockKey { uint32_t k0, k1; BlockKey(uint32_t a, uint32_t b) { k0 = a; k1 = b; } };
struct BlockEntry {                      // hashtable value_type: pair<BlockKey, vector_set<uint>>
    BlockKey first;
    VSet second;
    BlockEntry(const BlockKey& k, const VSet& v) : first(k), second(v) {}
};
struct false_type {};
struct BlockInsRes { uint32_t* node; uint32_t bucket; bool ok; BlockInsRes() {} };
struct BlockHash {                       // eastl::hashtable<BlockKey, ...> at tag+8
    BlockInsRes DoInsertValue(const BlockEntry& v, false_type);   // @ 0x0056e320
};
struct BlockSet {                        // vector_set<uint>
    uint32_t* mb; uint32_t* me;
};
struct cRigBlockTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    BlockHash mTable;                                                               // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b9e0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056bd30
};
struct TexHash {                         // eastl::vector_map<uint, vector_set<uint>> at tag+8
    struct Entry { uint32_t first; VSet second; Entry(uint32_t k, const VSet& v) : first(k), second(v) {} };
    struct R { uint32_t* it; bool ok; R() { it = 0; ok = false; } };
    R insert(const Entry& e);            // @ 0x0056e4d0
};
struct cTextureTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    TexHash mTable;                                                                 // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056bfa0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056c2d0
};
// ---- items of slice s0056b680 end

// ---- items of slice s0056df80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int ptrdiff_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line); // 0xf473a0
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots_s0056_df80() { uint32_t s[N]; }
template<> inline void ScratchSlots_s0056_df80<0>() {}
template<class T> struct declined_copy_slots { enum { value = 0 }; };
namespace eastl {
  class allocator_s0056_df80 {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  class hash_allocator {
  public:
    hash_allocator() {}
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  struct true_type {};
}
namespace eastl {
  template<class T> struct less_s0056_df80 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
  template<class T> struct equal_to_s0056_df80 { bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
  template<class P> struct use_first_s0056_df80 { const typename P::first_type& operator()(const P& x) const { return x.first; } };
}
namespace eastl {
  template<class T1, class T2> struct pair_s0056_df80 {
    typedef T1 first_type; typedef T2 second_type;
    T1 first; T2 second;
    pair_s0056_df80(const T1& x, const T2& y) : first(x), second(y) {}
    template<class U, class V> pair_s0056_df80(const pair_s0056_df80<U, V>& p) : first(p.first), second(p.second) {}
  };
}
template<class T1, class T2> struct declined_copy_slots<eastl::pair_s0056_df80<T1, T2> > { enum { value = declined_copy_slots<T2>::value }; };
namespace eastl {
  template<class T, class A = allocator_s0056_df80> struct VectorBase_s0056_df80 {
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;
    VectorBase_s0056_df80() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0056_df80()
    {
        if(mpBegin)
            EASTLFree(mpBegin, (size_t)(mpCapacity - mpBegin) * sizeof(T));
    }
    void EASTLFree(T* p, size_t n) { mAllocator.deallocate(p, n); }
  };
}
namespace eastl {
  template<class T, class A = allocator_s0056_df80> class vector_s0056_df80 : public VectorBase_s0056_df80<T, A> {
  public:
    typedef VectorBase_s0056_df80<T, A> base_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type; typedef vector_s0056_df80<T, A> this_type;
    using base_type::mpBegin; using base_type::mpEnd; using base_type::mpCapacity; using base_type::mAllocator;
    vector_s0056_df80() {}
    vector_s0056_df80(const this_type& x);
    ~vector_s0056_df80();
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
}
namespace eastl {
  template<class T, class A> vector_s0056_df80<T,A>::~vector_s0056_df80()
  {
    ScratchSlots_s0056_df80<4>();
    DoDestroyValues(mpBegin, mpEnd);
  }
}
namespace eastl {
  template<class T, class A> typename vector_s0056_df80<T,A>::iterator vector_s0056_df80<T,A>::insert(iterator position, const value_type& value)
  {
    const ptrdiff_t n = position - mpBegin;
    if((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) value_type((ScratchSlots_s0056_df80<declined_copy_slots<T>::value>(), value));
    return mpBegin + n;
  }
}
namespace eastl {
  template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* result);   // 0x5702c0
}
namespace eastl {
  struct copy_backward_impl {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        while(last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
  };
}
namespace eastl {
  template<class BI1, class BI2> inline BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    return copy_backward_impl::do_copy(first, last, resultEnd);
  }
}
namespace eastl {
  template<class T, class A> void vector_s0056_df80<T,A>::DoInsertValue(iterator position, const value_type& value)
  {
    if(mpEnd != mpCapacity)
    {
        const T* pValue = &value;
        if((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) value_type(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        ScratchSlots_s0056_df80<1>();
        *position = *pValue;
        ++mpEnd;
    }
    else
    {
        const size_type nPrevSize = size_type(mpEnd - mpBegin);
        const size_type nNewSize  = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        pointer const   pNewData  = DoAllocate(nNewSize);
        pointer pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        ScratchSlots_s0056_df80<8>();
        ::new(pNewEnd) value_type(value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots_s0056_df80<12>();
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
  }
}
namespace eastl {
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
    ScratchSlots_s0056_df80<1>();
    return first;
  }
}
namespace eastl {
  template<class K, class C = less_s0056_df80<K>, class A = allocator_s0056_df80, class RAC = vector_s0056_df80<K, A> >
  class vector_set_s0056_df80 : public RAC {
  public:
    C mCompare;   // +0x14
    vector_set_s0056_df80(const vector_set_s0056_df80& x) : RAC(x) {}
    vector_set_s0056_df80& operator=(const vector_set_s0056_df80& x) { RAC::operator=(x); return *this; }
  };
}
namespace eastl {
  template<class Key, class T, class Compare = less_s0056_df80<Key>, class Allocator = allocator_s0056_df80,
           class RAC = vector_s0056_df80<pair_s0056_df80<Key, T>, Allocator> >
  class vector_map_s0056_df80 : public RAC {
  public:
    typedef RAC base_type; typedef Key key_type; typedef pair_s0056_df80<Key, T> value_type;
    typedef typename RAC::iterator iterator;
    class value_compare {
    public:
      Compare mCompare;
      bool operator()(const value_type& a, const value_type& b) const { return mCompare(a.first, b.first); }
      bool operator()(const value_type& a, const Key& b) const { return mCompare(a.first, b); }
      bool operator()(const Key& a, const value_type& b) const { return mCompare(a, b.first); }
    };
    value_compare mValueCompare;   // +0x14
    vector_map_s0056_df80() { ScratchSlots_s0056_df80<1>(); }
    using base_type::begin; using base_type::end;
    iterator lower_bound(const key_type& k) { return eastl::lower_bound(begin(), end(), k, mValueCompare); }
    pair_s0056_df80<iterator, bool> insert(const value_type& value);
    pair_s0056_df80<iterator, iterator> equal_range(const key_type& k);
  };
}
namespace eastl {
  template<class K, class T, class C, class A, class RAC>
  pair_s0056_df80<typename vector_map_s0056_df80<K,T,C,A,RAC>::iterator, bool> vector_map_s0056_df80<K,T,C,A,RAC>::insert(const value_type& value)
  {
    const iterator itLB(eastl::lower_bound(begin(), end(), value, mValueCompare));
    if((itLB != end()) && !mValueCompare(value, *itLB))
        return pair_s0056_df80<iterator, bool>(itLB, false);
    ScratchSlots_s0056_df80<5>();
    return pair_s0056_df80<iterator, bool>(base_type::insert(itLB, value), true);
  }
}
namespace eastl {
  template<class V> struct hash_node_s0056_df80 { V mValue; hash_node_s0056_df80* mpNext; };
}
namespace eastl {
  template<class V> struct hashtable_iterator_base {
    typedef hash_node_s0056_df80<V> node_type;
    node_type*  mpNode;
    node_type** mpBucket;
    hashtable_iterator_base(node_type* pNode, node_type** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
  };
}
namespace eastl {
  template<class V> struct hashtable_iterator : public hashtable_iterator_base<V> {
    typedef hashtable_iterator_base<V> base_type; typedef hash_node_s0056_df80<V> node_type;
    hashtable_iterator(node_type* pNode, node_type** pBucket) : base_type(pNode, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  };
}
namespace eastl {
  struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
}
namespace eastl {
  struct prime_rehash_policy_s0056_df80 {
    float            mfMaxLoadFactor;
    float            mfGrowthFactor;
    mutable uint32_t mnNextResize;
    pair_s0056_df80<bool, uint32_t> GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd) const; // 0x921440
  };
}
namespace eastl {
  template<class K, class V, class H> class hashtable_s0056_df80 {
  public:
    typedef hash_node_s0056_df80<V> node_type; typedef V value_type; typedef K key_type; typedef unsigned size_type;
    typedef hashtable_iterator<V> iterator; typedef uint32_t hash_code_t;
    // hash_code_base: empty function objects (+0x0..+0x3)
    use_first_s0056_df80<V>        mExtractKey;
    equal_to_s0056_df80<K>         mEqual;
    H                   mH1;
    mod_range_hashing   mH2;
    node_type**         mpBucketArray;    // +0x4
    size_type           mnBucketCount;    // +0x8
    size_type           mnElementCount;   // +0xc
    prime_rehash_policy_s0056_df80 mRehashPolicy;    // +0x10
    hash_allocator      mAllocator;       // +0x1c

    pair_s0056_df80<iterator, bool> DoInsertValue(const value_type& value, true_type);
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
}
namespace eastl {
  template<class K, class V, class H>
  pair_s0056_df80<typename hashtable_s0056_df80<K,V,H>::iterator, bool> hashtable_s0056_df80<K,V,H>::DoInsertValue(const value_type& value, true_type)
  {
    const key_type&   k     = mExtractKey(value);
    const hash_code_t c     = get_hash_code(k);
    size_type         n     = bucket_index(c, (uint32_t)mnBucketCount);
    node_type* const  pNode = DoFindNode(mpBucketArray[n], k, c);

    if(pNode == 0)
    {
        const pair_s0056_df80<bool, uint32_t> bRehash = mRehashPolicy.GetRehashRequired((uint32_t)mnBucketCount, (uint32_t)mnElementCount, (uint32_t)1);
        node_type* const pNodeNew = DoAllocateNode(value);

        if(bRehash.first)
        {
            n = bucket_index(c, (uint32_t)bRehash.second);
            DoRehash(bRehash.second);
        }

        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;

        return pair_s0056_df80<iterator, bool>(iterator(pNodeNew, mpBucketArray + n), true);
    }
    return pair_s0056_df80<iterator, bool>(iterator(pNode, mpBucketArray + n), false);
  }
}
namespace eastl {
  template<class K, class T, class H> class hash_map_s0056_df80 : public hashtable_s0056_df80<K, pair_s0056_df80<const K, T>, H> {
  public:
    explicit hash_map_s0056_df80(const hash_allocator& allocator_s0056_df80 = hash_allocator());  // 0x5640f0
  };
}
namespace EA {
  template<class T> class RefCountVTemplate_s0056_df80 {
  public:
    RefCountVTemplate_s0056_df80() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s0056_df80();
    virtual int AddRef();
    virtual int Release();
    virtual int RefCount();
    T mnRefCount;   // +0x4
  };
}
namespace SP {
namespace Traits {
  using namespace eastl;
}
}
namespace SP {
namespace Traits {
  typedef vector_s0056_df80<uint32_t> UIntVector;   // copy 0x56b020 (via vector_map<cID, UIntVector>)
}
}
namespace SP {
namespace Traits {
  class cIClassifier_s0056_df80 : public EA::RefCountVTemplate_s0056_df80<int> {
  public:
    cIClassifier_s0056_df80() {}
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1c() = 0;
  };
}
}
namespace SP {
namespace Traits {
  typedef vector_set_s0056_df80<uint32_t> TagSet;
}
}
template<> struct declined_copy_slots<SP::Traits::TagSet> { enum { value = 18 }; };      // 0x50d440
template<> struct declined_copy_slots<SP::Traits::UIntVector> { enum { value = 2 }; };   // 0x56b020
namespace SP {
namespace Traits {
  class cRigBlockTag_s0056_df80 : public cIClassifier_s0056_df80 {
  public:
    struct BlockKey {
        unsigned int mnGroup;      // +0x0
        unsigned int mnInstance;   // +0x4
        bool operator==(const BlockKey& x) const { return (mnGroup == x.mnGroup) && (mnInstance == x.mnInstance); }
    };
    struct BlockKeyHash { uint32_t operator()(const BlockKey& k) const { return k.mnGroup ^ k.mnInstance; } };
    typedef hash_map_s0056_df80<BlockKey, TagSet, BlockKeyHash> TagsMap;

    cRigBlockTag_s0056_df80() { ScratchSlots_s0056_df80<1>(); }
    virtual ~cRigBlockTag_s0056_df80();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();

    TagsMap mTagsMap;   // +0x8
  };
}
}
namespace SP {
namespace Traits {
  class cIClassifierFactory {
  public:
    virtual cIClassifier_s0056_df80* Create() = 0;
  };
}
}
namespace SP {
namespace Traits {
  template<class T> class tClassifierFactory : public cIClassifierFactory {
  public:
    virtual cIClassifier_s0056_df80* Create();
  };
}
}
namespace SP {
namespace Traits {
  template<class T> cIClassifier_s0056_df80* tClassifierFactory<T>::Create()
  {
    return new("OTDB", 0, 0, 0, 0) T;
  }
}
}
namespace SP {
namespace Traits {
  typedef vector_map_s0056_df80<uint32_t, cIClassifierFactory*> FactoryMap;
}
}
namespace SP {
namespace Traits {
  struct cNullClassifierSource {
    void* GetClassifier();
  };
}
}
typedef eastl::hashtable_s0056_df80<SP::Traits::cRigBlockTag_s0056_df80::BlockKey, eastl::pair_s0056_df80<const SP::Traits::cRigBlockTag_s0056_df80::BlockKey, SP::Traits::TagSet>, SP::Traits::cRigBlockTag_s0056_df80::BlockKeyHash> RigTagsTable;
template RigTagsTable::node_type* RigTagsTable::DoAllocateNode(const RigTagsTable::value_type&);
template void RigTagsTable::DoRehash(unsigned);
typedef eastl::vector_s0056_df80<eastl::pair_s0056_df80<uint32_t, SP::Traits::TagSet> > TexTagsVector;
template eastl::pair_s0056_df80<SP::Traits::FactoryMap::iterator, SP::Traits::FactoryMap::iterator> SP::Traits::FactoryMap::equal_range(const uint32_t&);
// ---- items of slice s0056df80 end



// ---- items of slice s0056fb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Pair8 { uint32_t a; uint32_t b; };
inline bool LessU32(uint32_t a, uint32_t b) { return a < b; }
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key);   // @ 0x005701b0
// ---- items of slice s0056fb90 end

// @ 0x0056afc0
WStrHolder* WStrHolder::InitEmpty()
{
    WStr* pStr = &str;
    int tmp;
    pStr->mpBegin = 0;
    pStr->mpEnd = 0;
    pStr->mpCapacity = 0;
    pStr->mpBegin = g_emptyWStr;
    pStr->mpEnd = pStr->mpBegin;
    pStr->mpCapacity = pStr->mpBegin + 1;
    return this;
}






// @ 0x0056b020
WStrSrc* WStrSrc::CopyInit(WStrSrc* src)
{
    value = src->value;
    WStr* d = &src->str;
    WStr* s = &str;
    s->mpBegin = 0;
    s->mpEnd = 0;
    s->mpCapacity = 0;
    s->AllocateSelf(d->mpBegin, d->mpEnd);
    return this;
}





// @ 0x0056b680
bool cEditorPartCount::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                uint32_t n37[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, n37)) {
                    Feature buf;
                    buf.id = 0x4eab460;
                    buf.value = n37[0];
                    fv->add(buf, kPartCountWeight);
                }
            }
        }
    }
    return p30;
}





// @ 0x0056b7d0
bool cEditorPartCount::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            ScratchSlots<1>();
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WStr_s0056_b680 n37;
                uint32_t buf[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, buf)) {
                    Feature owner;
                    owner.id = 0x4eab460;
                    owner.value = buf[0];
                    if (n37.empty())
                        WStr_Format(&n37, L"0x%08x", buf[0]);
                    WStrSrc_s0056_b680 n6;
                    ScratchSlots<1>();
                    WStr_Format(&n6.str, L"(%ls) %ls", GetName(), n37.c_str());
                    n6.value = kPartCountWeight;
                    ScratchSlots<25>();
                    fv->addDescribed(owner, n6);
                }
            }
        }
    }
    return p30;
}





// @ 0x0056b9e0
bool cRigBlockTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            uint32_t* e = (uint32_t*)it;
            BlockInsRes res;
            res.node = 0;
            res.bucket = 0;
            res.ok = false;
            {
                VSet tmp;
                BlockEntry ent(BlockKey(e[0], e[1]), tmp);
                res = mTable.DoInsertValue(ent, false_type());
            }
            BlockSet* set = (BlockSet*)((char*)res.node + 8);
            if (res.ok) {
                PListRefCall pl;
                bool ok = SP::PropertyManager()->GetPropertyList(e[1], e[0], pl.AsPointer());
                if (ok) {
                    WStr_s0056_b680 s;
                    if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                        VSet* vs = (VSet*)set;
                        wchar_t* cur = s.mpBegin;
                        wchar_t* tokEnd = cur;
                        wchar_t* end = s.mpEnd;
                        do {
                            tokEnd = wfind(cur, end, '|');
                            *tokEnd = 0;
                            if (tokEnd != cur) {
                                uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                vs->insert(h);
                                cur = tokEnd + 1;
                            }
                        } while (tokEnd != end && cur != end);
                    }
                }
            }
            uint32_t* p = set->mb;
            uint32_t* pe = set->me;
            for (; p != pe; p++) {
                Feature f;
                f.id = 0x4ebfebd;
                f.value = *p;
                fv->add(f, (*weights)[it - first]);
            }
        }
    }
    return result;
}





// @ 0x0056bd30
bool cRigBlockTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WStr_s0056_b680 n37;
                if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                    wchar_t* owner = n37.mpBegin;
                    wchar_t* buf = owner;
                    wchar_t* n6 = n37.mpEnd;
                    do {
                        buf = wfind(owner, n6, '|');
                        *buf = 0;
                        if (buf != owner) {
                            uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                            Feature nSize;
                            nSize.id = 0x4ebfebd;
                            nSize.value = n28;
                            WStrSrc_s0056_b680 val;
                            ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                            val.value = (*weights)[t32 - begin];
                            ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                            owner = buf + 1;
                        }
                    } while (buf != n6 && owner != n6);
                }
            }
        }
    }
    return p30;
}





// @ 0x0056bfa0
bool cTextureTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            TextureBlock* blk = (TextureBlock*)it;
            uint32_t n = blk->mnKeys;
            for (uint32_t i = 0; i < n; i++) {
                TexHash::R r;
                {
                    VSet tmp;
                    uint32_t key = blk->mKeys[i];
                    TexHash::Entry ent(key, tmp);
                    r = mTable.insert(ent);
                }
                VSet* set = (VSet*)((char*)r.it + 4);
                if (r.ok) {
                    PListRefCall pl;
                    bool ok = SP::PropertyManager()->GetPropertyList(blk->mKeys[i], gTextureGroup, pl.AsPointer());
                    if (ok) {
                        WStr_s0056_b680 s;
                        if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                            wchar_t* cur = s.mpBegin;
                            wchar_t* tokEnd = cur;
                            wchar_t* end = s.mpEnd;
                            do {
                                tokEnd = wfind(cur, end, '|');
                                *tokEnd = 0;
                                if (tokEnd != cur) {
                                    uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                    set->insert(h);
                                    cur = tokEnd + 1;
                                }
                            } while (tokEnd != end && cur != end);
                        }
                    }
                }
                BlockSet* bs = (BlockSet*)set;
                uint32_t* p = bs->mb;
                uint32_t* pe = bs->me;
                for (; p != pe; p++) {
                    Feature f;
                    f.id = 0x5833344;
                    f.value = *p;
                    fv->add(f, (*weights)[it - first]);
                }
            }
        }
    }
    return result;
}





// @ 0x0056c2d0
bool cTextureTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            TextureBlock* n31 = (TextureBlock*)t32;
            uint32_t p4 = n31->mnKeys;
            for (uint32_t v1 = 0; v1 < p4; v1++) {
                PListRefInline t25;
                bool p32 = SP::PropertyManager()->GetPropertyList(n31->mKeys[v1], gTextureGroup, t25.AsPointer());
                if (p32) {
                    WStr_s0056_b680 n37;
                    if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                        wchar_t* owner = n37.mpBegin;
                        wchar_t* buf = owner;
                        wchar_t* n6 = n37.mpEnd;
                        do {
                            buf = wfind(owner, n6, '|');
                            *buf = 0;
                            if (buf != owner) {
                                uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                                Feature nSize;
                                nSize.id = 0x5833344;
                                nSize.value = n28;
                                WStrSrc_s0056_b680 val;
                                ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                                val.value = (*weights)[t32 - begin];
                                ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                                owner = buf + 1;
                            }
                        } while (buf != n6 && owner != n6);
                    }
                }
            }
        }
    }
    return p30;
}




// @ 0x0056ee90
template SP::Traits::cIClassifier_s0056_df80* SP::Traits::tClassifierFactory<SP::Traits::cRigBlockTag_s0056_df80>::Create()
;

// @ 0x0056f2b0
namespace SP { namespace Traits {
void* cNullClassifierSource::GetClassifier()
{
    return 0;
  }
}}  // namespace SP::Traits

// @ 0x0056f3e0
namespace eastl {
template<class K, class T, class C, class A, class RAC> pair_s0056_df80<typename SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::iterator, typename SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::iterator> SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::equal_range(const key_type& k)
{
    const iterator itLower(lower_bound(k));
    if((itLower == end()) || mValueCompare(k, *itLower))
        return pair_s0056_df80<iterator, iterator>(itLower, itLower);
    iterator itUpper(itLower);
    return pair_s0056_df80<iterator, iterator>(itLower, ++itUpper);
  }
}  // namespace eastl

// @ 0x0056f4e0
namespace eastl {
template<class K, class V, class H> typename hashtable_s0056_df80<K,V,H>::node_type* hashtable_s0056_df80<K,V,H>::DoAllocateNode(const value_type& value)
{
    node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type), 4, 0);
    ::new(&pNode->mValue) value_type((ScratchSlots_s0056_df80<declined_copy_slots<V>::value>(), value));
    pNode->mpNext = 0;
    return pNode;
  }
}  // namespace eastl

// @ 0x0056f560
namespace eastl {
template<class K, class V, class H> void hashtable_s0056_df80<K,V,H>::DoRehash(size_type nNewBucketCount)
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
}  // namespace eastl

// @ 0x0056f6d0
template TexTagsVector::iterator TexTagsVector::insert(TexTagsVector::iterator, const TexTagsVector::value_type&)
;

// @ 0x0056f830
template void TexTagsVector::DoInsertValue(TexTagsVector::iterator, const TexTagsVector::value_type&)
;

// @ 0x005701b0
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key)
{
    int n = (int)(last - first);
    ScratchSlots<1>();
    while (n > 0) {
        Pair8* it = first;
        int half = n >> 1;
        it = it + half;
        if (LessU32(it->a, key->a)) {
            it = it + 1;
            first = it;
            n = n - (half + 1);
        }
        else {
            n = half;
        }
    }
    return first;
}
