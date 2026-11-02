// src/game/SPGonzago/SPSpaceGfx.cpp -- migrated from slice(s) s01035900, s01033de0, s010377f0, s01036830 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceGfx.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cMWModel.h"
#include "SP/cViewer.h"
#include "SP/cCivData.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTradeRouteData.h"
#include "SP/cVarListSerializer.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "EA/Variant.h"
#include "SP/cSolarSystem.h"
#include <math.h>
#include "SP/cSPEditorPhysicsWorld.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_01021230();                       // 0x01021230  effect owner (this)
extern const float kOne;              // 0x01485720  1.0f
extern const float kColorScale;       // 0x013eecd4  1/255
extern const float kGalaxyOffsetA; // 0x016df3a8
extern const float kGalaxyOffsetB; // 0x016df3ac
extern const float kGalaxyOffsetC; // 0x016df3b0
extern const float kThresh144;     // 0x014998fc  144.0f
extern const float kThresh500;     // 0x01465544  500.0f
extern const float kPickA;  // 0x016df344
extern const float kPickB;  // 0x016df348
extern const float kPickC;  // 0x016df34c
extern const float kViewAngle;                         // 0x014998d4

// ---- items of slice s01036830 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct Vec3 { float x, y, z; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& src);              // 0x0041cb40
};
struct Transform {
    uint16_t mFlags;                          // +0x00
    uint16_t mnChangeCount;                   // +0x02
    Vec3     mPosition;                       // +0x04
    float    mfScale;                         // +0x10
    Matrix3  mOrientation;                    // +0x14
};
namespace EA {
namespace Swarm {
class cIVisualEffect_s0103_6830 {
public:
    virtual int  AddRef();                             // +0x00
    virtual int  Release();                            // +0x04
    virtual bool Start(int flags);                     // +0x08
    virtual bool Stop(int flags);                      // +0x0c
    virtual void _v10();                               // +0x10
    virtual void SetTransform(const ::Transform& xform); // +0x14
};
}
}
class cIVisualEffectBig {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
    virtual bool _v10b();                              // +0x10
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
    virtual void _v40();
    virtual void Apply(int a, void* p, int b);         // +0x44
};
struct cEffectsManager {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
    virtual void ReleaseEffect(uint32_t id);           // +0x50
};
struct RBNode;
struct ColonyMap {
    uint32_t mu00;       // +0x00
    void*    mpHead;     // +0x04
    void*    mpBegin;    // +0x08
    void*    mpRoot;     // +0x0c
    uint8_t  mb10;       // +0x10
    uint8_t  pad11[3];
    void*    mp14;       // +0x14
    void DoNukeSubtree(RBNode* pNode);   // 0x01036fc0
};
class cSPSpaceGfx {
public:
    // base cGonzagoSubsystem: IUnknown32 (AddRef/Release/QueryInterface) + cIGonzagoSubsystem vtable.
    virtual int  AddRef();                             // +0x00 (slot 1)
    virtual int  Release();                            // +0x04 (slot 2)
    virtual ~cSPSpaceGfx();                            // 0x01037030

    // cGonzagoSubsystem base data (vptr + 0x18 bytes of base state).
    uint8_t mBaseData[0x18];                           // +0x04

    void SetEffectEnabled(char enable);                // 0x01036830
    void UpdateSpaceColor(float x, float y, float z);  // 0x01036940
    void SetEffectTransform(Vec3 position);            // 0x01036d30
    void ShutdownForGame();                            // 0x010372b0
    void AllianceGraphCreate();                        // 0x01037700

