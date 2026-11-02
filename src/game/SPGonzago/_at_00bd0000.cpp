// src/game/SPGonzago/_at_00bd0000.cpp -- migrated from slice(s) s00bd5ea0, s00bd1820 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00bd0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cBuilding.h"
#include "SP/cBuildingCityHall.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cSpatialObject.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cCelestialBody.h"
#include "SP/cEllipticalOrbit.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cInteractionTarget.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPVector3.h"
#include "SP/cVarListSerializer.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern float gVec3Zero[3];         // 0x0168b66c .. 0x0168b674
extern float gRealOne;             // 0x01485720 (_HK_REAL_ONE)
extern float gScenarioRotation[9]; // 0x0168bc38
extern char cBuildingCityHall_vtable0[];         // 0x014672f0
extern char cBuildingCityHall_vtable1[];         // 0x014672dc
extern char cBuildingCityHall_vtable2[];         // 0x01467218
extern char cBuildingCityHall_vtable3[];         // 0x014671f8
extern char cBuildingCityHall_vtable4[];         // 0x01467190
extern char cBuildingCityHall_vtable5[];         // 0x01467168
extern char cBuildingIndustry_vtable0[];         // 0x01467528
extern char cBuildingIndustry_vtable1[];         // 0x01467514
extern char cBuildingIndustry_vtable2[];         // 0x01467450
extern char cBuildingIndustry_vtable3[];         // 0x01467430
extern char cBuildingIndustry_vtable4[];         // 0x014673c8
extern char cBuildingIndustry_vtable5[];         // 0x014673a4
extern char cBuildingHouse_vtable0[];            // 0x01467768
extern char cBuildingHouse_vtable1[];            // 0x01467754
extern char cBuildingHouse_vtable2[];            // 0x01467690
extern char cBuildingHouse_vtable3[];            // 0x01467670
extern char cBuildingHouse_vtable4[];            // 0x01467608
extern char cBuildingHouse_vtable5[];            // 0x014675e0
extern char cBuildingEntertainment_vtable0[];    // 0x014679a0
extern char cBuildingEntertainment_vtable1[];    // 0x0146798c
extern char cBuildingEntertainment_vtable2[];    // 0x014678c8
extern char cBuildingEntertainment_vtable3[];    // 0x014678a8
extern char cBuildingEntertainment_vtable4[];    // 0x01467840
extern char cBuildingEntertainment_vtable5[];    // 0x0146781c
extern char cBuildingScenario_vtable0[];         // 0x01467c30
extern char cBuildingScenario_vtable1[];         // 0x01467c1c
extern char cBuildingScenario_vtable2[];         // 0x01467b58
extern char cBuildingScenario_vtable3[];         // 0x01467b38
extern char cBuildingScenario_vtable4[];         // 0x01467ad0
extern char cBuildingScenario_vtable5[];         // 0x01467aac
extern "C" void __fastcall ctor_cGonzagoTimer(void* p);      // 0x00b63890
extern "C" void __fastcall dtor_cBuilding(void* p);          // 0x00bd0dd0
extern "C" void _ReadWriteBarrier(void);
extern "C" double  _CIacos(double fValue);
extern "C" char    Fn_0059ab10(float fValue);                             // 0x0059ab10
extern "C" char    Fn_00bfc600(void* pThis, void* pEdx);                  // 0x00bfc600
extern "C" int     GetDamageState(void* pThis, void* pEdx);               // 0x008e7f80
extern float gAimTurnStep;   // 0x0156d708
extern float gAimTurnMax;    // 0x0156d70c
extern float gEffectSize;    // 0x0147b9f0
extern char  gAppTag[];      // 0x01654c05
extern char cTurretVtableVtbl8[];   // 0x013ec458 (interim vptr at +0x08)
extern char cTurretVtable000[];     // 0x01466c50
extern char cTurretVtable008[];     // 0x01475114 (final vptr at +0x08)
extern "C" void __fastcall SetGameDataOwner2(void* pThis, void* pEdx, void* pArg); // 0x00b18550
extern "C" int  __fastcall GetWeaponryLevel(void* pThis, void* pEdx);               // 0x00c317a0
extern "C" void __fastcall SetEffectId(void* pThis, void* pEdx, int nId);           // 0x00c3f160
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s00bd1820 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
struct AABB { float minx, miny, minz, maxx, maxy, maxz; };
extern float gVec3Zero[3];         // 0x0168b66c .. 0x0168b674
extern float gRealOne;             // 0x01485720 (_HK_REAL_ONE)
extern float gScenarioRotation[9]; // 0x0168bc38
extern char cBuildingCityHall_vtable0[];         // 0x014672f0
extern char cBuildingCityHall_vtable1[];         // 0x014672dc
extern char cBuildingCityHall_vtable2[];         // 0x01467218
extern char cBuildingCityHall_vtable3[];         // 0x014671f8
extern char cBuildingCityHall_vtable4[];         // 0x01467190
extern char cBuildingCityHall_vtable5[];         // 0x01467168
extern char cBuildingIndustry_vtable0[];         // 0x01467528
extern char cBuildingIndustry_vtable1[];         // 0x01467514
extern char cBuildingIndustry_vtable2[];         // 0x01467450
extern char cBuildingIndustry_vtable3[];         // 0x01467430
extern char cBuildingIndustry_vtable4[];         // 0x014673c8
extern char cBuildingIndustry_vtable5[];         // 0x014673a4
extern char cBuildingHouse_vtable0[];            // 0x01467768
extern char cBuildingHouse_vtable1[];            // 0x01467754
extern char cBuildingHouse_vtable2[];            // 0x01467690
extern char cBuildingHouse_vtable3[];            // 0x01467670
extern char cBuildingHouse_vtable4[];            // 0x01467608
extern char cBuildingHouse_vtable5[];            // 0x014675e0
extern char cBuildingEntertainment_vtable0[];    // 0x014679a0
extern char cBuildingEntertainment_vtable1[];    // 0x0146798c
extern char cBuildingEntertainment_vtable2[];    // 0x014678c8
extern char cBuildingEntertainment_vtable3[];    // 0x014678a8
extern char cBuildingEntertainment_vtable4[];    // 0x01467840
extern char cBuildingEntertainment_vtable5[];    // 0x0146781c
extern char cBuildingScenario_vtable0[];         // 0x01467c30
extern char cBuildingScenario_vtable1[];         // 0x01467c1c
extern char cBuildingScenario_vtable2[];         // 0x01467b58
extern char cBuildingScenario_vtable3[];         // 0x01467b38
extern char cBuildingScenario_vtable4[];         // 0x01467ad0
extern char cBuildingScenario_vtable5[];         // 0x01467aac
extern "C" void __fastcall ctor_cGonzagoTimer(void* p);      // 0x00b63890
extern "C" void __fastcall dtor_cBuilding(void* p);          // 0x00bd0dd0
void  DestroyRange(void* pFirst, void* pLast);               // 0x00bd17e0
void  FreeObj(void* p);                                      // 0x00f47380 operator delete
void  __fastcall Fn_00bd0000(void* pThis, void* pEdx);                 // 0x00bd0000
void  Fn_00c3f2d0(void* pThis);                                        // 0x00c3f2d0
void  __fastcall Fn_00c421b0(void* pThis, void* pEdx, void* pArg);     // 0x00c421b0
void* __fastcall Fn_00bebe10(void* pThis, void* pEdx);                 // 0x00bebe10
void  __fastcall Fn_00bd15a0(void* pThis, void* pEdx, int n);          // 0x00bd15a0
void* StarManager();                                                   // 0x00b3d2a0
void* GetCurrentGameMode();                                            // 0x00b5b800
void* BehaviorManager();                                               // 0x00b3d260
void* NounManager();                                                   // 0x00b3d300
extern "C" void _ReadWriteBarrier(void);
struct cGonzagoTimer {
    u32 mData[8];
};
struct cWString {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    void*    mpPool;     // +0x0c
    cWString& assign(const wchar_t* pFirst, const wchar_t* pLast);  // 0x00423650
};
struct cStr8 {
    char* mpBegin;       // +0x00
    char* mpEnd;         // +0x04
    char* mpCapacity;    // +0x08
    void* mpPool;        // +0x0c
    cStr8* append_sprintf(const char* pFmt, ...);   // 0x005f9450
};
struct cSPMatrix3_s00bd_1820 {
    float m[9];
    void Assign(const float* pSrc);     // 0x0041cb40
};
struct cCoordArray {
    u32  mInline[6];     // +0x00 .. +0x17
    u32* mpCurrent;      // +0x18
    u32* mpUnused1c;     // +0x1c
    u32* mpCapacity;     // +0x20
    u32* mpUnused24;     // +0x24
    u32* mpUnused28;     // +0x28
    void Init(u32 nCapacity);   // 0x004ab350
    void Grow(u32* pValue);     // 0x00502dd0
};
struct cCoordVec {
    u32* mpBegin;        // +0x00
    u32* mpEnd;          // +0x04
    u32* mpCap;          // +0x08
    void DestroyRange(u32* pFirst, u32* pLast);   // 0x00bd17e0 (thiscall)
};
struct cSpatialObjectABI {
    void* mpVtbl;                                             // +0x00
    void SetLocalExtents(const AABB& bounds, float fScale);   // 0x00c89160
};
struct cInteractionABI { void* mpVtbl; };
struct cCombatABI      { void* mpVtbl; };
struct cPlaceABI       { void* mpVtbl; };
struct cBuilding {
    void* mpVtbl0;           // +0x000  cBuilding vtable
    void* mpVtbl1;           // +0x004  cBuilding vtable (DefaultRefCounted half)
    char  mData08[0x34 - 0x08];      // +0x008 .. +0x033 (cGameData tail)
    union { void* mpVtblSpatial; cSpatialObjectABI mSpatial; };  // +0x034
    char  mData38[0x88 - 0x38];      // +0x038 .. +0x087
    u32   mField88;          // +0x088
    char  mData8c[0xa4 - 0x8c];      // +0x08c .. +0x0a3
    u8    mbFlagA4;          // +0x0a4
    u8    mbFlagA5;          // +0x0a5
    char  mDataA6[0xda - 0xa6];      // +0x0a6 .. +0x0d9
    u8    mbFlagDa;          // +0x0da
    char  mDataDb[0x108 - 0xdb];     // +0x0db .. +0x107
    union { void* mpVtblInteraction; cInteractionABI mInteraction; };  // +0x108
    char  mData10c[0x120 - 0x10c];   // +0x10c .. +0x11f
    union { void* mpVtblCombatant; cCombatABI mCombatant; };       // +0x120
    char  mData124[0x14c - 0x124];   // +0x124 .. +0x14b
    float mField14c;         // +0x14c
    char  mData150[0x158 - 0x150];   // +0x150 .. +0x157
    float mField158;         // +0x158
    char  mData15c[0x1e8 - 0x15c];   // +0x15c .. +0x1e7
    union { void* mpVtblPlaceable; cPlaceABI mPlace; };             // +0x1e8
    u32   mF1ec;             // +0x1ec
    u32   mF1f0;             // +0x1f0
    u8    mF1f4;             // +0x1f4
    char  mF1f5[3];          // +0x1f5 .. +0x1f7
    cCoordArray mCoords;     // +0x1f8
    u32   mF224;             // +0x224
    u32   mF228;             // +0x228
    u32   mF22c;             // +0x22c
    u8    mF230;             // +0x230
    char  mF231[0x238 - 0x231];      // +0x231 .. +0x237
    cGonzagoTimer mTimer1;   // +0x238
    cGonzagoTimer mTimer2;   // +0x258
    cWString mName;          // +0x278
    u8    mF288;             // +0x288
    u8    mF289;             // +0x289
    char  mF28a[2];          // +0x28a .. +0x28b
    u32   mF28c;             // +0x28c
    u32   mF290;             // +0x290
    u32   mF294;             // +0x294
    u32   mF298;             // +0x298
    u32   mF29c;             // +0x29c
    u32   mF2a0;             // +0x2a0
    u32   mF2a4;             // +0x2a4
    u32   mF2a8;             // +0x2a8
    char  mF2ac[8];          // +0x2ac .. +0x2b3 (untouched subobject)
    u32   mF2b4;             // +0x2b4
    u32   mF2b8;             // +0x2b8
    u32   mF2bc;             // +0x2bc
    char  mF2c0[8];          // +0x2c0 .. +0x2c7 (untouched subobject)
    u32   mF2c8;             // +0x2c8
    u32   mF2cc;             // +0x2cc
    u32   mF2d0;             // +0x2d0
    char  mF2d4[8];          // +0x2d4 .. +0x2db (untouched subobject)
    u32   mF2dc;             // +0x2dc
    u32   mF2e0;             // +0x2e0
    u32   mF2e4;             // +0x2e4
    char  mF2e8[8];          // +0x2e8 .. +0x2ef (untouched subobject)
    u8    mF2f0;             // +0x2f0
    char  mF2f1[3];          // +0x2f1 .. +0x2f3
    u32   mF2f4;             // +0x2f4
    u32   mF2f8;             // +0x2f8
    u32   mF2fc;             // +0x2fc
    char  mF300[8];          // +0x300 .. +0x307 (untouched subobject)
    u32   mF308;             // +0x308
    u32   mF30c;             // +0x30c
    u32   mF310;             // +0x310
    char  mF314[0x320 - 0x314];      // +0x314 .. +0x31f
    cGonzagoTimer mTimer3;   // +0x320
    u8    mF340;             // +0x340 (CityHall: mbMoneyAddedThisTick)
    u8    mF341;             // +0x341 (CityHall: field_341)
    char  mF342[2];          // +0x342 .. +0x343
    cCoordVec mTailVec;      // +0x344 (Scenario coord vector / CityHall hit-sphere ptr)
    char  mF350[0x358 - 0x350];      // +0x350 .. +0x357
    cGonzagoTimer mTimerHit; // +0x358 (CityHall)
    char  mF378[0x388 - 0x378];      // +0x378 .. +0x387
    u16   mF388;             // +0x388 (Scenario: mnFlags)
    u16   mF38a;             // +0x38a (Scenario: mnTransformCount)
    float mF38c;             // +0x38c (Scenario: mOffset.x)
    float mF390;             // +0x390 (Scenario: mOffset.y)
    float mF394;             // +0x394 (Scenario: mOffset.z)
    float mF398;             // +0x398 (Scenario: mfScale)
    cSPMatrix3_s00bd_1820 mMatrix;      // +0x39c (Scenario: mRotation)

