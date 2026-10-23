// Slice s00f73260 -- SP terrain-sphere cube-map surface samplers (0x00f73260, 0x00f73760, 0x00f73c10).
//
// Three virtual methods of the same terrain-sphere object (vtable pairs at 0x01490908 / 0x01490940,
// next to the "Terrain/Sphere/{HeightMap,NormalMap,...}" registry strings).  They turn a local
// direction (or an already transformed point) into a surface point on the sphere shell:
//
//   * forward-transform the local direction into the object's space,
//   * compute the point p = t + scale*dir (with a 1e-6 nudge on the z term),
//   * pick the dominant cube-map face of p and its (u,v) in [0,1] (the shared DirToCube idiom),
//   * sample the height cube map (cTerrainMap<u16>::GetFloat) and place the surface point at
//     radius = (xform+0x38 + base) + max(scale*height, min) along the normalized direction,
//   * inverse-transform that point back (Xform::InverseTransformPoint 0x007CDA70), emit it, and
//     optionally emit the surface normal and a quaternion basis (FUN_00a81b80 + QuaternionFromMatrix33).
//
// 0x00f73c10 also samples the normal cube map (cTerrainMap<u32>::GetVector4), unmapping the stored
// [0,1] vector to [-1,1], and uses it as the output normal; 0x00f73760 is the same but takes an
// extra radial offset argument and short-circuits when radius <= |p|.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Status: all three are COMPLETE and behaviourally equivalent but not byte-exact (see
// nonmatching.txt).  0x00f73260 and 0x00f73760 pass difftest at 100%/99.3% instruction coverage;
// 0x00f73c10 passes all but one float-special (NaN/overflow) input.
#include "types.h"
#include <float.h>
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

struct Mat33 { float m[9]; };
struct FaceUV { float u; float v; int face; };

struct Xform {
    uint32_t flags;                       // +0x00  (bit 1: rotated, bit 2: biased)
    Vec3     t;                           // +0x04
    float    scale;                       // +0x10
    float    m[9];                        // +0x14
    float    pad38;                       // +0x38
    void InverseTransformPoint(Vec3* v) const;  // 0x007CDA70
};

namespace SP {
struct cTerrainMapU16 {
    float GetFloat(const FaceUV* uv);               // 0x00f8d620
    void  GetVector4(float* out, const FaceUV* uv); // 0x00f89e50
};
}

void  FUN_00a81b80(const Vec3* n, Mat33* out);                       // 0x00a81b80

// Returns a reference to the (temporary) quaternion it fills in: the original materialises the
// result in a temporary and then copies it out with a 16-byte SSE move.
Quat& QuaternionFromMatrix33(Quat* out, const Mat33* m, float eps);  // 0x00472b80

static const float kEps  = 1e-06f;

// direction -> cube face index + (u, v) in [0,1] (shared with the terrain-sphere slices)
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

// local direction -> the object space point p = t + scale*dir (+ 1e-6 on z)
static __forceinline Vec3 ForwardPoint(const Xform* xf, float dx, float dy, float dz)
{
    if (xf->flags & 2) {
        // The three rotated components are each staged through memory before the scale pass
        // (the original keeps them in a Vec3 local that the scale pass then reads back).
        float rx = (xf->m[6] * dz + xf->m[3] * dy) + xf->m[0] * dx;
        float ry = (xf->m[7] * dz + xf->m[4] * dy) + xf->m[1] * dx;
        float rz = (xf->m[8] * dz + xf->m[5] * dy) + xf->m[2] * dx;
        dx = rx; dy = ry; dz = rz;
    }
    float s = xf->scale;
    Vec3 p;
    p.x = xf->t.x + s * dx;
    p.y = xf->t.y + s * dy;
    p.z = (xf->t.z + s * dz) + kEps;
    return p;
}

// rotate a vector by the xform's matrix (row-major access, x term last)
static __forceinline Vec3 RotateBy(const Xform* xf, const Vec3& v)
{
    float z = v.z;
    float y = v.y;
    float x = v.x;
    Vec3 r;
    r.x = (xf->m[2] * z + xf->m[1] * y) + xf->m[0] * x;
    r.y = (xf->m[5] * z + xf->m[4] * y) + xf->m[3] * x;
    r.z = (xf->m[8] * z + xf->m[7] * y) + xf->m[6] * x;
    return r;
}

struct cTerrainSphere {
    uint8_t pad00[0x0c];
    float base;                       // +0x0c
    float scale;                      // +0x10
    float minv;                       // +0x14
    SP::cTerrainMapU16* heightMap;    // +0x18
    SP::cTerrainMapU16* normalMap;    // +0x1c

