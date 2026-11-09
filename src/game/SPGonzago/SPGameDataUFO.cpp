// src/game/SPGonzago/SPGameDataUFO.cpp -- migrated from slice(s) s0105c8d0, s0105b960, s00c3ae70, s00c3a180, s00c3daa0, s00c3cd60, s00c3bfe0, s00c38d00, s00c389f0, s00c368c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameDataUFO.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cEmpire.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern float       g_kZero;        // 0x01485378
extern float       g_kEpsilon;     // 0x0146bb74
#include <math.h>
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPGameDataUFO.h"
#include <string.h>
#include <intrin.h>
#include "cSPVector3.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cStarManager.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cSpatialObject.h"
#include <stdlib.h>
#include "SP/cCameraManager.h"
#include "SP/cInteractionTarget.h"
#include "SP/cViewer.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPTimer.h"

// ---- items of slice s00c368c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
typedef void*  (__thiscall *TFp0)(void*);
typedef void*  (__thiscall *TFpk)(void*, u32);
typedef float* (__thiscall *TFfp0)(void*);
typedef float  (__thiscall *TFf0)(void*);
typedef void   (__thiscall *TFv0)(void*);
typedef void   (__thiscall *TFv4)(void*, u32, void*, void*, void*);
extern float       g_kZero;        // 0x01485378
extern float       g_kEpsilon;     // 0x0146bb74
extern u32         g_168df70;      // 0x0168df70
extern u32         g_168df6c;      // 0x0168df6c
struct PlanetGlob {
  u8    pad00[0x0c];   // +0x000
  float f0c;           // +0x00c
  float f10;           // +0x010
  u8    pad14[0x08];   // +0x014
  float f1c;           // +0x01c
  float f20;           // +0x020
};
extern PlanetGlob* g_planetGlob;   // 0x0168df68
void*  __stdcall FUN_00b18460(u32 key);        // 0x00b18460
void*  __cdecl FUN_01021300();                 // 0x01021300 (GetPlayerEmpire)
void*  __cdecl MessageServer();                // 0x0067dcc0
struct SpaceGameC;
SpaceGameC* __cdecl SpaceGameGet();           // 0x01002bd0
float  __fastcall FUN_00b7e4d0(void* planet);  // 0x00b7e4d0
float  __fastcall FUN_0104be20(void* t);       // 0x0104be20
float  __fastcall FUN_0104be30(void* t);       // 0x0104be30
u8     __fastcall FUN_0104fff0(void* t);       // 0x0104fff0
void*  __cdecl FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, u32 c, u32 d);
bool   __cdecl WriteUint32(void* stream, const u32* v, u32 n, s32 f);
bool   __cdecl StreamWrite(void* stream, const void* data, s32 n);
struct PlanetModelC {
  float GetRadiusAt(float* pos);   // 0x00b7ef70
  float GetWaterHeight();          // 0x00b7e390
};
PlanetModelC* __cdecl PlanetModel();   // 0x00b3d350
struct NounMgr;
NounMgr* __cdecl NounManager();        // 0x00b3d300
struct PtrVec {
  u32* mBegin;   // +0x00
  u32* mEnd;     // +0x04
  u32* mCap;     // +0x08
};
struct Loco {
  void* vtbl;              // +0x00  (ufo+0x34)
  void* Find(u32 key);                       // 0x00c41d00
  void  Set(void* p);                        // 0x00c421b0
  u8    Write(void* stream);                 // 0x00c448a0
};
struct Combat {
  void* vtbl;              // +0x00  (ufo+0x508)
  void* Find2(u32 key);                      // 0x00bfc380
  u8    Write(void* stream);                 // 0x00bfc4a0
};
struct CCombatant0 {
  void NotifyAttack(void* p);                // 0x010829f0
};
struct Timer {
  u8 data[0x3c];                             // 0x00c37b8 sized subobject
  void Restart();                            // 0x00bc3130
};
struct Sub70 {
  u8  pad00[0x70];
  u32 f70;                                   // +0x070
};
struct BehTree {
  void Write(void* stream);                  // 0x00bc9a80
};
struct F18Obj {
  u8    pad00[0x18];
  float f18;                                 // +0x018
};
struct Ufo {
  void*  vtbl;                 // +0x000
  u8     pad004[0x30];         // +0x004
  Loco   loco;                 // +0x034
  u32*   p38;                  // +0x038
  u8     pad03c[0x1c];         // +0x03c
  float  f58;                  // +0x058
  u32    idx5c;                // +0x05c
  u8     pad060[0x1a8];        // +0x060
  void*  p208;                 // +0x208
  u8     pad20c[0x2fc];        // +0x20c
  Combat combat;               // +0x508
  u8     pad50c[0x34];         // +0x50c
  float  f540;                 // +0x540
  u8     pad544[0x184];        // +0x544
  void*  p6c8;                 // +0x6c8
  u8     pad6cc[0x14];         // +0x6cc
  u32    u6e0;                 // +0x6e0
  u8     pad6e4[0x30];         // +0x6e4
  u32    state714;             // +0x714
  u8     pad718[0x4c];         // +0x718
  void*  p764;                 // +0x764
  u8     pad768[0x14];         // +0x768
  u8     b77c;                 // +0x77c
  u8     b77d;                 // +0x77d
  u8     b77e;                 // +0x77e
  u32    k780;                 // +0x780
  u32    k784;                 // +0x784
  u32    k788;                 // +0x788
  u8     b78c;                 // +0x78c
  u8     b78d;                 // +0x78d
  u8     pad78e[0x0a];         // +0x78e
  void*  p798;                 // +0x798
  void*  p79c;                 // +0x79c
  void*  p7a0;                 // +0x7a0
  void*  p7a4;                 // +0x7a4
  u8     pad7a8[0x08];         // +0x7a8
  void*  p7b0;                 // +0x7b0
  u8     pad7b4[0x04];         // +0x7b4
  Timer  timer;                // +0x7b8
  float  f7f4;                 // +0x7f4
  float  f7f8;                 // +0x7f8
};
struct LocoF {
  u8    pad000[0x144];
  float f144;                  // +0x144
  float f148;                  // +0x148
  float f14c;                  // +0x14c
  float f150;                  // +0x150
};
struct ParamObj {
  void*  vtbl;                 // +0x000  (vtable of the source object)
  PtrVec vec;                  // +0x004
};
struct Cand {
  u8    pad000[0xc0];          // +0x000
  void* vtbl;                  // +0x0c0
  u8    pad0c4[0x135 - 0xc4];  // +0x0c4
  u8    b135;                  // +0x135
  u8    pad136[0xb1c - 0x136]; // +0x136
  s32   b1c;                   // +0xb1c
  u8    padB20[0xb5e - 0xb20]; // +0xb20
  u8    b5e;                   // +0xb5e
};
struct GDVec {
  u32  pad00;
  u32* mBegin;                 // +0x004
  u32* mEnd;                   // +0x008
};
struct NounMgr {
  GDVec* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
  void*  GetPlayerEmpireOrMinus1();       // 0x00b1f9d0
};
struct Empire {
  void SetUFOKey(void* key);              // 0x00c35740
};
struct Inventory {
  u8  pad00[0x76c];
  s32 f76c;                               // +0x76c
};
struct UFOsim {
  Inventory* GetPlayerInventory();        // 0x00a1ad60
};
UFOsim* __cdecl GetUFOSimulator();        // 0x00ffbe50
struct SpaceGameC {
  u8 f4c30();                             // 0x01004c30
};
struct CGameData {
  u8 Write(void* stream);                 // 0x00b18590
  void GetCastID();                       // 0x00bfcac0
};
struct CCommunity {
  void func54h(s32 id);                   // 0x00c88670
};
struct CInteractable {
  void SetEffectId(s32 id, float v);      // 0x00c3f160
};
struct Big28 {
  void* Init();                           // 0x0105d180
};
struct cVarListSerializer {
  u32 mData[0xa14 / 4];                   // +0x000
  void Ctor(void* owner, void* list, u32 sig);  // 0x00692f90
  u8   Serialize(void* stream);                 // 0x00692900
};
// ---- items of slice s00c368c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32         g_168df70;      // 0x0168df70
extern u32         g_168df6c;      // 0x0168df6c
extern PlanetGlob* g_planetGlob;   // 0x0168df68

// ---- items of slice s00c389f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
struct RefObj {                            // looked-up object: vtable + counters
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool vf2c();                   // +0x2c (slot 11, vptr at +0)
    uint8_t  pad04[0x224 - 0x04];          // +0x04 .. +0x223
    uint32_t m224;                         // +0x224
    uint32_t m228;                         // +0x228
    uint8_t  pad22c[0x638 - 0x22c];        // +0x22c .. +0x637
    uint32_t m638;                         // +0x638
    uint32_t m63c;                         // +0x63c
};
struct LookupObj {                         // smart pointer at UFOThing+0x7a8/0x7ac
    PV(0)
    virtual void    Release();             // +0x04 (slot 1)
    virtual void    d2();                  // +0x08 (slot 2)
    virtual RefObj* vf0c(uint32_t hash);   // +0x0c (slot 3)
};
struct UFOThing {
    void*      vft;                        // +0x000
    uint8_t    pad04[0x710];               // +0x004 .. +0x713
    uint32_t   m714;                       // +0x714
    uint8_t    pad718[0x90];               // +0x718 .. +0x7a7
    LookupObj* mp7a8;                      // +0x7a8
    LookupObj* mp7ac;                      // +0x7ac
    uint8_t    pad7b0[0x44];               // +0x7b0 .. +0x7f3
    float      m7f4;                       // +0x7f4
    float      m7f8;                       // +0x7f8

    float FUN_00c389f0(float d);           // 0x00c389f0
    void  FUN_00c38b10();                  // 0x00c38b10
    void  FUN_00c38b90();                  // 0x00c38b90
};
struct UFOObj     { void FUN_00ffc020(); };                 // 0x00ffc020
struct MissionMgr { bool IsRunning(); };                    // 0x00feba90
struct TerrainSphere {
    bool FUN_00c772c0(uint32_t hash);      // 0x00c772c0
    void FUN_00c77bf0(uint32_t hash);      // 0x00c77bf0
};
struct cTerrainEditor {
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct MsgObj     { void FUN_0106dcd0(); };                 // 0x0106dcd0
UFOObj*         GetUFOSimulator_s00c3_89f0();          // 0x00ffbe50
MissionMgr*     GetMissionManager();        // 0x00feb9f0
cTerrainEditor* NounManager_s00c3_89f0();              // 0x00b3d300
MsgObj*         FUN_010666a0(uint32_t);     // 0x010666a0
struct MsgHandler5 { uint32_t a, b, c, d, e; };
void EA_RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0
namespace Skinner {
struct PaintSystem {                       // base, vtbl 0x13eb394
    virtual ~PaintSystem() {}              // trivial: contributes only a vptr
};
}
struct PaintSystemExt : Skinner::PaintSystem {   // own vtbl 0x146bb78
    LookupObj* mp04;                       // +0x004
    uint8_t    pad08[0x18];                // +0x008 .. +0x01f
    float      m20;                        // +0x020
    uint8_t    pad24[0x184];               // +0x024 .. +0x1a7
    MsgHandler5 msg;                       // +0x1a8 .. +0x1bb

    PaintSystemExt();                      // 0x00c38c50
    virtual ~PaintSystemExt();             // 0x00c38c90
};
struct OffsetHolder {
    void GetPos(Vec3* out);                // 0x00c38c20
};
// ---- items of slice s00c389f0 end

// ---- items of slice s00c38d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  float* GetFloat();     // 0x0041EA70
  bool* GetBool();       // 0x0041E920
};
class cPropertyList {
 public:
  virtual void v000();
  virtual void v004();
  virtual void v008();
  virtual void v00c();
  virtual void v010();
  virtual void v014();
  virtual void v018();
  virtual void v01c();
  virtual void v020();
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};
template <class T>
struct AutoRefCount {
  T* mpObject;
};
struct IHandler {
  virtual void v000();
};
class cUFOKinestheticsTuning : public IHandler {
 public:
  AutoRefCount<cPropertyList> mPropList;  // +0x04

  float mHitTerrainDamage;                  // +0x08
  float mMinAltitude;                       // +0x0C
  float mMaxAltitude;                       // +0x10
  float mDamageToDestScale;                 // +0x14
  float mDamageToVelocityScale;             // +0x18
  float mHitSphereRadius;                   // +0x1C
  float mHitSphereActiveDistance;           // +0x20
  float mMinExtent;                         // +0x24
  float mBomberScale;                       // +0x28
  float mFighterScale;                      // +0x2C
  float mUberTurretScale;                   // +0x30
  float mAllyScale;                         // +0x34
  float mPlumpDistance;                     // +0x38
  float mPlumpScale;                        // +0x3C
  float mPlumpTransitionScale;              // +0x40
  float mNPCPlumpScale;                     // +0x44
  float mBasePlanetScale;                   // +0x48
  float mVelocityFactor;                    // +0x4C
  float mVelocityFactorNPC;                 // +0x50
  float mFighterVelocityFactor;             // +0x54
  float mUberTurretVelocityFactor;          // +0x58
  float mAllyVelocityFactor;                // +0x5C
  float mKeyboardMovementSpeedZoomedOut;    // +0x60
  float mKeyboardMovementSpeedZoomedIn;     // +0x64
  float mKeyboardAccelerationZoomedOut;     // +0x68
  float mKeyboardAccelerationZoomedIn;      // +0x6C
  float mBomberVelocityFactor;              // +0x70
  float mVelocityFactorZoomedOut;           // +0x74
  float mMouseMovementSpeedZoomedOut;       // +0x78
  float mMouseMovementSpeedZoomedIn;        // +0x7C
  float mMouseRotationSpeedZoomedOut;       // +0x80
  float mMouseRotationSpeedZoomedIn;        // +0x84
  float mLeavePlanetTimePad;                // +0x88
  float mMaxRotation;                       // +0x8C
  float mTargetFallOffRadius;               // +0x90
  float mBrakeFactor;                       // +0x94
  float mBrakeOvershootFactor;              // +0x98
  float mAccelerationFactor;                // +0x9C
  float mAccelerationFactorNPC;             // +0xA0
  float mVerticalAcclerationDown;           // +0xA4
  float mVerticalAcclerationUp;             // +0xA8
  float mCollisionElasticity;               // +0xAC
  float mCollisionRestitution;              // +0xB0
  float mRotationPercentageRate;            // +0xB4
  float mNoseTiltFactor;                    // +0xB8
  float mNoseTiltRate;                      // +0xBC
  float mMaxNoseTilt;                       // +0xC0
  float mVerticalTiltFactor;                // +0xC4
  float mMaxVerticalTilt;                   // +0xC8
  float mBankTiltFactor;                    // +0xCC
  float mBankTiltRate;                      // +0xD0
  float mMaxBankTilt;                       // +0xD4
  float mEscapeSequenceSpinRate;            // +0xD8
  float mEscapeSequenceVelocity;            // +0xDC
  float mTrailEffectAlwaysOn;               // +0xE0
  float mEffectMaxSpeedPlanet;              // +0xE4
  float mEffectMaxSpeedSolar;               // +0xE8
  float mEffectMaxSpeedGalaxy;              // +0xEC
  float mTrailEffectMinSize;                // +0xF0
  float mMaxAltitudeDestinationDelta;       // +0xF4
  float mSolarSpeed;                        // +0xF8
  bool mSolarAcceleration;                  // +0xFC
  char pad_fd[3];
  float mGalaxySpeed;                       // +0x100
  float mGalaxyAcceleration;                // +0x104
  float mSolarMinPlump;                     // +0x108
  float mSolarMaxPlump;                     // +0x10C
  float mGalaxyMinPlump;                    // +0x110
  float mGalaxyMaxPlump;                    // +0x114
  float mGalaxyMinPlumpDistance;            // +0x118
  float mGalaxyMaxPlumpDistance;            // +0x11C
  float mBaseUFODamagePush;                 // +0x120
  float mMaxUFODamagePush;                  // +0x124
  float mUFODamageVelocityDecayRate;        // +0x128
  float mAltMaxAltitude;                    // +0x12C
  float mAltPlumpDistance;                  // +0x130
  float mAltVelocityFactorZoomedOut;        // +0x134
  float mExtra138;                          // +0x138
  float mExtra13c;                          // +0x13C
  float mExtra140;                          // +0x140
  float mExtra144;                          // +0x144
  float mExtra148;                          // +0x148
  float mExtra14c;                          // +0x14C
  float mExtra150;                          // +0x150
  float m2HitTerrainDamage;                 // +0x154
  float m2MinAltitude;                      // +0x158
  float m2MaxAltitude;                      // +0x15C
  float m2DamageToDestScale;                // +0x160
  float m2DamageToVelocityScale;            // +0x164
  float m2HitSphereRadius;                  // +0x168
  float m2HitSphereActiveDistance;          // +0x16C
  float m2MinExtent;                        // +0x170
  float m2BomberScale;                      // +0x174
  float m2FighterScale;                     // +0x178
  float m2UberTurretScale;                  // +0x17C
  float m2AllyScale;                        // +0x180
  bool m2PlumpDistance;                     // +0x184
  char pad_185[3];
  float m2PlumpScale;                       // +0x188
  float m2PlumpTransitionScale;             // +0x18C
  float m2NPCPlumpScale;                    // +0x190
  float m2BasePlanetScale;                  // +0x194
  float m2VelocityFactor;                   // +0x198
  float m2VelocityFactorNPC;                // +0x19C
  float m2FighterVelocityFactor;            // +0x1A0
  float m2UberTurretVelocityFactor;         // +0x1A4

  void ReadProps();
};
inline void GetFloatProp(cPropertyList* list, uint32_t id, float& out) {
  Property* p;
  if (list && list->GetProperty(id, p) && p->mType == 0xd) out = *p->GetFloat();
}
inline void GetBoolProp(cPropertyList* list, uint32_t id, bool& out) {
  Property* p;
  if (list && list->GetProperty(id, p) && p->mType == 1) out = *p->GetBool();
}
// ---- items of slice s00c38d00 end

