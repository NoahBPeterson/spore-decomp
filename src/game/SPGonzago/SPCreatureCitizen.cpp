// src/game/SPGonzago/SPCreatureCitizen.cpp -- migrated from slice(s) s01335f70, s00da7780, s00c267e0, s00c25a50, s00c23f80, s00c22fc0, s00c22010 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureCitizen.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cInteractionTarget.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSpeciesArchetype.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cGonzagoTimer.h"
#include <stdlib.h>
#include <float.h>

// unnamed retail callees and globals (address in the comment)
extern float g_1687A00;   // 0x01687a00
extern float g_1687A14;   // 0x01687a14
extern float g_158129C;   // 0x0158129c
extern float g_15812A0;   // 0x015812a0
extern float g_15812D4;   // 0x015812d4
extern float g_15812D8;   // 0x015812d8
extern float g_15812DC;   // 0x015812dc
extern float g_15812E0;   // 0x015812e0
extern float g_15812E4;   // 0x015812e4
extern float g_15812E8;   // 0x015812e8
extern float g_1581344;   // 0x01581344
extern float g_146AA44;   // 0x0146aa44
extern float g_146AA40;   // 0x0146aa40 (FLT_MAX)
extern float g_13EC4D0;   // 0x013ec4d0
extern void* g_158128C;   // 0x0158128c

// ---- items of slice s00c22010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVN(n) virtual void pv##n();
extern float g_1687A00;   // 0x01687a00
extern float g_1687A14;   // 0x01687a14
extern float g_158129C;   // 0x0158129c
extern float g_15812A0;   // 0x015812a0
extern float g_15812D4;   // 0x015812d4
extern float g_15812D8;   // 0x015812d8
extern float g_15812DC;   // 0x015812dc
extern float g_15812E0;   // 0x015812e0
extern float g_15812E4;   // 0x015812e4
extern float g_15812E8;   // 0x015812e8
extern float g_1581344;   // 0x01581344
extern float g_146AA44;   // 0x0146aa44
extern float g_146AA40;   // 0x0146aa40 (FLT_MAX)
extern float g_13EC4D0;   // 0x013ec4d0
extern void* g_158128C;   // 0x0158128c
namespace EA {
namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pValue, uint32_t nCount, int nSomething);  // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool ReadInt32(void* pStream, int* pValue, uint32_t nCount, int nSomething);               // 0x0093a780
}
}
void*   FUN_00b3d2b0();                                   // 0x00b3d2b0  global getter
void*   FUN_00401090();                                   // 0x00401090  species manager getter
void*   GetCurrentGameMode();                             // 0x00b5b800
float   FUN_004d12a0(int nArchetype);                     // 0x004d12a0
int*    FUN_00c9cec0(int nId);                            // 0x00c9cec0
char    FUN_006a08b0(void* pGlobal, uint32_t nHash, int* pCount, void** ppArray);  // 0x006a08b0
void    FUN_00ba5df0(void* pKey, void* pLocal);           // 0x00ba5df0
void* __fastcall FUN_00cee330(void* pListOwner);          // 0x00cee330  first list entry
float __fastcall FUN_00cee380(void* pListOwner);          // 0x00cee380  sum of entries
class cSpeciesProfile;
class cSPCreatureBase;
class cInteractionTarget;
class cBehaviorStimuliOwner;
class cInteractionAgent;
class cSpeciesProfile {
public:
    uint8_t  mPad000[0x504];    // +0x000
    float    mf0504;            // +0x504
    float    mf0508;            // +0x508
    float    mf050C;            // +0x50c
    uint8_t  mPad510[0x53c - 0x510];
    uint32_t mn053C;            // +0x53c
    uint8_t  mPad540[0x56c - 0x540];
    float    mf056C;            // +0x56c
    uint8_t  mPad570[0x590 - 0x570];
    float    mf0590;            // +0x590
    float    mf0594;            // +0x594
    uint8_t  mPad598[0x634 - 0x598];
    int      mn0634;            // +0x634

    void*    FUN_004d9050(void* pAnim);   // 0x004d9050
    void*    FUN_004d9030(void* pAnim);   // 0x004d9030
    void*    FUN_004d5500(const void* pKey);  // 0x004df550  (species manager method)
};
struct ResourceKey { uint32_t mA; uint32_t mB; uint32_t mC; };
class cSpeciesManager {
public:
    cSpeciesProfile* GetProfile(const ResourceKey& key);     // 0x004df550
    cSpeciesProfile* GetAvatarProfile();                     // 0x004df420
    void* GetSpeciesArchetype(void* pKey, int nSomething);   // 0x004e0050
    char  GetReplacementKey(const ResourceKey& key, uint32_t nMode, ResourceKey* pOut);  // 0x004df7d0
};
class cObjB3D2B0 {
public:
    void FUN_00ac7d10(float fAmount, void* pAgent, int nZero);  // 0x00ac7d10
};
class cObj0xA8C {
public:
    uint8_t  mPad0[0x5fc];      // +0x000
    uint32_t mn05FC;            // +0x5fc
};
class cSpeciesArchetype {
public:
    uint8_t mPad0[0x388];       // +0x000
    uint8_t mb0388;             // +0x388
};
class cAnimatingCreature {
public:
    uint8_t mPad0[0x17c];       // +0x000
    void*   mp017C;             // +0x17c
};
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[0x88];            // +0x000
    uint8_t  mEntries[0x1d0 - 0x88];   // +0x088
    int      mn01D0;            // +0x1d0
    int      mn01D4;            // +0x1d4
    int      mn01D8;            // +0x1d8
    uint32_t mn01DC;            // +0x1dc

    int GetStimulusId() const { return *(const int*)((const char*)mEntries + mn01DC * 0xac); }
};
class cInteractionTarget {
public:
    uint8_t mPad000[0x34];         // +0x000
    uint8_t mSub34[0x12c - 0x34];  // +0x034 (sub-object passed to FUN_00c15d50)
    int     mnType12C;             // +0x12c
    int     mn0130;                // +0x130
    float   mf0134;                // +0x134
    int     GetAttackState();      // 0x00c35b60
};
class IRefCounted {
public:
    virtual void AddRef();       // 0x00
    virtual void Release();      // 0x04
};
class ITagObject {
public:
    virtual void s00();          // 0x00
    virtual void s04();          // 0x04
    virtual void s08();          // 0x08
    virtual void* GetByTag(uint32_t nTag);   // 0x0c
};
class cOutStream {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    virtual void* GetSerializationTarget();   // 0x20
};
class cSerTarget {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5)
    virtual void* GetStream();                // 0x18
};
class cVarListSerializer {
public:
    uint8_t mStorage[0xa14];      // stack storage
    cVarListSerializer(void* pOwner, void* pList, uint32_t nId);  // 0x692f90
    char SerializeOut(void* pStream);   // 0x692900
    char SerializeIn(void* pStream);    // 0x693e10
};
class cSub58 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12)
    virtual void vIdx13();       // 0x34
    uint8_t mPad04[0x40 - 4];    // +0x04 .. +0x3f
};
class cGameData {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30
    virtual void  vIdx13(int);   // 0x34
    virtual void  vIdx14(int);   // 0x38
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19)
    virtual void  vIdx20();      // 0x50
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31)
    virtual float vIdx32(int);   // 0x80
    PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41) PVN(42)
    virtual void  vIdx43(int);   // 0xac
    PVN(44)
    virtual void* vIdx45(int);   // 0xb4
    PVN(46)
    PVN(47) PVN(48) PVN(49) PVN(50) PVN(51) PVN(52) PVN(53)
    virtual int   vIdx54();      // 0xd8
    PVN(55) PVN(56) PVN(57) PVN(58) PVN(59)
    virtual void  vIdx60(int);   // 0xf0
    uint8_t mPad00[0x30];        // +0x04 .. +0x33
};
class cInteractionAgent {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void* pArg);            // 0x30
    PVN(13)
    virtual float GetBundleCapacity(uint32_t nToolType);  // 0x38

    void*  mpListBegin;          // +0x04
    void*  mpListEnd;            // +0x08
    uint8_t mPad0c[0x18 - 0x0c]; // +0x0c
    void*  mp0x18;               // +0x18
    uint8_t mPad1c[0x20 - 0x1c];
    float  mf0x20;               // +0x20
    cSub58 mSub58;               // +0x24
    uint8_t mPad64[0x89 - 0x64]; // +0x64
    uint8_t mb0x89;              // +0x89
    uint8_t mPad8a[0x8c - 0x8a]; // +0x8a

    float FUN_00c22530();                 // 0x00c22530
    void  FUN_010829f0(void* pArg);       // 0x010829f0
    void  FUN_00c22f60(void* pArg);       // 0x00c22f60
};
class cLocomotiveObject {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void lo40(float fScale);    // 0x40
    PVN(17) PVN(18) PVN(19)
    virtual char lo50();                // 0x50
    PVN(21)
    virtual char lo58();                // 0x58

    uint8_t mPad04[0x6c - 0x04]; // +0x04
    uint8_t mb0x6c;              // +0x6c
    uint8_t mPad6d[0x75 - 0x6d]; // +0x6d
    uint8_t mb0x75;              // +0x75
    uint8_t mPad76[0x4e8 - 0x76];// +0x76

    void FUN_00c226c0(char nFlag);   // 0x00c226c0
};
class cCombatant {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();        // 0x58

    uint8_t mPad04[0x34 - 0x04]; // +0x04
    void*   mp0x34;              // +0x34
    float   mf0x38;              // +0x38
    uint8_t mPad3c[0x40 - 0x3c]; // +0x3c

    float GetHealthRatio();              // 0x00bfc490
    void  PartialRepair(float fAmount);  // 0x00bfd1a0
    void  SetHealth(float fValue);       // 0x00f924e0
    int   FUN_00c22010();                // 0x00c22010
};
class cSPCreatureBase : public cGameData, public cInteractionAgent,
                        public cLocomotiveObject, public cCombatant {
public:
    // own members, from +0x5e8
    uint8_t  mPad5e8[0xa8c - 0x5e8];
    cObj0xA8C* mp0xA8C;          // +0xa8c
    uint8_t  mPadA90[0xb20 - 0xa90];
    cSpeciesProfile* mpSpeciesProfile;  // +0xb20
    uint32_t mn0xB24;            // +0xb24
    ResourceKey mKey0xB28;       // +0xb28
    int      mn0xB34;            // +0xb34 (age)
    uint8_t  mPadB38[0xb48 - 0xb38];
    void*    mp0xB48;            // +0xb48  (object with FUN_00bc9fe0)
    cBehaviorStimuliOwner* mpB4C;// +0xb4c
    uint8_t  mPadB50[0xb54 - 0xb50];
    cAnimatingCreature* mp0xB54; // +0xb54
    uint8_t  mPadB58[0xb67 - 0xb58];
    uint8_t  mb0xB67;            // +0xb67
    uint8_t  mPadB68[0xbbc - 0xb68];
    float    mf0xBBC;            // +0xbbc
    uint8_t  mPadBC0[0xe70 - 0xbc0];
    int      mn0xE70;            // +0xe70
    int      mn0xE74;            // +0xe74
    uint8_t  mPadE78[0xe80 - 0xe78];
    void*    mp0xE80;            // +0xe80
    cSpeciesArchetype* mp0xE84;  // +0xe84
    uint8_t  mPadE88[0xfc4 - 0xe88];
    int      mn0xFC4;            // +0xfc4
    uint8_t  mPadFC8[0xff8 - 0xfc8];
    int      mn0xFF8;            // +0xff8
    uint8_t  mPadFFC[0x1004 - 0xffc];
    float    mf0x1004;           // +0x1004
    float    mf0x1008;           // +0x1008
    float    mf0x100C;           // +0x100c
    uint8_t  mPad1010[0x1014 - 0x1010];
    void*    mp0x1014;           // +0x1014
    uint8_t  mPad1018[0x102c - 0x1018];
    int      mn0x102C;           // +0x102c

    // ---- helper calls (thiscall) ----
    void  FUN_00c21bf0(int a, int b);            // 0x00c21bf0  CheckCreatureModel
    char  FUN_00c0c2d0();                        // 0x00c0c2d0  IsDefaultSpecies_
    float FUN_00c0b9c0();                        // 0x00c0b9c0
    void  FUN_00c0b9d0(float fValue);            // 0x00c0b9d0
    char  FUN_00c0bab0();                        // 0x00c0bab0
    char  FUN_00c0ba30();                        // 0x00c0ba30
    int   FUN_00c0c080(int nId);                 // 0x00c0c080  FindIndex
    char  FUN_00b183f0(void* pArg);              // 0x00b183f0
    void  FUN_00c1d640(const char* pVox, int a, int b);  // 0x00c1d640
    void  FUN_00c15d50(void* pArg, int a, int b);        // 0x00c15d50
    void  FUN_00c42350();                        // 0x00c42350
    char  FUN_00c0e0c0(int nType);                       // 0x00c0e0c0
    void  FUN_00c14aa0(void* pStream);                   // 0x00c14aa0
    void  FUN_00c0bc20Write(void* pStream);              // 0x00c0bc20  cSPCreatureBase::Write

    // ---- sliced members ----
    void  FUN_00c22210(int nAge);                        // 0x00c22210
    void  FUN_00c22240();                                // 0x00c22240
    void  FUN_00c222f0(cSpeciesProfile* pNew);           // 0x00c222f0
    bool  FUN_00c22470(void* pArg);                      // 0x00c22470
    float GetBaseMaxHitPoints();                         // 0x00c22720
    char  FUN_00c22750();                                // 0x00c22750
    void  FUN_00c227c0();                                // 0x00c227c0
    void  FUN_00c227f0(int x, int y, int z);            // 0x00c227f0
    int   FUN_00c22830(int nValue);                      // 0x00c22830
    void  FUN_00c22870();                                // 0x00c22870
    void  FUN_00c228c0Write(void* pStream);              // 0x00c228c0
    void  FUN_00c22930Read(void* pStream);               // 0x00c22930
    char  FUN_00c229a0();                                // 0x00c229a0
    void  FUN_00c22a30();                                // 0x00c22a30
    char  FUN_00c22a80(cInteractionTarget* pTarget);     // 0x00c22a80
    void  FUN_00c22ae0();                                // 0x00c22ae0
    char  FUN_00c22ca0(int nType);                       // 0x00c22ca0
    void  FUN_00c22cb0(uint32_t nVox);                   // 0x00c22cb0
    int   FUN_00c22dd0();                                // 0x00c22dd0
    void  FUN_00c22ee0(void* pObj);                      // 0x00c22ee0
};
class cArg22E30 {
public:
    float   mf000;           // +0x00 (the value being drained)
    uint8_t mPad004[0x3c - 4];
    ITagObject* mp03C;       // +0x3c
};
// ---- items of slice s00c22010 end

