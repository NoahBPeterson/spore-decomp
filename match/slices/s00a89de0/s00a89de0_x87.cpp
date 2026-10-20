// Slice s00a89de0 -- EA::Swarm::cTransform::PostTransformBy (0x00a8a140).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast /arch:SSE
// Scalar SSE (movss/mulss/addss) with `movaps xmm,xmm` register copies, as in the original.
#include "types.h"

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Matrix3 {
  float m[3][3];
  Matrix3() {}
};

// rw::math::fpu::Vector3Template<float,0> operator*(const float&, const Vector3&) (0x0041de40)
static __forceinline Vector3 Scale(const float& s, const Vector3& v)
{
  Vector3 out;
  out.x = s * v.x;
  out.y = s * v.y;
  out.z = s * v.z;
  return out;
}

// rw::math::fpu::Vector3Template<float,0> operator*(const Vector3&, const Matrix33Template&) (0x0041daf0)
static __forceinline Vector3 Rot(const Vector3& v, const Matrix3& m)
{
  Vector3 out;
  out.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
  out.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
  out.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
  return out;
}

// Matrix33Template operator*(const Matrix33Template&, const Matrix33Template&) (0x0041de20)
static __forceinline Matrix3 Mul(const Matrix3& a, const Matrix3& b)
{
  Matrix3 out;
  for (int i = 0; i < 3; ++i) {
    out.m[i][0] = a.m[i][0] * b.m[0][0] + a.m[i][1] * b.m[1][0] + a.m[i][2] * b.m[2][0];
    out.m[i][1] = a.m[i][0] * b.m[0][1] + a.m[i][1] * b.m[1][1] + a.m[i][2] * b.m[2][1];
    out.m[i][2] = a.m[i][0] * b.m[0][2] + a.m[i][1] * b.m[1][2] + a.m[i][2] * b.m[2][2];
  }
  return out;
}

// 0x38 bytes: flags, modification count, translation, scale, rotation.
struct cTransform {
  uint16_t mFlags;       // +0x00
  uint16_t mModCount;    // +0x02
  Vector3  mTranslation; // +0x04
  float    mScale;       // +0x10
  Matrix3  mRotation;    // +0x14

  cTransform& PostTransformBy(const cTransform& b);
};

// @ 0x00a8a140
cTransform& cTransform::PostTransformBy(const cTransform& b)
{
  mTranslation = Scale(b.mScale, mTranslation);
  mTranslation = Rot(mTranslation, b.mRotation);
  mTranslation.x += b.mTranslation.x;
  mTranslation.y += b.mTranslation.y;
  mTranslation.z += b.mTranslation.z;
  mRotation = Mul(mRotation, b.mRotation);
  mScale = mScale * b.mScale;
  mFlags |= b.mFlags;
  ++mModCount;
  return *this;
}
