// Slice s01033de0 -- the space-stage "slow death" gameplay behaviour (SP::cSpaceGameBehaviorSlowDeath):
// the behaviour object's construction/deletion pair, the per-behaviour Action state machine, the death
// type setup, agent removal, a tuning-variant table refresh and a handful of small interface helpers.
//
// Subject objects:
//   * the 0xa0-byte behaviour object built by FUN_01033de0 (two vtables, cInteraction base, a
//     cGonzagoTimer at +0x78, one anim id at +0x98);
//   * the larger behaviour/editor object used by the Action dispatcher and the small helpers
//     (interface pointers at +0x60..+0x98, looked-up object at +0xa0, tuning source at +0x13c,
//     cViewer sub-objects at +0x178 / +0x2ec).
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// --------------------------------------------------------------------------- retail globals (absolute)
#define G_FACTOR_TABLE   ((float*)0x016df330)      // +0x000 4 per-behaviour float factors
#define G_TUNE_VARIANTS  ((TuningVariant*)0x016df3d8)  // +0x000 4 tuning variants, 0x14 bytes each
#define G_LAST_ANIM_POS  ((float*)0x015b7ca0)      // +0x000 Vec3 of the last animation position
#define G_REAL_ZERO      ((float*)0x01485378)      // _HK_REAL_ZERO
#define G_STR_15B79B8    ((void*)0x015b79b8)
#define G_STR_15B7844    ((void*)0x015b7844)
#define G_STR_16DF2F8    ((void*)0x016df2f8)
#define G_STR_SIMULATOR  ((void*)0x013f09b4)
#define G_VT_BEHAVIOUR_A ((uint32_t)0x01499810)
#define G_VT_BEHAVIOUR_B ((uint32_t)0x01499800)
#define G_VT_ITRACERBASE ((uint32_t)0x013eb938)

// --------------------------------------------------------------------------- opaque services
void* operator_new(uint32_t size, void* name, int a, int b, int c, int d);   // 0x00f473a0
void  operator_delete_array(void* p);                                        // 0x00f47380
void* FUN_01021260();                                                        // 0x01021260
void* GetUniverseContext();                                                  // 0x01021080
int   GetTerraformPlanetType(float value);                                   // 0x00fc1fd0
void* GetCurrentGameMode();                                                  // 0x00b5b800
float FUN_01043150(void* ptr, float value);                                  // 0x01043150
struct PlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* pos);            // 0x00b815a0
};
PlanetModel* GetPlanetModel();                                               // 0x00b3d350

// --------------------------------------------------------------------------- interfaces
struct Iface {                                  // reference-counted interface (+0x00 vtable)
    PV(0)
    virtual void pv1();                         // +0x04  Release
    virtual void pv2(int value);                // +0x08
    virtual void pv3(int value);                // +0x0c
    virtual bool pv4();                         // +0x10
};

struct AppView {                                // SP::App()
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual uint32_t pv20();                    // +0x50
};
AppView* SP_App();                              // 0x0067dd10

struct ObjA0 {                                  // object looked up at +0xa0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32)
    virtual void pv33(void* name, uint32_t value);   // +0x84
};

struct TuningVariant {                          // EA::Variant, 0x14 bytes
    uint8_t mPad00[0x14];
    void Set(uint32_t value);                   // 0x00542b80
};

struct TuningSource {                           // object pointed at by +0x13c
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
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
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual Vec3* pv11();                       // +0x2c  GetPosition
    PV(12) PV(13)
    virtual void pv14(const Vec3* pos);         // +0x38
    void FUN_c41d60(void* str);                 // 0x00c41d60
    void FUN_c41d90(void* str);                 // 0x00c41d90
};

struct Queryable {                              // object returned by the behaviour's vt+0x58 slot
    PV(0) PV(1)
    virtual Queryable* pv2(uint32_t tag);       // +0x08
    PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual void pv21();                        // +0x54
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    virtual void pv50(int value);               // +0xc8
    uint8_t mPad04_to_c0[0xc0 - 0x04];
    Loco    mLoco;                              // +0xc0 (embedded sub-object)
    uint8_t mPadC4[0x130 - 0xc4];
    uint8_t mFlag130;                           // +0x130
};

