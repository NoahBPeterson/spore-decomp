// Slice s00cb7e50 -- homing / orbiting steering update (a projectile-like locomotive steered towards
// a target that moves on a sphere around the origin; flags /O2 /MD /Gy /TP /arch:SSE /fp:fast).
//
//   0x00cb7e50  Steering::Update(StepArgs*)
//
// Summary: velocity is read from the locomotive. When a target is set and the retarget timer has run for
// at least 1500 ms, the desired direction is built as follows:
//   * tangent direction at the locomotive position towards the target (cross products against the radial
//     direction), pushed out by mRadius and re-projected onto the target's sphere of radius |targetPos|;
//   * when the target is 40..300 units away a spiral wobble is added: rotate the lateral axis about the
//     desired direction by half of mWobbleAngle (quaternion), mix it in at 0.5 and renormalize; advance
//     mWobbleAngle by dt * mWobbleRate (wrapped by 2pi);
//   * the heading is then rotated from the current forward towards the desired direction by at most
//     dt * mWobbleRate / angle (clamped to 1).
// Otherwise the current velocity is kept. In both cases the new velocity (speed * heading) is stored in
// the args and the locomotive orientation is set from QuaternionFromDirections(kForward, heading).
#include "types.h"

#include <intrin.h>
#include <math.h>

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ---- external helpers (cdecl) -----------------------------------------------------------
Vector3*    Vec3Normalize(Vector3* out, const Vector3* in);                           // 0x00436ce0
Vector3*    QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Vector3*    RotateTowards(Vector3* out, const Vector3* from, const Vector3* to, float t); // 0x00b0fd00
Quaternion* QuaternionFromDirections(Quaternion* out, const Vector3* from, const Vector3* to); // 0x00698180

extern const Vector3 kForward;     // 0x0169a9e8
extern const float   kTwoPi;       // 0x0169aa28

// maxss / minss semantics (the second operand wins when either is NaN)
inline float MaxSS(float a, float b) { return (a > b) ? a : b; }
inline float MinSS(float a, float b) { return (a < b) ? a : b; }

struct cSpatial {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();                      // +0x2c
};

struct cLocomotive : cSpatial {
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual void SetOrientation(const Quaternion* q);                       // +0x3c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void GetForward(Vector3* out);                                  // +0x5c
    const Vector3& GetVelocity();                                           // 0x00d20610
};

struct cSPTimer { uint32_t data[8]; uint64_t GetElapsedTime(); };           // 0x00bc3190

struct StepArgs {
    Vector3      mVelocity;    // +0x00 out
    uint32_t     pad0c;
    float        mDt;          // +0x10
    cLocomotive* mpLoco;       // +0x14
};

inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct Steering {
    uint32_t pad00[4];
    float    mRadius;          // +0x10
    float    mWobbleRate;      // +0x14
    cSpatial* mpTarget;        // +0x18
    uint32_t pad1c;
    cSPTimer mTimer;           // +0x20
    float    mWobbleAngle;     // +0x40

    void Update(StepArgs* args);   // 0x00cb7e50
};

