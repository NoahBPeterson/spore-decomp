// Slice s00f8e6c0 -- terrain-sphere ray cast against a cube-map heightfield (0x00f8e6c0).
// Intersects the ray P + t*D with the shell between radii (base - scale*1.001) and
// (base + scale*1.001) using FUN_00f884a0 (ray/sphere), then marches the ray in steps of 2.0 until
// the point drops below the terrain radius (map height * scale + base), then bisects (<= 20 steps).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>
#include <math.h>

struct FaceUV { float u, v; int face; };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };

namespace SP {
struct cTerrainMapU16 {
    float GetFloat(FaceUV* uv);   // 0x00f8d620 SP::cTerrainMap<unsigned short>::GetFloat
};
}

// 0x00f884a0 ray (P, D) vs sphere of radius r: t0/t1 roots; false if no hit
bool __cdecl RaySphere(Vec3* p, Vec3* d, float r, float* t0, float* t1);   // 0x00f884a0

static __forceinline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
static __forceinline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }

// direction -> cube face index + (u, v) in [0,1]
static __forceinline void DirToCubeInto(FaceUV& r, const Vec3& v)
{
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az >= ax && az >= ay) {
        r.u = (x / z + 1.0f) * 0.5f;
        r.v = (y / az + 1.0f) * 0.5f;
        if (z >= 0.0f) r.face = 0; else r.face = 1;
    } else if (ay >= ax) {
        r.u = (z / y + 1.0f) * 0.5f;
        r.v = (x / ay + 1.0f) * 0.5f;
        if (y >= 0.0f) r.face = 4; else r.face = 5;
    } else {
        r.u = (y / x + 1.0f) * 0.5f;
        r.v = (z / ax + 1.0f) * 0.5f;
        r.face = 2;
        if (!(x >= 0.0f)) r.face = 3;
    }
}

static __forceinline FaceUV DirToCube(const Vec3& v)
{
    FaceUV r;
    DirToCubeInto(r, v);
    return r;
}

// @ 0x00f8e6c0
bool __cdecl TerrainRayCast(SP::cTerrainMapU16* map, float base, float scale,
                            Vec3* origin, Vec3* dir, Vec3* out)
{
    float hi = scale * 1.001f + base;
    float lo = base - scale * 1.001f;
    Vec3 o = *origin;
    Vec3 d = *dir;
    float len2 = (o.y * o.y + o.x * o.x) + o.z * o.z;
    if (lo * lo > len2)
        return false;

    FaceUV uv;
    DirToCubeInto(uv, o);
    float r = map->GetFloat(&uv) * scale + base;
    if (r * r > len2)
        return false;

    float tmin = 0.0f;
    float tmax = FLT_MAX;
    float t0, t1;
    if (!RaySphere(&o, &d, hi, &t0, &t1))
        return false;
    if (1e-6f > fabsf(t0 - t1))
        return false;
    tmin = Max(tmin, t0);
    tmax = Min(tmax, t1);
    if (RaySphere(&o, &d, lo, &t0, &t1) && tmin < t0)
        tmax = Min(tmax, t0);

    float len = sqrtf((d.x * d.x + d.y * d.y) + d.z * d.z);
    float inv = 1.0f / len;
    float nx = d.x * inv;
    float ny = d.y * inv;
    float nz = d.z * inv;
    float t = len * tmin;
    float tEnd = len * tmax + 2.0f;
    float prev = t;
    if (!(tEnd > t))
        return false;

    Vec3 p;
    for (;;) {
        p.x = nx * t + o.x;
        p.y = ny * t + o.y;
        p.z = nz * t + o.z;
        uv = DirToCube(p);
        float rr = map->GetFloat(&uv) * scale + base;
        rr = rr * rr;
        float pl = (p.x * p.x + p.z * p.z) + p.y * p.y;
        if (rr >= pl)
            break;
        prev = t;
        t = t + 2.0f;
        if (!(tEnd > t))
            return false;
    }

    float a = prev;
    float b = t;
    for (int i = 0; i < 20; i++) {
        float mid = (b + a) * 0.5f;
        p.x = nx * mid + o.x;
        p.y = ny * mid + o.y;
        p.z = nz * mid + o.z;
        uv = DirToCube(p);
        float rr = map->GetFloat(&uv) * scale + base;
        rr = rr * rr;
        float pl = (p.x * p.x + p.z * p.z) + p.y * p.y;
        if (fabsf(rr - pl) < 0.01f)
            break;
        if (!(rr >= pl))
            a = mid;
        else
            b = mid;
    }
    out->x = p.x;
    out->y = p.y;
    out->z = p.z;
    return true;
}
