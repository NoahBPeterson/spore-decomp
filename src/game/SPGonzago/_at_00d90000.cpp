// src/game/SPGonzago/_at_00d90000.cpp -- migrated from slice(s) s00d9dce0, s00d9cd90, s00d9bee0, s00d9af60, s00d99ff0, s00d990a0, s00d90640 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCityVisualizer.h"
#include "SP/cCombatant.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureCitizen.h"
#include "cSPVector3.h"
#include "SP/cAnimState.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_00cd7d10();
extern "C" void FUN_00d3d420();
extern "C" void FUN_00ad48b0();
extern "C" void FUN_00ae72d0();
extern "C" void FUN_00b1e500();

// ---- items of slice s00d90640 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVN(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
namespace nSPBehaviorTree {
struct behavior_stimuli_s00d9_0640 {
    int   Play(int a, int b);                           // 0x00bc96a0
    void  ClearAll(int a, int b);                       // 0x00bc98f0
    void* GetAny();                                     // 0x00d997e0
};
}
struct StimulusSlot { uint32_t mId; void* mpTarget; };
struct IterEntry { uint8_t pad0[8]; void* mpObject; };
struct AuxGeom { uint8_t pad00[8]; float f08; uint8_t pad0c[8]; float f14; };
struct BehaviorStateOut {
    int      m00;                                       // +0x00
    float    mf04;                                      // +0x04
    int      m08;                                       // +0x08
    float    mf0C;                                      // +0x0c
    uint8_t  m10;                                       // +0x10
    uint8_t  mPad11[3];
    float    mf14;                                      // +0x14
    uint8_t  m18;                                       // +0x18
};
class cActionCircle_s00d9_0640 {                                   // 0x00afae50 / 0x00d5c470 / 0x00d5c580
public:
    void RemoveAgent(void* agent);                      // 0x00afae50
};
class cAgentPos {                                       // 0x00afad70
public:
    int CheckPosition(Vec3* pos);                       // 0x00afad70
};
class cBehaviorAgent {                                  // the object at cSPCreatureCitizen+0xfb8
public:
    uint8_t       mPad000[0x70];                        // +0x000
    cActionCircle_s00d9_0640 mCircle070;                           // +0x070
    uint8_t       mPad071[0xd4 - 0x71];                 // +0x071 .. +0x0d3
    cAgentPos     mPos;                                 // +0x0d4
    uint8_t       mPad0D5[0x1a8 - 0xd5];                // +0x0d5 .. +0x1a7
    int           mn1A8;                                // +0x1a8
    int           mn1AC;                                // +0x1ac
    uint8_t       mPad1B0[0x1bc - 0x1b0];               // +0x1b0 .. +0x1bb
    cActionCircle_s00d9_0640 mCircle1BC;                           // +0x1bc
    uint8_t       mPad1BD[0x1c8 - 0x1bd];               // +0x1bd .. +0x1c7
    uint32_t      mn1C8;                                // +0x1c8
    uint8_t       mPad1CC[0xa28 - 0x1cc];               // +0x1cc .. +0xa27
    int           mnA28;                                // +0xa28
    int           mUnkA2C;                              // +0xa2c
    int           mnA30;                                // +0xa30
    int           mUnkA34;                              // +0xa34
    int           mnA38;                                // +0xa38
    int           mUnkA3C;                              // +0xa3c
    int           mUnkA40;                              // +0xa40
    int           mnA44;                                // +0xa44
    uint8_t       mUnkA48[8];                           // +0xa48 .. +0xa4f
    uint8_t       mbA50;                                // +0xa50

    int* GetCounter(uint32_t idx);                      // 0x00d576b0
    void EnterZone(void* p, int b);                     // 0x00d5c470
    void ExitZone(void* p);                             // 0x00d5c580
};
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[8];                                // +0x00
    nSPBehaviorTree::behavior_stimuli_s00d9_0640 mStimuli;         // +0x08
    uint8_t  mPadStim[0x1c8 - 9];                       // +0x09 .. +0x1c7
    uint32_t mn1C8;                                     // +0x1c8
};
class cLocomotiveObject_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* GetPosition();                        // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    PVN(22) PVN(23) PVN(24) PVN(25)
    virtual void* GetAux68();                           // +0x68
    uint8_t mPad04[0x5c];                               // +0x04 .. +0x5f (size 0x60)
    char IsNearGoal();                                  // 0x00c42e20
};
class cGameObject {
public:
    PVN(0) PVN(1) PVN(2)
    virtual void* GetChild0c();                         // +0x0c
    PVN(4) PVN(5) PVN(6) PVN(7)
    virtual int   GetType20();                          // +0x20
    PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    virtual int   GetIdentity4c();                      // +0x4c
    PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25)
    virtual void* GetModel68();                         // +0x68
    uint8_t mPad04[0x30];                               // +0x04 .. +0x33
    cLocomotiveObject_s00d9_0640 mLoco34;                          // +0x34 (size 0x60)
    uint8_t mPad94[0x508 - 0x94];                       // +0x94 .. +0x507
    uint8_t mStimulus508;                               // +0x508 (target registered as a stimulus)
};
class cCombatant_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4)
    PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14)
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();                       // +0x58
    uint8_t mPad04[0x11];                               // +0x04
    char    mb15;                                       // +0x15
    uint8_t mPad16[0x22];                               // +0x16 .. +0x37
    float   mfHealth38;                                 // +0x38
    uint8_t mPad3c[4];                                  // +0x3c .. +0x3f (size 0x40)
    int GetDamageState();                               // 0x008e7f80
};
class cCommunity_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21)
    virtual float GetCap58();                           // +0x58
    uint8_t mPad04[0x34];                               // +0x04 .. +0x37 (size 0x38)
    void EnsureTimer(void* agent);                      // 0x00bfddc0
};
class cCity_s00d9_0640 {
public:
    PVN(0)
    uint8_t mPad04[0x2d0 - 0x04];                       // +0x04 .. +0x2cf
    int     mn2D0;                                      // +0x2d0
    int  GetVehicleSpecialty();                         // 0x00bd81d0
    int  FUN_00bd8190();                                // 0x00bd8190
    void FUN_00bd8170(int v);                           // 0x00bd8170
};
class cPlanetModel_s00d9_0640 {
public:
    PVN(0)
    void DirectionToSurfacePosition(Vec3& out, Vec3* dir);   // 0x00b815a0
};
class cGameNounManager_s00d9_0640 {
public:
    PVN(0)
    int* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* key);   // 0x00b21340
};
class cSPCreatureCitizen_s00d9_0640 {
public:
    // ---- vtable ----
    PVN(0)  PVN(1)  PVN(2)  PVN(3)  PVN(4)  PVN(5)  PVN(6)  PVN(7)  PVN(8)  PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    virtual int   GetIdentity();                        // +0x4c
    PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31) PVN(32) PVN(33) PVN(34)
    virtual void  Flag8c();                             // +0x8c
    PVN(36) PVN(37)
    virtual int   GetMode98();                          // +0x98
    virtual void  SetMode9c(int);                       // +0x9c
    PVN(40) PVN(41) PVN(42) PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49)
    virtual void  FlagC8(int);                          // +0xc8

    // ---- data ----
    uint8_t  mPad04[0xbc];                              // +0x04 .. +0xbf
    cLocomotiveObject_s00d9_0640 mLoco;                            // +0xc0 (size 0x60)
    cCombatant_s00d9_0640 mCombatant;                              // +0x120 (size 0x40)
    uint8_t  mPad160[0x448];                            // +0x160 .. +0x5a7
    cCommunity_s00d9_0640 mCommunity;                              // +0x5a8 (size 0x38)
    float    mf5E0;                                     // +0x5e0
    uint8_t  mPad5e4[0x568];                            // +0x5e4 .. +0xb4b
    cBehaviorStimuliOwner* mpB4C;                       // +0xb4c
    uint8_t  mPadB50[0x440];                            // +0xb50 .. +0xf8f
    char     mbF90;                                     // +0xf90
    uint8_t  mPadF91[0x27];                             // +0xf91 .. +0xfb7
    cBehaviorAgent* mpFB8;                              // +0xfb8
    char     mbFBC;                                     // +0xfbc
    uint8_t  mPadFBD[3];                                // +0xfbd .. +0xfbf
    int      mnFC0;                                     // +0xfc0
    uint8_t  mPadFC4[0x2c];                             // +0xfc4 .. +0xfef
    int      mnFF0;                                     // +0xff0
    uint8_t  mPadFF4[0x418];                            // +0xff4 .. +0x140b
    void*    mp140C;                                    // +0x140c  iterator begin
    void*    mp1410;                                    // +0x1410  iterator end

    // ---- helpers (thiscall, self == citizen) ----
    bool Flag388();                                     // 0x00c0c0e0
    int  GetAnimGuid();                                 // 0x00c0e040
    int  FUN_00c0e370();                                // 0x00c0e370
    void SetSprinting(int s);                           // 0x00c1ad10
    void InterruptAnimation(int anim, int a, int b);    // 0x00c12310
    int  PlayAnimation(int anim, int a, int b);         // 0x00c12190
    char AnimationFinished(int anim);                   // 0x00c123f0
    void Show();                                        // 0x00c0f2b0
    cCity_s00d9_0640* GetCity();                                   // 0x00c23e40
    uint32_t FUN_00c227b0();                            // 0x00c227b0
    void SetCurrentToolEffect(int a, int b);            // 0x00c24f40
    void FUN_00c0d0c0(int a, int b);                    // 0x00c0d0c0
};
void* FUN_00d51660();                                   // 0x00d51660
void* GetCurrentGameMode();                             // 0x00b5b800
cPlanetModel_s00d9_0640* PlanetModel();                            // 0x00b3d350
cGameNounManager_s00d9_0640* NounManager();                        // 0x00b3d300
bool FUN_00c38990(void* self, int flag);                // 0x00c38990
bool FUN_00c03520(void* entry);                         // 0x00c03520
void FUN_00b3d870(void* ppIt);                          // 0x00b3d870
struct cLocoWrapper { void FUN_00b45410(); };           // 0x00b45410
cLocoWrapper* __stdcall FUN_00b3d310(void* p);          // 0x00b3d310
int  FUN_00d99a10(int v);                               // 0x00d99a10
int* FUN_00d998f0(int v);                               // 0x00d998f0
extern "C" void FUN_00cd7d10();
extern "C" void FUN_00d3d420();
extern "C" void FUN_00ad48b0();
extern "C" void FUN_00ae72d0();
extern "C" void FUN_00b1e500();
// ---- items of slice s00d90640 end

// ---- items of slice s00d990a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
struct Vector3 {
    float x, y, z;
};
class cPlanetModel;
cPlanetModel* PlanetModel_s00d9_90a0();                                          // 0x00b3d350
class cPlanetModel {
public:
    float GetWaterHeight();                                           // 0x00b7e390
    // writes the surface orientation of a position into pOut and returns it.
    Vector3* BuildSurfaceOrientation2(Vector3* pOut, const Vector3* pDir,
                                      Vector3* pUp);                  // 0x00b7f250
    Vector3 DirectionToSurfacePosition(const Vector3& pos);           // 0x00b815a0
    Vector3 SnapToSurface(const Vector3& pos);                        // 0x00b81630
};
class cCreatureStatus {
public:
    uint8_t mOpaque[0x75];
    bool mIsAlive;                                                    // +0x75
};
class cCreatureOwner {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c
};
class cLocomotiveObject {
public:
    bool IsNearGoal();                                                // 0x00c42e20
    uint8_t mOpaque[0x60];
};
class cCombatant {
public:
    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    uint8_t mOpaque[0x15];                                            // +0x00 .. +0x14
};
class cAnimState {
public:
    uint8_t mPad00[8];
    float mfProgress;                                                 // +0x08
};
class cAnimationPlayer {
public:
    cAnimState* Play(uint32_t nAnimID, uint32_t nFlags);              // 0x00bc96a0
};
class cAnimation {
public:
    uint8_t mPad00[8];
    cAnimationPlayer mPlayer;                                         // +0x08
};
class cActionSlot {
public:
    uint32_t mField00;                                                // +0x00
    void* mpField04;                                                  // +0x04
    uint8_t mPad08[4];
    Vector3 mPos;                                                     // +0x0c
};
class cActionCircle {
public:
    uint8_t mPad00[0x14];
    Vector3 mPos;                                                     // +0x14
    uint8_t mPad20[0x30];                                             // +0x20 .. +0x4f
    cActionSlot* mpBegin;                                             // +0x50
    cActionSlot* mpEnd;                                               // +0x54
    uint8_t mPad58[0x0c];                                             // +0x58 .. +0x63
    cActionSlot* SlotAt(uint32_t nIndex);                             // 0x00af9ff0
};
class cCreatureTree {
public:
    uint8_t mPad000[0x220];
    cActionCircle* mpCircles;                                         // +0x220
};
class cSPCreatureBase {
public:
    VSLOT(0) VSLOT(1)
    virtual cCreatureStatus* GetStatus();                             // +0x08
    virtual cCreatureOwner* GetOwner();                               // +0x0c
    VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual uint32_t GetTypeID();                                     // +0x20
    VSLOT(9) VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c

    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    bool AnimationFinished(int32_t nFlags);                           // 0x00c123f0
    void PlayAnimation(uint32_t nAnimID, int32_t nLoops, int32_t nFlags);  // 0x00c12190

