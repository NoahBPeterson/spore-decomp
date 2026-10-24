// src/game/SPGonzago/SPToolManager.cpp -- migrated from slice(s) s013ac650, s01051850, s01050bb0, s01050070, s0104f2a0, s0104e060, s0104cf20, s0104bcc0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPToolManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPSpaceToolData.h"
#include "EA/Variant.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cSPTimer.h"
#include "SP/cString.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include "SP/cEffectInfo.h"
#include "SP/cSpatialObject.h"
#include <string.h>
#include "SP/cITerrainSphere.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"
#include "SP/cOrnament.h"
#include "SP/cPlanet.h"
#include "SP/cToolObjectData.h"
#include "SP/cPlanetRecord.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cSPGameDataUFO.h"
#include <intrin.h>

// ---- items of slice s0104bcc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef int                i32;
typedef unsigned long long u64;
typedef float              f32;
typedef double             f64;
struct cString_s0104_bcc0 {
    u8 mData[0x14];
    void ctorRaw();                       // 0x006b5060
    void dtorRaw();                       // 0x006b5240
    const unsigned short* GetText();      // 0x006b55c0
    bool Load(u32 group, u32 id, int flag);// 0x006b54b0
};
struct cSPTimer_s0104_bcc0 {
    u8 mData[0x20];
    bool IsRunning();                     // 0x00feba90
    u64  GetElapsedTime();                // 0x00bc3190
};
struct cGonzagoTimer_s0104_bcc0 : cSPTimer_s0104_bcc0 {
    void ctorRaw();                       // 0x00b63890
    void dtorRaw();                       // 0x00b638b0
};
struct Property {
    void*  mpValue;                       // +0x00
    u8     pad04[0x0c];
    u8     mFlags10;                      // +0x10
    u8     pad11;
    u16    mType12;                       // +0x12
    float* GetFloat();                    // 0x0041ea70
    u32*   GetUInt();                     // 0x0041ea00
    bool*  GetBool();                     // 0x0041e920
};
struct cPropertyList_s0104_bcc0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property** ppOut);  // +0x24
};
struct cItemID { u32 instanceID; u32 typeID; u32 groupID; };
struct cToolRef {
    void** mpVftbl;                                            // +0x00
    __forceinline void RefCountRelease()                        // vtable +0x04
    { ((void (__thiscall*)(void*))mpVftbl[0x04 / 4])(this); }
    __forceinline void EffectRelease()                          // vtable +0xc0
    { ((void (__thiscall*)(void*))mpVftbl[0xc0 / 4])(this); }
    __forceinline void* ActivateVfx(void* arg)                  // vtable +0xb8
    { return ((void* (__thiscall*)(void*, void*))mpVftbl[0xb8 / 4])(this, arg); }
    __forceinline u32 ActivateFlag(u32 flag)                    // 0x00c38990
    { return ((u32 (__thiscall*)(void*, u32))mpVftbl[-1])(this, flag); }
    u32 OnActivate(u32 flag);                                   // 0x00c38990
};
struct cIface {
    void** mpVftbl;                                             // +0x00
    __forceinline void* Call(u32 byteOff)
    { return ((void* (__thiscall*)(void*))mpVftbl[byteOff / 4])(this); }
    __forceinline void* Call1(u32 byteOff, u32 a)
    { return ((void* (__thiscall*)(void*, u32))mpVftbl[byteOff / 4])(this, a); }
};
typedef cIface cOutStream;
struct cPlanetModel_s0104_bcc0 {
    u8     pad00[0x24];
    void*  mpAnchor24;                       // +0x24
};
struct cVarListSerializer_s0104_bcc0 {
    u8   mData[0xa14];
    void ctorRaw(void* owner, u32 a, u32 b);                     // 0x00692f90
    bool Serialize(cOutStream* s);                               // 0x00692900
};
void* __cdecl PlanetModel();                                  // 0x00b3d350
void* __cdecl GetCurrentGameMode();                           // 0x00b5b800
void* __cdecl GetUniverseContext();                           // 0x01021080
void  __cdecl WriteUint32(void* s, const u32* v, int n, int flag); // 0x0093aa70
extern u8      gGameMode01654c05;                             // 0x01654c05
extern u8 vtbl_cSpaceToolData;                                // 0x0149ad40
extern u8 vtbl_cSpaceToolData8;                               // 0x0149ad38
extern u8 vtbl_cSpaceToolDataC;                               // 0x0149ad14
namespace SP {
struct cSPSpaceToolData_s0104_bcc0 {
    void*              mpVftable0;         // +0x00
    u32                mPad04;             // +0x04
    void*              mpVftable8;         // +0x08
    void*              mpVftableC;         // +0x0c
    u8                 mPad10[0x20];       // +0x10 .. +0x2f
    cPropertyList_s0104_bcc0*     mpPropList30;       // +0x30
    u8                 mPad34[0x28];       // +0x34 .. +0x5b
    cItemID            mItemID;            // +0x5c
    u8                 mPad68[0x14];       // +0x68 .. +0x7b
    i32                mAmmo7c;            // +0x7c
    u8                 mFlag80;            // +0x80
    u8                 mPad81[7];          // +0x81 .. +0x87
    cGonzagoTimer_s0104_bcc0      mIsInUse;           // +0x88
    cGonzagoTimer_s0104_bcc0      mRechargeTimer;     // +0xa8
    cGonzagoTimer_s0104_bcc0      mAutoFireTimer;     // +0xc8
    cGonzagoTimer_s0104_bcc0      mChargeTimer;       // +0xe8
    cToolRef*          mEffect108;         // +0x108
    cToolRef*          mEffect10c;         // +0x10c
    cToolRef*          mEffect110;         // +0x110
    cToolRef*          mEffect114;         // +0x114
    cToolRef*          mEffect118;         // +0x118
    i32                mField11c;          // +0x11c
    cToolRef*          mField120;          // +0x120
    cToolRef*          mField124;          // +0x124
    cToolRef*          mField128;          // +0x128
    cToolRef*          mField12c;          // +0x12c
    u8                 mPad130[0x10];      // +0x130 .. +0x13f
    cToolRef*          mField140;          // +0x140
    f32                mField144;          // +0x144
    f32                mField148;          // +0x148
    f32                mField14c;          // +0x14c
    u8                 mField150;          // +0x150
    u8                 mPad151[3];         // +0x151 .. +0x153
    f32                mField154;          // +0x154
    f32                mField158;
    f32                mField15c;
    f32                mField160;
    f32                mField164;
    f32                mField168;
    cToolRef*          mField16c;          // +0x16c
    cToolRef*          mField170;          // +0x170
    union {
        u32 mFlags174;                     // +0x174 (bit flags)
        struct { u16 mFlagsLow174; u8 mByte176; u8 mByte177; } mFlagsBytes;
    };
    u32                mField178;          // +0x178
    u32                mField17c;          // +0x17c
    i32                mField180;          // +0x180
    i32                mField184;          // +0x184
    u32                mField188;          // +0x188
    u32                mUpgradeInstance;   // +0x18c
    u32                mField190;          // +0x190
    u32                mField194;          // +0x194
    u32                mField198;          // +0x198
    i32                mField19c;          // +0x19c
    i32                mLimit1a0;          // +0x1a0
    u32                mField1a4;          // +0x1a4
    f32                mField1a8;          // +0x1a8
    f32                mField1ac;
    f32                mField1b0;
    f32                mField1b4;
    f32                mField1b8;
    f32                mField1bc;          // +0x1bc
    f32                mField1c0;          // +0x1c0
    f32                mField1c4;          // +0x1c4
    f32                mField1c8;          // +0x1c8
    f32                mField1cc;          // +0x1cc
    f32                mField1d0;          // +0x1d0
    f32                mField1d4;          // +0x1d4
    f32                mField1d8;
    f32                mField1dc;
    f32                mField1e0;
    f32                mField1e4;
    f32                mField1e8;
    f32                mField1ec;
    f32                mField1f0;          // +0x1f0
    f32                mField1f4;
    f32                mField1f8;
    f32                mField1fc;
    f32                mField200;
    u32                mField204;          // +0x204
    u32                mField208;
    u32                mField20c;
    u32                mField210;
    f32                mField214;          // +0x214
    u32                mField218;          // +0x218
    u32                mField21c;
    u32                mField220;
    u32                mField224;
    u32                mField228;
    u32                mField22c;
    u32                mField230;
    u32                mField234;
    f32                mField238;          // +0x238
    u32                mField23c;          // +0x23c
    u8                 mPad240[4];         // +0x240
    u32                mField244;          // +0x244
    i32                mField248;          // +0x248
    i32                mField24c;          // +0x24c
    i32                mField250;          // +0x250
    u32                mStrategyClassID;   // +0x254
    cString_s0104_bcc0            mWaterColorID;      // +0x258
    f32                mField26c;          // +0x26c
    f32                mField270;
    f32                mField274;
    f32                mField278;
    f32                mField27c;
    f32                mField280;
    f32                mField284;
    f32                mField288;
    f32                mField28c;
    f32                mField290;
    f32                mField294;
    f32                mField298;          // +0x298

    void baseCtorRaw();                                        // 0x00c87660
    void baseDtorRaw();                                        // 0x00c87770
    cSPSpaceToolData_s0104_bcc0();
    ~cSPSpaceToolData_s0104_bcc0();

    u8   FUN_00c87580(cOutStream* stream);                     // 0x00c87580
    u8   Write(cOutStream* stream);                            // 0x0104bcc0
    u32  FUN_0104bd50();                                       // 0x0104bd50
    i32  FUN_0104bde0();                                       // 0x0104bde0
    i32  FUN_0104be00();                                       // 0x0104be00
    f64  FUN_0104be30();                                       // 0x0104be30
    i32  FUN_0104bfa0();                                       // 0x0104bfa0
    u8   FUN_0104bff0();                                       // 0x0104bff0
    u8   FUN_0104c010();                                       // 0x0104c010
    u8   func48h();                                            // 0x0104ca20
    bool IsInContext();                                        // 0x0104cb70
    void FUN_0104cbd0(i32 delta);                              // 0x0104cbd0
    void FUN_0104cc00(i32 amount);                             // 0x0104cc00
    u32  IsDeselectedAfterUse();                               // 0x0104cc40
    u8   FUN_0104cc90();                                       // 0x0104cc90
    u8   FUN_0104cdb0(cIface* target);                         // 0x0104cdb0
};
}
// ---- items of slice s0104bcc0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u8      gGameMode01654c05;                             // 0x01654c05
extern u8 vtbl_cSpaceToolData;                                // 0x0149ad40
extern u8 vtbl_cSpaceToolData8;                               // 0x0149ad38
extern u8 vtbl_cSpaceToolDataC;                               // 0x0149ad14

// ---- items of slice s0104cf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property_s0104_cf20 {
    char pad[0x12];
    short type;   // 1 bool, 9 int, 0xa uint, 0xd float
    bool* GetBool();
    int* GetInt();  // 0x0041e990 (Property::GetInt)
    uint32_t* GetUInt();
    float* GetFloat();
};
struct PropertyList {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool Get(uint32_t id, Property_s0104_cf20** out);   // slot 9
};
__forceinline bool GetBoolProp(PropertyList* pl, uint32_t id, bool def) {
    bool v = def;
    Property_s0104_cf20* p;
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
        Property_s0104_cf20* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 9) *dst = *p->GetInt();
    }
    __forceinline void ReadFloat(uint32_t id, float* dst) {
        Property_s0104_cf20* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 13) *dst = *p->GetFloat();
    }
    __forceinline void ReadUInt(uint32_t id, uint32_t* dst) {
        Property_s0104_cf20* p;
        PropertyList* pl = mName.mpLocalString;
        if (pl && pl->Get(id, &p) && p->type == 10) *dst = *p->GetUInt();
    }
};
// ---- items of slice s0104cf20 end

