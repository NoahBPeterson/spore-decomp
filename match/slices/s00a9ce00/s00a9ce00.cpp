// Slice s00a9ce00: EA::Swarm::cParticlesEffect particle -> model transform (0x00a9ce00).
// Called per particle by StreamModelParticles (0x00a9f170, slice s00a9f170). Names are coined
// ("BuildParticleTransform"); layouts are retail (see s00a9f170): eastl::vector is 0x14 bytes, the
// description is cParticlesDescription (alignMode at +0x134, wiggles at +0x170).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for sqrt and the unsigned convert).
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// rw::math::fpu::Matrix33Template<float,0>: its copy ctor is out of line (0x41cb40).
struct Matrix33 {
  float m[3][3];
  Matrix33() {}
  Matrix33(const Matrix33& o);                          // @ 0x41cb40
};

struct Quat {
  float x, y, z, w;
};

// eastl::vector<T, sp_vector_allocator> as laid out in retail (0x14 bytes)
template <typename T>
struct CurveVector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
};
struct Wiggle {
  float f[7];
};

// runtime-initialized per-module constants (.bss)
extern const Vector3 kTransformZero;                    // 0x01678f44
extern const Matrix33 kTransformIdentity;               // 0x01679010
extern const float kDegToRad;                           // 0x01678ffc

// EA::Swarm::cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  uint16_t mFlags;                                      // +0x00
  uint16_t mModCount;                                   // +0x02
  Vector3 mOffset;                                      // +0x04
  float mScale;                                         // +0x10
  Matrix33 mRotation;                                   // +0x14
  cTransform()
      : mFlags(0), mModCount(0), mOffset(kTransformZero), mScale(1.0f),
        mRotation(kTransformIdentity) {}
  void RotateZ(float angle);                            // @ 0x007d1ac0
  void PreRotateX(float angle);                         // @ 0x005a2d90
  void RotateY(float angle);                            // @ 0x006b9050 (mixes rows 0 and 2)
};
struct cSPTransform {
  void operator=(const cTransform& t);                  // @ 0x00537dc0
};

struct cParticlesDescription {
  uint32_t pad00[3];
  uint32_t mFlags;                                      // +0x00c bit 2: particle carries an orientation quaternion
  uint32_t pad10[(0x7c - 0x10) / 4];
  float mRateCurveTime;                                 // +0x07c
  uint32_t pad80[(0x9c - 0x80) / 4];
  CurveVector<float> mRotXCurve;                        // +0x09c (PreRotateX)
  CurveVector<float> mRotYCurve;                        // +0x0b0 (RotateY)
  CurveVector<float> mRotZCurve;                        // +0x0c4 (RotateZ)
  uint32_t padD8[(0xe4 - 0xd8) / 4];
  float mRotXOffset;                                    // +0x0e4
  float mRotYOffset;                                    // +0x0e8
  float mRotZOffset;                                    // +0x0ec
  uint32_t padF0[(0x134 - 0xf0) / 4];
  uint8_t mAlignMode;                                   // +0x134 (2..4 = align an axis to the velocity)
  uint8_t pad135[3];
  uint32_t pad138[(0x170 - 0x138) / 4];
  CurveVector<Wiggle> mWiggles;                         // +0x170
  uint32_t pad184[(0x274 - 0x184) / 4];
  float mAlignLag;                                      // +0x274 (>0: smooth the spin angle)
  float mAlignSpin;                                     // +0x278
};

struct cParticle {
  uint32_t pad00[7];
  Vector3 mVelocity;                                    // +0x1c
  uint32_t pad28[(0x44 - 0x28) / 4];
  float mSpin;                                          // +0x44
  float mRotation;                                      // +0x48 (-999 = unset)
  uint32_t pad4c[(0x80 - 0x4c) / 4];
  Quat mOrientation;                                    // +0x80
  uint32_t pad90[1];
  float mRotZVary;                                      // +0x94
  float mRotXVary;                                      // +0x98
  float mRotYVary;                                      // +0x9c
};

// Callees (all cdecl)
Vector3* __cdecl RotateByQuat(Vector3* out, const Vector3* v, const Quat* q);   // @ 0x0059aed0
void __cdecl QuatToMatrix(Matrix33* out, const Quat* q);                        // @ 0x004a9b40
void __cdecl AlignAxisX(const Vector3* dir, Matrix33* out);                     // @ 0x00a81a20
void __cdecl AlignAxisY(const Vector3* dir, Matrix33* out);                     // @ 0x00a818f0
void __cdecl AlignAxisZ(const Vector3* dir, Matrix33* out);                     // @ 0x00a81b80
float __cdecl MatrixAngle(const Matrix33* m);                                   // @ 0x00a9af40
void __cdecl WigglePoint(float time, const CurveVector<Wiggle>* wiggles, const Vector3* center,
                         Vector3* pos);                                         // @ 0x00a9aff0