    uint8_t mPad04[0x30];                                             // +0x04 .. +0x33
    int32_t mnDamageState;                                            // +0x34
    float mf38;                                                       // +0x38
    uint8_t mPad3c[0x84];                                             // +0x3c .. +0xbf
    cLocomotiveObject mLocomotive;                                    // +0xc0
    cCombatant mCombatant;                                            // +0x120
    bool mB135;                                                       // +0x135
    uint8_t mPad136[0x472];                                           // +0x136 .. +0x5a7
    uint8_t mB5a8;                                                    // +0x5a8
    uint8_t mPad5a9[0x5a3];                                           // +0x5a9 .. +0xb4b
    cAnimation* mB4c;                                                 // +0xb4c
    uint8_t mPadB50[8];                                               // +0xb50 .. +0xb57
    uint8_t mB58;                                                     // +0xb58 (flags)
    uint8_t mPadB59[5];                                               // +0xb59 .. +0xb5d
    bool mB5e;                                                        // +0xb5e
    uint8_t mPadB5f[0x459];                                           // +0xb5f .. +0xfb7
    cCreatureTree* mFB8;                                              // +0xfb8
};
void* CastCreature(void* pObject, uint32_t nTypeID);                  // 0x00ac80d0
class cStimulusSource {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cSPCreatureBase* FindObject(uint32_t nStimulusID);        // +0x0c
};
struct cStimulusContext {
    uint8_t mPad00[0x2c];
    cStimulusSource* mpSource;                                        // +0x2c
};
class cStimulusAttrA {
public:
    VSLOT(0)
    VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual int32_t AddRef();                                         // +0x60
    virtual int32_t Release();                                        // +0x64
};
class cStimulusAttrB {
public:
    virtual int32_t AddRef();                                         // +0x00
    virtual int32_t Release();                                        // +0x04
};
class cStimulusAttrC {
public:
    VSLOT(0)
    virtual int32_t AddRef();                                         // +0x04
    virtual int32_t Release();                                        // +0x08
};
template <class T>
class IntrusivePtr {
public:
    IntrusivePtr& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    T* mpObject;                                                      // +0x00
};
struct sStimulusRecord {
    cStimulusAttrC* mpC;                                              // +0x00
    cStimulusAttrA* mpA;                                              // +0x04
    cStimulusAttrB* mpB;                                              // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
};
struct sStimulusAssignment {
    IntrusivePtr<cStimulusAttrA> mpA;                                 // +0x00
    IntrusivePtr<cStimulusAttrB> mpB;                                 // +0x04
    IntrusivePtr<cStimulusAttrC> mpC;                                 // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
    float mf28;                                                       // +0x28
};
struct sStimulusFlat {
    uint32_t mField00;                                                // +0x00
    uint32_t mField04;                                                // +0x04
    uint32_t mField08;                                                // +0x08
    Vector3 mOffset;                                                  // +0x0c
    uint32_t mField18;                                                // +0x18
    uint32_t mField1c;                                                // +0x1c
    uint32_t mField20;                                                // +0x20
    float mf24;                                                       // +0x24
};
struct sStimulusRotated {
    uint32_t mFieldSrc08;                                             // +0x00
    uint32_t mFieldSrc00;                                             // +0x04
    uint32_t mFieldSrc04;                                             // +0x08
    Vector3 mOffset;                                                  // +0x0c
    uint32_t mField18;                                                // +0x18
    uint32_t mField1c;                                                // +0x1c
    uint32_t mField20;                                                // +0x20
    float mf24;                                                       // +0x24
};
void AssignStimulus(const sStimulusRecord* pSrc, sStimulusAssignment* pDst);  // 0x00d99730
class cTreeNode {
public:
    uint32_t GetID();                                                 // 0x00c0ee60 (reads +0xe7c)
    uint8_t mOpaque[0xe80];
};
struct cTreeRing {
    cTreeNode* mpNodes[1];                                            // +0x00
    uint8_t mPad04[0x10];                                             // +0x04 .. +0x13
    uint32_t mnIndex;                                                 // +0x14
};
class cSpatialObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual Vector3* GetPosition(float fT);                           // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    virtual float GetRadius(const Vector3* pToward);                  // +0x74

    uint8_t mPad04[0x4c];                                             // +0x04 .. +0x4f
    uint32_t mFlags50;                                                // +0x50
};
float DistanceBetweenBodies(const Vector3* pA, float fRadiusA, const Vector3* pB,
                            float fRadiusB, bool bClamp);              // 0x00d99a60
float RecursiveSurfaceProbe(const Vector3* pFrom, const Vector3* pDir, float fLow,
                            float fHigh);                              // 0x00d99cd0
void WalkTree(float fA, double dB, void* pC, void* pD, void* pE, void* pF, void* pG,
              void* pH);                                              // 0x00bc8ff0
struct sStimulusDesc {
    uint32_t mID;                                                     // +0x00
    uint32_t mCount;                                                  // +0x04
    uint32_t mMax;                                                    // +0x08
    Vector3 mOffset;                                                  // +0x0c
};
// ---- items of slice s00d990a0 end

// ---- items of slice s00d99ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sqrtf(float);
extern "C" extern float DAT_0169f2f4;    // 0x0169f2f4
extern "C" extern float DAT_0169f2a4;    // 0x0169f2a4
extern "C" extern float DAT_0169f2a8;    // 0x0169f2a8
extern "C" extern float DAT_0169f2ac;    // 0x0169f2ac
extern "C" extern float DAT_0169f300;    // 0x0169f300
extern "C" extern float DAT_01471064;    // 0x01471064 (0.5f)
extern "C" extern void* DAT_016c7aa4;    // 0x016c7aa4
typedef unsigned int uint;
struct DB {
    void* FUN_00f3e8a0(int nounID);                    // 0x00f3e8a0 (thiscall: self = *(DAT_016c7aa4+0x74))
};
void* FUN_00ac80d0(void* obj, int type);               // 0x00ac80d0
void* CastCreature(void* obj);                         // 0x00ae66f0
struct C41Obj { char* Method(); };                     // 0x00c41ec0 (__thiscall)
void  FUN_0059aed0(void* dst, const void* src, int a); // 0x0059aed0
void* FUN_00b3d240(...);                               // 0x00b3d240 (query builder)
void* FUN_00b3d3c0(...);                               // 0x00b3d3c0 (scan context getter)
void* FUN_00b3d350(...);                               // 0x00b3d350 (planet model / query context)
struct Query     { bool Run(); };                      // 0x00b35bf0
void* FUN_00b815a0(...);                               // 0x00b815a0 (transform point)
float FUN_00b7e390(...);                               // 0x00b7e390 (distance/radius)
void  FUN_0059c190(...);                               // 0x0059c190
void  FUN_0041cb40(...);                               // 0x0041cb40 (matrix ctor)
bool  FUN_006989d0(...);                               // 0x006989d0 (ray/segment test)
void* __fastcall FUN_00af9ff0(void* self, void* dummy, int i);  // 0x00af9ff0 (ret 4)
void  __fastcall FUN_00afa070(void* self, void* dummy, int kind); // 0x00afa070 (ret 4)
void* __fastcall FUN_00b81630(void* self, void* dummy, void* dst, void* src); // 0x00b81630 (ret 8)
typedef void* (__thiscall *PFN_Find)(void*, int);
typedef int   (__thiscall *PFN_Tag)(void*);
typedef bool  (__thiscall *PFN_Query)(void*);
struct ICamInfo {
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
    virtual Vec3* GetPos();      // 0x2c
    virtual Vec3* GetForward();  // 0x30
};
struct AvatarObj {
    uint8_t pad000[0xc0];
    ICamInfo* mCam;              // +0xc0
};
struct NounMgr {
    void* GetAvatar();           // 0x00b1fdb0
};
struct AppObj {};
struct Viewer { void __stdcall GetCameraLocationInfo(int, int, int, Vec3* out); }; // 0x007c3d30
typedef void* (__thiscall *PFN_NoArg)(void*);
NounMgr*  SP_NounManager();                       // 0x00b3d300
AppObj*   SP_App();                               // 0x0067dd10
Vec3*     FUN_0059aed0(Vec3* dst, const float* src, void* a);                  // 0x0059aed0
typedef void* (__thiscall *PFN_Bounds)(void*, void*);   // vtable +0x6c: float* bounds
typedef bool  (__thiscall *PFN_Test)(void*);            // vtable +0x48/+0x58
typedef float (__thiscall *PFN_Float)(void*);           // vtable +0x74
struct TransformObj { void FUN_00c897e0(void* xf); };  // 0x00c897e0 LocalToWorld
struct Xf { void FUN_004ff6d0(Vec3* p); };             // 0x004ff6d0 BackTransform
void* FUN_00449c20(...);                                // 0x00449c20 normalized_safe
bool FUN_00d99ff0(void* obj, uint flags);
static bool scanVisitor(void* p, uint flags);
static Vec3 boundsCentre(void* obj)
{
    Vec3  scratch;
    float* b = (float*)((PFN_Bounds)(*(void***)obj)[0x6c / 4])(obj, &scratch);
    Vec3  c;
    c.x = (b[0] + b[3]) * DAT_01471064;
    c.y = (b[1] + b[4]) * DAT_01471064;
    c.z = (b[2] + b[5]) * DAT_01471064;
    return c;
}
static bool scanVisitor(void* p, uint flags)
{
    char* o = (char*)p;
    if (*(int*)(o + 0x64) == 0) return false;
    void* q = *(void**)(o + 0x90);
    if (q != 0 && *(int*)((char*)q + 8) == 0x2e81370) return false;
    void* inner = *(void**)(o + 0x64);
    if (inner != 0) {
        void* got = ((PFN_Find)(*(void***)inner)[0x0c / 4])(inner, 0x1186577);
        if (got != 0) {
            if (FUN_00d99ff0(got, flags)) return false;
            return true;
        }
    }
    return false;
}
struct IObj {
virtual void d00();
virtual void d04();
virtual void d08();
    virtual void* Find(int tag);   // 0x0c
};
struct IObj2 {
virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
    virtual bool Query();          // 0x2c
};
struct ScanRec {                 // candidate record produced by the query helpers
    uint8_t  mSkip;              // +0x00 non-zero = ignore
    uint8_t  pad01[0xb];
    float    mX, mY, mZ;         // +0x0c
};
struct ScanObj {
    uint8_t  pad00[0x38];
    float    mX, mY, mZ;         // +0x38
    float    mRadius;            // +0x44
    uint8_t  pad48[0x2f];
    uint8_t  mLocal;             // +0x77
};
typedef void  (__fastcall *PFN_Sort)(void* self, void* dummy, Vec3* centre, float tag,
                                     void*** list, void* a5,
                                     bool (__cdecl *cb)(void*, uint), void* a7);
typedef float (__thiscall *PFN_Radius)(void*);          // vtable +0x74
typedef float*(__thiscall *PFN_Point)(void*);           // vtable +0x2c
typedef void  (__thiscall *PFN_Release)(void*);         // vtable +0xc0
void  __fastcall FUN_00b79c30(void* self, void* dummy, Vec3* centre, void* a,
                              int b, float c, void* d, void* e);   // 0x00b79c30 (ret 0x18)
void* __fastcall FUN_00b815a0(void* self, void* dummy, void* dst, float* p); // 0x00b815a0 (ret 8)
struct PM {
    float FUN_00b7e390();                       // 0x00b7e390 water height (thiscall)
};
struct Playable {
    void* Play(int a, int b);              // 0x00bc96a0
    void  ClearAll(int a, int b);          // 0x00bc98f0
};
// ---- items of slice s00d99ff0 end

