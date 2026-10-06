// slice s00a8e7c0: EA::Swarm::cDistributeEffect, quasi-random sample creation
// (0x00a8e7c0). Name of the method coined here ("CreateRandomSamples"); it sits
// between CreateSamples2D (0x00a8dea0) and CreateClusteredSamples2D (0x00a8f6a0).
// For sample indices [first, last) it draws a Halton point, maps it into the
// emitter volume (sphere band for source types 3 and 6, cube / cube-mapped
// sphere for 4 and 5), transforms it by the source transform, filters it through
// the emit map, pins it through the pin map and appends a cDistributeSample.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 fsqrt).
#include "types.h"
#include <math.h>
#include <new>

// ---------------------------------------------------------------- math
struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};

struct Vector3 {
  float x, y, z;
  Vector3() {}
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
extern const Vector3 kVector3One;                     // 0x01678230
extern const Vector3 kVector3Zero;                    // 0x0167827c
extern const Matrix3 kMatrix3Identity;                // 0x01678328
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
  c = c0 - (c0 * r * 0.5f + s0) * r;
  s = (c0 - s0 * r * 0.5f) * r + s0;
}

// Row-vector times rotation matrix.
static inline Vector3 Rotate(const Vector3& v, const Matrix3& m) {
  Vector3 out;
  out.x = v.x * m.row[0].x + v.y * m.row[1].x + v.z * m.row[2].x;
  out.y = v.x * m.row[0].y + v.y * m.row[1].y + v.z * m.row[2].y;
  out.z = v.x * m.row[0].z + v.y * m.row[1].z + v.z * m.row[2].z;
  return out;
}

Vector3 CubeToSphere(Vector3 v);                      // 0x00a7c860 (cdecl, by value)

// ---------------------------------------------------------------- EA::Swarm types
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
      : mFlags(0), mModCount(0), mOffset(kVector3Zero), mScale(1.0f),
        mRotation(kMatrix3Identity) {}
  cTransform(const cTransform& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform& operator=(const cTransform& t);         // 0x00537dc0
  // retail: rotation and offset setters bump the modification count
  void SetRotation(const Matrix3& m) {
    mRotation = m;
    mFlags |= kRotation;
    ++mModCount;
  }
  void SetScale(float s) {
    mScale = s;
    ++mModCount;
  }
  void SetOffset(const Vector3& v) {
    mOffset = v;
    mFlags |= kOffset;
    ++mModCount;
  }
  void PreTransformBy(const cTransform& t);           // 0x00537f40
};

// Halton sequences (bases 2,3 and 2,3,5). mIndex low byte == 0 every 256 samples.
struct cHalton2D {
  Vector2 mValue;                                     // +0x00
  int mIndex;                                         // +0x08
  int mDigits3;                                       // +0x0c
  cHalton2D() : mValue(kVector2Zero), mIndex(0), mDigits3(0) {}
  void Seed(int index);                               // 0x00a7c3d0
  int Next();                                         // 0x00a7c350
};

struct cHalton3D {
  Vector3 mValue;                                     // +0x00
  int mIndex;                                         // +0x0c
  int mDigits3;                                       // +0x10
  int mDigits5;                                       // +0x14
  cHalton3D() : mValue(kVector3Zero), mIndex(0), mDigits3(0), mDigits5(0) {}
  void Seed(int index);                               // 0x00a7c540
  int Next();                                         // 0x00a7c450
};

struct cDistributeDescription {
  uint32_t pad00[2];
  uint32_t mFlags;                                    // +0x08 (bit 13: reseed every 256)
  uint32_t pad0c[3];
  int mSeed;                                          // +0x18
  uint8_t mSourceType;                                // +0x1c
  uint8_t pad1d[3];
  float mScale;                                       // +0x20
  cTransform mTransform;                              // +0x24
};

// cDistributeSample (0x4c)
struct cDistributeSample {
  uint32_t data[0x4c / 4];
  cDistributeSample(const cTransform& t, int index);  // 0x00a89980
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
  uint32_t pad18[(0x2c - 0x18) / 4];
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
  void CreateRandomSamples(int count, int first, int last);
  inline void AddSample(cTransform& sampleTransform, Vector3& pos, int index, int count);
  inline void CreateSphereSamples(const cTransform& tf, cTransform& sampleTransform,
                                  bool bReseed, int count, int first, int last);
};

