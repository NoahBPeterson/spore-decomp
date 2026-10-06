// slice s00a9f170: Swarm particle effect, stream every live particle to its model
// (0x00a9f170). Class and method names are coined ("cParticlesEffect::
// StreamModelParticles"); retail layout differs from the 2008 PDB, field roles are
// from usage. Particle fields follow EA::Swarm::cParticle (age, life, position,
// size, alpha, color) with a retail model pointer at +0x7c; description fields
// follow EA::Swarm::cParticlesDescription (size/color/alpha curves, loop box
// colour/alpha curves, screen-bloom bytes) at retail offsets.
//
// Per particle: optional screw twist around the effect centre, size curve,
// particle transform (0x00a9ce00), then for a loaded model: colour and alpha from
// curves, optional loop-box wrap (position folded into the box, colour/alpha from
// the loop-box curves), optional screen-edge bloom, and the model parameter /
// transform / draw calls.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for sqrt/fabs).
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)  // asm helpers return in eax / via memory

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Matrix3 {
  Vector3 row[3];
};

// rw::math 4x4 (row-vector convention, translation in row 3)
struct Matrix4 {
  float m[4][4];
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

// runtime-initialized per-module constants (.bss)
extern const Vector3 kTransformZero;                  // 0x01678f44
extern const Matrix3 kTransformIdentity;              // 0x01679010
extern float gSinCosTable[32];                        // 0x01677840 {sin, cos} per step
extern float gSinCosInvStep;                          // 0x01678f38
extern float gSinCosStep;                             // 0x01678fe8

// Fast sine/cosine: table lookup plus a second-order correction.
static inline void FastSinCos(float a, float& s, float& c) {
  float t = a * gSinCosInvStep + 12582912.0f;
  int bits = *(int*)&t;
  float r = a - (float)(bits - 0x4b400000) * gSinCosStep;
  int i = (bits & 0xf) * 2;
  float s0 = gSinCosTable[i];
  float c0 = gSinCosTable[i + 1];
  c = c0 - (c0 * r * 0.5f + s0) * r;
  s = (c0 - s0 * r * 0.5f) * r + s0;
}

// EA math helpers, hand-written SSE in the original.
__forceinline int FloorToInt(float f) {
  __asm {
    movss    xmm0, f
    cvtss2si eax, xmm0
    cvtsi2ss xmm1, eax
    mov      ecx, eax
    sub      ecx, 1
    ucomiss  xmm0, xmm1
    cmovb    eax, ecx
  }
}

__forceinline float Clamp01(float x) {
  float one = 1.0f;
  __asm {
    xorps xmm0, xmm0
    maxss xmm0, x
    minss xmm0, one
    movss x, xmm0
  }
  return x;
}

inline const float& Min(const float& a, const float& b) { return (a < b) ? a : b; }
inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }

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

// Vector curve lookup with a precomputed last index.
__forceinline Vector3 EvalCurve(const CurveVector<Vector3>& v, size_t n, float t) {
  Vector3 r;
  if (n == 0) {
    r = v.mpBegin[0];
  } else {
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    const Vector3* p = v.mpBegin + i;
    if (frac > 0.0f) {
      r.x = (p[1].x - p[0].x) * frac + p[0].x;
      r.y = p[0].y + (p[1].y - p[0].y) * frac;
      r.z = p[0].z + (p[1].z - p[0].z) * frac;
    } else {
      r = p[0];
    }
  }
  return r;
}

