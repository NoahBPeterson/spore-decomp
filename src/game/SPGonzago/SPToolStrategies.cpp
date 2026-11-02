// src/game/SPGonzago/SPToolStrategies.cpp -- migrated from slice(s) s0105aa50, s010593e0, s01056160, s010554c0, s0105b960, s0105a110, s01058b60, s01057d50, s01056f40, s01054110, s010527f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPToolStrategies.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cSPTimer.h"
#include "SP/cDefaultAoEArea.h"
#include "SP/cDefaultBeamProjectile.h"
#include "SP/cGameNounManager.h"
#include <math.h>
#include <string.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cEmptyBubble.h"
#include "SP/cTribe.h"
#include "SP/cBuilding.h"
#include "SP/cInteraction.h"
#include "SP/cSPMission.h"
#include "SP/cSpatialObject.h"
#include "SP/cEmpire.h"
#include "SP/cStarManager.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cCity.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPlayer.h"
#include "SP/cRelationshipManager.h"
#include "SP/cStarRecord.h"
#include "SP/cTerrainSphere.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cSPPlanetaryArtifact.h"
#include "SP/cCombatant.h"
#include "SP/cCityVisualizer.h"

// ---- items of slice s010527f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void v00();
    virtual void AddRef();          // 0x04
    virtual void Release();         // 0x08
    virtual void SetEnabled(int bEnabled);  // 0x0c
    virtual bool IsAlive();         // 0x10
    virtual IRefCounted* Query(const void* pType);  // 0x14
};
class cSPTimer {
public:
    void Stop();
    uint32_t mPad00[4];
};
class cSPUIEventLog {
public:
    void RemoveAllEventsOfSameType(int type);
    int PostFeedbackEvent(int type, uint32_t feedbackId, int a, int b, int c, int d);
    int GetEventInstanceID(int type, int data);
    void RestartTimer(int instanceId);
    void ModifyEventText(int instanceId, int textId);
    void ModifyData(int instanceId, int data);
    void RegisterCloseCallback(int instanceId, void* pCallback);
};
cSPUIEventLog* EventLog(int type, ...);
void KillSetiEffects();
void PlayUiSound(const char* pSound);
class cPlanetSpecies {
public:
    bool IsSpeciesScanned();
    void SetSpeciesAsScanned();
    bool IsColonyScanned();
    void SetColonyScanned();
    bool IsTribeScanned();
    void SetTribeAsScanned();
    float mPad24;
};
class cPlanet {
public:
    cPlanetSpecies* GetSpecies();   // 0x98
    cPlanetSpecies* GetTribe();     // 0x9c
    Vec3* GetPosition(Vec3* pOut);
    uint8_t mPad00[0x98];
};
class cPlanetModel {
public:
    Vec3* DirectionToSurfacePosition(Vec3* pOut, Vec3* pDirection);
    Vec3* MakeRandomWorldPosition(Vec3* pOut, Vec3* pDirection, float a, float b);
    uint8_t mPad00[0x20];
};
cPlanetModel* PlanetModel();
cPlanetModel* PlanetModel(Vec3* pOut);
cPlanetModel* PlanetModel(Vec3* pOut, Vec3* pDirection);
cPlanetModel* PlanetModel(Vec3* pOut, Vec3* pDirection, float a, float b);
Vec3* CreatureSurfacePoint(Vec3* pOut, cPlanetModel* pModel);
class cSPSpaceInventoryItem : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    Vec3* GetPosition(Vec3* pOut);       // 0x2c
    Vec3* GetDirection(Vec3* pOut);      // 0x30
};
class cSPSpaceInventory {
public:
    uint8_t mPad00[0x34];
    cSPSpaceInventoryItem* mpHeldItem;   // 0x34
    uint8_t mPad38[0x4d0];
    cSPSpaceInventoryItem* mpShipItem;   // 0x508
    uint8_t mPad50c[0x34];
    float mCargoMax;                     // 0x540
    uint8_t mPad544[0x2b0];
    float mEnergyCurrent;                // 0x7f4
    float mEnergyMax;                    // 0x7f8
};
class cSPSimulatorSpaceGame {
public:
    cSPSpaceInventory* GetPlayerInventory();
    void* GetPlayerUFO();
    void* GetPlayerEmpire();
    uint8_t mPad00[0x20];
};
cSPSimulatorSpaceGame* SpaceGameGet();
cSPSimulatorSpaceGame* GetActiveSpaceGame();
struct IVectorItem : public IRefCounted {
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    Vec3* GetPosition(Vec3* pOut);   // 0x2c
};
void* NounManager();
class cSPToolStrategy {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool CanUseToolAt(int nToolId, int nTarget, int bFlag = 0);  // 0x20
    virtual bool IsValidLocation(int nTarget, Vec3* pPosition, int bFlag);  // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void ShowToolEventLog(int nToolId, const void* pData, int nDataLen, int nFlags);  // 0x30
    virtual void v34();
    virtual void v38();
    virtual Vec3* GetMouseWorldPosition(Vec3* pOut);  // 0x3c
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void OnUseResult(int a, int b);  // 0x4c

    // 0x00 vftable
    cPlanet* mpPlanet;                 // 0x34
    uint8_t mPad38[0x48];
    uint8_t mbActive;                  // 0x80
    uint8_t mPad81[0x2f];
    IRefCounted* mpToolEffectA;        // 0xb0
    IRefCounted* mpToolEffectB;        // 0xb4
    uint8_t mPadB8[0x10];
    cSPTimer mTimer;                   // 0xc8
    uint8_t mPadD8[0x3c];
    cSPSpaceInventoryItem* mpTargetItem;  // 0x114
    IRefCounted* mpAreaEffect;          // 0x120
    IRefCounted* mpBeamProjectile;      // 0x124
    IRefCounted* mpEffectRef;           // 0x12c
    uint8_t mPad130[0x10];
    IRefCounted* mpActiveObject;        // 0x140
    uint8_t mPad144[0x2c];
    int mEventType;                     // 0x170

    // 0x00e14a30-style helpers replicated for this cluster.
    bool ActivateTool(int nToolId);                     // 0x00e537e0
    bool CanUseToolAtLocation(int nToolId, int nTarget);  // 0x00e53980
    void UpdatePassive();                                // 0x00e53bb0
    bool StopTool();                                     // 0x00e53650
    Vec3* FindTestTerrainLocation(Vec3* pOut, int nTarget);  // 0x00e53be0
    int SetErrorEvent(int nEventType, bool bPost);       // 0x00e527f0
};
class cSPDefaultBeamTool : public cSPToolStrategy {
public:
    bool StopTool();       // 0x00e53db0
    bool UpdateBeam();     // 0x00e53e00
};
class cSPDefaultAoETool : public cSPToolStrategy {
public:
    bool StopTool();       // 0x00e53ee0
    bool UpdateArea();     // 0x00e53f20
};
class cSPEnergyRepairToolStrategy : public cSPToolStrategy {
public:
    int AdjustCost(int nBaseCost);   // 0x00e53590
    int AdjustCostPercent(int nBaseCost);  // 0x00e535e0
};
class cSPScanToolStrategy : public cSPToolStrategy {
public:
    bool ActivateTool(int nToolId);           // 0x00e53fb0
    bool UseTool(int nToolId, int nTarget);   // 0x00e54080
    bool StopTool();                          // 0x00e53ff0
};
class cSPGetOutOfUFOToolStrategy : public cSPToolStrategy {
public:
    bool CanUseToolAtLocation(int nToolId, int nTarget);  // 0x00e540b0
    bool ActivateTool(int nToolId);                       // 0x00e540d0
};
void AppendScanResult(void* pList, int* pOut);              // 0x01052880
void GetMouseRay(Vec3* pOut);                               // 0x01052f90
void ShowScanEventLog(int a, int b, int c, int pCallback, int nDuration);
int ScanSpecies(cPlanet* pPlanet);                          // 0x01053240
int ScanTribe(cPlanet* pPlanet);                            // 0x01053320
int ScanColony(cSPSimulatorSpaceGame* pGame);               // 0x010533d0
int ScanAllSpecies(cPlanet* pPlanet);                       // 0x010534c0
void AttachToolEffect(const void* pData);                   // 0x01053d50
void AddToolCharge(int nAmount);
int gSpaceToolFlags[8];
class IQueryable {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual IRefCounted* Query(const void* pType);  // 0x0c
};
struct IItemHolder {
    IRefCounted* mpItem;      // 0x00
    uint32_t mPad04[2];       // 0x04
    IQueryable* mpSecondary;  // 0x0c
};
// ---- items of slice s010527f0 end

// ---- items of slice s01054110 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
 class cDefaultToolProjectile; 
}
extern void*  SP_SpaceGameGet(void);                  // 0x1002bd0
extern void*  SP_GetUniverseContext(void);            // 0x1021080
extern void*  SP_NounManager(void);                   // 0xb3d300
extern void   FUN_00bebb10(void);                     // 0xbebb10
extern void*  SP_GetGameTerrainCursor(void);          // 0xb30d70
extern void   FUN_00bed920(int a, int b);             // 0xbed920
extern void*  SP_GonzagoModelWorld(void);             // 0xb3d520
extern void*  FUN_0067cab0(int a);                    // 0x67cab0
extern void*  FUN_011e0810(void);                     // 0x11e0810
extern void*  FUN_00b3d3c0(void);                     // 0xb3d3c0
extern float* FUN_00449c20(float* dst, float* src);   // 0x449c20
extern float* FUN_006985b0(float* out, float* in);    // 0x6985b0
typedef unsigned int  u32;
typedef unsigned char u8;
struct Obj;
typedef void          (__thiscall *VfnRaw)();
typedef void          (__thiscall *Vfn0)(void*);
typedef void*         (__thiscall *VfnP)(void*);
typedef void          (__thiscall *VfnI)(void*, int);
typedef void*         (__thiscall *VfnPI)(void*, int);
typedef void          (__thiscall *VfnII)(void*, int, int);
typedef void          (__thiscall *VfnVV)(void*, void*, void*);
typedef void          (__thiscall *VfnV)(void*, void*);
typedef unsigned char (__thiscall *VfnB)(void*);
typedef unsigned char (__thiscall *VfnB3)(void*, void*, void*, int);
enum VSlot {
    kV00 = 0x00 / 4,
    kV04 = 0x04 / 4,
    kV0C = 0x0c / 4,
    kV10 = 0x10 / 4,
    kV18 = 0x18 / 4,
    kV24 = 0x24 / 4,
    kV2C = 0x2c / 4,
    kV38 = 0x38 / 4,
    kV48 = 0x48 / 4,
    kV54 = 0x54 / 4,
    kV5C = 0x5c / 4,
    kV68 = 0x68 / 4,
    kVB8 = 0xb8 / 4,
    kVD0 = 0xd0 / 4,
    kVD4 = 0xd4 / 4
};
struct Vtbl {
    VfnRaw mSlots[0xd8 / 4];    // +0x00 .. +0xd4
};
struct Vec3_s0105_4110 { float x, y, z; };
struct Sub34 {
    Vtbl* mpVtbl;               // +0x00
};
struct Obj {
    Vtbl*         mpVtbl;                  // +0x000
    unsigned char mPad004[0x30];           // +0x004
    Sub34         mSub34;                  // +0x034
    unsigned char mPad038[0xa6 - 0x38];    // +0x038
    u8            mByteA6;                 // +0x0a6
    unsigned char mPad0A7[0x110 - 0xa7];   // +0x0a7
    u8            mByte110;                // +0x110
    unsigned char mPad111[0x114 - 0x111];  // +0x111
    Obj*          mpManager114;            // +0x114  owning tool manager
    unsigned char mPad118[0x120 - 0x118];  // +0x118
    Obj*          mpArea120;               // +0x120  current AoE area noun
    Obj*          mpBeam124;               // +0x124  current beam projectile
    Obj*          mpUnk128;                // +0x128
    unsigned char mPad12c[0x140 - 0x12c];  // +0x12c
    Obj*          mpUnk140;                // +0x140
    float         mF144;                   // +0x144
    float         mF148;                   // +0x148
    float         mF14c;                   // +0x14c  range multiplier
    unsigned char mPad150[0x154 - 0x150];  // +0x150
    Vec3_s0105_4110          mVec154;                 // +0x154  previous aim/orientation
    Vec3_s0105_4110          mVec160;                 // +0x160  new aim/orientation
    Obj*          mpUnk16c;                // +0x16c  transform receiver
};
struct GameObj {
    void f50d0(int a);                            // 0x10050d0
};
struct NounMgr {
    void* CreateNoun(u32 key);                    // 0xb20c60
    void  RemoveNoun(void* noun);                 // 0xb225d0
};
struct C8017f0 {
    char Set(void* a);                            // 0x8017f0
};
struct ObjVec {
    void* erase(void* a);                         // 0xb3d390
};
struct ToolManager {
    void UseToolStop();                           // 0x104fa90
};
struct SpaceTool {
    float Get01();                                // 0x104bdd0
    float Get02(float x);                         // 0x104bdb0
    float Get03();                                // 0x104be30
    char  Get04();                                // 0x104cd00
    char  Get05();                                // 0x104cd10
    char  Get06();                                // 0x104cd30
    char  Get07();                                // 0x104cd50
    char  Get08();                                // 0x104cd90
    float Get09();                                // 0x104bee0
    float Get0a();                                // 0x104be50
    void  Get0b();                                // 0x104bdc0
};
struct ChargeTool {
    float Spread(float x);                        // 0xce6940
};
struct Projectile {
    void SetA(int a);                             // 0xcb3d00
    void SetB(int a);                             // 0xcb3ce0
};
struct BeamProjectile {
    void Fire(void* a, void* b);                  // 0xcb5770
};
struct AoEArea {
    void InitArea(void* tool);                    // 0xcb5cf0
    void StartArea();                             // 0xcb6090
};
struct Noun2 {
    void Cleanup();                               // 0xcb3c70
};
struct SubObj2 {
    void Notify(int a);                           // 0x1030dd0
};
struct Simulator {
    void ClearDirty();                            // 0xb78860
};
struct XformMsgObj {
    void construct();                             // 0x434040
};
struct XformMsg_s0105_4110 {
    unsigned short mFlags;      // +0x00
    unsigned short mCount;      // +0x02
    unsigned char  mPad04[0x50];
    Vec3_s0105_4110           mVec;        // +0x54
    float          mBasis[9];   // +0x60
};
struct PlaceColonyTool {
    char ActivateTool(int a);              // 0x10537e0
    char DeactivateTool(int param_1);      // @ 0x01054110
};
struct ToolStrategy2 {
    void StopTool(void* param_2, void* param_3);   // @ 0x01054350
};
extern void   FUN_00cb7c20(float* v, int a);          // 0xcb7c20
extern void   FUN_00cc0870(float f, void* a, void* b); // 0xcc0870
// ---- items of slice s01054110 end

// ---- items of slice s01056f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gProjectileMinDistance2;       // 0x0149af90
extern uint32_t gAimHandleName;             // 0x013f94d4
extern uint32_t gMissileHandleName;         // 0x017f243b
struct Vector3 {
    float x;
    float y;
    float z;
};
struct Matrix3Rows {
    float m[9];
};
class XformMsg {
public:
    XformMsg();                 // 0x00434040

    uint16_t mFlags;            // +0x00
    uint16_t mCount;            // +0x02
    Vector3 mPosition;          // +0x04
    uint16_t mBasisFlags;       // +0x0c
    uint16_t mBasisCount;       // +0x0e
    float mScale;               // +0x10
    uint8_t mPad11[0x0b];       // +0x11
    Matrix3Rows mBasis;         // +0x20
};
class IEffect;
class IEffectHandle {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual bool Create(uint32_t nType, int32_t nFlags, IEffect** ppEffect);   // +0x08
};
class IEffect {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual void Detach(int32_t nValue);                            // +0x08
    virtual void* Slot0c(void* pOut);                               // +0x0c
    virtual Vector3* Slot10(void* pOut);                            // +0x10
    virtual void* Slot14();                                         // +0x14
    virtual void Send(XformMsg* pMsg);                              // +0x18
    virtual void Slot44(int32_t nType, void* pValue, int32_t nFlags);   // +0x44
};
class cSPNoun {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual bool Slot08();                                          // +0x08
    virtual void* Slot0c(uint32_t nNounId);                         // +0x0c
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                                 // +0x2c
    virtual Vector3* Slot30(Vector3* pOut);
    virtual void* Slot34();
    virtual void Slot38(void* pOut);                                // +0x38
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void* Slot44();
    virtual void Slot48(void* pOwner);                              // +0x48
    virtual void* Slot4c();                                         // +0x4c
    virtual void* Slot50();
    virtual void Slot54(void* pOwner);                              // +0x54
    virtual void* Slot58();
    virtual void* Slot5c(uint32_t nConfig);                         // +0x5c
    virtual void* Slot60();
};
class cSPAimObject {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                                 // +0x2c
    virtual Vector3* GetTransform(Vector3* pOut);                   // +0x30
    virtual float GetScalar();                                      // +0x34
    virtual void* Slot38();
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void Slot44();
    virtual void* Slot48();
    virtual void* Slot4c();
    virtual void* Slot50();
    virtual void* Slot54();
    virtual void* Slot58();
    virtual void* Slot5c(uint32_t nConfig);                         // +0x5c
    virtual void* Slot60();
    virtual void* Slot64();
    virtual void* Slot68();
    virtual void* Slot6c();
    virtual float Slot70();                                         // +0x70
    virtual void* Slot74();
    virtual void* Slot78();
    virtual void* Slot7c();
    virtual void* Slot80();
    virtual void* Slot84();
    virtual void* Slot88();
    virtual void* Slot8c();
    virtual void* Slot90();
    virtual void* Slot94();
    virtual void* Slot98();
    virtual void* Slot9c();
    virtual void* SlotA0();
    virtual void* SlotA4();
    virtual void* SlotA8();
    virtual void* SlotAc();
    virtual void* SlotB0();
    virtual void* SlotB4();
    virtual void* Slotb8(const void* pName);                        // +0xb8
};
class cSPToolStrategy_s0105_6f40 {
public:
    uint8_t mPad000[0x114];     // +0x000
    cSPAimObject* mpAimer;      // +0x114
    cSPAimObject* mpTarget;     // +0x118
    uint8_t mPad11c[0x38];      // +0x11c
    Vector3 mPressedAt;         // +0x154
    Vector3 mReleasedAt;        // +0x160
    IEffect* mpEffect;          // +0x16c
};
class cEffectsManager_s0105_6f40 {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual bool CreateEffect(void* pConfig, int32_t nFlags);       // +0x2c
    virtual void* Slot30();
    virtual void* Slot34();
    virtual void* Slot38();
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void* Slot44();
    virtual void* Slot48();
    virtual void* Slot4c();
    virtual void* Slot50();
    virtual IEffectHandle* Acquire(uint32_t nType);                 // +0x54
};
class cGameNounManager {
public:
    cSPNoun* CreateNoun(uint32_t nNounId);                          // 0x00b20c60
};
class cScanIterator {
public:
    int32_t GetValue();                                             // 0x0104c4f0
};
class cSpaceItem {
public:
    uint32_t GetItemInstanceID();                                   // 0x00c87040
};
class cUniverseContext {
public:
    bool IsPlanetUnlocked(void* pPlanet);                           // 0x00c70b20
    void* GetPlayerObject();                                        // 0x00c71e30
    int32_t GetEmpireState();                                       // 0x00c70e00
    cSpaceItem* GetPlayerItem();                                    // 0x00c30c60
    uint8_t mPad000[0x13c];     // +0x000
    void* mpObjectList;         // +0x13c
};
class cPlanetModel;
class cSPPlaceObjectToolStrategy {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();                                         // +0x1c
    bool CanUseCheckA();                                            // 0x0104cc20
    bool CanUseCheckB();                                            // 0x0104cc30
};
bool __stdcall StartTool(cSPToolStrategy_s0105_6f40* pSelf, const Vector3* pTarget,
                         void* pParam);                             // 0x010568b0