// ---- items of slice s00c22fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gLeaderScaleBonus;
extern float gFollowerScaleBonus;
extern void* gCreatureToolContext;
extern float gMaxFloat;
typedef int intptr_t;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted_s00c2_2fc0 {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cSPTimer {
public:
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void SetElapsed(uint64_t nElapsed);
    virtual uint64_t GetElapsedTime();

    void* mVftable;                             // 0x00
    int mRefCount;                              // 0x04
    uint64_t mElapsedTime;                      // 0x08
    uint8_t mBaseTime;                          // 0x10
    uint8_t mPad11[0x03];                       // 0x11
    uint32_t mBaseTimeHigh;                     // 0x14
};
class cSpatialObject : public IRefCounted_s00c2_2fc0 {
public:
    Vec3* GetPosition();
};
class cPlanetModel {
public:
    void DirectionToSurfacePosition(const Vec3* pDirection, Vec3* pOut);
    void GetSurfacePoint(const Vec3* pPoint, Vec3* pOut, float fHeight);
};
class cSpeciesProfile_s00c2_2fc0 {
public:
    float GetScaleModifier();
};
class cBundle {
public:
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
    virtual void SetRotation(const Vec3* pRotation);
    virtual void SetPosition(const Vec3* pPosition);
};
class cToolOwner {
public:
    void* GetOwnerCreature();
    Vec3* GetColor();
};
class cCreatureBase : public cSpatialObject {
public:
    Vec3* GetIdentityColor();
    Vec3* GetActiveToolColor();
    void* GetToolById(int nToolId);
    void* GetActiveTool();
    void SetToolTarget(float fX, float fY, float fZ);
    void SetCasted(bool bCasted);
    float CalculateScale();
    char ApplyAttack(void* pTarget, void* pAttack, void* pContext);

    uint8_t mPad04[0x30];                       // 0x04
    cSpatialObject* mpSpatialObject;            // 0x34
    uint8_t mPad38[0x3d];                       // 0x38
    uint8_t mbCastedFlag;                       // 0x75
    uint8_t mPad76[0x4a];                       // 0x76
    uint8_t* mpIdentityColorSource;             // 0xc0
    uint8_t mPadC4[0x0c];                       // 0xc4
    uint8_t mPadD0[0x40];                       // 0xd0
    cSpeciesProfile_s00c2_2fc0* mpSpeciesProfile;          // 0x110
    uint8_t mPad114[0x80c];                     // 0x114
    void* mpToolTable;                          // 0x920
    uint8_t mPad924[0x6de];                     // 0x924
    uint8_t mbIsCastTarget;                     // 0x1002
    uint8_t mPad1003;                           // 0x1003
    float mfToolTargetX;                        // 0x1004
    float mfToolTargetY;                        // 0x1008
    float mfToolTargetZ;                        // 0x100c
    void* mpActiveTool;                         // 0x1010
    void* mpPendingTool;                        // 0x1014
    uint8_t mPad1018[0x14];                     // 0x1018
    void* mpInteractionState;                   // 0x102c
};
class cSPCreatureBase_s00c2_2fc0 : public cCreatureBase {
public:
    uint32_t GetCurrentAnimationGUID(uint32_t* pFlags);  // 0x00c0e040 (cSPCreatureBase::GetCurrentAnimationGUID)
    void PerformSocialAction(int nMode, uint32_t nAnimation);
};
class cSPCreatureCitizen : public cSPCreatureBase_s00c2_2fc0 {
public:
    void SetBundlePlacement(cBundle* pBundle);
    Vec3* GetBundlePosition(Vec3* pOut);
    bool IsLeader();
    bool IsBefriended();
    int GetToolEffect(uint32_t nToolId);
    bool HasSpecializedTool(int nToolId);

    uint8_t mPad1030[0x10];                     // 0x1030
    uint32_t mnIdentity;                        // 0x1040
    uint8_t mPad1044[0x11c];                    // 0x1044
    uint8_t mbBundleHidden;                     // 0x1160
    uint8_t mPad1161[0x3d];                     // 0x1161
    void* mpBundle;                             // 0x119e
};
class cGameNounManager : public IRefCounted_s00c2_2fc0 {
public:
    void* GetPlayerTribe();
    void RemoveNoun(void* pNoun);
};
class cTimerOwner {
public:
    uint8_t mPad00[0x18];                       // 0x00
    cSPTimer mSocialTimer;                      // 0x18
    uint8_t mPad30[0x28];                       // 0x30
    Vec3 mTargetPosition;                       // 0x58
};
void* PlanetModelGet();
void* NounManager();
void* GetCreatureRoot();
float GetRandomFloat(float fMin, float fMax);
void PreserveAnimation(uint32_t nAnimationGuid, uint32_t nFlags);
void PlayCreatureSocialAnimation(int a, int b, void* pCreature, float fSpeed, void* pParams, int c);
void* GetCreatureBehaviour(int nMode);
uint64_t cSPTimerGetElapsedTime(cSPTimer* pTimer);
void* GetCreatureToolSlot(int a, int b, int c, int d);
void QueueCreatureInteraction(int a, int b, int c);
void* CreateInteractionEffect(int nFlags, int a, float fValue, void* pOwner);
void* GetCreatureSocialTarget(void* pCreature);
void ReportInteraction(uint32_t nType, void* pEffect);
bool IsToolUsable(void* pTool, float fA, float fB);
int CompareCreatureTraits(void* pA, void* pB, int nMode);
void* FindToolInventoryItem(int nKey, void** ppParams);
int GetCreatureActionState(void* pCreature);
int GetCreatureType(void* pCreature);
float GetCreatorScaleModifier(cSpeciesProfile_s00c2_2fc0* pProfile);
float ApplyCreatureScale(int nCharacterLevel, float fScale);
float GetCreatureObjectScale(void* pCreature);
char IsCitizenLeader(void* pCreature);
uint32_t GetLeaderOfCommunity();
int GetCreatureSocialRelation(void* pA, void* pB, int nMode);
void* GetCreatureToolByKey(uint32_t nKey);
bool IsCreatureVisibleInUI(void* pCreature);
bool IsCreatureLeader(void* pCreature);
char ApplyAttackEffect(void* pTarget, void* pAttack, void* pContext);
void* GetCreatureChain(void* pCreature);
void RunCreatureAttackEffect(void* pCreature);
void PlayToolEffect(int a, void* pTarget, void* pOwner);
extern uint8_t gDefaultIdentityColor[0x10];
// ---- items of slice s00c22fc0 end

// ---- items of slice s00c23f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gP_0169b41c;                        // 0x0169b41c
#pragma warning(disable: 4100)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned __int64 u64;
typedef float          f32;
typedef double         f64;
#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))
extern f32   gF_01687a00;                        // 0x01687a00
extern f32   gF_01687a0c;                        // 0x01687a0c
extern f32   gF_01687a10;                        // 0x01687a10
extern f32   gF_0146aa40;                        // 0x0146aa40  (FLT_MAX)
extern f32   gF_0143ee00;                        // 0x0143ee00  (3000.0f)
extern f32   gF_0146aaf0;                        // 0x0146aaf0
extern f32   gF_01470f1c;                        // 0x01470f1c
extern f32   gF_01486110;                        // 0x01486110
extern f32   gF_013ec4d0;                        // 0x013ec4d0
extern f32   gF_013f9428;                        // 0x013f9428
extern f32   gF_013f4fd0;                        // 0x013f4fd0
extern f32   gF_01485720;                        // 0x01485720  (_HK_REAL_ONE)
extern f32   gF_0150c888;                        // 0x0150c888
extern f32   gF_0158121c;                        // 0x0158121c
extern u32   gU_0168dbb0;                        // 0x0168dbb0
extern u32   gU_0168dbb4;                        // 0x0168dbb4
extern u32   gU_0168dbb8;                        // 0x0168dbb8
void  __stdcall FUN_009ff7c0(u32 a1, u32 a2);          // 0x009ff7c0
void  __cdecl FUN_00bca810(u32 a1, u32 a2, void* a3, f32 a4, void* a5, u32 a6); // 0x00bca810
void  __cdecl FUN_00bca040(u32 a1);                  // 0x00bca040
void* __cdecl FUN_00b3d280();                        // 0x00b3d280  GetCameraCtl
void* __cdecl FUN_00b3d300();                        // 0x00b3d300  NounManager
void* __cdecl FUN_00b3d380();                        // 0x00b3d380  GameTimeManager
void* __cdecl FUN_00b3d3e0();                        // 0x00b3d3e0  EventLog
void* __cdecl FUN_004d9050(void* a1);                // 0x004d9050
void* __cdecl FUN_004d9030(void* a1);                // 0x004d9030
void* __cdecl FUN_00c9cec0(u32 a1);                  // 0x00c9cec0
void* __cdecl FUN_00d1e660();                        // 0x00d1e660
void* __cdecl FUN_00b6f0c0(u32 a1);                  // 0x00b6f0c0
void* __cdecl FUN_00cd40b0();                        // 0x00cd40b0  cTribeModeStrategy::Instance
u32   __cdecl FUN_009b2340(void* a1, u32 a2, u32 a3, void* a4, u32 a5, u32 a6); // 0x009b2340
struct cCreatureBase_s00c2_3f80;
void __cdecl FUN_00c24110(cCreatureBase_s00c2_3f80* param_1);   // 0x00c24110
struct COps
{
    void* FUN_00c00650();                            // 0x00c00650 (GetMember)
    u32   FUN_00c0e040(u32* out);                    // 0x00c0e040
    void* FUN_00c0f9b0(u32 a, u32* b);               // 0x00c0f9b0 (FindSlotByKey)
    void* FUN_00c0f4f0();                            // 0x00c0f4f0
    u8    FUN_00c0b770();                            // 0x00c0b770
    void  FUN_00c1c9f0(u32 a);                       // 0x00c1c9f0
    void* FUN_00c0bf10(u32 a1, u32 a2, u32 a3, u32 a4, f32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10, u32 a11); // 0x00c0bf10
    void* FUN_00bc96a0(u32 a, u32 b);                // 0x00bc96a0
    void* FUN_00bc97f0(u32 a, u32 b, f32 c, u32 d);  // 0x00bc97f0
    void* FUN_00bc9980(f32 a);                       // 0x00bc9980
    void  FUN_00c15bd0(u32 a, u32 b, u32 c);         // 0x00c15bd0
    void  FUN_00ac79d0();                            // 0x00ac79d0
    void  FUN_00ac7de0(void* a);                     // 0x00ac7de0
    void  FUN_00b137d0(void* a);                     // 0x00b137d0 (GetTargetOrientation)
    void  FUN_00c3f160(u32 a);                       // 0x00c3f160 (SetEffectId)
    void  FUN_00b225d0(void* a);                     // 0x00b225d0 (RemoveNoun)
    void* FUN_00c23300(u32 a, u32 b);                // 0x00c23300
    void  FUN_00d995f0(f32 a1, f64 a2, u32 a3, void* a4, void* a5, u32 a6, u32 a7, u32 a8); // 0x00d995f0
    void  FUN_00dd8640(u32 a1, u32 a2, void* a3); // 0x00dd8640
    void  FUN_00ccc400();                            // 0x00ccc400
    void* FUN_00bca2c0();                            // 0x00bca2c0 (FirstPending)
    u8    FUN_00c232d0();                            // 0x00c232d0 (IsLeader)
    void  FUN_00c1d400(u32 a, u32 b);                // 0x00c1d400
    void  FUN_00c213d0(u32 a);                       // 0x00c213d0
    u32   FUN_00cee330();                            // 0x00cee330
    void  FUN_00c14750(u32 a);                       // 0x00c14750
    u8    FUN_00c0c130();                            // 0x00c0c130
    f32   FUN_00c0c070();                            // 0x00c0c070
    void  FUN_00c0ba10();                            // 0x00c0ba10
    u8    FUN_00c0ba70();                            // 0x00c0ba70
    void  FUN_00c95cc0(void* a);                     // 0x00c95cc0
    u32   FUN_00abf760(u32 a, void* b, u32 c);       // 0x00abf760
    void  FUN_00c22240();                            // 0x00c22240
    u32   FUN_00c8f370();                            // 0x00c8f370 (GetAdultPopulation)
    u8    FUN_00c0e420();                            // 0x00c0e420
    u32   FUN_00a02ba0();                            // 0x00a02ba0
    void  FUN_00bc3110();                            // 0x00bc3110 (cSPTimer::Stop)
    u64   FUN_00b316c0();                            // 0x00b316c0
    u32   FUN_00c17de0(f32 a);                       // 0x00c17de0
    void* FUN_00c0b670(u32 a);                        // 0x00c0b670
    void  FUN_00c0d340(u32 a);                        // 0x00c0d340
    f64   FUN_00bfc490();                             // 0x00bfc490
    void  FUN_00bca810(u32 a1, u32 a2, void* a3, f32 a4, void* a5, u32 a6); // 0x00bca810
};
struct cCreatureBase_s00c2_3f80
{
    u8     pad0[0x24];                               // 0x0000
    u32    mField24;                                 // 0x0024
    u8     pad28[0x34 - 0x28];
    void*  mpObj34;                                  // 0x0034
    u8     pad38[0x58 - 0x38];
    void*  mpObj58;                                  // 0x0058
    u8     pad5c[0xc0 - 0x5c];
    void*  mpObjc0;                                  // 0x00c0
    u8     padc4[0x110 - 0xc4];
    u32    mFlags110;                                // 0x0110
    u8     pad114[0x135 - 0x114];
    u8     mField135;                                // 0x0135
    u8     mField136;                                // 0x0136
    u8     mField137;                                // 0x0137
    u8     pad138[0x1e4 - 0x138];
    f32    mField1e4;                                // 0x01e4
    u8     pad1e8[0x2b0 - 0x1e8];
    u32    mField2b0;                                // 0x02b0
    u8     pad2b4[0x5a8 - 0x2b4];
    f32    mNoAttackTimer;                           // 0x05a8
    u8     pad5ac[0xa68 - 0x5ac];
    u32    mFielda68;                                // 0x0a68
    u32    mFielda6c;                                // 0x0a6c
    u8     padb14a[0xaf4 - 0xa70];
    void*  mpFieldaf4;                               // 0x0af4
    u8     padb14b[0xb14 - 0xaf8];
    void*  mpFieldb14;                               // 0x0b14
    u8     padb18[0xb20 - 0xb18];
    void*  mpFieldb20;                               // 0x0b20
    u8     padb24[0xb48 - 0xb24];
    void*  mpOrderMgr_b48;                           // 0x0b48
    void*  mpFieldb4c;                               // 0x0b4c
    u8     padb50[0xb54 - 0xb50];
    void*  mpAnimWorld_b54;                          // 0x0b54
    u8     padb58[0xb5e - 0xb58];
    u8     mFieldb5e;                                // 0x0b5e
    u8     padb5f[0xb61 - 0xb5f];
    u8     mFieldb61;                                // 0x0b61
    u8     padb62[0xb80 - 0xb62];
    f32    mFieldb80;                                // 0x0b80
    u8     padb84[0xbbc - 0xb84];
    f32    mFieldbbc;                                // 0x0bbc
    u8     padbc0[0xc00 - 0xbc0];
    u32    mFieldc00;                                // 0x0c00
    u8     padc04[0xcc0 - 0xc04];
    i32    mLastMotiveState;                         // 0x0cc0
    u8     padcc4[0xe40 - 0xcc4];
    void*  mpNeighbor_e40;                           // 0x0e40
    u8     pade44[0xeac - 0xe44];
    i32    mFieldeac;                                // 0x0eac
    u8     padeb0[0xf50 - 0xeb0];
    void*  mpFieldf50;                               // 0x0f50
    void*  mpFieldf54;                               // 0x0f54
    u8     padf58[0xfbc - 0xf58];
    u32    mFieldfbc;                                // 0x0fbc
    i32    mFieldfc0;                                // 0x0fc0
    u32    mFieldfc4;                                // 0x0fc4
    u32    mFieldfc8;                                // 0x0fc8
    u8     padfcc[0xff0 - 0xfcc];
    u32    mFieldff0;                                // 0x0ff0
    u32    mFieldff4;                                // 0x0ff4
    u32    mFieldff8;                                // 0x0ff8
    u32    mFieldffc;                                // 0x0ffc
    u8     mField1000;                               // 0x1000
    u8     mField1001;                               // 0x1001
    u8     mField1002;                               // 0x1002
    u8     pad1003[0x1004 - 0x1003];
    u32    mField1004;                               // 0x1004
    u32    mField1008;                               // 0x1008
    u32    mField100c;                               // 0x100c
    void*  mField1010;                               // 0x1010
    void*  mpField1014;                              // 0x1014
    u8     pad1018[0x102c - 0x1018];
    i32    mField102c;                               // 0x102c
    void*  mpField1030;                              // 0x1030

    // methods defined in this slice
    u32  FUN_00c23f80(u32 a, u32 b, u32 c, u32 d);
    void FUN_00c24040(u32 a);
    void FUN_00c242b0(u32 a);
    i32  FUN_00c24480();
    void* FUN_00c24400(u32 a);
    u8   FUN_00c24430();
    bool FUN_00c24560();
    u32  FUN_00c245e0(u32 a1, u32 a2, f32 a3, u32 a4, u32 a5, u32 a6);
    u32  FUN_00c24680(u32 a1, u32 a2, f32 a3, u32 a4, void* a5, u32 a6);
    void FUN_00c24700(u32 a1, u32 a2, u32 a3);
    void FUN_00c24760();
    void FUN_00c248d0(i32 a);
    i32  FUN_00c24750();
    i32  FUN_00c24c50();
    void* FUN_00c24ce0(u32 a);
    f64  FUN_00c24df0();
};
// ---- items of slice s00c23f80 end

// ---- items of slice s00c25a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_01572068;                  // 0x01572068
extern "C" void _ReadWriteBarrier(void);
#pragma pack(push, 1)
#pragma pack(pop)
#pragma intrinsic(_ReadWriteBarrier)
typedef int            i32_s00c2_5a50;
class IRefCounted_s00c2_5a50 {
public:
    virtual void  AddRef();                 // +0x00 slot 0
    virtual void  Release();                // +0x04 slot 1
    virtual void  v08();
    virtual void* Query(const void* pType);
    virtual void  v10();
};
class cCommunity {
public:
    void* GetLeader();                      // 0x00c00650
};
class cVariant {
public:
    cVariant& operator=(const cVariant& rhs);   // 0x00542b80
    u8 mBytes[0x14];
};
class cOrderPlay {
public:
    void* Play(u32 a, u32 b);                        // 0x00bc96a0
    void  FUN_00bc97f0(u32 a, u32 b, f32 c, u32 d);  // 0x00bc97f0
};
class cAgentOrderManager {
public:
    void* FirstPending();                   // 0x00bca2c0
    u8 mPad_04[4];
    cOrderPlay mPlay_08;                    // +0x08
};
class cVTable { public: void* mpSlots[0x60]; };
class cDispatchObject {
public:
    void* Call(i32_s00c2_5a50 slot) {
        return ((void* (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    i32_s00c2_5a50 CallInt(i32_s00c2_5a50 slot) {
        return ((i32_s00c2_5a50 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    f32 CallFloat(i32_s00c2_5a50 slot) {
        return ((f32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    void CallVoid(i32_s00c2_5a50 slot) {
        ((void (__thiscall*)(cDispatchObject*))mpTable->mpSlots[slot >> 2])(this);
    }
    void* CallArg(i32_s00c2_5a50 slot, i32_s00c2_5a50 arg) {
        return ((void* (__thiscall*)(cDispatchObject*, i32_s00c2_5a50))mpTable->mpSlots[slot >> 2])(this, arg);
    }
    f32 CallFloatArg(i32_s00c2_5a50 slot, i32_s00c2_5a50 arg) {
        return ((f32 (__thiscall*)(cDispatchObject*, i32_s00c2_5a50))mpTable->mpSlots[slot >> 2])(this, arg);
    }
    cVTable* mpTable;                       // +0x00
};
class cOrder {
public:
    u32 mType_00;                           // +0x00
    u8  mPad_04[0x28 - 0x04];
    i32_s00c2_5a50 mn_28;                              // +0x28  (pending / active flag)
    u8  mPad_2c[0x38 - 0x2c];
    u8  mb_38;                              // +0x38
    u8  mPad_39[0x4b - 0x39];
    u16 mw_4b;                              // +0x4b  (order sub-type)
};
class cOrderData {
public:
    cOrderData* FUN_00c26730(const cOrderData* pSrc);

    i32_s00c2_5a50          mn_00;                     // +0x00
    u8           mPad_04[0x10 - 0x04];
    i32_s00c2_5a50          mn_10;                     // +0x10
    i32_s00c2_5a50          mn_14;                     // +0x14
    i32_s00c2_5a50          mn_18;                     // +0x18
    i32_s00c2_5a50          mn_1c;                     // +0x1c
    u8           mb_20;                     // +0x20
    u8           mPad_21[3];
    i32_s00c2_5a50          mn_24;                     // +0x24
    IRefCounted_s00c2_5a50* mp_28;                     // +0x28
    i32_s00c2_5a50          mn_2c;                     // +0x2c
    i32_s00c2_5a50          mn_30;                     // +0x30
    i32_s00c2_5a50          mn_34;                     // +0x34
    u8           mb_38;                     // +0x38
    cVariant     mv_39;                     // +0x39
    cVariant     mv_4d;                     // +0x4d
    cVariant     mv_61;                     // +0x61
    cVariant     mv_75;                     // +0x75
};
class cElem18 {
public:
    u8           mb_00;                     // +0x00
    IRefCounted_s00c2_5a50* mp_04;                     // +0x04
    i32_s00c2_5a50          mn_08;                     // +0x08
    f32          mf_0c;                     // +0x0c
    f32          mf_10;                     // +0x10
    f32          mf_14;                     // +0x14
};
extern f32 DAT_0146aa40;                    // 0x0146aa40 (FLT_MAX)
extern u32 DAT_0169ef30;                    // 0x0169ef30
extern u32 DAT_0169f028;                    // 0x0169f028
class cConstObj {
public:
    f32 FUN_0104bdb0();                     // 0x0104bdb0
    f32 FUN_00bfc490();                     // 0x00bfc490
};
class cSPCreatureCitizen_s00c2_5a50 {
public:
    // callees borrowed from the creature base (masked relocations)
    int   GetToolEffect(u32 nTool);                     // 0x00c235e0
    bool  HasSpecializedTool(i32_s00c2_5a50 nTool);                // 0x00c236e0
    bool  IsLeader();                                   // 0x00c232d0
    void  PerformSocialAction(i32_s00c2_5a50 nMode, u32 nAnim);    // 0x00c23300
    void  InterruptAnimation(u32 id, i32_s00c2_5a50 a, i32_s00c2_5a50 b);     // 0x00c12310
    bool  AnimationFinished(u32 id);                    // 0x00c123f0
    void* GetCurrentAnimationGUID();                    // 0x00c0e040
    int   PlayAnimationWithTarget(u32 id, i32_s00c2_5a50 a, i32_s00c2_5a50 b, i32_s00c2_5a50 c);   // 0x00c14910
    int   PlayAnimationWithTarget2(u32 id, i32_s00c2_5a50 a, i32_s00c2_5a50 b, i32_s00c2_5a50 c);  // 0x00c14940
    bool  WaitForAnimEventOrEnd(u32 a, void* out, u32 id, i32_s00c2_5a50 h, i32_s00c2_5a50 b); // 0x00c14ef0
    void  SetCurrentToolEffect(i32_s00c2_5a50 nTool, u32 a);       // 0x00c24f40
    int   FUN_00c0f4f0();                               // 0x00c0f4f0
    char  FUN_00c0e0c0(i32_s00c2_5a50 nType);                      // 0x00c0e0c0
    void* FUN_00c0fa70(u32 a, u32* pOut);               // 0x00c0fa70
    u32   FUN_00c0f6b0();                               // 0x00c0f6b0
    void* FUN_00c0f9b0(i32_s00c2_5a50 nKey, u32* pIndex);          // 0x00c0f9b0
    void* FUN_00c0dfb0(void* pKey);                     // 0x00c0dfb0
    void  FUN_00c0de60(void* pElem, void* pOffsets);    // 0x00c0de60
    void  FUN_00c24040(void* pTree);                    // 0x00c24040
    void  FUN_00c15150(void* pArg, i32_s00c2_5a50 n);              // 0x00c15150
    void* FUN_00c17d60(i32_s00c2_5a50 a, void* b, i32_s00c2_5a50 c, void* d, i32_s00c2_5a50 e); // 0x00c17d60
    int   FUN_00c22c40(i32_s00c2_5a50 a);                          // 0x00c22c40
    int   FUN_00c22dd0();                               // 0x00c22dd0
    int   FUN_00c23f80(i32_s00c2_5a50 a, i32_s00c2_5a50 b, i32_s00c2_5a50 c, i32_s00c2_5a50 d);     // 0x00c23f80
    int   FUN_00c245e0(i32_s00c2_5a50 a, i32_s00c2_5a50 b, f32 c, i32_s00c2_5a50 d, i32_s00c2_5a50 e, i32_s00c2_5a50 f); // 0x00c245e0

    // slice targets
    bool  FUN_00c25a50(void* pTree);
    void  FUN_00c25f80();
    i32_s00c2_5a50   FUN_00c26120();
    i32_s00c2_5a50   FUN_00c26170();
    void  FUN_00c26310(void* pTree);
    bool  IsWaitingForTool(i32_s00c2_5a50 nTool);  // 0x00c26380 (cSPCreatureCitizen::IsWaitingForTool)
    void  SetToolOnAnimEvent(i32_s00c2_5a50 nTool);
    void  FUN_00c26450();

    // fields
    u8   mPad_000[0x34];
    cDispatchObject mSub_034;               // +0x034 (locomotion / spatial)
    u8   mPad_038[0xc0 - 0x38];
    cDispatchObject mSub_0c0;               // +0x0c0 (identity / interactive)
    u8   mPad_0c4[0xb20 - 0xc4];
    void* mp_b20;                           // +0x0b20
    u8   mPad_b24[0xb4c - 0xb24];
    cAgentOrderManager* mpOrders_b4c;       // +0x0b4c
    u8   mPad_b50[0xb54 - 0xb50];
    void* mp_b54;                           // +0x0b54
    u8   mPad_b58[0xe40 - 0xb58];
    void* mp_e40;                           // +0x0e40
    u8   mPad_e44[0xfc4 - 0xe44];
    void* mpBT_fc4;                         // +0x0fc4 behavior tree data
    void* mpInteract_fc8;                   // +0x0fc8 who is interacting
    u8   mPad_fcc[0xffc - 0xfcc];
    i32_s00c2_5a50   mnCurTool_ffc;                    // +0x0ffc current tool effect bits
    u8   mPad_1000[0x1002 - 0x1000];
    u8    mb_1002;                          // +0x1002
    u8   mPad_1003[0x1004 - 0x1003];
    f32   mf_1004;                          // +0x1004
    f32   mf_1008;                          // +0x1008
    f32   mf_100c;                          // +0x100c
    void* mpOwnerCity_1010;                 // +0x1010
    void* mpOwnerTribe_1014;                // +0x1014
    u8   mPad_1018[0x102c - 0x1018];
    i32_s00c2_5a50   mnToolEffectIndex;                // +0x102c
};
void* FUN_005727b0(void* p);                                    // 0x005727b0
void* FUN_005727e0(void* p);                                    // 0x005727e0
// ---- items of slice s00c25a50 end

// ---- items of slice s00c267e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gsAllocatorFile[];
struct cVTable_s00c2_67e0 {
    void* mpSlots[0x100];                       // 0x000
};
class cDispatchObject_s00c2_67e0 {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject_s00c2_67e0*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    int32_t CallInt(int nSlot) {
        return ((int32_t (*)(cDispatchObject_s00c2_67e0*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject_s00c2_67e0*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoidArg(int nSlot, void* pArg) {
        ((void (*)(cDispatchObject_s00c2_67e0*, void*))mpTable->mpSlots[nSlot >> 2])(this, pArg);
    }

    cVTable_s00c2_67e0* mpTable;                           // 0x000
};
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
class cLocomotive {
public:
    void ResetLocomotion();                     // 0x00c44040
    void SetStrategy(void* pStrategy);          // 0x00c421b0
    void AddStrategy(void* pStrategy);          // 0x00c43fe0
    int32_t IsHidden();                         // slot 0x58 of the interface

    void* mpVtblLocal;                          // 0x000
    uint8_t mPad004[0xd0];                      // 0x004
};
class cBehaviorAgent {
public:
    void SetActive(int32_t nActive);            // slot 0x14 of the interface

    void* mpVtblLocal;                          // 0x000
    uint8_t mPad004[0x64];                      // 0x004
};
class cGonzagoTimer {
public:
    void Reset();
    void Restart();
    void Destroy();                             // 0x00b638b0

    uint8_t mbField20[0x20];                    // 0x000
    int32_t mnField24;                          // 0x020
    int32_t mnField28;                          // 0x024
    int32_t mnField2c;                          // 0x028
    int32_t mnField30;                          // 0x02c
    uint8_t mbField34;                          // 0x030
    uint8_t mPad035;                            // 0x031
    uint8_t mbField36;                          // 0x032
    uint8_t mPad037;                            // 0x033
    float mafOffset[3];                         // 0x034
};
class cStarRecordVector {
public:
    void Destroy();                             // 0x00ae6970
    cStarRecordVector& CopyFrom(cStarRecordVector* pOther);

    void* mpBegin;                              // 0x000
    void* mpEnd;                                // 0x004
    void* mpCapacity;                           // 0x008
};
class cCreatureCitizen {
public:
    void TakeToolHit(int32_t nToolIndex, int32_t nSource, int32_t nFlags, int32_t nUnused,
                     void* pInfo);
    void CreateLocomotionStrategy();
    void ApplyToolOrder(uint32_t nToolMask, void* pOrder);
    void UpdateSelectionFlags();
    cCreatureCitizen* Construct();
    void Destroy();
    void UpdateFrame(void* pTransform, int32_t nMode, int32_t nFlags, void* pContext);
    void* GiveOrder(void* pOrderInfo, void* pTarget, void* pParams);
    int32_t SelectSpeciesProfile(void* pSpeciesKey);
    void SetCreatureName(const char* pName);
    int32_t GetToolEffect(int32_t nTool);
    void ApplyOrder(int32_t nTool, void* pOrder);
    int32_t OnProfileSelected(void* pSpeciesKey);
    void SetLocalizedName(char** ppText);       // 0x00c43e40

    void* mpVtbl00;                             // 0x000
    void* mpVtbl04;                             // 0x004
    uint8_t mPad008[0x2c];                      // 0x008
    void* mpVtbl34;                             // 0x034
    uint8_t mPad038[0x20];                      // 0x038
    cBehaviorAgent mAgent;                      // 0x058
    cLocomotive mLocomotion;                    // 0x0c0
    void* mpVtbl194;                            // 0x194
    uint8_t mPad198[0x118];                     // 0x198
    int32_t mnPlanetCorrection;                 // 0x2b0
    uint8_t mPad2b4[0x2dc];                     // 0x2b4
    void* mpVtbl590;                            // 0x590
    uint8_t mPad594[0x14];                      // 0x594
    void* mpVtbl5a8;                            // 0x5a8
    uint8_t mPad5ac[0x34];                      // 0x5ac
    float mfToolDurability;                     // 0x5e0
    uint8_t mPad5e4[0x8c];                      // 0x5e4
    void* mpVtbl670;                            // 0x670
    uint8_t mPad674[0x4ac];                     // 0x674
    void* mpProfile;                            // 0xb20
    uint8_t mPadB24[0x04];                      // 0xb24
    uint8_t mSpeciesKey[0x20];                  // 0xb28
    void* mpFieldB48;                           // 0xb48
    cDispatchObject_s00c2_67e0* mpFieldB4C;                // 0xb4c
    uint8_t mPadB50[0x0e];                      // 0xb50
    uint8_t mbFieldB5E;                         // 0xb5e
    uint8_t mPadB5f[0x2e1];                     // 0xb5f
    void* mpListBegin;                          // 0xe40
    void* mpListEnd;                            // 0xe44
    uint8_t mPadE48[0x188];                     // 0xe48
    cGonzagoTimer mTimer;                       // 0xfd0
    cRefCounted* mpOwnerCity;                   // 0x1010
    cRefCounted* mpOwnerTribe;                  // 0x1014
    cStarRecordVector mStarRecords;             // 0x1018
    int32_t mnSpecializedTool;                  // 0x1024
    cRefCounted* mpHitSphere;                   // 0x1028
    int32_t mnToolEffectIndex;                  // 0x102c
    cRefCounted* mpRequest;                     // 0x1030
};
class cCreatureBase_s00c2_67e0 {
public:
    void ConstructBase();
    void DestroyBase();                         // 0x00c1bbd0
    void OnTakeHit(int32_t nSource, int32_t nFlags, int32_t nUnused, void* pInfo);
};
class cSimulatorService {
public:
    void* GetWorldStrategy();
    void* GetDefaultStrategy();
};
class cFlagOwner {
public:
    int32_t mnFlags;                            // 0x5fc
};
class cCitizenQueue {
public:
    int32_t mnFlagsA;
    int32_t mnFlagsB;
    int32_t mnFlagsC;
};
void* __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nFlags,
                           int32_t nAlignment, const char* pFile, int32_t nLine);
void __cdecl operator_delete_array(void* pBlock);
cSimulatorService* GetSimulatorService();       // 0x00b3d310
void PlanetLocomotionStrategy();
void SpaceLocomotionStrategy();
void RestartCitizenTimers();                    // 0x00c0ba10
int32_t UpdateCitizenEffects();                 // 0x00c0b770
void ForceOrdersUpdate(cCreatureCitizen* pCitizen);   // 0x00c26450
void __stdcall RebuildCitizenOrderList(int32_t nIndex);   // 0x00c26310
void PlayCitizenEffect(int32_t nEffect, int32_t nFlags, float fScale, void* pTarget);
void OnCitizenFlagChanged(int32_t nId, int32_t nValue);
int32_t GetSettingId(void* pKey);               // 0x00401090
void* GetProfileFromKey(void* pKey);            // 0x004df550
void FUN_00bc8fa0(void* pData);
void FUN_00bcb660(void* pData);
void FUN_00bc9a30(int32_t nId, void* pData);
void FUN_00c0cf50();
void* FUN_00bd99e0();
void* FUN_00b6f0c0(void* pData);
void FUN_00c0d950(int32_t nValue);
void FUN_00c21090();
void FUN_00c24110(cCreatureCitizen* pCitizen);
void* CreateCitizenNoun(int32_t nNounId);
void FUN_00c3f160(float fA, float fB);
void FUN_00c3f2d0(cCreatureCitizen* pCitizen);
void* FUN_00bca2c0();
void FUN_00bca470();
void FUN_00c26730(void* pOrder);
void* FUN_00bcaf70(void* pTarget, void* pParams, int32_t nFlags);
int32_t FUN_00bca180(void* pOrder);
void FUN_00bca120();
void CopyStarRecordRange(cStarRecordVector*& rpCursor, void* pBegin, void* pEnd, void* pBuffer,
                         cStarRecordVector* pSource);   // 0x00c266c0
class cGonzagoTempText {
public:
    cGonzagoTempText(const char* pText);        // 0x00b46d90

    char* mpText;                               // 0x000
    uint8_t mPad004[0x6c];                      // 0x004
};
class cTextAllocation {
public:
    int32_t mnSize;                             // 0x000 (stored right before the characters)
};
cCitizenQueue g_citizenQueue;
uint8_t g_bCitizenQueueInitialized = 0;
uint8_t g_bCitizenGlobalsReady = 0;
float g_fOffsetX = 0.0f;
float g_fOffsetY = 0.0f;
float g_fOffsetZ = 0.0f;
float g_fCitizenScale = 0.0f;
int32_t g_nCitizenMode = 0;
float g_fMaxFloat = 3.402823466e38f;
// ---- items of slice s00c267e0 end

// ---- items of slice s00da7780 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int            i32_s00da_7780;
struct Creature;
struct cTribe;
struct PtrVec { Creature** mBegin; Creature** mEnd; };
struct AutoRefCount {
    u32  mPtr;
    void operator=(void* p);
};
struct OrderSub39 {
    u32          mField00;                 // +0x39 +0x00
    u8           pad_04[0xc];
    u8           mByte10;                  // +0x49 (sub +0x10)
    u8           pad_11[1];
    u16          mField12;                 // +0x4b (sub +0x12)
};
struct OrderRec {
    u32          mField00;                 // +0x00
    u8           pad_04[0x24];
    AutoRefCount mRef28;                   // +0x28
    u8           pad_2c[0xd];
    OrderSub39   mSub39;                   // +0x39
    u8           pad_4d[0x2b];
    u32          mField78;                 // +0x78
    u32          mField7c;                 // +0x7c
    u8           pad_80[0x2c];
};
struct BehaviorStimuli {
    u32   mField00;                        // +0x00
    void* mField04;                        // +0x04
    u8    pad_08[0x38];
    u32 Play(u32 a, u32 flags);
    u32 ClearAll(u32 a, u32 flags);
    void GetAny();
};
struct AgentOrderManager {
    u8 pad_00[8];
    BehaviorStimuli mStimuli;              // +0x08
    u8 pad_48[0x118];
    OrderRec mRecs[1];                     // +0x160
    OrderRec* FirstPending();
    u32 FUN_00bc5040(u32 a);
    u32 FUN_00bc3db0(u32 a);
    u32 FUN_00bc3df0(u32 a);
};
struct SubObj58 {
    void* vptr;
    i32_s00da_7780 V_2c() { return (*(i32_s00da_7780 (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
};
struct Ret7780 {
    u8  pad_000[0x12c];
    i32_s00da_7780 mField12c;
};
struct Locomotive {
    u8  pad_00[0x24];
    SubObj58 mSub58;                       // creature +0x58
    u8  pad_28[0x64];
    Ret7780* FUN_00cee330();
};
struct Obj0xc0 {
    void* vptr;                            // +0x00
    u8    pad_04[0x4c];
    u8    V_58()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0x58))(this); }
    u8    V_f8()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0xf8))(this); }
    void  V_ec()      { (*(void (__thiscall**)(void*))(*(char**)this + 0xec))(this); }
    void  V_54(u32 a) { (*(void (__thiscall**)(void*, u32))(*(char**)this + 0x54))(this, a); }
    void* V_2c()      { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
    void  FUN_00c41d60(void* p);
    void  FUN_00c41d90(void* p);
};
struct cSPTimer_s00da_7780 {
    u8 mData[0x20];
    void Restart();  // 0x00bc3130 (cSPTimer::Restart)
};
struct cSub558 {
    u8 mData[0x10];
    void FUN_00cc7f90(u32 a);
};
struct cTribe {
    void* vptr;                            // +0x00
    u8  pad_004[0x268];
    i32_s00da_7780 mField26c;                         // +0x26c
    cSPTimer_s00da_7780 mTimer270;                    // +0x270
    u8  pad_290[0x2c8];
    cSub558 mSub558;                       // +0x558
    void FindSpot(u32 a, u32 b);
    void FUN_00c950f0(Creature* p);
    void V_9c(Creature* p, u32 a) { (*(void (__thiscall**)(void*, Creature*, u32))(*(char**)this + 0x9c))(this, p, a); }
};
struct S28 { u8 pad0[0x10]; i32_s00da_7780 mField10; };
struct Creature {
    void* vptr;                            // +0x000
    u8  pad_004[0x30];                     // 0x004..0x034
    Locomotive mLoco;                      // +0x034
    Obj0xc0 mObjC0;                        // +0x0c0
    u32 mFlags110;                         // +0x110
    u8  pad_114[0x1b];                     // 0x114..0x12f
    u8  mByte12f;                          // +0x12f
    u8  pad_130[0x7];                      // 0x130..0x137
    u8  mByte137;                          // +0x137
    u8  pad_138[0xa14];                    // 0x138..0xb4c
    AgentOrderManager* mpAgentOrders;      // +0xb4c
    u8  pad_b50[0xe];                      // 0xb50..0xb5e
    u8  mByte_b5e;                         // +0xb5e

    // vtable dispatch helpers
    void  V_8c()      { (*(void (__thiscall**)(void*))(*(char**)this + 0x8c))(this); }
    void  V_84(u32 a, u32 b, u32 c) { (*(void (__thiscall**)(void*, u32, u32, u32))(*(char**)this + 0x84))(this, a, b, c); }
    void* V_b4(void* a) { return (*(void* (__thiscall**)(void*, void*))(*(char**)this + 0xb4))(this, a); }
    PtrVec* V_90()    { return (*(PtrVec* (__thiscall**)(void*))(*(char**)this + 0x90))(this); }

    // methods (extern)
    cTribe* GetTribe();
    Creature* FUN_00bc9b10();
    u32   FUN_00c0ee60();
    void  FUN_00c14750(i32_s00da_7780 a);
    u8    FUN_00c0e0c0(u32 a);
    u32   PlayAnimation(u32 a, i32_s00da_7780 b, i32_s00da_7780 c);
    u32   InterruptAnimation(u32 a, i32_s00da_7780 b, i32_s00da_7780 c);
    u8    WaitForAnimEventOrEnd(u32 a, u32* out, u32 b, void* c, u32 d);
    u8    AnimationFinished(u32 a);
    u32   FUN_00c0b760();
    u8    FUN_00c0b770();
    void* FUN_00c22a70();
    void* FUN_00c22dc0();
    void* FUN_00c26120();
    u8    FUN_00c25480(void* a, u32 b);
    void  SetCurrentToolEffect(u32 a, i32_s00da_7780 b);
    void  RebuildCitizenOrderListDefault();
    void  d0c0(u32 a, i32_s00da_7780 b);
    void  ForceOrdersUpdate();
    u8    FUN_00c04710();
    void  FUN_00c0bf10(u32 a0, u32 a1, u32 a2, u32 a3, f32 f4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10);
};
// ---- items of slice s00da7780 end

// ---- items of slice s01335f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char H_692ca0[];                                              // 0x00692ca0  (all records)
extern "C" char H_572810_0[], H_572810_1[], H_572810_2[], H_572810_3[];
extern "C" char H_572810_4[], H_572810_5[], H_572810_6[], H_572810_7[];
extern "C" char H_572840_0[], H_572840_1[], H_572840_2[], H_572840_3[];
extern "C" char H_572840_4[], H_572840_5[], H_572840_6[], H_572840_7[];
extern "C" char H_692ff0_0[], H_693090_1[], H_693090_2[], H_692ff0_3[];
extern "C" char H_693090_4[], H_c2e4e0_5[], H_c2e4e0_6[], H_c2e4e0_7[];
extern "C" char H_694ee0_0[], H_694f00_1[], H_694f00_2[], H_694ee0_3[];
extern "C" char H_694fa0_4[], H_692fb0_g[];                              // _g shared by records 6,7,8
extern "C" char H_b1fbf0_0[], H_b1fbf0_g[], H_b1fbf0_3[], H_b1fbf0_4[];
extern "C" char H_b6f550_5[], H_b6f550_6[], H_b6f550_7[];
extern "C" char H_57cde0_0[], H_675ca0_g[], H_57cde0_3[], H_57ce00_4[], H_ac8050_g[];
struct AttrDesc {
    const char* mName;      // +0x00  member name
    uint32_t    mHash;      // +0x04  name hash
    uint32_t    mOffset;    // +0x08  byte offset of the member
    uint32_t    mPad0c[3];  // +0x0c  (not written by these initializers)
    uint32_t    mZero18;    // +0x18
    uint32_t    mZero1c;    // +0x1c
    void*       mFn20;      // +0x20  DefaultOffset
    void*       mFn24;      // +0x24  writer
    void*       mFn28;      // +0x28  writer2
    void*       mFn2c;      // +0x2c  parser
    void*       mFn30;      // +0x30  parser2
    void*       mFn34;      // +0x34
    void*       mFn38;      // +0x38
};
extern AttrDesc g_tbl_15721f0[];   // 0x015721f0  table written by $E401
#define REC401(i,nm,h,of,s20,s24,s28,s2c,s30,s34,s38)           \
    d.mName = nm; d.mHash = h; d.mZero18 = 0; d.mZero1c = 0;    \
    d.mFn20 = (void*)s20; d.mFn24 = (void*)s24; d.mFn28 = (void*)s28; \
    d.mFn2c = (void*)s2c; d.mFn30 = (void*)s30;                 \
    d.mFn34 = (void*)s34; d.mFn38 = (void*)s38;                 \
    d.mOffset = of; g_tbl_15721f0[i] = d;
// ---- items of slice s01335f70 end

// @ 0x00c22530
float cInteractionAgent::FUN_00c22530()
{
    int nType = 0;
    if (FUN_00cee330(this) != 0)
        nType = ((cInteractionTarget*)FUN_00cee330(this))->mnType12C;
    return GetBundleCapacity((uint32_t)nType);
}

// @ 0x00c22560
float cInteractionAgent::GetBundleCapacity(uint32_t nToolType)
{
    float fResult = mf0x20;
    cSPCreatureBase* pOwner = (cSPCreatureBase*)this;
    uint32_t nHash = 0;
    int nCount = 0;
    void* pArray = 0;

    switch (nToolType) {
    case 1: fResult = g_15812D4; nHash = 0x48888fad; break;
    case 2: fResult = g_15812D8; nHash = 0x0d4120fd; break;
    case 3: fResult = g_15812DC; nHash = 0xbebd9b84; break;
    case 4: fResult = g_15812E0; nHash = 0x250bd2bd; break;
    case 5: return g_15812E4;
    case 6: return g_146AA40;
    case 7: return g_15812E8;
    default:
        return fResult;
    }

    int nIdx = pOwner->mpSpeciesProfile->mn0634 - 1;
    if (pOwner->mpSpeciesProfile->mn0634 != 0) {
        if (FUN_006a08b0(g_158128C, nHash, &nCount, &pArray) != 0 &&
            nIdx < nCount)
            fResult += ((float*)pArray)[nIdx];
    }
    return fResult;
}

// @ 0x00c226c0
void cLocomotiveObject::FUN_00c226c0(char nFlag)
{
    if (this->lo50() == 0) {
        if (nFlag != 0)
            ((cSPCreatureBase*)this)->vIdx60(0x29b);
        mb0x6c = (uint8_t)nFlag;
        return;
    }
    mb0x6c = (uint8_t)nFlag;
}

// @ 0x00c22720
float cSPCreatureBase::GetBaseMaxHitPoints()
{
    int n = this->vIdx54();
    float f = FUN_004d12a0(n);
    return f + mpSpeciesProfile->mf056C;
}

// @ 0x00c22750
char cSPCreatureBase::FUN_00c22750()
{
    if (FUN_00c0c2d0() != 0 ||
        this->lo58() != 0 ||
        GetCurrentGameMode() == (void*)0x1654c02 ||
        GetCurrentGameMode() == (void*)0x1654c04)
        return 1;
    return 0;
}

// @ 0x00c227c0
void cSPCreatureBase::FUN_00c227c0()
{
    mn0xFF8 = -1;
}

// @ 0x00c227f0
void cSPCreatureBase::FUN_00c227f0(int x, int y, int z)
{
    *(int*)&mf0x1004 = x;
    *(int*)&mf0x1008 = y;
    *(int*)&mf0x100C = z;
}

// @ 0x00c22830
int cSPCreatureBase::FUN_00c22830(int nValue)
{
    if (nValue != -1)
        mn0xFC4 = nValue;
    return mn0xFC4;
}

// @ 0x00c22870
void cSPCreatureBase::FUN_00c22870()
{
    // The cInteractionAgent base subobject. Spelled through a byte pointer so the
    // object code keeps the adjusted pointer in a register (a derived->base cast
    // makes this compiler emit a null check the original does not have).
    cInteractionAgent* pAgent = (cInteractionAgent*)((char*)this + sizeof(cGameData));
    if (FUN_00cee330(pAgent) == 0)
        return;
    cInteractionTarget* e = (cInteractionTarget*)FUN_00cee330(pAgent);
    void* p = (e != 0) ? (void*)e->mSub34 : 0;
    FUN_00c15d50(p, 0, 0);
    pAgent->ia30((void*)FUN_00cee330(pAgent));
}

// @ 0x00c228c0
void cSPCreatureBase::FUN_00c228c0Write(void* pStream)
{
    cOutStream* pOuter = (cOutStream*)pStream;
    cSerTarget* pTarget = (cSerTarget*)pOuter->GetSerializationTarget();
    uint32_t nTag = 0x4f176642;
    void* pS = pTarget->GetStream();
    EA::IO::WriteUint32(pS, &nTag, 1, 0);
    this->FUN_00c0bc20Write(pStream);
    cVarListSerializer ser(this, (void*)0x015721f0, 0x1a80d26);
    ser.SerializeOut(pStream);
}

// @ 0x00c22930
void cSPCreatureBase::FUN_00c22930Read(void* pStream)
{
    cOutStream* pOuter = (cOutStream*)pStream;
    cSerTarget* pTarget = (cSerTarget*)pOuter->GetSerializationTarget();
    int nTag;
    void* pS = pTarget->GetStream();
    EA::IO::ReadInt32(pS, &nTag, 1, 0);
    this->FUN_00c14aa0(pStream);
    cVarListSerializer ser(this, (void*)0x015721f0, 0x1a80d26);
    ser.SerializeIn(pStream);
}

// @ 0x00c229a0
char cSPCreatureBase::FUN_00c229a0()
{
    if (mKey0xB28.mA == 0 ||
        ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28) != 0)
        return 1;

    ResourceKey local;
    local.mA = 0; local.mB = 0; local.mC = 0;
    void* p = mp0xE80;
    if (p == 0)
        p = (void*)0xbbaaecee;
    char ok = ((cSpeciesManager*)FUN_00401090())
                  ->GetReplacementKey(mKey0xB28, (uint32_t)p, &local);
    if (ok != 0) {
        FUN_00ba5df0(&mKey0xB28, &local);
        mKey0xB28 = local;
    }
    return ok;
}

// @ 0x00c22a30
void cSPCreatureBase::FUN_00c22a30()
{
    FUN_00c42350();
    mp0xA8C->mn05FC |= 0x80;
}

// @ 0x00c22a80
char cSPCreatureBase::FUN_00c22a80(cInteractionTarget* pTarget)
{
    if (pTarget->mnType12C > 4)
        return 0;
    int nState = pTarget->GetAttackState();
    if (nState != 6 && pTarget->mn0130 != 1) {
        float fDist = pTarget->mf0134;
        float fCap = this->GetBundleCapacity((uint32_t)pTarget->mnType12C);
        if (fDist < fCap)
            return 0;
    }
    return 1;
}

// @ 0x00c22ae0
void cSPCreatureBase::FUN_00c22ae0()
{
    cInteractionAgent* pAgent = (cInteractionAgent*)this;
    cInteractionTarget* pTarget = (cInteractionTarget*)FUN_00cee330(pAgent);
    if (pTarget == 0)
        return;
    if (pTarget->mnType12C == 6)
        return;

    float fBbc = FUN_00c0b9c0();
    if (g_1687A14 > fBbc) {
        /* fall through to body */
    } else {
        float fRatio = this->GetHealthRatio() * g_13EC4D0;
        if (g_1687A14 <= fRatio)
            return;
    }

    float fHealth = this->mf0x38;
    float fGap = this->GetMaxHealth() - fHealth;
    float a = fGap / g_15812A0;
    float b = (g_1687A00 - FUN_00c0b9c0()) / g_158129C;
    float m1 = (b > a) ? b : a;
    float s = FUN_00cee380(pAgent);
    float m2 = (m1 > s) ? s : m1;

    float fBbc2 = FUN_00c0b9c0();
    FUN_00c0b9d0(fBbc2 + g_158129C * m1);
    this->PartialRepair(g_15812A0 * m1);
    ((cObjB3D2B0*)FUN_00b3d2b0())->FUN_00ac7d10(m2, pAgent, 0);
}

// @ 0x00c22c40
int __stdcall FUN_00c22c40(int nType)
{
    switch (nType) {
    case 0: return 10;
    case 1: return 7;
    case 2: return 9;
    case 3: return 8;
    case 4: return 0x17;
    }
    return 0;
}

// @ 0x00c22ca0
char cSPCreatureBase::FUN_00c22ca0(int nType)
{
    return FUN_00c0e0c0(0x2c39200);
}

// @ 0x00c22cb0
void cSPCreatureBase::FUN_00c22cb0(uint32_t nVox)
{
    switch (nVox) {
    case 0:
        FUN_00c1d640("vcode_go_eat", 2, 0); return;
    case 3:
        FUN_00c1d640("vsoc_get_tool_rack", 2, 0); return;
    case 7:
    case 8:
    case 10:
    case 0xf:
        FUN_00c1d640("vcode_go_battle", 2, 0); return;
    case 0x29a:
        FUN_00c1d640("vcode_resp_illegal", 2, 0); return;
    case 0x29b:
        if (FUN_00c0bab0() != 0) { FUN_00c1d640("vcode_select_gung_ho", 2, 0); return; }
        if (FUN_00c0ba30() != 0) { FUN_00c1d640("vcode_select_grumble", 2, 0); return; }
        FUN_00c1d640("vcode_select", 2, 0); return;
    case 0x29c:
        FUN_00c1d640("vcode_arrived", 2, 0); return;
    }
    FUN_00c1d640("vcode_go_mot", 2, 0);
}

// @ 0x00c22dd0
int cSPCreatureBase::FUN_00c22dd0()
{
    if ((uint32_t)(mn0x102C - 1) <= 0xa)
        return FUN_00c9cec0(mn0x102C)[0x10 / 4];
    return 0;
}

// @ 0x00c22e30
char __cdecl FUN_00c22e30(cArg22E30* pArg, float fDelta)
{
    if (pArg->mp03C == 0)
        return 0;
    cSPCreatureBase* pCreature = (cSPCreatureBase*)pArg->mp03C->GetByTag(0x4f176642);
    if (pCreature == 0)
        return 0;
    cInteractionTarget* e =
        (cInteractionTarget*)FUN_00cee330((cInteractionAgent*)pCreature);
    cBehaviorStimuliOwner* pStim = pCreature->mpB4C;
    int nEntry = 0;
    if (pStim->mn01DC > 1)
        nEntry = pStim->GetStimulusId();
    if ((e != 0 && e->mnType12C == 5) || pStim->mn01D8 == 0x462855e ||
        nEntry == (int)0xf56bb5b1) {
        pArg->mf000 = g_1581344;
        return 1;
    }
    float fNew = pArg->mf000 - fDelta;
    pArg->mf000 = fNew;
    if (fNew > g_146AA44)
        return 1;
    return 0;
}

// @ 0x00c22ee0
void cSPCreatureBase::FUN_00c22ee0(void* pObj)
{
    void* pOld = mp0x1014;
    if (pObj != pOld) {
        if (pObj != 0)
            ((IRefCounted*)pObj)->AddRef();
        mp0x1014 = pObj;
        if (pOld != 0)
            ((IRefCounted*)pOld)->Release();
    }
    this->vIdx13((int)pObj);
    void* pRet = this->vIdx12();
    void* pOld2 = this->mp0x18;
    if (pRet != pOld2) {
        if (pRet != 0)
            ((IRefCounted*)pRet)->AddRef();
        this->mp0x18 = pRet;
        if (pOld2 != 0)
            ((IRefCounted*)pOld2)->Release();
    }
}

// @ 0x00c22f60
void cInteractionAgent::FUN_00c22f60(void* pArg)
{
    FUN_010829f0(pArg);
    // The owning creature is this base subobject minus sizeof(cGameData).
    cSPCreatureBase* pOwner = (cSPCreatureBase*)((char*)this - sizeof(cGameData));
    cInteractionAgent* pAgent = (cInteractionAgent*)((char*)pOwner + sizeof(cGameData));
    if (FUN_00cee330(pAgent) == 0)
        return;
    cInteractionTarget* e = (cInteractionTarget*)FUN_00cee330(pAgent);
    void* p = (e != 0) ? (void*)e->mSub34 : 0;
    pOwner->FUN_00c15d50(p, 0, 0);
    pAgent->ia30((void*)FUN_00cee330(pAgent));
}

// @ 0x00c22fc0
void cSPCreatureCitizen::SetBundlePlacement(cBundle* pBundle)
{
    if (pBundle == nullptr || mbBundleHidden != 0)
        return;

    Vec3 position;
    Vec3* pOrigin = ((cSpatialObject*)mpSpatialObject)->GetPosition();
    position.mX = pOrigin->mX;
    position.mY = pOrigin->mY;
    position.mZ = pOrigin->mZ;

    Vec3 offset;
    Vec3* pOffset = GetBundlePosition(&offset);
    position.mX = position.mX + pOffset->mX;
    position.mY = pOffset->mY + position.mY;
    position.mZ = pOffset->mZ + position.mZ;

    Vec3 surface;
    cPlanetModel* pPlanet = (cPlanetModel*)PlanetModelGet();
    pPlanet->DirectionToSurfacePosition(&position, &surface);

    Vec3 height;
    cPlanetModel* pPlanet2 = (cPlanetModel*)PlanetModelGet();
    pPlanet2->GetSurfacePoint(&surface, &height, 5.0f);

    Vec3 placement;
    placement.mX = height.mX;
    placement.mY = height.mY;
    placement.mZ = height.mZ;

    pBundle->SetPosition(&placement);
    pBundle->SetRotation(&position);
}

// @ 0x00c23110
Vec3* cSPCreatureCitizen::GetBundlePosition(Vec3* pOut)
{
    if (mbBundleHidden == 0) {
        Vec3* pPosition = ((cSpatialObject*)mpSpatialObject)->GetPosition();
        pOut->mX = pPosition->mX;
        pOut->mY = pPosition->mY;
        pOut->mZ = pPosition->mZ;
        float fOffsetY = mfToolTargetY;
        float fOffsetZ = mfToolTargetZ;
        pOut->mX = pOut->mX + mfToolTargetX;
        pOut->mY = fOffsetY + pOut->mY;
        pOut->mZ = fOffsetZ + pOut->mZ;
        return pOut;
    }

    void* pCreature = GetCreatureChain(this);
    void* pPart = nullptr;
    if (pCreature != nullptr)
        pPart = GetCreatureRoot();
    if (pPart != nullptr) {
        Vec3 orientation;
        GetBundlePosition(pOut);
        pOut->mX = orientation.mX;
        return pOut;
    }

    Vec3* pPosition = ((cSpatialObject*)mpSpatialObject)->GetPosition();
    pOut->mX = pPosition->mX;
    pOut->mY = pPosition->mY;
    pOut->mZ = pPosition->mZ;
    return pOut;
}

// @ 0x00c23200
Vec3* cCreatureBase::GetIdentityColor()
{
    if (mpActiveTool != nullptr)
        return ((cToolOwner*)mpActiveTool)->GetColor();
    if (mpPendingTool != nullptr) {
        Vec3* pColor = (Vec3*)(intptr_t)GetCreatureToolByKey(*(uint32_t*)((uint8_t*)mpPendingTool + 0x234));
        return pColor;
    }
    return (Vec3*)&gDefaultIdentityColor[0];
}

// @ 0x00c23230
void* cCreatureBase::GetToolById(int nToolId)
{
    int nIndex = GetCreatureActionState(&nToolId);
    if (nIndex != -1)
        return *(void**)((uint32_t*)mpToolTable + nIndex);

    if (mpInteractionState != nullptr) {
        void* pSlot = GetCreatureToolSlot((int)(intptr_t)mpInteractionState, 0, 0, 0);
        void* pEntry = *(void**)((uint8_t*)pSlot + 0x24);
        if (pEntry != nullptr && *(int*)((uint8_t*)pEntry + 8) == nToolId)
            return pEntry;
    }
    return nullptr;
}

// @ 0x00c23290
void* cCreatureBase::GetActiveTool()
{
    void* pTool = mpActiveTool;
    if (pTool == nullptr)
        pTool = mpPendingTool;
    return pTool;
}

// @ 0x00c232d0
bool cSPCreatureCitizen::IsLeader()
{
    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr) {
        pTool = (cToolOwner*)mpPendingTool;
        if (pTool == nullptr)
            return false;
    }
    return pTool->GetOwnerCreature() == this;
}

// @ 0x00c23300
void cSPCreatureBase_s00c2_2fc0::PerformSocialAction(int nMode, uint32_t nAnimation)
{
    void* pSpatial = mpSpatialObject;
    int nEffect = (**(int (__stdcall***)(void))(*(uint8_t**)pSpatial + 0xac))();

    if (nEffect == 0 || mbCastedFlag == 0)
        return;

    uint32_t nAnimationGuid = nAnimation;
    if (nAnimation == 0xffffffffu)
        nAnimationGuid = *(uint32_t*)((uint8_t*)&mpToolTable + 0x10);

    void* pParams = nullptr;
    void* pTool = GetCreatureToolSlot((int)(intptr_t)pSpatial, (int)(intptr_t)&pParams, 0, 0);
    if (pTool == nullptr) {
        pTool = FindToolInventoryItem((int)nAnimationGuid, &pParams);
        if (pTool == nullptr)
            return;
    }
    if (*(void**)((uint8_t*)pTool + 0x20) == pSpatial)
        return;
    if (GetCreatureBehaviour((int)(intptr_t)pSpatial) != nullptr)
        return;

    QueueCreatureInteraction((int)(intptr_t)pSpatial, (int)(intptr_t)pParams, 1);
    *(uint32_t*)((uint8_t*)pTool + 8) = 0x5f08f08;
    *(uint32_t*)((uint8_t*)pTool + 4) = 0x1f;

    uint32_t nFlags = 0;
    float fRadius = *(float*)((uint8_t*)&mpSpeciesProfile + 0x10);
    GetCurrentAnimationGUID(&nFlags);
    PreserveAnimation(*(uint32_t*)((uint8_t*)(intptr_t)fRadius + 0x184), nFlags);

    void* pAnimation = pParams;
    PlayCreatureSocialAnimation(5, 0, this, gMaxFloat, &pAnimation, 0);
    (void)nAnimationGuid;

    int nToolState = GetCreatureActionState((void*)(intptr_t)pSpatial);
    if (nToolState != 0) {
        if (*(uint8_t*)((uint8_t*)pTool + 0x18) != 0) {
            *(float*)((uint8_t*)nToolState + 0x18) = 1.0f;
            *(float*)((uint8_t*)nToolState + 0x1c) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x20) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x24) = 0.0f;
        }
        if (GetCreatureType((void*)(intptr_t)pSpatial) != 0) {
            *(float*)((uint8_t*)nToolState + 0x18) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x1c) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x20) = 1.0f;
            *(float*)((uint8_t*)nToolState + 0x24) = 0.0f;
        }
    }
    (void)nMode;
}

// @ 0x00c234a0
void cCreatureBase::SetToolTarget(float fX, float fY, float fZ)
{
    float fScale = *(float*)((uint8_t*)mpIdentityColorSource + 0x74) + 0.2f;
    mfToolTargetX = fX * fScale;
    mfToolTargetY = fY * fScale;
    mbIsCastTarget = 0;
    mfToolTargetZ = fZ * fScale;

    void* pCreature = GetCreatureChain(this);
    if (pCreature != nullptr) {
        void* pTarget = GetCreatureRoot();
        if (pTarget == nullptr)
            PlayToolEffect(0, nullptr, nullptr);
        else
            PlayToolEffect((int)(intptr_t)pTarget, nullptr, nullptr);

        void* pSpatial = mpSpatialObject;
        void* pOwner = GetCreatureChain(this);
        (**(void (__stdcall***)(void*))(*(uint8_t**)pSpatial + 0x30))(pOwner);
    }
}

// @ 0x00c23570
void cCreatureBase::SetCasted(bool bCasted)
{
    mbCastedFlag = bCasted ? 0 : 1;
    if (!bCasted)
        return;

    if (mpInteractionState != nullptr) {
        (**(void (__stdcall***)(void*))(*(uint8_t**)mpInteractionState + 0xa0))(this);
        return;
    }
    if (mbCastedFlag == 0) {
        if (mpIdentityColorSource != nullptr) {
            PlayToolEffect(0, nullptr, nullptr);
            return;
        }
    } else {
        RunCreatureAttackEffect(this);
        if (IsCreatureVisibleInUI(this))
            return;
    }
    cGameNounManager* pNouns = (cGameNounManager*)NounManager();
    pNouns->RemoveNoun(this);
}

// @ 0x00c235e0
int cSPCreatureCitizen::GetToolEffect(uint32_t nToolId)
{
    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr)
        pTool = (cToolOwner*)mpPendingTool;
    if (pTool != nullptr && pTool->GetOwnerCreature() == this) {
        switch (nToolId) {
        case 1:
        case 2:
        case 7:
        case 8:
        case 0xb:
            return 0x11;
        default:
            return 0;
        }
    }

    switch (nToolId) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 0xe;
    case 5:
        return 0xd;
    case 6:
        return 0xf;
    case 7:
        return 0x10;
    case 8:
        return 4;
    case 9:
        return 0x12;
    case 0xb:
        return 0x11;
    default:
        return 0;
    }
}

// @ 0x00c236e0
bool cSPCreatureCitizen::HasSpecializedTool(int nToolId)
{
    if (nToolId == 0)
        return true;

    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr)
        pTool = (cToolOwner*)mpPendingTool;
    if (pTool != nullptr && pTool->GetOwnerCreature() == this) {
        switch (nToolId) {
        case 1:
        case 2:
        case 7:
        case 8:
        case 0xb:
            return true;
        default:
            break;
        }
    }
    return *(int*)((uint8_t*)&mpToolTable + 0x08) == nToolId;
}

// @ 0x00c23750
uint32_t GetCreatureToolInteraction()
{
    uint32_t* pInteraction = (uint32_t*)GetCreatureBehaviour(0);
    if (pInteraction == nullptr)
        return 0;

    switch (*pInteraction) {
    case 7: {
        void* pCitizen = (void*)GetLeaderOfCommunity();
        if (pCitizen != nullptr) {
            int* pOwner = *(int**)((uint8_t*)pCitizen + 0x1014);
            if (pOwner != nullptr) {
                Vec3* pToolPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pOwner + 0x48))->GetPosition();
                Vec3* pOwnerPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pCitizen + 0xc0))->GetPosition();
                float fRange = (**(float (__stdcall***)(void))(*(uint8_t**)pOwner + 0x60))();
                float fDx = pOwnerPos->mX - pToolPos->mX;
                float fDy = pOwnerPos->mY - pToolPos->mY;
                float fDz = pOwnerPos->mZ - pToolPos->mZ;
                if (fDz * fDz + (fDx * fDx + fDy * fDy) < fRange * fRange)
                    return 0xad1a17du;
            }
        }
        return 0;
    }
    case 8:
        return 0x460fe7c5u;
    case 9:
    case 0x15:
        return 0xf72dd75du;
    case 0xf:
        return 0xad1a17du;
    default:
        return 0;
    }
}

