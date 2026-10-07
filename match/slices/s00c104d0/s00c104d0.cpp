// Slice s00c104d0 -- FUN_00c104d0 (0x00c104d0, 2734 bytes).
//
// Free __cdecl planet-surface helper (writes through `out`, returns nothing):
//   n   = normalize(up)                      (up is a planet-centred position)
//   dp  = (target - up) rejected from n      (tangent-plane direction to the target)
//   fp  = fwd rejected from n                (tangent-plane forward)
//   angle1 = wrapped signed angle (dp -> target-up) about normalize(dp x n)   (elevation)
//   s   = cPlanetModel::Get()->Func(up)      (0x00b7e3b0, a Vector3 by value)
//   angle2 = wrapped signed angle (fp -> fp rejected from s) about normalize(fp x n)
//   If the target lies more than 60 degrees off the forward direction (cos < 0.5), dp is
//   pulled toward fp rotated 60 degrees about n, and angle1 is blended toward angle2.
//   If |dp| < 1, dp/angle1 are blended by smoothstep(|dp|).
//   r   = dp rotated by angle1 about normalize(dp x n)
//   *out = lerp(up + r, p5, exp(t * -3.0103))
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (siblings s00c09fa0, s00c12640).
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

// Rotation of `angle` radians about the unit vector `axis`.
inline Quaternion AxisAngle(const Vector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
}

// SSE clamp helper from the original math headers (maxss then minss).
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

inline float SmoothStep(float v)
{
    v = Clamp(v, 0.0f, 1.0f);
    return (3.0f - v * 2.0f) * v * v;
}

inline Vector3 NormalizeSafe(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.LengthSq() + 1e-8f);
    return v * inv;
}

inline Vector3 Reject(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return v - n * d;
}

// ---- callees ----
Vector3 RotateVector(const Vector3& v, const Quaternion& q);                  // 0x0059aed0
float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis);   // 0x0069b760

struct cPlanetModel {
    static cPlanetModel* Get();                       // 0x00b3d350
    Vector3 SurfaceNormal(const Vector3& position);   // 0x00b7e3b0
};

extern const float kPi;     // 0x0157174c
extern float gTwoPi;        // 0x0168d960 (dynamic-initialized)

// fmod into (-pi, pi] using the module's 2*pi.
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}

// @ 0x00c104d0
void FUN_00c104d0(Vector3* out, const Vector3& up, const Vector3& fwd, const Vector3& target,
                  const Vector3& goal, float t)
{
    Vector3 u = up;
    float inv = 1.0f / sqrtf(u.LengthSq());
    Vector3 n = u * inv;
    Vector3 d = target - u;
    Vector3 dp = Reject(d, n);
    Vector3 fp = Reject(fwd, n);
    Vector3 dpN = NormalizeSafe(dp);
    float cosA = NormalizeSafe(fp).Dot(dpN);

    Vector3 side = NormalizeSafe(dp.Cross(n));
    float angle = WrapAngleMod(SignedAngle(dp, d, side));

    Vector3 surfUp = cPlanetModel::Get()->SurfaceNormal(up);
    Vector3 fpSide = NormalizeSafe(fp.Cross(n));
    float baseAngle = WrapAngleMod(SignedAngle(fp, Reject(fp, surfUp), fpSide));

    if (cosA < 0.5f) {
        float turn = WrapAngleMod(SignedAngle(fp, dpN, n));
        if (turn > 0.0f)
            turn = 1.0471976f;
        else
            turn = -1.0471976f;
        Vector3 r = RotateVector(fp, AxisAngle(n, turn));
        float w = SmoothStep((cosA + 1.0f) * 0.6666667f);
        float iw = 1.0f - w;
        dp = Vector3(r.x * w + fp.x * iw, r.y * w + fp.y * iw, r.z * w + fp.z * iw);
        dpN = NormalizeSafe(dp);
        angle = iw * baseAngle + w * angle;
    }

    float len = sqrtf(dp.LengthSq());
    if (len < 1.0f) {
        float w = SmoothStep(len);
        float iw = 1.0f - w;
        float k = iw * 3.0f;
        dp = Vector3(dpN.x * w + fp.x * k, dpN.y * w + fp.y * k, dpN.z * w + fp.z * k);
        angle = iw * baseAngle + w * angle;
    }

    Vector3 axis = NormalizeSafe(dp.Cross(n));
    Vector3 r = RotateVector(dp, AxisAngle(axis, angle));
    float f = (float)exp((double)(t * -3.0103f));
    float g = 1.0f - f;
    Vector3 p = up + r;
    out->x = goal.x * f + p.x * g;
    out->y = goal.y * f + p.y * g;
    out->z = goal.z * f + p.z * g;
}