// ---- items of slice s0104e060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gToolEffectEulerX;
extern const float gToolEffectEulerY;
extern const float gToolEffectEulerZ;
typedef int intptr_t;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cIVisualEffect : public IRefCounted {
public:
    virtual void v14(void* pConfig);
    virtual void v18(void* pParams);
    virtual void SetEnabled(int bEnabled);
    virtual void SetParamBlock(void* pBlock);
    virtual void v24();
    virtual void v28();
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
};
class cInteraction : public IRefCounted {
public:
};
class cEffectInfo : public IRefCounted {
public:
    Vec3* GetPosition();
    void* GetOrientation();
};
class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual bool GetProperty(uint32_t nKey, void** ppOut);
};
class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();
};
class cSPTimer {
public:
    virtual void Start();                       // 0x00
    virtual void Stop();                        // 0x04
    virtual bool IsRunning();                   // 0x08
    virtual void SetElapsed(uint64_t nElapsed); // 0x0c
    virtual uint64_t GetElapsedTime();          // 0x10

    void* mVftable;                             // 0x00
    int mRefCount;                              // 0x04
    uint64_t mElapsedTime;                      // 0x08
    uint8_t mBaseTime;                          // 0x10
    uint8_t mPad11[0x03];                       // 0x11
    uint32_t mBaseTimeHigh;                     // 0x14
};
class cSPUISpace : public IRefCounted {
public:
    void UpdateToolChargeBar(float fFraction);
};
class cSPSpaceInventoryItem : public IRefCounted {
public:
    cSPSpaceInventoryItem* operator=(cSPSpaceInventoryItem* pOther);
    bool IsDeselectedAfterUse();

    uint8_t mPad08[0x74];                       // 0x08
    int mnCharges;                              // 0x7c
    cSPTimer mRechargeTimer;                    // 0x80
    cSPTimer mAutoFireTimer;                    // 0x98
    cSPTimer mChargeHoldTimer;                  // 0xb0
    uint8_t mPadC8[0x18];                       // 0xc8
    void* mpName;                               // 0xe0
};
class cSPSpaceToolData_s0104_e060 : public cSPSpaceInventoryItem {
public:
    cSPSpaceToolData_s0104_e060();
    cSPSpaceToolData_s0104_e060* CopyFrom(cSPSpaceToolData_s0104_e060* pOther);
    void SetPropertyList(uint32_t nPropertyKey);
    void TryDeselectAfterUse();
    void ReloadItemEffects();
    bool NeedsCharges();
    void FreeEffectBuffers();

    uint8_t mPadE4[0x24];                       // 0xe4
    cIVisualEffect* mpEffectStage0;             // 0x108
    cIVisualEffect* mpEffectStage1;             // 0x10c
    cIVisualEffect* mpEffectStage2;             // 0x110
    cEffectInfo* mpEffectInfo;                  // 0x114
    uint8_t mPad118[0x4c];                      // 0x118
    uint32_t mDelayedValue;                     // 0x164
    uint8_t mPad168[0x0c];                      // 0x168
    uint32_t mFlags;                            // 0x174
    uint8_t mPad178[0x5c];                      // 0x178
    float mChargeTime;                          // 0x1d4
    cSpatialObject* mpToolTarget;               // 0x1d8
    cSpatialObject* mpArea;                     // 0x1dc
    cSpatialObject* mpBeam;                     // 0x1e0
    cInteraction* mpBehavior;                   // 0x1e4
    uint8_t mPriority;                          // 0x1e8
};
struct cEffectConfig {
    void* mVftable;                             // 0x00
    Vec3 mColor;                                // 0x04
    uint32_t mPhase0;                           // 0x10
    uint32_t mPhase1;                           // 0x14
    uint32_t mPhase2;                           // 0x18
    uint32_t mPhase3;                           // 0x1c
    uint32_t mPhase4;                           // 0x20
    uint32_t mPhase5;                           // 0x24
    uint8_t mChannelMask;                       // 0x28
};
struct cSpaceInventoryItemData {
    void* mVftable;                             // 0x00
    uint8_t mPad04[0x0c];                       // 0x04
    uint32_t mnItemId;                          // 0x10
    uint8_t mPad14[0x1c];                       // 0x14
    uint32_t mnFlags;                           // 0x30
};
struct cToolCategoryNode {
    void* mpKey;                                // 0x00
    void* mpCategory;                           // 0x04
    uint8_t mPad08[0x0c];                       // 0x08
    void* mpObject;                             // 0x14
};
struct cEffectNode {
    void* mpLeft;                               // 0x00
    void* mpRight;                              // 0x04
    uint8_t mPad08[0x08];                       // 0x08
    void* mpObject;                             // 0x10
    void* mpEffect;                             // 0x14
};
struct cEffectLists {
    void* mpList0[3];                           // 0x00
    void* mpList1[3];                           // 0x0c
    void* mpList2[3];                           // 0x18
    void* mpList3[3];                           // 0x24
    uint8_t mPad30[0x14];                       // 0x30
};
class cSPToolManager : public IRefCounted {
public:
    bool CreateToolFromToolID(uint32_t nToolId);
    int GetChargesForDiscoverableTool(uint32_t nToolId);
    void SelectTool(void* pTool, int nFlags, int bInstant);
    void ActivateToolEffect(void* pTool);
    void ShutdownGonzagoSubsystem();
    void ClearToolEffects();

    uint8_t mPad14[0xe4];                       // 0x14
    void* mpPropertyList;                       // 0xf8
    uint8_t mPadFc[0x0c];                       // 0xfc
    cSPSpaceInventoryItem* mpSelectedTool;      // 0x108
    uint8_t mPad10c[0x08];                      // 0x10c
    void* mpEffectTreeRoot;                     // 0x114
    uint8_t mPad118[0x08];                      // 0x118
    void* mpHandlerNode;                        // 0x120
};
class cToolManagerOwning {
public:
    cSPToolManager* mpToolManager;              // 0x00
    cSpatialObject* mpToolTarget;               // 0x04
};
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void operator_delete__(void* pMemory);
void* PropertyManager();
void* SpaceGameGet();
cSPUISpace* GetSpaceUI();
void* CreateEffectInfo();
void* GetEffectInfoBlock();
void RemoveEffectFromTree(void* pRoot, void* pKey);
void EraseToolStrategies(void* pTable);
void RemoveMessageHandler(void* pHandler);
void ReleaseEffectHandler(void* pNode);
uint32_t RandomUint32Uniform(int nRange);
void SetToolProperty(uint32_t nToolId);
void ReleaseInventoryItem(cSPSpaceInventoryItem* pItem);
bool HasToolProperty(uint32_t nItemId, uint32_t nKey, void* pOut);
cSPSpaceToolData_s0104_e060* AllocateToolData();
cSPSpaceToolData_s0104_e060* ConstructToolData(void* pMemory);
cSPSpaceToolData_s0104_e060* CreateToolDataCopy(cSPSpaceToolData_s0104_e060* pSource);
void* JoinToolEffect(void* pTool);
void* GetToolEffectConfig(void* pObject);
bool SelectInventoryTool(void* pItem);
bool AddSelectedToolToInventory(void* pItem);
extern const uint32_t gSpaceGameMode;
// ---- items of slice s0104e060 end

// ---- items of slice s0104f2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CPropertyList;
struct CStrategyMap
{
    /* 000h */ uint8_t  mPad_000[0x38];
    /* 038h */ uint32_t mTable_038[4];   // eastl hashtable (find reads +0x38/+0x3c/+0x40)
    CPropertyList* Find(uint32_t nID);   // 0x0104f850
};
struct CToolObject
{
    /* 000h */ uint8_t  mPad_000[0x7c];
    /* 07ch */ int32_t  mField_07c;
    /* 080h */ uint8_t  mPad_080[0x88 - 0x80];
    /* 088h */ uint8_t  mTimerA_088[0xa8 - 0x88];
    /* 0a8h */ uint8_t  mTimerB_0a8[0x174 - 0xa8];
    /* 174h */ uint32_t mFlags_174;
    /* 178h */ uint32_t mPropertyID_178;
    /* 17ch */ uint8_t  mPad_17c[0x1a4 - 0x17c];
    /* 1a4h */ uint32_t mEnergyCost_1a4;
    /* 1a8h */ uint8_t  mPad_1a8[0x1c0 - 0x1a8];
    /* 1c0h */ float    mField_1c0;
    /* 1c4h */ float    mField_1c4;
};
struct CPropertyList
{
    virtual void     vfn00();
    virtual void     vfn04();
    virtual void     vfn08();
    virtual int      vfn0c(uint32_t nID);
    virtual void     vfn10();
    virtual void     vfn14();
    virtual bool     vfn18(CToolObject* pOwner);
    virtual bool     vfn1c(CToolObject* pOwner);
    virtual bool     vfn20(CToolObject* pOwner, int nA, int nB);
    virtual void     vfn24();
    virtual void     vfn28();
    virtual void     vfn2c();
    virtual void     vfn30();
    virtual void     vfn34();
    virtual void     vfn38();
    virtual void     vfn3c();
    virtual void     vfn40();
    virtual uint32_t vfn44(uint32_t nValue);
};
CStrategyMap* GetToolStrategyMap();                 // 0x00b3d390: returns [0x0167eb08]
bool __fastcall FUN_0104ff10(CToolObject* pThis);   // 0x0104ff10
bool __fastcall FUN_0104fe50(CToolObject* pThis);   // 0x0104fe50
bool __fastcall FUN_0104feb0(CToolObject* pThis);   // 0x0104feb0
#define kDefaultPropertyID 0xB0DA49D9u
__forceinline bool IsFlagSet(uint32_t uWord, unsigned nBitIndex)
{
    return ((uWord >> nBitIndex) & 1) != 0;
}
__forceinline CPropertyList* GetToolProperty(uint32_t nID)
{
    if (nID)
    {
        CPropertyList* pList = GetToolStrategyMap()->Find(nID);
        if (pList)
            return pList;
    }
    return GetToolStrategyMap()->Find(kDefaultPropertyID);
}
// ---- items of slice s0104f2a0 end

// ---- items of slice s01050070 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned __int64 uint64;
#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
struct cSPTimer_s0105_0070;
struct cSPSimulatorSpaceGame_s0105_0070 {
  int* GetPlayerInventory();                                     // 0x00a1ad60
};
struct Msg {                       // message posted to the FX system
  char   pad00[0x04];              // +0x00..0x03
  float  m04;                      // +0x04
  int    m08;                      // +0x08
  int    m0c;                      // +0x0c
  ushort m0e;                      // +0x0e
  ushort m10;                      // +0x10
  short  m12;                      // +0x12
  int    m14;                      // +0x14
  int    m18;                      // +0x18
  int    m1c[9];                   // +0x1c..0x3f (matrix)
  void   ctor();                   // 0x00434040
};
void* __cdecl eOperatorNew(unsigned size, const char* name, int a, int b,
                           const char* file, int line);          // 0x00f473a0