    cBuilding();                        // 0x00bd1820
    void PushCoord(u32 value);          // 0x00bd1ab0
};
struct cBuildingCityHall : cBuilding {
    cBuildingCityHall();
};
struct cBuildingIndustry : cBuilding {
    cBuildingIndustry();
    void* Delete(u8 flags);             // 0x00bd1bb0 (scalar deleting destructor)
};
struct cBuildingHouse : cBuilding {
    cBuildingHouse();
};
struct cBuildingEntertainment : cBuilding {
    cBuildingEntertainment();
    void* Delete(u8 flags);             // 0x00bd1c80 (scalar deleting destructor)
};
struct cBuildingScenario : cBuilding {
    cBuildingScenario();
};
struct cVec3f  { float x, y, z; };
struct cQuat4f { float x, y, z, w; };
struct cMat33f { float m[9]; };
extern "C" cVec3f* normalized_safe(cVec3f* pOut, const cVec3f* pIn);      // 0x00449c20
extern "C" void    Fn_00576b00(cMat33f* pOut, const cVec3f* pAxis, float fAngle); // 0x00576b00
extern "C" double  _CIacos(double fValue);
extern "C" char    Fn_0059ab10(float fValue);                             // 0x0059ab10
extern "C" void    Fn_005b26f0(cQuat4f* pOut, const cQuat4f* pA,
                               const cQuat4f* pB, float fT);              // 0x005b26f0
extern "C" cQuat4f* QuaternionFromFacingAndUp(cQuat4f* pOut,
                                               const cVec3f* pFacing,
                                               const cVec3f* pUp);        // 0x0069b600