// ---- items of slice s00c3bfe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char    g_sz_Simulator[];        // 0x13f09b4  "Simulator"
extern char          g_allocator_13ebb38[];   // 0x13ebb38  EASTL allocator
extern const wchar_t g_wsz_UninitUfoName[];   // 0x146be08  L"UNINITIALIZED UFO NAME"
extern float gF_1470f1c;   // 2.0
extern float gF_1485720;   // HK_REAL_ONE (1.0)
extern float gF_13ec4b4;   // FLT_MAX
extern float gF_146bb6c;   // 0.9
extern float gF_168df74;
extern float gF_168df78;
extern float gF_168df7c;
extern float gF_15731bc;
extern float gF_15731c0;
extern float gF_15731c4;
extern float gF_15731c8;
extern float gF_15731cc;
extern float gF_15731d0;
extern float gF_15731d4;
extern float gF_13ec5b4;
typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned short U16;
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct ListNodeBase {
    ListNodeBase* mpNext;   // +0
    ListNodeBase* mpPrev;   // +4
};
struct CollisionInfo {
    int      mNounID;       // +0
    Vector3  mPosition;     // +4
};
struct CollisionNode : public ListNodeBase {
    CollisionInfo mValue;   // +8
};
struct IRefObject {
virtual void q00();
virtual void q01();
virtual void q02();
virtual void q03();
virtual void q04();
virtual void q05();
virtual void q06();
virtual void q07();
virtual void q08();
virtual void q09();
virtual void q10();
virtual void q11();
virtual void q12();
virtual void q13();
virtual void q14();
virtual void q15();
virtual void q16();
virtual void q17();
virtual void q18();
virtual void q19();
virtual void q20();
virtual void q21();
virtual void q22();
virtual void q23();
virtual void q24();
virtual void q25();
virtual void q26();
virtual void q27();
virtual void q28();
virtual void q29();
virtual void q30();
virtual void q31();
virtual void q32();
virtual void q33();
virtual void q34();
virtual void q35();
virtual void q36();
virtual void q37();
virtual void q38();
virtual void q39();
virtual void q40();
virtual void q41();
virtual void q42();
virtual void q43();
virtual void q44();
virtual void q45();
virtual void q46();
    virtual int AddRef();    // +0xbc
    virtual int Release();   // +0xc0
};
struct RefHolder {
    IRefObject* mpObject;                                       // +0
    __forceinline RefHolder& operator=(const RefHolder& o)
    {
        if (mpObject != o.mpObject) {
            if (o.mpObject) o.mpObject->AddRef();
            IRefObject* pOld = mpObject;
            mpObject = o.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    __forceinline RefHolder& operator=(IRefObject* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            IRefObject* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
void* __cdecl operator_new(U32 size, const char* pName, int a, int b, void* pAlloc, U32 line);  // 0xf473a0
void  __cdecl operator_delete(void* p);                                                          // 0xf47380
Vector3* __cdecl GetCities();           // 0x005c65e0 cCivData::GetCities
struct FnB18660  { void  __thiscall f(); };                  // 0x00b18660 cGameData::cGameData
struct FnC43860  { void  __thiscall f(); };                  // 0x00c43860
struct FnBFD4E0  { void  __thiscall f(); };                  // 0x00bfd4e0 cCombatant::cCombatant
struct FnAC03D0  { void  __thiscall f(); };                  // 0x00ac03d0 cInteractionTarget::cInteractionTarget
struct FnBC3110  { void  __thiscall f(); };                  // 0x00bc3110 cSPTimer::Stop
struct FnB63890  { void  __thiscall f(); };                  // 0x00b63890 cGonzagoTimer::cGonzagoTimer
struct Fn423650  { void  __thiscall f(void*, void*); };      // 0x00423650 eastl wstring assign(first,last)
struct Fn105D1D0 { void* __thiscall f(); };                  // 0x0105d1d0
struct FnC421B0  { void  __thiscall f(void*); };             // 0x00c421b0
struct cPlanet;   // opaque
struct cSPGameDataUFO {
    void SetDestination(const Vector3* pDest);
    void SetDestination(cPlanet* pPlanet);
    void SetDestinationFromCities(int param);
    int  GetNextCollision(Vector3* pOut);
    void StartPlayerDeathSequence();
    cSPGameDataUFO();

    void* mpVftbl00;            // +0x000
    void* mpVftbl04;            // +0x004
    U32   md008[0x2c / 4];      // +0x008
    void* mpVftbl34;            // +0x034  cLocomotiveObject vftable
    float mf038;                // +0x038
    float mf03c;                // +0x03c
    float mf040;                // +0x040
    U32   md044[0xc4 / 4];      // +0x044
    void* mpVftbl108;           // +0x108
    U32   md10c[0x118 / 4];     // +0x10c
    int   mInt224;              // +0x224
    U32   md228[0x2e0 / 4];     // +0x228
    U32   mCombatant[0xc8 / 4]; // +0x508
    U32   mInteraction[0x18 / 4];// +0x5d0
    void* mpVftbl5e8;           // +0x5e8
    float mf5ec;                // +0x5ec
    float mf5f0;                // +0x5f0
    float mf5f4;                // +0x5f4
    float mf5f8;                // +0x5f8
    float mf5fc;                // +0x5fc
    float mf600;                // +0x600
    float mf604;                // +0x604
    U8    mb608;                // +0x608
    U8    md609[3];             // +0x609 (pad)
    float mf60c;                // +0x60c
    float mf610;                // +0x610
    float mf614;                // +0x614
    float mf618;                // +0x618
    float mf61c;                // +0x61c
    float mf620;                // +0x620
    U8    mb624;                // +0x624
    U8    md625[3];             // +0x625 (pad)
    U32   mTimer628[0x20 / 4];  // +0x628
    U32   mTimer648[0x20 / 4];  // +0x648
    U32   mTimer668[0x20 / 4];  // +0x668
    U8    mb688;                // +0x688
    U8    mb689;                // +0x689
    U16   mw68a;                // +0x68a (pad)
    U32   md68c;                // +0x68c
    U8    mb690;                // +0x690
    U8    mb691;                // +0x691
    U16   mw692;                // +0x692 (pad)
    float mf694;                // +0x694
    float mf698;                // +0x698
    float mf69c;                // +0x69c
    float mf6a0;                // +0x6a0
    float mf6a4;                // +0x6a4
    float mf6a8;                // +0x6a8
    float mf6ac;                // +0x6ac
    int   mInt6b0;              // +0x6b0
    float mf6b4;                // +0x6b4
    float mf6b8;                // +0x6b8
    float mf6bc;                // +0x6bc
    float mf6c0;                // +0x6c0
    float mf6c4;                // +0x6c4
    void* mp6c8;                // +0x6c8
    U32   md6cc;                // +0x6cc (pad)
    U32   mTimer6d0[0x20 / 4];  // +0x6d0
    U32   mTimer6f0[0x20 / 4];  // +0x6f0
    int   md710;                // +0x710
    int   mUFOType;             // +0x714
    float mf718;                // +0x718
    float mf71c;                // +0x71c
    float mf720;                // +0x720
    float mf724;                // +0x724
    float mf728;                // +0x728
    float mf72c;                // +0x72c
    float mf730;                // +0x730
    float mf734;                // +0x734
    float mf738;                // +0x738
    float mf73c;                // +0x73c
    float mf740;                // +0x740
    float mf744;                // +0x744
    float mf748;                // +0x748
    U8    mb74c;                // +0x74c
    U8    md74d[3];             // +0x74d (pad)
    Vector3 mDestination;       // +0x750
    RefHolder mRef75C;          // +0x75c
    RefHolder mRef760;          // +0x760
    int   mInt764;              // +0x764
    float mf768;                // +0x768
    int   md76c;                // +0x76c
    ListNodeBase mCollisions;   // +0x770
    U32   md778;                // +0x778 (pad)
    U8    mb77c;                // +0x77c
    U8    mb77d;                // +0x77d
    U8    mb77e;                // +0x77e
    U8    mb77f;                // +0x77f (pad)
    void* mp780;                // +0x780
    void* mp784;                // +0x784
    void* mp788;                // +0x788
    U8    mb78c;                // +0x78c
    U8    mb78d;                // +0x78d
    U16   mw78e;                // +0x78e (pad)
    void* mp790;                // +0x790
    void* mp794;                // +0x794
    void* mp798;                // +0x798
    void* mp79c;                // +0x79c
    void* mp7a0;                // +0x7a0
    void* mp7a4;                // +0x7a4
    void* mp7a8;                // +0x7a8
    void* mp7ac;                // +0x7ac
    void* mp7b0;                // +0x7b0
    U32   mTimer7b8[0x20 / 4];  // +0x7b8
    void* mp7d8;                // +0x7d8
    void* mp7dc;                // +0x7dc
    wchar_t* mNameBegin;        // +0x7e0  eastl wstring
    wchar_t* mNameEnd;          // +0x7e4
    wchar_t* mNameCapacity;     // +0x7e8
    U32   md7ec;                // +0x7ec (pad)
    RefHolder mRef7f0;          // +0x7f0
    float mf7f4;                // +0x7f4
    float mf7f8;                // +0x7f8
    int   mInt7fc;              // +0x7fc
    void* mp800;                // +0x800
    void* mp804;                // +0x804
    void* mp808;                // +0x808
    void* mp80c;                // +0x80c
    int   md810;                // +0x810
    int   md814;                // +0x814
};
struct DestParam {
    void* mpArray;      // +0x00
    U32   d004;         // +0x04
    U32   d008;         // +0x08
    U32   d00c;         // +0x0c  (uninitialised in the original)
    U32   d010;         // +0x10  (uninitialised in the original)
    float x;            // +0x14
    float y;            // +0x18
    float z;            // +0x1c
    float f020;         // +0x20
    U32   d024;         // +0x24
    U32   d028[9];      // +0x28  (uninitialised in the original)
    U8    b04c;         // +0x4c
    U32   d050;         // +0x50
    U32   d054;         // +0x54
    U32   d058;         // +0x58
    U32   d05c;         // +0x5c
    float f060;         // +0x60
    float f064;         // +0x64
    float f068;         // +0x68
    float f06c;         // +0x6c
    U32   d070;         // +0x70
};
typedef void (__thiscall* VfDest)(void*, DestParam*);
__forceinline void EmitDestParam(cSPGameDataUFO* self)
{
    DestParam dp;
    dp.mpArray = 0;
    dp.d004 = 0;
    dp.d008 = 0;
    dp.x = self->mDestination.x;
    dp.y = self->mDestination.y;
    dp.z = self->mDestination.z;
    dp.f020 = gF_1485720;
    dp.d024 = 0;
    dp.b04c = 0;
    dp.d050 = 0;
    dp.d054 = 0;
    dp.d058 = 0;
    dp.d05c = 1;
    dp.f060 = gF_1470f1c;
    dp.f064 = gF_13ec4b4;
    dp.f068 = gF_146bb6c;
    dp.f06c = 0.0f;
    dp.d070 = 0;
    void* pLoco = (char*)self + 0x34;
    ((VfDest)(*(void**)((char*)self->mpVftbl34 + 0xdc)))(pLoco, &dp);
    if (dp.mpArray != 0 && ((int*)dp.mpArray)[-1] != 0)
        operator_delete(dp.mpArray);
}
// ---- items of slice s00c3bfe0 end

// ---- items of slice s00c3cd60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00c3_cd60 {
    float x, y, z;
    Vector3_s00c3_cd60() {}
    Vector3_s00c3_cd60(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00c3_cd60(const Vector3_s00c3_cd60& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s00c3_cd60 operator*(float f) const { return Vector3_s00c3_cd60(x * f, y * f, z * f); }
    Vector3_s00c3_cd60 operator+(const Vector3_s00c3_cd60& o) const { return Vector3_s00c3_cd60(x + o.x, y + o.y, z + o.z); }
    Vector3_s00c3_cd60 operator-(const Vector3_s00c3_cd60& o) const { return Vector3_s00c3_cd60(x - o.x, y - o.y, z - o.z); }
    Vector3_s00c3_cd60& operator+=(const Vector3_s00c3_cd60& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3_s00c3_cd60& operator-=(const Vector3_s00c3_cd60& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    float Dot(const Vector3_s00c3_cd60& o) const { return x * o.x + y * o.y + z * o.z; }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };
Vector3_s00c3_cd60 Vector3_Normalize(const Vector3_s00c3_cd60& v);                 // 0x436ce0
Matrix3 Quaternion_ToMatrix(const Quaternion& q);            // 0x4a9b40
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Transform {
    int16_t mnFlags;            // +0x00
    int16_t mnTransformCount;   // +0x02
    Vector3_s00c3_cd60 mOffset;            // +0x04
    float   mfScale;            // +0x10
    Matrix3 mRotation;          // +0x14
    Transform();                                // 0x434040
    void SetOffset(const Vector3_s00c3_cd60& v);           // 0x571d40
    void SetScale(float v) { mfScale = v; mnTransformCount++; }
    __forceinline void SetRotation(const Quaternion& q)
    {
        mRotation = Quaternion_ToMatrix(q);
        mnFlags |= 2;
        mnTransformCount++;
    }
};
namespace EA {
namespace Swarm {
class cIVisualEffect_s00c3_cd60 { public:
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
    virtual void Start(int hardStart) = 0;                                  // 0x08
    virtual int  Stop(int) = 0;
    virtual int  IsRunning() = 0;
    virtual void SetRigidTransform(const Transform& t) = 0;
    virtual void SetSourceTransform(const Transform& t) = 0;                // 0x18
    virtual void v1c() = 0; virtual void v20() = 0; virtual void v24() = 0; virtual void v28() = 0;
    virtual void v2c() = 0; virtual void v30() = 0; virtual void v34() = 0; virtual void v38() = 0;
    virtual void v3c() = 0; virtual bool v40() = 0;
    virtual bool SetFloatParams(int param, const float* data, int count) = 0;   // 0x44
    virtual bool SetIntParams(int param, const int* data, int count) = 0;       // 0x48
};
}
}
namespace EA {
namespace Swarm {
struct IEffectsManager {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0; virtual void v0c() = 0;
    virtual void v10() = 0; virtual void v14() = 0; virtual void v18() = 0; virtual void v1c() = 0;
    virtual void v20() = 0; virtual void v24() = 0; virtual void v28() = 0;
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, cIVisualEffect_s00c3_cd60** dst) = 0;   // 0x2c
};
}
}
namespace EA {
template <class T> class AutoRefCount_s00c3_cd60 { public:
    T* mpObject;
    AutoRefCount_s00c3_cd60() : mpObject(0) {}
    explicit AutoRefCount_s00c3_cd60(T* p);        // 0x61df40 (tool instance)
    ~AutoRefCount_s00c3_cd60() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam();                // 0xa16f40
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};
}
namespace EA {
namespace Random {
class RandomLinearCongruential_s00c3_cd60 { public: double RandomDoubleUniform(); };   // 0x9360d0
}
}
namespace SP {
class cEmpire_s00c3_cd60 { public:
    uint32_t pad00[0x58 / 4];
    int      mArchetype;        // +0x58
    const ResourceKey& GetUFOKey();     // 0xc326b0
};
}
namespace SP {
class cGameData_s00c3_cd60 { public:
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
    virtual bool IsDestroyed();                     // 0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual int  GetPoliticalID();                  // 0x4c
    uint32_t pad04[(0x34 - 4) / 4];
};
}
namespace SP {
class cLocomotiveObject_s00c3_cd60 { public:
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
    virtual const Vector3_s00c3_cd60&    GetPosition();        // 0x2c
    virtual const Quaternion& GetOrientation();     // 0x30
    virtual float             GetBoundingRadius();  // 0x34
    uint32_t pad04[(0x4d4 - 4) / 4];
};
}
namespace SP {
struct cSpaceToolData {
    virtual void v00();
    virtual int  AddRef();
    virtual int  Release();
    uint32_t pad04[(0x13c - 4) / 4];
    bool     mbInUse;           // +0x13c
};
}
namespace SP {
class cCombatant_s00c3_cd60 { public:
    virtual ~cCombatant_s00c3_cd60();
    virtual bool v04();
    virtual void v08();
    virtual cGameData_s00c3_cd60* ToGameData();                // 0x0c
    virtual int  v10();
    virtual void v14();
    virtual void TakeHit(float damage, int attackerPoliticalID, int damageType,
                         const Vector3_s00c3_cd60& direction, cCombatant_s00c3_cd60* pAttacker);   // 0x18
    virtual void AddHostileUnit(cCombatant_s00c3_cd60* pAttacker);                      // 0x1c

    bool IsInvulnerable();          // 0xbfc480

    uint32_t pad04[(0x2c - 4) / 4];
    float    mMaxHealthPoints;      // +0x2c
    uint32_t pad30;
    int      mDeathState;           // +0x34
    float    mHealthPoints;         // +0x38
    uint32_t pad3c[(0xc8 - 0x3c) / 4];
};
}
namespace SP {
class cGonzagoTimer_s00c3_cd60 { public: void Stop(); };   // 0xbc3110
}
namespace SP {
struct cMission { uint8_t pad[0x21c]; bool mbIgnoreAwareness; };   // +0x21c
}
namespace SP {
class cSPGameDataUFO_s00c3_cd60 : public cGameData_s00c3_cd60, public cLocomotiveObject_s00c3_cd60, public cCombatant_s00c3_cd60 {
public:
    void TakeHit(float damage, int attackerPoliticalID, int damageType,
                 const Vector3_s00c3_cd60& direction, cCombatant_s00c3_cd60* pAttacker);
    void StartPlayerDeathSequence();    // 0xc3c520
    bool IsOnMission();                 // 0xc372c0

    uint32_t      pad5d0[(0x60c - 0x5d0) / 4];
    Vector3_s00c3_cd60       mOffsetDueToDamage;   // +0x60c
    Vector3_s00c3_cd60       mDamageVelocity;      // +0x618
    bool          mbRotateTowardsDestination;   // +0x624
    uint32_t      pad628[(0x648 - 0x628) / 4];
    cGonzagoTimer_s00c3_cd60 mHoverTimer;          // +0x648
    uint32_t      pad64c[(0x714 - 0x64c) / 4];
    int           mUFOType;             // +0x714
    Vector3_s00c3_cd60       mNextPosition;        // +0x718
    uint32_t      pad724[(0x74c - 0x724) / 4];
    bool          mbAtDestination;      // +0x74c
    Vector3_s00c3_cd60       mDestination;         // +0x750
    uint32_t      pad75c[(0x76c - 0x75c) / 4];
    int           mCombatState;         // +0x76c
    uint32_t      pad770[(0x780 - 0x770) / 4];
    int           mModelKeyInstance;    // +0x780 (mDesiredModelKey)
    int           mModelKeyType;        // +0x784
    int           mModelKeyGroup;       // +0x788
    uint32_t      pad78c[(0x800 - 0x78c) / 4];
    int           mOwnerMission;        // +0x800
};
}
namespace SP {
struct cUFOSimulator {
    bool IsPlayerDying();                                   // 0xffc090
    int  ffc320();
    int  ffc2d0();
    void ffd710(cSpaceToolData* tool, cCombatant_s00c3_cd60* attacker);
    void RemovePoliticalID(int politicalID, int);           // 0x1001700
};
}
namespace SP {
struct cPlayerInventory { cSpaceToolData* GetActiveTool(); };          // 0xff3f00
}
namespace SP {
class cSPSimulatorSpaceGame { public:
    cPlayerInventory* GetPlayerInventory();                 // 0xa1ad60
    void f1005180(int);
};
}
namespace SP {
struct cSpaceCombatTuning {
    float GetDamageMultiplier();                            // 0x102a5e0
    float GetLootDropChance(int ufoType);                   // 0x102a1d0
};
}
namespace SP {
class cStarManager_s00c3_cd60 { public: cEmpire_s00c3_cd60* GetEmpireByID(int id); };    // 0xba9370
}
namespace SP {
class cRelationshipManager_s00c3_cd60 { public:
    float RecordEvent(int politicalID1, int politicalID2, uint32_t eventType, float scale);   // 0xd06240
};
}
namespace SP {
class cSPUIEventLog { public:
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0xdd8640
};
}
namespace SP {
class cSimulatorUniverse { public:
    void AdjustAwareness(int politicalID, int amount);      // 0x1014a80
    void OnPlayerDeath(int attackerPoliticalID);            // 0x100e6e0
    static cSimulatorUniverse* sInstance;                   // 0x16dc798
};
}
namespace SP {
struct cAchievementsController {
    void Trigger(uint32_t id, int a, int b);                // 0x676ed0
    void AutoTest(uint32_t id, int a);                      // 0x676e90
};
}
namespace SP {
class cGameViewManager { public:
    bool a98020();
    int  GetAccessFlags();                                  // 0xff0420
};
}
namespace SP {
class cPlanet_s00c3_cd60 { public:
    bool HasFlag(uint32_t id);                              // 0xc772c0
    void SetFlag(uint32_t id);                              // 0xc77bf0
};
}
namespace SP {
class cTerrainEditor_s00c3_cd60 { public: cPlanet_s00c3_cd60* GetCurrentTerrainSphere(); };   // 0xf67d90
}
namespace SP {
struct cMissionManager { bool IsRunning(); };               // 0xfeba90
}
namespace SP {
struct cTutorial { void Trigger(uint32_t id); };            // 0x106dcd0
}
namespace SP {
class cSpaceTokenTranslator { public: uint32_t pad[0x30 / 4]; cGameData_s00c3_cd60* mpDestroyedUFO; };   // +0x30
}
namespace SP {
struct cMessageData {
    cMessageData(cLocomotiveObject_s00c3_cd60* obj, int);              // 0xad7a30
    ~cMessageData();                                        // 0xad7ad0
    uint32_t pad[8];
};
}
namespace SP {
struct cMessageRouter { void Post(uint32_t id, const cMessageData& data); };   // 0xae09b0
}
namespace SP {
void* GetCurrentGameMode();                                 // 0xb5b800
}
namespace SP {
bool  IsGamePaused();                                       // 0x1041d10
}
namespace SP {
int   GetUniverseContext();                                 // 0x1021080
}
namespace SP {
int   GetPlayerEmpireID();                                  // 0x1021090
}
namespace SP {
cEmpire_s00c3_cd60* GetPlayerEmpire();                                 // 0x1021300
}
namespace SP {
cUFOSimulator* GetUFOSimulator_s00c3_cd60();                           // 0xffbe50
}
namespace SP {
cSPGameDataUFO_s00c3_cd60* CombatantToUFO(cCombatant_s00c3_cd60* c);              // 0xae3370
}
namespace SP {
void* CombatantToBuilding(cCombatant_s00c3_cd60* c);                   // 0xbcd430
}
namespace SP {
cSpaceCombatTuning* GetSpaceCombatTuning();                 // 0x1029940
}
namespace SP {
cStarManager_s00c3_cd60* StarManager();                                // 0xb3d2a0
}
namespace SP {
cRelationshipManager_s00c3_cd60* RelationshipManager();                // 0xb3d2c0
}
namespace SP {
cSPUIEventLog* EventLog();                                  // 0xb3d3e0
}
namespace SP {
cTerrainEditor_s00c3_cd60* NounManager_s00c3_cd60();                              // 0xb3d300
}
namespace SP {
cMessageRouter* MessageRouter();                            // 0xb3d4d0
}
namespace SP {
cSPSimulatorSpaceGame* SpaceGameGet_s00c3_cd60();                      // 0x1002bd0
}
namespace SP {
cAchievementsController* AchievementsController();         // 0x675250
}
namespace SP {
cGameViewManager* GameViewManager();                        // 0x1015df0
}
namespace SP {
EA::Swarm::IEffectsManager* EffectsManager();               // 0x67ddd0
}
namespace SP {
cMissionManager* GetMissionManager_s00c3_cd60();                       // 0xfeb9f0
}
namespace SP {
cTutorial* TutorialManager();                               // 0x10666a0
}
namespace SP {
cMission* GetMissionByID(int id);                           // 0xb67700
}
namespace SP {
bool  ToolCanTarget(cSpaceToolData* tool, cGameData_s00c3_cd60* target);   // 0x102af80
}
namespace SP {
void  DropLoot(Vector3_s00c3_cd60 position, cSPGameDataUFO_s00c3_cd60* ufo);      // 0x102ba30
}
namespace SP {
void  OnUFODestroyed(cSPGameDataUFO_s00c3_cd60* ufo, int);             // 0x102c340
}
namespace SP {
void  PostUFOEvent(uint32_t id, cEmpire_s00c3_cd60* empire, const ResourceKey& ufoKey, ResourceKey* a,
                   int b, int c, ResourceKey* d, ResourceKey* e);   // 0xe39ab0
}
namespace SP {
void  TriggerTutorialEvent(const char* name, uint32_t id, int);    // 0x1041c50
}
namespace SP {
void* Audio_GetState();                                     // 0x435e90
}
namespace SP {
void  Audio_PlaySound(uint32_t id, void* state);            // 0x435ed0
}
namespace SP {
extern char gGameModeSpace;                                 // 0x1654c10
}
namespace SP {
extern char gGameModeSpaceAlt;                              // 0x1654c05
}
namespace SP {
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;       // 0x16e0d08
}
namespace SP {
struct cUFOTuning { uint32_t pad[5]; float mImpulseScale; float mImpulseScale2;
                           uint32_t pad1c[(0x178 - 0x1c) / 4]; float mImpulseBase; };
}
namespace SP {
extern cUFOTuning* gpUFOTuning;   // 0x168df68
}
namespace SP {
extern EA::Random::RandomLinearCongruential_s00c3_cd60 sMathRandom;   // 0x1601760
}
namespace SP {
static __forceinline void PlayEmpireHitSound(cEmpire_s00c3_cd60* empire)
{
    uint32_t id = 0;
    switch (empire->mArchetype) {
    case 0: id = 0x681fca05; break;
    case 1: id = 0xbd17d8bc; break;
    case 2: id = 0x69f8ac9d; break;
    case 3: id = 0x2db4202e; break;
    case 4: id = 0x7e0f4c24; break;
    case 5: id = 0x4669212d; break;
    case 6: id = 0x79d83254; break;
    case 7: id = 0xfef69e24; break;
    case 8: id = 0x9df6192d; break;
    default:
        if (empire == GetPlayerEmpire())
            id = 0xdc553e7f;
        break;
    }
    Audio_PlaySound(id, Audio_GetState());
}
}
namespace SP {
static __forceinline void PlayEmpireDestroyedSound(cEmpire_s00c3_cd60* empire)
{
    uint32_t id = 0;
    switch (empire->mArchetype) {
    case 0: id = 0x50d22af7; break;
    case 1: id = 0xe1ab9994; break;
    case 2: id = 0x62c31dff; break;
    case 3: id = 0x9b657912; break;
    case 4: id = 0x85c96a4c; break;
    case 5: id = 0xaf8f406f; break;
    case 6: id = 0xe2f6ca9c; break;
    case 7: id = 0xcadac04c; break;
    case 8: id = 0x2434a86f; break;
    default:
        if (empire == GetPlayerEmpire())
            id = 0x1fe441d5;
        break;
    }
    Audio_PlaySound(id, Audio_GetState());
}
}
// ---- items of slice s00c3cd60 end

// ---- items of slice s00c3daa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl GetUniverseContext();                            // 0x01021080 SP::cSPLivingUniverse::GetUniverseContext
void  __stdcall FUN_00c3c810(void*, void*);                    // 0x00c3c810
void* __cdecl FUN_00b20c60(void*, int);                        // 0x00b20c60 cGameNounManager::CreateNoun
void* __cdecl GetSpaceCombatTuning();                          // 0x01029940
int   __cdecl FUN_01021240();                                  // 0x01021240 cSPMission::IsArchived
float* __cdecl FUN_005c65e0(void*);                            // 0x005c65e0 cCivData::GetCities
int   __cdecl FUN_0102a360(void*, void*, void*, void*);        // 0x0102a360 cSPSpaceCombatTuning::GetWeaponLevel
int   __cdecl FUN_00c317a0(void*);                             // 0x00c317a0 cEmpire::GetWeaponryLevel
double __cdecl FUN_0059da80(float);                            // 0x0059da80 RandomRange
float __cdecl FUN_0102a630(void*, float, int);                 // 0x0102a630 cSPSpaceCombatTuning::GetUFOHealth
void  __cdecl FUN_00c3a220(int, float, void*);                 // 0x00c3a220 enableWeapon
void* __cdecl FUN_00c463d0(void*);                             // 0x00c463d0
void  __cdecl FUN_00b3d390(void*, void*);                      // 0x00b3d390 eastl vector erase
struct Fn455d60 { void __thiscall append(const char*, const char*); };  // 0x00455d60 eastl string::append
void* __cdecl FUN_005f9450(void*, const char*, ...);           // 0x005f9450 append_sprintf
void  __cdecl FUN_00563de0(void*, void*);                      // 0x00563de0
void* __cdecl FUN_00ffbe50();                                  // 0x00ffbe50 GetUFOSimulator
struct FnFFd8e0 { float __thiscall f(); };                     // 0x00ffd8e0 CalculateMaxHealth
struct FnFFda80 { float __thiscall f(); };                     // 0x00ffda80 CalculateMaxEnergy
void* __cdecl FUN_0067dcc0();                                  // 0x0067dcc0 MessageServer
struct FnC326b0 { void* __thiscall f(int); };                 // 0x00c326b0 cEmpire::GetUFOKey
struct FnC37180 { void* __thiscall f(void*); };                // 0x00c37180 SetDesiredModel
struct FnC43fe0 { void* __thiscall f(void*); };                // 0x00c43fe0
struct Fn3be70 { void __thiscall f(void*); };                  // 0x00c3be70
struct Fn37e60 { void __thiscall f(); };                       // 0x00c37e60 PopToDestination
struct Fn3bfe0 { void __thiscall f(void*); };                  // 0x00c3bfe0 SetDestination
struct Fn3f160 { void __thiscall f(float); };                  // 0x00c3f160
struct Fn3f1b0 { void __thiscall f(float, float); };           // 0x00c3f1b0
struct Fn3f2d0 { void __thiscall f(void*); };                  // 0x00c3f2d0
struct Fn385d0 { void __thiscall f(); };                       // 0x00c385d0
struct Fn3a2b0 { void __thiscall f(int); };                    // 0x00c3a2b0 OnContextChange
struct Fn3dba0 { void __thiscall f(int, float); };             // 0x00c3dba0 InitNPC
struct Fn3dae0 { void __thiscall f(void*); };                  // 0x00c3dae0
struct UFO {
    char  pad0[0x34];
    void* mpSpatial;          // +0x34   cSpatialObject
    char  pad1[0x4f8 - 0x38];
    char  padMove[0x20];      // +0x4f8  mMovementTimer
    char  padHover[0x20];     // +0x518  mHoverTimer
    char  padColl[0x20];      // +0x538  mCollisionTimer
    char  pad2[0x68c - 0x558];
    uint8_t mFlag690;         // +0x690
    char  pad3[0x714 - 0x691];
    int   mType714;           // +0x714
    char  pad4[0x750 - 0x718];
    float pos750;             // +0x750
    char  pad5[0x768 - 0x754];
    float field768;           // +0x768
    char  pad6[0x7d8 - 0x76c];
    void* mpNoun7d8;          // +0x7d8  noun object
    char  pad7[0x7e0 - 0x7dc];
    char  str7e0[0x8];        // +0x7e0  eastl string

    void func3daa0(float val);     // 0x00c3daa0
    void func3dac0(void* p);       // 0x00c3dac0
    void func3dae0(float* p);      // 0x00c3dae0
    void func3db50(void* a, void* b); // 0x00c3db50
    void func3dba0(int a, float b);   // 0x00c3dba0
    void func3e0b0(float a, void* b); // 0x00c3e0b0
    void func3e010(void* s);       // 0x00c3e010
};
struct Str { void __thiscall assign(void*, void*); };
extern float gF_13f7670;   // 0x013f7670  35.0f
extern float gF_13eecd8;   // 0x013eecd8  RandomRange bound
extern float gF_1473c70;   // 0x01473c70  RandomRange bound
extern float gF_142eae0;   // 0x0142eae0  float constant
extern void* g_168df68;    // 0x0168df68
// ---- items of slice s00c3daa0 end

// ---- items of slice s00c3a180 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObject_s00c3_a180 {
    virtual void q00();                    // +0x00
    virtual int  AddRef();                 // +0x04
    virtual int  Release();                // +0x08
};
void* __cdecl GetSpaceCombatTuning_s00c3_a180();       // 0x01029940
int   __cdecl GetPropertyAsFloatArray(void* pList, int id, int* pCount, float** pArray); // 0x006a08b0
void* __cdecl EraseToolEntry(void* p, void* q);   // 0x00b3d390
char  __cdecl UTFWin_Window_Initialize();          // 0x00b1fbf0 (bool)
void  __cdecl FUN_006a0ae0(void* pVector, int id, int* pCount, int* pBase); // 0x006a0ae0 (vector reserve)
struct Fn0104e340 {
    char __thiscall f(unsigned int toolId);    // 0x0104e340  CreateToolFromToolID (ret 4)
};
static const int kPropGalaxyWarpTime = 0x5c8077c;
struct IHandler_s00c3_a180 {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
};
struct cUFOKinestheticsTuning_s00c3_a180 : public IHandler_s00c3_a180 {
    void* mpPropList;                        // +0x04
    U8 mf008[0x1e4 - 0x08];                  // +0x08 .. +0x1e3 (opaque tuning scalars)

    void  ReadProps();                       // 0x00c38d00
    float GetGalaxyWarpTime(int warpMode, float unused, float t);  // 0x00c3a1b0 (cUFOKinestheticsTuning::GetGalaxyWarpTime)
    char  HandleMessage(int messageID, int arg);
};
struct cSPGameDataUFO_s00c3_a180 {
    void* mpVftbl0;                          // +0x000
    U8 pad004[48];                           // +0x004
    void* mpVftbl34;                         // +0x034
    U8 pad038[0x288 - 0x38];                 // +0x038
    IRefObject_s00c3_a180* mp288;                       // +0x288
    U8 pad28c[0x508 - 0x28c];                // +0x28c
    void* mpVftbl508;                        // +0x508
    U8 pad50c[0x5f4 - 0x50c];                // +0x50c .. +0x5f3
    float mDestZ;                            // +0x5f4 orthogonal component (z)
    float mDestX;                            // +0x5f8 orthogonal component (x)
    float mDestY;                            // +0x5fc orthogonal component (y)
    U8 pad600[0x648 - 0x600];                // +0x600 .. +0x647
    U8 mTimer648[0x20];                      // +0x648 cSPTimer
    U8 pad668[0x68c - 0x668];                // +0x668
    IRefObject_s00c3_a180* mp68c;                       // +0x68c
    U8 pad690[0x710 - 0x690];                // +0x690
    IRefObject_s00c3_a180* mp710;                       // +0x710
    int   mUFOType;                          // +0x714
    float mCurX;                             // +0x718
    float mCurY;                             // +0x71c
    float mCurZ;                             // +0x720
    U8 pad724[0x74c - 0x724];                // +0x724 .. +0x74b
    U8    mb74c;                             // +0x74c
    U8    pad74d[3];                         // +0x74d
    Vector3 mDestination;                    // +0x750
    IRefObject_s00c3_a180* mp75c;                       // +0x75c
    IRefObject_s00c3_a180* mp760;                       // +0x760
    U8 pad764[0x790 - 0x764];                // +0x764
    IRefObject_s00c3_a180* mp790;                       // +0x790
    IRefObject_s00c3_a180* mp794;                       // +0x794
    IRefObject_s00c3_a180* mp798;                       // +0x798
    IRefObject_s00c3_a180* mp79c;                       // +0x79c
    IRefObject_s00c3_a180* mp7a0;                       // +0x7a0
    IRefObject_s00c3_a180* mp7a4;                       // +0x7a4
    IRefObject_s00c3_a180* mp7a8;                       // +0x7a8
    IRefObject_s00c3_a180* mp7ac;                       // +0x7ac
    void* mp7b0;                             // +0x7b0 (cCivData*)
    U8 pad7b4[0x7bc - 0x7b4];                // +0x7b4
    int   mInt7bc;                           // +0x7bc
    U8 pad7c0[0x7d8 - 0x7c0];                // +0x7c0
    IRefObject_s00c3_a180* mp7d8;                       // +0x7d8
    U8 pad7dc[0x7f0 - 0x7dc];                // +0x7dc
    IRefObject_s00c3_a180* mp7f0;                       // +0x7f0
    U8 pad7f4[0x800 - 0x7f4];                // +0x7f4
    void* mp800;                             // +0x800
    void* mp804;                             // +0x804
    void* mp808;                             // +0x808
    void* mp80c;                             // +0x80c
    int   md810;                             // +0x810
    int   md814;                             // +0x814

    int   HandleMessage(int messageID, int arg);
    void  OnContextChange(int context);  // 0x00c3a2b0 (cSPGameDataUFO::OnContextChange)
    void  ShutdownInternal();
    void  SetNPCTool(void* pTool);
    void  SetNPCToolIndexed(void* pTool, int index);
    char  Initialize();
    char  vtableSlot40Wrapper(int arg);
    void  SetFacing(const Vector3* pFacing);
    float GetContextScale();
};
struct FnB183F0 { char __thiscall f(int arg); };   // 0x00b183f0 cGameData::vtableSlot40 (ret 4)
struct FnC385D0 { void __thiscall f(); };           // 0x00c385d0
static inline void vcall_release8(IRefObject_s00c3_a180* p)          // vtable +0x8
{
    (*(void (__thiscall**)(void*))((U8*)*(void**)p + 0x8))(p);
}
// ---- items of slice s00c3a180 end

// ---- items of slice s00c3ae70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_1471064;   // 0.5
#pragma intrinsic(sqrt, fabs)
struct Vector3_s00c3_ae70 {
    float x, y, z;
    Vector3_s00c3_ae70() {}
    Vector3_s00c3_ae70(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00c3_ae70(const Vector3_s00c3_ae70& o) : x(o.x), y(o.y), z(o.z) {}
};
struct IRefObject_s00c3_ae70 {
    virtual void q00();                    // +0x00
    virtual int  AddRef();                 // +0x04
    virtual int  Release();                // +0x08
};
struct IReleased {
    virtual void q00();                    // +0x00
    virtual int  Release();                // +0x04
};
void* __cdecl PropertyManager();            // 0x0067de30
void* __cdecl SpaceGameGet_s00c3_ae70();               // 0x01002bd0
struct FnB18E40 { bool  __thiscall f(); };           // 0x00b18e40 (bool in AL)
struct FnC382E0 { void  __thiscall f(); };           // 0x00c382e0
struct Fn1005C60{ float __thiscall f(int); };        // 0x01005c60 GetWarpScale (this=SpaceGame)
struct FnB18420 { int   __thiscall f(void*); };      // 0x00b18420 cGameData::WriteAsText (ret 4)
struct FnC0AF90 { int   __thiscall f(void*); };      // 0x00c0af90 cLocomotiveObject::GetFieldValues
int __cdecl FUN_6a08b0(void* pList, int id, int* pCount, float** pArray);  // 0x006a08b0
struct RefHolder_s00c3_ae70 {
    IRefObject_s00c3_ae70* mpObject;                                       // +0
    RefHolder_s00c3_ae70() : mpObject(0) {}
    RefHolder_s00c3_ae70& operator=(IRefObject_s00c3_ae70* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            IRefObject_s00c3_ae70* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
struct IHandler_s00c3_ae70 {
    virtual void v000();
    virtual void v004();
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02c();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03c();
    virtual void v040();
    virtual void v044();
    virtual void v048();
};
struct cUFOKinestheticsTuning_s00c3_ae70 : public IHandler_s00c3_ae70 {
    void* mpPropList;                        // +0x04
    float mHitTerrainDamage;                 // +0x08
    float mMinAltitude;                      // +0x0C
    float mMaxAltitude;                      // +0x10
    float mDamageToDestScale;                // +0x14
    float mDamageToVelocityScale;            // +0x18
    float mHitSphereRadius;                  // +0x1C
    float mHitSphereActiveDistance;          // +0x20
    float mMinExtent;                        // +0x24
    float mBomberScale;                      // +0x28
    float mFighterScale;                     // +0x2C
    float mUberTurretScale;                  // +0x30
    float mAllyScale;                        // +0x34
    float mPlumpDistance;                    // +0x38
    float mPlumpScale;                       // +0x3C
    float mPlumpTransitionScale;             // +0x40
    float mNPCPlumpScale;                    // +0x44
    float mBasePlanetScale;                  // +0x48
    float mVelocityFactor;                   // +0x4C
    float mVelocityFactorNPC;                // +0x50
    float mFighterVelocityFactor;            // +0x54
    float mUberTurretVelocityFactor;         // +0x58
    float mAllyVelocityFactor;               // +0x5C
    float mKeyboardMovementSpeedZoomedOut;   // +0x60
    float mKeyboardMovementSpeedZoomedIn;    // +0x64
    float mKeyboardAccelerationZoomedOut;    // +0x68
    float mKeyboardAccelerationZoomedIn;     // +0x6C
    float mBomberVelocityFactor;             // +0x70
    float mVelocityFactorZoomedOut;          // +0x74
    float mMouseMovementSpeedZoomedOut;      // +0x78
    float mMouseMovementSpeedZoomedIn;       // +0x7C
    float mMouseRotationSpeedZoomedOut;      // +0x80
    float mMouseRotationSpeedZoomedIn;       // +0x84
    float mLeavePlanetTimePad;               // +0x88
    float mMaxRotation;                      // +0x8C
    float mTargetFallOffRadius;              // +0x90
    float mBrakeFactor;                      // +0x94
    float mBrakeOvershootFactor;             // +0x98
    float mAccelerationFactor;               // +0x9C
    float mAccelerationFactorNPC;            // +0xA0
    float mVerticalAcclerationDown;          // +0xA4
    float mVerticalAcclerationUp;            // +0xA8
    float mCollisionElasticity;              // +0xAC
    float mCollisionRestitution;             // +0xB0
    float mRotationPercentageRate;           // +0xB4
    float mNoseTiltFactor;                   // +0xB8
    float mNoseTiltRate;                     // +0xBC
    float mMaxNoseTilt;                      // +0xC0
    float mVerticalTiltFactor;               // +0xC4
    float mMaxVerticalTilt;                  // +0xC8
    float mBankTiltFactor;                   // +0xCC
    float mBankTiltRate;                     // +0xD0
    float mMaxBankTilt;                      // +0xD4
    float mEscapeSequenceSpinRate;           // +0xD8
    float mEscapeSequenceVelocity;           // +0xDC
    float mTrailEffectAlwaysOn;              // +0xE0
    float mEffectMaxSpeedPlanet;             // +0xE4
    float mEffectMaxSpeedSolar;              // +0xE8
    float mEffectMaxSpeedGalaxy;             // +0xEC
    float mTrailEffectMinSize;               // +0xF0
    float mMaxAltitudeDestinationDelta;      // +0xF4
    float mSolarSpeed;                       // +0xF8
    float mSolarAcceleration;                // +0xFC
    float mGalaxySpeed;                      // +0x100
    float mGalaxyAcceleration;               // +0x104
    float mSolarMinPlump;                    // +0x108
    float mSolarMaxPlump;                    // +0x10C
    float mGalaxyMinPlump;                   // +0x110
    float mGalaxyMaxPlump;                   // +0x114
    float mGalaxyMinPlumpDistance;           // +0x118
    float mGalaxyMaxPlumpDistance;           // +0x11C
    float mBaseUFODamagePush;                // +0x120
    float mMaxUFODamagePush;                 // +0x124
    float mUFODamageVelocityDecayRate;       // +0x128
    float mAltMaxAltitude;                   // +0x12C
    float mAltPlumpDistance;                 // +0x130
    float mAltVelocityFactorZoomedOut;       // +0x134
    float mExtra138;                         // +0x138
    float mExtra13c;                         // +0x13C
    float mExtra140;                         // +0x140
    float mExtra144;                         // +0x144
    float mExtra148;                         // +0x148
    float mExtra14c;                         // +0x14C
    float mExtra150;                         // +0x150
    float m2HitTerrainDamage;                // +0x154
    float m2MinAltitude;                     // +0x158
    float m2MaxAltitude;                     // +0x15C
    float m2DamageToDestScale;               // +0x160
    float m2DamageToVelocityScale;           // +0x164
    float m2HitSphereRadius;                 // +0x168
    float m2HitSphereActiveDistance;         // +0x16C
    float m2MinExtent;                       // +0x170
    float m2BomberScale;                     // +0x174
    float m2FighterScale;                    // +0x178
    float m2UberTurretScale;                 // +0x17C
    float m2AllyScale;                       // +0x180
    float m2PlumpDistance;                   // +0x184
    float m2PlumpScale;                      // +0x188
    float m2PlumpTransitionScale;            // +0x18C
    float m2NPCPlumpScale;                   // +0x190
    float m2BasePlanetScale;                 // +0x194
    float m2VelocityFactor;                  // +0x198
    float m2VelocityFactorNPC;               // +0x19C
    float m2FighterVelocityFactor;           // +0x1A0
    float m2UberTurretVelocityFactor;        // +0x1A4
    U32   md1a8;                             // +0x1A8 (MessageServer*)
    U32   md1ac;                             // +0x1AC (this)
    U32   md1b0;                             // +0x1B0 (= 0x146bb64)
    U32   md1b4;                             // +0x1B4 (= 1)
    U32   md1b8;                             // +0x1B8 (= 0)

    void  ReadProps();                       // 0x00c38d00
    void  Init();
    float GetGalaxyWarpMultiplier(int index, int warpMode);  // 0x00c3b880 (cUFOKinestheticsTuning::GetGalaxyWarpMultiplier)
};
struct cSPGameDataUFO_s00c3_ae70 {
    // --- flat retail layout: vtable pointers of the four subobjects are at
    // +0x000 (cGameData), +0x034 (cLocomotiveObject), +0x108, +0x508 (cCombatant),
    // +0x5d0 (cInteractionTarget), +0x5e8.
    // --- methods defined in this slice
    float GetScale();
    void  UpdateScale();
    void  UpdateDestinationFromTarget();
    bool  OnMessage(U32 messageID, int arg);
    void  SetNPCTool(void* pTool);
    int   ClearAttackBehaviorTarget(IRefObject_s00c3_ae70* pTarget);   // this is the +0x7a8 target 0x00c3b630
    int   ClearDefenseBehaviorTarget(IRefObject_s00c3_ae70* pTarget);  // this is the +0x7ac target
    int   GetFieldValues(void* pOut);  // 0x00c3bc80 (cSPGameDataUFO::GetFieldValues)
    float GetScaleRadius();
    void  SetHeading(const Vector3_s00c3_ae70* pDir);
    void  Destroy();

    // --- helpers in the same module
    float GetScaleFactor();       // 0x00c3ad40

    // --- fields (flat retail layout; offsets are exact)
    void* mpVftbl0;                        // +0x000
    U8 pad004[48];                         // +0x004
    void* mpVftbl34;                       // +0x034
    U8 pad038[28];                         // +0x038
    float mf054;                           // +0x054
    float mf058;                           // +0x058
    float mf05c;                           // +0x05c
    float mf060;                           // +0x060
    float mf064;                           // +0x064
    float mf068;                           // +0x068
    float mf06c;                           // +0x06c
    float mf070;                           // +0x070
    float mf074;                           // +0x074
    float mf078;                           // +0x078
    float mf07c;                           // +0x07c
    float mf080;                           // +0x080
    U32 mFlags84;                          // +0x084
    U8 pad088[8];                          // +0x088
    float mf090;                           // +0x090
    float mf094;                           // +0x094
    U8 pad098[112];                        // +0x098
    void* mpVftbl108;                      // +0x108
    U8 pad10c[280];                        // +0x10c
    int mInt224;                           // +0x224
    int mInt228;                           // +0x228
    U8 pad22c[732];                        // +0x22c
    void* mpVftbl508;                      // +0x508
    U8 pad50c[196];                        // +0x50c
    void* mpVftbl5d0;                      // +0x5d0
    U8 pad5d4[20];                         // +0x5d4
    void* mpVftbl5e8;                      // +0x5e8
    U8 pad5ec[160];                        // +0x5ec
    void* mp68c;                           // +0x68c
    U8 pad690[56];                         // +0x690
    void* mp6c8;                           // +0x6c8
    U32 md6cc;                             // +0x6cc
    U32 mTimer6d0[8];                      // +0x6d0
    U32 mTimer6f0[8];                      // +0x6f0
    U32 md710;                             // +0x710
    int mUFOType;                          // +0x714
    float mf718;                           // +0x718
    float mf71c;                           // +0x71c
    float mf720;                           // +0x720
    U8 pad724[40];                         // +0x724
    U8 mb74c;                              // +0x74c
    U8 pad74d[3];                          // +0x74d
    Vector3_s00c3_ae70 mDestination;                  // +0x750
    RefHolder_s00c3_ae70 mRef75C;                     // +0x75c
    RefHolder_s00c3_ae70 mRef760;                     // +0x760
    int mInt764;                           // +0x764
    float mf768;                           // +0x768
    int md76c;                             // +0x76c
    U32 md770[0x18 / 4];                   // +0x770
    U32 md788;                             // +0x788
    U32 md78c;                             // +0x78c
    RefHolder_s00c3_ae70 mRef790;                     // +0x790
    RefHolder_s00c3_ae70 mRef794;                     // +0x794
    RefHolder_s00c3_ae70 mRef798;                     // +0x798
    RefHolder_s00c3_ae70 mRef79c;                     // +0x79c
    RefHolder_s00c3_ae70 mRef7a0;                     // +0x7a0
    RefHolder_s00c3_ae70 mRef7a4;                     // +0x7a4
    RefHolder_s00c3_ae70 mRef7a8;                     // +0x7a8
    RefHolder_s00c3_ae70 mRef7ac;                     // +0x7ac
    void* mp7b0;                           // +0x7b0
    U8 pad7b4[4];                          // +0x7b4
    U32 mTimer7b8[8];                      // +0x7b8
    RefHolder_s00c3_ae70 mRef7d8;                     // +0x7d8
    U32 mFlags7dc;                         // +0x7dc
    void* mp7e0;                           // +0x7e0
    void* mp7e4;                           // +0x7e4
    void* mp7e8;                           // +0x7e8
    U8 pad7ec[4];                          // +0x7ec
    RefHolder_s00c3_ae70 mRef7f0;                     // +0x7f0
    U8 pad7f4[12];                         // +0x7f4
    void* mp800;                           // +0x800
    void* mp804;                           // +0x804
    void* mp808;                           // +0x808
    void* mp80c;                           // +0x80c
    int md810;                             // +0x810
    int md814;                             // +0x814
};
struct cVarListSerializer_s00c3_ae70 {
    U32 md[0xa14 / 4];
    void ctor(void* pA, void* pB, int pC);   // 0x00692f90
    int  GetFields(void* pOut);              // 0x00695960
};
// ---- items of slice s00c3ae70 end

// ---- items of slice s0105b960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern float g_radius10;                         // 0x01473c70 = 10.0f
extern float g_scale12;                          // 0x013f6b68 = 12.0f
extern float g_scale6;                           // 0x0147b9f0 = 6.0f
extern float g_scale15;                          // 0x014007f4 = 15.0f
extern float g_scale2p4;                         // 0x0149bfc4 = 2.4f
extern float g_one;                              // 0x01485720 = 1.0f
extern float g_ratio0p2;                         // 0x015b8ddc = 0.2f
extern float g_ratio0p5;                         // 0x015b8dd8 = 0.5f
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
struct ResourceKey_s0105_b960 {
    uint32_t mInstanceID;                        // +0x00
    uint32_t mTypeID;                            // +0x04
    uint32_t mGroupID;                           // +0x08
};
extern Vector3_s0105_b960 g_upAxis;                         // 0x015b8db4 = (0, 0, 1)
class cGameObject;
class cSpaceToolData_s0105_b960;
class cSpaceShip;
class cLocatable;
class cPlanetModel;
class cApp;
class cConfigNode;
void* GetTriggerMgr();                                               // 0x00b3d4d0
cPlanetModel* PlanetModel_s0105_b960();                                         // 0x00b3d350 (getter)
cApp* App();                                                          // 0x0067dd10
int  FUN_00c70880(cSpaceToolData_s0105_b960* pTool);                             // 0x00c70880
bool FUN_00c71540(cSpaceToolData_s0105_b960* pTool);                             // 0x00c71540
void* FUN_00c37360();                                                 // 0x00c37360 (sim tuning block)
float FUN_01017030(int which);                                        // 0x01017030
float FUN_01017070(int which);                                        // 0x01017070
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
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
};
class cGameObject {
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
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
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
    virtual const ResourceKey_s0105_b960& GetToolID();                      // +0x18
    virtual void* CreateImpact();                                 // +0x1c (no stack args)
    uint32_t pad20[(0x30 - 0x04) / 4];                            // +0x04
    void* mpToolProperties;                                      // +0x30 (property list)
    uint32_t pad34[(0x114 - 0x34) / 4];                           // +0x34
    cLocatable* mpToolOwner;                                     // +0x114 (owner transform)
    uint32_t pad118[(0x124 - 0x118) / 4];                         // +0x118
    cGameObject* mpOwnerObject;                                  // +0x124
    uint32_t pad128[(0x170 - 0x128) / 4];                         // +0x128
    uint32_t mLastErrorID;                                       // +0x170
    float FUN_0104bdb0();                                        // 0x0104bdb0 (first scalar, ecx = this)
};
class cPlanetModel {
public:
    bool FUN_00b7e3e0(const Vector3_s0105_b960& position);                   // 0x00b7e3e0
    const Vector3_s0105_b960* FUN_00b81630(Vector3_s0105_b960* out, const Vector3_s0105_b960& position);  // 0x00b81630
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3_s0105_b960& position);  // 0x00b7f190
};
class cSpaceShip {
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
    uint32_t pad04[(0x34 - 0x04) / 4];                            // +0x04
    cLocatable mLocation;                                         // +0x34 (vptr-only view of the sub-object)
    uint32_t pad48[(0x750 - 0x38) / 4];                           // +0x38
    Vector3_s0105_b960 mDirection;                                           // +0x750
    float mPad75c;                                                // +0x75c
    float mPad760[2];                                             // +0x760
    float mRadius;                                                // +0x768
    float GetReach();                                             // 0x00c37120
};
class cConfigNode {
public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cConfigNode* GetTag(uint32_t typeID);                   // +0x0c
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
    virtual cConfigNode* GetSubNode();                              // +0x38
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual float GetFloat();                                       // +0x5c
};
class cApp {
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
    virtual cConfigNode* GetModeHolder();                            // +0x50
};
static float TagFloat(cConfigNode* node, uint32_t tagID, const float& dflt)
{
    if (node) {
        cConfigNode* tag = node->GetTag(tagID);
        if (tag)
            return tag->GetFloat();
    }
    return dflt;
}
// ---- items of slice s0105b960 end

// ---- items of slice s0105c8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kCoupling;                           // 0x015b8df4 = 5.0
extern const float kMinSpeed;                           // 0x015b8df0 = 0.001
extern const float kHeadingDot;                         // 0x015b8dec = -0.8
extern const float kRetargetDist;                       // 0x015b8de8 = 5.0
extern const float kDirDot;                             // 0x015b8de4 = -0.8
extern const float kLead;                               // 0x015b8de0 = 2.0
extern void* g_vtCVS[];                 // 0x013ec458
extern void* g_vtD180Class[];           // 0x0149bfc8
extern void* g_vtD180Base[];            // 0x01475114
extern void* g_vtD1D0Class[];           // 0x0149bfd8
extern uint32_t g_warpAxisKey;                          // 0x016e2160
extern const float kMsToSeconds;                        // 0x013f9428 (0.001f)
extern const float kMinWarpExtent;                      // 0x0149bfc0 (1.5258789e-05f)
extern const float kWarpFacingThreshold;                // 0x01486cd8 (0.999f)
#define VPAD(n) virtual void vpad##n()
struct Vector3_s0105_c8d0 {
    float x, y, z;
    Vector3_s0105_c8d0() {}
    Vector3_s0105_c8d0(float a, float b, float c) : x(a), y(b), z(c) {}
};
Vector3_s0105_c8d0 normalized_safe(const Vector3_s0105_c8d0& v);              // 0x00449c20 (cdecl, hidden sret)
struct cSpatialPart {                                   // sub-object at +0x34
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
    virtual const Vector3_s0105_c8d0* GetPosition();               // +0x2c
};
struct cSPTimer {
    void Stop();                                        // 0x00bc3110
    void Restart();                                     // 0x00bc3130
    void Clear();                                       // 0x00bc3170
    uint64_t GetElapsedTime();                          // 0x00bc3190
    bool IsRunning();                                   // 0x00feba90
};
struct cSteerConfig {                                   // singleton at 0x0168df68
    uint32_t pad00[0x11c / 4];
    float mGalaxyMaxPlumpDistance;                      // +0x11c
    uint32_t pad120[(0x184 - 0x120) / 4];
    uint8_t mbGalaxyWarpEnabled;                        // +0x184
    float GetBlend();                                   // 0x00c37470 (+0xc8)
    float GetDamping();                                 // 0x00c37480 (+0xcc)
    float GetKinestheticBlend();                        // 0x00a0ab60
    float GetGalaxyWarpMultiplier(int kind, int mode);  // 0x00c3b880
    float GetGalaxyWarpTime(int kind, int mode, float dist);    // 0x00c3a1b0
};
cSteerConfig* SteerConfig();                            // 0x00c37360
struct cSteered {
    uint32_t pad00[0x34 / 4];
    cSpatialPart mAnchor;                               // +0x34
    uint32_t pad38[(0x60c - 0x38) / 4];
    Vector3_s0105_c8d0 mPush;                                      // +0x60c
    uint32_t pad618[(0x624 - 0x618) / 4];
    uint8_t mb624;
    uint8_t pad625[0x648 - 0x625];
    cSPTimer mTimerA;                                   // +0x648
    uint32_t pad64c[(0x668 - 0x64c) / 4];
    cSPTimer mTimerB;                                   // +0x668
    uint32_t pad66c[(0x718 - 0x66c) / 4];
    Vector3_s0105_c8d0 mPos;                                       // +0x718
    Vector3_s0105_c8d0 mVel;                                       // +0x724
    uint32_t pad730[(0x74c - 0x730) / 4];
    uint8_t mbTargetValid;                              // +0x74c
    uint8_t pad74d[3];
    Vector3_s0105_c8d0 mTarget;                                    // +0x750
    uint32_t pad75c[(0x768 - 0x75c) / 4];
    float mTargetDist;                                  // +0x768 (read via GetTargetDist)

    float GetTargetDist();                              // 0x00c37120
    void SetTargetDist(float d);                        // 0x00c3daa0
    float GetFollowDist();                              // 0x00c3be10
    void SetFollow(float w, const Vector3_s0105_c8d0* v);          // 0x00c3db50
};
struct cWarpDaemon {                                    // drive object at +0x508 (vtable)
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
    virtual void StartWarp();                           // +0x38
};
struct cMaterialTable {                                 // object at +0x730 (opaque storage)
    uint32_t pad00[(0x76c - 0x730) / 4];
};
const Vector3_s0105_c8d0* RotateByQuat(Vector3_s0105_c8d0* out, const void* key, const cMaterialTable* table);  // 0x0059aed0
struct cSPGameDataUFO_s0105_c8d0 {                                 // the UFO's state block (0x718 = position)
    uint32_t pad00[0x508 / 4];
    cWarpDaemon mWarpDaemon;                            // +0x508 (vptr; 15 vtable slots)
    uint8_t pad50c[0x628 - 0x50c];
    cSPTimer mWarpClock;                                // +0x628 (methods only)
    uint8_t pad629[0x714 - 0x629];
    int mMode;                                          // +0x714
    Vector3_s0105_c8d0 mPos;                                       // +0x718
    Vector3_s0105_c8d0 mVel;                                       // +0x724
    cMaterialTable mMaterial;                           // +0x730
    int mWarpState;                                     // +0x76c
    uint8_t pad770[0x7f4 - 0x770];
    float mWarpSpeed;                                   // +0x7f4
    bool CanWarp();                                     // 0x00c37040
};
struct cPlanetModel_s0105_c8d0 {
    float FUN_b7e4d0();                                 // 0x00b7e4d0
};
cPlanetModel_s0105_c8d0* PlanetModel_s0105_c8d0();                            // 0x00b3d350
struct cSPSpacePlanetCameraController {
    float GetMouseWheelSpeed();                         // 0x01017e80
};
struct cControllerHolder {
VPAD(0);
VPAD(1);
VPAD(2);
    virtual cSPSpacePlanetCameraController* FindController(uint32_t key);   // +0x0c
};
struct cAppInner {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
    virtual cControllerHolder* GetControllers();        // +0x38
};
struct cAppObj {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
    virtual cAppInner* GetSimulator();                  // +0x50
};
cAppObj* App_s0105_c8d0();                                         // 0x0067dd10
extern const Vector3_s0105_c8d0 kDefaultSummarizerExtents;         // 0x016e2114
struct cSummarizerD180 {
    void** mClassVt;                    // +0x00
    uint32_t mPad04;                    // +0x04
    void** volatile mBaseVt;            // +0x08
    uint32_t mField0C;                  // +0x0c
    Vector3_s0105_c8d0 mExtents;                   // +0x10
};
struct cSummarizerD1D0 {
    void** mClassVt;                    // +0x00
    uint32_t mPad04;                    // +0x04
    void** volatile mBaseVt;            // +0x08
    uint32_t mField0C;                  // +0x0c
};
struct cSPPlayerInventory {
    uint32_t pad00[0x76c / 4];
    int mWarpMode;                                      // +0x76c
};
struct cSPSimulatorSpaceGame_s0105_c8d0 {
    cSPPlayerInventory* GetPlayerInventory();           // 0x00a1ad60
    float GetMaxTravelDistance();                       // 0x00ffbfc0
};
cSPSimulatorSpaceGame_s0105_c8d0* GetUFOSimulator_s0105_c8d0();               // 0x00ffbe50
__forceinline float Length_s0105_c8d0(const Vector3_s0105_c8d0& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
__forceinline float Distance(const Vector3_s0105_c8d0& a, const Vector3_s0105_c8d0& b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
// ---- items of slice s0105c8d0 end

// @ 0x00c36e80
void* __fastcall FUN_00c36e80(Ufo* self, void* dummy, u32 key)
{
  (void)dummy;
  if (key != 0xb033b403u) {
    void* r = FUN_00b18460(key);
    if (r == 0) {
      r = self->loco.Find(key);
      if (r == 0) r = self->combat.Find2(key);
    }
    return r;
  }
  return self;
}

// @ 0x00c36ee0
u8 __fastcall FUN_00c36ee0(Ufo* self, void* dummy, void* stream)
{
  (void)dummy;
  void* w = ((TFp0)((void**)stream)[0x20 / 4])(stream);
  w = ((TFp0)((void**)w)[0x18 / 4])(w);
  u32 ver = 0xb033b403u;
  WriteUint32(w, &ver, 1, 0);

  u8 ok = 0;
  if (!((CGameData*)self)->Write(stream)) goto afterChain;
  if (!self->combat.Write(stream)) goto afterChain;
  if (!self->loco.Write(stream)) goto afterChain;
  ok = 1;
afterChain:
  g_168df70 = (self->p7b0 != 0) ? ((Sub70*)self->p7b0)->f70 : 0;
  g_168df6c = (self->p764 != 0) ? ((Sub70*)self->p764)->f70 : 0;

  cVarListSerializer ser;
  ser.Ctor(self, (void*)0x01573290, 0x1a80d26u);
  if (ok) ok = ser.Serialize(stream);

  void* p = ((TFp0)((void**)stream)[0x20 / 4])(stream);
  if (self->p6c8 != 0) {
    void* ow = ((TFp0)((void**)p)[0x18 / 4])(p);
    u8 one = 1;
    StreamWrite(ow, &one, 1);
    ((BehTree*)self->p6c8)->Write(stream);
  } else {
    void* ow = ((TFp0)((void**)p)[0x18 / 4])(p);
    u8 zero = 0;
    StreamWrite(ow, &zero, 1);
  }
  return ok;
}

// @ 0x00c37040
bool __fastcall FUN_00c37040(Ufo* self, void* dummy)
{
  (void)dummy;
  switch (self->state714) {
  case 0:
    if (self->f7f4 > g_kZero) {
      SpaceGameC* sg = (SpaceGameC*)SpaceGameGet();
      return sg->f4c30() == 0;
    }
    return false;
  case 3: {
    Inventory* inv = GetUFOSimulator()->GetPlayerInventory();
    if (inv == 0) return true;
    return inv->f76c >= 2;
  }
  case 8:
  case 9:
    return false;
  default:
    return true;
  }
}

// @ 0x00c370e0
bool __fastcall FUN_00c370e0(Ufo* self, void* dummy)
{
  (void)dummy;
  if (self->b77e != 0) {
    void* p = ((TFp0)((void**)self->loco.vtbl)[0xac / 4])(&self->loco);
    if (p != 0) {
      return ((F18Obj*)p)->f18 <= g_kEpsilon;
    }
  }
  return 0;
}

// @ 0x00c37130
void __fastcall FUN_00c37130(Ufo* self, void* dummy, u8 v)
{
  (void)dummy;
  if (self->b77c != v) {
    self->b77c = v;
    self->b77d = 1;
  }
}

// @ 0x00c37180
void __fastcall FUN_00c37180(Ufo* self, void* dummy, u32* key, u8 flag)
{
  (void)dummy;
  if (self->k780 == key[0] && self->k784 == key[1] && self->k788 == key[2]) return;
  bool initial = (self->state714 == 0);
  self->k780 = key[0];
  self->k784 = key[1];
  self->k788 = key[2];
  self->b78c = flag;
  self->b78d = 1;
  if (initial) {
    Empire* e = (Empire*)FUN_01021300();
    if (e != 0) {
      e->SetUFOKey(key);
      void* ms = MessageServer();
      ((TFv4)((void**)ms)[0x18 / 4])(ms, 0x5da932eu, 0, 0, 0);
    }
  }
}

// @ 0x00c37230
void __fastcall FUN_00c37230(Ufo* self, void* dummy, u32* out, u8* outFlag)
{
  (void)dummy;
  out[0] = self->k780;
  out[1] = self->k784;
  out[2] = self->k788;
  *outFlag = self->b78c;
}

// @ 0x00c37270
void __fastcall FUN_00c37270(Ufo* self, void* dummy)
{
  (void)dummy;
  void* o = FUN_00f473a0(0x1c, "Simulator", 0, 0, 0, 0);
  void* u = (o != 0) ? ((Big28*)o)->Init() : 0;
  self->loco.Set(u);
  self->timer.Restart();
}

// @ 0x00c372c0
s32 __fastcall FUN_00c372c0(Ufo* self, void* dummy)
{
  (void)dummy;
  float v = self->f540;
  float r = ((TFf0)((void**)self->combat.vtbl)[0x58 / 4])(&self->combat);
  if (v <= r * 0.2f) return 1;
  return 0;
}

// @ 0x00c37300
s32 __fastcall FUN_00c37300(Ufo* self, void* dummy)
{
  (void)dummy;
  if (self->f7f8 * 0.2f >= self->f7f4) return 1;
  return 0;
}

// @ 0x00c37330
bool __fastcall FUN_00c37330(Loco* loco, void* dummy)
{
  (void)dummy;
  Ufo* self = (Ufo*)((char*)loco - 0x34);
  void* emp = NounManager()->GetPlayerEmpireOrMinus1();
  void* v = ((TFp0)((void**)self->vtbl)[0x4c / 4])(self);
  return v == emp;
}

// @ 0x00c37550
float __fastcall FUN_00c37550(LocoF* self, void* dummy, s32 which)
{
  (void)dummy;
  if (which == 0) return self->f144;
  return self->f14c;
}

// @ 0x00c37570
float __fastcall FUN_00c37570(LocoF* self, void* dummy, s32 which)
{
  (void)dummy;
  if (which == 0) return self->f148;
  return self->f150;
}

// @ 0x00c375d0
float __cdecl FUN_00c375d0(float* pos)
{
  float radius = PlanetModel()->GetRadiusAt(pos);
  float water = PlanetModel()->GetWaterHeight();
  float base = (water > radius) ? water : radius;
  float h = FUN_00b7e4d0(PlanetModel());
  PlanetGlob* pg = g_planetGlob;
  float t = (sqrtf(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]) - (pg->f0c + base)) /
            ((pg->f10 + h) - (pg->f0c + base));
  float r = (1.0f - t) * base + t * h;
  return (r > base) ? r : base;
}

// @ 0x00c376b0
float __cdecl FUN_00c376b0()
{
  float top = g_planetGlob->f10;
  return FUN_00b7e4d0(PlanetModel()) + top;
}

// @ 0x00c37740
void* __fastcall FUN_00c37740(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  if (param == 0) return 0;
  void* a = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  void* b = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0x137e8e0u);
  if (a == 0 && (b == 0 || ((Cand*)b)->b1c != 2)) return 0;

  void* t = ((TFp0)((void**)param->vtbl)[0x08 / 4])(param);
  float* p1 = ((TFfp0)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco);
  float* p2 = ((TFfp0)((void**)t)[0x2c / 4])(t);
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float d = sqrtf(dx * dx + dy * dy + dz * dz);

  if (self->p798 != 0) {
    float lo = FUN_0104be20(self->p798);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p798);
      if (d <= hi) return self->p798;
    }
  }
  if (self->p79c != 0) {
    float lo = FUN_0104be20(self->p79c);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p79c);
      if (d <= hi) return self->p79c;
    }
  }
  if (self->p7a0 != 0) {
    float lo = FUN_0104be20(self->p7a0);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p7a0);
      if (d <= hi) return self->p7a0;
    }
  }
  return 0;
}

