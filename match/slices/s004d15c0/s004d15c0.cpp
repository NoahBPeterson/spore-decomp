// Slice s004d15c0: SP::BuildParameters (SPEditorSpeciesManager.obj in the dev build).
// Builds the FunctionalMatch parameter list for a creature summary and, when asked, adds
// one "archetype" parameter per matching species record of the species manager.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc: the smart pointer
// below has a dtor but the original has no EH frame).
#include "types.h"

// Reserves N unused /Od frame dwords (stands in for the frame of an inline helper cl declined).
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace EA { namespace ResourceMan {
struct Key { uint32_t instance; uint32_t type; uint32_t group; };

struct ResourceObject {
    virtual int AddRef();   // +0
    virtual int Release();  // +4
};

struct IResourceManager {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual bool GetResource(const Key& key, ResourceObject** ppOut, int, int, int, int);  // +0xc
};

IResourceManager* GetManager();  // 0x0067dcd0
}}

// Intrusive ref pointer (EA AutoRefCount-style); operator& releases the old object first.
template <class T> struct ResourcePtr {
    T* mpObject;
    ResourcePtr() : mpObject(0) {}
    ~ResourcePtr() { if (mpObject) mpObject->Release(); }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* get() const { return mpObject; }
};

namespace App {
struct Property {
    uint32_t pad0[4];
    uint16_t pad10;
    uint16_t mnType;           // +0x12
    uint32_t* GetValueUInt32();  // 0x0041ea00
};

struct PropertyList {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

inline bool GetUInt32(PropertyList* pList, uint32_t propertyID, uint32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(propertyID, prop) && prop->mnType == 10) {
        ScratchSlots<1>();
        dst = *prop->GetValueUInt32();
        return true;
    }
    return false;
}
}

namespace SP {
bool GetPropertyAsUint32Array(App::PropertyList* pList, uint32_t propertyID, int* pCount, uint32_t** ppValues);  // 0x006a0840

namespace FunctionalMatch {
struct DeclareParam {
    uint32_t mParameter;
    int mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam(uint32_t parameter, float value);  // 0x00558b90
    DeclareParam(uint32_t parameter, int value);    // 0x00558bc0
};
}
}

namespace eastl {
template <class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);        // 0x0041e4d0
    void push_back(const T& value);  // 0x004e19a0
};

template <class Node> struct hashtable_iterator_base {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    void increment_bucket();  // 0x00552750
};

template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    typename Node::value_type* operator->() const { return &this->mpNode->mValue; }
    hashtable_iterator& operator++() { this->increment(); return *this; }
};

template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b)
{
    return a.mpNode != b.mpNode;
}

template <class Node> struct hashtable {
    uint32_t mHashCodeBase;  // empty functor members
    Node** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    typedef hashtable_iterator<Node> iterator;
    iterator begin() {
        iterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
};
}

struct cSPVector3 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
typedef cSPVector3 ParamRange[2];  // per pass: {enabled-if-<eps, min, max}

// Species record held by the species manager's hash_map (value at node+4).
struct cSpeciesRecord {
    uint32_t pad00[5];
    uint32_t mSpeciesKey;  // +0x14
    ParamRange r00, r01, r02, r03, r04, r05, r06, r07, r08, r09;  // +0x18 .. +0x108
    ParamRange r10, r11, r12, r13, r14, r15, r16, r17, r18, r19;  // +0x108 .. +0x1f8
    ParamRange r20, r21, r22, r23, r24, r25, r26, r27, r28;       // +0x1f8 .. +0x2d0
    int mStatus;           // +0x2d0
    uint32_t pad2d4[(0x43c - 0x2d4) / 4];
    App::PropertyList* mpPropList;  // +0x43c
    App::PropertyList* GetPropList() const { return mpPropList; }
};

struct SpeciesNode {
    struct value_type { uint32_t first; cSpeciesRecord second; };
    value_type mValue;
    SpeciesNode* mpNext;  // +0x444
};

struct cSpeciesManager {
    uint32_t pad00[0xb0 / 4];
    eastl::hashtable<SpeciesNode> mSpecies;  // +0xb0
    eastl::hashtable<SpeciesNode>& GetSpecies() { return mSpecies; }
};
cSpeciesManager* GetSpeciesManagerInstance();  // 0x00401090
inline cSpeciesManager* SpeciesManager() { return GetSpeciesManagerInstance(); }

