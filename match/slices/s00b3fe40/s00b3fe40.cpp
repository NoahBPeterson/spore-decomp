// Slice s00b3fe40: sphere vs. transformed box contact (0x00b3fe40, 3036 bytes; complete, not byte-exact).
// Transforms the sphere center into the box frame (cSPTransform: offset, scale, rotation), rejects it
// if outside the box grown by the radius, then either uses the closest point on the box surface
// (center outside) or pushes out through the nearest face plane (center inside; 4 or 6 faces), and
// writes one contact (point, normal, penetration) when the depth exceeds 1/65536.
// Declared void in the original, but each exit leaves a different value in eax (see below); the
// function is modelled as returning that residue bit-for-bit so the hidden eax matches retail.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE; sqrt/fabs chains go to x87).
#include "types.h"
#include <math.h>
#include <float.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    __forceinline Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    __forceinline Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    __forceinline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    __forceinline Vector3 operator-() const { return Vector3(-x, -y, -z); }
    __forceinline Vector3& operator*=(float s) { x = s * x; y = s * y; z = s * z; return *this; }
};
__forceinline Vector3 operator*(float s, const Vector3& v) { return Vector3(s * v.x, s * v.y, s * v.z); }
__forceinline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct Matrix3 { float m[3][3]; };
// m * v (rows) and v * m (columns).
__forceinline Vector3 operator*(const Matrix3& m, const Vector3& v)
{
    return Vector3(m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
                   m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
                   m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z);
}
__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
                   v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
                   v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]);
}

struct BoundingBox {
    Vector3 lower, upper;
    __forceinline bool Contains(const Vector3& p) const
    {
        return p.x >= lower.x && p.x <= upper.x && p.y >= lower.y && p.y <= upper.y &&
               p.z >= lower.z && p.z <= upper.z;
    }
};

struct cSPTransform {
    enum { kTransformFlagScale = 1, kTransformFlagRotation = 2, kTransformFlagOffset = 4 };
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;   // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14
};

struct Plane {
    Vector3 n;
    float d;
    Plane() {}
    __forceinline Plane(const Vector3& normal, const Vector3& point) : n(normal), d(-Dot(normal, point)) {}
    __forceinline float Distance(const Vector3& p) const { return Dot(n, p) + d; }
};

// Contact output: 16 contact points twice, a count, the normal, a float and the penetration.
struct ContactManifold {
    Vector3 mPoints[16];        // +0x000
    Vector3 mPointsB[16];       // +0x0c0
    int mCount;                 // +0x180
    Vector3 mNormal;            // +0x184
    float mf190;                // +0x190
    Vector3 mPenetration;       // +0x194
};

extern const Vector3 kBoxAxes[3];   // @ 0x167ec2c: X, Y, Z axes (runtime-initialized)

template <class T> __forceinline T Clamp(T v, T lo, T hi) { return (v < lo) ? lo : ((v > hi) ? hi : v); }
__forceinline unsigned int EaxBits(float v) { union { float f; unsigned int u; } t; t.f = v; return t.u; }