struct Viewer {                                 // cViewer helper sub-object (0x007c4000)
    uint32_t mVt;
    void FUN_007c4000();
};

struct BigThing {                               // object removed by FUN_010347a0 (vtbl 0x013eb938)
    uint32_t mVt;                               // +0x000
    Viewer   mSub004;                           // +0x004
    uint8_t  mPad08[0x178 - 0x08];
    Viewer   mSub178;                           // +0x178
    uint8_t  mPad17C[0x2ec - 0x17c];
    Viewer   mSub2EC;                           // +0x2ec

    void* FUN_010347a0(uint8_t del);
};

struct SlowDeathTimer {                         // SP::cGonzagoTimer (0x20 bytes)
    uint8_t mPad00[0x20];
    void ctor();                                // 0x00b63890
    void dtor();                                // 0x00b638b0
    void Restart();                             // 0x00bc3130  (this == &mTimer, cSPTimer::Restart)
};

struct SlowDeathCore {                          // 0xa0-byte cInteraction-derived behaviour object
    uint32_t mVt0;                              // +0x00
    uint32_t mVt4;                              // +0x04
    uint8_t  mPad08[0x74 - 0x08];
    int32_t  mMode;                             // +0x74
    SlowDeathTimer mTimer;                      // +0x78
    int32_t  mAnimId;                           // +0x98
    uint8_t  mPad9C[0xa0 - 0x9c];

    void baseCtor();                            // 0x00abf320
    void baseDtor();                            // 0x00abf190

    void* FUN_01033e60(uint8_t del);
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

struct View {                                   // helper subject of FUN_01034680
    bool FUN_c71540();                          // 0x00c71540
    int  FUN_c70880();                          // 0x00c70880
};

struct TerraformSource {                        // object returned by FUN_01021260()
    float FUN_c70a20();                         // 0x00c70a20
};

// --------------------------------------------------------------------------- views of the large dispatchers
struct DeathLoco {                              // locomotion sub-object embedded at creature+0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual Vec3* pv11(int arg);                // +0x2c  GetPosition (the argument is unused)
    PV(12) PV(13)
    virtual Vec3* pv14(float a, float b);       // +0x38  surface position (used by SetDeathType)
};

struct AnimTimer {                              // creature->mNoAttackTimer (+0x5a8)
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void  pv6(float value);             // +0x18  apply the queried animation time
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)
    virtual float pv22(uint32_t tag, int anim, void* pos);   // +0x58
};

struct Creature {                               // SP::cSPCreatureBase (partial view)
    uint8_t    mPad00[0xc0];
    DeathLoco  mLoco;                           // +0x0c0
    uint8_t    mPadC4[0x2b0 - 0xc4];
    int32_t    m2B0;                            // +0x2b0  animation-driver mode
    uint8_t    mPad2B4[0x5a8 - 0x2b4];
    AnimTimer* mNoAttackTimer;                  // +0x5a8
    uint8_t    mPad5AC[0xb54 - 0x5ac];
    void*      mB54;                            // +0xb54

    char     CCM_Check();                       // 0x00c0e420
    int      GetCurrentAnimationGUID();
    uint32_t InterruptAnim(uint32_t anim, int32_t a, int32_t b);   // 0x00c12310
    uint32_t PlayAnim(uint32_t anim, int32_t a, int32_t b);
};

struct B54 {                                    // object stored at creature+0xb54
    float FUN_a049f0(int32_t value);            // 0x00a049f0
};

struct DeathView {                              // SP::cSpaceGameBehaviorSlowDeath (behaviour side)
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
    virtual Queryable* pv22();                  // +0x58
    uint8_t  mPad5C[0x74 - 0x5c];
    int32_t  m74;                               // +0x74  death type / armed mode
    SlowDeathTimer mTimer;                      // +0x78  cGonzago/cSP timer pair
    int32_t  m98;                               // +0x98  current animation id
    uint8_t  mPad9C[0xa0 - 0x9c];
    ObjA0*   mObjA0;                            // +0xa0
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
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual void pv17(int mode, const Vec3* value, int count);   // +0x44
};