// ---- items of slice s00d9af60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern float g_fltMax;        // 0x0147c190 (FLT_MAX)
extern "C" extern char  kWildAnimalSocial[];   // 0x0147c198
extern "C" extern char  kGiftInField[];        // 0x0147c1ac
struct Creature;                       // cSPCreatureBase / cSPCreatureCitizen
struct Loco;                           // cLocomotiveObject, addressed as creature + 0xc0
struct AnimHandle {
    char  pad0[0xc];
    int   mState;         // +0xc
    int   mId;            // +0x10
    int   mKind;          // +0x14
    float mValue;         // +0x18
    int   mExtra;         // +0x1c
};
struct BehaviorStimuli {
    AnimHandle* Play(uint flags, uint a);                 // 0x00bc96a0 (ret 8)
    void        ClearAll(uint flags, uint a);             // 0x00bc98f0 (ret 8)
    void        SetStimulus(uint flags, uint a, float f);// 0x00bc97f0 (ret 0x10)
    void*       GetAny();                                 // 0x00d997e0 (ret)
};
struct GoalTableEntry {               // at behaviour-tree-data + 0x1d0
    char pad0[8];
    int  mKey;                        // +0x08 (== 0x546e8804 when the table is live)
    int  mIndex;                      // +0x0c
};
struct BehaviorTreeData {
    char            pad0[0x8];
    BehaviorStimuli mStimuli;    // +0x08
    char            pad8[0x164 - 0x09];
    char            mTable[1];    // +0x164 (stride-0xac entries, field 0 read by 0x00d9b480)
    char            pad164[0x1d0 - 0x165];
    GoalTableEntry  mGoalTable;   // +0x1d0
};
struct BehaviorMgr;                       // cAgentOrderManager singleton
BehaviorMgr* FUN_00bc9b00();              // 0x00bc9b00 (0-arg getter)
struct BehaviorMgr {
    AnimHandle* FindNode(uint type, void* fn, void* blk);                          // 0x00bca620 (ret 0xc)
    AnimHandle* AddOrder(uint type, uint size, uint nounId, const char* name);     // 0x00bcb0b0 (ret 0x10)
    void        SetNode(AnimHandle* st, void* creature, void* res, void* fn);      // 0x00bcb480 (ret 0x10)
    void        Activate(int a, int b, void* c, float f, void* d, void* e);        // 0x00bca810 (ret 0x18)
    int         FindSlot(int a, int b, int c, int d);                              // 0x00bca0c0 (ret 0x10)
    Creature*   At(int idx);                                                       // 0x00bc9b10 (ret; [ecx+0x14]+idx)
    bool        IsEmpty();                                                         // 0x00bc9b50 (ret)
    char        pad0[0x1a4];
    int         mKey1a4;                                                           // +0x1a4
    int         mKey1a8;                                                           // +0x1a8
};
struct Creature {
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
virtual void s0a();
virtual void s0b();
virtual void s0c();
virtual void s0d();
virtual void s0e();
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1a();
virtual void s1b();
virtual void s1c();
virtual void s1d();
virtual void s1e();
virtual void s1f();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s2a();
virtual void s2b();
virtual void s2c();
virtual void s2d();
virtual void s2e();
virtual void s2f();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s3a();
virtual void s3b();
virtual void s3c();
virtual void s3d();
virtual void s3e();
virtual void s3f();
    virtual void s40();
    virtual void SetTarget(void* o, int a, int b);        // +0x84 (slot 0x84/4)
    virtual void* QueryObj(uint id);                      // +0x18c (slot 0x18c/4)
    char   pad4[0xc - 4];
    float  mX;                                            // +0x0c (compared by 0x00d9b4e0)
    char   pad10[0x34 - 0x10];
    int    mSub34;                                        // +0x34 (agent-order node key)
    char   pad38[0x1a4 - 0x38];
    int    mOrderKey1a4;                                  // +0x1a4
    int    mOrderKey1a8;                                  // +0x1a8 (compared by 0x00d9b2d0)
    char   pad1ac[0xb20 - 0x1ac];
    void*  mpAux;                                         // +0xb20
    char   padb24[0xb28 - 0xb24];
    char   mGroupData[0x20];                              // +0xb28
    BehaviorMgr* mpAgentOrders;                           // +0xb48
    BehaviorTreeData* mpBehaviorTreeData;                 // +0xb4c
    char   padb50[0xb54 - 0xb50];
    int    mpAnimating;                                   // +0xb54 (cAnimatingCreature*)
    uint   mFlagsB58;                                     // +0xb58

    Loco*  GetLoco();                                     // this + 0xc0
    uint   GetNounID();                                   // virtual +0x20
    int    GetSocialGoal();                               // 0x00c0e6a0
    int    GetTribe();                                    // 0x00c22f50 (citizen)
    bool   IsLeader();                                    // 0x00c232d0 (citizen)
    bool   IsAnimFinished(void* h);                       // 0x00c12400 (ret 0x1c)
    uint   InterruptAnim(uint a, int b, int c);           // 0x00c12310
    void   FUN_00c14750(bool v);                          // 0x00c14750
    int    FUN_00c0c1a0();                                // 0x00c0c1a0
};
struct Loco {
    char pad0[0xc0];
};
struct cSPUISocialRainbow {
    void StartFill(int side, int seg, float minRate, float rate, float frac, uint color, int p); // 0x00e33ab0 (ret 0x1c)
};
struct SocialWidget {
    bool  Check0(int a, int b);              // 0x00e31aa0 (ret 8)
    bool  IsBusy();                          // 0x00e31a90 (ret)
    float Get(int a);                        // 0x00e31a30 (ret 4)
    void  Set(int a, float f);               // 0x00e319d0 (ret 8)
    void  Fade(int a, float f, float g);     // 0x00e32460 (ret 0xc)
    void  Clear(int a);                      // 0x00e324f0 (ret 4)
    void  Reset();                           // 0x00e31c90 (ret)
    void  SetNode(int a);                    // 0x00e31cb0 (ret 4)
};
struct SocialValues {
    float mTotal;                       // +0x00
    float mFillRate;                    // +0x04
    float mDrainAmount;                 // +0x08
    bool  mbDrain;                      // +0x0c
    bool  mbFailed;                     // +0x0d
    char  pad0e[6];
    bool  mbTimerRunning;               // +0x14
    char  pad15[3];
    int   mHandle0;                     // +0x18 (behaviour node / anim handle)
    int   mHandle1;                     // +0x1c
    SocialWidget* mpWidget;             // +0x20 (cSPUISocialRainbow-ish UI object)

    bool  AnyActive();                                             // 0x00d9b010 (thiscall)
    void  SetDrainDelay(bool v);                                  // 0x00d9b040
    void  StartFillRight(float rate, float d);                     // 0x00d9b090
    void  StartFillLeft(float rate, float d);                      // 0x00d9b0d0
    void  Update(int a0, int a1, Creature* c0, Creature* c1);     // 0x00d9ba60 (thiscall, ret 0x10)
};
void*  SP_MessageServer();                                // 0x00b5b800-ish; see 0x00da6270 family
int    FUN_00d998d0(int handle, uint key);                // 0x00d998d0
int    FUN_00d99500(void* p);                             // 0x00d99500
int    FUN_00d994c0(void* p);                             // 0x00d994c0
void*  FUN_00d999d0(int handle);                          // 0x00d999d0 (WatchMemoryBlock)
void   FUN_00da6270(Creature* c, int state);              // 0x00da6270
void*  FUN_00b3d2b0(int a, void* b);                      // 0x00b3d2b0 (ret 8)
void   FUN_00ac7de0(void* p);                             // 0x00ac7de0 (thiscall)
void   GetAny_00d997e0(void* p);                          // 0x00d997e0
// ---- items of slice s00d9af60 end

// ---- items of slice s00d9bee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __stdcall FUN_00b3d480(void* p);
extern "C" void* __cdecl FUN_00c8ea70(void* p);
extern "C" float g_147c194;    // 0x0147c194  1.5258789e-05
extern "C" float g_1473c70;    // 0x01473c70  10.0f
#pragma warning(disable : 4100)
typedef unsigned int u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
extern "C" void* __cdecl FUN_00d99500_s00d9_bee0(void* p);
struct cSPCreatureBase_s00d9_bee0;
struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};
struct ICreatureNoun : VPad<6, IRefCount> {              // slots 0x08..0x1c
    virtual u32 GetNounID();                             // +0x20 (slot 8)
};
struct ICreatureVerb : VPad<24, ICreatureNoun> {         // slots 0x24..0x80
    virtual void* FUN_84(void* p, int a, int b);         // +0x84 (slot 33)
};
struct ICreatureCombat : VPad<11, ICreatureVerb> {       // slots 0x88..0xb0
    virtual void* FUN_b4(int slot);                      // +0xb4 (slot 45)
};
struct ICreatureMisc : VPad<7, ICreatureCombat> {        // slots 0xb8..0xd0
    virtual bool FUN_d4();                               // +0xd4 (slot 53)
};
struct ILocoPos : VPad<11, IEmpty> {
    virtual const Vec3* GetPosition();                   // +0x2c (slot 11)
};
struct ILocoRadius : VPad<17, ILocoPos> {
    virtual float GetRadius();                           // +0x74 (slot 29)
};
struct cLocomotiveObject_s00d9_bee0 : VPad<29, ILocoRadius> {
    virtual void FUN_ec();                               // +0xec (slot 59)

    bool  IsNearGoal();                                  // 0x00c42e20
    void* FUN_00c41ec0();                                // 0x00c41ec0  -> object with flags at +0x70
};
struct behavior_stimuli {
    void* Play(int a, int b);                            // 0x00bc96a0
    void  FUN_00bc97f0(int a, int b, float c, void* d);  // 0x00bc97f0
    void  ClearAll(int a, int b);                        // 0x00bc98f0
    void* GetAny();                                      // 0x00d997e0
};
struct cMemoryBlockSlot {                                // stride 0xc
    bool  mbUsed;                                        // +0x00
    u8    pad01[3];
    void* mpObject;                                      // +0x04
    u32   mExtra;                                        // +0x08
};
struct cMemoryBlock {
    u8              pad000[0x18];
    u32             mCount;                              // +0x18
    u8              pad01c[0x04];
    cMemoryBlockSlot mSlots_20[0x21];                    // +0x20 .. 0x1ac
    cSPCreatureBase_s00d9_bee0* mpOwner;                            // +0x1ac
};
struct cBehaviorTree {
    void*            mpVtbl;                             // +0x00
    u8               pad04[0x04];
    behavior_stimuli mStimuli_08;                        // +0x08
    u8               pad09[0x600 - 0x09];
    cMemoryBlock*    mpBlock_600;                        // +0x600

    void PopFront();                                     // 0x00bcaf40
};
struct cCreatureCombatPart {                             // subobject at creature+0x34
    u8    pad00[0x01];
    void* FUN_00cee330();                                // 0x00cee330
};
struct cSPCreatureBase_s00d9_bee0 : ICreatureMisc {
    u8                  pad04[0x34 - 0x04];
    cCreatureCombatPart mCombatPart_34;                  // +0x34
    u8                  pad35[0xc0 - 0x35];
    cLocomotiveObject_s00d9_bee0   mLoco_c0;                        // +0xc0
    u8                  padc4[0xb4c - 0xc4];
    cBehaviorTree*      mpTree_b4c;                      // +0xb4c
    u32                 padb50[0x02];
    u32                 mFlags_b58;                      // +0xb58
    u8                  padb5c[0xfc8 - 0xb5c];
    u32                 mStealthTime_fc8;                // +0xfc8

    void*                  ApplyCombatTarget();          // 0x00c0ee90
    cSPCreatureBase_s00d9_bee0*       GetTargetAsCreature();        // 0x00c0ee70
    void*                  GetSocialGoal();              // 0x00c0e6a0
    void                   MoveToPointAtSpeed(int mode, const Vec3* p, float a, float b);       // 0x00c1c1d0
    void                   MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* dir,
                                                        float a, float b);                        // 0x00c1c5c0
    void*                  PlayAnimation(u32 id, int a, int b);                                  // 0x00c12190
    bool                   AnimationFinished(void* h);                                            // 0x00c12400
    void*                  PlayAnimationWithTarget(u32 id, void* target, int a, int b);           // 0x00c14940
    void*                  PlayAnimationWithTargetPos(u32 id, const Vec3* p, int a);              // 0x00c14910
    void*                  FindSlotByCombatant(int slot, u32* out);                                // 0x00c0fa10
    void                   ApplyWave(float f);                                                    // 0x00c15dc0
};
struct cCargoManager {
    void FUN_00aca360();                                 // 0x00aca360
    void FUN_00acd2d0();                                 // 0x00acd2d0
};
struct cFloatVec {
    u8    pad00[0x10];
    void* mpData_10;                                     // +0x10  element base
    int   mCount_14;                                     // +0x14  element count
    int   mCap_18;                                       // +0x18  capacity

