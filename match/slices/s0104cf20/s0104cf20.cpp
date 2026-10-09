// Slice s0104cf20: SP::cSPSpaceToolData::UpdateTuning (0x0104cf20, 4403 bytes, thiscall).
// Reloads a space tool's tuning from its property list (mName.mpLocalString at +0x30): weapon/projectile
// type keys, strategy-class bit flags (mStrategyClassID +0x174), ammo/damage/range numbers,
// effect IDs, reward counts and the colour/tuning floats at the end. Retail layout (offsets
// verified against the disassembly; unnamed fields are named mField<offset>).
// Flags: default /O2 /MD /Gy /EHsc /TP.
#include "types.h"

struct Property {
    char pad[0x12];
    short type;   // 1 bool, 9 int, 0xa uint, 0xd float
    bool* GetBool();
    int* GetInt();
    uint32_t* GetUInt();
    float* GetFloat();
};

struct PropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool Get(uint32_t id, Property** out);   // slot 9
};

__forceinline bool GetBoolProp(PropertyList* pl, uint32_t id, bool def) {
    bool v = def;
    Property* p;
    if (pl && pl->Get(id, &p) && p->type == 1) v = *p->GetBool();
    return v;
}

struct cString {
    void* mpTableResource;
    PropertyList* mpLocalString;
};

struct Key { uint32_t instance, type, group; };

bool GetPropertyAsKeyInstance(PropertyList* pl, uint32_t id, uint32_t* out);
bool GetPropertyAsText(PropertyList* pl, uint32_t id, int* out);  // 0x006a1360
void UpdateColorTuning(PropertyList* pl, int* out);  // 0x0104c120

struct cSPSpaceToolData {
    char pad0[0x2c];
    cString mName;   // +0x2c; mName.mpLocalString (+0x30) is the property list
    char pad_34[0x140];
    uint32_t mStrategyClassID;  // +0x174
    uint32_t mToolType;  // +0x178
    uint32_t mWeaponSubtype;  // +0x17c
    uint32_t mProjectileType;  // +0x180
    uint32_t mProjectileMotion;  // +0x184
    uint32_t mContext;  // +0x188
    Key mUpgradeID;  // +0x18c
    int mAmmoUsedPerShot;  // +0x198
    int mMaxAmmoCount;  // +0x19c
    int mUseCost;  // +0x1a0
    int mEnergyCost;  // +0x1a4
    float mDamageArea;  // +0x1a8
    float mRange;  // +0x1ac
    float mMinDamage;  // +0x1b0
    float mMaxDamage;  // +0x1b4
    float mMaxScale;  // +0x1b8
    float mRechargeRate;  // +0x1bc
    float mAutoFireRate;  // +0x1c0
    float mMinRange;  // +0x1c4
    float mMaxRange;  // +0x1c8
    float mDamageRadius;  // +0x1cc
    float mChargeTime;  // +0x1d0
    float mProjectileSpeed;  // +0x1d4
    float mProjectileAcceleration;  // +0x1d8
    float mProjectileTurnRate;  // +0x1dc
    float mProjectileMaxAltitude;  // +0x1e0
    float mProjectileMinAltitude;  // +0x1e4
    float mProjectileDetonationDistance;  // +0x1e8
    float mProjectileTimeout;  // +0x1ec
    float mProjectileEccentricity;  // +0x1f0
    float mRelationshipDelta;  // +0x1f4
    float mBeamFlags;  // +0x1f8
    float mPickFlags;  // +0x1fc
    float mPassFlags;  // +0x200
    int mCulturalRewardCount;  // +0x204
    int mMilitaryRewardCount;  // +0x208
    int mEconomicRewardCount;  // +0x20c
    int mMeaningOfLifeRewardCount;  // +0x210
    float mUsesLobAngle;  // +0x214
    uint32_t mLobAngle;  // +0x218
    uint32_t mHitPlayerEffectID;  // +0x21c
    uint32_t mBeamEffectID;  // +0x220
    uint32_t mHitGroundEffectID;  // +0x224
    uint32_t mHitWaterEffectID;  // +0x228
    uint32_t mHitCombatantEffectID;  // +0x22c
    uint32_t mMuzzleEffectID;  // +0x230
    uint32_t mToolProjectileEffectID;  // +0x234
    float mToolTargetEffectID;  // +0x238
    uint32_t mToolProjectileExplosionExpansionRate;  // +0x23c
    uint32_t mPlacedModelID;  // +0x240
    uint32_t mpButtonImageKeys;  // +0x244
    int mDoesActionPostEffect;  // +0x248
    int mMinimapSlotsToggleEffect;  // +0x24c
    int mTerraformImageID;  // +0x250
    int mTerrainColorID;  // +0x254
    int mWaterColorID;  // +0x258
    char pad_25c[0x10];
    float mField26c;  // +0x26c
    float mField270;  // +0x270
    float mField274;  // +0x274
    float mField278;  // +0x278
    float mField27c;  // +0x27c
    float mField280;  // +0x280
    float mField284;  // +0x284
    float mField288;  // +0x288
    float mField28c;  // +0x28c
    float mField290;  // +0x290
    float mField294;  // +0x294
    float mField298;  // +0x298
    char padEnd[0x2a0 - 0x29c];
    void UpdateTuning();
    void BaseUpdateTuning();
    // Reads a bool property into one bit of mStrategyClassID.
    __forceinline void UpdateFlag(uint32_t id, uint32_t mask, bool def) {
        if (GetBoolProp(mName.mpLocalString, id, def)) mStrategyClassID |= mask; else mStrategyClassID &= ~mask;
    }
    __forceinline void ReadInt(uint32_t id, int* dst) {
        Property* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 9) *dst = *p->GetInt();
    }
    __forceinline void ReadFloat(uint32_t id, float* dst) {
        Property* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 13) *dst = *p->GetFloat();
    }
    __forceinline void ReadUInt(uint32_t id, uint32_t* dst) {
        Property* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 10) *dst = *p->GetUInt();
    }
};