// @ 0x00c37890
u8 __fastcall FUN_00c37890(Ufo* self, void* dummy, ParamObj* param, s32 which)
{
  (void)dummy;
  void* t;
  if (which == 1) t = self->p798;
  else if (which == 2) t = self->p79c;
  else if (which == 3) t = self->p7a0;
  else return 0;
  if (t == 0) return 0;
  if (FUN_0104fff0(t) == 0) return 0;
  if (param == 0) return 0;

  void* a = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  void* b = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0x137e8e0u);
  if (a != 0 || (b != 0 && ((Cand*)b)->b1c == 2)) {
    void* o = ((TFp0)((void**)param->vtbl)[0x08 / 4])(param);
    float* p1 = ((TFfp0)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco);
    float* p2 = ((TFfp0)((void**)o)[0x2c / 4])(o);
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];
    float d = sqrtf(dx * dx + dy * dy + dz * dz);
    if (FUN_0104be20(t) <= d && d <= FUN_0104be30(t)) return 1;
  }
  return 0;
}

// @ 0x00c379a0
void __fastcall FUN_00c379a0(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  ((CCombatant0*)self)->NotifyAttack(param);
  if (param == 0) return;
  void* p = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  if (p == 0) return;
  void* old = self->p208;
  if (p == old) return;
  ((TFv0)(*(void***)p)[0x00 / 4])(p);
  self->p208 = p;
  if (old != 0) ((TFv0)(*(void***)old)[0x04 / 4])(old);
}

