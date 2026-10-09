// Shared stub types for slices s0055ce80..s00567a90 (SP::cSPObjectTemplateDB module).
// EASTL / class declarations harvested from the validated neighbouring slices and extended.
#pragma once
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// Local-frame size of the (declined-inline) erase(first, last) instance, which /Od callers reserve.
template<typename T> struct EraseFrame { enum { kSlots = 6 }; };
template<> struct EraseFrame<uint32_t> { enum { kSlots = 4 }; };
template<> struct EraseFrame<int> { enum { kSlots = 4 }; };
template<> struct EraseFrame<float> { enum { kSlots = 4 }; };
namespace eastl { template<typename T1, typename T2> struct pair; }
template<> struct EraseFrame<eastl::pair<uint32_t, float> > { enum { kSlots = 4 }; };

namespace eastl {

struct allocator { allocator() {} };
struct sp_vector_allocator;
void EASTL_allocator_deallocate(void* p); // 0x00f47380
inline void EASTLFree(void* p) { EASTL_allocator_deallocate(p); }
struct sp_vector_allocator : public allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const allocator& a);
    void deallocate(void* p, size_t n) { void* pMem = p; EASTLFree(pMem); }
    const char* mpName;
    uint32_t mFlags;
};

template<typename T> struct less {
    less() {}
    bool operator()(const T& a, const T& b) const { return a < b; }
};
struct random_access_iterator_tag { random_access_iterator_tag() {} };
struct false_type { false_type() {} };

template<typename Container>
struct insert_iterator {
    Container* container;
    typename Container::iterator it;
    insert_iterator(Container& x, typename Container::iterator i) : container(&x), it(i) {}
    insert_iterator& operator=(const typename Container::value_type& value) {
        it = container->insert(it, value);
        ++it;
        return *this;
    }
    insert_iterator& operator*() { return *this; }
    insert_iterator& operator++(int) { return *this; }
};
// Output iterator that inserts the key (first) of each pair it is assigned.
template<typename Container>
struct key_insert_iterator {
    Container* container;
    typename Container::iterator it;
    key_insert_iterator(Container& x, typename Container::iterator i) : container(&x), it(i) {}
    template<typename Pair>
    key_insert_iterator& operator=(const Pair& value) {
        it = container->insert(it, value.first);
        ++it;
        return *this;
    }
    key_insert_iterator& operator*() { return *this; }
    key_insert_iterator& operator++(int) { return *this; }
};
template<typename Container>
inline key_insert_iterator<Container> key_inserter(Container& x, typename Container::iterator i) {
    return key_insert_iterator<Container>(x, i);
}
template<typename Container>
inline insert_iterator<Container> inserter(Container& x, typename Container::iterator i) {
    return insert_iterator<Container>(x, i);
}
template<typename I1, typename I2, typename O>
O set_intersection(I1 first1, I1 last1, I2 first2, I2 last2, O result);
template<typename I1, typename I2, typename O>
O set_difference(I1 first1, I1 last1, I2 first2, I2 last2, O result);
template<typename I, typename T>
inline I find(I first, I last, const T& value) {
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

template<typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
    pair() {}
    pair(const T1& x, const T2& y) : first(x), second(y) {}
    template<typename U, typename W>
    pair(const pair<U, W>& p) : first(p.first), second(p.second) {}
};
template<typename T1, typename T2>
inline pair<T1, T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }

template<typename T, typename A = allocator>
class vector {
public:
    typedef T* iterator;
    typedef T value_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() { ScratchSlots<1>(); }
    vector(const vector& x);
    ~vector();
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_t size() const { return mpEnd - mpBegin; }
    T& operator[](size_t n) { return *(mpBegin + n); }
    const T& operator[](size_t n) const { return *(mpBegin + n); }
    iterator erase(iterator first, iterator last);
    iterator erase(iterator position);
    void clear() { ScratchSlots<EraseFrame<T>::kSlots>(); erase(mpBegin, mpEnd); }
    void clear_noframe() { erase(mpBegin, mpEnd); }
    bool empty() const;
    void swap(vector& x);
    template<typename It> void DoAssignFromIterator(It first, It last, random_access_iterator_tag);
    template<typename It> void assign(It first, It last) {
        false_type bIsIntegral;
        false_type bIsPOD;
        DoAssignFromIterator(first, last, random_access_iterator_tag());
    }
    void reserve(size_t n);
    void push_back(const T& value);
    iterator insert(iterator position, const T& value);
    void DoInsertValues(iterator position, size_t n, const T& value);
    void insert(iterator position, size_t n, const T& value) { DoInsertValues(position, n, value); }
    void resize(size_t n);
};