// @ 0x0104cf20
void cSPSpaceToolData::UpdateTuning()
{
    BaseUpdateTuning();
    if (mName.mpLocalString) {
    mStrategyClassID = 0;
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x51191d92, &mWeaponSubtype);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x23fbb0e, &mProjectileType);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x23fbe00, &mProjectileMotion);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x317c936, &mContext);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x10609ee4, &mUpgradeID.instance);
    UpdateFlag(0xf0609ed3, 0x20, false);
    UpdateFlag(0x4163a04, 0x40, false);
    UpdateFlag(0x4163a05, 0x80, false);
    UpdateFlag(0x4163a06, 0x20000, false);
    ReadInt(0x2afc090, &mMaxAmmoCount);
    ReadInt(0x2b24d49, &mUseCost);
    ReadInt(0x10609edf, &mEnergyCost);
    ReadFloat(0x57b4eec, &mDamageArea);
    ReadFloat(0x909ac99e, &mRange);
    ReadFloat(0x3712dc0, &mMinDamage);
    ReadFloat(0x51191d87, &mMaxDamage);
    ReadFloat(0x51191d8b, &mMaxScale);
    ReadFloat(0x39fb03d, &mRechargeRate);
    ReadFloat(0x51191d8f, &mAutoFireRate);
    ReadFloat(0x51191d96, &mMinRange);
    ReadFloat(0x31192468, &mMaxRange);
    ReadFloat(0x3119246d, &mDamageRadius);
    ReadFloat(0x3119246e, &mChargeTime);
    ReadFloat(0x51375b2d, &mProjectileSpeed);
    ReadFloat(0x23fbe01, &mProjectileAcceleration);
    ReadFloat(0x5a5df68, &mProjectileTurnRate);
    ReadFloat(0x4c6efb4, &mRelationshipDelta);
    UpdateFlag(0x3138c9b1, 0x1, false);
    UpdateFlag(0x281899e, 0x2, false);
    UpdateFlag(0x685f767, 0x40000, false);
    UpdateFlag(0x46e82d7, 0x100, false);
    UpdateFlag(0x4d4190d, 0x200, true);
    UpdateFlag(0x5e778e7, 0x400, false);
    uint32_t upgradeType = 0;
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x711d1aee, &upgradeType);
    mUpgradeID.type = upgradeType;
    mUpgradeID.group = 0;
    mAmmoUsedPerShot = 0;
    UpdateFlag(0x314f32a, 0x4, false);
    UpdateFlag(0x331dd2a, 0x8, false);
    UpdateFlag(0x339d3cb, 0x10, false);
    ReadFloat(0x39a4caf, &mBeamFlags);
    ReadFloat(0x686ef4e, &mPickFlags);
    ReadFloat(0x686f4b2, &mPassFlags);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0xa70d87ac, &mToolType);
    ReadInt(0x488bb2c, &mCulturalRewardCount);
    ReadInt(0x488bb52, &mMilitaryRewardCount);
    ReadInt(0x488bb57, &mEconomicRewardCount);
    ReadInt(0x4ed2f4f, &mMeaningOfLifeRewardCount);
    bool hasLob = false;
    { Property* p; PropertyList* pl = mName.mpLocalString;
      if (pl && pl->Get(0x47f7383, &p) && p->type == 0xd) { mUsesLobAngle = *p->GetFloat(); hasLob = true; } }
    if (hasLob) mStrategyClassID |= 0x800; else mStrategyClassID &= ~0x800u;
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x47f7359, &mLobAngle);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x1138c0b9, &mHitPlayerEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x3138c0bf, &mBeamEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x3138c0c2, &mHitGroundEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x3138c0c6, &mHitWaterEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x3025b14, &mHitCombatantEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x3025b0b, &mMuzzleEffectID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x317b2cc, &mToolProjectileEffectID);
    ReadFloat(0x30c073a, &mToolTargetEffectID);
    ReadUInt(0x4d164aa, &mPlacedModelID);
    GetPropertyAsKeyInstance(mName.mpLocalString, 0x4e3eca1, &mToolProjectileExplosionExpansionRate);
    UpdateFlag(0x4f4c626, 0x1000, false);
    ReadUInt(0x521abf7, &mpButtonImageKeys);
    ReadInt(0x535a500, &mDoesActionPostEffect);
    ReadInt(0x535a50b, &mMinimapSlotsToggleEffect);
    ReadInt(0x53d4c67, &mTerraformImageID);
    ReadFloat(0x30d28c1, &mProjectileEccentricity);
    ReadFloat(0x579017f, &mProjectileMaxAltitude);
    ReadFloat(0x5790183, &mProjectileMinAltitude);
    ReadFloat(0x5a82cb4, &mProjectileDetonationDistance);
    ReadFloat(0x5790187, &mProjectileTimeout);
    UpdateFlag(0x580bc29, 0x2000, false);
    UpdateFlag(0x580bc3d, 0x4000, false);
    UpdateFlag(0x5931133, 0x8000, false);
    UpdateFlag(0x6157363, 0x10000, false);
    UpdateFlag(0x69423b2, 0x80000, false);
    UpdateColorTuning(mName.mpLocalString, &mTerrainColorID); // 0x0104c120
    GetPropertyAsText(mName.mpLocalString, 0x5e62e33, &mWaterColorID); // 0x006a1360
    ReadFloat(0x30fd84d, &mField26c);
    ReadFloat(0x30fd85a, &mField270);
    ReadFloat(0x30fd85d, &mField274);
    ReadFloat(0x30fd861, &mField278);
    ReadFloat(0x30fd864, &mField27c);
    ReadFloat(0x30fd868, &mField280);
    ReadFloat(0x30fd86b, &mField284);
    ReadFloat(0x30fd86e, &mField288);
    ReadFloat(0x30fd872, &mField28c);
    ReadFloat(0x30fe481, &mField290);
    ReadFloat(0x30fe485, &mField294);
    ReadFloat(0x30fe488, &mField298);
    }
}
// --- equivalence checker address annotations
    void GetPropertyAsText(...); // 0x006a1360
    void UpdateColorTuning(...); // 0x0104c120

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