// The original is declared void, but every exit leaves a value in eax (equiv calls this
// `void_hides_eax`: the single epilogue at 0x00b40a12 ends a `mov eax,[esp+0xe8]` followed by the
// `mov [eax+...]` contact stores).  It is modelled as returning that residue bit-for-bit.
// @ 0xb3fe40
unsigned int SphereVsBoxContact(const Vector3& center, float radius, const BoundingBox& box,
                                const cSPTransform& xform, bool bAllFaces, ContactManifold* out)
{
    Vector3 p = center - xform.mTranslation;
    if (xform.mScale != 1.0f) {
        float invScale = 1.0f / xform.mScale;
        p *= invScale;
    }
    if (xform.mFlags & cSPTransform::kTransformFlagRotation)
        p = xform.mRotation * p;

    BoundingBox expanded;
    expanded.lower = Vector3(box.lower.x - radius, box.lower.y - radius, box.lower.z - radius);
    expanded.upper = Vector3(box.upper.x + radius, box.upper.y + radius, box.upper.z + radius);
    // The six rejection exits at 0x00b3ffd0..0xb40009 still hold the box pointer loaded at 0x00b3ff88.
    if (!expanded.Contains(p))
        return (unsigned int)(size_t)&box;

    Vector3 normal;
    float depth;
    unsigned int eaxResidue;
    if (!box.Contains(p)) {
        // Center outside the box: closest point on the box surface.
        Vector3 q;
        q.x = Clamp(p.x, box.lower.x, box.upper.x);
        q.y = Clamp(p.y, box.lower.y, box.upper.y);
        q.z = Clamp(p.z, box.lower.z, box.upper.z);
        eaxResidue = EaxBits(q.y);      // 0x00b400d4 `mov eax,dword ptr [esp+0x38]` (the clamped y)
        p = q;
        if (xform.mFlags & cSPTransform::kTransformFlagRotation)
            p = p * xform.mRotation;
        p = xform.mTranslation + xform.mScale * p;
        Vector3 d = p - center;
        float invLen = (float)(1.0 / sqrt((double)d.x * d.x + (double)d.y * d.y + (double)d.z * d.z + 1e-8f));
        normal = -(invLen * d);
        depth = (float)(radius - sqrt((double)d.x * d.x + (double)d.y * d.y + (double)d.z * d.z));
    } else {
        // Center inside the box: push out through the nearest face.
        Plane planes[6] = {
            Plane(-kBoxAxes[0], box.lower),
            Plane(-kBoxAxes[2], box.lower),
            Plane(kBoxAxes[2], box.upper),
            Plane(kBoxAxes[0], box.upper),
            Plane(kBoxAxes[1], box.upper),
            Plane(-kBoxAxes[1], box.lower),
        };
        float minDist = FLT_MAX;
        Plane best = planes[0];
        int numPlanes = bAllFaces ? 6 : 4;
        // The original searches planes 0..3 with a 4x-unrolled loop that finishes by leaving the index
        // (4) in eax (0x00b405bb / 0x00b406dd) and only the two leftover planes write a plane's d back
        // to eax (0x00b40727 `mov eax,dword ptr [ecx+8]`): the residue is 4 unless plane 4 or 5 wins.
        unsigned int residue = 4;
        for (int i = 0; i < numPlanes; i++) {
            float dist = (float)fabs(planes[i].Distance(p));
            if (dist < minDist) {
                minDist = dist;
                best = planes[i];
                if (i >= 4)
                    residue = EaxBits(planes[i].d);
            }
        }
        if (minDist == FLT_MAX)             // 0x00b4076e `jnp 0xb40a12`: eax is still that index
            return residue;
        p = p - best.n * radius;
        if (xform.mFlags & cSPTransform::kTransformFlagRotation)
            p = p * xform.mRotation;
        p = xform.mScale * p + xform.mTranslation;
        normal = best.n;
        if (xform.mFlags & cSPTransform::kTransformFlagRotation)
            normal = normal * xform.mRotation;
        normal = xform.mScale * normal;
        depth = minDist + radius;
        // 0x00b40795 `mov ax,word ptr [esp+0x40]` replaces the low word of eax with (mFlags & 2).
        eaxResidue = (residue & 0xFFFF0000u) | (unsigned int)(xform.mFlags & 2);
    }
    if (depth > 1.0f / 65536.0f) {
        out->mPoints[0] = p;
        out->mPointsB[0] = p;
        out->mCount = 1;
        out->mNormal = -normal;
        out->mf190 = 0.0f;
        out->mPenetration = depth * -normal;
        return (unsigned int)(size_t)out;   // 0x00b40982 `mov eax,dword ptr [esp+0xe8]`
    }
    return eaxResidue;
}