// @ 0x00cb7e50
void Steering::Update(StepArgs* args)
{
    Vector3 vel = args->mpLoco->GetVelocity();
    Vector3 heading;

    uint64_t elapsed;
    if (mpTarget != 0 && ((elapsed = mTimer.GetElapsedTime()) > 0x5db)) {
        Vector3 pos = *args->mpLoco->GetPosition();
        Vector3 fwd;
        args->mpLoco->GetForward(&fwd);

        const Vector3* tp = mpTarget->GetPosition();
        Vector3 d;
        d.x = tp->x - pos.x;
        d.y = tp->y - pos.y;
        d.z = tp->z - pos.z;
        float dInv = 1.0f / sqrtf(d.z * d.z + (d.x * d.x + d.y * d.y));
        d.x *= dInv; d.y *= dInv; d.z *= dInv;
        float pInv = 1.0f / sqrtf(pos.x * pos.x + (pos.y * pos.y + pos.z * pos.z));
        Vector3 pn;
        pn.x = pInv * pos.x; pn.y = pos.y * pInv; pn.z = pos.z * pInv;

        // c = pn x d ; tangent = c x pn
        Vector3 c;
        c.x = pn.z * d.y - pn.y * d.z;
        c.y = d.z * pn.x - pn.z * d.x;
        c.z = pn.y * d.x - d.y * pn.x;
        Vector3 t;
        t.x = mRadius * (c.z * pn.y - c.y * pn.z) + pos.x;
        t.y = (pn.z * c.x - c.z * pn.x) * mRadius + pos.y;
        t.z = (c.y * pn.x - pn.y * c.x) * mRadius + pos.z;
        float tInv = 1.0f / sqrtf(t.y * t.y + (t.z * t.z + t.x * t.x));
        t.x *= tInv; t.y *= tInv; t.z *= tInv;

        const Vector3* tp2 = mpTarget->GetPosition();
        float radius = sqrtf((tp2->x * tp2->x + tp2->y * tp2->y) + tp2->z * tp2->z);
        Vector3 w;
        w.x = t.x * radius - pos.x;
        w.y = t.y * radius - pos.y;
        w.z = t.z * radius - pos.z;
        float wInv = 1.0f / sqrtf(w.z * w.z + (w.y * w.y + w.x * w.x));
        Vector3 dir;
        dir.x = wInv * w.x; dir.y = w.y * wInv; dir.z = w.z * wInv;
        Vector3 axis = dir;

        const Vector3* tp3 = mpTarget->GetPosition();
        float dist = sqrtf((tp3->y - pos.y) * (tp3->y - pos.y) +
                           ((tp3->z - pos.z) * (tp3->z - pos.z) + (tp3->x - pos.x) * (tp3->x - pos.x)));
        if (40.0f < dist && dist < 300.0f) {
            Vector3 tmp0, tmp1, tmp2;
            const Vector3* n1 = Vec3Normalize(&tmp0, &pos);
            const Vector3* n2 = Vec3Normalize(&tmp1, &dir);
            axis.x = n1->z * n2->y - n1->y * n2->z;
            axis.z = n2->x * n1->y - n1->x * n2->y;
            float angle = mWobbleAngle;
            float half = angle * 0.5f;
            float s = (float)sin(half);
            axis.y = n1->x * n2->z - n2->x * n1->z;
            Quaternion q;
            float c2 = (float)cos(half);
            q.x = s * t.x; q.y = t.y * s; q.z = t.z * s;
            q.w = c2;
            const Vector3* r = QuaternionRotate(&tmp2, &axis, &q);
            Vector3 mix;
            mix.x = r->x * 0.5f + t.x;
            mix.y = r->y * 0.5f + t.y;
            mix.z = r->z * 0.5f + t.z;
            const Vector3* nm = Vec3Normalize(&tmp2, &mix);
            dir.x = nm->x; dir.y = nm->y; dir.z = nm->z;
            float na = args->mDt * mWobbleRate + angle;
            mWobbleAngle = na;
            if (na > kTwoPi) mWobbleAngle = na - kTwoPi;
        }

        float cs = fwd.x * dir.x + fwd.y * dir.y + fwd.z * dir.z;
        cs = MinSS(MaxSS(cs, -1.0f), 1.0f);
        float ang = (float)acos(cs);
        float step = 1.0f;
        if (ang > 0.0f) {
            float f = (args->mDt * mWobbleRate) / ang;
            step = MinSS(1.0f, f);
        }
        Vector3 out;
        RotateTowards(&out, &fwd, &dir, step);
        args->mVelocity.x = mRadius * out.x;
        args->mVelocity.y = mRadius * out.y;
        args->mVelocity.z = mRadius * out.z;
        Quaternion qo;
        cLocomotive* loco = args->mpLoco;
        loco->SetOrientation(QuaternionFromDirections(&qo, &kForward, &out));
        return;
    }
    args->mVelocity = vel;
    Quaternion qo;
    cLocomotive* loco = args->mpLoco;
    loco->SetOrientation(QuaternionFromDirections(&qo, &kForward, &vel));
}

// ===========================================================================
// Simulator projectile family, 0x00cb84b0..0x00cb9170
//
// Every class below is laid out exactly as the original stores touch it: the
// vtable pointers of the base subobjects sit at +0x000, +0x034, +0x108, +0x504
// and +0x518 (the missile/cultural/resource group) or +0x000, +0x034, +0x108
// and +0x11c (the beam/AoE group); everything in between is padding.  The base
// constructors/destructors are out-of-line functions called with `this` in ecx.
// ===========================================================================
#include <xmmintrin.h>

struct Vtbl {
    void* mSlots[0xc8];
};

typedef void  (__thiscall *VfnV)(void*);
typedef void* (__thiscall *VfnP)(void*);
typedef void* (__thiscall *VfnPU)(void*, unsigned int);
typedef float (__thiscall *VfnF0)(void*);
typedef int   (__thiscall *VfnIF)(void*, float);

// Byte offsets (in vtable slots) of the virtual functions called below.
enum {
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0c / 4,
    kVt2C = 0x2c / 4, kVt34 = 0x34 / 4, kVt60 = 0x60 / 4, kVt64 = 0x64 / 4,
    kVtC0 = 0xc0 / 4
};

