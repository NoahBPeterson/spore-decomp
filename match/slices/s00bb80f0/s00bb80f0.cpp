// Slice s00bb80f0: Simulator::cStarManager galaxy-generation pass 4 (0x00BB80F0, 2586 bytes):
// picks the possible start locations and seeds the AI empires.
// Called from cStarManager::LoadStarDatabase (s00bb8b20, "GeneratePass4") right after the seed points.
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the locals with dtors get no EH frame).
//
// Flow:
//  - reads the galaxy-generation property list 0x288CFA78 (min/max start distance 0xD2125FBA and
//    0x745DB9D0, default 100/500; eleven further properties are read but unused);
//  - reads the float array 0x057FA8DD of list 0xCCB6BE71/0x02AE0C7E as (x, y, count) triples and,
//    for each triple, lays a 10x10 grid of points (offsets -1000..800 step 200) around (x, y),
//    keeping the points outside mGrobOnlyRadius;
//  - for each point: the closest yellow star (type 0x10) at a distance in (min, max) from the
//    galactic centre becomes a possible start location (tech level 1, no empire); otherwise the closest
//    star (types 0x1FF1, tech levels 0x3E, within 3 parsecs) not yet an empire home gets a new
//    political id, tech level 5 (empire), flag 4, and goes into a local map political id -> seed;
//  - drops seeds whose home star has fewer than two stars within 3 parsecs (types 0x1FFF, tech 2);
//  - runs three generation passes, then sets each seed empire's level/fields and lets the empire
//    growth sim take 0-3 random turns for it;
//  - removes possible start locations rejected by 0x00BB24D0.
#include "types.h"
#include <math.h>

inline void* operator new(size_t, void* p) { return p; }

template<class T> struct AutoRefCount
{
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T*& AsOutParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return mpObject;
    }
};

// ---------------------------------------------------------------------------------------------
// Properties
struct Property
{
    uint32_t pad_00[0x10 / 4];
    uint16_t field_10;
    uint16_t mnType;                                                // +0x12 (0x0D = float)
    float* GetFloat();                                              // 0x0041EA70
};

struct cPropertyList
{
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& pDst);         // +0x24
};

struct IPropertyManager
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool HasPropertyList(uint32_t instance, uint32_t group);           // +0x28
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList*& pList); // +0x2C
};
IPropertyManager* PropertyManager();                                // 0x0067DE30

namespace App { namespace Property {
inline bool GetFloat(cPropertyList* pList, uint32_t id, float& dst)
{
    ::Property* pProp;
    if (pList && pList->GetProperty(id, pProp) && pProp->mnType == 0x0D) {
        dst = *pProp->GetFloat();
        return true;
    }
    return false;
}
// Reads a property whose value this function never uses (only the lookup survives).
inline bool HasProperty(cPropertyList* pList, uint32_t id)
{
    ::Property* pProp;
    if (pList && pList->GetProperty(id, pProp))
        return true;
    return false;
}
} }

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};

// ---------------------------------------------------------------------------------------------
// eastl vector (Spore layout: 0x14 bytes)
namespace eastl {
template<class T> struct vector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t mAllocator2;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    void reserve(uint32_t n);
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* position);
    T* erase(T* first, T* last);
    void clear() { erase(mpBegin, mpEnd); }
};
}

// ---------------------------------------------------------------------------------------------
// Simulator
struct StarRequestFilter
{
    int starTypes;
    int techLevels;
    int flags;
    float minDistance;
    float maxDistance;
    float field_14;
    int field_18;
    StarRequestFilter()
        : starTypes(0x1FFF), techLevels(0x3F), flags(0), minDistance(-1.0f), maxDistance(-1.0f),
          field_14(-1.0f), field_18(0) {}
};

struct cStarRecord
{
    virtual int AddRef();
    virtual int Release();
    void SetEmpireID(uint32_t id);                                  // 0x00A16A90 (+0x54)
    uint32_t GetEmpireID();                                         // 0x00B1FDB0 (+0x54)
    void SetTechLevel(int level);                                   // 0x00BB9AD0 (+0x4C)
    int GetTechLevel();                                             // 0x00BB9AE0 (+0x4C)
    void SetFlag(int flag, bool value);                             // 0x00BB9B00 (+0x5C)
    const Vector3& GetPosition();                                   // 0x005C65E0 (+0x3C)
};
typedef AutoRefCount<cStarRecord> cStarRecordPtr;

