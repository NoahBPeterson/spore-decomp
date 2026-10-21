// src/game/SPBake/SPEditorSpeciesManager.cpp -- migrated from slice(s) s004e01d0, s005beaf0, s004df2d0, s004dc660, s004db6e0, s004db1b0, s004da440, s004da330, s004d92b0, s004d8c10, s004d44e0, s004d34f0, s004d2450, s004d2200, s004d15c0, s004d06e0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorSpeciesManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
#include "game/types.h"
#include "EA/Audio/ConfigurationAggregate.h"
#include "SP/FunctionalMatch/DeclareParam.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Key.h"
#include "eastl/hash_map.h"
#include "cSPVector3.h"
#include "EA/Audio/Group.h"
#include "cSPUIBehaviorValueInterpolator.h"
#include "SP/cCreatureAbility.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cSpeciesCheat.h"
#include "EA/IO/FileStream.h"
#include "EA/ArgScript/cArguments.h"
#include <string.h>
#include <stdlib.h>
#include "SP/cPlantSummarizer.h"
#include "SP/cSpeciesSummarizer.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cSpeciesArchetype.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWin/CustomWindow.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cCollectableItems.h"
#include "cISPUICursorAttachment.h"
#include "SP/cPropertyList.h"
#include "cSPBoundingBox.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "SP/cSPEditorLimbStructure.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorSpine.h"
#include "cSPMatrix3.h"
#include "cSPUIPropertyLayout.h"
#include "cSPUILayout.h"
#include <new>
#include <float.h>
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPEditorBlock.h"
#pragma pack(push, 4)
#pragma pack(pop)

// ---- items of slice s004d06e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector2 {
    float x, y;
    Vector2(const Vector2& v) { x = v.x; y = v.y; }
    float& operator[](int i) { return (&x)[i]; }
};
struct cSkinPaintEntry { const Vector2& GetUV(); };                 // 0x004E1A20
struct cSkinPaintTable {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual bool HasEntry(uint32_t id);                              // 0x1c
    virtual void _v20(); virtual void _v24();
    virtual cSkinPaintEntry* GetEntry(uint32_t id);                  // 0x28
};
// ---- items of slice s004d06e0 end

// ---- items of slice s004d15c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ResourceMan {
struct Key_s004d_15c0 { uint32_t instance; uint32_t type; uint32_t group; };
}
}
namespace EA {
namespace ResourceMan {
struct ResourceObject {
    virtual int AddRef();   // +0
    virtual int Release();  // +4
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceManager {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual bool GetResource(const Key_s004d_15c0& key, ResourceObject** ppOut, int, int, int, int);  // +0xc
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();  // 0x0067dcd0
}
}
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
}
namespace App {
struct PropertyList {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};
}
namespace App {
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
}
namespace SP {
namespace FunctionalMatch {
struct DeclareParam_s004d_15c0 {
    uint32_t mParameter;
    int mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam_s004d_15c0(uint32_t parameter, float value);  // 0x00558b90
    DeclareParam_s004d_15c0(uint32_t parameter, int value);    // 0x00558bc0
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
}
namespace eastl {
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
}
namespace eastl {
template <class Node> struct hashtable_iterator : public hashtable_iterator_base<Node> {
    hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base<Node>(pNode, pBucket) {}
    hashtable_iterator(Node** pBucket) : hashtable_iterator_base<Node>(*pBucket, pBucket) {}
    typename Node::value_type* operator->() const { return &this->mpNode->mValue; }
    hashtable_iterator& operator++() { this->increment(); return *this; }
};
}
namespace eastl {
template <class Node> inline bool operator!=(const hashtable_iterator_base<Node>& a, const hashtable_iterator_base<Node>& b)
{
    return a.mpNode != b.mpNode;
}
}
namespace eastl {
template <class Node> struct hashtable_s004d_15c0 {
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
struct cSPVector3_s004d_15c0 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
typedef cSPVector3_s004d_15c0 ParamRange[2];  // per pass: {enabled-if-<eps, min, max}
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
    eastl::hashtable_s004d_15c0<SpeciesNode> mSpecies;  // +0xb0
    eastl::hashtable_s004d_15c0<SpeciesNode>& GetSpecies() { return mSpecies; }
};
cSpeciesManager* GetSpeciesManagerInstance();  // 0x00401090
struct cCreatureSummary {
    uint32_t pad000[0x504 / 4];
    EA::ResourceMan::Key_s004d_15c0 mKey;  // +0x504
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
int FUN_00556140(EA::ResourceMan::Key_s004d_15c0* pKey, uint32_t id);                           // 0x00556140 (returns an asset pointer or 0)
bool FUN_00556210_Has(EA::ResourceMan::Key_s004d_15c0* pKey, uint32_t id);                       // 0x00556210
bool FUN_005580e0_Check(EA::ResourceMan::ResourceObject* pDB, uint32_t id, bool b);  // 0x005580e0
using SP::FunctionalMatch::DeclareParam_s004d_15c0;
const float kParamEpsilon = 1.5258789e-05f;  // 0x013f07bc
// ---- items of slice s004d15c0 end

// ---- items of slice s004d2450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool sSpeciesTuningLoaded;           // 0x015D9C48
extern uint32_t sTuning_15d9674;            // 0x1368995d
extern uint32_t sTuning_15d9670;            // 0xd8f99173
extern uint32_t sTuning_150c884;            // 0x7717409a (seconds -> ms)
extern float sTuning_150c888;               // 0x11074696
extern float sTuning_150c88c;               // 0x61ecd45c
extern float sTuning_15d9650;               // 0x518ea467
extern float sTuning_15d9654;               // 0x518ea466
extern float sTuning_15d9658;               // 0x518ea465
extern float sTuning_15d965c;               // 0x518ea464
extern float sTuning_15d9660;               // 0x518ea463
extern float sTuning_15d9664;               // 0x518ea462
extern float sTuning_150c900;               // 0xd899bec5
extern float sTuning_15d96b8;               // 0x4745de1b
extern float sTuning_150c890;               // 0x57634c7c
extern float sTuning_150c894;               // 0x57634c7d
extern float sTuning_150c898;               // 0x57634c7e
extern float sTuning_150c89c;               // 0x57634c7f
extern float sTuning_150c8a0;               // 0x57634c78
extern float sTuning_150c8a4;               // 0x57634c79
extern float sTuning_150c8a8;               // 0x57634c7a
extern float sTuning_150c8ac;               // 0xb6ec210b
extern float sTuning_150c8b0;               // 0x71c653b2
extern float sTuning_150c8b4;               // 0xffb2d688
extern float sTuning_150c8b8;               // 0x49c7436e
extern float sTuning_150c8bc;               // 0x0a97c583
extern float sTuning_150c8c0;               // 0x6b559718
extern uint32_t sTuning_150c8c4;            // 0x24cb8070
extern float sTuning_15d9668;               // 0xd237f426
extern bool sTuning_15d966c;                // 0x32380e2c
extern uint32_t sTuning_150c8c8;            // 0x523a8f4c
extern float sTuning_150c8cc;               // 0x036ad4db
extern float sTuning_150c8d4;               // 0xbf623956
extern float sTuning_150c8e4;               // 0xa597b8c1
extern float sTuning_150c8e8;               // 0xa597b8c0
extern float sTuning_150c8ec;               // 0xa597b8c3
extern float sTuning_150c8f0;               // 0xa597b8c2
extern float sTuning_150c8f4;               // 0xa597b8c5
extern float sTuning_150c8f8;               // 0xa597b8c4
extern float sTuning_150c8fc;               // 0xa597b8c7
extern float sTuning_150c8d0;               // 0x81275d0a
extern uint32_t sTuning_150c8d8;            // 0x32ca0de1 (seconds -> ms)
extern float sTuning_150c8dc;               // 0x3e7cf53b
extern uint32_t sTuning_150c8e0;            // 0x0435d996 (seconds -> ms)
extern float sTuning_150c904;               // 0x5c74d18b
struct Vector2_s004d_2450 { float x, y; };
struct Vector3 { float x, y, z; };
enum PropertyType {
    kPropBool = 1,
    kPropUInt32 = 10,
    kPropFloat = 13
};
struct Property_s004d_2450 {
    uint32_t pad0[4];
    uint16_t mFlags;            // +0x10
    uint16_t mType;             // +0x12
    bool* GetBool();            // 0x0041E920
    uint32_t* GetUInt();        // 0x0041EA00
    float* GetFloat();          // 0x0041EA70
};
struct PropertyList_s004d_2450 {
    virtual int AddRef();                                           // slot 0
    virtual int Release();                                          // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004d_2450*& pOut);         // slot 9  (+0x24)
};
struct PropertyListPtr {
    PropertyList_s004d_2450* mpObject;
    PropertyListPtr() { mpObject = 0; }
    ~PropertyListPtr();                                             // 0x004A9B10
    PropertyList_s004d_2450* get() const { return mpObject; }
    void** AsPPVoidParam();                                         // 0x0041D870: release, return &mpObject
    PropertyList_s004d_2450** AsPPTypeParam() { return (PropertyList_s004d_2450**)AsPPVoidParam(); }
};
struct IPropManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyList_s004d_2450** ppOut);  // slot 12 (+0x30)
};
inline void ReadPropertyUInt32(PropertyList_s004d_2450* pList, uint32_t id, uint32_t& dst)
{
    Property_s004d_2450* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32)
        dst = *prop->GetUInt();
}
inline void ReadPropertyFloat(PropertyList_s004d_2450* pList, uint32_t id, float& dst)
{
    Property_s004d_2450* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropFloat)
        dst = *prop->GetFloat();
}
inline void ReadPropertyBool(PropertyList_s004d_2450* pList, uint32_t id, bool& dst)
{
    Property_s004d_2450* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropBool)
        dst = *prop->GetBool();
}
namespace SP {
IPropManager* PropertyManager();                                                        // 0x0067DE30
}
namespace SP {
bool GetPropertyAsFloat(PropertyList_s004d_2450* p, uint32_t id, float* pOut);                     // 0x0040CF10
}
namespace SP {
bool GetPropertyAsUint32(PropertyList_s004d_2450* p, uint32_t id, uint32_t* pOut);                 // 0x004AF210
}
namespace SP {
bool GetPropertyAsVector2(PropertyList_s004d_2450* p, uint32_t id, Vector2_s004d_2450* pOut);                 // 0x006A10C0
}
namespace SP {
bool GetPropertyAsFloatArray(PropertyList_s004d_2450* p, uint32_t id, int* pCount, float** ppData);      // 0x006A08B0
}
namespace SP {
bool GetPropertyAsVector3Array(PropertyList_s004d_2450* p, uint32_t id, int* pCount, Vector3** ppData);  // 0x006A0AE0
}
struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);                                        // 0x004AFC80
};
struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);                                        // 0x004548D0
};
extern Vector2_s004d_2450 sTuning_15d9834;             // 0xb237e271
extern Vector2_s004d_2450 sTuning_15d9764;             // 0xf237e2d7
extern Vector2_s004d_2450 sTuning_15d9a68;             // 0x5237e2d8
extern Vector2_s004d_2450 sTuning_15d992c;             // 0x036ad587
extern FloatVector sTuning_15d976c;         // 0x0610d73b
extern Vector3Vector sTuning_15d96fc;       // 0x53d75041
extern Vector3Vector sTuning_15d99fc;       // 0xf3d75063
extern Vector3Vector sTuning_15d97fc;       // 0x33f6c3c4
// ---- items of slice s004d2450 end

// ---- items of slice s004d34f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;
extern wchar_t gEmptyWStr[2];   // 0x01667bac
void LoadSpeciesTuning(uint32_t which);
struct TuningObj {
    char pad0[0x48];
    int   mBegin;      // +0x48
    int   mEnd;        // +0x4c
    char pad50[0x20];  // up to +0x70
    int   m70;         // +0x70
    int   m74;         // +0x74
    char pad78[0x134 - 0x78];
    float mMin;        // +0x134
    float mMax;        // +0x138

    uint32_t GetAt(uint32_t index);
    int      GetActive();
    float    GetBound(bool which);
    void     SetBounds(float lo, float hi);
};
template<int N> inline void ScratchSlots_s004d_34f0() { uint32_t s[N]; }
struct MapNode { uint32_t key; uint32_t v[5]; MapNode* next; };
struct MapIter {
    MapNode* mpNode; MapNode** mpBucket;
    MapIter(MapNode** p) { MapNode* t = *p; mpNode = t; mpBucket = p; }
    bool operator!=(const MapIter& o) const { return mpNode != o.mpNode; }
};
struct SpeciesMap {
    char pad0[4];
    MapNode** mpBuckets; // +4
    uint32_t mCount;  // +8
    MapIter find(const uint32_t& k);
    MapIter end() { ScratchSlots_s004d_34f0<12>(); return MapIter(mpBuckets + mCount); }
};
struct MapDefault { uint32_t a,b,c; float d,e; MapDefault(){ a=0; b=0; c=0; d=kOne; e=kOne; } };
template<class T> struct AbVec {
    T* b; T* e; T* c; uint32_t alloc[2];
    AbVec() { b = 0; e = 0; c = 0; }
    void Free();
    ~AbVec() { ScratchSlots_s004d_34f0<3>(); for (T* p = b; p < e; ++p) {} Free(); }
};
struct AbStr { char pad[0x14]; AbStr(); ~AbStr(); };
struct AbIObj { virtual void AddRef(); virtual void Release(); };
struct AbSmartPtr { AbIObj* p; AbSmartPtr() { p = 0; if (p) p->AddRef(); } ~AbSmartPtr() { if (p) p->Release(); } };
struct AbKey { uint32_t instanceID, typeID, groupID; AbKey() { ScratchSlots_s004d_34f0<2>(); instanceID = 0; typeID = 0; groupID = 0; } };
struct CreatureAbilityBase { int field04; CreatureAbilityBase() { field04 = 0; } virtual ~CreatureAbilityBase() {} virtual void a(); virtual void b(); };
struct CreatureAbility : CreatureAbilityBase {
    int mType, mCategory, mSocialCategory;
    AbStr nName;                       // 0x14
    uint32_t mVerbIconImageID;       // 0x28
    AbKey mVerbIconGameLayout;         // 0x2c
    uint32_t mVerbIconTriggerKey;    // 0x38
    float mDamage, mRangedDamage, mRazeDamage; // 0x3c
    AbVec<uint32_t> mAnimationIDs;     // 0x48
    AbVec<uint32_t> mFollowerAnimationIDs; // 0x5c
    uint32_t mVerbIconRepresentativeAnimation, mBabyGameAnimationID, mBuildingSpecificAnimationID, mEffectKind; // 0x70
    float mEffectDuration, mEffectDamage;   // 0x80
    uint32_t mMuzzleEffectID, mTrailEffectID, mImpactEffectID; // 0x88
    float mConeDist, mConeRadius, mRefresh, mDuration, mRecharge, mRange, mEnergyCost, mSpeed; // 0x94
    int mSpeedGear;                  // 0xb4
    AbVec<uint32_t> mCombatEffectTypes; // 0xb8
    AbVec<float> mCombatEffectPercentages; // 0xcc
    AbVec<uint32_t> mCombatEffectEffectIds; // 0xe0
    float mRushingRange; uint32_t mRushingAnimationID; float mRushingSpeed; // 0xf4
    bool mbRushingTargetedCharge, mbRushingDoDamage; // 0x100
    float mAdventurerEnergyCost; int mSprintBuff; float mDNAPoints, mLevelMultiplier; // 0x104
    bool mbIsSpecial, mbUseForBabyGame; // 0x114
    uint32_t mHintName; float mAreaOfEffect; // 0x118
    uint32_t mReactionAnimation, mReactionDeathAnimation, mReactionLiveAnimation; // 0x120
    float mReactionDuration;         // 0x12c
    AbSmartPtr mpPropList;             // 0x130
    float mRangeMin, mAvatarRangeMin; // 0x134
    CreatureAbility();
    ~CreatureAbility();
    virtual void a(); virtual void b();
};
struct CapsTag1 { bool c; CapsTag1() { c = false; } };
struct CapsTag2 { CapsTag2() {} };
struct CapsMap {
    char data[0x4e0];
    CapsMap(const CapsTag1&, const CapsTag2&);   // 0x004e0370
};
struct ColorRGB { float r, g, b; ColorRGB() { ScratchSlots_s004d_34f0<7>(); } };
struct ResKey { uint32_t instanceID, typeID; int groupID; ResKey() { instanceID = 0; typeID = 0; groupID = 0; } };
struct ProfWStr { wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc;
    ProfWStr() { b = 0; e = 0; c = 0; b = gEmptyWStr; e = b; c = b + 1; } };