// vtables of this binary (only their addresses are stored here; chk masks them)
extern Vtbl gVtbl013eb938;  // ??_7ITracerBase@Trace@EA@@6B@
extern Vtbl gVtbl013ec458;  // vtbl_cContentValidationSummarizer
extern Vtbl gVtbl0145dca8;  // PTR_FUN_0145dca8 (cIProjectile common)
extern Vtbl gVtbl014751b4;  // Simulator::cDefaultAoEArea
extern Vtbl gVtbl014751e0;  // Simulator::cDefaultAoEArea +0x34
extern Vtbl gVtbl014752a4;  // Simulator::cDefaultAoEArea +0x04
extern Vtbl gVtbl014752b8;  // Simulator::cDefaultAoEArea +0x00
extern Vtbl gVtbl01475738;  // Simulator::cSpaceDefenseMissile +0x518
extern Vtbl gVtbl014757a0;  // Simulator::cSpaceDefenseMissile +0x504
extern Vtbl gVtbl014757c8;  // Simulator::cSpaceDefenseMissile +0x108
extern Vtbl gVtbl014757d0;  // Simulator::cSpaceDefenseMissile +0x034
extern Vtbl gVtbl014758cc;  // Simulator::cSpaceDefenseMissile +0x004
extern Vtbl gVtbl014758e0;  // Simulator::cSpaceDefenseMissile +0x000
extern Vtbl gVtbl01475990;  // Simulator::cDefaultBeamProjectile +0x11c
extern Vtbl gVtbl014759ac;  // Simulator::cDefaultBeamProjectile +0x108
extern Vtbl gVtbl014759d8;  // Simulator::cDefaultBeamProjectile +0x034
extern Vtbl gVtbl01475a9c;  // Simulator::cDefaultBeamProjectile +0x004
extern Vtbl gVtbl01475ab0;  // Simulator::cDefaultBeamProjectile +0x000
extern Vtbl gVtbl01475b38;  // Simulator::cCulturalProjectile +0x504
extern Vtbl gVtbl01475b60;  // Simulator::cCulturalProjectile +0x108
extern Vtbl gVtbl01475b68;  // Simulator::cCulturalProjectile +0x004
extern Vtbl gVtbl01475b78;  // Simulator::cCulturalProjectile +0x000
extern Vtbl gVtbl01475bd0;  // Simulator::cCulturalProjectile +0x034
extern Vtbl gVtbl01475cf4;  // Simulator::cResourceProjectile +0x504
extern Vtbl gVtbl01475d1c;  // Simulator::cResourceProjectile +0x108
extern Vtbl gVtbl01475d28;  // Simulator::cResourceProjectile +0x034
extern Vtbl gVtbl01475e24;  // Simulator::cResourceProjectile +0x004
extern Vtbl gVtbl01475e38;  // Simulator::cResourceProjectile +0x000

// constants read by the constructors / setters
extern const float g01477fbc;   // 200.0f  (mMaxBeamLength)
extern const float g01485720;   // 1.0f
extern const float g0157d350;   // locomotion speed scale
extern const float g0157d364;   // beam turn rate base
extern const float g013eeda0;   // 8.0f
extern const float g0169a414;   // AoE source offset x
extern const float g0169a418;   // AoE source offset y
extern const float g0169a41c;   // AoE source offset z
extern const float g0169a410;   // effect argument
extern const float g0147515c;   // effect argument

extern "C" void  __cdecl operator_delete(void* p);                                        // 0x00f47380
extern "C" void* __cdecl operator_new(unsigned int size, const char* name,
                                      int a, int b, int c, int d);                        // 0x00f473a0
extern "C" int   __cdecl cSPLivingUniverse_GetUniverseContext();                           // 0x01021080

// ---------------------------------------------------------------------------
// shared sub-objects
// ---------------------------------------------------------------------------
class cGonzagoTimer {
public:
    uint32_t mPad00[8];            // +0x00..+0x1f
    void Construct();              // 0x00b63890
    void Destroy();                // 0x00b638b0
    void Restart();                // 0x00bc3130
};

class IVtblObject {
public:
    Vtbl* mpVtbl;                  // +0x00
};

class cSPSpaceToolData {
public:
    Vtbl* mpVtbl;                  // +0x00
    float FUN_00c41d40(int v);     // 0x00c41d40
    float FUN_0104be50(float v);   // 0x0104be50
};

class cInteractableObject : public IVtblObject {
public:
    void SetEffectId(int id);              // 0x00c3f160
    void FUN_00c3f1b0(float a, float b);   // 0x00c3f1b0
    void FUN_00c3f2d0(void* owner);        // 0x00c3f2d0
};

