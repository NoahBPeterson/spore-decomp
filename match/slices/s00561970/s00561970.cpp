// Slice s00561970: SP::cSPObjectTemplateDB population bookkeeping, parameter-value queries,
// constraint matching and priority constraints.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// ScratchSlots<N>() reproduces frame space that /Od callers reserve for EASTL helpers the
// compiler declined to inline; local names reproduce the /Od name-hash slot order.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// Local-frame size of the (declined-inline) erase(first, last) instance, which /Od callers reserve.
template<typename T> struct EraseFrame { enum { kSlots = 6 }; };
template<> struct EraseFrame<uint32_t> { enum { kSlots = 4 }; };
template<> struct EraseFrame<int> { enum { kSlots = 4 }; };
template<> struct EraseFrame<float> { enum { kSlots = 4 }; };

namespace eastl {

struct allocator { allocator() {} };
struct sp_vector_allocator : public allocator {
    sp_vector_allocator() {}
    const char* mpName;
    uint32_t mFlags;
};

template<typename T> struct less { less() {} };
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
};

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
};

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
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};

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

namespace SP {
IConfigManager* ConfigManager();
IMessageManager* MessageManager();

namespace FunctionalMatch {
enum eType {
    kInteger = 48342877,
    kFloat = 48343039,
    kTerminal = 48343507,
    kNotEqual = 0xcba453f7
};
enum EqualConstraint { kEquals = 0 };

struct Constraint {
    unsigned int mParameter;
    eType mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector<Constraint, eastl::sp_vector_allocator> mConstraints;

    Constraint(unsigned int param, EqualConstraint, int value);
};
}
using namespace FunctionalMatch;

class cSPObjectTemplateDB {
public:
    struct AssetInfo {
        ResourceKey mKey;
        char pad0c[0x2c - 0x0c];
        eastl::vector_set<uint32_t> mGroupIDs;
        char pad44[0x50 - 0x44];
    };
    struct PriorityConstraint {
        uint32_t mnTag;
        Constraint mConstraint;
        PriorityConstraint(uint32_t tag, const Constraint& c) : mnTag(tag), mConstraint(c) {}
        bool operator==(uint32_t tag) const { return mnTag == tag; }
    };
    typedef eastl::vector_map<uint32_t, uint32_t> CountMap;
    typedef eastl::map<int, eastl::vector_set<uint32_t> > IntValueMap;
    typedef eastl::map<float, eastl::vector_set<uint32_t> > FloatValueMap;

    char pad00[0x14];
    eastl::vector<AssetInfo, eastl::sp_vector_allocator> mAssetList;    // +0x14
    eastl::vector_set<uint32_t> mFreeList;                               // +0x28
    char pad40[0x64 - 0x40];
    eastl::vector_set<uint32_t> mCandidates;                             // +0x64
    char pad7c[0xac - 0x7c];
    CountMap mPopulationCount;                                           // +0xac
    CountMap mRefillCount;                                               // +0xc4
    CountMap mTypePopulation;                                            // +0xdc
    eastl::map<uint32_t, IntValueMap> mIntParameters;                    // +0xf4
    eastl::map<uint32_t, FloatValueMap> mFloatParameters;                // +0x110
    eastl::vector_set<uint32_t> mMatchResults;                           // +0x12c
    eastl::vector_set<uint32_t> mResultSet;                              // +0x144
    eastl::vector_set<uint32_t> mScratchSet;                             // +0x15c
    char pad174[0x258 - 0x174];
    eastl::vector<PriorityConstraint, eastl::sp_vector_allocator> mPriorityConstraints; // +0x258

    void DecreasePopulation(int index);
    void CheckForMinPopulations();
    void RebuildFreeList();
    void ReleaseAsset(int index);
    void FindMatching(eastl::vector_set<uint32_t>* pResults, const Constraint& c);
    void AddIntMatches(eastl::vector_set<uint32_t>* pResults, int minVal, int maxVal, IntValueMap& values);
    void AddFloatMatches(eastl::vector_set<uint32_t>* pResults, float minVal, float maxVal, FloatValueMap& values);
    void FilterByConstraint(eastl::vector_set<uint32_t>& candidates, const Constraint& c);
    bool GetAssetKeys(eastl::vector<uint32_t>& indices, eastl::vector<ResourceKey>& keys);
    void ExcludeCandidates(eastl::vector_set<uint32_t>& candidates, bool force);
    void AddPriorityConstraint(const Constraint& c, uint32_t tag);
    void RemovePriorityConstraint(uint32_t tag);
    void SetExcludedParameter(int value);
    bool GetFloatParameterValues(uint32_t paramID, eastl::vector<float>& values);
    bool GetIntParameterValues(uint32_t paramID, eastl::vector<int>& values);
    bool GetFloatParameterTable(uint32_t paramID, eastl::vector<float>& values, eastl::vector<ResourceKey>& keys);
    bool GetIntParameterTable(uint32_t paramID, eastl::vector<int>& values, eastl::vector<ResourceKey>& keys);
    void ClearExcludedParameter();
};

}

