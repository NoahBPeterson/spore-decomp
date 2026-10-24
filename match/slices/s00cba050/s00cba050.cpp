// Slice s00cba050 (worker 23) -- the space-defence / cultural / resource projectile
// explode-and-drive block at 0x00CBA050.  Functions (VA order):
//   0x00CBA050  SP::cSpaceDefenseMissile::Explode             (1158 bytes)
//   0x00CBA4E0  SP::cSpaceDefenseMissile::TakeHit             (  93 bytes, ret 0x14)
//   0x00CBA560  SP::cSPSpaceToolData::DoAreaEffectSpellHit    ( 301 bytes)
//   0x00CBA690  SP::cCulturalProjectile::Explode              (1516 bytes)
//   0x00CBAC80  SP::cResourceProjectile::Update              ( 128 bytes)
//   0x00CBAD00  SP::cICBM::Update                            ( 138 bytes)
//   0x00CBAD90  FUN_00cbad90, a property-list serialiser      ( 134 bytes)
//   0x00CBAF00  Simulator::cPathFollowingLocomotion::cPathFollowingLocomotion (280, ret 8)
//
// Every field below is a named member of a declared struct, never a raw offset.
// Callees keep the original's calling convention (this in ecx unless marked cdecl).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the originals have no EH
// frame although 0x00cba050 and 0x00cba560 own eastl vectors with destructors).
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };
struct Matrix3Rows { float m[3][3]; };

#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_pf)(void*, float);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void* (__thiscall *Fn_p_p)(void*);
typedef void* (__thiscall *Fn_p_pi)(void*, int);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pi)(void*, int);
typedef Vector3* (__thiscall *Fn_v3_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_pfiiii)(void*, float, int, int, int, int);

// ---------------------------------------------------------------------------
// engine data
// ---------------------------------------------------------------------------
extern float DAT_01470f1c;                     // 0x01470f1c  2.0f   guide arrival radius
extern float DAT_01486110;                     // 0x01486110  5.0f   ICBM ground clearance
extern float DAT_01471064;                     // 0x01471064  0.5f   radius half
extern float DAT_013eeda0;                     // 0x013eeda0  8.0f   radius scale
extern float DAT_014853e0;                     // 0x014853e0  4.0f   transform scale
extern float DAT_01485720;                     // 0x01485720  1.0f   HK_REAL_ONE
extern float DAT_0147515c;                     // 0x0147515c  FLT_MAX
extern "C" float DAT_0169aa18 = 0.0f;          // 0x0169aa18  ZERO.x
extern "C" float DAT_0169aa1c = 0.0f;          // 0x0169aa1c  ZERO.y
extern "C" float DAT_0169aa20 = 0.0f;          // 0x0169aa20  ZERO.z
extern "C" void* DAT_013f94d4 = 0;             // 0x013f94d4  space-tool interface key
extern "C" void* DAT_01186577 = 0;             // 0x01186577  serialiser node key
extern "C" void* gRandom = 0;                  // 0x01601760  EA::Random global (this)

// ---------------------------------------------------------------------------
// engine entry points
// ---------------------------------------------------------------------------
struct Obj;
void*   __cdecl SP_GetCurrentGameMode();                        // 0x00b5b800
void*   __cdecl SP_PlanetModel(Vector3* pPos);                  // 0x00b3d350
void*   __cdecl SP_RelationshipManager();                       // 0x00b3d2c0
void*   __cdecl SP_EffectsManagerPtr();                         // 0x0067ddd0
void*   __cdecl SP_NounManager();                               // 0x00b3d300
void*   __cdecl SP_ToolManager();                               // 0x00b3d240
void*   __cdecl eastl_RBTreeIncrement(void* pNode);             // 0x00921580
void    __cdecl EA_IO_WriteUint32(int a, void* p, int n, int f); // 0x0093aa70
Vector3* __cdecl SP_NormalizedSafe(Vector3* pOut, Vector3* pV); // 0x00449c20
Matrix3Rows* __cdecl Matrix3FromFacingAndUp(Matrix3Rows* pOut, Vector3* pFacing,
                                            Vector3* pUp);      // 0x0069b440
int     __cdecl GetPlayerEmpireOrMinus1();                      // 0x00b1f9d0
unsigned __cdecl RandomUint32Uniform(unsigned range);           // 0x00a68fb0 (this=gRandom)
double  __cdecl RandomDoubleUniform();                          // 0x009360d0 (this=gRandom)

