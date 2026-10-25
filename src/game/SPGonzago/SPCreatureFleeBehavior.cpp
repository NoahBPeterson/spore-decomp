// src/game/SPGonzago/SPCreatureFleeBehavior.cpp -- migrated from slice(s) s00d6b020, s00d6aa30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureFleeBehavior.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "EA/Variant.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPropertyList.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include <math.h>

// ---- items of slice s00d6aa30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct Quat { float x, y, z, w; };
}
namespace SP {
class cSPCreatureBase_s00d6_aa30;
}
namespace SP {
struct LocoMoveParams;
}
namespace SP {
#define PVCAT2(a, b) a##b
}
namespace SP {
#define PVCAT(a, b) PVCAT2(a, b)
}
namespace SP {
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
}
namespace SP {
#define PV2 PV PV
}
namespace SP {
#define PV4 PV2 PV2
}
namespace SP {
#define PV8 PV4 PV4
}
namespace SP {
struct Loco {
    PV8 PV2 PV                                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                 // +0x2c
    virtual Quat* GetOrientation();              // +0x30
    PV4 PV                                       // 0x34 .. 0x44
    virtual bool IsOnView();                     // +0x48
    PV4                                          // 0x4c .. 0x58
    virtual Vec3* GetDirection(Vec3* out);       // +0x5c
    PV4 PV                                       // 0x60 .. 0x70
    virtual float GetFootprintRadius();          // +0x74
    PV8 PV8 PV4 PV2 PV2 PV                       // 0x78 .. 0xd8
    virtual void vDC(LocoMoveParams* p);         // +0xdc
    PV2 PV                                       // 0xe0 .. 0xe8
    virtual void vEC();                          // +0xec
};
}
namespace SP {
struct ThreatOwner {
    PV8 PV2 PV                                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                 // +0x2c
};
}
namespace SP {
struct TargetRef {
    PV PV
    virtual ThreatOwner* GetOwner();             // +0x08
};
}
namespace SP {
class cSPCreatureBase_s00d6_aa30 {
public:
    PV PV PV                                              // 0x00 .. 0x08
    virtual cSPCreatureBase_s00d6_aa30* Cast(uint32_t type);         // +0x0c
    PV8 PV8 PV8 PV4 PV                                    // 0x10 .. 0x80
    virtual void SetTarget(void* obj, int a, int b);      // +0x84
    PV8 PV2 PV                                            // 0x88 .. 0xb0
    virtual void* GetObjectById(int id);                  // +0xb4
    PV PV                                                 // 0xb8 0xbc
    virtual bool CanReach(cSPCreatureBase_s00d6_aa30* o, float a, float b);   // +0xc0

    uint32_t pad4[(0xc0 - 4) / 4];
    Loco mLoco;                                           // +0xc0
    uint32_t padc4[(0xb20 - (0xc0 + sizeof(Loco))) / 4];
    void* mGroup;                                         // +0xb20
    uint32_t padb24[(0xb4c - 0xb24) / 4];
    void* mBehav;                                         // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                                      // +0xb58
    uint8_t mScared;                                      // +0xb5c
    uint8_t padb5d;
    uint8_t mDead;                                        // +0xb5e

    int  PlayAnimation(uint32_t id, int a, int b);        // 0x00c12190 (ret 12)
    int InterruptAnimation(uint32_t id, int a, int b);    // 0x00c12310 (ret 12)
    bool AnimationFinished2(int id);                      // 0x00c123f0 (ret 4)
    void PlayAnimationWithTarget(uint32_t id, ThreatOwner* a, int b, int c);   // 0x00c14940 (ret 16)
    bool Hover(int on);                                   // 0x00c13a30 (ret 4)
    void FUN_00c14750(int a);                             // ret 4
    void SetStealthed(int a, int b);                      // 0x00c1aed0 (ret 8)
    TargetRef* GetTargetObj();                            // 0x00c0ee60
    cSPCreatureBase_s00d6_aa30* GetTargetAsCreature();               // 0x00c0ee70
    bool FUN_00c0c130();
    bool FUN_00c11480(const Vec3* p, float a, float b);           // ret 12
    bool FUN_00c0d560(cSPCreatureBase_s00d6_aa30* t, float a, float b);      // ret 12
};
}
namespace SP {
struct RandomLCG {
    uint32_t RandomUint32Uniform(uint32_t limit);         // 0x00a68fb0 (ret 4)
};
}
namespace SP {
extern RandomLCG sMathRandom;                             // 0x01601760
}
namespace SP {
struct ScaredState {                                      // per-node behaviour state block
    int mState;        // +0x00
    float mTimer1;     // +0x04
    float mTimer2;     // +0x08
    float mTimer3;     // +0x0c
    float mTimer4;     // +0x10
    bool mB14;         // +0x14
    bool mB15;         // +0x15
    uint16_t pad16;
    int mFreakOut;     // +0x18
    float mTimer5;     // +0x1c
    Vec3 mVec;         // +0x20
    float mF2c;        // +0x2c
    int mAnim;         // +0x30
};
}
namespace SP {
struct RefObj { uint32_t f0; void* f4; };
}
namespace SP {
struct BehStim {                                          // creature->mBehav + 8
    void FUN_00bc97f0(uint32_t lo, uint32_t hi, float f, cSPCreatureBase_s00d6_aa30* ref);   // ret 0x10
    void* PlayIdleAnimation(int a, int b);                // 0x00bc96a0 (ret 8)
};
}
namespace SP {
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};
}
namespace SP {
class cPropertyList_s00d6_aa30 {
public:
    PV8 PV
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};
}
namespace SP {
struct CreatureModeStrategy {
    uint32_t padb4[0xb4 / 4];
    cPropertyList_s00d6_aa30* mProps;                                // +0xb4
};
}
namespace SP {
class IObject {
public:
    PV8 PV8 PV4 PV2 PV
    virtual void* v5c(uint32_t type);                     // +0x5c
};
}
namespace SP {
struct BlockHeader { uint32_t mUsed; };                    // lives immediately before a heap block
}
namespace SP {
struct LocoMoveParams {
    void* mpResult;      // +0x00
    void* mp04;          // +0x04
    void* mp08;          // +0x08
    uint32_t pad0c;      // +0x0c
    uint32_t pad10;      // +0x10
    Vec3 mPos;           // +0x14
    float f20;           // +0x20
    uint32_t pad24;      // +0x24
    uint32_t pad28[9];   // +0x28 .. +0x4b
    uint8_t b4c;         // +0x4c
    uint8_t pad4d;       // +0x4d
    uint16_t pad4e;      // +0x4e
    float f50;           // +0x50
    float f54;           // +0x54
    float f58;           // +0x58
    uint32_t f5c;        // +0x5c
    float f60;           // +0x60
    float f64;           // +0x64
    float f68;           // +0x68
    float f6c;           // +0x6c
    uint32_t f70;        // +0x70
};
}
namespace SP {
extern CreatureModeStrategy* gCreatureModeStrategy;       // 0x0169e294
}
namespace SP {
extern float DAT_015d9c6c;                                // 0x015d9c6c
}
namespace SP {
extern float DAT_013ec4b4;                                // 0x013ec4b4
}
namespace SP {
extern float DAT_0147bc40;                                // 0x0147bc40
}
namespace SP {
TargetRef* FUN_00d998f0(void* x);                         // 0x00d998f0 (cdecl)
}
namespace SP {
void* FUN_00d998d0(void* idle, int type);                 // 0x00d998d0 (cdecl)
}
namespace SP {
cSPCreatureBase_s00d6_aa30* FUN_00d99470(cSPCreatureBase_s00d6_aa30* c);        // 0x00d99470 (cdecl)
}
namespace SP {
void operator delete(void* p);                            // 0x00f47380 (cdecl)
}
namespace SP {
extern Vec3 DAT_0169ed0c;                                 // 0x0169ed0c
}
// ---- items of slice s00d6aa30 end

