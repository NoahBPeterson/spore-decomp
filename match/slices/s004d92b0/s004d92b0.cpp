// Slice s004d92b0: SP::ReadAbilityData (0x004D92B0, 4127 bytes).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (SPEditorSpeciesManager module).
//
// Fills a creature ability (retail Simulator::cCreatureAbility, ModAPI layout) from its property
// list: ~50 typed properties (inline typed getters with a default), three uint32/float arrays
// copied into the combat-effect vectors, two animation-id lists pushed into vectors, two resource
// keys, the range pair (SetRangeMin), and finally the hint name picked from the ability type.
#include "types.h"
#pragma pack(push, 4)

// ---- properties -----------------------------------------------------------

enum PropertyType {
    kPropBool = 1,
    kPropInt32 = 9,
    kPropUInt32 = 10,
    kPropFloat = 13
};

struct Property {
    uint32_t pad0[4];
    uint16_t mFlags;              // +0x10
    uint16_t mType;               // +0x12
    int32_t* GetInt();            // 0x0041E990
    uint32_t* GetUInt();          // 0x0041EA00
    float* GetFloat();            // 0x0041EA70
    float* GetFloatValue();       // 0x004E4230 (untyped access)
    bool* GetBoolValue();         // 0x004E42A0 (untyped access)
};

struct PropertyList {
    virtual int AddRef();                                           // slot 0
    virtual int Release();                                          // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                          // slot 7  (+0x1c)
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& pOut);         // slot 9  (+0x24)
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct LocalizedString {
    uint32_t pad[5];
};

bool GetPropertyAsText(PropertyList* p, uint32_t id, LocalizedString* pOut);                      // 0x006A1360
bool GetPropertyAsKey(PropertyList* p, uint32_t id, ResourceKey* pOut);                          // 0x006A1250
bool GetPropertyAsKeyInstance(PropertyList* p, uint32_t id, uint32_t* pOut);                     // 0x006A12A0
bool GetPropertyAsUint32Array(PropertyList* p, uint32_t id, int* pCount, uint32_t** ppData);     // 0x006A0840
bool GetPropertyAsFloatArray(PropertyList* p, uint32_t id, int* pCount, float** ppData);         // 0x006A08B0
bool GetPropertyAsFloat(PropertyList* p, uint32_t id, float* pOut);                              // 0x0040CF10
bool GetPropertyAsBool(PropertyList* p, uint32_t id, bool* pOut);                                // 0x00407190
bool GetPropertyAsUint32(PropertyList* p, uint32_t id, uint32_t* pOut);                          // 0x004AF210

// Typed reads into an existing value (left unchanged when missing or mistyped).
inline void GetInt32(PropertyList* pList, uint32_t id, int& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropInt32)
        dst = *prop->GetInt();
}

inline void GetUInt32(PropertyList* pList, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropUInt32)
        dst = *prop->GetUInt();
}

inline void GetFloat(PropertyList* pList, uint32_t id, float& dst)
{
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == kPropFloat)
        dst = *prop->GetFloat();
}

// Untyped reads with a default.
inline bool GetBoolValue(PropertyList* pList, uint32_t id)
{
    bool bValue;
    Property* prop;
    if (pList && pList->GetProperty(id, prop))
        bValue = *prop->GetBoolValue();
    else
        bValue = false;
    return bValue;
}

inline float GetFloatValue(PropertyList* pList, uint32_t id, float defaultValue)
{
    float bValue;
    Property* prop;
    if (pList && pList->GetProperty(id, prop))
        bValue = *prop->GetFloatValue();
    else
        bValue = defaultValue;
    return bValue;
}

// SSE max (the module's asm helper).
__forceinline float Max(float value, float minValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        movss value, xmm0
    }
    return value;
}

// ---- containers -----------------------------------------------------------

// Reserved frame of an inline callee that cl declined (keeps the original's stack holes).
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

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

// eastl::vector<uint32_t> (sp_vector_allocator)
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

// eastl::vector<float> (sp_vector_allocator)
struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32_t mAllocator[2];
    void resize(uint32_t n);                            // 0x004AFC80
    float& operator[](int i) { return mpBegin[i]; }
};

// ---- ability --------------------------------------------------------------

struct cCreatureAbility {
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
    FloatVector mCombatEffectPercentages;         // +0xcc
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
    AutoRefCount<PropertyList> mpPropList;        // +0x130
    float mRangeMin;                              // +0x134
    float mAvatarRangeMin;                        // +0x138

    void SetRangeMin(float rangeMin, float avatarRangeMin);   // 0x004D3DA0
};

namespace SP {

// @ 0x004D92B0  SP::ReadAbilityData
bool ReadAbilityData(cCreatureAbility* ability, PropertyList* propList)
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
    GetUInt32(propList, 0x75e00b7, ability->mReactionAnimation);
    ability->mReactionDeathAnimation = 0xffffffff;
    GetUInt32(propList, 0x7a7ffd5, ability->mReactionDeathAnimation);
    ability->mReactionLiveAnimation = 0xffffffff;
    GetUInt32(propList, 0x7a7ffd9, ability->mReactionLiveAnimation);
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
    GetUInt32(propList, 0x5e7eca0, ability->mBuildingSpecificAnimationID);
    GetUInt32(propList, 0x742b4dcf, ability->mBabyGameAnimationID);
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
    GetUInt32(propList, 0x35f26c8, ability->mMuzzleEffectID);
    GetUInt32(propList, 0x35f26cc, ability->mTrailEffectID);
    GetUInt32(propList, 0x35f26d2, ability->mImpactEffectID);
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

    GetUInt32(propList, 0x4a3b2f8, ability->mRushingAnimationID);
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

#pragma pack(pop)
