// src/game/Swarm/DistributeEffect.cpp -- migrated from slice(s) s00a8f6a0, s00a8e7c0, s00a8c850, s00a88d50, s007046e0 by tools/migrate/rewrite.py
// Object file: Swarm/DistributeEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
#include <new>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s007046e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
// ---- items of slice s007046e0 end

// ---- items of slice s00a88d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Random {
struct RandomLinearCongruential_s00a8_8d50 { double RandomDoubleUniform(); };   // 0x009360d0
}
}
extern EA::Random::RandomLinearCongruential_s00a8_8d50 sRandom_Swarm;           // 0x016778dc
static __forceinline double RandRange(double lo, double hi)
{
    double r = sRandom_Swarm.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct Vector4 { float x, y, z, w; };
struct Matrix3 { float m[9]; };
struct cTransform {                        // 0x38 bytes
    uint16_t mFlags;                       // +0x00 (bit 1: rotation)
    uint16_t mModCount;                    // +0x02
    Vector3 mOffset;                       // +0x04
    float mScale;                          // +0x10
    Matrix3 mRotation;                     // +0x14
};
template <class T> struct SpVector {       // eastl::vector with sp_vector_allocator (retail: 0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};
struct cDistributeDescription {
    char pad00[0xcc];
    SpVector<Vector3> mColorCurve;         // +0xcc
    Vector3 mColorVary;                    // +0xe0
    SpVector<float> mAlphaCurve;           // +0xec
    float mAlphaVary;                      // +0x100
};
struct cDistributeSample {                 // 0x4c bytes
    cTransform mTransform;                 // +0x00
    Vector4 mColorAlpha;                   // +0x38
    int mNumber;                           // +0x48
};
struct cIMap {                             // colour map (vtable only)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool Contains(const Vector3* p);                    // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector4* Sample(Vector4* out, const Vector3* p);    // +0x2c
};
static __forceinline Vector3 SampleCurve3(const SpVector<Vector3>& c, float t)
{
    unsigned n = c.size() - 1;
    if (n == 0)
        return c.mpBegin[0];
    t = (float)n * t;
    int idx = (int)t;
    float frac = t - (float)idx;
    const Vector3* a = c.mpBegin + idx;
    if (frac > 0.0f)
        return a[0] + (a[1] - a[0]) * frac;
    return a[0];
}
static __forceinline float SampleCurve1(const SpVector<float>& c, float t)
{
    unsigned n = c.size() - 1;
    if (n == 0)
        return c.mpBegin[0];
    t = (float)n * t;
    int idx = (int)t;
    float frac = t - (float)idx;
    if (frac > 0.0f) {
        float a = c.mpBegin[idx];
        return (c.mpBegin[idx + 1] - a) * frac + a;
    }
    return c.mpBegin[idx];
}
static __forceinline Vector3 MulRows(const Matrix3& m, const Vector3& v)
{
    return Vector3(m.m[2] * v.z + m.m[1] * v.y + m.m[0] * v.x,
                   m.m[5] * v.z + m.m[4] * v.y + m.m[3] * v.x,
                   m.m[8] * v.z + m.m[7] * v.y + m.m[6] * v.x);
}
static __forceinline Vector3 Untransform(const cTransform& t, const Vector3& p0)
{
    Vector3 p(p0.x - t.mOffset.x, p0.y - t.mOffset.y, p0.z - t.mOffset.z);
    if (t.mScale != 1.0f) {
        float inv = 1.0f / t.mScale;
        p = Vector3(inv * p.x, p.y * inv, p.z * inv);
    }
    if (t.mFlags & 2)
        p = MulRows(t.mRotation, p);
    return p;
}
static __forceinline float SamplePosition(const cDistributeSample& s, float invCount)
{
    return ((float)s.mNumber + 0.5f) * invCount;
}
struct cDistributeEffect {
    char pad00[0x14];
    cDistributeDescription* mDesc;         // +0x14
    char pad18[0x28 - 0x18];
    uint32_t mFlags;                       // +0x28 (bit 8: samples already local)
    cTransform mSourceTransform;           // +0x2c
    cTransform mRigidTransform;            // +0x64
    char pad9c[0xbc - 0x9c];
    SpVector<cDistributeSample> mSamples;  // +0xbc
    char padd0[4];
    int mTargetSampleCount;                // +0xd4
    char padd8[0x160 - 0xd8];
    cIMap* mColorMap;                      // +0x160

    void ApplyColorAndAlpha(int first, int last);
};
// ---- items of slice s00a88d50 end

// ---- items of slice s00a8c850 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t uint32;
void operator_delete__(void* p);
static inline void FreeBlock(void* p) {
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete__(p);
}
struct cIRefObj {
    virtual void Slot0();
    virtual void Release();
};
struct cSubObjD {
    uint32 pad00[(0x44) / 4];
    void FUN_00a89da0();
};
struct cSubObjC {
    uint32 pad00[(0x14) / 4];
    void FUN_00a8c440();
};
struct cDistributeEffect_s00a8_c850 {
    volatile uint32 mVtblIComponent;    // +0x00 (cComponentBase cIComponent part; volatile pins the store order)
    volatile uint32 mVtblRefCount;      // +0x04 (RefCountTemplate<int> part)
    uint32 pad08;
    volatile uint32 mVtblTextureStreamer;   // +0x0c (cITextureParticleStreamer)
    volatile uint32 mVtblModelStreamer;     // +0x10 (cIModelParticleStreamer)
    uint32 pad14[(0xa8 - 0x14) / 4];
    void*  mRenderSamplesBegin;     // +0xa8  (sp_vector block)
    uint32 padac[(0xbc - 0xac) / 4];
    void*  mSamplesBegin;           // +0xbc  (sp_vector block)
    uint32 padc0[(0xd8 - 0xc0) / 4];
    cSubObjD mSubD;                 // +0xd8
    cSubObjC mSubC;                 // +0x11c
    void*  mpBlock130;              // +0x130 (sp_vector block)
    uint32 pad134[(0x144 - 0x134) / 4];
    void*  mpBlock144;              // +0x144 (sp_vector block)
    uint32 pad148[(0x15c - 0x148) / 4];
    cIRefObj* mpRef15c;             // +0x15c (released)
    cIRefObj* mpRef160;             // +0x160 (released)
    cIRefObj* mpRef164;             // +0x164 (released)
    uint32 pad168[(0x19c - 0x168) / 4];
    void* volatile mpBlock19c;      // +0x19c (sp_vector block; volatile keeps the load after the vtable stores)

    ~cDistributeEffect_s00a8_c850();
};
// ---- items of slice s00a8c850 end

// ---- items of slice s00a8e7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gSinCosTable[32];                        // 0x01677840 {sin, cos} per step
extern float gSinCosInvStep;                          // 0x01678278
extern float gSinCosStep;                             // 0x01678300
struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Vector3_s00a8_e7c0 {
  float x, y, z;
  Vector3_s00a8_e7c0() {}
  Vector3_s00a8_e7c0(const Vector3_s00a8_e7c0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix3_s00a8_e7c0 {
  Vector3_s00a8_e7c0 row[3];
  Matrix3_s00a8_e7c0(const Matrix3_s00a8_e7c0& m);                          // 0x0041cb40
};
extern const Vector2 kVector2Zero;                    // 0x0167824c
extern const Vector2 kVector2One;                     // 0x01678260
extern const Vector3_s00a8_e7c0 kVector3One;                     // 0x01678230
extern const Vector3_s00a8_e7c0 kVector3Zero;                    // 0x0167827c
extern const Matrix3_s00a8_e7c0 kMatrix3Identity;                // 0x01678328
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
static inline Vector3_s00a8_e7c0 Rotate(const Vector3_s00a8_e7c0& v, const Matrix3_s00a8_e7c0& m) {
  Vector3_s00a8_e7c0 out;
  out.x = v.x * m.row[0].x + v.y * m.row[1].x + v.z * m.row[2].x;
  out.y = v.x * m.row[0].y + v.y * m.row[1].y + v.z * m.row[2].y;
  out.z = v.x * m.row[0].z + v.y * m.row[1].z + v.z * m.row[2].z;
  return out;
}
Vector3_s00a8_e7c0 CubeToSphere(Vector3_s00a8_e7c0 v);                      // 0x00a7c860 (cdecl, by value)
namespace EA {
namespace Swarm {
struct cTransform_s00a8_e7c0 {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3_s00a8_e7c0 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3_s00a8_e7c0 mRotation;                                  // +0x14

  cTransform_s00a8_e7c0()
      : mFlags(0), mModCount(0), mOffset(kVector3Zero), mScale(1.0f),
        mRotation(kMatrix3Identity) {}
  cTransform_s00a8_e7c0(const cTransform_s00a8_e7c0& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform_s00a8_e7c0& operator=(const cTransform_s00a8_e7c0& t);         // 0x00537dc0
  // retail: rotation and offset setters bump the modification count
  void SetRotation(const Matrix3_s00a8_e7c0& m) {
    mRotation = m;
    mFlags |= kRotation;
    ++mModCount;
  }
  void SetScale(float s) {
    mScale = s;
    ++mModCount;
  }
  void SetOffset(const Vector3_s00a8_e7c0& v) {
    mOffset = v;
    mFlags |= kOffset;
    ++mModCount;
  }
  void PreTransformBy(const cTransform_s00a8_e7c0& t);           // 0x00537f40
};
}
}
namespace EA {
namespace Swarm {
struct cHalton2D {
  Vector2 mValue;                                     // +0x00
  int mIndex;                                         // +0x08
  int mDigits3;                                       // +0x0c
  cHalton2D() : mValue(kVector2Zero), mIndex(0), mDigits3(0) {}
  void Seed(int index);                               // 0x00a7c3d0
  int Next();                                         // 0x00a7c350
};
}
}
namespace EA {
namespace Swarm {
struct cHalton3D {
  Vector3_s00a8_e7c0 mValue;                                     // +0x00
  int mIndex;                                         // +0x0c
  int mDigits3;                                       // +0x10
  int mDigits5;                                       // +0x14
  cHalton3D() : mValue(kVector3Zero), mIndex(0), mDigits3(0), mDigits5(0) {}
  void Seed(int index);                               // 0x00a7c540
  int Next();                                         // 0x00a7c450
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeDescription_s00a8_e7c0 {
  uint32_t pad00[2];
  uint32_t mFlags;                                    // +0x08 (bit 13: reseed every 256)
  uint32_t pad0c[3];
  int mSeed;                                          // +0x18
  uint8_t mSourceType;                                // +0x1c
  uint8_t pad1d[3];
  float mScale;                                       // +0x20
  cTransform_s00a8_e7c0 mTransform;                              // +0x24
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeSample_s00a8_e7c0 {
  uint32_t data[0x4c / 4];
  cDistributeSample_s00a8_e7c0(const cTransform_s00a8_e7c0& t, int index);  // 0x00a89980
  cDistributeSample_s00a8_e7c0(const cDistributeSample_s00a8_e7c0& s);      // 0x00a89de0
};
}
}
namespace EA {
namespace Swarm {
struct SampleVector {
  cDistributeSample_s00a8_e7c0* mpBegin;
  cDistributeSample_s00a8_e7c0* mpEnd;
  cDistributeSample_s00a8_e7c0* mpCapacity;
  uint32_t mAllocator[2];
  void DoInsertValue(cDistributeSample_s00a8_e7c0* position, const cDistributeSample_s00a8_e7c0& value);  // 0x00a8ce30
  void push_back(const cDistributeSample_s00a8_e7c0& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) cDistributeSample_s00a8_e7c0(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeEffect_s00a8_e7c0 {
  uint32_t pad00[0x14 / 4];
  cDistributeDescription_s00a8_e7c0* mDesc;                      // +0x014
  uint32_t pad18[(0x2c - 0x18) / 4];
  cTransform_s00a8_e7c0 mSourceTransform;                        // +0x02c
  uint32_t pad64[(0xbc - 0x64) / 4];
  SampleVector mSamples;                              // +0x0bc
  uint32_t padd0[(0x100 - 0xd0) / 4];
  Vector3_s00a8_e7c0 mSubdivOffset;                              // +0x100
  Vector3_s00a8_e7c0 mSubdivScale;                               // +0x10c
  struct cSubdivOwner { uint32_t pad[4]; cTransform_s00a8_e7c0* mpTransform; }* mSubdivOwner;  // +0x118
  uint32_t pad11c[(0x15c - 0x11c) / 4];
  void* mEmitMap;                                     // +0x15c
  void* mColorMap;                                    // +0x160
  void* mPinMap;                                      // +0x164
  uint32_t pad168[(0x18c - 0x168) / 4];
  float mSizeScale;                                   // +0x18c

  bool IsMaskedOut(const Vector3_s00a8_e7c0& pos, int index, int count);  // 0x00a89a90
  void PinToMap(Vector3_s00a8_e7c0& pos);                        // 0x00a89ce0
  void CreateRandomSamples(int count, int first, int last);
  inline void AddSample(cTransform_s00a8_e7c0& sampleTransform, Vector3_s00a8_e7c0& pos, int index, int count);
  inline void CreateSphereSamples(const cTransform_s00a8_e7c0& tf, cTransform_s00a8_e7c0& sampleTransform,
                                  bool bReseed, int count, int first, int last);
};
}
}
namespace EA {
namespace Swarm {
__forceinline void cDistributeEffect_s00a8_e7c0::AddSample(cTransform_s00a8_e7c0& sampleTransform, Vector3_s00a8_e7c0& pos, int index,
                                         int count) {
  if (mEmitMap && IsMaskedOut(pos, index, count))
    return;
  if (mPinMap)
    PinToMap(pos);
  sampleTransform.SetOffset(pos);
  const cTransform_s00a8_e7c0& descTransform = mDesc->mTransform;
  if (descTransform.mScale == 1.0f &&
      !(descTransform.mFlags & (cTransform_s00a8_e7c0::kRotation | cTransform_s00a8_e7c0::kOffset))) {
    cDistributeSample_s00a8_e7c0 sample(sampleTransform, index);
    mSamples.push_back(sample);
  } else {
    cTransform_s00a8_e7c0 t(sampleTransform);
    t.PreTransformBy(descTransform);
    cDistributeSample_s00a8_e7c0 sample(t, index);
    mSamples.push_back(sample);
  }
}
}
}
namespace EA {
namespace Swarm {
__forceinline void cDistributeEffect_s00a8_e7c0::CreateSphereSamples(const cTransform_s00a8_e7c0& tf,
                                                   cTransform_s00a8_e7c0& sampleTransform, bool bReseed,
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
    Vector3_s00a8_e7c0 pos;
    pos.x = c * radius;
    pos.y = s * radius;
    pos.z = z;
    if (tf.mFlags & cTransform_s00a8_e7c0::kRotation)
      pos = Rotate(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = pos.y * tf.mScale + tf.mOffset.y;
    pos.z = pos.z * tf.mScale + tf.mOffset.z;
    AddSample(sampleTransform, pos, i, count);
  }
}
}
}
// ---- items of slice s00a8e7c0 end

// ---- items of slice s00a8f6a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  FUN_00a8bf60(int);
extern void  FUN_00a8cc40(int);
extern void  FUN_00a8ce30(void* p, void* rec);
extern void  FUN_00a89de0(void* rec);
extern char  FUN_00a89a90(const void* v, int n, int count);
extern int   FUN_00a89980(void* rec, float f);
extern void  FUN_00537f40(void* p);
extern float* CubeToSphereSurface(float* out, float* v);     // anonymous-namespace helper
extern float DAT_0156502c, _DAT_01678300, DAT_01678278;
extern float DAT_01677840[], DAT_01677844[];
extern float DAT_01678230, DAT_01678234, DAT_01678238, DAT_0167827c, DAT_01678280,
             DAT_01678284;
struct M33 { V3 x, y, z; };
#define SF(off) (*(float*)((char*)self + (off)))
#define SI(off) (*(int*)((char*)self + (off)))
struct Transform {
    float tx, ty, tpad;
    M33   rot;
    float scale;
    short flags, mod;
};
static void PushSample(void* self, void* rec)
{
    void* pEnd   = (void*)SI(0xb8 + 4);
    void* pCap   = (void*)SI(0xb8 + 8);
    if (pEnd < pCap) {
        SI(0xb8 + 4) = (int)pEnd + 0x30;
        if (pEnd) FUN_00a89de0(rec);
    } else {
        FUN_00a8ce30(pEnd, rec);
    }
}
struct Sample {
    float px, py, pz;
    float dx, dy, dz;
    M33   m;
    float time;
    float scale;
    unsigned short flags;
    unsigned short mod;
};
// ---- items of slice s00a8f6a0 end

// @ 0x00705290
void mul_705290(V3* a, V3* b)
{
    V3 r;
    r.x = a->x * b->x;
    r.y = a->y * b->y;
    r.z = a->z * b->z;
    *a = r;
}

// @ 0x00a88d50
void cDistributeEffect::ApplyColorAndAlpha(int first, int last)
{
    if (mSamples.empty())
        return;

    float invCount = 1.0f / (float)mTargetSampleCount;

    if (!mDesc->mColorCurve.empty() && first < last) {
        for (int i = first; i < last; ++i) {
            float t = SamplePosition(mSamples.mpBegin[i], invCount);
            _ReadWriteBarrier();   // keeps t computed in SSE before the curve lookup (as in the original)
            Vector3 c = SampleCurve3(mDesc->mColorCurve, t);
            float v0 = mDesc->mColorVary.x;
            float r0 = (float)RandRange(1.0 - v0, v0 + 1.0);
            float v1 = mDesc->mColorVary.y;
            float r1 = (float)RandRange(1.0 - v1, v1 + 1.0);
            float v2 = mDesc->mColorVary.z;
            float r2 = (float)RandRange(1.0 - v2, v2 + 1.0);
            mSamples.mpBegin[i].mColorAlpha.x = c.x * r0;
            mSamples.mpBegin[i].mColorAlpha.y = c.y * r1;
            mSamples.mpBegin[i].mColorAlpha.z = c.z * r2;
        }
    }

    if (!mDesc->mAlphaCurve.empty() && first < last) {
        for (int i = first; i < last; ++i) {
            float t = SamplePosition(mSamples.mpBegin[i], invCount);
            _ReadWriteBarrier();   // keeps t computed in SSE before the curve lookup (as in the original)
            float a = SampleCurve1(mDesc->mAlphaCurve, t);
            float v = mDesc->mAlphaVary;
            mSamples.mpBegin[i].mColorAlpha.w = (float)RandRange(1.0 - v, v + 1.0) * a;
        }
    }

    if (mColorMap && first < last) {
        for (int i = first; i < last; ++i) {
            cDistributeSample* s = &mSamples.mpBegin[i];
            Vector3 p = s->mTransform.mOffset;
            if (!((mFlags >> 8) & 1)) {
                p = Untransform(mRigidTransform, p);
                p = Untransform(mSourceTransform, p);
            }
            if (mColorMap->Contains(&p)) {
                Vector4 tmp;
                const Vector4* c = mColorMap->Sample(&tmp, &p);
                s = &mSamples.mpBegin[i];
                s->mColorAlpha.x = c->x * s->mColorAlpha.x;
                s->mColorAlpha.y = s->mColorAlpha.y * c->y;
                s->mColorAlpha.z = s->mColorAlpha.z * c->z;
                s->mColorAlpha.w = s->mColorAlpha.w * c->w;
            }
        }
    }
}

// @ 0x00a8cb00
cDistributeEffect_s00a8_c850::~cDistributeEffect_s00a8_c850()
{
    mVtblIComponent = 0x1458308;
    mVtblRefCount = 0x1458304;
    mVtblTextureStreamer = 0x1458300;
    mVtblModelStreamer = 0x14582fc;

    FreeBlock(mpBlock19c);

    if (mpRef164)
        mpRef164->Release();
    if (mpRef160)
        mpRef160->Release();
    if (mpRef15c)
        mpRef15c->Release();

    FreeBlock(mpBlock144);
    FreeBlock(mpBlock130);

    mSubC.FUN_00a8c440();
    mSubD.FUN_00a89da0();

    FreeBlock(mSamplesBegin);
    FreeBlock(mRenderSamplesBegin);

    mVtblIComponent = 0x13f21d4;
    mVtblRefCount = 0x13ef094;
}

// @ 0x00a8e7c0
namespace EA { namespace Swarm {
void cDistributeEffect_s00a8_e7c0::CreateRandomSamples(int count, int first, int last)
{
  cTransform_s00a8_e7c0 tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;
  tf.mScale = mDesc->mScale * tf.mScale;
  tf.mFlags |= cTransform_s00a8_e7c0::kScale;

  cTransform_s00a8_e7c0 sampleTransform;
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
      Vector3_s00a8_e7c0 pos;
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
        if (tf.mFlags & cTransform_s00a8_e7c0::kRotation)
          pos = Rotate(pos, tf.mRotation);
        pos.x = tf.mOffset.x + tf.mScale * pos.x;
        pos.y = pos.y * tf.mScale + tf.mOffset.y;
        pos.z = pos.z * tf.mScale + tf.mOffset.z;
        AddSample(sampleTransform, pos, i, count);
      }
  }
}
}}  // namespace EA::Swarm

// @ 0x00a8f6a0
void cDistributeEffect_CreateClusteredMatchingSamples2D(void* self, int param_2)
{
    Transform tf;
    void* desc = (void*)SI(0x14);
    int   count = SI(0xd0 + 4);          // mEffects.mpEnd (element count)
    float inv = 1.0f / (float)count;

    // copy mSourceTransform (this+0x2c)
    {
        char* s = (char*)self + 0x2c;
        tf.tx = *(float*)(s + 0);
        tf.ty = *(float*)(s + 4);
        tf.tpad = *(float*)(s + 8);
        tf.rot.x.x = *(float*)(s + 12);
        tf.rot.x.y = *(float*)(s + 16);
        tf.rot.x.z = *(float*)(s + 20);
        tf.rot.y.x = *(float*)(s + 24);
        tf.rot.y.y = *(float*)(s + 28);
        tf.rot.y.z = *(float*)(s + 32);
        tf.rot.z.x = *(float*)(s + 36);
        tf.rot.z.y = *(float*)(s + 40);
        tf.rot.z.z = *(float*)(s + 44);
        tf.scale = *(float*)(s + 48);
        tf.flags = *(short*)(s + 52);
        tf.mod = *(short*)(s + 54);
    }
    // optional per-surface override (mSurfaceRecs at +0x114)
    {
        void* srEnd = (void*)SI(0x114 + 4);
        if (srEnd) tf = *(Transform*)srEnd; // cSPTransform::operator=
    }

    float preScale = *(float*)((char*)desc + 0) * tf.scale;   // mPreTransform * mScale
    tf.flags = (short)(tf.flags | 1);
    tf.mod   = (short)(tf.mod + 1);
    float colorScale = *(float*)((char*)self + 0x15c);
    float subdivScaleZ = SF(0x104 + 8);      // mSubdivScale.PaddingForAlignment[0]
    float subdivScaleX = SF(0x104 + 0);
    float subdivScaleY = SF(0x104 + 4);
    float subdivOff    = SF(0xf8 + 8);       // mSubdivOffset.PaddingForAlignment[0]
    int   subdivOwner  = SI(0x110);
    int   surfBegin    = SI(0x114);
    float timeAcc = 0.0f;

    float base = inv;
    float step = inv * 2.0f;
    float s3 = subdivScaleZ * inv;
    float sOwner = (float)subdivOwner * inv;
    float sSurf = (float)surfBegin * inv;

    if (((*(unsigned*)((char*)desc + 4)) >> 9 & 1) != 0) {   // mDesc->mFlags bit 9
        tf.flags = (short)(tf.flags | 1);
        tf.mod   = (short)(tf.mod + 1);
        preScale = (subdivScaleZ * inv) * preScale;
    }

    int format = *(unsigned char*)((char*)desc + 8);   // mSourceSize byte (mSourceFormat)
    float halfExtent = (float)(count - 1) * 0.5f;

    switch (format) {
    case 0: {
        FUN_00a8bf60(count * count);
        FUN_00a8cc40(count * count);
        if (count <= 0) break;
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count; ++j) {
                float u = fi * subdivScaleX + subdivOff;
                float v = ((float)j - halfExtent) * step * (float)subdivOwner + subdivScaleY;
                float w = 0.0f + subdivScaleZ;
                Sample rec;
                rec.px = u; rec.py = v; rec.pz = w;
                rec.scale = preScale;
                PushSample(self, &rec);
                float rx = u, ry = v, rz = w;
                // optional cube->sphere mapping
                if (((SI(0x28) >> 4) & 1) == 0) {
                    if ((SI(0x28) >> 5) & 1) {
                        float* c = CubeToSphereSurface((float*)&rec.m, &u);
                        rx = c[0]; ry = c[1]; rz = c[2];
                    }
                } else {
                    float t = (v * DAT_0156502c) * DAT_01678278 + 12582912.0f;
                    float rad = sqrtf(1.0f - u * u);
                    float a = DAT_01677840[((unsigned)t & 0xf) * 2];
                    float d = v * DAT_0156502c - (float)((int)t - 0x4b400000) * _DAT_01678300;
                    float b = DAT_01677844[((unsigned)t & 0xf) * 2];
                    rx = (b - ((b * d) * 0.5f + a) * d) * rad;
                    ry = ((b - (a * d) * 0.5f) * d + a) * rad;
                    rz = u;
                }
                // rotate if the rigid flag is set
                if ((tf.flags & 2) != 0) {
                    float ox = rx, oy = ry, oz = rz;
                    rx = ox * tf.rot.x.x + oz * tf.rot.z.x + oy * tf.rot.y.x;
                    ry = ox * tf.rot.x.y + oz * tf.rot.z.y + oy * tf.rot.y.y;
                    rz = ox * tf.rot.x.z + oz * tf.rot.z.z + oy * tf.rot.y.z;
                }
                tf.flags |= 4;
                tf.mod = (short)(tf.mod + 1);
                float wx = rx * preScale + tf.tx;
                float wy = tf.ty + ry * preScale;
                float wz = tf.tpad + rz * preScale;
                if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                    // build the mSamples record (with or without the pre-transform)
                    FUN_00537f40(desc);
                    (void)FUN_00a89980(&rec, timeAcc);
                    PushSample(self, &rec);
                    timeAcc = (float)((int)timeAcc + 1);
                }
            }
        }
        return;
    }
    case 3: {
        int n = count * count * 2;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        SI(0x28) = SI(0x28) | 0x10;
        float halfY = (float)subdivOwner * 0.5f;
        if (count <= 0) break;
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count * 2; ++j) {
                float u = fi * subdivScaleX + subdivOff;
                float v = ((((float)j - (float)(count * 2 - 1) * 0.5f) * step) * 0.5f) *
                          (float)subdivOwner + subdivScaleY;
                float w = 0.0f + subdivScaleZ;
                Sample rec;
                rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                PushSample(self, &rec);
                float t = (v * DAT_0156502c) * DAT_01678278 + 12582912.0f;
                float rad = sqrtf(1.0f - u * u);
                float a = DAT_01677840[((unsigned)t & 0xf) * 2];
                float d = v * DAT_0156502c - (float)((int)t - 0x4b400000) * _DAT_01678300;
                float b = DAT_01677844[((unsigned)t & 0xf) * 2];
                float rx = (b - ((d * b) * 0.5f + a) * d) * rad;
                float ry = ((b - (d * a) * 0.5f) * d + a) * rad;
                float rz = u;
                if ((tf.flags & 2) != 0) {
                    float ox = rx, oy = ry, oz = rz;
                    rx = oz * tf.rot.z.x + oy * tf.rot.y.x + ox * tf.rot.x.x;
                    ry = oz * tf.rot.z.y + oy * tf.rot.y.y + ox * tf.rot.x.y;
                    rz = oz * tf.rot.z.z + oy * tf.rot.y.z + ox * tf.rot.x.z;
                }
                tf.flags |= 4;
                tf.mod = (short)(tf.mod + 1);
                float wx = rx * preScale + tf.tx;
                float wy = tf.ty + ry * preScale;
                float wz = tf.tpad + rz * preScale;
                if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                    FUN_00537f40(desc);
                    (void)FUN_00a89980(&rec, timeAcc);
                    PushSample(self, &rec);
                    timeAcc = (float)((int)timeAcc + 1);
                }
            }
        }
        return;
    }
    case 4: {
        int n = count * count * count;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count; ++j) {
                float fj = ((float)j - halfExtent) * step;
                for (int k = 0; k < count; ++k) {
                    float fk = ((float)k - halfExtent) * step;
                    float x = fi * subdivScaleX + subdivOff;
                    float y = ((float)j - halfExtent) * step * (float)subdivOwner + subdivScaleY;
                    float z = fk * (float)surfBegin + subdivScaleZ;
                    float u = x + subdivOff;
                    float v = subdivScaleX + y;
                    float w = subdivScaleY + z;
                    Sample rec;
                    rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                    PushSample(self, &rec);
                    float rx = u, ry = v, rz = w;
                    if ((tf.flags & 2) != 0) {
                        float ox = rx, oy = ry, oz = rz;
                        rx = oz * tf.rot.z.x + oy * tf.rot.y.x + ox * tf.rot.x.x;
                        ry = oz * tf.rot.z.y + oy * tf.rot.y.y + ox * tf.rot.x.y;
                        rz = oz * tf.rot.z.z + oy * tf.rot.y.z + ox * tf.rot.x.z;
                    }
                    tf.flags |= 4;
                    tf.mod = (short)(tf.mod + 1);
                    float wx = rx * preScale + tf.tx;
                    float wy = tf.ty + ry * preScale;
                    float wz = tf.tpad + rz * preScale;
                    if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                        FUN_00537f40(desc);
                        (void)FUN_00a89980(&rec, timeAcc);
                        PushSample(self, &rec);
                        timeAcc = (float)((int)timeAcc + 1);
                    }
                }
            }
        }
        return;
    }
    case 6: {
        int n = count * count * 6;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        SI(0x28) = SI(0x28) | 0x20;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < count; ++j) {
                float fj = ((float)j - halfExtent) * step;
                for (int k = 0; k < count; ++k) {
                    float fk = ((float)k - halfExtent) * step;
                    float u = fj * subdivScaleX + subdivOff;
                    float v = (float)i * (float)surfBegin + subdivScaleY;
                    float w = fk * (float)subdivOwner + subdivScaleZ;
                    Sample rec;
                    rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                    PushSample(self, &rec);
                    float invLen = 1.0f / sqrtf((u * u + v * v) + 1.0f);
                    int tbl = (((int)u) >> 1) * 4;   // use u as the face coordinate
                    float sgn = ((int)u & 1) ? -invLen : invLen;
                    float n[3];
                    n[0] = sgn * u;
                    n[1] = invLen * v;
                    n[2] = sgn;
                    if ((tf.flags & 2) != 0) {
                        float ox = n[0], oy = n[1], oz = n[2];
                        n[0] = ox * tf.rot.x.x + oy * tf.rot.y.x + oz * tf.rot.z.x;
                        n[1] = ox * tf.rot.x.y + oy * tf.rot.y.y + oz * tf.rot.z.y;
                        n[2] = ox * tf.rot.x.z + oy * tf.rot.y.z + oz * tf.rot.z.z;
                    }
                    tf.flags |= 4;
                    tf.mod = (short)(tf.mod + 1);
                    float wx = n[0] * preScale + tf.tx;
                    float wy = tf.ty + n[1] * preScale;
                    float wz = tf.tpad + n[2] * preScale;
                    if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                        FUN_00537f40(desc);
                        (void)FUN_00a89980(&rec, timeAcc);
                        PushSample(self, &rec);
                        timeAcc = (float)((int)timeAcc + 1);
                    }
                    (void)tbl;
                }
            }
        }
        return;
    }
    default: {
        // single sample at the mPreTransform origin
        Sample rec;
        rec.px = DAT_0167827c; rec.py = DAT_01678280; rec.pz = DAT_01678284;
        rec.scale = DAT_01678230;
        PushSample(self, &rec);
        return;
    }
    }
}