cGameNounManager* __cdecl NounManager_s0105_6f40();                            // 0x00b3d300
cEffectsManager_s0105_6f40* __cdecl EffectsManagerPtr_s0105_6f40();                       // 0x0067ddd0
void __stdcall LaunchProjectile(cSPToolStrategy_s0105_6f40* pSelf, void* pProjectile,
                                const Vector3* pOrigin,
                                const Vector3* pTarget);            // 0x010543e0
void* __cdecl FUN_0104bf40(IEffect** ppEffect);                     // 0x0104bf40
void __stdcall FUN_00cb5140(void* pObject, void* pOut);             // 0x00cb5140
Matrix3Rows* __stdcall Matrix3FromFacingAndUp(Matrix3Rows* pOut,
                                              const Vector3* pFacing,
                                              const Vector3* pUp);  // 0x0069b440
int32_t __stdcall FUN_0104bd80(void* pSelf);                        // 0x0104bd80
bool __stdcall GetCreatureColorProperty(void* pColor, void* pOut);  // 0x0102c720
float __cdecl FUN_0104be50();                                       // 0x0104be50
void __stdcall FUN_00cb8760(const Vector3* pDir, void* pTarget);    // 0x00cb8760
void __stdcall FUN_00cb7ba0(const Vector3* pDir, float fSpeed);     // 0x00cb7ba0
float __cdecl FUN_00e21850();                                       // 0x00e21850
float __cdecl FUN_00c41f20();                                       // 0x00c41f20
cPlanetModel* __cdecl PlanetModel(Vector3* pPosition);              // 0x00ba0cc0
float __fastcall GetRadiusAt(cPlanetModel* pModel, void*,
                             const Vector3* pPosition);             // 0x00ba0cc0
Vector3* __cdecl normalized_safe(Vector3* pOut, const Vector3* pIn);   // 0x00449c20
Vector3* __cdecl OrthogonalVector(Vector3* pOut, const Vector3* pIn);  // 0x006985b0
bool __stdcall BaseCanUseTool(cSPPlaceObjectToolStrategy* pSelf, bool bArg,
                              int32_t* pOut);                       // 0x01056160
void __cdecl SetErrorEvent(cSPPlaceObjectToolStrategy* pSelf, int32_t nId,
                           bool bArg);                              // 0x010527f0
void __cdecl AppendScanResult(int32_t nId, int32_t* pOut);          // 0x01052880
cScanIterator* __cdecl EraseScanItem(int32_t nIndex);               // 0x00b3d390
void* __cdecl FUN_01021260();                                       // 0x01021260
cSpaceItem* __cdecl FUN_01021240();                                 // 0x01021240
void* __stdcall FUN_01021300(int32_t nZero);                        // 0x01021300
bool __cdecl FUN_00b8e040(void* pObject, void* pOther);             // 0x00b8e040
extern Vector3 gZeroPoint;                  // 0x016e1b14 (three floats)
// ---- items of slice s01056f40 end

// ---- items of slice s01057d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_spaceTokenTranslator[];    // 0x16e0d08
typedef int                i32;
struct cSpeciesSubRec {
    u8    mPad000[0x504];
};
struct cSPCreatureBase {
    void** vftable;                     // 0x00
    u8     mPad04[0x0b20 - 0x04];
    void*  mpField0b20;                 // 0x0b20 (active-planet-ish object)

    void* GetSpeciesRecord();           // 0x00c0bbd0 -> returns species profile
};
struct cSpeciesProfile {
    u8    mPad000[0x504];
    i32   mField504;                    // 0x504
    i32   mField508;                    // 0x508
    i32   mField50c;                    // 0x50c
};
void __cdecl NotifyScannedCreatureSpecies(void* speciesRec, i32 flag);   // 0x01058460
void* __cdecl GetIconTrayObj();                                          // 0x010666a0
void __cdecl ShowScanEventLog(i32 v3, i32 v1, i32 v2, void* fn, void* text);   // 0x010531b0
static inline u32 VT_0C_0(void* p, void* arg)
{
    void** vt = *(void***)p;
    void* fn = vt[3];
    return ((u32 (__thiscall*)(void*, void*))fn)(p, arg);
}
u8   __cdecl cPlanet_SetSpeciesAsScanned(void* planet, void* sub);         // 0x00c73ea0
void __cdecl cPlanet_ResetSpecies(void* planet, void* sub, i32 a, i32 b);  // 0x00c74690
void* __cdecl Text_GetText(void* strObj);                                  // 0x006b55c0
// ---- items of slice s01057d50 end

// ---- items of slice s01058b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gEmptyBubbleFade;                                      // 0x013ec5b4
extern const void* gDataFilter;                                     // 0x018c43e8
extern const void* gTribeDataFilter;                                // 0x018c6d19
inline void* operator new(unsigned int, void* pWhere) { return pWhere; }
float sqrtf_c(float fValue);
class cGameNounManager_s0105_8b60 {
public:
    void* GetGameDataVector(uint32_t nFilter, uint32_t nTypeA, uint32_t nTypeB,
                            uint32_t nTypeC, const void* pFilterData);   // 0x00b21340
};
cGameNounManager_s0105_8b60* NounManager_s0105_8b60();                                     // 0x00b3d300
struct cGameDataList {
    uint32_t mnUnk00;                                               // 0x00
    void** mpBegin;                                                 // 0x04
    void** mpEnd;                                                   // 0x08
};
struct cVector3 {
    float x;                                                        // 0x00
    float y;                                                        // 0x04
    float z;                                                        // 0x08
};
struct cEmptyBubble {
    cVector3 mPosition;                                             // 0x00
    float mfFade;                                                   // 0x0c
    int mnFlags;                                                    // 0x10

    cEmptyBubble() : mfFade(0.0f), mnFlags(0) {}
};
class cBubbleVector {
public:
    cEmptyBubble* mpBegin;                                          // 0x00
    cEmptyBubble* mpEnd;                                            // 0x04
    cEmptyBubble* mpCapacity;                                       // 0x08

    void push_back()
    {
        if (mpEnd < mpCapacity) {
            cEmptyBubble* pSlot = mpEnd++;
            if (pSlot != 0)
                new (pSlot) cEmptyBubble();
        } else {
            cEmptyBubble value;
            DoInsertValue(mpEnd, &value);
        }
    }

    void DoInsertValue(cEmptyBubble* pEnd,
                       const cEmptyBubble* pValue);                 // 0x00bde910
};
struct cBubbleSource {
    void* mpVtable;                                                 // 0x00
};
class cGameObject {
public:
    uint32_t mUnk000[0x45];                                         // 0x000
    void* mpUnk114;                                                 // 0x114
    uint32_t mUnk118[2];                                            // 0x118
    cBubbleSource mBubbleSource;                                    // 0x120
    uint32_t mUnk124[0x65];                                         // 0x124
    cBubbleVector mBubbles;                                         // 0x2b8
    uint32_t mUnk2c4[2];                                            // 0x2c4
    uint32_t mnUnk2cc;                                              // 0x2cc
    uint32_t mnUnk2d0;                                              // 0x2d0
};
class cSPToolStrategy_s0105_8b60 {
public:
    bool StartTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);   // 0x010568b0
    bool CanUseTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);  // 0x010568b0
};
int  ToolStrategy_IsValid();                                        // 0x01021230
int  ToolStrategy_GetCount();                                       // 0x00c8b5a0
int  ToolStrategy_GetOwner();                                       // 0x00c8b5b0
int  ToolStrategy_GetLimit();                                       // 0x00bbe470
int  cSPLivingUniverse_GetActivePlanetRecord();                     // 0x01021260
void ToolStrategy_Fail(uint32_t nArg1, uint32_t nReason, uint32_t nArg2);  // 0x010527f0
uint32_t ToolStrategy_MakeResult(uint32_t nReason);                 // 0x0104c4f0
float ToolStrategy_GetRadius();                                     // 0x0104bdc0
int  ToolStrategy_GetTargetId();                                    // 0x0104bd80
float ToolStrategy_GetScore(uint32_t nId);                          // 0x00ce6930
void ToolStrategy_SpawnBubble(float* pPosition, float fScore, uint32_t nId);  // 0x00bdff50
class cSPPlaceColonyToolStrategy : public cSPToolStrategy_s0105_8b60 {
public:
    bool CanUseTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);
    bool StartTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult);
};
class cTribe {
public:
    void* mpUnk114;                                                 // 0x114
    cBubbleSource mBubbleSource;                                    // 0x120
};
// ---- items of slice s01058b60 end

// ---- items of slice s0105a110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_016df2f4;
struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
class cSpaceToolData;
class cOwnerObject;
class cSpatialObject;
class cInteraction;
class cBuilding;
class cArtifact;
class cArtifactSub;
class cPlanet_s0105_a110;
class cCreature;
class cUFO;
class cSPMission;
class cSPSimulatorSpaceGame_s0105_a110;
class cSPSpaceInventory_s0105_a110;
class cSPSpaceInventoryItem_s0105_a110;
class cMessageServer;
class cTerrainEditor;
class cWalkAround;
class cToolManager;
class cSpatialObject {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);       // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual bool Flag2c();                     // +0x2c
};
class cOwnerObject {
public:
    cSpatialObject* FUN_006e87e0();            // 0x006e87e0, [this+0x1e0]
    void FUN_00cb5bb0();                       // 0x00cb5bb0
    uint8_t pad04[0x11c - 0x04];
    uint8_t field11c;                          // +0x11c
};
class cInteraction {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t typeID, void* pObject, int flags);  // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();                       // +0x20
};
class cArtifactSub {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t typeID, void* pObject, int flags);  // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();                       // +0x20
    virtual uint32_t GetID();                  // +0x24
};
class cBuilding {
public:
    uint8_t pad00[0x58];
    cInteraction mInteraction;                 // +0x58
    uint8_t pad5c[0x2b0 - (0x58 + sizeof(cInteraction))];
    uint32_t field2b0;                         // +0x2b0
    uint8_t pad2b4[0xb58 - 0x2b4];
    uint32_t flags_b58;                        // +0xb58
    uint8_t padb5c[0xb67 - 0xb5c];
    uint8_t byte_b67;                          // +0xb67
    bool Flag388();                            // 0x00c0c0e0
    void* FUN_00c0bc00(int a, int b);          // 0x00c0bc00
};
class cArtifact {
public:
    uint8_t pad00[0x224];
    uint32_t field224;                         // +0x224
    uint8_t pad228[0x5d0 - 0x228];
    cArtifactSub mSub5d0;                      // +0x5d0
    cArtifactSub mSub5e8;                      // +0x5e8
    uint8_t pad5ec[0x638 - (0x5e8 + sizeof(cArtifactSub))];
    uint32_t field638;                         // +0x638
    uint8_t pad63c[0x658 - 0x63c];
    int field658;                              // +0x658
    uint8_t byte65c;                           // +0x65c
    uint8_t pad65d;
    uint8_t byte65e;                           // +0x65e
    void* FUN_00ad2620(void* pOut);            // 0x00ad2620
    void* FUN_00c3e1e0(void* pOut);            // 0x00c3e1e0
};
class cPlanet_s0105_a110 {
public:
    uint8_t pad00[0x54];
    uint32_t field54;                          // +0x54
    uint8_t pad58[0x7c - 0x58];
    uint8_t speciesData[0x88 - 0x7c];          // +0x7c
    uint32_t field88;                          // +0x88
};
class cCreature {
public:
    uint8_t pad00[0x54];
    uint32_t field54;                          // +0x54
    uint8_t pad58[0x5e8 - 0x58];
    cArtifactSub mSub5e8;                      // +0x5e8
    void* FUN_00c3e1e0(void* pOut);            // 0x00c3e1e0
};
class cUFO {
public:
    uint8_t pad00[0x714];
    int field714;                              // +0x714
};
class cSPMission {
public:
    uint32_t GetMissionID();                   // 0x01030e10
};
class cSPSpaceInventoryItem_s0105_a110 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14(void*);
virtual void v18();
virtual void v1c();
    uint8_t pad04[0x10 - 0x04];
    uint32_t field10;                          // +0x10
    uint32_t field14;                          // +0x14
    void Construct();                          // 0x00c87660
};
class cSPSpaceInventory_s0105_a110 {
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
    virtual bool v80(cSPSpaceInventoryItem_s0105_a110* pItem, int a, int b);  // +0x80
};
class cSPSimulatorSpaceGame_s0105_a110 {
public:
    cSPSpaceInventory_s0105_a110* GetPlayerInventory();   // 0x00a1ad60
};
class cTerrainEditor {
public:
    cTerrainEditor* GetCurrentTerrainSphere(); // 0x00f67d90
    void FUN_00c77bf0(uint32_t id);            // 0x00c77bf0
};
class cWalkAround {
public:
    bool FUN_01016470(void* pPlant);           // 0x01016470
    void SetHighLODPlant(void* pPlant);        // 0x010166c0
    void* FUN_01015fa0(void* pPlant);          // 0x01015fa0
};
class cToolManager {
public:
    bool CreateToolFromToolID(void* pPropertyList);  // 0x0104e340
};
class cGlobalManager {
public:
    void FUN_00b2c980(void* pObject, int flag);     // 0x00b2c980
};
class cBehaviorManager {
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
    virtual void v38(void* pBehavior);              // +0x38
};
class IAudioSystem {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void* v20();                       // +0x20
};
class ToolHitMessage {
public:
    void Construct(int flags);                 // 0x00421c80
    void Destruct();                           // 0x00421cf0
    struct Slot {
        const void* mpData;
        uint32_t mType;
    };
    uint32_t mVtable;                          // +0x00
    uint32_t mRefCount;                        // +0x04
    Slot mData[5];                             // +0x08
    uint32_t mMessageID;                       // +0x30
    uint32_t pad34;
    uint32_t mFlags;                           // +0x38
    uint32_t pad3c;
};
class cMessageServer {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void MessageSend(uint32_t messageID, void* pMessage, int flags);  // +0x14
};
class cSpaceToolData {
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
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
    virtual void v120();
    uint8_t pad04[0x30 - 0x04];
    void* mpToolProperties;                    // +0x30
    uint8_t pad34[0x114 - 0x34];
    cSpatialObject* mpToolOwner;               // +0x114
    uint8_t pad118[0x124 - 0x118];
    cOwnerObject* mpOwnerObject;               // +0x124
    uint8_t pad128[0x170 - 0x128];
    uint32_t mLastErrorID;                     // +0x170
};
class AutoRefCountIWinText {
public:
    void operator=(void* pText);               // 0x00b5f950
    void* mpText;
};
class cSPToolStrategy_s0105_a110 {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
    bool CanDoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};
class cSPScanToolStrategy_s0105_a110 : public cSPToolStrategy_s0105_a110 {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};
bool __cdecl FUN_01058950(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);  // 0x01058950
void* __cdecl GetActivePlanet();                                  // 0x01021260
cSPSimulatorSpaceGame_s0105_a110* __cdecl SpaceGameGet_s0105_a110();                    // 0x01002bd0
cToolManager* __cdecl NounManager_s0105_a110();                              // 0x00b3d300
void* __cdecl FUN_00c0c380(void* pObject);                        // 0x00c0c380
void* __cdecl FUN_00b3d480();                                     // 0x00b3d480
void* __cdecl FUN_00ace2c0();                                     // 0x00ace2c0
void* __cdecl FUN_00ac9dd0(void* pList, const Vector3& position); // 0x00ac9dd0
void* __cdecl FUN_00acd9d0();                                     // 0x00acd9d0
void* __cdecl FUN_00c52f80(void* pList, const Vector3& position); // 0x00c52f80
void* __cdecl FUN_00c8e7e0(void* pObject);                        // 0x00c8e7e0
void __cdecl FUN_01062e70(void* pTarget, int a, cSpaceToolData* pTool, float f);  // 0x01062e70
void* __cdecl FUN_00c9f040(void* pOwner);                         // 0x00c9f040
void* __cdecl FUN_00b2a390(void* pObject);                        // 0x00b2a390
void* __cdecl FUN_010536c0(void* pObject);                        // 0x010536c0
void* __cdecl FUN_01030e40(void* pObject);                        // 0x01030e40
void* __cdecl FUN_00ae6760(void* pObject);                        // 0x00ae6760
void* __cdecl FUN_00b67720(void* pObject);                        // 0x00b67720
void* __cdecl FUN_00b67740(void* pObject);                        // 0x00b67740
void* __cdecl FUN_00bd8460(void* pObject);                        // 0x00bd8460
void* __cdecl FUN_00b3d3b0();                                     // 0x00b3d3b0
void* __cdecl FUN_00b3d390();                                     // 0x00b3d390
void* __cdecl FUN_01030e60(void* pObject);                        // 0x01030e60
cMessageServer* __cdecl MessageServer();                          // 0x0067dcc0
cBehaviorManager* __cdecl BehaviorManager();                      // 0x00b3d260
void* __cdecl FUN_00b3d420();                                     // 0x00b3d420
void* __cdecl FUN_00b3d450();                                     // 0x00b3d450
void* __cdecl FUN_00c463d0(void* pStack);                         // 0x00c463d0
void* __cdecl FUN_00c77bf0(cTerrainEditor* pEditor, uint32_t id); // 0x00c77bf0
void* __cdecl FUN_00c878d0(void* pObject);                        // 0x00c878d0
void* __cdecl FUN_00ad2620(cArtifact* pArtifact, void* pOut);     // 0x00ad2620
void __cdecl FUN_00ac0cb0(void* pList, void* pSpecies, int a, int b);  // 0x00ac0cb0
void* __cdecl FUN_00acd2d0(void* pObject, void* pArg);            // 0x00acd2d0
void* __cdecl FUN_00b90410(void* pManager, void* pSpecies);       // 0x00b90410
void* __cdecl FUN_0061df40(void* pList, void* pItem);             // 0x0061df40
void* __cdecl operator_new(uint32_t size, const char* pName, int a, int b, int c, int d);  // 0x00f473a0
void* __cdecl FUN_01015df0();                                     // 0x01015df0
bool __cdecl FUN_01016470(void* pPlant);                          // 0x01016470
void* __cdecl FUN_01015fa0(void* pPlant);                         // 0x01015fa0
void* __cdecl FUN_00c3e1e0(cCreature* pCreature, void* pOut);     // 0x00c3e1e0
IAudioSystem* __cdecl GetSystemAT();                              // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t id, void* pAudio);          // 0x00435ed0
int __cdecl SetErrorEvent(cSpaceToolData* pTool, uint32_t eventID, bool post);  // 0x010527f0
bool __cdecl ScanBuilding(void* pBuilding);                       // 0x01058680
bool __cdecl ScanAllSpecies(void* pPlanet);                       // 0x010534c0
bool __cdecl ScanTribe(void* pTribe);                             // 0x01053320
bool __cdecl ScanSpecies(void* pPlanet);                          // 0x01053240
bool __cdecl ScanColony(void* pColony);                           // 0x010533d0
// ---- items of slice s0105a110 end