extern "C" char    Fn_00bfc600(void* pThis, void* pEdx);                  // 0x00bfc600
extern "C" int     GetDamageState(void* pThis, void* pEdx);               // 0x008e7f80
extern float gAimTurnStep;   // 0x0156d708
extern float gAimTurnMax;    // 0x0156d70c
extern u32   gBehaviorId;    // 0x0169ebbc
extern float gEffectSize;    // 0x0147b9f0
extern char  gAppTag[];      // 0x01654c05
struct cPosObject;
struct cRefObject;
struct cPosVtbl {
    char    mSlots00[0x2c];
    cVec3f* (__fastcall* GetPosition)(void* pSelf, void* pEdx);           // +0x2c
};
struct cPosObject { cPosVtbl* mpVtbl; };                                  // +0x00
struct cRefVtbl {
    char        mSlots00[0x08];
    cPosObject* (__fastcall* GetRef)(void* pSelf, void* pEdx);            // +0x08
};
struct cRefObject { cRefVtbl* mpVtbl; };                                  // +0x00
struct cWeaponVtbl {
    char    mSlots00[0x58];
    cVec3f* (__fastcall* GetMuzzle)(void* pSelf, void* pEdx, cVec3f* pOut); // +0x58
};
struct cWeaponObject { cWeaponVtbl* mpVtbl; };                            // +0x00
struct cTargetVtbl {
    char  mSlots00[0xb8];
    void* (__fastcall* GetByTag)(void* pSelf, void* pEdx, u32 nTag);      // +0xb8
};
struct cCombatantObjVtbl {
    char         mSlots00[0x54];
    cRefObject*  (__fastcall* GetRefObject)(void* pSelf, void* pEdx);     // +0x54
};
struct cCombatantSub { cCombatantObjVtbl* mpVtbl; };                      // +0x00
struct cAimSpatialVtbl {
    char      mSlots00[0x2c];
    cVec3f*   (__fastcall* GetPosition)(void* pSelf, void* pEdx);         // +0x2c
    cQuat4f*  (__fastcall* GetOrientation)(void* pSelf, void* pEdx);      // +0x30
    char      mSlots34[0x3c - 0x34];
    void      (__fastcall* SetOrientation)(void* pSelf, void* pEdx, cQuat4f* pQ); // +0x3c
    char      mSlots40[0x5c - 0x40];
    void      (__fastcall* GetForward)(void* pSelf, void* pEdx, cVec3f* pOut);    // +0x5c
};
struct cAimSpatialSub { cAimSpatialVtbl* mpVtbl; };                       // +0x00
struct cAimWorld {
    cTargetVtbl*    mpVtbl;          // +0x000
    char            mData04[0x34 - 0x04];
    cAimSpatialSub  mSpatial;        // +0x034
    char            mData38[0x588 - 0x38];
    cCombatantSub   mCombatant;      // +0x588
    char            mData58c[0x684 - 0x58c];
    int             mF684;           // +0x684
    cWeaponObject*  mpWeapon;        // +0x688
    char            mData68c[0x6a4 - 0x68c];
    cRefObject*     mpF6a4;          // +0x6a4
};
struct cAimUpdateArgs {
    cVec3f       mPos;        // +0x00 (output)
    char         mData0c[0x10 - 0x0c];
    float        mScale;      // +0x10
    cAimWorld*   mpTarget;    // +0x14
};
struct cAimController {
    char   mData00[0x10];
    int    mMode;       // +0x10
    int    mCounter;    // +0x14
    cVec3f mFacing;     // +0x18
    void Update(cAimUpdateArgs* pArgs);   // 0x00bd1cd0
};
struct cCitizenData;
struct cListNode;
struct cNoun;
struct cCitizenDataVtbl {
    void (__fastcall* AddRef)(void* pSelf, void* pEdx);                   // +0x00
    void (__fastcall* Release)(void* pSelf, void* pEdx);                  // +0x04
    char mSlots08[0x4c - 0x08];
    u32  (__fastcall* GetEmpireId)(void* pSelf, void* pEdx);              // +0x4c
    char mSlots50[0x6c - 0x50];
    cCitizenData* (__fastcall* GetOwner)(void* pSelf, void* pEdx);        // +0x6c
};
struct cCitizenData {
    cCitizenDataVtbl* mpVtbl;      // +0x000
    char              mData04[0x1f4 - 0x04];
    u8                mF1f4;       // +0x1f4
};
struct cListNodeVtbl {
    char mSlots00[0x04];
    void (__fastcall* Release)(void* pSelf, void* pEdx);                  // +0x04
    void (__fastcall* Fn08)(void* pSelf, void* pEdx);                     // +0x08
};
struct cListNode { cListNodeVtbl* mpVtbl; };                              // +0x00
struct cCitizenSpatialVtbl {
    char mSlots00[0x2c];
    int  (__fastcall* Fn2c)(void* pSelf, void* pEdx, float fArg);         // +0x2c
    char mSlots30[0x94 - 0x30];
    void (__fastcall* Fn94)(void* pSelf, void* pEdx, void* pArg);         // +0x94
};
struct cBehaviorListVtbl {
    char mSlots00[0x0c];
    void (__fastcall* Fn0c)(void* pSelf, void* pEdx, u32 a, void* b, int c); // +0x0c
};
struct cBehaviorList { cBehaviorListVtbl* mpVtbl; };                       // +0x00
struct cBehaviorMgrVtbl {
    char mSlots00[0x38];
    void (__fastcall* Fn38)(void* pSelf, void* pEdx, void* pArg);         // +0x38
};
struct cBehaviorMgr { cBehaviorMgrVtbl* mpVtbl; };                         // +0x00
struct cNounVtbl {
    char mSlots00[0x0c];
    cCitizenData* (__fastcall* CreateRef)(void* pSelf, void* pEdx, u32 nId); // +0x0c
};
struct cNoun { cNounVtbl* mpVtbl; };                                       // +0x00
extern char cTurretVtableVtbl8[];   // 0x013ec458 (interim vptr at +0x08)
extern char cTurretVtable000[];     // 0x01466c50
extern char cTurretVtable008[];     // 0x01475114 (final vptr at +0x08)
extern "C" void __fastcall SetGameDataOwner2(void* pThis, void* pEdx, void* pArg); // 0x00b18550
extern "C" void* __fastcall GetEmpireByID(void* pThis, void* pEdx, u32 nId);        // 0x00ba9370
extern "C" int  __fastcall GetWeaponryLevel(void* pThis, void* pEdx);               // 0x00c317a0
extern "C" void* __fastcall CreateNoun(void* pThis, void* pEdx, u32 nId);           // 0x00b20c60
extern "C" void __fastcall SetEffectId(void* pThis, void* pEdx, int nId);           // 0x00c3f160
extern "C" void* NewObj(u32 nSize, const char* pName, int a, int b, int c, int d);  // 0x00f473a0
struct cTurretRotator {
    void*  mpVtbl0;    // +0x00
    void*  mpVtbl1;    // +0x04
    void*  mpVtbl2;    // +0x08
    void*  mpVtbl3;    // +0x0c
    u32    mF10;       // +0x10
    u32    mF14;       // +0x14
    cVec3f mF18;       // +0x18
};
struct cSPCreatureCitizen {
    char                  mData00[0x34];
    cCitizenSpatialVtbl*  mpVtblSpatial;   // +0x034
    char                  mData38[0xa5 - 0x38];
    u8                    mbFlagA5;        // +0x0a5
    char                  mDataA6[0xda - 0xa6];
    u8                    mbFlagDa;        // +0x0da
    char                  mDataDb[0x224 - 0xdb];
    u32                   mF224;           // +0x224
    char                  mData228[0x51c - 0x228];
    cBehaviorList         mBehaviorList;   // +0x51c
    char                  mData520[0x654 - 0x520];
    cVec3f                mF654;           // +0x654
    char                  mData660[0x688 - 0x660];
    cCitizenData*         mpF688;          // +0x688
    cListNode*            mpF68c;          // +0x68c
    cListNode*            mpF690;          // +0x690
    char                  mData694[0x6a0 - 0x694];
    cCitizenData*         mpF6a0;          // +0x6a0
    void Init(cCitizenData* pArg);         // 0x00bd2310
};
struct cPair { int x, y; };
struct cPairVec {
    cPair* mpBegin;    // +0x00
    cPair* mpEnd;      // +0x04
    cPair* mpCap;      // +0x08
};
struct cCityFlattenVtbl {
    char mSlots00[0x84];
    void* (__fastcall* FillPairs)(void* pSelf, void* pEdx, cPairVec* pVec); // +0x84
};
struct cCityFlatten {
    cCityFlattenVtbl* mpVtbl;   // +0x00
    void Flatten5a4(cPairVec* pVec);   // 0x00bdf750
};
struct cFlattenOuter {
    cCityFlatten* mpFlatten;    // +0x00
};
// ---- items of slice s00bd1820 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" cVec3f* normalized_safe(cVec3f* pOut, const cVec3f* pIn);      // 0x00449c20
extern "C" void    Fn_00576b00(cMat33f* pOut, const cVec3f* pAxis, float fAngle); // 0x00576b00
extern "C" void    Fn_005b26f0(cQuat4f* pOut, const cQuat4f* pA,
                               const cQuat4f* pB, float fT);              // 0x005b26f0