// @ 0x00c238b0
void UpdateCreatureToolInteractions(void* pManager)
{
    uint32_t* pState = (uint32_t*)pManager;
    uint8_t bCasted = 0;
    (void)bCasted;

    uint8_t* pOwner = (uint8_t*)*(uint32_t*)((uint8_t*)pState + 0xc0);
    uint8_t bOwnerFlag = (**(uint8_t (__stdcall***)(void))(pOwner + 0x58))();

    uint32_t* pBegin = *(uint32_t**)((uint8_t*)pState + 0x338);
    uint32_t* pEnd = *(uint32_t**)((uint8_t*)pState + 0x33c);
    void* pSelf = (void*)GetCreatureToolSlot(0, 0, 0, 0);
    (void)pSelf;

    for (; pBegin != pEnd; ++pBegin) {
        uint8_t* pEntry = (uint8_t*)*pBegin;
        if (pEntry == nullptr)
            continue;

        uint8_t* pTool = (uint8_t*)(**(intptr_t (__stdcall***)(uint32_t))(*(uint8_t**)pEntry + 0xb8))(0x17f243b);
        if (*(uint8_t*)(pEntry + 0x75) == 0)
            continue;

        int nToolKind = (**(int (__stdcall***)(void))(pTool + 0x2c))();
        if (nToolKind != 0)
            continue;

        intptr_t nKind = (**(intptr_t (__stdcall***)(void))(pTool + 0x20))();
        if (nKind == 1) {
            if (*(uint8_t*)((uint8_t*)pTool + 0xb5e) != 1)
                continue;
            void* pEffect = CreateInteractionEffect(0x400000, 0, 10.0f, pTool);
            if (pEffect == nullptr)
                continue;
            Vec3* pPosition = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pTool + 0xc0))->GetPosition();
            *(float*)((uint8_t*)pEffect + 0x0c) = pPosition->mX;
            *(float*)((uint8_t*)pEffect + 0x10) = pPosition->mY;
            *(float*)((uint8_t*)pEffect + 0x14) = pPosition->mZ;
            continue;
        }

        if (nKind != 2)
            continue;

        if (*(uint8_t*)((uint8_t*)pTool + 0xb5e) != 0) {
            void* pTarget = GetCreatureSocialTarget(*(void**)((uint8_t*)pState + 0x1014));
            Vec3* pToolPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)(pTool + 0x30))->GetPosition();
            Vec3* pTargetPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pTarget + 0x34))->GetPosition();
            float fToolRange = (**(float (__stdcall***)(void))(*(uint8_t**)(pTool + 0x30) + 0x74))();
            float fTargetRange = (**(float (__stdcall***)(void))(*(uint8_t**)((uint8_t*)pTarget + 0x34) + 0x74))();
            float fRange = fToolRange + fTargetRange;
            float fDx = pTargetPos->mX - pToolPos->mX;
            float fDy = pTargetPos->mY - pToolPos->mY;
            float fDz = pTargetPos->mZ - pToolPos->mZ;
            if (fRange * fRange <= fDz * fDz + (fDx * fDx + fDy * fDy)) {
                void* pEffect = CreateInteractionEffect(0x400000, 0, 10.0f, pTool);
                if (pEffect != nullptr) {
                    Vec3* pPosition = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)(pTool + 0x30))->GetPosition();
                    *(float*)((uint8_t*)pEffect + 0x0c) = pPosition->mX;
                    *(float*)((uint8_t*)pEffect + 0x10) = pPosition->mY;
                    *(float*)((uint8_t*)pEffect + 0x14) = pPosition->mZ;
                }
            }
            continue;
        }

        if (bOwnerFlag != 0)
            continue;
        if (IsCreatureLeader((void*)pTool))
            continue;
        void* pToolOwner = pTool;
        ((IRefCounted_s00c2_2fc0*)pToolOwner)->v10();
        if ((int)(intptr_t)pToolOwner == (int)(intptr_t)pSelf)
            continue;
        int nRelation = CompareCreatureTraits(pSelf, pTool, 1);
        if (nRelation == -1)
            continue;
        cTimerOwner* pOwner2 = (cTimerOwner*)((uint8_t*)pState + 0xc0);
        float fDistance = (float)GetCreatureActionState(pOwner2);
        bool bUsable = IsToolUsable(pTool, 1.0f, fDistance);
        if (!bUsable)
            bUsable = IsToolUsable(pState, 1.0f, fDistance);
        if (!bUsable)
            continue;
        (void)nRelation;
        if (nRelation < 2) {
            uint64_t nElapsed = cSPTimerGetElapsedTime(&pOwner2->mSocialTimer);
            if ((int)(nElapsed >> 32) != 0 || (uint32_t)nElapsed > 20000)
                CreateInteractionEffect(0, 0x1000, 10.0f, pTool);
            int nSlot = (int)(intptr_t)GetCreatureToolSlot(0, 2, 0, 0);
            if (nSlot == -1) {
                nSlot = (int)(intptr_t)GetCreatureToolSlot(1, 2, 0, 0);
                if (nSlot == -1)
                    CreateInteractionEffect(0, 0x2000, 10.0f, pTool);
            }
        } else if (nRelation < 5) {
            uint64_t nElapsed = cSPTimerGetElapsedTime(&pOwner2->mSocialTimer);
            if ((int)(nElapsed >> 32) != 0 || (uint32_t)nElapsed > 20000)
                CreateInteractionEffect(0, 0x1000, 10.0f, pTool);
        }
    }
}