// ---- items of slice s0105b960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern float g_radius100;                        // 0x013ec4d0 = 100.0f
extern float g_radius10;                         // 0x01473c70 = 10.0f
extern char g_spaceMode;                         // 0x01654c05 (current-game-mode token)
#pragma intrinsic(sqrt)
struct Vector3_s0105_b960 {
    float x, y, z;
    Vector3_s0105_b960() {}
    Vector3_s0105_b960(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3_s0105_b960(const Vector3_s0105_b960& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3_s0105_b960 operator*(const Vector3_s0105_b960& v, float s)
{
    Vector3_s0105_b960 r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}
inline Vector3_s0105_b960 operator-(const Vector3_s0105_b960& a, const Vector3_s0105_b960& b)
{
    Vector3_s0105_b960 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
inline float Length(const Vector3_s0105_b960& v)
{
    return (float)sqrt((double)(v.z * v.z + v.y * v.y + v.x * v.x));
}
inline float Distance(const Vector3_s0105_b960& a, const Vector3_s0105_b960& b)
{
    return Length(a - b);
}
struct Quaternion { float x, y, z, w; };
struct Matrix33 { float m[9]; };                 // 0x24 bytes
inline bool KeyEquals(const ResourceKey& a, const ResourceKey& b)
{
    return a.mInstanceID == b.mInstanceID && a.mTypeID == b.mTypeID && a.mGroupID == b.mGroupID;
}
struct XformMsg_s0105_b960 {
    uint16_t  mFlags;                            // +0x00
    uint16_t  mCount;                            // +0x02
    Vector3_s0105_b960   mPos;                              // +0x04
    float     mScale;                            // +0x10
    Matrix33  mMat;                              // +0x14
    XformMsg_s0105_b960();
    void SetPos(const Vector3_s0105_b960& v);               // 0x00571d40
    void SetRot(const Matrix33& r)               // inline in the original
    {
        mMat = r;
        mFlags |= 2;
        ++mCount;
    }
};
extern ResourceKey k_placeuberturret;            // 0x016e1db4 (zero-filled .bss key)
class cGameObject_s0105_b960;
class cSpaceToolData_s0105_b960;
class cLocatable;
class cGameNounManager_s0105_b960;
class cSpaceGame;
class cPlanetModel_s0105_b960;
class cAvatar;
class cEffectsManager;
class cEffectInstance;
class cEffectFactory;
cGameNounManager_s0105_b960* NounManager_s0105_b960();                                     // 0x00b3d300
void* GetCurrentGameMode();                                          // 0x00b5b800
cSpaceGame* SpaceGameGet_s0105_b960();                                          // 0x01002bd0
cPlanetModel_s0105_b960* PlanetModel_s0105_b960();                                         // 0x00b3d350 (getter)
class cGameTerrainCursor* GetGameTerrainCursor();                     // 0x00b30d70
cEffectsManager* EffectsManagerPtr();                                 // 0x0067ddd0
uint32_t GetPlayerEmpireID();                                         // 0x01021090
void* __cdecl EAOperatorNew(size_t size, const char* name, int flags, int debugFlags, int file, int line);
inline void* operator new(size_t n, const char* name, int flags, int debugFlags, int file, int line)
{
    return EAOperatorNew(n, name, flags, debugFlags, file, line);
}
void FUN_00fdc340(const Vector3_s0105_b960& position, float radius);             // 0x00fdc340
void FUN_010527f0(cSpaceToolData_s0105_b960* pTool, uint32_t errorID, int show);  // 0x010527f0
void FUN_01058c90();                                                  // 0x01058c90 (marker callback)
class cSpaceCombatTuning* GetSpaceCombatTuning();                     // 0x01029940
cGameObject_s0105_b960* FUN_00ac9310(void** begin, const Vector3_s0105_b960& position, bool);  // 0x00ac9310
bool FUN_0105a050(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);  // 0x0105a050
void GetPropertyAsKeyInstance(void* propertyList, uint32_t key, void** out);  // 0x006a12a0
Matrix33& QuaternionToMatrix(Matrix33& out, const Quaternion& q);     // 0x004a9b40
void FUN_00ff8560(void* impact, const Vector3_s0105_b960& position, float health);  // 0x00ff8560
void FUN_0102b780(void* impact, const Vector3_s0105_b960& position);             // 0x0102b780
class cLocatable {                                // transform sub-object (embedded at +0x34 / +0x120)
public:
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
virtual void v0a();
    virtual const Vector3_s0105_b960* GetPosition();                        // +0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
    virtual bool IsActive();                                     // +0x58
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
    virtual void v1b();
    virtual float GetRadius();                                   // +0x70
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cGameObject_s0105_b960* Cast(uint32_t typeID);                  // +0xb8
};
class cGameObject_s0105_b960 {
public:
    virtual void AddRef();                                       // +0x00
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void Release();                                      // +0x04
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual uint32_t GetPoliticalID();                           // +0x4c
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cGameObject_s0105_b960* Cast(uint32_t typeID);                  // +0xb8
    uint32_t pad04[(0x34 - 0x04) / 4];                           // +0x04
    cLocatable mLocation;                                        // +0x34
    void FUN_00c389c0(int a, int b);                             // 0x00c389c0
};
class cSpaceToolData_s0105_b960 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual const ResourceKey& GetToolID();                      // +0x18
    virtual void* CreateImpact();                                 // +0x1c (no stack args)
    uint32_t pad20[(0x30 - 0x04) / 4];                            // +0x04
    void* mpToolProperties;                                      // +0x30 (property list)
    uint32_t pad34[(0x114 - 0x34) / 4];                           // +0x34
    cLocatable* mpToolOwner;                                     // +0x114 (owner transform)
    uint32_t pad118[(0x124 - 0x118) / 4];                         // +0x118
    cGameObject_s0105_b960* mpOwnerObject;                                  // +0x124
    uint32_t pad128[(0x170 - 0x128) / 4];                         // +0x128
    uint32_t mLastErrorID;                                       // +0x170
    float FUN_0104bdb0();                                        // 0x0104bdb0 (first scalar, ecx = this)
};
class cPlanetModel_s0105_b960 {
public:
    bool FUN_00b7e3e0(const Vector3_s0105_b960& position);                   // 0x00b7e3e0
    const Vector3_s0105_b960* FUN_00b81630(Vector3_s0105_b960* out, const Vector3_s0105_b960& position);  // 0x00b81630
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3_s0105_b960& position);  // 0x00b7f190
};
class cSpaceCombatTuning {
public:
    float GetColonyObjectHealth();                                // 0x0102a7f0
};
class cGameNounManager_s0105_b960 {
public:
    void* GetGameDataVector(void* fn1, void* fn2, void* fn3, void* fn4, void* key);  // 0x00b21340
};
class cGameDataVector {
public:
    void* mpAllocator;                                            // +0x00
    cGameObject_s0105_b960** mpBegin;                                        // +0x04
    cGameObject_s0105_b960** mpEnd;                                          // +0x08
};
class cAvatar {
public:
    void FUN_00ff88c0(const Vector3_s0105_b960& position, cEffectInstance* effect);  // 0x00ff88c0
    void FUN_00ff6450(const Vector3_s0105_b960& position);                    // 0x00ff6450
};
class cSpaceGame {
public:
    uint32_t pad00[(0x54 - 0x00) / 4];                             // +0x00 (space game has no vptr slot used)
    cAvatar* GetAvatar();                                          // 0x00b1fdb0 ([this+0x54])
};
class cEffectInstance {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Enable(int flag);                                   // +0x08
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void SetXform(const XformMsg_s0105_b960* msg);                      // +0x18
};
class cEffectFactory {
public:
    virtual void v00();
    virtual void v01();
    virtual bool CreateInstance(void* key, int unused, cEffectInstance** out);  // +0x08
};
class cEffectsManager {
public:
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
virtual void v0a();
    virtual void CreateEffectAt(uint32_t effectID, const Vector3_s0105_b960* position,
                                cEffectInstance** out);              // +0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void v14();
    virtual cEffectFactory* GetFactory(uint32_t effectID);           // +0x54
};
class cGameTerrainCursor {
public:
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
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
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
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
    virtual void v34();
    virtual cGameObject_s0105_b960* GetHoverObject();                           // +0xd4
};
class cSPToolStrategy_s0105_b960 {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);  // 0x0105a110 (cSPToolStrategy::DoToolAction)
    void StartTool(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3);          // 0x010568b0
    char OnHit(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int hitType, int);    // 0x010593e0
};
class cSPDefaultProjectileWeapon : public cSPToolStrategy_s0105_b960 {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);  // 0x0105b350
};
namespace Simulator_s0105_b960 {
class SimSingleton {
public:
    uint32_t pad00[0x18 / 4];                                    // +0x00
    uint32_t mPlayerEmpireID;                                    // +0x18
    uint32_t pad1c[(0xc8 - 0x1c) / 4];

    SimSingleton();                                              // 0x00ae5c30
    void* AddMarker(void* callback, int empireID, const Vector3_s0105_b960* position, int kind,
                    uint32_t typeID, void* info, const Quaternion* orientation, int flag);  // 0x00ae49d0

    static SimSingleton* sInstance;                              // 0x0167a60c
    static __forceinline SimSingleton* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        return sInstance;
    }
};
}
using Simulator_s0105_b960::SimSingleton;
class cSPCityMarkerStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
class cSPPlaceObjectStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
class cSpaceCity {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    uint32_t pad04[(0x120 - 0x04) / 4];                           // +0x04
    cLocatable mLocation;                                         // +0x120
};
class cSPPlaceObjectToolStrategy_s0105_b960 : public cSPPlaceObjectStrategy {
public:
    bool CanUseToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3);  // 0x01053980
    bool CanUseToolAtLocation(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3);  // 0x0105ba00 (cSPPlaceObjectToolStrategy::CanUseToolAtLocation)
};
class cSPArtilleryWeaponStrategy : public cSPToolStrategy_s0105_b960 {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
struct tErasedCityRecord {                         // 0x14-byte element of the list at +0x2b8
    Vector3_s0105_b960 mPosition;                             // +0x00
    float   mEffectHeight;                         // +0x0c
    uint32_t mPad10;                               // +0x10
};
struct tErasedCityList {
    tErasedCityRecord* mpBegin;                    // +0x00
    tErasedCityRecord* mpEnd;                      // +0x04
    tErasedCityRecord* mpCapacity;                 // +0x08
    void FUN_00bdf3e0();                           // 0x00bdf3e0 (append a default element)
};
class cErasedCityObject {
public:
    uint32_t pad00[0x2b8 / 4];
    tErasedCityList mRecords;                      // +0x2b8
};
class cSPMindEraseToolStrategy : public cSPToolStrategy_s0105_b960 {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
class cSPGenesisDeviceToolStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
class cCropCirclesToolStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4);
};
// ---- items of slice s0105b960 end

// ---- items of slice s010554c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator_s0105_54c0 {
struct cSimRegistrationBase {
    cSimRegistrationBase(int);                // 0x00692f60
    virtual ~cSimRegistrationBase();
    bool IsRegistered();                      // 0x00ab30c0
    void Register();                          // 0x00692850
    uint32_t mData[4];
};
}
namespace Simulator_s0105_54c0 {
template <int N>
struct cSimRegistration : cSimRegistrationBase {
    cSimRegistration() : cSimRegistrationBase(0) {}
    virtual ~cSimRegistration();
};
}
namespace Simulator_s0105_54c0 {
#define STATIC_REGISTRATION(N) \
    static cSimRegistration<N> sRegistration##N; \
    if (!sRegistration##N.IsRegistered()) sRegistration##N.Register();
}
// ---- items of slice s010554c0 end

// ---- items of slice s01056160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_16e2090;
extern void* g_13f94d4;
extern void* g_16e1f94;
extern void* g_16e1f98;
extern void* g_16e1f9c;
extern void* g_16e1ce8;
extern void* g_16e1cec;
extern void* g_16e1cf0;
extern void* g_16e1e2c;
extern void* g_16e1e30;
extern void* g_16e1e34;
extern void* g_16e1d18;
extern void* g_16e1d90;
class IRefCounted_s0105_6160 {
public:
    virtual void v00();
    virtual void AddRef();                        // 0x04
    virtual void Release();                       // 0x08
    virtual void SetEnabled(int bEnabled);        // 0x0c
    virtual bool IsAlive();                       // 0x10
    virtual void* Query(const void* pType);       // 0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v2c();
    virtual Vec3* GetPosition(Vec3* pOut);        // 0x30
    virtual Vec3* GetDirection(Vec3* pOut);       // 0x30
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual float v58();                          // 0x58
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
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void* vb8(const void* pType);         // 0xb8  cached interface lookup
};
class cSPSpaceInventoryItem_s0105_6160 : public IRefCounted_s0105_6160 {
public:
    uint8_t mPad04[0x34];        // 0x04..0x38
    float mValue38;              // 0x38  comparison value (scan/repair progress)
    uint8_t mPad3c[0x6d8];       // 0x3c..0x714
    uint32_t mFlags714;          // 0x714
    uint8_t mPad718[0xdc];       // 0x718..0x7f4
    float mEnergyMax;            // 0x7f4
    float mEnergyCurrent;        // 0x7f8
};
class cSPInteractableObject {
public:
    uint8_t mPad00[0x14];        // 0x00..0x14
    int mObjectType;             // 0x14  eInteractableObjectType
};
class cSPSimulatorSpaceGame_s0105_6160 {
public:
    void* GetPlayerInventory();  // 0x00a1ad60 (cSPSimulatorSpaceGame::GetPlayerInventory)
    void* GetPlayerUFO();
    void* GetPlayerEmpire();
    uint8_t mPad00[0x20];
};
void* GetUFOSimulator();                 // 0x00ffbe50
void* SpaceGameGetRaw();                 // 0x01002bd0
void* GetUniverseContext();              // 0x01021080
int   GetPlayerEmpire();                 // cSPLivingUniverse::GetPlayerEmpire
void* __fastcall PlanetModelGet();       // 0x00b3d350 (result in eax)
int __fastcall GameDataBigCountList(void* self, void* pGameData);  // 0x00b20470
void  __fastcall FUN_00f67d90(void* self);   // GetCurrentTerrainSphere (this = NounManager)
class cSPToolStrategy_s0105_6160 {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void* GetToolKey();   // 0x18  returns pointer to a 3-dword resource Key
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30(int a, int b, int c, int d);   // 0x30  ShowToolEventLog
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48(int a, int b);   // 0x48
    virtual void v4c();

    // 0x00 vftable
    uint8_t mPad04[0x30];
    void* mpPlanet;                           // 0x34
    uint8_t mPad38[0x28];
    void* mpChargeObject;                     // 0x60
    uint8_t mPad64[0x1c];
    uint8_t mbActive;                         // 0x80
    uint8_t mPad81[0x2f];
    IRefCounted_s0105_6160* mpToolEffectA;               // 0xb0
    IRefCounted_s0105_6160* mpToolEffectB;               // 0xb4
    uint8_t mPadB8[0x10];
    cSPTimer mTimer;                          // 0xc8
    uint8_t mPadD8[0x3c];
    cSPSpaceInventoryItem_s0105_6160* mpTargetItem;      // 0x114
    uint32_t mStrategyClassID;                // 0x118
    uint8_t mPad11c[0x4];
    IRefCounted_s0105_6160* mpAreaEffect;                // 0x120
    uint8_t mPad124[0x1c];
    IRefCounted_s0105_6160* mpActiveObject;              // 0x140
    uint8_t mPad144[0x2c];
    int mEventType;                           // 0x170
};
class cSPDefaultAoETool_s0105_6160 : public cSPToolStrategy_s0105_6160 {
public:
    bool StartTool(int nToolId, int nTarget, int nFlags);   // 0x01056b50
};
class cSPRepairAOEToolStrategy : public cSPToolStrategy_s0105_6160 {
public:
    bool StartTool(int nToolId, int nTarget, int nFlags);   // 0x01056c70
};
bool __stdcall CanUseTool_56160(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut);
bool __stdcall StartTool_568b0(cSPToolStrategy_s0105_6160* self, int nTarget, int nFlags);
int __stdcall SetErrorEvent_527f0(cSPToolStrategy_s0105_6160* self, int nEventType, int bPost);
void __stdcall AppendScanResult_52880(void* pList, int* pOut);
int __fastcall GetTextAt_4c4f0(void* node);
void* __fastcall FUN_00ff3f10(void* self);
void __fastcall FUN_00b3d510(void* self);
void __fastcall FUN_00c389c0(void* self, int a, int b);
void __fastcall FUN_00bc3110(void* self);
void* __fastcall FUN_01050640(void* self);
void __fastcall FUN_00c75630(void* self);
void __fastcall FUN_00c73cf0(void* self, int a);
float __cdecl FUN_00c375d0(void* a);
float fun_sqrt(float x);
void* __fastcall FUN_00c37360();
float __fastcall FUN_00fb7ba0(void* self);
bool __fastcall FUN_00b7e3e0(void* self);
Vec3* __fastcall FUN_00b81630(void* self, Vec3* pOut);
void* __fastcall FUN_00b894a0(void* self, Vec3* pOut);
bool __fastcall FUN_00bd9c00(void* self, Vec3* pOut);
void* __stdcall FUN_00b3d390(int v);
int __fastcall FUN_0104c4f0(void* node);// 0x00bc3130 cSPTimer::Restart(void* self)
void __fastcall FUN_00bc3130(void* self);
void __fastcall FUN_00bfc470(void* self, int a);
void __fastcall FUN_00b71fb0(void* a, int b);
void* __fastcall MessageServer_s0105_6160();
void __fastcall SlotMessageConstruct(void* self, int id);
void __fastcall SlotMessageDestruct(void* self);
extern uint8_t g_15b743d;
void* __fastcall AppSystem();
// ---- items of slice s01056160 end

// ---- items of slice s010593e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(fabs)
#pragma intrinsic(_InterlockedExchange)
struct Vector3_s0105_93e0 {
    float x, y, z;
    Vector3_s0105_93e0() {}
    Vector3_s0105_93e0(const Vector3_s0105_93e0& v) : x(v.x), y(v.y), z(v.z) {}
    float SquaredLength() const { return z * z + y * y + x * x; }
};
inline Vector3_s0105_93e0 operator-(const Vector3_s0105_93e0& a, const Vector3_s0105_93e0& b) {
    Vector3_s0105_93e0 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
struct ResourceKey_s0105_93e0 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey_s0105_93e0() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
};
class cPlanet_s0105_93e0;
class cBeamProjectile;
class cSpaceToolData_s0105_93e0 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual const ResourceKey_s0105_93e0& GetToolID();                         // +0x18
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
    virtual ResourceKey_s0105_93e0 GetStrategyKey();                           // +0x38

    uint32_t pad04[(0x30 - 0x04) / 4];
    int mbEnabled;                                                  // +0x30
    uint32_t pad34[(0x114 - 0x34) / 4];
    class cGameObject_s0105_93e0* mpToolOwner;                                 // +0x114
    uint32_t pad118[(0x124 - 0x118) / 4];
    cBeamProjectile* mpBeamProjectile;                              // +0x124