class cGameNounManager {
public:
    IVtblObject* CreateNoun(uint32_t nameHash);   // 0x00b20c60
};

extern "C" cGameNounManager* __cdecl NounManager();    // 0x00b3d300

class cSpaceDefenseMissileLocomotion {
public:
    uint32_t mPad00[0x12];                                  // +0x00..+0x47 (size 0x48)
    cSpaceDefenseMissileLocomotion* Construct(float a, float b, int v);   // 0x00cb54a0
};

// base body of SP::cGameData at +0x000 (two vtable pointers, then its fields)
class cGameDataBase {
public:
    Vtbl* mpVtbl00;                // +0x000
    Vtbl* mpVtbl04;                // +0x004
    uint32_t mPad08[11];           // +0x008..+0x033
    void Construct();              // 0x00b18660
    void Destroy();                // 0x00b184c0
};

// base body of SP::cLocomotiveObject at +0x034 (extends to +0x108)
class cLocomotiveBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x034)
    uint32_t mPad04[52];           // +0x004..+0xd3
    void Construct();              // 0x00c43860
    void Destroy();                // 0x00c432e0
    void FUN_00c421b0(void* locomotion);   // 0x00c421b0
};

// base body of SP::cSpatialObject at +0x034 (the beam / AoE group)
class cSpatialBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x034)
    uint32_t mPad04[52];           // +0x004..+0xd3
    void Construct();              // 0x00c89630
    void Destroy();                // 0x00c8a420
};

// the +0x108 base body of the missile / cultural / resource group
class cProjSuperBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x108)
    uint32_t mPad04[60];           // +0x004..+0x0f3
    float mTargetPosX;             // +0x0f4 (+0x1fc)
    float mTargetPosY;             // +0x0f8 (+0x200)
    float mTargetPosZ;             // +0x0fc (+0x204)
    uint32_t mPad100[7];           // +0x100..+0x11b
    uint32_t mMode;                // +0x11c (+0x224)
    uint32_t mPad120[30];          // +0x120..+0x197
    float mField198;               // +0x198 (+0x2a0)
    uint32_t mPad19c[152];         // +0x19c..+0x3fb
};

// the SP::cIProjectile base body at +0x504 / +0x108; its constructor writes the
// common vtable and clears the three offsets plus the triggered flag
class cProjectileBody {
public:
    Vtbl* volatile mpVtbl;         // +0x000
    float mTargetOffsetX;          // +0x004
    float mTargetOffsetY;          // +0x008
    float mTargetOffsetZ;          // +0x00c
    uint8_t mActionTriggered;      // +0x010
    uint8_t mPad11[3];             // +0x011..+0x013
};

// the common cIProjectile constructor body, inlined by every projectile ctor
inline void InitProjectileBody(cProjectileBody& body, uint32_t zero)
{
    __m128 z = _mm_setzero_ps();
    _ReadWriteBarrier();
    body.mpVtbl = &gVtbl0145dca8;
    _mm_store_ss(&body.mTargetOffsetX, z);
    _mm_store_ss(&body.mTargetOffsetY, z);
    _mm_store_ss(&body.mTargetOffsetZ, z);
    body.mActionTriggered = (uint8_t)zero;
}

class cCombatantBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x518)
    uint32_t mPad04[49];           // +0x004..+0xc7
    void Construct();              // 0x00bfd4e0
    void Destroy();                // 0x00bfcd00
};

class cInteractionBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x11c)
    uint32_t mPad04[5];            // +0x004..+0x017
    void Construct();              // 0x00ac03d0
    void Destroy();                // 0x00ac0520
};

inline void StoreZero3(float& a, float& b, float& c)
{
    __m128 z = _mm_setzero_ps();
    _mm_store_ss(&a, z);
    _mm_store_ss(&b, z);
    _mm_store_ss(&c, z);
}

// ---------------------------------------------------------------------------
// SP::cSpaceDefenseMissile
// ---------------------------------------------------------------------------
class cSpaceDefenseMissile {
public:
    cGameDataBase     mBase;           // +0x000
    cLocomotiveBody   mLoco;           // +0x034
    cProjSuperBody    mProjSuper;      // +0x108
    cProjectileBody   mProj;           // +0x504
    cCombatantBody    mCombatant;      // +0x518
    cSPSpaceToolData* mpTool;          // +0x5e0
    IVtblObject*      mpTarget;        // +0x5e4
    cGonzagoTimer     mLifeTimer;      // +0x5e8
    cInteractableObject* mpHitSphere;  // +0x608
    uint32_t          mPad60c;         // +0x60c