// @ 0x00c23cf0
float cCreatureBase::CalculateScale()
{
    float fScale = GetRandomFloat(0.0f, 1.0f);
    if (mpIdentityColorSource != nullptr || mpSpeciesProfile == nullptr)
        return fScale;

    fScale = GetCreatorScaleModifier(mpSpeciesProfile) * fScale;
    if (IsCitizenLeader(this)) {
        if (IsCreatureLeader(this))
            fScale = gLeaderScaleBonus * fScale;
        else
            fScale = GetRandomFloat(gFollowerScaleBonus, gLeaderScaleBonus) * fScale;
    }
    int nBrainLevel = GetCreatureActionState(this);
    fScale = ApplyCreatureScale(nBrainLevel, fScale);
    return fScale * GetCreatureObjectScale(this);
}

// @ 0x00c23da0
bool cSPCreatureCitizen::IsBefriended()
{
    bool bBefriended = false;
    uint8_t bFlag = (**(uint8_t (__stdcall***)(void))((uint8_t*)this + 0xd0))();
    if (bFlag == 0) {
        void* pCreature = GetCreatureRoot();
        if (pCreature != nullptr) {
            int nRelation = GetCreatureSocialRelation((void*)((uint8_t*)this + 0xd0), nullptr, 0);
            bBefriended = nRelation == 6;
        }
    } else if (*(int*)((uint8_t*)&mpToolTable + 0x18) != 0) {
        cGameNounManager* pNouns = (cGameNounManager*)NounManager();
        int* pTribe = (int*)pNouns->GetPlayerTribe();
        void* pOther = *(void**)((uint8_t*)&mpToolTable + 0x18);
        int nRelation = GetCreatureSocialRelation(pOther, pTribe, 1);
        bBefriended = nRelation == 4;
    }

    if (((*(uint32_t*)((uint8_t*)this + 0xb60) >> 7) & 1) == 0 && !bBefriended)
        return false;
    return true;
}

