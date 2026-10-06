// Slice s00ce6af0: SP::cTribeTuningData::Init (0x00ce6af0, 5741 bytes).
// /O2 /arch:SSE module (movss float copies), no /EHsc (the local PropertyListPtr
// has a dtor but no EH frame).
//
// Fetches the tribe tuning property list from the terrain manager (sphere vs.
// flat variant), shares it as the tribe list, loads the CommunityEditor and
// hit-hut lists from the property manager, then copies every tribe tuning value
// into the object through the inline App::Property-style getters
//   (pl && pl->GetProperty(id, p) && p->mnType == T  ->  *p->GetValueT()).
// The retail layout differs from the 2008 dev PDB (fields were added/moved), so
// members are named after the property each one is read from (names from the
// SporeModder-FX property registry; unnamed hashes keep an offset name).
#include "types.h"

// ---------------------------------------------------------------- properties
extern const bool     kDefaultBoolValue;
extern const int      kDefaultInt32Value;
extern const uint32_t kDefaultUInt32Value;
extern const float    kDefaultFloatValue;   // 0x015d9c6c

struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    uint16_t GetType() const { return mnType; }
    void* GetValuePtr()                                         // 0x00446ff0
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    bool* GetValueBool()                                        // 0x0041e920
    {
        if (mnType == 1 || mnType == 0x10)
            return (bool*)GetValuePtr();
        return (bool*)&kDefaultBoolValue;
    }
    int* GetValueInt32()                                        // 0x0041e990
    {
        if (mnType == 9 || mnType == 0x10)
            return (int*)GetValuePtr();
        return (int*)&kDefaultInt32Value;
    }
    uint32_t* GetValueUInt32()                                  // 0x0041ea00
    {
        if (mnType == 10 || mnType == 0x10)
            return (uint32_t*)GetValuePtr();
        return (uint32_t*)&kDefaultUInt32Value;
    }
    float* GetValueFloat()                                      // 0x0041ea70
    {
        if (mnType == 13 || mnType == 0x10)
            return (float*)GetValuePtr();
        return (float*)&kDefaultFloatValue;
    }
};

class cPropertyList {
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};

// eastl::intrusive_ptr<cPropertyList> (just what is used here)
struct PropertyListPtr {
    cPropertyList* mpObject;

    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    cPropertyList* get() const { return mpObject; }
    operator cPropertyList*() const { return mpObject; }
    void reset()
    {
        if (mpObject) {
            cPropertyList* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    PropertyListPtr& operator=(cPropertyList* pObject)
    {
        if (pObject != mpObject) {
            cPropertyList* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    PropertyListPtr& operator=(const PropertyListPtr& x) { return operator=(x.mpObject); }
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyListRaw(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst); // 0x2c
    virtual bool GetGlobalPropertyListRaw(uint32_t instanceID, PropertyListPtr& dst);              // 0x30

    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
    {
        dst.reset();
        return GetPropertyListRaw(instanceID, groupID, dst);
    }
    bool GetPropertyList(uint32_t instanceID, PropertyListPtr& dst)
    {
        dst.reset();
        return GetGlobalPropertyListRaw(instanceID, dst);
    }
};

// App::Property static getters (inline in this module)
inline bool GetBool(cPropertyList* pl, uint32_t id, bool& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 1) { v = *p->GetValueBool(); return true; }
    return false;
}
inline bool GetInt(cPropertyList* pl, uint32_t id, int& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 9) { v = *p->GetValueInt32(); return true; }
    return false;
}
inline bool GetUInt(cPropertyList* pl, uint32_t id, uint32_t& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 10) { v = *p->GetValueUInt32(); return true; }
    return false;
}
inline bool GetFloat(cPropertyList* pl, uint32_t id, float& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 13) { v = *p->GetValueFloat(); return true; }
    return false;
}
// value-or-default form: no type check beyond GetValueFloat's own
inline float GetFloatOr(cPropertyList* pl, uint32_t id, float defaultValue)
{
    Property* p;
    if (pl && pl->GetProperty(id, p))
        return *p->GetValueFloat();
    return defaultValue;
}

struct cSPVector2 { float x, y; };

