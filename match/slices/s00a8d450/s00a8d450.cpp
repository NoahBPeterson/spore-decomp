// slice s00a8d450: EA::Swarm::cDistributeEffect::CreateSamples2D (0x00a8d450, 2639 bytes).
// For sample indices [first, last) it draws a 2D Halton point, maps it into the unit
// square (source shape 0), disc (1) or ring (2), scales/offsets it by the subdivision
// cell, optionally wraps it onto a sphere band (effect flag bit 4) or a cube-mapped
// sphere (bit 5), transforms it by the source transform, filters it through the emit
// map, pins it through the pin map and appends a cDistributeSample.
// Same module and helpers as CreateRandomSamples (s00a8e7c0); member offsets are retail.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 fsqrt).
#include "types.h"
#include <math.h>
#include <new>

// ---------------------------------------------------------------- math
struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(float _x, float _y) : x(_x), y(_y) {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// rw::math::fpu::Matrix33Template<float> (rows), out-of-line copy at 0x0041cb40
struct Matrix3 {
  Vector3 row[3];
  Matrix3(const Matrix3& m);                          // 0x0041cb40
};

// runtime-initialized math constants (.bss)
extern const Vector2 kVector2Zero;                    // 0x0167824c
extern const Vector2 kVector2One;                     // 0x01678260
extern const Matrix3 kMatrix3Identity;                // 0x01678328
extern const float kSampleColor[4];                   // 0x01678318 (default sample color)
extern float gSinCosTable[32];                        // 0x01677840 {sin, cos} per step
extern float gSinCosInvStep;                          // 0x01678278
extern float gSinCosStep;                             // 0x01678300

// Fast sine/cosine: table lookup plus a second-order correction.
static inline void FastSinCos(float a, float& s, float& c) {
  float t = a * gSinCosInvStep + 12582912.0f;
  int bits = *(int*)&t;
  float r = a - (float)(bits - 0x4b400000) * gSinCosStep;
  int i = (bits & 0xf) * 2;
  float s0 = gSinCosTable[i];
  float c0 = gSinCosTable[i + 1];
  c = c0 - (r * c0 * 0.5f + s0) * r;
  s = (c0 - r * s0 * 0.5f) * r + s0;
}

// Row-vector times rotation matrix.
static inline Vector3 Rotate(const Vector3& v, const Matrix3& m) {
  return Vector3(m.row[0].x * v.x + m.row[2].x * v.z + m.row[1].x * v.y,
                 m.row[1].y * v.y + m.row[2].y * v.z + m.row[0].y * v.x,
                 m.row[2].z * v.z + m.row[1].z * v.y + m.row[0].z * v.x);
}

namespace EA { namespace Swarm {
Vector2 SquareToCircle(Vector2 p);                    // 0x00a7c630 (cdecl, by value)
}}
namespace {
Vector2 SquareToRing(Vector2 p, float innerRadius);   // 0x00a88490 (cdecl, by value)
Vector3 CubeToSphereSurface(const Vector3& v);        // 0x00a88400
}

// ---------------------------------------------------------------- EA::Swarm types
namespace EA { namespace Swarm {

// Plain transform data (flags, mod count, offset, scale, rotation rows); copied field by field.
struct cTransformData {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  float mOffset[3];                                   // +0x04
  float mScale;                                       // +0x10
  float mRotation[9];                                 // +0x14
  void PreTransformBy(const struct cTransform& t);    // 0x00537f40
};

// cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3 mRotation;                                  // +0x14

  cTransform() : mFlags(0), mModCount(0), mRotation(kMatrix3Identity) {}
  cTransform(const cTransform& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform& operator=(const cTransform& t);         // 0x00537dc0
  void SetRotation(const Matrix3& m) {
    mRotation.row[0] = m.row[0];
    mRotation.row[1] = m.row[1];
    mRotation.row[2] = m.row[2];
    mFlags |= kRotation;
    ++mModCount;
  }
  void SetScale(float s) {
    mScale = s;
    ++mModCount;
  }
  void SetOffset(const Vector3& v) {
    mOffset.x = v.x;
    mOffset.y = v.y;
    mOffset.z = v.z;
    mFlags |= kOffset;
    ++mModCount;
  }
  __forceinline void CopyTo(cTransformData& d) const {
    d.mFlags = mFlags;
    d.mModCount = mModCount;
    d.mOffset[0] = mOffset.x;
    d.mOffset[1] = mOffset.y;
    d.mOffset[2] = mOffset.z;
    d.mScale = mScale;
    d.mRotation[0] = mRotation.row[0].x;
    d.mRotation[1] = mRotation.row[0].y;
    d.mRotation[2] = mRotation.row[0].z;
    d.mRotation[3] = mRotation.row[1].x;
    d.mRotation[4] = mRotation.row[1].y;
    d.mRotation[5] = mRotation.row[1].z;
    d.mRotation[6] = mRotation.row[2].x;
    d.mRotation[7] = mRotation.row[2].y;
    d.mRotation[8] = mRotation.row[2].z;
  }
};

// Halton sequence (bases 2,3). mIndex low byte == 0 every 256 samples.
struct cHalton2D {
  Vector2 mValue;                                     // +0x00
  int mIndex;                                         // +0x08
  int mDigits3;                                       // +0x0c
  cHalton2D() : mValue(kVector2Zero), mIndex(0), mDigits3(0) {}
  void Seed(int index);                               // 0x00a7c3d0
  int Next();                                         // 0x00a7c350
};

struct cDistributeDescription {
  uint32_t pad00[2];
  uint32_t mFlags;                                    // +0x08 (bit 13: reseed every 256)
  uint32_t pad0c[3];
  int mSeed;                                          // +0x18
  uint8_t mSourceType;                                // +0x1c (2D shape: square, circle, ring)
  uint8_t pad1d[3];
  float mScale;                                       // +0x20
  cTransform mTransform;                              // +0x24
  float mRingInnerRadius;                             // +0x5c
};

// cDistributeSample (0x4c): transform, color, sample index.
struct cDistributeSample {
  cTransformData mTransform;                          // +0x00
  float mColor[4];                                    // +0x38
  int mIndex;                                         // +0x48
  cDistributeSample() {}
  cDistributeSample(const cDistributeSample& s);      // 0x00a89de0
};

// eastl::vector<cDistributeSample, sp_vector_allocator> (retail: 0x14 bytes)
struct SampleVector {
  cDistributeSample* mpBegin;
  cDistributeSample* mpEnd;
  cDistributeSample* mpCapacity;
  uint32_t mAllocator[2];
  void DoInsertValue(cDistributeSample* position, const cDistributeSample& value);  // 0x00a8ce30
  void push_back(const cDistributeSample& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) cDistributeSample(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

struct cDistributeEffect {
  uint32_t pad00[0x14 / 4];
  cDistributeDescription* mDesc;                      // +0x014
  uint32_t pad18[(0x28 - 0x18) / 4];
  uint32_t mFlags;                                    // +0x028 (bit 4: sphere band, bit 5: cube sphere)
  cTransform mSourceTransform;                        // +0x02c
  uint32_t pad64[(0xbc - 0x64) / 4];
  SampleVector mSamples;                              // +0x0bc
  uint32_t padd0[(0x100 - 0xd0) / 4];
  Vector3 mSubdivOffset;                              // +0x100
  Vector3 mSubdivScale;                               // +0x10c
  struct cSubdivOwner { uint32_t pad[4]; cTransform* mpTransform; }* mSubdivOwner;  // +0x118
  uint32_t pad11c[(0x15c - 0x11c) / 4];
  void* mEmitMap;                                     // +0x15c
  void* mColorMap;                                    // +0x160
  void* mPinMap;                                      // +0x164
  uint32_t pad168[(0x18c - 0x168) / 4];
  float mSizeScale;                                   // +0x18c

  bool IsMaskedOut(const Vector3& pos, int index, int count);  // 0x00a89a90
  void PinToMap(Vector3& pos);                        // 0x00a89ce0
  void CreateSamples2D(int count, int first, int last);
};

// ---------------------------------------------------------------- 0x00a8d450
void cDistributeEffect::CreateSamples2D(int count, int first, int last) {
  cTransform tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;

  cTransform sampleTransform;
  sampleTransform.SetRotation(tf.mRotation);
  sampleTransform.SetScale(mSizeScale);

  cHalton2D gen;
  gen.Seed(mDesc->mSeed + first);
  bool bReseed = (mDesc->mFlags >> 13) & 1;
  for (int i = first; i < last; ++i) {
    gen.Next();
    if (bReseed && (uint8_t)gen.mIndex == 0)
      gen.Seed(mDesc->mSeed + i + 1);

    Vector2 p;
    p = gen.mValue;
    switch (mDesc->mSourceType) {
      case 0:
        p = Vector2(gen.mValue.x * 2.0f - kVector2One.x, gen.mValue.y * 2.0f - kVector2One.y);
        break;
      case 1:
        p = SquareToCircle(gen.mValue);
        break;
      case 2:
        p = SquareToRing(gen.mValue, mDesc->mRingInnerRadius);
        break;
    }

    Vector3 pos;
    pos = Vector3(mSubdivScale.x * p.x, mSubdivScale.y * p.y, mSubdivScale.z * 0.0f);
    pos.x = mSubdivOffset.x + pos.x;
    pos.y = mSubdivOffset.y + pos.y;
    pos.z = mSubdivOffset.z + pos.z;

    if (mFlags & 0x10) {
      // sphere band: z from x, longitude from y
      float z = pos.x;
      float angle = pos.y * 3.14159265f;
      float radius = sqrtf(1.0f - z * z);
      float s, c;
      FastSinCos(angle, s, c);
      pos = Vector3(c * radius, s * radius, z);
    } else if (mFlags & 0x20) {
      pos = CubeToSphereSurface(pos);
    }

    if (tf.mFlags & cTransform::kRotation)
      pos = Rotate(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = tf.mOffset.y + pos.y * tf.mScale;
    pos.z = tf.mOffset.z + pos.z * tf.mScale;

    if (mEmitMap && IsMaskedOut(pos, i, count))
      continue;
    if (mPinMap)
      PinToMap(pos);
    sampleTransform.SetOffset(pos);

    const cTransform& descTransform = mDesc->mTransform;
    cDistributeSample sample;
    if (descTransform.mScale == 1.0f &&
        !(descTransform.mFlags & (cTransform::kRotation | cTransform::kOffset))) {
      sampleTransform.CopyTo(sample.mTransform);
    } else {
      cTransformData t;
      sampleTransform.CopyTo(t);
      t.PreTransformBy(descTransform);
      sample.mTransform = t;
    }
    sample.mColor[0] = kSampleColor[0];
    sample.mColor[1] = kSampleColor[1];
    sample.mColor[2] = kSampleColor[2];
    sample.mColor[3] = kSampleColor[3];
    sample.mIndex = i;
    mSamples.push_back(sample);
  }
}

}}  // namespace EA::Swarm
