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
    virtual void v30(); virtual void SetOrientation(const Quaternion* q);   // +0x3c
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
