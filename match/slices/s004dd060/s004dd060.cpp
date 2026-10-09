// Slice s004dd060: SP::cSPEditorSpeciesManager::ReloadTuning (8809 bytes, /Od).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// Reloads the species tuning: LoadSpeciesTuning(true), then (once) loads every
// creature ability property list of group 0xdd91ac58 into gCreatureAbilities,
// then walks every archetype property list of group 0x02f98b67 and, for each
// one with a non-zero archetype type (0xb10f785d), fills
// mArchetypes[instanceID] (a retail cSpeciesArchetype, 0x440 bytes) from ~50
// typed properties, 6 float ranges, 27 Vector3 ranges, the origin-distance
// list and three uint32 lists; type-1 archetypes also register their two
// template mappings (0x05e67a40 / 0x05e67a41).
//
// Retail cSpeciesArchetype offsets differ from the 2008 PDB layout (fields
// were inserted), so its fields are named by offset and type.
#include "types.h"
#pragma pack(push, 4)

struct Vector2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector3 { float x, y, z; };

// ---- properties -----------------------------------------------------------

enum PropertyType {
    kPropBool = 1,
    kPropInt32 = 9,
    kPropUInt32 = 10,
    kPropFloat = 13,
    kPropArrayOrDefault = 16   // also accepted by the typed getters
};

struct Property {
    uint32_t pad0[4];
    uint16_t mFlags;            // +0x10
    uint16_t mType;             // +0x12
    void* GetValue();           // 0x00446FF0 (value pointer, array-aware)
    int32_t* GetInt();          // 0x0041E990
    uint32_t* GetUInt();        // 0x0041EA00
};

struct PropertyList {
    virtual int AddRef();                                           // slot 0
    virtual int Release();                                          // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& pOut);         // slot 9  (+0x24)
    virtual Property* FindProperty(uint32_t id);                    // slot 10 (+0x28), never null
};

// eastl::intrusive_ptr<PropertyList>
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() { mpObject = 0; }
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList* get() const { return mpObject; }
    PropertyList** AsParam();                                       // 0x0041D870: release, return &mpObject
    PropertyListPtr& operator=(PropertyList* p);                    // 0x004535D0
};

// PropertyTraits<T>::kDefault: the value returned when a property is missing
// or mistyped (bool 0x015D115D, int32 0x015D1160, uint32 0x015D1164,
// float 0x015D1168).

template<class T> struct PropertyTraits;
template<> struct PropertyTraits<bool> {
    enum { kType = kPropBool };
    static const bool kDefault;
};
template<> struct PropertyTraits<int32_t> {
    enum { kType = kPropInt32 };
    static const int32_t kDefault;
};
template<> struct PropertyTraits<uint32_t> {
    enum { kType = kPropUInt32 };
    static const uint32_t kDefault;
};
template<> struct PropertyTraits<float> {
    enum { kType = kPropFloat };
    static const float kDefault;
};

// Typed property read with a default (no list null-check, as in the original).
template<class T>
__forceinline const T& GetPropertyValue(PropertyList* pList, uint32_t id)
{
    Property* prop = pList->FindProperty(id);
    if (prop->mType == PropertyTraits<T>::kType || prop->mType == kPropArrayOrDefault)
        return *(const T*)prop->GetValue();
    return PropertyTraits<T>::kDefault;
}

inline bool GetPropertyInt32(PropertyList* pList, uint32_t id, int32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropInt32) {
        dst = *prop->GetInt();
        return true;
    }
    return false;
}

inline bool GetPropertyUInt32(PropertyList* pList, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32) {
        dst = *prop->GetUInt();
        return true;
    }
    return false;
}

// Same read, result discarded (no bool temp in the original).
inline void ReadPropertyUInt32(PropertyList* pList, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32)
        dst = *prop->GetUInt();
}

