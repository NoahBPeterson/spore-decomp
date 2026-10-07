// Slice s009b6b10 (batch op3_big) — 0x009b6b10, 3216 bytes.
//
// FUN_009b6b10(Vector3* pMin, Vector3* pMax, const cPartOwner* pOwner)   (__cdecl)
//
// Computes the world-space axis-aligned bounds of every oriented box in pOwner's part
// vector (element size 0x468): each box has a centre (+0x10c), an orientation quaternion
// (+0x118) and half extents (+0x138).  Four extent vectors are rotated by the quaternion and
// centre -/+ each one is merged into [*pMin, *pMax] (8 corners per box).
// No name recovered; the owner/element classes are declared with the retail offsets.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include "types.h"

#pragma pack(push, 8)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
};

struct Quaternion {
    float x, y, z, w;

    // v' = v + 2 * (rotation-matrix-minus-identity * v)
    Vector3 Rotate(const Vector3& v) const
    {
        float xw = x * w;
        float yw = y * w;
        float zw = z * w;
        float xx = -(x * x);
        float yx = y * x;
        float yy = -(y * y);
        float zx = z * x;
        float zy = z * y;
        float zz = -(z * z);
        return Vector3(((zz + yy) * v.x + (yx - zw) * v.y + (zx + yw) * v.z) * 2.0f + v.x,
                       ((zz + xx) * v.y + (yx + zw) * v.x + (zy - xw) * v.z) * 2.0f + v.y,
                       ((zx - yw) * v.x + (yy + xx) * v.z + (zy + xw) * v.y) * 2.0f + v.z);
    }
};

inline Vector3 Min(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x > b.x ? b.x : a.x, a.y > b.y ? b.y : a.y, a.z > b.z ? b.z : a.z);
}
inline Vector3 Max(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
}

inline void ExpandBounds(Vector3& vMin, Vector3& vMax, const Vector3& pt)
{
    vMin = Min(pt, vMin);
    vMax = Max(vMax, pt);
}

struct cOrientedPart {                  // 0x468 bytes
    uint32_t pad000[0x10c / 4];
    Vector3 mPosition;                  // +0x10c
    Quaternion mOrientation;            // +0x118
    uint32_t pad128[(0x138 - 0x128) / 4];
    Vector3 mHalfExtents;               // +0x138
    uint32_t pad144[(0x468 - 0x144) / 4];
};

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    const T& operator[](uint32_t i) const { return mpBegin[i]; }
};

struct cPartOwner {
    uint32_t pad000[0x384 / 4];
    vector<cOrientedPart> mParts;       // +0x384
};

static const float kMaxFloat = 3.402823466e+38F;

void FUN_009b6b10(Vector3* pMin, Vector3* pMax, const cPartOwner* pOwner)
{
    *pMin = Vector3(kMaxFloat, kMaxFloat, kMaxFloat);
    *pMax = Vector3(-kMaxFloat, -kMaxFloat, -kMaxFloat);

    for (uint32_t i = 0; i < pOwner->mParts.size(); i++) {
        const cOrientedPart& part = pOwner->mParts[i];
        const Vector3& center = part.mPosition;
        Vector3 extents = part.mHalfExtents;

        Vector3 r = part.mOrientation.Rotate(Vector3(extents.x, extents.y, extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(-extents.x, extents.y, extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(-extents.x, extents.y, -extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);

        r = part.mOrientation.Rotate(Vector3(extents.x, extents.y, -extents.z));
        ExpandBounds(*pMin, *pMax, center - r);
        ExpandBounds(*pMin, *pMax, center + r);
    }
}

#pragma pack(pop)