bool GetPropertyAsVector2(cPropertyList* pl, uint32_t id, cSPVector2& value);           // 0x006a10c0
bool GetPropertyAsIntArray(cPropertyList* pl, uint32_t id, int& count, int*& values);  // 0x006a07d0

// ---------------------------------------------------------------- engine
class cTerrainEditor { public: void* GetCurrentTerrainSphere(); };   // 0x00f67d90
cTerrainEditor* NounManager();                                         // 0x00b3d300 (SP::NounManager)
class TerrainMgr { public: cPropertyList* Fn1(const char* key, int sphere); }; // 0x00b1daf0
TerrainMgr* GetTerrainMgr();                                           // 0x00b3d320
extern const char kTribeTuningKey[];                                   // 0x01654c02
cPropertyManager* PropertyManager();                                   // 0x0067de30

namespace eastl {
    template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}

// eastl::map<uint32_t, int> (retail layout: 4-byte compare, anchor, size, allocator)
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;   // +0
    rbtree_node_base* mpNodeLeft;    // +4
    rbtree_node_base* mpNodeParent;  // +8
    char              mColor;        // +c
};
struct UIntIntMap {
    uint32_t         mCompare;       // +0x00 (empty less<>, padded)
    rbtree_node_base mAnchor;        // +0x04
    uint32_t         mnSize;         // +0x14
    uint32_t         mAllocator;     // +0x18

    int& operator[](const uint32_t& key);                         // 0x00643a40
    void DoNukeSubtree(rbtree_node_base* pNode);                  // 0x009a9600
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        rbtree_node_base* pNode = mAnchor.mpNodeParent;
        while (pNode) {
            DoNukeSubtree(pNode->mpNodeRight);
            rbtree_node_base* const pNodeLeft = pNode->mpNodeLeft;
            operator delete[](pNode);
            pNode = pNodeLeft;
        }
        reset();
    }
};

// EA float->int64 helper: fistp in the current (round-to-nearest) mode, not a
// truncating cast.
inline int64_t FloatToInt64(float f)
{
    int64_t result;
    __asm fld   f
    __asm fistp result
    return result;
}

extern const int kMaxMatingTimers;     // 0x01477a78 (= 15)