    // AutoRefCount<EA::Swarm::cIVisualEffect> galaxy effects
    void* mpGalaxyCrossfadeEffect;                     // +0x1c
    void* mpGalaxyEffect;                              // +0x20
    void* mpGalaxyScreenEffect;                        // +0x24
    void* mpGalaxyAmbienceEffect;                      // +0x28
    void* mpGalaxyBackgroundGalaxies;                  // +0x2c
    void* mpTravelLineEffect;                          // +0x30
    void* mpSporepediaPlotPathEffect;                  // +0x34
    void* mpTravelLineStar;                            // +0x38
    ColonyMap mColonyModelMap;                         // +0x3c
    uint8_t pad54[4];                                  // +0x54
    bool  mbAllianceMapVisible;                        // +0x58
    bool  mbColonyMapIsDirty;                          // +0x59
    uint8_t pad5a[2];                                  // +0x5a
    void* mpPlanetScreenEffect;                        // +0x5c
    void* mpLavaPlanetScreenEffect;                    // +0x60
    void* mpSkyboxEffect;                              // +0x64
    void* mpSolarScreenEffect;                         // +0x68
    void* mpSolarClouds;                               // +0x6c
    void* mpSolarLoopbox;                              // +0x70
    void* mpSolarBackgroundEffect;                     // +0x74
    void* mpSolarBackgroundDustEffect;                 // +0x78
    void* mpPlanetBackgroundEffect;                    // +0x7c
    void* mpPlanetBackgroundDustEffect;                // +0x80
    void* mpSolarComets;                               // +0x84
    void* mpMeaningOfLifeEffect;                       // +0x88
    void* mpRingEffect;                                // +0x8c
    void* mpSolarEffectsWorld;                         // +0x90
    void* mpTrailEffectsWorld;                         // +0x94
    void* mpPtolemaicEffectsWorld;                     // +0x98
    void* mpPtolemaicEffectsRenderer;                  // +0x9c
    void* mpSolarBackgroundEffectsWorld;               // +0xa0
    void* mpSolarBackgroundRenderer;                   // +0xa4
    void* mpEffectA8;                                  // +0xa8
    void* mpGalaxyEffectsWorld;                        // +0xac
    void* mpMoneyEffectPlanet;                         // +0xb0
    void* mpMoneyEffectUFO;                            // +0xb4
    void* mpEffectB8;                                  // +0xb8
    void* mpEffectBC;                                  // +0xbc
    void* mpEffectC0;                                  // +0xc0
    void* mpEffectC4;                                  // +0xc4
    uint8_t mTimerC8[0x38];                            // +0xc8  SP::cGonzagoTimer
    bool  mb100;                                       // +0x100
    uint8_t pad101[0x0f];                              // +0x101
    Vec3  mSpaceColor;                                 // +0x110
    Vec3  mPrevColor;                                  // +0x11c
    int   mn128;                                       // +0x128
    uint8_t pad12c[0x10];                              // +0x12c
    void* mp13c;                                       // +0x13c
};
extern "C" void* FUN_01021230();                       // 0x01021230  effect owner (this)
extern "C" Vec3* FUN_00c8b360(void* p);                 // 0x00c8b360  return &p->mPosition
void* GetSpaceGfx();                                   // 0x00b3d470  SP::cSPSpaceGfx::Get()
void* GetSpaceGfx2();                                  // 0x00b3d240
cEffectsManager* EffectsManagerPtr();                  // 0x0067ddd0  SP::EffectsManager()
void* SpaceApp();                                      // 0x0067dd10  SP::App
void* GetResourceManager();                            // 0x0067dcd0  EA::ResourceMan::GetManager
void* RBTreeIncrement(void* pNode);                    // 0x00921580
void* operator_delete_array(void* p);                  // 0x00f47380
void Matrix3Assign(Matrix3& dst, const void* src);     // 0x0041cb40
float FUN_01036610(uint32_t param);                    // 0x01036610
void  FUN_010367e0(void* p, int flag);                 // 0x010367e0
void  TimerOwnerDtor(void* p);                         // 0x00af1430  ?Dtor@TimerOwner
void  FUN_007c3ba0(void* p);                           // 0x007c3ba0
void  SetViewAngle(float angle);                       // 0x007c5350  cViewer::SetViewAngle
void  FUN_007c46f0(void* a, void* b);                  // 0x007c46f0
int   FUN_00c6ff90(void* p);                           // 0x00c6ff90
extern const float kOne;              // 0x01485720  1.0f
extern const float kColorScale;       // 0x013eecd4  1/255
extern const Matrix3 kIdentityMatrix;  // 0x016df384
extern const float kGalaxyOffsetA; // 0x016df3a8
extern const float kGalaxyOffsetB; // 0x016df3ac
extern const float kGalaxyOffsetC; // 0x016df3b0
extern const float kThresh144;     // 0x014998fc  144.0f
extern const float kThresh500;     // 0x01465544  500.0f
extern const float kPickA;  // 0x016df344
extern const float kPickB;  // 0x016df348
extern const float kPickC;  // 0x016df34c
struct ResourceManKey {
    uint32_t mId;        // +0x00
    uint32_t mType;      // +0x04
    uint32_t mOwner;     // +0x08
};
struct ResourceManager {
virtual void _v00();
virtual void _v04();
virtual void _v08();
    virtual bool Find(ResourceManKey* pKey, void** ppOut,
                      uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // +0x0c
};
struct ColorResource {
    uint8_t pad00[0x1c];
    int   mWidth;        // +0x1c
    int   mHeight;       // +0x20
    uint8_t* mpData;     // +0x28
};
struct cEffectByName {                                  // slots 0x10 / 0x18 / 0x40
    virtual void _v00();
    virtual int  _v04release();                        // +0x04
    virtual void _v08start(int flags);                 // +0x08
    virtual void _v0c();
    virtual bool _v10b();                              // +0x10
    virtual void _v14SetTransform(void* xform);        // +0x14
    virtual void ApplyByName(void* name);              // +0x18
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
    virtual void _v3c();
    virtual void SetEffectIndexed(int a, void* b);     // +0x40
};
struct cEffectByKey {                                  // slot 0x2c -> returns a Vector3
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    virtual Vec3* GetPosition();                       // +0x2c
};
struct cEffect34 {                                     // slot 0x2c -> Vector3
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    virtual Vec3* GetPosition(int index);              // +0x2c
};
struct cEffectC0 {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
    virtual void _v30();
    void* mp34;                                        // +0x34
};
class cSPSimulatorSpaceGame {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
    void SolarContextFinishActivate(float value, char active);  // 0x01036c20
    int   mpSelectedBuilding;                          // +0x5c
    uint8_t pad60[0x1c];                               // +0x60
    void* mpHighLODPlanetSim;                          // +0x7c
    uint8_t pad80[0x24];                               // +0x80
    void* mpCivTransitionMiniGame;                     // +0xa4
};
struct cIVisualEffectHost {
    virtual void _v00();
    virtual int  _v04release();                        // +0x04
    virtual void _v08();
    virtual int  _v0cstop(int arg);                    // +0x0c
};
struct cMiniGame {                                     // slot 0x08 takes (int,int,void**)
virtual void _v00();
virtual void _v04();
    virtual void Switch(int a, int b, void** ppOut);    // +0x08
};
struct cFound {
virtual void _v00();
virtual void _v04();
virtual void _v08();
    virtual void* FindName(uint32_t name);             // +0x0c
};
struct cSearchElem {
    uint8_t pad00[0x64];
    cFound* mp64;                                      // +0x64
};
struct cSearchSource {                                 // FUN_00b3d240 result
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
    virtual void _v30();
    virtual void Collect(cSearchElem*** ppBegin, cSearchElem*** ppEnd, int a, int b); // +0x34
    virtual void GetProbe(Vec3* pOut, int a, Vec3 in); // +0x38
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
    virtual void _v6c();
    virtual cSearchSource* GetInner();                 // +0x70
};
struct cMWModel {
    PV16 PV16 PV16 PV16 PV16 PV8 PV4
    uint32_t mu04;                                     // +0x04
    uint8_t  pad08[0x38];                              // +0x08
    int  mRefCount;                                    // +0x40
    virtual void Destroy(int flags);                   // +0x170
};
struct RBNode {
    RBNode*  mpLeft;      // +0x00
    RBNode*  mpRight;     // +0x04
    RBNode*  mpParent;    // +0x08
    uint8_t  mbColor;     // +0x0c
    uint8_t  pad0d[3];    // +0x0d
    uint32_t mu10;        // +0x10
    cMWModel* mpValue;    // +0x14  AutoRefCount<SP::cMWModel>
};
struct cEffectFull {
virtual void _v00();
virtual void _v04();
virtual void _v08();
    virtual void _v0cStop(int arg);                    // +0x0c
    PV16 PV8 PV2 PV                                     // slots 4..30
    virtual void _v7c();                               // +0x7c
    PV16 PV16 PV16 PV8 PV2 PV                           // slots 32..90
    virtual void _v16c(int arg);                       // +0x16c
};
struct cApp {
    PV16 PV4
    virtual void* GetSubSystem();                      // +0x50
};
struct cViewer {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
    virtual void SetViewAngle(float angle);            // (method, 0x007c5350)
};
struct cModelNodeValue {
    uint8_t pad00[0x58];
    float   mf58;                                      // +0x58
};
extern const float kViewAngle;                         // 0x014998d4
struct cSubSys {
    PV4 PV2
    virtual void* GetViewer();                         // +0x1c
};
// ---- items of slice s01036830 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" Vec3* FUN_00c8b360(void* p);                 // 0x00c8b360  return &p->mPosition
extern const Matrix3 kIdentityMatrix;  // 0x016df384

// ---- items of slice s010377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gSpaceFadeDelay;           // 0x0149996c
extern const void* gImpostorTimer;      // 0x015b77b4
extern const void* gSpaceGfxTimerId;    // 0x016df344
class cGonzagoSubsystem {
public:
    void Construct();                                           // 0x00b5b960
};
class cSpaceTimerOwner {
public:
    void AddTimer(const void* pTimerId, const void* pEventId,
                  float fDelay, int nFlags);                    // 0x00a6c9f0
};
class cPlanetSubsystem {
public:
    cSpaceTimerOwner* GetTimerOwner();                          // 0x008414c0
};
class cTimerOwner {
public:
    void* Construct();                                          // 0x00af14b0
};
int cSPLivingUniverse_GetUniverseContext();                     // 0x01021080
void* cSPLivingUniverse_GetActivePlanet();                      // 0x01021260
void SpaceGfx_UpdateAudio0();                                   // 0x00c2e4e0
void SpaceGfx_UpdateAudioN(int nMode, uint32_t nA, uint32_t nB); // 0x00c2e4e0
void SpaceGfx_UpdateGroup1();                                   // 0x01036af0
void SpaceGfx_UpdateGroup2();                                   // 0x01037760
void SpaceGfx_UpdateGroup3(void* pThis, int nArg);              // 0x01034d40
extern uint8_t gSpaceAudioEnabled0;     // 0x016e06de
extern uint8_t gSpaceAudioEnabled1;     // 0x016e06e1
extern uint8_t gSpaceAudioEnabled2;     // 0x016e06e2
extern uint8_t gSpaceAudioEnabled3;     // 0x016e06e3
extern uint32_t gSpaceAudioParam0;      // 0x016e06e4
extern uint32_t gSpaceAudioParam1;      // 0x016e06e8
struct cIntrusiveLink {
    void* mp0;                          // 0x00
    void* mp4;                          // 0x04
    void* mp8;                          // 0x08
    void* mpc;                          // 0x0c
};
class cSPSpaceGfx_s0103_77f0 : public cGonzagoSubsystem {
public:
    cSPSpaceGfx_s0103_77f0();
    void UpdateForSpaceGame(int nArg);                          // 0x010377f0