// A generic engine object; each method is named after its retail address.
struct Obj {
    int      m_8e7f80();                     // 0x008e7f80  damage state (this+0x34)
    void     m_b225d0(void* pNoun);          // 0x00b225d0  cGameNounManager::RemoveNoun
    void*    m_b25f40(void* pOwner);         // 0x00b25f40  noun lookup by owner
    bool     m_b81f90(Vector3* p);           // 0x00b81f90  IsPositionBelowSurface
    void     m_bfc460(int a);                // 0x00bfc460  store a at this+0x34
    Vector3* m_position();                   // vftable slot 0x2c
    void     m_setPosition(Vector3* p);      // vftable slot 0x38
};

// A world transform provider (position / facing through its vtable).
struct cWorldXform {
    Vector3* m_position();                   // vftable slot 0x2c
    Vector3* m_facing();                     // vftable slot 0x5c
};

// A hit object reached from the tool-manager list: an embedded transform at +0x34,
// a position at +0xc4, a target block at +0x508 and a live-hit count at +0x714.
struct cHitObject {
    uint32_t  mPad000[0x34 / 4];
    cWorldXform mLoco;                       // +0x034
    uint32_t  mPad050[(0xc4 - 0x50) / 4];
    Vector3   mPosition;                     // +0x0c4
    uint32_t  mPad0d0[(0x508 - 0xd0) / 4];
    uint32_t  m508;                          // +0x508
    uint32_t  mPad50c[(0x714 - 0x50c) / 4];
    int       mLiveHits;                     // +0x714
};

// The space-tool data object stored at +0x5e0 / +0x518 of the projectile classes.
struct cSPSpaceToolData {
    uint32_t mPad000[0x114 / 4];
    void*    mpTarget_114;                   // +0x114
    uint32_t mPad118[(0x1ac - 0x118) / 4];
    float    m1ac;                           // +0x1ac
    float    m1b0;                           // +0x1b0
    float    m1b4;                           // +0x1b4
    float    m1b8;                           // +0x1b8
    uint32_t mPad1bc[(0x1d0 - 0x1bc) / 4];
    float    m1d0;                           // +0x1d0
    uint32_t mPad1d4[(0x218 - 0x1d4) / 4];
    int      m218;                           // +0x218
    int      m21c;                           // +0x21c
    int      m220;                           // +0x220
    int      m224;                           // +0x224
    void     m_bfc460(int a);                // 0x00bfc460  store a at this+0x34
    float    GetDamageRadius(float a, float b, int c, int d, int e, int f);  // 0x0104be40
};

// The object list a tool-manager query fills (eastl::vector<Obj*, sp_vector_allocator>).
struct cSPObjectList {
    Obj**  mpBegin;
    Obj**  mpEnd;
    Obj**  mpCapacity;
    uint32_t mAllocator;
};

// eastl::vector<Vector3, sp_vector_allocator>.
struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3Vector() {}                        // (retail constructs in place at 0x00473460)
    void CopyFrom(const Vector3Vector& src);  // 0x00473460
};

// The locomotion object at cCulturalProjectile+0x51c: a path vector at +0x10, a
// guidance sub-block at +0x508 and a blast radius at +0xc50.
struct cCulturalLocomotion {
    uint32_t mPad000[0x10 / 4];
    Vector3Vector mPath;                     // +0x010
    uint32_t mPad020[(0x508 - 0x20) / 4];
    uint32_t mBlock508;                      // +0x508
    uint32_t mPad50c[(0xc50 - 0x50c) / 4];
    float    mRadius;                        // +0xc50
};

// cSPTimer, only its time queries matter here.
struct cSPTimer {
    uint32_t mPad00[0x18 / 4];
    bool     mRunning;                       // +0x18
    uint64_t GetElapsedTime();               // 0x00bc3190  -> edx:eax
    void     Start();                        // 0x00bc30f0
    bool     IsRunning();                    // 0x00feba90  -> +0x18
};

