// @ 0x00f6c940   DecalBoxBuilder  (5623 bytes)
//
// __thiscall, ret 0x28 (10 stack args).  Projects a square decal centred on `pos` onto the
// six faces of a cube map (the planet texture cube):
//   1. builds an orthonormal frame around pos (side = up x pos, up2 = pos x side, fwd =
//      normalize(side x up2)) and two in-plane axes from the two base axes at 0x015b0df8 /
//      0x015b0e04, optionally spun by a random angle about the axis at 0x015b0e10 and then
//      rotated by `orient`; if the result is not facing fwd (< 0.95) the frame axes are used.
//   2. writes the decal's plane, origin (corner 0 projected onto that plane), axes and sizes.
//   3. maps the 4 corner directions to cube faces.  If all four land on one face it emits a
//      single quad for that face; otherwise it clips the corner quad against the 4 side planes
//      of every face (table 0x016d6fa8) and emits each non-empty clipped polygon.
// The per-face texel rectangle (uv bounding box) is written to rects[face] (a local scratch
// array when rects is null) and handed to EmitFace (0x00f6c600) with the projected points.

#include "types.h"
#include <math.h>
#include <float.h>

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float& operator[](int i) { return (&x)[i]; }
};

static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
static inline float Length(const Vector3& v) { return sqrtf(Dot(v, v)); }
static inline Vector3 Normalized(const Vector3& v) { return v * (1.0f / Length(v)); }

struct Quaternion { float x, y, z, w; };

struct Plane {
    Vector3 n;
    float   d;
    // Ray (origin, dir) / plane intersection; t >= 0 only.
    bool Intersect(const Vector3& origin, const Vector3& dir, float& t) const
    {
        float denom = Dot(n, dir);
        if (denom != 0.0f) {
            t = -(Dot(n, origin) + d) / denom;
            if (t >= 0.0f)
                return true;
        }
        return false;
    }
};

struct BoundingBox {
    Vector3 lo;
    Vector3 hi;
    BoundingBox() : lo(FLT_MAX, FLT_MAX, FLT_MAX),
                    hi(-FLT_MAX, -FLT_MAX, -FLT_MAX) {}
    explicit BoundingBox(const Vector3& p) : lo(p), hi(p) {}
    bool IsEmpty() const { return lo.x > hi.x; }
    void Extend(const Vector3& p);              // 0x0041bd50 (out of line)
    __forceinline void ExtendInline(const Vector3& p)       // same body, inlined in the clip loop
    {
        if (IsEmpty()) {
            lo = p;
            hi = p;
            return;
        }
        if (lo.x > p.x) lo.x = p.x;
        else if (hi.x < p.x) hi.x = p.x;
        if (lo.y > p.y) lo.y = p.y;
        else if (hi.y < p.y) hi.y = p.y;
        if (lo.z > p.z) lo.z = p.z;
        else if (hi.z < p.z) hi.z = p.z;
    }
};

// 0x1c-byte clip-polygon vertex (position + 4 floats the clipper carries along)
struct ClipVertex {
    Vector3 pos;
    float   extra[4];
};

struct Decal {                      // param_4
    char    pad00[6];
    char    noRandomSpin;           // +0x06
    char    pad07[0x2c - 7];
    Plane   plane;                  // +0x2c
    char    pad3c[4];
    Vector3 origin;                 // +0x40
    Vector3 axisU;                  // +0x4c
    float   sizeU;                  // +0x58
    Vector3 axisV;                  // +0x5c
    float   sizeV;                  // +0x68
};

struct CubeTarget {                 // param_5
    char pad00[0x60];
    u32  width;                     // +0x60
    u32  height;                    // +0x64
    u32  depth;                     // +0x68
};

struct FaceRect { float minU, minV, maxU, maxV; };

extern "C" const Vector3    DAT_015b0df8;       // base axis U
extern "C" const Vector3    DAT_015b0e04;       // base axis V
extern "C" const Vector3    DAT_015b0e10;       // random-spin axis
extern "C" const Vector3    DAT_016d6fa8[6][4]; // side-plane normals per cube face
extern "C" const u8         DAT_0148f608[6 / 2][4]; // per-axis component permutation