    void* mpVtable;                     // 0x000
    void* mpVtable2;                    // 0x004
    uint8_t mPad008[0x14];              // 0x008
    uint32_t mUnk1c;                    // 0x01c
    uint32_t mUnk20;                    // 0x020
    uint32_t mUnk24;                    // 0x024
    uint32_t mUnk28;                    // 0x028
    uint32_t mUnk2c;                    // 0x02c
    uint32_t mUnk30;                    // 0x030
    uint32_t mUnk34;                    // 0x034
    uint32_t mUnk38;                    // 0x038
    uint8_t mPad03c[0x04];              // 0x03c
    cIntrusiveLink mUnk40;              // 0x040
    uint32_t mUnk50;                    // 0x050
    uint8_t mPad054[0x04];              // 0x054
    uint8_t mUnk58;                     // 0x058
    uint8_t mUnk59;                     // 0x059
    uint8_t mPad05a[0x02];              // 0x05a
    uint32_t mUnk5c;                    // 0x05c
    uint32_t mUnk60;                    // 0x060
    uint32_t mUnk64;                    // 0x064
    uint32_t mUnk68;                    // 0x068
    uint32_t mUnk6c;                    // 0x06c
    uint32_t mUnk70;                    // 0x070
    uint32_t mUnk74;                    // 0x074
    uint32_t mUnk78;                    // 0x078
    uint32_t mUnk7c;                    // 0x07c
    uint32_t mUnk80;                    // 0x080
    uint32_t mUnk84;                    // 0x084
    uint32_t mUnk88;                    // 0x088
    uint32_t mUnk8c;                    // 0x08c
    uint32_t mUnk90;                    // 0x090
    uint32_t mUnk94;                    // 0x094
    uint32_t mUnk98;                    // 0x098
    uint32_t mUnk9c;                    // 0x09c
    uint32_t mUnkA0;                    // 0x0a0
    uint32_t mUnkA4;                    // 0x0a4
    uint32_t mUnkA8;                    // 0x0a8
    uint32_t mUnkAc;                    // 0x0ac
    uint32_t mUnkB0;                    // 0x0b0
    uint32_t mUnkB4;                    // 0x0b4
    uint32_t mUnkB8;                    // 0x0b8
    uint32_t mUnkBC;                    // 0x0bc
    uint32_t mUnkC0;                    // 0x0c0
    uint32_t mUnkC4;                    // 0x0c4
    cTimerOwner mTimer;                 // 0x0c8
    uint8_t mUnk100;                    // 0x100
    uint8_t mPad101[0x3b];              // 0x101
    uint32_t mUnk13c;                   // 0x13c
};
// ---- items of slice s010377f0 end

// ---- items of slice s01033de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s0103_3de0(n) virtual void pv##n();
#define G_FACTOR_TABLE   ((float*)0x016df330)      // +0x000 4 per-behaviour float factors
#define G_TUNE_VARIANTS  ((TuningVariant*)0x016df3d8)  // +0x000 4 tuning variants, 0x14 bytes each
struct Iface {                                  // reference-counted interface (+0x00 vtable)
    PV_s0103_3de0(0)
    virtual void pv1();                         // +0x04  Release
    virtual void pv2(int value);                // +0x08
    virtual void pv3(int value);                // +0x0c
    virtual bool pv4();                         // +0x10
};
struct ObjA0 {                                  // object looked up at +0xa0
    PV_s0103_3de0(0) PV_s0103_3de0(1) PV_s0103_3de0(2) PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8) PV_s0103_3de0(9)
    PV_s0103_3de0(10) PV_s0103_3de0(11) PV_s0103_3de0(12) PV_s0103_3de0(13) PV_s0103_3de0(14) PV_s0103_3de0(15) PV_s0103_3de0(16) PV_s0103_3de0(17) PV_s0103_3de0(18) PV_s0103_3de0(19)
    PV_s0103_3de0(20) PV_s0103_3de0(21) PV_s0103_3de0(22) PV_s0103_3de0(23) PV_s0103_3de0(24) PV_s0103_3de0(25) PV_s0103_3de0(26) PV_s0103_3de0(27) PV_s0103_3de0(28) PV_s0103_3de0(29)
    PV_s0103_3de0(30) PV_s0103_3de0(31) PV_s0103_3de0(32)
    virtual void pv33(void* name, uint32_t value);   // +0x84
};
struct TuningVariant {                          // EA::Variant, 0x14 bytes
    uint8_t mPad00[0x14];
    void Set(uint32_t value);                   // 0x00542b80
};
struct TuningSource {                           // object pointed at by +0x13c
    PV_s0103_3de0(0) PV_s0103_3de0(1) PV_s0103_3de0(2) PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8)
    virtual bool pv9(uint32_t key, void** out); // +0x24
    virtual uint32_t pv10(uint32_t value);      // +0x28
};
struct Entry {                                  // record returned through TuningSource::pv9
    union { void* mPtr; float mFloat; };        // +0x00
    uint8_t  mPad04[0x10 - 4];
    uint8_t  mFlags;                            // +0x10
    uint8_t  mPad11;
    uint16_t mType;                             // +0x12
};
struct Loco {                                   // locomotion sub-object
    PV_s0103_3de0(0) PV_s0103_3de0(1) PV_s0103_3de0(2) PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8) PV_s0103_3de0(9) PV_s0103_3de0(10)
    virtual Vec3* pv11();                       // +0x2c  GetPosition
    PV_s0103_3de0(12) PV_s0103_3de0(13)
    virtual void pv14(const Vec3* pos);         // +0x38
    void FUN_c41d60(void* str);                 // 0x00c41d60
    void FUN_c41d90(void* str);                 // 0x00c41d90
};
struct Queryable {                              // object returned by the behaviour's vt+0x58 slot
    PV_s0103_3de0(0) PV_s0103_3de0(1)
    virtual Queryable* pv2(uint32_t tag);       // +0x08
    PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8) PV_s0103_3de0(9) PV_s0103_3de0(10) PV_s0103_3de0(11) PV_s0103_3de0(12) PV_s0103_3de0(13) PV_s0103_3de0(14) PV_s0103_3de0(15)
    PV_s0103_3de0(16) PV_s0103_3de0(17) PV_s0103_3de0(18) PV_s0103_3de0(19) PV_s0103_3de0(20)
    virtual void pv21();                        // +0x54
    PV_s0103_3de0(22) PV_s0103_3de0(23) PV_s0103_3de0(24) PV_s0103_3de0(25) PV_s0103_3de0(26) PV_s0103_3de0(27) PV_s0103_3de0(28) PV_s0103_3de0(29) PV_s0103_3de0(30) PV_s0103_3de0(31)
    PV_s0103_3de0(32) PV_s0103_3de0(33) PV_s0103_3de0(34) PV_s0103_3de0(35) PV_s0103_3de0(36) PV_s0103_3de0(37) PV_s0103_3de0(38) PV_s0103_3de0(39) PV_s0103_3de0(40) PV_s0103_3de0(41)
    PV_s0103_3de0(42) PV_s0103_3de0(43) PV_s0103_3de0(44) PV_s0103_3de0(45) PV_s0103_3de0(46) PV_s0103_3de0(47) PV_s0103_3de0(48) PV_s0103_3de0(49)
    virtual void pv50(int value);               // +0xc8
    uint8_t mPad04_to_c0[0xc0 - 0x04];
    Loco    mLoco;                              // +0xc0 (embedded sub-object)
    uint8_t mPadC4[0x130 - 0xc4];
    uint8_t mFlag130;                           // +0x130
};
struct AgentRefChunk;                           // blocks of the agent reference table
struct AgentRefEntry {                          // 8-byte entry inside a block
    void*    mAgent;                            // +0x00
    uint32_t mType;                             // +0x04
};
struct AgentRefChunk {
    uint32_t      mCount;                       // +0x00
    AgentRefEntry mEntries[1];                  // +0x04
};
struct AgentRef {                               // argument of RemoveAgent
    AgentRefChunk** mChunks;                    // +0x00
};
struct RemoveArgs {                             // 0x18-byte argument block of cInteraction::RemoveAgent
    void*    mRef;                              // +0x00
    uint32_t mIndex;                            // +0x04
    int32_t  mA;                                // +0x08
    int32_t  mB;                                // +0x0c
    int32_t  mC;                                // +0x10
    int32_t  mD;                                // +0x14
};
struct IfaceBank {                              // interface bank used by FUN_01034950's subject
    uint8_t  mPad00[0x60];
    Iface*   mIface60;                          // +0x60
    Iface*   mIface64;                          // +0x64
    Iface*   mIface68;                          // +0x68
    Iface*   mIface6C;                          // +0x6c
    Iface*   mIface70;                          // +0x70
    Iface*   mIface74;                          // +0x74
    Iface*   mIface78;                          // +0x78
    Iface*   mIface7C;                          // +0x7c
    Iface*   mIface80;                          // +0x80
    Iface*   mIface84;                          // +0x84
    Iface*   mIface88;                          // +0x88
    Iface*   mIface8C;                          // +0x8c
    Iface*   mIface90;                          // +0x90
    Iface*   mIface94;                          // +0x94
    Iface*   mIface98;                          // +0x98
    uint8_t  mPad9C[0x110 - 0x9c];
    Vec3     mVec110;                           // +0x110
};
struct Iface44 {                                // +0x80 sub-object, slot 0x44 method
    PV_s0103_3de0(0) PV_s0103_3de0(1) PV_s0103_3de0(2) PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8) PV_s0103_3de0(9) PV_s0103_3de0(10) PV_s0103_3de0(11)
    PV_s0103_3de0(12) PV_s0103_3de0(13) PV_s0103_3de0(14) PV_s0103_3de0(15) PV_s0103_3de0(16)
    virtual void pv17(int mode, const Vec3* value, int count);   // +0x44
};
struct Behavior {                               // large behaviour/editor subject
    PV_s0103_3de0(0) PV_s0103_3de0(1) PV_s0103_3de0(2) PV_s0103_3de0(3) PV_s0103_3de0(4) PV_s0103_3de0(5) PV_s0103_3de0(6) PV_s0103_3de0(7) PV_s0103_3de0(8) PV_s0103_3de0(9)
    PV_s0103_3de0(10) PV_s0103_3de0(11) PV_s0103_3de0(12) PV_s0103_3de0(13) PV_s0103_3de0(14) PV_s0103_3de0(15) PV_s0103_3de0(16) PV_s0103_3de0(17) PV_s0103_3de0(18) PV_s0103_3de0(19)
    PV_s0103_3de0(20) PV_s0103_3de0(21)
    virtual Queryable* pv22();                  // +0x58

