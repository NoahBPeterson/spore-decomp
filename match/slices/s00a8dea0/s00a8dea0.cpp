// slice s00a8dea0: EA::Swarm::cDistributeEffect, clustered 2D sample creation (0x00a8dea0, 2333 bytes).
// Name coined here ("CreateClusteredSamples2D", as the PDB-derived symbol says). Samples are
// grouped into N cells ("clusters"): a Halton generator A walks the cell index inside
// [start, start+N), a second Halton generator B gives the offset inside a cell. The offset is
// tested against a disc whose radius comes from the size curve (indexed by cell position);
// accepted points follow the CreateSamples2D path (square/circle/ring, sphere band, cube
// sphere, rotation, emit/pin maps) and a cDistributeSample is appended.
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
  float mRingInnerRadius;                             // +0x5c
  uint8_t pad60[0x160 - 0x60];
  int mNumClusters;                                   // +0x160 (cells N)
  int mClusterStart;                                  // +0x164 (first cell index)
  float mClusterScale;                                // +0x168
  float* mCurveBegin;                                 // +0x16c (size curve)
  float* mCurveEnd;                                   // +0x170
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
  void CreateClusteredSamples2D(int count, int first, int last);
  inline void AddSample(cTransform& sampleTransform, Vector3& pos, int index, int count);
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
  if (descTransform.mScale != 1.0f ||
      (descTransform.mFlags & (cTransform::kRotation | cTransform::kOffset))) {
    cTransform t(sampleTransform);
    t.PreTransformBy(descTransform);
    cDistributeSample sample(t, index);
    mSamples.push_back(sample);
  } else {
    cDistributeSample sample(sampleTransform, index);
    mSamples.push_back(sample);
  }
}


// Size curve lookup: linear interpolation over t in [0,1].
static inline float SampleCurve(const float* begin, const float* end, float t) {
  unsigned n = (unsigned)(end - begin) - 1;
  if (n == 0)
    return begin[0];
  float f = (float)n * t;
  int idx = (int)f;
  float frac = f - (float)idx;
  if (frac > 0.0f) {
    float a = begin[idx];
    return (begin[idx + 1] - a) * frac + a;
  }
  return begin[idx];
}

// @ 0x00a8dea0
void cDistributeEffect::CreateClusteredSamples2D(int count, int first, int last) {
  cTransform tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;

  cTransform sampleTransform;
  sampleTransform.SetRotation(tf.mRotation);
  sampleTransform.SetScale(mSizeScale);

  int n = mDesc->mNumClusters;
  int base = mDesc->mClusterStart;
  int seedIndex = mDesc->mSeed + first;
  int cell = seedIndex / n;
  cHalton2D cellGen;
  cHalton2D subGen;
  cellGen.Seed(seedIndex % n + base);
  unsigned step = 0x50000000 / n;
  unsigned phase = (seedIndex - cell * n) * step;
  subGen.Seed((phase >> 24) + cell * 5);
  phase &= 0xfffffff;
  bool bReseed = (mDesc->mFlags >> 13) & 1;
  float invN = 1.0f / (float)n;

  for (int i = first; i < last; ++i) {
    cellGen.Next();
    if (bReseed && (uint8_t)cellGen.mIndex == 0) {
      cellGen.Seed((mDesc->mSeed + i + 1) % n + base);
    } else if (cellGen.mIndex == base + n) {
      cellGen.Seed(base);
      if (phase != 0) {
        subGen.Next();
        phase = 0;
      }
    }
    phase += step;
    float dx = subGen.mValue.x - 0.5f;
    float dy = subGen.mValue.y - 0.5f;
    while (phase & 0xf0000000) {
      subGen.Next();
      phase -= 0x10000000;
    }

    float radius = SampleCurve(mDesc->mCurveBegin, mDesc->mCurveEnd,
                               (float)(unsigned)(cellGen.mIndex - base) * invN) * 0.5f;
    if (dx * dx + dy * dy > radius * radius)
      continue;

    Vector2 p;
    p.x = dx * mDesc->mClusterScale + cellGen.mValue.x;
    p.y = cellGen.mValue.y + dy * mDesc->mClusterScale;
    switch (mDesc->mSourceType) {
      case 0:
        p = Vector2(p.x * 2.0f - kVector2One.x, p.y * 2.0f - kVector2One.y);
        break;
      case 1:
        p = SquareToCircle(p);
        break;
      case 2:
        p = SquareToRing(p, mDesc->mRingInnerRadius);
        break;
    }

    Vector3 pos;
    pos = Vector3(mSubdivScale.x * p.x, mSubdivScale.y * p.y, mSubdivScale.z * 0.0f);
    pos.x = mSubdivOffset.x + pos.x;
    pos.y = mSubdivOffset.y + pos.y;
    pos.z = mSubdivOffset.z + pos.z;

    if (mFlags & 0x10) {
      float z = pos.x;
      float angle = pos.y * 3.14159265f;
      float r = sqrtf(1.0f - z * z);
      float s, c;
      FastSinCos(angle, s, c);
      pos = Vector3(c * r, s * r, z);
    } else if (mFlags & 0x20) {
      pos = CubeToSphereSurface(pos);
    }

    if (tf.mFlags & cTransform::kRotation)
      pos = Rotate(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = tf.mOffset.y + pos.y * tf.mScale;
    pos.z = tf.mOffset.z + pos.z * tf.mScale;
    AddSample(sampleTransform, pos, i, count);
  }
}

}}  // namespace EA::Swarm
