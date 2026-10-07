// Slice s00b922c0 -- FUN_00b922c0: marks the planet's cube-map grid cells covered by a path.
// For each segment of a polyline (eastl::vector<Vector3>) it walks the segment in grid-cell steps
// and, at each step, flags the cell under the point plus the cells on both sides up to `width`
// (side direction = the planet-space "right" axis rotated into the segment's facing frame).
// The end point of each segment and its side cells are flagged as well.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (float->int is an inline cvttss2si helper;
// sqrt/fabs are the double intrinsics, which /fp:fast keeps on the x87 stack).
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

__forceinline int FloatToInt(float f) { __asm cvttss2si eax, f }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3 Normalized() const {
        float inv = (float)(1.0f / sqrt(x * x + y * y + z * z + 1e-08f));
        return Vector3(x * inv, y * inv, z * inv);
    }
};
struct Quaternion { float x, y, z, w; };

namespace eastl {
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
};
}

Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up);   // 0x0069b600
Vector3 QuatRotate(const Vector3& v, const Quaternion& q);                         // 0x0059aed0
extern const Vector3 kPlanetSideAxis;   // 0x01688900

// planet cube-map grid (0x0156c080)
struct cGridCell {          // 12 bytes
    uint32_t pad0;
    uint32_t mFlags;        // +0x04
    uint32_t pad8;
};
extern int g_PlanetGridSize;            // 0x0156c084
extern cGridCell* g_PlanetGridCells;    // 0x0156c094
extern float g_PlanetGridScale;         // 0x0156c0ac

// Cube-map projection: dominant axis picks the face, the other two give (u, v).
__forceinline cGridCell* GetGridCell(const Vector3& p)
{
    float ax = (float)fabs(p.x);
    float ay = (float)fabs(p.y);
    float half = (float)g_PlanetGridSize * 0.5f;
    float az = (float)fabs(p.z);
    int u, v, face;
    if (az >= ax && az >= ay) {
        u = FloatToInt((p.x / p.z + 1.0f) * half);
        v = FloatToInt((p.y / az + 1.0f) * half);
        face = (p.z < 0.0f) ? 1 : 0;
    } else if (ay >= ax) {
        u = FloatToInt((p.z / p.y + 1.0f) * half);
        v = FloatToInt((p.x / ay + 1.0f) * half);
        face = (p.y < 0.0f) ? 5 : 4;
    } else {
        u = FloatToInt((p.y / p.x + 1.0f) * half);
        v = FloatToInt((p.z / ax + 1.0f) * half);
        face = (p.x < 0.0f) ? 3 : 2;
    }
    if (u == g_PlanetGridSize) u--;
    if (v == g_PlanetGridSize) v--;
    return &g_PlanetGridCells[(face * g_PlanetGridSize + v) * g_PlanetGridSize + u];
}

__forceinline void MarkCell(const Vector3& p) { GetGridCell(p)->mFlags |= 0xf0; }

// 0x00b922c0
void FUN_00b922c0(eastl::vector<Vector3>* path, float width)
{
    Vector3* it = path->mpBegin;
    Vector3* end = path->mpEnd;
    if (it == end) return;
    float step = g_PlanetGridScale / (float)g_PlanetGridSize;
    for (Vector3* next = it + 1; next != end; it = next, ++next) {
        Vector3 a(*it);
        Vector3 diff = *next - a;
        float len = diff.Length();
        Vector3 dir(diff);
        if (len > 1.5258789e-05f) {
            dir *= 1.0f / len;
            Quaternion q = QuaternionFromFacingAndUp(dir, a.Normalized());
            Vector3 side = QuatRotate(kPlanetSideAxis, q).Normalized();

            for (float t = 0.0f; t < len; t += step) {
                Vector3 c = *it + dir * t;
                MarkCell(c);
                for (float w = step; w < width; w += step) {
                    Vector3 off = side * w;
                    MarkCell(off + c);
                    MarkCell(c - off);
                }
            }

            MarkCell(*next);
            for (float w = step; w < width; w += step) {
                Vector3 off = side * w;
                MarkCell(off + *next);
                MarkCell(*next - off);
            }
        }
    }
}