// Shared tail of every sample: emit-map rejection, pin map, sample transform.
__forceinline void cDistributeEffect::AddSample(cTransform& sampleTransform, Vector3& pos, int index,
                                         int count) {
  if (mEmitMap && IsMaskedOut(pos, index, count))
    return;
  if (mPinMap)
    PinToMap(pos);
  sampleTransform.SetOffset(pos);
  const cTransform& descTransform = mDesc->mTransform;
  if (descTransform.mScale == 1.0f &&
      !(descTransform.mFlags & (cTransform::kRotation | cTransform::kOffset))) {
    cDistributeSample sample(sampleTransform, index);
    mSamples.push_back(sample);
  } else {
    cTransform t(sampleTransform);
    t.PreTransformBy(descTransform);
    cDistributeSample sample(t, index);
    mSamples.push_back(sample);
  }
}

// Points on a sphere band: z = offset.x + scale.x*(2u-1), longitude from v.
__forceinline void cDistributeEffect::CreateSphereSamples(const cTransform& tf,
                                                   cTransform& sampleTransform, bool bReseed,
                                                   int count, int first, int last) {
  cHalton2D gen;
  gen.Seed(mDesc->mSeed + first);
  for (int i = first; i < last; ++i) {
    gen.Next();
    if (bReseed && (uint8_t)gen.mIndex == 0)
      gen.Seed(mDesc->mSeed + i + 1);
    Vector2 r;
    r.x = mSubdivScale.x * (gen.mValue.x * 2.0f - kVector2One.x);
    r.y = (gen.mValue.y * 2.0f - kVector2One.y) * mSubdivScale.y;
    Vector2 p(r);
    p.x = mSubdivOffset.x + p.x;
    float z = p.x;
    float angle = (p.y + mSubdivOffset.y) * 3.14159265f;
    float radius = sqrtf(1.0f - z * z);
    float s, c;
    FastSinCos(angle, s, c);
    Vector3 pos;
    pos.x = c * radius;
    pos.y = s * radius;
    pos.z = z;
    if (tf.mFlags & cTransform::kRotation)
      pos = Rotate(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = pos.y * tf.mScale + tf.mOffset.y;
    pos.z = pos.z * tf.mScale + tf.mOffset.z;
    AddSample(sampleTransform, pos, i, count);
  }
}

// ---------------------------------------------------------------- 0x00a8e7c0
void cDistributeEffect::CreateRandomSamples(int count, int first, int last) {
  cTransform tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;
  tf.mScale = mDesc->mScale * tf.mScale;
  tf.mFlags |= cTransform::kScale;

  cTransform sampleTransform;
  sampleTransform.SetRotation(tf.mRotation);
  sampleTransform.SetScale(mSizeScale);

  bool bReseed = (mDesc->mFlags >> 13) & 1;
  uint8_t sourceType = mDesc->mSourceType;
  if (sourceType == 3) {
    CreateSphereSamples(tf, sampleTransform, bReseed, count, first, last);
  } else if (sourceType == 6) {
    CreateSphereSamples(tf, sampleTransform, bReseed, count, first, last);
  } else {
      cHalton3D gen;
      gen.Seed(mDesc->mSeed + first);
      Vector3 pos;
      for (int i = first; i < last; ++i) {
        gen.Next();
        if (bReseed && (uint8_t)gen.mIndex == 0)
          gen.Seed(mDesc->mSeed + i + 1);
        switch (mDesc->mSourceType) {
          case 4:
            pos.x = gen.mValue.x * 2.0f - kVector3One.x;
            pos.y = gen.mValue.y * 2.0f - kVector3One.y;
            pos.z = gen.mValue.z * 2.0f - kVector3One.z;
            break;
          case 5:
            pos = CubeToSphere(gen.mValue);
            break;
        }
        pos.y = pos.y * mSubdivScale.y + mSubdivOffset.y;
        pos.x = mSubdivScale.x * pos.x + mSubdivOffset.x;
        pos.z = pos.z * mSubdivScale.z + mSubdivOffset.z;
        if (tf.mFlags & cTransform::kRotation)
          pos = Rotate(pos, tf.mRotation);
        pos.x = tf.mOffset.x + tf.mScale * pos.x;
        pos.y = pos.y * tf.mScale + tf.mOffset.y;
        pos.z = pos.z * tf.mScale + tf.mOffset.z;
        AddSample(sampleTransform, pos, i, count);
      }
  }
}

}}  // namespace EA::Swarm