struct ProfVec3 { uint32_t* b; uint32_t* e; uint32_t* c; ProfVec3() { b = 0; e = 0; c = 0; } };
struct ProfObjA {
    uint32_t d[0x1a];
    ProfObjA();   // 0x004e0500
};
struct SubTag { SubTag() {} };
struct ObjAB {
    uint32_t d[0x1a];
    void SubInit(const SubTag&);   // 0x00540470
    void Init();                   // 0x004e07d0
    ObjAB() { SubTag t; SubInit(t); Init(); }
};
void BadModelKey(ResKey* k, int n);   // 0x0068c700
inline bool IsEditorGroup(uint32_t g) { return ((g >> 30) & 3) == 1; }
struct cSpeciesProfile {
    CapsMap capsInfos;               // 0x0
    ColorRGB mSkinColors[3];            // 0x4e0
    ResKey animatedCreatureKey;         // 0x504
    ResKey animatedBabyKey;             // 0x510
    ProfWStr animatedCreatureName;       // 0x51c
    ProfWStr animatedCreatureDesc;       // 0x52c
    uint32_t m53c;
    uint32_t m540;
    uint32_t m544;
    float m548;
    float m54c;
    float m550;
    char pad554[0x18];
    float m56c;
    float m570;
    float m574;
    bool m578;
    char pad579[0x3];
    uint32_t m57c;
    char pad580[0x8];
    uint32_t m588;
    float m58c;
    float m590;
    float m594;
    float m598;
    float m59c;
    float m5a0;
    float m5a4;
    float m5a8;
    float m5ac;
    float m5b0;
    float m5b4;
    float m5b8;
    float m5bc;
    float m5c0;
    float m5c4;
    uint32_t m5c8;
    float m5cc;
    uint32_t m5d0;
    uint32_t m5d4;
    uint32_t m5d8;
    uint32_t m5dc;
    uint32_t m5e0;
    uint32_t m5e4;
    uint32_t m5e8;
    uint32_t m5ec;
    uint32_t m5f0;
    char pad5f4[0x4];
    uint32_t m5f8;
    uint32_t m5fc;
    uint32_t m600;
    uint32_t m604;
    uint32_t m608;
    uint32_t m60c;
    uint32_t m610;
    uint32_t m614;
    char pad618[0x4];
    uint32_t m61c;
    char pad620[0x20];
    float m640;
    char pad644[0x4];
    uint32_t m648;
    uint32_t m64c;
    uint32_t m650;
    uint32_t m654;
    uint32_t m658;
    uint32_t m65c;
    uint32_t m660;
    uint32_t m664;
    uint32_t m668;
    float m66c;
    uint32_t m670;
    uint32_t m674;
    uint32_t m678;
    uint32_t m67c;
    uint32_t m680;
    uint32_t m684;
    uint32_t m688;
    uint32_t m68c;
    uint32_t m690;
    uint32_t m694;
    uint32_t m698;
    uint32_t m69c;
    uint32_t m6a0;
    uint32_t m6a4;
    uint32_t m6a8;
    uint32_t m6ac;
    float m6b0;
    uint32_t m6b4;
    ProfVec3 m6b8;                      // 0x6b8
    char pad6c4[8];
    bool m6cc;
    uint32_t m6d0;
    ObjAB m6d4;
    ObjAB m73c;
    ProfObjA m7a4;
    bool m80c, m80d;
    ProfObjA m810, m878, m8e0, m948, m9b0;
    cSpeciesProfile(const ResKey& key, bool flag);
};
// ---- items of slice s004d34f0 end

// ---- items of slice s004d44e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SpeciesDB {
    char  pad0[0x5ac];
    float mScale;      // +0x5ac
    char  pad2[0x6d4 - 0x5b0];
    int   mVecBegin;   // +0x6d4
    int   mVecEnd;     // +0x6d8

    float GetScale();
    uint32_t FindField8(int id);
    uint32_t FindField10(int id);
};
// ---- items of slice s004d44e0 end

// ---- items of slice s004d8c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SpeciesProfile {
    char pad0[0x17c];
    int* m17c;            // +0x17c (pointer whose target holds +0x31c)
    char pad2[0x518 - 0x180];
    int  mSelector;       // +0x518
    char pad3[0x9b4 - 0x51c];

    void Update(void* p, int flag);   // 0x004d8c10

    int GetVariantA(void* p);
    int GetVariantB(void* p);
    int GetVariantC(void* p);
};
// ---- items of slice s004d8c10 end

// ---- items of slice s004d92b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
enum PropertyType_s004d_92b0 {
    kPropBool_s004d_92b0 = 1,
    kPropInt32 = 9,
    kPropUInt32_s004d_92b0 = 10,
    kPropFloat_s004d_92b0 = 13
};
struct Property_s004d_92b0 {
    uint32_t pad0[4];
    uint16_t mFlags;              // +0x10
    uint16_t mType;               // +0x12
    int32_t* GetInt();            // 0x0041E990
    uint32_t* GetUInt();          // 0x0041EA00
    float* GetFloat();            // 0x0041EA70
    float* GetFloatValue();       // 0x004E4230 (untyped access)
    bool* GetBoolValue();         // 0x004E42A0 (untyped access)
};
struct PropertyList_s004d_92b0 {
    virtual int AddRef();                                           // slot 0
    virtual int Release();                                          // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                          // slot 7  (+0x1c)
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004d_92b0*& pOut);         // slot 9  (+0x24)
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct LocalizedString {
    uint32_t pad[5];
};
bool GetPropertyAsText(PropertyList_s004d_92b0* p, uint32_t id, LocalizedString* pOut);                      // 0x006A1360
bool GetPropertyAsKey(PropertyList_s004d_92b0* p, uint32_t id, ResourceKey* pOut);                          // 0x006A1250
bool GetPropertyAsKeyInstance(PropertyList_s004d_92b0* p, uint32_t id, uint32_t* pOut);                     // 0x006A12A0
bool GetPropertyAsUint32Array(PropertyList_s004d_92b0* p, uint32_t id, int* pCount, uint32_t** ppData);     // 0x006A0840
bool GetPropertyAsFloatArray(PropertyList_s004d_92b0* p, uint32_t id, int* pCount, float** ppData);         // 0x006A08B0
bool GetPropertyAsFloat(PropertyList_s004d_92b0* p, uint32_t id, float* pOut);                              // 0x0040CF10
bool GetPropertyAsBool(PropertyList_s004d_92b0* p, uint32_t id, bool* pOut);                                // 0x00407190
bool GetPropertyAsUint32(PropertyList_s004d_92b0* p, uint32_t id, uint32_t* pOut);                          // 0x004AF210
inline void GetInt32(PropertyList_s004d_92b0* pList, uint32_t id, int& dst)
{
    Property_s004d_92b0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropInt32)
        dst = *prop->GetInt();
}
inline void GetUInt32_s004d_92b0(PropertyList_s004d_92b0* pList, uint32_t id, uint32_t& dst)
{
    Property_s004d_92b0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32_s004d_92b0)
        dst = *prop->GetUInt();
}
inline void GetFloat(PropertyList_s004d_92b0* pList, uint32_t id, float& dst)
{
    Property_s004d_92b0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropFloat_s004d_92b0)
        dst = *prop->GetFloat();
}
inline bool GetBoolValue(PropertyList_s004d_92b0* pList, uint32_t id)
{
    bool bValue;
    Property_s004d_92b0* prop;
    if (pList && pList->GetProperty(id, prop))
        bValue = *prop->GetBoolValue();
    else
        bValue = false;
    return bValue;
}
inline float GetFloatValue(PropertyList_s004d_92b0* pList, uint32_t id, float defaultValue)
{
    float bValue;
    Property_s004d_92b0* prop;
    if (pList && pList->GetProperty(id, prop))
        bValue = *prop->GetFloatValue();
    else
        bValue = defaultValue;
    return bValue;
}
__forceinline float Max(float value, float minValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        movss value, xmm0
    }
    return value;
}
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t* erase(uint32_t* first, uint32_t* last);   // 0x004769B0
    void reserve(uint32_t n);                           // 0x004E0880
    void push_back(const uint32_t& value);              // 0x00454860
    void resize(uint32_t n);                            // 0x004CD3C0
    void clear() { erase(mpBegin, mpEnd); }
    uint32_t& operator[](int i) { return mpBegin[i]; }
};
struct FloatVector_s004d_92b0 {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32_t mAllocator[2];
    void resize(uint32_t n);                            // 0x004AFC80
    float& operator[](int i) { return mpBegin[i]; }
};
struct cCreatureAbility_s004d_92b0 {
    void* vftable;                                // +0x00
    int mnRefCount;                               // +0x04
    int mType;                                    // +0x08
    int mCategory;                                // +0x0c
    int mSocialCategory;                          // +0x10
    LocalizedString mName;                        // +0x14
    uint32_t mVerbIconImageID;                    // +0x28
    ResourceKey mVerbIconGameLayout;              // +0x2c
    int mVerbIconTriggerKey;                      // +0x38
    float mDamage;                                // +0x3c
    float mRangedDamage;                          // +0x40
    float mRazeDamage;                            // +0x44
    UIntVector mAnimationIDs;                     // +0x48
    UIntVector mFollowerAnimationIDs;             // +0x5c
    uint32_t mVerbIconRepresentativeAnimation;    // +0x70
    uint32_t mBabyGameAnimationID;                // +0x74
    uint32_t mBuildingSpecificAnimationID;        // +0x78
    int mEffectKind;                              // +0x7c
    float mEffectDuration;                        // +0x80
    float mEffectDamage;                          // +0x84
    uint32_t mMuzzleEffectID;                     // +0x88
    uint32_t mTrailEffectID;                      // +0x8c
    uint32_t mImpactEffectID;                     // +0x90
    float mConeDist;                              // +0x94
    float mConeRadius;                            // +0x98
    float mRefresh;                               // +0x9c
    float mDuration;                              // +0xa0
    float mRecharge;                              // +0xa4
    float mRange;                                 // +0xa8
    float mEnergyCost;                            // +0xac
    float mSpeed;                                 // +0xb0
    uint32_t mSpeedGear;                          // +0xb4
    UIntVector mCombatEffectTypes;                // +0xb8
    FloatVector_s004d_92b0 mCombatEffectPercentages;         // +0xcc
    UIntVector mCombatEffectEffectIds;            // +0xe0
    float mRushingRange;                          // +0xf4
    uint32_t mRushingAnimationID;                 // +0xf8
    float mRushingSpeed;                          // +0xfc
    bool mbRushingTargetedCharge;                 // +0x100
    bool mbRushingDoDamage;                       // +0x101
    float mAdventurerEnergyCost;                  // +0x104
    int mSprintBuff;                              // +0x108
    float mDNAPoints;                             // +0x10c
    float mLevelMultiplier;                       // +0x110
    bool mbIsSpecial;                             // +0x114
    bool mbUseForBabyGame;                        // +0x115
    uint32_t mHintName;                           // +0x118
    float mAreaOfEffect;                          // +0x11c
    uint32_t mReactionAnimation;                  // +0x120
    uint32_t mReactionDeathAnimation;             // +0x124
    uint32_t mReactionLiveAnimation;              // +0x128
    float mReactionDuration;                      // +0x12c
    AutoRefCount<PropertyList_s004d_92b0> mpPropList;        // +0x130
    float mRangeMin;                              // +0x134
    float mAvatarRangeMin;                        // +0x138

    void SetRangeMin(float rangeMin, float avatarRangeMin);   // 0x004D3DA0
};
// ---- items of slice s004d92b0 end

// ---- items of slice s004da330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t kCreatureEditorModelGroup;   // 0x015d97ac
extern uint32_t kFloraEditorModelGroup;      // 0x015d9760
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void sprintf(const wchar_t* fmt, ...);                    // 0x0041e050
    bool empty() const { return mpBegin == mpEnd; }
};
struct cSpeciesProfile_s004d_a330 {
    char    pad0[0x504];
    int     mInstance;   // +0x504
    char    pad1[0x51c - 0x508];
    WString mName;       // +0x51c
    void GetUiName(WString* out);  // 0x004da330 (cSpeciesProfile::GetUiName)
};
// ---- items of slice s004da330 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void ResourceManager(uint32_t param);  // 0x004da3a0 (stays in the slice: not this object's)

// ---- items of slice s004da440 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPVector3
{
	float x, y, z;
	cSPVector3() {}
};
}
namespace SP {
struct cSPVector2
{
	float x, y;
	cSPVector2(float _x, float _y) : x(_x), y(_y) {}
};
}
namespace SP {
static const float kMaxFloat = 3.402823466e+38F;   // FLT_MAX (named constant: /Od copies it into the inline ctor's params)
}
namespace SP {
extern wchar_t gEmptyWString[];                 // 0x01667BAC (eastl empty-string sentinel)
}
namespace SP {
struct SpAllocatorTag { SpAllocatorTag() {} };
}
namespace SP {
struct StringAllocator
{
	explicit StringAllocator(const SpAllocatorTag&) {}
	uint32_t mData;
};
}
namespace SP {
struct WString_s004d_a440
{
	wchar_t* mpBegin;
	wchar_t* mpEnd;
	wchar_t* mpCapacity;
	StringAllocator mAllocator;
	explicit WString_s004d_a440(const SpAllocatorTag& tag) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag)
	{
		mpBegin = gEmptyWString;
		mpEnd = mpBegin;
		mpCapacity = mpBegin + 1;
	}
};
}
namespace SP {
struct SpVectorAllocator
{
	SpVectorAllocator(const SpAllocatorTag& tag);   // 0x00429360
	uint32_t mData[2];
};
}
namespace SP {
template <class T>
struct SpVector                                 // eastl::vector<T, eastl::sp_vector_allocator>, 0x14 bytes
{
	T* mpBegin;
	T* mpEnd;
	T* mpCapacity;
	SpVectorAllocator mAllocator;
	explicit SpVector(const SpAllocatorTag& tag) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag) {}
};
}
namespace SP {
class cPropertyList_s004d_a440;
}
namespace SP {
template <class T>
struct AutoRefCount_s004d_a440
{
	T* mpObject;
	AutoRefCount_s004d_a440() : mpObject(0) {}
};
}
namespace SP {
class cSpeciesArchetype_s004d_a440
{
public:
	cSpeciesArchetype_s004d_a440();

	WString_s004d_a440 debugName;                          // +0x00
	unsigned int archetypeID;                   // +0x10
	unsigned int archetypeQueryID;              // +0x14
	cSPVector3 costRange[2];                    // +0x18
	cSPVector3 baseGear[2];                     // +0x30
	cSPVector3 mass[2];                         // +0x48
	cSPVector3 height[2];                       // +0x60
	cSPVector3 health[2];                       // +0x78
	cSPVector3 cuteness[2];                     // +0x90
	cSPVector3 social[2];                       // +0xa8
	cSPVector3 totalSocial[2];                  // +0xc0
	cSPVector3 numGraspers[2];                  // +0xd8
	cSPVector3 carnivore[2];                    // +0xf0
	cSPVector3 herbivore[2];                    // +0x108
	cSPVector3 attack[2];                       // +0x120
	cSPVector3 totalAttack[2];                  // +0x138
	cSPVector3 meanLooking[2];                  // +0x150
	cSPVector3 numFeet[2];                      // +0x168
	cSPVector3 maxPartLevel[2];                 // +0x180
	cSPVector3 averagePartLevel[2];             // +0x198
	cSPVector3 biteCapRange[2];                 // +0x1b0
	cSPVector3 strikeCapRange[2];               // +0x1c8
	cSPVector3 chargeCapRange[2];               // +0x1e0
	cSPVector3 spitCapRange[2];                 // +0x1f8
	cSPVector3 singCapRange[2];                 // +0x210
	cSPVector3 danceCapRange[2];                // +0x228
	cSPVector3 gestureCapRange[2];              // +0x240
	cSPVector3 postureCapRange[2];              // +0x258
	cSPVector3 glideCapRange[2];                // +0x270
	cSPVector3 stealthCapRange[2];              // +0x288
	cSPVector3 sprintCapRange[2];               // +0x2a0
	cSPVector3 senseCapRange[2];                // +0x2b8 (retail, name guessed from the cheat's -senseCapRange)
	unsigned int modelType;                     // +0x2d0
	float slopeMin;                             // +0x2d4
	float slopeMax;                             // +0x2d8
	float slopeArea;                            // +0x2dc
	float altitudeMin;                          // +0x2e0
	float altitudeMax;                          // +0x2e4
	float waterDistanceMin;                     // +0x2e8
	float waterDistanceMax;                     // +0x2ec
	float numCreaturesMin;                      // +0x2f0
	float numCreaturesMax;                      // +0x2f4
	float creatureShortfallMin;                 // +0x2f8
	float creatureShortfallMax;                 // +0x2fc
	float numNestsMin;                          // +0x300
	float numNestsMax;                          // +0x304
	float exclusiveAreaRadiusGroupSmall;        // +0x308
	float exclusiveAreaRadiusGroupMedium;       // +0x30c
	float exclusiveAreaRadiusGroupLarge;        // +0x310
	float respawnRate;                          // +0x314
	cSPVector2 dnaPointsEvolutionThresholds;    // +0x318
	float evoPointsRewarded;                    // +0x320
	float evoPointsRewardedSocial;              // +0x324
	float evoPointsRewardedOther;               // +0x328 (retail, name guessed)
	int partUnlockLevelReward;                  // +0x32c
	int foodChainLevel;                         // +0x330
	bool bUseOrigin;                            // +0x334
	bool bAvatarRelative;                       // +0x335 (not initialized by the constructor)
	float scaleMultiplier;                      // +0x338
	float overrideHeight;                       // +0x33c
	float hitpointOverride;                     // +0x340
	float damageMultiplier;                     // +0x344
	float socialPower;                          // +0x348
	float baseSightRadius;                      // +0x34c
	float baseSightAngle;                       // +0x350
	float basePerceptionRadius;                 // +0x354
	float abilityPerceptionMultiplier;          // +0x358
	float territoryRadius;                      // +0x35c
	float percentGuards;                        // +0x360
	float percentBabies;                        // +0x364
	float foodValue;                            // +0x368
	int numGuardLocations;                      // +0x36c
	int guardsPerLocation;                      // +0x370
	cSPVector2 guardLocationRadiusRange;        // +0x374
	cSPVector2 guardPositionDurationRange;      // +0x37c
	float guardLocationAreaBuffer;              // +0x384
	bool bIsEpic;                               // +0x388
	bool bIsMiniBoss;                           // +0x389 (not initialized by the constructor)
	unsigned int defaultPersonality;            // +0x38c
	unsigned int initialAvatarRelationship;     // +0x390
	cSPVector2 groupSizeRange;                  // +0x394
	SpVector<float> originDistances;            // +0x39c
	SpVector<unsigned int> relatedArchetypes;   // +0x3b0
	SpVector<unsigned int> archetypeGenerations;   // +0x3c4
	int eggIndex;                               // +0x3d8
	SpVector<unsigned int> schedulerTemplates;  // +0x3dc
	int fightGroupSize;                         // +0x3f0
	int standardAttacksPerSpecial;              // +0x3f4
	int numInGroupToStartWithSpecial;           // +0x3f8
	int numToKillForFearfulRelationship;        // +0x3fc
	int numToKillForExtinction;                 // +0x400
	int numToImpressForCurious;                 // +0x404
	int numToImpressForFriendly;                // +0x408
	int numToImpressForBestFriends;             // +0x40c
	int relationshipCuriousReward;              // +0x410
	int relationshipFriendlyReward;             // +0x414
	int relationshipBestFriendsReward;          // +0x418
	int relationshipFearedReward;               // +0x41c
	int extinctionReward;                       // +0x420
	unsigned int numSocialProposals;            // +0x424
	float socialTimeBeforeDrain;                // +0x428
	float socialDrainRate;                      // +0x42c
	int socialProposalLimit;                    // +0x430 (retail, name guessed)
	float attacked_SpeciesHelpRadius;           // +0x434
	int attacked_MaxSpeciesToAlert;             // +0x438
	AutoRefCount_s004d_a440<cPropertyList_s004d_a440> mpPropertyList; // +0x43c
};
}
// ---- items of slice s004da440 end