float   RandomRange(float lo, float hi);                       // 0x007d45d0
Vector3 FUN_0059aed0(const Vector3& v, const Quaternion& q);    // 0x0059aed0 rotate v by q
void    FUN_00fc2c70(ClipVertex* poly, int* count, const Vector3* planeNormal); // 0x00fc2c70 clip

// Cube face of a direction (0/1 = +z/-z, 2/3 = +x/-x, 4/5 = +y/-y) and its [0,1] face uv.
static __forceinline int CubeFaceUV(const Vector3& d, float& u, float& v)
{
    float ax = fabsf(d.x);
    float ay = fabsf(d.y);
    float az = fabsf(d.z);
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (d.y / d.x + 1.0f) * 0.5f;
            v = (d.z / ax + 1.0f) * 0.5f;
            return d.x < 0.0f ? 3 : 2;
        }
        u = (d.z / d.y + 1.0f) * 0.5f;
        v = (d.x / ay + 1.0f) * 0.5f;
        return d.y < 0.0f ? 5 : 4;
    }
    u = (d.x / d.z + 1.0f) * 0.5f;
    v = (d.y / az + 1.0f) * 0.5f;
    return d.z < 0.0f ? 1 : 0;
}

class DecalProjector {
public:
    void BuildDecal(const Vector3* pos, const Quaternion* orient, float size, Decal* decal,
                    CubeTarget* target, u32 arg6, u32 arg7, float spinRange, FaceRect* rects,
                    u32 arg10);
    // 0x00f6c600
    void EmitFace(CubeTarget* target, Vector3* pts, int count, int face, Decal* decal,
                  FaceRect* rect, u32 arg10, u32 arg6);
};