// eastl::copy for AutoRefCount<cStarRecord> ranges (out of line, folded with other instances)
cStarRecordPtr* do_copy(cStarRecordPtr* first, cStarRecordPtr* last, cStarRecordPtr* dest); // 0x006782C0

template<> inline cStarRecordPtr* eastl::vector<cStarRecordPtr>::erase(cStarRecordPtr* first, cStarRecordPtr* last)
{
    cStarRecordPtr* const position = do_copy(last, mpEnd, first);
    for (cStarRecordPtr* p = position; p < mpEnd; ++p)
        p->~cStarRecordPtr();
    mpEnd -= (last - first);
    return first;
}
template<> inline cStarRecordPtr* eastl::vector<cStarRecordPtr>::erase(cStarRecordPtr* position)
{
    if ((position + 1) < mpEnd)
        do_copy(position + 1, mpEnd, position);
    --mpEnd;
    mpEnd->~cStarRecordPtr();
    return position;
}

struct cEmpire
{
    virtual int AddRef();
    virtual int Release();
    uint32_t pad_04[(0x58 - 0x04) / 4];
    uint32_t field_58;                                              // +0x58
    uint32_t pad_5c[(0xD4 - 0x5C) / 4];
    int8_t mEmpireLevel;                                            // +0xD4
};

uint32_t GetEmpireSize(int level);                                  // 0x00BA5EE0

struct cEmpireGrowthSim { void TakeTurn(uint32_t politicalID); };  // 0x00FE9580
struct cSpaceGame { uint32_t pad[0x188 / 4]; cEmpireGrowthSim* mpGrowthSim; };
cSpaceGame* SpaceGame();                                            // 0x00FD9C60

struct RandomLinearCongruential { int RandomUint32Uniform(uint32_t range); }; // 0x00A68FB0
extern RandomLinearCongruential sMathRandom;                        // 0x01601760