// @ 0x00c23e90
char cCreatureBase::ApplyAttack(void* pTarget, void* pAttack, void* pContext)
{
    float fDamage = GetRandomFloat(0.0f, 1.0f);
    char bApplied = ApplyAttackEffect(pTarget, pAttack, pContext);
    if (bApplied == 0 || fDamage <= 0.0f)
        return bApplied;

    if (GetCurrentGameMode() != &gCreatureToolContext)
        return bApplied;
    if (!(**(uint8_t (__stdcall***)(void))((uint8_t*)this + 0x58))())
        return bApplied;
    if (pTarget == nullptr)
        return bApplied;

    int nKey = (**(int (__stdcall***)(uint32_t))(*(uint8_t**)pTarget + 0x5c))(0xce9f6639);
    if (nKey == 0)
        return bApplied;
    if (GetCreatureType(pTarget) == 0)
        return bApplied;

    Vec3 offset;
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = 0.0f;
    uint32_t nEffect = (uint32_t)(intptr_t)GetCreatureChain((void*)&offset);
    RunCreatureAttackEffect((void*)(intptr_t)nEffect);
    ReportInteraction(0x7ae0330du, (void*)(intptr_t)nEffect);
    return bApplied;
}

// @ 0x00c23f80
u32 cCreatureBase_s00c2_3f80::FUN_00c23f80(u32 param_2, u32 param_3, u32 param_4, u32 param_5)
{
    u32 slot = 0;
    void* s = MOPS(this)->FUN_00c0f9b0(param_4, &slot);
    if (s)
    {
        *(u32*)((u8*)s + 0x10) = param_3;
        *(u32*)((u8*)s + 0x04) = param_2;
        if (param_5)
        {
            *(u32*)((u8*)s + 0x08) = param_5;
            void* animWorld = mpAnimWorld_b54;
            u32 guid = 0;
            u32 ret = MOPS(this)->FUN_00c0e040(&guid);
            FUN_009ff7c0(*(u32*)((u8*)animWorld + 0x184), ret);
            struct { u32 a, b, c; u32 pad[5]; } msg;
            msg.a = slot;
            msg.b = guid;
            msg.c = 0;
            MOPS(mpOrderMgr_b48)->FUN_00bca810(5, 0, this, gF_0146aa40, &msg, 0);
        }
    }
    return (u32)s;
}