void  __cdecl eOperatorDeleteArray(void* p);                     // 0x00f47380
void  __cdecl FUN_0104f140(void* a, uint b, void* c);            // 0x0104f140
void  __cdecl FUN_0104f100(void* a, void* b, void* c, void* d, void* e); // 0x0104f100
void  __cdecl FUN_0104f1b0(void* a, void* b, void* c);           // 0x0104f1b0
void  __cdecl FUN_0104f900(void* a, void* b, void* c);           // 0x0104f900
void  __cdecl FUN_006606a0(void* a);                             // 0x006606a0
bool  __cdecl SP_GetPropertyAsKeyInstance(int obj, uint key, int* out); // 0x006a12a0
void* __cdecl SP_EffectsManager();                               // 0x0067ddd0
void  __cdecl FUN_0104fcd0(void* p);                             // 0x0104fcd0
void  __cdecl PtrField_assign(void* p);                          // 0x00ad7ec0
void* __cdecl GetUFOSimulator();                                 // 0x00ffbe50
int*  __cdecl QuaternionToMatrix(void* out, int quat);           // 0x004a9b40
struct cInventory { char pad00[0x34]; void* m34; };              // player inventory view
struct cSPTimer_s0105_0070 {
  char   pad[0x20];              // +0x00..0x1f
  void   Restart();              // 0x00bc3130
  void   Stop();                 // 0x00bc3170
  uint64 GetElapsedTime();       // 0x00bc3190
  bool   IsRunning();            // 0x00feba90
};
struct cSPToolManager_s0105_0070;
struct ArrayHeader { int count; };   // +0x00: element count; buffer begins at +0x04
struct cSPToolManager_s0105_0070 {
  char     pad00[0x0c];          // +0x00..0x0b
  char     m0c_sub[0x24];        // +0x0c..0x2f embedded effect-target owner object
  void*    m30;                  // +0x30
  char     pad34[0x48];          // +0x34..0x7b
  int      m7c;                  // +0x7c
  char     m80;                  // +0x80
  char     pad81[0x07];          // +0x81..0x87
  cSPTimer_s0105_0070 mTimer88;             // +0x88
  cSPTimer_s0105_0070 mTimerA8;             // +0xa8
  cSPTimer_s0105_0070 mTimerC8;             // +0xc8
  char     padE8[0x20];          // +0xe8..0x107
  void*    m108;                 // +0x108
  void*    m10c;                 // +0x10c
  void*    m110;                 // +0x110
  void*    m114;                 // +0x114
  void*    m118;                 // +0x118
  int      m11c;                 // +0x11c
  char     pad120[0x1c];         // +0x120..0x13b
  char     m13c;                 // +0x13c
  char     pad13d[0x33];         // +0x13d..0x16f
  void*    m170;                 // +0x170
  uint     m174;                 // +0x174
  void*    m178;                 // +0x178
  char     pad17c[0x20];         // +0x17c..0x19b
  int      m19c;                 // +0x19c
  char     pad1a0[0x04];         // +0x1a0..0x1a3
  int      m1a4;                 // +0x1a4
  float    m1a8;                 // +0x1a8
  char     pad1ac[0x14];         // +0x1ac..0x1bf
  float    m1c0;                 // +0x1c0
  float    m1c4;                 // +0x1c4
  char     pad1c8[0x0c];         // +0x1c8..0x1d3
  float    m1d4;                 // +0x1d4

  bool  FUN_0104fe50();          // 0x0104fe50
  bool  FUN_0104feb0();          // 0x0104feb0
  void* Lookup(uint key);        // 0x0104f850
  void  UseToolStop(cSPToolManager_s0105_0070* self);                                   // 0x0104fa90
  char  UseToolStart(cSPToolManager_s0105_0070* self, int a2, int a3, int a4, int a5,
                     int a6, int a7);                                        // 0x01050070
  char  UseToolUpdate(cSPToolManager_s0105_0070* self, int a2, int a3, int a4);         // 0x010504a0
  int*  CreateGenericToolEffect(cSPToolManager_s0105_0070* self);                      // 0x01050640
};
struct cVec14 {
  char* begin;                   // +0x00
  char* end;                     // +0x04
  char* cap;                     // +0x08
  void  insert(void* pos, uint count, void* val);   // 0x01050850
};
// ---- items of slice s01050070 end

// ---- items of slice s01050bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_01021300(void);                 // 0x01021300  cSPLivingUniverse::GetPlayerEmpire
extern "C" void* __cdecl FUN_00ffbe50(void);                 // 0x00ffbe50  GetUFOSimulator
extern "C" void* __cdecl FUN_00b3d390(void);                 // 0x00b3d390  palette/property manager getter
extern "C" void* __cdecl FUN_01021080(void);                 // 0x01021080  cSPLivingUniverse::GetUniverseContext
extern "C" void* __cdecl FUN_01021260(void);                 // 0x01021260  GetActivePlanet
extern "C" void* __cdecl FUN_00b3d300(void);                 // 0x00b3d300  NounManager
extern "C" int   __cdecl FUN_004eb930(const void* a, const void* b);                 // 0x004eb930
extern "C" int   __cdecl FUN_0102aec0(void* pTool, float* pA, float* pB);            // 0x0102aec0  IsNearbyObject
extern "C" int   __cdecl FUN_010527f0(void* pTool, uint32_t id, int flag);           // 0x010527f0  SetErrorEvent
extern "C" void  __cdecl FUN_0104e060(void* pOut, float, float, float, float);       // 0x0104e060  ComputeToolEffectPosition
struct Vec3_s0105_0bb0 { float x, y, z; };
struct Key3 { uint32_t a, b, c; };
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
class tHost {
public:
    void*    __thiscall FUN_00a1ad60();                            // 0x00a1ad60  cSPSimulatorSpaceGame::GetPlayerInventory
    uint32_t __thiscall FUN_00c30cb0();                            // 0x00c30cb0  [ecx+0xd0]
    uint32_t __thiscall FUN_00ffc2d0();                            // 0x00ffc2d0  [ecx+0xd8]
    void*    __thiscall FUN_0104f850(uint32_t key);                // 0x0104f850
    uint32_t __thiscall FUN_0104bff0();                            // 0x0104bff0  tool flag query
    uint32_t __thiscall FUN_01050020();                            // 0x01050020  cSPSpaceToolData::GetUseCost
    int      __thiscall FUN_0104cb70();                            // 0x0104cb70  cSPSpaceToolData::IsInContext
    uint8_t  __thiscall FUN_00feba90();                            // 0x00feba90  cSPTimer::IsRunning
    bool     __thiscall FUN_00c37170();                            // 0x00c37170  empire bool query
    void     __thiscall FUN_0083f660();                            // 0x0083f660  byte[ecx+0x28] = 1
    void     __thiscall FUN_00ffc0a0();                            // 0x00ffc0a0  ++dword[ecx+0x24]
    void*    __thiscall FUN_00f67d90();                            // 0x00f67d90  cTerrainEditor::GetCurrentTerrainSphere
    void*    __thiscall FUN_008414c0();                            // 0x008414c0  [ecx+0x154]
    void     __thiscall FUN_00c7e2f0(uint8_t b);                   // 0x00c7e2f0
    void     __thiscall FUN_00c75640();                            // 0x00c75640  cSPTimer::Stop(ecx+0x1258)
    void*    __thiscall FUN_01050070(void* pTool, void* pSub, Vec3_s0105_0bb0* pPos, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x01050070 UseToolStart
    uint32_t __thiscall FUN_010504a0(void* pTool, Vec3_s0105_0bb0* pPos, int flag, uint32_t d);   // 0x010504a0 UseToolUpdate
    void     __thiscall FUN_0104fa90(void* pTool);                 // 0x0104fa90 UseToolStop
    void*    __thiscall FUN_01051c30();                            // 0x01051c30  RandDoubleUniform thunk
    double   __thiscall FUN_009360d0();                            // 0x009360d0  RandomDoubleUniform
    uint32_t __thiscall FUN_00a68fb0(uint32_t n);                  // 0x00a68fb0  RandomUint32Uniform
};
extern Key3 DAT_016e1440;                                     // 0x016e1440  kTool_planetbusterbomb
extern Key3 DAT_016e1734;                                     // 0x016e1734  kTool_portal
extern Key3 DAT_016e138c;                                     // 0x016e138c  kTool_placecolony
extern Key3 DAT_016e1554;                                     // 0x016e1554  kTool_CreatureEdit
extern Key3 DAT_016e15c0;                                     // 0x016e15c0  kTool_zoo
class cSPToolData {
public:
    uint8_t  mPad000[0x80];    // +0x000
    uint8_t  m080;             // +0x080  mnPriority / auto-handler flag
    uint8_t  mPad081[0x97];    // +0x081
    void*    m118;             // +0x118  charge visual effect object
    uint8_t  mPad11c[0x2c];    // +0x11c
    float    m148;             // +0x148  mDamageMultiplier
    uint8_t  mPad14c[0x28];    // +0x14c
    uint32_t m174;             // +0x174  mStrategyClassID
    uint32_t m178;             // +0x178  mToolType
    uint32_t m17c;             // +0x17c  mWeaponSubtype
    uint8_t  mPad180[0x24];    // +0x180
    uint32_t m1a4;             // +0x1a4  mEnergyCost
    float    m1a8;             // +0x1a8  mDamageArea
    uint8_t  mPad1ac[0x20];    // +0x1ac
    float    m1cc;             // +0x1cc  mDamageRadius
    uint8_t  mPad1d0[0x84];    // +0x1d0
    uint32_t m254;             // +0x254  tool flags
};
struct cSpaceGame {
    uint8_t  mPad000[0x18];    // +0x000
    uint8_t  m18;              // +0x018
    uint8_t  mPad019[7];       // +0x019
    uint8_t  m20;              // +0x020
    uint8_t  mPad021[3];       // +0x021
    uint32_t m24;              // +0x024
    uint8_t  mPad028[0x0c];    // +0x028
    uint8_t  mSub34[0x0c];     // +0x034  subobject (vtable)
    uint8_t  mPad040[0x7b4];   // +0x040
    float    m7f4;             // +0x7f4
};
class cSPToolManager_s0105_0bb0 {
public:
    uint32_t __thiscall PlayerUseToolStart(cSPToolData* pTool, float* pPos, uint32_t p3);  // 0x01050bb0 (cSPToolManager::PlayerUseToolStart)
    uint8_t  __thiscall PlayerUseToolUpdate(cSPToolData* pTool, float* pPos, uint32_t p3);
    Key3*    __thiscall GetRandomDiscoverableTool(Key3* pOut);  // 0x010513a0 (cSPToolManager::GetRandomDiscoverableTool)
};
// ---- items of slice s01050bb0 end

// ---- items of slice s01051850 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) throw() { return p; }
void EASTL_allocator_deallocate(void* p);   // 0x00f47380 (operator delete[])
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    bool operator!=(const Vector3& b) const { return x != b.x || y != b.y || z != b.z; }
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct Matrix3 { float m[9]; };
Quaternion QuaternionFromMatrix33(const Matrix3& m, float tolerance);   // 0x00472b80
Matrix3 Matrix3FromQuaternion(const Quaternion& q);   // 0x0059c190 (cdecl, result by value)
extern Vector3 kInvalidPosition;   // 0x016e12cc (runtime-initialized copy)
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};
struct ResourceKeyZ {   // default-constructed key (zeroed)
    uint32_t instanceID, typeID, groupID;
    ResourceKeyZ() : instanceID(0), typeID(0), groupID(0) {}
    ResourceKeyZ& operator=(const ResourceKey& o) {
        instanceID = o.instanceID; typeID = o.typeID; groupID = o.groupID; return *this;
    }
};
struct Transform {
    uint16_t mFlags;
    uint16_t mnRevision;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    Transform();                                            // 0x00409930
    Vector3 GetOffset() const { return mOffset; }
    void SetOffset(const Vector3& v) { mFlags |= 4; mOffset = v; mnRevision++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnRevision++; mFlags |= 2; }
    void SetScale(float s) { mnRevision++; mfScale = s; }
};
struct EffectTransform {
    uint16_t mFlags;
    uint16_t mnRevision;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    EffectTransform();                                      // 0x00434040
    void SetOffset(const Vector3& v);                       // 0x00571d40
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mnRevision++; }
};
template <typename T>
struct sp_vector {   // 0x14 bytes, storage carries a header dword before the data
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* position, const T& value);   // 0x004e3e10
    void push_back(const T& value)                          // inline; out-of-line copy 0x004e19a0
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T& back() { return *(mpEnd - 1); }
};
struct cPlantProfile;
struct PlantProfileArray {   // 0x418 bytes: fixed_vector<cPlantProfile*, 256>
    cPlantProfile** mpBegin;
    cPlantProfile** mpEnd;
    cPlantProfile** mpCapacity;
    uint32_t mAllocator[2];
    uint32_t mHeader;            // +0x14 (zero = inline buffer)
    cPlantProfile* mBuffer[256]; // +0x18