// @ 0x00c37a00
void __fastcall FUN_00c37a00(Ufo* self, void* dummy)
{
  (void)dummy;
  ((CGameData*)self)->GetCastID();
  void* p = self->p208;
  if (p != 0) {
    self->p208 = 0;
    ((TFv0)(*(void***)p)[0x04 / 4])(p);
  }
}

// @ 0x00c37a30
void __fastcall FUN_00c37a30(Ufo* self, void* dummy, s32 effectId)
{
  (void)dummy;
  ((CCommunity*)self)->func54h(effectId);
  CInteractable* p = (CInteractable*)self->p7a4;
  if (p == 0) return;
  float m;
  if (self->u6e0 != 3) m = g_planetGlob->f1c;
  else m = g_planetGlob->f20;
  float r = ((TFf0)((void**)self->vtbl)[0x34 / 4])(self);
  p->SetEffectId(effectId, r * m);
}

// @ 0x00c389f0
float UFOThing::FUN_00c389f0(float d)
{
    if (d < 0.0f) {
        if (m714 == 0)
            GetUFOSimulator_s00c3_89f0()->FUN_00ffc020();
    }
    if (m714 == 0 && d < 0.0f) {
        if (!GetMissionManager()->IsRunning())
            return m7f4;
    }

    float hi = m7f8;
    float v  = m7f4 + d;
    float lo = 0.0f;
    v = (v < lo) ? lo : v;
    v = (hi < v) ? hi : v;
    m7f4 = v;

    if (m714 == 0 && v <= m7f8 * 0.2f) {
        TerrainSphere* t = NounManager_s00c3_89f0()->GetCurrentTerrainSphere();
        if (t != 0 && !t->FUN_00c772c0(0x66269e7)) {
            t->FUN_00c77bf0(0x66269e7);
            FUN_010666a0(0x73213921)->FUN_0106dcd0();
        }
    }
    return m7f4;
}