namespace EA { namespace Swarm {

// cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3 mRotation;                                  // +0x14
  cTransform()
      : mFlags(0), mModCount(0), mOffset(kTransformZero), mScale(1.0f),
        mRotation(kTransformIdentity) {}
};

struct cParticlesDescription {
  uint32_t pad00[3];
  uint32_t mFlags;                                    // +0x00c bit0 radial screw, bit1 loop box
  uint32_t pad10[(0x84 - 0x10) / 4];
  CurveVector<float> mSizeCurve;                      // +0x084
  uint32_t pad98[(0xf0 - 0x98) / 4];
  CurveVector<Vector3> mColorCurve;                   // +0x0f0
  uint32_t pad104[(0x110 - 0x104) / 4];
  CurveVector<float> mAlphaCurve;                     // +0x110
  uint32_t pad124[(0x12c - 0x124) / 4];
  int mDrawCount;                                     // +0x12c
  uint32_t pad130[(0x16c - 0x130) / 4];
  float mScrewRate;                                   // +0x16c
  uint32_t pad170[(0x184 - 0x170) / 4];
  uint8_t mScreenBloomAlphaRate;                      // +0x184
  uint8_t mScreenBloomAlphaBase;                      // +0x185
  uint8_t mScreenBloomSizeRate;                       // +0x186
  uint8_t mScreenBloomSizeBase;                       // +0x187
  CurveVector<Vector3> mLoopBoxColorCurve;            // +0x188
  CurveVector<float> mLoopBoxAlphaCurve;              // +0x19c
};

struct cModelParticle {
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual bool IsReady();                                             // +0x10
  virtual void Draw(float a, float b, struct cStreamContext* ctx);    // +0x14
  virtual void SetTransform(const cTransform& t, const cTransform& parent);  // +0x18
  virtual void SetParam(int id, const float* values, int count);     // +0x1c
};

struct cStreamContext {
  uint32_t pad[2];
  int mDrawn;                                         // +0x08
};

struct cParticle {
  cParticle* mpNext;                                  // +0x00
  cParticle* mpPrev;                                  // +0x04
  float mAge;                                         // +0x08
  float mLife;                                        // +0x0c
  Vector3 mPosition;                                  // +0x10
  Vector3 mVelocity;                                  // +0x1c
  float mOverallSize;                                 // +0x28
  float mOverallAspect;                               // +0x2c
  float mOverallRotation;                             // +0x30
  float mOverallAlpha;                                // +0x34
  Vector3 mOverallColor;                              // +0x38
  uint32_t pad44[(0x7c - 0x44) / 4];
  cModelParticle* mpModel;                            // +0x7c
};

struct cCamera {
  uint32_t pad[0x1c / 4];
  Matrix4 mViewProjection;                            // +0x1c
};

struct ListNode {
  cParticle* mpNext;
  cParticle* mpPrev;
};

struct cParticlesEffect {
  uint32_t pad00[3];
  cParticlesDescription* mDesc;                       // +0x00c
  uint32_t pad10[2];
  cCamera* mpCamera;                                  // +0x018
  uint32_t pad1c[2];
  ListNode mParticles;                                // +0x024 intrusive list anchor
  uint32_t pad2c[2];
  Vector3 mCenter;                                    // +0x034
  uint32_t pad40[4];
  Vector3 mLoopBoxGradient;                           // +0x050
  uint32_t pad5c[3];
  cTransform mTransform;                              // +0x068
  uint32_t padA0[(0x180 - 0xa0) / 4];
  float mSizeScale;                                   // +0x180
  float mAlphaScale;                                  // +0x184
  Vector3 mColorScale;                                // +0x188
  uint32_t pad194[(0x1a4 - 0x194) / 4];
  Vector3 mLoopBoxMin;                                // +0x1a4
  Vector3 mLoopBoxMax;                                // +0x1b0

