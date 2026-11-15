// Math module (continued): Vector3 / Matrix3 helpers, a bounding box and a
// scale/rotate/translate transform that can map a bounding box.
//
// Built without optimization: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /Oi
// (frame pointer, movss float arithmetic, x87 fabs, no EH frames).
#include <math.h>
#pragma intrinsic(fabs)

// Plain three-float storage (trivially copyable: struct copies are three integer moves).
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

// Vector helpers living at 0x0041Dxxx (compiled out of line with the same flags).
Vector3 operator-(const Vec3Data& a, const Vec3Data& b);    // 0x0041DB10
Vector3 operator+(const Vec3Data& a, const Vec3Data& b);    // 0x0041DC10
Vector3 operator*(const Vec3Data& a, const float& s);      // 0x0041DCA0
Vector3 operator*(const float& s, const Vec3Data& a);      // 0x0041DE40
Vec3Data& operator*=(Vec3Data& a, const float& s);          // 0x0041DBA0
Vec3Data& operator+=(Vec3Data& a, const Vec3Data& b);        // 0x0041DDB0
Vector3 operator*(const Vec3Data& v, const Matrix3& m);    // 0x0041DAF0 (calls 0x00423160)

extern Matrix3 g_IdentityMatrix;  // 0x015D1434
extern Vector3 g_ZeroVector;      // 0x015D1564
extern const float kFloatMax;     // 0x013EB258

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

// Plain 3x3 float storage (no constructors), used for scratch copies.
struct Matrix3Raw { float f[9]; };
Vector3 operator*(const Vec3Data& v, const Matrix3Raw& m);   // 0x0041DAF0
void Matrix3_Abs(const Matrix3& in, Matrix3Raw& out);       // 0x0040A0F0 (same function, raw destination)
void Matrix3_Abs(const Matrix3& in, Matrix3& out);          // 0x0040A0F0

// @ 0x004098A0  (nonmatching stand-in, see nonmatching.txt: the real Vector3 copy
// constructor is emitted out of line while every other copy is inlined)
struct Vector3Copyable {
    float x, y, z;
    Vector3Copyable(const Vector3Copyable& o);
};
Vector3Copyable::Vector3Copyable(const Vector3Copyable& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
}

// @ 0x004098E0
Vector3& MulMatrixAssign(Vector3& dst, const Matrix3& m)
{
    dst = dst * m;
    return dst;
}

// @ 0x00409930
Transform::Transform()
    : mFlags(0), mVersion(0), mPos(g_ZeroVector), mScale(1.0f), mRot(g_IdentityMatrix)
{
}

// @ 0x004099B0
void Transform::RotateY(float angle)
{
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    Vector3 r0 = mRot[0];
    Vector3 r1 = mRot[1];
    mRot[0] = c * r0 + s * r1;
    mRot[1] = (-s) * r0 + c * r1;
    mFlags |= 2;
    mVersion++;
}

// @ 0x00409B30
void Transform::Scale(float s)
{
    mScale *= s;
    mPos *= s;
    mFlags |= 1;
    mVersion++;
}

// @ 0x00409B90
Vector3& BoundingBox::GetCenter(Vector3& out) const
{
    out = (min + max) * 0.5f;
    return out;
}

// @ 0x00409C00
void BoundingBox::Reset()
{
    min = Vector3(kFloatMax, kFloatMax, kFloatMax);
    max = Vector3(-kFloatMax, -kFloatMax, -kFloatMax);
}

// @ 0x00409CE0
void BoundingBox::SetCenterRadius(const Vector3& center, float r)
{
    min[0] = center[0] - r;
    min[1] = center[1] - r;
    min[2] = center[2] - r;
    max[0] = center[0] + r;
    max[1] = center[1] + r;
    max[2] = center[2] + r;
}

// @ 0x00409DD0
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

// @ 0x0040A0F0
void Matrix3_Abs(const Matrix3& in, Matrix3& out)
{
    const Vec3Data& sr = in[0];
    const float* s = &sr[0];
    Vec3Data& dr = out[0];
    float* d = &dr[0];
    for (int i = 0; i < 9; i++)
        d[i] = Abs(s[i]);
}
