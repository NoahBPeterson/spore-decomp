// Slice s00b42760 — 0x00b42760, 2858 bytes.
//
// Support feature of a collision shape (same module as the sphere-vs-box contact of slice
// s00b3fe40).  For a box shape (mShapeType not 0/1) it finds the feature of the oriented box that
// lies furthest along -dir: the box half extents come from the shape's local bounding box
// (0x00b3f420), its center from GetCenter (0x00b3d9c0) and its axes are the rows of mAxes (+0xf8).
//   - |axis_i . dir| > 0.9999: a face; writes its 4 corners (table 0x01461158 of corner indices
//     into the unit-cube corners, a function-local static at 0x0167ec58) and returns 4;
//   - |axis_i . dir| < 0.0026: an edge along axis i; writes its 2 end points and returns 2;
//   - otherwise: the single corner, returns 1.
// For a sphere/capsule shape (type 0 or 1) it returns 1 with the point of this shape's sphere
// (center, GetRadius 0x00b3d630) towards the center of `other`.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (as s00b3fe40; scalar SSE, fabs/sqrt in x87).
//
// Notes: the unit-cube corners are the function-local static of a __forceinline helper so that
// the static and its guard are external COMDAT symbols (the difftest resolver maps them to
// 0x0167ec58 / 0x0167ecb8; a static local of this function would be a private symbol).  The
// bounding box is filled component-wise: the original builds Vector3 temporaries, but with them
// cl gives `center` the temporaries' stack slot, and GetCenter leaves `center` unwritten for an
// unknown shape kind, so the result on such (garbage) input would depend on stale stack data.
//
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
};
__forceinline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct BoundingBox {
    Vector3 lower, upper;
};

extern const int kBoxFaceCorners[6][4];     // 0x01461158: corner indices of the 6 faces (-x,+x,-y,+y,-z,+z)

// The 8 corners of the unit cube, a function-local static (0x0167ec58, guard bit 1 of 0x0167ecb8)
// of an inline helper, initialized on first use.
__forceinline const Vector3* UnitCubeCorners()
{
    static const Vector3 sCorners[8] = {
        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3(1.0f, -1.0f, -1.0f),
        Vector3(1.0f, -1.0f, 1.0f),
        Vector3(-1.0f, -1.0f, 1.0f),
        Vector3(-1.0f, 1.0f, -1.0f),
        Vector3(1.0f, 1.0f, -1.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(-1.0f, 1.0f, 1.0f),
    };
    return sCorners;
}

class CollisionShape {
public:
    uint32_t pad00[3];
    int mShapeType;             // +0x0c: 0/1 sphere-like, otherwise box
    uint32_t pad10[(0xf8 - 0x10) / 4];
    Vector3 mAxes[3];           // +0xf8: box axes (rows)

    void GetCenter(Vector3* out);                   // 0x00b3d9c0
    float GetRadius();                              // 0x00b3d630
    void AddToBoundingBox(BoundingBox* box);        // 0x00b3f420

    int GetSupportFeature(const Vector3& dir, Vector3* out, CollisionShape* other);
};

// @ 0x00b42760
int CollisionShape::GetSupportFeature(const Vector3& dir, Vector3* out, CollisionShape* other)
{
    if (mShapeType != 0 && mShapeType != 1) {
        const Vector3* kCorners = UnitCubeCorners();
        Vector3 center;

        BoundingBox box;
        box.lower.x = FLT_MAX;
        box.lower.y = FLT_MAX;
        box.lower.z = FLT_MAX;
        box.upper.x = -FLT_MAX;
        box.upper.y = -FLT_MAX;
        box.upper.z = -FLT_MAX;
        AddToBoundingBox(&box);
        Vector3 ext = (box.upper - box.lower) * 0.5f;
        float halfExt[3];
        halfExt[0] = ext.x;
        halfExt[1] = ext.y;
        halfExt[2] = ext.z;

        GetCenter(&center);

        float dots[3];
        int i;
        for (i = 0; i < 3; i++) {
            float d = Dot(mAxes[i], dir);
            dots[i] = d;
            if (fabsf(d) > 0.9999f) {
                // face
                int face;
                if (0.0f > d)
                    face = i * 2;
                else
                    face = i * 2 + 1;
                for (int k = 0; k < 4; k++) {
                    const Vector3& c = kCorners[kBoxFaceCorners[face][k]];
                    Vector3 v(-(ext.x * c.x), -(ext.y * c.y), -(ext.z * c.z));
                    out[k] = center + mAxes[0] * v.x + mAxes[1] * v.y + mAxes[2] * v.z;
                }
                return 4;
            }
        }

        for (i = 0; i < 3; i++) {
            if (fabsf(dots[i]) < 0.0026f) {
                // edge along axis i
                int j = (i + 1) % 3;
                int k = (i + 2) % 3;
                float vk = -(halfExt[k] * (0.0f > dots[k] ? -1.0f : 1.0f));
                float vj = -(halfExt[j] * (0.0f > dots[j] ? -1.0f : 1.0f));
                Vector3 p = center + mAxes[j] * vj + mAxes[k] * vk;
                Vector3 half = mAxes[i] * -halfExt[i];
                out[0] = p + half;
                out[1] = p - half;
                return 2;
            }
        }

        // corner
        float vz = -(ext.z * (0.0f > dots[2] ? -1.0f : 1.0f));
        float vy = -(ext.y * (0.0f > dots[1] ? -1.0f : 1.0f));
        float vx = -(ext.x * (0.0f > dots[0] ? -1.0f : 1.0f));
        *out = center + mAxes[0] * vx + mAxes[1] * vy + mAxes[2] * vz;
        return 1;
    }

    // sphere: the point of this sphere towards the other shape's center
    {
        Vector3 a;
        GetCenter(&a);
        Vector3 b;
        other->GetCenter(&b);
        Vector3 d = b - a;
        float invLen = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
        Vector3 n(invLen * d.x, d.y * invLen, d.z * invLen);
        float r = GetRadius();
        *out = n * r + a;
        return 1;
    }
}