// Creature summary the parameters are read from.
struct cCreatureSummary {
    uint32_t pad000[0x504 / 4];
    EA::ResourceMan::Key mKey;  // +0x504
    uint32_t pad510[(0x540 - 0x510) / 4];
    int m540;  // +0x540
    int m544;
    uint32_t pad548[(0x55c - 0x548) / 4];
    float m55c;  // +0x55c
    uint32_t pad560[(0x57c - 0x560) / 4];
    uint32_t mArchetype;  // +0x57c
    uint32_t pad580[(0x58c - 0x580) / 4];
    float m58c;  // +0x58c
    float m590;
    uint32_t pad594[(0x5a8 - 0x594) / 4];
    float m5a8;  // +0x5a8
    float m5ac;
    float m5b0;
    float m5b4;
    float m5b8;
    float m5bc;
    uint32_t pad5c0[(0x5d4 - 0x5c0) / 4];
    uint32_t m5d4;  // +0x5d4
    uint32_t m5d8;
    uint32_t m5dc;
    uint32_t m5e0;
    uint32_t m5e4;
    uint32_t m5e8;
    uint32_t m5ec;
    uint32_t m5f0;
    uint32_t m5f4;
    uint32_t pad5f8[(0x604 - 0x5f8) / 4];
    uint32_t m604;  // +0x604
    uint32_t m608;
    uint32_t m60c;
    uint32_t pad610;
    uint32_t m614;  // +0x614
    uint32_t m618;
    uint32_t m61c;
};

int FUN_00556140(EA::ResourceMan::Key* pKey, uint32_t id);                           // 0x00556140 (returns an asset pointer or 0)
bool FUN_00556210_Has(EA::ResourceMan::Key* pKey, uint32_t id);                       // 0x00556210
bool FUN_005580e0_Check(EA::ResourceMan::ResourceObject* pDB, uint32_t id, bool b);  // 0x005580e0

using SP::FunctionalMatch::DeclareParam;

const float kParamEpsilon = 1.5258789e-05f;  // 0x013f07bc