    float GetEffectRadius();                                        // 0x0104bdb0
    bool HasFlag8();                                                // 0x0104cd40
    bool HasFlag10();                                               // 0x0104cd50
    int GetTerrainColorIndex();                                     // 0x0104bf70
    int GetWaterColorIndex();                                       // 0x0104bf80
    int GetAtmosphereColorIndex();                                  // 0x0104bf90
    float GetDamage();                                              // 0x0104bdc0
    float GetRelationshipDelta();                                   // 0x0104beb0
    float GetGalacticRelationshipDelta();                           // 0x0104bec0
    float GetGalacticRelationshipRadius();                          // 0x0104bed0
    float GetHitGroundAtmosphereVelocity();                         // 0x0104c040
    float GetHitGroundWaterVelocity();                              // 0x0104c050
    float GetHitGroundTemperatureVelocity();                        // 0x0104c060
    float GetHitWaterAtmosphereVelocity();                          // 0x0104c070
    float GetHitWaterWaterVelocity();                               // 0x0104c080
    float GetHitWaterTemperatureVelocity();                         // 0x0104c090
    float GetHitCombatantAtmosphereVelocity();                      // 0x0104c0a0
    float GetHitCombatantWaterVelocity();                           // 0x0104c0b0
    float GetHitCombatantTemperatureVelocity();                     // 0x0104c0c0
    float GetHitAirAtmosphereVelocity();                            // 0x0104c0d0
    float GetHitAirWaterVelocity();                                 // 0x0104c0e0
    float GetHitAirTemperatureVelocity();                           // 0x0104c0f0
    float GetDamageRadius();                                        // 0x00ce6930
};
class cBeamProjectile {
public:
    uint32_t pad00[0x16c / 4];
    uint8_t mb16c;                                                  // +0x16c
    uint8_t mb16d;                                                  // +0x16d
    bool HasTarget();                                               // 0x00cb5ba0
    void GetEndPoints(Vector3_s0105_93e0* start, Vector3_s0105_93e0* end);                // 0x00cb8ba0
};
class cSpaceShip {                                                  // owner cast target 0xb033b403
public:
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
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual uint32_t GetPoliticalID();                              // +0x4c
    uint32_t pad04[(0x714 - 0x04) / 4];
    int mnDisabled;                                                 // +0x714
};
class cGameObject_s0105_93e0 {
public:
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
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
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
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cSpaceShip* Cast(uint32_t typeID);                      // +0xb8
};
class cTerraformingManager {
public:
    void AddAtmosphere(cPlanet_s0105_93e0* planet, float amount);              // 0x00bbc340
    void AddWater(cPlanet_s0105_93e0* planet, float amount);                   // 0x00bbc370
    void AddTemperature(cPlanet_s0105_93e0* planet, float amount);             // 0x00bbc3c0
    void ApplyAt(Vector3_s0105_93e0* position, float radius);                  // 0x00bbec40
};
cTerraformingManager* TerraformingManager();                        // 0x00b3d430
namespace SP {
class cBeamTarget {
public:
    virtual void AddRef();                                          // +0x00
    virtual void Release();                                         // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool IsValid();                                         // +0x2c
    uint8_t pad04[0x154 - 0x04];
    uint8_t mb154;                                                  // +0x154
};
}
namespace SP {
template<class T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    __forceinline AutoRefCount& operator=(T* pObject) {
        if (mpObject != pObject) {
            if (pObject) pObject->AddRef();
            T* pOld = mpObject;
            mpObject = pObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    __forceinline operator T*() const { return mpObject; }
    __forceinline T* operator->() const { return mpObject; }
};
}
namespace SP {
class IRefCounted_s0105_93e0 {
public:
    virtual void v00();
    virtual void AddRef();                                          // +0x04
    virtual void Release();                                         // +0x08
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
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
    virtual void vb4();
    virtual void* vb8(const void* pType);                           // +0xb8
};
}
namespace SP {
class cSPToolStrategy_s0105_93e0 {
public:
    bool OnHit(cSpaceToolData_s0105_93e0* pTool, const Vector3_s0105_93e0& position, int hitType, int);
    uint32_t pad00[0x114 / 4];
    IRefCounted_s0105_93e0* mpTargetItem;                                      // +0x114
    uint32_t pad118[(0x124 - 0x118) / 4];
    cBeamTarget* mBeamTarget;                                       // +0x124
    bool FUN_0104cd50();                                            // 0x0104cd50
};
}
namespace SP {
class cSPDefaultBeamTool_s0105_93e0 {
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
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void v48(cSPToolStrategy_s0105_93e0* self, const Vector3_s0105_93e0* position);   // +0x48
    bool StartTool(cSPToolStrategy_s0105_93e0* self, const Vector3_s0105_93e0& position, int flags);
};
}
namespace SP {
bool __stdcall StartTool_568b0(cSPToolStrategy_s0105_93e0* self, const Vector3_s0105_93e0& position, int flags);  // 0x010568b0
}
namespace SP {
void __stdcall CreatePanicBubbleForTool(cSPToolStrategy_s0105_93e0* self, Vector3_s0105_93e0 position);           // 0x01059170
}
namespace SP {
class cGlobalManager_s0105_93e0 {
public:
    void FUN_00b7c160(int value);                                   // 0x00b7c160
};
}
namespace SP {
cGlobalManager_s0105_93e0* FUN_00b3d3c0_s0105_93e0();                                     // 0x00b3d3c0
}
namespace SP {
class cSPDefaultAoETool_s0105_93e0 : public cSPToolStrategy_s0105_93e0 {
public:
    bool DoToolAction(cSpaceToolData_s0105_93e0* pTool, const Vector3_s0105_93e0& position, int hitType, int);  // 0x0105a100 (SP::cSPDefaultAoETool::DoToolAction)
};
}
namespace SP {
bool __stdcall OnHitTool(cSpaceToolData_s0105_93e0* pTool, const Vector3_s0105_93e0& position, int hitType, int);  // 0x010593e0
}
// ---- items of slice s010593e0 end

// ---- items of slice s0105aa50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_oneF;                                                   // 0x01485720
#define P(n) virtual void pad##n();
#define P4(a) P(a##0) P(a##1) P(a##2) P(a##3)
#define P8(a) P4(a##x) P4(a##y)
struct Vec3_s0105_aa50 { float x, y, z; };
struct Unk {
    virtual void p0();
    virtual void p1();
    virtual void Release();
};
struct Item {
    P(i0) P(i1) P(i2) P(i3) P(i4) P(i5)
    virtual int GetN();                // +0x18
    char pad4[0x10 - 4];
    int f10;
    int type;
    char pad18[0x20 - 0x18];
    int f20;
};
struct Inv {
    P4(a) P4(b) P4(c) P4(d) P4(e) P4(f)
    P(g0)
    virtual int Find(int type, int n);                        // +0x64 (slot 25)
    P(h0) P(h1) P(h2) P(h3) P(h4)
    virtual bool Take(int handle, void** out, int count);     // +0x7c (slot 31)
    Item* Current();                                          // 0x00ff3f10
    void Refresh();                                           // 0x00ff3e80
};
struct ArtSub {
    P8(a) P4(b) P(c0) P(c1)
    virtual void SetPos(Vec3_s0105_aa50* p);                                         // +0x38 (slot 14)
};
struct Artifact {
    char pad0[0x34];
    ArtSub sub;                                                           // +0x34
    char pad1[0x638 - 0x34 - 4];
    int f638;
    void Init1();                                                         // 0x00c69090
    void Set(int type, int n, int f10, int one);                          // 0x00c74d30
    int Dir(Vec3_s0105_aa50* out);                                                   // 0x00ad2620
};
struct GameDataVec;
struct Nm {
    Artifact* Get();                                                      // 0x0103a080
    GameDataVec* GetGameDataVector(int a, int b, int c, int d, void* e);  // 0x00b21340
};
struct Empire;
struct Planet {
    char pad[0x13c];
    int f13c;
    bool Fb7e3e0(Vec3_s0105_aa50* p);                                               // 0x00b7e3e0
    Empire* F00c71e30();                                                 // 0x00c71e30
};
struct Empire { char pad[0x84]; int f84; };
struct Game {
    Inv* GetPlayerInventory();                // 0x00a1ad60
    void* f5180(int n);                       // 0x01005180
    void* GetAvatar();                        // 0x00b1fdb0
    void* F1003480();                         // 0x01003480
};
Game* SpaceGameGet_s0105_aa50();                                                     // 0x01002bd0
Nm* NounManager_s0105_aa50();                                                        // 0x00b3d300
struct ItemBase {
    P8(a) P8(b) P8(c) P8(d) P8(e) P4(f) P(g0) P(g1)
    virtual void* FindPlugin(int key);                                // +0xb8 (slot 46)
};
struct Strategy {
    P(a0)
    virtual void Slot1();                                             // +0x04
    P(a2) P(a3) P(a4) P(a5)
    virtual void* GetKey();                                           // +0x18 action key (int[3])
    P8(b) P8(c) P(d0) P(d1)
    virtual bool Slot64(void* z);                                     // +0x64
    P8(e) P8(f) P4(g)
    char pad0[0x14 - 4];
    int f14;                                                          // +0x14
    char pad1[0x114 - 0x18];
    ItemBase* item;                                                   // +0x114 held item sub-object
    bool CanUse();                                                    // 0x0104cbc0
    void SetValue(int v);                                             // 0x0104cc00
    int GetCount();                                                   // 0x00a02d30
    float GetRate();                                                  // 0x00ce6940
};
struct RepairObj {
    char pad0[0x714];
    int f714;                                                         // +0x714
    char pad1[0x7f4 - 0x718];
    float f7f4;                                                       // +0x7f4
    float f7f8;                                                       // +0x7f8
    float Repair(float amount);                                       // 0x00c389f0
};
struct Combatant {
    P8(a) P8(b) P4(c) P(d0) P(d1)
    virtual float Slot58();                                           // +0x58
    char pad0[0x38 - 4];
    float f38;                                                        // +0x38
    void PartialRepair(float amount);                                 // 0x00bfd1a0
};
struct FVec8 {
    char pad[0xc];
    float* mData;                                                     // +0x0c element array
    void resize(uint32_t n);                                          // 0x007eb820
};
struct WalkAround { void GetOutOfUFO(); };                            // 0x01016070
struct WM {
    P(b0)
    virtual void* Slot1();                                            // +0x04
    P8(c) P8(d) P(e0)
    virtual void Slot4c(int a, void* b);                              // +0x4c (slot 19)
};
struct GDSub {
    P8(a) P(b0) P(b1) P(b2)
    virtual void* Slot2c();                                           // +0x2c (slot 11)
};
struct GDElem {
    P8(a) P(b0) P(b1) P(b2)
    virtual void* Slot2c();                                           // +0x2c of the element itself
    char pad[0x34 - 4];
    GDSub sub;                                                        // +0x34
    int ProfLeaveZone();                                              // 0x00bd9e30
};
struct ColonySub {
    P8(a) P(b0) P(b1) P(b2)
    virtual void* Position();                                         // +0x2c (slot 11)
    P(c0) P(c1)
    virtual void SetPosition(Vec3_s0105_aa50* p);                                // +0x38 (slot 14)
    P8(d) P4(e) P(f0)
    virtual float Radius();                                           // +0x70 (slot 28)
};
struct ColonyObj {
    virtual void Slot0();                                             // +0x00
    virtual void Slot1();                                             // +0x04
    P8(a) P8(b) P8(c) P8(d) P8(e) P4(f)
    virtual void* SlotB8(int key);                                    // +0xb8 (slot 46)
    char pad[0x34 - 4];
    ColonySub sub;                                                    // +0x34
};
struct Cursor {
    P8(a) P8(b) P8(c) P8(d) P8(e) P8(f) P(g0) P(g1) P(g2) P(g3) P(g4)
    virtual void* SlotD4();                                           // +0xd4 (slot 53)
};
struct GameDataVec { char pad[4]; void** mBegin; void** mEnd; };
bool __stdcall OnHit(void* self, void* a2, int a3, int zero);          // 0x010593e0 cSPToolStrategy::OnHit
bool __stdcall CanUseToolBase(void* self, Vec3_s0105_aa50* pos, int a3);          // 0x01053980 cSPToolStrategy::CanUseToolAtLocation
int SetErrorEvent(void* self, int key, int flag);                      // 0x010527f0 cSPToolStrategy::SetErrorEvent
Planet* PlanetModel_s0105_aa50();                                                 // 0x00b3d350
Cursor* GetGameTerrainCursor_s0105_aa50();                                        // 0x00b30d70
WalkAround* F1015df0();                                                // 0x01015df0
WM* WindowManager();                                                   // 0x0067caa0
// ---- items of slice s0105aa50 end

// ---- items of slice s010554c0_tools begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3Rows_s0105_54c0__tools {
    float m[9];
    void Assign(const Matrix3Rows_s0105_54c0__tools* pOther);   // 0x0041cb40
};
extern Vector3 gZeroVector;                   // 0x016e1b14
extern Vector3 gDefaultPosition;              // 0x016e20fc
extern Matrix3Rows_s0105_54c0__tools gDefaultBasis;             // 0x016e20d8
class XformMsg_s0105_54c0__tools {
public:
    XformMsg_s0105_54c0__tools()
    {
        mFlags = 0;
        mCount = 0;
        mPosition.x = gDefaultPosition.x;
        mPosition.y = gDefaultPosition.y;
        mPosition.z = gDefaultPosition.z;
        mScale = 1.0f;
        mBasis.Assign(&gDefaultBasis);
    }

    uint16_t mFlags;      // +0x00
    uint16_t mCount;      // +0x02
    Vector3 mPosition;    // +0x04
    float mScale;         // +0x10
    Matrix3Rows_s0105_54c0__tools mBasis;   // +0x14
};
class cSPNoun_s0105_54c0__tools;
class cSPAimObject_s0105_54c0__tools;
class IEffect_s0105_54c0__tools;
class cEffectsManager_s0105_54c0__tools;
class IEffect_s0105_54c0__tools {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void Release();                                      // +0x04
    virtual void Detach(int32_t nValue);                         // +0x08
    virtual void* Slot0c(void* pOut);                            // +0x0c
    virtual void* Slot10(void* pOut);
    virtual void* Slot14();
    virtual void Send(XformMsg_s0105_54c0__tools* pMsg);                           // +0x18
};
class cSPAimObject_s0105_54c0__tools {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                              // +0x2c
};
class cSPNoun_s0105_54c0__tools {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void Release();                                      // +0x04
    virtual bool Slot08();                                       // +0x08
    virtual void* Slot0c(uint32_t nNounId);                      // +0x0c
};
class cEffectsManager_s0105_54c0__tools {
public:
    virtual void* Slot00();                                      // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual bool CreateEffect(uint32_t nEffectId, int32_t nFlags,
                              IEffect_s0105_54c0__tools** ppEffect);               // +0x2c
};
class cGameNounManager_s0105_54c0__tools {
public:
    cSPNoun_s0105_54c0__tools* CreateNoun(uint32_t nNounId);                       // 0x00b20c60
};
class cSpaceToolData_s0105_54c0__tools {
public:
    int32_t GetEffectId() const;                                 // 0x0104bf40

    uint8_t mPad000[0x114];       // +0x000
    cSPAimObject_s0105_54c0__tools* mpToolOwner;    // +0x114
    uint8_t mPad118[0x3c];        // +0x118
    Vector3 mPressedAt;           // +0x154
    Vector3 mReleasedAt;          // +0x160
    IEffect_s0105_54c0__tools* mpEffect;            // +0x16c
    uint8_t mPad170[0xbc];        // +0x170
    int32_t mEffectId;            // +0x22c
};
class cSPDragInputProjectileToolStrategy {
public:
    bool OnMouseUp(cSpaceToolData_s0105_54c0__tools* pTool);
};
class cSPDeepSpaceProjectileToolStrategy {
public:
    bool StartTool(cSpaceToolData_s0105_54c0__tools* pTool, const Vector3* pDirection,
                   void* pParam);
};
cGameNounManager_s0105_54c0__tools* __cdecl NounManager_s0105_54c0__tools();                         // 0x00b3d300
cEffectsManager_s0105_54c0__tools* __cdecl EffectsManagerPtr_s0105_54c0__tools();                    // 0x0067ddd0
void __cdecl LaunchProjectile(cSpaceToolData_s0105_54c0__tools* pTool, void* pProjectile,
                              const Vector3* pOrigin,
                              const Vector3* pDirection);        // 0x010543e0
Matrix3Rows_s0105_54c0__tools* __cdecl Matrix3FromFacingAndUp_s0105_54c0__tools(Matrix3Rows_s0105_54c0__tools* pOut,
                                            const Vector3* pFacing,
                                            const Vector3* pUp);  // 0x0069b440
// ---- items of slice s010554c0_tools end

// @ 0x010527f0
int cSPToolStrategy::SetErrorEvent(int nEventType, bool bPost)
{
    int nResult = 0;
    if (bPost && mEventType != nEventType) {
        mEventType = nEventType;
        cSPUIEventLog* pLog = EventLog(nEventType);
        pLog->RemoveAllEventsOfSameType(nEventType);
        pLog = EventLog(nEventType, 0x131a9f54, 0, 0, 1, 0);
        nResult = pLog->PostFeedbackEvent(nEventType, 0x131a9f54, 0, 0, 1, 0);
        PlayUiSound("Ui_spg_target_error");
        KillSetiEffects();
    }
    return nResult;
}

// @ 0x01052880
void AppendScanResult(void* pList, int* pOut)
{
    if (pOut == nullptr)
        return;
    // The list drops its previous front element, then reports the new size.
    *(int*)pList = *(int*)pList;
    *pOut = *(int*)pList;
}

// @ 0x01052f00
Vec3* cSPToolStrategy::GetMouseWorldPosition(Vec3* pOut)
{
    cSPSimulatorSpaceGame* pGame = GetActiveSpaceGame();
    cSPSpaceInventory* pInventory = pGame->GetPlayerInventory();
    cSPSpaceInventoryItem* pItem = nullptr;
    if (pInventory != nullptr)
        pItem = pInventory->mpHeldItem;

    IVectorItem* pRay = (IVectorItem*)NounManager();
    Vec3* pResult = pRay->GetPosition(pOut);
    pOut->mX = pResult->mX;
    pOut->mY = pResult->mY;
    pOut->mZ = pResult->mZ;
    return pOut;
}

// @ 0x01052f90
void GetMouseRay(Vec3* pOut)
{
    IVectorItem* pRay = (IVectorItem*)NounManager();
    Vec3 local;
    Vec3* pResult = pRay->GetPosition(&local);
    pOut->mX = pResult->mX;
    pOut->mY = pResult->mY;
    pOut->mZ = pResult->mZ;
}

// @ 0x010531b0
void ShowScanEventLog(int pData, int a, int b, int pCallback, int nTextId)
{
    (void)a;
    (void)b;
    if (pData == 0)
        return;

    cSPUIEventLog* pLog = EventLog(0x6e000a7a, pData);
    int nEventId = pLog->GetEventInstanceID(0x6e000a7a, pData);
    if (nEventId != 0) {
        EventLog(nEventId)->RestartTimer(nEventId);
        return;
    }

    pLog = EventLog(0x6e000a7a, 0x131a9f54, 0, 0, 1, 0);
    nEventId = pLog->PostFeedbackEvent(0x6e000a7a, 0x131a9f54, 0, 0, 1, 0);
    EventLog(nEventId, nTextId)->ModifyEventText(nEventId, nTextId);
    EventLog(nEventId, pData)->ModifyData(nEventId, pData);
    if (pCallback != 0)
        EventLog(nEventId, pCallback)->RegisterCloseCallback(nEventId, (void*)pCallback);
}

// @ 0x01053240
int ScanSpecies(cPlanet* pPlanet)
{
    gSpaceToolFlags[10] = (int)pPlanet;
    cPlanetSpecies* pSpecies = pPlanet->GetSpecies();

    if (!pSpecies->IsSpeciesScanned()) {
        pSpecies->SetSpeciesAsScanned();
        ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, (int)pSpecies, 0);
        return 1;
    }
    ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, (int)pSpecies, 0);
    return 0;
}

// @ 0x01053320
int ScanTribe(cPlanet* pPlanet)
{
    gSpaceToolFlags[11] = (int)pPlanet;
    cPlanetSpecies* pTribe = pPlanet->GetTribe();

    if (!pTribe->IsTribeScanned()) {
        pTribe->SetTribeAsScanned();
        ShowScanEventLog(pTribe != nullptr ? 1 : 0, 0, 0, (int)pTribe, 0);
        return 1;
    }
    ShowScanEventLog(pTribe != nullptr ? 1 : 0, 0, 0, (int)pTribe, 0);
    return 0;
}

// @ 0x010533d0
int ScanColony(cSPSimulatorSpaceGame* pGame)
{
    if (pGame->mPad00[0] == 1 && pGame->mPad00[1] == 0x714)
        return 0;

    gSpaceToolFlags[12] = (int)pGame;

    Vec3 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = 0.0f;
    (void)position;

    cPlanetSpecies* pColony = pGame->GetPlayerUFO() != nullptr ? (cPlanetSpecies*)pGame->GetPlayerUFO() : nullptr;
    if (pColony != nullptr && !pColony->IsColonyScanned()) {
        pColony->SetColonyScanned();
        ShowScanEventLog(1, 0, 0, (int)pColony, 0);
        return 1;
    }
    ShowScanEventLog(pColony != nullptr ? 1 : 0, 0, 0, (int)pColony, 0);
    return 0;
}