// @ 0x00c38b10
void UFOThing::FUN_00c38b10()
{
    RefObj* x = mp7a8 ? mp7a8->vf0c(0xee9b2232) : 0;
    RefObj* y = mp7a8 ? mp7a8->vf0c(0x4e3faaf) : 0;
    if (x != 0) {
        x->m224--;
    } else {
        if (y != 0)
            y->m63c--;
    }
    if (mp7a8 != 0) {
        LookupObj* t = mp7a8;
        mp7a8 = 0;
        t->Release();
    }
}

// @ 0x00c38b90
void UFOThing::FUN_00c38b90()
{
    RefObj* x = mp7ac ? mp7ac->vf0c(0xee9b2232) : 0;
    RefObj* y = mp7ac ? mp7ac->vf0c(0x4e3faaf) : 0;
    if (x != 0 && !x->vf2c()) {
        x->m228--;
    } else if (y != 0 && !y->vf2c()) {
        y->m638--;
    }
    if (mp7ac != 0) {
        LookupObj* t = mp7ac;
        mp7ac = 0;
        t->Release();
    }
}

// @ 0x00c38c20
void OffsetHolder::GetPos(Vec3* out)
{
    Vec3* p = (Vec3*)((float*)this - 0x134);   // 0x134 floats == 0x4d0 bytes
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
}

// @ 0x00c38c50
PaintSystemExt::PaintSystemExt()
{
    mp04 = 0;
    m20  = 1.0f;
    msg.a = 0;
    msg.b = 0;
    msg.c = 0;
    msg.d = 0;
    msg.e = 0;
}

// @ 0x00c38c90
PaintSystemExt::~PaintSystemExt()
{
    _ReadWriteBarrier();
    if (mp04 != 0) {
        LookupObj* t = mp04;
        mp04 = 0;
        t->Release();
    }
    if (msg.a != 0) {
        uint32_t a = msg.a;
        uint32_t b = msg.b;
        uint32_t c = msg.c;
        uint32_t d = msg.d;
        uint32_t e = msg.e;
        msg.a = 0;
        EA_RemoveHandler(a, b, c, d, e);
    }
    if (mp04 != 0)
        mp04->Release();
}