namespace SP {

// ============================================================================
// cSpaceDefenseMissile -- `this` is the missile base object.  The damage tool
// sits at +0x5e0, the embedded locomotive at +0x34, a second tool block at +0x518.
// ============================================================================
struct cSpaceDefenseMissile {
    uint32_t          mPad000[0x34 / 4];
    cWorldXform       mLoco;                 // +0x034
    uint32_t          mPad050[(0x508 - 0x50) / 4];
    void*             mpVtable508;           // +0x508
    void*             mpField50c;            // +0x50c
    cSPSpaceToolData* mpTool518;             // +0x518
    cSPSpaceToolData* mpGuidance51c;         // +0x51c
    uint32_t          mPad520[(0x550 - 0x520) / 4];
    float             m550;                  // +0x550
    uint32_t          mPad554[(0x5e0 - 0x554) / 4];
    cSPSpaceToolData* mpDamageTool;          // +0x5e0
    void Explode();
};

// ============================================================================
// cCombatant -- `this` is the subobject embedded at missile+0x4d0.
// ============================================================================
struct cCombatant {
    uint32_t mPad000[0x518 / 4];
    int  m_8e7f80();                                     // 0x008e7f80  damage state
    void m_bfcdd0(float f, int a, int b, int c, int d);  // 0x00bfcdd0  base TakeHit
    void TakeHit(float f, int a, int b, int c, int d);   // ret 0x14
};

// ============================================================================
// cCulturalProjectile guidance block (Update's `this`).
// ============================================================================
struct cCulturalProjectile {
    uint32_t mPad000[0x34 / 4];
    cWorldXform mLoco;                       // +0x034  embedded locomotion/transform
    uint32_t mPad050[(0x518 - 0x50) / 4];
    void*    mpLocomotion;                   // +0x518
    void*    mpVehicle;                      // +0x51c
    void*    mpTarget;                       // +0x520
    void*    mpTool;                         // +0x524
    int      mAimIndex;                      // +0x528
    Vector3  mTargetPos;                     // +0x52c
    uint8_t  mbFlag538;                      // +0x538
    uint8_t  mbSpin539;                      // +0x539
    uint32_t mPad53c[(0x560 - 0x53c) / 4];
    uint32_t mOwner;                         // +0x560
    uint32_t mPad564[(0x568 - 0x564) / 4];
    cSPTimer mTimer;                         // +0x568
    void Explode();
};

// ============================================================================
// cResourceProjectile guidance block.
// ============================================================================
struct cResourceProjectile {
    uint32_t mPad000[0x1c / 4];
    Vector3  mEndPoint;                      // +0x01c
    uint32_t mPad028[(0x2c - 0x28) / 4];
    cSPTimer mTimer;                         // +0x02c
    bool Update();
};

// ============================================================================
// cICBM guidance block.
// ============================================================================
struct cICBM {
    uint32_t mPad000[0x1c / 4];
    Obj*     mpGuidance_1c;                  // +0x01c
    bool Update();
};

}  // namespace SP

// cCulturalProjectile::LaunchProjectile (0x00cbda10) returns an object whose
// +0x508 block is the guidance data (0x00cbb2a0's cCulturalBody).
struct cCulturalBody {
    void Explode();                          // 0x00cba690
};

// The projectile base object that owns the guidance blocks below (resource/ICBM
// guidance sits at base+0x504).  Explode is virtual-slot-free and reached directly.
struct cProjectileBase {
    void ExplodeResource();                  // 0x00cb91d0
    void ExplodeICBM();                      // 0x00cb9650
};

// ============================================================================
// @ 0x00cba4e0  SP::cSpaceDefenseMissile::TakeHit
// ============================================================================
void SP::cCombatant::TakeHit(float f, int a, int b, int c, int d)
{
    int before = m_8e7f80();
    m_bfcdd0(f, a, b, c, d);    int after = m_8e7f80();
    if (after == 2 && before != 2) {
        SP::cSpaceDefenseMissile* pMissile = (SP::cSpaceDefenseMissile*)((char*)this - 0x518);
        pMissile->Explode();
        ((Obj*)SP_NounManager())->m_b225d0(pMissile);
    }
}

