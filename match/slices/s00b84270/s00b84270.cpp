// s00b84270: one function, 0x00b84730 (447 bytes), thiscall void(float* out) ret 4 on cPlanetModel.
// Picks a random direction, scales it by the planet radius, then walks it toward the terrain
// (at most 10000 steps) and writes the final point; falls back to a constant if the walk never settles.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

struct Vec3POD { float x, y, z; };

// Terrain map set. Only the floats read here are named (+0x34, +0x38, +0x3c).
struct cTerrainMapSet {
    char pad0[0x34];
    float f34;
    float f38;
    float f3c;
    float GetHeightAt(const Vec3POD* pos);      // 0x00f927c0, thiscall ret 4
};

// Interface behind cPlanetModel::mpISphere (+0x24). Slot +0xC (index 3) returns a map set, no args.
struct cITerrainSphere {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual cTerrainMapSet* s3();               // +0xC, thiscall ret 0
};

struct cPlanetModel {
    char pad0[0x20];
    void* mpSphere;                             // +0x20 (only null-checked here)
    cITerrainSphere* mpISphere;                 // +0x24
    float GetRadiusAt(const Vec3POD* dir);      // 0x00b7ef70, thiscall ret 4
    void GetRandomSurfacePoint(float* out);     // 0x00b84730
};

void RandomDirection3(Vec3POD* out);            // 0x00b7e560, cdecl
extern const Vec3POD kFallbackPoint;            // 0x016881f0
extern const float kDefaultHeight;              // 0x01465414

void cPlanetModel::GetRandomSurfacePoint(float* out)
{
    Vec3POD dir;
    RandomDirection3(&dir);
    float radius = GetRadiusAt(&dir);

    Vec3POD cur;
    cur.x = dir.x * radius;
    cur.y = dir.y * radius;
    cur.z = dir.z * radius;

    int n = 0;
    for (;;) {
        ++n;
        if (!mpISphere)
            break;
        float h = mpISphere->s3()->GetHeightAt(&cur);
        cTerrainMapSet* m = mpISphere->s3();
        float surf = m->f34 + m->f3c * m->f38;
        if (surf <= h)
            break;

        Vec3POD d2;
        RandomDirection3(&d2);
        float s;
        if (mpSphere) {
            s = mpISphere->s3()->GetHeightAt(&d2);
        } else {
            if (mpISphere && mpISphere->s3())
                s = mpISphere->s3()->f34;
            else
                s = kDefaultHeight;
        }

        Vec3POD tmp;
        tmp.x = d2.x * s;
        tmp.y = d2.y * s;
        tmp.z = d2.z * s;
        cur = tmp;
        if (n >= 10000)
            break;
    }

    if (n < 10000) {
        out[0] = cur.x;
        out[1] = cur.y;
        out[2] = cur.z;
    } else {
        out[0] = kFallbackPoint.x;
        out[1] = kFallbackPoint.y;
        out[2] = kFallbackPoint.z;
    }
}
