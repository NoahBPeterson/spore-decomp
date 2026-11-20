// @ 0x00dc95e0
// Vehicle path upkeep: when the vehicle already has a repark pending (path flag 4) or the
// locomotion object still wants to move, nothing happens; otherwise the order's destination and
// the distance band it accepts are fetched from 0x00c9e8a0, the vehicle's distance to the
// destination is measured and a repark is requested when it falls outside that band.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8

struct Vector3 {
    float x, y, z;
};

// Spatial-object interface embedded at +0x34 of vehicles.
struct cSpatialObject {
    PAD8 PAD1 PAD1 PAD1                                            // slots 0..10
    virtual const Vector3& GetPosition();                          // +0x2c
    PAD16 PAD16 PAD4 PAD1 PAD1                                     // slots 12..49
    virtual float GetDesiredSpeed();                               // +0xc8
};

struct cVehicle {
    char           pad0[0x34];
    cSpatialObject mLoco;                                          // +0x34
    char           pad38[0x2a4 - 0x38];
    uint8_t        mPathFlags;                                     // +0x2a4

    void Fc9e8a0(Vector3* dest, float* minDist, float* maxDist);   // 0x00c9e8a0
};

extern void __cdecl AttemptRepark(cVehicle* v);                    // 0x00dc9430

// The distance is accumulated in double (x87) and truncated back to float, which is why the
// game's code keeps the three coordinate deltas on the x87 stack and ends in a bare fsqrt.
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

void __cdecl Fdc95e0(cVehicle* v)
{
    if (v->mPathFlags & 4)
        return;

    if (v->mLoco.GetDesiredSpeed() > 0.0f)
        return;

    Vector3 dest;
    float minDist;
    float maxDist;
    v->Fc9e8a0(&dest, &minDist, &maxDist);

    const Vector3& pos = v->mLoco.GetPosition();
    double dx = pos.x - dest.x;
    double dy = pos.y - dest.y;
    double dz = pos.z - dest.z;
    float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);

    if (dist < minDist || dist > maxDist)
        AttemptRepark(v);
}