// Piecewise-linear curve lookup, t in [0,1].
__forceinline float EvalCurve(const CurveVector<float>& v, float t) {
  size_t n = v.size() - 1;
  if (n == 0)
    return v.mpBegin[0];
  float f = (float)n * t;
  int i = (int)f;
  float frac = f - (float)i;
  if (frac > 0.0f)
    return (v.mpBegin[i + 1] - v.mpBegin[i]) * frac + v.mpBegin[i];
  return v.mpBegin[i];
}

struct cParticlesEffect {
  uint32_t pad00[3];
  cParticlesDescription* mDesc;                         // +0x00c
  uint32_t pad10[(0x34 - 0x10) / 4];
  Vector3 mCenter;                                      // +0x034
  uint32_t pad40[(0xa0 - 0x40) / 4];
  double mOverallTime;                                  // +0x0a0

  void BuildParticleTransform(cParticle* p, float t, float size, Vector3* pos,
                              cSPTransform* out);       // @ 0x00a9ce00
};

// @ 0x00A9CE00
void cParticlesEffect::BuildParticleTransform(cParticle* p, float t, float size,
                                              Vector3* pos, cSPTransform* out) {
  cTransform tr;
  ++tr.mModCount;
  tr.mScale = size;
  cParticlesDescription* d = mDesc;
  uint8_t mode = d->mAlignMode;
  if (mode < 2 || mode > 4) {
    tr.RotateZ(p->mRotation * kDegToRad);
  } else {
    Matrix33 m(kTransformIdentity);
    Vector3 v = p->mVelocity;
    float len = (float)sqrt((v.z * v.z + v.y * v.y) + v.x * v.x);
    if (len > 0.0001f) {
      float inv = 1.0f / len;
      v.x = inv * v.x;
      v.y = v.y * inv;
      v.z = v.z * inv;
    } else {
      v.x = v.x * 10000.0f;
      v.y = v.y * 10000.0f;
      v.z = v.z * 10000.0f;
      (&v.x)[mode - 2] = (1.0f - len * 10000.0f) + (&v.x)[mode - 2];
    }
    d = mDesc;
    if ((d->mFlags >> 2) & 1) {
      Quat q;
      q.x = -p->mOrientation.x;
      q.y = -p->mOrientation.y;
      q.z = -p->mOrientation.z;
      q.w = p->mOrientation.w;
      Vector3 tmp;
      v = *RotateByQuat(&tmp, &v, &q);
    }
    switch (d->mAlignMode) {
    case 2: AlignAxisX(&v, &m); break;
    case 3: AlignAxisY(&v, &m); break;
    case 4: AlignAxisZ(&v, &m); break;
    }
    tr.mRotation = m;
    tr.mFlags |= 2;
    ++tr.mModCount;
    float lag = mDesc->mAlignLag;
    if (lag > 0.0f) {
      float cur = MatrixAngle(&m);
      float old = p->mRotation;
      float target;
      if (old == -999.0f) {
        target = cur;
      } else {
        if (old - 0.5f > cur)
          old = old - 1.0f;
        else if (cur > old + 0.5f)
          old = old + 1.0f;
        target = ((cur - old) / lag) * 0.06666667f + old;
      }
      tr.RotateZ((target - cur) * kDegToRad);
      p->mRotation = target;
    }
    d = mDesc;
    if (d->mAlignSpin != 0.0f) {
      switch (d->mAlignMode) {
      case 2: tr.PreRotateX(p->mSpin); break;
      case 3: tr.RotateY(p->mSpin); break;
      case 4: tr.RotateZ(p->mSpin); break;
      }
    }
  }
  if ((d->mFlags >> 2) & 1) {
    Matrix33 q;
    QuatToMatrix(&q, &p->mOrientation);
    Matrix33 r;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        r.m[i][j] = (tr.mRotation.m[i][0] * q.m[0][j] + tr.mRotation.m[i][1] * q.m[1][j]) +
                    tr.mRotation.m[i][2] * q.m[2][j];
    tr.mRotation = r;
    tr.mFlags |= 2;
    ++tr.mModCount;
  }
  d = mDesc;
  tr.RotateY((p->mRotYVary * EvalCurve(d->mRotYCurve, t) + d->mRotYOffset) * kDegToRad);
  d = mDesc;
  tr.PreRotateX((p->mRotXVary * EvalCurve(d->mRotXCurve, t) + d->mRotXOffset) * kDegToRad);
  d = mDesc;
  tr.RotateZ((p->mRotZVary * EvalCurve(d->mRotZCurve, t) + d->mRotZOffset) * kDegToRad);
  if (!d->mWiggles.empty())
    WigglePoint((float)(d->mRateCurveTime * mOverallTime), &d->mWiggles, &mCenter,
                pos);
  tr.mOffset.x = pos->x;
  tr.mOffset.y = pos->y;
  tr.mOffset.z = pos->z;
  tr.mFlags |= 4;
  ++tr.mModCount;
  *out = tr;
}