    uint32_t mVt4;                              // +0x04
    uint8_t  mPad08[0x60 - 0x08];
    Iface*   mIface60;                          // +0x60
    Iface*   mIface64;                          // +0x64
    Iface*   mIface68;                          // +0x68
    uint8_t  mPad6C[0x74 - 0x6c];
    int32_t  m74;                               // +0x74
    uint8_t  mPad78[0x90 - 0x78];
    Iface*   mIface90;                          // +0x90
    uint8_t  mPad94[0x98 - 0x94];
    int32_t  m98;                               // +0x98
    uint8_t  mPad9C[0xa0 - 0x9c];
    ObjA0*   mObjA0;                            // +0xa0
    uint8_t  mPadA4[0x130 - 0xa4];
    uint8_t  m130;                              // +0x130
    uint8_t  mPad131[0x13c - 0x131];
    TuningSource* mTuning13C;                   // +0x13c

    bool FUN_00abf640(int value);               // 0x00abf640
    void baseRemoveAgent(RemoveArgs args);      // 0x00abedb0

    int  FUN_01033f50();
    void FUN_01034260(int deathType);
    void FUN_01034950(int mode, int unused);
    void FUN_01034b90(void* star);

    bool   FUN_01033ea0(int value);
    void   RemoveAgent(AgentRef* ref, uint32_t index, int a2, int a3, int a4, int a5);
    void   FUN_010346e0();
    void   FUN_010347e0();
    void   FUN_01034810();
    void   FUN_01034840();
    void   FUN_01034880();
};
// ---- items of slice s01033de0 end

