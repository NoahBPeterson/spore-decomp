// Slice s00f6edc0: SP terrain-effect map helpers (anonymous-namespace cTerrainEffectMapNormal
// and the cTerrainMap / cCubeImage samplers it reads through).  All nine functions are a
// "pick the cube face for a direction, map it to (u,v) in [0,1], sample a terrain map there"
// pattern: the four small getters, the vector "Normal" sampling, the two blend helpers and the
// three range tests.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE   (x87 fabs + SSE float mix => VC7.1/2003 toolchain)
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- sampled resources
// Sample sources; the only field these helpers read is the element count at +0xc.
struct cTerrainMapShort {                             // 8-bit/16-bit height map
    char  mPad00[0x0c];
    int   m0c;                                        // +0x0c
    float GetFloat(const void* uv);                   // 0x00f8d620
};

struct cTerrainMapInt {                               // 32-bit splat map
    char  mPad00[0x0c];
    int   m0c;                                        // +0x0c
    float GetFloat(const void* uv);                   // 0x00f88650
    const float* GetVector3(void* out, const void* uv); // 0x00f88eb0
};

struct cCubeImage {                                   // cube-map normal source
    char  mPad00[0x0c];
    int   m0c;                                        // +0x0c
    float SampleBilinear(const void* uv);             // 0x00f8de70
};

// blend evaluator reached through cTerrainEffectMapNormal::mp10
struct cEffectBlend {
    float Eval(float a, float b);                     // 0x00fb8830
};

// the map set a cTerrainEffectMapNormal points at (*(this+0xc))
struct cTerrainEffectMapSet {
    char              mPad00[0x08];
    cTerrainMapShort* mp08;     // +0x08
    cTerrainMapInt*   mp0c;     // +0x0c
    cCubeImage*       mp10;     // +0x10
    char              mPad14[0x24];
    float             m38;      // +0x38
    float             m3c;      // +0x3c
    char              mPad40[4];
    float             m44;      // +0x44
    float             m48;      // +0x48
};

// fallback direction returned by Normal when the map is not loaded
extern Vec3 gDefaultNormal;                               // 0x016c99e0

// ---------------------------------------------------------------- face / uv mapping
struct FaceUv {
    float u;
    float v;
    int   face;
};

// Project a direction onto the dominant axis' cube face and map it to (u,v) in [0,1].
static __forceinline void FaceFromDir(const float* dir, FaceUv* r)
{
    float x = dir[0];
    float y = dir[1];
    float z = dir[2];
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);

    if (az >= ax && az >= ay) {
        r->u = (x / z + 1.0f) * 0.5f;
        r->v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f)
            r->face = 1;
        else
            r->face = 0;
    } else if (ay < ax) {
        r->u = (y / x + 1.0f) * 0.5f;
        r->v = (z / ax + 1.0f) * 0.5f;
        r->face = 2;
        if (x < 0.0f)
            r->face = 3;
    } else {
        r->u = (z / y + 1.0f) * 0.5f;
        r->v = (x / ay + 1.0f) * 0.5f;
        if (y < 0.0f)
            r->face = 5;
        else
            r->face = 4;
    }
}

// ---------------------------------------------------------------- the map itself
struct cTerrainEffectMapNormal {
    char                  mPad00[0x0c];
    cTerrainEffectMapSet* mp0c;    // +0x0c  the loaded map set
    cEffectBlend*         mp10;    // +0x10  the blend evaluator

    float GetFloat(const float* dir);                 // 0x00f6edc0
    int   GetCountShort();                            // 0x00f6efa0
    Vec3  Normal(const float* dir);                   // 0x00f6efc0
    int   GetCountSum();                              // 0x00f6f190
    float Blend(const float* dir);                    // 0x00f6f1b0
    float GetNormalized(const float* dir);            // 0x00f6f390
    float Test(const float* dir);                     // 0x00f6f5a0
    float GetRatio(const float* dir);                 // 0x00f6f7d0
    float TestRange(const float* dir);                // 0x00f6fa00
};

// @ 0x00f6edc0
float cTerrainEffectMapNormal::GetFloat(const float* dir)
{
    cTerrainMapInt* map = mp0c->mp0c;
    if (map == 0)
        return 0.0f;

    FaceUv r;
    FaceFromDir(dir, &r);
    return map->GetFloat(&r);
}