    PlantProfileArray(int n, cPlantProfile* const& value);   // 0x00ac1060
    ~PlantProfileArray()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int flags);                          // +0x08
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void SetTransform(const EffectTransform& t);    // +0x18
};
struct IVisualEffectPtr {
    IVisualEffect* mpObject;
    IVisualEffectPtr() : mpObject(0) {}
    ~IVisualEffectPtr() { if (mpObject) mpObject->Release(); }
    IVisualEffect** AsPPTypeParam();                        // 0x00a16f40
    IVisualEffect* get() const { return mpObject; }
    IVisualEffect* operator->() const { return mpObject; }
};
struct IEffectsManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst); // +0x2c
};
IEffectsManager* EffectsManager();          // 0x0067ddd0
IEffectsManager* EffectsManager2();         // 0x0067de30
struct IMessageManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void PostMSG(uint32_t messageID, void* pData, void* p2, int p3);  // +0x18
};
IMessageManager* MessageManager();          // 0x0067dcc0
struct cSpatialObjectI {   // cSpatialObject vtable view
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3& GetPosition();                   // +0x2c
    virtual const Quaternion& GetOrientation();             // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3& v);             // +0x38
    virtual void SetOrientation(const Quaternion& q);       // +0x3c
};
struct cToolEffectHolder {
    uint32_t pad[0x38 / 4];
    int mEffectHandle;                                      // +0x38
};
struct cToolEffectHost {
    cToolEffectHolder* Add(const Vector3& pos, float radius);   // 0x00ae41b0
};
cToolEffectHost* ToolEffectHost();          // 0x00b26930
struct IPlanetEffects {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void v50();
    virtual int AttachEffect(const Transform& t, IVisualEffect* effect);    // +0x54
virtual void v58();
virtual void v5c();
virtual void v60();
    virtual void PlaceAt(const Transform& t, uint32_t id, int flags);       // +0x64
};
struct cPlanetModel {
    uint32_t pad[0x24 / 4];
    IPlanetEffects* mpEffects;                              // +0x24
    Quaternion BuildSurfaceOrientation(const Vector3& pos); // 0x00b7f190
};
cPlanetModel* PlanetModel_s0105_1850();                // 0x00b3d350
struct cSimulationEvent {   // 0x30 bytes; ctor 0x00ad79d0, dtor 0x00ad7ad0
    uint32_t pad[0x30 / 4];
    cSimulationEvent(const Vector3& pos, const Quaternion& orientation);   // 0x00ad79d0
    ~cSimulationEvent();                                    // 0x00ad7ad0
};
struct cGameModeState {
    uint32_t GetModeID(const char* name);                   // 0x00ad7db0
    bool IsInEditor();                                      // 0x00ac80f0
    void Trigger(uint32_t id, cSimulationEvent* evt, int flags);   // 0x00ae09b0
    void Announce(const char* name, int a, int b, int c, int d, int e);  // 0x00ae0930
};
cGameModeState* GameModeState();            // 0x00b3d4d0
void TriggerAdventureEvent(const char* name, uint32_t id, int flag);   // 0x01041c50 (cdecl)
struct cPlanetObjectData {   // 0x2c bytes
    uint32_t pad[0x2c / 4];
    cPlanetObjectData(int type, const Vector3& pos);       // 0x0104e290
};
struct PlanetObjectVector {
    cPlanetObjectData* mpBegin;
    cPlanetObjectData* mpEnd;
    cPlanetObjectData* mpCapacity;
    uint32_t mAllocator[2];
    void push_back_planetobj(const cPlanetObjectData& v);   // 0x00acbbe0 (vector::push_back)
};
struct cPlantProfile {
    uint32_t pad[0x504 / 4];
    ResourceKey mKey;                                       // +0x504
    uint32_t pad2[(0x57c - 0x510) / 4];
    uint32_t mPlantType;                                    // +0x57c
};
struct cPlanetRecord;
struct cStarRecordView {
    void SetSpeciesKey(const ResourceKey& key);             // 0x00bb9b90
};
struct cPlanetRecord {
    uint32_t pad[0xbc / 4];
    sp_vector<ResourceKey> mPlantSpecies;                   // +0xbc
    sp_vector<ResourceKey> mAnimalSpecies;                  // +0xd0
    uint32_t pad2[(0x134 - 0xe4) / 4];
    PlanetObjectVector mPlanetObjects;                      // +0x134
    uint32_t GetID();                                       // 0x00ce6950
    cStarRecordView* GetStarView();                         // 0x00b8de30
};
struct PlantSwapData {   // 0x50 bytes; ctor 0x0104ef00, dtor 0x0104e6f0
    sp_vector<ResourceKey> mOldPlants;                      // +0x00
    sp_vector<ResourceKey> mNewPlants;                      // +0x14
    sp_vector<ResourceKey> mOldAnimals;                     // +0x28
    sp_vector<ResourceKey> mNewAnimals;                     // +0x3c
    PlantSwapData();                                        // 0x0104ef00
    ~PlantSwapData();                                       // 0x0104e6f0
};
struct cPlanetSim {
    void ApplySwap(PlantSwapData& data);                    // 0x00c80780
};
struct cPlanet {
    uint32_t pad[0x13c / 4];
    cPlanetRecord* mpPlanetRecord;                          // +0x13c
    void ReplaceSpecies(const ResourceKey& key, int a, int b);   // 0x00c74690
    cPlanetSim* GetPlanetSim();                             // 0x008414c0
    int GetTechLevel();                                     // 0x00c70e00
};
cPlanet* GetActivePlanet();                 // 0x01021260
cPlanetRecord* GetActivePlanetRecord();     // 0x010212a0
cPlanetRecord* GetPlayerHomePlanet();       // 0x01021370
struct cSpeciesManager {
    void GetMatchingPlantProfiles(PlantProfileArray& dst, int count, uint32_t type);  // 0x004dfd50
    cPlantProfile* GetPlantProfile(const ResourceKey& key);     // 0x004df440
    cPlantProfile* GetProfile(const ResourceKey& key);          // 0x004df550
};
cSpeciesManager* SpeciesManager();          // 0x00401090
uint32_t GetReplacementSpecies(cPlantProfile* profile);     // 0x01041d30 (cdecl)
struct cSpeciesPool {
    cPlantProfile* Pick(uint32_t id);                       // 0x00ac10a0
};
cSpeciesPool* SpeciesPool();                // 0x00b3d450
struct cTerraformingManager {
    int GetTerraformLevel(cPlanetRecord* rec);                          // 0x00bbc670
    ResourceKey GetPlantKey(int level, uint32_t type, cPlanetRecord* rec);      // 0x00bbc870
    ResourceKey GetAnimalKey(int level, int kind, cPlanetRecord* rec);          // 0x00bbc950
    ResourceKey GetCreatureKey(int level, cPlanetRecord* rec);                  // 0x00bbca30
};
cTerraformingManager* TerraformingManager();    // 0x00b3d430
struct cTerrainObjectList {
    void Clear();                                           // 0x00c53a90
};
struct cTerrainObjectEntry {
    uint32_t pad[2];
    cTerrainObjectList mList;                               // +0x08
};
struct cTerrainObjectMap {
    cTerrainObjectEntry& operator[](const uint32_t& key);   // 0x00ba4e60
};
struct cTerrainSphere {
    uint32_t pad[0x11c0 / 4];
    cTerrainObjectMap mObjects;                             // +0x11c0
};
struct cCreatureAnimal {
    uint32_t pad[0xc0 / 4];
    cSpatialObjectI mSpatial;                               // +0xc0
    uint32_t pad2[(0x135 - 0xc4) / 4];
    uint8_t pad3;
    bool mbAlive;                                           // +0x135
    uint8_t pad4[0xb5e - 0x136];
    bool mbIsPlayer;                                        // +0xb5e
    bool IsInTribe();                                       // 0x00c0c0e0
    const ResourceKey& GetSpeciesKey();                     // 0x00c0bc00
};
struct CreatureVector {
    cCreatureAnimal** mpBegin;
    cCreatureAnimal** mpEnd;
};
struct cOrnament {
    void SetModelKey(uint32_t instance, int type, uint32_t group);  // 0x00c6f770
    uint32_t pad[0x70 / 4];
    cSpatialObjectI mSpatial;                               // +0x70
};
struct cGameNounManager {
    cOrnament* CreateNoun(uint32_t nounID);                 // 0x00b20c60
    const CreatureVector& GetCreatures();                   // 0x00ace2f0
    cTerrainSphere* GetCurrentTerrainSphere();              // 0x00f67d90
};
cGameNounManager* NounManager();            // 0x00b3d300
struct cPositionTracker {
    void Update(const ResourceKey& key, const Vector3& pos);    // 0x00acf3e0
};
cPositionTracker* PositionTracker();        // 0x00b3d480
struct cUFO {
    void SetToolActive(bool b);                             // 0x00c37130
    void PopToDestination();                                // 0x00c37e60
    void SetDestination(const Vector3& pos);                // 0x00c3bfe0
    void SetDestinationStar(uint32_t star);                 // 0x00c3c190
    uint32_t pad[0x34 / 4];
    cSpatialObjectI mSpatial;                               // +0x34
    uint32_t pad2[(0x75c - 0x38) / 4];
    uint32_t mDestinationStar;                              // +0x75c
};
struct cUFOSimulator {
    cUFO* GetPlayerUFO();                                   // 0x00a1ad60
    void PopState();                                        // 0x00ffc0b0
    void ClearPending();                                    // 0x00ffc0d0
    uint32_t pad[0x18 / 4];
    bool mb18;                                              // +0x18
    uint8_t pad19[7];
    bool mb20;                                              // +0x20
};
cUFOSimulator* UFOSimulator();              // 0x00ffbe50
struct cSpaceInventory {
    virtual void v00();
    // slot 0x8c
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
    virtual int GetCapacity();                              // +0x8c
};
void AddPlantItem(cSpaceInventory* inv, const ResourceKeyZ& key, int& capacity, int count);   // 0x0104e620
void AddAnimalItem(cSpaceInventory* inv, const ResourceKeyZ& key, int& capacity, int count);  // 0x0104e570
struct cAvatar {
    void Abduct();                                          // 0x00ffb030
    void Release();                                         // 0x00ffb180
};
struct cSpaceGame_s0105_1850 {
    cSpaceInventory* GetPlayerInventory();                  // 0x00a1ad60
    cAvatar* GetAvatar();                                   // 0x00b1fdb0
    void OnPlanetUplifted(cPlanet* planet);                 // 0x0100aec0
};
cSpaceGame_s0105_1850* SpaceGame();                    // 0x01002bd0
struct cAppModeSpace {
    void SetMode(int mode);                                 // 0x00fde3e0
    void TransitionFromPlanetToSolar(cStarRecordView* star, int flag);   // 0x00fdd390
};
cAppModeSpace* AppModeSpace();              // 0x00fd9c60
struct cMission {
    cPlanet* GetTargetPlanet();                             // 0x00970b30
};
struct cMissionManager {
    cMission* GetMissionByID(uint32_t id);                  // 0x00fee480
};
cMissionManager* MissionManager();          // 0x00feb9f0
struct cAchievements {
    void AutoTest(uint32_t id, int flag);                   // 0x00676e90
};
cAchievements* AchievementsController();    // 0x00675250
struct ToolMessage {
    uint32_t mID;                                           // +0x00
    uint32_t mField4;
    uint32_t mValue;                                        // +0x08
    uint32_t pad[7];
    Transform* mpTransform;                                 // +0x28
};
struct ISimulatorStrategy { virtual void s0(); };
struct DefaultRefCounted { virtual void r0(); int mnRefCount; };
struct cStrategy : ISimulatorStrategy, DefaultRefCounted { uint32_t mStrategy[4]; };   // 0x1c
struct IUnmanagedMessageListener {
    virtual ~IUnmanagedMessageListener();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};
struct LocalizedString { uint32_t data[5]; };
class cToolManager : public cStrategy, public IUnmanagedMessageListener {
public:
    virtual ~cToolManager();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);

    ResourceKey field_20;                                   // +0x20
    Vector3 field_2C;                                       // +0x2c
    uint32_t mStrategies[8];                                // +0x38
    uint32_t field_58[7];                                   // +0x58
    LocalizedString mToolFailTexts[26];                     // +0x74
    uint32_t field_27C[5];                                  // +0x27c
    Vector3 field_290;                                      // +0x290
};
// ---- items of slice s01051850 end