// ============================================================================
// @ 0x00cba050  SP::cSpaceDefenseMissile::Explode
// Fans the warhead's damage over every object the tool manager returns for the
// missile, nudging each hit object's +0x508 block, then plays the death effect.
// ============================================================================
void SP::cSpaceDefenseMissile::Explode()
{
    Obj* pManager = (Obj*)SP_ToolManager();

    cSPObjectList vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;

    // tool manager -> slot 0x48(float f, ObjVector* out) fills the hit list
    float f = ((float (__thiscall*)(void*))0x0104bdb0)(mpDamageTool);
    Vector3* pDir = mLoco.m_position();
    Vector3* unused = mLoco.m_facing();
    (void)unused; (void)pDir; (void)f;
    ((Fn_v_pp)VTSLOT(pManager, 0x48))(pManager, &vec);

    m550 = 0.0f;
    mpGuidance51c->m_bfc460(2);

    int n = (int)(vec.mpEnd - vec.mpBegin);
    bool bAll = false;
    for (int i = 0; i < n; ++i) {
        Obj* p = vec.mpBegin[i];
        if (!p)
            continue;
        cHitObject* pHit = (cHitObject*)((Fn_p_pi)VTSLOT(p, 0xb8))(p, 0xb033b403);
        if (!pHit)
            continue;

        void* pKey = 0;
        if (mpDamageTool->mpTarget_114)
            pKey = ((Fn_p_pi)VTSLOT(mpDamageTool->mpTarget_114, 0xb8))(
                mpDamageTool->mpTarget_114, (int)&DAT_013f94d4);

        Vector3* pa = mLoco.m_position();
        Vector3* pb = pHit->mLoco.m_position();
        Vector3 dir;
        dir.x = pb->x - pa->x;
        dir.y = pb->y - pa->y;
        dir.z = pb->z - pa->z;
        float inv = 1.0f / sqrtf(dir.z * dir.z + (dir.y * dir.y + dir.x * dir.x));
        dir.x *= inv; dir.y *= inv; dir.z *= inv;

        float fMin = ((float (__thiscall*)(void*))0x0104bdc0)(mpDamageTool);
        float fBase = ((float (__thiscall*)(void*))0x00ce6940)(mpDamageTool);
        float span = fMin - fBase;
        float r = (float)::RandomDoubleUniform() * span;
        if (r < span) { if (r < 0.0f) r = 0.0f; } else r = span;

        void* pArg = pKey;
        ((Fn_v_p)VTSLOT(this, 0x4c))(this);
        ((Obj*)&pHit->m508)->m_bfc460(
            (int)(((float (__thiscall*)(void*))0x00ce6940)(mpDamageTool) + r));
        (void)pArg;
        if (pHit->mLiveHits == 0)
            bAll = true;
    }
    (void)bAll;
}

// ============================================================================
// @ 0x00cba560  SP::cSPSpaceToolData::DoAreaEffectSpellHit
// The dev PDB names this SP::cSPSpaceToolData::DoAreaEffectSpellHit.  It fills an
// object list from the tool manager, applies a spell hit to every object that
// yields the 0x013f94d4 interface (skipping the two owner objects), then applies
// the same hit to the owner itself.  The original takes its first two arguments in
// registers (eax/edi) -- a register ABI no scalar declaration reproduces -- so the
// body below is the behavioural equivalent.
// ============================================================================
void __cdecl FUN_00cba560(void* pTool, void* pOwner1, int pOwner2, int arg3, float f1, float f2,
                          int arg6, int arg7)
{
    cSPObjectList vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;

    Obj* pManager = (Obj*)SP_ToolManager();
    ((Fn_v_pf)VTSLOT(pManager, 0x48))(pManager, f1);   // fill the hit list

    int n = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < n; ++i) {
        Obj* p = vec.mpBegin[i];
        if (!p)
            continue;
        void* pHit = ((Fn_p_pi)VTSLOT(p, 0xb8))(p, (int)&DAT_013f94d4);
        if (!pHit)
            continue;
        // pTool+0x220 interface identity, pOwner, and pOwner2 all skip
        if (pHit == (void*)arg6 || pHit == pOwner1)
            continue;
        // cSPSpaceToolData::DoAreaEffectHit 0x00cb59b0
        ((void (__thiscall*)(void*, int, int, void*, void*, void*, int, float, float))
         0x00cb59b0)(pTool, 0, 0, pHit, pOwner1, (void*)arg6, arg3, f2, f1);
    }
    if (pOwner1) {
        ((void (__thiscall*)(void*, int, int, void*, void*, void*, int, float, float))
         0x00cb59b0)(pTool, 0, 0, pOwner1, (void*)pOwner2, (void*)arg6, arg3, f2, f1);
    }
    // the eastl vector local is released by the caller's tail (operator delete[])
}