// @ 0x00f6c940
void DecalProjector::BuildDecal(const Vector3* pos, const Quaternion* orient, float size,
                                Decal* decal, CubeTarget* target, u32 arg6, u32 arg7,
                                float spinRange, FaceRect* rects, u32 arg10)
{
    target->width  = 0x200;
    target->height = 0x200;
    target->depth  = 0x200;

    // ---- 1. frame around pos ------------------------------------------------------------
    Vector3 n = Normalized(*pos);
    Vector3 up(0.0f, 0.0f, 1.0f);
    if (Dot(n, Vector3(0.0f, 0.0f, 1.0f)) >= 0.999f)
        up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 side = Cross(up, *pos);
    Vector3 up2  = Cross(*pos, side);
    Vector3 fwd  = Normalized(Cross(side, up2));

    Vector3 axisU = DAT_015b0df8;
    Vector3 axisV = DAT_015b0e04;
    if (decal->noRandomSpin == 0 && spinRange != 0.0f) {
        float half = RandomRange(0.0f, spinRange) * 0.017453292f * 0.5f;
        float s = sinf(half);
        Quaternion spin;
        spin.x = s * DAT_015b0e10.x;
        spin.y = s * DAT_015b0e10.y;
        spin.z = s * DAT_015b0e10.z;
        spin.w = cosf(half);
        axisU = FUN_0059aed0(DAT_015b0df8, spin);
        axisV = FUN_0059aed0(DAT_015b0e04, spin);
    }
    axisU = FUN_0059aed0(axisU, *orient);
    axisV = FUN_0059aed0(axisV, *orient);
    if (Dot(Cross(axisU, axisV), fwd) < 0.95f) {
        axisU = Normalized(side);
        axisV = Normalized(up2);
    }

    // ---- 2. corners, plane and decal frame -------------------------------------------------
    Vector3 a = axisU * size;
    Vector3 b = axisV * size;
    Vector3 corner0 = *pos - a - b;
    Vector3 dir[4];
    dir[1] = Normalized(*pos - a + b);
    dir[2] = Normalized(*pos + a + b);
    dir[3] = Normalized(*pos + a - b);
    dir[0] = Normalized(corner0);

    Plane plane;
    plane.n = n;
    plane.d = -Dot(n, *pos);
    decal->plane = plane;
    float t;
    if (decal->plane.Intersect(Vector3(0.0f, 0.0f, 0.0f), dir[0], t))
        corner0 = dir[0] * t;
    decal->origin = corner0;

    float lenU = Length(a);
    decal->sizeU = lenU * 2.0f;
    decal->axisU = a * (1.0f / lenU);
    float lenV = Length(b);
    decal->sizeV = lenV * 2.0f;
    decal->axisV = b * (1.0f / lenV);

    // ---- 3. cube faces of the four corners ---------------------------------------------------
    float u[4], v[4];
    int face1 = CubeFaceUV(dir[1], u[1], v[1]);
    int face2 = CubeFaceUV(dir[2], u[2], v[2]);
    int face3 = CubeFaceUV(dir[3], u[3], v[3]);
    int face0 = CubeFaceUV(dir[0], u[0], v[0]);

    FaceRect localRects[6];
    if (rects == 0)
        rects = localRects;

    Vector3 quad[4];
    quad[0] = dir[1];
    quad[1] = dir[2];
    quad[2] = dir[3];
    quad[3] = dir[0];

    Vector3 pts[16];
    if (face1 == face2 && face1 == face3 && face1 == face0) {
        // whole decal on one face: a single quad
        float w = (float)target->width;
        float h = (float)target->height;
        for (int i = 0; i < 4; ++i)
            pts[i] = Vector3(u[i] * w, v[i] * h, 0.0f);
        BoundingBox box(Vector3(u[1], v[1], 0.0f));
        box.Extend(Vector3(u[0], v[0], 0.0f));
        box.Extend(Vector3(u[3], v[3], 0.0f));
        box.Extend(Vector3(u[2], v[2], 0.0f));
        FaceRect* r = &rects[face1];
        r->minU = box.lo.x;
        r->minV = box.lo.y;
        r->maxU = box.hi.x;
        r->maxV = box.hi.y;
        EmitFace(target, pts, 4, face1, decal, r, arg10, arg6);
        return;
    }

    // ---- spans several faces: clip against each face's frustum ------------------------------
    for (int face = 0; face < 6; ++face) {
        ClipVertex poly[16];
        for (int i = 0; i < 4; ++i)
            poly[i].pos = quad[i];
        int count = 4;
        for (int k = 0; k < 4; ++k) {
            if (count == 0)
                break;
            FUN_00fc2c70(poly, &count, &DAT_016d6fa8[face][k]);
        }
        if (count == 0)
            continue;

        BoundingBox box;
        float sign = (face & 1) ? -1.0f : 1.0f;
        const u8* perm = DAT_0148f608[face >> 1];
        float flip[3];
        flip[0] = sign;
        flip[1] = 1.0f;
        flip[2] = sign;
        Vector3 scale(flip[perm[0]], flip[perm[1]], flip[perm[2]]);

        float w = (float)target->width;
        float h = (float)target->height;
        for (int i = 0; i < count; ++i) {
            Vector3 f;
            f[perm[0]] = poly[i].pos.x * scale.x;
            f[perm[1]] = poly[i].pos.y * scale.y;
            f[perm[2]] = poly[i].pos.z * scale.z;
            float pu = (f.x * (1.0f / f.z) + 1.0f) * 0.5f;
            float pv = (f.y * (1.0f / f.z) + 1.0f) * 0.5f;
            pts[i] = Vector3(pu * w, pv * h, 0.0f);
            box.ExtendInline(Vector3(pu, pv, 0.0f));
        }
        FaceRect* r = &rects[face];
        r->minU = box.lo.x;
        r->minV = box.lo.y;
        r->maxU = box.hi.x;
        r->maxV = box.hi.y;
        EmitFace(target, pts, count, face, decal, r, arg10, arg6);
    }
    (void)arg7;
}