// ---- items of slice s013ac650 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__cdecl *fp)();
struct PropDesc {
    const char* name;
    unsigned    hash;
    int         off;
    int         p3, p4, p5;
    int         z0, z1;
    fp          f[7];
    PropDesc(const char* n, unsigned h, int o, fp f0, fp a, fp b, fp c, fp d, fp e, fp ff)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = a; f[2] = b; f[3] = c; f[4] = d; f[5] = e; f[6] = ff; off = o;
    }
};
extern PropDesc g_015b8850, g_015b888c, g_015b88c8, g_015b8904, g_015b8940, g_015b897c,
                g_015b89b8, g_015b89f4, g_015b8a30, g_015b8a6c, g_015b8aa8, g_015b8ae4,
                g_015b8b20, g_015b8b5c, g_015b8b98, g_015b8bd4;
// ---- items of slice s013ac650 end

// @ 0x0104bcc0
u8 SP::cSPSpaceToolData_s0104_bcc0::Write(cOutStream* stream)
{
    cIface* a = (cIface*)stream->Call(0x20);
    u32 tag = 0x707459f0;
    cIface* b = (cIface*)a->Call(0x18);
    WriteUint32(b, &tag, 1, 0);
    u8 ok = FUN_00c87580(stream);
    cVarListSerializer_s0104_bcc0 ser;
    ser.ctorRaw((u8*)this - 0xc, 0x15b8850, 0x1a80d26);
    u8 serOk = ser.Serialize(stream);
    if (serOk != 0 && ok != 0) return 1;
    return 0;
}

// @ 0x0104bde0
i32 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104bde0()
{
    i32 v = (i32)(mField1c0 * 1000.0f);
    if (v < 0) v = -1;
    return v;
}

// @ 0x0104be00
i32 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104be00()
{
    i32 v = (i32)(mField1c4 * 1000.0f);
    if (v < 0) v = -1;
    return v;
}

// @ 0x0104be30
f64 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104be30()
{
    return (f64)mField1cc * (f64)mField148;
}

// @ 0x0104c910
SP::cSPSpaceToolData_s0104_bcc0::~cSPSpaceToolData_s0104_bcc0()
{
    mpVftable0 = &vtbl_cSpaceToolData;
    mpVftable8 = &vtbl_cSpaceToolData8;
    mpVftableC = &vtbl_cSpaceToolDataC;
    mWaterColorID.dtorRaw();
    if (mField16c != 0)  mField16c->RefCountRelease();
    if (mField140 != 0)  mField140->RefCountRelease();
    if (mField12c != 0)  mField12c->RefCountRelease();
    if (mField128 != 0)  mField128->RefCountRelease();
    if (mField124 != 0)  mField124->RefCountRelease();
    if (mField120 != 0)  mField120->RefCountRelease();
    if (mEffect118 != 0) mEffect118->EffectRelease();
    cToolRef** p = &mEffect114;
    if (mEffect114 != 0) mEffect114->EffectRelease();
    for (i32 i = 2; i >= 0; i--) {
        p--;
        cToolRef* r = *p;
        if (r != 0) r->RefCountRelease();
    }
    mChargeTimer.dtorRaw();
    mAutoFireTimer.dtorRaw();
    mRechargeTimer.dtorRaw();
    mIsInUse.dtorRaw();
    baseDtorRaw();
}

// @ 0x0104cb70
bool SP::cSPSpaceToolData_s0104_bcc0::IsInContext()
{
    bool result = false;
    if (mUpgradeInstance != 0) {
        if (mUpgradeInstance != 0x5f848353) {
            result = true;
        } else if (PlanetModel() != 0 && ((cPlanetModel_s0104_bcc0*)PlanetModel())->mpAnchor24 != 0) {
            if (GetCurrentGameMode() != &gGameMode01654c05) {
                result = true;
            } else if (GetUniverseContext() == 0) {
                result = true;
            }
        }
    }
    return result;
}

// @ 0x0104cbd0
void SP::cSPSpaceToolData_s0104_bcc0::FUN_0104cbd0(i32 delta)
{
    i32 limit = mLimit1a0;
    if (mAmmo7c < limit) {
        i32 v = mAmmo7c + delta;
        mAmmo7c = v;
        if (v > limit) mAmmo7c = limit;
    }
}

// @ 0x0104cc00
void SP::cSPSpaceToolData_s0104_bcc0::FUN_0104cc00(i32 amount)
{
    if (amount == -1) amount = mField19c;
    mAmmo7c -= amount;
}

// @ 0x0104cc40
u32 SP::cSPSpaceToolData_s0104_bcc0::IsDeselectedAfterUse()
{
    cPropertyList_s0104_bcc0* pl = mpPropList30;
    if (pl != 0) {
        Property* p;
        if (pl->FindProperty(0x3348701, &p) && p->mType12 == 1 && *p->GetBool())
            goto Ltrue;
    }
    if (((mFlags174 >> 0xf) & 1) == 0) return 0;
Ltrue:
    return 1;
}

// @ 0x0104cc90
u8 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104cc90()
{
    bool result = false;
    cPropertyList_s0104_bcc0* pl = mpPropList30;
    if (pl != 0) {
        Property* p;
        if (pl->FindProperty(0x6df688d, &p) && p->mType12 == 1)
            result = *p->GetBool();
    }
    return (u8)result;
}

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
    { Property_s0104_cf20* p; PropertyList* pl = mName.mpLocalString;
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

// @ 0x0104e260
void cSPSpaceToolData_s0104_e060::TryDeselectAfterUse()
{
    if (!IsDeselectedAfterUse())
        return;

    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
    void* pInventory = pSpaceGame->GetPlayerInventory();
    if (pInventory != nullptr)
        ReleaseInventoryItem(this);
}

// @ 0x0104e290
void SetEffectConfig(cEffectConfig* pConfig, uint32_t nChannel, const Vec3* pColor)
{
    pConfig->mPhase3 = 0;
    pConfig->mPhase4 = 0;
    pConfig->mPhase5 = 0;
    pConfig->mChannelMask = (uint8_t)(1 << (nChannel & 0x1f));
    pConfig->mColor.mX = pColor->mX;
    pConfig->mColor.mY = pColor->mY;
    pConfig->mColor.mZ = pColor->mZ;
    pConfig->mPhase2 = 0;
}

// @ 0x0104e2f0
uint32_t cSpaceInventoryItem_GetItemCount(cSpaceInventoryItemData* pItem, uint32_t* pCount)
{
    if (((pItem->mnFlags >> 5) & 1) != 0)
        *pCount = pItem->mnItemId;
    return pItem->mnFlags >> 5 & 0xffffff01;
}

// @ 0x0104e320
bool cSPSpaceToolData_s0104_e060::NeedsCharges()
{
    if (((mFlags >> 5) & 1) != 0 && mnCharges < 1)
        return true;
    return false;
}

// @ 0x0104e340
bool cSPToolManager::CreateToolFromToolID(uint32_t nToolId)
{
    cPropertyList* pPropertyManager = (cPropertyList*)PropertyManager();
    pPropertyManager->v2c();

    cSPSpaceToolData_s0104_e060* pTool = AllocateToolData();
    pTool->SetPropertyList(0x30608f0bu);
    pTool->mFlags = 0;
    pTool->mnCharges = 1;

    uint32_t nValue = 0;
    if (HasToolProperty(0x30608f0bu, 0xf0609eceu, &nValue))
        pTool->mpName = (void*)(intptr_t)nValue;
    if (HasToolProperty(0x30608f0bu, 0xf0609ed9u, &nValue))
        pTool->mDelayedValue = nValue;

    mpSelectedTool = pTool;
    pTool->Release();
    SetToolProperty(nToolId);
    return true;
}

// @ 0x0104e470
int cSPToolManager::GetChargesForDiscoverableTool(uint32_t nToolId)
{
    int nMin = 0;
    int nMax = 0;

    cPropertyList* pPropertyManager = (cPropertyList*)PropertyManager();
    cSPSpaceToolData_s0104_e060* pTool = nullptr;
    pPropertyManager->v2c();

    uint32_t nValue = 0;
    if (HasToolProperty(nToolId, 0x2e06e31u, &nValue))
        nMin = (int)nValue;
    if (pTool != nullptr && HasToolProperty(nToolId, 0x2e06e36u, &nValue))
        nMax = (int)nValue;

    if (nMin != 0 && nMax != 0) {
        int nRandom = (int)RandomUint32Uniform(nMax - nMin);
        if (pTool != nullptr)
            pTool->Release();
        return nRandom + nMin;
    }
    if (pTool != nullptr)
        pTool->Release();
    return 1;
}

// @ 0x0104e570
void cSPToolManager::SelectTool(void* pTool, int nFlags, int bInstant)
{
    if (pTool == nullptr)
        return;

    void* pCandidate = nullptr;
    SelectInventoryTool(pTool);
    RemoveEffectFromTree(pCandidate, pTool);

    cSpatialObject* pObject = (cSpatialObject*)pCandidate;
    if (pObject != nullptr) {
        uint32_t nValue = 0;
        (void)nValue;
        bool bAdded = AddSelectedToolToInventory(pCandidate);
        if (mpSelectedTool != nullptr || bAdded) {
            mpEffectTreeRoot = (void*)&pObject;
            if (!bAdded)
                mpEffectTreeRoot = (void*)((uint8_t*)mpEffectTreeRoot - 4);
        }
    }
    (void)nFlags;
    (void)bInstant;
}

// @ 0x0104e620
void cSPToolManager::ActivateToolEffect(void* pTool)
{
    if (pTool == nullptr)
        return;

    void* pEffect = nullptr;
    void* pObject = JoinToolEffect(pTool);
    if (pObject != nullptr) {
        bool bAdded = AddSelectedToolToInventory(pObject);
        if (mpSelectedTool != nullptr || bAdded) {
            void* pConfig = nullptr;
            pConfig = GetToolEffectConfig(pObject);
            mpEffectTreeRoot = (void*)&mpSelectedTool;
            if (!bAdded)
                mpEffectTreeRoot = (void*)((uint8_t*)mpEffectTreeRoot - 4);
        }
    }
    (void)pEffect;
}

// @ 0x0104e6f0
void cSPSpaceToolData_s0104_e060::FreeEffectBuffers()
{
    uint8_t** ppBlock = (uint8_t**)this;
    if (ppBlock[0xf] != nullptr && *(int*)(ppBlock[0xf] - 4) != 0)
        operator_delete__(ppBlock[0xf]);
    if (ppBlock[10] != nullptr && *(int*)(ppBlock[10] - 4) != 0)
        operator_delete__(ppBlock[10]);
    if (ppBlock[5] != nullptr && *(int*)(ppBlock[5] - 4) != 0)
        operator_delete__(ppBlock[5]);
    if (ppBlock[0] != nullptr && *(int*)(ppBlock[0] - 4) != 0)
        operator_delete__(ppBlock[0]);
}

// @ 0x0104e7b0
cToolCategoryNode* CreateToolCategoryNode(cToolManagerOwning* pOwner)
{
    cToolCategoryNode* pNode = (cToolCategoryNode*)
        (intptr_t)operator_new(0x18, "Simulator", 0, 0,
                               "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                               0xd1);
    pOwner = pOwner;
    pNode->mpKey = pOwner->mpToolManager;
    if (pOwner->mpToolManager != nullptr)
        pOwner->mpToolManager->AddRef();
    pNode->mpObject = pOwner->mpToolTarget;
    if (pOwner->mpToolTarget != nullptr)
        pOwner->mpToolTarget->AddRef();
    return pNode;
}

// @ 0x0104e810
cSPSpaceToolData_s0104_e060* cSPSpaceToolData_s0104_e060::CopyFrom(cSPSpaceToolData_s0104_e060* pOther)
{
    cSPSpaceInventoryItem::operator=(pOther);
    if (this == pOther)
        return this;

    mRechargeTimer.mVftable = pOther->mRechargeTimer.mVftable;
    mRechargeTimer.mRefCount = pOther->mRechargeTimer.mRefCount;
    mRechargeTimer.mElapsedTime = pOther->mRechargeTimer.mElapsedTime;
    mRechargeTimer.mBaseTime = pOther->mRechargeTimer.mBaseTime;
    mRechargeTimer.mBaseTimeHigh = pOther->mRechargeTimer.mBaseTimeHigh;

    mAutoFireTimer.mVftable = pOther->mAutoFireTimer.mVftable;
    mAutoFireTimer.mRefCount = pOther->mAutoFireTimer.mRefCount;
    mAutoFireTimer.mElapsedTime = pOther->mAutoFireTimer.mElapsedTime;
    mAutoFireTimer.mBaseTime = pOther->mAutoFireTimer.mBaseTime;
    mAutoFireTimer.mBaseTimeHigh = pOther->mAutoFireTimer.mBaseTimeHigh;

    mChargeHoldTimer.mVftable = pOther->mChargeHoldTimer.mVftable;
    mChargeHoldTimer.mRefCount = pOther->mChargeHoldTimer.mRefCount;
    mChargeHoldTimer.mElapsedTime = pOther->mChargeHoldTimer.mElapsedTime;
    mChargeHoldTimer.mBaseTime = pOther->mChargeHoldTimer.mBaseTime;
    mChargeHoldTimer.mBaseTimeHigh = pOther->mChargeHoldTimer.mBaseTimeHigh;

    if (mpEffectStage1 != pOther->mpEffectStage1) {
        if (pOther->mpEffectStage1 != nullptr)
            pOther->mpEffectStage1->AddRef();
        mpEffectStage1 = pOther->mpEffectStage1;
        if (mpEffectStage1 != nullptr)
            mpEffectStage1->Release();
    }

    if (mpName != pOther->mpName) {
        if (pOther->mpName != nullptr)
            ((cIVisualEffect*)pOther->mpName)->AddRef();
        mpName = pOther->mpName;
        if (mpName != nullptr)
            ((cIVisualEffect*)mpName)->Release();
    }

    mPriority = pOther->mPriority;

    if (mpToolTarget != pOther->mpToolTarget) {
        if (pOther->mpToolTarget != nullptr)
            pOther->mpToolTarget->AddRef();
        mpToolTarget = pOther->mpToolTarget;
        if (mpToolTarget != nullptr)
            mpToolTarget->Release();
    }

    if (mpArea != pOther->mpArea) {
        if (pOther->mpArea != nullptr)
            pOther->mpArea->AddRef();
        mpArea = pOther->mpArea;
        if (mpArea != nullptr)
            mpArea->Release();
    }

    if (mpBeam != pOther->mpBeam) {
        if (pOther->mpBeam != nullptr)
            pOther->mpBeam->AddRef();
        mpBeam = pOther->mpBeam;
        if (mpBeam != nullptr)
            mpBeam->Release();
    }

    if (mpBehavior != pOther->mpBehavior) {
        if (pOther->mpBehavior != nullptr)
            pOther->mpBehavior->AddRef();
        mpBehavior = pOther->mpBehavior;
        if (mpBehavior != nullptr)
            mpBehavior->Release();
    }

    ReloadItemEffects();
    return this;
}

// @ 0x0104ea40
cSPSpaceToolData_s0104_e060* CreateToolDataCopy(cSPSpaceToolData_s0104_e060* pSource)
{
    cSPSpaceToolData_s0104_e060* pTool = (cSPSpaceToolData_s0104_e060*)
        (intptr_t)operator_new(0x2a0, "Simulator/cSpaceToolData", 0, 0, 0, 0);
    if (pTool == nullptr)
        return nullptr;

    pTool = ConstructToolData(pTool);
    if (pTool != nullptr)
        pTool->CopyFrom(pSource);
    return pTool;
}

// @ 0x0104ea80
void DoChargeEffects(cSPSpaceToolData_s0104_e060* pTool)
{
    uint32_t nChargeMs = (uint32_t)(pTool->mChargeTime * 1000.0f);
    if (!pTool->mChargeHoldTimer.IsRunning())
        return;

    cEffectConfig config;
    config.mColor.mX = gToolEffectEulerX;
    config.mColor.mY = gToolEffectEulerY;
    config.mColor.mZ = gToolEffectEulerZ;
    config.mPhase3 = 0;
    config.mPhase4 = 0;
    config.mPhase5 = 0;

    cEffectInfo* pEffectInfo = pTool->mpEffectInfo;
    config.mPhase0 = (uint32_t)(intptr_t)pEffectInfo->GetOrientation();
    config.mPhase1 = (uint32_t)(intptr_t)pEffectInfo->GetPosition();
    config.mPhase2 = (uint32_t)(intptr_t)GetEffectInfoBlock();

    if (GetCurrentGameMode() == &gSpaceGameMode) {
        uint64_t nElapsed = pTool->mChargeHoldTimer.GetElapsedTime();
        float fFraction = (float)nElapsed / (float)(int)nChargeMs;
        cSPUISpace* pSpaceUI = GetSpaceUI();
        pSpaceUI->UpdateToolChargeBar(fFraction);
    }

    uint64_t nElapsed = pTool->mChargeHoldTimer.GetElapsedTime();
    if (nElapsed < (uint64_t)(int)nChargeMs / 3) {
        if (pTool->mpEffectStage0 == nullptr) {
            if (pTool->mpEffectStage0 != nullptr) {
                pTool->mpEffectStage0->Release();
                pTool->mpEffectStage0 = nullptr;
            }
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage0->v14(&config);
                pTool->mpEffectStage0->v18(&nChargeMs);
                pTool->mpEffectStage0->SetEnabled(0);
            }
        }
    } else if (nElapsed < (uint64_t)(int)(nChargeMs * 2) / 3) {
        if (pTool->mpEffectStage1 == nullptr) {
            if (pTool->mpEffectStage1 != nullptr) {
                pTool->mpEffectStage1->Release();
                pTool->mpEffectStage1 = nullptr;
            }
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage1->v14(&config);
                pTool->mpEffectStage1->v18(&nChargeMs);
                pTool->mpEffectStage1->SetEnabled(0);
            }
            if (pTool->mpEffectStage0 != nullptr) {
                pTool->mpEffectStage0->SetEnabled(0);
                pTool->mpEffectStage0->Release();
                pTool->mpEffectStage0 = nullptr;
            }
        }
    } else if (nElapsed < (uint64_t)nChargeMs) {
        if (pTool->mpEffectStage2 == nullptr) {
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage2->v14(&config);
                pTool->mpEffectStage2->v18(&nChargeMs);
                pTool->mpEffectStage2->SetEnabled(0);
            }
            if (pTool->mpEffectStage1 != nullptr) {
                pTool->mpEffectStage1->SetEnabled(0);
                pTool->mpEffectStage1->Release();
                pTool->mpEffectStage1 = nullptr;
            }
        }
    }

    cIVisualEffect** ppEffect = &pTool->mpEffectStage0;
    for (int i = 0; i < 3; ++i) {
        if (*ppEffect != nullptr)
            (*ppEffect)->v18(&config);
        ++ppEffect;
    }
}