// @ 0x010534c0
int ScanAllSpecies(cPlanet* pPlanet)
{
    cPlanetModel* pModel = PlanetModel();
    (void)pModel;

    gSpaceToolFlags[5] = (int)pPlanet;

    cPlanetSpecies* pSpecies = pPlanet->GetSpecies();
    if (!pSpecies->IsSpeciesScanned()) {
        pSpecies->SetSpeciesAsScanned();
        ShowScanEventLog(1, 0, 0, (int)pSpecies, 0);
        return 1;
    }
    ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, nullptr, 0);
    return 0;
}

// @ 0x01053590
int cSPEnergyRepairToolStrategy::AdjustCost(int nBaseCost)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fCurrent = pInventory->mEnergyCurrent;
    pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    return (int)(((pInventory->mEnergyMax - fCurrent) / pInventory->mEnergyMax) * (float)nBaseCost);
}

// @ 0x010535e0
int cSPEnergyRepairToolStrategy::AdjustCostPercent(int nBaseCost)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fCargo = pInventory->mCargoMax;
    pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fMax = (float)(pInventory->mpShipItem != nullptr ? 1.0f : 0.0f);
    return (int)(((fMax - fCargo) / fMax) * (float)nBaseCost);
}

// @ 0x01053650
bool cSPToolStrategy::StopTool()
{
    mbActive = 0;
    mTimer.Stop();
    return true;
}

// @ 0x010536e0
IRefCounted* CastToAnimalCargoInfo(IItemHolder* pHolder)
{
    if (pHolder->mpItem == nullptr)
        return nullptr;
    return pHolder->mpSecondary->Query((const void*)0x30fc270b);
}

// @ 0x01053700
IRefCounted* CastToPlantCargoInfo(IItemHolder* pHolder)
{
    if (pHolder->mpItem == nullptr)
        return nullptr;
    return pHolder->mpSecondary->Query((const void*)0x70a2863c);
}

// @ 0x010537e0
bool cSPToolStrategy::ActivateTool(int nToolId)
{
    if (mpActiveObject != nullptr && !mpActiveObject->IsAlive()) {
        IRefCounted* pOld = mpActiveObject;
        mpActiveObject = nullptr;
        pOld->AddRef();
    }

    if (CanUseToolAt(nToolId, 1)) {
        (void)nToolId;
        mpEffectRef = mpEffectRef;
    }
    return true;
}

// @ 0x01053980
bool cSPToolStrategy::CanUseToolAtLocation(int nToolId, int nTarget)
{
    bool bResult = CanUseToolAt(nToolId, nTarget, 0);

    if (SpaceGameGet() == nullptr)
        return bResult;

    if (bResult) {
        cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
        cSPSpaceInventoryItem* pHeld = nullptr;
        if (pInventory != nullptr)
            pHeld = pInventory->mpHeldItem;

        if (mpTargetItem == pHeld) {
            cSPSpaceInventoryItem* pItem = mpTargetItem;
            if (pItem != nullptr) {
                Vec3 dir;
                pItem->GetDirection(&dir);
                if (!IsValidLocation(nTarget, &dir, 1)) {
                    SetErrorEvent(0xfd2c5d0a, true);
                    return false;
                }
            }
        }
    }
    return bResult;
}

// @ 0x01053bb0
void cSPToolStrategy::UpdatePassive()
{
    if (mpActiveObject != nullptr && !mpActiveObject->IsAlive()) {
        IRefCounted* pOld = mpActiveObject;
        mpActiveObject = nullptr;
        pOld->AddRef();
        mEventType = mEventType;
    }
}

// @ 0x01053be0
Vec3* cSPToolStrategy::FindTestTerrainLocation(Vec3* pOut, int nTarget)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    pOut->mX = 0.0f;
    pOut->mY = 0.0f;
    pOut->mZ = 0.0f;

    Vec3 direction;
    if (pInventory == nullptr) {
        cPlanetModel* pModel = PlanetModel();
        if (pModel != nullptr) {
            Vec3 local;
            pModel = PlanetModel(&local);
            Vec3* pPoint = CreatureSurfacePoint(&local, pModel);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    } else {
        Vec3* pItemPos = pInventory->mpHeldItem->GetPosition(&direction);
        direction.mX = pItemPos->mX;
        direction.mY = pItemPos->mY;
        direction.mZ = pItemPos->mZ;

        cPlanetModel* pModel = PlanetModel();
        if (pModel != nullptr) {
            Vec3 local;
            pModel = PlanetModel(&local, &direction);
            Vec3* pPoint = pModel->DirectionToSurfacePosition(&local, &direction);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    }

    int i = 0;
    do {
        if (IsValidLocation(nTarget, pOut, 1))
            break;
        Vec3 local;
        cPlanetModel* pModel = PlanetModel(&local, pOut, 50.0f, 200.0f);
        Vec3* pPoint = pModel->MakeRandomWorldPosition(&local, pOut, 50.0f, 200.0f);
        pOut->mX = pPoint->mX;
        pOut->mY = pPoint->mY;
        pOut->mZ = pPoint->mZ;
        ++i;
    } while (i < 1000);

    if (i >= 1000) {
        for (i = 0; i < 1000; ++i) {
            if (IsValidLocation(nTarget, pOut, 1))
                return pOut;
            Vec3 local;
            PlanetModel(&local);
            Vec3* pPoint = CreatureSurfacePoint(&local, nullptr);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    }
    return pOut;
}

// @ 0x01053d50
void AttachToolEffect(const void* pData)
{
    (void)pData;
    uint8_t local40[16];
    uint8_t local30[48];
    local40[0] = 0;
    local30[0] = 0;
}

// @ 0x01053db0
bool cSPDefaultBeamTool::StopTool()
{
    if (mpBeamProjectile != nullptr) {
        IRefCounted* pOld = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pOld->AddRef();
    }
    AddToolCharge(0);
    return true;
}

// @ 0x01053e00
bool cSPDefaultBeamTool::UpdateBeam()
{
    if (mpBeamProjectile != nullptr && mpBeamProjectile->IsAlive()) {
        IRefCounted* pOld = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pOld->AddRef();
    }
    if (mpBeamProjectile == nullptr)
        return false;

    Vec3 target;
    target.mX = 0.0f;
    target.mY = 0.0f;
    target.mZ = 0.0f;
    if (mpTargetItem != nullptr) {
        IVectorItem* pBeam = (IVectorItem*)mpTargetItem->Query((const void*)0x13f94d4);
        if (pBeam != nullptr) {
            pBeam->GetPosition(&target);
        } else {
            mpTargetItem->GetPosition(&target);
        }
    } else {
        mpTargetItem->GetPosition(&target);
    }

    IVectorItem* pProjectile = (IVectorItem*)mpBeamProjectile->Query((const void*)0x13f94d4);
    if (pProjectile != nullptr)
        pProjectile->GetPosition(&target);
    return true;
}

// @ 0x01053ee0
bool cSPDefaultAoETool::StopTool()
{
    if (mpAreaEffect != nullptr) {
        IRefCounted* pOld = mpAreaEffect;
        mpAreaEffect = nullptr;
        pOld->AddRef();
    }
    return true;
}

// @ 0x01053f20
bool cSPDefaultAoETool::UpdateArea()
{
    if (mpAreaEffect == nullptr)
        return true;

    Vec3 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = 0.0f;

    IVectorItem* pArea = (IVectorItem*)mpAreaEffect->Query((const void*)0x13f94d4);
    if (pArea != nullptr)
        pArea->GetPosition(&position);
    else if (mpTargetItem != nullptr)
        mpTargetItem->GetPosition(&position);

    if (mpTargetItem != nullptr)
        mpTargetItem->GetDirection(&position);
    return true;
}

// @ 0x01053fb0
bool cSPScanToolStrategy::ActivateTool(int nToolId)
{
    bool bResult = cSPToolStrategy::ActivateTool(nToolId);
    cPlanet* pPlanet = (cPlanet*)NounManager();
    if (pPlanet != nullptr) {
        cPlanetSpecies* pSpecies = pPlanet->GetSpecies();
        if (pSpecies != nullptr)
            (void)pSpecies;
    }
    return bResult;
}

// @ 0x01053ff0
bool cSPScanToolStrategy::StopTool()
{
    cSPSpaceInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
    (void)pInventory;

    IRefCounted* pOld = mpEffectRef;
    mpEffectRef = nullptr;
    if (pOld != nullptr)
        pOld->AddRef();

    if (mpBeamProjectile != nullptr) {
        IRefCounted* pProjectile = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pProjectile->AddRef();
    }
    AddToolCharge(0);
    return true;
}

// @ 0x01054080
bool cSPScanToolStrategy::UseTool(int nToolId, int nTarget)
{
    if (mpEffectRef != nullptr)
        return true;
    return CanUseToolAtLocation(nToolId, nTarget);
}

// @ 0x010540b0
bool cSPGetOutOfUFOToolStrategy::CanUseToolAtLocation(int nToolId, int nTarget)
{
    return cSPToolStrategy::CanUseToolAtLocation(nToolId, nTarget);
}

// @ 0x010540d0
bool cSPGetOutOfUFOToolStrategy::ActivateTool(int nToolId)
{
    if (!cSPToolStrategy::ActivateTool(nToolId))
        return false;
    ShowToolEventLog(nToolId, (const void*)0x16e1b14, 3, 0);
    return true;
}

// @ 0x01054110
char PlaceColonyTool::DeactivateTool(int param_1)
{
    if (!ActivateTool(param_1))
        return 0;
    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    if (SP_GetUniverseContext() != 0)
        return 0;
    ((GameObj*)game)->f50d0(1);

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x244fb08u);
    Obj* obj;
    if (!noun) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x2450023);
        if (obj)
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
    }

    obj->mByteA6 = 1;
    Sub34* sub = &obj->mSub34;
    ((VfnI)sub->mpVtbl->mSlots[kV54])(sub, 1);
    ((Vfn0)obj->mpVtbl->mSlots[kV68])(obj);
    obj->mByte110 = 1;
    FUN_00bebb10();

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, sub);
    FUN_00bed920(0xfd701f6f, 5);
    ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

// @ 0x010541f0
char __stdcall FUN_010541f0(int param_1)
{
    (void)param_1;
    Obj* world = (Obj*)SP_GonzagoModelWorld();
    ((VfnII)world->mpVtbl->mSlots[kV18])(world, 0, 5);

    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    void* host = FUN_0067cab0(0);
    ((C8017f0*)host)->Set(0);
    ((GameObj*)game)->f50d0(0);

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
        if (obj) {
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
            Obj* nounMgr = (Obj*)SP_NounManager();
            ((NounMgr*)nounMgr)->RemoveNoun(obj);
        }
    }
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, 0);
    if (obj)
        ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

// @ 0x010542a0
char __stdcall FUN_010542a0(int param_1)
{
    (void)param_1;
    Obj* world = (Obj*)SP_GonzagoModelWorld();
    ((VfnII)world->mpVtbl->mSlots[kV18])(world, 0, 4);

    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    if (SP_GetUniverseContext() != 0)
        return 0;
    void* host = FUN_0067cab0(0);
    ((C8017f0*)host)->Set(0);

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
        if (obj) {
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
            Obj* nounMgr = (Obj*)SP_NounManager();
            ((NounMgr*)nounMgr)->RemoveNoun(obj);
        }
    }
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, 0);
    if (obj)
        ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

// @ 0x01054350
void ToolStrategy2::StopTool(void* param_2, void* param_3)
{
    Obj* self = (Obj*)this;
    Obj* p2 = (Obj*)param_2;
    Obj* sub = p2->mpUnk140;
    if (sub != 0 && !((VfnB)sub->mpVtbl->mSlots[kV10])(sub)) {
        void* r = ((ObjVec*)sub)->erase(param_2);
        ((ToolManager*)r)->UseToolStop();
    }

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj)
        return;
    obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
    if (!obj)
        return;
    ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
    u8 w = ((VfnB3)self->mpVtbl->mSlots[kV24])(self, param_2, param_3, 0);
    ((VfnI)obj->mpVtbl->mSlots[kV5C])(obj, w);
    ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
}

// @ 0x010543e0
namespace SP {
void LaunchProjectile(cSPSpaceToolData * param_1, cDefaultToolProjectile * param_2, cSPVector3 const & a3, cSPVector3 const & a4)
{
    Obj* tool = (Obj*)param_1;

    // 1. projectile-motion hash -> discrete kind 0..0x10
    int kind = 0;
    {
        int h = ((SpaceTool*)tool)->Get07();
        switch (h) {
        case 0x1d128dd5:      kind = 4;   break;
        case (int)0xd1ed94c1: kind = 0xb; break;
        case (int)0x87fbadc9: kind = 0xd; break;
        case (int)0xcb738c11: kind = 10;  break;
        case 0x188b10a2:      kind = 0xf; break;
        case 0x229300a9:      kind = 0xe; break;
        case 0x543f8e29:      kind = 0xc; break;
        case 0x732ed233:      kind = 0x10; break;
        default:              kind = 0;   break;
        }
    }

    // 2. spread / jitter scalars fed to the charge object.
    float base = ((SpaceTool*)tool)->Get01();
    float spread = (base - 1.0f) * tool->mF14c + 1.0f;
    float jitter = ((SpaceTool*)tool)->Get02(spread);
    ((SpaceTool*)tool)->Get0b();
    ((ChargeTool*)tool)->Spread(jitter);
    void* vfx = FUN_011e0810();
    (void)vfx;

    // 3. projectile angle (degrees -> radians -> half-angle) feeds the
    //    orientation-frame / quaternion build that the original then reduces
    //    to a modified push vector.
    float angle = ((SpaceTool*)tool)->Get09() * 0.017453292f * 0.5f;
    (void)angle;

    float push[3];
    push[0] = tool->mVec154.x;
    push[1] = tool->mVec154.y;
    push[2] = tool->mVec154.z;
    if (((SpaceTool*)tool)->Get06() && param_2)
        FUN_00cc0870(push[0], param_2, push);
    else
        FUN_00cb7c20(push, 0);
}
}  // namespace SP

// @ 0x01054ec0
char __stdcall FUN_01054ec0(void* param_1, void* param_2)
{
    Obj* tool = (Obj*)param_1;
    if (!tool->mpManager114)
        return 0;
    Obj* mgr = tool->mpManager114;
    Obj* deed = (Obj*)((VfnPI)mgr->mpVtbl->mSlots[kVB8])(mgr, 0x13f94d4);
    if (!deed)
        return 0;

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x24630d7u);
    Obj* proj;
    if (!noun) {
        proj = 0;
    } else {
        proj = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x24630ce);
        if (proj)
            ((Vfn0)proj->mpVtbl->mSlots[kV00])(proj);
    }

    float a = ((SpaceTool*)tool)->Get01();
    float b = ((SpaceTool*)tool)->Get02((a - 1.0f) * tool->mF14c + 1.0f);
    float y = ((ChargeTool*)tool)->Spread(b) * tool->mF144;
    (void)y;
    void* vfx = FUN_011e0810();
    ((VfnVV)proj->mpVtbl->mSlots[kV54])(proj, tool, vfx);

    char c1 = ((SpaceTool*)tool)->Get04();
    ((Projectile*)proj)->SetA(c1);
    char c2 = ((SpaceTool*)tool)->Get05();
    ((Projectile*)proj)->SetB(c2);
    proj->mVec154.z = ((SpaceTool*)tool)->Get03();

    Obj* m2 = tool->mpManager114;
    void* up = ((VfnP)m2->mpVtbl->mSlots[kV2C])(m2);
    Sub34* sub = &proj->mSub34;
    ((VfnV)sub->mpVtbl->mSlots[kV38])(sub, up);

    void* push = ((VfnP)deed->mpVtbl->mSlots[kV10])(deed);
    ((VfnV)proj->mpVtbl->mSlots[kV48])(proj, push);

    ((BeamProjectile*)proj)->Fire(deed, param_2);

    Obj* old = tool->mpBeam124;
    if (proj != old) {
        ((Vfn0)proj->mpVtbl->mSlots[kV00])(proj);
        tool->mpBeam124 = proj;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kV04])(old);
    }
    ((Vfn0)proj->mpVtbl->mSlots[kV04])(proj);
    return 1;
}

// @ 0x01055040
char __stdcall FUN_01055040(void* param_1, void* param_2)
{
    (void)param_2;
    Obj* tool = (Obj*)param_1;
    if (!tool->mpManager114)
        return 0;
    Obj* mgr = tool->mpManager114;
    Obj* deed = (Obj*)((VfnPI)mgr->mpVtbl->mSlots[kVB8])(mgr, 0x13f94d4);
    if (!deed)
        return 0;

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x4167186u);
    Obj* area;
    if (!noun) {
        area = 0;
    } else {
        area = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x4167194);
        if (area)
            ((Vfn0)area->mpVtbl->mSlots[kV00])(area);
    }

    ((AoEArea*)area)->InitArea(tool);

    Obj* m2 = tool->mpManager114;
    void* up = ((VfnP)m2->mpVtbl->mSlots[kV2C])(m2);
    Sub34* sub = &area->mSub34;
    ((VfnV)sub->mpVtbl->mSlots[kV38])(sub, up);

    void* push = ((VfnP)deed->mpVtbl->mSlots[kV10])(deed);
    ((VfnV)area->mpVtbl->mSlots[kV48])(area, push);

    ((AoEArea*)area)->StartArea();

    Obj* old = tool->mpArea120;
    if (area != old) {
        ((Vfn0)area->mpVtbl->mSlots[kV00])(area);
        tool->mpArea120 = area;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kV04])(old);
    }
    ((Vfn0)area->mpVtbl->mSlots[kV04])(area);
    return 1;
}

// @ 0x01055130
char __stdcall FUN_01055130(void* param_1)
{
    Obj* tool = (Obj*)param_1;
    if (tool->mpUnk128) {
        Obj* o = tool->mpUnk128;
        Obj* sub = (Obj*)((VfnPI)o->mpVtbl->mSlots[kV0C])(o, 0x114242e6);
        if (sub)
            ((SubObj2*)sub)->Notify(2);
    }
    if (tool->mpBeam124) {
        ((Noun2*)tool->mpBeam124)->Cleanup();
        Obj* o = tool->mpBeam124;
        if (o) {
            tool->mpBeam124 = 0;
            ((Vfn0)o->mpVtbl->mSlots[kV04])(o);
        }
    }
    if (((SpaceTool*)tool)->Get07()) {
        void* sim = FUN_00b3d3c0();
        ((Simulator*)sim)->ClearDirty();
    }
    return 1;
}

// @ 0x010551b0
void __stdcall FUN_010551b0(void* param_1, float* param_2)
{
    Obj* tool = (Obj*)param_1;
    Vec3_s0105_4110 old = tool->mVec154;
    Vec3_s0105_4110 nw;
    nw.x = param_2[0];
    nw.y = param_2[1];
    nw.z = param_2[2];
    tool->mVec160 = nw;

    if (!tool->mpUnk16c)
        return;

    const float kZero = 0.0f;
    bool oldNonZero = (old.x != kZero || old.y != kZero || old.z != kZero);
    bool newNonZero = (nw.x != kZero || nw.y != kZero || nw.z != kZero);
    bool changed = (old.x != nw.x || old.y != nw.y || old.z != nw.z);
    if (!(oldNonZero && newNonZero && changed))
        return;

    XformMsg_s0105_4110 msg;
    ((XformMsgObj*)&msg)->construct();
    msg.mFlags |= 4;
    msg.mCount++;
    msg.mVec = old;

    // unit direction of the aim change, falling back to an orthogonal of the
    // old vector when the two are (nearly) coincident.
    Vec3_s0105_4110 unitOld;
    FUN_00449c20(&unitOld.x, &old.x);
    Vec3_s0105_4110 delta;
    delta.x = nw.x - old.x;
    delta.y = nw.y - old.y;
    delta.z = nw.z - old.z;
    float len2 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    Vec3_s0105_4110 dir;
    if (len2 <= 1.5258789e-05f) {
        Vec3_s0105_4110 ortho;
        FUN_006985b0(&ortho.x, &unitOld.x);
        FUN_00449c20(&dir.x, &ortho.x);
    } else {
        FUN_00449c20(&dir.x, &delta.x);
    }

    // right = dir x unitOld, up = unitOld x right, basis = {right, up, dir}
    Vec3_s0105_4110 right;
    right.x = dir.y * unitOld.z - dir.z * unitOld.y;
    right.y = dir.z * unitOld.x - dir.x * unitOld.z;
    right.z = dir.x * unitOld.y - dir.y * unitOld.x;
    Vec3_s0105_4110 up;
    up.x = unitOld.y * right.z - unitOld.z * right.y;
    up.y = unitOld.z * right.x - unitOld.x * right.z;
    up.z = unitOld.x * right.y - unitOld.y * right.x;

    msg.mBasis[0] = right.x; msg.mBasis[1] = right.y; msg.mBasis[2] = right.z;
    msg.mBasis[3] = up.x;    msg.mBasis[4] = up.y;    msg.mBasis[5] = up.z;
    msg.mBasis[6] = dir.x;   msg.mBasis[7] = dir.y;   msg.mBasis[8] = dir.z;

    msg.mFlags |= 2;
    msg.mCount++;
    ((VfnV)tool->mpUnk16c->mpVtbl->mSlots[kV18])(tool->mpUnk16c, &msg);
}