    void* FUN_00cb84f0();                                      // ctor
    void FUN_00cb86a0();                                       // dtor
    void FUN_00cb8760(const Vector3* pos, IVtblObject* target);
};

// @ 0x00cb84f0  Simulator::cSpaceDefenseMissile::cSpaceDefenseMissile
void* cSpaceDefenseMissile::FUN_00cb84f0()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mCombatant.Construct();
    mBase.mpVtbl00 = &gVtbl014758e0;
    mBase.mpVtbl04 = &gVtbl014758cc;
    mLoco.mpVtbl = &gVtbl014757d0;
    mProjSuper.mpVtbl = &gVtbl014757c8;
    mProj.mpVtbl = &gVtbl014757a0;
    mCombatant.mpVtbl = &gVtbl01475738;
    mpTool = (cSPSpaceToolData*)zero;
    mpTarget = (IVtblObject*)zero;
    mLifeTimer.Construct();
    mpHitSphere = (cInteractableObject*)zero;
    return this;
}

// @ 0x00cb86a0  Simulator::cSpaceDefenseMissile::~cSpaceDefenseMissile
void cSpaceDefenseMissile::FUN_00cb86a0()
{
    if (mpHitSphere)
        ((VfnV)mpHitSphere->mpVtbl->mSlots[kVt04])(mpHitSphere);
    mLifeTimer.Destroy();
    if (mpTarget)
        ((VfnV)mpTarget->mpVtbl->mSlots[kVt64])(mpTarget);
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    mCombatant.Destroy();
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
}

// @ 0x00cb8760  Simulator::cSpaceDefenseMissile::SetTarget -- new target + locomotion
void cSpaceDefenseMissile::FUN_00cb8760(const Vector3* pos, IVtblObject* target)
{
    IVtblObject* old = mpTarget;
    if (target != old) {
        if (target)
            ((VfnV)target->mpVtbl->mSlots[kVt60])(target);
        mpTarget = target;
        if (old)
            ((VfnV)old->mpVtbl->mSlots[kVt64])(old);
    }
    mProjSuper.mMode = 4;
    cSpaceDefenseMissileLocomotion* locomotion = 0;
    void* mem = operator_new(0x48, "Simulator/cSpaceDefenseMissileLocomotion", 0, 0, 0, 0);
    if (mem) {
        int v = (int)((VfnP)target->mpVtbl->mSlots[kVt08])(target);
        cSPSpaceToolData* tool = mpTool;
        float speed = tool->FUN_00c41d40(v);
        float turn = tool->FUN_0104be50(speed);
        locomotion = ((cSpaceDefenseMissileLocomotion*)mem)->Construct(turn, speed, v);
    }
    mLoco.FUN_00c421b0(locomotion);
    mProjSuper.mTargetPosX = pos->x;
    mProjSuper.mTargetPosY = pos->y;
    mProjSuper.mTargetPosZ = pos->z;
    mLifeTimer.Restart();
    if (cSPLivingUniverse_GetUniverseContext() == 0) {
        cGameNounManager* manager = NounManager();
        IVtblObject* hitSphere = manager->CreateNoun(0x2e72cae);
        if (hitSphere)
            hitSphere = (IVtblObject*)((VfnPU)hitSphere->mpVtbl->mSlots[kVt0C])(hitSphere, 0x2e71a5a);
        IVtblObject* prev = mpHitSphere;
        if (hitSphere != prev) {
            if (hitSphere)
                ((VfnV)hitSphere->mpVtbl->mSlots[kVt00])(hitSphere);
            mpHitSphere = (cInteractableObject*)hitSphere;
            if (prev)
                ((VfnV)prev->mpVtbl->mSlots[kVt04])(prev);
        }
        float turnRate = ((VfnF0)mLoco.mpVtbl->mSlots[kVt34])(&mLoco) * g0157d350;
        int effect = ((VfnIF)mLoco.mpVtbl->mSlots[kVt2C])(&mLoco, turnRate);
        mpHitSphere->SetEffectId(effect);
        mpHitSphere->FUN_00c3f1b0(g0169a410, g0147515c);
        mpHitSphere->FUN_00c3f2d0(this);
    }
}