namespace SP {

// @ 0x00561970
void cSPObjectTemplateDB::DecreasePopulation(int index) {
    AssetInfo& assetEntry = mAssetList[index];
    eastl::vector_set<uint32_t> groupList(assetEntry.mGroupIDs);
    bool disabled = ConfigManager()->GetInt(0x5de7b4a) != 0;
    uint32_t* pos = groupList.begin();
    uint32_t* itEnd = groupList.end();
    for (; pos != itEnd; ++pos) {
        uint32_t groupID = *pos;
        CountMap::iterator refill = mRefillCount.find_(groupID);
        if (refill != mRefillCount.end()) {
            CountMap::iterator itPop = mPopulationCount.find_(groupID);
            if (itPop != mPopulationCount.end()) {
                eastl::pair<uint32_t, uint32_t>& pop = *itPop;
                if (pop.second > 0) {
                    uint32_t count = --pop.second;
                    if (count == refill->second && !disabled) {
                        uint32_t msgGroupID = groupID;
                        MessageManager()->MessageSend(0x45883b0, &msgGroupID);
                    }
                }
            }
        }
    }
    CountMap::iterator itTypeCount = mTypePopulation.find_(assetEntry.mKey.mTypeID);
    if (itTypeCount != mTypePopulation.end()) {
        eastl::pair<uint32_t, uint32_t>& typePop = *itTypeCount;
        if (typePop.second > 0)
            typePop.second--;
    }
    ScratchSlots<4>();
}


// @ 0x00561bd0
void cSPObjectTemplateDB::CheckForMinPopulations() {
    if (ConfigManager()->GetInt(0x5de7b4a) == 0) {
        for (CountMap::iterator iter = mPopulationCount.begin(), last = mPopulationCount.end(); iter != last; ++iter) {
            eastl::pair<uint32_t, uint32_t>& entry = *iter;
            CountMap::iterator itRefill = mRefillCount.find(entry.first);
            if (itRefill != mRefillCount.end() && entry.second <= itRefill->second)
                MessageManager()->MessageSend(0x45883b0, &entry);
        }
    }
}

// @ 0x00561cc0
void cSPObjectTemplateDB::RebuildFreeList() {
    mPopulationCount.clear();
    uint32_t count = mAssetList.size();
    for (uint32_t i = 0; i < count; i++) {
        if (mFreeList.find(i) == mFreeList.end())
            ReleaseAsset(i);
    }
}

// @ 0x00561d80
bool cSPObjectTemplateDB::GetFloatParameterValues(uint32_t paramID, eastl::vector<float>& values) {
    eastl::map<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(paramID);
    if (it != mFloatParameters.end()) {
        FloatValueMap& valueMap = (*it).second;
        values.clear();
        eastl::copy(valueMap.begin(), valueMap.end(), eastl::key_inserter(values, values.end()), eastl::input_iterator_tag());
        return true;
    } else {
        return false;
    }
}

// @ 0x00561ea0
bool cSPObjectTemplateDB::GetIntParameterValues(uint32_t paramID, eastl::vector<int>& values) {
    eastl::map<uint32_t, IntValueMap>::iterator it = mIntParameters.find(paramID);
    if (it != mIntParameters.end()) {
        IntValueMap& valueMap = (*it).second;
        values.clear();
        eastl::copy(valueMap.begin(), valueMap.end(), eastl::key_inserter(values, values.end()), eastl::input_iterator_tag());
        return true;
    } else {
        return false;
    }
}


// @ 0x00561fc0
bool cSPObjectTemplateDB::GetFloatParameterTable(uint32_t paramID, eastl::vector<float>& values, eastl::vector<ResourceKey>& keys) {
    eastl::map<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(paramID);
    if (it != mFloatParameters.end()) {
        FloatValueMap& vm = (*it).second;
        values.clear_noframe();
        keys.clear_noframe();
        values.reserve(vm.size());
        keys.reserve(vm.size());
        FloatValueMap::iterator vit = vm.begin();
        FloatValueMap::iterator vend = vm.end();
        for (; vit != vend; ++vit) {
            float paramValue = (*vit).first;
            eastl::vector_set<uint32_t>& owners = (*vit).second;
            uint32_t* iter2 = owners.begin();
            uint32_t* iEnd = owners.end();
            for (; iter2 != iEnd; ++iter2) {
                keys.push_back(mAssetList[*iter2].mKey);
                values.push_back(paramValue);
            }
        }
        ScratchSlots<4>();
        return true;
    } else {
        return false;
    }
}

// @ 0x00562120
bool cSPObjectTemplateDB::GetIntParameterTable(uint32_t paramID, eastl::vector<int>& values, eastl::vector<ResourceKey>& keys) {
    eastl::map<uint32_t, IntValueMap>::iterator it = mIntParameters.find(paramID);
    if (it != mIntParameters.end()) {
        IntValueMap& vm = (*it).second;
        values.clear_noframe();
        keys.clear_noframe();
        values.reserve(vm.size());
        keys.reserve(vm.size());
        IntValueMap::iterator vit = vm.begin();
        IntValueMap::iterator vend = vm.end();
        for (; vit != vend; ++vit) {
            int paramValue = (*vit).first;
            eastl::vector_set<uint32_t>& owners = (*vit).second;
            uint32_t* iter2 = owners.begin();
            uint32_t* iEnd = owners.end();
            for (; iter2 != iEnd; ++iter2) {
                keys.push_back(mAssetList[*iter2].mKey);
                values.push_back(paramValue);
            }
        }
        ScratchSlots<4>();
        return true;
    } else {
        return false;
    }
}

// @ 0x00562280
void cSPObjectTemplateDB::FindMatching(eastl::vector_set<uint32_t>* pResults, const Constraint& c) {
    switch (c.mType) {
    case kInteger: {
        eastl::map<uint32_t, IntValueMap>::iterator it = mIntParameters.find(c.mParameter);
        if (it != mIntParameters.end()) {
            IntValueMap& values = (*it).second;
            AddIntMatches(pResults, c.mIntVal.mMin, c.mIntVal.mMax, values);
        }
        break;
    }
    case kFloat: {
        eastl::map<uint32_t, FloatValueMap>::iterator it = mFloatParameters.find(c.mParameter);
        if (it != mFloatParameters.end()) {
            FloatValueMap& values = (*it).second;
            AddFloatMatches(pResults, c.mFloatVal.mMin, c.mFloatVal.mMax, values);
        }
        // falls through (a float constraint has no sub-constraints)
    }
    case kNotEqual:
        for (uint32_t i = 0; i < c.mConstraints.size(); i++)
            FindMatching(pResults, c.mConstraints[i]);
        break;
    }
}

// @ 0x005623f0
void cSPObjectTemplateDB::FilterByConstraint(eastl::vector_set<uint32_t>& candidates, const Constraint& c) {
    if (!candidates.empty()) {
        mResultSet.clear();
        FindMatching(&mResultSet, c);
        mScratchSet.clear();
        eastl::set_intersection(candidates.begin(), candidates.end(), mResultSet.begin(), mResultSet.end(),
                                eastl::inserter(mScratchSet, mScratchSet.begin()));
        candidates.swap(mScratchSet);
    }
    ScratchSlots<21>();
}

// @ 0x00562510
bool cSPObjectTemplateDB::GetAssetKeys(eastl::vector<uint32_t>& indices, eastl::vector<ResourceKey>& keys) {
    keys.clear();
    keys.reserve(indices.size());
    for (uint32_t* it = indices.begin(), *itEnd = indices.end(); it != itEnd; ++it)
        keys.push_back(mAssetList[*it].mKey);
    return !keys.empty();
}

// @ 0x005625a0
void cSPObjectTemplateDB::ExcludeCandidates(eastl::vector_set<uint32_t>& candidates, bool force) {
    mResultSet.clear();
    eastl::set_difference(candidates.begin(), candidates.end(), mCandidates.begin(), mCandidates.end(),
                          eastl::inserter(mResultSet, mResultSet.begin()));
    if (force || !mResultSet.empty())
        candidates.swap(mResultSet);
    ScratchSlots<24>();
}

// @ 0x00562680
void cSPObjectTemplateDB::AddPriorityConstraint(const Constraint& c, uint32_t tag) {
    PriorityConstraint pc(tag, c);
    mPriorityConstraints.push_back(pc);
    ScratchSlots<9>();
}

// @ 0x00562710
void cSPObjectTemplateDB::RemovePriorityConstraint(uint32_t tag) {
    PriorityConstraint* it = eastl::find(mPriorityConstraints.begin(), mPriorityConstraints.end(), tag);
    if (it != mPriorityConstraints.end())
        mPriorityConstraints.erase(it);
    ScratchSlots<12>();
}

// @ 0x00562790
void cSPObjectTemplateDB::SetExcludedParameter(int value) {
    RemovePriorityConstraint(0x5dd2a5b);
    Constraint c(0x3cc89b1, kEquals, value);
    AddPriorityConstraint(c, 0x5dd2a5b);
    mMatchResults.clear();
    FindMatching(&mMatchResults, c);
    eastl::set_difference(mCandidates.begin(), mCandidates.end(), mMatchResults.begin(), mMatchResults.end(),
                          eastl::inserter(mResultSet, mResultSet.begin()));
    mCandidates.assign(mResultSet.begin(), mResultSet.end());
    ScratchSlots<5>();
}

// @ 0x005628b0
void cSPObjectTemplateDB::ClearExcludedParameter() {
    RemovePriorityConstraint(0x5dd2a5b);
}

}