namespace SP {
// @ 0x004D15C0  SP::BuildParameters (byte-exact)
// /Od frame notes: local names decide slot order (hash bucket, later-declared first within a
// bucket), so the loop-body locals are declared up front in reverse slot order, and
// ScratchSlots<N> stands in for the frames of inline helpers cl declined.
void BuildParameters(cCreatureSummary* pSummary, eastl::sp_vector<DeclareParam>& params, bool bArchetypes)
{
    params.reserve(params.size() + 9);
    params.push_back(DeclareParam(0x2f05c58, pSummary->m608 > 0 ? 1.0f : 0.0f));
    params.push_back(DeclareParam(0x2f05c59, pSummary->m60c > 0 ? 1.0f : 0.0f));
    params.push_back(DeclareParam(0x3fea1a0, pSummary->m5b0));
    params.push_back(DeclareParam(0x2f05c5f, pSummary->m5ac));

    float values[] = {
        (float)pSummary->m540,
        (float)pSummary->m544,
        pSummary->m55c,
        pSummary->m608 > 0 ? 1.0f : 0.0f,
        pSummary->m60c > 0 ? 1.0f : 0.0f,
        pSummary->m5b0,
        pSummary->m5b4,
        pSummary->m5a8,
        pSummary->m5bc,
        pSummary->m5ac,
        pSummary->m5b8,
        pSummary->m58c,
        pSummary->m590,
        (float)pSummary->m5d4,
        (float)pSummary->m5e0,
        (float)pSummary->m5d8,
        (float)pSummary->m5dc,
        (float)pSummary->m5e4,
        (float)pSummary->m5e8,
        (float)pSummary->m5ec,
        (float)pSummary->m5f0,
        (float)pSummary->m61c,
        (float)pSummary->m5f4,
        (float)pSummary->m614,
        (float)pSummary->m618,
        (float)pSummary->m604,
    };
    const uint32_t numValues = sizeof(values) / sizeof(values[0]);

    if (bArchetypes) {
        EA::ResourceMan::ResourceObject* pDB = 0;
        ScratchSlots<8>();
        eastl::hashtable<SpeciesNode>& species = GetSpeciesManagerInstance()->GetSpecies();
        eastl::hashtable<SpeciesNode>::iterator it = species.begin();
        eastl::hashtable<SpeciesNode>::iterator last = species.end();
        for (; it != last; ++it) {
            uint32_t speciesId = it->first;
            cSpeciesRecord* pEntry = &it->second;
            int archetypeCount;
            bool results[2];
            bool bArchetypeMatch;
            uint32_t numRangeEntries;
            uint32_t* pArchetypeList;
            if (pEntry->mStatus != 1)
                continue;
            if (pEntry->mSpeciesKey != speciesId)
                continue;

            bArchetypeMatch = true;
            archetypeCount = 0;
            pArchetypeList = 0;
            if (SP::GetPropertyAsUint32Array(pEntry->GetPropList(), 0x50437407, &archetypeCount, &pArchetypeList) && archetypeCount > 0) {
                bArchetypeMatch = false;
                for (int i = 0; i < archetypeCount; ++i) {
                    if (pArchetypeList[i] == pSummary->mArchetype) {
                        bArchetypeMatch = true;
                        break;
                    }
                }
            }
            if (!bArchetypeMatch)
                continue;

            cSPVector3* rangePtrs[] = {
                pEntry->r00, pEntry->r01, pEntry->r03, pEntry->r09, pEntry->r10,
                pEntry->r12, pEntry->r11, pEntry->r05, pEntry->r13, pEntry->r07,
                pEntry->r06, pEntry->r14, pEntry->r08, pEntry->r17, pEntry->r18,
                pEntry->r19, pEntry->r20, pEntry->r21, pEntry->r22, pEntry->r23,
                pEntry->r24, pEntry->r25, pEntry->r26, pEntry->r27, pEntry->r28,
                pEntry->r04,
            };
            numRangeEntries = sizeof(rangePtrs) / sizeof(rangePtrs[0]);
            results[0] = true;
            results[1] = true;

            for (uint32_t pass = 0; pass < 2; ++pass) {
                bool& bPass = results[pass];
                for (uint32_t j = 0; bPass && j < numValues; ++j) {
                    float value = values[j];
                    cSPVector3* pRange = rangePtrs[j];
                    if (pRange[pass][0] < kParamEpsilon)
                        bPass = value >= pRange[pass][1] && pRange[pass][2] + kParamEpsilon > value;
                }

                if (bPass) {
                    uint32_t* pKeys = 0;
                    int numKeys;
                    if (SP::GetPropertyAsUint32Array(pEntry->GetPropList(), 0x88ec8f6c, &numKeys, &pKeys) && numKeys > 0) {
                        bPass = false;
                        if ((pSummary->mArchetype == 0x65672ade || pSummary->mArchetype == 0x4178b8e8) &&
                            FUN_00556140(&pSummary->mKey, 0x2db6dad3) == 0) {
                            bPass = true;
                        } else {
                            for (int k = 0; k < numKeys; ++k) {
                                uint32_t key = pKeys[k];
                                if (FUN_00556210_Has(&pSummary->mKey, key)) {
                                    bPass = true;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (bPass) {
                    const uint32_t kDatabaseProp = 0xad8b3088;
                    uint32_t databaseKey;
                    if (App::GetUInt32(pEntry->GetPropList(), kDatabaseProp, databaseKey) && databaseKey != 0) {
                        if (!pDB) {
                            EA::ResourceMan::IResourceManager* pResMgr = EA::ResourceMan::GetManager();
                            ResourcePtr<EA::ResourceMan::ResourceObject> pResource;
                            if (pResMgr->GetResource(pSummary->mKey, &pResource, 0, 0, 0, 0))
                                pDB = pResource.mpObject;
                            ScratchSlots<4>();
                        }
                        bPass = pDB && FUN_005580e0_Check(pDB, databaseKey, true);
                    }
                    break;
                }
            }

            if (results[0])
                params.push_back(DeclareParam(0x52def3f, (int)speciesId));
            else if (results[1])
                params.push_back(DeclareParam(0x52def4b, (int)speciesId));
        }
    }
}
}