// @ 0x010554c0
bool cSPDragInputProjectileToolStrategy::OnMouseUp(cSpaceToolData_s0105_54c0__tools* pTool)
{
    bool bResult = false;

    if (pTool->mpEffect != 0) {
        pTool->mpEffect->Slot0c(0);
        if (pTool->mpEffect != 0) {
            IEffect_s0105_54c0__tools* pOld = pTool->mpEffect;
            pTool->mpEffect = 0;
            pOld->Release();
        }
    }

    if (pTool->mPressedAt.x != gZeroVector.x
        || pTool->mPressedAt.y != gZeroVector.y
        || pTool->mPressedAt.z != gZeroVector.z) {
        cSPNoun_s0105_54c0__tools* pNoun = NounManager_s0105_54c0__tools()->CreateNoun(0x24270c5);
        void* pProjectile = (pNoun != 0) ? pNoun->Slot0c(0x24270c4) : 0;

        Vector3* pOwnerPosition = pTool->mpToolOwner->GetPosition();
        Vector3 origin;
        origin.x = pOwnerPosition->x;
        origin.y = pOwnerPosition->y;
        origin.z = pOwnerPosition->z;
        LaunchProjectile(pTool, pProjectile, &origin, &pTool->mPressedAt);

        IEffect_s0105_54c0__tools* pEffect = 0;
        cEffectsManager_s0105_54c0__tools* pManager = EffectsManagerPtr_s0105_54c0__tools();
        if (pEffect != 0) {
            pEffect = 0;
            pEffect->Release();
        }
        if (pManager->CreateEffect(pTool->GetEffectId(), 0, &pEffect)) {
            Vector3 facing;
            facing.x = pTool->mPressedAt.x - origin.x;
            facing.y = pTool->mPressedAt.y - origin.y;
            facing.z = pTool->mPressedAt.z - origin.z;
            float fInv = 1.0f / sqrtf(facing.x * facing.x
                                      + facing.y * facing.y
                                      + facing.z * facing.z);
            facing.x *= fInv;
            facing.y *= fInv;
            facing.z *= fInv;

            XformMsg_s0105_54c0__tools msg;
            msg.mFlags |= 4;
            msg.mCount += 1;
            msg.mPosition = origin;
            msg.mBasis = *Matrix3FromFacingAndUp_s0105_54c0__tools(&msg.mBasis, &facing, &origin);
            msg.mFlags |= 2;
            msg.mCount += 1;

            pEffect->Send(&msg);
            pEffect->Detach(0);
        }
        bResult = true;
        if (pEffect != 0)
            pEffect->Release();
    }

    pTool->mPressedAt = gZeroVector;
    pTool->mReleasedAt = gZeroVector;
    return bResult;
}

// @ 0x01055790
bool cSPDeepSpaceProjectileToolStrategy::StartTool(cSpaceToolData_s0105_54c0__tools* pTool, const Vector3* pDirection, void* pParam)
{
    bool bResult = false;
    if (pDirection->x != gZeroVector.x || pDirection->y != gZeroVector.y
        || pDirection->z != gZeroVector.z) {
        cSPNoun_s0105_54c0__tools* pNoun = NounManager_s0105_54c0__tools()->CreateNoun(0x24270c7);
        void* pProjectile = (pNoun != 0) ? pNoun->Slot0c(0x24270c6) : 0;

        float fInv = 1.0f / sqrtf(pDirection->x * pDirection->x
                                  + pDirection->y * pDirection->y
                                  + pDirection->z * pDirection->z);
        Vector3 velocity;
        velocity.x = pDirection->x * fInv * 2000.0f;
        velocity.y = pDirection->y * fInv * 2000.0f;
        velocity.z = pDirection->z * fInv * 2000.0f;

        LaunchProjectile(pTool, pProjectile, &velocity, pDirection);
        return true;
    }
    return bResult;
}

// @ 0x01055890
namespace Simulator_s0105_54c0 {
void RegisterStaticRegistrations()
{
    STATIC_REGISTRATION(0)
    STATIC_REGISTRATION(1)
    STATIC_REGISTRATION(2)
    STATIC_REGISTRATION(3)
    STATIC_REGISTRATION(4)
    STATIC_REGISTRATION(5)
    STATIC_REGISTRATION(6)
    STATIC_REGISTRATION(7)
    STATIC_REGISTRATION(8)
    STATIC_REGISTRATION(9)
    STATIC_REGISTRATION(10)
    STATIC_REGISTRATION(11)
    STATIC_REGISTRATION(12)
    STATIC_REGISTRATION(13)
    STATIC_REGISTRATION(14)
    STATIC_REGISTRATION(15)
    STATIC_REGISTRATION(16)
    STATIC_REGISTRATION(17)
    STATIC_REGISTRATION(18)
    STATIC_REGISTRATION(19)
    STATIC_REGISTRATION(20)
    STATIC_REGISTRATION(21)
    STATIC_REGISTRATION(22)
    STATIC_REGISTRATION(23)
    STATIC_REGISTRATION(24)
    STATIC_REGISTRATION(25)
    STATIC_REGISTRATION(26)
    STATIC_REGISTRATION(27)
}
}  // namespace Simulator_s0105_54c0

// @ 0x01056160
bool __stdcall CanUseTool_56160(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut)
{
    if (self == nullptr)
        return false;

    // Must have the UFO simulator and the player inventory.
    if (GetUFOSimulator() != nullptr) {
        void* game = GetUFOSimulator();
        void* inv = game != nullptr ? ((cSPSimulatorSpaceGame_s0105_6160*)game)->GetPlayerInventory() : nullptr;
        if ((void*)(inv != nullptr ? (char*)inv + 0x34 : nullptr) != nullptr &&
            (char*)inv + 0x34 == (char*)self->mpTargetItem)
            ;
        if ((void*)(inv != nullptr ? (char*)inv + 0x34 : nullptr) == (void*)self->mpTargetItem)
            ;
    }

    // Placeholder body: delegate the validity checks to the error-event helpers.
    if (self->mpTargetItem == nullptr) {
        SetErrorEvent_527f0(self, 0xbf808149, nTarget);
        AppendScanResult_52880(pOut, (int*)4);
        return false;
    }
    return true;
}

// @ 0x010568b0
bool __stdcall StartTool_568b0(cSPToolStrategy_s0105_6160* self, int nTarget, int nFlags)
{
    void* key;
    // Stop the charge timer on the held item.
    if (self->mpTargetItem != nullptr) {
        int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
        if (obj != 0) {
            FUN_00c389c0((void*)obj, 1, 0);
            FUN_00bc3110((void*)(obj + 0x6f0));
        }
    }

    // Drop the active object, then start a fresh one.
    GetActivePlanet();
    if (self->mpActiveObject != nullptr) {
        self->mpActiveObject->SetEnabled(0);
        IRefCounted_s0105_6160* old = self->mpActiveObject;
        if (old != nullptr) {
            self->mpActiveObject = nullptr;
            old->AddRef();
        }
    }
    if (self->mpActiveObject == nullptr) {
        IRefCounted_s0105_6160* fresh = (IRefCounted_s0105_6160*)FUN_01050640(self);
        IRefCounted_s0105_6160* old = self->mpActiveObject;
        if (fresh != old) {
            if (fresh != nullptr)
                fresh->v00();
            self->mpActiveObject = fresh;
            if (old != nullptr)
                old->AddRef();
        }
    }

    // Terrain / shield tool keys.
    key = self->GetToolKey();
    if (((int*)key)[0] == (int)g_16e1f94 &&
        ((int*)key)[1] == (int)g_16e1f98 &&
        ((int*)key)[2] == (int)g_16e1f9c) {
        void* editor = NounManager();
        FUN_00f67d90(editor);
        FUN_00c75630(editor);
        return true;
    }

    key = self->GetToolKey();
    if (((int*)key)[0] == (int)g_16e1ce8 &&
        ((int*)key)[1] == (int)g_16e1cec &&
        ((int*)key)[2] == (int)g_16e1cf0) {
        if (GetActivePlanet() != nullptr) {
            FUN_00c73cf0(self, 1);
            return true;
        }
    } else {
        key = self->GetToolKey();
        if (((int*)key)[0] == (int)g_16e1e2c &&
            ((int*)key)[1] == (int)g_16e1e30 &&
            ((int*)key)[2] == (int)g_16e1e34) {
            int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
            if (obj != 0) {
                FUN_00c389c0((void*)obj, 1, 1);
                FUN_00bc3130((void*)(obj + 0x6f0));
                return true;
            }
        } else {
            if (*(int*)self->GetToolKey() == (int)g_16e1d18) {
                int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
                if (obj != 0) {
                    FUN_00bfc470((void*)obj, 1);
                    FUN_00bc3130((void*)(obj + 0x6d0));
                    return true;
                }
            } else if (*(int*)self->GetToolKey() == (int)g_16e1d90) {
                void* server = MessageServer_s0105_6160();
                int msg[3];
                SlotMessageConstruct(msg, 0x3c5dbc7);
                ((void(__fastcall*)(void*, int*, int))(*(void***)server)[5])(server, msg, 0);
                SlotMessageDestruct(msg);
                return true;
            } else if (*(int*)self->GetToolKey() == (int)g_16e2090) {
                void* obj = self->mpTargetItem;
                FUN_00b3d510(obj);
                FUN_00b71fb0(obj, 0);
            }
        }
    }
    return true;
}

// @ 0x01056b50
bool cSPDefaultAoETool_s0105_6160::StartTool(int nToolId, int nTarget, int nFlags)
{
    cSPToolStrategy_s0105_6160* other = (cSPToolStrategy_s0105_6160*)nToolId;
    if (StartTool_568b0(other, nTarget, nFlags)) {
        cSPSpaceInventoryItem_s0105_6160* mi = other->mpTargetItem;
        if (mi != nullptr) {
            int r = (int)mi->vb8((const void*)&g_13f94d4);
            if (r != 0 && other->mpAreaEffect == nullptr) {
                v48(nToolId, nTarget);
            }
        }
    }
    return true;
}

// @ 0x01056bb0
bool __stdcall CanUseTool_56bb0(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSimulatorSpaceGame_s0105_6160* game = (cSPSimulatorSpaceGame_s0105_6160*)SpaceGameGetRaw();
        void* inv = game->GetPlayerInventory();
        int item = (int)FUN_00ff3f10(inv);
        if (item != 0) {
            cSPInteractableObject* obj = (cSPInteractableObject*)item;
            if (obj->mObjectType != 3)
                return true;
        }
    }
    return false;
}

// @ 0x01056bf0
bool __stdcall CanUseTool_56bf0(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSpaceInventoryItem_s0105_6160* item = self->mpTargetItem;
        if (item != nullptr) {
            cSPSpaceInventoryItem_s0105_6160* obj = (cSPSpaceInventoryItem_s0105_6160*)item->vb8((const void*)0xb033b403);
            if (obj != nullptr && obj->mFlags714 == 0) {
                if (obj->mEnergyCurrent > obj->mEnergyMax)
                    return true;
                if (pOut != nullptr)
                    *pOut = GetTextAt_4c4f0(FUN_00b3d390(0x13));
            }
        }
    }
    return false;
}

// @ 0x01056c70
bool cSPRepairAOEToolStrategy::StartTool(int nToolId, int nTarget, int nFlags)
{
    if (StartTool_568b0((cSPToolStrategy_s0105_6160*)nToolId, nTarget, nFlags)) {
        v30(nToolId, nTarget, 3, 0);
        return true;
    }
    return false;
}

// @ 0x01056cb0
bool __stdcall CanUseTool_56cb0(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSpaceInventoryItem_s0105_6160* item = self->mpTargetItem;
        if (item != nullptr) {
            cSPSpaceInventoryItem_s0105_6160* obj = (cSPSpaceInventoryItem_s0105_6160*)item->vb8((const void*)&g_13f94d4);
            if (obj != nullptr) {
                float stored = obj->mValue38;
                float other = obj->v58();
                if (stored < other)
                    return true;
                if (pOut != nullptr)
                    *pOut = GetTextAt_4c4f0(FUN_00b3d390(0x14));
            }
        }
    }
    return false;
}

// @ 0x01056d30
bool __stdcall CanUseTool_56d30(cSPToolStrategy_s0105_6160* self, int nTarget, int* pOut)
{
    if (!CanUseTool_56160(self, nTarget, pOut))
        return false;

    void* ctx = GetUniverseContext();
    void* planet = GetActivePlanet();
    if (ctx != nullptr)
        return false;

    void* game = GetUFOSimulator();
    void* inv = game != nullptr ? ((cSPSimulatorSpaceGame_s0105_6160*)game)->GetPlayerInventory() : nullptr;
    if (inv == nullptr)
        return false;

    void* held = *(void**)((char*)inv + 0x34);
    Vec3 pos;
    Vec3* p = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    float radius = FUN_00c375d0(p);
    (void)planet;
    p = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    float dx = p->mX, dy = p->mY, dz = p->mZ;
    float dist = (float)fun_sqrt(dx * dx + dy * dy + dz * dz);
    void* gm = FUN_00c37360();
    float range = FUN_00fb7ba0(gm);
    if (GameDataBigCountList(NounManager(), (void*)0x24270c5) != 0)
        return false;

    void* game2 = GetUFOSimulator();
    void* inv2 = game2 != nullptr ? ((cSPSimulatorSpaceGame_s0105_6160*)game2)->GetPlayerInventory() : nullptr;
    held = *(void**)((char*)inv2 + 0x34);
    Vec3* q = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    pos.mX = q->mX;
    pos.mY = q->mY;
    pos.mZ = q->mZ;
    if (FUN_00b7e3e0(PlanetModelGet())) {
        SetErrorEvent_527f0(self, 0x85af2a11, nTarget);
        if (pOut != nullptr) {
            *pOut = FUN_0104c4f0(FUN_00b3d390(0x15));
            return false;
        }
    } else {
        Vec3 r;
        (void)r;
        Vec3* sp = FUN_00b81630(PlanetModelGet(), &pos);
        pos.mX = sp->mX;
        pos.mY = sp->mY;
        pos.mZ = sp->mZ;
        void* child = FUN_00b894a0(PlanetModelGet(), &pos);
        if (child != nullptr && FUN_00bd9c00(child, &pos)) {
            SetErrorEvent_527f0(self, 0xadb2f40, nTarget);
            AppendScanResult_52880(pOut, (int*)0x16);
            return false;
        }
        if (range + 70.0f < dist - radius) {
            SetErrorEvent_527f0(self, 0xe8ee796f, nTarget);
            AppendScanResult_52880(pOut, (int*)0x17);
            return false;
        }
        void* app = AppSystem();
        if (!((bool(__fastcall*)(void*))(((void**)*(void**)app)[0x14]))(app) ||
            g_15b743d != 0) {
            return true;
        }
    }
    return false;
}

// @ 0x01056f40
bool __stdcall DefaultProjectile_StartTool(cSPToolStrategy_s0105_6f40* pSelf, const Vector3* pTarget, void* pParam)
{
    bool bResult = false;
    if (!StartTool(pSelf, pTarget, pParam))
        return bResult;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return bResult;

    cSPAimObject* pAimer = pSelf->mpAimer;
    Vector3 position = *pAimer->GetPosition();
    Vector3 local;
    cSPNoun* pAimHandle = (cSPNoun*)pAimer->Slotb8(&gAimHandleName);
    if (pAimHandle != nullptr)
        position = *pAimHandle->Slot30(&local);

    float fDX = pTarget->x - position.x;
    float fDY = pTarget->y - position.y;
    float fDZ = pTarget->z - position.z;
    if (fDX * fDX + fDY * fDY + fDZ * fDZ < gProjectileMinDistance2)
        return false;

    cSPNoun* pProjectile = NounManager_s0105_6f40()->CreateNoun(0x24270c5);
    void* pNoun = (pProjectile != nullptr) ? pProjectile->Slot0c(0x24270c4) : nullptr;
    LaunchProjectile(pSelf, pNoun, &position, pTarget);

    IEffect* pEffect = nullptr;
    cEffectsManager_s0105_6f40* pManager = EffectsManagerPtr_s0105_6f40();
    if (pEffect != nullptr) {
        pEffect = nullptr;
        pEffect->Release();
    }
    if (pManager->CreateEffect(FUN_0104bf40(&pEffect), 0)) {
        Matrix3Rows transform;
        FUN_00cb5140(pNoun, &transform);

        XformMsg msg;
        msg.mFlags |= 4;
        msg.mCount += 1;
        msg.mPosition = *pTarget;

        Vector3 facing;
        facing.x = position.x;
        facing.y = position.y;
        facing.z = position.z;
        Vector3 up;
        up.x = local.x;
        up.y = local.y;
        up.z = local.z;
        msg.mBasis = *Matrix3FromFacingAndUp(&msg.mBasis, &facing, &up);
        msg.mBasisFlags |= 2;
        msg.mBasisCount += 1;

        if (SP_GetUniverseContext() != nullptr) {
            msg.mScale = pAimer->GetScalar();
            msg.mCount += 1;
        }

        pEffect->Send(&msg);

        if (FUN_0104bd80(pSelf) == (int32_t)0xe810d505 && pEffect != nullptr) {
            uint8_t color[0x30];
            if (GetCreatureColorProperty(pEffect->Slot0c(color), color))
                pEffect->Slot44(5, color, 3);
        }
        pEffect->Detach(0);
    }

    if (pEffect != nullptr) {
        pEffect->Release();
        return true;
    }
    return true;
}