    void push_back(float a, float b);                    // 0x00e315f0
};
struct cScaleHelper {
    u8    pad000[0x0c];
    void* mpField_0c;                                    // +0x0c  -> object whose +0x550 is read
    u8    pad10[0x34 - 0x10];
    float mFloat_34;                                     // +0x34
    float mFloat_38;                                     // +0x38
    u8    pad3c[0xe8 - 0x3c];
    cFloatVec* mpVec_e8;                                 // +0xe8  spd vector of float pairs
    int   mField_ec;                                     // +0xec

    void FUN_00d9ccc0(float a, float b);                 // 0x00d9ccc0
};
// ---- items of slice s00d9bee0 end

// ---- items of slice s00d9cd90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  __cdecl FUN_00a75010(void* x);                    // 0x00a75010
extern "C" int   __cdecl FUN_00afa5d0(void* pos);                  // FindClosestFreeSlot
extern "C" void* __cdecl FUN_00af9ff0(void* circle, int idx);      // SlotAt
extern "C" void  __cdecl FUN_00afa030(void* slot, void* creature); // tSlot::Reserve
extern "C" void  __cdecl FUN_00c1c5c0(void* creature, int style, void* dst, void* face, float a, float b); // MoveToPoint
extern "C" void* __cdecl FUN_00c41ec0(void* x);                    // 0x00c41ec0
extern "C" void* __cdecl FUN_00449c20(void* out, float* v, float a, float b); // normalized_safe
extern "C" char  __cdecl FUN_00c42e20(void* x);                    // IsNearGoal
extern "C" void  __cdecl FUN_00c12310(void* creature, int a, int b, int c);   // InterruptAnimation
extern "C" char  __cdecl FUN_00c123f0(void* creature, int x);      // AnimationFinished
extern "C" void  __cdecl FUN_00bc98f0(void* tree, int a, int b);   // ClearAll
extern "C" void  __cdecl FUN_00bcafe0(void* x, int y);             // 0x00bcafe0
extern "C" char  __cdecl FUN_00ac0730(void* a, void* b);           // 0x00ac0730
extern "C" void  __cdecl FUN_00d9b950(void* arr, void* a, int n, float f1, float f2,
                                      float f3, float f4, float f5, float f6,
                                      float f7, float f8, void* cmp);  // 0x00d9b950
extern "C" void  __cdecl FUN_00d9b9b0(void* arr, void* a, int n, float f1,
                                      float f2, float f3);         // 0x00d9b9b0
extern "C" void  __cdecl FUN_00c0ba10(void* creature);              // 0x00c0ba10
extern "C" int   __cdecl FUN_00c22dc0(void* creature);              // 0x00c22dc0
extern "C" void* __cdecl FUN_00c0bbd0(void* creature);             // 0x00c0bbd0 SP::cSPCreatureBase::GetSpeciesProfile
extern "C" char  __cdecl FUN_00c232d0(void* citizen);              // 0x00c232d0 SP::cSPCreatureCitizen::IsLeader
extern "C" void  __cdecl FUN_00d9ccc0(float a, float b);            // 0x00d9ccc0
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
inline void* VCall0(void* o, int off) { return ((void* (*)(void*))VFn(o, off))(o); }
inline void VCall3(void* o, int off, void* a, void* b, void* c) { ((void (*)(void*, void*, void*, void*))VFn(o, off))(o, a, b, c); }
inline void Copy8(int* d, int* s) {
  d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
  d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
}
struct S {
  void  FUN_00d9cd90();                              // 0x00d9cd90 SWARM tick
  void  FUN_00d9cf70();                              // 0x00d9cf70 AddAgent
  void  FUN_00d9d100(void* creature, int target);    // 0x00d9d100
  char  FUN_00d9d1e0(void* creature);                // 0x00d9d1e0
  float FUN_00d9d420(void* creature);                // 0x00d9d420
  void  FUN_00d9d570(void* owner);                   // 0x00d9d570
  char  FUN_00d9d5b0(void* creature, int block);     // 0x00d9d5b0
  int   FUN_00d9d840(int idx);                       // 0x00d9d840
  void  FUN_00d9d890(int* first, int* last);         // 0x00d9d890
  void  FUN_00d9d8d0(int* out, int* src, int* end, int* dst); // 0x00d9d8d0
  void  FUN_00d9d9a0(void* arr, int a, int n, int i, int v,
                     float f1, float f2, float f3, float f4,
                     float f5, float f6, float f7, void* cmp);  // 0x00d9d9a0
  void  FUN_00d9da80(void* arr, void* a, int n, int i, float f1,
                     float f2, float f3);                       // 0x00d9da80
  void  FUN_00d9db30(void* src, void* end, void* dst);          // 0x00d9db30
  char  FUN_00d9dba0(void* creature);                            // 0x00d9dba0
  void  FUN_00d9dc80(void* creature, void* block);               // 0x00d9dc80
};
struct Elem20 { int a; float f[7]; };
// ---- items of slice s00d9cd90 end