extern "C" cQuat4f* QuaternionFromFacingAndUp(cQuat4f* pOut,
                                               const cVec3f* pFacing,
                                               const cVec3f* pUp);        // 0x0069b600
extern u32   gBehaviorId;    // 0x0169ebbc
extern "C" void* __fastcall GetEmpireByID(void* pThis, void* pEdx, u32 nId);        // 0x00ba9370
extern "C" void* __fastcall CreateNoun(void* pThis, void* pEdx, u32 nId);           // 0x00b20c60
extern "C" void* NewObj(u32 nSize, const char* pName, int a, int b, int c, int d);  // 0x00f473a0

// ---- items of slice s00bd5ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gPos_168bc90[3];      // 0x0168bc90 (0,0,0)
extern wchar_t gEmptyString16[];   // 0x01667bac
extern char  gVarTable_A[];        // 0x0156e0c8
extern char  gVarTable_B[];        // 0x0156df10
extern char  gVarTable_C[];        // 0x0157a1f8
extern float gOrbitAngle_156def8;   // 0x0156def8
extern float gOrbitUp_156defc[3];       // 0x0156defc
extern float gOrbitBasis_168bcc4[9];    // 0x0168bcc4
extern float gOrbitEye_168bce8[3];      // 0x0168bce8
#pragma warning(disable: 4100)
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef void* (__thiscall* Fn_p_v)(void*);
struct IV {  // pure vtable stub (48 slots covers every call site here)
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
};
#define VT(p, off)     (*(void**)((char*)(*(void**)(p)) + (off)))
void* __cdecl SP_MessageServer();                            // 0x0067dcc0
void* __cdecl SP_GameInputManager();                         // 0x00b3d250
void  __cdecl operator_delete__(void* p);                    // 0x00f47380
struct cVarListSerializer_s00bd_5ea0 {
  uint32_t mData[645];                                   // size 0xa14
  void ctor(void* owner, const void* table, uint id);    // 0x00692f90
  int  Write(void* s);                                   // 0x00692900
  int  Read(void* s);                                    // 0x00693e10
  int  GetFields(void* out);                             // 0x00695960
};
void  __fastcall FUN_00ac0520(void* p);                      // 0x00ac0520
void  __fastcall FUN_00c8a420(void* p);                      // 0x00c8a420
void  __fastcall FUN_00b184c0(void* p);                      // 0x00b184c0
void* __cdecl FUN_00fe8780(void* out, void* a, void* b, void* c, float f); // 0x00fe8780
void* __cdecl SP_normalized_safe(void* out, void* v);        // 0x00449c20
void  __cdecl MatrixFromTwoVectors(void* out, const void* up, const void* fwd);  // 0x0069b1c0
struct cXform { void RotateZ(float a); };                    // 0x007d1ac0 (__thiscall)
struct cRandomLinearCongruential {                            // RNG singleton @0x01601760
  double __thiscall RandomDoubleUniform();                   // 0x009360d0
};
void  __cdecl FUN_00f924e0_hack(float v);                    // 0x00f924e0
void  __cdecl FUN_00c0b9d0_hack(float v);                    // 0x00c0b9d0
struct IOStream {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
};
bool __cdecl EA_IO_WriteUint32(IOStream* s, const void* p, int n, int z);  // 0x0093aa70
struct IRef {
  virtual int AddRef();
  virtual int Release();
};
struct cSPVector3_s00bd_5ea0 { float x, y, z; };
struct GameDataVec { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct cGameNounManager_s00bd_5ea0 {
  void RemoveNoun(void* noun);                               // 0x00b225d0
  void RemoveNounsOfType(int type);                          // 0x00b22650
  GameDataVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint tag);  // 0x00b21340
};
cGameNounManager_s00bd_5ea0* __cdecl NounManager_s00bd_5ea0();                     // 0x00b3d300
namespace SP {
class cGameData_s00bd_5ea0 : public IRef {
 public:
  char  pad04[8];
  void* mpNext;                  // +0x0c
  void* mpPrev;                  // +0x10
  bool  mIsDestroyed;            // +0x14
  char  pad15[3];
  uint  mID;                     // +0x18
  uint  mDefinitionID;           // +0x1c
  bool  mb20;                    // +0x20
  bool  mb21;                    // +0x21
  char  pad22[2];
  uint  m24;                     // +0x24
  void* mView;                   // +0x28
  IRef* mpGameDataOwner;         // +0x2c
  uint  mPoliticalID;            // +0x30

  cGameData_s00bd_5ea0();                                            // 0x00b18660
  int GetFieldValues(void* vec);                         // 0x00b18420
  uint GetPoliticalID() const;                            // 0x00804830
  uint GetNounID() const;                                 // vtable slot 0x20
  uint GetNounKey() const;                                // vtable slot 0x4c
  void WriteData(void* s) const;                          // 0x00b18590
  void ReadData(void* s);                                 // 0x00b18600
  void WriteTagged(void* s);                              // 0x00bd6230
  void DtorBody();                                        // 0x00b184c0
  void* AsInterfaceQuery(uint id);                        // 0x00b18460
};
}
namespace SP {
struct cEllipticalOrbit_s00bd_5ea0 {   // retail size 0x68; +0x38 relative to cCelestialBody
  bool  mNullOrbit;          // +0x00
  char  pad01[3];
  cSPVector3_s00bd_5ea0 mPlaneNormal;   // +0x04
  float mEccentricity;       // +0x10
  cSPVector3_s00bd_5ea0 mPerihelion;    // +0x14
  float mPeriod;             // +0x20
  float a;                   // +0x24
  float a2;                  // +0x28
  float b;                   // +0x2c
  float b2;                  // +0x30
  float c;                   // +0x34
  float c2;                  // +0x38
  float e2;                  // +0x3c
  float area;                // +0x40
  cSPVector3_s00bd_5ea0 planeRelativeXAxis;  // +0x44
  cSPVector3_s00bd_5ea0 planeRelativeYAxis;  // +0x50
  cSPVector3_s00bd_5ea0 centerToFocus;       // +0x5c
};
}
namespace SP {
class cCelestialBody_s00bd_5ea0 : public cGameData_s00bd_5ea0 {
 public:
  enum eType { kUnknownCelestialBody = -1, kStar = 0, kAsteroidBelt = 1, kComet = 2 };

  cCelestialBody_s00bd_5ea0(eType type);                       // 0x00bd6410
  ~cCelestialBody_s00bd_5ea0();                                // 0x00bd6530
  void RemoveOwner();                               // 0x00bd61c0
  void UpdateOrbit();                               // 0x00bd6300
  void UpdatePosition(float dt);                    // 0x00bd6590

  eType            mType;         // +0x34
  cEllipticalOrbit_s00bd_5ea0 mOrbit;        // +0x38
  cSPVector3_s00bd_5ea0       mPosition;     // +0xa0
  float            mRotationRate;  // +0xac
  wchar_t*         mNameBegin;    // +0xb0
  wchar_t*         mNameEnd;      // +0xb4
  wchar_t*         mNameCap;      // +0xb8
  uint             mNameD;        // +0xbc
  IRef*            mEffect;       // +0xc0
  IRef*            mHitSphere;    // +0xc4
  float            mHitSphereSize;// +0xc8
};
}
namespace SP {
class cSpatialObject_s00bd_5ea0 {
 public:
  virtual ~cSpatialObject_s00bd_5ea0();
  bool WriteSpatial(void* s) const;                 // 0x00c88a90
  bool ReadSpatial(void* s);                        // 0x00c88b00
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();