// ---- items of slice s004db1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_paintSystemVtblA[];
extern int g_paintSystemVtblB[];
struct Sub0 { void f(); };
struct Sub1 { void f(); };
struct Sub2 { void f(); };
struct Sub3 { void f(); };
struct IVtbl9 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(int a, int b);
};
struct PaintSystem {
    void Destroy();
};
struct Connector {
    void* mpObj;    // +0
    int   mnB;      // +4
    int   mnC;      // +8
    int   mnD;      // +0xc
    int   mnE;      // +0x10
    void Init(void* pObj, int b, int c, uint32_t n);
};
// ---- items of slice s004db1b0 end

// ---- items of slice s004db6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWStr[];            // 0x01667bac, eastl empty-string sentinel
extern wchar_t gNewlineW[];                                  // L"\n" at 0x013f0ce0
#pragma intrinsic(strcmp)
void operator delete[](void* p);       // 0x00f47380
struct WString_s004d_b6e0 {                        // eastl::basic_string<wchar_t>, 12 bytes (+ empty allocator)
    wchar_t* b; wchar_t* e; wchar_t* cap;
    WString_s004d_b6e0() { b = 0; e = 0; cap = 0; b = gEmptyWStr; e = b; cap = b + 1; }
    void FreeBuffer();                  // 0x004237d0
    void Ctor(const wchar_t* s, char* tag);   // 0x0041df50
    void Append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x00429580
};
struct CString {                        // eastl::basic_string<char>
    char* b; char* e; char* cap;
    CString() { b = 0; e = 0; cap = 0; b = (char*)gEmptyWStr; e = b; cap = b + 1; }
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    void Dtor();                        // 0x00530670
    void InlineFree() { if ((cap - b) > 1 && b) operator delete[](b); }
};
struct Item12 { uint32_t a, b, c; };    // 12-byte resource key
struct VecF {                           // eastl::vector<float>
    float* b; float* e; float* cap;
    uint32_t alloc;
    void AllocCtor(char* tag);          // 0x00429360
    void Ctor(char* tag);               // 0x00540470
    void Reserve(uint32_t n);           // 0x004e0880
    void Dtor();                        // 0x00425990
};
struct VecK {                           // eastl::vector<Item12>
    Item12* b; Item12* e; Item12* cap;
    uint32_t alloc;
    void AllocCtor(char* tag);          // 0x00429360
    void Ctor(char* tag);               // 0x00540470
    void Reserve(uint32_t n);           // 0x0041e4d0
    bool Empty();                       // 0x00526430 (shared instantiation)
    void Dtor();                        // 0x005156b0
};
struct VecC {                           // eastl::vector<FunctionalMatch::Constraint>
    uint32_t* b; uint32_t* e; uint32_t* cap;
    void Ctor(char* tag);               // 0x00540470
    bool Empty();                       // 0x00526430
    void PushBack(void* constraint);    // 0x004e18e0
    void Dtor();                        // 0x004e1780 (applied to the Constraint's inner vector)
};
struct Constraint {                     // SP::FunctionalMatch::Constraint
    uint32_t pad[4];
    VecC inner;
    Constraint* Construct(uint32_t id, int zero, float mn, float mx);   // 0x005588f0
};
struct FloatVecNode { Item12 key; VecF vals; };   // rbtree value_type: pair<Item12, vector<float>>
struct RbIter {                         // rbtree_iterator
    void* node;
    void Ctor(void* n);                 // 0x00566c50
    FloatVecNode* Deref();              // 0x00564f50
    void Inc();                         // 0x00422c50
};
struct RbMap {                          // eastl::map<Item12, vector<float>>
    uint32_t pad[7];
    void Ctor(char* tag);               // 0x004b5980
    VecF* Index(Item12* key);           // 0x004e1a90
    void DoNuke(void* root);            // 0x004e4170
};
void PushBackFloat(VecF* v, float* val);  // 0x004547f0 (thiscall on vector<float>)
struct IFileStream {
    virtual void v0();
    virtual void AddRef();              // +4
    virtual void Release();             // +8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Close();               // +0x18 (slot 6)
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void Flush();               // +0x34 (slot 13)
    virtual void Write(const void* p, uint32_t n);   // +0x38 (slot 14)
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18();
    virtual bool Open(int a, int b, int c, int d);   // +0x4c (slot 19)
};
struct cArguments {
    bool HasArgument(const char* name);                   // 0x00837ee0
    const char** OptionArguments(const char* name, int n);   // 0x00838330
};
struct IObjectTemplateDB {
    virtual void v0();
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void QueryMatches(VecK* out, VecC* constraints);   // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual bool GetParameterRange(uint32_t id, VecF* out);    // +0x44
    virtual void v18();
    virtual bool GetParameterValues(uint32_t id, VecF* values, VecK* items);   // +0x4c
};
struct IResourceManagerFull {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30();
    virtual void GetPath(Item12* key, WString_s004d_b6e0* out);   // +0x7c (slot 31)
};
struct ParamDef { uint32_t id; const char* name; };
extern ParamDef gSpeciesParams[26];     // 0x013f07e8
IObjectTemplateDB* ObjectTemplateDB();          // 0x0067cb40
IResourceManagerFull* GetManager_s004d_b6e0();             // 0x0067dcd0
void  ArgScriptOutput(void* parser, const char* fmt, ...);   // EA::ArgScript::Output 0x00841000
void  AppendFormat(WString_s004d_b6e0* s, const wchar_t* fmt, ...);     // 0x004e0850 (append sprintf)
void  Format(WString_s004d_b6e0* s, const wchar_t* fmt, ...);           // 0x0041e050 (sprintf)
void  GetDataPath(uint32_t id, WString_s004d_b6e0* out, int flag);      // 0x00688830
void* NewObject(uint32_t size);                              // 0x006abeb0
IFileStream* FileStreamCtor(void* mem, const wchar_t* path); // EA::IO::FileStream::FileStream 0x00931e10
WString_s004d_b6e0* ConvertToString16(WString_s004d_b6e0* out, const char* s, int n);   // EA::ConvertToString16 0x0093c5a0
CString* ConvertToString8(CString* out, WString_s004d_b6e0* s);              // EA::ConvertToString8  0x0093c570
void  OpenFile(const wchar_t* path);                         // EA::Process::OpenFile 0x00935e60
namespace SP {
struct cSpeciesCheat_s004d_b6e0 {
    uint32_t pad0;
    void*    mParser;               // +4: cCommandBase::mParser
    uint32_t pad[2];                // base cCommandStateT<...>, size 0x10
    void Execute(cArguments* pArguments);   // __thiscall, virtual override 0x004db6e0
    void GetFullPath(Item12* key, WString_s004d_b6e0* out);   // 0x004dc660
};  // namespace SP
}
    void operator delete(void*); // 0x00f47380
// ---- items of slice s004db6e0 end

// ---- items of slice s004dc660 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPEditorSpeciesManager_s004d_c660 {
    char pad[0x100];
    void Teardown();                        // @ 0x004dcaa0
    bool HandleMessage(int msgId, void* payload); // @ 0x004dcee0
};
}
extern int g_plantStaticType;   // DAT_015d9670
extern int g_speciesStaticType; // DAT_015d9674
// ---- items of slice s004dc660 end

// ---- items of slice s004df2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
namespace EA {
namespace ResourceMan {
struct Key_s004d_f2d0 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s004d_f2d0& a, const Key_s004d_f2d0& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
}
}
namespace EA {
namespace ResourceMan {
inline bool operator!=(const Key_s004d_f2d0& a, const Key_s004d_f2d0& b) { return a.mInstance != b.mInstance || a.mType != b.mType || a.mGroup != b.mGroup; }
}
}
using EA::ResourceMan::Key_s004d_f2d0;
class RandomLinearCongruential;
extern RandomLinearCongruential sMathRandom;                                   // 0x01601760
double RandomRange(RandomLinearCongruential* r, double lo, double hi);         // 0x004B8900
struct Vector2_s004d_f2d0 { float mData[2]; const float& operator[](int i) const { return mData[i]; } };
namespace SP {
class cSpeciesProfile_s004d_f2d0 {
public:
    cSpeciesProfile_s004d_f2d0(const Key_s004d_f2d0& key, bool bPlant);   // 0x004D3DD0
    ~cSpeciesProfile_s004d_f2d0();                              // 0x004D44E0
    bool Load(const Key_s004d_f2d0& key);                       // 0x004D4F10
    char pad0[0x504];
    Key_s004d_f2d0 mSpeciesKey;          // 0x504
    char pad510[0x53C - 0x510];
    int mbLoaded;             // 0x53C
    char pad540[0xA18 - 0x540];
};
}
namespace SP {
class cSpeciesArchetype_s004d_f2d0;
}
namespace SP {
bool ResourceExists(const Key_s004d_f2d0* key); // 0x004DA3A0
}
namespace SP {
struct IObjectTemplateDB_s004d_f2d0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
    virtual void FindTemplates(struct KeyVector& out, int count, struct ConstraintVector& constraints);   // 0x24
virtual void v28();
virtual void v2C();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3C();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4C();
virtual void v50();
virtual void v54();
    virtual void Prefetch(const Key_s004d_f2d0& key, bool b);                         // 0x58
virtual void v5C();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6C();
virtual void v70();
    virtual void Remove(const Key_s004d_f2d0& key, int flags);                           // 0x74
};
}
namespace SP {
IObjectTemplateDB_s004d_f2d0* ObjectTemplateDB_s004d_f2d0();   // 0x0067CB40
}
namespace SP {
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
    virtual void MessageSend(uint32_t id, void* msg, int flags);   // 0x14
};
}
namespace SP {
IMessageServer* MessageServer();   // 0x0067DCC0
}
namespace SP {
union MessageValue { uint32_t mUint32; float mFloat; uint32_t pad[2]; };
}
namespace SP {
class MessageBasicRC5 {
public:
    MessageBasicRC5(uint32_t id);   // 0x00421C80
    ~MessageBasicRC5();             // 0x00421CF0
    const void* vptr;               // 0x00
    volatile long mRefCount;        // 0x04
    MessageValue mData[5];          // 0x08
    void SetUint32(int i, uint32_t v) { mData[i].mUint32 = v; }
    uint32_t mId;                   // 0x30
    uint32_t pad34;
    uint32_t mRCFlags;              // 0x38
    uint32_t pad3C;
};
}
namespace eastl {
struct HashNode {
    Key_s004d_f2d0 mKey;
    SP::cSpeciesProfile_s004d_f2d0* mpProfile;
    HashNode* mpNext;
};
}
namespace eastl {
struct hashtable_iterator_base_s004d_f2d0 {
    HashNode* mpNode;
    HashNode** mpBucket;
    hashtable_iterator_base_s004d_f2d0(HashNode* pNode, HashNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
struct hashtable_iterator_s004d_f2d0 : public hashtable_iterator_base_s004d_f2d0 {
    hashtable_iterator_s004d_f2d0(HashNode* pNode = 0, HashNode** pBucket = 0) : hashtable_iterator_base_s004d_f2d0(pNode, pBucket) {}
    hashtable_iterator_s004d_f2d0(HashNode** pBucket) : hashtable_iterator_base_s004d_f2d0(*pBucket, pBucket) {}
    hashtable_iterator_s004d_f2d0(const hashtable_iterator_s004d_f2d0& x) : hashtable_iterator_base_s004d_f2d0(x.mpNode, x.mpBucket) {}
};
}
namespace eastl {
struct hashtable_const_iterator : public hashtable_iterator_base_s004d_f2d0 {
    hashtable_const_iterator(const hashtable_iterator_s004d_f2d0& x) : hashtable_iterator_base_s004d_f2d0(x.mpNode, x.mpBucket) {}
};
}
namespace eastl {
inline bool operator!=(const hashtable_iterator_base_s004d_f2d0& a, const hashtable_iterator_base_s004d_f2d0& b) { return a.mpNode != b.mpNode; }
}
namespace eastl {
class SpeciesMap_s004d_f2d0 {   // hash_map<Key, cSpeciesProfile*, KeyHash>
public:
    typedef hashtable_iterator_s004d_f2d0 iterator;
    typedef hashtable_const_iterator const_iterator;
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const Key_s004d_f2d0& k);                       // 0x004E0F80
    SP::cSpeciesProfile_s004d_f2d0*& operator[](const Key_s004d_f2d0& k);    // 0x004E0560
    uint32_t erase(const Key_s004d_f2d0& k);                      // 0x004E10A0
    iterator erase(iterator it);                       // 0x004E11E0
    uint32_t mFunctors;
    HashNode** mpBucketArray;   // 0x04
    uint32_t mnBucketCount;     // 0x08
    uint32_t mnElementCount;    // 0x0C
    uint32_t mRehashPolicy[3];  // 0x10
    uint32_t mAllocator;        // 0x1C
};
}
namespace eastl {
struct ArchetypeNode;
}
namespace eastl {
struct archetype_iterator_base {
    ArchetypeNode* mpNode;
    ArchetypeNode** mpBucket;
    archetype_iterator_base(ArchetypeNode* pNode, ArchetypeNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
struct archetype_iterator : public archetype_iterator_base {
    archetype_iterator(ArchetypeNode* pNode = 0, ArchetypeNode** pBucket = 0) : archetype_iterator_base(pNode, pBucket) {}
    archetype_iterator(ArchetypeNode** pBucket) : archetype_iterator_base(*pBucket, pBucket) {}
};
}
namespace eastl {
inline bool operator!=(const archetype_iterator_base& a, const archetype_iterator_base& b) { return a.mpNode != b.mpNode; }
}
namespace eastl {
class ArchetypeMap {   // hash_map<uint32_t, cSpeciesArchetype>
public:
    typedef archetype_iterator iterator;
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const uint32_t& k);                  // 0x004E14E0
    uint32_t mFunctors;
    ArchetypeNode** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    uint32_t mRehashPolicy[3];
    uint32_t mAllocator;
};
}
namespace SP {
struct ArchetypeIdVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); } };
}
namespace SP {
class cSpeciesArchetype_s004d_f2d0 {
public:
    char pad0[0x3C4];
    ArchetypeIdVector mParentIds;   // 0x3C4
};
}
namespace eastl {
struct ArchetypeNode { uint32_t mKey; SP::cSpeciesArchetype_s004d_f2d0 mValue; };
}
namespace SP {
namespace FunctionalMatch {
 class Constraint_s004d_f2d0; 
}
}
namespace SP {
struct DefaultAllocTag { DefaultAllocTag() {} };
}
namespace SP {
struct ConstraintAllocator {
    ConstraintAllocator() {}
    ConstraintAllocator(const DefaultAllocTag&);   // 0x00429360
    uint32_t mFlags;
};
}
namespace SP {
struct ConstraintVectorBase {
    FunctionalMatch::Constraint_s004d_f2d0* mpBegin;
    FunctionalMatch::Constraint_s004d_f2d0* mpEnd;
    FunctionalMatch::Constraint_s004d_f2d0* mpCapacity;
    ConstraintAllocator mAllocator;
    ConstraintVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ConstraintVectorBase(const DefaultAllocTag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ConstraintVectorBase(uint32_t n, const DefaultAllocTag& a);   // 0x004E3CF0
    ~ConstraintVectorBase();   // 0x004AB0D0
};
}
namespace SP {
struct ConstraintVector : public ConstraintVectorBase {   // eastl::vector<FunctionalMatch::Constraint>
    ConstraintVector() {}
    ConstraintVector(const DefaultAllocTag& a) : ConstraintVectorBase(a) {}
    inline ConstraintVector(uint32_t n, const FunctionalMatch::Constraint_s004d_f2d0& value, const DefaultAllocTag& a = DefaultAllocTag());
    ~ConstraintVector();   // 0x004E1780
    void DoDestroyValues(FunctionalMatch::Constraint_s004d_f2d0* first, FunctionalMatch::Constraint_s004d_f2d0* last);   // 0x004E39A0
    void reserve(uint32_t n);                                   // 0x004E17E0
    void push_back(const FunctionalMatch::Constraint_s004d_f2d0& value);   // 0x004E18E0
};
}
namespace SP {
namespace FunctionalMatch {
class Constraint_s004d_f2d0 {
public:
    Constraint_s004d_f2d0(uint32_t property, uint32_t op, uint32_t value);   // 0x00558960
    uint32_t mData[4];
    ConstraintVector mSubConstraints;   // 0x10
    uint32_t mFlags;                    // 0x20
};
}
}
namespace SP {
void uninitialized_fill_n(FunctionalMatch::Constraint_s004d_f2d0* p, uint32_t n, const FunctionalMatch::Constraint_s004d_f2d0& value);   // 0x004E3D60
}
namespace SP {
inline ConstraintVector::ConstraintVector(uint32_t n, const FunctionalMatch::Constraint_s004d_f2d0& value, const DefaultAllocTag& a)
    : ConstraintVectorBase(n, a)
{
    uninitialized_fill_n(mpBegin, n, value);
    mpEnd = mpBegin + n;
}
}
namespace SP {
template <class T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }
}
namespace SP {
struct KeyVectorBase {
    Key_s004d_f2d0* mpBegin;
    Key_s004d_f2d0* mpEnd;
    Key_s004d_f2d0* mpCapacity;
    uint32_t mAllocator;
    KeyVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVectorBase();   // 0x005156B0
};
}
namespace SP {
struct KeyVector : public KeyVectorBase {   // eastl::vector<ResourceKey>
    ~KeyVector() { destruct(mpBegin, mpEnd); }
};
}
namespace SP {
struct ProfileAllocator { uint32_t mData[3]; };
}
namespace SP {
struct ProfileVectorBase {
    cSpeciesProfile_s004d_f2d0** mpBegin;
    cSpeciesProfile_s004d_f2d0** mpEnd;
    cSpeciesProfile_s004d_f2d0** mpCapacity;
    ProfileVectorBase(const DefaultAllocTag& a);   // 0x00540470
};
}
namespace SP {
struct ProfileVector : public ProfileVectorBase {   // eastl::fixed_vector<cSpeciesProfile*, 5>
    ProfileVector() : ProfileVectorBase(DefaultAllocTag()) { InitBuffer(); SetOverflowCapacity(1); }
    ~ProfileVector();                    // 0x004E1BF0
    void InitBuffer();                   // 0x004E0810
    void SetOverflowCapacity(uint32_t);  // 0x004CD3C0
    cSpeciesProfile_s004d_f2d0*& operator[](uint32_t i) { return mpBegin[i]; }
    ProfileAllocator mAllocator;
    cSpeciesProfile_s004d_f2d0* mBuffer[5];
};
}
namespace SP {
int FindMatchingCreatures(ProfileVector& out, cSpeciesArchetype_s004d_f2d0* pArchetype, int count, int a, bool b, ConstraintVector& constraints); // 0x004D2200
}
namespace SP {
class cSPEditorSpeciesManager_s004d_f2d0 {
public:
    void SetAvatarSpecies(const Key_s004d_f2d0& key);  // 0x004df310 (SP::cSPEditorSpeciesManager::SetAvatarSpecies)
    void SetAvatarProfile(cSpeciesProfile_s004d_f2d0* pProfile);
    cSpeciesProfile_s004d_f2d0* GetAvatarProfile();
    cSpeciesProfile_s004d_f2d0* GetPlantProfile(const Key_s004d_f2d0& key);
    cSpeciesProfile_s004d_f2d0* GetProfile(const Key_s004d_f2d0& key);
    cSpeciesProfile_s004d_f2d0* FindProfile(eastl::SpeciesMap_s004d_f2d0& map, const Key_s004d_f2d0& key);
    bool GetDefaultReplacementKey(const Key_s004d_f2d0& key, Key_s004d_f2d0& outKey);
    bool GetReplacementKey(const Key_s004d_f2d0& key, uint32_t archetypeId, Key_s004d_f2d0& outKey);
    bool GetReplacementKeyForArchetype(const Key_s004d_f2d0& key, cSpeciesArchetype_s004d_f2d0* pArchetype, Key_s004d_f2d0& outKey);
    bool UpdateProfile(cSpeciesProfile_s004d_f2d0* pProfile, const Key_s004d_f2d0& key);
    int GetMatchingPlantProfiles(ProfileVector& results, int maxCount, int plantType);  // 0x004dfd50 (SP::cSPEditorSpeciesManager::GetMatchingPlantProfiles)
    int GetMatchingCreatureKeys(ProfileVector& out, uint32_t archetypeId, int count, int a, bool b);
    int GetMatchingCreatureKeys(ProfileVector& out, cSpeciesArchetype_s004d_f2d0* pArchetype, int count, int a, bool b);
    cSpeciesArchetype_s004d_f2d0* GetSpeciesArchetype(uint32_t id, uint32_t level);
    cSpeciesArchetype_s004d_f2d0* GetDefaultArchetype();