// ============================================================================
// @ 0x00cba690  SP::cCulturalProjectile::Explode
// Plays the cultural explosion effect when the projectile is flagged to explode and
// not spinning; then, when it has a locomotion and a tool, computes the damage
// radius, applies the area hit, drives the relationship/fame bookkeeping, and
// occasionally spawns the secondary effect.
// ============================================================================
void SP::cCulturalProjectile::Explode()
{
    // --- 0x00cba69a: effect (only when mbFlag538 && !mbSpin539) --------------
    if (mbFlag538 && !mbSpin539) {
        Obj* pFx = (Obj*)SP_EffectsManagerPtr();
        void* pEffect = ((Fn_p_pi)VTSLOT(pFx, 0x54))(pFx, 0x3701a5c);
        void* pOut = 0;
        bool ok = ((bool (__thiscall*)(void*, int, int, void**))VTSLOT(pEffect, 0x08))(
            pEffect, 0xf88730e6, 0, &pOut);
        if (ok) {
            struct XformMsg { int mData[16]; };
            XformMsg msg;
            Vector3 pos = *mLoco.m_position();
            msg.mData[1] = 0; // (offset slot filled by SetOffset below)
            ((void (__thiscall*)(void*, Vector3*))0x00571d40)(&msg, &pos);
            Vector3* pFacing = mLoco.m_facing();
            Matrix3Rows rot;
            Matrix3FromFacingAndUp(&rot, pFacing, pFacing);
            (void)rot;
            // XformMsg::operator= through the message receiver
            ((Fn_v_pp)VTSLOT(pEffect, 0x18))(pEffect, &msg);

            uint32_t owner = mOwner;
            Obj* pNoun = (Obj*)((void* (__cdecl*)(uint32_t))0x00b3d300)(owner);
            cHitObject* pHit = 0;
            if (pNoun)
                pHit = (cHitObject*)pNoun->m_b25f40(pNoun);
            if (pHit) {
                Vector3 tp = pHit->mPosition;
                ((Fn_v_pi)VTSLOT(pOut, 0x44))(pOut, 3);
                (void)tp;
            }
            ((Fn_v_pi)VTSLOT(pEffect, 0x08))(pEffect, 0);
        }
    }

    // --- 0x00cba7ea: main branch needs a locomotion and a tool ----------------
    if (!mpVehicle || !mpTool)
        return;

    int aimIndex;
    {
        cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
        // the +0x508 guidance sub-block slot 0x3c: path exhausted?
        bool bDone = ((bool (__thiscall*)(void*))VTSLOT(&pLoco->mBlock508, 0x3c))(&pLoco->mBlock508);
        if (bDone)
            aimIndex = -1;
        else
            aimIndex = (int)((Fn_p_p)VTSLOT(mpVehicle, 0x4c))(mpVehicle);
    }

    void* pToolKey = 0;
    if (mpTarget)
        pToolKey = ((Fn_p_p)VTSLOT(mpTarget, 0x0c))(mpTarget);
    cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
    float radius = (pLoco->mRadius + DAT_01471064) * DAT_013eeda0;

    float damage = ((cSPSpaceToolData*)mpTool)->GetDamageRadius(radius, radius, 3, aimIndex,
                                                               (int)pToolKey, 0);

    // 0x00cba8cb FUN_00cba560(tool, owner object, ...)
    FUN_00cba560(mpTool, 0, 0, 0, damage, radius, 0, 0);

    void* pTimerOwner = mpTarget;
    if (pTimerOwner) {
        void* pTimerKey = ((Fn_p_p)VTSLOT(pTimerOwner, 0x10))(pTimerOwner);
        ((void (__thiscall*)(void*, void*))0x00bfddc0)(
            &((cCulturalLocomotion*)mpVehicle)->mBlock508, pTimerKey);
    }
    void* pSelfId = 0;
    if (mpTarget)
        pSelfId = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, 0x3d5c477);
    void* pBuilding = 0;
    if (mpTarget)
        pBuilding = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, (int)0xe9cb8ba);
    void* pTurret = 0;
    if (mpTarget)
        pTurret = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, 0x436f315);
    void* pAnimal = 0;
    if (mpTarget)
        pAnimal = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, (int)0xd0036e08);

    // relationship bookkeeping (0x00cba952..0x00cba9c3)
    void* pOther = (void*)0;
    if (pTurret) pOther = pTurret;
    else if (pBuilding) pOther = pBuilding;
    else if (pSelfId) pOther = pSelfId;
    else if (pAnimal) pOther = pAnimal;
    if (pOther) {
        if ((void*)((Fn_p_p)VTSLOT(pOther, 0x4c))(pOther) !=
            (void*)((Fn_p_p)VTSLOT(this, 0x4c))(this)) {
            ((Fn_v_p)VTSLOT(pOther, 0x4c))(pOther);
            Obj* pRel = (Obj*)SP_RelationshipManager();
            ((void (__thiscall*)(void*, float))0x00d06270)(pRel, 1.0f);
            Obj* pNoun = (Obj*)SP_NounManager();
            if ((int)((Fn_p_p)VTSLOT(this, 0x4c))(this) == GetPlayerEmpireOrMinus1()) {
                if (RandomUint32Uniform(10) == 0) {
                    // 0x00cba9dd secondary effect / fame branch
                    Obj* pTool2 = (Obj*)((void* (*)(void*))0x00cb4650)(&mpVehicle);
                    int cnt = ((int (__thiscall*)(void*))0x00ca0380)(mpVehicle);
                    if (pTool2 && ((bool (__thiscall*)(void*))VTSLOT(&mLoco, 0x48))(&mLoco)) {
                        cSPTimer* pTimer = &mTimer;
                        if (pTimer->IsRunning()) {
                            uint64_t el = pTimer->GetElapsedTime();
                            uint64_t limit = (uint64_t)(uint32_t)(cnt * 5000);
                            if (el < limit)
                                return;
                        }
                        (void)pTool2;
                        ((void (__thiscall*)(void*))0x00bc3130)(pTimer);   // Restart
                    }
                }
            }
        }
    } else {
        // 0x00cbaba7: no target object -- use the locomotion path
        if (mpVehicle) {
            cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
            Vector3* pPts = pLoco->mPath.mpBegin;
            int cnt = (int)(pLoco->mPath.mpEnd - pLoco->mPath.mpBegin);
            if (cnt / (int)sizeof(Vector3) > 1) {
                int idx = cnt / (int)sizeof(Vector3);
                Vector3 a = pPts[idx];
                Vector3 b = pPts[idx - 2];
                Vector3 d;
                d.x = a.x - b.x; d.y = a.y - b.y; d.z = a.z - b.z;
                Vector3 n;
                SP_NormalizedSafe(&n, &d);
                Obj* pToolMan = (Obj*)SP_ToolManager();
                ((void (__thiscall*)(void*, int, Vector3*, Vector3*))VTSLOT(pToolMan, 0x60))(
                    pToolMan, 0x65baa81, &a, &n);
            }
        }
    }
}