bool GetPropertyAsVector2(PropertyList* p, uint32_t id, Vector2* pOut);                       // 0x006A10C0
bool GetPropertyAsVector2Array(PropertyList* p, uint32_t id, int* pCount, Vector2** ppData);  // 0x006A0920
bool GetPropertyAsUint32Array(PropertyList* p, uint32_t id, int* pCount, uint32_t** ppData);  // 0x006A0840
// Same-TU helpers: a Vector2 property split into two floats (0 when missing),
// and a 1- or 2-element Vector3 array read as a [min,max] range.
bool GetPropertyFloatRange(PropertyList* p, uint32_t id, float* pMin, float* pMax);           // 0x004D1470
bool GetPropertyVector3Range(PropertyList* p, uint32_t id, Vector3* pRange);                  // 0x004D1510
float RandomInRange(const Vector2& range);                                                    // 0x004DF2D0

struct IPropManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppOut);  // slot 11 (+0x2c)
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual bool GetPropertyListIDs(uint32_t groupID, struct UIntVector& result);              // slot 18 (+0x48)
    virtual bool GetAllPropertyListIDs(uint32_t groupID, struct UIntVector& result);           // slot 19 (+0x4c)
};

// ---- containers -----------------------------------------------------------

struct allocator {
    allocator() {}
};

struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
    UIntVector(const allocator& a = allocator());                   // 0x00540470
    ~UIntVector()
    {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p) {}              // trivial element dtors
        DeallocateSelf();
    }
    void DeallocateSelf();                                          // 0x00425990 (VectorBase dtor)
    uint32_t* begin() { return mpBegin; }
    uint32_t* end() { return mpEnd; }
    uint32_t size() { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);                                       // 0x004E0880 (shared instance)
    void push_back(const uint32_t& v);                              // 0x00454860
    uint32_t* erase(uint32_t* first, uint32_t* last);               // 0x004769B0
    void clear() { erase(mpBegin, mpEnd); }
};

struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);                                        // 0x004AFC80
    void push_back(const float& v);                                 // 0x004547F0
    float& operator[](int i) { return mpBegin[i]; }
};

// ---- abilities ------------------------------------------------------------

namespace Simulator {
struct cCreatureAbility {
    void* vptr;
    int mnRefCount;                                                 // +0x04
    uint32_t pad08[(0x13c - 0x08) / 4];
    cCreatureAbility();                                             // 0x004D3760
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                                                  // 0x00453540 RefCountTemplate<int>::Release
};
}
using Simulator::cCreatureAbility;

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) { mpObject = p; if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
};

struct AbilityVector {
    AutoRefCount<cCreatureAbility>* mpBegin;
    AutoRefCount<cCreatureAbility>* mpEnd;
    AutoRefCount<cCreatureAbility>* mpCapacity;
    uint32_t mAllocator;
    bool empty();                                                   // 0x00526430
    void reserve(uint32_t n);                                       // 0x004E0880
    void push_back(const AutoRefCount<cCreatureAbility>& v);        // 0x004E0E80
};
extern AbilityVector gCreatureAbilities;                            // 0x015D9780

void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);                     // 0x00F473A0

namespace SP {
IPropManager* PropertyManager();                                    // 0x0067DE30
bool ReadAbilityData(cCreatureAbility* pAbility, PropertyList* pList);   // 0x004D92B0
namespace { void LoadSpeciesTuning(bool force); }                   // 0x004D2450
}

// ---- object template registries -------------------------------------------

struct IObjectTemplateDB {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual void SetArchetypeTemplate(uint32_t archetypeKey, uint32_t templateID);   // slot 27 (+0x6c)
};

struct cTemplateMapping {
    void SetMapping(uint32_t key, uint32_t value);                  // 0x00610DD0: mMap(+0xf4)[key] = value
};

namespace SP {
IObjectTemplateDB* ObjectTemplateDB();                              // 0x0067CB40
cTemplateMapping* TemplateMapping();                                // 0x0067CB30 (global at 0x015FCC70)
}

// ---- archetypes -----------------------------------------------------------