    void* vptr;                              // 0x00
    eastl::SpeciesMap_s004d_f2d0 mSpecies;              // 0x04
    eastl::SpeciesMap_s004d_f2d0 mOldSpeciesMapping;    // 0x24
    eastl::SpeciesMap_s004d_f2d0 mPlantSpecies;         // 0x44
    eastl::SpeciesMap_s004d_f2d0 mReplacementSpecies;   // 0x64
    eastl::SpeciesMap_s004d_f2d0 mReplacementCache;     // 0x84
    Key_s004d_f2d0 mAvatarSpeciesKey;                   // 0xA4
    eastl::ArchetypeMap mArchetypes;         // 0xB0
};
}
// ---- items of slice s004df2d0 end

// ---- items of slice s005beaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#define PV(n) virtual void pv##n();
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_eaf0 {
 public:
  T x, y, z;
  Vector3Template_s005b_eaf0() {}
  Vector3Template_s005b_eaf0(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator+(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator-(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator*(const Vector3Template_s005b_eaf0<T, N>& a, T s) {
  return Vector3Template_s005b_eaf0<T, N>(a.x * s, a.y * s, a.z * s);
}
}
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_eaf0 {
 public:
  T* mpObject;
  AutoRefCount_s005b_eaf0() : mpObject(0) {}
  AutoRefCount_s005b_eaf0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_eaf0() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
};
}
namespace EA {
struct Variant_s005b_eaf0 {
  uint32_t mData[4];
  unsigned short mFlags;   // +0x10
  unsigned short mTypeId;  // +0x12
  Variant_s005b_eaf0() : mFlags(0), mTypeId(0) {}
  ~Variant_s005b_eaf0() {
    if (mFlags & 4)
      Destruct(0);  // 0x0093db80 (EA::Variant::Destruct)
  }
  void Destruct(int);                                       // EA::Variant::Destruct 0x0093db80
  Variant_s005b_eaf0& operator=(const int& v);                         // Variant_SetU32 (0x00422eb0)
  void SetResourceKey(int a, int b, uint32_t v, int c, int d);  // FUN_0093dd80
};
}
namespace EA {
namespace ResourceMan {
class Key_s005b_eaf0 {
 public:
  unsigned int mInstance;  // +0x0
  unsigned int mType;      // +0x4
  unsigned int mGroup;     // +0x8
};
}
}
namespace EA {
namespace ResourceMan {
class IResourceManager_s005b_eaf0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual class IRecord* GetDatabaseFor(const Key_s005b_eaf0& key, int a, int b);  // +0x30 (name guessed)
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager_s005b_eaf0* GetManager_s005b_eaf0();
}
}
namespace EA {
namespace ResourceMan {
class IDatabase {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetAccessFlags();  // +0x20 (name guessed)
};
}
}
namespace eastl {
template <typename T>
class sp_vector_s005b_eaf0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector_s005b_eaf0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector_s005b_eaf0() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};  // namespace eastl
}
struct Property_s005b_eaf0 {
  union {
    bool mBool;
    int mInt32;
  };
  char pad04[0x12 - 4];
  unsigned short mType;  // +0x12
  int* GetInt();         // Property::GetInt (0x0041e990)
};
namespace App {
class PropertyList_s005b_eaf0 {
 public:
  virtual void AddRef();
  virtual void Release();
  PV(2) PV(3) PV(4)
  virtual void SetProperty(uint32_t id, const EA::Variant_s005b_eaf0& value);   // +0x14
  virtual void RemoveProperty(uint32_t id);                         // +0x18
  PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property_s005b_eaf0*& result);         // +0x24
  virtual Property_s005b_eaf0* GetPropertyObject(uint32_t id);                 // +0x28
  PV(11) PV(12)
  virtual void SetParent(PropertyList_s005b_eaf0* parent);                     // +0x34
  PV(14) PV(15)
  PV(16)
  virtual void GetPropertyIDs(eastl::sp_vector_s005b_eaf0<uint32_t>& out);     // +0x44
};
}
namespace App {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual bool HasPropertyList(uint32_t instanceID, uint32_t groupID);                         // +0x28
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s005b_eaf0*& result);  // +0x2c
};
}
namespace SP {
App::IPropertyManager* PropertyManager_s005b_eaf0();
}
namespace SP {
bool GetPropertyAsKey(App::PropertyList_s005b_eaf0* list, uint32_t id, EA::ResourceMan::Key_s005b_eaf0* key);
}
namespace SP {
bool GetPropertyKeys(App::PropertyList_s005b_eaf0* list, uint32_t id, int* count, EA::ResourceMan::Key_s005b_eaf0** keys);  // 0x006a0ae0
}
namespace SP {
EA::ResourceMan::IDatabase* GetSaveArea(uint32_t id);
}
namespace SP {
bool SaveResource(App::PropertyList_s005b_eaf0* list, EA::ResourceMan::IDatabase* db, int flags);
}
namespace SP {
class IObjectTemplateDB_s005b_eaf0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  virtual void AddTemplate(const EA::ResourceMan::Key_s005b_eaf0& key);        // +0x70
  virtual void InvalidateTemplate(const EA::ResourceMan::Key_s005b_eaf0& key, int b);  // +0x74
};
}
namespace SP {
IObjectTemplateDB_s005b_eaf0* ObjectTemplateDB_s005b_eaf0();
}
namespace SP {
namespace FunctionalMatch {
enum eType_s005b_eaf0 { kTypeBool_s005b_eaf0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct DeclareParam_s005b_eaf0 {
  unsigned int mParameter;  // +0x0
  eType_s005b_eaf0 mType;              // +0x4
  int mIntVal;              // +0x8
  DeclareParam_s005b_eaf0(unsigned int parameter, bool value);
};
}
}
static inline uint32_t PropListGroup(uint32_t group) { return (group & 0xffffe5ff) | 0xe500; }
struct ListNode {
  ListNode* mpNext;
  ListNode* mpPrev;
  uint32_t mGroup;
  uint32_t mInstance;
};
namespace Simulator {
class cCollectableItems {
 public:
  cCollectableItems();
  virtual void AddRef();
  virtual void Release();
  bool Load(uint32_t instance, uint32_t group, int flags);    // FUN_00599440
  struct ListNode* GetItemList();                              // FUN_005939a0
  bool IsRare(uint32_t group, uint32_t instance);             // FUN_00595190
  void AddItem(uint64_t item, int flags);                     // FUN_00596da0
  void FinishedLoading();                                     // FUN_005942e0
  char pad[0x6dac - 4];
};
}
namespace Simulator {
uint64_t MakeItemID(uint32_t group, uint32_t instance);       // FUN_00593980
}
// ---- items of slice s005beaf0 end

// ---- items of slice s004e01d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
#pragma intrinsic(memcpy)
void EASTLFree(void* p);                                                         // 0x00F47380
void* EASTLAlloc(void* allocator_s004e_01d0, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
namespace EA {
template <class T> class RefCountTemplate_s004e_01d0 {
public:
    virtual ~RefCountTemplate_s004e_01d0();
    int AddRef() { return mnRefCount++ + 1; }
    int Release();   // 0x00453540
    T mnRefCount;
};
}
namespace EA {
template <class T> class AutoRefCount_s004e_01d0 {
public:
    AutoRefCount_s004e_01d0(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004e_01d0(const AutoRefCount_s004e_01d0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004e_01d0() { if (mpObject) mpObject->Release(); }
    T* mpObject;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s004e_01d0 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s004e_01d0& a, const Key_s004e_01d0& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s004e_01d0 { uint32_t operator()(const Key_s004e_01d0& k) const { return k.mInstance ^ k.mGroup; } };
}
}
using EA::ResourceMan::Key_s004e_01d0;
namespace eastl {
struct sp_vector_allocator_s004e_01d0 {
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
template <class T> struct vector_s004e_01d0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s004e_01d0 mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    void reserve(uint32_t n);
    void push_back(const T& value);
};
}
namespace eastl {
template <class T> struct equal_to_s004e_01d0 { bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
template <class T> struct hash_s004e_01d0 { uint32_t operator()(T val) const { return (uint32_t)val; } };
}
namespace eastl {
struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
}
namespace eastl {
struct default_ranged_hash {};
}
namespace eastl {
template <class P> struct use_first_s004e_01d0 {};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s004e_01d0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_s004e_01d0(float fMaxLoadFactor = 1.f) : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.f), mnNextResize(0) {}
    static uint32_t GetPrevBucketCountOnly(uint32_t nBucketCountHint);   // 0x00921340
    uint32_t GetNextBucketCount(uint32_t nBucketCountHint) const;        // 0x00921360
    uint32_t GetBucketCount(uint32_t nElementCount) const;               // 0x009213C0
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_base_s004e_01d0 {
    Node* mpNode;
    Node** mpBucket;
    hashtable_iterator_base_s004e_01d0(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
}
namespace eastl {
template <class Node> struct hashtable_iterator_s004e_01d0 : public hashtable_iterator_base_s004e_01d0<Node> {
    hashtable_iterator_s004e_01d0(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base_s004e_01d0<Node>(pNode, pBucket) {}
    hashtable_iterator_s004e_01d0(Node** pBucket) : hashtable_iterator_base_s004e_01d0<Node>(*pBucket, pBucket) {}
    hashtable_iterator_s004e_01d0(const hashtable_iterator_s004e_01d0& x) : hashtable_iterator_base_s004e_01d0<Node>(x.mpNode, x.mpBucket) {}
    hashtable_iterator_s004e_01d0& operator++() { this->increment(); return *this; }
};
}
namespace eastl {
template <class Node> struct hashtable_const_iterator_s004e_01d0 : public hashtable_iterator_base_s004e_01d0<Node> {
    hashtable_const_iterator_s004e_01d0(Node* pNode = 0, Node** pBucket = 0) : hashtable_iterator_base_s004e_01d0<Node>(pNode, pBucket) {}
    hashtable_const_iterator_s004e_01d0(Node** pBucket) : hashtable_iterator_base_s004e_01d0<Node>(*pBucket, pBucket) {}
};
}
namespace eastl {
template <class Node> inline bool operator!=(const hashtable_iterator_base_s004e_01d0<Node>& a, const hashtable_iterator_base_s004e_01d0<Node>& b) { return a.mpNode != b.mpNode; }
}
namespace eastl {
template <class Node> struct insert_return_type {
    hashtable_iterator_s004e_01d0<Node> first;
    bool second;
};
}
namespace eastl {
struct allocator_s004e_01d0 {
    void deallocate(void* p, uint32_t) { void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
extern void* gpEmptyBucketArray[2];                  // 0x0154DF28
}
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
}
namespace eastl {
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void* mpPoolBegin;
    void* mpCapacity;
    uint32_t mnNodeSize;
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
class fixed_hashtable_allocator { public:
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    fixed_hashtable_allocator(void* pNodeBuffer, uint32_t nodeBufferSize, uint32_t nodeSize, void* pBucketBuffer) {
        mPool.mpHead = 0;
        mPool.init(pNodeBuffer, nodeBufferSize, nodeSize, 4, 0);
        mPool.mpPoolBegin = pNodeBuffer;
        mPool.mpCapacity = (char*)pNodeBuffer + nodeBufferSize;
        mPool.mnNodeSize = nodeSize;
        mpBucketBuffer = pBucketBuffer;
    }
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);   // 0x004E2F20
    void deallocate(void* p, uint32_t) {
        if (p != mpBucketBuffer) {
            if ((p >= mPool.mpPoolBegin) && (p < mPool.mpCapacity)) {
                ((Link*)p)->mpNext = mPool.mpHead;
                mPool.mpHead = (Link*)p;
            } else
                fixed_pool_with_overflow::OverflowFree(p, mPool.mnNodeSize);
        }
    }
};
}
namespace eastl {
template <class K, class V> struct pair_s004e_01d0 {
    K first;
    V second;
    pair_s004e_01d0(const K& x, const V& y) : first(x), second(y) {}
};
}
namespace eastl {
template <class K, class V> struct hash_node_s004e_01d0 {
    pair_s004e_01d0<K, V> mValue;
    hash_node_s004e_01d0* mpNext;
};
}
namespace eastl {
template <class K, class V, class H, class A> class hashtable_s004e_01d0 {
public:
    typedef hash_node_s004e_01d0<K, V> node_type;
    typedef hashtable_iterator_s004e_01d0<node_type> iterator;
    typedef hashtable_const_iterator_s004e_01d0<node_type> const_iterator;
    typedef pair_s004e_01d0<K, V> value_type;

    hashtable_s004e_01d0(uint32_t nBucketCount, const H& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to_s004e_01d0<K>& eq, const use_first_s004e_01d0<value_type>& ek, const A& allocator_s004e_01d0);
    ~hashtable_s004e_01d0();

    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const K& k);
    const_iterator find_const(const K& k);
    insert_return_type<node_type> DoInsertValue(const value_type& value, true_type);
    insert_return_type<node_type> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    uint32_t erase(const K& k);
    iterator erase(iterator i);
    void set_max_load_factor(float fMaxLoadFactor);
    void rehash_policy(const prime_rehash_policy_s004e_01d0& rehashPolicy) {
        mRehashPolicy = rehashPolicy;
        const uint32_t nBuckets = rehashPolicy.GetBucketCount((uint32_t)mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }
    void reset() {
        ScratchSlots<1>();
        mnBucketCount = 1;
        mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(node_type*));
    }
    void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode, sizeof(node_type)); }
    void DoFreeNodes(node_type** pBucketArray, uint32_t n);
    node_type** DoAllocateBuckets(uint32_t n);
    void DoRehash(uint32_t nBucketCount);
    uint32_t get_hash_code(const K& key) const { return (uint32_t)m_h1(key); }
    uint32_t bucket_index(const K&, uint32_t c, uint32_t n) const { return (uint32_t)m_h2(c, n); }
    bool compare(const K& k, uint32_t, node_type* pNode) const { return m_equal(k, pNode->mValue.first); }
    node_type* DoFindNode(node_type* pNode, const K& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (compare(k, c, pNode))
                return pNode;
        }
        return 0;
    }

    use_first_s004e_01d0<value_type> m_extract;   // 0x00
    equal_to_s004e_01d0<K> m_equal;               // 0x01
    H m_h1;                            // 0x02
    mod_range_hashing m_h2;            // 0x03
    node_type** mpBucketArray;         // 0x04
    uint32_t mnBucketCount;            // 0x08
    uint32_t mnElementCount;           // 0x0C
    prime_rehash_policy_s004e_01d0 mRehashPolicy; // 0x10
    A mAllocator;                      // 0x1C
};
}
namespace eastl {
template <class K, class V, class H, class A>
typename hashtable_s004e_01d0<K, V, H, A>::iterator hashtable_s004e_01d0<K, V, H, A>::find(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    node_type* const pNode = DoFindNode(mpBucketArray[n], k, c);
    return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <class K, class V, class H, class A>
uint32_t hashtable_s004e_01d0<K, V, H, A>::erase(const K& k)
{
    const uint32_t c = get_hash_code(k);
    const uint32_t n = (uint32_t)bucket_index(k, c, (uint32_t)mnBucketCount);
    const uint32_t nElementCountSaved = mnElementCount;
    node_type** pBucketArray = mpBucketArray + n;
    while (*pBucketArray && !compare(k, c, *pBucketArray))
        pBucketArray = &(*pBucketArray)->mpNext;
    while (*pBucketArray && compare(k, c, *pBucketArray)) {
        node_type* const pNode = *pBucketArray;
        *pBucketArray = pNode->mpNext;
        DoFreeNode(pNode);
        --mnElementCount;
    }
    return nElementCountSaved - mnElementCount;
}
}
namespace eastl {
template <class K, class V, class H, class A>
typename hashtable_s004e_01d0<K, V, H, A>::iterator hashtable_s004e_01d0<K, V, H, A>::erase(iterator i)
{
    iterator iNext(i);
    ++iNext;
    node_type* pNode = i.mpNode;
    node_type* pNodeCurrent = *i.mpBucket;
    if (pNodeCurrent == pNode)
        *i.mpBucket = pNodeCurrent->mpNext;
    else {
        node_type* pNodeNext = pNodeCurrent->mpNext;
        while (pNodeNext != pNode) {
            pNodeCurrent = pNodeNext;
            pNodeNext = pNodeCurrent->mpNext;
        }
        pNodeCurrent->mpNext = pNodeNext->mpNext;
    }
    DoFreeNode(pNode);
    --mnElementCount;
    return iNext;
}
}
namespace eastl {
template <class K, class V, class H, class A>
hashtable_s004e_01d0<K, V, H, A>::hashtable_s004e_01d0(uint32_t nBucketCount, const H& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
                                 const equal_to_s004e_01d0<K>& eq, const use_first_s004e_01d0<value_type>& ek, const A& allocator_s004e_01d0)
    : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(allocator_s004e_01d0)
{
    if (nBucketCount < 2)
        reset();
    else {
        mnBucketCount = (uint32_t)mRehashPolicy.GetNextBucketCount((uint32_t)nBucketCount);
        mpBucketArray = DoAllocateBuckets(mnBucketCount);
    }
}
}
namespace eastl {
template <class K, class V, class H, class A>
hashtable_s004e_01d0<K, V, H, A>::~hashtable_s004e_01d0()
{
    clear();
    DoFreeBuckets(mpBucketArray, mnBucketCount);
}
}
namespace eastl {
template <class K, class V, class H, class A> class hash_map_s004e_01d0 : public hashtable_s004e_01d0<K, V, H, A> {
public:
    typedef hashtable_s004e_01d0<K, V, H, A> base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::value_type value_type;
    hash_map_s004e_01d0(uint32_t nBucketCount, const H& hashFunction, const equal_to_s004e_01d0<K>& predicate, const A& allocator_s004e_01d0)
        : base_type(nBucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), predicate,
                    use_first_s004e_01d0<value_type>(), allocator_s004e_01d0) {}
    V& operator[](const K& key);
};
}
namespace eastl {
template <class V> struct OperatorIndexSlots { enum { N = 13 }; };
}
namespace eastl {
template <class V> struct OperatorIndexSlots<V*> { enum { N = 12 }; };
}
namespace eastl {
template <class K, class V, class H, class A>
V& hash_map_s004e_01d0<K, V, H, A>::operator[](const K& key)
{
    ScratchSlots<OperatorIndexSlots<V>::N>();
    iterator it = base_type::find(key);
    if (it != base_type::end())
        return (*it.mpNode).mValue.second;
    return (*base_type::insert(value_type(key, V())).first.mpNode).mValue.second;
}
}
struct PartLayout {   // 0x14-byte value of a fixed_hash_map<uint32_t, PartLayout, 32, 33>
    uint32_t mFields[3];
    float mScale;
    float mWeight;
    PartLayout() { mFields[0] = 0; mFields[1] = 0; mFields[2] = 0; mScale = 1.0f; mWeight = 1.0f; }
};
namespace SP {
class cSpeciesProfile_s004e_01d0;
}
namespace SP {
class cSpeciesArchetype_s004e_01d0 {
public:
    cSpeciesArchetype_s004e_01d0();                               // 0x004DA440
    cSpeciesArchetype_s004e_01d0(const cSpeciesArchetype_s004e_01d0& x);     // 0x004E1CB0
    ~cSpeciesArchetype_s004e_01d0();                              // 0x004DB1B0
    uint32_t mData[0x110];
};
}
namespace SP {
class cTextureInstance_s004e_01d0;
}
namespace SP {
class cEditorEvent : public EA::RefCountTemplate_s004e_01d0<int> {
public:
    uint32_t mSubType;   // 0x08
    uint32_t mType;      // 0x0C
    uint32_t pad10[0x29];
    uint32_t mValue;     // 0xB4
};
}
namespace eastl {
typedef hashtable_s004e_01d0<uint32_t, PartLayout, hash_s004e_01d0<uint32_t>, fixed_hashtable_allocator> PartLayoutTable;
}
namespace eastl {
typedef hash_map_s004e_01d0<uint32_t, PartLayout, hash_s004e_01d0<uint32_t>, fixed_hashtable_allocator> PartLayoutMap;
}
namespace eastl {
typedef hash_map_s004e_01d0<Key_s004e_01d0, SP::cSpeciesProfile_s004e_01d0*, EA::ResourceMan::KeyHash_s004e_01d0, allocator_s004e_01d0> SpeciesMap_s004e_01d0;
}
namespace eastl {
typedef hash_map_s004e_01d0<uint32_t, SP::cSpeciesArchetype_s004e_01d0, hash_s004e_01d0<uint32_t>, allocator_s004e_01d0> ArchetypeMap_s004e_01d0;
}
namespace eastl {
template class hashtable_s004e_01d0<uint32_t, PartLayout, hash_s004e_01d0<uint32_t>, fixed_hashtable_allocator>;
}
namespace eastl {
template class hash_map_s004e_01d0<uint32_t, PartLayout, hash_s004e_01d0<uint32_t>, fixed_hashtable_allocator>;
}
namespace eastl {
template class hash_map_s004e_01d0<Key_s004e_01d0, SP::cSpeciesProfile_s004e_01d0*, EA::ResourceMan::KeyHash_s004e_01d0, allocator_s004e_01d0>;
}
namespace eastl {
template class hashtable_s004e_01d0<Key_s004e_01d0, SP::cSpeciesProfile_s004e_01d0*, EA::ResourceMan::KeyHash_s004e_01d0, allocator_s004e_01d0>;
}
namespace eastl {
 template class hash_map_s004e_01d0<uint32_t, SP::cSpeciesArchetype_s004e_01d0, hash_s004e_01d0<uint32_t>, allocator_s004e_01d0>; 
}
template void eastl::vector_s004e_01d0<EA::AutoRefCount_s004e_01d0<SP::cTextureInstance_s004e_01d0> >::reserve(uint32_t);
template void eastl::vector_s004e_01d0<EA::AutoRefCount_s004e_01d0<SP::cEditorEvent> >::push_back(const EA::AutoRefCount_s004e_01d0<SP::cEditorEvent>&);
namespace SP {
class cEditorEventQueue {
public:
    void QueueEvent(cEditorEvent* pEvent);
    uint32_t pad0[0x544 / 4];
    uint32_t mLastValue;                                          // 0x544
    uint32_t pad548[(0x6D4 - 0x548) / 4];
    eastl::vector_s004e_01d0<EA::AutoRefCount_s004e_01d0<cEditorEvent> > mEvents;       // 0x6D4
    uint32_t pad6E8[(0x73C - 0x6E8) / 4];
    eastl::vector_s004e_01d0<EA::AutoRefCount_s004e_01d0<cEditorEvent> > mLateEvents;   // 0x73C
};
}
// ---- items of slice s004e01d0 end

// @ 0x004d1470
bool GetPaintUV(cSkinPaintTable* table, uint32_t id, float* u, float* v)
{
    if (table->HasEntry(id)) {
        ScratchSlots<1>();
        Vector2 uv = table->GetEntry(id)->GetUV();
        *u = uv[0];
        *v = uv[1];
        return true;
    }
    *v = 0.0f;
    *u = 0.0f;
    return false;
}

// @ 0x004d15c0
namespace SP {
void BuildParameters(cCreatureSummary* pSummary, eastl::sp_vector<DeclareParam_s004d_15c0>& params, bool bArchetypes)
{
    params.reserve(params.size() + 9);
    params.push_back(DeclareParam_s004d_15c0(0x2f05c58, pSummary->m608 > 0 ? 1.0f : 0.0f));
    params.push_back(DeclareParam_s004d_15c0(0x2f05c59, pSummary->m60c > 0 ? 1.0f : 0.0f));
    params.push_back(DeclareParam_s004d_15c0(0x3fea1a0, pSummary->m5b0));
    params.push_back(DeclareParam_s004d_15c0(0x2f05c5f, pSummary->m5ac));

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
        eastl::hashtable_s004d_15c0<SpeciesNode>& species = GetSpeciesManagerInstance()->GetSpecies();
        eastl::hashtable_s004d_15c0<SpeciesNode>::iterator it = species.begin();
        eastl::hashtable_s004d_15c0<SpeciesNode>::iterator last = species.end();
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

            cSPVector3_s004d_15c0* rangePtrs[] = {
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
                    cSPVector3_s004d_15c0* pRange = rangePtrs[j];
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
                params.push_back(DeclareParam_s004d_15c0(0x52def3f, (int)speciesId));
            else if (results[1])
                params.push_back(DeclareParam_s004d_15c0(0x52def4b, (int)speciesId));
        }
    }
}
}  // namespace SP

// @ 0x004d2200
int GetMatchingCreatureKeys(uint32_t* self, uint32_t manager, int maxCount, uint32_t filter, char useAll, uint32_t* outParams)
{
    (void)self; (void)manager; (void)maxCount; (void)filter; (void)useAll; (void)outParams;
    return 0;
}

// @ 0x004d2450
namespace SP {
void LoadSpeciesTuning(bool force)
{
    if (force || !sSpeciesTuningLoaded) {
        sSpeciesTuningLoaded = true;

        IPropManager* propManager = PropertyManager();
        PropertyListPtr propList;
        if (propManager->GetGlobalPropertyList(0x236f18f2, propList.AsPPTypeParam())) {
            ReadPropertyUInt32(propList.mpObject, 0x1368995d, sTuning_15d9674);
            ReadPropertyUInt32(propList.mpObject, 0xd8f99173, sTuning_15d9670);
            ReadPropertyUInt32(propList.mpObject, 0x7717409a, sTuning_150c884);
            sTuning_150c884 *= 1000;
            ReadPropertyFloat(propList.mpObject, 0x11074696, sTuning_150c888);
            ReadPropertyFloat(propList.mpObject, 0x61ecd45c, sTuning_150c88c);
            ReadPropertyFloat(propList.mpObject, 0x518ea467, sTuning_15d9650);
            ReadPropertyFloat(propList.mpObject, 0x518ea466, sTuning_15d9654);
            ReadPropertyFloat(propList.mpObject, 0x518ea465, sTuning_15d9658);
            ReadPropertyFloat(propList.mpObject, 0x518ea464, sTuning_15d965c);
            ReadPropertyFloat(propList.mpObject, 0x518ea463, sTuning_15d9660);
            ReadPropertyFloat(propList.mpObject, 0x518ea462, sTuning_15d9664);
            ReadPropertyFloat(propList.mpObject, 0xd899bec5, sTuning_150c900);
            ReadPropertyFloat(propList.mpObject, 0x4745de1b, sTuning_15d96b8);
            ReadPropertyFloat(propList.mpObject, 0x57634c7c, sTuning_150c890);
            ReadPropertyFloat(propList.mpObject, 0x57634c7d, sTuning_150c894);
            ReadPropertyFloat(propList.mpObject, 0x57634c7e, sTuning_150c898);
            ReadPropertyFloat(propList.mpObject, 0x57634c7f, sTuning_150c89c);
            ReadPropertyFloat(propList.mpObject, 0x57634c78, sTuning_150c8a0);
            ReadPropertyFloat(propList.mpObject, 0x57634c79, sTuning_150c8a4);
            ReadPropertyFloat(propList.mpObject, 0x57634c7a, sTuning_150c8a8);
            ReadPropertyFloat(propList.mpObject, 0xb6ec210b, sTuning_150c8ac);
            ReadPropertyFloat(propList.mpObject, 0x71c653b2, sTuning_150c8b0);
            ReadPropertyFloat(propList.mpObject, 0xffb2d688, sTuning_150c8b4);
            ReadPropertyFloat(propList.mpObject, 0x49c7436e, sTuning_150c8b8);
            ReadPropertyFloat(propList.mpObject, 0x0a97c583, sTuning_150c8bc);
            ReadPropertyFloat(propList.mpObject, 0x6b559718, sTuning_150c8c0);
            ReadPropertyUInt32(propList.mpObject, 0x24cb8070, sTuning_150c8c4);
            GetPropertyAsVector2(propList.mpObject, 0xb237e271, &sTuning_15d9834);
            GetPropertyAsVector2(propList.mpObject, 0xf237e2d7, &sTuning_15d9764);
            GetPropertyAsVector2(propList.mpObject, 0x5237e2d8, &sTuning_15d9a68);
            ReadPropertyFloat(propList.mpObject, 0xd237f426, sTuning_15d9668);
            ReadPropertyBool(propList.mpObject, 0x32380e2c, sTuning_15d966c);
            ReadPropertyUInt32(propList.mpObject, 0x523a8f4c, sTuning_150c8c8);
            ReadPropertyFloat(propList.mpObject, 0x036ad4db, sTuning_150c8cc);
            GetPropertyAsVector2(propList.mpObject, 0x036ad587, &sTuning_15d992c);
            ReadPropertyFloat(propList.mpObject, 0xbf623956, sTuning_150c8d4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c1, sTuning_150c8e4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c0, sTuning_150c8e8);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c3, sTuning_150c8ec);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c2, sTuning_150c8f0);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c5, sTuning_150c8f4);
            ReadPropertyFloat(propList.mpObject, 0xa597b8c4, sTuning_150c8f8);
            GetPropertyAsFloat(propList.mpObject, 0xa597b8c7, &sTuning_150c8fc);
            GetPropertyAsFloat(propList.mpObject, 0x81275d0a, &sTuning_150c8d0);
            GetPropertyAsUint32(propList.mpObject, 0x32ca0de1, &sTuning_150c8d8);
            sTuning_150c8d8 *= 1000;
            GetPropertyAsFloat(propList.mpObject, 0x3e7cf53b, &sTuning_150c8dc);

            int numItems = 0;
            float* vectors = 0;
            if (GetPropertyAsFloatArray(propList.get(), 0x0610d73b, &numItems, &vectors)) {
                sTuning_15d976c.resize(numItems);
                for (int i = 0; i < numItems; i++)
                    sTuning_15d976c.mpBegin[i] = vectors[i];
            }

            GetPropertyAsUint32(propList.mpObject, 0x0435d996, &sTuning_150c8e0);
            sTuning_150c8e0 *= 1000;
            GetPropertyAsFloat(propList.mpObject, 0x5c74d18b, &sTuning_150c904);

            int numVectors;
            Vector3* source;
            if (GetPropertyAsVector3Array(propList.get(), 0x53d75041, &numVectors, &source)) {
                sTuning_15d96fc.resize(numVectors);
                for (int i = 0; i < numVectors; i++)
                    sTuning_15d96fc.mpBegin[i] = source[i];
            }
            int arraySize;
            Vector3* vectorData;
            if (GetPropertyAsVector3Array(propList.get(), 0xf3d75063, &arraySize, &vectorData)) {
                sTuning_15d99fc.resize(arraySize);
                for (int i = 0; i < arraySize; i++)
                    sTuning_15d99fc.mpBegin[i] = vectorData[i];
            }
            int size;
            Vector3* src;
            if (GetPropertyAsVector3Array(propList.get(), 0x33f6c3c4, &size, &src)) {
                sTuning_15d97fc.resize(size);
                for (int i = 0; i < size; i++)
                    sTuning_15d97fc.mpBegin[i] = src[i];
            }
        }
    }
}
}  // namespace SP

