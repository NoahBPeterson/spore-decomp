// Slice s00dadce0: one spawn-placement test (0x00dadfb0). Looks up a region on the input's
// owner, has the host attach to it, picks a random radius in [1,2] from the shared math RNG,
// copies the input position into the output record, and returns true when the region's
// position lies strictly within distance 1 of that position.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar SSE float math, x87 for the double RNG).
#include "types.h"

namespace EA {
namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();
};
}
}
extern EA::Random::RandomLinearCongruential sMathRandomA;   // 0x1601760

#define VFILL(n) virtual void vs##n() {}

// Object reached through SpawnIn::owner; vtable slot 0x5c (index 23) finds a region by key.
struct RegionOwner {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22)
    virtual struct Region* FindRegion(uint32_t key);
};

// Embedded sub-object at Region+0xc0; vtable slot 0x2c (index 11) returns a float[3] position.
struct RegionPosition {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10)
    virtual float* GetPosition();
};

struct Region {
    char pad0[0xc0];
    RegionPosition sub;                                   // +0xc0
    char pad1[0x5a8 - 0xc0 - sizeof(RegionPosition)];
    char target[4];                                       // +0x5a8, address handed to the host
};

// Host object; vtable slot 0x84 (index 33) attaches a target pointer with two flags.
struct SpawnHost {
    VFILL(0) VFILL(1) VFILL(2) VFILL(3) VFILL(4) VFILL(5) VFILL(6) VFILL(7)
    VFILL(8) VFILL(9) VFILL(10) VFILL(11) VFILL(12) VFILL(13) VFILL(14) VFILL(15)
    VFILL(16) VFILL(17) VFILL(18) VFILL(19) VFILL(20) VFILL(21) VFILL(22) VFILL(23)
    VFILL(24) VFILL(25) VFILL(26) VFILL(27) VFILL(28) VFILL(29) VFILL(30) VFILL(31)
    VFILL(32)
    virtual void Attach(void* p, bool a, bool b);
};

struct SpawnIn {
    int32_t pad0;
    RegionOwner* owner;                                   // +0x4
    int32_t pad1;
    float x, y, z;                                        // +0xc, +0x10, +0x14
};

struct SpawnOut {
    int32_t zero0;                                        // +0x0
    float radius;                                         // +0x4
    float x, y, z;                                        // +0x8, +0xc, +0x10
    int32_t zero1;                                        // +0x14
};

// Clamp to [1,2]. Not NaN-safe in the same way as the original's branch order, but the RNG never yields NaN.
static inline double ClampRadius(double v)
{
    if (2.0 <= v)
        return 2.0;
    if (v < 1.0)
        return 1.0;
    return v;
}

// @ 0x00dadfb0  cdecl; four of the seven stack arguments are never read.
bool SpawnPlacementTest(SpawnHost* host, int32_t, int32_t, int32_t, int32_t, SpawnOut* out, SpawnIn* in)
{
    RegionOwner* owner = in->owner;
    if (owner != 0) {
        Region* region = owner->FindRegion(0xce9f6639);
        if (region != 0) {
            host->Attach(region->target, true, false);
            out->zero0 = 0;
            out->radius = (float)ClampRadius(sMathRandomA.RandomDoubleUniform() + 1.0);
            *(uint32_t*)&out->x = *(uint32_t*)&in->x;     // integer copies, as in the original
            *(uint32_t*)&out->y = *(uint32_t*)&in->y;
            *(uint32_t*)&out->z = *(uint32_t*)&in->z;
            out->zero1 = 0;
            const float* p = region->sub.GetPosition();
            float dx = out->x - p[0];
            float dy = out->y - p[1];
            float dz = out->z - p[2];
            float d2 = dx * dx;
            d2 += dy * dy;
            d2 += dz * dz;
            return 1.0f > d2;
        }
    }
    return false;
}