// ---- items of slice s01035900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_SpaceCullNear;             // 0x015b7ca0
extern float g_SpaceCullFar;              // 0x015b7ca4
extern float g_SpaceFov;                  // 0x015b7ca8
#define PV_s0103_5900(n) virtual void _v##n();
struct Eff {                              // visual effect handle
  virtual int AddRef();                   // 0x00
  virtual int Release();                  // 0x04
  virtual bool Play(int n);               // 0x08
};
struct World {                            // effects world / renderer / planet-like owners
  virtual int AddRef();                   // 0x00
  virtual int Release();                  // 0x04
  virtual bool Create(uint32_t id, int flags, Eff** out);   // 0x08: spawn effect `id` into *out
  virtual void SetState(int n);           // 0x0c
  PV_s0103_5900(4) PV_s0103_5900(5) PV_s0103_5900(6)
  virtual void Attach(World* other);      // 0x1c
  PV_s0103_5900(8) PV_s0103_5900(9) PV_s0103_5900(10) PV_s0103_5900(11) PV_s0103_5900(12) PV_s0103_5900(13) PV_s0103_5900(14) PV_s0103_5900(15) PV_s0103_5900(16) PV_s0103_5900(17) PV_s0103_5900(18) PV_s0103_5900(19) PV_s0103_5900(20) PV_s0103_5900(21)
  PV_s0103_5900(22) PV_s0103_5900(23) PV_s0103_5900(24) PV_s0103_5900(25) PV_s0103_5900(26) PV_s0103_5900(27) PV_s0103_5900(28) PV_s0103_5900(29)
  virtual void SetMode(int n);            // 0x78
  PV_s0103_5900(31) PV_s0103_5900(32)
  virtual void SetView(int a, int b);     // 0x84
};
namespace EA {
template <class T> class AutoRefCount_s0103_5900 {
public:
  T* mpObject;
  AutoRefCount_s0103_5900() : mpObject(0) {}
  ~AutoRefCount_s0103_5900() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s0103_5900& operator=(T* p)
  {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  T** AsPPTypeParam()
  {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return &mpObject;
  }
};  // namespace EA
}
using EA::AutoRefCount_s0103_5900;
struct Vec3_s0103_5900 {
  float x, y, z;
  Vec3_s0103_5900() {}
  Vec3_s0103_5900(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct Property {
  char pad[0x12];
  int16_t type;                           // +0x12
  uint32_t* GetUInt();                    // 0x0041ea00
};
struct PropertyList {
  virtual int AddRef();
  virtual int Release();
  PV_s0103_5900(2) PV_s0103_5900(3) PV_s0103_5900(4) PV_s0103_5900(5) PV_s0103_5900(6) PV_s0103_5900(7) PV_s0103_5900(8)
  virtual bool GetProperty(uint32_t id, Property** out);   // 0x24
};
struct PropertyManagerT {
  PV_s0103_5900(0) PV_s0103_5900(1) PV_s0103_5900(2) PV_s0103_5900(3) PV_s0103_5900(4) PV_s0103_5900(5) PV_s0103_5900(6) PV_s0103_5900(7) PV_s0103_5900(8) PV_s0103_5900(9) PV_s0103_5900(10)
  virtual void GetPropertyList(uint32_t group, uint32_t id, PropertyList** out);   // 0x2c
};
struct EffectsManagerT {
  PV_s0103_5900(0) PV_s0103_5900(1) PV_s0103_5900(2) PV_s0103_5900(3) PV_s0103_5900(4) PV_s0103_5900(5) PV_s0103_5900(6) PV_s0103_5900(7) PV_s0103_5900(8) PV_s0103_5900(9) PV_s0103_5900(10) PV_s0103_5900(11) PV_s0103_5900(12) PV_s0103_5900(13) PV_s0103_5900(14) PV_s0103_5900(15) PV_s0103_5900(16) PV_s0103_5900(17) PV_s0103_5900(18)
  virtual World* Create(uint32_t id, int flags);           // 0x4c
};
struct AppT {
  PV_s0103_5900(0) PV_s0103_5900(1) PV_s0103_5900(2) PV_s0103_5900(3) PV_s0103_5900(4) PV_s0103_5900(5) PV_s0103_5900(6) PV_s0103_5900(7) PV_s0103_5900(8) PV_s0103_5900(9) PV_s0103_5900(10) PV_s0103_5900(11) PV_s0103_5900(12) PV_s0103_5900(13) PV_s0103_5900(14) PV_s0103_5900(15) PV_s0103_5900(16) PV_s0103_5900(17) PV_s0103_5900(18) PV_s0103_5900(19)
  virtual void* GetViewA();               // 0x50
  PV_s0103_5900(21)
  virtual void* GetViewB();               // 0x58
};
struct PhysWorld {
  void Init(bool b);                      // 0x007c4dd0 cSPEditorPhysicsWorld::Init
};
PropertyManagerT* PropertyManager();      // 0x0067de30
EffectsManagerT* EffectsManager();        // 0x0067ddd0
AppT* App();                              // 0x0067dd10
World* NewWorld();                        // 0x006eea10
void ModelManager();                      // 0x0067dd80 (returns the manager; only the tail call matters here)
void GetPropertyAsVector3(PropertyList* props, uint32_t id, Vec3_s0103_5900* out);   // 0x006a1110
extern PhysWorld g_PhysWorldA;            // 0x015b7844
extern PhysWorld g_PhysWorldB;            // 0x015b79b8
extern PhysWorld g_PhysWorldC;            // 0x015b7b2c
class cSPSpaceGfx_s0103_5900 {
public:
  void InitForGame();                     // 0x01035900
  void InitSub();                         // 0x010346e0

  char pad0[0x1c];
  AutoRefCount_s0103_5900<Eff> mGalaxyCrossfadeEffect;     // +0x1c
  AutoRefCount_s0103_5900<Eff> mGalaxyEffect;              // +0x20
  AutoRefCount_s0103_5900<Eff> mGalaxyScreenEffect;        // +0x24
  AutoRefCount_s0103_5900<Eff> mGalaxyAmbienceEffect;      // +0x28
  AutoRefCount_s0103_5900<Eff> mGalaxyBackgroundGalaxies;  // +0x2c
  AutoRefCount_s0103_5900<Eff> mTraveLineEffect;           // +0x30
  AutoRefCount_s0103_5900<Eff> mSporepediaPlotPathEffect;  // +0x34
  void* mTravelLineStar;                        // +0x38
  char pad3c[0x5c - 0x3c];
  int mPlanetScreenEffect;                      // +0x5c
  AutoRefCount_s0103_5900<Eff> mLavaPlanetScreenEffect;    // +0x60
  AutoRefCount_s0103_5900<Eff> mSkyboxEffect;              // +0x64
  AutoRefCount_s0103_5900<Eff> mSolarScreenEffect;         // +0x68
  AutoRefCount_s0103_5900<Eff> mSolarClouds;               // +0x6c
  AutoRefCount_s0103_5900<Eff> mSolarLoopbox;              // +0x70
  AutoRefCount_s0103_5900<Eff> mSolarBackgroundEffect;     // +0x74
  AutoRefCount_s0103_5900<Eff> mSolarBackgroundDustEffect; // +0x78
  AutoRefCount_s0103_5900<Eff> mPlanetBackgroundEffect;    // +0x7c
  AutoRefCount_s0103_5900<Eff> mPlanetBackgroundDustEffect;// +0x80
  AutoRefCount_s0103_5900<Eff> mSolarComets;               // +0x84
  AutoRefCount_s0103_5900<Eff> mpMeaningOfLifeEffect;      // +0x88
  char pad8c[0x94 - 0x8c];
  AutoRefCount_s0103_5900<World> mTrailEffectsWorld;       // +0x94
  AutoRefCount_s0103_5900<World> mPtolemaicEffectsWorld;   // +0x98
  AutoRefCount_s0103_5900<World> mPtolemaicEffectsRenderer;// +0x9c
  AutoRefCount_s0103_5900<World> mSolarBackgroundEffectsWorld; // +0xa0
  AutoRefCount_s0103_5900<World> mSolarBackgroundRenderer; // +0xa4
  AutoRefCount_s0103_5900<World> mGalaxyEffectsWorld;      // +0xa8
  AutoRefCount_s0103_5900<World> mMoneyEffect;             // +0xac
  AutoRefCount_s0103_5900<World> mMoneyEffectPlanet;       // +0xb0
  AutoRefCount_s0103_5900<World> mMoneyEffectUFO;          // +0xb4
  char padb8[0x100 - 0xb8];
  bool mInitedForGame;                          // +0x100
  char pad101[3];
  Vec3_s0103_5900 mVecA;                                   // +0x104
  Vec3_s0103_5900 mVecB;                                   // +0x110
  Vec3_s0103_5900 mVecC;                                   // +0x11c
  char pad128[4];
  uint32_t mTravelLineValue;                    // +0x12c
  Vec3_s0103_5900 mTravelLineVec;                          // +0x130
  AutoRefCount_s0103_5900<PropertyList> mProps;            // +0x13c (placed below)
};
// ---- items of slice s01035900 end

// @ 0x010346e0
void Behavior::FUN_010346e0()
{
    for (int i = 0; i < 4; i++) {
        uint32_t key = 0;
        uint32_t value = 0;
        switch (i) {
        case 0: key = 0x195f002; value = key - 1; break;
        case 1: key = 0x195f004; value = key - 1; break;
        case 2: key = 0x195f008; value = key - 1; break;
        case 3: key = 0x195f006; value = key - 1; break;
        }
        if (mTuning13C != 0) {
            Entry* entry;
            if (mTuning13C->pv9(key, (void**)&entry)) {
                if (entry->mType == 0xd) {
                    const void* src = ((entry->mFlags & 0x30) != 0) ? entry->mPtr : (const void*)entry;
                    G_FACTOR_TABLE[i] = *(const float*)src;
                }
            }
            G_TUNE_VARIANTS[i].Set(mTuning13C->pv10(value));
        }
    }
}

// @ 0x01034950
void Behavior::FUN_01034950(int mode, int unused)
{
    IfaceBank* self = (IfaceBank*)this;
    Iface* iface6C = self->mIface6C;
    if (iface6C == 0) {
        return;
    }
    if (mode == 1) {
        iface6C->pv2(0);
        self->mIface84->pv2(0);
        self->mIface88->pv2(0);
        self->mIface60->pv2(0);
        self->mIface70->pv3(1);
        FUN_01034880();
        self->mIface74->pv3(1);
        self->mIface78->pv3(1);
        self->mIface7C->pv3(1);
        self->mIface80->pv3(1);
        self->mIface98->pv3(2);
        return;
    }
    if (mode == 2) {
        iface6C->pv2(0);
        self->mIface60->pv3(1);
        self->mIface64->pv3(1);
        Iface* iface68 = self->mIface68;
        if (iface68 != 0) {
            iface68->pv3(1);
        }
        self->mIface70->pv2(0);
        self->mIface74->pv2(0);
        self->mIface78->pv2(0);
        self->mIface7C->pv2(0);
        self->mIface80->pv2(0);
        self->mIface84->pv3(1);
        self->mIface88->pv3(1);
        self->mIface98->pv3(0);
        Vec3 surface;
        surface.x = self->mVec110.x;
        surface.y = self->mVec110.y;
        surface.z = self->mVec110.z;
        ((Iface44*)self->mIface80)->pv17(5, &surface, 3);
        return;
    }
    if (mode == 3 || mode == 0) {
        self->mIface60->pv3(1);
        self->mIface64->pv3(1);
        Iface* iface68 = self->mIface68;
        if (iface68 != 0) {
            iface68->pv3(1);
        }
        self->mIface70->pv3(1);
        self->mIface78->pv3(1);
        self->mIface7C->pv3(1);
        self->mIface80->pv2(0);
        self->mIface84->pv3(1);
        self->mIface88->pv3(1);
        self->mIface98->pv3(2);
    }
}

// @ 0x01035900
void cSPSpaceGfx_s0103_5900::InitForGame()
{
  if (mInitedForGame)
    return;
  mInitedForGame = true;

  PropertyManager()->GetPropertyList(0xa0cb680a, 0x2ae0c7e, mProps.AsPPTypeParam());
  InitSub();
  g_PhysWorldA.Init(false);
  g_PhysWorldB.Init(false);
  g_PhysWorldC.Init(false);
  g_SpaceCullNear = 50000.0f;
  g_SpaceCullFar = 200000.0f;
  g_SpaceFov = 90.0f;

  mTrailEffectsWorld = EffectsManager()->Create(0x17f40c7, 0);
  mTrailEffectsWorld->SetState(2);
  mMoneyEffect = EffectsManager()->Create(0x17f40c9, 0);
  mMoneyEffect->SetState(2);
  mPtolemaicEffectsWorld = EffectsManager()->Create(0x17f40c8, 0);
  mPtolemaicEffectsWorld->SetState(2);
  mPtolemaicEffectsRenderer = EffectsManager()->Create(0x26f8fcb, 0);

  mSolarBackgroundEffectsWorld = NewWorld();
  mSolarBackgroundEffectsWorld->SetMode(7);
  mSolarBackgroundEffectsWorld->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mPtolemaicEffectsRenderer->Attach(mSolarBackgroundEffectsWorld);
  {
    World* r = mPtolemaicEffectsRenderer;
    r->Create(0x3ebf4ae, 0, mSolarComets.AsPPTypeParam());
  }
  {
    World* r = mPtolemaicEffectsRenderer;
    r->Create(0x3ebf4b5, 0, mpMeaningOfLifeEffect.AsPPTypeParam());
  }

  mMoneyEffectPlanet = EffectsManager()->Create(0x67247e6, 0);
  mMoneyEffectPlanet->SetState(2);
  mMoneyEffectUFO = NewWorld();
  mMoneyEffectUFO->SetMode(0);
  mMoneyEffectUFO->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mMoneyEffectPlanet->Attach(mMoneyEffectUFO);

  mSolarBackgroundRenderer = EffectsManager()->Create(0x284e479, 0);
  mGalaxyEffectsWorld = NewWorld();
  mGalaxyEffectsWorld->SetMode(4);
  mGalaxyEffectsWorld->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mSolarBackgroundRenderer->Attach(mGalaxyEffectsWorld);
  {
    World* r = mSolarBackgroundRenderer;
    r->Create(0x3eac08a, 0, mPlanetBackgroundEffect.AsPPTypeParam());
  }
  {
    World* r = mSolarBackgroundRenderer;
    r->Create(0x3eaf98c, 0, mPlanetBackgroundDustEffect.AsPPTypeParam());
  }

  {
    World* w = mTrailEffectsWorld;
    mPlanetScreenEffect = 1;
    w->Create(0x275fdf3d, 0, mSolarClouds.AsPPTypeParam());
  }
  { World* w = mTrailEffectsWorld; w->Create(0x4cab5702, 0, mLavaPlanetScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0x4e7a261f, 0, mSkyboxEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xc150010a, 0, mSolarScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xf1f7d4dc, 0, mSolarLoopbox.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xbf4763d8, 0, mSolarBackgroundEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xa0c77d6f, 0, mSolarBackgroundDustEffect.AsPPTypeParam()); }

  {
    World* w = mMoneyEffect;
    if (w->Create(0x803132fa, 0, mGalaxyCrossfadeEffect.AsPPTypeParam()))
      mGalaxyCrossfadeEffect->Play(1);
  }
  {
    World* w = mMoneyEffect;
    if (w->Create(0x5c830352, 0, mGalaxyEffect.AsPPTypeParam()))
      mGalaxyEffect->Play(1);
  }
  {
    World* w = mMoneyEffect;
    if (w->Create(0x61609a45, 0, mGalaxyAmbienceEffect.AsPPTypeParam()))
      mGalaxyAmbienceEffect->Play(1);
  }
  { World* w = mMoneyEffect; w->Create(0xc467b744, 0, mGalaxyBackgroundGalaxies.AsPPTypeParam()); }
  { World* w = mMoneyEffect; w->Create(0xbbc2a565, 0, mGalaxyScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0x840cea6, 0, mTraveLineEffect.AsPPTypeParam()); }
  {
    World* w = mTrailEffectsWorld;
    mTravelLineStar = 0;
    w->Create(0x45846142, 0, mSporepediaPlotPathEffect.AsPPTypeParam());
  }

  mMoneyEffect->SetState(2);
  mTrailEffectsWorld->SetState(0);
  mPtolemaicEffectsWorld->SetState(0);
  mPtolemaicEffectsRenderer->SetState(0);
  mSolarBackgroundRenderer->SetState(0);
  mMoneyEffectPlanet->SetState(0);

  Vec3_s0103_5900 zero(0.0f, 0.0f, 0.0f);
  mVecB = zero;
  mVecA = zero;
  mVecC = zero;

  Property* prop;
  if (mProps && mProps->GetProperty(0x68c45d1, &prop) && prop->type == 10)
    mTravelLineValue = *prop->GetUInt();
  GetPropertyAsVector3(mProps, 0x68c4614, &mTravelLineVec);
  ModelManager();
}

// @ 0x01036830
void cSPSpaceGfx::SetEffectEnabled(char enable)
{
    if (enable == 0) {
        ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyEffectsWorld)->Stop(2);
        if (mpGalaxyCrossfadeEffect != 0)
            ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyCrossfadeEffect)->Stop(1);
        return;
    }
    ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyEffectsWorld)->Stop(0);
    ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyScreenEffect)->Start(1);
    ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyBackgroundGalaxies)->Start(0);
    if (mpGalaxyCrossfadeEffect != 0)
        ((EA::Swarm::cIVisualEffect_s0103_6830*)mpGalaxyCrossfadeEffect)->Start(0);

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    void* pOwner = FUN_01021230();    Vec3* pPos = FUN_00c8b360(pOwner);
    xform.mPosition = *pPos;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((EA::Swarm::cIVisualEffect_s0103_6830*)mpPlanetBackgroundDustEffect)->SetTransform(xform);
}