namespace SP {

// Retail layout (size 0x200).
struct cTribeTuningData
{
    cSPVector2 kSizeLimits;                          // +0x000 sizeLimits
    float    kTribeCreatureScaleMultiplier;          // +0x008 tribeCreatureScaleMultiplier
    float    kChieftainScaleMultiplier;              // +0x00c chieftainScale
    float    kChieftainDamageScaleMultiplier;        // +0x010 chieftainDamageScale
    float    kChieftainHealthScaleMultiplier;        // +0x014 chieftainHealthScale
    float    kChieftainDefendDistanceMin;            // +0x018
    float    kChieftainDefendDistanceMax;            // +0x01c
    float    kChieftainRespawnTime;                  // +0x020
    float    kJumpMaxDistance;                       // +0x024
    float    kGlideTime;                             // +0x028
    cSPVector2 kHoverInterval;                       // +0x02c
    cSPVector2 kJumpInterval;                        // +0x034
    cSPVector2 kTimeBetweenAttacks;                  // +0x03c
    cSPVector2 kTimeBetweenCombatMovement;           // +0x044
    cSPVector2 kTimeBetweenTargetCheck;              // +0x04c
    float    kMaxFishingDistance;                    // +0x054
    float    kMaxForagingDistance;                   // +0x058
    float    kMaxDistanceSprintCatchUp;              // +0x05c
    float    kInitialTribeZoningRadius;              // +0x060
    float    kNewToolReactionTime;                   // +0x064
    uint32_t kMaxNumDomesticatedAnimals;             // +0x068
    float    kMiniMapZoom;                           // +0x06c
    uint32_t kSPCamReturnWaitTime;                   // +0x070
    uint32_t kSPCamReturnVerbTime;                   // +0x074
    float    kBallisticCamDistanceMin;               // +0x078
    float    kRepairRate;                            // +0x07c (percent * 0.01)
    PropertyListPtr mpTribeTuningPropList;           // +0x080
    PropertyListPtr mpTribePropList;                 // +0x084
    PropertyListPtr mpCommunityEditorPropList;       // +0x088
    PropertyListPtr mpTribeHitHutPropList;           // +0x08c
    float    mEatFoodPerSecond;                      // +0x090 (0x284e0a58, default 1)
    float    mEatHungerPerFood;                      // +0x094 eatHungerBoostPerFood
    float    mEatHealthPerFood;                      // +0x098 eatHealthBoostPerFood
    UIntIntMap mTreeSmackYield;                      // +0x09c gatherTreeSmackYield
    int64_t  mTimeBeforeBabyGrowsUp_ms;              // +0x0b8
    int64_t  mBabyGrowthBoost_ms;                    // +0x0c0
    float    mCarryBundleAmountMax;                  // +0x0c8
    float    mCarryBundleAmountMax_Fruit;            // +0x0cc
    float    mCarryBundleAmountMax_Meat;             // +0x0d0
    float    mCarryBundleAmountMax_Fish;             // +0x0d4
    float    mCarryBundleAmountMax_Eggs;             // +0x0d8
    float    mCarryBundleAmountMax_Gift;             // +0x0dc giftFoodAmount
    float    mGiftFoodAmount;                        // +0x0e0 giftFoodAmount
    float    kMultiplierPerSocialLevel;              // +0x0e4
    float    mTuning0e8;                             // +0x0e8 (0x8067d26f)
    float    mTuning0ec;                             // +0x0ec (0x1660ea24)
    float    mTuning0f0;                             // +0x0f0 (0x90cfac05)
    float    kScoreContributionPerTool;              // +0x0f4
    float    kScoreContributionPerCreature;          // +0x0f8
    float    kScoreContributionPerAccessoryLevel;    // +0x0fc
    float    kScoreContributionForHoldingTool;       // +0x100
    float    kScoreContributionForChieftain;         // +0x104
    float    mTuning108;                             // +0x108 (0xb4649f94)
    float    mTuning10c;                             // +0x10c (0x459ce162)
    float    mTuning110;                             // +0x110 (0x26f685c1)
    float    mTuning114;                             // +0x114 (0x58f922e2)
    float    kSocialNeutralScoreThreshold;           // +0x118
    float    kSocialPositiveScoreThreshold;          // +0x11c
    float    kSocialRelationshipImprovement;         // +0x120
    float    mTuning124;                             // +0x124 (0xe32237c9)
    float    mTuning128;                             // +0x128 (0xfa555876)
    float    kToolScaleHeightRatio;                  // +0x12c
    float    kFoodTrayScale;                         // +0x130
    float    mTuning134;                             // +0x134 (0xe8c2bcae, reset to 0)
    float    mTuning138;                             // +0x138 (0xdae22b88)
    float    mTuning13c;                             // +0x13c (0xd8066440)
    float    mTuning140;                             // +0x140 (0xa7384ff2)
    float    mTuning144;                             // +0x144 (0xa7384ff1)
    float    mTuning148;                             // +0x148 (0xa7384ff0)
    float    mTuning14c;                             // +0x14c (0x412ffa82)
    float    mTribeMaxFood;                          // +0x150 tribeMaxFood
    float    mRolloverRltnshpVBadCap;                // +0x154
    float    mRolloverRltnshpBadCap;                 // +0x158
    float    mRolloverRltnshp15c;                    // +0x15c (reset to 0 when ui list loads)
    float    mRolloverRltnshpNeutralCap;             // +0x160
    float    mRolloverRltnshpGoodCap;                // +0x164
    float    mTuning168;                             // +0x168 (0x64cf738f)
    bool     mTuning16c;                             // +0x16c (0xb4853f28)
    uint8_t  pad16d[3];
    float    mTuning170;                             // +0x170 (0xa4775a7a)
    float    mTuning174;                             // +0x174 (0xb6ce0861)
    int      mNewTribeFood;                          // +0x178
    int      mPopulationStart;                       // +0x17c
    int      mFlavorIdleMin;                         // +0x180
    int      mFlavorIdleMax;                         // +0x184
    float    mGameSpeeds[4];                         // +0x188 tribeSpeed1..4
    float    mGotoWaitTime;                          // +0x198
    float    mTribeHutLevel1Health;                  // +0x19c
    float    mTribeHutLevel2Health;                  // +0x1a0
    float    mTribeHutLevel3Health;                  // +0x1a4
    float    mTribeToolHiDamage;                     // +0x1a8
    float    mTribeToolLoDamage;                     // +0x1ac
    float    mTribeHutHiDamage;                      // +0x1b0
    float    mTribeHutLoDamage;                      // +0x1b4
    uint32_t pad1b8[2];
    uint32_t mRepairDelayMs;                         // +0x1c0
    int      mMatingTimer[15];                       // +0x1c4