template<typename T, typename A>
vector<T, A>::~vector() {
    for (T* p = mpBegin; p < mpEnd; ++p)
        p->~T();
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
}

template<typename In, typename Out>
inline Out copy_impl3(In first, In last, Out result) {
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
template<typename In, typename Out>
inline Out copy_n3(In first, In last, Out result) {
    const bool isPOD = false;
    const bool isScalar = false;
    const bool isTrivial = false;
    return copy_impl3(first, last, result);
}

template<typename T, typename A>
typename vector<T, A>::iterator vector<T, A>::erase(iterator position) {
    if ((position + 1) < mpEnd)
        copy_n3(position + 1, mpEnd, position);
    --mpEnd;
    mpEnd->~T();
    return position;
}

template<typename T, typename A>
void vector<T, A>::resize(size_t n) {
    if (n > (size_t)(mpEnd - mpBegin))
        insert(mpEnd, n - (size_t)(mpEnd - mpBegin), value_type());
    else
        erase(mpBegin + n, mpEnd);
    ScratchSlots<6>();
}

template<typename K, typename C = less<K>, typename A = sp_vector_allocator>
class vector_set : public vector<K, A> {
public:
    typedef vector<K, A> base_type;
    typedef K* iterator;
    C mCompare;
    vector_set(const vector_set& x);
    ~vector_set();
    pair<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
};

template<typename K, typename V, typename C = less<K>, typename A = sp_vector_allocator>
class vector_map : public vector<pair<K, V>, A> {
public:
    typedef vector<pair<K, V>, A> base_type;
    typedef pair<K, V> value_type;
    typedef pair<K, V>* iterator;
    C mCompare;
    pair<iterator, iterator> equal_range(const K& k);
    iterator find(const K& k) {
        const pair<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<5>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    // Same as find(); this instance reserves a smaller declined-inline frame.
    iterator find_(const K& k) {
        const pair<iterator, iterator> pairIts(equal_range(k));
        ScratchSlots<3>();
        if (pairIts.first != pairIts.second)
            return pairIts.first;
        return base_type::end();
    }
    V& operator[](const K& k);
};

template<typename I, typename T, typename C>
I lower_bound(I first, I last, const T& value, C compare);

template<typename K, typename V, typename C, typename A>
V& vector_map<K, V, C, A>::operator[](const K& k) {
    iterator pos;   // unused in the original as well (it occupies a frame slot)
    iterator itLB = lower_bound(base_type::begin(), base_type::end(), k, mCompare);
    if ((itLB == base_type::end()) || mCompare(k, (*itLB).first)) {
        itLB = base_type::insert(itLB, value_type(k, V()));
    }
    return (*itLB).second;
}

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};

template<typename V>
struct rbtree_const_iterator;
template<typename V>
struct rbtree_iterator {
    rbtree_node_base* mpNode;
    rbtree_iterator(const rbtree_node_base* pNode);
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    V& operator*() const;
    rbtree_iterator& operator++();
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};

template<typename K, typename V, typename C = less<K>, typename A = allocator>
class map {
public:
    typedef pair<const K, V> value_type;
    typedef rbtree_iterator<value_type> iterator;
    C mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    A mAllocator;
    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    iterator end() { return iterator(&mAnchor); }
    size_t size() const { return mnSize; }
    iterator find(const K& k);
    pair<iterator, iterator> equal_range(const K& k);

    struct const_iterator {
        rbtree_node_base* mpNode;
        const_iterator(const iterator& x);
        const value_type& operator*() const;
        const_iterator& operator++();
        bool operator!=(const const_iterator& x) const { return mpNode != x.mpNode; }
    };

    struct key_iterator {
        rbtree_node_base* mpNode;
        key_iterator(const rbtree_node_base* pNode);
        const K& operator*() const;
        key_iterator& operator++();
        bool operator!=(const key_iterator& x) const { return mpNode != x.mpNode; }
    };
    key_iterator key_begin() { return key_iterator(mAnchor.mpNodeLeft); }
    key_iterator key_end() { return key_iterator(&mAnchor); }
};

template<typename Container>
struct insert_iterator2;

struct input_iterator_tag {};
template<typename In, typename Out>
inline Out copy(In first, In last, Out result, input_iterator_tag) {
    for (; first != last; ++first) {
        *result++ = *first;
        ScratchSlots<3>();
    }
    return result;
}

}