// ---------------------------------------------------------------------------
// SP::cDefaultBeamProjectile
// ---------------------------------------------------------------------------
class cDefaultBeamProjectile {
public:
    cGameDataBase       mBase;                // +0x000
    cSpatialBody        mSpatial;             // +0x034
    cProjectileBody     mProj;                // +0x108
    cInteractionBody    mInteraction;         // +0x11c
    cSPSpaceToolData*   mpTool;               // +0x134
    IVtblObject*        mpSource;             // +0x138
    float               mTargetPositionX;     // +0x13c
    float               mTargetPositionY;     // +0x140
    float               mTargetPositionZ;     // +0x144
    float               mHitPositionX;        // +0x148
    float               mHitPositionY;        // +0x14c
    float               mHitPositionZ;        // +0x150
    uint8_t             mActionTriggered;     // +0x154
    uint8_t             mbStopBeam;           // +0x155
    uint8_t             mPad156[2];           // +0x156..+0x157
    float               mMaxBeamLength;       // +0x158
    float               mProjectileScale;     // +0x15c
    float               mBeamDirectionX;      // +0x160
    float               mBeamDirectionY;      // +0x164
    float               mBeamDirectionZ;      // +0x168
    uint8_t             mbHittingGround;      // +0x16c
    uint8_t             mbHittingWater;       // +0x16d
    uint8_t             mOrientsToTerrain;    // +0x16e
    uint8_t             mbPassesThroughToTerrain;  // +0x16f
    float               mDamageRadius;        // +0x170
    float               mBeamTurnRate;        // +0x174
    uint32_t            mMsPerDamagePointLo;  // +0x178
    uint32_t            mMsPerDamagePointHi;  // +0x17c
    uint32_t            mPad180[16];          // +0x180..+0x1bf
    cGonzagoTimer       mLifeTimer;           // +0x1c0
    IVtblObject*        mTargetedCombatant;   // +0x1e0
    Vector3*            mPathBegin;           // +0x1e4
    Vector3*            mPathEnd;             // +0x1e8
    Vector3*            mPathCapacity;        // +0x1ec

    void* FUN_00cb88e0();                                    // ctor
    void FUN_00cb8b20();                                     // dtor
    void FUN_00cb8ba0(Vector3* start, Vector3* end);         // GetEndPoints
};

// @ 0x00cb88e0  Simulator::cDefaultBeamProjectile::cDefaultBeamProjectile
void* cDefaultBeamProjectile::FUN_00cb88e0()
{
    mBase.Construct();
    mSpatial.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mInteraction.Construct();
    mBase.mpVtbl00 = &gVtbl01475ab0;
    mBase.mpVtbl04 = &gVtbl01475a9c;
    mSpatial.mpVtbl = &gVtbl014759d8;
    mProj.mpVtbl = &gVtbl014759ac;
    mInteraction.mpVtbl = &gVtbl01475990;
    mpTool = (cSPSpaceToolData*)zero;
    mpSource = (IVtblObject*)zero;
    mMaxBeamLength = g01477fbc;
    mProjectileScale = g01485720;
    mDamageRadius = g01485720;
    mActionTriggered = (uint8_t)zero;
    mbStopBeam = (uint8_t)zero;
    mbHittingGround = (uint8_t)zero;
    mbHittingWater = (uint8_t)zero;
    mOrientsToTerrain = (uint8_t)zero;
    mbPassesThroughToTerrain = (uint8_t)zero;
    mBeamTurnRate = g0157d364 * g013eeda0;
    mMsPerDamagePointLo = zero;
    mMsPerDamagePointHi = zero;
    mLifeTimer.Construct();
    mTargetedCombatant = (IVtblObject*)zero;
    mPathBegin = (Vector3*)zero;
    mPathEnd = (Vector3*)zero;
    mPathCapacity = (Vector3*)zero;
    return this;
}

// @ 0x00cb8b20  Simulator::cDefaultBeamProjectile::~cDefaultBeamProjectile
void cDefaultBeamProjectile::FUN_00cb8b20()
{
    Vector3* path = mPathBegin;
    if (path != 0 && ((int*)path)[-1] != 0)
        operator_delete(path);
    if (mTargetedCombatant)
        ((VfnV)mTargetedCombatant->mpVtbl->mSlots[kVt04])(mTargetedCombatant);
    mLifeTimer.Destroy();
    if (mpSource)
        ((VfnV)mpSource->mpVtbl->mSlots[kVt64])(mpSource);
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    mInteraction.Destroy();
    mProj.mpVtbl = &gVtbl0145dca8;
    mSpatial.Destroy();
    mBase.Destroy();
}