// ---------------------------------------------------------------------------------------------
// eastl rbtree / map
namespace eastl {
struct rbtree_node_base
{
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
}
eastl::rbtree_node_base* RBTreeIncrement(const eastl::rbtree_node_base* pNode); // 0x00921580
void RBTreeErase(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeAnchor); // 0x00921880

namespace eastl {
template<class K, class V> struct pair { K first; V second; };

template<class K, class V> struct rbtree_node : rbtree_node_base
{
    pair<const K, V> mValue;
};

template<class K, class V> struct rbtree_iterator
{
    rbtree_node<K, V>* mpNode;
    rbtree_iterator() : mpNode(0) {}
    explicit rbtree_iterator(rbtree_node<K, V>* p) : mpNode(p) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    rbtree_iterator& operator++()
    {
        mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode);
        return *this;
    }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    pair<const K, V>* operator->() const { return &mpNode->mValue; }
};

template<class K, class V> struct map
{
    typedef rbtree_node<K, V> node_type;
    typedef rbtree_iterator<K, V> iterator;

    int mCompare;
    rbtree_node_base mAnchor;
    uint32_t mnSize;
    uint32_t mAllocator;

    map() : mAnchor(), mnSize(0) { reset(); }
    ~map() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
    void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    iterator begin() { return iterator((node_type*)mAnchor.mpNodeLeft); }
    iterator end() { return iterator((node_type*)&mAnchor); }
    iterator lower_bound(const K& key)
    {
        node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
        node_type* pRangeEnd = (node_type*)&mAnchor;
        while (pCurrent) {
            if (!(pCurrent->mValue.first < key)) {
                pRangeEnd = pCurrent;
                pCurrent = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        return iterator(pRangeEnd);
    }
    iterator find(const K& key)
    {
        const iterator itEnd(end());
        const iterator itLower(lower_bound(key));
        if ((itLower != itEnd) && !(key < itLower.mpNode->mValue.first))
            return itLower;
        return itEnd;
    }
    V& operator[](const K& key);                                    // out of line
    void DoNukeSubtree(node_type* pNode);                           // out of line
    void DoFreeNode(node_type* pNode)
    {
        pNode->mValue.~pair<const K, V>();
        operator delete[](pNode);
    }
    iterator erase(iterator position)
    {
        const iterator iErase(position);
        --mnSize;
        ++position;
        RBTreeErase(iErase.mpNode, &mAnchor);
        DoFreeNode(iErase.mpNode);
        return position;
    }
};
}

// Seed of an AI empire (value of the local map, keyed by political id).
struct ScratchArray
{
    void* mpData;
    ~ScratchArray() { if (mpData) operator delete[](mpData); }
};
struct EmpireSeed
{
    eastl::vector<cStarRecordPtr> mStars;                           // +0x00
    float mLevel;                                                   // +0x14
    int mSizeIndex;                                                 // +0x18
    ScratchArray field_1c;                                          // +0x1C
};
typedef eastl::map<uint32_t, EmpireSeed> EmpireSeedMap;
// 0x00BB8010 = EmpireSeedMap::operator[], 0x00BABA60 = EmpireSeedMap::DoNukeSubtree

// A generated start point: position plus the count read from the property triple.
struct StartPoint
{
    Vector3 pos;
    int count;
    StartPoint(const Vector3& p, int n) : pos(p), count(n) {}
    StartPoint(const StartPoint& x) : pos(x.pos), count(x.count) {}
};
// 0x00BAA170 = vector<StartPoint>::reserve, 0x00BAA410 = vector<StartPoint>::DoInsertValue
// 0x00AEA5D0 = vector<cStarRecordPtr>::DoInsertValue

bool GetPropertyFloatArray(cPropertyList* pList, uint32_t id, int type, eastl::vector<float>& dst); // 0x00BB15D0

struct cStarManager
{
    uint32_t pad_00[0x118 / 4];
    eastl::vector<cStarRecordPtr> mPossibleStartLocations;          // +0x118
    uint32_t pad_12c[(0x150 - 0x12C) / 4];
    eastl::map<uint32_t, AutoRefCount<cEmpire> > mEmpires;          // +0x150
    uint32_t pad_16c[(0x1BC - 0x16C) / 4];
    float mGrobOnlyRadius;                                          // +0x1BC
    uint32_t pad_1c0[(0x1D4 - 0x1C0) / 4];
    uint32_t mNextPoliticalID;                                      // +0x1D4

    cStarRecord* FindClosestStar(const Vector3& pos, const StarRequestFilter& filter); // 0x00BB0E90
    void FindStars(const Vector3& pos, const StarRequestFilter& filter, eastl::vector<cStarRecordPtr>& dst); // 0x00BB1080
    void GeneratePass4a();                                          // 0x00BB2610
    void CreateEmpires();                                           // 0x00BB2070
    void GeneratePass4c();                                          // 0x00BAA930
    bool IsValidStartLocation(cStarRecord* pStar);                  // 0x00BB24D0

    cEmpire* GetEmpire(uint32_t politicalID)
    {
        if (politicalID == 0xFFFFFFFF)
            return 0;
        eastl::map<uint32_t, AutoRefCount<cEmpire> >::iterator it = mEmpires.find(politicalID);
        if (it == mEmpires.end())
            return 0;
        return it->second.get();
    }

    void GeneratePass4();
};

// @ 0x00BB80F0
void cStarManager::GeneratePass4()
{
    float minDistance = 100.0f;
    float maxDistance = 500.0f;

    AutoRefCount<cPropertyList> pPropList;
    if (PropertyManager()->GetPropertyList(0x288CFA78, 0, pPropList.AsOutParam())) {
        App::Property::HasProperty(pPropList, 0xA08E82FB);
        App::Property::HasProperty(pPropList, 0x6FFD9055);
        App::Property::HasProperty(pPropList, 0x2B3BC207);
        App::Property::HasProperty(pPropList, 0xE6296AD3);
        App::Property::HasProperty(pPropList, 0x09B691CB);
        App::Property::HasProperty(pPropList, 0xF024580D);
        App::Property::HasProperty(pPropList, 0x3ACEF25C);
        App::Property::HasProperty(pPropList, 0x42CEFEB2);
        App::Property::GetFloat(pPropList, 0xD2125FBA, minDistance);
        App::Property::GetFloat(pPropList, 0x745DB9D0, maxDistance);
        App::Property::HasProperty(pPropList, 0x15939A97);
        App::Property::HasProperty(pPropList, 0xC9F15B65);
        App::Property::HasProperty(pPropList, 0x1DBFF33C);
    }

    eastl::vector<float> clusters;
    AutoRefCount<cPropertyList> pClusterList;
    PropertyManager()->GetPropertyList(0xCCB6BE71, 0x02AE0C7E, pClusterList.AsOutParam());
    GetPropertyFloatArray(pClusterList, 0x057FA8DD, 0x0D, clusters);

    eastl::vector<StartPoint> points;
    points.reserve(2000);
    const float* pValues = clusters.begin();
    const uint32_t count = clusters.size();
    for (uint32_t i = 0; i < count; i += 3) {
        for (float dx = -1000.0f; dx < 1000.0f; dx += 200.0f) {
            for (float dy = -1000.0f; dy < 1000.0f; dy += 200.0f) {
                StartPoint point(Vector3(pValues[i] + dx, pValues[i + 1] + dy, 0.0f), (int)pValues[i + 2]);
                if (point.pos.x * point.pos.x + point.pos.y * point.pos.y > mGrobOnlyRadius * mGrobOnlyRadius)
                    points.push_back(point);
            }
        }
    }

    EmpireSeedMap seeds;
    StarRequestFilter filter;
    {
        StarRequestFilter startFilter;
        startFilter.starTypes = 0x10;
        startFilter.techLevels = 0x3F;
        startFilter.flags = 0;
        startFilter.minDistance = -1.0f;
        startFilter.maxDistance = 5.0f;
        startFilter.field_14 = -1.0f;
        startFilter.field_18 = 0;

        filter.starTypes = 0x1FF1;
        filter.techLevels = 0x3E;
        filter.flags = 0;
        filter.minDistance = -1.0f;
        filter.maxDistance = 3.0f;
        filter.field_14 = -1.0f;
        filter.field_18 = 0;

        StartPoint* pPoints = points.begin();
        const uint32_t pointCount = points.size();
        for (uint32_t j = 0; j < pointCount; ++j) {
            StartPoint* pPoint = &pPoints[j];
            cStarRecord* pStar = FindClosestStar(pPoint->pos, startFilter);
            if (pStar) {
                float distance = pStar->GetPosition().Length();
                if (pStar->GetTechLevel() != 5 && pPoint->count == 0 &&
                    distance > minDistance && distance < maxDistance) {
                    pStar->SetEmpireID(0xFFFFFFFF);
                    pStar->SetTechLevel(1);
                    mPossibleStartLocations.push_back(cStarRecordPtr(pStar));
                    continue;
                }
            }

            pStar = FindClosestStar(pPoint->pos, filter);
            if (pStar && pStar->GetTechLevel() != 5) {
                pStar->SetEmpireID(mNextPoliticalID++ | 0x80000000);
                pStar->SetTechLevel(5);
                pStar->SetFlag(4, true);
                {
                    cStarRecordPtr pRecord(pStar);
                    seeds[pStar->GetEmpireID()].mStars.push_back(pRecord);
                }
                seeds[pStar->GetEmpireID()].mLevel = 4.0f;
                seeds[pStar->GetEmpireID()].mSizeIndex = pPoint->count - 1;
                if (seeds[pStar->GetEmpireID()].mSizeIndex < 0)
                    seeds[pStar->GetEmpireID()].mSizeIndex = sMathRandom.RandomUint32Uniform(3);
            }
        }
    }

    {
        filter.starTypes = 0x1FFF;
        filter.techLevels = 2;
        filter.flags = 0;
        filter.minDistance = -1.0f;
        filter.maxDistance = 3.0f;
        filter.field_14 = -1.0f;
        filter.field_18 = 0;

        eastl::vector<cStarRecordPtr> neighbours;
        for (EmpireSeedMap::iterator it = seeds.begin(); it != seeds.end(); ) {
            cStarRecord* pHome = it->second.mStars[0].get();
            neighbours.clear();
            FindStars(pHome->GetPosition(), filter, neighbours);
            if (neighbours.size() < 2) {
                pHome->SetEmpireID(0xFFFFFFFF);
                pHome->SetFlag(4, false);
                pHome->SetTechLevel(1);
                it = seeds.erase(it);
            } else
                ++it;
        }
    }

    GeneratePass4a();
    CreateEmpires();
    GeneratePass4c();

    for (EmpireSeedMap::iterator it = seeds.begin(); it != seeds.end(); ++it) {
        cEmpire* pEmpire = GetEmpire(it->first);
        pEmpire->mEmpireLevel = (int8_t)(int)it->second.mLevel;
        pEmpire->field_58 = GetEmpireSize(it->second.mSizeIndex);
        int turns = sMathRandom.RandomUint32Uniform(4);
        for (int i = 0; i < turns; ++i)
            SpaceGame()->mpGrowthSim->TakeTurn(it->first);
    }

    for (cStarRecordPtr* it = mPossibleStartLocations.begin(); it != mPossibleStartLocations.end(); ) {
        if (IsValidStartLocation(it->get()))
            ++it;
        else
            it = mPossibleStartLocations.erase(it);
    }
}