// ---- items of slice s00d9dce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct cMethodTable {
    void* mpSlots[0x100];                       // 0x000
};
class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    char CallChar(int nSlot) {
        return ((char (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cMethodTable* mpTable;                      // 0x000
};
class cBehaviorStimuli {
public:
    void ClearAll(uint32_t nFlags, uint32_t nValue);
    void* Play(uint32_t nFlags, uint32_t nValue);
};
class nBehaviorTree {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cBehaviorStimuli mStimuli;                  // 0x008

    uint8_t mPad_600[0x600 - 0x008 - sizeof(cBehaviorStimuli)];
    void* mpCurrentTask;                        // 0x600
};
struct cFoundTarget {
    void* mpObject;                             // 0x000
    uint32_t mnField04;                         // 0x004
    uint32_t mnField08;                         // 0x008
    uint32_t mnField0c;                         // 0x00c
    float mfField10;                            // 0x010
    uint32_t mnField14;                         // 0x014
};
struct cBehaviorCallback {
    void* mpTarget;                             // 0x000
    void* mpOwner;                              // 0x004
    void* mpHandler;                            // 0x008
};
class cLocationComponent {
public:
    void* GetObject();
    void* GetOwner();
};
class cSimCreature {
public:
    void* GetCombatTarget();
    void* GetTargetCreature();
    void* GetActionObject();
    int32_t GetBehaviorPhase();
    char IsGroupLeader();
    int32_t InterruptAnimation(uint32_t nAnimId, int32_t nA, int32_t nB);
    char AnimationFinished(uint32_t nAnimId);
    char WaitForAnimEvent(uint32_t nEventId, void* pData, int32_t nA,
                          uint32_t nAnimId, int32_t nB);
    void SetCombatEngaged(char bEngaged);
    void StopLocomotion(int32_t nA, int32_t nB);
    void* GetTargetData();
    void UpdatePose();
    void ResetPose();
    void UpdateTargetPose();
    void UpdateAttackTarget();
    void NotifyTargetLost();
    void UpdateWorldTarget();
    void* GetTargetRecord();

    uint8_t mPad000[0x34];                      // 0x000
    cLocationComponent mLocation;               // 0x034
    uint8_t mPad038[0x88];                      // 0x038
    cDispatchObject mMovement;                  // 0x0c0
    uint8_t mPad0c4[0xa88];                     // 0x0c4
    nBehaviorTree* mpBehaviorTree;              // 0xb4c
};
class cEpisodeObject {
public:
    void* GetRecord();
};
class cBehaviorHandler {
public:
    virtual void Method00();                    // slot 0x00
    virtual void Method04();                    // slot 0x04
};
class cPoolObject {
public:
    virtual void Destroy(char bFree);           // slot 0x00
    virtual void AddRef();                      // slot 0x04
};
void* __stdcall BehaviorManager(cSimCreature* pCreature);
void* GetObjectFromId(void* pId);
void* WatchMemoryBlock(void* pBlock);
// ---- items of slice s00d9dce0 end

// @ 0x00d90640
namespace SP {
float FUN_00d90640(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint32_t flags, void* pStimuli, char* pOut)
{
    cGameObject* pSel = 0;
    void* pVar = FUN_00d51660();
    if ((flags & 0x800000) != 0)
        return 0.0f;
    if ((flags & 0x400) == 0) {
        if (pVar == 0)
            return 0.0f;
        if ((((uint32_t*)pVar)[0x6c / 4] >> 2 & 1) == 0)
            return 0.0f;
    }

    Vec3* pPos = p->mLoco.GetPosition();
    float bestSq;

    if (p->Flag388()) {
        AuxGeom* pAux = (AuxGeom*)p->mLoco.GetAux68();
        float r = (pAux->f14 - pAux->f08) + 20.0f;
        bestSq = r * r + 1600.0f;

        void** it = (void**)p->mp140C;
        void** itEnd = (void**)p->mp1410;
        if (it == itEnd)
            return 0.0f;
        if (!FUN_00c03520(*it))
            FUN_00b3d870(&it);
        if (it == itEnd)
            return 0.0f;
        do {
            void* pObj = ((IterEntry*)*it)->mpObject;
            if (pObj != 0) {
                cGameObject* pGO = (cGameObject*)pObj;
                if (pGO->GetType20() == (int)0x018ebadc && !FUN_00c38990(pObj, 1)) {
                    Vec3* pV = pGO->mLoco34.GetPosition();
                    float dz = pV->z - pPos->z, dy = pV->y - pPos->y, dx = pV->x - pPos->x;
                    float d = (dz * dz + dy * dy) + dx * dx;
                    if (bestSq > d) {
                        pSel = pGO;
                        bestSq = d;
                    }
                }
            }
            do {
                ++it;
                if (it == itEnd)
                    goto done;
            } while (!FUN_00c03520(*it));
        } while (it != itEnd);
    } else {
        cPlanetModel_s00d9_0640* pPlanet = PlanetModel();
        bestSq = 2900.0f;
        int* pVec = NounManager()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0,
                                                     FUN_00b1e500, (void*)0x018ebadc);
        void** pBegin = (void**)pVec[1];
        void** pEnd = (void**)pVec[2];
        if (pBegin == pEnd)
            return 0.0f;
        do {
            cGameObject* pObj = (cGameObject*)*pBegin;
            if (!FUN_00c38990(pObj, 1)) {
                Vec3* pV = pObj->mLoco34.GetPosition();
                float dz = pV->z - pPos->z, dy = pV->y - pPos->y, dx = pV->x - pPos->x;
                float d = (dz * dz + dy * dy) + dx * dx;
                if (bestSq > d) {
                    Vec3 surf;
                    pPlanet->DirectionToSurfacePosition(surf, pV);
                    float sz = pV->z - surf.z, sy = pV->y - surf.y, sx = pV->x - surf.x;
                    if (!(2500.0f <= (sz * sz + sy * sy) + sx * sx)) {
                        pSel = pObj;
                        bestSq = d;
                    }
                }
            }
            ++pBegin;
        } while (pBegin != pEnd);
    }

done:
    if (pSel == 0)
        return 0.0f;
    if (pStimuli != 0)
        ((nSPBehaviorTree::behavior_stimuli_s00d9_0640*)pStimuli)->GetAny();
    *pOut = 1;
    ((StimulusSlot*)pStimuli)->mpTarget = &pSel->mStimulus508;
    return 1.0f;
}
}  // namespace SP

// @ 0x00d90950
namespace SP {
float FUN_00d90950(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint32_t a4, void* pStimuli, char* pOut)
{
    int* pVec = NounManager()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ae72d0,
                                                 FUN_00b1e500, (void*)0x018c6de8);
    if (pVec[1] == pVec[2])
        return 0.0f;

    int id = p->GetIdentity();
    void** it = (void**)p->mp140C;
    void** itEnd = (void**)p->mp1410;
    if (it != itEnd) {
        if (!FUN_00c03520(*it))
            FUN_00b3d870(&it);
        while (it != itEnd) {
            void* pObj = ((IterEntry*)*it)->mpObject;
            if (pObj != 0) {
                cGameObject* pGO = (cGameObject*)pObj;
                if (pGO->GetType20() == (int)0x018c6de8 && pGO->GetIdentity4c() != id) {
                    if (pStimuli != 0)
                        ((nSPBehaviorTree::behavior_stimuli_s00d9_0640*)pStimuli)->GetAny();
                    *pOut = 1;
                    ((StimulusSlot*)pStimuli)->mpTarget = &pGO->mStimulus508;
                    return 1.0f;
                }
            }
            do {
                ++it;
                if (it == itEnd)
                    return 0.0f;
            } while (!FUN_00c03520(*it));
        }
    }
    return 0.0f;
}
}  // namespace SP

// @ 0x00d90a60
namespace SP {
float FUN_00d90a60(cSPCreatureCitizen_s00d9_0640* p)
{
    if (GetCurrentGameMode() == (void*)0x01654c05 && p->mf5E0 <= 0.0f)
        return 1.0f;
    if (GetCurrentGameMode() == (void*)0x01654c04)
        if (p->mf5E0 < p->mCommunity.GetCap58())
            return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d90b20
namespace SP {
bool FUN_00d90b20(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint32_t a4, void* a5, BehaviorStateOut* pOut)
{
    pOut->mf04 = 0.0f;
    pOut->mf0C = 10.0f;
    pOut->mf14 = 1.5f;
    pOut->m00 = 0;
    pOut->m08 = 0;
    pOut->m10 = 0;
    pOut->m18 = 0;
    if (p->mf5E0 <= 1.5258789e-05f) {
        FUN_00b3d310(&p->mLoco)->FUN_00b45410();
        cSPCreatureCitizen_s00d9_0640* q = p;
        q->Flag8c();
        pOut->mf0C = 10.0f;
        pOut->mf14 = 1.5f;
        pOut->m18 = 0;
    }
    return true;
}
}  // namespace SP

// @ 0x00d90bb0
namespace SP {
float FUN_00d90bb0(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint32_t a4, void* pStimuli, char* pOut)
{
    int a = p->mpB4C->mStimuli.Play(0, 0x80);
    int v = FUN_00d99a10(a);
    if (v == 0) {
        p->mpB4C->mStimuli.ClearAll(0, 0x80);
    } else {
        cGameObject* pObj = (cGameObject*)FUN_00d998f0(v);
        if (pObj != 0) {
            cGameObject* pChild = (cGameObject*)pObj->GetChild0c();
            if (pChild->GetType20() != (int)0x02a034cd) {
                if (pStimuli != 0)
                    ((nSPBehaviorTree::behavior_stimuli_s00d9_0640*)pStimuli)->GetAny();
                ((StimulusSlot*)pStimuli)->mpTarget = pObj;
                *pOut = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}
}  // namespace SP

// @ 0x00d90c40
namespace SP {
void FUN_00d90c40(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mpFB8->mnA30 -= 1;
}
}  // namespace SP

// @ 0x00d90c60
namespace SP {
char FUN_00d90c60(cSPCreatureCitizen_s00d9_0640* p)
{
    return !p->mLoco.IsNearGoal();
}
}  // namespace SP

// @ 0x00d90c80
namespace SP {
float FUN_00d90c80(void* a1, void* a2, void* a3, uint32_t flags)
{
    if ((flags & 1) == 0 && (flags & 0x1000) != 0)
        return 0.0f;
    return 1.0f;
}
}  // namespace SP

// @ 0x00d90ca0
namespace SP {
void FUN_00d90ca0(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mnFC0 = 3;
    p->FUN_00c0d0c0(2, 0);
    p->mpFB8->mnA28 -= 1;
}
}  // namespace SP

// @ 0x00d90cd0
namespace SP {
void FUN_00d90cd0(cSPCreatureCitizen_s00d9_0640* p)
{
    p->SetSprinting(0);
}
}  // namespace SP

// @ 0x00d99470
cSPCreatureBase* ExtinguishTarget(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && !pCreature->mB5e && pCreature->mB135 &&
        !pCreature->IsUnavailable()) {
        if (CastCreature(pCreature, 0x18eb45e) == 0 || (pCreature->mB58 & 4) == 0)
            return pCreature;
    }
    return 0;
}

// @ 0x00d994c0
cSPCreatureBase* FireTarget(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && pCreature->GetTypeID() == 0x18eb4b7 && !pCreature->mB5e &&
        pCreature->mB135 && !pCreature->IsUnavailable())
        return pCreature;
    return 0;
}

// @ 0x00d99550
int32_t IsAnimRunning(cAnimState* pState)
{
    if (pState == 0 || pState->mfProgress < 1.0f)
        return true;
    return false;
}

// @ 0x00d99570
bool PlayIdleAnimation(cSPCreatureBase* pCreature, uint32_t nAnimID, uint32_t nFlags)
{
    if (pCreature == 0 || pCreature->mB4c == 0)
        return false;
    cAnimState* pState = pCreature->mB4c->mPlayer.Play(nAnimID, nFlags);
    if (pState == 0 || pState->mfProgress < 1.0f)
        return true;
    return false;
}

// @ 0x00d995c0
bool RingNodeMatches(cTreeRing* pRing, const uint32_t* pValue)
{
    uint32_t nValue = *pValue;
    bool bMatches = pRing->mpNodes[(pRing->mnIndex + 3) * 3]->GetID() == nValue;
    return bMatches;
}

// @ 0x00d995f0
void ForwardWalkTree(float fA, double dB, void* pC, void* pD, void* pE, void* pF, void* pG, void* pH)
{
    WalkTree(fA, dB, pC, pD, pE, pF, pG, pH);
}

// @ 0x00d99630
bool StepIndex(int32_t* pnValue, int32_t* pnStep, bool* pbBounced, int32_t nLimit, int32_t nMode)
{
    *pbBounced = false;
    switch (nMode) {
    case 0: {
        int32_t nNext = *pnValue + *pnStep;
        if (nNext < 0 || nNext >= nLimit) {
            *pbBounced = true;
            *pnStep = -*pnStep;
        }
        *pnValue += *pnStep;
        return true;
    }
    case 1:
        if (*pnValue == nLimit - 1)
            return false;
        (*pnValue)++;
        return true;
    case 2:
        if (*pnValue == nLimit - 1) {
            *pnValue = 0;
            return true;
        }
        (*pnValue)++;
        return true;
    }
    return false;
}

// @ 0x00d996b0
void MakeStimulusDesc(uint32_t nID, uint32_t nUnused, const Vector3* pOffset, sStimulusDesc* pOut)
{
    pOut->mID = nID;
    pOut->mMax = 1;
    pOut->mCount = 1;
    pOut->mOffset = *pOffset;
}

// @ 0x00d996e0
void CopyStimulusFlat(const sStimulusFlat* pSrc, sStimulusRotated* pDst)
{
    pDst->mFieldSrc00 = pSrc->mField00;
    pDst->mFieldSrc04 = pSrc->mField04;
    pDst->mOffset = pSrc->mOffset;
    pDst->mFieldSrc08 = pSrc->mField08;
    pDst->mField18 = pSrc->mField18;
    pDst->mField1c = pSrc->mField1c;
    pDst->mField20 = pSrc->mField20;
    pDst->mf24 = pSrc->mf24;
}

// @ 0x00d99730
void AssignStimulus(const sStimulusRecord* pSrc, sStimulusAssignment* pDst)
{
    pDst->mpA = pSrc->mpA;
    pDst->mpB = pSrc->mpB;
    pDst->mOffset = pSrc->mOffset;
    pDst->mpC = pSrc->mpC;
    pDst->mField18 = pSrc->mField18;
    pDst->mField1c = pSrc->mField1c;
    pDst->mField20 = pSrc->mField20;
    pDst->mf24 = pSrc->mf24;
}

// @ 0x00d99a10
cSPCreatureBase* GetStimulusCreature(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0x13f94d4);
            if (pCreature != 0) {
                cCreatureStatus* pStatus = pCreature->GetStatus();
                if (pStatus->mIsAlive && !pCreature->GetOwner()->IsUnavailable())
                    return pCreature;
            }
        }
    }
    return 0;
}

// @ 0x00d99a60
float DistanceBetweenBodies(const Vector3* pA, float fRadiusA, const Vector3* pB, float fRadiusB, bool bClamp)
{
    Vector3 d;
    d.x = pA->x - pB->x;
    d.y = pA->y - pB->y;
    d.z = pA->z - pB->z;

    float fDist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) - (fRadiusA + fRadiusB);
    if (bClamp) {
        // The clamp runs in the float domain (the original stores the distance, then
        // maxes it against zero), so the result is rounded to float before the compare.
        volatile float fStore = fDist;
        if (fStore < 0.0f)
            fStore = 0.0f;
        return fStore;
    }
    return fDist;
}

// @ 0x00d99ac0
float ComputeBodyDistance(cSpatialObject* pA, cSpatialObject* pB, uint32_t nFlag)
{
    if ((pA->mFlags50 & 0x1000) == 0 && (pB->mFlags50 & 0x1000) == 0) {
        float fRadiusB = pB->GetRadius((const Vector3*)nFlag);
        Vector3* pPosB = pB->GetPosition(fRadiusB);
        float fRadiusA = pA->GetRadius(pPosB);
        Vector3* pPosA = pA->GetPosition(fRadiusA);
        return DistanceBetweenBodies(pPosA, fRadiusA, pPosB, fRadiusB, (bool)nFlag);
    }

    Vector3* pPosA = pA->GetPosition(0.0f);
    float fScale = 1.0f / sqrtf(pPosA->x * pPosA->x + pPosA->y * pPosA->y + pPosA->z * pPosA->z);
    Vector3* pPosB = pB->GetPosition(fScale);
    float fDot = ((pPosB->y - pPosA->y) * (pPosA->y * fScale) +
                  (pPosB->z - pPosA->z) * (pPosA->z * fScale)) +
                 (pPosB->x - pPosA->x) * (pPosA->x * fScale);
    pPosB = pB->GetPosition(fScale);
    float fRadiusA = pA->GetRadius((const Vector3*)0);
    float fRadiusB = pB->GetRadius((const Vector3*)0);
    float fDz = pPosA->z - (pPosB->z - (pPosA->z * fScale) * fDot);
    float fDy = pPosA->y - (pPosB->y - (pPosA->y * fScale) * fDot);
    float fDx = pPosA->x - (pPosB->x - (pPosA->x * fScale) * fDot);
    float fDist = sqrtf(fDx * fDx + (fDy * fDy + fDz * fDz)) - (fRadiusA + fRadiusB);
    if (nFlag != 0 && fDist < 0.0f)
        fDist = 0.0f;
    return fDist;
}

// @ 0x00d99cd0
float RecursiveSurfaceProbe(const Vector3* pFrom, const Vector3* pDir, float fLow, float fHigh)
{
    if (fHigh - fLow <= 2.0f)
        return fLow;
    float fMid = (fHigh - fLow) * 0.5f + fLow;
    cPlanetModel* pPlanet = PlanetModel_s00d9_90a0();
    Vector3 pt;
    pt.x = pFrom->x + pDir->x * fMid;
    pt.y = pFrom->y + pDir->y * fMid;
    pt.z = pFrom->z + pDir->z * fMid;
    pt = pPlanet->DirectionToSurfacePosition(pt);
    float fWater = pPlanet->GetWaterHeight();
    if (pt.z * pt.z + pt.y * pt.y + pt.x * pt.x > fWater * fWater)
        return RecursiveSurfaceProbe(pFrom, pDir, fMid, fHigh);
    return RecursiveSurfaceProbe(pFrom, pDir, fLow, fMid);
}

// @ 0x00d99e20
void ProjectToSurface(const Vector3* pFrom, Vector3* pTo)
{
    if (pFrom->x == pTo->x && pFrom->y == pTo->y && pFrom->z == pTo->z)
        return;
    cPlanetModel* pPlanet = PlanetModel_s00d9_90a0();
    float fWater = pPlanet->GetWaterHeight();
    float fWaterSq = fWater * fWater;
    if (pFrom->y * pFrom->y + pFrom->z * pFrom->z + pFrom->x * pFrom->x <= fWaterSq) {
        *pTo = pPlanet->SnapToSurface(*pTo);
        return;
    }
    if (fWaterSq <= pTo->z * pTo->z + pTo->y * pTo->y + pTo->x * pTo->x)
        return;
    Vector3 dir;
    dir.x = pTo->x - pFrom->x;
    dir.y = pTo->y - pFrom->y;
    dir.z = pTo->z - pFrom->z;
    float fLen = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    float fInv = 1.0f / fLen;
    dir.x = dir.x * fInv;
    dir.y = dir.y * fInv;
    dir.z = dir.z * fInv;
    float fHit = RecursiveSurfaceProbe(pFrom, &dir, 0.0f, fLen);
    pTo->z = dir.z * fHit + pFrom->z;
    pTo->x = pFrom->x + dir.x * fHit;
    pTo->y = pFrom->y + dir.y * fHit;
}