// @ 0x01036940
void cSPSpaceGfx::UpdateSpaceColor(float x, float y, float z)
{
    if (mpPlanetBackgroundDustEffect == 0 && mpMeaningOfLifeEffect == 0)
        return;

    ResourceManKey key;
    key.mId = 0xafa8deb9;
    key.mType = 0x3e421ed;
    key.mOwner = 0;
    void* pRes = 0;
    ResourceManager* pMgr = (ResourceManager*)GetResourceManager();
    if (pRes != 0) {
        pRes = 0;
        ((EA::Swarm::cIVisualEffect_s0103_6830*)0)->Release();
    }
    if (!pMgr->Find(&key, &pRes, 0, 0, 0, 0)) {
        if (pRes != 0)
            ((EA::Swarm::cIVisualEffect_s0103_6830*)pRes)->Release();
        return;
    }

    ColorResource* pColor = (ColorResource*)pRes;
    mPrevColor = mSpaceColor;

    int width  = pColor->mWidth;      // +0x1c
    int height = pColor->mHeight;     // +0x20
    uint8_t* pData = pColor->mpData;  // +0x28
    int xi = (int)((x + 1000.0f) * (float)width  * 0.0005f);
    int yi = (int)((z + 1000.0f) * (float)height * 0.0005f);
    uint8_t* pPixel = pData + (yi * width + xi) * 4;
    mSpaceColor.x = (float)pPixel[2] * kColorScale;
    mSpaceColor.y = (float)pPixel[1] * kColorScale;
    mSpaceColor.z = (float)pPixel[0] * kColorScale;
    mn128 = 0;

    if (mpMeaningOfLifeEffect != 0) {
        if (((cIVisualEffectBig*)mpMeaningOfLifeEffect)->_v10b())
            ((cIVisualEffectBig*)mpMeaningOfLifeEffect)->Apply(5, &mSpaceColor, 3);
    }

    if (pRes != 0)
        ((EA::Swarm::cIVisualEffect_s0103_6830*)pRes)->Release();
}

// @ 0x01036af0
void FUN_01036af0()
{
    cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
    if (pGfx->mpEffectB8 == 0)
        return;

    if (!((cEffectByName*)pGfx->mpEffectB8)->_v10b()) {
        if (pGfx->mpEffectB8 != 0) {
            void* p = pGfx->mpEffectB8;
            pGfx->mpEffectB8 = 0;
            ((cEffectByName*)p)->_v04release();
        }
        pGfx->mpEffectBC = 0;
        if (pGfx->mpEffectC0 != 0) {
            void* p = pGfx->mpEffectC0;
            pGfx->mpEffectC0 = 0;
            ((cEffectByName*)p)->_v04release();
        }
        return;
    }

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    Vec3* pPos = ((cEffectByKey*)pGfx->mpEffectBC)->GetPosition();
    xform.mPosition = *pPos;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((cEffectByName*)pGfx->mpEffectB8)->ApplyByName(&xform);

    void* pC0 = pGfx->mpEffectC0;
    void* pB8 = pGfx->mpEffectB8;
    Vec3* pPos2 = ((cEffect34*)((cEffectC0*)pC0)->mp34)->GetPosition(1);
    ((cEffectByName*)pB8)->SetEffectIndexed(9, pPos2);
}

// @ 0x01036c20
void cSPSimulatorSpaceGame::SolarContextFinishActivate(float value, char active)
{
    int context;
    if (value < kThresh144)
        context = 0;
    else if (value < kThresh500)
        context = 1;
    else
        context = 2;

    if (mpSelectedBuilding == context)
        return;

    if (!active)
        goto set;

    {
        void* pHighLOD = mpHighLODPlanetSim;
        if (pHighLOD != 0) {
            ((cIVisualEffectHost*)pHighLOD)->_v0cstop(0);
            pHighLOD = mpHighLODPlanetSim;
            if (pHighLOD != 0) {
                mpHighLODPlanetSim = 0;
                ((cIVisualEffectHost*)pHighLOD)->_v04release();
            }
        }
        cMiniGame* pMini = (cMiniGame*)mpCivTransitionMiniGame;
        cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
        void** ppSlot = &pGfx->mpPlanetBackgroundEffect;   // singleton +0x7c

        if (context == 0) {
            if (*ppSlot != 0) {
                void* p = *ppSlot;
                *ppSlot = 0;
                ((cIVisualEffectHost*)p)->_v04release();
            }
            pMini->Switch(0x3eac08d, 0, ppSlot);
            mpSelectedBuilding = 0;
            return;
        }
        if (context == 1) {
            if (*ppSlot != 0) {
                void* p = *ppSlot;
                *ppSlot = 0;
                ((cIVisualEffectHost*)p)->_v04release();
            }
            pMini->Switch(0x3eac08a, 0, ppSlot);
            mpSelectedBuilding = 1;
            return;
        }
        if (*ppSlot != 0) {
            void* p = *ppSlot;
            *ppSlot = 0;
            ((cIVisualEffectHost*)p)->_v04release();
        }
        pMini->Switch(0x3eac086, 0, ppSlot);
    }
set:
    mpSelectedBuilding = context;
}

// @ 0x01036d30
void cSPSpaceGfx::SetEffectTransform(Vec3 position)
{
    if (mpPlanetBackgroundDustEffect == 0)
        return;

    if (!((cEffectByName*)mpPlanetBackgroundDustEffect)->_v10b()) {
        ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v08start(0);
        UpdateSpaceColor(position.x, position.y, position.z);
    }

    Transform xform;
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mPosition.x = kGalaxyOffsetA;
    xform.mPosition.y = kGalaxyOffsetB;
    xform.mPosition.z = kGalaxyOffsetC;
    xform.mfScale = kOne;
    Matrix3Assign(xform.mOrientation, &kIdentityMatrix);

    xform.mPosition = position;
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v14SetTransform(&xform);
}