// @ 0x0104ef00
void ClearEffectLists(cEffectLists* pLists)
{
    pLists->mpList0[0] = nullptr;
    pLists->mpList0[1] = nullptr;
    pLists->mpList0[2] = nullptr;
    pLists->mpList1[0] = nullptr;
    pLists->mpList1[1] = nullptr;
    pLists->mpList1[2] = nullptr;
    pLists->mpList2[0] = nullptr;
    pLists->mpList2[1] = nullptr;
    pLists->mpList2[2] = nullptr;
    pLists->mpList3[0] = nullptr;
    pLists->mpList3[1] = nullptr;
    pLists->mpList3[2] = nullptr;
}

// @ 0x0104ef30
void EraseEffectTree(cEffectNode* pNode)
{
    while (pNode != nullptr) {
        void* pNext = pNode->mpRight;
        ReleaseEffectHandler(pNode);
        if (pNode->mpEffect != nullptr)
            ((cIVisualEffect*)pNode->mpEffect)->v08();
        if (pNode->mpObject != nullptr)
            ((cIVisualEffect*)pNode->mpObject)->Release();
        operator_delete__(pNode);
        pNode = (cEffectNode*)pNext;
    }
}

// @ 0x0104f1f0
void cSPToolManager::ShutdownGonzagoSubsystem()
{
    EraseToolStrategies(this);
    mpHandlerNode = nullptr;
    if (mpHandlerNode != nullptr) {
        void* pHandler = mpHandlerNode;
        mpHandlerNode = nullptr;
        RemoveMessageHandler(pHandler);
    }
}

// @ 0x0104f250
void cSPToolManager::ClearToolEffects()
{
    cEffectNode* pNode = (cEffectNode*)mpEffectTreeRoot;
    while (pNode != (cEffectNode*)this) {
        if (pNode->mpEffect != nullptr)
            ((cIVisualEffect*)pNode->mpEffect)->SetEnabled(1);
        pNode = (cEffectNode*)pNode->mpRight;
    }

    EraseEffectTree((cEffectNode*)mpEffectTreeRoot);
    mpEffectTreeRoot = (void*)this;
    pNode = (cEffectNode*)mpEffectTreeRoot;
    pNode->mpRight = (void*)pNode;
    mpEffectTreeRoot = nullptr;
}

// @ 0x0104f930
CPropertyList* __fastcall FUN_0104f930(CToolObject* pThis)
{
    return GetToolProperty(pThis->mPropertyID_178);
}

// @ 0x0104fbb0
bool __stdcall FUN_0104fbb0(CToolObject* pTool)
{
    CPropertyList* pList = 0;
    if (pTool->mPropertyID_178)
        pList = GetToolStrategyMap()->Find(pTool->mPropertyID_178);
    if (pList == 0)
        pList = GetToolStrategyMap()->Find(kDefaultPropertyID);
    if (pList)
        pList->vfn00();
    bool bResult = pList->vfn18(pTool);
    pList->vfn04();
    return bResult;
}

// @ 0x0104fe10
void __fastcall FUN_0104fe10(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    pList->vfn20(pThis, 0, 0);
}

// @ 0x0104fe50
bool __fastcall FUN_0104fe50(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    return (pList ? pList->vfn0c(0x060079DEu) : 0) != 0;
}

// @ 0x0104feb0
bool __fastcall FUN_0104feb0(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    return (pList ? pList->vfn0c(0x061D959Au) : 0) != 0;
}

// @ 0x0104fff0
int32_t __fastcall FUN_0104fff0(CToolObject* pThis)
{
    if (!IsFlagSet(pThis->mFlags_174, 5) || pThis->mField_07c > 0)
    {
        if (!FUN_0104ff10(pThis))
            return 1;
    }
    return 0;
}

// @ 0x01050020
void __fastcall FUN_01050020(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    pList->vfn44(pThis->mEnergyCost_1a4);
}

// @ 0x01050640
int* cSPToolManager_s0105_0070::CreateGenericToolEffect(cSPToolManager_s0105_0070* self)
{
  if (!self->m30)
    return 0;
  int local64[5];
  if (!SP_GetPropertyAsKeyInstance((int)self->m30, 0x306c86ef, local64))
    return 0;

  void* src = 0;
  void* effects = SP_EffectsManager();
  if (src) {
    src = 0;
    ((void(__thiscall*)(void*))VT(src, 4))(src);
  }
  if (!((char(__thiscall*)(void*, int, int, void**))VT(effects, 0x2c))
          (effects, local64[0], 0, &src))
    return 0;

  ((void(__thiscall*)(void*, int, void*))VT(src, 0x4c))(src, 1, self->m0c_sub);

  Msg msg;
  msg.ctor();                                       // 0x00434040

  void* m114 = self->m114;
  void* quat = ((void*(__thiscall*)(void*))VT(m114, 0x30))(m114);
  QuaternionToMatrix(&msg.m1c[0], (int)quat);
  msg.m10 = (ushort)(msg.m10 | 2);
  msg.m12 = (short)(msg.m12 + 1);

  int* v3 = (int*)((int*(__thiscall*)(void*))VT(m114, 0x2c))(m114);
  msg.m14 = v3[0];
  msg.m18 = v3[1];
  msg.m04 = (float)v3[2];
  msg.m10 = (ushort)(msg.m10 | 4);
  msg.m12 = (short)(msg.m12 + 1);

  ((void(__thiscall*)(void*, Msg*))VT(src, 0x18))(src, &msg);

  float fVar10 = 1.0f;
  if (m114 &&
      ((int(__thiscall*)(void*, uint))VT(m114, 0xb8))(m114, 0xb033b403) != 0) {
    cSPSimulatorSpaceGame_s0105_0070* sim = (cSPSimulatorSpaceGame_s0105_0070*)GetUFOSimulator();
    int* inv = sim->GetPlayerInventory();
    void* ph = inv ? ((cInventory*)inv)->m34 : 0;
    fVar10 = ((float(__thiscall*)(void*))VT(ph, 0x34))(ph);
  }
  msg.m0e = (ushort)(msg.m0e + 1);
  msg.m04 = fVar10;
  ((void(__thiscall*)(void*, Msg*))VT(src, 0x18))(src, &msg);
  ((void(__thiscall*)(void*, int))VT(src, 8))(src, 0);

  int local1c = 0;
  FUN_0104fcd0(&local1c);
  PtrField_assign(&self->m114);
  if (local1c)
    ((void(__thiscall*)(void*))VT((void*)local1c, 4))((void*)local1c);
  return (int*)local1c;
}