  cSpatialObject_s00bd_5ea0();                                 // 0x00c89630
  void DtorBody();                                  // 0x00c8a420
  void* AsInterfaceQuery(uint id);                  // 0x00c884f0
  char pad80[0x6c];
  bool mbSpatialFlag;                               // +0x70 (retail)
  char pad71[0x63];                                 // -> retail size 0xd4
};
}
namespace SP {
class cInteractionTarget_s00bd_5ea0 {
 public:
  virtual ~cInteractionTarget_s00bd_5ea0();
  virtual void* AsInterface(uint id);
  virtual void RemoveInteraction(void* i);
  virtual void AddInteraction(void* i);
  virtual void Shutdown();
  virtual int Release();
  cInteractionTarget_s00bd_5ea0();                             // 0x00ac03d0
  void DtorBody();                                  // 0x00ac0520
  void* QueryInterfaceHere(uint id);                // 0x00ac0320
  char pad04[0x14];                                 // -> retail size 0x18
};
}
namespace SP {
class cCheatObject : public cGameData_s00bd_5ea0, public cSpatialObject_s00bd_5ea0, public cInteractionTarget_s00bd_5ea0 {
 public:
  cCheatObject();                                   // 0x00bd6a80
  ~cCheatObject();                                  // 0x00bd6c10
  void BindCheatHandlers();                         // 0x00bd6c60
  void DtorBases();                                 // 0x00bd6750
  void* QueryInterface(uint id);                    // 0x00bd6770
  void WriteBody(void* s) const;                    // 0x00bd67c0
  void ReadBody(void* s);                           // 0x00bd6810
  int GetFieldValuesAll(void* vec);                 // 0x00bd6b10
  IRef* mpDataObject;                               // +0x120
  bool  mFlag124;                                   // +0x124
  char  pad125[3];
};
}
using SP::cGameData_s00bd_5ea0;
using SP::cCelestialBody_s00bd_5ea0;
using SP::cCheatObject;
#define VT_cCelestialBody0 ((void*)0x01467e80)
#define VT_cCelestialBody1 ((void*)0x01467e6c)
#define VT_cCheatObject0   ((void*)0x014680b8)
#define VT_cCheatObject1   ((void*)0x014680a4)
#define VT_cCheatObject2   ((void*)0x01467fe0)
#define VT_cCheatObject3   ((void*)0x01467fc0)
#define VT_GB1             ((void*)0x013eb384)
struct Matrix3f {
  float m[9];
  void Assign(const float* src);   // 0x0041cb40  (__thiscall)
};
struct OrbitFrame {
  unsigned short mFlags;    // +0x00
  unsigned short mSerial;   // +0x02
  cSPVector3_s00bd_5ea0 mOrigin;       // +0x04
  Matrix3f mBasis;          // +0x10
};
struct IDirty {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
  virtual void Notify();    // slot 0x20
  virtual void NotifyOff(); // slot 0x24
  char pad08[0x1c];
  bool mb20;                // +0x20
};
struct ICheatSink {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
  virtual void RegPart(uint id, const char* name);   // vtable slot 0x40
};
#define gCheatCmd0 ((const char*)0x01468294)
#define gCheatCmd1 ((const char*)0x01468274)
#define gCheatCmd2 ((const char*)0x01468258)
#define gCheatCmd3 ((const char*)0x0146823c)
#define gCheatCmd4 ((const char*)0x01468220)
#define gCheatCmd5 ((const char*)0x01468208)
#define gCheatCmd6 ((const char*)0x014681f0)
#define gCheatCmd7 ((const char*)0x014681d8)
#define gCheatCmd8 ((const char*)0x014681b8)
#define gCheatCmd9 ((const char*)0x0146819c)
#define gCheatCmdA ((const char*)0x01468184)
#define gCheatCmdB ((const char*)0x01468168)
#define gCheatCmdC ((const char*)0x01468150)
#define gCheatCmdD ((const char*)0x01468134)
extern uint gCheatHandlerIds[3];  // 0x01468128
namespace SP {
class cGonzagoSubsystem_s00bd_5ea0 {
 public:
  void Construct();                                 // 0x00b5b960
  char m00[0x1c];
};
}
// ---- items of slice s00bd5ea0 end

// @ 0x00bd1ab0
void cBuilding::PushCoord(u32 value)
{
    u32* pCur = mCoords.mpCurrent;
    cCoordArray* pCoords = &mCoords;
    u32* pNew = pCur + 1;
    if (pNew != pCoords->mpCapacity) {
        pCoords->mpCurrent = pNew;
        if (pCur != 0)
            *pCur = value;
    } else {
        pCoords->Grow(&value);
    }
}

// @ 0x00bd1af0
cBuildingCityHall::cBuildingCityHall()
{
    mpVtbl0 = (void*)&cBuildingCityHall_vtable0;
    mpVtbl1 = (void*)&cBuildingCityHall_vtable1;
    mpVtblSpatial = (void*)&cBuildingCityHall_vtable2;
    mpVtblInteraction = (void*)&cBuildingCityHall_vtable3;
    mpVtblCombatant = (void*)&cBuildingCityHall_vtable4;
    mpVtblPlaceable = (void*)&cBuildingCityHall_vtable5;
    mF340 = 0;
    mF341 = 1;
    _ReadWriteBarrier();
    cGonzagoTimer* pTimer = &mTimerHit;
    mTailVec.mpBegin = 0;
    ctor_cGonzagoTimer(pTimer);
}

// @ 0x00bd1b70
cBuildingIndustry::cBuildingIndustry()
{
    mpVtbl0 = (void*)&cBuildingIndustry_vtable0;
    mpVtbl1 = (void*)&cBuildingIndustry_vtable1;
    mpVtblSpatial = (void*)&cBuildingIndustry_vtable2;
    mpVtblInteraction = (void*)&cBuildingIndustry_vtable3;
    mpVtblCombatant = (void*)&cBuildingIndustry_vtable4;
    mpVtblPlaceable = (void*)&cBuildingIndustry_vtable5;
}

// @ 0x00bd1bb0
void* cBuildingIndustry::Delete(u8 flags)
{
    mpVtbl0 = (void*)&cBuildingIndustry_vtable0;
    mpVtbl1 = (void*)&cBuildingIndustry_vtable1;
    mpVtblSpatial = (void*)&cBuildingIndustry_vtable2;
    mpVtblInteraction = (void*)&cBuildingIndustry_vtable3;
    mpVtblCombatant = (void*)&cBuildingIndustry_vtable4;
    mpVtblPlaceable = (void*)&cBuildingIndustry_vtable5;
    dtor_cBuilding(this);
    if ((flags & 1) != 0)
        FreeObj(this);
    return this;
}

// @ 0x00bd1c00
cBuildingHouse::cBuildingHouse()
{
    mpVtbl0 = (void*)&cBuildingHouse_vtable0;
    mpVtbl1 = (void*)&cBuildingHouse_vtable1;
    mpVtblSpatial = (void*)&cBuildingHouse_vtable2;
    mpVtblInteraction = (void*)&cBuildingHouse_vtable3;
    mpVtblCombatant = (void*)&cBuildingHouse_vtable4;
    mpVtblPlaceable = (void*)&cBuildingHouse_vtable5;
}

// @ 0x00bd1c40
cBuildingEntertainment::cBuildingEntertainment()
{
    mpVtbl0 = (void*)&cBuildingEntertainment_vtable0;
    mpVtbl1 = (void*)&cBuildingEntertainment_vtable1;
    mpVtblSpatial = (void*)&cBuildingEntertainment_vtable2;
    mpVtblInteraction = (void*)&cBuildingEntertainment_vtable3;
    mpVtblCombatant = (void*)&cBuildingEntertainment_vtable4;
    mpVtblPlaceable = (void*)&cBuildingEntertainment_vtable5;
}

// @ 0x00bd1c80
void* cBuildingEntertainment::Delete(u8 flags)
{
    mpVtbl0 = (void*)&cBuildingEntertainment_vtable0;
    mpVtbl1 = (void*)&cBuildingEntertainment_vtable1;
    mpVtblSpatial = (void*)&cBuildingEntertainment_vtable2;
    mpVtblInteraction = (void*)&cBuildingEntertainment_vtable3;
    mpVtblCombatant = (void*)&cBuildingEntertainment_vtable4;
    mpVtblPlaceable = (void*)&cBuildingEntertainment_vtable5;
    dtor_cBuilding(this);
    if ((flags & 1) != 0)
        FreeObj(this);
    return this;
}