// @ 0x01036e20
int FUN_01036e20()
{
    cSearchSource* pSource = (cSearchSource*)GetSpaceGfx2();
    Vec3 probe;
    probe.x = kPickA;
    probe.y = kPickB;
    probe.z = kPickC;
    pSource->GetProbe(&probe, 0, probe);               // slot 0x38

    if (probe.x != kPickA || probe.y != kPickB || probe.z != kPickC)
        return 0;

    uint8_t scratch1[64];
    uint8_t scratch2[32];
    FUN_007c46f0(scratch2, scratch1);

    cSearchSource* pSource2 = (cSearchSource*)GetSpaceGfx2();
    cSearchSource* pInner = pSource2->GetInner();

    cSearchElem** pBegin = 0;
    cSearchElem** pEnd = 0;
    cSearchElem** pCap = 0;
    uint8_t flags[8];
    flags[0] = 0;
    flags[1] = 1;
    pInner->Collect(&pBegin, &pEnd, 0, 0);

    cSearchElem** pIt = pBegin;
    if (pBegin != pEnd) {
        do {
            cSearchElem* pElem = *pIt;
            cFound* pFound = pElem->mp64;
            if (pFound != 0) {
                void* pObj = pFound->FindName(0x3275872);
                if (pObj != 0 && FUN_00c6ff90(pObj) == 2) {
                    if (pBegin != 0 && pBegin != pCap)
                        operator_delete_array(pBegin);
                    return (int)pObj;
                }
            }
            ++pIt;
        } while (pIt != pEnd);
    }

    if (pBegin != 0 && pBegin != pCap)
        operator_delete_array(pBegin);
    return 0;
}

// @ 0x01036fc0
void ColonyMap::DoNukeSubtree(RBNode* pNode)
{
    while (pNode != 0) {
        DoNukeSubtree(pNode->mpLeft);
        cMWModel* pValue = pNode->mpValue;
        RBNode* pRight = pNode->mpRight;
        if (pValue != 0) {
            if (pValue->mRefCount > 1) {
                pValue->mRefCount--;
            } else {
                pValue->Destroy((pValue->mu04 >> 31) & 1);
            }
        }
        operator_delete_array(pNode);
        pNode = pRight;
    }
}

// @ 0x01037030
cSPSpaceGfx::~cSPSpaceGfx()
{
    if (mp13c != 0)
        ((cEffectByName*)mp13c)->_v04release();
    TimerOwnerDtor(mTimerC8);
    if (mpEffectC4 != 0) ((cEffectByName*)mpEffectC4)->_v04release();
    if (mpEffectC0 != 0) ((cEffectByName*)mpEffectC0)->_v04release();
    if (mpEffectB8 != 0) ((cEffectByName*)mpEffectB8)->_v04release();
    if (mpMoneyEffectUFO != 0) ((cEffectByName*)mpMoneyEffectUFO)->_v04release();
    if (mpMoneyEffectPlanet != 0) ((cEffectByName*)mpMoneyEffectPlanet)->_v04release();
    if (mpGalaxyEffectsWorld != 0) ((cEffectByName*)mpGalaxyEffectsWorld)->_v04release();
    if (mpGalaxyEffectsWorld != 0) ((cEffectByName*)mpGalaxyEffectsWorld)->_v04release();
    if (mpSolarBackgroundRenderer != 0) ((cEffectByName*)mpSolarBackgroundRenderer)->_v04release();
    if (mpSolarBackgroundEffectsWorld != 0) ((cEffectByName*)mpSolarBackgroundEffectsWorld)->_v04release();
    if (mpPtolemaicEffectsRenderer != 0) ((cEffectByName*)mpPtolemaicEffectsRenderer)->_v04release();
    if (mpPtolemaicEffectsWorld != 0) ((cEffectByName*)mpPtolemaicEffectsWorld)->_v04release();
    if (mpTrailEffectsWorld != 0) ((cEffectByName*)mpTrailEffectsWorld)->_v04release();
    if (mpSolarEffectsWorld != 0) ((cEffectByName*)mpSolarEffectsWorld)->_v04release();
    if (mpRingEffect != 0) ((cEffectByName*)mpRingEffect)->_v04release();
    if (mpMeaningOfLifeEffect != 0) ((cEffectByName*)mpMeaningOfLifeEffect)->_v04release();
    if (mpSolarComets != 0) ((cEffectByName*)mpSolarComets)->_v04release();
    if (mpPlanetBackgroundDustEffect != 0) ((cEffectByName*)mpPlanetBackgroundDustEffect)->_v04release();
    if (mpPlanetBackgroundEffect != 0) ((cEffectByName*)mpPlanetBackgroundEffect)->_v04release();
    if (mpSolarBackgroundDustEffect != 0) ((cEffectByName*)mpSolarBackgroundDustEffect)->_v04release();
    if (mpSolarBackgroundEffect != 0) ((cEffectByName*)mpSolarBackgroundEffect)->_v04release();
    if (mpSolarLoopbox != 0) ((cEffectByName*)mpSolarLoopbox)->_v04release();
    if (mpSolarClouds != 0) ((cEffectByName*)mpSolarClouds)->_v04release();
    if (mpSolarScreenEffect != 0) ((cEffectByName*)mpSolarScreenEffect)->_v04release();
    if (mpSkyboxEffect != 0) ((cEffectByName*)mpSkyboxEffect)->_v04release();
    if (mpLavaPlanetScreenEffect != 0) ((cEffectByName*)mpLavaPlanetScreenEffect)->_v04release();
    if (mpPlanetScreenEffect != 0) ((cEffectByName*)mpPlanetScreenEffect)->_v04release();
    mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
    if (mpSporepediaPlotPathEffect != 0) ((cEffectByName*)mpSporepediaPlotPathEffect)->_v04release();
    if (mpTravelLineEffect != 0) ((cEffectByName*)mpTravelLineEffect)->_v04release();
    if (mpGalaxyBackgroundGalaxies != 0) ((cEffectByName*)mpGalaxyBackgroundGalaxies)->_v04release();
    if (mpGalaxyAmbienceEffect != 0) ((cEffectByName*)mpGalaxyAmbienceEffect)->_v04release();
    if (mpGalaxyScreenEffect != 0) ((cEffectByName*)mpGalaxyScreenEffect)->_v04release();
    if (mpGalaxyEffect != 0) ((cEffectByName*)mpGalaxyEffect)->_v04release();
    if (mpGalaxyCrossfadeEffect != 0) ((cEffectByName*)mpGalaxyCrossfadeEffect)->_v04release();
}