  void BuildParticleTransform(cParticle* p, float t, float size, const Vector3* pos,
                              cTransform* out);       // 0x00a9ce00
  void StreamModelParticles(float a, float b, cStreamContext* ctx);
};

// ---------------------------------------------------------------- 0x00a9f170
void cParticlesEffect::StreamModelParticles(float a, float b, cStreamContext* ctx) {
  // screen-bloom factors (bytes scaled to [0,1] / [0,16])
  float alphaBase, alphaRate, sizeBase, sizeRate;
  if (mDesc->mScreenBloomAlphaRate | mDesc->mScreenBloomSizeRate) {
    alphaBase = (float)mDesc->mScreenBloomAlphaBase * (1.0f / 255.0f);
    alphaRate = (float)mDesc->mScreenBloomAlphaRate * (16.0f / 255.0f);
    sizeBase = (float)mDesc->mScreenBloomSizeBase * (1.0f / 255.0f);
    sizeRate = (float)mDesc->mScreenBloomSizeRate * (16.0f / 255.0f);
  }

  const size_t colorLast = mDesc->mColorCurve.size() - 1;
  for (cParticle* p = mParticles.mpNext; p != (cParticle*)&mParticles; p = p->mpNext) {
    // screw twist around the effect centre
    float screw = mDesc->mScrewRate;
    Vector3 pos = p->mPosition;
    if (screw != 0.0f) {
      float dx = pos.x - mCenter.x;
      float dy = pos.y - mCenter.y;
      float dz = pos.z - mCenter.z;
      float angle;
      if (mDesc->mFlags & 1)
        angle = sqrtf(dx * dx + dy * dy) * screw;
      else
        angle = screw * dz;
      float s, c;
      FastSinCos(angle, s, c);
      pos.x = dx * c - dy * s + mCenter.x;
      pos.y = dy * c + dx * s + mCenter.y;
    }

    float t = p->mAge / p->mLife;
    float sizeCurve = EvalCurve(mDesc->mSizeCurve, t);
    cTransform transform;
    BuildParticleTransform(p, t, p->mOverallSize * mSizeScale * sizeCurve, &pos, &transform);

    cModelParticle* model = p->mpModel;
    if (!model || !model->IsReady())
      continue;

    Vector3 colorCurve = EvalCurve(mDesc->mColorCurve, colorLast, t);
    Vector3 color;
    color.x = p->mOverallColor.x * colorCurve.x * mColorScale.x;
    color.y = mColorScale.y * (p->mOverallColor.y * colorCurve.y);
    color.z = mColorScale.z * (p->mOverallColor.z * colorCurve.z);
    float alpha = mAlphaScale * p->mOverallAlpha * EvalCurve(mDesc->mAlphaCurve, t);

    if (mDesc->mFlags & 2) {
      // fold the position into the loop box
      Vector3 rel;
      rel.x = transform.mOffset.x - mCenter.x - mLoopBoxMin.x;
      rel.y = transform.mOffset.y - mCenter.y - mLoopBoxMin.y;
      rel.z = transform.mOffset.z - mCenter.z - mLoopBoxMin.z;
      Vector3 g;
      g.x = rel.x / (mLoopBoxMax.x - mLoopBoxMin.x);
      g.y = rel.y / (mLoopBoxMax.y - mLoopBoxMin.y);
      g.z = rel.z / (mLoopBoxMax.z - mLoopBoxMin.z);
      float fx = g.x - (float)FloorToInt(g.x);
      float fy = g.y - (float)FloorToInt(g.y);
      float fz = g.z - (float)FloorToInt(g.z);
      float d = mLoopBoxGradient.z * (fz - 0.5f) + mLoopBoxGradient.y * (fy - 0.5f) +
                mLoopBoxGradient.x * (fx - 0.5f) + 0.5f;
      d = Clamp01(d);
      if (!mDesc->mLoopBoxColorCurve.empty()) {
        Vector3 boxColor = EvalCurve(mDesc->mLoopBoxColorCurve,
                                     mDesc->mLoopBoxColorCurve.size() - 1, d);
        color.x = boxColor.x * color.x;
        color.y = boxColor.y * color.y;
        color.z = boxColor.z * color.z;
      }
      if (!mDesc->mLoopBoxAlphaCurve.empty())
        alpha = EvalCurve(mDesc->mLoopBoxAlphaCurve, d) * alpha;
      Vector3 boxPos;
      boxPos.x = (mLoopBoxMax.x - mLoopBoxMin.x) * fx + mLoopBoxMin.x;
      boxPos.y = (mLoopBoxMax.y - mLoopBoxMin.y) * fy + mLoopBoxMin.y;
      boxPos.z = (mLoopBoxMax.z - mLoopBoxMin.z) * fz + mLoopBoxMin.z;
      transform.mOffset.x = boxPos.x + mCenter.x;
      transform.mOffset.y = mCenter.y + boxPos.y;
      transform.mOffset.z = mCenter.z + boxPos.z;
      transform.mFlags |= cTransform::kOffset;
      transform.mModCount += 1;
    }

    if (mDesc->mScreenBloomSizeRate | mDesc->mScreenBloomAlphaRate) {
      // screen-space distance from the view edge
      Vector3 w = transform.mOffset;
      if (mTransform.mFlags & cTransform::kRotation) {
        Vector3 r;
        r.x = mTransform.mRotation.row[2].x * w.z + mTransform.mRotation.row[1].x * w.y +
              w.x * mTransform.mRotation.row[0].x;
        r.y = mTransform.mRotation.row[2].y * w.z + mTransform.mRotation.row[1].y * w.y +
              mTransform.mRotation.row[0].y * w.x;
        r.z = mTransform.mRotation.row[2].z * w.z + mTransform.mRotation.row[1].z * w.y +
              mTransform.mRotation.row[0].z * w.x;
        w = r;
      }
      w.x = w.x * mTransform.mScale + mTransform.mOffset.x;
      w.y = mTransform.mOffset.y + w.y * mTransform.mScale;
      w.z = mTransform.mOffset.z + w.z * mTransform.mScale;
      const Matrix4& m = mpCamera->mViewProjection;
      float invW = 1.0f / (m.m[2][3] * w.z + m.m[1][3] * w.y + m.m[0][3] * w.x + m.m[3][3]);
      float sy = invW * (m.m[2][1] * w.z + m.m[1][1] * w.y + m.m[0][1] * w.x + m.m[3][1]);
      float sx = invW * (m.m[2][0] * w.z + m.m[1][0] * w.y + w.x * m.m[0][0] + m.m[3][0]);
      float ay = fabsf(sy);
      float ax = fabsf(sx);
      float edge = 1.0f - Max(ay, ax);
      if (edge > 0.0f) {
        float one = 1.0f;
        float alphaFactor = edge * alphaRate + alphaBase;
        alpha = Min(alphaFactor, one) * alpha;
        float one2 = 1.0f;
        float sizeFactor = edge * sizeRate + sizeBase;
        transform.mScale = transform.mScale * Min(sizeFactor, one2);
      } else {
        alpha = alpha * alphaBase;
        transform.mScale = transform.mScale * sizeBase;
      }
      transform.mFlags |= cTransform::kScale;
      transform.mModCount += 1;
    }

    model->SetParam(4, &alpha, 1);
    model->SetParam(5, &color.x, 3);
    model->SetTransform(transform, mTransform);
    if (mDesc->mDrawCount >= 1) {
      model->Draw(a, b, ctx);
      ctx->mDrawn++;
    }
  }
}

}}  // namespace EA::Swarm
