// Slice s00dc9770: SP::VehicleTree::AirAttack_Tick (0x00dc9770).
// Behavior-tree callback for an air vehicle attacking its target: state 0 flies away from the target (120 units
// past it), state 1 waits until the path is short, state 2 keeps queueing strafing-run waypoints (on the
// planet surface) in front of / to the side of the target and slows down when close.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Raw3 {                            // plain struct (bitwise copies)
    float x, y, z;
};

struct Waypoint {                        // 0x3c bytes
    Vector3  pos;                         // +0
    float    speed;                       // +0xc
    int      i10;                         // +0x10
    float    rest[9];                     // +0x14 .. +0x38
    uint8_t  flag;                        // +0x38
    Waypoint(float x, float y, float z) { pos.x = x; pos.y = y; pos.z = z; speed = 1.0f; i10 = 0; flag = 0; }
    Waypoint(const Waypoint& o);          // 0x00ac1ff0
};
inline void* operator new(unsigned int, void* p) { return p; }

struct WaypointVector {                   // sp_vector<Waypoint>, the path of the locomotion object
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    void DoInsertValue(Waypoint* pos, const Waypoint& v);     // 0x00ac45e0
    const Vector3* Back();                                    // 0x00c423c0 (last waypoint position)
    void push_back(const Waypoint& v)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Waypoint(v);
        else
            DoInsertValue(mpEnd, v);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

// Spatial-object interface embedded at +0x34 of vehicles.
struct cSpatialObject {
    PAD8 PAD1 PAD1 PAD1                                            // slots 0..10
    virtual const Vector3& GetPosition();                          // +0x2c
    PAD8 PAD1 PAD1 PAD1                                            // slots 12..22
    virtual Vector3 GetVelocity();                                 // +0x5c
    PAD16 PAD8 PAD1 PAD1 PAD1                                      // slots 24..50
    virtual float GetSpeed();                                      // +0xcc
    PAD4 PAD1                                                      // slots 52..56
    virtual void MoveTo(const Vector3& dst, float speed);          // +0xe4

    WaypointVector* GetPath();                                     // 0x00c41ec0
};

struct cTargetObject {
    PAD8 PAD1 PAD1 PAD1                                            // slots 0..10
    virtual const Vector3& GetPosition();                          // +0x2c
    PAD16 PAD16 PAD1 PAD1                                          // slots 12..45
    virtual void* IsType(const void* typeKey);                     // +0xb8
};

struct cGameData {      // embedded at +0x508 of the vehicle
    PAD16 PAD4
    virtual void SetAttackTarget(void* target);                    // +0x50
};

struct cPlanetModel {
    Raw3 ToSurface(const Raw3& pos);                         // 0x00b81630
};
extern cPlanetModel* __cdecl PlanetModel();                        // 0x00b3d350
extern Raw3 __cdecl normalized_safe(const Raw3& v);          // 0x00449c20

namespace EA { namespace Random {
struct RandomLinearCongruential {
    double RandomDoubleUniform();                                  // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;           // 0x01601760
extern char g_AirAttackTypeKey[];                                  // 0x013f94d4
extern float g_Dispatch016a006c;                                   // 0x016a006c

struct cVehicle {
    PAD16 PAD1 PAD1 PAD1
    char           pad4[0x30];
    cSpatialObject mLoco;                                          // +0x34
    char           pad38[0x21c - 0x38];
    float          mfSpeedRef;                                     // +0x21c
    char           pad220[0x508 - 0x220];
    cGameData      mGameData;                                      // +0x508