// @ 0x004d34f0
void InitStatics()
{
    LoadSpeciesTuning(0);
}

// @ 0x004d3500
float Blend(float, float, float a, float, float b, float c, float d)
{
    float k1 = 40.0f;
    float kr = 20.0f;
    float k2 = 20.0f;
    float k3 = (b * k1 + a) + c * kr + d * k2;
    return k3;
}

// @ 0x004d3570
uint32_t MapGetFieldC(SpeciesMap* m, uint32_t key)
{
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return it.mpNode->v[2];
    return 0;
}

// @ 0x004d35d0
uint32_t MapGetClamped(SpeciesMap* m, uint32_t key)
{
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) { if (it.mpNode->v[2] > 5) return 5; else return it.mpNode->v[2]; }
    return 0;
}

// @ 0x004d3640
uint32_t MapGetField4(SpeciesMap* m, uint32_t key)
{
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return it.mpNode->v[0];
    return 0;
}

// @ 0x004d36a0
void* MapGetPtr(SpeciesMap* m, uint32_t key)
{
    MapIter it = m->find(key);
    MapIter e = m->end();
    if (it != e) return &it.mpNode->v[0];
    static MapDefault def;
    return &def;
}

// @ 0x004d3760
CreatureAbility::CreatureAbility()
: mType(0), mCategory(1), mSocialCategory(0),
    nName(),
    mVerbIconImageID(0),
    mVerbIconGameLayout(),
    mVerbIconTriggerKey(0),
    mDamage(0.0f), mRangedDamage(0.0f), mRazeDamage(0.0f),
    mAnimationIDs(), mFollowerAnimationIDs(),
    mVerbIconRepresentativeAnimation(0), mBabyGameAnimationID(0), mBuildingSpecificAnimationID(0), mEffectKind(0),
    mEffectDuration(0.0f), mEffectDamage(0.0f),
    mMuzzleEffectID(0), mTrailEffectID(0), mImpactEffectID(0),
    mConeDist(0.0f), mConeRadius(0.0f), mRefresh(5.0f), mDuration(0.0f), mRecharge(0.0f),
    mRange(10.0f), mEnergyCost(0.0f), mSpeed(5.0f),
    mSpeedGear(0),
    mCombatEffectTypes(), mCombatEffectPercentages(), mCombatEffectEffectIds(),
    mRushingRange(0.0f), mRushingAnimationID(0xffffffff), mRushingSpeed(20.0f),
    mbRushingTargetedCharge(true), mbRushingDoDamage(false),
    mAdventurerEnergyCost(0.0f), mSprintBuff(2), mDNAPoints(0.0f), mLevelMultiplier(1.0f),
    mbIsSpecial(false), mbUseForBabyGame(false),
    mHintName(0), mAreaOfEffect(0.0f),
    mReactionAnimation(0xffffffff), mReactionDeathAnimation(0xffffffff), mReactionLiveAnimation(0xffffffff),
    mReactionDuration(0.0f),
    mpPropList(),
    mRangeMin(0.0f), mAvatarRangeMin(0.0f)
{
}