// @ 0x00c24040
void cCreatureBase_s00c2_3f80::FUN_00c24040(u32 param_2)
{
    u32 slot = 0;
    void* s = MOPS(this)->FUN_00c0f9b0(param_2, &slot);
    if (!s)
        return;
    u8* base = (u8*)mpOrderMgr_b48;
    u32 i = 0;
    while (i < 8)
    {
        u8* e = base + i * 0x44;
        if (*(u32*)(e + 0x24) == 5 && *(u32*)(e + 0x28) == 0 && *(u32*)e == slot)
        {
            FUN_00bca040(*(u16*)(e + 0x20) | (i << 0x10));
            break;
        }
        i++;
    }
    void* obj = *(void**)((u8*)s + 0x20);
    u32 r = 0;
    if (obj)
    {
        r = (u32)((void* (__thiscall*)(void*, u32))VT(obj)[0xb8 / 4])(obj, 0x4ffcdeda);
        if (r)
            ((void (__thiscall*)(void*))VT(r)[0])((void*)r);
    }
    MOPS(this)->FUN_00c15bd0(slot, 0, 0);
    if (r)
    {
        void* out = FUN_00b3d2b0();
        MOPS(out)->FUN_00ac79d0();
        MOPS(FUN_00b3d2b0())->FUN_00ac7de0((void*)r);
        ((void (__thiscall*)(void*))VT(r)[1])((void*)r);
    }
}

// @ 0x00c24110
void FUN_00c24110(cCreatureBase_s00c2_3f80* param_1)
{
    if (param_1->mpField1014 != 0)
    {
        u32 n = (u32)MOPS(param_1)->FUN_00c0f4f0();
        if (n == 0)
            return;
        u32 idx = param_1->mField24 % n;
        u8* tbl = (u8*)param_1->mpNeighbor_e40;
        u32 e0 = *(u32*)(tbl + idx * 0x24);
        u8 key = *(u8*)(tbl + idx * 0x24 + 0x18);
        param_1->mFieldfc4 = e0;
        u32 j = (idx + 1) % n;
        param_1->mFieldfc8 = *(u32*)(tbl + j * 0x24);
        while (j != idx)
        {
            if (key != *(u8*)(tbl + j * 0x24 + 0x18))
            {
                param_1->mFieldfc8 = *(u32*)(tbl + j * 0x24);
                return;
            }
            j = (j + 1) % n;
        }
        return;
    }
    {
        u32* v = (u32*)FUN_004d9050(param_1->mpAnimWorld_b54);
        if (((v[1] - v[0]) >> 2) > 0)
        {
            struct { u32 len, key, b, c; } local;
            local.len = 8;
            local.key = 0x70737267;
            local.b = 0;
            local.c = 0;
            u32 out = 0xffffffff;
            u32* p = (u32*)((u8*)param_1->mpAnimWorld_b54 + 0x17c);
            u32 r = FUN_009b2340(&out, 1, *(u32*)*p, &local.key, 0, 0);
            if (r && out != 0xffffffff)
                param_1->mFieldfc4 = out;
            return;
        }
        u32* w = (u32*)FUN_004d9030(param_1->mpAnimWorld_b54);
        if (((w[1] - w[0]) >> 2) > 0)
        {
            u32* p = (u32*)FUN_004d9030(param_1->mpAnimWorld_b54);
            u32 val = *(u32*)*p;
            if (val != 0xffffffff)
                param_1->mFieldfc4 = val;
        }
    }
}

// @ 0x00c24280
void FUN_00c24280(cCreatureBase_s00c2_3f80* self)
{
    if (!self)
        return;
    u32 id = (u32)((void* (__thiscall*)(void*))VT(self)[0x20 / 4])(self);
    if (id == 0x18eb4b7)
        FUN_00c24110(self);
}

// @ 0x00c242b0
void cCreatureBase_s00c2_3f80::FUN_00c242b0(u32 param_2)
{
    MOPS(this)->FUN_00c1c9f0(param_2);
    if ((u8)param_2 != 0)
        return;
    mFieldff0 = 0;
    mField102c = 0;
    mFieldfc0 = 3;
    mFieldff4 = 0xffffffff;
    mFieldff8 = 0xffffffff;
    mFieldffc = 0;
    mField1000 = 0;
    mField1002 = 1;
    mField1004 = gU_0168dbb0;
    mField1008 = gU_0168dbb4;
    mField100c = gU_0168dbb8;
    MOPS((u8*)this + 0xfd0)->FUN_00bc3110();
    u32 noun = *(u32*)((u8*)this + 0x1030);
    if (noun)
        MOPS(FUN_00b3d300())->FUN_00b225d0((void*)noun);
    u32 noun2 = *(u32*)((u8*)this + 0x1030);
    if (noun2)
    {
        *(u32*)((u8*)this + 0x1030) = 0;
        ((void (__thiscall*)(void*))VT((void*)noun2)[1])((void*)noun2);
    }
    mFieldbbc = gF_01687a00;
    MOPS(this)->FUN_00c0ba10();
}