struct Gfx94 {                                  // object stored at behaviour+0x94
    PV(0) PV(1) PV(2)
    virtual void pv3(int value);                // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    virtual void pv15(float radius, float height, void* out);    // +0x3c
};

struct cSolarSystem {                           // SP::cSolarSystem (partial view)
    uint8_t mPad00[0x10];
    void**  mPlanetsBegin;                      // +0x10
    void**  mPlanetsEnd;                        // +0x14

    void ActivateGraphics(int flag);            // 0x00c86c70
    void FUN_c86390(float value);               // 0x00c86390
};

cSolarSystem* GetSolarSystem(void* star);       // 0x00c8b770 SP::cStar::GetSolarSystem
char FUN_00c8b800(void* star);                  // 0x00c8b800
Vec3* Vector3_Normalize(Vec3* out, const Vec3* in);   // 0x00436ce0

#define G_PARTICLE_RADIUS ((*(float*)0x015b7730))
#define G_PARTICLE_COUNT  ((*(int32_t*)0x015b7734))

struct Behavior {                               // large behaviour/editor subject
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
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

// --------------------------------------------------------------------------- 0x01033de0
// Build a fresh 0xa0-byte slow-death behaviour object.
// @ 0x01033de0
void* FUN_01033de0()
{
    SlowDeathCore* p = (SlowDeathCore*)operator_new(0xa0, G_STR_SIMULATOR, 0, 0, 0, 0);
    if (p != 0) {
        p->baseCtor();
        p->mVt0 = G_VT_BEHAVIOUR_A;
        p->mVt4 = G_VT_BEHAVIOUR_B;
        p->mMode = 0;
        p->mTimer.ctor();
        p->mAnimId = 0;
        return p;
    }
    return 0;
}

// --------------------------------------------------------------------------- 0x01033e60
// @ 0x01033e60
void* SlowDeathCore::FUN_01033e60(uint8_t del)
{
    mVt0 = G_VT_BEHAVIOUR_A;
    mVt4 = G_VT_BEHAVIOUR_B;
    mTimer.dtor();
    baseDtor();
    if ((del & 1) != 0) {
        operator_delete_array(this);
    }
    return this;
}

// --------------------------------------------------------------------------- 0x01033ea0
// Apply a change to the behaviour's target agent: re-point the locomotion object at the planet
// surface position under the agent, clear its "seated" flag and refresh two locomotion strings.
// @ 0x01033ea0
bool Behavior::FUN_01033ea0(int value)
{
    bool result = FUN_00abf640(value);
    Queryable* owner = pv22();
    if (owner != 0) {
        Queryable* agent = owner->pv2(0xce9f6639);
        if (agent != 0) {
            agent->pv21();
            Loco* loco = &agent->mLoco;
            Vec3 point;
            loco->pv14(GetPlanetModel()->DirectionToSurfacePosition(&point, loco->pv11()));
            agent->mFlag130 = 0;
            loco->FUN_c41d60(G_STR_16DF2F8);
            loco->FUN_c41d90(G_STR_16DF2F8);
        }
    }
    return result;
}

// --------------------------------------------------------------------------- 0x01033f50
// Per-tick action dispatcher.  Resolves the creature the behaviour drives (behaviour slot 0x58 ->
// tag 0xce9f6639), bails out for the "attack" animation / the CCM gate, then feeds the locomotion
// position through Vector3_Normalize into the creature's no-attack timer for the armed mode
// (m74 = 1..8).
//
// NOT byte-exact, and not matchable with this toolchain: retail stores the eight-way switch's jump
// table inline at 0x01034238 (inside the function), while this build always emits jump tables in
// .rdata, which puts the table bytes outside the compared function slice.  Modes 3, 6 (alternate
// path), 7 and 8 are only partly recovered; see the comments below.
// @ 0x01033f50
int Behavior::FUN_01033f50()
{
    DeathView* self = (DeathView*)this;
    Queryable* q = self->pv22();
    if (q == 0) {
        return 0;
    }
    Creature* c = (Creature*)q->pv2(0xce9f6639);
    if (c == 0) {
        return 0;
    }
    if (c->GetCurrentAnimationGUID() == 0x3cc7f55) {
        return 1;
    }
    if (!c->CCM_Check() && ((B54*)c->mB54)->FUN_a049f0(self->m98) < 1.0f) {
        return 1;
    }
    Vec3 buf;
    switch (self->m74) {
    case 1:
        c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 6, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
        return 0;
    case 2:
        c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 7, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
        return 0;
    case 3:
        // partial: retail normalises into the 0x4c frame slot and breaks out to the code after the
        // switch (shared with mode 6's alternate path); the exact animation index is not recovered.
        c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 0, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
        return 0;
    case 4:
        c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 0, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
        return 0;
    case 5:
        c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 7, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
        return 0;
    case 6:
        if (c->GetCurrentAnimationGUID() != 0x3cc80e8) {
            c->mNoAttackTimer->pv6(c->mNoAttackTimer->pv22(0xffffffff, 5, Vector3_Normalize(&buf, c->mLoco.pv11(0))));
            return 0;
        }
        // partial: retail compares the cSPTimer elapsed time against 0x2711 and, while it is below,
        // plays animation 0x3cc838c (1, 0xffffffff) and stores the returned id into the behaviour's
        // animation-id slot (+0x98).
        self->m98 = c->PlayAnim(0x3cc838c, 1, 0xffffffff);
        return 0;
    default:
        // partial: modes 7 and 8 (the two "interrupt 0x4286319 / 0x428631a" paths) are not recovered.
        return 0;
    }
}

// --------------------------------------------------------------------------- 0x01034260
// Arm the death type: store the new mode into the behaviour's timer/refcount slot (+0x74), restart
// the cSPTimer at +0x78, re-resolve the creature tag 0xce9f6639, clear the animation id and then run
// the mode's animation script (cases 1..8); the tail re-arms the graphics state and, when the script
// asked for a new animation, retries a random world position until it is accepted.
//
// NOT byte-exact and structurally unmatchable: the chk.py bound for this address (848 bytes) is
// derived from the distance to the next listed function and therefore spans the unlisted
// FUN_01034340 at 0x01034340; retail also stores this switch's jump table inline at 0x01034590.
// The trailing block (the 0x90-byte parameter record, the loco slot 0xdc call and the
// MakeRandomWorldPosition retry loop) is not recovered.
// @ 0x01034260
void Behavior::FUN_01034260(int deathType)
{
    DeathView* self = (DeathView*)this;
    self->m74 = deathType;
    self->mTimer.Restart();
    Queryable* q = self->pv22();
    if (q == 0) {
        return;
    }
    Creature* c = (Creature*)q->pv2(0xce9f6639);
    if (c == 0) {
        return;
    }
    bool retry = false;
    self->m98 = 0;
    switch (self->m74) {
    case 1:
        self->m98 = c->InterruptAnim(0x3cc7f35, 0xffffffff, 0);
        break;
    case 2:
        c->InterruptAnim(0x3cc7f55, 0xffffffff, 0);
        self->m98 = c->PlayAnim(0x3cc83ce, 1, 0xffffffff);
        break;
    case 3:
        c->InterruptAnim(0x3cc7f55, 0xffffffff, 0);
        self->m98 = c->PlayAnim(0x5c01ade, 1, 0xffffffff);
        retry = true;
        break;
    case 4:
        c->InterruptAnim(0x3cc7f55, 0xffffffff, 0);
        self->m98 = c->PlayAnim(0x3cc7fd0, 1, 0xffffffff);
        break;
    case 5:
        c->InterruptAnim(0x3cc7f55, 0xffffffff, 0);
        self->m98 = c->PlayAnim(0x3cc8401, 1, 0xffffffff);
        break;
    case 6:
        c->InterruptAnim(0x3cc7f55, 0xffffffff, 0);
        self->m98 = c->PlayAnim(0x3cc80e8, 1, 0xffffffff);
        retry = true;
        break;
    case 7:
        self->m98 = c->InterruptAnim(0x4286319, 0xffffffff, 0);
        c->m2B0 = 6;
        break;
    case 8:
        self->m98 = c->InterruptAnim(0x428631a, 0xffffffff, 0);
        c->m2B0 = 6;
        break;
    default:
        break;
    }
    // partial: the trailing block re-arms the graphics state (globals 0x016df2f8/0x016df2fc/
    // 0x016df300 plus the locomotion surface position through the loco slot 0xdc call), releases the
    // temporary, calls FUN_00c0cff0(0) and - when the script above set `retry` - loops on
    // cPlanetModel::MakeRandomWorldPosition until FUN_00b7e3e0 accepts the point before calling
    // FUN_00c0cff0(2).  It is not reconstructed here.
    (void)retry;
}

// --------------------------------------------------------------------------- 0x010345b0
// Drop an agent from the behaviour: forward the removal to the cInteraction base and, when the
// reference table still holds an agent for that index, tell its query object to detach.
// @ 0x010345b0
void Behavior::RemoveAgent(AgentRef* ref, uint32_t index, int a2, int a3, int a4, int a5)
{
    void* agent = ref->mChunks[index >> 7]->mEntries[index & 0x7f].mAgent;
    RemoveArgs args;
    args.mRef = ref;
    args.mIndex = index;
    args.mA = a2;
    args.mB = a3;
    args.mC = a4;
    args.mD = a5;
    baseRemoveAgent(args);
    if (agent != 0) {
        Queryable* query = ((Queryable*)agent)->pv2(0xce9f6639);
        if (query != 0) {
            query->pv50(0);
        }
    }
}

// --------------------------------------------------------------------------- 0x01034630
// Per-behaviour factor lookup: reuse the cached non-zero factor, else recompute it from the tuning
// variant table.
//
// NOT byte-exact: retail keeps the cached-return block out of line at the end of the function (the
// "cached != 0" branch is a forward jump past the recompute call), while every equivalent source
// shape tried here places it inline right after the comparison; the instruction mix, the x87
// cached-value spill into the argument home slot and the function size (72 bytes) do agree.
// @ 0x01034630
float FUN_01034630(int index, float value, char reuse)
{
    if (reuse != 0) {
        float cached = G_FACTOR_TABLE[index];
        if (cached != *G_REAL_ZERO) {
            return cached;
        }
    }
    return FUN_01043150((char*)G_TUNE_VARIANTS + index * 0x14, value);
}

// --------------------------------------------------------------------------- 0x01034680
// @ 0x01034680
int FUN_01034680(View* view)
{
    if (view->FUN_c71540()) {
        return 1;
    }
    int stage = view->FUN_c70880();
    return (stage == 1) ? 2 : 0;
}

// --------------------------------------------------------------------------- 0x010346b0
// Store the last animation position used by the behaviour.
// @ 0x010346b0
void __stdcall FUN_010346b0(float x, float y, float z)
{
    G_LAST_ANIM_POS[0] = x;
    G_LAST_ANIM_POS[1] = y;
    G_LAST_ANIM_POS[2] = z;
}

// --------------------------------------------------------------------------- 0x010346e0
// Refresh the four per-behaviour factors and tuning variants from the tuning source.
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

// --------------------------------------------------------------------------- 0x010347a0
// @ 0x010347a0
void* BigThing::FUN_010347a0(uint8_t del)
{
    mSub2EC.FUN_007c4000();
    mSub178.FUN_007c4000();
    mSub004.FUN_007c4000();
    mVt = G_VT_ITRACERBASE;
    if ((del & 1) != 0) {
        operator_delete_array(this);
    }
    return this;
}

// --------------------------------------------------------------------------- 0x010347e0
// Hand the current animation (App()->slot 0x50) to the looked-up object's slot 0x84 method under the
// animation-name string 0x015b79b8.
// @ 0x010347e0
void Behavior::FUN_010347e0()
{
    AppView* app = SP_App();
    ObjA0* obj = mObjA0;
    obj->pv33(G_STR_15B79B8, app->pv20());
}

// --------------------------------------------------------------------------- 0x01034810
// Same hand-off as FUN_010347e0 but under the second name string 0x015b7844.
// @ 0x01034810
void Behavior::FUN_01034810()
{
    AppView* app = SP_App();
    ObjA0* obj = mObjA0;
    obj->pv33(G_STR_15B7844, app->pv20());
}

// --------------------------------------------------------------------------- 0x01034840
// @ 0x01034840
void Behavior::FUN_01034840()
{
    if (mIface90 != 0) {
        mIface90->pv3(1);
        if (mIface90 != 0) {
            Iface* old = mIface90;
            mIface90 = 0;
            old->pv1();
        }
    }
}

// --------------------------------------------------------------------------- 0x01034880
// @ 0x01034880
void Behavior::FUN_01034880()
{
    if (FUN_01021260() == 0) {
        return;
    }
    if (GetUniverseContext() != 0) {
        return;
    }
    if (GetTerraformPlanetType(((TerraformSource*)FUN_01021260())->FUN_c70a20()) == 4) {
        mIface60->pv3(1);
        if (GetCurrentGameMode() == (void*)0x01654c10) {
            if (mIface68->pv4()) {
                return;
            }
            mIface68->pv2(0);
            return;
        }
        if (mIface64->pv4()) {
            return;
        }
        mIface64->pv2(0);
        return;
    }
    if (GetCurrentGameMode() == (void*)0x01654c10) {
        mIface68->pv3(1);
    } else {
        mIface64->pv3(1);
    }
    if (mIface60->pv4()) {
        return;
    }
    mIface60->pv2(0);
}

// --------------------------------------------------------------------------- 0x01034950
// Enable/disable the behaviour's interface bank for a death mode: mode 1 arms the "full" set (all
// interface pointers switched on with argument 1, two of them with 2), mode 2 switches several
// pointers off again and finishes by handing a copy of the behaviour's surface vector (+0x110) to
// the +0x80 interface's slot 0x44 method, and modes 0/3 arm the remaining subset.  The whole body is
// guarded by the +0x6c interface pointer.
//
// The second (unused) argument is real: retail's epilogue is `ret 8`, i.e. thiscall plus two stack
// arguments, and the original caller only ever fills the first one.  The +0x6c and +0x68 interface
// pointers are held in locals so that the guard and the following calls reuse one register.
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

// --------------------------------------------------------------------------- 0x01034b90
// Solar-system graphics preroll (PDB hint: SP::cSPSpaceGfx::PrerollParticles).  Looks the star's
// solar system up and, when it holds no planets yet, activates its graphics and pushes the global
// particle radius into the +0x94 interface's slot 0x3c method once per particle slot before
// switching it off.
//
// partial: the branch taken when the solar system does hold planets (noun-manager ProcessPending,
// 0x5a iterations of the +0xc86390 method, then the per-planet follow-up loop) is not reconstructed.
// @ 0x01034b90
void Behavior::FUN_01034b90(void* star)
{
    IfaceBank* self = (IfaceBank*)this;
    cSolarSystem* sys = GetSolarSystem(star);
    if (sys == 0) {
        return;
    }
    if (sys->mPlanetsBegin != sys->mPlanetsEnd) {
        // partial: planet-list present path (see note above).
        return;
    }
    if (FUN_00c8b800(star)) {
        return;
    }
    sys->ActivateGraphics(1);
    Vec3 buf;
    for (int i = 0; i < G_PARTICLE_COUNT; i++) {
        ((Gfx94*)self->mIface94)->pv15(G_PARTICLE_RADIUS, G_PARTICLE_RADIUS, &buf);
    }
    ((Gfx94*)self->mIface94)->pv3(0);
}