// ---- items of slice s00d6b020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_01654c10;                                      // game-mode object
extern float DAT_01582e18;
extern float DAT_01582e08;
extern float DAT_01583f98;
#define PVCAT2_s00d6_b020(a, b) a##b
#define PVCAT_s00d6_b020(a, b) PVCAT2_s00d6_b020(a, b)
#define PV_s00d6_b020 virtual void PVCAT_s00d6_b020(pv_, __COUNTER__)();
#define PV2_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020
#define PV4_s00d6_b020 PV2_s00d6_b020 PV2_s00d6_b020
#define PV8 PV4_s00d6_b020 PV4_s00d6_b020
namespace SP {
class cSPCreatureBase_s00d6_b020;
}
namespace SP {
struct Avatar;
}
namespace SP {
struct ThreatOwner_s00d6_b020 {                                   // the "owner" of the target object
    PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                       // +0x2c
    PV8 PV2_s00d6_b020                                            // 0x30 .. 0x54
    virtual bool IsPlayerOwned();                      // +0x58
    PV4_s00d6_b020 PV2_s00d6_b020                                            // 0x5c .. 0x70
    virtual float GetFootprintRadius();                // +0x74
    PV8 PV8                                            // 0x78 .. 0xb4
    virtual void* Cast(uint32_t type);                 // +0xb8
};
}
namespace SP {
struct TargetRef_s00d6_b020 {                                     // result of cSPCreatureBase::GetTargetObj
    PV_s00d6_b020 PV_s00d6_b020
    virtual ThreatOwner_s00d6_b020* GetOwner();                   // +0x08
};
}
namespace SP {
struct LocoState {
    uint32_t pad[0x14 / 4];
    Vec3 mV14;                                         // +0x14
    uint32_t pad20[(0x5c - 0x20) / 4];
    int mHasPath;                                      // +0x5c
};
}
namespace SP {
struct Loco_s00d6_b020 {                                          // sub-object at creature+0xc0 (own vtable)
    PV8 PV2_s00d6_b020 PV_s00d6_b020                                         // 0x00 .. 0x28
    virtual Vec3* GetPosition();                       // +0x2c
    virtual Quat* GetOrientation();                    // +0x30
    PV4_s00d6_b020 PV_s00d6_b020                                             // 0x34 .. 0x44
    virtual bool IsOnView();                           // +0x48
    PV4_s00d6_b020                                                // 0x4c .. 0x58
    virtual Vec3* GetDirection(Vec3* out);             // +0x5c
    PV4_s00d6_b020 PV_s00d6_b020                                             // 0x60 .. 0x70
    virtual float GetFootprintRadius();                // +0x74
    bool IsNearGoal();                                 // 0x00c42e20
    Vec3* FUN_00c42de0();                              // 0x00c42de0
    LocoState* GetState();                             // 0x00c41ec0
};
}
namespace SP {
struct Avatar {                                        // GetAvatar() result
    uint32_t pad[0xc0 / 4];
    Loco_s00d6_b020 mLoco;                                        // +0xc0
};
}
namespace SP {
class cGameNounManager_s00d6_b020 { public:
    Avatar* GetAvatar();                               // 0x00b1fdb0
};
}
namespace SP {
class cSPDramaManager { public:
    bool IsDramaEventActive(int type);                 // 0x00d4cb30
};
}
namespace SP {
class cViewer_s00d6_b020 { public:
    void GetCameraLocationInfo(Vec3* pos, Vec3* dir, Vec3* a, Vec3* b);   // 0x007c3d30
};
}
namespace SP {
class cApp { public:
    PV8 PV8 PV4_s00d6_b020 PV2_s00d6_b020                                    // 0x00 .. 0x54
    virtual cViewer_s00d6_b020* GetViewer();                      // +0x58
};
}
namespace SP {
struct RandomLCG_s00d6_b020 {                                     // EA::Random::RandomLinearCongruential
    uint32_t RandomUint32Uniform(uint32_t limit);      // 0x00a68fb0
    double RandomDoubleUniform();                      // 0x009360d0
};
}
namespace SP {
struct CreatureModeStrategy_s00d6_b020 {
    uint32_t pad[0xb4 / 4];
    void* mProperties;                                 // +0xb4
};
}
namespace SP {
struct BehStim_s00d6_b020 {                                       // creature->mBehav + 8
    void FUN_00bc97f0(uint32_t lo, uint32_t hi, float f, cSPCreatureBase_s00d6_b020* ref);   // ret 0x10
};
}
namespace SP {
struct Behav {
    uint32_t pad0[2];
    uint32_t pad1[(0x1d8 - 8) / 4];
    uint32_t m1d8;                                     // +0x1d8
};
}
namespace SP {
struct NearEntry {                                     // element of the list at creature+0x1124 (via filter)
    float mDistance;                                   // +0x00
    uint32_t pad04;
    cSPCreatureBase_s00d6_b020* mCreature;                        // +0x08
};
}
namespace SP {
struct HomeObj {
    Vec3* FUN_00c6acc0();                              // 0x00c6acc0
};
}
namespace SP {
struct SpotObj {
    uint32_t pad[0x5c / 4];
    Vec3 mPos;                                         // +0x5c
    float FUN_00aff550();                              // 0x00aff550
};
}
namespace SP {
struct SpotEntry {
    uint32_t pad[3];
    SpotObj* mObj;                                     // +0x0c
};
}
namespace SP {
struct Pred {                                          // stateless filter functor (0x00c02600)
    bool Test(NearEntry* e);                           // 0x00c02600 (thiscall ret 4)
};
}
namespace SP {
struct FilterRange {                                   // 0x00b41a40 / 0x00b3d850
    NearEntry** mpCur;
    NearEntry** mpEnd;
    Pred mPred;
    FilterRange* FUN_00b41a40(void* container, bool* unused);   // ret 8
    void Advance();                                    // 0x00b3d850
};
}
namespace SP {
struct ObjInfo {
    uint32_t pad[0x7c / 4];
    int m7c;                                           // +0x7c
};
}
namespace SP {
struct GroupObj {
    uint32_t pad[0x58c / 4];
    float mF58c;                                       // +0x58c
};
}
namespace SP {
struct OwnerCastObj {                                  // owner->Cast(0xb033b403) result
    uint32_t pad[0x714 / 4];
    int m714;                                          // +0x714
};
}
namespace SP {
class cSPCreatureBase_s00d6_b020 {
public:
    PV_s00d6_b020 PV_s00d6_b020 PV_s00d6_b020
    virtual cSPCreatureBase_s00d6_b020* Cast(uint32_t type);      // +0x0c
    PV8 PV8 PV8 PV4_s00d6_b020 PV_s00d6_b020                                 // 0x10 .. 0x80
    virtual void SetTarget(void* obj, int a, int b);   // +0x84
    PV8 PV2_s00d6_b020 PV_s00d6_b020                                         // 0x88 .. 0xb0
    virtual ObjInfo* GetObjectById(int id);            // +0xb4
    PV_s00d6_b020 PV_s00d6_b020                                              // 0xb8 0xbc
    virtual bool CanReach(cSPCreatureBase_s00d6_b020* o, float a, float b);   // +0xc0