// @ 0x01057210
bool __stdcall TurretDefenseMissile_StartTool(cSPToolStrategy_s0105_6f40* pSelf, const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return false;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return false;

    cSPAimObject* pAimer = pSelf->mpAimer;
    cSPNoun* pSource = nullptr;
    if (pAimer != nullptr)
        pSource = (cSPNoun*)pAimer->Slotb8(&gMissileHandleName);

    cSPNoun* pTargetObject = nullptr;
    if (pSelf->mpTarget != nullptr)
        pTargetObject = (cSPNoun*)pSelf->mpTarget->Slotb8(&gAimHandleName);

    float fLifetime = pAimer->Slot70() * 0.9f;

    Vector3 direction = *pAimer->GetPosition();
    float fInvLength = 1.0f / sqrtf(direction.x * direction.x
                                    + direction.y * direction.y
                                    + direction.z * direction.z);
    Vector3 velocity;
    velocity.x = direction.x * fInvLength * fLifetime;
    velocity.y = direction.y * fInvLength * fLifetime;
    velocity.z = direction.z * fInvLength * fLifetime;

    Vector3 origin = *pAimer->GetPosition();
    origin.x += velocity.x;
    origin.y += velocity.y;
    origin.z += velocity.z;

    cSPNoun* pMissile = NounManager_s0105_6f40()->CreateNoun(0x244d3c8);
    cSPNoun* pObject = (pMissile != nullptr) ? (cSPNoun*)pMissile->Slot0c(0x244d3c0)
                                             : nullptr;

    pObject->Slot54(pSelf);
    Vector3 launchPosition;
    pObject->Slot38(&launchPosition);

    float fSpeed = FUN_0104be50();
    Vector3 aim;
    aim.x = launchPosition.x;
    aim.y = launchPosition.y;
    aim.z = launchPosition.z;
    float fInvAim = 1.0f / sqrtf(aim.x * aim.x + aim.y * aim.y + aim.z * aim.z);
    Vector3 shot;
    shot.x = aim.x * fInvAim * fSpeed;
    shot.y = aim.y * fInvAim * fSpeed;
    shot.z = aim.z * fInvAim * fSpeed;

    FUN_00cb8760(&shot, pTargetObject);
    pObject->Slot48(pSource->Slot4c());
    return true;
}

// @ 0x01057460
bool __stdcall TurretFlak_StartTool(cSPToolStrategy_s0105_6f40* pSelf, const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return false;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return false;

    cSPAimObject* pAimer = pSelf->mpAimer;
    if (pAimer != nullptr)
        pAimer->Slotb8(&gAimHandleName);

    cSPNoun* pTargetBase = nullptr;
    void* pConfig = nullptr;
    if (pSelf->mpTarget != nullptr) {
        pTargetBase = (cSPNoun*)pSelf->mpTarget->Slotb8(&gAimHandleName);
        if (pTargetBase != nullptr)
            pConfig = pTargetBase->Slot5c(0xb033b403);
    }

    float fLifetime = pAimer->Slot70() * 0.9f;
    Vector3 forward = *pAimer->GetPosition();
    float fInvLength = 1.0f / sqrtf(forward.x * forward.x
                                    + forward.y * forward.y
                                    + forward.z * forward.z);
    Vector3 velocity;
    velocity.x = forward.x * fInvLength * fLifetime;
    velocity.y = forward.y * fInvLength * fLifetime;
    velocity.z = forward.z * fInvLength * fLifetime;

    Vector3 muzzle = *pAimer->GetPosition();
    muzzle.x += velocity.x;
    muzzle.y += velocity.y;
    muzzle.z += velocity.z;

    Vector3 aim;
    aim.x = pTarget->x - muzzle.x;
    aim.y = pTarget->y - muzzle.y;
    aim.z = pTarget->z - muzzle.z;
    float fInvAim = 1.0f / sqrtf(aim.x * aim.x + aim.y * aim.y + aim.z * aim.z);
    aim.x *= fInvAim;
    aim.y *= fInvAim;
    aim.z *= fInvAim;

    cSPNoun* pOriginNoun = (cSPNoun*)pTargetBase->Slot08();
    Vector3 center = *pOriginNoun->GetPosition();
    if (pConfig != nullptr && *(bool*)((uint8_t*)pConfig + 0x74c))
        center = *(Vector3*)((uint8_t*)pConfig + 0x750);

    float fCenterLength2 = center.x * center.x + center.y * center.y
                           + center.z * center.z;
    float fInvCenter = 1.0f / sqrtf(fCenterLength2);
    Vector3 centerDir;
    centerDir.x = center.x * fInvCenter;
    centerDir.y = center.y * fInvCenter;
    centerDir.z = center.z * fInvCenter;

    cPlanetModel* pPlanet = PlanetModel(&centerDir);
    float fRadius = GetRadiusAt(pPlanet, nullptr, &centerDir);
    float fCenterLength = sqrtf(fCenterLength2);
    float fHigh = fRadius + FUN_00e21850();
    float fLow = fRadius + FUN_00c41f20();
    float fDistance = fCenterLength;
    if (fDistance <= fHigh)
        fDistance = fHigh;
    if (fLow <= fDistance)
        fDistance = fLow;

    Vector3 impact;
    impact.x = centerDir.x * fDistance;
    impact.y = centerDir.y * fDistance;
    impact.z = centerDir.z * fDistance;

    Vector3 offset;
    offset.x = impact.x - muzzle.x;
    offset.y = impact.y - muzzle.y;
    offset.z = impact.z - muzzle.z;

    float fDenominator = centerDir.x * aim.x + centerDir.y * aim.y
                         + centerDir.z * aim.z;
    float fT = (offset.x * centerDir.x + offset.y * centerDir.y
                + offset.z * centerDir.z) / fDenominator;

    Vector3 hit;
    hit.x = muzzle.x + aim.x * fT;
    hit.y = muzzle.y + aim.y * fT;
    hit.z = muzzle.z + aim.z * fT;

    float fDistanceA = hit.x * hit.x + hit.y * hit.y + hit.z * hit.z;
    float fDistanceB = offset.x * offset.x + offset.y * offset.y
                       + offset.z * offset.z;
    float fSpeed = FUN_0104be50();
    float fRatio = sqrtf(fDistanceA) / (sqrtf(fDistanceB) / fSpeed);

    Vector3 shot;
    shot.x = aim.x * fRatio;
    shot.y = aim.y * fRatio;
    shot.z = aim.z * fRatio;

    cSPNoun* pShell = NounManager_s0105_6f40()->CreateNoun(0x240e3bf);
    cSPNoun* pObject = (pShell != nullptr) ? (cSPNoun*)pShell->Slot0c(0x240e3b7)
                                           : nullptr;

    pObject->Slot54(pSelf);
    Vector3 launch;
    pObject->Slot38(&launch);
    pObject->Slot48(pShell->Slot10());
    FUN_00cb7ba0(&shot, fRatio);
    return true;
}

// @ 0x01057990
bool __stdcall DragInputProjectile_StartTool(cSPToolStrategy_s0105_6f40* pSelf, const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return true;
    if (pSelf->mpEffect != nullptr)
        return true;

    pSelf->mPressedAt = *pTarget;
    pSelf->mReleasedAt = *pTarget;

    cEffectsManager_s0105_6f40* pManager = EffectsManagerPtr_s0105_6f40();
    IEffectHandle* pHandle = pManager->Acquire(0x3701a5c);
    if (pSelf->mpEffect != nullptr) {
        IEffect* pOld = pSelf->mpEffect;
        pSelf->mpEffect = nullptr;
        pOld->Release();
    }

    if (!pHandle->Create(0x23c4ca24, 0, &pSelf->mpEffect))
        return true;

    XformMsg msg;
    msg.mFlags |= 4;
    msg.mCount += 1;
    msg.mPosition = *pTarget;

    Vector3 facing;
    normalized_safe(&facing, pTarget);
    Vector3 up;
    OrthogonalVector(&up, &facing);
    Vector3 up2;
    normalized_safe(&up2, &up);

    Vector3 side;
    side.x = facing.y * up2.z - facing.z * up2.y;
    side.y = facing.z * up2.x - facing.x * up2.z;
    side.z = facing.x * up2.y - facing.y * up2.x;

    Vector3 realUp;
    realUp.x = up2.y * side.z - up2.z * side.y;
    realUp.y = up2.z * side.x - up2.x * side.z;
    realUp.z = up2.x * side.y - up2.y * side.x;

    msg.mBasis.m[0] = up2.x;
    msg.mBasis.m[1] = up2.y;
    msg.mBasis.m[2] = up2.z;
    msg.mBasis.m[3] = realUp.x;
    msg.mBasis.m[4] = realUp.y;
    msg.mBasis.m[5] = realUp.z;
    msg.mBasis.m[6] = side.x;
    msg.mBasis.m[7] = side.y;
    msg.mBasis.m[8] = side.z;

    msg.mBasisFlags |= 2;
    msg.mBasisCount += 1;

    pSelf->mpEffect->Send(&msg);
    pSelf->mpEffect->Detach(0);
    return true;
}

// @ 0x01057bd0
bool __stdcall PlaceObject_CanUseTool(cSPPlaceObjectToolStrategy* pSelf, bool bArg, int32_t* pOut)
{
    if (!BaseCanUseTool(pSelf, bArg, pOut))
        return false;

    cUniverseContext* pContext = (cUniverseContext*)FUN_01021260();
    if (pSelf->CanUseCheckA()) {
        if (!pContext->IsPlanetUnlocked(FUN_01021300(0))) {
            SetErrorEvent(pSelf, 0xb6cb3e94, bArg);
            if (pOut != nullptr)
                *pOut = EraseScanItem(6)->GetValue();
            return false;
        }
    }

    if (!pSelf->CanUseCheckB())
        goto check_planet;

    if ((FUN_01021240()->GetItemInstanceID() & 2) != 0) {
        if (pContext->GetPlayerItem() != FUN_01021240()) {
            SetErrorEvent(pSelf, 0x15589a01, bArg);
            AppendScanResult(5, pOut);
            return false;
        }
        goto check_empire;
    }

check_empire:
    if (pContext->GetPlayerObject() == FUN_01021300(0)) {
        SetErrorEvent(pSelf, 0x15589a01, bArg);
        if (pOut != nullptr)
            *pOut = EraseScanItem(5)->GetValue();
        return false;
    }
    if (pContext->GetEmpireState() != 5) {
        SetErrorEvent(pSelf, 0x15589a01, bArg);
        AppendScanResult(5, pOut);
        return false;
    }

check_planet:
    pContext = (cUniverseContext*)FUN_01021260();
    if (!FUN_00b8e040(*(void**)((uint8_t*)pContext + 0x13c), pSelf->Slot1c()))
        return true;

    SetErrorEvent(pSelf, 0x14a144d8, bArg);
    if (pOut != nullptr)
        *pOut = EraseScanItem(7)->GetValue();
    return false;
}

// @ 0x01058660
void __cdecl ScanBuildingSpecies(void* obj, i32 flag)
{
    NotifyScannedCreatureSpecies((char*)*(void**)((char*)obj + 0x0b20) + 0x504, flag);
}

// @ 0x01058680
extern "C" u32 __cdecl ScanBuilding(cSPCreatureBase* creature)
{
    u32 ok = 0;
    i32 v1;
    i32 v2;
    if (creature != 0) {
        if (VT_0C_0(creature, (void*)0xd0036e08) != 0) {
            void* planet = GetActivePlanet();
            cSpeciesProfile* species = (cSpeciesProfile*)creature->GetSpeciesRecord();
            cSpeciesSubRec* sub = (cSpeciesSubRec*)((char*)species + 0x504);

            v1 = species->mField508;
            v2 = species->mField50c;
            i32 v3 = species->mField504;

            char* tok = *(char**)g_spaceTokenTranslator;
            *(i32*)(tok + 0x14) = 0;
            *(void**)(tok + 0x24) = species;

            if (cPlanet_SetSpeciesAsScanned(planet, sub) == 0) {
                cPlanet_ResetSpecies(planet, sub, 1, 1);
                void* tray = GetIconTrayObj();
                void* text = Text_GetText((char*)tray + 0x44);
                ShowScanEventLog(v3, v1, v2, (void*)0x01052fd0, text);
                NotifyScannedCreatureSpecies((char*)creature->mpField0b20 + 0x504, 1);
                ok = 1;
            } else {
                void* tray = GetIconTrayObj();
                void* text = Text_GetText((char*)tray + 0x58);
                ShowScanEventLog(v3, v1, v2, 0, text);
            }
        }
    }
    return ok;
}

// @ 0x01058b60
bool cSPPlaceColonyToolStrategy::CanUseTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult)
{
    if (!cSPToolStrategy_s0105_8b60::CanUseTool(nArg1, nArg2, pnResult))
        return false;
    int nTarget = ToolStrategy_IsValid();
    if (nTarget != 0 && ToolStrategy_GetCount() > 1) {
        int nOwner = ToolStrategy_GetOwner();
        if (ToolStrategy_GetOwner() != nOwner)
            return false;
    }
    cGameNounManager_s0105_8b60* pNounManager = NounManager_s0105_8b60();
    cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
    int nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    int nLimit = ToolStrategy_GetLimit();
    if (nCount >= 1 && nCount >= nLimit) {
        ToolStrategy_Fail(nArg1, 0xc4a882d7, nArg2);
        if (pnResult != 0)
            *pnResult = ToolStrategy_MakeResult(0x19);
        return false;
    }
    int nRecord = cSPLivingUniverse_GetActivePlanetRecord();
    if (nRecord == 0 || (nRecord & 0x800) == 0)
        return true;
    return false;
}

// @ 0x01059040
bool cSPPlaceColonyToolStrategy::StartTool(uint32_t nArg1, uint32_t nArg2, uint32_t* pnResult)
{
    if (cSPToolStrategy_s0105_8b60::StartTool(nArg1, nArg2, pnResult)) {
        cGameNounManager_s0105_8b60* pNounManager = NounManager_s0105_8b60();
        cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
            0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
        int nCount = (int)(pData->mpEnd - pData->mpBegin);
        for (unsigned int i = 0; i < (unsigned int)nCount; ++i) {
            cGameObject* pObject = (cGameObject*)pData->mpBegin[i];
            pObject->mBubbles.push_back();
            const cVector3* pPosition =
                ((const cVector3* (__thiscall*)(cBubbleSource*))
                     ((void**)pObject->mBubbleSource.mpVtable)[0x2c / 4])(
                    &pObject->mBubbleSource);
            pObject->mBubbles.mpEnd[-1].mPosition = *pPosition;
            pObject->mBubbles.mpEnd[-1].mfFade = gEmptyBubbleFade;
            pObject->mnUnk2d0 = 0;
            pObject->mnUnk2cc = 0;
        }
    }
    return true;
}

// @ 0x01059170
void CreatePanicBubbleForTool(uint32_t nTool, float fX, float fY, float fZ)
{
    if (ToolStrategy_GetRadius() <= 0.0f)
        return;
    cGameNounManager_s0105_8b60* pNounManager = NounManager_s0105_8b60();
    cGameDataList* pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, &gDataFilter);
    int nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    for (int i = 0; i < nCount; ++i) {
        cGameObject* pObject = (cGameObject*)pData->mpBegin[i];
        const cVector3* pPosition =
            ((const cVector3* (__thiscall*)(cBubbleSource*))
                 ((void**)pObject->mBubbleSource.mpVtable)[0x2c / 4])(
                &pObject->mBubbleSource);
        float fDX = pPosition->x - fX;
        float fDY = pPosition->y - fY;
        float fDZ = pPosition->z - fZ;
        if (sqrtf_c(fDX * fDX + fDY * fDY + fDZ * fDZ) < 100.0f) {
            uint32_t nId = ToolStrategy_GetTargetId();
            ToolStrategy_SpawnBubble(&fX, ToolStrategy_GetScore(nId), nId);
        }
    }
    pNounManager = NounManager_s0105_8b60();
    pData = (cGameDataList*)pNounManager->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00accbb0, 0x00b1e500, &gTribeDataFilter);
    nCount = (int)((char*)pData->mpEnd - (char*)pData->mpBegin) >> 2;
    for (int i = 0; i < nCount; ++i) {
        cTribe* pTribe = (cTribe*)pData->mpBegin[i];
        const cVector3* pPosition =
            ((const cVector3* (__thiscall*)(cBubbleSource*))
                 ((void**)pTribe->mBubbleSource.mpVtable)[0x2c / 4])(
                &pTribe->mBubbleSource);
        float fDX = pPosition->x - fX;
        float fDY = pPosition->y - fY;
        float fDZ = pPosition->z - fZ;
        if (sqrtf_c(fDX * fDX + fDY * fDY + fDZ * fDZ) < 100.0f) {
            uint32_t nId = ToolStrategy_GetTargetId();
            ToolStrategy_SpawnBubble(&fX, ToolStrategy_GetScore(nId), nId);
        }
    }
}

// @ 0x01059f20
namespace SP {
bool cSPDefaultBeamTool_s0105_93e0::StartTool(cSPToolStrategy_s0105_93e0* self, const Vector3_s0105_93e0& position, int flags)
{
    if (!StartTool_568b0(self, position, flags))
        return true;

    IRefCounted_s0105_93e0* pItem = self->mpTargetItem;
    IRefCounted_s0105_93e0* pCasted = pItem ? (IRefCounted_s0105_93e0*)pItem->vb8((const void*)0x13f94d4) : 0;
    if (!pCasted)
        return true;

    Vector3_s0105_93e0 positionCopy = position;
    AutoRefCount<cBeamTarget> pTarget;
    pTarget = self->mBeamTarget;
    if (pTarget) {
        if (pTarget->IsValid()) {
            v48(self, &positionCopy);
            pTarget = self->mBeamTarget;
            if (self->FUN_0104cd50())
                FUN_00b3d3c0_s0105_93e0()->FUN_00b7c160(7);
        }
        pTarget->mb154 = 1;
    }

    CreatePanicBubbleForTool(self, position);
    return true;
}
}  // namespace SP