// @ 0x004d3b80
CreatureAbility::~CreatureAbility()
{}

// @ 0x004d3cd0
uint32_t TuningObj::GetAt(uint32_t index)
{
    int* vec = (int*)((char*)this + 0x48);
    int count = (vec[1] - vec[0]) >> 2;
    if (count == 0 || index >= (uint32_t)count)
        return 0x04330667;
    return *(uint32_t*)(*(int*)((char*)this + 0x48) + index * 4);
}

// @ 0x004d3d40
int TuningObj::GetActive()
{
    if (m74 != 0)
        return m74;
    else
        return m70;
}

// @ 0x004d3d70
float TuningObj::GetBound(bool which)
{
    if (which)
        return mMax;
    else
        return mMin;
}

// @ 0x004d3da0
void TuningObj::SetBounds(float lo, float hi)
{
    mMin = lo;
    mMax = hi;
}

// @ 0x004d3dd0
cSpeciesProfile::cSpeciesProfile(const ResKey& key, bool flag)
: capsInfos(CapsTag1(), CapsTag2()),
    mSkinColors(),
    animatedCreatureKey(), animatedBabyKey(), animatedCreatureName(), animatedCreatureDesc(),
    m53c(0),
    m540(0),
    m544(0),
    m548(0.0f),
    m54c(0.0f),
    m550(0.0f),
    m56c(100.0f),
    m570(200.0f),
    m574(0.0f),
    m578(false),
    m57c(0),
    m588(1),
    m58c(0.0f),
    m590(0.0f),
    m594(0.0f),
    m598(0.0f),
    m59c(0.0f),
    m5a0(0.0f),
    m5a4(0.0f),
    m5a8(0.0f),
    m5ac(0.0f),
    m5b0(0.0f),
    m5b4(0.0f),
    m5b8(0.0f),
    m5bc(0.0f),
    m5c0(0.0f),
    m5c4(0.0f),
    m5c8(5000),
    m5cc(1.0f),
    m5d0(2),
    m5d4(0),
    m5d8(0),
    m5dc(0),
    m5e0(0),
    m5e4(0),
    m5e8(0),
    m5ec(0),
    m5f0(0),
    m5f8(0),
    m5fc(0),
    m600(0),
    m604(0),
    m608(0),
    m60c(0),
    m610(0),
    m614(0),
    m61c(0),
    m640(0.0f),
    m648(0),
    m64c(0),
    m650(0),
    m654(0),
    m658(0),
    m65c(0),
    m660(0),
    m664(0),
    m668(0),
    m66c(0.0f),
    m670(0),
    m674(0),
    m678(0),
    m67c(0),
    m680(0),
    m684(0),
    m688(0),
    m68c(0),
    m690(0),
    m694(0),
    m698(0),
    m69c(0),
    m6a0(0),
    m6a4(0),
    m6a8(0),
    m6ac(0),
    m6b0(0.0f),
    m6b4(0),
    m6b8(), m6cc(flag), m6d0(0), m6d4(), m73c(), m7a4(), m80c(false), m80d(false),
    m810(), m878(), m8e0(), m948(), m9b0()
{
    animatedCreatureKey = key;
    animatedBabyKey = key;
    if (key.instanceID != 0 && IsEditorGroup(animatedBabyKey.groupID))
        BadModelKey(&animatedBabyKey, 1);
}

// @ 0x004d44e0
void SpeciesDB_Op1(void* self)
{ (void)self; }

// @ 0x004d46b0
float SpeciesDB::GetScale()
{
    return mScale * 0.025f * 100.0f;
}

// @ 0x004d46d0
uint32_t SpeciesDB::FindField8(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 8) == id)
            return i;
    }
    return 0xffffffff;
}

// @ 0x004d4750
uint32_t SpeciesDB::FindField10(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 0x10) == id)
            return i;
    }
    return 0xffffffff;
}

// @ 0x004d47d0
void SpeciesDB_Op2(void* self)
{ (void)self; }

// @ 0x004d4ad0
void SpeciesDB_Op3(void* self)
{ (void)self; }

// @ 0x004d4f10
void SpeciesDB_Op4(void* self)
{ (void)self; }

// @ 0x004d8c10
void SpeciesProfile_Update(void* a, int b)
{ (void)a; (void)b; }

// @ 0x004d8ee0
int SpeciesProfile::GetVariantA(void* p)
{
    Update(p, 0);
    return (int)((char*)this + 0x810);
}

// @ 0x004d8f10
int SpeciesProfile::GetVariantB(void* p)
{
    int* pOwner = *(int**)((char*)p + 0x17c);
    int* pData = (int*)*pOwner;
    bool b = *(int*)((char*)pData + 0x31c) == mSelector;
    Update(p, b);
    int result;
    if (b)
        result = (int)((char*)this + 0x948);
    else
        result = (int)((char*)this + 0x878);
    return result;
}

// @ 0x004d8f90
int SpeciesProfile::GetVariantC(void* p)
{
    int* pOwner = *(int**)((char*)p + 0x17c);
    int* pData = (int*)*pOwner;
    bool b = *(int*)((char*)pData + 0x31c) == mSelector;
    Update(p, b);
    int result;
    if (b)
        result = (int)((char*)this + 0x9b0);
    else
        result = (int)((char*)this + 0x8e0);
    return result;
}

// @ 0x004d90a0
void cSpeciesProfile_FillInProfileValues(void* self)
{ (void)self; }

// @ 0x004d92b0
namespace SP {
bool ReadAbilityData(cCreatureAbility_s004d_92b0* ability, PropertyList_s004d_92b0* propList)
{
    ability->mpPropList = propList;
    GetPropertyAsText(propList, 0x1b7c544, &ability->mName);

    int iType = 0;
    GetInt32(propList, 0x1ba8c38, iType);
    ability->mType = iType;
    int category = 0;
    GetInt32(propList, 0x1ef3be2, category);
    ability->mCategory = category;
    int socialCategory = 0;
    GetInt32(propList, 0x743bdd6, socialCategory);
    ability->mSocialCategory = socialCategory;

    ability->mbIsSpecial = GetBoolValue(propList, 0x6270927);
    ability->mAdventurerEnergyCost = GetFloatValue(propList, 0x73b88ef, 0.0f);
    ability->mSprintBuff = 2;
    GetInt32(propList, 0x772e3a5, ability->mSprintBuff);
    ability->mAreaOfEffect = 0.0f;
    GetFloat(propList, 0x7460f10, ability->mAreaOfEffect);
    ability->mReactionAnimation = 0xffffffff;
    GetUInt32_s004d_92b0(propList, 0x75e00b7, ability->mReactionAnimation);
    ability->mReactionDeathAnimation = 0xffffffff;
    GetUInt32_s004d_92b0(propList, 0x7a7ffd5, ability->mReactionDeathAnimation);
    ability->mReactionLiveAnimation = 0xffffffff;
    GetUInt32_s004d_92b0(propList, 0x7a7ffd9, ability->mReactionLiveAnimation);
    ability->mReactionDuration = 0.0f;
    GetFloat(propList, 0x75e0100, ability->mReactionDuration);

    ability->mRefresh = GetFloatValue(propList, 0x1b8346e, 5.0f);
    ability->mRefresh = Max(ability->mRefresh, 0.1f);
    ability->mDuration = GetFloatValue(propList, 0x1c6c623, 0.0f);
    ability->mRecharge = GetFloatValue(propList, 0x5417d08, 0.0f);

    {
    int numAnimations = 0;
    uint32_t* pAnimations = 0;
    if (GetPropertyAsUint32Array(propList, 0x52047f7, &numAnimations, &pAnimations)) {
        ability->mAnimationIDs.clear();
        ScratchSlots<2>();
        ability->mAnimationIDs.reserve(numAnimations);
        for (int i = 0; i < numAnimations; i++) {
            uint32_t animationID = pAnimations[i];
            ability->mAnimationIDs.push_back(animationID);
        }
    }
    if (GetPropertyAsUint32Array(propList, 0x5204800, &numAnimations, &pAnimations)) {
        ability->mFollowerAnimationIDs.clear();
        ScratchSlots<2>();
        ability->mFollowerAnimationIDs.reserve(numAnimations);
        for (int i = 0; i < numAnimations; i++) {
            uint32_t animationID = pAnimations[i];
            ability->mFollowerAnimationIDs.push_back(animationID);
        }
    }

    ResourceKey animationKey = { 0, 0, 0 };
    if (GetPropertyAsKey(propList, 0x4d7ff37, &animationKey))
        ability->mVerbIconRepresentativeAnimation = animationKey.instanceID;
    GetUInt32_s004d_92b0(propList, 0x5e7eca0, ability->mBuildingSpecificAnimationID);
    GetUInt32_s004d_92b0(propList, 0x742b4dcf, ability->mBabyGameAnimationID);
    }

    {
    int numEffectTypes = 0;
    uint32_t* pEffectTypes = 0;
    if (GetPropertyAsUint32Array(propList, 0x423bc52, &numEffectTypes, &pEffectTypes)) {
        ScratchSlots<3>();
        ability->mCombatEffectTypes.resize(numEffectTypes);
        for (int i = 0; i < numEffectTypes; i++)
            ability->mCombatEffectTypes[i] = pEffectTypes[i];
    }
    int numEffectPercentages = 0;
    float* pEffectPercentages = 0;
    if (GetPropertyAsFloatArray(propList, 0x423bc50, &numEffectPercentages, &pEffectPercentages)) {
        ScratchSlots<3>();
        ability->mCombatEffectPercentages.resize(numEffectPercentages);
        for (int i = 0; i < numEffectPercentages; i++)
            ability->mCombatEffectPercentages[i] = pEffectPercentages[i];
    }
    int numEffectIds = 0;
    uint32_t* pEffectIds = 0;
    if (GetPropertyAsUint32Array(propList, 0x423bc51, &numEffectIds, &pEffectIds)) {
        ScratchSlots<3>();
        ability->mCombatEffectEffectIds.resize(numEffectIds);
        for (int i = 0; i < numEffectIds; i++)
            ability->mCombatEffectEffectIds[i] = pEffectIds[i];
    }

    int nKind = 0;
    GetInt32(propList, 0x21d798c, nKind);
    ability->mEffectKind = nKind;
    }
    GetFloat(propList, 0x2154c2a, ability->mEffectDuration);
    GetFloat(propList, 0x4a4ce5a, ability->mEffectDamage);
    GetFloat(propList, 0x1b8346a, ability->mDamage);
    GetFloat(propList, 0x558e32a, ability->mRangedDamage);
    ability->mRazeDamage = ability->mDamage * 0.5f;
    GetFloat(propList, 0x558e337, ability->mRazeDamage);
    GetUInt32_s004d_92b0(propList, 0x35f26c8, ability->mMuzzleEffectID);
    GetUInt32_s004d_92b0(propList, 0x35f26cc, ability->mTrailEffectID);
    GetUInt32_s004d_92b0(propList, 0x35f26d2, ability->mImpactEffectID);
    GetFloat(propList, 0x51dddd5, ability->mConeDist);
    GetFloat(propList, 0x51dddda, ability->mConeRadius);
    GetInt32(propList, 0x4dad031, ability->mVerbIconTriggerKey);
    GetPropertyAsKeyInstance(propList, 0x626efe0, &ability->mVerbIconImageID);
    GetPropertyAsKey(propList, 0x62f16d8, &ability->mVerbIconGameLayout);
    GetFloat(propList, 0x1b83470, ability->mRange);

    {
    float rangeMin = 0.0f;
    float avatarRangeMin = 0.0f;
    GetFloat(propList, 0x4a35ee9, rangeMin);
    if (propList->HasProperty(0x7fb05d2))
        GetFloat(propList, 0x7fb05d2, avatarRangeMin);
    else
        avatarRangeMin = rangeMin;
    ability->SetRangeMin(rangeMin, avatarRangeMin);
    }

    GetUInt32_s004d_92b0(propList, 0x4a3b2f8, ability->mRushingAnimationID);
    GetPropertyAsFloat(propList, 0x4a3b36c, &ability->mRushingRange);
    GetPropertyAsFloat(propList, 0x4ab0daf, &ability->mRushingSpeed);
    GetPropertyAsBool(propList, 0x6400f3f, &ability->mbRushingTargetedCharge);
    GetPropertyAsBool(propList, 0x642607a, &ability->mbRushingDoDamage);
    GetPropertyAsFloat(propList, 0x1c291d8, &ability->mEnergyCost);
    GetPropertyAsFloat(propList, 0x3601c39, &ability->mSpeed);
    GetPropertyAsUint32(propList, 0x73561a8f, &ability->mSpeedGear);
    GetPropertyAsFloat(propList, 0x39f727c, &ability->mDNAPoints);
    GetPropertyAsFloat(propList, 0xf96c61b7, &ability->mLevelMultiplier);
    GetPropertyAsBool(propList, 0x74163bdf, &ability->mbUseForBabyGame);

    switch (ability->mType) {
    case 0x1e:
        ability->mHintName = 0xeff9f865;
        break;
    case 0x1f:
        ability->mHintName = 0x256d59fb;
        break;
    case 0x20:
        ability->mHintName = 0xb6acd709;
        break;
    case 0x3d:
        ability->mHintName = 0xb6acd709;
        break;
    case 0x3e:
        ability->mHintName = 0xb6acd709;
        break;
    case 0x21:
        ability->mHintName = 0x45aa9fe5;
        break;
    case 0x22:
        ability->mHintName = 0x5d090c04;
        break;
    case 0x23:
        ability->mHintName = 0xf94611d9;
        break;
    case 0x24:
        ability->mHintName = 0x9e805e6c;
        break;
    case 0x25:
        ability->mHintName = 0xb1eb383a;
        break;
    case 0x40:
        ability->mHintName = 0x9e805e6c;
        break;
    }
    return true;
}
}  // namespace SP