// @ 0x00d99ff0
bool FUN_00d99ff0(void* obj, uint flags)
{
    void* p;
    int   tag;
    if (obj == 0) goto fail;
    p = ((PFN_Find)(*(void***)obj)[0xb8 / 4])(obj, 0x17f243b);
    if (p == 0) goto fail;
    tag = ((PFN_Tag)(*(void***)p)[0x20 / 4])(p);

    if (tag > 0x2c9cc91) {
        if (tag > 0x3ed8573) {
            if (tag == 0x52aa6122) return true;
            goto fail;
        }
        if (tag == 0x3ed8573) return true;
        if (tag == 0x2e72cae) return true;
        if (tag != 0x3a2511e) goto fail;
        {
            void* r = FUN_00ac80d0(p, tag);
            if (*(int*)((char*)r + 0x108) == 0) goto fail;
        }
        return true;
    }
    if (tag == 0x2c9cc91) return true;
    if (tag > 0x18c88e4) {
        if (tag == 0x18eb45e || tag == 0x18eb4b7) {
            if ((flags & 1) == 0) return true;
            {
                char* c = (char*)CastCreature(obj);
                if (c[0x137] == 0) return true;
                if (c[0xb5e] != 0) return true;
                void* vt = (char*)c + 0xc0;
                char* r = ((C41Obj*)vt)->Method();
                if (*(int*)(r + 0x5c) == 0) return false;
                if (((PFN_Query)(*(void***)vt)[0xf8 / 4])(vt)) return true;
            }
            return false;
        }
        goto fail;
    }
    if (tag == 0x18c88e4) {
        void* r = FUN_00ac80d0(p, tag);
        int v = *(int*)((char*)r + 0x228);
        if (v == 0x5b9a06e) return false;
        if (v != 0x5d97f762) return true;
        return false;
    }
    if (tag == 0x18c431c) return true;
    if (tag == 0x18c84a9) return true;
    goto fail;

fail:
    return *(uint8_t*)((char*)obj + 0x71) == 0;
}

// @ 0x00d9a110
bool FUN_00d9a110(void* ea, void* param)
{
    float* pmax = (float*)ea;
    float* pf = *(float**)param;
    int    n = (int)(*(int*)((char*)param + 4) - (int)pf) / 12;
    float* other = *(float**)ea;
    int    i;
    if (n <= 0) return false;
    for (i = 0; i < n; ++i) {
        if (pf[0] != other[0]) return true;
        if (pf[1] != other[1]) return true;
        if (pf[2] != other[2]) return true;
        pf += 3;
        other += 3;
    }
    (void)pmax;
    return false;
}

// @ 0x00d9a190
int FUN_00d9a190(void* ecxObj, float* eaxPt)
{
    float* pf = *(float**)ecxObj;
    int    n = (*(int*)((char*)ecxObj + 4) - (int)pf) / 12;
    float  dx = pf[0] - eaxPt[0];
    float  dy = pf[1] - eaxPt[1];
    float  dz = pf[2] - eaxPt[2];
    float  best = dx * dx + dy * dy + dz * dz;
    best = sqrtf(best);
    int    bi = 0;
    int    i;
    if (n <= 1) return bi;
    for (i = 1; i < n; ++i) {
        float* q = pf + i * 3;
        float ax = q[0] - eaxPt[0];
        float ay = q[1] - eaxPt[1];
        float az = q[2] - eaxPt[2];
        float d = ax * ax + ay * ay + az * az;
        d = sqrtf(d);
        if (d < best) {
            bi = i;
            best = d;
        }
    }
    return bi;
}

// @ 0x00d9a290
void FUN_00d9a290(int a1, void* a2, void* a3, int* a4)
{
    int noun;
    int off;
    char* rec;
    int v;
    if (a2 == 0) return;
    if (a1 == 0) return;
    *a4 = a1;
    noun = (int)((DB*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3e8a0(*(int*)a2);
    off = a1 * 0x4e0;
    rec = (char*)(*(int*)(noun + 0x70) + off);
    v = *(int*)(rec + 0x4b8);
    if (!((v == 6) || (v == 4) || (rec[0x4c8] != 0))) return;
    if (!FUN_00d9a110((void*)(*(int*)((char*)a2 + 0x28) + a1 * 0x34 - 0x18),
                     (void*)(*(int*)((char*)a2 + 0x28) + a1 * 0x34 + 0x1c))) return;
    a4[1] = FUN_00d9a190((char*)a2 + 0x28 + a1 * 0x34 - 0x18 + 0x1c, (float*)a3);
    {
        int noun2 = (int)((DB*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3e8a0(*(int*)a2);
        if (*(int*)(*(int*)(noun2 + 0x70) + off - 0x28) == 6 &&
            *(int*)(rec + 0x4b8) == 4) {
            a4[3] = *(int*)a3;
            a4[4] = *(int*)((char*)a3 + 4);
            a4[5] = *(int*)((char*)a3 + 8);
        }
    }
}

// @ 0x00d9a360
bool FUN_00d9a360(Vec3* io, Vec3* out)
{
    AvatarObj* avatar = (AvatarObj*)((NounMgr*)SP_NounManager())->GetAvatar();
    void* app = (void*)SP_App();
    void* viewer = ((PFN_NoArg)(*(void***)app)[0x50 / 4])(app);
    viewer = ((PFN_NoArg)(*(void***)viewer)[0x1c / 4])(viewer);
    if (viewer == 0 || avatar == 0) return false;

    ((Viewer*)viewer)->GetCameraLocationInfo(0, 0, 0, io);

    ICamInfo* cam = avatar->mCam;
    Vec3* pos = cam->GetPos();
    float dx = pos->x - io->x;
    float dy = pos->y - io->y;
    float dz = pos->z - io->z;
    float* fwd = (float*)cam->GetForward();

    Vec3 tmp;
    float* r = (float*)FUN_0059aed0(&tmp, &DAT_0169f2f4, (void*)fwd);
    (void)r;
    float nx = r[0], ny = r[1], nz = r[2];
    float d = nz * dz + nx * dx + ny * dy;
    out->x = dx - d * nx;
    out->y = dy - ny * d;
    out->z = dz - nz * d;
    return true;
}

// @ 0x00d9a4a0
Vec3* FUN_00d9a4a0(Vec3* out, void* a2, void* obj)
{
    // Reference point = half-extent centre of the object's bounds (slot 0x6c).
    char* o = (char*)obj;
    Vec3  c = boundsCentre(o);
    *out = c;

    // Selection/action-circle pass: when the object is not already selected, ask the
    // action circle (a2+0xc0) whether the point should be pulled to its surface.
    bool reprojected = false;
    if ((*(uint8_t*)(o + 0x50) & 0x10) == 0) {
        char* circle = (char*)a2 + 0xc0;
        bool ok = ((PFN_Test)(*(void***)circle)[0x58 / 4])(circle);
        if (!ok) ok = ((PFN_Test)(*(void***)o)[0x48 / 4])(o);
        if (!ok) ok = ((PFN_Test)(*(void***)circle)[0x48 / 4])(circle);
        if (ok) {
            Vec3  ref;
            Vec3* rb = (Vec3*)((PFN_Bounds)(*(void***)circle)[0x6c / 4])(circle, &ref);
            ref.x = out->x;
            ref.y = out->y;
            ref.z = (rb->z + *(float*)((char*)rb + 8)) * DAT_01471064;
            c = boundsCentre(o);
            void* q = FUN_00b3d240(o, &ref, &c, out);
            reprojected = ((Query*)q)->Run();
        }
    }

    // Projected path: build the object->world transform, back-transform both the
    // circle centre and the current point, then clip against the circle plane.
    if (((PFN_Test)(*(void***)o)[0x48 / 4])(o) && !reprojected) {
        float xf[0x20];
        // transform header: rotation rows at +0x18, translation at +0x04,
        // uniform scale at +0x4c (the original fills these from .rdata).
        for (int i = 0; i < 0x20; i++) xf[i] = 0.0f;
        ((float*)xf)[0x04] = 0.0f;
        ((float*)xf)[0x05] = DAT_0169f2a4;
        ((float*)xf)[0x06] = DAT_0169f2a8;
        ((float*)xf)[0x07] = DAT_0169f2ac;
        ((float*)xf)[0x08] = 1.0f;
        FUN_0041cb40(&((float*)xf)[0x18], &DAT_0169f300);
        ((TransformObj*)o)->FUN_00c897e0(xf);

        void* u = ((PFN_NoArg)(*(void***)o)[0x68 / 4])(o);
        Vec3  p1 = boundsCentre((char*)a2 + 0xc0);
        ((Xf*)xf)->FUN_004ff6d0(&p1);
        ((Xf*)xf)->FUN_004ff6d0(out);

        float t = 0.0f;
        if (FUN_006989d0(&p1, out, u, &t)) {
            out->x = (out->x - p1.x) * t + p1.x;
            out->y = (out->y - p1.y) * t + p1.y;
            out->z = (out->z - p1.z) * t + p1.z;
            if (((int*)xf)[0] & 2) {
                float x = out->x, y = out->y, z = out->z;
                out->x = ((float*)xf)[0x14] * z + ((float*)xf)[0x11] * y + ((float*)xf)[0x0e] * x;
                out->y = ((float*)xf)[0x15] * z + ((float*)xf)[0x12] * y + ((float*)xf)[0x0f] * x;
                out->z = ((float*)xf)[0x16] * z + ((float*)xf)[0x13] * y + ((float*)xf)[0x10] * x;
            }
            float s = ((float*)xf)[0x13];
            out->x = s * out->x + ((float*)xf)[0x01];
            out->y = s * out->y + ((float*)xf)[0x02];
            out->z = s * out->z + ((float*)xf)[0x03];
            return out;
        }

        // No clipping result: push the point out to the object radius along the
        // normalized direction from the circle centre.
        float r = ((PFN_Float)(*(void***)o)[0x74 / 4])(o);
        Vec3  centre = boundsCentre((char*)a2 + 0xc0);
        Vec3  d;
        d.x = centre.x - out->x;
        d.y = centre.y - out->y;
        d.z = centre.z - out->z;
        Vec3  tmp;
        float* n = (float*)FUN_00449c20(&tmp, &d);
        out->x = out->x + n[0] * r;
        out->y = out->y + n[1] * r;
        out->z = out->z + n[2] * r;
    }
    return out;
}

// @ 0x00d9a9c0
bool FUN_00d9a9c0(void* a1, void* a2)
{
    char* p = (char*)a1;
    if (*(int*)(p + 0x64) == 0) return true;
    {
        void* inner = *(void**)(p + 0x64);
        if (inner != 0) {
            void* got = ((IObj*)inner)->Find(0x17f243b);
            if (got != 0) {
                if (((IObj2*)got)->Query()) return false;
                if (got == a2) return false;
            }
        }
    }
    {
        void* q = *(void**)(p + 0x90);
        if (q != 0 && *(int*)((char*)q + 8) == 0x2e81370) return false;
    }
    return true;
}

// @ 0x00d9aa20
void FUN_00d9aa20(void* self)
{
    char*  s      = (char*)self;
    float  tag    = *(float*)(s + 0x0c);
    float  radius = *(float*)(s + 0x10);
    Vec3*  centre = (Vec3*)(s + 0x14);
    bool   torus  = *(uint8_t*)(s + 0x28) != 0;

    // Nearby-object list produced by the scan context, and the sorted candidate
    // vector produced by the query helper.  Both are EASTL vectors in the original.
    void*  nearStore[64];
    void** nearBegin = nearStore;
    void** nearEnd   = nearStore;
    void*  candStore[64];
    void** candBegin = candStore;
    void** candEnd   = candStore;

    // 0x00b3d3c0 returns the scan context (ecx); 0x00b79c30 filters by tag and
    // pops its six stack arguments itself (LTCG ABI).
    FUN_00b79c30(FUN_00b3d3c0(), 0, centre, &nearBegin, 0x1f, tag, 0, 0);

    void* sorter = FUN_00b3d240();
    // The query fills the sorted candidate vector using the interaction predicate
    // as its acceptance callback.
    ((PFN_Sort)(*(void***)sorter)[0x48 / 4])(sorter, 0, centre, tag,
                                             &candBegin, 0, scanVisitor, 0);

    float m[16];
    FUN_0059c190(m, s + 0x2c);
    PM* pm = (PM*)FUN_00b3d350();
    float water = pm->FUN_00b7e390();
    float waterSq = water * water;

    int n = 0;
    for (char* rec = (char*)FUN_00af9ff0(s, 0, 0); rec != 0;
         rec = (char*)FUN_00af9ff0(s, 0, n)) {
        n++;
        if (rec[0] != 0) continue;

        ScanRec* r = (ScanRec*)rec;
        float px = r->mX, py = r->mY, pz = r->mZ;

        if (torus) {
            // rotate the local offset by the quaternion matrix and add the origin
            float tx = centre->x + (m[6] * pz + m[3] * py + m[0] * px);
            float ty = centre->y + (m[7] * pz + m[4] * py + m[1] * px);
            float tz = centre->z + (m[8] * pz + m[5] * py + m[2] * px);
            Vec3  tmp;
            float* q = (float*)FUN_00b815a0(pm, 0, &tmp, &tx);
            px = q[0]; py = q[1]; pz = q[2];
        }

        if (!(waterSq < px * px + py * py + pz * pz)) {
            FUN_00afa070(rec, 0, 1);
            continue;
        }

        // first pass: nearby objects (bounds position + radius)
        for (void** it = nearBegin; it != nearEnd; ++it) {
            ScanObj* o = (ScanObj*)*it;
            float rad = o->mRadius + radius;
            float dx = px - o->mX, dy = py - o->mY, dz = pz - o->mZ;
            if (dx * dx + dy * dy + dz * dz < rad * rad)
                FUN_00afa070(rec, 0, 1);
        }

        // second pass: verb entries from the sorted list, with their own radius
        for (void** it = candBegin; it != candEnd; ++it) {
            ScanObj* o = (ScanObj*)*it;
            float v = ((PFN_Radius)(*(void***)o)[0x74 / 4])(o);
            float lim = v - radius;
            if (!(0.1f <= lim)) lim = 0.1f;
            float* q;
            if (o->mLocal) q = ((PFN_Point)(*(void***)o)[0x2c / 4])(o);
            else {
                Vec3 tmp;
                q = (float*)FUN_00b81630(pm, 0, &tmp,
                                         ((PFN_Point)(*(void***)o)[0x2c / 4])(o));
            }
            float dx = px - q[0], dy = py - q[1], dz = pz - q[2];
            if (dx * dx + dy * dy + dz * dz < (lim + radius) * (lim + radius))
                FUN_00afa070(rec, 0, 2);
        }
    }

    // release the sorted candidates
    for (void** it = candBegin; it != candEnd; ++it) {
        void* o = *it;
        if (o != 0) ((PFN_Release)(*(void***)o)[0xc0 / 4])(o);
    }
}

// @ 0x00d9ae60
float FUN_00d9ae60(char* self)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0, 0x80);
    if (r == 0 && *(int*)(*(char**)(self + 0xb4c) + 0x1d8) != 0x5218bb3) return 1.0f;
    return 0.0f;
}

// @ 0x00d9afe0
void FUN_00d9afe0(Creature* self)
{
    self->mpBehaviorTreeData->mStimuli.ClearAll(0x10000, 0);
    typedef void (__thiscall *SetTargetFn)(Creature*, void*, int, int);
    ((SetTargetFn)(*(void***)self)[0x84 / 4])(self, 0, 0, 0);
}

// @ 0x00d9b0d0
void SocialValues::StartFillLeft(float rate, float d)
{
    float r = rate / mTotal;
    ((cSPUISocialRainbow*)mpWidget)->StartFill(1, 1, 0.0f, 0.0f, r, 0xff7bcc76, 1);
    mHandle1 = *(int*)&d;
}

// @ 0x00d9b2d0
bool FUN_00d9b2d0(BehaviorMgr* mgr, int* pair)
{
    Creature* c0 = *(Creature**)pair;
    Creature* got = mgr->At(0);
    int t1 = got->GetTribe();
    int t2 = c0->GetTribe();
    if (t2 == t1) return pair[1] == mgr->mKey1a8;
    return false;
}

// @ 0x00d9b320
float FUN_00d9b320(Creature* self, int a, int b, int c, int d, void* stimuli, char* outFlag)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0, 0x200);
    if (h == 0) return 0.0f;
    int f = FUN_00d998d0((int)h, 0x4ffcdeda);
    if (f == 0) return 0.0f;
    void* v = FUN_00b3d2b0(f, &self->mSub34);
    FUN_00ac7de0(v);
    if (stimuli) GetAny_00d997e0(stimuli);
    *(int*)((char*)stimuli + 8) = f;
    *(int*)((char*)stimuli + 0x18) = h->mState;
    *outFlag = 1;
    (void)a;(void)b;(void)c;(void)d;
    return 1.0f;
}