// @ 0x00bd1cd0
void cAimController::Update(cAimUpdateArgs* pArgs)
{
    pArgs->mPos.x = gVec3Zero[0];
    pArgs->mPos.y = gVec3Zero[1];
    pArgs->mPos.z = gVec3Zero[2];

    cAimWorld* pWorld = pArgs->mpTarget;
    if (pWorld == 0)
        return;

    cAimWorld* pObj = (cAimWorld*)pWorld->mpVtbl->GetByTag(pWorld, 0, 0x436f315u);
    if (pObj == 0)
        return;
    if (pObj->mF684 > 0)
        return;
    if (Fn_00bfc600(&pObj->mCombatant, 0) != 0)
        return;
    if (GetDamageState(&pObj->mCombatant, 0) == 2)
        return;

    cVec3f vForward;
    pObj->mSpatial.mpVtbl->GetForward(&pObj->mSpatial, 0, &vForward);
    cVec3f vPos = *pObj->mSpatial.mpVtbl->GetPosition(&pObj->mSpatial, 0);

    cPosObject* pTargetPos = 0;
    cRefObject* pRef = pObj->mCombatant.mpVtbl->GetRefObject(&pObj->mCombatant, 0);
    if (pRef != 0)
        pTargetPos = pRef->mpVtbl->GetRef(pRef, 0);

    cPosObject* pOtherPos = 0;
    if (pObj->mpF6a4 != 0)
        pOtherPos = pObj->mpF6a4->mpVtbl->GetRef(pObj->mpF6a4, 0);

    if (pTargetPos != 0 || pOtherPos != 0)
    {
        cPosObject* pChosen = (pTargetPos != 0) ? pTargetPos : pOtherPos;
        cVec3f vTarget = *pChosen->mpVtbl->GetPosition(pChosen, 0);
        cVec3f vDelta;
        vDelta.x = vTarget.x - vPos.x;
        vDelta.y = vTarget.y - vPos.y;
        vDelta.z = vTarget.z - vPos.z;
        cVec3f* pNorm = normalized_safe(&mFacing, &vDelta);
        mFacing = *pNorm;
        mMode = 1;
    }
    else
    {
        float fDot = mFacing.x * vForward.x +
                     mFacing.y * vForward.y +
                     mFacing.z * vForward.z;
        if (mMode != 1 && fDot <= 0.96f)
            goto build_quaternion;

        ++mCounter;
        mMode = 0;

        cVec3f vPositionDir;
        normalized_safe(&vPositionDir, &vPos);

        cVec3f vMuzzleOut;
        cVec3f* pMuzzle = pObj->mpWeapon->mpVtbl->GetMuzzle(pObj->mpWeapon, 0, &vMuzzleOut);
        cVec3f vToMuzzle;
        vToMuzzle.x = vPos.x - pMuzzle->x;
        vToMuzzle.y = vPos.y - pMuzzle->y;
        vToMuzzle.z = vPos.z - pMuzzle->z;

        cVec3f vToMuzzleDir;
        cVec3f* pToMuzzle = normalized_safe(&vToMuzzleDir, &vToMuzzle);

        float fAlong = vPositionDir.x * pToMuzzle->x +
                       vPositionDir.y * pToMuzzle->y +
                       vPositionDir.z * pToMuzzle->z;
        cVec3f vTangent;
        vTangent.x = pToMuzzle->x - vPositionDir.x * fAlong;
        vTangent.y = pToMuzzle->y - vPositionDir.y * fAlong;
        vTangent.z = pToMuzzle->z - vPositionDir.z * fAlong;
        cVec3f vTangentDir = *normalized_safe(&vTangent, &vTangent);

        float fRoll = 0.0f;
        if ((mCounter & 1) == 0)
            fRoll = ((mCounter & 3) == 0) ? gAimTurnStep : -gAimTurnStep;

        cMat33f matRot;
        Fn_00576b00(&matRot, &vPositionDir, fRoll);

        cVec3f vRotated;
        vRotated.x = matRot.m[3] * vTangentDir.y + matRot.m[6] * vTangentDir.z + matRot.m[0] * vTangentDir.x;
        vRotated.y = matRot.m[4] * vTangentDir.y + matRot.m[7] * vTangentDir.z + matRot.m[1] * vTangentDir.x;
        vRotated.z = matRot.m[5] * vTangentDir.y + matRot.m[8] * vTangentDir.z + matRot.m[2] * vTangentDir.x;

        if ((mCounter % 5) == 0)
        {
            cVec3f vOffset;
            if ((mCounter & 1) == 0)
            {
                vOffset.x = vRotated.x - vPositionDir.x * 0.6666667f;
                vOffset.y = vRotated.y - vPositionDir.y * 0.6666667f;
                vOffset.z = vRotated.z - vPositionDir.z * 0.6666667f;
            }
            else
            {
                vOffset.x = vPositionDir.x * 0.6666667f + vRotated.x;
                vOffset.y = vPositionDir.y * 0.6666667f + vRotated.y;
                vOffset.z = vPositionDir.z * 0.6666667f + vRotated.z;
            }
            vRotated = *normalized_safe(&vOffset, &vOffset);
        }

        mFacing = vRotated;
    }

build_quaternion:
    {
        cVec3f vUp;
        normalized_safe(&vUp, &vPos);
        cQuat4f qFacing;
        QuaternionFromFacingAndUp(&qFacing, &mFacing, &vUp);

        cQuat4f qOrient = *pObj->mSpatial.mpVtbl->GetOrientation(&pObj->mSpatial, 0);

        float fCos = mFacing.x * qOrient.x +
                     mFacing.y * qOrient.y +
                     mFacing.z * qOrient.z;
        if (fCos > 1.0f)
            fCos = 1.0f;
        if (fCos < 0.0f)
            fCos = 0.0f;

        float fAngle = (float)_CIacos(fCos);
        if (Fn_0059ab10(fAngle) != 0)
        {
            float fT = gAimTurnMax;
            if (mMode == 0)
                fT = gAimTurnStep * 0.666f;
            if (fAngle <= 0.0f)
            {
                fT = 1.0f;
            }
            else
            {
                fT = (pArgs->mScale * fT) / fAngle;
                if (fT >= 1.0f)
                    fT = 1.0f;
            }
            cQuat4f qBlended;
            Fn_005b26f0(&qBlended, &qOrient, &qFacing, fT);
            pObj->mSpatial.mpVtbl->SetOrientation(&pObj->mSpatial, 0, &qBlended);
        }
    }
}

// @ 0x00bd2310
void cSPCreatureCitizen::Init(cCitizenData* pArg)
{
    mF654.x = gVec3Zero[0];
    mF654.y = gVec3Zero[1];
    mF654.z = gVec3Zero[2];
    mbFlagDa = 0;
    mbFlagA5 = 1;

    SetGameDataOwner2(this, 0, pArg);

    {
        cCitizenData* pOld = mpF688;
        if (pArg != pOld)
        {
            if (pArg != 0)
                pArg->mpVtbl->AddRef(pArg, 0);
            mpF688 = pArg;
            if (pOld != 0)
                pOld->mpVtbl->Release(pOld, 0);
        }
    }

    {
        void* pOwnerRaw = pArg->mpVtbl->GetOwner(pArg, 0);
        void* pOwner = Fn_00bebe10(pOwnerRaw, 0);
        mpVtblSpatial->Fn94(&mpVtblSpatial, 0, pOwner);
    }

    Fn_00bd0000(this, 0);

    {
        cListNode* pNew = mpF690;
        cListNode* pOld = mpF68c;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->mpVtbl->Release(pNew, 0);
            mpF68c = pNew;
            if (pOld != 0)
                pOld->mpVtbl->Fn08(pOld, 0);
        }
    }

    void* pGameMode = GetCurrentGameMode();
    int nLevel = 0;
    if (pGameMode == (void*)gAppTag)
    {
        u32 nEmpireId = pArg->mpVtbl->GetEmpireId(pArg, 0);
        void* pStarManager = StarManager();
        void* pEmpire = GetEmpireByID(pStarManager, 0, nEmpireId);
        if (pEmpire != 0)
            nLevel = GetWeaponryLevel(pEmpire, 0);
    }
    Fn_00bd15a0(this, 0, nLevel);

    cBehaviorMgr* pBehaviorMgr = (cBehaviorMgr*)BehaviorManager();
    pBehaviorMgr->mpVtbl->Fn38(pBehaviorMgr, 0, &mBehaviorList);

    if (pGameMode == (void*)gAppTag)
    {
        void* pEffectArg = (mpF688 != 0) ? (void*)&mpF688->mF1f4 : 0;
        mBehaviorList.mpVtbl->Fn0c(&mBehaviorList, 0, gBehaviorId, pEffectArg, 0);
    }

    mF224 = 5;

    {
        cTurretRotator* pRotator =
            (cTurretRotator*)NewObj(0x24, "Simulator/cTurretRotatorLocomotion", 0, 0, 0, 0);
        if (pRotator != 0)
        {
            pRotator->mpVtbl2 = (void*)&cTurretVtableVtbl8;
            pRotator->mpVtbl3 = 0;
            pRotator->mpVtbl0 = (void*)&cTurretVtable000;
            pRotator->mpVtbl2 = (void*)&cTurretVtable008;
            pRotator->mF10 = 1;
            pRotator->mF14 = 0;
            pRotator->mF18.x = gVec3Zero[0];
            pRotator->mF18.y = gVec3Zero[1];
            pRotator->mF18.z = gVec3Zero[2];
        }
        Fn_00c421b0(&mpVtblSpatial, 0, pRotator);
    }

    {
        void* pNounMgr = NounManager();
        cCitizenData* pRef = 0;
        cNoun* pNoun = (cNoun*)CreateNoun(pNounMgr, 0, 0x2e72caeu);
        if (pNoun != 0)
            pRef = pNoun->mpVtbl->CreateRef(pNoun, 0, 0x2e71a5au);

        cCitizenData* pOld = mpF6a0;
        if (pRef != pOld)
        {
            if (pRef != 0)
                pRef->mpVtbl->AddRef(pRef, 0);
            mpF6a0 = pRef;
            if (pOld != 0)
                pOld->mpVtbl->Release(pOld, 0);
        }
    }

    if (mpF6a0 != 0)
    {
        Fn_00c3f2d0(this);
        int nEffect = mpVtblSpatial->Fn2c(&mpVtblSpatial, 0, gEffectSize);
        SetEffectId(mpF6a0, 0, nEffect);
    }
}