// ============================================================================
// @ 0x00cbac80  SP::cResourceProjectile::Update
// ============================================================================
bool SP::cResourceProjectile::Update()
{
    cSPTimer* pTimer = &mTimer;

    uint64_t e = pTimer->GetElapsedTime();
    if (e != 0) {
        uint64_t e2 = pTimer->GetElapsedTime();
        if (e2 > 1000u)
            return false;
    } else {
        Obj* loco = (Obj*)((char*)this - 0x4d0);
        Vector3* p = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
        float dx = mEndPoint.x - p->x;
        float dy = mEndPoint.y - p->y;
        float dz = mEndPoint.z - p->z;
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) < DAT_01470f1c) {
            pTimer->Start();
            ((cProjectileBase*)((char*)this - 0x504))->ExplodeResource();
        }
    }
    return true;
}

// ============================================================================
// @ 0x00cbad00  SP::cICBM::Update
// ============================================================================
bool SP::cICBM::Update()
{
    Obj* loco = (Obj*)((char*)this - 0x4d0);

    Obj* pGuide = (Obj*)((Fn_p_p)VTSLOT(mpGuidance_1c, 0x08))(mpGuidance_1c);
    Vector3* pa = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
    Vector3* pb = (Vector3*)((Fn_p_p)VTSLOT(pGuide, 0x2c))(pGuide);

    float dx = pb->x - pa->x;
    float dy = pb->y - pa->y;
    float dz = pb->z - pa->z;
    float dist = sqrtf(dx * dx + (dy * dy + dz * dz));
    if (dist < DAT_01486110) {
        ((cProjectileBase*)((char*)this - 0x504))->ExplodeICBM();
        return false;
    }
    Vector3* p2 = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
    Obj* planet = (Obj*)SP_PlanetModel(p2);
    if (!planet->m_b81f90(p2))
        return true;
    ((cProjectileBase*)((char*)this - 0x504))->ExplodeICBM();
    return false;
}