    cTargetObject* GetTarget();                                    // 0x00c9fee0
    void SetStrafeDistance(float f);                               // 0x00c9ee70
    float GetSurfaceHeight();                                      // 0x00c9eb80
};

static __forceinline void PushSurface(cSpatialObject* loco, cVehicle* self, Raw3& p)
{
    p = PlanetModel()->ToSurface(p);
    float h = self->GetSurfaceHeight();
    Raw3 n = normalized_safe(p);
    p.x = n.x * h + p.x;
    p.y = n.y * h + p.y;
    p.z = n.z * h + p.z;
    loco->GetPath()->push_back(Waypoint(p.x, p.y, p.z));
}

namespace SP { namespace VehicleTree {

// @ 0x00dc9770
bool AirAttack_Tick(cVehicle* self, int, int, int, int, int* pState)
{
    cTargetObject* target = self->GetTarget();
    if (!target) {
        self->SetStrafeDistance(0.0f);
        *pState = 0;
    }
    switch (*pState) {
    case 0:
        if (target) {
            Vector3 tp = target->GetPosition();
            const Vector3& sp = self->mLoco.GetPosition();
            float dx = tp.x - sp.x, dy = tp.y - sp.y, dz = tp.z - sp.z;
            float len = (float)sqrt(dx * dx + dy * dy + dz * dz);
            float inv = 1.0f / len;
            Vector3 away;
            away.x = tp.x - dx * inv * 120.0f;
            away.y = tp.y - dy * inv * 120.0f;
            away.z = tp.z - dz * inv * 120.0f;
            self->mLoco.MoveTo(away, 1.0f);
            *pState = 1;
        }
        break;
    case 1:
        if (self->mLoco.GetPath()->size() < 4)
            *pState = 2;
        break;
    case 2: {
        cSpatialObject* loco = &self->mLoco;
        Vector3 me = loco->GetPosition();
        Vector3 tp = target->GetPosition();
        float dx = tp.x - me.x, dy = tp.y - me.y, dz = tp.z - me.z;
        float len = (float)sqrt(dx * dx + dy * dy + dz * dz);
        float inv = 1.0f / len;
        Vector3 dir;
        dir.x = dx * inv; dir.y = dy * inv; dir.z = dz * inv;

        Vector3 vel = loco->GetVelocity();
        float dot = vel.z * dir.z + vel.y * dir.y + dir.x * vel.x;
        if (dot < 0.1f)
            self->mGameData.SetAttackTarget(0);
        else {
            void* t = target->IsType(g_AirAttackTypeKey);
            self->mGameData.SetAttackTarget(t);
        }

        if (len < 100.0f)
            self->SetStrafeDistance(loco->GetSpeed() * 0.5f);

        if (loco->GetPath()->size() < 4) {
            Vector3 g = *loco->GetPath()->Back();
            float gx = g.x, gy = g.y, gz = g.z;
            float ex = tp.x - gx, ey = tp.y - gy, ez = tp.z - gz;
            float len2 = (float)sqrt(ex * ex + ey * ey + ez * ez);
            float inv2 = 1.0f / len2;
            Vector3 dir2;
            dir2.x = ex * inv2; dir2.y = ey * inv2; dir2.z = ez * inv2;

            Raw3 p1;
            p1.x = dir2.x * len2 + gx; p1.y = dir2.y * len2 + gy; p1.z = dir2.z * len2 + gz;
            PushSurface(loco, self, p1);

            float t = (g_Dispatch016a006c / self->mfSpeedRef / g_Dispatch016a006c) * loco->GetSpeed() * 2.1f + len2;
            Raw3 p2;
            p2.x = dir2.x * t + gx; p2.y = dir2.y * t + gy; p2.z = dir2.z * t + gz;
            PushSurface(loco, self, p2);

            Raw3 tpr; tpr.x = tp.x; tpr.y = tp.y; tpr.z = tp.z;
            Raw3 a = normalized_safe(tpr);
            Raw3 c;
            c.x = a.y * dir2.z - a.z * dir2.y;
            c.y = a.z * dir2.x - dir2.z * a.x;
            c.z = dir2.y * a.x - a.y * dir2.x;
            if (sMathRandom.RandomDoubleUniform() < 0.5) {
                c.x = c.x * -1.0f; c.y = c.y * -1.0f; c.z = c.z * -1.0f;
            }
            float r = (float)sMathRandom.RandomDoubleUniform();
            Raw3 v;
            v.x = dir2.x * r + c.x; v.y = dir2.y * r + c.y; v.z = dir2.z * r + c.z;
            Raw3 n = normalized_safe(v);
            Raw3 p3;
            p3.x = n.x * 90.0f + tp.x; p3.y = n.y * 90.0f + tp.y; p3.z = n.z * 90.0f + tp.z;
            PushSurface(loco, self, p3);
        }
        break;
    }
    }
    return true;
}

}}