// @ 0x01050850
void cVec14::insert(void* pos, uint count, void* val)
{
  if ((uint)((end - begin) / 0x14) < count) {
    int   oldn = (int)((end - begin) / 0x14);
    uint  cap2 = (uint)oldn * 2;
    if (oldn == 0)
      cap2 = 1;
    uint  newcap = (uint)oldn + count;
    if (newcap < cap2)
      newcap = cap2;
    char* nb;
    if (newcap == 0)
      nb = 0;
    else
      nb = (char*)eOperatorNew(newcap * 0x14, "Simulator", 0, 0,
                               (const char*)0x13ebb38, 0xd1);
    int   s6  = (int)pos - (int)begin;
    char* p1  = (char*)memcpy(nb, begin, (size_t)s6);
    char* p2  = p1 + (s6 / 0x14) * 0x14;
    FUN_0104f140(p2, count, val);
    int   s6b = (int)end - (int)pos;
    char* p3  = (char*)memcpy(p2 + count * 0x14, pos, (size_t)s6b);
    if (begin != 0 && ((ArrayHeader*)begin - 1)->count != 0)
      eOperatorDeleteArray(begin);
    begin = nb;
    end   = p3 + (s6b / 0x14) * 0x14;
    cap   = nb + newcap * 0x14;
  } else if (count != 0) {
    int local14[5];
    FUN_006606a0(val);
    uint  u4 = (uint)((end - (char*)pos) / 0x14);
    char* e  = end;
    char* p7;
    if (count < u4) {
      char* p5 = end - count * 0x14;
      FUN_0104f100(&val, p5, end, end, pos);
      end = end + count * 0x14;
      FUN_0104f1b0(pos, p5, e);
      p7 = (char*)(count * 0x14 + (int)pos);
    } else {
      FUN_0104f140(end, count - u4, local14);
      end = end + (count - u4) * 0x14;
      FUN_0104f100(&pos, pos, e, end, pos);
      end = end + u4 * 0x14;
      p7  = e;
    }
    FUN_0104f900(pos, p7, local14);
    if (local14[0] != 0 && (((ArrayHeader*)(void*)local14[0]) - 1)->count != 0)
      eOperatorDeleteArray((void*)local14[0]);
  }
}

// @ 0x01050a60
float __fastcall FUN_01050a60(cSPToolManager_s0105_0070* self)
{
  float r = 0.0f;
  if (!self->FUN_0104fe50() && !self->FUN_0104feb0()) {
    int a = (int)(self->m1c0 * 1000.0f);
    if (a < 0)
      a = -1;
    float fa = (float)a;
    int b = (int)(self->m1c4 * 1000.0f);
    if (b < 0)
      b = -1;
    float fb = (float)b;
    if (fb > 0.0f) {
      if (self->mTimerA8.IsRunning()) {
        uint64 t = self->mTimerA8.GetElapsedTime();
        r = (float)((double)t / fb);
      }
    }
    if (fa > 0.0f) {
      if (self->mTimer88.IsRunning()) {
        uint64 t = self->mTimer88.GetElapsedTime();
        r = (float)((double)t / fa);
      }
    }
    if (r > 1.0f)
      r = 0.0f;
  }
  return r;
}

// @ 0x01050bb0
uint32_t __thiscall cSPToolManager_s0105_0bb0::PlayerUseToolStart(cSPToolData* pTool, float* pPos, uint32_t p3)
{
    void* pEmpire = FUN_01021300();
    if (pEmpire == 0) return 0;
    cSpaceGame* pInv = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();

    uint32_t toolType = pTool->m178;
    void* pr;
    if (toolType == 0) {
        pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(0xb0da49d9u);
    } else {
        pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(toolType);
        if (pr == 0) pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(0xb0da49d9u);
    }

    uint32_t cost = ((uint32_t(__thiscall*)(void*, uint32_t))VFN(pr, 0x44))(pr, pTool->m1a4);
    uint32_t have = ((tHost*)pEmpire)->FUN_00c30cb0();
    if (have < cost) goto FAIL;
    if (pInv->m7f4 < pTool->m1a8) goto FAIL;

    Vec3_s0105_0bb0 pos;
    pos.x = pPos[0];
    pos.y = pPos[1];
    pos.z = pPos[2];

  {
    uint32_t u9, u12, u14;
    void* pObj;
    if ((pTool->m174 >> 0x10) & 1) {
        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00ffc2d0();
    } else {
        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00c30cb0();
    }

    if (pObj == 0) {
        u14 = 0; u12 = 0; u9 = 0xffffffff;
    } else {
        if (FUN_01021080() == 0) {
            void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
            float* pf = (float*)((void*(__thiscall*)(void*, Vec3_s0105_0bb0*))VFN(v, 0x6c))(v, &pos);
            float x = (pf[0] + pf[3]) * 0.5f;
            float y = (pf[4] + pf[1]) * 0.5f;
            float z = (pf[5] + pf[2]) * 0.5f;
            pos.x = x; pos.y = y; pos.z = z;
        } else {
            void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
            float* pf = (float*)((void*(__thiscall*)(void*))VFN(v, 0x2c))(v);
            pos.x = pf[0]; pos.y = pf[1]; pos.z = pf[2];
        }

        if ((pTool->m174 >> 2) & 1) {
            void* r = ((void*(__thiscall*)(void*, uint32_t))VFN(pObj, 8))(pObj, p3);
            u14 = ((uint32_t(__thiscall*)(void*, uint32_t))VFN(pObj, 0x24))(pObj, 0);
            u12 = 0;
            u9  = (uint32_t)r;
        } else {
            u14 = 0; u12 = 0; u9 = 0xffffffff;
        }
    }

    ((tHost*)this)->FUN_01050070(pTool, pInv->mSub34, &pos, u9, u12, u14, p3);
  }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c) goto L_ed0;
        k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1734.a && k->b == DAT_016e1734.b && k->c == DAT_016e1734.c) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e15c0)) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e138c)) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e1554)) goto L_ed0;
        goto L_ed9;
      L_ed0:
        ((cSpaceGame*)FUN_00ffbe50())->m18 = 1;
      L_ed9:
        ;
    }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1734.a && k->b == DAT_016e1734.b && k->c == DAT_016e1734.c) {
            ((cSpaceGame*)FUN_00ffbe50())->m20 = 1;
        }
    }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (!(k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c)) {
            k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
            if (!(k->a == DAT_016e1554.a && k->b == DAT_016e1554.b && k->c == DAT_016e1554.c)) {
                if (!FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e1734))
                    goto L_f84;
            }
        }
        ((tHost*)FUN_00ffbe50())->FUN_00ffc0a0();
    }

  L_f84:
    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c) {
            ((tHost*)FUN_00ffbe50())->FUN_0083f660();
        }
    }

    if (pTool->m17c == 0xe810d505u) {
        void* pTerrain = ((tHost*)FUN_00b3d300())->FUN_00f67d90();
        ((tHost*)pTerrain)->FUN_00c75640();
    }

    if (pTool->m17c == 0x293e3f3du) {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (!(k->a == DAT_016e138c.a && k->b == DAT_016e138c.b && k->c == DAT_016e138c.c)) {
            void* pPlanet = FUN_01021260();
            if (pPlanet != 0) {
                void* p154 = ((tHost*)pPlanet)->FUN_008414c0();
                if (p154 != 0) ((tHost*)p154)->FUN_00c7e2f0(1);
            }
        }
    }

    return 1;

  FAIL:
    have = ((tHost*)pEmpire)->FUN_00c30cb0();
    cost = ((tHost*)pTool)->FUN_01050020();
    if (have < cost) FUN_010527f0(pTool, 0x1999ea5fu, 1);
    if (pTool->m1a8 > pInv->m7f4) FUN_010527f0(pTool, 0xf04aa52au, 1);
    return 0;
}

// @ 0x01051090
uint8_t __thiscall cSPToolManager_s0105_0bb0::PlayerUseToolUpdate(cSPToolData* pTool, float* pPos, uint32_t p3)
{
    uint8_t result = 0;

    if (pTool == 0) return result;

    if (pTool->m080 == 0 && ((tHost*)((char*)pTool + 0xc8))->FUN_00feba90() == 0)
        return result;

    void* pEmpire = FUN_01021300();
    if (pEmpire == 0) return result;

    if (((tHost*)pTool)->FUN_0104cb70() != 0) {
        uint32_t have = ((tHost*)pEmpire)->FUN_00c30cb0();
        uint32_t cost = ((tHost*)pTool)->FUN_01050020();
        if (cost <= have) {
            cSpaceGame* pInv = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
            if (pTool->m1a8 <= pInv->m7f4) {
                cSpaceGame* pInv2 = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
                if (((tHost*)pInv2)->FUN_00c37170() != 0) {
                    Vec3_s0105_0bb0 pos;
                    pos.x = pPos[0]; pos.y = pPos[1]; pos.z = pPos[2];

                    void* pObj;
                    if ((pTool->m174 & 0x10000) == 0) {
                        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00c30cb0();
                    } else {
                        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00ffc2d0();
                    }

                    if (pObj != 0) {
                        void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
                        float* pf = (float*)((void*(__thiscall*)(void*, Vec3_s0105_0bb0*))VFN(v, 0x6c))(v, &pos);
                        pos.z = (pf[0] + pf[3]) * 0.5f;
                        pos.x = (pf[4] + pf[1]) * 0.5f;
                        pos.y = (pf[5] + pf[2]) * 0.5f;
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }

                    if (pTool->m118 != 0) {
                        void* pEff = pTool->m118;
                        pTool->m118 = 0;
                        ((void(__thiscall*)(void*))VFN(pEff, 0xc0))(pEff);
                    }

                    cSpaceGame* pInv2 = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
                    float* q = (float*)((void*(__thiscall*)(void*))VFN(pInv2->mSub34, 0x2c))(pInv2->mSub34);
                    if (FUN_0102aec0(pTool, q, (float*)&pos) == 0) {
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }

                    if (((tHost*)pTool)->FUN_0104bff0() != 0) {
                        float* pf2 = (float*)((void*(__thiscall*)(void*))VFN(pInv2->mSub34, 0x2c))(pInv2->mSub34);
                        FUN_0104e060(&pos, pf2[0], pf2[1], pf2[2], pTool->m1cc * pTool->m148);
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }
                }
            }
        }
    }

    ((tHost*)this)->FUN_0104fa90(pTool);
    return result;
}