// @ 0x00c38d00
void cUFOKinestheticsTuning::ReadProps()
{
  GetFloatProp(mPropList.mpObject, 0x4496ebe, mHitTerrainDamage);
  GetFloatProp(mPropList.mpObject, 0x195d000, mMinAltitude);
  GetFloatProp(mPropList.mpObject, 0x195d002, mMaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x195d037, mDamageToDestScale);
  GetFloatProp(mPropList.mpObject, 0x195d038, mDamageToVelocityScale);
  GetFloatProp(mPropList.mpObject, 0x331e543, mHitSphereRadius);
  GetFloatProp(mPropList.mpObject, 0x6ba86fb, mHitSphereActiveDistance);
  GetFloatProp(mPropList.mpObject, 0x331e8cf, mMinExtent);
  GetFloatProp(mPropList.mpObject, 0x33c591d, mBomberScale);
  GetFloatProp(mPropList.mpObject, 0x609ee15, mFighterScale);
  GetFloatProp(mPropList.mpObject, 0x338d246, mUberTurretScale);
  GetFloatProp(mPropList.mpObject, 0x338d24d, mAllyScale);
  GetFloatProp(mPropList.mpObject, 0x4ea4823, mPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x5b56b19, mPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb58d, mPlumpTransitionScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb592, mNPCPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb596, mBasePlanetScale);
  GetFloatProp(mPropList.mpObject, 0x5ecb59b, mVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x5ecb5a0, mVelocityFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x2faa5db, mFighterVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x2faa5d7, mUberTurretVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x49b3d7e, mAllyVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x435b5a7, mKeyboardMovementSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x303bef4, mKeyboardMovementSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x195d010, mKeyboardAccelerationZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x339b758, mKeyboardAccelerationZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x2fa986a, mBomberVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x4ea6acf, mVelocityFactorZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x5b694ba, mMouseMovementSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x339b716, mMaxRotation);
  GetFloatProp(mPropList.mpObject, 0x4867421, mTargetFallOffRadius);
  GetFloatProp(mPropList.mpObject, 0x195d014, mBrakeFactor);
  GetFloatProp(mPropList.mpObject, 0x195d015, mBrakeOvershootFactor);
  GetFloatProp(mPropList.mpObject, 0x3309693, mAccelerationFactor);
  GetFloatProp(mPropList.mpObject, 0x3309697, mAccelerationFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x344436f, mVerticalAcclerationDown);
  GetFloatProp(mPropList.mpObject, 0x3309d37, mVerticalAcclerationUp);
  GetFloatProp(mPropList.mpObject, 0x195d012, mMouseMovementSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x195d013, mMouseRotationSpeedZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x32f7c0a, mMouseRotationSpeedZoomedIn);
  GetFloatProp(mPropList.mpObject, 0x32f7c06, mLeavePlanetTimePad);
  GetFloatProp(mPropList.mpObject, 0x3066aa0, mCollisionElasticity);
  GetFloatProp(mPropList.mpObject, 0x3308805, mCollisionRestitution);
  GetFloatProp(mPropList.mpObject, 0x195d011, mRotationPercentageRate);
  GetFloatProp(mPropList.mpObject, 0x2fa986f, mNoseTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x195d03a, mNoseTiltRate);
  GetFloatProp(mPropList.mpObject, 0x195d039, mMaxNoseTilt);
  GetFloatProp(mPropList.mpObject, 0x681b1aa, mVerticalTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x4f639fc, mMaxVerticalTilt);
  GetFloatProp(mPropList.mpObject, 0x195d03b, mBankTiltFactor);
  GetFloatProp(mPropList.mpObject, 0x330d208, mBankTiltRate);
  GetFloatProp(mPropList.mpObject, 0x3337396, mMaxBankTilt);
  GetFloatProp(mPropList.mpObject, 0x33375f6, mEscapeSequenceSpinRate);
  GetFloatProp(mPropList.mpObject, 0x33373a9, mEscapeSequenceVelocity);
  GetFloatProp(mPropList.mpObject, 0x4ea5863, mTrailEffectAlwaysOn);
  GetFloatProp(mPropList.mpObject, 0x4e6a105, mEffectMaxSpeedPlanet);
  GetFloatProp(mPropList.mpObject, 0x33b1de9, mEffectMaxSpeedSolar);
  GetFloatProp(mPropList.mpObject, 0x33b1df1, mEffectMaxSpeedGalaxy);
  GetFloatProp(mPropList.mpObject, 0x33b1dec, mTrailEffectMinSize);
  GetFloatProp(mPropList.mpObject, 0x31f7670, mMaxAltitudeDestinationDelta);
  GetFloatProp(mPropList.mpObject, 0x31f7668, mSolarSpeed);
  GetBoolProp(mPropList.mpObject, 0x195d03c, mSolarAcceleration);
  GetFloatProp(mPropList.mpObject, 0x195d03e, mGalaxySpeed);
  GetFloatProp(mPropList.mpObject, 0x195d03f, mGalaxyAcceleration);
  GetFloatProp(mPropList.mpObject, 0x195d040, mSolarMinPlump);
  GetFloatProp(mPropList.mpObject, 0x195d03d, mSolarMaxPlump);
  GetFloatProp(mPropList.mpObject, 0x37d5830, mGalaxyMinPlump);
  GetFloatProp(mPropList.mpObject, 0x4a06d7b, mGalaxyMaxPlump);
  GetFloatProp(mPropList.mpObject, 0x4a06d84, mGalaxyMinPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x4a06d8b, mGalaxyMaxPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x4a06d94, mBaseUFODamagePush);
  GetFloatProp(mPropList.mpObject, 0x4d7dbe9, mMaxUFODamagePush);
  GetFloatProp(mPropList.mpObject, 0x4d7dbea, mUFODamageVelocityDecayRate);
  GetFloatProp(mPropList.mpObject, 0x66cf309, mAltMaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x66cf318, mAltPlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x66d06a5, mAltVelocityFactorZoomedOut);
  GetFloatProp(mPropList.mpObject, 0x66d06a9, mExtra138);
  GetFloatProp(mPropList.mpObject, 0x66d06c0, mExtra13c);
  GetFloatProp(mPropList.mpObject, 0x66d0769, mExtra140);
  GetFloatProp(mPropList.mpObject, 0x66d0883, m2MaxAltitude);
  GetFloatProp(mPropList.mpObject, 0x66d0885, m2DamageToDestScale);
  GetFloatProp(mPropList.mpObject, 0x66d0888, m2DamageToVelocityScale);
  GetFloatProp(mPropList.mpObject, 0x66d088c, m2HitSphereRadius);
  GetFloatProp(mPropList.mpObject, 0x4d7dbeb, mExtra144);
  GetFloatProp(mPropList.mpObject, 0x4d7dbec, mExtra148);
  GetFloatProp(mPropList.mpObject, 0x5ecd92b, mExtra14c);
  GetFloatProp(mPropList.mpObject, 0x5ecd938, mExtra150);
  GetFloatProp(mPropList.mpObject, 0x4d972e7, m2HitTerrainDamage);
  GetFloatProp(mPropList.mpObject, 0x4d972e9, m2MinAltitude);
  GetFloatProp(mPropList.mpObject, 0x6400ea3, m2HitSphereActiveDistance);
  GetFloatProp(mPropList.mpObject, 0x64001ad, m2MinExtent);
  GetFloatProp(mPropList.mpObject, 0x64001c2, m2BomberScale);
  GetFloatProp(mPropList.mpObject, 0x4daaefc, m2FighterScale);
  GetFloatProp(mPropList.mpObject, 0x4dc0642, m2UberTurretScale);
  GetFloatProp(mPropList.mpObject, 0x4dcfba7, m2AllyScale);
  m2PlumpDistance = true;
  GetBoolProp(mPropList.mpObject, 0x672734f, m2PlumpDistance);
  GetFloatProp(mPropList.mpObject, 0x5ecf67c, m2PlumpScale);
  GetFloatProp(mPropList.mpObject, 0x60212c5, m2PlumpTransitionScale);
  GetFloatProp(mPropList.mpObject, 0x60212c6, m2NPCPlumpScale);
  GetFloatProp(mPropList.mpObject, 0x60212c7, m2BasePlanetScale);
  GetFloatProp(mPropList.mpObject, 0x65ba2cc, m2VelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x65ba2dc, m2VelocityFactorNPC);
  GetFloatProp(mPropList.mpObject, 0x65ba2f3, m2FighterVelocityFactor);
  GetFloatProp(mPropList.mpObject, 0x65ba2f6, m2UberTurretVelocityFactor);
}

// @ 0x00c3a180
char cUFOKinestheticsTuning_s00c3_a180::HandleMessage(int messageID, int arg)
{
    if (messageID == 0xf62def && *(int*)(arg + 0x18) == (int)0x99fb6f5b)
        this->ReadProps();
    return 0;
}

// @ 0x00c3a1b0
float cUFOKinestheticsTuning_s00c3_a180::GetGalaxyWarpTime(int warpMode, float unused, float t)
{
    (void)unused;
    float* pArray = 0;
    int    count  = 0;
    GetPropertyAsFloatArray(this->mpPropList, kPropGalaxyWarpTime, &count, &pArray);

    switch (warpMode)
    {
    case 2:
        if (count > 1)
            return (pArray[1] - pArray[0]) * t + pArray[0];
        break;
    case 4:
        if (count > 2)
            return pArray[2];
        break;
    default:
        break;
    }
    return 1.0f;
}

// @ 0x00c3a220
void enableWeapon(int toolID, int weaponLevel, IRefObject_s00c3_a180** ppSlot)
{
    int base  = 0;
    int count = 0;
    void* pTuning = GetSpaceCombatTuning_s00c3_a180();
    FUN_006a0ae0(*(void**)((U8*)pTuning + 8), toolID, &count, &base);

    if (count <= weaponLevel)
    {
        if (count > 0)
            weaponLevel = count - 1;
        if (count <= weaponLevel)
            return;
    }

    void* pEntry = (void*)(base + weaponLevel * 0xc);
    IRefObject_s00c3_a180* pOld = *ppSlot;
    if (pOld != 0)
    {
        *ppSlot = 0;
        vcall_release8(pOld);           // vtable +0x8
    }
    void* pEntryResult = EraseToolEntry(pEntry, ppSlot);
    // CreateToolFromToolID is `?CreateToolFromToolID@cSPToolManager@@QAE_NI@Z`; its `this`
    // (ecx) is the erase result and the tool id is the stack argument.  MSVC /O2 folds the
    // `mov ecx, eax` here, so the encoded call differs from the original even though the
    // observable behaviour is the same (see nonmatching.txt).
    ((Fn0104e340*)pEntryResult)->f((unsigned int)(U32)pEntry);
}

// @ 0x00c3a9f0
char cSPGameDataUFO_s00c3_a180::Initialize()
{
    if (this->mInt7bc == 0)
        return UTFWin_Window_Initialize();
    return 0;
}

// @ 0x00c3aa10
char cSPGameDataUFO_s00c3_a180::vtableSlot40Wrapper(int arg)
{
    char ok = ((FnB183F0*)this)->f(arg);
    if (ok != 0)
        ((FnC385D0*)this)->f();
    return ok;
}

// @ 0x00c3b560
bool cSPGameDataUFO_s00c3_ae70::OnMessage(U32 messageID, int arg)
{
    (void)arg;
    if ((messageID == 0x44f1189 || messageID == 0x67b2a95) && *(int*)((char*)this + 0x208) != 0) {
        void* pSpaceGame = SpaceGameGet_s00c3_ae70();
        if (((FnB18E40*)pSpaceGame)->f()) {
            void* pServer = MessageServer();
            typedef int (__thiscall* Vf)(void*, U32, int, int, int);
            ((Vf)(*(void**)(*(char**)pServer + 0x18)))(pServer, 0x67b2a95, 0, 0, 0);
            return false;
        }
        ((FnC382E0*)((char*)this - 0x5e8))->f();
    }
    return false;
}

// @ 0x00c3b7f0
void cUFOKinestheticsTuning_s00c3_ae70::Init()
{
    void* pManager = PropertyManager();
    if (mpPropList != 0) {
        void* pOld = mpPropList;
        mpPropList = 0;
        ((IReleased*)pOld)->Release();
    }
    typedef void (__thiscall* Vf)(void*, U32, int, void*);
    ((Vf)(*(void**)(*(char**)pManager + 0x2c)))(pManager, 0x99fb6f5b, 0x2ae0c7e, &mpPropList);
    ReadProps();
    void* pServer = MessageServer();
    md1a8 = (U32)pServer;
    md1ac = (U32)this;
    md1b0 = 0x146bb64;
    md1b4 = 1;
    md1b8 = 0;
    if (pServer != 0) {
        if (this != 0) {
            typedef int (__thiscall* Vf2)(void*, void*, U32);
            ((Vf2)(*(void**)(*(char**)pServer + 0x24)))(pServer, this, 0xf62def);
        }
    }
}

// @ 0x00c3b880
float cUFOKinestheticsTuning_s00c3_ae70::GetGalaxyWarpMultiplier(int index, int warpMode)
{
    float factor = gF_1485720;
    if (warpMode == 0) {
        void* pSpaceGame = SpaceGameGet_s00c3_ae70();
        if ((*(U8*)((char*)pSpaceGame + 0xc4) & 0x20) != 0)
            factor = ((Fn1005C60*)pSpaceGame)->f(5);
    } else if (warpMode == 4) {
        factor = m2PlumpScale;   // +0x188
    }

    int count = 0;
    float* array = 0;
    FUN_6a08b0(mpPropList, 0x5c80689, &count, &array);
    int i = index - 1;
    if (i < count)
        return array[i] * factor;
    return factor;
}

// @ 0x00c3bc80
int cSPGameDataUFO_s00c3_ae70::GetFieldValues(void* pOut)
{
    cVarListSerializer_s00c3_ae70 localA14;    // +0x508 serialiser (constructed first, lower in the frame)
    cVarListSerializer_s00c3_ae70 local1428;   // `this` serialiser

    int sum = ((FnB18420*)this)->f(pOut);
    sum += ((FnC0AF90*)((char*)this + 0x34))->f(pOut);

    localA14.ctor((char*)this + 0x508, (void*)0x1570858, 0x1a80d26);
    sum += localA14.GetFields(pOut);

    local1428.ctor(this, (void*)0x1573290, 0x1a80d26);
    sum += local1428.GetFields(pOut);

    return sum;
}

// @ 0x00c3be10
float cSPGameDataUFO_s00c3_ae70::GetScaleRadius()
{
    float v[3];
    v[0] = mf078 - mf06c;
    v[1] = mf07c - mf070;
    v[2] = mf080 - mf074;
    float* pExtent = v + 1;
    if (!(v[0] < v[1]))
        pExtent = v;
    if (v[2] > *pExtent)
        pExtent = v + 2;

    return GetScale() * *pExtent * gF_1471064;
}