// @ 0x00c24380
void FUN_00c24380(cCreatureBase_s00c2_3f80* self, void* item)
{
    MOPS(self)->FUN_00c0d340((u32)item);
    void* sub = (u8*)self - 0x34;
    void* cur = (void*)((void* (__thiscall*)(void*))VT(sub)[0x30 / 4])(sub);
    void* old = self->mpObj58;
    if (cur != old)
    {
        if (cur)
            ((void (__thiscall*)(void*))VT(cur)[0])(cur);
        self->mpObj58 = cur;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
    MOPS(sub)->FUN_00c23300((u32)item, 0xffffffff);
    if (*(u32*)((u8*)item + 0x12c) == 5)
        MOPS(self->mpFieldb14)->FUN_00bca810(0, 2, sub, gF_0146aa40, 0, 0);
}

// @ 0x00c24400
void* cCreatureBase_s00c2_3f80::FUN_00c24400(u32 id)
{
    if (id == 0x4f176642)
        return this;
    if (id == 0xef3da0d7 && mpField1014)
        return this;
    return (void*)MOPS(this)->FUN_00c0b670(id);
}

// @ 0x00c24430
u8 cCreatureBase_s00c2_3f80::FUN_00c24430()
{
    if (mpFieldf50)
    {
        void* p = (u8*)mpFieldf50 + 0x120;
        return ((u8 (__thiscall*)(void*))VT(p)[0x58 / 4])(p) ? 1 : 0;
    }
    if (mpFieldf54)
    {
        void* p = (u8*)mpFieldf54 + 0x120;
        if (((u8 (__thiscall*)(void*))VT(p)[0x58 / 4])(p))
            return 1;
    }
    return 0;
}

// @ 0x00c24480
i32 cCreatureBase_s00c2_3f80::FUN_00c24480()
{
    if (!mpField1014)
        return 0;
    f32 t = (f32)(MOPS((u8*)this + 0x5a8)->FUN_00bfc490() * (f64)gF_013ec4d0);
    f32* cmp;
    if (t <= mNoAttackTimer)
        cmp = &mNoAttackTimer;
    else
        cmp = &t;
    f32 v = *cmp;
    i32 id = *(i32*)((u8*)mpFieldb4c + 0x1d8);
    u8 b = (u8)(id == 0x5218bb3 || id == 0x462854e);
    i32 state;
    if (mFieldb5e != 0 || b)
        state = 0;
    else if (v > gF_01687a0c)
        state = 1;
    else if (v > gF_01687a10)
        state = (mNoAttackTimer <= t) ? 2 : 4;
    else
        state = (mNoAttackTimer <= t) ? 3 : 5;
    if (state != mLastMotiveState)
    {
        mLastMotiveState = state;
        mFieldb61 = 1;
    }
    return mLastMotiveState;
}

// @ 0x00c24560
bool cCreatureBase_s00c2_3f80::FUN_00c24560()
{
    if (mpField1014 && mpFieldb4c && *(u32*)mpFieldb4c)
    {
        if (!MOPS(this)->FUN_00c0b770())
            return true;
        void* a = MOPS(mpFieldb4c)->FUN_00bca2c0();
        void* b = (void*)((void* (__thiscall*)(void*))VT((u8*)this + 0x58)[0x20 / 4])((u8*)this + 0x58);
        if (a || b)
            return false;
        return true;
    }
    bool r = false;
    void* p = (void*)((void* (__thiscall*)(void*))VT((u8*)this + 0x58)[0x20 / 4])((u8*)this + 0x58);
    if (p == 0)
        r = true;
    else if (*(u32*)((u8*)p + 0x68) == 1)
    {
        if (!MOPS(this)->FUN_00c0ba70())
            r = true;
    }
    return r;
}

// @ 0x00c245e0
u32 cCreatureBase_s00c2_3f80::FUN_00c245e0(u32 a1, u32 a2, f32 a3, u32 a4, u32 a5, u32 a6)
{
    if (!mpField1014 || !mpFieldb4c || !*(u32*)mpFieldb4c)
        return 0;
    MOPS(this)->FUN_00c0bf10(a1, a2, 0x1d3fbffa, 0x81240a0, a3, 1, 0, a4, a5, a6, 1);
    void* p = MOPS((u8*)mpFieldb4c + 8)->FUN_00bc96a0(1, 0);
    if (p)
        *(u32*)((u8*)p + 0xc) = 1;
    void* q = MOPS((u8*)mpFieldb4c + 8)->FUN_00bc96a0(a1, a2);
    *(u32*)((u8*)q + 0x14) = 0;
    return (u32)q;
}

// @ 0x00c24680
u32 cCreatureBase_s00c2_3f80::FUN_00c24680(u32 a1, u32 a2, f32 a3, u32 a4, void* a5, u32 a6)
{
    if (mpField1014 && mpFieldb4c && *(u32*)mpFieldb4c)
    {
        u32 v;
        if (a5)
            v = (u32)((void* (__thiscall*)(void*, u32))VT(a5)[4 / 4])(a5, 0xee3f516e);
        else
            v = 0;
        FUN_00c245e0(a1, a2, a3, a6, a4, v);
        return 0;
    }
    return MOPS((u8*)this + 0x58)->FUN_00abf760(a4, a5, a6);
}

// @ 0x00c24700
void cCreatureBase_s00c2_3f80::FUN_00c24700(u32 a1, u32 a2, u32 a3)
{
    if (mFieldfbc && mpFieldaf4 && *(u32*)mpFieldaf4)
    {
        ((cCreatureBase_s00c2_3f80*)((u8*)this - 0x58))->FUN_00c24680(2, 0, gF_0146aa40, a1, (void*)a2, a3);
        return;
    }
    MOPS(this)->FUN_00abf760(a1, (void*)a2, a3);
}

// @ 0x00c24750
i32 cCreatureBase_s00c2_3f80::FUN_00c24750()
{
    return (mField1010 != 0) + 5;
}

// @ 0x00c24760
void cCreatureBase_s00c2_3f80::FUN_00c24760()
{
    MOPS(this)->FUN_00c22240();
    void* tribe = mpField1014;
    if (!tribe)
        goto END;
    {
        MOPS(tribe)->FUN_00c95cc0(this);
        void* sub = (u8*)this + 0xc0;
        if (((u8 (__thiscall*)(void*))VT(sub)[0x58 / 4])(sub))
        {
            ((void (__thiscall*)(void*, u32))VT(this)[0xe4 / 4])(this, 0x1572074);
        }
        else
        {
            u32 v = (u32)FUN_00b6f0c0(*(u32*)((u8*)tribe + 0x234));
            ((void (__thiscall*)(void*, u32))VT(this)[0xe4 / 4])(this, v);
        }
        void* strat = FUN_00cd40b0();
        void* r = (void*)((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
        if (r)
        {
            strat = FUN_00cd40b0();
            r = (void*)((void* (__thiscall*)(void*, void*))VT(strat)[0x6c / 4])(strat, this);
            MOPS(r)->FUN_00ccc400();
        }
        sub = (u8*)this + 0xc0;
        if (((u8 (__thiscall*)(void*))VT(sub)[0x58 / 4])(sub))
        {
            *(void**)((u8*)gP_0169b41c + 0x14) = this;
            u32 pop = MOPS(tribe)->FUN_00c8f370();
            *(u32*)((u8*)gP_0169b41c + 0xc) = pop;
            void* r3 = (void*)((void* (__thiscall*)(void*, u32, u32))VT((u8*)tribe + 0x120)[0x2c / 4])((u8*)tribe + 0x120, 0, 1);
            MOPS(FUN_00b3d3e0())->FUN_00dd8640(0x11c9ad29, 0x182cd6ce, r3);
        }
        MOPS((u8*)mpFieldb4c + 8)->FUN_00bc97f0(0, 0x200, gF_01486110, 0);
    }
END:
    {
        void* sub = (u8*)this + 0x58;
        ((void (__thiscall*)(void*))VT(sub)[0x34 / 4])(sub);
    }
    *(u32*)((u8*)mpFieldb4c + 0x5fc) |= 2;
    u32 noun = *(u32*)((u8*)this + 0x1030);
    if (noun)
        MOPS(FUN_00b3d300())->FUN_00b225d0((void*)noun);
    u32 noun2 = *(u32*)((u8*)this + 0x1030);
    if (noun2)
    {
        *(u32*)((u8*)this + 0x1030) = 0;
        ((void (__thiscall*)(void*))VT((void*)noun2)[1])((void*)noun2);
    }
    MOPS(this)->FUN_00c1d400(0x3a616fee, 0x715fb4a7);
}

// @ 0x00c248d0
void cCreatureBase_s00c2_3f80::FUN_00c248d0(i32 param_2)
{
    if (!mField135)
        return;
    if (((u8 (__thiscall*)(void*))VT(this)[0x2c / 4])(this))
        return;
    f32 fdt = (f32)param_2;
    if (param_2 < 0)
        fdt = fdt + gF_013f4fd0;
    fdt = fdt * gF_013f9428;
    f32 saved = fdt;
    ((void (__thiscall*)(void*, f32))VT(this)[0x70 / 4])(this, fdt);
    f32 fvar;
    if (MOPS(this)->FUN_00c0c130())
        fvar = 0.0f;
    else
        fvar = MOPS(this)->FUN_00c0c070();
    mFieldb80 = fvar;
    if (mpFieldb4c && *(u32*)mpFieldb4c && !mField1010)
    {
        if (!mFieldb5e)
            MOPS(this)->FUN_00c17de0(saved);
        u32 flags = *(u32*)((u8*)mpFieldb4c + 0x5fc);
        u32 a = (u32)MOPS(this)->FUN_00cee330();
        u32 b = (u32)MOPS(mpFieldb4c)->FUN_00bca2c0();
        flags |= (a ? 4 : 0);
        flags |= ((mFlags110 & 0x100) ? 0 : 8);
        flags |= (b ? 0x40 : 0);
        if (mFieldeac == 0) flags |= 0x400;
        else if (mFieldeac == 1) flags |= 0x800;
        else if (mFieldeac == 2) flags |= 0x1000;
        u32 v = (u32)MOPS((u8*)mpFieldb4c + 8)->FUN_00bc9980(saved);
        MOPS(FUN_00b3d380())->FUN_00b316c0();
        void* pw = (u8*)mpFieldb4c;
        MOPS(this)->FUN_00d995f0(saved, 0.0, *(u32*)pw, this, (void*)((u8*)pw + 0x1d0),
                                 *(u32*)((u8*)pw + 0x5e8), flags, v);
        if (!mFieldb5e)
        {
            if (MOPS(this)->FUN_00c0e420())
            {
                if (mpAnimWorld_b54)
                {
                    if (MOPS(mpAnimWorld_b54)->FUN_00a02ba0() <= 0)
                        MOPS(this)->FUN_00c14750(0);
                }
            }
        }
    }
    if (!mFieldb5e)
    {
        ((void (__thiscall*)(void*, f32))VT(this)[0x64 / 4])(this, fdt);
        ((void (__thiscall*)(void*, f32))VT(this)[0x68 / 4])(this, fdt);
    }
    if (mField2b0 == 3 && !(mFlags110 & 0x1000) && mField137)
        ((void (__thiscall*)(void*))VT(this)[0x58 / 4])(this);
    if (mpField1030)
    {
        f32 d = gF_0143ee00;
        if (FUN_00b3d280())
        {
            struct { f32 a, b, c, d; } q;
            MOPS(FUN_00b3d280())->FUN_00b137d0(&q);
            f32* p = (f32*)((void* (__thiscall*)(void*))VT((u8*)mpField1030 + 0x70)[0x2c / 4])((u8*)mpField1030 + 0x70);
            f32 dx = p[0] - q.a;
            f32 dy = p[1] - q.b;
            f32 dz = p[2] - q.c;
            f32 dist = dx*dx + dy*dy + dz*dz;
            f32 sel = (dist > gF_0143ee00) ? d : dist;
            f32 cur = (f32)((f64 (__thiscall*)(void*))VT((u8*)this + 0xc0)[0x70 / 4])((u8*)this + 0xc0);
            f32 v2 = (sel * gF_0146aaf0) * (gF_01470f1c - cur) + cur;
            u32 e = (u32)((void* (__thiscall*)(void*, f32))VT((u8*)this + 0xc0)[0x2c / 4])((u8*)this + 0xc0, v2);
            MOPS(mpField1030)->FUN_00c3f160(e);
        }
    }
    MOPS(this)->FUN_00c213d0((u32)param_2);
    if (!mField1010 && mpAnimWorld_b54)
        *(u32*)((u8*)mpAnimWorld_b54 + 0x14c) = 0;
}

// @ 0x00c24c50
i32 cCreatureBase_s00c2_3f80::FUN_00c24c50()
{
    i32 n = mField102c - 1;
    i32 c = 0;
    switch (n)
    {
    case 0: case 1: case 2: case 3: case 4: case 5:
        c = 2; break;
    case 8: case 10:
        c = 1; break;
    default: break;
    }
    void* community = mField1010;
    if (!community)
        community = mpField1014;
    if (community)
    {
        bool leader = (MOPS(community)->FUN_00c00650() == (void*)this);
        if (leader)
            c += 6;
    }
    void* prof = mpFieldb20;
    u32* v = (u32*)((u8*)prof + 0x6d4);
    i32 vec = ((i32)v[1] - (i32)v[0]) >> 2;
    return vec + c;
}

// @ 0x00c24ce0
void* cCreatureBase_s00c2_3f80::FUN_00c24ce0(u32 param_2)
{
    if (param_2 == 0xffffffff)
        return 0;
    void* prof = mpFieldb20;
    u32 n = (u32)((*(u32*)((u8*)prof + 0x6d8) - *(u32*)((u8*)prof + 0x6d4)) >> 2);
    if (param_2 < n)
        return *(void**)(*(u32*)((u8*)prof + 0x6d4) + param_2 * 4);
    u32 i = param_2 - n;
    if (i == 0)
    {
        void* r = FUN_00c9cec0(mField102c);
        return *(void**)((u8*)r + 0x24);
    }
    if (MOPS(this)->FUN_00c232d0())
    {
        if (i - 1 < 6)
        {
            void* r = FUN_00d1e660();
            return *(void**)((u8*)r + 0x1c + (i - 1) * 4);
        }
        return 0;
    }
    if (i != 1)
        return 0;
    switch (mField102c - 1)
    {
    case 0: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x34); }
    case 1: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x38); }
    case 2: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x3c); }
    case 3: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x40); }
    case 4: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x44); }
    case 5: { void* r = FUN_00d1e660(); return *(void**)((u8*)r + 0x48); }
    default: return 0;
    }
}

// @ 0x00c24df0
f64 cCreatureBase_s00c2_3f80::FUN_00c24df0()
{
    f32 scale = gF_01485720;
    cCreatureBase_s00c2_3f80* self = (cCreatureBase_s00c2_3f80*)((u8*)this - 0x5a8);
    if (!MOPS(self)->FUN_00c0b770())
        scale = gF_0150c888;
    if (mFielda6c != 0)
    {
        void* community = self->mField1010;
        if (!community)
            community = self->mpField1014;
        if (community)
        {
            bool leader = (MOPS(community)->FUN_00c00650() == (void*)self);
            if (leader)
                scale = gF_0158121c * scale;
        }
    }
    f32 base = (f32)((f64 (__thiscall*)(void*))VT(self)[0x7c / 4])(self);
    return (f64)base * (f64)scale;
}

// @ 0x00c25f80
void cSPCreatureCitizen_s00c2_5a50::FUN_00c25f80()
{
    void* pBT = mpBT_fc4;
    if (pBT == 0)
        return;
    FUN_00c24040(pBT);
    FUN_00c15150(pBT, 1);
    if (pBT == mpBT_fc4)
        mnCurTool_ffc = 0;
}

// @ 0x00c26120
i32_s00c2_5a50 cSPCreatureCitizen_s00c2_5a50::FUN_00c26120()
{
    i32_s00c2_5a50 tool = mnToolEffectIndex;
    if (tool != 0)
        return GetToolEffect((u32)tool);
    cCommunity* pComm = (cCommunity*)mpOwnerCity_1010;
    if (pComm == 0)
        pComm = (cCommunity*)mpOwnerTribe_1014;
    if (pComm != 0 && pComm->GetLeader() == this)
        return 0x11;
    return 0;
}

// @ 0x00c26170
i32_s00c2_5a50 cSPCreatureCitizen_s00c2_5a50::FUN_00c26170()
{
    cOrder* pOrder = (cOrder*)mpOrders_b4c->FirstPending();
    if (pOrder == 0)
        return mnCurTool_ffc;
    switch (pOrder->mType_00) {
    case 1:
        return IsLeader() ? 0x11 : 4;
    case 2:
        return IsLeader() ? 0x11 : 0x10;
    case 4:
    case4_ret:
        return FUN_00c26120();
    case 5:
        if (mnToolEffectIndex == 9)
            return 0x12;
        /* fall through */
    case 3:
    case 6:
    case 0x1c:
        return mnCurTool_ffc;
    case 7:
    case 10:
    case 0xf:
        if (IsLeader())
            return 0x11;
        if (FUN_00c22dd0() == 1)
            goto case4_ret;
        if (mnToolEffectIndex == 9)
            return 0x12;
        break;
    case 0x19:
        return 0x0c;
    case 0x1a:
        if (IsLeader())
            return 0x11;
        if (FUN_00c22dd0() == 2)
            goto case4_ret;
        break;
    case 0x16:
        return 0x11;
    case 0x18:
        {
            cConstObj* pObj = (cConstObj*)FUN_00cee330(&mSub_034);
            f32 a = pObj->FUN_00bfc490();
            f32 b = ((cConstObj*)0x1581208)->FUN_0104bdb0();
            return (a < b) ? 0 : 0x13;
        }
    default:
        break;
    }
    return 0;
}

// @ 0x00c26310
void cSPCreatureCitizen_s00c2_5a50::FUN_00c26310(void* pTree)
{
    i32_s00c2_5a50 eff;
    if (mnToolEffectIndex != 0) {
        eff = GetToolEffect((u32)mnToolEffectIndex);
    } else {
        cCommunity* pComm = (cCommunity*)mpOwnerCity_1010;
        if (pComm == 0)
            pComm = (cCommunity*)mpOwnerTribe_1014;
        if (pComm != 0 && pComm->GetLeader() == this)
            eff = 0x11;
        else
            eff = 0;
    }
    if (pTree != mpBT_fc4 || eff != mnCurTool_ffc)
        SetCurrentToolEffect(eff, (u32)pTree);
}

// @ 0x00c26380
bool cSPCreatureCitizen_s00c2_5a50::IsWaitingForTool(i32_s00c2_5a50 nTool)
{
    i32_s00c2_5a50 cur = mnCurTool_ffc;
    if (cur != GetToolEffect((u32)nTool)) {
        if (HasSpecializedTool(nTool) || mnCurTool_ffc != 0) {
            InterruptAnimation(0x2c39200, (i32_s00c2_5a50)(intptr_t)mpBT_fc4, 0);
            return true;
        }
    }
    return false;
}

// @ 0x00c263e0
void cSPCreatureCitizen_s00c2_5a50::SetToolOnAnimEvent(i32_s00c2_5a50 nTool)
{
    i32_s00c2_5a50 tool = nTool;
    if (!HasSpecializedTool(tool))
        tool = 0;
    i32_s00c2_5a50 eff = GetToolEffect((u32)tool);
    if (mnCurTool_ffc != eff) {
        if ((i32_s00c2_5a50)(intptr_t)GetCurrentAnimationGUID() == 0x2c39200) {
            nTool = -1;
            if (WaitForAnimEventOrEnd((u32)(intptr_t)DAT_01572068, &nTool, 0xffffffff, 0, 1))
                SetCurrentToolEffect(eff, (u32)nTool);
        }
    }
}

// @ 0x00c26450
void cSPCreatureCitizen_s00c2_5a50::FUN_00c26450()
{
    if (mpOwnerTribe_1014 == 0)
        return;
    cOrder* pOrder = (cOrder*)mpOrders_b4c->FirstPending();
    if (pOrder == 0)
        return;
    if (pOrder->mn_28 == 0 && pOrder->mb_38 != 0) {
        mpOrders_b4c->mPlay_08.FUN_00bc97f0(0x4000, 0, DAT_0146aa40, 0);
        return;
    }
    u32 anim = 0, flags = 0, extra = 0;
    switch (pOrder->mType_00) {
    case 0:  anim = 8; break;
    case 1:  anim = 0x10; extra = DAT_0169ef30; break;
    case 2:  anim = 0x20; break;
    case 3:  anim = 0x40; break;
    case 4:  anim = 0x80; break;
    case 5:  anim = 0x100; break;
    case 6:  anim = 0x200; break;
    case 7:  anim = 0x400; break;
    case 8:  anim = 0x800; break;
    case 9:  anim = 0x2000; break;
    case 10: anim = 0x8000; break;
    case 0xb: anim = 0x20000; break;
    case 0xc: anim = 0x40000; extra = DAT_0169f028; break;
    case 0xd: anim = 0x80000; break;
    case 0xe: anim = 0x100000; break;
    case 0xf: anim = 0x200000; break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x17: anim = 0; flags = 0x8000000; break;
    case 0x14: anim = 0x8000000; break;
    case 0x15: anim = 0x1000; break;
    case 0x16: anim = 0x10000000; break;
    case 0x18: anim = 0x1000000; break;
    case 0x19: anim = 0; flags = 0x100000; break;
    case 0x1a: anim = 0x10000; break;
    case 0x1b: anim = 0x4000000; break;
    case 0x1c: anim = 0; flags = 0x8000000; break;
    default:
        return;
    }
    FUN_00c245e0((i32_s00c2_5a50)anim, (i32_s00c2_5a50)flags, DAT_0146aa40, 0, (i32_s00c2_5a50)extra, pOrder->mn_28);
    cOrderPlay* pPlay = (cOrderPlay*)((char*)mpOrders_b4c + 8);
    i32_s00c2_5a50 r = (i32_s00c2_5a50)(intptr_t)pPlay->Play(anim, flags);
    if (r == 0)
        return;
    switch (pOrder->mw_4b) {
    case 1:
    case 7:
    case 10:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 5:
    case 8:
    case 0xb:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 6:
    case 9:
    case 0xc:
        *(u32*)(r + 0xc) = *(u32*)FUN_005727b0((char*)pOrder + 0x39);
        return;
    case 0xd:
    case 0xe:
        *(f32*)(r + 0xc) = *(f32*)FUN_005727e0((char*)pOrder + 0x39);
        return;
    default:
        return;
    }
}

// @ 0x00c266c0
cElem18** __cdecl FUN_00c266c0(cElem18** ppOut, cElem18* pBegin, cElem18* pEnd, cElem18* pValue)
{
    *ppOut = pValue;
    for (; pBegin != pEnd; ++pBegin) {
        cElem18* p = *ppOut;
        if (p != 0) {
            p->mb_00 = pBegin->mb_00;
            p->mp_04 = pBegin->mp_04;
            if (p->mp_04 != 0)
                p->mp_04->AddRef();
            p->mn_08 = pBegin->mn_08;
            p->mf_0c = pBegin->mf_0c;
            p->mf_10 = pBegin->mf_10;
            p->mf_14 = pBegin->mf_14;
        }
        *ppOut = *ppOut + 1;
    }
    return ppOut;
}

// @ 0x00c26730
cOrderData* cOrderData::FUN_00c26730(const cOrderData* pSrc)
{
    mn_00 = pSrc->mn_00;
    mn_10 = pSrc->mn_10;
    mn_14 = pSrc->mn_14;
    mn_18 = pSrc->mn_18;
    mn_1c = pSrc->mn_1c;
    mb_20 = pSrc->mb_20;
    mn_24 = pSrc->mn_24;
    _ReadWriteBarrier();
    IRefCounted_s00c2_5a50* pNew = pSrc->mp_28;
    IRefCounted_s00c2_5a50* pOld = mp_28;
    if (pNew != pOld) {
        if (pNew != 0)
            pNew->AddRef();
        mp_28 = pNew;
        if (pOld != 0)
            pOld->Release();
    }
    mn_2c = pSrc->mn_2c;
    mn_30 = pSrc->mn_30;
    mn_34 = pSrc->mn_34;
    mb_38 = pSrc->mb_38;
    mv_39 = pSrc->mv_39;
    mv_4d = pSrc->mv_4d;
    mv_61 = pSrc->mv_61;
    mv_75 = pSrc->mv_75;
    return this;
}