// @ 0x004da330
void cSpeciesProfile_s004d_a330::GetUiName(WString* out)
{
    WString* pName = &mName;
    if (pName != out)
        out->assign(pName->mpBegin, pName->mpEnd);
    if (out->empty())
        out->sprintf(L"Species %d", mInstance);
}

// @ 0x004da3d0
uint32_t* GetValidatedSpeciesKey(uint32_t* out, uint32_t instance, bool flora)
{
    uint32_t keyInstance;              // actually the group id (slot -0x10)
    if (!flora)
        keyInstance = kCreatureEditorModelGroup;
    else
        keyInstance = kFloraEditorModelGroup;
    uint32_t group = instance;         // actually the instance (slot -0xc)
    uint32_t keyGroup = ((flora ? 0xffffffffu : 0u) & 0x17f7d701) + 0x2b978c46;  // type (slot -8)
    uint32_t keyType = keyInstance;    // group copy (slot -4)
    ResourceManager((uint32_t)&group);
    out[0] = group;
    out[1] = keyGroup;
    out[2] = keyType;
    return out;
}

// @ 0x004da440
namespace SP {
cSpeciesArchetype_s004d_a440::cSpeciesArchetype_s004d_a440()
: debugName(SpAllocatorTag())
	, archetypeID(0)
	, archetypeQueryID(0)
	, modelType(0)
	, slopeMin(0.0f)
	, slopeMax(0.0f)
	, slopeArea(0.0f)
	, altitudeMin(0.0f)
	, altitudeMax(0.0f)
	, waterDistanceMin(0.0f)
	, waterDistanceMax(0.0f)
	, numCreaturesMin(0.0f)
	, numCreaturesMax(0.0f)
	, creatureShortfallMin(0.0f)
	, creatureShortfallMax(0.0f)
	, numNestsMin(0.0f)
	, numNestsMax(0.0f)
	, exclusiveAreaRadiusGroupSmall(0.0f)
	, exclusiveAreaRadiusGroupMedium(0.0f)
	, exclusiveAreaRadiusGroupLarge(0.0f)
	, respawnRate(0.0f)
	, dnaPointsEvolutionThresholds(kMaxFloat, kMaxFloat)
	, evoPointsRewarded(0.0f)
	, evoPointsRewardedSocial(0.0f)
	, evoPointsRewardedOther(0.0f)
	, partUnlockLevelReward(-1)
	, foodChainLevel(0)
	, bUseOrigin(false)
	, scaleMultiplier(0.0f)
	, overrideHeight(0.0f)
	, hitpointOverride(0.0f)
	, damageMultiplier(0.0f)
	, socialPower(0.0f)
	, baseSightRadius(0.0f)
	, baseSightAngle(0.0f)
	, basePerceptionRadius(0.0f)
	, abilityPerceptionMultiplier(1.0f)
	, territoryRadius(1.0f)
	, percentGuards(1.0f)
	, percentBabies(1.0f)
	, foodValue(1.0f)
	, numGuardLocations(1)
	, guardsPerLocation(1)
	, guardLocationRadiusRange(10.0f, 15.0f)
	, guardPositionDurationRange(60.0f, 160.0f)
	, guardLocationAreaBuffer(1.25f)
	, bIsEpic(false)
	, defaultPersonality(0)
	, initialAvatarRelationship(0)
	, groupSizeRange(1.0f, 1.0f)
	, originDistances(SpAllocatorTag())
	, relatedArchetypes(SpAllocatorTag())
	, archetypeGenerations(SpAllocatorTag())
	, eggIndex(0)
	, schedulerTemplates(SpAllocatorTag())
	, fightGroupSize(4)
	, standardAttacksPerSpecial(2)
	, numInGroupToStartWithSpecial(0)
	, numToKillForFearfulRelationship(1)
	, numToKillForExtinction(5)
	, numToImpressForCurious(1)
	, numToImpressForFriendly(3)
	, numToImpressForBestFriends(6)
	, relationshipCuriousReward(0)
	, relationshipFriendlyReward(0)
	, relationshipBestFriendsReward(0)
	, relationshipFearedReward(0)
	, extinctionReward(0)
	, numSocialProposals(0)
	, socialTimeBeforeDrain(0.0f)
	, socialDrainRate(0.0f)
	, socialProposalLimit(1)
	, attacked_SpeciesHelpRadius(0.0f)
	, attacked_MaxSpeciesToAlert(0)
{
}
}  // namespace SP

// @ 0x004db1b0
void SpeciesCheat_Op1(void* self)
{ (void)self; }

// @ 0x004db2c0
void SpeciesCheat_Op2(void* self)
{ (void)self; }

// @ 0x004db3e0
void PaintSystem::Destroy()
{
    *(void**)this = (void*)g_paintSystemVtblA;
    ((Sub0*)this)->f();
    int* p = (int*)((char*)this + 0xd0);
    if (*p != 0)
        ((Sub1*)p)->f();
    ((Sub2*)((char*)this + 0xb0))->f();
    ((Sub3*)((char*)this + 0x84))->f();
    ((Sub3*)((char*)this + 0x64))->f();
    ((Sub3*)((char*)this + 0x44))->f();
    ((Sub3*)((char*)this + 0x24))->f();
    ((Sub3*)((char*)this + 4))->f();
    *(void**)this = (void*)g_paintSystemVtblB;
}

// @ 0x004db470
void SpeciesCheat_Op3(void* self)
{ (void)self; }

// @ 0x004db620
void Connector::Init(void* pObj, int b, int c, uint32_t n)
{
    mpObj = pObj;
    mnB = b;
    mnC = c;
    mnD = n;
    mnE = 0;
    if (pObj != 0 && b != 0 && mnC != 0) {
        for (uint32_t i = 0; i < n; i = i + 1) {
            ((IVtbl9*)pObj)->v09(b, *(int*)(c + i * 4));
        }
    }
}

// @ 0x004db6b0
char const * SP::cSpeciesCheat::Description(EA::ArgScript::tHelpType param) const
{
    if (param == 0)
        return "Used to test species queries to the OTDB";
    else
        return "[-<param> <min> <max> [-<param> <min> <max>]...] | [-dump <param>] | [-dumpFull <param>]\n"
           "-cost <min> <max>\n-baseGear <min> <max>\n-height <min> <max>\n-carnivore <min> <max>\n"
           "-herbivore <min> <max>\n-numGraspers <min> <max>\n-totalAttack <min> <max>\n"
           "-attack <min> <max>\n-cuteness <min> <max>\n-totalSocial <min> <max>\n-social <min> <max>\n"
           "-numFeet <min> <max>\n-meanLookingScore <min> <max>\n-biteCapRange <min> <max>\n"
           "-strikeCapRange <min> <max>\n-chargeCapRange <min> <max>\n-spitCapRange <min> <max>\n"
           "-singCapRange <min> <max>\n-danceCapRange <min> <max>\n-charmCapRange <min> <max>\n"
           "-poseCapRange <min> <max>\n-glideCapRange <min> <max>\n-stealthCapRange <min> <max>\n"
           "-sprintCapRange <min> <max>\n-senseCapRange <min> <max>\n-healthCapRange <min> <max>\n";
}

// @ 0x004db6e0
namespace SP {
void cSpeciesCheat_s004d_b6e0::Execute(cArguments* pArguments)
{
    IObjectTemplateDB* pDB = ObjectTemplateDB();
    VecC constraints;
    char tagC;
    constraints.Ctor(&tagC);
    uint32_t nParams = 26;

    for (uint32_t i = 0; i < nParams; i = i + 1) {
        if (pArguments->HasArgument(gSpeciesParams[i].name)) {
            const char** pOpts = pArguments->OptionArguments(gSpeciesParams[i].name, 2);
            if (pOpts) {
                char* endp0;
                char* endp1;
                float fMin = (float)strtod(pOpts[0], &endp0);
                float fMax = (float)strtod(pOpts[1], &endp1);
                Constraint c;
                constraints.PushBack(c.Construct(gSpeciesParams[i].id, 0, fMin, fMax));
                c.inner.Dtor();
            } else {
                ArgScriptOutput(mParser, "Usage:\n species_query -%s  <min> <max>\n",
                                gSpeciesParams[i].name);
            }
        }
    }

    if (!constraints.Empty()) {
        char tagR;
        VecK results;
        results.Ctor(&tagR);
        pDB->QueryMatches(&results, &constraints);
        if (!results.Empty()) {
            Item12* pEnd = results.e;
            for (Item12* p = results.b; p != pEnd; p = p + 1) {
                WString_s004d_b6e0 path;
                GetManager_s004d_b6e0()->GetPath(p, &path);
                ArgScriptOutput(mParser, "%ls\n", path.b);
                path.FreeBuffer();
            }
        }
        for (Item12* q = results.b; q < results.e; q = q + 1) { }
        results.Dtor();
        constraints.Dtor();
        return;
    }

    if (pArguments->HasArgument("dumpFull")) {
        bool bDone = false;
        const char** pOpts = pArguments->OptionArguments("dumpFull", 1);
        if (pOpts) {
            uint32_t k;
            for (k = 0; k < nParams; k = k + 1) {
                if (strcmp(gSpeciesParams[k].name, pOpts[0]) == 0) break;
            }
            if (k < nParams) {
                char tagI, tagF;
                VecK items;
                items.Ctor(&tagI);
                VecF floats;
                floats.Ctor(&tagF);
                if (pDB->GetParameterValues(gSpeciesParams[k].id, &floats, &items)) {
                    bDone = true;
                    WString_s004d_b6e0 path;
                    uint32_t n = (uint32_t)(((char*)items.e - (char*)items.b) / 12);
                    for (uint32_t a = 0; a < n; a = a + 1) {
                        float val = floats.b[a];
                        Item12* pItem = (Item12*)((char*)items.b + a * 12);
                        GetFullPath(pItem, &path);
                        ArgScriptOutput(mParser, "%f\t%ls\n", (double)val, path.b);
                    }
                    path.FreeBuffer();
                }
                for (float* q = floats.b; q < floats.e; q = q + 1) { }
                floats.Dtor();
                for (Item12* q = items.b; q < items.e; q = q + 1) { }
                items.Dtor();
            }
        }
        if (!bDone) {
            ArgScriptOutput(mParser, "Usage:\n species_query -dumpFull <parameter name>\n");
        }
    }
    else if (pArguments->HasArgument("dump")) {
        bool bDone = false;
        const char** pOpts = pArguments->OptionArguments("dump", 1);
        if (pOpts) {
            uint32_t k;
            for (k = 0; k < nParams; k = k + 1) {
                if (strcmp(gSpeciesParams[k].name, pOpts[0]) == 0) break;
            }
            if (k < nParams) {
                char tagF;
                VecF floats;
                floats.Ctor(&tagF);
                if (pDB->GetParameterRange(gSpeciesParams[k].id, &floats)) {
                    bDone = true;
                    float* pEnd = floats.e;
                    for (float* p = floats.b; p != pEnd; p = p + 1) {
                        ArgScriptOutput(mParser, "%f\n", (double)*p);
                    }
                }
                for (float* q = floats.b; q < floats.e; q = q + 1) { }
                floats.Dtor();
            }
        }
        if (!bDone) {
            ArgScriptOutput(mParser, "Usage:\n species_query -dump <parameter name>\n");
        }
    }
    else if (pArguments->HasArgument("speciesDump")) {
        pArguments->OptionArguments("speciesDump", 0);
        WString_s004d_b6e0 csvPath;
        WString_s004d_b6e0 dataDir;
        GetDataPath(0xa02150, &dataDir, 0);
        Format(&csvPath, L"%lsspecies_dump.csv", dataDir.b);

        IFileStream* pFile = (IFileStream*)NewObject(0x22c);
        if (pFile) {
            pFile = FileStreamCtor(pFile, csvPath.b);
        } else {
            pFile = 0;
        }
        IFileStream* pStream = pFile;
        if (pStream) pStream->AddRef();
        pStream->Open(3, 2, 1, 0);

        char tagH, tagM;
        WString_s004d_b6e0 line;
        line.Ctor(L"File,", &tagH);
        CString out8;
        WString_s004d_b6e0 rowPath;
        RbMap perItem;
        perItem.Ctor(&tagM);

        for (uint32_t p = 0; p < nParams; p = p + 1) {
            char tagA, tagB;
            VecK items;
            items.b = 0; items.e = 0; items.cap = 0;
            items.AllocCtor(&tagA);
            VecF floats;
            floats.b = 0; floats.e = 0; floats.cap = 0;
            floats.AllocCtor(&tagB);
            items.Reserve(100);
            floats.Reserve(100);
            if (pDB->GetParameterValues(gSpeciesParams[p].id, &floats, &items)) {
                WString_s004d_b6e0 name16;
                ConvertToString16(&name16, gSpeciesParams[p].name, -1);
                AppendFormat(&line, L"%ls,", name16.b);
                uint32_t n = (uint32_t)(floats.e - floats.b);
                for (uint32_t j = 0; j < n; j = j + 1) {
                    float val = floats.b[j];
                    Item12* pItem = (Item12*)((char*)items.b + j * 12);
                    PushBackFloat(perItem.Index(pItem), &val);
                }
                name16.FreeBuffer();
            }
            for (float* q = floats.b; q < floats.e; q = q + 1) { }
            floats.Dtor();
            for (Item12* q = items.b; q < items.e; q = q + 1) { }
            items.Dtor();
        }

        {   // header row
            const wchar_t* pe = gNewlineW;
            while (*pe) pe = pe + 1;
            line.Append(gNewlineW, gNewlineW + (pe - gNewlineW));
            CString tmp;
            CString* r = ConvertToString8(&tmp, &line);
            if (r != &out8) out8.assign(r->b, r->e);
            tmp.Dtor();
            pStream->Write(out8.b, (uint32_t)(out8.e - out8.b));
        }

        RbIter it;
        RbIter itEnd;
        it.Ctor(((void**)&perItem)[2]);                // begin (anchor.left)
        itEnd.Ctor(&((void**)&perItem)[1]);            // end (anchor)
        for (; it.node != itEnd.node; it.Inc()) {
            FloatVecNode* pNode = it.Deref();
            Item12* pKey = &pNode->key;
            VecF* pVals = &it.Deref()->vals;
            GetFullPath(pKey, &rowPath);
            Format(&line, L"%ls,", rowPath.b);
            float* pv = pVals->b;
            float* pvEnd = pVals->e;
            for (; pv != pvEnd; pv = pv + 1) {
                float val = *pv;
                AppendFormat(&line, L"%f,", (double)val);
            }
            const wchar_t* pe = gNewlineW;
            while (*pe) pe = pe + 1;
            line.Append(gNewlineW, gNewlineW + (pe - gNewlineW));
            CString tmp;
            CString* r = ConvertToString8(&tmp, &line);
            if (r != &out8) out8.assign(r->b, r->e);
            tmp.InlineFree();
            pStream->Write(out8.b, (uint32_t)(out8.e - out8.b));
        }
        pStream->Flush();
        pStream->Close();
        OpenFile(csvPath.b);
        perItem.DoNuke(((void**)&perItem)[3]);
        rowPath.FreeBuffer();
        out8.Dtor();
        line.FreeBuffer();
        if (pStream) pStream->Release();
        dataDir.FreeBuffer();
        csvPath.FreeBuffer();
    }

    constraints.Dtor();
}
}  // namespace SP

