// src/game/SPGonzago/SPGonzagoPhysics.cpp -- migrated from slice(s) s004098a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoPhysics.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPBoundingBox.h"
#include "cSPVector3.h"
#include <math.h>
#pragma intrinsic(fabs)

// ---- items of slice s004098a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3Data {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3 : Vec3Data {
    Vector3() {}
    Vector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    Vector3(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Matrix3 {
    Vec3Data m[3];
    Matrix3() {}
    Matrix3(const Matrix3& o);  // 0x0041CB40
    Vec3Data& operator[](int i) { return m[i]; }
    const Vec3Data& operator[](int i) const { return m[i]; }
};
Vector3 operator-(const Vec3Data& a, const Vec3Data& b);    // 0x0041DB10
Vector3 operator+(const Vec3Data& a, const Vec3Data& b);    // 0x0041DC10
Vector3 operator*(const Vec3Data& a, const float& s);      // 0x0041DCA0
Vector3 operator*(const float& s, const Vec3Data& a);      // 0x0041DE40
Vec3Data& operator*=(Vec3Data& a, const float& s);          // 0x0041DBA0
Vec3Data& operator+=(Vec3Data& a, const Vec3Data& b);        // 0x0041DDB0
Vector3 operator*(const Vec3Data& v, const Matrix3& m);    // 0x0041DAF0 (calls 0x00423160)
inline float Abs(float v) { return (float)fabs(v); }
struct BoundingBox {
    Vec3Data min;
    Vec3Data max;
    void Reset();                                    // 0x00409C00
    void SetCenterRadius(const Vector3& center, float r);  // 0x00409CE0
    Vector3& GetCenter(Vector3& out) const;          // 0x00409B90
    void TransformBy(const struct Transform& t);     // 0x00409DD0
};
struct Transform {
    unsigned short mFlags;    // bit0 = scaled, bit1 = rotated
    unsigned short mVersion;  // bumped on every change
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    Transform();                                // 0x00409930
    void RotateY(float angle);                  // 0x004099B0
    void Scale(float s);                        // 0x00409B30
    float GetScale() const { return mScale; }
    bool IsRotated() const { return (mFlags & 2) != 0; }
};
struct Matrix3Raw { float f[9]; };
Vector3 operator*(const Vec3Data& v, const Matrix3Raw& m);   // 0x0041DAF0
void Matrix3_Abs(const Matrix3& in, Matrix3Raw& out);       // 0x0040A0F0 (same function, raw destination)
void Matrix3_Abs(const Matrix3& in, Matrix3& out);          // 0x0040A0F0
// ---- items of slice s004098a0 end

// @ 0x00409dd0
void BoundingBox::TransformBy(const Transform& t)
{
    if (t.IsRotated()) {
        Vector3 extent;
        extent = max - min;
        Vector3 sum;
        sum = max + min;
        float half = t.GetScale() * 0.5f;
        Matrix3Raw absRot;
        Matrix3_Abs(t.mRot, absRot);
        extent *= half;
        extent = extent * absRot;
        sum *= half;
        sum = sum * t.mRot;
        sum += t.mPos;
        min = sum - extent;
        max = sum + extent;
    } else {
        min *= t.GetScale();
        min += t.mPos;
        max *= t.GetScale();
        max += t.mPos;
    }
}

// @ 0x0040a0f0
void Matrix3_Abs(const Matrix3& in, Matrix3& out)
{
    const Vec3Data& sr = in[0];
    const float* s = &sr[0];
    Vec3Data& dr = out[0];
    float* d = &dr[0];
    for (int i = 0; i < 9; i++)
        d[i] = Abs(s[i]);
}