// @ 0x00cb8ba0  Simulator::cDefaultBeamProjectile::GetEndPoints
void cDefaultBeamProjectile::FUN_00cb8ba0(Vector3* start, Vector3* end)
{
    if ((uint32_t)(mPathEnd - mPathBegin) > 1) {
        *start = *mPathBegin;
        *end = mPathEnd[-1];
        return;
    }
    const Vector3* pStart = (const Vector3*)((VfnP)mSpatial.mpVtbl->mSlots[kVt2C])(&mSpatial);
    *start = *pStart;
    float length = mMaxBeamLength;
    if (mTargetedCombatant != 0 || mbHittingGround != 0 || mbHittingWater != 0) {
        float dx = start->x - mHitPositionX;
        float dy = start->y - mHitPositionY;
        float dz = start->z - mHitPositionZ;
        length = (float)sqrt((double)dx * (double)dx + (double)dy * (double)dy +
                             (double)dz * (double)dz);
    }
    end->x = start->x + mBeamDirectionX * length;
    end->y = start->y + mBeamDirectionY * length;
    end->z = start->z + mBeamDirectionZ * length;
}

// ---------------------------------------------------------------------------
// SP::cDefaultAoEArea
// ---------------------------------------------------------------------------
class cDefaultAoEArea {
public:
    cGameDataBase       mBase;                // +0x000
    cSpatialBody        mSpatial;             // +0x034
    cProjectileBody     mProj;                // +0x108
    cSPSpaceToolData*   mpTool;               // +0x11c
    float               mSourceOffsetX;       // +0x120
    float               mSourceOffsetY;       // +0x124
    float               mSourceOffsetZ;       // +0x128
    float               mDamageRadius;        // +0x12c
    uint8_t             mbStopArea;           // +0x130
    uint8_t             mPad131[7];           // +0x131..+0x137
    cGonzagoTimer       mLifeTimer;           // +0x138
    uint32_t            mAccumulatedTimeLo;   // +0x158
    uint32_t            mAccumulatedTimeHi;   // +0x15c
    uint32_t            mCulturalTimeLo;      // +0x160
    uint32_t            mCulturalTimeHi;      // +0x164
    uint32_t            mLastUpdateLo;        // +0x168
    uint32_t            mLastUpdateHi;        // +0x16c
    void* FUN_00cb8cd0();                                    // ctor
};

// @ 0x00cb8cd0  Simulator::cDefaultAoEArea::cDefaultAoEArea
void* cDefaultAoEArea::FUN_00cb8cd0()
{
    mBase.Construct();
    mSpatial.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mBase.mpVtbl00 = &gVtbl014752b8;
    mBase.mpVtbl04 = &gVtbl014752a4;
    mSpatial.mpVtbl = &gVtbl014751e0;
    mProj.mpVtbl = &gVtbl014751b4;
    mpTool = (cSPSpaceToolData*)zero;
    __m128 zed = _mm_setzero_ps();
    mSourceOffsetX = g0169a414;
    mSourceOffsetY = g0169a418;
    mSourceOffsetZ = g0169a41c;
    _mm_store_ss(&mDamageRadius, zed);
    mbStopArea = (uint8_t)zero;
    mLifeTimer.Construct();
    mAccumulatedTimeLo = zero;
    mAccumulatedTimeHi = zero;
    mCulturalTimeLo = zero;
    mCulturalTimeHi = zero;
    mLastUpdateLo = zero;
    mLastUpdateHi = zero;
    return this;
}

// ---------------------------------------------------------------------------
// SP::cCulturalProjectile
// ---------------------------------------------------------------------------
class cCulturalProjectile {
public:
    cGameDataBase       mBase;                // +0x000
    cLocomotiveBody     mLoco;                // +0x034
    cProjSuperBody      mProjSuper;           // +0x108
    cProjectileBody     mProj;                // +0x504
    IVtblObject*        mPathLocomotion;      // +0x518
    IVtblObject*        mpVehicle;            // +0x51c
    IVtblObject*        mpTarget;             // +0x520
    cSPSpaceToolData*   mpTool;               // +0x524
    uint32_t            mField528;            // +0x528
    uint32_t            mPad52c[3];           // +0x52c..+0x537
    uint8_t             mbExplode;            // +0x538
    uint8_t             mbSpin;               // +0x539
    uint8_t             mPad53a[6];           // +0x53a..+0x53f
    cGonzagoTimer       mLifeTimer;           // +0x540
    uint32_t            mOwner;               // +0x560
    uint32_t            mPad564;              // +0x564
    cGonzagoTimer       mField568;            // +0x568
    void* FUN_00cb8dd0();                                    // ctor
    void FUN_00cb8f50();                                     // dtor
};