// @ 0x004dc660
void SP::cSpeciesCheat::GetFullPath(EA::ResourceMan::Key const & key, eastl::basic_string<wchar_t, eastl::allocator> & out)
{
    (void)key; (void)out;
}

// @ 0x004dc730
unsigned int SP::cPlantSummarizer::GetVersion() const
{
    return g_plantStaticType;
}

// @ 0x004dc740
unsigned int SP::cPlantSummarizer::GetResType(unsigned int p) const
{
    if (p == 0)
        return 0x438f6347;
    return -1;
}

// @ 0x004dc760
bool SP::cPlantSummarizer::ExtractParameters(EA::ResourceMan::Key const & desc, eastl::vector<SP::FunctionalMatch::DeclareParam, eastl::sp_vector_allocator> & out) const
{
    (void)desc; (void)out;
    return false;
}

// @ 0x004dc920
unsigned int SP::cSpeciesSummarizer::GetVersion() const
{
    return g_speciesStaticType;
}

// @ 0x004dc930
unsigned int SP::cSpeciesSummarizer::GetResType(unsigned int p) const
{
    if (p == 0)
        return 0x2b978c46;
    return -1;
}

// @ 0x004dc950
bool SP::cSpeciesSummarizer::ExtractParameters(EA::ResourceMan::Key const & desc, eastl::vector<SP::FunctionalMatch::DeclareParam, eastl::sp_vector_allocator> & out) const
{
    (void)desc; (void)out;
    return false;
}

// @ 0x004dcaa0
void SP::cSPEditorSpeciesManager_s004d_c660::Teardown()
{
}

// @ 0x004dcee0
bool SP::cSPEditorSpeciesManager_s004d_c660::HandleMessage(int msgId, void* payload)
{
    (void)msgId; (void)payload;
    return false;
}

// @ 0x004df2d0
namespace SP {
float RandomInRange(const Vector2_s004d_f2d0& range)
{
    return (float)RandomRange(&sMathRandom, range[0], range[1]);
}
}  // namespace SP

// @ 0x004df310
namespace SP {
void cSPEditorSpeciesManager_s004d_f2d0::SetAvatarSpecies(const Key_s004d_f2d0& key)
{
    mAvatarSpeciesKey = key;
    if (key.mInstance)
        ObjectTemplateDB_s004d_f2d0()->Prefetch(key, true);
    MessageBasicRC5 msg(0x3795725);
    ScratchSlots<2>();
    msg.SetUint32(0, key.mType);
    msg.SetUint32(1, key.mInstance);
    msg.SetUint32(2, key.mGroup);
    ScratchSlots<1>();
    MessageServer()->MessageSend(msg.mId, &msg, 0);
}
}  // namespace SP

// @ 0x004df3e0
namespace SP {
void cSPEditorSpeciesManager_s004d_f2d0::SetAvatarProfile(cSpeciesProfile_s004d_f2d0* pProfile)
{
    SetAvatarSpecies(pProfile->mSpeciesKey);
}
}  // namespace SP

// @ 0x004df420
namespace SP {
cSpeciesProfile_s004d_f2d0* cSPEditorSpeciesManager_s004d_f2d0::GetAvatarProfile()
{
    return GetProfile(mAvatarSpeciesKey);
}
}  // namespace SP

// @ 0x004df440
namespace SP {
cSpeciesProfile_s004d_f2d0* cSPEditorSpeciesManager_s004d_f2d0::GetPlantProfile(const Key_s004d_f2d0& key)
{
    ScratchSlots<27>();
    cSpeciesProfile_s004d_f2d0* pProfile = FindProfile(mPlantSpecies, key);
    if (!pProfile) {
        Key_s004d_f2d0 k = key;
        if (ResourceExists(&k)) {
            pProfile = FindProfile(mPlantSpecies, k);
            if (!pProfile) {
                cSpeciesProfile_s004d_f2d0* pNew = new ("Simulator/cSpeciesProfile", 0, 0, 0, 0) cSpeciesProfile_s004d_f2d0(k, true);
                mPlantSpecies[k] = pNew;
                pProfile = FindProfile(mPlantSpecies, k);
            }
        }
    }
    return pProfile;
}
}  // namespace SP

// @ 0x004df550
namespace SP {
cSpeciesProfile_s004d_f2d0* cSPEditorSpeciesManager_s004d_f2d0::GetProfile(const Key_s004d_f2d0& key)
{
    if (!key.mInstance && !mAvatarSpeciesKey.mInstance)
        return 0;
    ScratchSlots<27>();
    cSpeciesProfile_s004d_f2d0* pProfile = FindProfile(mSpecies, key);
    if (!pProfile) {
        Key_s004d_f2d0 k = key;
        if (!k.mInstance) {
            k = mAvatarSpeciesKey;
            pProfile = FindProfile(mSpecies, k);
            if (pProfile)
                return pProfile;
        }
        if (ResourceExists(&k)) {
            pProfile = FindProfile(mSpecies, k);
            if (!pProfile) {
                cSpeciesProfile_s004d_f2d0* pNew = new ("Simulator/cSpeciesProfile", 0, 0, 0, 0) cSpeciesProfile_s004d_f2d0(k, false);
                mSpecies[k] = pNew;
                pProfile = FindProfile(mSpecies, k);
            }
        }
    }
    return pProfile;
}
}  // namespace SP

// @ 0x004df6d0
namespace SP {
cSpeciesProfile_s004d_f2d0* cSPEditorSpeciesManager_s004d_f2d0::FindProfile(eastl::SpeciesMap_s004d_f2d0& map, const Key_s004d_f2d0& key)
{
    ScratchSlots<14>();
    eastl::SpeciesMap_s004d_f2d0::const_iterator it = map.find(key);
    if (it != map.end() && it.mpNode->mpProfile) {
        cSpeciesProfile_s004d_f2d0* pProfile = it.mpNode->mpProfile;
        if (!pProfile->mbLoaded) {
            InitStatics();
            if (!pProfile->Load(pProfile->mSpeciesKey))
                return 0;
        }
        return pProfile;
    }
    return 0;
}
}  // namespace SP

// @ 0x004df790
namespace SP {
bool cSPEditorSpeciesManager_s004d_f2d0::GetDefaultReplacementKey(const Key_s004d_f2d0& key, Key_s004d_f2d0& outKey)
{
    cSpeciesArchetype_s004d_f2d0* pArchetype = GetSpeciesArchetype(0xdada0591, 0);
    if (pArchetype)
        return GetReplacementKeyForArchetype(key, pArchetype, outKey);
    return false;
}
}  // namespace SP

// @ 0x004df7d0
namespace SP {
bool cSPEditorSpeciesManager_s004d_f2d0::GetReplacementKey(const Key_s004d_f2d0& key, uint32_t archetypeId, Key_s004d_f2d0& outKey)
{
    cSpeciesArchetype_s004d_f2d0* pArchetype = GetSpeciesArchetype(archetypeId, 0);
    if (!pArchetype)
        pArchetype = GetSpeciesArchetype(0xdada0591, 0);
    if (pArchetype)
        return GetReplacementKeyForArchetype(key, pArchetype, outKey);
    return false;
}
}  // namespace SP

// @ 0x004df830
namespace SP {
bool cSPEditorSpeciesManager_s004d_f2d0::GetReplacementKeyForArchetype(const Key_s004d_f2d0& key, cSpeciesArchetype_s004d_f2d0* pArchetype, Key_s004d_f2d0& outKey)
{
    eastl::SpeciesMap_s004d_f2d0::iterator it = mReplacementSpecies.find(key);
    if (it != mReplacementSpecies.end()) {
        cSpeciesProfile_s004d_f2d0* pProfile = it.mpNode->mpProfile;
        outKey = pProfile->mSpeciesKey;
        return true;
    }
    it = mReplacementCache.find(key);
    if (it != mReplacementCache.end()) {
        delete it.mpNode->mpProfile;
        mReplacementCache.erase(it);
    }
    ConstraintVector constraints = ConstraintVector(DefaultAllocTag());
    constraints.reserve(2);
    constraints.push_back(FunctionalMatch::Constraint_s004d_f2d0(0x3cc89b1, 0, 0x913b23be));
    ProfileVector profiles;
    int n = FindMatchingCreatures(profiles, pArchetype, 1, 0, false, constraints);
    if (!n)
        n = FindMatchingCreatures(profiles, pArchetype, 1, 0, true, constraints);
    if (n) {
        cSpeciesProfile_s004d_f2d0* pProfile = profiles[0];
        outKey = pProfile->mSpeciesKey;
        mReplacementSpecies[key] = pProfile;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x004dfb50
namespace SP {
bool cSPEditorSpeciesManager_s004d_f2d0::UpdateProfile(cSpeciesProfile_s004d_f2d0* pNewProfile, const Key_s004d_f2d0& key)
{
    Key_s004d_f2d0 oldKey = pNewProfile->mSpeciesKey;
    cSpeciesProfile_s004d_f2d0* pProfile = pNewProfile;
    if (pProfile) {
        bool bResult = pProfile->Load(key);
        if (bResult) {
            if (oldKey != key) {
                ScratchSlots<12>();
                eastl::SpeciesMap_s004d_f2d0::iterator it = mSpecies.find(key);
                if (it != mSpecies.end()) {
                    cSpeciesProfile_s004d_f2d0* pOld = it.mpNode->mpProfile;
                    delete pOld;
                }
                mSpecies[key] = pProfile;
                mSpecies.erase(oldKey);
                mOldSpeciesMapping[oldKey] = pProfile;
            }
            ScratchSlots<52>();
            if (oldKey == mAvatarSpeciesKey)
                SetAvatarSpecies(key);
        }
        return bResult;
    }
    return false;
}
}  // namespace SP

// @ 0x004dfd50
namespace SP {
int cSPEditorSpeciesManager_s004d_f2d0::GetMatchingPlantProfiles(ProfileVector& results, int maxCount, int plantType)
{
    IObjectTemplateDB_s004d_f2d0* pDB = ObjectTemplateDB_s004d_f2d0();
    if (pDB) {
        ConstraintVector constraints(1, FunctionalMatch::Constraint_s004d_f2d0(0x2dd90af, 0, 0x438f6347));
        if (plantType != -1)
            constraints.push_back(FunctionalMatch::Constraint_s004d_f2d0(0x2dc9d1e, 0, plantType));
        KeyVector keys;
        pDB->FindTemplates(keys, maxCount, constraints);
        int n = 0;
        for (Key_s004d_f2d0 *it = keys.mpBegin, *itEnd = keys.mpEnd; n < maxCount && it != itEnd; ++it) {
            const Key_s004d_f2d0* pKey = it;
            if (pKey->mGroup) {
                cSpeciesProfile_s004d_f2d0* pProfile = GetPlantProfile(*pKey);
                if (pProfile)
                    results[n++] = pProfile;
                else
                    pDB->Remove(*pKey, 0);
            }
        }
        return n;
    }
    return 0;
}
}  // namespace SP

// @ 0x004e01d0
namespace SP {
void cEditorEventQueue::QueueEvent(cEditorEvent* pEvent)
{
    switch (pEvent->mType) {
    case 0: {
        EA::AutoRefCount_s004e_01d0<cEditorEvent> ref(pEvent);
        ScratchSlots<6>();
        mEvents.push_back(ref);
        break;
    }
    case 1: {
        EA::AutoRefCount_s004e_01d0<cEditorEvent> ref(pEvent);
        ScratchSlots<6>();
        mEvents.push_back(ref);
        break;
    }
    case 2: {
        if (pEvent->mSubType == 0xe)
            mLastValue = pEvent->mValue;
        EA::AutoRefCount_s004e_01d0<cEditorEvent> ref(pEvent);
        ScratchSlots<3>();
        mEvents.push_back(ref);
        break;
    }
    case 3: {
        EA::AutoRefCount_s004e_01d0<cEditorEvent> ref(pEvent);
        ScratchSlots<2>();
        mLateEvents.push_back(ref);
        break;
    }
    }
}
}  // namespace SP

// @ 0x005bf0a0
int HasEditorPropertyList(const EA::ResourceMan::Key_s005b_eaf0& key)
{
  App::IPropertyManager* pm = SP::PropertyManager_s005b_eaf0();
  if (pm && pm->HasPropertyList(key.mInstance, PropListGroup(key.mGroup)))
    return 1;
  return 0;
}

// @ 0x005bf0e0
int GetEditorPropertyList(const EA::ResourceMan::Key_s005b_eaf0& key, App::PropertyList_s005b_eaf0*& result)
{
  App::IPropertyManager* pm = SP::PropertyManager_s005b_eaf0();
  if (pm && pm->GetPropertyList(key.mInstance, PropListGroup(key.mGroup), result))
    return 1;
  return 0;
}

// @ 0x005bf120
bool SaveEditorPropertyList(const EA::ResourceMan::Key_s005b_eaf0& key, App::PropertyList_s005b_eaf0* list, int flags, EA::ResourceMan::IDatabase* db)
{
  uint32_t instance = key.mInstance;
  uint32_t group = PropListGroup(key.mGroup);
  if (!db)
    db = (EA::ResourceMan::IDatabase*)EA::ResourceMan::GetManager_s005b_eaf0()->GetDatabaseFor(key, 0, 0);
  if (!db || !(db->GetAccessFlags() & 2))
    db = SP::GetSaveArea(0x11ac19c);
  if (db && list) {
    ((uint32_t*)list)[2] = instance;
    ((uint32_t*)list)[3] = 0xb1b104;
    ((uint32_t*)list)[4] = group;
    bool ok = SP::SaveResource(list, db, flags);
    if (ok) {
      SP::ObjectTemplateDB_s005b_eaf0()->InvalidateTemplate(key, 0);
      SP::ObjectTemplateDB_s005b_eaf0()->AddTemplate(key);
    }
    return ok;
  }
  return false;
}

// @ 0x005bf1e0
bool LoadCollectableItems(App::PropertyList_s005b_eaf0* list, Simulator::cCollectableItems** result)
{
  bool ok = false;
  EA::ResourceMan::Key_s005b_eaf0 key;
  key.mInstance = 0;
  key.mType = 0;
  key.mGroup = 0;
  if (SP::GetPropertyAsKey(list, 0xc339d5c7, &key)) {
    EA::AutoRefCount_s005b_eaf0<Simulator::cCollectableItems> items(new ("Editor/cCollectableItems", 0, 0, 0, 0) Simulator::cCollectableItems());
    if (items->Load(key.mGroup, key.mInstance, 0)) {
      EA::ResourceMan::Key_s005b_eaf0* unlocked;
      EA::ResourceMan::Key_s005b_eaf0* rare;
      int numUnlocked = 0;
      SP::GetPropertyKeys(list, 0xbeac70b6, &numUnlocked, &unlocked);
      int numRare = 0;
      SP::GetPropertyKeys(list, 0xc285e3db, &numRare, &rare);
      for (int i = 0; i < numUnlocked; i++)
      {
        uint64_t id = Simulator::MakeItemID(unlocked[i].mGroup, unlocked[i].mInstance);
        items->AddItem(id, 0);
      }
      items->FinishedLoading();
      for (int i = 0; i < numRare; i++)
      {
        uint64_t id = Simulator::MakeItemID(rare[i].mGroup, rare[i].mInstance);
        items->AddItem(id, 0);
      }
      *result = items;
      ok = true;
      items->AddRef();
    }
  }
  return ok;
}

// @ 0x005bf500
bool __stdcall GetBoolParams(const EA::ResourceMan::Key_s005b_eaf0& key, eastl::sp_vector_s005b_eaf0<SP::FunctionalMatch::DeclareParam_s005b_eaf0>& params)
{
  EA::AutoRefCount_s005b_eaf0<App::PropertyList_s005b_eaf0> list;
  App::IPropertyManager* pm = SP::PropertyManager_s005b_eaf0();
  if (pm->GetPropertyList(key.mInstance, PropListGroup(key.mGroup), list.AsOutParam())) {
    eastl::sp_vector_s005b_eaf0<uint32_t> ids;
    list->GetPropertyIDs(ids);
    int count = ids.size();
    for (int i = 0; i < count; i++) {
      uint32_t id = ids[i];
      Property_s005b_eaf0* prop = list->GetPropertyObject(id);
      if (prop->mType == 1)
        params.push_back(SP::FunctionalMatch::DeclareParam_s005b_eaf0(id, prop->mBool != 0));
    }
  }
  return true;
}