// ============================================================================
// @ 0x00cbad90  FUN_00cbad90 -- write a property list to a stream
// ============================================================================
struct PropertyList {
    void*    mpNode0;                        // +0x00
    uint32_t m4;                             // +0x04  end sentinel marker
    void*    mpRoot;                         // +0x08
    uint32_t m0c[2];
    int      mCount;                         // +0x14
};

void __cdecl FUN_00cbad90(Obj* pStream, PropertyList* pList)
{
    PropertyList* pListArg = pList;
    int count = pListArg->mCount;
    void* pWriter = ((Fn_p_p)VTSLOT(pStream, 0x20))(pStream);
    void* pOut = ((Fn_p_p)VTSLOT(pWriter, 0x18))(pWriter);

    EA_IO_WriteUint32((int)pOut, &count, 1, 0);

    void** pSentinel = (void**)((char*)pListArg + 4);
    for (void* it = pListArg->mpRoot; it != pSentinel;
         it = eastl_RBTreeIncrement(it)) {
        int v = 0;
        void* p = *(void**)((char*)it + 0x10);
        if (p)
            v = (int)((Fn_p_pi)VTSLOT(p, 0xb8))(p, 0x179c807);
        ((Fn_v_pi)VTSLOT(pStream, 0x2c))(pStream, v);
        ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
    }
    ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
}

// ============================================================================
// @ 0x00cbaf00  Simulator::cPathFollowingLocomotion::cPathFollowingLocomotion
// ============================================================================
namespace Simulator {

struct cPathFollowingLocomotion {
    void*    mpVftable0;                     // +0x00
    uint32_t mRefCount;                      // +0x04
    void*    mpVftable8;                     // +0x08
    uint32_t mField0c;                       // +0x0c
    Vector3Vector mPath;                     // +0x10
    int      m20;                            // +0x20
    int      mDistanceFromLastPoint;         // +0x24
    float    mCurrentSegmentLength;          // +0x28
    float    mLastPointReached;              // +0x2c
    int      m30;                            // +0x30
    Vector3  mToNextPoint;                   // +0x34
    int      m40;                            // +0x40
    float    mLowestAltitude;                // +0x44
    float    mLastSpeed;                     // +0x48
    uint32_t m4c;                            // +0x4c

    cPathFollowingLocomotion(const Vector3Vector& points, int motionID);
    void PathUpdated();                      // 0x00cb4a70
};

// eastl::vector<cSPVector3, sp_vector_allocator>::vector(const vector&) at 0x00473460;
// declared as Vector3Vector's copy constructor above so its `this` lands in ecx.

}  // namespace Simulator

Simulator::cPathFollowingLocomotion::cPathFollowingLocomotion(const Vector3Vector& points,
                                                             int motionID)
{
    mpVftable8 = (void*)0x13ec458;
    mField0c = 0;
    mpVftable0 = (void*)0x1475500;
    mpVftable8 = (void*)0x14754f0;

    mPath.CopyFrom(points);

    mCurrentSegmentLength = 0.0f;
    m30 = 0;
    m40 = motionID;
    mLowestAltitude = 0.0f;
    mLastSpeed = DAT_0147515c;
    m4c = 0;

    if (mPath.mpBegin != mPath.mpEnd) {
        int n = (int)(mPath.mpEnd - mPath.mpBegin) - 1;
        mDistanceFromLastPoint = n;
        if (n != 0) {
            Vector3* p = mPath.mpBegin;
            float dx = p[1].x - p[0].x;
            float dy = p[1].y - p[0].y;
            float dz = p[1].z - p[0].z;
            mToNextPoint.x = dx;
            mToNextPoint.y = dy;
            mToNextPoint.z = dz;
            float len = sqrtf(dx * dx + dy * dy + dz * dz);
            mLastPointReached = len;
            float inv = 1.0f / len;
            mToNextPoint.x *= inv;
            mToNextPoint.y *= inv;
            mToNextPoint.z *= inv;
        }
        PathUpdated();
    }
}