// @ 0x00bd2560
void __fastcall Fn_00bd2560(cFlattenOuter* pOuter, void* pEdx, cStr8* pStr)
{
    cPair buffer[64];
    cPairVec vec;
    vec.mpBegin = buffer;
    vec.mpEnd = buffer;
    vec.mpCap = buffer + 64;
    buffer[0].x = 0;

    cCityFlatten* pFlatten =
        (cCityFlatten*)pOuter->mpFlatten->mpVtbl->FillPairs(pOuter->mpFlatten, 0, &vec);
    pFlatten->Flatten5a4(&vec);

    int nCount = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < nCount; ++i)
        pStr->append_sprintf("\n%d: %d", vec.mpBegin[i].x, vec.mpBegin[i].y);

    cPair* pBegin = vec.mpBegin;
    if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
        FreeObj(pBegin);
}

// @ 0x00bd2600
cBuildingScenario::cBuildingScenario()
{
    mpVtbl0 = (void*)&cBuildingScenario_vtable0;
    mpVtbl1 = (void*)&cBuildingScenario_vtable1;
    mpVtblSpatial = (void*)&cBuildingScenario_vtable2;
    mpVtblInteraction = (void*)&cBuildingScenario_vtable3;
    mpVtblCombatant = (void*)&cBuildingScenario_vtable4;
    mpVtblPlaceable = (void*)&cBuildingScenario_vtable5;

    _ReadWriteBarrier();
    u32 zero = 0;
    mTailVec.mpBegin = (u32*)zero;
    mTailVec.mpEnd = (u32*)zero;
    mTailVec.mpCap = (u32*)zero;
    mF388 = (u16)zero;
    mF38a = (u16)zero;
    mF38c = gVec3Zero[0];
    mF390 = gVec3Zero[1];
    mF394 = gVec3Zero[2];
    mF398 = gRealOne;
    mMatrix.Assign(gScenarioRotation);
    mbFlagA4 = 1;
}

// @ 0x00bd61c0
void SP::cCelestialBody_s00bd_5ea0::RemoveOwner()
{
  IRef* owner = mEffect;
  if (owner) {
    ((void(__thiscall*)(IRef*, int))VT(owner, 0xc))(owner, 1);
    owner = mEffect;
    if (owner) {
      mEffect = 0;
      ((void(__thiscall*)(IRef*))VT(owner, 4))(owner);
    }
  }
  IRef* noun = mHitSphere;
  if (noun) {
    NounManager_s00bd_5ea0()->RemoveNoun(noun);
    noun = mHitSphere;
    if (noun) {
      mHitSphere = 0;
      ((void(__thiscall*)(IRef*))VT(noun, 4))(noun);
    }
  }
}

// @ 0x00bd6230
void SP::cGameData_s00bd_5ea0::WriteTagged(void* stream)
{
  cVarListSerializer_s00bd_5ea0 s;
  IV* obj = (IV*)stream;
  IV* writer = (IV*)((Fn_p_v)VT(obj, 0x20))(obj);
  uint magic = 0x38cfb68;
  void* w = ((Fn_p_v)VT(writer, 0x18))(writer);
  EA_IO_WriteUint32((IOStream*)w, &magic, 1, 0);
  s.ctor(this, gVarTable_B, 0x1a80d26);
  s.Write(stream);
}

// @ 0x00bd6300
void SP::cCelestialBody_s00bd_5ea0::UpdateOrbit()
{
  double range = gOrbitAngle_156def8;
  double nrange = -range;
  double angle = ((cRandomLinearCongruential*)0x01601760)->RandomDoubleUniform() * (range - nrange) + nrange;
  if (angle >= range)
    angle = range;
  else if (angle < nrange)
    angle = nrange;
  float ca = (float)cos(angle);
  float denom = (1.0f - mOrbit.e2) * mOrbit.a;
  float r = denom / (mOrbit.mEccentricity * ca + 1.0f);
  float rsa = (float)(r * sin(angle));
  mPosition.x = mOrbit.planeRelativeXAxis.x * (r * ca) + mOrbit.planeRelativeYAxis.x * rsa;
  mPosition.y = mOrbit.planeRelativeXAxis.y * (r * ca) + mOrbit.planeRelativeYAxis.y * rsa;
  mPosition.z = mOrbit.planeRelativeXAxis.z * (r * ca) + mOrbit.planeRelativeYAxis.z * rsa;
}

// @ 0x00bd6410
SP::cCelestialBody_s00bd_5ea0::cCelestialBody_s00bd_5ea0(cCelestialBody_s00bd_5ea0::eType type)
{
  *(void**)this = VT_cCelestialBody0;
  *(void**)((char*)this + 4) = VT_cCelestialBody1;
  mType = type;
  mOrbit.mNullOrbit = true;
  mPosition.x = gPos_168bc90[0];
  mPosition.y = gPos_168bc90[1];
  mPosition.z = gPos_168bc90[2];
  *(float volatile*)&mRotationRate = 0.0f;
  *(wchar_t* volatile*)&mNameBegin = gEmptyString16;
  *(wchar_t* volatile*)&mNameEnd = gEmptyString16;
  *(wchar_t* volatile*)&mNameCap = gEmptyString16 + 1;
  *(IRef* volatile*)&mEffect = 0;
  *(IRef* volatile*)&mHitSphere = 0;
  *(float volatile*)&mHitSphereSize = 1.0f;
  if (type == kStar) {
    mPosition = *(const cSPVector3_s00bd_5ea0*)gPos_168bc90;
    mOrbit.mNullOrbit = true;
  }
}

// @ 0x00bd6530
void __fastcall cCelestialBody_Dtor(cCelestialBody_s00bd_5ea0* self)
{
  *(void* volatile*)self = VT_cCelestialBody0;
  *(void* volatile*)((char*)self + 4) = VT_cCelestialBody1;
  IRef* hs = *(IRef* volatile*)&self->mHitSphere;
  if (hs) {
    ((void(__thiscall*)(IRef*))VT(hs, 4))(hs);
  }
  if (self->mEffect) {
    ((void(__thiscall*)(IRef*))VT(self->mEffect, 4))(self->mEffect);
  }
  char* nameBegin = (char*)self->mNameBegin;
  int diff = (int)((char*)self->mNameCap - nameBegin);
  if (((diff & ~1) > 2) && nameBegin)
    operator_delete__(nameBegin);
  self->DtorBody();
}

// @ 0x00bd6590
void SP::cCelestialBody_s00bd_5ea0::UpdatePosition(float dt)
{
  {
    cSPVector3_s00bd_5ea0 tmp;
    cSPVector3_s00bd_5ea0* p = (cSPVector3_s00bd_5ea0*)FUN_00fe8780(&tmp, &mPosition, gPos_168bc90, &mOrbit, dt);
    mPosition = *p;
  }

  if (mEffect == 0)
    return;
  if (!((char(__thiscall*)(IRef*))VT(mEffect, 0x10))(mEffect))
    return;

  OrbitFrame frame;
  frame.mFlags = 0;
  frame.mSerial = 0;
  frame.mOrigin.x = gOrbitEye_168bce8[0];
  frame.mOrigin.y = gOrbitEye_168bce8[1];
  frame.mOrigin.z = gOrbitEye_168bce8[2];
  frame.mBasis.m[0] = 1.0f;
  frame.mBasis.Assign(gOrbitBasis_168bcc4);
  ((void(__thiscall*)(IRef*, OrbitFrame*))VT(mEffect, 0x20))(mEffect, &frame);

  if (mType == kComet) {
    cSPVector3_s00bd_5ea0 up;
    void* n = SP_normalized_safe(&up, &mPosition);
    Matrix3f tmp2;
    MatrixFromTwoVectors(&tmp2, gOrbitUp_156defc, n);
    frame.mBasis = tmp2;
    frame.mFlags |= 2;
    frame.mSerial++;
  } else if (mRotationRate != 0.0f) {
    frame.mFlags |= 4;
    frame.mSerial++;
    frame.mOrigin = *(cSPVector3_s00bd_5ea0*)gPos_168bc90;
    ((cXform*)&frame)->RotateZ(mRotationRate * dt);
  }

  frame.mOrigin = mPosition;
  frame.mFlags |= 4;
  frame.mSerial++;
  ((void(__thiscall*)(IRef*, OrbitFrame*))VT(mEffect, 0x18))(mEffect, &frame);
}