// @ 0x00d9b3a0
bool FUN_00d9b3a0(Creature* self)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x8000000, 0);
    if (h == 0) { FUN_00da6270(self, 0x14); return false; }
    int r = FUN_00d99500(FUN_00d999d0((int)h));
    if (r == 0) { FUN_00da6270(self, 0x14); return false; }
    int blk[2];
    blk[0] = (int)self; blk[1] = r;
    BehaviorMgr* mgr = FUN_00bc9b00();
    AnimHandle* node = mgr->FindNode(0x668e405, (void*)&FUN_00d9b2d0, blk);
    if (node == 0) {
        node = mgr->AddOrder(0x668e405, 0x20, 0x18eb4b7, kWildAnimalSocial);
        *(void**)((char*)node + 0x224) = (void*)0xdb4a20;
        *(int*)((char*)node + 0x1a4) = 0;
        *(int*)((char*)node + 0x1ac) = 0;
        *(int*)((char*)node + 0x1a8) = r;
    }
    mgr->SetNode(node, self, 0, 0);
    return true;
}

// @ 0x00d9b480
bool FUN_00d9b480(Creature* a, Creature* b)
{
    BehaviorTreeData* ta = a->mpBehaviorTreeData;
    BehaviorTreeData* tb = b->mpBehaviorTreeData;
    GoalTableEntry* ga = &ta->mGoalTable;
    GoalTableEntry* gb = &tb->mGoalTable;
    if (ga->mKey != 0x546e8804 || gb->mKey != 0x546e8804) return false;
    int ia = ga->mIndex;
    int ib = gb->mIndex;
    int va = *(int*)((char*)ta + 0x164 + ia * 0xac);
    int vb = *(int*)((char*)tb + 0x164 + ib * 0xac);
    return va < vb;
}

// @ 0x00d9b4e0
int FUN_00d9b4e0(Creature** a, Creature** b)
{
    Creature* ca = a[0];
    Creature* cb = b[0];
    float fa = ca->mX;
    float fb = cb->mX;
    if (fb > fa) return -1;
    if (fa > fb) return 1;
    return 0;
}