    uint32_t padc4[(0xc0 - 4) / 4];
    Loco_s00d6_b020 mLoco;                                        // +0xc0
    uint32_t padc4b[(0xb20 - 0xc4) / 4];
    GroupObj* mGroup;                                  // +0xb20
    uint32_t padb24[(0xb4c - 0xb24) / 4];
    Behav* mBehav;                                     // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                                   // +0xb58
    uint8_t mScared;                                   // +0xb5c
    uint8_t padb5d;
    uint8_t mDead;                                     // +0xb5e
    uint8_t padb5f[(0xe7c - 0xb5f)];
    uint32_t padE7c;                                   // +0xe7c (target ref)
    uint8_t pade80[(0xf90 - 0xe80)];
    uint8_t mF90;                                      // +0xf90
    uint8_t padf91[(0x108c - 0xf91)];
    SpotEntry** mSpotsBegin;                           // +0x108c
    SpotEntry** mSpotsEnd;                             // +0x1090
    uint8_t pad1094[(0x1124 - 0x1094)];
    NearEntry** mNearBegin;                            // +0x1124
    NearEntry** mNearEnd;                              // +0x1128

    TargetRef_s00d6_b020* GetTargetObj();                         // 0x00c0ee60
    cSPCreatureBase_s00d6_b020* GetTargetAsCreature();            // 0x00c0ee70
    bool FUN_00c0c130();
    bool FUN_00c0c0e0();                               // "cCreatureBase" (+0xe84 flag test)
    uint32_t FUN_00c0cdb0();
    int FUN_00c0b750();
    void* FUN_00c04750();
    int FUN_00c0f570();
    int FUN_00c0c140();
    bool FUN_00c11480(const Vec3* p, float a, float b);          // ret 12
    bool FUN_00c0d560(cSPCreatureBase_s00d6_b020* t, float a, float b);     // ret 12
    int FUN_00c12410(uint32_t* mask, float range, int a, int b, int c, int d, int e);   // ret 28
    void InterruptAnimation(int id, int a, int b);               // 0x00c12310 (ret 12)
    int PlayAnimation(int id, int a, int b);                     // 0x00c12190 (ret 12)
    bool FUN_00c0e0c0(int id);                                   // ret 4
    bool AnimationFinished(int id);                              // 0x00c12400
    bool AnimationFinished2(int id);                             // 0x00c123f0
    bool WaitForAnimEventOrEnd(int id, float* out, int a, int b, int c);   // 0x00c14ef0 (ret 20)
    void SetStealthed(int a, int b);                             // 0x00c1aed0 (ret 8)
    bool Hover(int on);                                          // 0x00c13a30 (ret 4)
    void FUN_00c19940(int a);                                    // ret 4 0x00c19940
    void FUN_00c0cff0(int a);                                    // ret 4
    void FUN_00c0d0c0(uint32_t idx, bool on);                    // ret 8
    void MoveToPointAndFacingAtSpeed(int a, const Vec3* p, const Vec3* facing, float s0, float s1);   // 0x00c1c5c0 (ret 20)
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);                              // 0x00c1c1d0 (ret 16)
    void TryJumpToTarget(int a, const Vec3* p, const Vec3* q, float f, int b);                     // 0x00c190e0 (ret 20)
    HomeObj* FUN_00c04590();                                     // helper object (ptr at +0x1674)
};
}
namespace SP {
struct FleeState {
    int mState;        // +0x00
    float mTimer1;     // +0x04
    float mTimer2;     // +0x08
    float mTimer3;     // +0x0c
    float mTimer4;     // +0x10
    bool mB14;         // +0x14
    bool mB15;         // +0x15
    uint16_t pad16;
    int mFreakOut;     // +0x18
    float mTimer5;     // +0x1c
    Vec3 mVec;         // +0x20
    float mF2c;        // +0x2c
    int mAnim;         // +0x30
};
}
namespace SP {
class cPlanetModel_s00d6_b020 {
public:
    void FUN_00b81630(Vec3* out, const Vec3* in);                // ret 8 (position -> direction)
    void DirectionToSurfacePosition(Vec3* out, const Vec3* in);  // 0x00b815a0, ret 8
};
}
namespace SP {
bool FLEE_Tick(cSPCreatureBase_s00d6_b020* self, int, int, unsigned flags4, unsigned flags5, FleeState* st, int, float dt);
}
namespace SP {
cSPCreatureBase_s00d6_b020* FUN_00d99470(cSPCreatureBase_s00d6_b020* c);
}
namespace SP {
cSPDramaManager* FUN_00d51660();                                // drama manager singleton
}
namespace SP {
cGameNounManager_s00d6_b020* NounManager();                                // 0x00b3d300
}
namespace SP {
float GetPropertyT_float(void* props, uint32_t hash, float def);   // 0x004e1c70
}
namespace SP {
float FUN_00d38a30(int which, cSPCreatureBase_s00d6_b020* c);
}
namespace SP {
cPlanetModel_s00d6_b020* PlanetModel();                                    // 0x00b3d350
}
namespace SP {
float FUN_00d99a60(Vec3* a, float ra, Vec3* b, float rb, bool clamp);
}
namespace SP {
void* GetCurrentGameMode();                                     // 0x00b5b800
}
namespace SP {
void PlayScaredAnimation(cSPCreatureBase_s00d6_b020* c, ThreatOwner_s00d6_b020* owner, int* slot);   // 0x00d6ab00
}
namespace SP {
int FreakOut(cSPCreatureBase_s00d6_b020* c, int flag);                     // 0x00d6aa30
}
namespace SP {
Vec3* Vector3_Normalize(Vec3* out, const Vec3* in);             // 0x00436ce0
}
namespace SP {
Vec3* normalized_safe(Vec3* out, const Vec3* in);               // 0x00449c20
}
namespace SP {
char Vector3Equal(const Vec3* a, const Vec3* b);                // 0x004232c0
}
namespace SP {
void FUN_00d99e20(Vec3* pos, Vec3* inout);
}
namespace SP {
Vec3* FUN_0059aed0(Vec3* out, const Vec3* v, const Quat* q);
}
namespace SP {
float FUN_00572a60(float a);
}
namespace SP {
void FUN_00576b00(float* mat9, const Vec3* axis, float angle);
}
namespace SP {
cApp* App();                                                    // 0x0067dd10
}
namespace SP {
cSPCreatureBase_s00d6_b020* interface_cast_animal(cSPCreatureBase_s00d6_b020* c);     // 0x00ac8960
}
extern SP::CreatureModeStrategy_s00d6_b020* gCreatureModeStrategy;        // 0x0169e294
extern SP::RandomLCG_s00d6_b020 sMathRandom;                              // 0x01601760
extern SP::Vec3 DAT_0169ed0c;
extern SP::Vec3 DAT_0169ed58;
// ---- items of slice s00d6b020 end