    void Init();
};

// @ 0x00ce6af0
void cTribeTuningData::Init()
{
    cPropertyManager* pPropManager = PropertyManager();
    bool bSphere = NounManager()->GetCurrentTerrainSphere() != 0;
    mpTribeTuningPropList = GetTerrainMgr()->Fn1(kTribeTuningKey, bSphere);
    mpTribePropList = mpTribeTuningPropList;
    pPropManager->GetPropertyList(0x6b3f727b /*CommunityEditor*/, 0, mpCommunityEditorPropList);
    pPropManager->GetPropertyList(0xe289a5f1, 0, mpTribeHitHutPropList);

    GetInt  (mpTribeTuningPropList, 0x0375418a, mNewTribeFood);           // newTribeFood
    GetFloat(mpTribeTuningPropList, 0xb565559b, mTribeMaxFood);           // tribeMaxFood

    float value;
    GetFloat(mpTribeTuningPropList, 0x70adc7c2, value);                   // timeBeforeBabyGrowsUp
    mTimeBeforeBabyGrowsUp_ms = FloatToInt64(value * 1000.0f);
    GetFloat(mpTribeTuningPropList, 0x70adc7c3, value);                   // babyGrowthBoost
    mBabyGrowthBoost_ms = FloatToInt64(value * 1000.0f);

    mTuning134 = 0.0f;
    GetFloat(mpTribeTuningPropList, 0xe8c2bcae, mTuning134);
    GetFloat(mpTribeTuningPropList, 0xdae22b88, mTuning138);
    GetFloat(mpTribeTuningPropList, 0xd8066440, mTuning13c);
    GetFloat(mpTribeTuningPropList, 0x412ffa82, mTuning14c);
    GetFloat(mpTribeTuningPropList, 0xa7384ff2, mTuning140);
    GetFloat(mpTribeTuningPropList, 0xa7384ff1, mTuning144);
    GetFloat(mpTribeTuningPropList, 0xa7384ff0, mTuning148);
    GetInt  (mpTribeTuningPropList, 0x01ba3d4f, mPopulationStart);        // tribePopulationStart
    GetFloat(mpTribeTuningPropList, 0x01fb1887, mGameSpeeds[0]);          // tribeSpeed1
    GetFloat(mpTribeTuningPropList, 0x01fb1888, mGameSpeeds[1]);          // tribeSpeed2
    GetFloat(mpTribeTuningPropList, 0x01fb1889, mGameSpeeds[2]);          // tribeSpeed3
    GetFloat(mpTribeTuningPropList, 0x01fb188a, mGameSpeeds[3]);          // tribeSpeed4
    GetFloat(mpTribeTuningPropList, 0x02ae25ab, mGotoWaitTime);           // tribeGotoWaitTime
    GetUInt (mpTribeTuningPropList, 0x04acac4d, mRepairDelayMs);          // tribeRepairDelay
    mRepairDelayMs *= 1000;
    GetFloat(mpTribeTuningPropList, 0x03a2641d, mTribeHutLevel1Health);
    GetFloat(mpTribeTuningPropList, 0x03a2641e, mTribeHutLevel2Health);
    GetFloat(mpTribeTuningPropList, 0x03a2641f, mTribeHutLevel3Health);
    GetFloat(mpTribeTuningPropList, 0x03a26421, mTribeToolHiDamage);
    GetFloat(mpTribeTuningPropList, 0x03a26422, mTribeToolLoDamage);
    GetFloat(mpTribeTuningPropList, 0x03a26423, mTribeHutHiDamage);
    GetFloat(mpTribeTuningPropList, 0x03a26424, mTribeHutLoDamage);
    GetInt  (mpTribeTuningPropList, 0x03a2641b, mFlavorIdleMin);          // tribeFlavorIdleMin
    GetInt  (mpTribeTuningPropList, 0x03a2641c, mFlavorIdleMax);          // tribeFlavorIdleMax
    GetFloat(mpTribeTuningPropList, 0x03710e22, kChieftainScaleMultiplier);
    GetFloat(mpTribeTuningPropList, 0xf3cef643, kChieftainDamageScaleMultiplier);
    GetFloat(mpTribeTuningPropList, 0xfc122b80, kChieftainHealthScaleMultiplier);
    GetFloat(mpTribeTuningPropList, 0x0f46a59f, kChieftainDefendDistanceMin);
    GetFloat(mpTribeTuningPropList, 0x07469921, kChieftainDefendDistanceMax);
    GetFloat(mpTribeTuningPropList, 0x5fac3dc3, kChieftainRespawnTime);
    GetFloat(mpTribeTuningPropList, 0x88fb0354, kJumpMaxDistance);
    GetFloat(mpTribeTuningPropList, 0x341ad29f, kGlideTime);
    GetPropertyAsVector2(mpTribeTuningPropList, 0x2a7aa2ea, kHoverInterval);
    GetPropertyAsVector2(mpTribeTuningPropList, 0x37158a96, kJumpInterval);
    GetPropertyAsVector2(mpTribeTuningPropList, 0xb8ce3ade, kTimeBetweenAttacks);
    GetPropertyAsVector2(mpTribeTuningPropList, 0xe0f7d46c, kTimeBetweenCombatMovement);
    GetPropertyAsVector2(mpTribeTuningPropList, 0x964b7120, kTimeBetweenTargetCheck);
    GetFloat(mpTribeTuningPropList, 0xd1873793, kToolScaleHeightRatio);
    GetFloat(mpTribeTuningPropList, 0x9ad14166, kFoodTrayScale);
    GetFloat(mpTribeTuningPropList, 0x35354924, kMaxFishingDistance);
    GetFloat(mpTribeTuningPropList, 0x3e6db41f, kMaxForagingDistance);
    GetFloat(mpTribeTuningPropList, 0xd0b3f18a, kMaxDistanceSprintCatchUp);
    GetFloat(mpTribeTuningPropList, 0xe05fecdd, kNewToolReactionTime);
    GetUInt (mpTribeTuningPropList, 0xa725fcc2, kMaxNumDomesticatedAnimals);
    GetFloat(mpTribeTuningPropList, 0xde67264f, kMiniMapZoom);
    GetUInt (mpTribeTuningPropList, 0xf46fdcad, kSPCamReturnWaitTime);
    GetUInt (mpTribeTuningPropList, 0x3b5b7e2f, kSPCamReturnVerbTime);
    GetFloat(mpTribeTuningPropList, 0x7e9dd146, kBallisticCamDistanceMin);
    GetFloat(mpTribeTuningPropList, 0x51697a01, kRepairRate);             // tribeRepairRatePercent
    kRepairRate *= 0.01f;
    GetFloat(mpCommunityEditorPropList, 0xf61ce4b0, kInitialTribeZoningRadius);
    GetFloat(mpTribeTuningPropList, 0x8067d26f, mTuning0e8);
    GetFloat(mpTribeTuningPropList, 0x1660ea24, mTuning0ec);
    GetFloat(mpTribeTuningPropList, 0x90cfac05, mTuning0f0);
    GetFloat(mpTribeTuningPropList, 0xbe6712de, kMultiplierPerSocialLevel);
    GetFloat(mpTribeTuningPropList, 0x2be4751e, kScoreContributionPerTool);
    GetFloat(mpTribeTuningPropList, 0x764c5217, kScoreContributionPerCreature);
    GetFloat(mpTribeTuningPropList, 0x486716b0, kScoreContributionPerAccessoryLevel);
    GetFloat(mpTribeTuningPropList, 0xff73fecb, kScoreContributionForHoldingTool);
    GetFloat(mpTribeTuningPropList, 0x90aa60e7, kScoreContributionForChieftain);
    GetFloat(mpTribeTuningPropList, 0xb4649f94, mTuning108);
    GetFloat(mpTribeTuningPropList, 0x459ce162, mTuning10c);
    GetFloat(mpTribeTuningPropList, 0x26f685c1, mTuning110);
    GetFloat(mpTribeTuningPropList, 0x58f922e2, mTuning114);
    GetFloat(mpTribeTuningPropList, 0xe67dd8c2, kSocialNeutralScoreThreshold);
    GetFloat(mpTribeTuningPropList, 0xf2bc93c6, kSocialPositiveScoreThreshold);
    GetFloat(mpTribeTuningPropList, 0xe8db4bd2, kSocialRelationshipImprovement);
    GetFloat(mpTribeTuningPropList, 0xe32237c9, mTuning124);
    GetFloat(mpTribeTuningPropList, 0xfa555876, mTuning128);

    // tribeMatingTimers: up to 15 entries, the rest zeroed
    int  count  = 0;
    int* values = 0;
    if (GetPropertyAsIntArray(mpTribeTuningPropList, 0x0537293a, count, values))
    {
        count = eastl::min(count, kMaxMatingTimers);
        int i = 0;
        for (; i < count; i++)
            mMatingTimer[i] = values[i];
        for (; i < 15; i++)
            mMatingTimer[i] = 0;
    }

    // gatherTreeSmackYield: three yields keyed by tree type
    count  = 0;
    values = 0;
    mTreeSmackYield.clear();
    if (GetPropertyAsIntArray(mpTribePropList, 0x734cf2c6, count, values))
    {
        mTreeSmackYield[0x6d60a1cc] = values[0];
        mTreeSmackYield[0x029c388a] = values[1];
        mTreeSmackYield[0x3a8be428] = values[2];
    }

    GetFloat(mpTribePropList, 0x04ee9169, mCarryBundleAmountMax);
    GetFloat(mpTribePropList, 0x6933849b, mCarryBundleAmountMax_Fruit);
    GetFloat(mpTribePropList, 0x17258636, mCarryBundleAmountMax_Meat);
    GetFloat(mpTribePropList, 0xdbe20fa1, mCarryBundleAmountMax_Fish);
    GetFloat(mpTribePropList, 0xa818aa65, mCarryBundleAmountMax_Eggs);
    GetFloat(mpTribePropList, 0xfd444753, mCarryBundleAmountMax_Gift);   // giftFoodAmount
    GetFloat(mpTribePropList, 0xfd444753, mGiftFoodAmount);              // giftFoodAmount
    mEatFoodPerSecond = GetFloatOr(mpTribePropList, 0x284e0a58, 1.0f);
    mEatHungerPerFood = GetFloatOr(mpTribePropList, 0x520d1066, 100.0f); // eatHungerBoostPerFood
    mEatHealthPerFood = GetFloatOr(mpTribePropList, 0xe7523441, 25.0f);  // eatHealthBoostPerFood
    GetPropertyAsVector2(mpTribePropList, 0xaee4eaa6, kSizeLimits);       // sizeLimits
    GetFloat(mpTribePropList, 0xf463852c, kTribeCreatureScaleMultiplier);

    PropertyListPtr pUIPropList;
    if (PropertyManager()->GetPropertyList(0x5c770db7 /*ui*/, pUIPropList))
    {
        GetFloat(pUIPropList, 0x01d379fa, mRolloverRltnshpVBadCap);
        GetFloat(pUIPropList, 0x01d37be0, mRolloverRltnshpBadCap);
        mRolloverRltnshp15c = 0.0f;
        GetFloat(pUIPropList, 0x01d37a06, mRolloverRltnshpNeutralCap);
        GetFloat(pUIPropList, 0x01d37a0c, mRolloverRltnshpGoodCap);
    }

    GetFloat(mpTribePropList, 0x64cf738f, mTuning168);
    GetBool (mpTribePropList, 0xb4853f28, mTuning16c);
    GetFloat(mpTribePropList, 0xa4775a7a, mTuning170);
    GetFloat(mpTribePropList, 0xb6ce0861, mTuning174);
}

} // namespace SP