// @ 0x00cb8dd0  Simulator::cCulturalProjectile::cCulturalProjectile
void* cCulturalProjectile::FUN_00cb8dd0()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mLoco.mpVtbl = &gVtbl01475bd0;
    mBase.mpVtbl00 = &gVtbl01475b78;
    mBase.mpVtbl04 = &gVtbl01475b68;
    mProjSuper.mpVtbl = &gVtbl01475b60;
    mProj.mpVtbl = &gVtbl01475b38;
    mPathLocomotion = (IVtblObject*)zero;
    mpVehicle = (IVtblObject*)zero;
    mpTarget = (IVtblObject*)zero;
    mpTool = (cSPSpaceToolData*)zero;
    mField528 = 0xffffffff;
    mbExplode = (uint8_t)zero;
    mbSpin = (uint8_t)zero;
    mLifeTimer.Construct();
    mOwner = 0xffffffff;
    mField568.Construct();
    mProjSuper.mField198 = 0.0f;
    return this;
}

// @ 0x00cb8f50  Simulator::cCulturalProjectile::~cCulturalProjectile
void cCulturalProjectile::FUN_00cb8f50()
{
    mField568.Destroy();
    mLifeTimer.Destroy();
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    if (mpTarget)
        ((VfnV)mpTarget->mpVtbl->mSlots[kVt64])(mpTarget);
    if (mpVehicle)
        ((VfnV)mpVehicle->mpVtbl->mSlots[kVt04])(mpVehicle);
    if (mPathLocomotion)
        ((VfnV)mPathLocomotion->mpVtbl->mSlots[kVt04])(mPathLocomotion);
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
}

// ---------------------------------------------------------------------------
// SP::cResourceProjectile
// ---------------------------------------------------------------------------
class cResourceProjectile {
public:
    cGameDataBase       mBase;                // +0x000
    cLocomotiveBody     mLoco;                // +0x034
    cProjSuperBody      mProjSuper;           // +0x108
    cProjectileBody     mProj;                // +0x504
    IVtblObject*        mPathLocomotion;      // +0x518
    IVtblObject*        mpNode;               // +0x51c
    uint32_t            mPad520[4];           // +0x520..+0x52f
    cGonzagoTimer       mLifeTimer;           // +0x530
    uint32_t            mOwner;               // +0x550
    void* FUN_00cb9010();                                    // ctor
    void* FUN_00cb9170(int flags);                           // deleting dtor
};

// @ 0x00cb9010  Simulator::cResourceProjectile::cResourceProjectile
void* cResourceProjectile::FUN_00cb9010()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mBase.mpVtbl00 = &gVtbl01475e38;
    mBase.mpVtbl04 = &gVtbl01475e24;
    mLoco.mpVtbl = &gVtbl01475d28;
    mProjSuper.mpVtbl = &gVtbl01475d1c;
    mProj.mpVtbl = &gVtbl01475cf4;
    mPathLocomotion = (IVtblObject*)zero;
    mpNode = (IVtblObject*)zero;
    mLifeTimer.Construct();
    mOwner = 0xffffffff;
    return this;
}

// @ 0x00cb9170  Simulator::cResourceProjectile::~cResourceProjectile (deleting)
void* cResourceProjectile::FUN_00cb9170(int flags)
{
    mLifeTimer.Destroy();
    if (mpNode)
        ((VfnV)mpNode->mpVtbl->mSlots[kVt04])(mpNode);
    if (mPathLocomotion)
        ((VfnV)mPathLocomotion->mpVtbl->mSlots[kVt04])(mPathLocomotion);
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
    if (flags & 1)
        operator_delete(this);
    return this;
}

// ---------------------------------------------------------------------------
// cContentValidationSummarizer (tracer-backed summarizer, 0x00cb84b0)
// ---------------------------------------------------------------------------
class cContentValidationSummarizer {
public:
    Vtbl*         mpVtblTracer;        // +0x00  ??_7ITracerBase@Trace@EA@@6B@
    uint32_t      mPad04;              // +0x04
    Vtbl*         mpVtblSelf;          // +0x08  vtbl_cContentValidationSummarizer
    uint32_t      mPad0c[3];           // +0x0c..+0x17
    IVtblObject*  mpField18;           // +0x18
    uint32_t      mPad1c;              // +0x1c
    cGonzagoTimer mTimer;              // +0x20
    void* FUN_00cb84b0(int flags);     // deleting dtor
};

// @ 0x00cb84b0  cContentValidationSummarizer::~cContentValidationSummarizer (deleting)
void* cContentValidationSummarizer::FUN_00cb84b0(int flags)
{
    mTimer.Destroy();
    if (mpField18)
        ((VfnV)mpField18->mpVtbl->mSlots[kVtC0])(mpField18);
    mpVtblSelf = &gVtbl013ec458;
    mpVtblTracer = &gVtbl013eb938;
    if (flags & 1)
        operator_delete(this);
    return this;
}