    bool SampleHeight(const Vec3* dir, Vec3* outPos, Vec3* outN, Quat* outQ, const Xform* xf, int);    // 0x00f73260
    bool SampleOffset(float extra, int, Vec3* pos, Vec3* outN, const Xform* xf, int);                  // 0x00f73760
    bool SampleNormal(const Vec3* dir, Vec3* outPos, Vec3* outN, Quat* outQ, const Xform* xf, int);    // 0x00f73c10
};

// @ 0x00f73260
bool cTerrainSphere::SampleHeight(const Vec3* dir, Vec3* outPos, Vec3* outN, Quat* outQ, const Xform* xf, int)
{
    Vec3 p = ForwardPoint(xf, dir->x, dir->y, dir->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);

    FaceUV uv;
    DirToCubeInto(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = (xf->pad38 + base) + (h < minv ? minv : h);
    // comiss + jb: unordered (NaN) counts as "below", i.e. the guard fires
    if (!(len >= kEps))
        return false;

    float inv = 1.0f / len;
    Vec3 n;
    n.x = inv * p.x;
    n.y = inv * p.y;
    n.z = p.z * inv;
    Vec3 nn = n;

    Vec3 out;
    out.x = n.x * radius;
    out.y = n.y * radius;
    out.z = n.z * radius;
    xf->InverseTransformPoint(&out);
    *outPos = out;

    if (outN) {
        if (xf->flags & 2)
            nn = RotateBy(xf, n);
        *outN = nn;
    }
    if (outQ) {
        Mat33 m;
        FUN_00a81b80(&nn, &m);
        Quat q;   // the helper's out-param is a stack temporary; the result is copied to *outQ
        *outQ = QuaternionFromMatrix33(&q, &m, 0.0f);
    }
    return true;
}

// @ 0x00f73760
bool cTerrainSphere::SampleOffset(float extra, int, Vec3* pos, Vec3* outN, const Xform* xf, int)
{
    Vec3 p = ForwardPoint(xf, pos->x, pos->y, pos->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);

    FaceUV uv;
    DirToCubeInto(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = ((xf->pad38 + base) + (h < minv ? minv : h)) + extra;
    // comiss + jbe: unordered (NaN) counts as "below or equal", i.e. the guard fires
    if (!(radius > len))
        return false;

    float inv = 1.0f / len;
    Vec3 out;
    out.x = (inv * p.x) * radius;
    out.y = (inv * p.y) * radius;
    out.z = (p.z * inv) * radius;

    float v4[4];
    normalMap->GetVector4(v4, &uv);
    Vec3 n;
    n.x = v4[0] * 2.0f - 1.0f;
    n.y = v4[1] * 2.0f - 1.0f;
    n.z = v4[2] * 2.0f - 1.0f;

    if (xf->scale != 1.0f || (xf->flags & 6)) {
        xf->InverseTransformPoint(&out);
        if (xf->flags & 2)
            n = RotateBy(xf, n);
    }

    *pos = out;
    *outN = n;
    return true;
}

// @ 0x00f73c10
bool cTerrainSphere::SampleNormal(const Vec3* dir, Vec3* outPos, Vec3* outN, Quat* outQ, const Xform* xf, int)
{
    Vec3 p = ForwardPoint(xf, dir->x, dir->y, dir->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);
    // comiss + jb: unordered (NaN) counts as "below", i.e. the guard fires
    if (!(len >= kEps))
        return false;

    float inv = 1.0f / len;
    Vec3 n;
    n.x = inv * p.x;
    n.y = p.y * inv;
    n.z = p.z * inv;

    FaceUV uv;
    DirToCubeInto(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = (xf->pad38 + base) + (h < minv ? minv : h);

    Vec3 out;
    out.x = n.x * radius;
    out.y = n.y * radius;
    out.z = n.z * radius;

    float v4[4];
    normalMap->GetVector4(v4, &uv);
    Vec3 nn;
    nn.x = v4[0] * 2.0f - 1.0f;
    nn.y = v4[1] * 2.0f - 1.0f;
    nn.z = v4[2] * 2.0f - 1.0f;

    xf->InverseTransformPoint(&out);
    *outPos = out;

    if (outN) {
        if (xf->flags & 2)
            nn = RotateBy(xf, nn);
        *outN = nn;
    }
    if (outQ) {
        Mat33 m;
        FUN_00a81b80(&nn, &m);
        Quat q;   // the helper's out-param is a stack temporary; the result is copied to *outQ
        *outQ = QuaternionFromMatrix33(&q, &m, 0.0f);
    }
    return true;
}