// @ 0x00c3bfe0
void cSPGameDataUFO::SetDestination(const Vector3* pDest)
{
    // mRef760 = (mByte74c ? mRef75c : null)
    IRefObject* pNew = mb74c ? mRef75C.mpObject : 0;
    if (pNew != mRef760.mpObject) {
        if (pNew) pNew->AddRef();
        IRefObject* pOld = mRef760.mpObject;
        mRef760.mpObject = pNew;
        if (pOld) pOld->Release();
    }
    mRef75C = (IRefObject*)0;
    mInt764 = 0;
    mDestination = *pDest;
    mb74c = 0;
    if (mUFOType == 0)
        ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c190
void cSPGameDataUFO::SetDestination(cPlanet* pPlanet)
{
    IRefObject* pNew = mb74c ? mRef75C.mpObject : 0;
    if (pNew != mRef760.mpObject) {
        if (pNew) pNew->AddRef();
        IRefObject* pOld = mRef760.mpObject;
        mRef760.mpObject = pNew;
        if (pOld) pOld->Release();
    }
    mRef75C = (IRefObject*)pPlanet;
    mInt764 = 0;
    typedef Vector3* (__thiscall* VGet)(void*);
    void* pObj = (void*)pPlanet;
    Vector3* pd = ((VGet)(*(void**)(*(char**)pObj + 0x2c)))(pObj);
    mDestination = *pd;
    mb74c = 0;
    ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c360
void cSPGameDataUFO::SetDestinationFromCities(int param)
{
    mRef75C = (IRefObject*)0;
    mRef760 = mRef75C;
    mInt764 = param;
    Vector3* pd = GetCities();
    mDestination = *pd;
    mb74c = 0;
    ((FnBC3110*)((char*)this + 0x648))->f();
    EmitDestParam(this);
}

// @ 0x00c3c4d0
int cSPGameDataUFO::GetNextCollision(Vector3* pOut)
{
    ListNodeBase* pHead = &mCollisions;
    if (pHead->mpNext != pHead) {
        CollisionInfo* pInfo = &((CollisionNode*)pHead->mpNext)->mValue;
        int nounID = pInfo->mNounID;
        *pOut = pInfo->mPosition;
        CollisionNode* pNode = (CollisionNode*)pHead->mpNext;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        operator_delete(pNode);
        return nounID;
    }
    return 0;
}

// @ 0x00c3c810
void __stdcall FUN_00c3c810(ListNodeBase* pHead, const CollisionInfo* pValue)
{
    CollisionNode* pNode = (CollisionNode*)operator_new(0x18, g_sz_Simulator, 0, 0,
                                                        g_allocator_13ebb38, 0xd1);
    CollisionInfo* pDst = &pNode->mValue;
    if (pDst != 0) {
        pDst->mNounID      = pValue->mNounID;
        pDst->mPosition.x  = pValue->mPosition.x;
        pDst->mPosition.y  = pValue->mPosition.y;
        pDst->mPosition.z  = pValue->mPosition.z;
    }
    pNode->mpNext = pHead;
    pNode->mpPrev = pHead->mpPrev;
    pHead->mpPrev->mpNext = pNode;
    pHead->mpPrev = pNode;
}

// @ 0x00c3c870
cSPGameDataUFO::cSPGameDataUFO()
{
    ((FnB18660*)this)->f();                   // cGameData::cGameData
    void* p34 = (char*)this + 0x34;
    ((FnC43860*)p34)->f();
    void* p508 = (char*)this + 0x508;
    ((FnBFD4E0*)p508)->f();                   // cCombatant::cCombatant
    void* p5d0 = (char*)this + 0x5d0;
    ((FnAC03D0*)p5d0)->f();                   // cInteractionTarget::cInteractionTarget

    mpVftbl5e8 = (void*)0x13eb394;
    *(void**)p5d0 = (void*)0x146bb88;
    mpVftbl00 = (void*)0x146bd28;
    mpVftbl04 = (void*)0x146bd14;
    *(void**)p34 = (void*)0x146bc18;
    mpVftbl108 = (void*)0x146bc10;
    *(void**)p508 = (void*)0x146bba8;
    mpVftbl5e8 = (void*)0x146bb80;

    mf5ec = 0.0f;
    mf5f0 = 0.0f;
    mf5f4 = gF_168df74;
    mf5f8 = gF_168df78;
    mf5fc = gF_168df7c;
    mf600 = 0.0f;
    mf604 = 0.0f;
    mb608 = 0;

    mf60c = gF_168df74;
    mf610 = gF_168df78;
    mf614 = gF_168df7c;
    mf618 = gF_168df74;
    mf61c = gF_168df78;
    mf620 = gF_168df7c;
    mb624 = 0;

    ((FnB63890*)((char*)this + 0x628))->f();
    ((FnB63890*)((char*)this + 0x648))->f();
    ((FnB63890*)((char*)this + 0x668))->f();

    mb688 = 0;
    mb689 = 0;
    md68c = 0;
    mb690 = 0;
    mb691 = 0;
    mf694 = 0.0f;
    mf698 = 0.0f;
    mf69c = 0.0f;
    mf6a0 = 0.0f;
    mf6a4 = 0.0f;
    mf6a8 = 0.0f;
    mf6ac = 0.0f;
    mf6b4 = gF_1485720;
    mf6b8 = gF_1485720;
    mInt6b0 = -1;

    mf6bc = gF_15731bc;
    mf6c0 = gF_15731c0;
    mf6c4 = gF_15731c4;
    mp6c8 = 0;

    ((FnB63890*)((char*)this + 0x6d0))->f();
    ((FnB63890*)((char*)this + 0x6f0))->f();

    md710 = 0;
    mUFOType = -1;

    mf718 = gF_15731bc;
    mf71c = gF_15731c0;
    mf720 = gF_15731c4;
    mf724 = gF_168df74;
    mf728 = gF_168df78;
    mf72c = gF_168df7c;
    mf730 = gF_15731c8;
    mf734 = gF_15731cc;
    mf738 = gF_15731d0;
    mf73c = gF_15731d4;
    mf740 = gF_168df74;
    mf744 = gF_168df78;
    mf748 = gF_168df7c;

    mb74c = 1;
    mDestination.x = gF_15731bc;
    mDestination.y = gF_15731c0;
    mDestination.z = gF_15731c4;

    (void)gF_13ec5b4;
    mRef75C.mpObject = 0;
    mRef760.mpObject = 0;
    mInt764 = 0;
    mf768 = gF_13ec5b4;
    md76c = 0;

    mCollisions.mpNext = &mCollisions;
    mCollisions.mpPrev = &mCollisions;

    mb77c = 1;
    mb77d = 0;
    mb77e = 0;
    mp780 = 0;
    mp784 = 0;
    mp788 = 0;
    mb78c = 1;
    mb78d = 0;
    mp790 = 0;
    mp794 = 0;
    mp798 = 0;
    mp79c = 0;
    mp7a0 = 0;
    mp7a4 = 0;
    mp7a8 = 0;
    mp7ac = 0;
    mp7b0 = 0;

    ((FnB63890*)((char*)this + 0x7b8))->f();

    mp7d8 = 0;
    mp7dc = 0;
    mNameBegin = (wchar_t*)0x1667bac;
    mNameEnd = (wchar_t*)0x1667bac;
    mNameCapacity = (wchar_t*)0x1667bae;

    mRef7f0.mpObject = 0;
    mf7f4 = 0.0f;
    mf7f8 = 0.0f;
    mInt7fc = -1;
    mp800 = 0;
    mp804 = 0;
    mp808 = 0;
    mp80c = 0;
    md810 = 0;
    md814 = 0;

    mf038 = gF_15731bc;
    mf03c = gF_15731c0;
    mf040 = gF_15731c4;

    void* p = operator_new(0x10, g_sz_Simulator, 0, 0, 0, 0);
    if (p != 0)
        p = ((Fn105D1D0*)p)->f();
    else
        p = 0;
    ((FnC421B0*)p34)->f(p);

    mInt224 = 5;

    const wchar_t* pEnd = g_wsz_UninitUfoName;
    while (*pEnd != 0)
        ++pEnd;
    ((Fn423650*)((char*)this + 0x7e0))->f((void*)g_wsz_UninitUfoName, (void*)pEnd);
}

// @ 0x00c3cd60
namespace SP {
void cSPGameDataUFO_s00c3_cd60::TakeHit(float damage, int attackerPoliticalID, int damageType, const Vector3_s00c3_cd60& direction, cCombatant_s00c3_cd60* pAttacker)
{
    if (GetCurrentGameMode() == &gGameModeSpace && mUFOType == 0)
        return;

    if (damageType == 10) {
        cCombatant_s00c3_cd60::TakeHit(damage, attackerPoliticalID, damageType, direction, pAttacker);
        return;
    }

    if (IsInvulnerable() || IsGamePaused() || mDeathState == 2)
        return;
    if (mCombatState == 3 && damageType != 5)
        return;
    if (GetUniverseContext() == 0 && mUFOType == 0 && GetUFOSimulator_s00c3_cd60()->IsPlayerDying())
        return;

    if (pAttacker && pAttacker->ToGameData()->IsDestroyed())
        pAttacker = 0;

    cSPGameDataUFO_s00c3_cd60* pAttackerUFO = CombatantToUFO(pAttacker);
    if (pAttackerUFO) {
        if (pAttackerUFO->mUFOType == 3)
            attackerPoliticalID = GetPlayerEmpireID();
        if (GetPoliticalID() == attackerPoliticalID)
            return;
        if (mUFOType == 3) {
            if (attackerPoliticalID == GetPlayerEmpireID())
                return;
            if (pAttackerUFO->mUFOType == 3)
                return;
        }
    }

    void* pAttackerBuilding = CombatantToBuilding(pAttacker);
    if (pAttackerBuilding) {
        if (GetPoliticalID() == attackerPoliticalID)
            return;
        if (mUFOType == 3 && attackerPoliticalID == GetPlayerEmpireID())
            return;
    }

    AddHostileUnit(pAttacker);

    int type = mUFOType;
    if (type != 0 && type != 3 &&
        (pAttackerBuilding ||
         (pAttackerUFO && pAttackerUFO->mUFOType != 0 && pAttackerUFO->mUFOType != 3)))
    {
        damage *= GetSpaceCombatTuning()->GetDamageMultiplier();
    }

    if (GetUniverseContext() == 0 && damageType != 8) {
        Vector3_s00c3_cd60 impulse = direction * damage;
        float lengthSq = impulse.SquaredLength();
        if (lengthSq > 1.5258789e-05f) {
            Vector3_s00c3_cd60 up = Vector3_Normalize(GetPosition());
            impulse -= up * up.Dot(impulse) * 0.9f;
            impulse = Vector3_Normalize(impulse);
            if (mbAtDestination)
                mbRotateTowardsDestination = false;
            float scale1 = gpUFOTuning->mImpulseScale;
            float scale2 = gpUFOTuning->mImpulseScale2;
            float base = gpUFOTuning->mImpulseBase;
            mbAtDestination = false;
            mHoverTimer.Stop();
            float length = sqrtf(lengthSq);
            float k1 = length * scale1 + base;
            float k2 = length * scale2 + base;
            Vector3_s00c3_cd60 a = impulse * k1;
            mDestination += a;
            Vector3_s00c3_cd60 b = impulse * k2;
            mDamageVelocity += b;
            mOffsetDueToDamage += b;
        }
    }

    if (mUFOType == 3 && mHealthPoints == mMaxHealthPoints && damage > 0.0f) {
        cEmpire_s00c3_cd60* empire = StarManager()->GetEmpireByID(GetPoliticalID());
        if (empire)
            PlayEmpireHitSound(empire);
    }

    cCombatant_s00c3_cd60::TakeHit(damage, attackerPoliticalID, damageType, direction, pAttacker);

    if (mUFOType == 0) {
        EA::AutoRefCount_s00c3_cd60<cSpaceToolData> tool(SpaceGameGet_s00c3_cd60()->GetPlayerInventory()->GetActiveTool());
        if (tool)
            tool->mbInUse = true;
        mCombatState = 1;
        if (pAttacker) {
            cSpaceToolData* activeTool = SpaceGameGet_s00c3_cd60()->GetPlayerInventory()->GetActiveTool();
            cUFOSimulator* sim = GetUFOSimulator_s00c3_cd60();
            if (!sim->ffc320() && !sim->ffc2d0() && ToolCanTarget(activeTool, pAttacker->ToGameData()))
                sim->ffd710(activeTool, pAttacker);
        }
    }

    if (GetCurrentGameMode() == &gGameModeSpaceAlt && attackerPoliticalID == GetPlayerEmpireID()) {
        cMission* mission = GetMissionByID(mOwnerMission);
        if (!mission || !mission->mbIgnoreAwareness)
        {
            cSimulatorUniverse* universe = cSimulatorUniverse::sInstance;
            universe->AdjustAwareness(GetPoliticalID(), 5);
        }
    }

    bool destroyed = false;
    if (mHealthPoints <= 0.0f) {
        if (mUFOType == 0) {
            SpaceGameGet_s00c3_cd60()->f1005180(10);
            AchievementsController()->Trigger(0xd456d958, 0x10, 1);
            if (!GameViewManager()->a98020() && !GameViewManager()->GetAccessFlags())
                StartPlayerDeathSequence();
            ResourceKey key1(0, 0, 0);
            ResourceKey key2(0, 0, 0);
            ResourceKey key3(0, 0, 0);
            PostUFOEvent(0x949ace8, 0, GetPlayerEmpire()->GetUFOKey(), &key3, 0, 0, &key2, &key1);
            cSimulatorUniverse::sInstance->OnPlayerDeath(attackerPoliticalID);
        }
        else {
            if (pAttackerUFO && (pAttackerUFO->mUFOType == 0 || pAttackerUFO->mUFOType == 3) &&
                GetUniverseContext() == 0)
            {
                float chance = GetSpaceCombatTuning()->GetLootDropChance(mUFOType);
                if (sMathRandom.RandomDoubleUniform() <= chance)
                    DropLoot(mNextPosition, this);
            }

            if (mUFOType == 3) {
                cEmpire_s00c3_cd60* empire = StarManager()->GetEmpireByID(GetPoliticalID());
                if (empire)
                    PlayEmpireDestroyedSound(empire);
                if (GetPoliticalID() != GetPlayerEmpireID()) {
                    if (!NounManager_s00c3_cd60()->GetCurrentTerrainSphere()->HasFlag(0xfce7461)) {
                        gpSpaceTokenTranslator->mpDestroyedUFO = this;
                        MessageRouter()->Post(0x39c4d972, cMessageData(this, 0));
                        TriggerTutorialEvent("SPG_PlayerDestroyedPossee", 0xfce7461, 1);
                    }
                    int politicalID = GetPoliticalID();
                    if (politicalID != -1 && politicalID != GetPlayerEmpireID()) {
                        RelationshipManager()->RecordEvent(GetPoliticalID(), GetPlayerEmpireID(), 0x526e542, 1.0f);
                        EventLog()->PostFeedbackEvent(0x86862dec, 0x131a9f54, 0, 0, 1, 0);
                    }
                    EA::AutoRefCount_s00c3_cd60<EA::Swarm::cIVisualEffect_s00c3_cd60> effect;
                    if (EffectsManager()->CreateVisualEffect(0x3e2cc60, 0, effect.AsPPTypeParam())) {
                        Transform transform;
                        transform.SetOffset(GetPosition());
                        effect->SetSourceTransform(transform);
                        effect->Start(0);
                    }
                }
                GetUFOSimulator_s00c3_cd60()->RemovePoliticalID(GetPoliticalID(), 0);
            }
            else if (mUFOType != 0) {
                if (GetPoliticalID() != -1 && attackerPoliticalID != -1) {
                    cMission* mission = GetMissionByID(mOwnerMission);
                    if (!mission || !mission->mbIgnoreAwareness)
                        RelationshipManager()->RecordEvent(GetPoliticalID(), attackerPoliticalID, 0x591f833, 1.0f);
                    cEmpire_s00c3_cd60* empire = StarManager()->GetEmpireByID(GetPoliticalID());
                    if (empire) {
                        ResourceKey key1(0, 0, 0);
                        ResourceKey key2(0, 0, 0);
                        ResourceKey key3(0, 0, 0);
                        PostUFOEvent(0xbc7c7b37, empire, empire->GetUFOKey(), &key3, 0, 0, &key2, &key1);
                    }
                }
            }

            EA::AutoRefCount_s00c3_cd60<EA::Swarm::cIVisualEffect_s00c3_cd60> effect;
            if (mUFOType == 4)
                EffectsManager()->CreateVisualEffect(0x3d6f82d, 0, effect.AsPPTypeParam());
            else
                EffectsManager()->CreateVisualEffect(0x3d6f830, 0, effect.AsPPTypeParam());
            if (effect) {
                int modelIDs[2] = { mModelKeyInstance, mModelKeyGroup };
                effect->SetIntParams(6, modelIDs, 2);
                float radius = GetBoundingRadius();
                effect->SetFloatParams(1, &radius, 1);
                Transform transform;
                transform.SetRotation(GetOrientation());
                transform.SetOffset(GetPosition());
                transform.SetScale(radius);
                effect->SetSourceTransform(transform);
                effect->Start(0);
            }
            destroyed = true;
            OnUFODestroyed(this, 0);
        }
    }

    if (GetCurrentGameMode() == &gGameModeSpaceAlt && attackerPoliticalID == GetPlayerEmpireID() && destroyed)
        AchievementsController()->AutoTest(0x2a7c313d, 1);

    if (mUFOType == 0 && IsOnMission()) {
        if (GetMissionManager_s00c3_cd60()->IsRunning()) {
            cPlanet_s00c3_cd60* planet = NounManager_s00c3_cd60()->GetCurrentTerrainSphere();
            if (planet && !planet->HasFlag(0x6627799)) {
                planet->SetFlag(0x6627799);
                TutorialManager()->Trigger(0xe8aec881);
            }
        }
    }
}
}  // namespace SP

// @ 0x00c3daa0
void UFO::func3daa0(float val)
{
    char* self = (char*)this;
    *(float*)(self + 0x768) = val;
    void* key = self + 0x750;
    ((Fn3be70*)self)->f(key);
}

// @ 0x00c3dac0
void UFO::func3dac0(void* p)
{
    char* self = (char*)this;
    char* dst = self + 0x7e0;
    if ((char*)p != dst) {
        void** v = (void**)p;
        ((Str*)dst)->assign(v[0], v[1]);
    }
}

// @ 0x00c3dae0
void UFO::func3dae0(float* p)
{
    char* self = (char*)this;
    if (GetUniverseContext() == 0) {
        ((Fn3be70*)self)->f(p);
        *(float*)(self + 0x768) = (float)sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
        ((Fn3be70*)self)->f(self + 0x750);
    } else {
        ((Fn3bfe0*)self)->f(p);
    }
    ((Fn37e60*)self)->f();
}

// @ 0x00c3db50
void UFO::func3db50(void* a, void* b)
{
    char* self = (char*)this;
    struct { int a; float b, c, d; } tmp;
    float* v = (float*)b;
    tmp.a = (int)a;
    tmp.b = v[0];
    tmp.c = v[1];
    tmp.d = v[2];
    FUN_00c3c810(self + 0x770, &tmp);
}

// @ 0x00c3dba0
void SP::cSPGameDataUFO::InitNPC(SP::cEmpire * param_2, int param_3)
{
    int param_2_v = (int)param_2;
    char* self = (char*)this;
    char* ctx = (char*)GetUniverseContext();
    char bUniv0 = (ctx == 0) ? 1 : 0;

    void* nm = NounManager();
    void* noun = FUN_00b20c60(nm, 0x2e72cae);
    char* npc;
    if (noun != 0) {
        typedef void* (__thiscall* M)(void*, int);
        npc = (char*)((M)(*(void**)(*(char**)noun + 0xc)))(noun, 0x2e71a5a);
    } else {
        npc = 0;
    }
    void* old = *(void**)(self + 0x7d8);
    if (npc != old) {
        if (npc != 0) {
            typedef void(__thiscall* A)(void*);
            ((A)(*(void**)(*(char**)npc + 0)))(npc);
        }
        *(char**)(self + 0x7d8) = npc;
        if (old != 0) {
            typedef void(__thiscall* R)(void*);
            ((R)(*(void**)(*(char**)old + 4)))(old);
        }
    }

    void* glob = g_168df68;
    float fA;
    if (*(int*)(self + 0x714) == 3) fA = *(float*)((char*)glob + 0x20);
    else                          fA = *(float*)((char*)glob + 0x1c);
    float fB = *(float*)((char*)glob + 0x24);

    char* sp34 = self + 0x34;
    void* sub = *(void**)sp34;
    typedef float(__thiscall* G)(void*);
    float rr = ((G)(*(void**)((char*)sub + 0x34)))(sp34);

    ((Fn3f160*)(*(void**)(self + 0x7d8)))->f(rr * fA);
    ((Fn3f1b0*)(*(void**)(self + 0x7d8)))->f(fB, 3.402823466e+38F);
    ((Fn3f2d0*)(*(void**)(self + 0x7d8)))->f(self);

    float radius;
    if (bUniv0) radius = 0.0f;
    else        radius = (float)FUN_00b7e4d0(PlanetModel());

    void* tune = GetSpaceCombatTuning();
    int level = param_2_v;
    if (level == -1) {
        void* empire = ctx;
        if (empire != 0) {
            level = FUN_00c317a0(empire);
        } else {
            if (GetSpaceCombatTuning() != 0 && FUN_01021240() != 0) {
                void* cities = (void*)(int)FUN_01021240();
                float* c = FUN_005c65e0(cities);
                float v0 = c[0], v1 = c[1], v2 = c[2];
                level = FUN_0102a360(GetSpaceCombatTuning(), &v0, &v1, &v2);
            } else {
                level = 0;
            }
        }
    }

    float hp = FUN_0102a630(tune, param_3, level);
    *(float*)(self + 0x534) = hp;
    *(float*)(self + 0x540) = hp;
    *(int*)(self + 0x7fc) = level;
    ((Fn385d0*)self)->f();

    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = gF_142eae0;
    v[3] = 0.0f;
    ((Fn3dae0*)self)->f(v);

    int t = *(int*)(self + 0x714) - 1;
    switch (t) {
    case 0:  // 0x00c3dd6e
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x6170e8b, param_3, self + 0x7a0);
        FUN_00c3a220(0x6170e8d, param_3, self + 0x794);
        *(uint8_t*)(self + 0x690) = 1;
        return;
    case 1:  // 0x00c3ddca
        *(float*)(self + 0x768) = (float)(FUN_0059da80(gF_13eecd8) + (double)radius) + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x578e8f0, param_3, self + 0x798);
        FUN_00c3a220(0x616df37, param_3, self + 0x79c);
        FUN_00c3a220(0x616df39, param_3, self + 0x7a0);
        FUN_00c3a220(0x578ec56, param_3, self + 0x794);
        return;
    case 2:  // 0x00c3de4f
        *(float*)(self + 0x768) = (float)(FUN_0059da80(gF_1473c70) + (double)radius) + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        {
            void* tool = FUN_00c463d0(self + 0x7a4);
            FUN_00b3d390((void*)0x168e0a4, tool);
        }
        return;
    case 3:  // 0x00c3dea6
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x578f417, param_3, self + 0x798);
        FUN_00c3a220(0x6170e66, param_3, self + 0x79c);
        FUN_00c3a220(0x6170e68, param_3, self + 0x7a0);
        FUN_00c3a220(0x6171707, param_3, self + 0x794);
        return;
    case 4:  // 0x00c3df1f
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        ((Fn3a2b0*)self)->f((int)ctx);
        return;
    case 5:  // 0x00c3df59
        {
            void* tool = FUN_00c463d0(self + 0x798);
            FUN_00b3d390((void*)0x168e230, tool);
        }
        return;
    case 6:  // 0x00c3df80
        if ((int)ctx == 2) *(int*)(self + 0x76c) = 2;
        ((Fn3a2b0*)self)->f((int)ctx);
        return;
    case 7:  // 0x00c3dfa1
        FUN_00c3a220(0x578e8f0, param_3, self + 0x798);
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        return;
    default:
        return;
    }
}

