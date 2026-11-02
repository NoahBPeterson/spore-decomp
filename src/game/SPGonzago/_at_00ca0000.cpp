// src/game/SPGonzago/_at_00ca0000.cpp -- migrated from slice(s) s00caded0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ca0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float kPI;                   // 0x0157D2E8
extern float kTwoPI;                // 0x0169A3F8
#include <math.h>

// ---- items of slice s00caded0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    Vector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return Vector3(x * inv, y * inv, z * inv);
    }
};
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
extern float kPI;                   // 0x0157D2E8
extern float kTwoPI;                // 0x0169A3F8
float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);            // 0x006994A0
Vector3 RotateTowards(const Vector3& from, const Vector3& to, float t);                     // 0x00B0FD00
// ---- items of slice s00caded0 end

// @ 0x00cadf50
Vector3 TurnTowards(const Vector3& from, const Vector3& to, float turnRate, float dt)
{
    Vector3 result = to;
    Vector3 axis = from.Cross(to);
    axis = axis.Normalized();
    float angle = fmodf(SignedAngle(from, to, axis), kTwoPI);
    if (angle > kPI)
        angle -= kTwoPI;
    else if (angle < -kPI)
        angle += kTwoPI;
    float mag = fabsf(angle);
    float limit = turnRate * dt;
    if (limit < mag) {
        axis = RotateTowards(from, to, limit / mag);
        result = axis;
    }
    return result;
}