// @ 0x01051850
bool cToolManager::HandleMessage(uint32_t messageID, void* pMessage)
{
    ToolMessage* msg = (ToolMessage*)pMessage;
    switch (messageID)
    {
    case 0x05e667a2:
    {
        Transform* xf = msg->mpTransform;
        uint32_t effectID = msg->mID;
        Vector3 position = xf->GetOffset();
        cToolEffectHolder* holder = ToolEffectHost()->Add(position, 5.0f);
        Transform transform;
        transform.SetOffset(xf->GetOffset());
        transform.SetRotation(xf->mRotation);
        transform.SetScale(xf->mfScale);
        IVisualEffectPtr effect;
        if (EffectsManager2()->CreateVisualEffect(effectID, 0x40828100, effect.AsPPTypeParam())) {
            int handle = PlanetModel_s0105_1850()->mpEffects->AttachEffect(transform, effect.get());
            if (holder)
                holder->mEffectHandle = handle;
        }
        return true;
    }

    case 0x04a32d09:
        if (PlanetModel_s0105_1850() && PlanetModel_s0105_1850()->mpEffects) {
            uint32_t id = msg->mID;
            Transform* xf = msg->mpTransform;
            PlanetModel_s0105_1850()->mpEffects->PlaceAt(*xf, id, 0);
            return true;
        }
        return true;

    case 0x044f1189:
    {
        uint32_t value = msg->mValue;
        if (value == GameModeState()->GetModeID("SPG_CreatureTribeUplift")) {
            cOrnament* ornament = NounManager()->CreateNoun(0x018c88e4);
            if (ornament) {
                ornament->SetModelKey(0x0345bd5d, -1, 0x1a4f418e);
                ornament->mSpatial.SetPosition(field_290);
                ornament->mSpatial.SetOrientation(PlanetModel_s0105_1850()->BuildSurfaceOrientation(field_290));
                cPlanetObjectData data(7, field_290);
                GetActivePlanet()->mpPlanetRecord->mPlanetObjects.push_back_planetobj(data);
            }
            field_290 = kInvalidPosition;
            return true;
        }
        return true;
    }

    case 0x0611691f:
        UFOSimulator()->GetPlayerUFO()->SetToolActive(false);
        return true;

    case 0x06116922:
    {
        cPlanetRecord* record = GetActivePlanetRecord();
        cPlanet* planet = GetActivePlanet();
        int level = TerraformingManager()->GetTerraformLevel(record);
        PlantProfileArray smallPlants(level, 0);
        PlantProfileArray mediumPlants(level, 0);
        PlantProfileArray largePlants(level, 0);
        cSpeciesManager* species = SpeciesManager();
        species->GetMatchingPlantProfiles(smallPlants, level, 0x37148141);
        species->GetMatchingPlantProfiles(mediumPlants, level, 0xb8669ec9);
        species->GetMatchingPlantProfiles(largePlants, level, 0xbcd73e89);

        PlantSwapData swap;
        NounManager()->GetCurrentTerrainSphere()->mObjects[record->GetID()].mList.Clear();

        int numPlants = (int)(record->mPlantSpecies.mpEnd - record->mPlantSpecies.mpBegin);
        int iSmall = 0, iMedium = 0, iLarge = 0;
        {
            for (int i = 0; i < numPlants; i++) {
                cPlantProfile* profile = species->GetPlantProfile(record->mPlantSpecies.mpBegin[i]);
                swap.mOldPlants.push_back(profile->mKey);
                switch (profile->mPlantType) {
                case 0xb8669ec9:
                    swap.mNewPlants.push_back(mediumPlants.mpBegin[iMedium++]->mKey);
                    break;
                case 0xbcd73e89:
                    swap.mNewPlants.push_back(largePlants.mpBegin[iLarge++]->mKey);
                    break;
                case 0x37148141:
                    swap.mNewPlants.push_back(smallPlants.mpBegin[iSmall++]->mKey);
                    break;
                }
                record->mPlantSpecies.mpBegin[i] = swap.mNewPlants.back();
                planet->ReplaceSpecies(swap.mNewPlants.back(), 1, 0);
            }
        }

        int numAnimals = (int)(record->mAnimalSpecies.mpEnd - record->mAnimalSpecies.mpBegin);
        {
            for (int i = 0; i < numAnimals; i++) {
                cPlantProfile* profile = species->GetProfile(record->mAnimalSpecies.mpBegin[i]);
                swap.mOldAnimals.push_back(profile->mKey);
                cPlantProfile* replacement = SpeciesPool()->Pick(GetReplacementSpecies(profile));
                swap.mNewAnimals.push_back(replacement->mKey);
                record->mAnimalSpecies.mpBegin[i] = swap.mNewAnimals.back();
                planet->ReplaceSpecies(swap.mNewAnimals.back(), 1, 0);
            }
        }

        planet->GetPlanetSim()->ApplySwap(swap);
        return true;
    }

    case 0x06117665:
    {
        if (GameModeState()->IsInEditor()) {
            MessageManager()->PostMSG(0x06117665, 0, 0, 0);
            return true;
        }
        AppModeSpace()->SetMode(0);
        AppModeSpace()->TransitionFromPlanetToSolar(GetPlayerHomePlanet()->GetStarView(), 1);
        IVisualEffectPtr effect;
        if (EffectsManager()->CreateVisualEffect(0x719a262a, 0, effect.AsPPTypeParam())) {
            cUFO* ufo = UFOSimulator()->GetPlayerUFO();
            ufo->PopToDestination();
            EffectTransform transform;
            transform.SetOffset(ufo->mSpatial.GetPosition());
            transform.SetRotation(Matrix3FromQuaternion(ufo->mSpatial.GetOrientation()));
            effect->SetTransform(transform);
            effect->Start(0);
        }
        return true;
    }

    case 0x0612d770:
    {
        cPlanetRecord* record = GetActivePlanetRecord();
        cSpaceInventory* inventory = SpaceGame()->GetPlayerInventory();
        int capacity = inventory->GetCapacity();
        cTerraformingManager* terraform = TerraformingManager();
        int level = terraform->GetTerraformLevel(record);
        for (int i = 1; i <= level; i++) {
            ResourceKeyZ key;
            key = terraform->GetPlantKey(i, 0x3a8be428, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetPlantKey(i, 0x029c388a, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetPlantKey(i, 0x6d60a1cc, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetAnimalKey(i, 0, record);
            AddAnimalItem(inventory, key, capacity, 2);
            key = terraform->GetAnimalKey(i, 1, record);
            AddAnimalItem(inventory, key, capacity, 2);
            key = terraform->GetCreatureKey(i, record);
            AddAnimalItem(inventory, key, capacity, 2);
        }
        return true;
    }

    case 0x06255124:
    {
        Transform* xf = msg->mpTransform;
        cUFO* ufo = UFOSimulator()->GetPlayerUFO();
        uint32_t star = ufo->mDestinationStar;
        Vector3 destination = xf->GetOffset();
        ufo->SetDestination(destination);
        ufo->PopToDestination();
        ufo->SetDestinationStar(star);
        ufo->SetToolActive(true);
        UFOSimulator()->mb18 = false;
        UFOSimulator()->PopState();
        UFOSimulator()->mb20 = false;
        return true;
    }

    case 0x0643d5cb:
    {
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x5dce504a, &evt, 0);
        TriggerAdventureEvent("SPG_ZooCreated", 0x05482570, 0);
        return true;
    }

    case 0x0643d5cc:
    {
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x14a7d231, &evt, 0);
        field_290 = position;
        GameModeState()->Announce("SPG_CreatureTribeUplift", 1, 0, 0, 0, 0);
        cPlanet* planet = GetActivePlanet();
        cPlanetRecord* record = planet->mpPlanetRecord;
        SpaceGame()->OnPlanetUplifted(planet);
        if (planet->GetTechLevel() == 2)
            AchievementsController()->AutoTest(0x313be103, 1);
        if (planet->GetTechLevel() == 1) {
            cCreatureAnimal* closest = 0;
            float closestDist = 3.402823466e+38F;
            const CreatureVector& creatures = NounManager()->GetCreatures();
            for (cCreatureAnimal** it = creatures.mpBegin; it != creatures.mpEnd; ++it) {
                cCreatureAnimal* creature = *it;
                if (creature && creature->mbAlive && !creature->mbIsPlayer && !creature->IsInTribe()) {
                    const Vector3& pos = creature->mSpatial.GetPosition();
                    float dy = field_290.y - pos.y;
                    float dx = field_290.x - pos.x;
                    float dz = field_290.z - pos.z;
                    float dist = dz * dz + dy * dy + dx * dx;
                    if (closestDist > dist) {
                        closest = creature;
                        closestDist = dist;
                    }
                }
            }
            record->GetStarView()->SetSpeciesKey(
                closest ? closest->GetSpeciesKey() : record->mAnimalSpecies.mpBegin[0]);
        }
        return true;
    }

    case 0x0653a95b:
    {
        cMission* mission = MissionManager()->GetMissionByID(0x398aca5e);
        if (!mission)
            return true;
        if (mission->GetTargetPlanet() != GetActivePlanet())
            return true;
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x5dce504a, &evt, 0);
        TriggerAdventureEvent("SPG_ColonizeMissionComplete", 0x09f3a466, 1);
        return true;
    }

    case 0x06565534:
        if (field_2C != kInvalidPosition) {
            PositionTracker()->Update(field_20, field_2C);
            field_2C = kInvalidPosition;
        }
        return true;

    case 0x066605a6:
    {
        cAvatar* avatar = SpaceGame()->GetAvatar();
        if (avatar) {
            avatar->Release();
            UFOSimulator()->mb18 = false;
            UFOSimulator()->PopState();
            UFOSimulator()->ClearPending();
        }
        return true;
    }

    case 0x0668af00:
    {
        cAvatar* avatar = SpaceGame()->GetAvatar();
        if (avatar)
            avatar->Abduct();
        return true;
    }
    }
    return false;
}

// @ 0x013ac650
void FUN_013ac650()
{
    g_015b8850 = PropDesc("mCurrentAmmoCount", 0x0385030du, 124, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00572840, (fp)0x00692ff0, (fp)0x00694ee0, (fp)0x00b1fbf0, (fp)0x0057cde0);
    g_015b888c = PropDesc("mRechargeTimer", 0x0385031du, 136, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b88c8 = PropDesc("mAutoFireTimer", 0x03850360u, 168, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b8904 = PropDesc("mChargeTimer", 0x03850362u, 200, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b8940 = PropDesc("mMissCheckTimer", 0x03850364u, 232, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b897c = PropDesc("mpToolOwner", 0x03850690u, 276, (fp)0x00692ca0,
        (fp)0x00bdc650, (fp)0x00bdd350, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b89b8 = PropDesc("mpToolTarget", 0x038506b6u, 280, (fp)0x00692ca0,
        (fp)0x00bdc650, (fp)0x00bdd350, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b89f4 = PropDesc("mTargetDamagePointId", 0x063fc849u, 284, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00572840, (fp)0x00692ff0, (fp)0x00694ee0, (fp)0x00b1fbf0, (fp)0x0057cde0);
    g_015b8a30 = PropDesc("mpArea", 0x03850926u, 288, (fp)0x00692ca0,
        (fp)0x0104e750, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b8a6c = PropDesc("mpBeam", 0x03850927u, 292, (fp)0x00692ca0,
        (fp)0x0104e780, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b8aa8 = PropDesc("mpAppTarget", 0x03850929u, 300, (fp)0x00692ca0,
        (fp)0x00bca770, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00bca7e0, (fp)0x00ac8050);
    g_015b8ae4 = PropDesc("mInterruptedByDamage", 0x03850952u, 316, (fp)0x00692ca0,
        (fp)0x00ac8750, (fp)0x00ac8780, (fp)0x00693090, (fp)0x00694fa0, (fp)0x00b1fbf0, (fp)0x0057ce00);
    g_015b8b20 = PropDesc("mDamageMultiplier", 0x038509c7u, 324, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8b5c = PropDesc("mRangeMultiplier", 0x038509d5u, 328, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8b98 = PropDesc("mProjectileScale", 0x039fb1a8u, 332, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8bd4 = PropDesc("mIsInUse", 0x057f830fu, 128, (fp)0x00692ca0,
        (fp)0x00ac8750, (fp)0x00ac8780, (fp)0x00693090, (fp)0x00694fa0, (fp)0x00b1fbf0, (fp)0x0057ce00);
}