// @ 0x00d9b510
void FUN_00d9b510(Creature* self, int a, int b, int c2, int d, void* flag)
{
    if (self->IsLeader() && *(char*)((char*)flag + 8) == 0) {
        int* ms = (int*)SP_MessageServer();
        typedef void (__thiscall *MsgFn)(int*, uint, int, int);
        ((MsgFn)(*(void***)ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
    }
    self->mpBehaviorTreeData->mStimuli.ClearAll(0x800000, 0);
    (void)a;(void)b;(void)c2;(void)d;
}

// @ 0x00d9b560
bool FUN_00d9b560(Creature* self, int a, int b, int c2, int d, void* flag)
{
    if (self->IsAnimFinished(*(void**)((char*)flag + 4))) {
        if (self->IsLeader()) {
            *(char*)((char*)flag + 8) = 1;
            int* ms = (int*)SP_MessageServer();
            typedef void (__thiscall *MsgFn)(int*, uint, int, int);
            ((MsgFn)(*(void***)ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
        }
        return false;
    }
    return true;
}

// @ 0x00d9b5b0
bool FUN_00d9b5b0(int a, int b, int c, int d, int e, int* out, int* in)
{
    out[0] = in[6];
    out[1] = in[7];
    long long v;
    if (in[8] != 0) v = 1i64 << in[8];
    else v = 0;
    *(long long*)(out + 6) = v;
    int* p = in + 3;
    struct Triple { int a, b, c; };
    Triple* t = (Triple*)p;
    out[2] = t->a;
    out[3] = t->b;
    out[4] = t->c;
    out[5] = 0;
    (void)a;(void)b;(void)c;(void)d;(void)e;
    return true;
}

// @ 0x00d9b610
void FUN_00d9b610(Creature* self, int a, int b, int c2, int d, void* p)
{
    typedef bool (__thiscall *LocoFn)(void*);
    void* loco = (void*)((char*)self + 0xc0);
    bool r = ((LocoFn)(*(void***)loco)[0xf8 / 4])(loco);
    self->FUN_00c14750(!r);
    int x = *(int*)((char*)p + 0x18);
    int y = *(int*)((char*)p + 0x1c);
    if ((x | y) != 0) {
        self->mpBehaviorTreeData->mStimuli.ClearAll(x, y);
    }
    (void)a;(void)b;(void)c2;(void)d;
}

// @ 0x00d9b660
bool FUN_00d9b660(Creature* self)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x1000, 0);
    if (h == 0) { FUN_00da6270(self, 0x15); return false; }
    int r = FUN_00d994c0(FUN_00d999d0((int)h));
    if (r == 0) { FUN_00da6270(self, 0x15); return false; }
    int blk[2];
    blk[0] = (int)self; blk[1] = r;
    BehaviorMgr* mgr = FUN_00bc9b00();
    AnimHandle* node = mgr->FindNode(0x156bb1c6, (void*)&FUN_00d9b2d0, blk);
    if (node == 0) {
        node = mgr->AddOrder(0x156bb1c6, 0x20, 0x18eb4b7, kGiftInField);
        *(void**)((char*)node + 0x224) = (void*)0xdb4a20;
        *(int*)((char*)node + 0x1a4) = 0;
        *(int*)((char*)node + 0x1ac) = 0;
        *(int*)((char*)node + 0x1a8) = r;
        *(int*)((char*)node + 0x1b0) = 0;
    }
    mgr->SetNode(node, self, 0, 0);
    mgr->Activate(1, 2, self, g_fltMax, 0, 0);
    return true;
}

// @ 0x00d9c960
void __cdecl FUN_00d9c960(cSPCreatureBase_s00d9_bee0* c)
{
    void* r = FUN_00d99500_s00d9_bee0(c->ApplyCombatTarget());
    if (r != 0)
        ((cCargoManager*)FUN_00b3d480(r))->FUN_00aca360();

    cMemoryBlock* mb = c->mpTree_b4c->mpBlock_600;
    if (mb != 0 && mb->mpOwner == c)
        mb->mpOwner = 0;

    c->FUN_84(0, 0, 0);
}

// @ 0x00d9ccc0
void cScaleHelper::FUN_00d9ccc0(float a, float b)
{
    mFloat_34 = a + mFloat_34;
    void* p = *(void**)((u8*)mpField_0c + 0x550);
    if (p == 0)
        return;
    u8* r = (u8*)FUN_00c8ea70(p);
    float f = *(float*)(r + 0x94);
    if (mField_ec == 1)
        f = *(float*)(r + 0x90);
    if (f > g_147c194) {
        if (mpVec_e8 != 0) {
            a = a / f;
            mpVec_e8->push_back(a, a / b);
        }
        float ten = g_1473c70;
        float t = (mFloat_34 / f) * ten;
        float* p = (t > ten) ? &ten : &t;
        mFloat_38 = *p;
    }
}

// @ 0x00d9cd90
void S::FUN_00d9cd90()
{
  char* self = (char*)this;
  char* cur = *(char**)(self + 100);
  char* end = *(char**)(self + 0x68);
  float local_c = 0.0f;
  *(int*)(self + 0x3c) = *(int*)0x01581314;
  *(int*)(self + 0x40) = *(int*)0x01581318;
  bool b5 = false, b6 = false, b7 = false;
  int local_8 = 0;
  if (cur != end) {
    do {
      int obj = *(int*)cur;
      int citizen = 0;
      if (obj != 0)
        citizen = ((int (__thiscall*)(void*, unsigned))VFn((void*)(obj + 0x34), 0xc))((void*)(obj + 0x34), 0x4f176642u);
      if (obj == 0 || citizen == 0) {
        local_c = *(float*)0x01581310 + local_c;
      } else {
        int kind = FUN_00c22dc0((void*)obj);
        if (kind == 4) { local_c = *(float*)0x01581308 + local_c; b5 = true; }
        else if (kind == 5) { local_c = *(float*)0x01581308 + local_c; b7 = true; }
        else if (kind == 6) { local_c = *(float*)0x01581308 + local_c; b6 = true; }
        local_c = *(float*)0x01581300 + local_c;
        int prof = (int)FUN_00c0bbd0((void*)obj);
        local_8 = *(int*)(prof + 0x62c);
        char leader = FUN_00c232d0((void*)citizen);
        if (leader != 0) {
          *(float*)(self + 0x3c) = *(float*)0x0158130c + *(float*)(self + 0x3c);
          *(float*)(self + 0x40) = *(float*)(self + 0x40) + *(float*)0x0158130c;
        }
      }
      cur += 4;
    } while (cur != end);
    if (b5) local_c = *(float*)0x015812fc + local_c;
    if (b6) local_c = *(float*)0x015812fc + local_c;
    if (b7) local_c = *(float*)0x015812fc + local_c;
  }
  float f3 = (float)*(int*)(self + 0x48);
  if (*(int*)(self + 0x48) < 0) f3 = f3 + 4294967296.0f;
  float f4 = (float)local_8;
  if (local_8 < 0) f4 = f4 + 4294967296.0f;
  FUN_00d9ccc0(f4 * *(float*)0x01581304 + local_c, f3 * *(float*)(self + 0x4c));
}

// @ 0x00d9d0e0
char __cdecl FUN_00d9d0e0(void* p)
{
  char* e = (char*)p;
  int a = *(int*)(e + 0xb4c);
  int b = *(int*)((char*)a + 0x600);
  char c = ((char(__thiscall*)(void*))FUN_00a75010)((void*)b);
  return c == 0;
}

// @ 0x00d9d100
void S::FUN_00d9d100(void* creature, int target)
{
  char* self = (char*)this;
  char* t = (char*)target;
  float pos[3];
  int src = *(int*)(t + 0xf4);
  pos[0] = *(float*)(src + 0x3c);
  pos[1] = *(float*)(src + 0x40);
  pos[2] = *(float*)(src + 0x44);
  int slot = FUN_00afa5d0(pos);
  *(int*)(self + 0xc) = slot;
  if (slot == -1) return;
  void* slotObj = FUN_00af9ff0((void*)(self + 0x178), slot);
  FUN_00afa030(slotObj, creature);
  float face[3];
  face[0] = *(float*)(t + 0x1c);
  face[1] = *(float*)(t + 0x20);
  face[2] = *(float*)(t + 0x24);
  unsigned nx = *(unsigned*)&face[0] ^ 0x80000000u;
  unsigned ny = *(unsigned*)&face[1] ^ 0x80000000u;
  unsigned nz = *(unsigned*)&face[2] ^ 0x80000000u;
  float nf[3];
  nf[0] = *(float*)&nx; nf[1] = *(float*)&ny; nf[2] = *(float*)&nz;
  FUN_00c1c5c0(creature, 2, (void*)((char*)slotObj + 0xc), nf, 1.0f, 2.0f);
  void* r = FUN_00c41ec0((char*)creature + 0xc0);
  *(unsigned*)((char*)r + 0x70) |= 2;
}

// @ 0x00d9d1e0
char S::FUN_00d9d1e0(void* creature)
{
  char* self = (char*)this;
  unsigned* st = *(unsigned**)(self + 0x18);
  unsigned state = st[5];
  if (state > 3) return 1;
  switch (state) {
    case 0: {
      if (*(float*)(self + 8) != *(float*)0x0169f32c ||
          *(float*)(self + 0xc) != *(float*)0x0169f330 ||
          *(float*)(self + 0x10) != *(float*)0x0169f334) {
        char* cb = (char*)creature + 0xc0;
        float* p = (float*)VCall0(cb, 0x2c);
        float d[3];
        d[0] = *(float*)(self + 8) - p[0];
        d[1] = *(float*)(self + 0xc) - p[1];
        d[2] = *(float*)(self + 0x10) - p[2];
        char nbuf[12];
        float* n = (float*)FUN_00449c20(nbuf, d, 1.0f, 2.0f);
        float* q = (float*)VCall0(cb, 0x2c);
        FUN_00c1c5c0(creature, 2, q, n, 1.0f, 2.0f);
        st[5] = 1;
        return 1;
      }
      break;
    }
    case 1: {
      char near = FUN_00c42e20((char*)creature + 0xc0);
      if (near == 0 && (*(unsigned char*)((char*)creature + 0x330) & 1) == 0) return 1;
      break;
    }
    case 2: {
      FUN_00c12310(creature, *st, -1, 0);
      st[5] = 3;
      return 1;
    }
    case 3: {
      char fin = FUN_00c123f0(creature, 0);
      if (fin == 0) return 1;
      unsigned* ctr = st + 1;
      *ctr = *ctr - 1;
      if (*ctr == 0) return 0;
      break;
    }
    default: return 1;
  }
  st[5] = 2;
  return 1;
}

// @ 0x00d9d570
void S::FUN_00d9d570(void* owner)
{
  char* self = (char*)this;
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  if (arr != 0 && *(int*)(arr + 0x1ac) == (int)self) *(int*)(arr + 0x1ac) = 0;
  int base = *(int*)(self + 0xb4c);
  int* p = *(int**)(base + 0x600);
  if (p != 0) {
    *(int*)(base + 0x600) = 0;
    ((void (*)(int*))VFn(p, 8))(p);
  }
  FUN_00bcafe0(p, *(int*)(base + 0x604));
  *(int*)(base + 0x604) = -1;
}

// @ 0x00d9d800
void __cdecl FUN_00d9d800(void* owner)
{
  char* self = (char*)owner;
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  if (arr != 0 && *(int**)(arr + 0x1ac) == (int*)self) *(int*)(arr + 0x1ac) = 0;
  ((void (__thiscall*)(void*, int, int, int))VFn(self, 0x84))(self, 0, 0, 0);
}

// @ 0x00d9d840
int S::FUN_00d9d840(int idx)
{
  unsigned* p = *(unsigned**)this;
  p += idx * 0x84;
  bool b30 = ((((unsigned)*p) >> 0x1e) & 1) != 0;
  if (b30) return 0x3fffffff;
  do {
    p += 0x84;
    ++idx;
    bool b31 = ((((unsigned)*p) >> 0x1f) & 1) != 0;
    if (!b31) return idx;
    b30 = ((((unsigned)*p) >> 0x1e) & 1) != 0;
  } while (!b30);
  return 0x3fffffff;
}

// @ 0x00d9d890
void S::FUN_00d9d890(int* first, int* last)
{
  for (; first < last; first += 0x84) {
    bool flag = (((unsigned)*first) >> 31) & 1;
    if (!flag) {
      void* obj = (void*)(first + 1);
      (*(void (__thiscall***)(void*, int))obj)[0](obj, 0);
    }
  }
}

// @ 0x00d9d8d0
void S::FUN_00d9d8d0(int* out, int* src, int* end, int* dst)
{
  *out = (int)dst;
  if (src != end) {
    int* d = dst;
    while (src != end) {
      if (d != 0) {
        d[0] = src[0]; d[1] = src[1]; d[2] = src[2]; d[3] = src[3];
        d[4] = src[4]; d[5] = src[5]; d[6] = src[6]; d[7] = src[7];
      }
      src += 8;
      d += 8;
    }
    *out = (int)d;
  }
}

// @ 0x00d9d940
void __cdecl FUN_00d9d940(void* dst, unsigned n, void* src)
{
  Elem20* d = (Elem20*)dst;
  Elem20* s = (Elem20*)src;
  while (n > 0) {
    if (d != 0) {
      d->a = s->a;
      d->f[0] = s->f[0]; d->f[1] = s->f[1]; d->f[2] = s->f[2]; d->f[3] = s->f[3];
      d->f[4] = s->f[4]; d->f[5] = s->f[5]; d->f[6] = s->f[6];
    }
    --n;
    ++d;
  }
}

// @ 0x00d9d9a0
void S::FUN_00d9d9a0(void* arr, int a, int n, int i, int v, float f1, float f2, float f3, float f4, float f5, float f6, float f7, void* cmp)
{
  char* base = (char*)arr;
  (void)a; (void)v;
  for (;;) {
    int child = i * 2 + 2;
    if (n <= child) break;
    char* c = base + child * 0x20;
    char ok = ((char (*)(void*, void*))cmp)(c, c - 0x20);
    if (ok != 0) child = i * 2 + 1;
    Copy8((int*)(base + i * 0x20), (int*)(base + child * 0x20));
    i = child;
  }
  if (i == n - 1) {
    Copy8((int*)(base + i * 0x20), (int*)(base + (n - 1) * 0x20));
    i = n - 1;
  }
  FUN_00d9b950(arr, (void*)a, i, f1, f2, f3, f4, f5, f6, f7, *(float*)&v, cmp);
}

// @ 0x00d9da80
void S::FUN_00d9da80(void* arr, void* a, int n, int i, float f1, float f2, float f3)
{
  int* base = (int*)arr;
  (void)a;
  for (;;) {
    int child = i * 2 + 2;
    if (n <= child) break;
    int r = base[child];
    void* c1 = r == 0 ? 0 : (void*)(r + 0xc0);
    int l = base[child - 1];
    void* c0 = l == 0 ? 0 : (void*)(l + 0xc0);
    char ok = FUN_00ac0730(c0, c1);
    if (ok != 0) child = i * 2 + 1;
    base[i] = base[child];
    i = child;
  }
  if (i == n - 1) {
    base[i] = base[n - 1];
    i = n - 1;
  }
  FUN_00d9b9b0(arr, a, i, f1, f2, f3);
}

// @ 0x00d9db30
void S::FUN_00d9db30(void* src, void* end, void* dst)
{
  int* s = (int*)src;
  int* e = (int*)end;
  int* d = (int*)dst;
  if (s != e) {
    while (s != e) {
      if (d != 0) {
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
        d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
      }
      s += 8; d += 8;
    }
  }
}

// @ 0x00d9dc80
void S::FUN_00d9dc80(void* creature, void* block)
{
  char* self = (char*)this;
  char* blk = (char*)block;
  if (((*(unsigned*)(self + 0xb58) >> 9) & 1) == 0) VCall3(self, 0x84, 0, 0, 0);
  FUN_00bc98f0((void*)(*(int*)(self + 0xb4c) + 8), 0x10000000, 0);
  FUN_00c0ba10(self);
  *(unsigned*)(self + 0xb58) &= 0xffffffdfu;
  if (blk != 0) {
    int* q = *(int**)(blk + 4);
    if (q != 0) {
      ((void (*)(int*))((void**)q[0])[1])(q);
    }
  }
}

// @ 0x00d9e420
void FinishBehaviorTask(cSimCreature* pCreature, void* pA, void* pB, void* pC, void* pD, cBehaviorCallback* pCallback)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x200);
    void* pManager = BehaviorManager(pCreature);
    ((cEpisodeObject*)pManager)->GetRecord();
    if (pCallback == nullptr)
        return;
    cBehaviorHandler* pHandler = (cBehaviorHandler*)pCallback->mpHandler;
    if (pHandler != nullptr)
        pHandler->Method04();
}

// @ 0x00d9ea30
char StartFindTargetBehavior(cSimCreature* pCreature, void* pA, void* pB, void* pC, cFoundTarget* pFound)
{
    if (pFound != nullptr)
        pFound->mpObject = nullptr;

    void* pAnimation = pCreature->mpBehaviorTree->mStimuli.Play(0x2000000, 0);
    void* pResult = GetObjectFromId(WatchMemoryBlock(pAnimation));
    if (pResult == nullptr || pResult == pCreature) {
        pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000000, 0);
        return 0;
    }

    pCreature->mMovement.CallVoid(0xec);
    pCreature->SetCombatEngaged(!pCreature->mMovement.CallChar(0xf8));

    void* pPrevious = pFound->mpObject;
    pFound->mnField14 = 0;
    if (pResult != pPrevious) {
        ((cPoolObject*)pResult)->AddRef();
        pFound->mpObject = pResult;
        if (pPrevious != nullptr)
            ((cPoolObject*)pPrevious)->Destroy(0);
    }

    const uint32_t* pAnimationData = (const uint32_t*)pAnimation;
    pFound->mnField04 = pAnimationData[3];
    pFound->mnField08 = pAnimationData[4];
    pFound->mnField0c = pAnimationData[5];
    pFound->mfField10 = ((const float*)pAnimationData)[6];
    return 1;
}

// @ 0x00d9eb20
void CancelBehaviorTask(cSimCreature* pCreature, void* pA, void* pB, void* pC, void* pD, cBehaviorCallback* pCallback)
{
    pCreature->mMovement.CallVoid(0xec);
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000000, 0);
    if (pCallback != nullptr && pCallback->mpTarget != nullptr)
        ((cBehaviorHandler*)pCallback->mpTarget)->Method04();
}