// @ 0x00c267e0
void cCreatureCitizen::TakeToolHit(int32_t nToolIndex, int32_t nSource, int32_t nFlags, int32_t nUnused, void* pInfo)
{
    float fOldDurability = mfToolDurability;
    ((cCreatureBase_s00c2_67e0*)this)->OnTakeHit(nSource, nFlags, nUnused, pInfo);

    if (mfToolDurability >= 0.000015258789f) {
        if (mpOwnerTribe != nullptr) {
            if (nToolIndex != -1) {
                void* pTool = ((cDispatchObject_s00c2_67e0*)this)->Call(0x4c);
                PlayCitizenEffect(0, nToolIndex, 1.0f, pTool);
            }
            if (pInfo != nullptr) {
                void* pEffect = ((cDispatchObject_s00c2_67e0*)pInfo)->Call(0x08);
                void* pTarget = ((cDispatchObject_s00c2_67e0*)pInfo)->Call(0x0c);
                int32_t nAmount = ((cDispatchObject_s00c2_67e0*)pEffect)->CallInt(0x74);
                ((cDispatchObject_s00c2_67e0*)pTarget)->Call(0x2c);
                OnCitizenFlagChanged((int32_t)0xb9d14c31u, nAmount);
            }
        }
    }
    else if (mpOwnerTribe != nullptr && fOldDurability > 0.000015258789f) {
        if (((cDispatchObject_s00c2_67e0*)this)->CallInt(0x58) == 0) {
            if (((cDispatchObject_s00c2_67e0*)this)->CallInt(0x58) == 0 && mpOwnerTribe != nullptr) {
                if (pInfo != nullptr)
                    ((cDispatchObject_s00c2_67e0*)pInfo)->Call(0x0c);
                OnCitizenFlagChanged(0x7c5b1068, 0);
            }
        }
        else {
            if (pInfo != nullptr)
                ((cDispatchObject_s00c2_67e0*)pInfo)->CallVoid(0x20);
            OnCitizenFlagChanged((int32_t)0xb9d14c31u, 2);
        }
    }

    if (mpOwnerTribe != nullptr && pInfo != nullptr)
        OnCitizenFlagChanged((int32_t)0xd0036e08u, 0);
    else if (pInfo != nullptr && ((cDispatchObject_s00c2_67e0*)pInfo)->CallInt(0x5c) != 0)
        PlayCitizenEffect(0, 0x80, 5.0f, nullptr);

    UpdateCitizenEffects();
}

// @ 0x00c26c10
void cCreatureCitizen::CreateLocomotionStrategy()
{
    mnPlanetCorrection = 0;
    mLocomotion.ResetLocomotion();

    if (mpOwnerTribe != nullptr) {
        mLocomotion.SetStrategy(GetSimulatorService()->GetWorldStrategy());
        return;
    }

    mLocomotion.AddStrategy((void*)&PlanetLocomotionStrategy);
    mLocomotion.AddStrategy((void*)&SpaceLocomotionStrategy);
    mLocomotion.SetStrategy(GetSimulatorService()->GetDefaultStrategy());
}

// @ 0x00c26c80
void RebuildCitizenOrderListDefault()
{
    RebuildCitizenOrderList(-1);
}

// @ 0x00c26c90
void cCreatureCitizen::ApplyToolOrder(uint32_t nToolMask, void* pOrder)
{
    uint32_t nEffect;

    if (mnToolEffectIndex != 0) {
        nEffect = (uint32_t)GetToolEffect(mnToolEffectIndex);
        if (nEffect == 0)
            goto default_order;
    }
    else {
        cCommunity* pCommunity = (cCommunity*)mpOwnerCity;
        if (pCommunity == nullptr) {
            pCommunity = (cCommunity*)mpOwnerTribe;
            if (pCommunity == nullptr)
                goto default_order;
        }
        if (pCommunity->GetLeader() != this)
            goto default_order;
        nEffect = 0x11;
    }

    if ((nToolMask & (1u << nEffect)) != 0) {
        ApplyOrder((int32_t)nEffect, pOrder);
        return;
    }

default_order:
    ApplyOrder(0, pOrder);
}

// @ 0x00c26d10
void cCreatureCitizen::UpdateSelectionFlags()
{
    if (mpOwnerTribe == nullptr && mbFieldB5E == 0)
        return;

    if (!g_bCitizenQueueInitialized) {
        FUN_00bc8fa0(&g_citizenQueue);
        g_bCitizenQueueInitialized = 1;
    }
    FUN_00bcb660(&g_citizenQueue);

    cFlagOwner* pFlags = (cFlagOwner*)mpFieldB4C;
    int32_t nHidden = mLocomotion.IsHidden();
    int32_t nFlags = pFlags->mnFlags;
    pFlags->mnFlags = nFlags | (nHidden != 0 ? 1 : 0);

    nFlags = pFlags->mnFlags;
    int32_t nAlive = UpdateCitizenEffects() != 0 ? 2 : 0;
    pFlags->mnFlags = nFlags | nAlive;

    bool bLeader;
    if (mpOwnerCity != nullptr || mpOwnerTribe != nullptr) {
        cCommunity* pCommunity = (cCommunity*)(mpOwnerCity != nullptr ? mpOwnerCity : mpOwnerTribe);
        bLeader = pCommunity->GetLeader() == this;
    }
    else {
        bLeader = false;
    }
    pFlags->mnFlags |= bLeader ? 0x20 : 0;

    mAgent.SetActive(1);
    ForceOrdersUpdate(this);
}

// @ 0x00c26e00
cCreatureCitizen* cCreatureCitizen::Construct()
{
    ((cCreatureBase_s00c2_67e0*)this)->ConstructBase();

    mpVtbl00 = (void*)0x146ad60;
    mpVtbl04 = (void*)0x146ad4c;
    mpVtbl34 = (void*)0x146ad08;
    mAgent.mpVtblLocal = (void*)0x146aca0;
    mLocomotion.mpVtblLocal = (void*)0x146aba0;
    mpVtbl194 = (void*)0x146ab94;
    mpVtbl590 = (void*)0x146ab78;
    mpVtbl5a8 = (void*)0x146ab10;
    mpVtbl670 = (void*)0x146aaf8;

    mTimer.mbField20[0] = 0;
    mTimer.mbField20[1] = 0;
    mTimer.mbField20[2] = 0;
    mTimer.mbField20[3] = 0;
    mTimer.mbField20[4] = 1;
    mTimer.mnField24 = 3;
    mTimer.Reset();
    mTimer.mnField28 = 0;
    mTimer.mnField2c = -1;
    mTimer.mnField30 = 0;
    mTimer.mbField34 = 0;
    mTimer.mbField36 = 1;
    mTimer.mafOffset[0] = g_fOffsetX;
    mTimer.mafOffset[1] = g_fOffsetY;
    mTimer.mafOffset[2] = g_fOffsetZ;
    mpOwnerCity = nullptr;
    mpOwnerTribe = nullptr;
    mStarRecords.mpBegin = nullptr;
    mStarRecords.mpEnd = nullptr;
    mStarRecords.mpCapacity = nullptr;
    mnSpecializedTool = 0;
    mpHitSphere = nullptr;

    RestartCitizenTimers();
    CreateLocomotionStrategy();
    mTimer.Restart();

    if (!g_bCitizenGlobalsReady) {
        g_bCitizenGlobalsReady = 1;
        g_fCitizenScale = 0.0f;
        g_nCitizenMode = 1;
    }

    if (mpFieldB48 != nullptr)
        FUN_00bc9a30(2, &g_citizenQueue);

    return this;
}

// @ 0x00c27120
void cCreatureCitizen::Destroy()
{
    mpVtbl00 = (void*)0x146ad60;
    mpVtbl04 = (void*)0x146ad4c;
    mpVtbl34 = (void*)0x146ad08;
    mAgent.mpVtblLocal = (void*)0x146aca0;
    mLocomotion.mpVtblLocal = (void*)0x146aba0;
    mpVtbl194 = (void*)0x146ab94;
    mpVtbl590 = (void*)0x146ab78;
    mpVtbl5a8 = (void*)0x146ab10;
    mpVtbl670 = (void*)0x146aaf8;

    if (mpRequest != nullptr)
        mpRequest->Release();
    mStarRecords.Destroy();
    if (mpOwnerTribe != nullptr)
        mpOwnerTribe->Release();
    if (mpOwnerCity != nullptr)
        mpOwnerCity->Release();
    mTimer.Destroy();
    ((cCreatureBase_s00c2_67e0*)this)->DestroyBase();
}

// @ 0x00c271d0
void cCreatureCitizen::UpdateFrame(void* pTransform, int32_t nMode, int32_t nFlags, void* pContext)
{
    ((cDispatchObject_s00c2_67e0*)&mLocomotion)->CallVoid(0x38);
    ((cDispatchObject_s00c2_67e0*)this)->CallVoid(0x3c);
    FUN_00c0cf50();
    UpdateCitizenEffects();

    int32_t nHidden = mLocomotion.IsHidden();
    if (nHidden == 0) {
        if (mpOwnerTribe == nullptr) {
            if (mpFieldB48 != nullptr)
                FUN_00bd99e0();
        }
        else {
            FUN_00b6f0c0(mpListBegin);
        }
    }
    FUN_00c0d950(nHidden == 0);

    if (mpOwnerTribe != nullptr)
        FUN_00c21090();
    FUN_00c24110(this);
    UpdateSelectionFlags();

    if (mpListEnd == nullptr) {
        void* pNoun = CreateCitizenNoun(0x2e72cae);
        if (pNoun != nullptr)
            pNoun = ((cDispatchObject_s00c2_67e0*)pNoun)->Call(0x0c);
        cRefCounted* pOld = mpOwnerTribe;
        if (pNoun != (void*)pOld) {
            if (pNoun != nullptr)
                ((cRefCounted*)pNoun)->AddRef();
            mpOwnerTribe = (cRefCounted*)pNoun;
            if (pOld != nullptr)
                pOld->Release();
        }
        FUN_00c3f160(0.5f, 2.0f);
        FUN_00c3f2d0(this);
    }

    mbFieldB5E = mpOwnerTribe != nullptr ? 1 : 0;
    (void)pTransform;
    (void)nMode;
    (void)nFlags;
    (void)pContext;
}

// @ 0x00c275b0
void* cCreatureCitizen::GiveOrder(void* pOrderInfo, void* pTarget, void* pParams)
{
    void* pExisting = FUN_00bca2c0();
    FUN_00bca470();
    if (pExisting != nullptr)
        FUN_00c26730(pExisting);

    void* pOrder = FUN_00bcaf70(pTarget, pParams, 1);
    if (pOrder == nullptr)
        return nullptr;

    ((cDispatchObject_s00c2_67e0*)pOrder)->CallVoid(0x38);
    if (pOrderInfo != nullptr)
        ((cDispatchObject_s00c2_67e0*)pOrder)->CallVoidArg(0x39, pOrderInfo);

    if (pTarget != nullptr) {
        void* pFirst = ((cDispatchObject_s00c2_67e0*)pTarget)->Call(0x0c);
        void* pSecond = ((cDispatchObject_s00c2_67e0*)pTarget)->Call(0x0c);
        if (pFirst == nullptr) {
            float* pPosition = (float*)((uint8_t*)pSecond + 0x10);
            OnCitizenFlagChanged((int32_t)pPosition[0], (int32_t)pPosition[1]);
        }
        else {
            ((cDispatchObject_s00c2_67e0*)pFirst)->Call(0x2c);
        }
    }

    ForceOrdersUpdate(this);
    if (pExisting != nullptr) {
        if (FUN_00bca180(pOrder) == 0)
            PlayCitizenEffect(0x4000, 0, g_fMaxFloat, nullptr);
    }
    FUN_00bca120();
    return pOrder;
}

// @ 0x00c276d0
int32_t cCreatureCitizen::SelectSpeciesProfile(void* pSpeciesKey)
{
    void* pKey = mSpeciesKey;
    if (GetSettingId(pKey) < 0)
        return 0;

    void* pProfile = GetProfileFromKey(pKey);
    if (OnProfileSelected(pSpeciesKey) == 0)
        return 0;

    if (mpProfile != nullptr && mpOwnerTribe != nullptr) {
        if (pProfile != mpProfile)
            return 0;
        int32_t nCount = (int32_t)(((uint8_t*)mpListEnd - (uint8_t*)mpListBegin) / 0x48);
        if ((float)nCount >= mfToolDurability)
            return 1;
    }

    mpProfile = pProfile;
    return 1;
}

// @ 0x00c277f0
cStarRecordVector& cStarRecordVector::CopyFrom(cStarRecordVector* pOther)
{
    int32_t nCount = (int32_t)(((uint8_t*)pOther->mpEnd - (uint8_t*)pOther->mpBegin) / 0x18);
    void* pBuffer;
    if (nCount == 0)
        pBuffer = nullptr;
    else
        pBuffer = operator_new(nCount * 0x18, "Simulator", 0, 0, gsAllocatorFile, 0xd1);

    mpCapacity = (uint8_t*)pBuffer + nCount * 0x18;
    mpBegin = pBuffer;
    mpEnd = pBuffer;
    CopyStarRecordRange(pOther, pOther->mpBegin, pOther->mpEnd, pBuffer, pOther);
    mpEnd = pOther;
    return *this;
}

// @ 0x00c278a0
void cCreatureCitizen::SetCreatureName(const char* pName)
{
    cGonzagoTempText temp(pName);
    SetLocalizedName(&temp.mpText);
    if (temp.mpText != nullptr) {
        if (((cTextAllocation*)temp.mpText - 1)->mnSize != 0)
            operator_delete_array(temp.mpText);
    }
}

// @ 0x00da80f0
bool FUN_00da80f0(Creature* p, Creature* q)
{
    Creature* a = p->FUN_00bc9b10();
    if (a->GetTribe() == q->GetTribe())
        return true;
    return false;
}

// @ 0x00da8120
void FUN_00da8120(Creature* p, i32_s00da_7780, i32_s00da_7780, i32_s00da_7780, i32_s00da_7780, S28* s)
{
    if (s->mField10 != -1) {
        p->SetCurrentToolEffect(0, s->mField10);
        p->RebuildCitizenOrderListDefault();
    }
}

// @ 0x00da8150
bool GrowUp(Creature* p, i32_s00da_7780, i32_s00da_7780, i32_s00da_7780, i32_s00da_7780, u32* out)
{
    *out = p->InterruptAnimation(0x3a79244, -1, 0);
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x200);
    return 1;
}

// @ 0x00da8190
f32 FUN_00da8190(Creature* p)
{
    i32_s00da_7780 a = (i32_s00da_7780)p->FUN_00c22a70();
    i32_s00da_7780 b = (i32_s00da_7780)p->FUN_00c26120();
    if (a != b)
        return 1.0f;
    return 0.0f;
}

// @ 0x01335fe0
void FUN_01335fe0(void)
{
    AttrDesc d;
    REC401(0, "mSelectionGroup",             0x2e6e1b0, 0xff4,
           H_692ca0, H_572810_0, H_572840_0, H_692ff0_0, H_694ee0_0, H_b1fbf0_0, H_57cde0_0)
    REC401(1, "mFavoredGrasperlikeAppendage",0x2e6e1b1, 0xfc4,
           H_692ca0, H_572810_1, H_572840_1, H_693090_1, H_694f00_1, H_b1fbf0_g, H_675ca0_g)
    REC401(2, "mGrasperlikeAppendageForBundle",0x5f0d6f3,0xfc8,
           H_692ca0, H_572810_2, H_572840_2, H_693090_2, H_694f00_2, H_b1fbf0_g, H_675ca0_g)
    REC401(3, "mSpecializedTool",            0x2e6e1b2, 0x102c,
           H_692ca0, H_572810_3, H_572840_3, H_692ff0_3, H_694ee0_3, H_b1fbf0_3, H_57cde0_3)
    REC401(4, "mAffectedByRecruiting",       0x2e6e1ab, 0x1000,
           H_692ca0, H_572810_4, H_572840_4, H_693090_4, H_694fa0_4, H_b1fbf0_4, H_57ce00_4)
    REC401(5, "mpOwnerCity",                 0x2e6e1ad, 0x1010,
           H_692ca0, H_572810_5, H_572840_5, H_c2e4e0_5, H_692fb0_g, H_b6f550_5, H_ac8050_g)
    REC401(6, "mpOwnerTribe",                0x2e6e1af, 0x1014,
           H_692ca0, H_572810_6, H_572840_6, H_c2e4e0_6, H_692fb0_g, H_b6f550_6, H_ac8050_g)
    REC401(7, "mpHitSphere",                 0x6a814a9, 0x1030,
           H_692ca0, H_572810_7, H_572840_7, H_c2e4e0_7, H_692fb0_g, H_b6f550_7, H_ac8050_g)
}