namespace eastl {
template<typename T> struct hash {};
struct mod_range_hashing {};
struct default_ranged_hash {};
template<typename T> struct equal_to { equal_to() {} };
template<typename P> struct use_first {};
struct true_type {};
struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};

template<typename V>
struct hash_node {
    V mValue;
    hash_node* mpNext;
};

template<typename V>
struct hashtable_iterator_base {
    hash_node<V>* mpNode;
    hash_node<V>** mpBucket;
    hashtable_iterator_base(hash_node<V>* pNode, hash_node<V>** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket();
};

template<typename V>
struct hashtable_iterator : public hashtable_iterator_base<V> {
    typedef hashtable_iterator_base<V> base_type;
    hashtable_iterator(hash_node<V>** pBucket) : base_type(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
    V* operator->() const { return &base_type::mpNode->mValue; }
    hashtable_iterator& operator++() {
        base_type::mpNode = base_type::mpNode->mpNext;
        while (!base_type::mpNode)
            base_type::mpNode = *++base_type::mpBucket;
        return *this;
    }
    bool operator!=(const hashtable_iterator& x) const { return base_type::mpNode != x.mpNode; }
};

template<typename K, typename V, typename A, typename ExtractKey, typename Equal, typename H1, typename H2, typename H>
class hashtable {
public:
    typedef V value_type;
    typedef hashtable_iterator<V> iterator;
    typedef hash_node<V> node_type;
    typedef A allocator_type;

    uint32_t mFunctorPad;   // empty hash/compare functor bases
    node_type** mpBucketArray;
    size_t mnBucketCount;
    size_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    A mAllocator;

    hashtable(size_t nBucketCount, const H1& h1, const H2& h2, const H& h, const Equal& eq, const ExtractKey& ek, const A& a);
    ~hashtable();
    iterator begin();
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    pair<iterator, bool> DoInsertValue(const value_type& value, true_type);
    pair<iterator, bool> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
};

template<typename K, typename V, typename A, typename ExtractKey, typename Equal, typename H1, typename H2, typename H>
typename hashtable<K, V, A, ExtractKey, Equal, H1, H2, H>::iterator hashtable<K, V, A, ExtractKey, Equal, H1, H2, H>::begin() {
    iterator i(mpBucketArray);
    if (!i.mpNode)
        i.increment_bucket();
    return i;
}

template<typename K, typename T>
class hash_map : public hashtable<K, pair<const K, T>, allocator, use_first<pair<const K, T> >, equal_to<K>, hash<K>, mod_range_hashing, default_ranged_hash> {
public:
    typedef hashtable<K, pair<const K, T>, allocator, use_first<pair<const K, T> >, equal_to<K>, hash<K>, mod_range_hashing, default_ranged_hash> base_type;
    hash_map(const allocator& a = allocator());
};

template<typename K, typename T>
hash_map<K, T>::hash_map(const allocator& a)
    : base_type(0, hash<K>(), mod_range_hashing(), default_ranged_hash(), equal_to<K>(), use_first<pair<const K, T> >(), a) {
}
}

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};

class IConfigManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual int GetInt(uint32_t id);
};

class IMessageManager {
public:
    virtual void v00();
    virtual void MessageSend(uint32_t messageID, void* pData);
};