// @ 0x010372b0
void cSPSpaceGfx::ShutdownForGame()
{
    if (!mb100)
        return;
    mb100 = false;

    if (mp13c != 0) {
        void* p = mp13c;
        mp13c = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpSolarClouds != 0)
        ((cEffectFull*)mpSolarClouds)->_v0cStop(1);
    if (mpSolarClouds != 0) {
        void* p = mpSolarClouds;
        mpSolarClouds = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyCrossfadeEffect != 0)
        ((cEffectFull*)mpGalaxyCrossfadeEffect)->_v0cStop(1);
    if (mpGalaxyCrossfadeEffect != 0) {
        void* p = mpGalaxyCrossfadeEffect;
        mpGalaxyCrossfadeEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyEffect != 0)
        ((cEffectFull*)mpGalaxyEffect)->_v0cStop(1);
    if (mpGalaxyEffect != 0) {
        void* p = mpGalaxyEffect;
        mpGalaxyEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpGalaxyAmbienceEffect != 0)
        ((cEffectFull*)mpGalaxyAmbienceEffect)->_v0cStop(1);
    if (mpGalaxyAmbienceEffect != 0) {
        void* p = mpGalaxyAmbienceEffect;
        mpGalaxyAmbienceEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpPlanetBackgroundEffect != 0)
        ((cEffectFull*)mpPlanetBackgroundEffect)->_v0cStop(1);
    if (mpPlanetBackgroundEffect != 0) {
        void* p = mpPlanetBackgroundEffect;
        mpPlanetBackgroundEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpPlanetBackgroundDustEffect != 0)
        ((cEffectFull*)mpPlanetBackgroundDustEffect)->_v0cStop(1);
    if (mpPlanetBackgroundDustEffect != 0) {
        void* p = mpPlanetBackgroundDustEffect;
        mpPlanetBackgroundDustEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpRingEffect != 0)
        ((cEffectFull*)mpRingEffect)->_v0cStop(1);
    if (mpRingEffect != 0) {
        void* p = mpRingEffect;
        mpRingEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpSolarComets != 0)
        ((cEffectFull*)mpSolarComets)->_v0cStop(1);
    if (mpSolarComets != 0) {
        void* p = mpSolarComets;
        mpSolarComets = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpMeaningOfLifeEffect != 0)
        ((cEffectFull*)mpMeaningOfLifeEffect)->_v0cStop(1);
    if (mpMeaningOfLifeEffect != 0) {
        void* p = mpMeaningOfLifeEffect;
        mpMeaningOfLifeEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    if (mpTravelLineEffect != 0)
        ((cEffectFull*)mpTravelLineEffect)->_v0cStop(1);
    if (mpTravelLineEffect != 0) {
        void* p = mpTravelLineEffect;
        mpTravelLineEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }
    mpTravelLineStar = 0;
    if (mpSporepediaPlotPathEffect != 0)
        ((cEffectFull*)mpSporepediaPlotPathEffect)->_v0cStop(1);
    if (mpSporepediaPlotPathEffect != 0) {
        void* p = mpSporepediaPlotPathEffect;
        mpSporepediaPlotPathEffect = 0;
        ((cEffectByName*)p)->_v04release();
    }

    ((cEffectFull*)mpGalaxyEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpPtolemaicEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpTrailEffectsWorld)->_v0cStop(2);
    ((cEffectFull*)mpPtolemaicEffectsRenderer)->_v0cStop(2);
    ((cEffectFull*)mpSolarBackgroundRenderer)->_v0cStop(2);
    ((cEffectFull*)mpMoneyEffectPlanet)->_v0cStop(2);

    EffectsManagerPtr()->ReleaseEffect(0x17f40c9);
    if (mpGalaxyEffectsWorld != 0) { void* p = mpGalaxyEffectsWorld; mpGalaxyEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x17f40c7);
    if (mpTrailEffectsWorld != 0) { void* p = mpTrailEffectsWorld; mpTrailEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x17f40c8);
    if (mpPtolemaicEffectsWorld != 0) { void* p = mpPtolemaicEffectsWorld; mpPtolemaicEffectsWorld = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x26f8fcb);
    if (mpPtolemaicEffectsRenderer != 0) { void* p = mpPtolemaicEffectsRenderer; mpPtolemaicEffectsRenderer = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x284e479);
    if (mpSolarBackgroundRenderer != 0) { void* p = mpSolarBackgroundRenderer; mpSolarBackgroundRenderer = 0; ((cEffectByName*)p)->_v04release(); }
    EffectsManagerPtr()->ReleaseEffect(0x67247e6);
    if (mpMoneyEffectPlanet != 0) { void* p = mpMoneyEffectPlanet; mpMoneyEffectPlanet = 0; ((cEffectByName*)p)->_v04release(); }

    if (mpSolarBackgroundEffectsWorld != 0) {
        ((cEffectFull*)mpSolarBackgroundEffectsWorld)->_v7c();
        if (mpSolarBackgroundEffectsWorld != 0) {
            void* p = mpSolarBackgroundEffectsWorld;
            mpSolarBackgroundEffectsWorld = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }
    if (mpGalaxyEffectsWorld != 0) {
        ((cEffectFull*)mpGalaxyEffectsWorld)->_v7c();
        if (mpGalaxyEffectsWorld != 0) {
            void* p = mpGalaxyEffectsWorld;
            mpGalaxyEffectsWorld = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }
    if (mpMoneyEffectUFO != 0) {
        ((cEffectFull*)mpMoneyEffectUFO)->_v7c();
        if (mpMoneyEffectUFO != 0) {
            void* p = mpMoneyEffectUFO;
            mpMoneyEffectUFO = 0;
            ((cEffectByName*)p)->_v04release();
        }
    }

    {
        cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
        RBNode* pNode = (RBNode*)pGfx->mColonyModelMap.mpBegin;
        while (pNode != (RBNode*)&pGfx->mColonyModelMap.mpHead) {
            ((cEffectFull*)pNode->mpValue)->_v16c(0);
            pNode = (RBNode*)RBTreeIncrement(pNode);
        }
    }

    {
        mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
        void* pHead = (void*)&mColonyModelMap.mpHead;
        mColonyModelMap.mpRoot = 0;
        mColonyModelMap.mb10 = 0;
        mColonyModelMap.mp14 = 0;
        mColonyModelMap.mpBegin = pHead;
        mColonyModelMap.mpHead = pHead;
    }

    if (SpaceApp() != 0) {
        cApp* pApp = (cApp*)SpaceApp();
        cSubSys* pSub = (cSubSys*)pApp->GetSubSystem();
        ((cViewer*)pSub->GetViewer())->SetViewAngle(kViewAngle);
    }

    FUN_007c3ba0((void*)0x15b7844);
    FUN_007c3ba0((void*)0x15b79b8);
    FUN_007c3ba0((void*)0x15b7b2c);
}

// @ 0x01037700
void cSPSpaceGfx::AllianceGraphCreate()
{
    RBNode* pNode = (RBNode*)mColonyModelMap.mpBegin;
    RBNode* pHead = (RBNode*)&mColonyModelMap.mpHead;
    while (pNode != pHead) {
        ((cEffectFull*)pNode->mpValue)->_v16c(0);
        pNode = (RBNode*)RBTreeIncrement(pNode);
    }

    mColonyModelMap.DoNukeSubtree((RBNode*)mColonyModelMap.mpRoot);
    void* head = (void*)&mColonyModelMap.mpHead;
    mColonyModelMap.mpRoot = 0;
    mColonyModelMap.mb10 = 0;
    mColonyModelMap.mp14 = 0;
    mColonyModelMap.mpBegin = head;
    mColonyModelMap.mpHead = head;
}

// @ 0x01037760
void AllianceGraphUpdate(uint32_t param)
{
    float t = FUN_01036610(param);
    if (t <= 0.0f) {
        FUN_010367e0(GetSpaceGfx(), 0);
        return;
    }
    FUN_010367e0(GetSpaceGfx(), 1);
    cSPSpaceGfx* pGfx = (cSPSpaceGfx*)GetSpaceGfx();
    if (pGfx->mbColonyMapIsDirty)
        pGfx->AllianceGraphCreate();

    RBNode* pNode = (RBNode*)((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpBegin;
    RBNode* pHead = (RBNode*)&((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpHead;
    if (pNode == pHead)
        return;
    do {
        ((cModelNodeValue*)pNode->mpValue)->mf58 = t;
        pNode = (RBNode*)RBTreeIncrement(pNode);
        pHead = (RBNode*)&((cSPSpaceGfx*)GetSpaceGfx())->mColonyModelMap.mpHead;
    } while (pNode != pHead);
}

// @ 0x010377f0
void cSPSpaceGfx_s0103_77f0::UpdateForSpaceGame(int nArg)
{
    int nContext = cSPLivingUniverse_GetUniverseContext();
    if (nContext == 1)
        SpaceGfx_UpdateGroup1();
    else if (nContext == 2) {
        SpaceGfx_UpdateGroup2();
        SpaceGfx_UpdateGroup3(this, nArg);
    }

    if (gSpaceAudioEnabled0 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0) {
            cPlanetSubsystem* pPlanet = (cPlanetSubsystem*)cSPLivingUniverse_GetActivePlanet();
            if (pPlanet == 0)
                return;
            cSpaceTimerOwner* pTimerOwner = pPlanet->GetTimerOwner();
            if (pTimerOwner == 0)
                return;
            pTimerOwner->AddTimer(gSpaceGfxTimerId, gImpostorTimer, gSpaceFadeDelay, 0);
        }
    }

    if (gSpaceAudioEnabled1 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudio0();
    }
    if (gSpaceAudioEnabled2 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudioN(1, gSpaceAudioParam0, gSpaceAudioParam1);
    }
    if (gSpaceAudioEnabled3 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudioN(0, gSpaceAudioParam0, gSpaceAudioParam1);
    }

    ((void (__thiscall*)(void*, int))((void**)*(void**)((char*)&mTimer))[0x04 / 4])(&mTimer, 0);
}

// @ 0x010378f0
cSPSpaceGfx_s0103_77f0::cSPSpaceGfx_s0103_77f0()
{
    Construct();

    mpVtable = (void*)0x1499908;
    mpVtable2 = (void*)0x1499900;

    mUnk1c = 0;
    mUnk20 = 0;
    mUnk24 = 0;
    mUnk28 = 0;
    mUnk2c = 0;
    mUnk30 = 0;
    mUnk34 = 0;
    mUnk38 = 0;

    mUnk40.mp4 = 0;
    mUnk40.mp8 = 0;
    mUnk40.mpc = 0;
    mUnk40.mp0 = &mUnk40;
    mUnk40.mp4 = &mUnk40;

    mUnk50 = 0;
    mUnk58 = 0;
    mUnk59 = 0;
    mUnk5c = 1;
    mUnk60 = 0;
    mUnk64 = 0;
    mUnk68 = 0;
    mUnk6c = 0;
    mUnk70 = 0;
    mUnk74 = 0;
    mUnk78 = 0;
    mUnk7c = 0;
    mUnk80 = 0;
    mUnk84 = 0;
    mUnk88 = 0;
    mUnk8c = 0;
    mUnk90 = 0;
    mUnk94 = 0;
    mUnk98 = 0;
    mUnk9c = 0;
    mUnkA0 = 0;
    mUnkA4 = 0;
    mUnkA8 = 0;
    mUnkAc = 0;
    mUnkB0 = 0;
    mUnkB4 = 0;
    mUnkB8 = 0;
    mUnkBC = 0;
    mUnkC0 = 0;
    mUnkC4 = 0;

    mTimer.Construct();

    mUnk100 = 0;
    mUnk13c = 0;
}