// @ 0x00c3e010
void UFO::func3e010(void* s)
{
    char* self = (char*)this;
    char* q = (char*)s;
    if (*(int*)(self + 0x714) == 0) {
        ((Fn455d60*)q)->append("== Player UFO ==", (const char*)0x146be9c);
    } else {
        ((Fn455d60*)q)->append("== NPC UFO ==", (const char*)0x146be89);
    }
    FUN_005f9450(q, (const char*)0x146be68, (double)*(float*)(self + 0x768));

    float hp = *(float*)(self + 0x540);
    void* sub = self + 0x508;
    typedef float(__thiscall* GetF)(void*);
    float maxf = ((GetF)(*(void**)(*(char**)sub + 0x58)))(sub);
    FUN_005f9450(q, (const char*)0x146be54, (double)hp, (double)maxf);

    FUN_00563de0(self + 0x780, q);
}

// @ 0x00c3e0b0
void SP::cSPGameDataUFO::Init(SP::eUFOType a, SP::cEmpire * empire)
{
    char* self = (char*)this;
    *(int*)(self + 0x714) = *(int*)&a;
    if (empire != 0) {
        char* e = (char*)empire;
        typedef void(__thiscall* Vf)(void*, void*);
        ((Vf)(*(void**)(*(char**)self + 0x48)))(self, *(void**)(e + 0x84));
        void* key = ((FnC326b0*)e)->f(1);
        ((FnC37180*)self)->f(key);
    }
    if (*(int*)(self + 0x714) == 0) {
        float h = ((FnFFd8e0*)FUN_00ffbe50())->f();
        *(float*)(self + 0x534) = h;
        *(float*)(self + 0x540) = h;
        float en = ((FnFFda80*)FUN_00ffbe50())->f();
        *(float*)(self + 0x7f8) = en;
        *(float*)(self + 0x7f4) = en;

        void* sub = self + 0x5e8;
        void* ms = FUN_0067dcc0();
        *(void**)(self + 0x804) = ms;
        *(void**)(self + 0x808) = sub;
        *(int*)(self + 0x80c) = 0x146bb58;
        *(int*)(self + 0x810) = 2;
        *(int*)(self + 0x814) = 0;
        if (ms != 0 && sub != 0) {
            unsigned int off = 0;
            do {
                typedef void(__thiscall* Vf)(void*, void*, void*);
                ((Vf)(*(void**)(*(char**)ms + 0x24)))(ms, sub, *(void**)(off + 0x146bb58));
                off += 4;
            } while (off < 8);
        }
        ((FnC43fe0*)(self + 0x34))->f((void*)0xb4c850);
        return;
    }
    ((Fn3dba0*)self)->f((int)empire, -1.0f);
    ((FnC43fe0*)(self + 0x34))->f((void*)0xb4c850);
}

// @ 0x0105c3d0
void FUN_0105c3d0(Vector3_s0105_b960* out, cSpaceToolData_s0105_b960* pTool, float t)
{
    float radius;
    int mode = *(int*)((char*)GetTriggerMgr() + 0x2c);
    if (mode == 1 || mode == 2) {
        float editorScale = FUN_00c70880(pTool) == 1 ? g_scale12 : g_scale6;
        radius = (t + 1.0f) * editorScale;
    } else {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_radius10);
        float* tuning = (float*)FUN_00c37360();
        float low = tuning[0x13c / 4];
        float probeA = FUN_01017030(1);
        const float& near = (low > probeA) ? low : probeA;
        float high = tuning[0x140 / 4];
        float probeB = FUN_01017070(1);
        const float& far = (probeB > high) ? probeB : high;
        float ratio = (base - near) / (far - near);
        float minScale = 0.0f;
        float maxScale = 1.0f;
        if (ratio < minScale)
            ratio = minScale;
        if (ratio > maxScale)
            ratio = maxScale;
        float mid = (tuning[0x138 / 4] - tuning[0x134 / 4]) * ratio + tuning[0x134 / 4];
        float scale;
        if (FUN_00c70880(pTool) == 1)
            scale = g_scale15;
        else if (FUN_00c71540(pTool))
            scale = g_scale2p4;
        else
            scale = g_scale6;
        radius = scale * mid;
    }
    out->z = g_upAxis.z * radius;
    out->y = g_upAxis.y * radius;
    out->x = g_upAxis.x * radius;
}

// @ 0x0105c5d0
void FUN_0105c5d0(Vector3_s0105_b960* out, cSpaceToolData_s0105_b960* pTool, float t)
{
    float radius;
    int mode = *(int*)((char*)GetTriggerMgr() + 0x2c);
    if (mode == 1 || mode == 2) {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_one);
        float scaled = g_ratio0p2 * base;
        const float& limit = (g_ratio0p5 > scaled) ? scaled : g_ratio0p5;
        radius = (t + 1.0f) * limit;
    } else {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_one);
        float* tuning = (float*)FUN_00c37360();
        float low = tuning[0x164 / 4];
        float probeA = FUN_01017030(2);
        const float& near = (low > probeA) ? low : probeA;
        float high = tuning[0x168 / 4];
        float probeB = FUN_01017070(2);
        const float& far = (probeB > high) ? probeB : high;
        float ratio = (base - near) / (far - near);
        float minScale = 0.0f;
        float maxScale = 1.0f;
        if (ratio < minScale)
            ratio = minScale;
        if (ratio > maxScale)
            ratio = maxScale;
        radius = (tuning[0x160 / 4] - tuning[0x15c / 4]) * ratio + tuning[0x15c / 4];
    }
    out->z = g_upAxis.z * radius;
    out->y = g_upAxis.y * radius;
    out->x = g_upAxis.x * radius;
}

// @ 0x0105c7e0
void FUN_0105c7e0(cSpaceShip* ship, const Vector3_s0105_b960& position, float extra)
{
    Vector3_s0105_b960 surface;
    const Vector3_s0105_b960* offset = PlanetModel_s0105_b960()->FUN_00b81630(&surface, position);
    float radius = Length(*offset) + extra;
    float reach = ship->GetReach();
    if (radius > reach) {
        ship->mRadius = radius;
        reach = radius;
    }
    float inv = 1.0f / Length(ship->mDirection);
    Vector3_s0105_b960 dir = ship->mDirection * inv;
    ship->mDirection.x = dir.x * reach;
    ship->mDirection.y = dir.y * reach;
    ship->mDirection.z = dir.z * reach;
}

// @ 0x0105c8d0
void __stdcall GetMaxHeight(cSPGameDataUFO_s0105_c8d0* o)
{
    float len = sqrtf(o->mPos.x * o->mPos.x + o->mPos.y * o->mPos.y + o->mPos.z * o->mPos.z);
    float cap = SteerConfig()->GetKinestheticBlend() + PlanetModel_s0105_c8d0()->FUN_b7e4d0();
    float ratio;
    if (o->mMode == 0) {
        cControllerHolder* holder = App_s0105_c8d0()->GetSimulator()->GetControllers();
        if (holder) {
            cSPSpacePlanetCameraController* ctl = holder->FindController(0x303154cd);
            if (ctl) {
                float wheel = ctl->GetMouseWheelSpeed();
                if (wheel < len) {
                    ratio = wheel / len;
                    goto apply;
                }
                return;
            }
        }
    }
    if (!(len > cap))
        return;
    ratio = cap / len;
apply:
    {
        o->mPos.x = o->mPos.x * ratio;
        o->mPos.y = o->mPos.y * ratio;
        o->mPos.z = o->mPos.z * ratio;
    }
}

// @ 0x0105c9d0
void __stdcall FUN_0105c9d0(cSteered* o, const Vector3_s0105_c8d0* a2, const Vector3_s0105_c8d0* a3, float a4)
{
    const Vector3_s0105_c8d0* c = o->mAnchor.GetPosition();
    Vector3_s0105_c8d0 pos = o->mPos;
    float iu = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3_s0105_c8d0 up(pos.x * iu, pos.y * iu, pos.z * iu);
    Vector3_s0105_c8d0 d(pos.x - c->x, pos.y - c->y, pos.z - c->z);
    float speed = sqrtf(o->mVel.x * o->mVel.x + o->mVel.y * o->mVel.y + o->mVel.z * o->mVel.z);
    float dl = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    float delta = dl - sqrtf(a2->x * a2->x + a2->y * a2->y + a2->z * a2->z);
    float id = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
    o->mPos.x = a2->x + (c->x + (id * d.x) * delta);
    o->mPos.y = a2->y + (c->y + (id * d.y) * delta);
    o->mPos.z = a2->z + (c->z + (id * d.z) * delta);

    float blend = SteerConfig()->GetBlend();
    float damp = SteerConfig()->GetDamping();
    float k = fabsf(o->mVel.x * a3->x + o->mVel.z * a3->z + o->mVel.y * a3->y) * (blend + 1.0f);
    Vector3_s0105_c8d0 t(a3->x * k, a3->y * k, a3->z * k);
    o->mPush.y += t.y * kCoupling;
    o->mPush.x += t.x * kCoupling;
    o->mPush.z += t.z * kCoupling;
    Vector3_s0105_c8d0 nv(t.x + o->mVel.x, o->mVel.y + t.y, o->mVel.z + t.z);
    if (nv.z * nv.z + nv.y * nv.y + nv.x * nv.x < 1.52587890625e-05f)
        nv = up;

    Vector3_s0105_c8d0 heading;
    const Vector3_s0105_c8d0* h;
    if (speed > 1.52587890625e-05f) {
        float vx = o->mVel.x, vy = o->mVel.y, vz = o->mVel.z;
        float iv = 1.0f / sqrtf(vz * vz + vy * vy + vx * vx + 1e-8f);
        heading = Vector3_s0105_c8d0(iv * vx, iv * vy, iv * vz);
        h = &heading;
    } else {
        h = &up;
    }
    float dot = (h->z * a3->z + h->y * a3->y) + h->x * a3->x;
    float blendDot = dot + 1.0f;
    float in = 1.0f / sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z + 1e-8f);
    Vector3_s0105_c8d0 nd(in * nv.x, nv.y * in, in * nv.z);
    if (blendDot <= 0.0f)
        blendDot = 0.0f;
    if (1.0f <= blendDot)
        blendDot = 1.0f;
    const float* sp = &speed;
    if (speed <= kMinSpeed)
        sp = &kMinSpeed;
    float nspeed = *sp * ((1.0f - damp) * blendDot + damp);
    o->mVel.x = nd.x * nspeed;
    o->mVel.y = nd.y * nspeed;
    o->mVel.z = nd.z * nspeed;

    float len;
    bool reaim = true;
    if (!o->mbTargetValid && !(dot < kHeadingDot)) {
        Vector3_s0105_c8d0 tg(o->mTarget.x - pos.x, o->mTarget.y - pos.y, o->mTarget.z - pos.z);
        float tl = sqrtf(tg.y * tg.y + tg.z * tg.z + tg.x * tg.x);
        if (!(tl < kRetargetDist)) {
            Vector3_s0105_c8d0 dir = normalized_safe(tg);
            const Vector3_s0105_c8d0& aim = normalized_safe(*a2);
            if (!((aim.y * dir.y + aim.z * dir.z) + dir.x * aim.x < kDirDot))
                reaim = false;
        }
    }
    if (reaim) {
        float l2 = a2->x * a2->x + a2->y * a2->y + a2->z * a2->z;
        float lead = sqrtf(l2) + kLead;
        float il = 1.0f / sqrtf(l2 + 1e-8f);
        o->mTarget.x = (a2->x * il) * lead + pos.x;
        o->mTarget.y = (a2->y * il) * lead + pos.y;
        o->mTarget.z = (a2->z * il) * lead + pos.z;
        o->mbTargetValid = 0;
        o->mTimerA.Stop();
        o->mb624 = 0;
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        o->SetTargetDist(len);
    } else {
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        if (len > o->GetTargetDist())
            o->SetTargetDist(len);
    }
    o->mTimerB.Restart();
    float f = o->GetFollowDist();
    float ia = 1.0f / sqrtf(a2->z * a2->z + (a2->y * a2->y + a2->x * a2->x) + 1e-8f);
    Vector3_s0105_c8d0 np(o->mPos.x - (a2->x * ia) * f, o->mPos.y - (a2->y * ia) * f, o->mPos.z - (a2->z * ia) * f);
    o->SetFollow(a4, &np);
}

// @ 0x0105d180
void* __fastcall FUN_0105d180(cSummarizerD180* s)
{
    s->mBaseVt = g_vtCVS;
    s->mField0C = 0;
    s->mClassVt = g_vtD180Class;
    s->mBaseVt = g_vtD180Base;
    s->mExtents.x = kDefaultSummarizerExtents.x;
    s->mExtents.y = kDefaultSummarizerExtents.y;
    s->mExtents.z = kDefaultSummarizerExtents.z;
    return s;
}

// @ 0x0105d1d0
void* __fastcall FUN_0105d1d0(cSummarizerD1D0* s)
{
    s->mBaseVt = g_vtCVS;
    s->mField0C = 0;
    s->mClassVt = g_vtD1D0Class;
    s->mBaseVt = g_vtD180Base;
    return s;
}

// @ 0x0105d200
void __stdcall UpdateWarpMode(cSPGameDataUFO_s0105_c8d0* ufo, const Vector3_s0105_c8d0* dest)
{
    cSteerConfig* cfg = SteerConfig();

    if (!cfg->mbGalaxyWarpEnabled) {
        if (ufo->mWarpState == 0) {
            ufo->mWarpState = ufo->CanWarp() ? 3 : 1;
            return;
        }
        if (ufo->mMode == 0 && ufo->mWarpSpeed <= 0.0f)
            ufo->mWarpState = 1;
        return;
    }

    cSPPlayerInventory* inv = GetUFOSimulator_s0105_c8d0()->GetPlayerInventory();
    if (ufo->mMode == 3 && inv->mWarpMode != 1 &&
        (ufo->mWarpState == 1 || ufo->mWarpState == 4))
        ufo->mWarpState = 0;

    if (ufo->mWarpState == 4) {
        float reach = cfg->GetGalaxyWarpMultiplier(4, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
        float ms = (Distance(ufo->mPos, *dest) / reach) * kMsToSeconds;
        float warpTime = cfg->GetGalaxyWarpTime(4, ufo->mMode, 0.0f);
        if (ms > warpTime * 2.0f)
            ufo->mWarpState = 0;
    }

    if (ufo->mWarpState == 0) {
        ufo->mWarpState = 1;
        if (ufo->CanWarp()) {
            ufo->mWarpDaemon.StartWarp();
            float dist = Distance(ufo->mPos, *dest);
            float plump = cfg->mGalaxyMaxPlumpDistance;
            float m1 = cfg->GetGalaxyWarpMultiplier(1, ufo->mMode) * plump;
            float m3 = cfg->GetGalaxyWarpMultiplier(3, ufo->mMode) * plump;
            float travel = GetUFOSimulator_s0105_c8d0()->GetMaxTravelDistance();
            float warpTime = cfg->GetGalaxyWarpTime(2, ufo->mMode, dist / travel);
            if ((dist / m3) * kMsToSeconds + warpTime < (dist / m1) * kMsToSeconds) {
                ufo->mWarpState = 2;
                ufo->mWarpClock.Restart();
            }
        }
    }

    if (ufo->mWarpState == 2) {
        if (!ufo->mWarpClock.IsRunning())
            ufo->mWarpClock.Restart();
        float elapsed = (float)ufo->mWarpClock.GetElapsedTime() * kMsToSeconds;
        float dist = Distance(ufo->mPos, *dest);
        float travel = GetUFOSimulator_s0105_c8d0()->GetMaxTravelDistance();
        float warpTime = cfg->GetGalaxyWarpTime(2, ufo->mMode, dist / travel);
        if (elapsed > warpTime) {
            Vector3_s0105_c8d0 axisTmp;
            const Vector3_s0105_c8d0* axis = RotateByQuat(&axisTmp, &g_warpAxisKey, &ufo->mMaterial);
            Vector3_s0105_c8d0 toDest(dest->x - ufo->mPos.x, dest->y - ufo->mPos.y, dest->z - ufo->mPos.z);
            Vector3_s0105_c8d0 dir = normalized_safe(toDest);
            if (kWarpFacingThreshold < dir.x * axis->x + dir.y * axis->y + dir.z * axis->z) {
                ufo->mWarpState = 3;
                float reach = cfg->GetGalaxyWarpMultiplier(3, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
                float len = Length_s0105_c8d0(ufo->mVel);
                if (len > kMinWarpExtent) {
                    float s = reach / len;
                    ufo->mVel.x = ufo->mVel.x * s;
                    ufo->mVel.y = ufo->mVel.y * s;
                    ufo->mVel.z = ufo->mVel.z * s;
                }
            }
        }
        return;
    }

    if (ufo->mWarpState == 3) {
        float reach = cfg->GetGalaxyWarpMultiplier(4, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
        float ms = (Distance(ufo->mPos, *dest) / reach) * kMsToSeconds;
        float warpTime = cfg->GetGalaxyWarpTime(4, ufo->mMode, 0.0f);
        if (!(ms < warpTime))
            return;
        ufo->mWarpState = 4;
        float len = Length_s0105_c8d0(ufo->mVel);
        if (len > kMinWarpExtent) {
            float s = reach / len;
            ufo->mVel.x = ufo->mVel.x * s;
            ufo->mVel.y = ufo->mVel.y * s;
            ufo->mVel.z = ufo->mVel.z * s;
        }
        ufo->mWarpClock.Clear();
    }
}