// @ 0x00d6aa30
namespace SP {
uint32_t FreakOut(cSPCreatureBase_s00d6_aa30* p, char b)
{
    typedef int PVCAT;   // keeps the slice's PV/PVCAT macro items (see report)
    if (b) {
        p->PlayAnimation(0x65e5226, 1, -1);
        return 0x65e5226;
    }
    p->InterruptAnimation(0x9238f939, -1, 0);
    p->PlayAnimation(0xf238f946, 1, -1);
    return 0xf238f946;
}
}  // namespace SP

// @ 0x00d6aa80
namespace SP {
void FUN_00d6aa80(cSPCreatureBase_s00d6_aa30* p)
{
    p->SetTarget(0, 0, 0);
    p->Hover(0);
    if (!p->mDead)
        p->InterruptAnimation(0x2481de5, -1, 0);
}
}  // namespace SP

// @ 0x00d6aac0
namespace SP {
void FUN_00d6aac0(cSPCreatureBase_s00d6_aa30* p)
{
    p->SetTarget(0, 0, 0);
    p->Hover(0);
    if (!p->mDead)
        p->FUN_00c14750(1);
}
}  // namespace SP

// @ 0x00d6ab00
namespace SP {
void PlayScaredAnimation(cSPCreatureBase_s00d6_aa30* p, ThreatOwner* param_2, int* slot)
{
    if (*slot == 0 || p->AnimationFinished2(*slot)) {
        int id;
        do {
            id = sMathRandom.RandomUint32Uniform(3) + 0x40e01e0;
        } while (id == *slot);
        p->PlayAnimationWithTarget(id, param_2, -1, -1);
        *slot = id;
    }
}
}  // namespace SP