// Retail SP::cSpeciesArchetype (0x440 bytes).
struct cSpeciesArchetype {
    uint32_t pad00[4];
    uint32_t mArchetypeID;          // +0x010
    uint32_t mQueryID;              // +0x014 (archetype key, overridable by 0xd6828e2f)
    Vector3 mRanges[29][2];         // +0x018 .. +0x2d0, [min,max] Vector3 ranges
    int32_t mType;                  // +0x2d0
    float mFloat_2d4, mFloat_2d8;   // +0x2d4 range
    float mFloat_2dc;
    float mFloat_2e0, mFloat_2e4;   // ranges
    float mFloat_2e8, mFloat_2ec;
    float mFloat_2f0, mFloat_2f4;
    float mFloat_2f8, mFloat_2fc;
    float mFloat_300, mFloat_304;
    float mFloat_308, mFloat_30c, mFloat_310, mFloat_314;
    Vector2 mVec2_318;
    float mFloat_320, mFloat_324, mFloat_328;
    int32_t mInt_32c, mInt_330;
    bool mBool_334;
    float mFloat_338, mFloat_33c, mFloat_340, mFloat_344, mFloat_348;
    float mFloat_34c, mFloat_350, mFloat_354, mFloat_358, mFloat_35c;
    uint32_t pad360;
    float mFloat_364;               // random pick in the 0x748b77b range
    float mFloat_368;
    int32_t mInt_36c, mInt_370;
    Vector2 mVec2_374;
    Vector2 mVec2_37c;
    float mFloat_384;
    bool mBool_388, mBool_389;
    uint32_t mUInt_38c, mUInt_390;
    Vector2 mVec2_394;
    FloatVector mOriginDistances;   // +0x39c
    uint32_t pad3ac;
    UIntVector mUIntList_3b0;       // +0x3b0
    uint32_t pad3c0;
    UIntVector mUIntList_3c4;       // +0x3c4
    uint32_t pad3d4;
    int32_t mInt_3d8;
    UIntVector mUIntList_3dc;       // +0x3dc
    uint32_t pad3ec;
    int32_t mInt_3f0, mInt_3f4, mInt_3f8, mInt_3fc, mInt_400, mInt_404, mInt_408;
    int32_t mInt_40c, mInt_410, mInt_414, mInt_418, mInt_41c, mInt_420;
    uint32_t mUInt_424;
    float mFloat_428, mFloat_42c;
    int32_t mInt_430;
    float mFloat_434;
    int32_t mInt_438;
    PropertyListPtr mpPropertyList; // +0x43c
};

struct ArchetypeMap {
    cSpeciesArchetype& operator[](const uint32_t& key);             // 0x004E0600
};

