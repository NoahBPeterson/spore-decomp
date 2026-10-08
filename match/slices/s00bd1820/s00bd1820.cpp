// Slice s00bd1820: 0x00bd1cd0 (1589 bytes, thiscall ret 4), a vehicle aim/facing update.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (scalar SSE math, acos via _CIacos).
//
// Given a record whose +0x14 field holds the vehicle's object, picks a point to face:
//  - the combatant's current target (or the vehicle's own fallback target) when there is one,
//    facing straight at it;
//  - otherwise it wanders: every few updates (counter) it re-picks a heading by rotating the
//    up-projected direction around the vehicle's position vector by +-pi/4 (or not at all),
//    biased by +-2/3 of the position vector every fifth update.
// Then builds the facing quaternion (facing + planet up) and slerps the vehicle's orientation
// toward it with a step limited by the turn angle.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vec3 { float x, y, z; };                 // plain POD (integer-register copies)
struct Vec3c {                                  // Vector3 with a user copy ctor (movss member copies)
    float x, y, z;
    Vec3c() {}
    Vec3c(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3c(const Vec3c& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3c(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quat { float x, y, z, w; };
struct QuatC {
    float x, y, z, w;
    QuatC() {}
    QuatC(const QuatC& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct Matrix33 { float m[9]; };

// ---------------------------------------------------------------- engine helpers
Vec3 normalized_safe(const Vec3& v);                                   // 0x00449c20 SP::normalized_safe
Quat QuaternionFromFacingAndUp(const Vec3& facing, const Vec3& up);    // 0x0069b600
Quat SlerpWrap(const Quat& a, const Quat& b, float t);                 // 0x005b26f0
Matrix33 AxisAngleMatrix(const Vec3& axis, float angle);               // 0x00576b00
bool IsFinite(float f);                                                // 0x0059ab10

extern const Vec3 gDefaultVec3;                                        // 0x0168b66c
extern float gQuarterPi;                                               // 0x0156d708
extern float gHalfPi;                                                  // 0x0156d70c

// ---------------------------------------------------------------- objects
struct ISpatial {
    PV8 PV2 PV
    virtual const Vec3* GetPosition();                                 // +0x2c
};

struct IRefObject {                                                    // holder whose +8 slot yields the object
    PV2
    virtual ISpatial* GetObject();                                     // +0x08
};

struct IVehicleBody {                                                  // sub-object at vehicle +0x34
    PV8 PV2 PV
    virtual const Vec3* GetPosition();                                 // +0x2c
    virtual const Quat* GetOrientation();                              // +0x30
    PV2
    virtual void SetOrientation(const Quat* q);                        // +0x3c
    PV4 PV2 PV
    virtual void GetDirection(Vec3* pOut);                             // +0x5c
};

struct Combatant {                                                     // at vehicle +0x588
    PV16 PV4 PV
    virtual IRefObject* GetTargetRef();                                // +0x54
    bool IsExcluded();                                                 // 0x00bfc600
    int GetDamageState();                                              // 0x008e7f80
};

struct IPathHelper {
    PV8 PV8 PV4 PV2
    virtual const Vec3* GetAnchor(Vec3* pTmp);                         // +0x58
};

struct Vehicle {
    char pad00[0x34];
    IVehicleBody body;                                                 // +0x34
    char pad38[0x684 - 0x38];
    int mHostileCount;                                                 // +0x684
    IPathHelper* mpHelper;                                             // +0x688
    char pad68c[0x6a4 - 0x68c];
    IRefObject* mpFallbackTarget;                                      // +0x6a4
};

struct IObject {
    PV16 PV16 PV8 PV4 PV2
    virtual Vehicle* Cast(uint32_t typeID);                            // +0xb8
};

struct AimRecord {
    Vec3 mDefault;                                                     // +0x00
    uint32_t pad0c;
    float mScale;                                                      // +0x10
    IObject* mpObject;                                                 // +0x14
};

static __forceinline Vec3 operator*(const Vec3& u, const Matrix33& m)
{
    Vec3 r;
    r.x = m.m[3] * u.y + m.m[6] * u.z + m.m[0] * u.x;
    r.y = m.m[4] * u.y + m.m[7] * u.z + m.m[1] * u.x;
    r.z = m.m[5] * u.y + m.m[8] * u.z + m.m[2] * u.x;
    return r;
}
static __forceinline const float& MinR(const float& a, const float& b) { return (b < a) ? b : a; }
static __forceinline const float& MaxR(const float& a, const float& b) { return (a < b) ? b : a; }

struct cAimController {
    uint32_t pad00[4];
    int mMode;                                                         // +0x10
    int mCounter;                                                      // +0x14
    Vec3 mDir;                                                         // +0x18

    void Update(AimRecord* pRec);                                      // 0x00bd1cd0
};

// @ 0x00bd1cd0
void cAimController::Update(AimRecord* pRec)
{
    pRec->mDefault = gDefaultVec3;
    if (!pRec->mpObject)
        return;
    Vehicle* pVeh = pRec->mpObject->Cast(0x436f315);
    if (!pVeh)
        return;
    if (pVeh->mHostileCount > 0)
        return;
    Combatant* pCmb = (Combatant*)((char*)pVeh + 0x588);
    if (pCmb->IsExcluded())
        return;
    if (pCmb->GetDamageState() == 2)
        return;

    IVehicleBody* pBody = &pVeh->body;
    Vec3 fwd;
    pBody->GetDirection(&fwd);
    Vec3c pos(*pBody->GetPosition());

    ISpatial* pTarget;
    if (pCmb->GetTargetRef())
        pTarget = pCmb->GetTargetRef()->GetObject();
    else
        pTarget = 0;
    IRefObject* pHolder = pVeh->mpFallbackTarget;
    ISpatial* pFallback = pHolder ? pHolder->GetObject() : 0;

    ISpatial* pFace = pTarget;
    if (!pFace)
        pFace = pFallback;
    if (pFace) {
        const Vec3* p = pFace->GetPosition();
        Vec3 d;
        d.x = p->x - pos.x;
        d.y = p->y - pos.y;
        d.z = p->z - pos.z;
        mDir = normalized_safe(d);
        mMode = 1;
    } else {
        bool bPick = true;
        if (mMode != 1) {
            float dot = mDir.y * fwd.y + mDir.z * fwd.z + mDir.x * fwd.x;
            bPick = dot > 0.96f;
        }
        if (bPick) {
            mCounter += 1;
            mMode = 0;
            const Vec3& n1 = normalized_safe(*(Vec3*)&pos);
            Vec3 tmp;
            const Vec3* a = pVeh->mpHelper->GetAnchor(&tmp);
            Vec3 d;
            d.x = pos.x - a->x;
            d.y = pos.y - a->y;
            d.z = pos.z - a->z;
            const Vec3& n2 = normalized_safe(d);
            float k = n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
            Vec3 v;
            v.x = n2.x - n1.x * k;
            v.y = n2.y - n1.y * k;
            v.z = n2.z - n1.z * k;
            const Vec3& u = normalized_safe(v);

            float angle;
            if (mCounter % 2 != 0)
                angle = 0.0f;
            else if (mCounter % 4 == 0)
                angle = gQuarterPi;
            else
                angle = -gQuarterPi;
            Vec3 r = u * AxisAngleMatrix(n1, angle);

            if (mCounter % 5 == 0) {
                Vec3 w;
                if (mCounter % 2 == 0) {
                    w.x = r.x - n1.x * 0.6666667f;
                    w.y = r.y - n1.y * 0.6666667f;
                    w.z = r.z - n1.z * 0.6666667f;
                } else {
                    w.x = n1.x * 0.6666667f + r.x;
                    w.y = n1.y * 0.6666667f + r.y;
                    w.z = n1.z * 0.6666667f + r.z;
                }
                mDir = normalized_safe(w);
            } else {
                mDir = r;
            }
        }
    }

    const Vec3& up = normalized_safe(*(Vec3*)&pos);
    const Quat& target = QuaternionFromFacingAndUp(mDir, up);
    QuatC cur(*(const QuatC*)pBody->GetOrientation());
    float dotf = mDir.y * fwd.y + mDir.z * fwd.z + mDir.x * fwd.x;
    float angle = acosf(MaxR(-1.0f, MinR(1.0f, dotf)));
    if (IsFinite(angle)) {
        float f = gHalfPi;
        if (mMode == 0)
            f = gQuarterPi * 0.666f;
        float t;
        if (angle > 0.0f) {
            float q = pRec->mScale * f / angle;
            t = MinR(1.0f, q);
        } else {
            t = 1.0f;
        }
        Quat res = SlerpWrap(*(const Quat*)&cur, target, t);
        pBody->SetOrientation(&res);
    }
}