// @ 0x00d6ab50
namespace SP {
bool FUN_00d6ab50(cSPCreatureBase_s00d6_aa30* p, int a1, int a2, int a3, int a4, ScaredState* st, RefObj* o)
{
    st->mState = 0;
    st->mTimer1 = 2.0f;
    TargetRef* obj = FUN_00d998f0(o->f4);
    if (obj) {
        p->mLoco.vEC();
        p->SetTarget(obj, 1, 0);
        p->SetStealthed(0, 0);
        PlayScaredAnimation(p, obj->GetOwner(), (int*)st);
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x00d6ad60
namespace SP {
bool FUN_00d6ad60(cSPCreatureBase_s00d6_aa30* p, int a2, int a3, unsigned a4, unsigned char a5, ScaredState* st, RefObj* o)
{
    st->mTimer1 = 5.0f;
    st->mTimer2 = 0.0f;
    st->mTimer3 = 0.0f;
    st->mState = 1;
    st->mTimer4 = 1.1f;
    st->mB14 = false;
    st->mB15 = false;
    st->mFreakOut = 0;

    Property* prop;
    float f;
    cPropertyList_s00d6_aa30* props = gCreatureModeStrategy->mProps;
    if (props != 0 && props->GetProperty(0x82fb1acc, prop)) {
        const float* pData;
        if (prop->mnType == 0xd || prop->mnType == 0x10) {
            if (prop->mnFlags & 0x30)
                pData = *(const float**)prop;
            else
                pData = prop->mnType ? (const float*)prop : 0;
        } else {
            pData = &DAT_015d9c6c;
        }
        f = *pData;
    } else {
        f = 5.0f;
    }
    st->mTimer5 = f;

    st->mVec = DAT_0169ed0c;
    st->mF2c = 0.0f;
    st->mAnim = 0;

    if (a5 & 1) {
        st->mAnim = p->InterruptAnimation(0x5f0abb5, -1, 0);
        st->mState = 0;
    } else if (a4 & 0x2000000) {
        st->mAnim = p->InterruptAnimation(0x65e535c, -1, 0);
        st->mState = 0;
    } else {
        if (((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 0x100)) {
            st->mAnim = p->InterruptAnimation(0x5f0abb5, -1, 0);
            st->mState = 0;
        }
    }

    IObject* found = 0;
    if (o != 0)
        found = (IObject*)o->f4;
    if (found == 0) {
        void* r = ((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 0x40);
        if (r != 0)
            found = (IObject*)FUN_00d998d0(r, 0x13f94d4);
        if (found == 0) {
            void* r2 = ((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 2);
            if (r2 != 0)
                found = (IObject*)FUN_00d998d0(r2, 0x13f94d4);
            if (found == 0)
                return false;
        }
    }
    IObject* sub = (IObject*)found->v5c(0xce9f6639);
    if (sub != 0) {
        if (FUN_00d99470((cSPCreatureBase_s00d6_aa30*)sub) == 0)
            return false;
    } else {
        st->mTimer1 = 1.0f;
    }

    p->SetTarget(found, 0, 0);

    LocoMoveParams s;
    s.mpResult = 0;
    s.mp04 = 0;
    s.mp08 = 0;
    s.mPos.x = DAT_0169ed0c.x;
    s.mPos.y = DAT_0169ed0c.y;
    s.mPos.z = DAT_0169ed0c.z;
    s.f20 = 1.0f;
    s.pad24 = 0;
    s.b4c = 0;
    s.f50 = 0.0f;
    s.f54 = 0.0f;
    s.f58 = 0.0f;
    s.f5c = 0;
    s.f60 = 2.0f;
    s.f64 = DAT_013ec4b4;
    s.f68 = DAT_0147bc40;
    s.f6c = 0.0f;
    s.f70 = 0;
    p->mLoco.vDC(&s);
    if (s.mpResult != 0 && ((BlockHeader*)s.mpResult)[-1].mUsed != 0)
        operator delete(s.mpResult);
    p->SetStealthed(0, 0);
    return true;
}
}  // namespace SP

// @ 0x00d6b020
bool SP::FLEE_Tick(SP::cSPCreatureBase_s00d6_b020* self, int, int, unsigned flags4, unsigned flags5, SP::FleeState* st, int, float dt)
{
    SP::TargetRef_s00d6_b020* tgtObj = self->GetTargetObj();
    SP::cSPCreatureBase_s00d6_b020* tgt = self->GetTargetAsCreature();
    if (!tgtObj)
        return false;
    if (tgt) {
        if (!SP::FUN_00d99470(tgt))
            return false;
        if (tgt->FUN_00c0c130()) {
            ((SP::BehStim_s00d6_b020*)((char*)self->mBehav + 8))->FUN_00bc97f0(0x1000000, 0, 10.0f, tgt);
            return false;
        }
    }

    unsigned dramaFlag = flags5 & 1;
    if (dramaFlag) {
        if (!SP::FUN_00d51660()->IsDramaEventActive(3))
            return false;
    }

    if ((self->mFlags >> 8) & 1) {
        SP::Avatar* avatar = SP::NounManager()->GetAvatar();
        if (avatar) {
            SP::Vec3* p = self->mLoco.GetPosition();
            SP::Vec3* q = avatar->mLoco.GetPosition();
            float dx = q->x - p->x;
            float dy = q->y - p->y;
            float dz = q->z - p->z;
            float lim = DAT_01582e18 + DAT_01582e08;
            if (!(lim * lim > ((dx * dx + dy * dy) + dz * dz)))
                return false;
        }
    }

    SP::cSPCreatureBase_s00d6_b020* animal = tgt ? tgt->Cast(0xd0036e08) : 0;
    SP::ThreatOwner_s00d6_b020* owner = tgtObj->GetOwner();
    SP::OwnerCastObj* ownerCast = owner ? (SP::OwnerCastObj*)owner->Cast(0xb033b403) : 0;
    bool scaredOrCaster = owner->IsPlayerOwned() || ownerCast != 0;

    void* props = ::gCreatureModeStrategy->mProperties;
    uint32_t fleeHash;
    if (flags4 & 0x2000000)
        fleeHash = 0x1eb2ca6d;
    else if (dramaFlag)
        fleeHash = 0xd6379aa9;
    else
        fleeHash = 0x679d56bb;
    float fleeDist = SP::GetPropertyT_float(props, fleeHash, 50.0f);
    float restTime = SP::GetPropertyT_float(props, 0x6a3e31f9, 5.0f);
    float margin = SP::GetPropertyT_float(props, 0x322d5dd6, 0.25f);
    float scaredTime = SP::GetPropertyT_float(props, 0x45ee098c, 3.0f);
    SP::GetPropertyT_float(props, 0x35cd8f0c, 30.0f);
    float hideTime = SP::GetPropertyT_float(props, 0x3d3e2988, 10.0f);
    float hideTime2 = SP::GetPropertyT_float(props, 0x2eba30a8, 10.0f);
    float timerLimit = SP::GetPropertyT_float(props, 0x3757372c, 10.0f);
    float timerReset = SP::GetPropertyT_float(props, 0x9c2ad71b, 5.0f);
    float jumpTime = SP::GetPropertyT_float(props, 0x82fb1acc, 5.0f);
    float randDist = SP::FUN_00d38a30(5, self);
    float speedScale = SP::FUN_00d38a30(3, self);
    float stopDist = ((speedScale > fleeDist) ? fleeDist : speedScale);
    float neighbourWeight = SP::GetPropertyT_float(props, 0xbd82fae8, 0.5f);
    float dirScale = SP::GetPropertyT_float(props, 0x8836316c, 1.0f);
    float viewWeight = SP::GetPropertyT_float(props, 0x82e52579, 1.0f);
    float friendWeight = SP::GetPropertyT_float(props, 0x5be9d5f9, 1.0f);

    SP::Loco_s00d6_b020* loco = &self->mLoco;
    SP::Vec3* myPos = loco->GetPosition();
    SP::Vec3* ownerPos = owner->GetPosition();
    SP::Vec3 ownerDir;
    SP::PlanetModel()->FUN_00b81630(&ownerDir, ownerPos);
    float ownerRadius = owner->GetFootprintRadius();
    float dist = SP::FUN_00d99a60(myPos, loco->GetFootprintRadius(), &ownerDir, ownerRadius, true);
    float scale1 = SP::FUN_00d38a30(1, self);
    float scale2 = SP::FUN_00d38a30(2, self);

    bool nearEnough;
    if (!tgt) {
        nearEnough = self->FUN_00c11480(&ownerDir, dist, scale2);
    } else {
        nearEnough = self->FUN_00c0d560(tgt, scale1, dist) || self->CanReach(tgt, scale2, dist);
    }

    uint32_t selfCount = self->FUN_00c0cdb0();
    if (tgt) {
        uint32_t tgtCount = tgt->FUN_00c0cdb0();
        if (st->mState != 1 && !(tgtCount < selfCount) && dist < fleeDist && self->FUN_00c0b750() > 1) {
            if (timerLimit <= st->mTimer3) {
                st->mTimer2 = timerReset;
                st->mTimer3 = 0.0f;
            }
            st->mTimer3 = st->mTimer3 + dt;
        }
    }
    st->mTimer1 = st->mTimer1 - dt;
    st->mTimer2 = st->mTimer2 - dt;

    if (SP::GetCurrentGameMode() == &DAT_01654c10 && self->FUN_00c04750() != 0 &&
        *(int*)((char*)self->FUN_00c04750() + 0x4b8) == 1) {
        SP::PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (0.0f < st->mTimer1)
            return true;
        if (self->FUN_00c0f570() < 1)
            return false;
        self->InterruptAnimation(0x3a74a08, -1, 0);
        st->mState = 2;
        return false;
    }

    bool hasTimer = st->mTimer2 > 0.0f;
    st->mB15 = hasTimer;
    bool waitOk = !hasTimer || selfCount != 0;
    unsigned freakFlag = (flags4 >> 25) & 1;

    if (st->mAnim == 0 && (flags4 & 0x100000) && scaredOrCaster && nearEnough && !hasTimer && animal &&
        !dramaFlag && st->mState != 5 && st->mState != 1 && st->mState != 7) {
        uint32_t mask[3];
        mask[0] = 0; mask[1] = 0; mask[2] = 0;
        uint32_t i = 0;
        do {
            mask[i] = ~mask[i];
            i = i + 1;
        } while (i < 3);
        mask[2] &= 0xffffff;
        if (animal->FUN_00c0c0e0())
            mask[0] &= 0x7fffffff;
        int id = self->FUN_00c12410(mask, dist + margin, 0, 0, 0, 0, 0);
        if (id != -1 && animal->GetObjectById(id)->m7c != 1) {
            st->mTimer1 = scaredTime;
            st->mState = 4;
            if (st->mB14)
                st->mFreakOut = SP::FreakOut(self, freakFlag);
        }
    }

    // ---- keep-fleeing decision ----
    bool scaredOn;
    if (!(dist >= fleeDist)) {
        scaredOn = (st->mState == 6 || st->mState == 1);
    } else if (st->mState == 6) {
        scaredOn = true;
    } else {
        if (st->mState != 1 && st->mState != 7) {
            bool goOn = true;
            if (dramaFlag) {
                SP::FilterRange range;
                range.FUN_00b41a40(&self->mNearBegin, &waitOk);
                if (range.mpCur != range.mpEnd) {
                    do {
                        SP::NearEntry* e = *range.mpCur;
                        if (e->mDistance < fleeDist) {
                            SP::cSPCreatureBase_s00d6_b020* c = e->mCreature;
                            if (c != self->GetTargetAsCreature() && !c->mDead) {
                                self->SetTarget(c ? (void*)((char*)c + 0x5a8) : 0, 0, 0);
                                st->mState = 0;
                                goOn = false;
                            }
                        }
                        range.Advance();
                    } while (range.mpCur != range.mpEnd);
                }
            }
            if (goOn) {
                st->mTimer1 = hideTime;
                st->mState = 6;
                SP::Vec3 myDir;
                SP::PlanetModel()->FUN_00b81630(&myDir, myPos);
                SP::Vec3 diff;
                diff.x = ownerDir.x - myDir.x;
                diff.y = ownerDir.y - myDir.y;
                diff.z = ownerDir.z - myDir.z;
                SP::Vec3 facing;
                self->MoveToPointAndFacingAtSpeed(2, &myDir, SP::Vector3_Normalize(&facing, &diff), 1.0f, 2.0f);
            }
        }
        scaredOn = (st->mState == 6 || st->mState == 1);
    }
    self->mScared = scaredOn;

    switch (st->mState) {
    case 0:
        if (self->AnimationFinished(st->mAnim)) {
            st->mAnim = 0;
            st->mB14 = true;
            st->mFreakOut = SP::FreakOut(self, freakFlag);
            self->SetStealthed(0, 0);
            self->Hover(1);
            st->mState = 3;
        }
        break;

    case 1: {
        float t = st->mTimer4 + dt;
        st->mTimer4 = t;
        if (t > 1.0f) {
            SP::Vec3 d;
            d.x = myPos->x - ownerDir.x;
            d.y = myPos->y - ownerDir.y;
            d.z = myPos->z - ownerDir.z;
            SP::Vec3 u;
            SP::normalized_safe(&u, &d);
            const float& pick = ((stopDist > dist) ? stopDist : dist);
            float ownerR = owner->GetFootprintRadius();
            float s = (loco->GetFootprintRadius() + ownerR) + pick;
            SP::Vec3 tp;
            tp.x = ownerDir.x + u.x * s;
            tp.y = ownerDir.y + u.y * s;
            tp.z = ownerDir.z + u.z * s;
            {
            SP::Vec3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
            SP::FUN_00d99e20(myPos, &surf);
            self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
            st->mTimer4 = 0.0f;
        }
        SP::PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (flags4 & 0x100000) {
            if (0.0f < st->mTimer1)
                break;
            if (!(stopDist > dist)) {
                if (!loco->IsNearGoal())
                    break;
            }
        }
        if (self->FUN_00c0f570() > 0) {
            self->InterruptAnimation(0x3a74a08, -1, 0);
            st->mState = 2;
            break;
        }
        if ((flags4 & 0x100000) && self->FUN_00c0c140() != -1 && self->mSpotsBegin != self->mSpotsEnd) {
            SP::SpotObj* o = (*self->mSpotsBegin)->mObj;
            st->mVec = o->mPos;
            st->mF2c = o->FUN_00aff550();
            st->mTimer1 = hideTime2;
            st->mState = 7;
            SP::Vec3 d;
            d.x = st->mVec.x - ownerDir.x;
            d.y = st->mVec.y - ownerDir.y;
            d.z = st->mVec.z - ownerDir.z;
            SP::Vec3 u;
            SP::normalized_safe(&u, &d);
            float s = loco->GetFootprintRadius() + st->mF2c;
            SP::Vec3 tp;
            tp.x = st->mVec.x + s * u.x;
            tp.y = st->mVec.y + u.y * s;
            tp.z = st->mVec.z + u.z * s;
            {
            SP::Vec3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
            SP::FUN_00d99e20(myPos, &surf);
            self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
            break;
        }
        goto settle;
    }

    case 2:
        if (!self->WaitForAnimEventOrEnd(0x81d12704, &jumpTime, -1, 0, 1) && !self->AnimationFinished2(0))
            break;
        self->FUN_00c19940(0);
    settle:
        st->mB14 = true;
        st->mFreakOut = SP::FreakOut(self, freakFlag);
        st->mState = 3;
        self->Hover(1);
        break;

    case 3:
        st->mTimer5 = st->mTimer5 - dt;
        self->FUN_00c19940(0);
        if (waitOk) {
            if (loco->IsNearGoal() || !(0.0f < st->mTimer1)) {
                unsigned hideFlag = flags4 & 0x100000;
                if (hideFlag && self->FUN_00c0c140() != -1 && self->mSpotsBegin != self->mSpotsEnd &&
                    !(dist < stopDist * 0.5f)) {
                    SP::SpotObj* o = (*self->mSpotsBegin)->mObj;
                    st->mVec = o->mPos;
                    st->mF2c = o->FUN_00aff550();
                    st->mState = 7;
                    SP::Vec3 d;
                    d.x = st->mVec.x - ownerDir.x;
                    d.y = st->mVec.y - ownerDir.y;
                    d.z = st->mVec.z - ownerDir.z;
                    SP::Vec3 u;
                    SP::normalized_safe(&u, &d);
                    float s = loco->GetFootprintRadius() + st->mF2c;
                    SP::Vec3 tp;
                    tp.x = st->mVec.x + s * u.x;
                    tp.y = st->mVec.y + u.y * s;
                    tp.z = st->mVec.z + u.z * s;
                    {
            SP::Vec3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
            SP::FUN_00d99e20(myPos, &surf);
            self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
                    break;
                }

                SP::Vec3* dirp;
                SP::Vec3 dbuf;
                if (nearEnough) {
                    SP::Vec3 d;
                    d.x = myPos->x - ownerDir.x;
                    d.y = myPos->y - ownerDir.y;
                    d.z = myPos->z - ownerDir.z;
                    dirp = SP::normalized_safe(&dbuf, &d);
                } else {
                    dirp = loco->GetDirection(&dbuf);
                }
                SP::Vec3 w;
                w.x = dirp->x * dirScale;
                w.y = dirp->y * dirScale;
                w.z = dirp->z * dirScale;
                SP::HomeObj* home = self->FUN_00c04590();
                if (!scaredOrCaster || (randDist < dist && (int)sMathRandom.RandomUint32Uniform(100) < 0x32)) {
                    SP::Vec3* q = home->FUN_00c6acc0();
                    SP::Vec3 d;
                    d.x = q->x - myPos->x;
                    d.y = q->y - myPos->y;
                    d.z = q->z - myPos->z;
                    SP::Vec3 n;
                    SP::normalized_safe(&n, &d);
                    w.x = n.x * neighbourWeight + w.x;
                    w.y = n.y * neighbourWeight + w.y;
                    w.z = n.z * neighbourWeight + w.z;
                }
                if (scaredOrCaster && (self->mF90 || hideFlag)) {
                    SP::NearEntry** cur = self->mNearEnd;
                    SP::NearEntry** begin = self->mNearBegin;
                    if (cur != begin) {
                        do {
                            SP::NearEntry* h = cur[-1];
                            SP::cSPCreatureBase_s00d6_b020* a = SP::interface_cast_animal(h->mCreature);
                            SP::Pred pred;
                            if (pred.Test(h) && a && a->mGroup == self->mGroup && a->GetTargetObj() == tgtObj &&
                                a->mBehav->m1d8 == 0x2d852e0) {
                                SP::LocoState* ls = a->mLoco.GetState();
                                if (ls->mHasPath != 0) {
                                    SP::Vec3 d;
                                    d.x = ls->mV14.x - myPos->x;
                                    d.y = ls->mV14.y - myPos->y;
                                    d.z = ls->mV14.z - myPos->z;
                                    SP::Vec3 n;
                                    SP::Vec3* np = SP::Vector3_Normalize(&n, &d);
                                    w.x = friendWeight * np->x + w.x;
                                    w.y = np->y * friendWeight + w.y;
                                    w.z = np->z * friendWeight + w.z;
                                    break;
                                }
                            }
                            cur = cur - 1;
                        } while (cur != begin);
                    }
                }
                if (loco->IsOnView() &&
                    ((animal && ((animal->mFlags >> 9) & 1)) || (ownerCast && ownerCast->m714 == 0))) {
                    SP::cViewer_s00d6_b020* viewer = SP::App()->GetViewer();
                    SP::Vec3 camPos, camDir;
                    viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
                    SP::Vec3 n;
                    SP::Vector3_Normalize(&n, myPos);
                    float dp = (n.x * camDir.x + camDir.y * n.y) + camDir.z * n.z;
                    n.x = camDir.x - dp * n.x;
                    n.y = camDir.y - dp * n.y;
                    n.z = camDir.z - dp * n.z;
                    SP::Vec3 n2buf;
                    SP::Vec3* n2 = SP::Vector3_Normalize(&n2buf, &n);
                    w.x = viewWeight * n2->x + w.x;
                    w.y = n2->y * viewWeight + w.y;
                    w.z = n2->z * viewWeight + w.z;
                }
                SP::Vec3 wbuf;
                SP::Vec3* wn = SP::normalized_safe(&wbuf, &w);
                w = *wn;
                SP::Vec3 tp;
                tp.x = w.x * fleeDist + myPos->x;
                tp.y = myPos->y + w.y * fleeDist;
                tp.z = myPos->z + w.z * fleeDist;
                {
            SP::Vec3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
            SP::FUN_00d99e20(myPos, &surf);
            self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
                loco->GetState()->mHasPath = 2;
                st->mTimer1 = restTime;
                break;
            }
        }
        if (!loco->IsNearGoal() && !self->FUN_00c0c0e0()) {
            if (!(0.0f < st->mTimer5)) {
                st->mTimer5 = jumpTime;
                self->TryJumpToTarget(0, loco->FUN_00c42de0(), &DAT_0169ed0c, 0.0f, 0);
            }
            self->FUN_00c0cff0(2);
        }
        break;

    case 4: {
        SP::Vec3 d;
        d.x = myPos->x - ownerDir.x;
        d.y = myPos->y - ownerDir.y;
        d.z = myPos->z - ownerDir.z;
        SP::Vec3 w;
        SP::normalized_safe(&w, &d);
        if (SP::Vector3Equal(&w, &DAT_0169ed0c)) {
            SP::Vec3 tmp;
            w = *SP::FUN_0059aed0(&tmp, &DAT_0169ed58, loco->GetOrientation());
        }
        float angle = SP::FUN_00572a60(DAT_01583f98);
        SP::Vec3 axis;
        float m[9];
        SP::FUN_00576b00(m, SP::Vector3_Normalize(&axis, loco->GetPosition()), angle);
        SP::Vec3 r;
        r.x = (m[0] * w.x + m[6] * w.z) + m[3] * w.y;
        r.y = (m[7] * w.z + m[4] * w.y) + m[1] * w.x;
        r.z = (m[8] * w.z + m[5] * w.y) + m[2] * w.x;
        SP::Vec3 wbuf;
        w = *SP::Vector3_Normalize(&wbuf, &r);
        SP::Vec3 tp;
        tp.x = w.x * fleeDist + myPos->x;
        tp.y = w.y * fleeDist + myPos->y;
        tp.z = w.z * fleeDist + myPos->z;
        SP::Vec3 surf;
        SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
        SP::FUN_00d99e20(myPos, &surf);
        self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        loco->GetState()->mHasPath = 2;
        if (!self->Hover(1) && self->mGroup->mF58c > 1.52587890625e-05f) {
            float p = SP::GetPropertyT_float(::gCreatureModeStrategy->mProperties, 0x04f7cf2c, 0.25f);
            if (::sMathRandom.RandomDoubleUniform() < (double)p)
                self->TryJumpToTarget(0, &surf, &DAT_0169ed0c, 0.0f, 0);
        }
        st->mState = 5;
        break;
    }

    case 5:
        if (!(0.0f >= st->mTimer1) && !loco->IsNearGoal()) {
            self->FUN_00c0cff0(2);
            break;
        }
        st->mState = 3;
        break;

    case 6:
        self->Hover(0);
        SP::PlayScaredAnimation(self, owner, &st->mFreakOut);
        if (!(0.0f < st->mTimer1) && loco->IsNearGoal())
            return false;
        if (nearEnough && stopDist > dist) {
            if (st->mB14)
                st->mFreakOut = SP::FreakOut(self, freakFlag);
            st->mState = 3;
            self->Hover(1);
            st->mTimer1 = 0.0f;
        }
        break;

    case 7:
        if (stopDist * 0.5f > dist) {
            st->mB14 = true;
            st->mFreakOut = SP::FreakOut(self, freakFlag);
            st->mState = 3;
            break;
        }
        if (!(0.0f > st->mTimer1)) {
            SP::Vec3 d1;
            d1.x = myPos->x - st->mVec.x;
            d1.y = myPos->y - st->mVec.y;
            d1.z = myPos->z - st->mVec.z;
            SP::Vec3 u;
            SP::normalized_safe(&u, &d1);
            SP::Vec3 d2;
            d2.x = ownerDir.x - st->mVec.x;
            d2.y = ownerDir.y - st->mVec.y;
            d2.z = ownerDir.z - st->mVec.z;
            SP::Vec3 v;
            SP::normalized_safe(&v, &d2);
            if (!((u.y * v.y + u.z * v.z) + v.x * u.x >= 0.0f)) {
                if (loco->IsNearGoal() && !self->FUN_00c0e0c0(0x52b0e04))
                    self->PlayAnimation(0x52b0e04, 1, -1);
            } else {
                SP::Vec3 d3;
                d3.x = st->mVec.x - ownerDir.x;
                d3.y = st->mVec.y - ownerDir.y;
                d3.z = st->mVec.z - ownerDir.z;
                SP::Vec3 u2;
                SP::normalized_safe(&u2, &d3);
                float s = loco->GetFootprintRadius() + st->mF2c;
                SP::Vec3 tp;
                tp.x = s * u2.x + st->mVec.x;
                tp.y = st->mVec.y + s * u2.y;
                tp.z = st->mVec.z + s * u2.z;
                {
            SP::Vec3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &tp);
            SP::FUN_00d99e20(myPos, &surf);
            self->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
            }
        } else {
            st->mTimer1 = hideTime;
            st->mState = 6;
        }
        break;
    }

    self->FUN_00c0d0c0(2, hasTimer);
    return true;
}