namespace SP {

struct cSPEditorSpeciesManager {
    uint32_t pad0[0xb0 / 4];
    ArchetypeMap mArchetypes;       // +0xb0
    void ReloadTuning();            // @ 0x004dd060
};

static const uint32_t kAbilityGroupID = 0xdd91ac58;

// @ 0x004dd060
void cSPEditorSpeciesManager::ReloadTuning()
{
    IPropManager* pPropManager = PropertyManager();
    LoadSpeciesTuning(true);

    if (gCreatureAbilities.empty()) {
        UIntVector abilityIDs;
        pPropManager->GetAllPropertyListIDs(kAbilityGroupID, abilityIDs);
        gCreatureAbilities.reserve(abilityIDs.size());

        PropertyListPtr pAbilityProp;
        for (uint32_t* it = abilityIDs.begin(), *itEnd = abilityIDs.end(); it != itEnd; ++it) {
            uint32_t abilityID = *it;
            if (pPropManager->GetPropertyList(abilityID, kAbilityGroupID, pAbilityProp.AsParam())) {
                AutoRefCount<cCreatureAbility> pAbility =
                    new("Simulator/cCreatureAbility", 0, 0, 0, 0) cCreatureAbility();
                if (ReadAbilityData(pAbility.get(), pAbilityProp.get()))
                    gCreatureAbilities.push_back(pAbility);
            }
        }
    }

    const uint32_t kArchetypeGroupID = 0x02f98b67;
    PropertyListPtr pProp;
    UIntVector archetypeIDs;
    pPropManager->GetPropertyListIDs(kArchetypeGroupID, archetypeIDs);
    for (uint32_t* it = archetypeIDs.begin(), *itEnd = archetypeIDs.end(); it != itEnd; ++it) {
        uint32_t instanceID = *it;
        if (pPropManager->GetPropertyList(instanceID, kArchetypeGroupID, pProp.AsParam())) {
            int32_t type;
            if (GetPropertyInt32(pProp.get(), 0xb10f785d, type) && type != 0) {
                cSpeciesArchetype& a = mArchetypes[instanceID];
                a.mpPropertyList = pProp.get();
                a.mArchetypeID = instanceID;
                a.mType = type;
                a.mQueryID = instanceID;
                ReadPropertyUInt32(pProp.get(), 0xd6828e2f, a.mQueryID);

                Vector2 randomRange;
                a.mBool_334 = GetPropertyValue<bool>(pProp.get(), 0x54f1ce40);
                a.mFloat_308 = GetPropertyValue<float>(pProp.get(), 0x24a02634);
                a.mFloat_30c = GetPropertyValue<float>(pProp.get(), 0xcbb8d102);
                a.mFloat_310 = GetPropertyValue<float>(pProp.get(), 0x561c98ac);
                a.mFloat_314 = GetPropertyValue<float>(pProp.get(), 0x21aec90d);
                a.mFloat_320 = GetPropertyValue<float>(pProp.get(), 0xc33386a0);
                a.mFloat_324 = GetPropertyValue<float>(pProp.get(), 0x5b0e0d01);
                a.mFloat_328 = GetPropertyValue<float>(pProp.get(), 0x5fba6ee4);
                a.mInt_32c = GetPropertyValue<int32_t>(pProp.get(), 0xacd16349);
                a.mInt_330 = GetPropertyValue<int32_t>(pProp.get(), 0x7fb8d666);
                a.mFloat_2dc = GetPropertyValue<float>(pProp.get(), 0xc75c3509);
                a.mFloat_338 = GetPropertyValue<float>(pProp.get(), 0x534bafec);
                a.mFloat_33c = GetPropertyValue<float>(pProp.get(), 0x56ebd162);
                a.mFloat_340 = GetPropertyValue<float>(pProp.get(), 0xb8c0a572);
                a.mFloat_344 = GetPropertyValue<float>(pProp.get(), 0xba1f314b);
                a.mFloat_34c = GetPropertyValue<float>(pProp.get(), 0xe95bf2f7);
                a.mFloat_350 = GetPropertyValue<float>(pProp.get(), 0xed65739a);
                a.mFloat_354 = GetPropertyValue<float>(pProp.get(), 0x8c20b411);
                a.mFloat_358 = GetPropertyValue<float>(pProp.get(), 0x23a57cb5);
                a.mFloat_348 = GetPropertyValue<float>(pProp.get(), 0x79b9184b);
                a.mInt_3d8 = GetPropertyValue<int32_t>(pProp.get(), 0x7ade0c40);
                a.mInt_3f0 = GetPropertyValue<int32_t>(pProp.get(), 0x90cb151d);
                a.mInt_3f4 = GetPropertyValue<int32_t>(pProp.get(), 0x690a9b9b);
                a.mInt_3f8 = GetPropertyValue<int32_t>(pProp.get(), 0x2d5624e5);
                a.mInt_3fc = GetPropertyValue<int32_t>(pProp.get(), 0xbb833f5a);
                a.mInt_400 = GetPropertyValue<int32_t>(pProp.get(), 0x04c07d38);
                a.mInt_404 = GetPropertyValue<int32_t>(pProp.get(), 0x2028ad2e);
                a.mInt_408 = GetPropertyValue<int32_t>(pProp.get(), 0xe9caa7e5);
                a.mInt_40c = GetPropertyValue<int32_t>(pProp.get(), 0x8a7f7999);
                a.mInt_410 = GetPropertyValue<int32_t>(pProp.get(), 0xa9de6046);
                a.mInt_414 = GetPropertyValue<int32_t>(pProp.get(), 0xe7548abb);
                a.mInt_418 = GetPropertyValue<int32_t>(pProp.get(), 0x85e8af05);
                a.mInt_41c = GetPropertyValue<int32_t>(pProp.get(), 0x1900d4b3);
                a.mInt_420 = GetPropertyValue<int32_t>(pProp.get(), 0xa1b3a751);
                a.mUInt_424 = GetPropertyValue<uint32_t>(pProp.get(), 0x0dfe5f93);
                a.mFloat_428 = GetPropertyValue<float>(pProp.get(), 0xb1559418);
                a.mFloat_42c = GetPropertyValue<float>(pProp.get(), 0x3e89acc8);
                a.mInt_430 = GetPropertyValue<int32_t>(pProp.get(), 0xb3d796fe);
                a.mFloat_434 = GetPropertyValue<float>(pProp.get(), 0xbf54a4fe);
                a.mInt_438 = GetPropertyValue<int32_t>(pProp.get(), 0x95ceda48);
                GetPropertyAsVector2(pProp.get(), 0x8a3b9858, &a.mVec2_318);
                a.mFloat_35c = GetPropertyValue<float>(pProp.get(), 0xcc8dcb37);
                GetPropertyAsVector2(pProp.get(), 0x748b77b, &randomRange);
                a.mFloat_364 = RandomInRange(randomRange);
                a.mFloat_368 = GetPropertyValue<float>(pProp.get(), 0x12bb0264);
                a.mInt_36c = GetPropertyValue<int32_t>(pProp.get(), 0x84d781ce);
                a.mInt_370 = GetPropertyValue<int32_t>(pProp.get(), 0xf04c3db9);
                GetPropertyAsVector2(pProp.get(), 0x45d1a932, &a.mVec2_374);
                GetPropertyAsVector2(pProp.get(), 0xfe43f720, &a.mVec2_37c);
                a.mFloat_384 = GetPropertyValue<float>(pProp.get(), 0x03b8ce20);
                a.mBool_388 = GetPropertyValue<bool>(pProp.get(), 0xd2125bfe);
                a.mBool_389 = GetPropertyValue<bool>(pProp.get(), 0x299abcff);
                a.mUInt_38c = GetPropertyValue<uint32_t>(pProp.get(), 0x3f5504ec);
                a.mUInt_390 = GetPropertyValue<uint32_t>(pProp.get(), 0xe6c38666);
                GetPropertyAsVector2(pProp.get(), 0x5459d34, &a.mVec2_394);

                GetPropertyFloatRange(pProp.get(), 0xfb40d940, &a.mFloat_300, &a.mFloat_304);
                GetPropertyFloatRange(pProp.get(), 0x012499e3, &a.mFloat_2f0, &a.mFloat_2f4);
                GetPropertyFloatRange(pProp.get(), 0xf51b95cb, &a.mFloat_2f8, &a.mFloat_2fc);
                GetPropertyFloatRange(pProp.get(), 0x00d7e2d7, &a.mFloat_2e8, &a.mFloat_2ec);
                GetPropertyFloatRange(pProp.get(), 0xebc9f3ba, &a.mFloat_2d4, &a.mFloat_2d8);
                GetPropertyFloatRange(pProp.get(), 0x440a932b, &a.mFloat_2e0, &a.mFloat_2e4);

                GetPropertyVector3Range(pProp.get(), 0xe0c5a5c2, a.mRanges[0]);    // +0x018
                GetPropertyVector3Range(pProp.get(), 0x2379984f, a.mRanges[1]);    // +0x030
                GetPropertyVector3Range(pProp.get(), 0x4c47d5c0, a.mRanges[3]);    // +0x060
                GetPropertyVector3Range(pProp.get(), 0xa28a67e8, a.mRanges[9]);    // +0x0f0
                GetPropertyVector3Range(pProp.get(), 0x2dfb4f9f, a.mRanges[10]);   // +0x108
                GetPropertyVector3Range(pProp.get(), 0x172832c8, a.mRanges[8]);    // +0x0d8
                GetPropertyVector3Range(pProp.get(), 0xff890a19, a.mRanges[5]);    // +0x090
                GetPropertyVector3Range(pProp.get(), 0xa9145490, a.mRanges[7]);    // +0x0c0
                GetPropertyVector3Range(pProp.get(), 0x5ec025c8, a.mRanges[6]);    // +0x0a8
                GetPropertyVector3Range(pProp.get(), 0xda893255, a.mRanges[12]);   // +0x138
                GetPropertyVector3Range(pProp.get(), 0x0ac4aeed, a.mRanges[11]);   // +0x120
                GetPropertyVector3Range(pProp.get(), 0xf25e3665, a.mRanges[13]);   // +0x150
                GetPropertyVector3Range(pProp.get(), 0xa49feb7f, a.mRanges[14]);   // +0x168
                GetPropertyVector3Range(pProp.get(), 0xb923d558, a.mRanges[17]);   // +0x1b0
                GetPropertyVector3Range(pProp.get(), 0x0650f110, a.mRanges[18]);   // +0x1c8
                GetPropertyVector3Range(pProp.get(), 0x2772c33e, a.mRanges[19]);   // +0x1e0
                GetPropertyVector3Range(pProp.get(), 0xb600fecc, a.mRanges[20]);   // +0x1f8
                GetPropertyVector3Range(pProp.get(), 0xe6151f13, a.mRanges[21]);   // +0x210
                GetPropertyVector3Range(pProp.get(), 0x0d7389ad, a.mRanges[22]);   // +0x228
                GetPropertyVector3Range(pProp.get(), 0xa5ae7f21, a.mRanges[23]);   // +0x240
                GetPropertyVector3Range(pProp.get(), 0x095be098, a.mRanges[24]);   // +0x258
                GetPropertyVector3Range(pProp.get(), 0xb7dae82b, a.mRanges[25]);   // +0x270
                GetPropertyVector3Range(pProp.get(), 0x5afbcd71, a.mRanges[26]);   // +0x288
                GetPropertyVector3Range(pProp.get(), 0x82b6a8b2, a.mRanges[27]);   // +0x2a0
                GetPropertyVector3Range(pProp.get(), 0x56590eba, a.mRanges[28]);   // +0x2b8
                GetPropertyVector3Range(pProp.get(), 0x07ef4b84, a.mRanges[4]);    // +0x078

                // Origin distances: the 0x5cd03ffa pair first, then every Vector2 of 0xafd5e585.
                float originMin, originMax;
                GetPropertyFloatRange(pProp.get(), 0x5cd03ffa, &originMin, &originMax);
                a.mOriginDistances.resize(2);
                a.mOriginDistances[0] = originMin;
                a.mOriginDistances[1] = originMax;

                int originCount = 0;
                Vector2* originList = 0;
                if (GetPropertyAsVector2Array(pProp.get(), 0xafd5e585, &originCount, &originList)) {
                    for (int i = 0; i < originCount; ++i) {
                        Vector2& v = originList[i];
                        a.mOriginDistances.push_back(v[0]);
                        a.mOriginDistances.push_back(v[1]);
                    }
                }

                int count = 0;
                uint32_t* list = 0;
                if (GetPropertyAsUint32Array(pProp.get(), 0x7ecaf0ee, &count, &list)) {
                    a.mUIntList_3b0.clear();
                    a.mUIntList_3b0.reserve(count);
                    for (int i = 0; i < count; ++i)
                        a.mUIntList_3b0.push_back(list[i]);
                }
                if (GetPropertyAsUint32Array(pProp.get(), 0x536f1c37, &count, &list)) {
                    a.mUIntList_3c4.clear();
                    a.mUIntList_3c4.reserve(count);
                    for (int i = 0; i < count; ++i)
                        a.mUIntList_3c4.push_back(list[i]);
                }
                if (GetPropertyAsUint32Array(pProp.get(), 0x8ecead6d, &count, &list)) {
                    a.mUIntList_3dc.clear();
                    a.mUIntList_3dc.reserve(count);
                    for (int i = 0; i < count; ++i)
                        a.mUIntList_3dc.push_back(list[i]);
                }

                if (a.mType == 1) {
                    uint32_t templateID;
                    if (GetPropertyUInt32(pProp.get(), 0x05e67a40, templateID)) {
                        ObjectTemplateDB()->SetArchetypeTemplate(a.mQueryID, templateID);
                        uint32_t mappedID;
                        if (GetPropertyUInt32(pProp.get(), 0x05e67a41, mappedID))
                            TemplateMapping()->SetMapping(a.mQueryID, mappedID);
                    }
                }
            }
        }
    }
}

} // namespace SP

#pragma pack(pop)
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct H {
    void kDefault();   // 0x015d1160 (equiv t3)
};
struct I {
    void kDefault();   // 0x015d1164 (equiv t3)
};
struct M {
    void kDefault();   // 0x015d1168 (equiv t3)
};
struct _N {
    void kDefault();   // 0x015d115d (equiv t3)
};
}