// @ 0x00bd6750
void SP::cCheatObject::DtorBases()
{
  ((cInteractionTarget_s00bd_5ea0*)((char*)this + 0x108))->DtorBody();
  ((cSpatialObject_s00bd_5ea0*)((char*)this + 0x34))->DtorBody();
}

// @ 0x00bd6770
void* SP::cCheatObject::QueryInterface(uint id)
{
  if (id == 0x2a37e34)
    return this;
  void* r = ((cInteractionTarget_s00bd_5ea0*)((char*)this + 0x108))->QueryInterfaceHere(id);
  if (r == 0) {
    r = ((cGameData_s00bd_5ea0*)this)->AsInterfaceQuery(id);
    if (r == 0)
      r = ((cSpatialObject_s00bd_5ea0*)((char*)this + 0x34))->AsInterfaceQuery(id);
  }
  return r;
}

// @ 0x00bd67c0
void SP::cCheatObject::WriteBody(void* stream) const
{
  cVarListSerializer_s00bd_5ea0 s;
  ((cSpatialObject_s00bd_5ea0*)((char*)this + 0x34))->WriteSpatial(stream);
  ((cGameData_s00bd_5ea0*)this)->WriteData(stream);
  s.ctor((void*)this, gVarTable_A, 0x1a80d26);
  s.Write(stream);
}

// @ 0x00bd6810
void SP::cCheatObject::ReadBody(void* stream)
{
  cVarListSerializer_s00bd_5ea0 s;
  ((cSpatialObject_s00bd_5ea0*)((char*)this + 0x34))->ReadSpatial(stream);
  ((cGameData_s00bd_5ea0*)this)->ReadData(stream);
  s.ctor(this, gVarTable_A, 0x1a80d26);
  s.Read(stream);
}

// @ 0x00bd6870
void __fastcall FUN_00bd6870(IDirty* self)
{
  if (self->mb20 == false) {
    self->mb20 = true;
    self->Notify();
  }
}

// @ 0x00bd6890
void __fastcall FUN_00bd6890(IDirty* self)
{
  self->mb20 = false;
  self->NotifyOff();
}

// @ 0x00bd68a0
void FUN_00bd68a0()
{
  NounManager_s00bd_5ea0()->RemoveNounsOfType(0x2a37e35);
}

// @ 0x00bd6a60
void* __fastcall FUN_00bd6a60(char* self)
{
  if (*(uint*)(self + 0x10) & 0x30)
    return *(void**)self;
  return (*(ushort*)(self + 0x12) != 0) ? (void*)self : 0;
}

// @ 0x00bd6a80
SP::cCheatObject::cCheatObject()
{
  *(void**)this = VT_cCheatObject0;
  *(void**)((char*)this + 4) = VT_cCheatObject1;
  *(void**)((char*)this + 0x34) = VT_cCheatObject2;
  *(void**)((char*)this + 0x108) = VT_cCheatObject3;
  *(IRef* volatile*)&mpDataObject = 0;
  *(bool volatile*)&((cSpatialObject_s00bd_5ea0*)((char*)this + 0x34))->mbSpatialFlag = false;
  IRef* p = *(IRef* volatile*)&mpDataObject;
  if (p) {
    mpDataObject = 0;
    ((void(__thiscall*)(IRef*))VT(p, 4))(p);
  }
}

// @ 0x00bd6b10
int SP::cCheatObject::GetFieldValuesAll(void* vec)
{
  cVarListSerializer_s00bd_5ea0 s;
  int n = GetFieldValues(vec);
  s.ctor((char*)this + 0x34, gVarTable_C, 0x1a80d26);
  return s.GetFields(vec) + n;
}

// @ 0x00bd6c10
void __fastcall cCheatObject_Dtor(cCheatObject* self)
{
  void* sp = (char*)self + 0x34;
  void* it = (char*)self + 0x108;
  *(void**)self = VT_cCheatObject0;
  *(void**)((char*)self + 4) = VT_cCheatObject1;
  *(void**)sp = VT_cCheatObject2;
  *(void**)it = VT_cCheatObject3;
  IRef* p = *(IRef* volatile*)&self->mpDataObject;
  if (p) {
    ((void(__thiscall*)(IRef*))VT(p, 4))(p);
  }
  FUN_00ac0520(it);
  FUN_00c8a420(sp);
  FUN_00b184c0(self);
}

// @ 0x00bd6c60
void SP::cCheatObject::BindCheatHandlers()
{
  ICheatSink* gm = (ICheatSink*)SP_GameInputManager();
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f40, gCheatCmd0);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f44, gCheatCmd1);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f41, gCheatCmd2);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f43, gCheatCmd3);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f42, gCheatCmd4);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f46, gCheatCmd5);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f47, gCheatCmd6);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f48, gCheatCmd7);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f49, gCheatCmd8);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4a, gCheatCmd9);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4b, gCheatCmdA);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f45, gCheatCmdB);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4c, gCheatCmdC);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4d, gCheatCmdD);

  char* handler = (char*)this - 4;
  void* ms = SP_MessageServer();
  *(void**)((char*)this + 0x20) = ms;
  *(void**)((char*)this + 0x24) = handler;
  *(void**)((char*)this + 0x28) = (void*)&gCheatHandlerIds;
  *(uint*)((char*)this + 0x2c) = 3;
  *(uint*)((char*)this + 0x30) = 0;
  if (ms != 0 && handler != 0) {
    for (uint i = 0; i < 3; ++i)
      ((void(__thiscall*)(void*, char*, uint))VT(ms, 0x24))(ms, handler, gCheatHandlerIds[i]);
  }
}

// @ 0x00bd6eb0
void __cdecl FUN_00bd6eb0(int* vec, int command, int amount)
{
  switch (amount) {
    case 0x1f41: amount = 1;    break;
    case 0x1f42: amount = 0x32; break;
    case 0x1f43: amount = 100;  break;
  }

  uint i;
  if (command == 0x1f4b) {
    for (i = 0; i < (uint)((vec[1] - *vec) >> 2); i++) {
      void* e = (void*)(*(int*)(*vec + i * 4));
      FUN_00c0b9d0_hack((float)amount);
      float cur = ((float(__thiscall*)(void*))VT((char*)e + 0x5a8, 0x58))((char*)e + 0x5a8);
      FUN_00f924e0_hack(cur * ((float)amount * 0.01f));
    }
  } else {
    for (i = 0; i < (uint)((vec[1] - *vec) >> 2); i++) {
      void* e = (void*)(*(int*)(*vec + i * 4));
      switch (command) {
        case 0x1f48: {
          float cur = ((float(__thiscall*)(void*))VT((char*)e + 0x5a8, 0x58))((char*)e + 0x5a8);
          FUN_00f924e0_hack(cur * ((float)amount * 0.01f));
          break;
        }
        default:
          FUN_00c0b9d0_hack((float)amount);
          break;
      }
    }
  }
}

// @ 0x00bd7010
void* __fastcall FUN_00bd7010(char* self)
{
  SP::cGonzagoSubsystem_s00bd_5ea0* base = (SP::cGonzagoSubsystem_s00bd_5ea0*)(self + 4);
  *(void**)self = VT_GB1;
  base->Construct();
  *(char volatile*)(self + 0x20) = 0;
  *(void* volatile*)self = (void*)0x14683d0;
  *(void* volatile*)(self + 4) = (void*)0x1468380;
  *(void* volatile*)(self + 8) = (void*)0x146837c;
  *(uint volatile*)(self + 0x24) = 0;
  *(uint volatile*)(self + 0x28) = 0;
  *(uint volatile*)(self + 0x2c) = 0;
  *(uint volatile*)(self + 0x30) = 0;
  *(uint volatile*)(self + 0x34) = 0;
  return self;
}