// @ 0x00f6efa0
int cTerrainEffectMapNormal::GetCountShort()
{
    cTerrainMapShort* map = mp0c->mp08;
    if (map)
        return map->m0c;
    return 0;
}

// @ 0x00f6efc0
Vec3 cTerrainEffectMapNormal::Normal(const float* dir)
{
    const Vec3* src;
    cTerrainMapInt* map = mp0c->mp0c;

    if (map == 0) {
        src = &gDefaultNormal;
    } else {
        FaceUv r;
        FaceFromDir(dir, &r);

        Vec3 tmp;
        const float* p = map->GetVector3(&tmp, &r);
        Vec3 res;
        res.x = p[0];
        res.y = p[1];
        res.z = p[2];
        src = &res;
    }

    return *src;
}

// @ 0x00f6f190
int cTerrainEffectMapNormal::GetCountSum()
{
    cTerrainMapShort* a = mp0c->mp08;
    cCubeImage*       b = mp0c->mp10;
    if (b != 0 && a != 0)
        return b->m0c + a->m0c;
    return 0;
}

// @ 0x00f6f1b0
float cTerrainEffectMapNormal::Blend(const float* dir)
{
    FaceUv r;
    FaceFromDir(dir, &r);

    cTerrainEffectMapSet* m = mp0c;
    if (m->mp10 == 0 || m->mp08 == 0)
        return 0.0f;

    float t = m->mp10->SampleBilinear(&r);
    float k = m->m38;
    float s = m->mp08->GetFloat(&r);

    return mp10->Eval(s * k, t);
}

// @ 0x00f6f390
float cTerrainEffectMapNormal::GetNormalized(const float* dir)
{
    cTerrainEffectMapSet* m = mp0c;
    if (m->mp08 == 0 || m->mp0c == 0)
        return 0.0f;

    float k   = m->m38;
    float mid = (m->m44 + m->m3c) * m->m38;
    float b   = m->m48;

    FaceUv r;
    FaceFromDir(dir, &r);

    float v = m->mp0c->GetFloat(&r) * k;
    if (b > v) {
        float t = m->mp08->GetFloat(&r) * k;
        if (mid < t)
            return (t - mid) / (k - mid);
    }
    return 0.0f;
}

// @ 0x00f6f5a0
float cTerrainEffectMapNormal::Test(const float* dir)
{
    cTerrainEffectMapSet* m = mp0c;
    if (m->mp08 == 0 || m->mp0c == 0)
        return 0.0f;

    float k   = m->m38;
    float mid = (m->m44 + m->m3c) * m->m38;
    float b   = m->m48;

    FaceUv r;
    FaceFromDir(dir, &r);

    float v = m->mp0c->GetFloat(&r) * k;
    if (b > v) {
        float t = m->mp08->GetFloat(&r) * k;
        if (mid < t)
            return 1.0f;
        return 0.0f;
    }
    return 0.0f;
}

// @ 0x00f6f7d0
float cTerrainEffectMapNormal::GetRatio(const float* dir)
{
    cTerrainEffectMapSet* m = mp0c;
    if (m->mp08 == 0 || m->mp0c == 0)
        return 0.0f;

    float k   = m->m38;
    float hi  = (m->m44 + m->m3c) * m->m38;
    float lo  = m->m3c * m->m38;
    float b   = m->m48;

    FaceUv r;
    FaceFromDir(dir, &r);

    float t = m->mp08->GetFloat(&r) * k;
    if (lo <= t && t <= hi) {
        float s = m->mp0c->GetFloat(&r) * k;
        if (b > s)
            return (t - lo) / (hi - lo);
    }
    return 0.0f;
}

// @ 0x00f6fa00
float cTerrainEffectMapNormal::TestRange(const float* dir)
{
    cTerrainEffectMapSet* m = mp0c;
    if (m->mp08 == 0 || m->mp0c == 0)
        return 0.0f;

    float k   = m->m38;
    float hi  = (m->m44 + m->m3c) * m->m38;
    float lo  = m->m3c * m->m38;
    float b   = m->m48;

    FaceUv r;
    FaceFromDir(dir, &r);

    float t = m->mp08->GetFloat(&r) * k;
    if (lo <= t && t <= hi) {
        float s = m->mp0c->GetFloat(&r) * k;
        if (b > s)
            return 1.0f;
        return 0.0f;
    }
    return 0.0f;
}