namespace SP { struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
}; }
struct DatabasePackedFile {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void Commit();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual void v0e(); virtual void v0f();
    virtual void DeleteRecord(const ResourceKey& key);
};
struct IResourceFilter {
    IResourceFilter() {}
    virtual ~IResourceFilter() {}
    virtual bool IsValid(const ResourceKey& key);
};
struct ResourceKeyFilter : public IResourceFilter {
    uint32_t mInstanceID;
    uint32_t mGroupID;
    uint32_t mTypeID;
    uint32_t mFlags;
    ResourceKeyFilter(uint32_t groupID, uint32_t instanceID)
        : mInstanceID(instanceID), mGroupID(groupID), mTypeID(0xffffffff), mFlags(0xdfff0000) {}
    virtual bool IsValid(const ResourceKey& key);
};
namespace eastl { template<typename T> class basic_vector; template<typename T> class key_vector; }
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b(); virtual void v0c();
    // MSVC lays out overloaded virtuals in reverse declaration order.
    virtual int GetResourceKeyList(eastl::key_vector<ResourceKey>& keys, IResourceFilter& filter, eastl::basic_vector<DatabasePackedFile*>& dbs);
    virtual int GetResourceKeyList(eastl::key_vector<ResourceKey>& keys, IResourceFilter& filter);
};
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); }}

template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

namespace EA { namespace COM {
template<typename T, typename U> T* interface_cast(IntrusivePtr<U>& p);
}}

namespace eastl {
template<typename T>
inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
template<typename T>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase();
};
template<typename T>
struct KeyVectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    KeyVectorBase(const allocator& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~KeyVectorBase();
};
template<typename T>
class key_vector : public KeyVectorBase<T> {
public:
    typedef KeyVectorBase<T> base_type;
    key_vector(const allocator& a = allocator()) : base_type(a) {}
    ~key_vector() { destruct(base_type::mpBegin, base_type::mpEnd); ScratchSlots<3>(); }
    size_t size() const { return base_type::mpEnd - base_type::mpBegin; }
    T& operator[](size_t n) { return base_type::mpBegin[n]; }
    T* begin() { return base_type::mpBegin; }
    T* end() { return base_type::mpEnd; }
    T* erase(T* first, T* last);
    void clear() { ScratchSlots<4>(); erase(base_type::mpBegin, base_type::mpEnd); }
};
template<typename T>
class basic_vector : public VectorBase<T> {
public:
    T& operator[](size_t n) { return VectorBase<T>::mpBegin[n]; }
    basic_vector() {}
    ~basic_vector() { destruct(VectorBase<T>::mpBegin, VectorBase<T>::mpEnd); ScratchSlots<3>(); }
};
}
namespace SP { class cEditorResource; }

namespace SP {

namespace Traits {
class cFeatureVector {
public:
    bool IsEmpty() const;
    cFeatureVector& operator=(const cFeatureVector& x);
    char pad[0x1c];
};
void ApplyWeights(cFeatureVector& v, const eastl::vector_map<uint32_t, float>& weights);

class cIClassifier {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void v06();
};
}

namespace FunctionalMatch {
struct DeclareParam {
    unsigned int mParameter;
    unsigned int mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam();
};
class cISummarizer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual uint32_t GetID();
    virtual uint32_t GetGroup();
    virtual void* GetSummary();
    virtual void v07();
    virtual bool Validate(cEditorResource* pResource, eastl::basic_vector<uint32_t>& blockIDs, int flags);
};
}

class cISPObjectTemplateDB {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c();
    virtual void OnAssetBanned(const ResourceKey& key, bool permanent);
};

class cIMatchTuning {
public:
    virtual void m00();
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey& key, int flags);
};

template<typename T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};

class cSPObjectTemplateDB : public cISPObjectTemplateDB, public cIMatchTuning {
public:
    struct AssetInfo {
        ResourceKey mKey;
        uint32_t mnModelSubtype;
        Traits::cFeatureVector mFeatureVector;
        eastl::vector_set<uint32_t> mGroupIDs;
        char pad44[0x50 - 0x44];
    };
    typedef eastl::vector_map<uint32_t, float> WeightMap;

    char pad08[0x14 - 0x08];
    eastl::vector<AssetInfo, eastl::sp_vector_allocator> mAssetList;    // +0x14
    char pad28[0x1ac - 0x28];
    WeightMap mClassifierWeights;                                        // +0x1ac
    bool mbUseClassifierWeights;                                         // +0x1c4
    char pad1c5[0x1ec - 0x1c5];
    eastl::map<uint32_t, AutoRefCount<Traits::cIClassifier> > mClassifierTable;            // +0x1ec
    eastl::map<uint32_t, AutoRefCount<FunctionalMatch::cISummarizer> > mSummarizerTable;   // +0x208
    char pad224[0x240 - 0x224];
    WeightMap mDefaultClassifierWeights;                                 // +0x240