// @ 0x0105a050
namespace SP {
bool __stdcall DefaultAoEOnHit(cSpaceToolData_s0105_93e0* pTool, const Vector3_s0105_93e0* position, int hitType, int)
{
    if (OnHitTool(pTool, *position, hitType, 0)) {
        if (pTool->GetEffectRadius() > 0.0f) {
            if (pTool->mpBeamProjectile
                && (pTool->mpBeamProjectile->HasTarget()
                    || pTool->mpBeamProjectile->mb16c
                    || pTool->mpBeamProjectile->mb16d)
                && pTool->HasFlag8()) {
                Vector3_s0105_93e0 start;
                Vector3_s0105_93e0 end;
                cBeamProjectile* pBeam = pTool->mpBeamProjectile;
                pBeam->GetEndPoints(&end, &start);
                TerraformingManager()->ApplyAt(&start, pTool->GetEffectRadius());
            }
        }
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x0105a100
namespace SP {
bool cSPDefaultAoETool_s0105_93e0::DoToolAction(cSpaceToolData_s0105_93e0* pTool, const Vector3_s0105_93e0& position, int hitType, int)
{
    return OnHit(pTool, position, hitType, 0);
}
}  // namespace SP

// @ 0x0105a110
bool cSPToolStrategy_s0105_a110::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (!CanDoToolAction(pTool, position, a3, 0))
        return true;

    if (!pTool->mpOwnerObject)
        goto LAB_838;

    {
        cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        if (!pSpatial)
            goto LAB_838;

        pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        if (pSpatial->Flag2c())
            goto LAB_838;
    }

    cUFO* pUFO = (cUFO*)FUN_00c9f040(&pTool->mpToolOwner);
    if (pUFO && pUFO->field714 != 0 && pUFO->field714 != 7) {
        return FUN_01058950(pTool, position, a3, a4);
    }

    {
        cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        cBuilding* pBuilding = 0;
        if (pSpatial) {
            pBuilding = (cBuilding*)pSpatial->Cast(0xce9f6639);
        }

        if (pBuilding) {
            cInteraction* pInteraction = &pBuilding->mInteraction;
            cSPMission* pMission = (cSPMission*)FUN_01030e60(pInteraction->v20());
            int nMission = (int)FUN_01030e60(pInteraction->v20());
            bool bFlag = pBuilding->Flag388();
            if (!bFlag
                && ((pBuilding->flags_b58 >> 9) & 1) == 0
                && ((pBuilding->flags_b58 >> 8) & 1) == 0
                && nMission == 0
                && (!pMission || pMission->GetMissionID() == 2)) {
                if (!pUFO || pUFO->field714 == 0 || pUFO->field714 == 7) {
                    FUN_00c0c380(pSpatial);
                    if (pBuilding->byte_b67) {
                        FUN_00acd2d0(FUN_00b3d480(), pBuilding);
                    }
                    pBuilding->field2b0 = 4;

                    void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                    pInteraction->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                    ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pInteraction->v20());

                    NounManager_s0105_a110();
                    void* pNoun = FUN_00ace2c0();
                    void* pFound = FUN_00ac9dd0(pNoun, position);
                    if (pFound) {
                        *(float*)((uint8_t*)pFound + 0x2d4) = position.x;
                        *(float*)((uint8_t*)pFound + 0x2d8) = position.y;
                        *(float*)((uint8_t*)pFound + 0x2dc) = position.z;
                    }

                    void* pTribeList = FUN_00acd9d0();
                    void* pTribe = FUN_00c52f80(pTribeList, position);
                    if (pTribe) {
                        void* pTarget = FUN_00c8e7e0(pTribe);
                        FUN_01062e70(pTarget, 6, pTool, 200.0f);
                    }
                }
                else {
                    cSPSimulatorSpaceGame_s0105_a110* pGame = SpaceGameGet_s0105_a110();
                    pGame->GetPlayerInventory();

                    int bHas = FUN_00c0c380(pSpatial) != 0;
                    void* pSpecies = pBuilding->FUN_00c0bc00(1, bHas);
                    void* pList = FUN_00c463d0(0);
                    void* pMgr = FUN_00b3d450();
                    FUN_00ac0cb0(pList, pSpecies, 1, bHas);
                    if (pUFO->field714 == 0)
                        goto LAB_3f5;
                }
                goto LAB_825;
            }
        }
        else {
            cCreature* pCreature = (cCreature*)FUN_00b2a390(pSpatial);
            cPlanet_s0105_a110* pPlanet = (cPlanet_s0105_a110*)FUN_010536c0(pSpatial);
            if (!(pCreature == 0 && (pPlanet == 0 || (pPlanet->field88 != 0 && pPlanet->field88 != 1 && pPlanet->field88 != 2)))) {
                // human / plant path
                uint8_t bResult = 1;
                if (pUFO == 0 || pUFO->field714 != 0)
                    goto LAB_756;

                cSPSimulatorSpaceGame_s0105_a110* pGame = SpaceGameGet_s0105_a110();
                cSPSpaceInventory_s0105_a110* pInventory = pGame->GetPlayerInventory();

                void* pSpecies;
                if (pCreature)
                    pSpecies = pCreature->FUN_00c3e1e0(0);
                else
                    pSpecies = (uint8_t*)pPlanet + 0x7c;

                void* pSpeciesMgr = FUN_00b3d420();
                void* pSpeciesObj = FUN_00b90410(pSpeciesMgr, pSpecies);
                AutoRefCountIWinText ref;
                ref.mpText = 0;
                void* pProp = FUN_00c463d0(&ref);
                ((cSPSpaceInventoryItem_s0105_a110*)pSpeciesObj)->v14(pProp);
                uint8_t bOk = pInventory->v80((cSPSpaceInventoryItem_s0105_a110*)pSpeciesObj, 0, 0);
                if (!bOk) {
                    SetErrorEvent(pTool, 0xb24b77da, true);
                    pCreature = 0;
                    bResult = 0;
                }
                else {
                    bResult = 1;
                }
                FUN_00c463d0(&ref);
                if (bResult)
                    goto LAB_756;
                goto LAB_796;

LAB_756:
                if (!pCreature) {
                    cWalkAround* pWalk = (cWalkAround*)FUN_01015df0();
                    if (!pWalk)
                        goto LAB_825;
                    pWalk = (cWalkAround*)FUN_01015df0();
                    if (!FUN_01016470(pPlanet) && pPlanet->field54 != 0)
                        pWalk->SetHighLODPlant(pPlanet);
                    pCreature = (cCreature*)FUN_01015fa0(pPlanet);
                }

LAB_796:
                if (!pCreature)
                    goto LAB_825;

                if (pUFO && pUFO->field714 == 0) {
                    cArtifactSub* pSub = &pCreature->mSub5e8;
                    if (pSub->GetID() != 0x114242e6) {
                        BehaviorManager()->v38(pSub);
                        void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                        pSub->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                        ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pSub->v20());
                        ((cGlobalManager*)FUN_00b3d3b0())->FUN_00b2c980(pCreature, 1);
                    }
                }
                goto LAB_825;
            }

            // artifact path
            cArtifact* pArtifact = (cArtifact*)FUN_01030e40(pSpatial);
            if (!pUFO || pUFO->field714 != 0 || !pArtifact)
                goto LAB_825;
            if (pArtifact->mSub5d0.GetID() == 0x114242e6)
                goto LAB_825;
            if (!pArtifact->byte65e)
                goto LAB_825;

            uint8_t bResult = 0;
            cSPSimulatorSpaceGame_s0105_a110* pGame = SpaceGameGet_s0105_a110();
            cSPSpaceInventory_s0105_a110* pInventory = pGame->GetPlayerInventory();

            switch (pArtifact->field658) {
            case 2: {
                ResourceKey key;
                void* pKey = pArtifact->FUN_00ad2620(&key);
                if (pKey != (void*)0x16e1b20 && pArtifact->field638 != 0) {
                    AutoRefCountIWinText ref;
                    ref.mpText = 0;
                    void* pProp = FUN_00c463d0(&ref);
                    ResourceKey key2;
                    void* pKey2 = pArtifact->FUN_00ad2620(&key2);
                    void* pMgr = FUN_00b3d390();
                    if (((cToolManager*)pMgr)->CreateToolFromToolID(pProp))
                        bResult = 1;
                    FUN_00c463d0(&ref);
                }
                if (bResult)
                    goto LAB_642;
                break;
            }
            case 4: {
                cSPSpaceInventoryItem_s0105_a110* pItem = (cSPSpaceInventoryItem_s0105_a110*)operator_new(0x7c, "Simulator/cSpaceInventoryItem", 0, 0, 0, 0);
                if (pItem)
                    pItem->Construct();
                FUN_0061df40(0, pItem);
                if (pArtifact->field638 != 0) {
                    pItem->field14 = 4;
                    ResourceKey key;
                    void* pKey = pArtifact->FUN_00ad2620(&key);
                    pItem->v14(pKey);
                    pItem->field10 = pArtifact->field638;
                    pArtifact->byte65c = 1;
                    bool bOk = pInventory->v80(pItem, 0, 0);
                    pItem->v08();
                    bResult = bOk;
                }
                if (bResult)
                    goto LAB_642;
                break;
            }
            case 5: {
                ResourceKey key;
                void* pKey = pArtifact->FUN_00ad2620(&key);
                AutoRefCountIWinText ref;
                ref.mpText = 0;
                void* pProp = FUN_00c463d0(&ref);
                FUN_00c878d0(pKey);
                FUN_00c463d0(&ref);
                break;
            }
            case 7:
LAB_642: {
                cArtifactSub* pSub = &pArtifact->mSub5d0;
                BehaviorManager()->v38(pSub);
                pArtifact->field224 = 4;
                void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                pSub->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pSub->v20());
                goto LAB_825;
            }
            default:
                break;
            }
        }
    }

LAB_3f5:
    SetErrorEvent(pTool, 0xb24b77da, true);
    goto LAB_825;

LAB_825:
    if (pTool->mpOwnerObject)
        pTool->mpOwnerObject->FUN_00cb5bb0();

LAB_838:
    {
        cTerrainEditor* pEditor = (cTerrainEditor*)NounManager_s0105_a110();
        if (pEditor->GetCurrentTerrainSphere()) {
            cTerrainEditor* pEditor2 = (cTerrainEditor*)NounManager_s0105_a110();
            pEditor2 = pEditor2->GetCurrentTerrainSphere();
            pEditor2->FUN_00c77bf0(0x56d1874);
        }
    }
    return true;
}

// @ 0x0105a890
bool cSPScanToolStrategy_s0105_a110::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    GetActivePlanet();

    if (!CanDoToolAction(pTool, position, a3, 0))
        return true;

    if (!pTool->mpOwnerObject)
        return true;

    if (!pTool->mpOwnerObject->FUN_006e87e0())
        return true;

    uint8_t bResult = 0;
    cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
    if (pSpatial) {
        void* pBuilding = pSpatial->Cast(0xce9f6639);
        if (pBuilding) {
            bResult = ScanBuilding(pBuilding);
            goto LAB_aa0e;
        }

        void* pPlanet = pSpatial->Cast(0x3ed590d);
        if (pPlanet) {
            uint32_t nType = *(uint32_t*)((uint8_t*)pPlanet + 0x88);
            if (nType == 0 || nType == 1 || nType == 2) {
                bResult = ScanAllSpecies((uint8_t*)pPlanet + 0x7c);
                goto LAB_aa0e;
            }
        }
    }

    void* pTribe = FUN_00ae6760(pSpatial);
    if (pTribe) {
        bResult = ScanTribe(pTribe);
        goto LAB_aa0e;
    }

    void* pBuilding2 = FUN_00b67720(pSpatial);
    if (pBuilding2) {
        bResult = ScanSpecies(pBuilding2);
        goto LAB_aa0e;
    }

    void* pColony = FUN_00b67740(pSpatial);
    if (pColony) {
        bResult = ScanColony(pColony);
        goto LAB_aa0e;
    }

    void* pArtifact = FUN_01030e40(pSpatial);
    if (pArtifact) {
        ToolHitMessage msg;
        msg.Construct(0);
        msg.mData[0].mpData = pArtifact;
        cMessageServer* pServer = (cMessageServer*)MessageServer();
        pServer->MessageSend(0xf46092d3, &msg, 0);
        msg.Destruct();
    }
    else {
        void* pOther = FUN_00bd8460(pSpatial);
        if (pOther) {
            ToolHitMessage msg;
            msg.Construct(0);
            msg.mData[0].mpData = pOther;
            cMessageServer* pServer = (cMessageServer*)MessageServer();
            pServer->MessageSend(0xf46093da, &msg, 0);
            msg.Destruct();
        }
    }

LAB_aa0e:
    if (pTool->mpOwnerObject)
        pTool->mpOwnerObject->FUN_00cb5bb0();

    if (bResult) {
        IAudioSystem* pAudio = GetSystemAT();
        void* pAudioArg = pAudio ? pAudio->v20() : 0;
        KillSetiEffects(0x75c412dd, pAudioArg);
    }
    return true;
}

// @ 0x0105b0f0
bool __stdcall EnergyRepairDoToolAction(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        ItemBase* item = self->item;
        if (item) {
            RepairObj* obj = (RepairObj*)item->FindPlugin(0xb033b403);
            if (obj && !obj->f714) {
                float v = obj->f7f8;
                if (v > obj->f7f4) obj->Repair(v * self->GetRate() * 0.01f);
                return true;
            }
        }
    }
    return false;
}

// @ 0x0105b180
bool __stdcall FUN_0105b180(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        Combatant* c = 0;
        ItemBase* item = self->item;
        if (item) c = (Combatant*)item->FindPlugin(0x13f94d4);
        float cap = c->f38;
        if (c->Slot58() > cap) {
            float r = c->Slot58() * self->GetRate() * 0.01f;
            c->PartialRepair(r);
            FVec8* v = (FVec8*)SpaceGameGet_s0105_aa50()->f5180(0xc);
            v->resize(8);
            v->mData[7] = r;
            return true;
        }
    }
    return false;
}

// @ 0x0105b240
bool __stdcall GetOutOfUFODoToolAction(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        if (self->CanUse()) {
            self->SetValue(-1);
            if (self->GetCount() <= 0) {
                Inv* inv = SpaceGameGet_s0105_aa50()->GetPlayerInventory();
                int handle = inv->Find(self->f14, (int)self->GetKey());
                void* taken = self;
                self->Slot1();
                if (SpaceGameGet_s0105_aa50()->GetPlayerInventory()->Take(handle, &taken, -1)) {
                    SpaceGameGet_s0105_aa50()->GetPlayerInventory()->Refresh();
                }
                if (taken) ((Unk*)taken)->Release();
            }
        }
        SpaceGameGet_s0105_aa50()->F1003480();
        WalkAround* wa = F1015df0();
        wa->GetOutOfUFO();
        WindowManager()->Slot4c(0, WindowManager()->Slot1());
        return true;
    }
    return false;
}

// @ 0x0105b6a0
bool __stdcall PlaceColonyCanUseToolAtLocation(Strategy* self, Vec3_s0105_aa50* pos, int a3)
{
    if (!CanUseToolBase(self, pos, a3)) return false;
    Planet* pm = PlanetModel_s0105_aa50();
    if (pm && pm->Fb7e3e0(pos)) {
        SetErrorEvent(self, 0xd7ff4c0b, a3);
        return false;
    }
    Cursor* cur = GetGameTerrainCursor_s0105_aa50();
    ColonyObj* probe = (ColonyObj*)cur->SlotD4();
    if (!probe) return false;
    ColonyObj* obj = (ColonyObj*)probe->SlotB8(0x2450023);
    if (!obj) return false;
    obj->Slot0();
    obj->sub.SetPosition(pos);
    Nm* nm = NounManager_s0105_aa50();
    GameDataVec* vec = NounManager_s0105_aa50()->GetGameDataVector(0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, (void*)0x18c43e8);
    GDElem** it = (GDElem**)vec->mBegin;
    GDElem** end = (GDElem**)vec->mEnd;
    for (; it != end; ++it) {
        GDElem* e = *it;
        if (!e->Slot2c()) {
            int z = e->ProfLeaveZone();
            if (z && self->Slot64((void*)z)) {
                SetErrorEvent(self, 0x147e3c98, a3);
                obj->Slot1();
                return false;
            }
        }
    }
    GameDataVec* vec2 = nm->GetGameDataVector(0xcd7d10, 0xd3d420, 0xae5ea0, 0xb1e500, (void*)0x403df5c);
    float r = obj->sub.Radius();
    float radius = r * obj->sub.Radius() - g_oneF;
    bool found = false;
    GDElem** it2 = (GDElem**)vec2->mBegin;
    GDElem** end2 = (GDElem**)vec2->mEnd;
    for (; it2 != end2; ++it2) {
        Vec3_s0105_aa50* p = (Vec3_s0105_aa50*)(*it2)->sub.Slot2c();
        if ((pos->y - p->y) * (pos->y - p->y) + (pos->z - p->z) * (pos->z - p->z)
            + (pos->x - p->x) * (pos->x - p->x) <= 14400.0f) {
            SetErrorEvent(self, 0x1458fe70, a3);
            obj->Slot1();
            return false;
        }
        Vec3_s0105_aa50* q = (Vec3_s0105_aa50*)(*it2)->sub.Slot2c();
        if ((pos->z - q->z) * (pos->z - q->z) + (pos->y - q->y) * (pos->y - q->y)
            + (pos->x - q->x) * (pos->x - q->x) <= radius) {
            found = true;
        }
    }
    if (!found) SetErrorEvent(self, 0xc18c8011, a3);
    obj->Slot1();
    return found;
}

// @ 0x0105b960
bool cSPCityMarkerStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        FUN_00fdc340(position, g_radius100);
        SimSingleton::Get()->AddMarker((void*)&FUN_01058c90, (int)GetPlayerEmpireID(), &position,
                                       0, 0xfd701f6f, 0, 0, 0);
        return true;
    }
    return false;
}

// @ 0x0105ba00
bool cSPPlaceObjectToolStrategy_s0105_b960::CanUseToolAtLocation(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3)
{
    if (!CanUseToolAction(pTool, position, a3))
        return false;
    cPlanetModel_s0105_b960* model = PlanetModel_s0105_b960();
    if (model && model->FUN_00b7e3e0(position)) {
        FUN_010527f0(pTool, 0xcebd3c75, a3);
        return false;
    }

    cGameObject_s0105_b960* hover = GetGameTerrainCursor()->GetHoverObject();
    cGameObject_s0105_b960* obj = hover ? hover->Cast(0x2450023) : 0;
    if (obj)
        obj->AddRef();

    cGameDataVector* cities = (cGameDataVector*)NounManager_s0105_b960()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0, (void*)0x00b1e500,
        (void*)0x018c43e8);
    cGameObject_s0105_b960** cityEnd = cities->mpEnd;
    for (cGameObject_s0105_b960** it = cities->mpBegin; it != cityEnd; ++it) {
        cSpaceCity* city = (cSpaceCity*)*it;
        float dist = Distance(*city->mLocation.GetPosition(), *obj->mLocation.GetPosition());
        if (dist < obj->mLocation.GetRadius() + city->mLocation.GetRadius()) {
            FUN_010527f0(pTool, 0x9ad55101, a3);
            if (obj)
                obj->Release();
            return false;
        }
    }

    cGameDataVector* others = (cGameDataVector*)NounManager_s0105_b960()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00dc3250, (void*)0x00b1e500,
        (void*)0x04e3fab5);
    cGameObject_s0105_b960** otherEnd = others->mpEnd;
    for (cGameObject_s0105_b960** it = others->mpBegin; it != otherEnd; ++it) {
        cGameObject_s0105_b960* other = *it;
        float dist = Distance(*other->mLocation.GetPosition(), *obj->mLocation.GetPosition());
        if (dist < obj->mLocation.GetRadius() + g_radius10) {
            FUN_010527f0(pTool, 0x90ab2881, a3);
            if (obj)
                obj->Release();
            return false;
        }
    }

    if (obj)
        obj->Release();
    return true;
}

// @ 0x0105bc70
bool cSPPlaceObjectStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        if (!KeyEquals(pTool->GetToolID(), k_placeuberturret)) {
            float health = GetSpaceCombatTuning()->GetColonyObjectHealth();
            FUN_00ff8560(pTool->CreateImpact(), position, health);
            return true;
        }
        FUN_0102b780(pTool->CreateImpact(), position);
        return true;
    }
    return false;
}

// @ 0x0105bd00
bool cSPArtilleryWeaponStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    return cSPToolStrategy_s0105_b960::OnHit(pTool, position, a3, 0);
}

// @ 0x0105bd20
bool cSPMindEraseToolStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    if (FUN_0105a050(pTool, position, a3, 0) && pTool->mpOwnerObject) {
        float height = pTool->FUN_0104bdb0();
        cGameDataVector* cities = (cGameDataVector*)NounManager_s0105_b960()->GetGameDataVector(
            (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0, (void*)0x00b1e500,
            (void*)0x018c43e8);
        cErasedCityObject* city =
            (cErasedCityObject*)FUN_00ac9310((void**)&cities->mpBegin, position, false);
        if (city) {
            city->mRecords.FUN_00bdf3e0();
            tErasedCityRecord* record = city->mRecords.mpEnd - 1;
            record->mPosition = position;
            city->mRecords.mpEnd[-1].mEffectHeight = height;
        }
    }
    return true;
}

// @ 0x0105bde0
bool cCropCirclesToolStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        cSpaceGame* game = SpaceGameGet_s0105_b960();
        if (game && GetCurrentGameMode() == &g_spaceMode) {
            cEffectFactory* factory = EffectsManagerPtr()->GetFactory(0x3701a5c);
            void* key = 0;
            GetPropertyAsKeyInstance(pTool->mpToolProperties, 0x719f6876, &key);
            cEffectInstance* effect = 0;
            if (key && factory->CreateInstance(key, 0, &effect)) {
                XformMsg_s0105_b960 msg;
                msg.SetPos(position);
                Quaternion orientation;
                Matrix33 rot;
                msg.SetRot(QuaternionToMatrix(
                    rot, *PlanetModel_s0105_b960()->BuildSurfaceOrientation(&orientation, position)));
                effect->SetXform(&msg);
                effect->Enable(0);
            }
            game->GetAvatar()->FUN_00ff88c0(position, effect);
            if (effect)
                effect->Release();
            return true;
        }
        return false;
    }
    return false;
}

// @ 0x0105bf50
bool cSPGenesisDeviceToolStrategy::DoToolAction(cSpaceToolData_s0105_b960* pTool, const Vector3_s0105_b960& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        cSpaceGame* game = SpaceGameGet_s0105_b960();
        if (game && GetCurrentGameMode() == &g_spaceMode) {
            game->GetAvatar()->FUN_00ff6450(position);
            return true;
        }
        return false;
    }
    return false;
}