    int FindAssetIndex(uint32_t assetID);
    virtual bool GetFeatureVector(uint32_t assetID, Traits::cFeatureVector& features);
    virtual void* FindSummaryByID(const uint32_t& id);
    virtual void* FindSummary(uint32_t id);
    virtual void SetClassifierWeights(const eastl::vector_map<uint32_t, float>& weights);
    virtual void GetDefaultClassifierWeights(eastl::vector_map<uint32_t, float>& weights);
    virtual bool ValidateResource(const ResourceKey& key, int flags);
    void SaveGroupRecords();
    uint32_t GetGroupForAssetGroup(uint32_t groupID);
    void BanAsset(const ResourceKey& key, bool permanent);

    // ---- unnamed/extra methods (slices s0055ce80..s00567a90) ----
    bool FUN_0055cff0(void* pKey);
    char FUN_0055d230(int index, void* pList);
    bool FUN_0055d790(void* pKey, void* pList);
    char FUN_0055d9e0(void* pObj, int count, void* pItems, char flag);
    char FUN_0055db30(void* pObj);
    bool FUN_0055cd90(void* pKey, void* pOut, void* pIn);
    int  FUN_00560c30(void* pKey);
    void FUN_00561850(int index);
    bool FUN_00558bf0(int a, int b);
};

// Generic stub whose methods stand in for the real helper functions (call targets
// are relocated, so only the calling convention/stack shape matters).
struct DBSub {
    bool GetResType();
    void Find(void* outIt, void* key);
    void End(void* outIt);
    void* Deref(void* it);
    void Insert(void* out, void* val);
    void AddVal(int a, void* p, unsigned value);
    void AddKey0(void* out, void* val, char flag);
    void AddKey1(void* out, void* val);
    void Destroy();
    void AddIter(void* outIt, void* it);
};

namespace SP { uint32_t EditorEntityToResourceType(uint32_t modelType, int a); }

}


namespace EA { namespace Messaging {
class IMessageServer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void MessageSend(uint32_t messageID, void* pMessage, int flags);
};
IMessageServer* GetServer();

class MessageRCBase {
public:
    MessageRCBase(int flags);
    virtual ~MessageRCBase();
    uint32_t mnRefCount;
};
template<int N>
class MessageBasicRC : public MessageRCBase {
public:
    struct Data { uint32_t mValue; uint32_t mType; };
    Data mData[N];
    uint32_t mId;
    uint32_t mRC;
    uint32_t mRCFlags;
    uint32_t mReserved;
    MessageBasicRC(uint32_t id) : MessageRCBase(0) { mRCFlags = 0; mId = id; }
    ~MessageBasicRC();
    void SetUint32(int index, uint32_t value) { mData[index].mValue = value; }
    uint32_t GetId() const { return mId; }
};
}}

class cAssetBrowser {
public:
    void OnAssetBanned(const ResourceKey& key);
};
cAssetBrowser* GetAssetBrowser();

class IPropertyManager2 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e();
    virtual void RemovePropertyList(int flags, const ResourceKey& key);
};

namespace SP {
DatabasePackedFile* GetSaveArea(uint32_t groupID);
IPropertyManager2* PropertyManager();
void RemoveResource(const ResourceKey& key);

}
struct IDPair { uint32_t mID; uint32_t mIndex; };
struct WeightedID {
    IDPair mIDs;
    float mWeight;
    WeightedID() : mIDs(), mWeight() {}
};

namespace ArgScript {
class cCommandBase {
public:
    cCommandBase();
    virtual ~cCommandBase();
};
}
namespace Editor {
class OTDB : public ArgScript::cCommandBase {
public:
    OTDB();
    virtual void ParseLine();
};
}

namespace SP {


void WritePillRecord(uint32_t instanceID, uint32_t value);
void GetBlockIDs(cEditorResource* pResource, eastl::basic_vector<uint32_t>& blockIDs);
}
