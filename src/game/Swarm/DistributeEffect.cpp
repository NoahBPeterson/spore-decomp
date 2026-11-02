// src/game/Swarm/DistributeEffect.cpp -- migrated from slice(s) s00a92d90, s00a92450, s00a8b940, s00a8aec0, s00a8a450, s00a89de0, s00a87fb0, s00a86b30, s00a85c00, s00a8dea0, s00a8d450, s00a8f6a0, s00a8e7c0, s00a8c850, s00a88d50, s007046e0 by tools/migrate/rewrite.py
// Object file: Swarm/DistributeEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
#include <new>
#include "EA/Swarm/cTransform.h"
#include "cSPTransform.h"
#include "EA/Swarm/cIEffectsWorld.h"
#include "EA/Swarm/cIMap.h"
#include "EA/Swarm/cITextureParticleRenderer.h"
#include "EA/Swarm/cEffectParams.h"
#include "EA/Swarm/cIVisualEffect.h"
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s007046e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
// ---- items of slice s007046e0 end

// ---- items of slice s00a88d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3 { float m[9]; };
namespace EA {
namespace Random {
class RandomLinearCongruential_s00a8_8d50 { public: double RandomDoubleUniform(); };   // 0x009360d0
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
extern Vector4 gDefaultSampleColor;        // 0x01678318 (default sample colour/alpha)
struct Matrix3_s00a8_8d50 {
    float m[9];
    void CopyFrom(const Matrix3_s00a8_8d50& src);     // 0x0041cb40 (out-of-line copy)
};
struct cTransform_s00a8_8d50 {                        // 0x38 bytes
    uint16_t mFlags;                       // +0x00 (bit 1: rotation)
    uint16_t mModCount;                    // +0x02
    Vector3 mOffset;                       // +0x04
    float mScale;                          // +0x10
    Matrix3_s00a8_8d50 mRotation;                     // +0x14

    void CopyFrom(const cTransform_s00a8_8d50* src);  // 0x00537dc0 (flags compare + full copy)
    void ApplyInverse(Vector3* p) const;   // 0x007cda70 (p = R^-1 * ((p - offset) / scale))
    void ApplyForward(Vector3* p) const;   // 0x007cdee0 (p = R * p * scale + offset)
};
struct IRenderTarget {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
    virtual void ReleaseUnshared(int index);                    // +0x1c
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2c();
    virtual void ReleaseShared(int index);                      // +0x30
};
struct IRenderHost {                       // object at effect +0x1c
virtual void h00();
virtual void h04();
virtual void h08();
virtual void h0c();
virtual void h10();
virtual void h14();
virtual void h18();
virtual void h1c();
    virtual IRenderTarget* GetTarget();                         // +0x20
};
struct IRefCounted {                       // samples at +0xbc are AddRef'd when copied out
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
virtual void r20();
virtual void r24();
virtual void r28();
virtual void r2c();
    virtual void r30();
    virtual void AddRef();                                      // +0x34
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
    char pad00[8];
    uint32_t mFlags;                       // +0x08 (bits 2/3: density range test, bit 10: keep local pos)
    char pad0c[0xcc - 0x0c];
    SpVector<Vector3> mColorCurve;         // +0xcc
    Vector3 mColorVary;                    // +0xe0
    SpVector<float> mAlphaCurve;           // +0xec
    float mAlphaVary;                      // +0x100
};
struct cDistributeSample {                 // 0x4c bytes
    cTransform_s00a8_8d50 mTransform;                 // +0x00
    Vector4 mColorAlpha;                   // +0x38
    int mNumber;                           // +0x48

    cDistributeSample() {}
    cDistributeSample(const cDistributeSample& src, int number);
};
struct cIMap_s00a8_8d50 {                             // colour map (vtable only)
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool Contains(const Vector3* p);                    // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual Vector4* Sample(Vector4* out, const Vector3* p);    // +0x2c
};
struct cISampleMap {                       // density/height map at +0x15c and +0x164
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool Contains(const Vector3* p);                    // +0x18
    virtual void v1c();
    virtual float GetValue(const Vector3* p);                   // +0x20
};
struct cRenderMesh {                       // element of mMeshes (+0xd8)
    char pad00[0xa8];
    cDistributeSample* mpBegin;            // +0xa8
    cDistributeSample* mpEnd;              // +0xac
};
struct cSampleSlot {                       // 0x58-byte element of cSampleSource::mSlots
    char pad00[8];
    uint32_t mMaskA;                       // +0x08
    uint32_t mMaskB;                       // +0x0c
    char pad10[0x48];
};
struct cSampleSource {                     // argument of CollectSamples (0x00a89680)
    char pad00[8];
    uint32_t mFlags;                       // +0x08 (bits 7/8: use the base-transform fill)
    char pad0c[4];
    int mCount;                            // +0x10 (negative: take the flag path)
    uint8_t mFlag14;                       // +0x14
    char pad15[0x104 - 0x15];
    SpVector<cSampleSlot> mSlots;          // +0x104
    uint32_t mMaskA0; uint32_t mMaskA1;    // +0x118/+0x11c
    uint32_t mMaskB0; uint32_t mMaskB1;    // +0x120/+0x124
    uint32_t mMaskC0; uint32_t mMaskC1;    // +0x128/+0x12c
    char pad130[8];
    char mBaseTransform[0x20];             // +0x138
};
struct cSampleOut {                        // 0x10-byte output record
    uint32_t mValue0;                      // +0x00
    uint32_t mValue1;                      // +0x04
    uint32_t mKind;                        // +0x08
    uint32_t mPad0c;                       // +0x0c
};
struct cSampleTarget {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
    virtual int GetSamples(int count, cSampleOut* out, int capacity);   // +0x2c
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
    if (frac > 0.0f) {
        Vector3 d = a[1] - a[0];
        _ReadWriteBarrier();   // make cl reload a[0] for the add (the original does not CSE it)
        return Vector3(d.x * frac + a[0].x, d.y * frac + a[0].y, d.z * frac + a[0].z);
    }
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
static __forceinline Vector3 MulRows(const Matrix3_s00a8_8d50& m, const Vector3& v)
{
    return Vector3(m.m[2] * v.z + m.m[1] * v.y + m.m[0] * v.x,
                   m.m[5] * v.z + m.m[4] * v.y + m.m[3] * v.x,
                   m.m[8] * v.z + m.m[7] * v.y + m.m[6] * v.x);
}
static __forceinline Vector3 Untransform(const cTransform_s00a8_8d50& t, const Vector3& p0)
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
struct cEffectFlagBits {
    uint32_t mBits00_06 : 7;
    uint32_t mRigidOnly : 1;               // bit 7
    uint32_t mSamplesLocal : 1;            // bit 8
    uint32_t mSkipMapRoundTrip : 1;        // bit 9
    uint32_t mBits10_13 : 4;
    uint32_t mSharedRenderSet : 1;         // bit 14
    uint32_t mBits15_31 : 17;
};
struct cDistributeEffect {
    char pad00[0x14];
    cDistributeDescription* mDesc;         // +0x14
    char pad18[4];
    IRenderHost* mpRenderHost;             // +0x1c
    char pad20[8];
    union {
        uint32_t mFlags;                   // +0x28 (bit 7: rigid-only, bit 8: samples already local,
                                           //        bit 9: no map round-trip, bit 14: shared render set)
        cEffectFlagBits mFlagBits;
    };
    cTransform_s00a8_8d50 mSourceTransform;           // +0x2c
    cTransform_s00a8_8d50 mRigidTransform;            // +0x64
    int mRenderCounter;                    // +0x9c
    float mRangeLo;                        // +0xa0
    float mRangeHi;                        // +0xa4
    char padA8[0xbc - 0xa8];
    SpVector<cDistributeSample> mSamples;  // +0xbc
    char padD0[4];
    int mTargetSampleCount;                // +0xd4
    SpVector<cRenderMesh*> mMeshes;        // +0xd8
    int mRenderIndex;                      // +0xec
    char padF0[8];
    uint8_t mRenderType;                   // +0xf8 (index into gRenderFns)
    uint8_t mRenderArg;                    // +0xf9 (opaque per-renderer byte)
    char padFA[0x15c - 0xfa];
    cISampleMap* mDensityMap;              // +0x15c
    cIMap_s00a8_8d50* mColorMap;                      // +0x160
    cISampleMap* mHeightMap;               // +0x164

    void ApplyColorAndAlpha(int first, int last);
    void ReleaseRenderSet();
    void Render(int target);
    void SetTransforms(cTransform_s00a8_8d50* source, cTransform_s00a8_8d50* rigid);
    bool ProjectSample(Vector3* pos, int i0, int i1);
    void MapSample(Vector3* pos);
};
struct cDistributeEffectPart {
    char pad00[8];
    cDistributeDescription* mDesc;         // +0x08 (= base +0x14)
    char pad0c[0x90 - 0x0c];
    int mRenderCounter;                    // +0x90 (= base +0x9c)
    char pad94[0xec - 0x94];
    uint8_t mRenderType;                   // +0xec (= base +0xf8)
    uint8_t mRenderArg;                    // +0xed (= base +0xf9)

    void Dispatch(int arg);
};
typedef void (__cdecl* RenderFn)(void* mesh, void* ctx, uint8_t* arg);
extern RenderFn gRenderFns[];              // 0x016781b0
void CopySamplesWithAddRef(void** dst, unsigned count, void** src);
int CollectSamples(cSampleTarget* target, cSampleSource* info, cSampleOut* out, int capacity);
void FillFromBaseTransform(void* base, unsigned char flag, int* count, cSampleOut** out, int* capacity);   // 0x00a6c7a0
static __forceinline Vector3 MulCols(const Matrix3_s00a8_8d50& m, const Vector3& v)
{
    return Vector3(m.m[6] * v.z + m.m[3] * v.y + m.m[0] * v.x,
                   m.m[7] * v.z + m.m[4] * v.y + m.m[1] * v.x,
                   m.m[8] * v.z + m.m[5] * v.y + m.m[2] * v.x);
}
struct cRenderParams {
    void* mpVtbl;                          // +0x00
    void* mpRenderer;                      // +0x04
    int mCount;                            // +0x08
    int mWritten;                          // +0x0c
    int mPad10;                            // +0x10
    int mPad14;                            // +0x14
};
struct IRenderer {                         // the platform renderer behind the +0x1c host chain
    virtual int Begin(int count, void* a, void* b);   // +0x00
    virtual void v1();                                 // +0x04
    virtual void End();                                // +0x08
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

// ---- items of slice s00a8d450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kSampleColor[4];                   // 0x01678318 (default sample color)
struct Vector2_s00a8_d450 {
  float x, y;
  Vector2_s00a8_d450() {}
  Vector2_s00a8_d450(float _x, float _y) : x(_x), y(_y) {}
  Vector2_s00a8_d450(const Vector2_s00a8_d450& v) : x(v.x), y(v.y) {}
};
struct Matrix3_s00a8_d450 {
  Vector3 row[3];
  Matrix3_s00a8_d450(const Matrix3_s00a8_d450& m);                          // 0x0041cb40
};
extern const Vector2_s00a8_d450 kVector2Zero_s00a8_d450;                    // 0x0167824c
extern const Vector2_s00a8_d450 kVector2One_s00a8_d450;                     // 0x01678260
extern const Matrix3_s00a8_d450 kMatrix3Identity_s00a8_d450;                // 0x01678328
static inline void FastSinCos_s00a8_d450(float a, float& s, float& c) {
  float t = a * gSinCosInvStep + 12582912.0f;
  int bits = *(int*)&t;
  float r = a - (float)(bits - 0x4b400000) * gSinCosStep;
  int i = (bits & 0xf) * 2;
  float s0 = gSinCosTable[i];
  float c0 = gSinCosTable[i + 1];
  c = c0 - (r * c0 * 0.5f + s0) * r;
  s = (c0 - r * s0 * 0.5f) * r + s0;
}
static inline Vector3 Rotate_s00a8_d450(const Vector3& v, const Matrix3_s00a8_d450& m) {
  return Vector3(m.row[0].x * v.x + m.row[2].x * v.z + m.row[1].x * v.y,
                 m.row[1].y * v.y + m.row[2].y * v.z + m.row[0].y * v.x,
                 m.row[2].z * v.z + m.row[1].z * v.y + m.row[0].z * v.x);
}
namespace EA {
namespace Swarm {
Vector2_s00a8_d450 SquareToCircle(Vector2_s00a8_d450 p);                    // 0x00a7c630 (cdecl, by value)
}
}
namespace EA {
namespace Swarm {
struct cTransformData {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  float mOffset[3];                                   // +0x04
  float mScale;                                       // +0x10
  float mRotation[9];                                 // +0x14
  void PreTransformBy(const struct cTransform_s00a8_d450& t);    // 0x00537f40
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00a8_d450 {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3_s00a8_d450 mRotation;                                  // +0x14

  cTransform_s00a8_d450() : mFlags(0), mModCount(0), mRotation(kMatrix3Identity_s00a8_d450) {}
  cTransform_s00a8_d450(const cTransform_s00a8_d450& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform_s00a8_d450& operator=(const cTransform_s00a8_d450& t);         // 0x00537dc0
  void SetRotation(const Matrix3_s00a8_d450& m) {
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
}
}
namespace EA {
namespace Swarm {
struct cHalton2D_s00a8_d450 {
  Vector2_s00a8_d450 mValue;                                     // +0x00
  int mIndex;                                         // +0x08
  int mDigits3;                                       // +0x0c
  cHalton2D_s00a8_d450() : mValue(kVector2Zero_s00a8_d450), mIndex(0), mDigits3(0) {}
  void Seed(int index);                               // 0x00a7c3d0
  int Next();                                         // 0x00a7c350
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeDescription_s00a8_d450 {
  uint32_t pad00[2];
  uint32_t mFlags;                                    // +0x08 (bit 13: reseed every 256)
  uint32_t pad0c[3];
  int mSeed;                                          // +0x18
  uint8_t mSourceType;                                // +0x1c (2D shape: square, circle, ring)
  uint8_t pad1d[3];
  float mScale;                                       // +0x20
  cTransform_s00a8_d450 mTransform;                              // +0x24
  float mRingInnerRadius;                             // +0x5c
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeSample_s00a8_d450 {
  cTransformData mTransform;                          // +0x00
  float mColor[4];                                    // +0x38
  int mIndex;                                         // +0x48
  cDistributeSample_s00a8_d450() {}
  cDistributeSample_s00a8_d450(const cDistributeSample_s00a8_d450& s);      // 0x00a89de0
};
}
}
namespace EA {
namespace Swarm {
struct SampleVector_s00a8_d450 {
  cDistributeSample_s00a8_d450* mpBegin;
  cDistributeSample_s00a8_d450* mpEnd;
  cDistributeSample_s00a8_d450* mpCapacity;
  uint32_t mAllocator[2];
  void DoInsertValue(cDistributeSample_s00a8_d450* position, const cDistributeSample_s00a8_d450& value);  // 0x00a8ce30
  void push_back(const cDistributeSample_s00a8_d450& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) cDistributeSample_s00a8_d450(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeEffect_s00a8_d450 {
  uint32_t pad00[0x14 / 4];
  cDistributeDescription_s00a8_d450* mDesc;                      // +0x014
  uint32_t pad18[(0x28 - 0x18) / 4];
  uint32_t mFlags;                                    // +0x028 (bit 4: sphere band, bit 5: cube sphere)
  cTransform_s00a8_d450 mSourceTransform;                        // +0x02c
  uint32_t pad64[(0xbc - 0x64) / 4];
  SampleVector_s00a8_d450 mSamples;                              // +0x0bc
  uint32_t padd0[(0x100 - 0xd0) / 4];
  Vector3 mSubdivOffset;                              // +0x100
  Vector3 mSubdivScale;                               // +0x10c
  struct cSubdivOwner { uint32_t pad[4]; cTransform_s00a8_d450* mpTransform; }* mSubdivOwner;  // +0x118
  uint32_t pad11c[(0x15c - 0x11c) / 4];
  void* mEmitMap;                                     // +0x15c
  void* mColorMap;                                    // +0x160
  void* mPinMap;                                      // +0x164
  uint32_t pad168[(0x18c - 0x168) / 4];
  float mSizeScale;                                   // +0x18c

  bool IsMaskedOut(const Vector3& pos, int index, int count);  // 0x00a89a90
  void PinToMap(Vector3& pos);                        // 0x00a89ce0
  void CreateSamples2D(int count, int first, int last);  // 0x00a8d450 (EA::Swarm::cDistributeEffect::CreateSamples2D)
};
}
}
// ---- items of slice s00a8d450 end

// ---- items of slice s00a8dea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector2_s00a8_dea0 {
  float x, y;
  Vector2_s00a8_dea0() {}
  Vector2_s00a8_dea0(float _x, float _y) : x(_x), y(_y) {}
  Vector2_s00a8_dea0(const Vector2_s00a8_dea0& v) : x(v.x), y(v.y) {}
};
struct Matrix3_s00a8_dea0 {
  Vector3 row[3];
  Matrix3_s00a8_dea0(const Matrix3_s00a8_dea0& m);                          // 0x0041cb40
};
extern const Vector2_s00a8_dea0 kVector2Zero_s00a8_dea0;                    // 0x0167824c
extern const Vector2_s00a8_dea0 kVector2One_s00a8_dea0;                     // 0x01678260
extern const Vector3 kVector3Zero_s00a8_dea0;                    // 0x0167827c
extern const Matrix3_s00a8_dea0 kMatrix3Identity_s00a8_dea0;                // 0x01678328
static inline void FastSinCos_s00a8_dea0(float a, float& s, float& c) {
  float t = a * gSinCosInvStep + 12582912.0f;
  int bits = *(int*)&t;
  float r = a - (float)(bits - 0x4b400000) * gSinCosStep;
  int i = (bits & 0xf) * 2;
  float s0 = gSinCosTable[i];
  volatile float c0 = gSinCosTable[i + 1];
  c = c0 - (r * c0 * 0.5f + s0) * r;
  s = (c0 - r * s0 * 0.5f) * r + s0;
}
static inline Vector3 Rotate_s00a8_dea0(const Vector3& v, const Matrix3_s00a8_dea0& m) {
  return Vector3(m.row[0].x * v.x + m.row[2].x * v.z + m.row[1].x * v.y,
                 m.row[1].y * v.y + m.row[2].y * v.z + m.row[0].y * v.x,
                 m.row[2].z * v.z + m.row[1].z * v.y + m.row[0].z * v.x);
}
namespace EA {
namespace Swarm {
Vector2_s00a8_dea0 SquareToCircle(Vector2_s00a8_dea0 p);                    // 0x00a7c630 (cdecl, by value)
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00a8_dea0 {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3_s00a8_dea0 mRotation;                                  // +0x14

  cTransform_s00a8_dea0()
      : mFlags(0), mModCount(0), mOffset(kVector3Zero_s00a8_dea0), mScale(1.0f),
        mRotation(kMatrix3Identity_s00a8_dea0) {}
  cTransform_s00a8_dea0(const cTransform_s00a8_dea0& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform_s00a8_dea0& operator=(const cTransform_s00a8_dea0& t);         // 0x00537dc0
  // retail: rotation and offset setters bump the modification count
  void SetRotation(const Matrix3_s00a8_dea0& m) {
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
  void PreTransformBy(const cTransform_s00a8_dea0& t);           // 0x00537f40
};
}
}
namespace EA {
namespace Swarm {
struct cHalton2D_s00a8_dea0 {
  Vector2_s00a8_dea0 mValue;                                     // +0x00
  int mIndex;                                         // +0x08
  int mDigits3;                                       // +0x0c
  cHalton2D_s00a8_dea0() : mValue(kVector2Zero_s00a8_dea0), mIndex(0), mDigits3(0) {}
  void Seed(int index);                               // 0x00a7c3d0
  int Next();                                         // 0x00a7c350
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeDescription_s00a8_dea0 {
  uint32_t pad00[2];
  uint32_t mFlags;                                    // +0x08 (bit 13: reseed every 256)
  uint32_t pad0c[3];
  int mSeed;                                          // +0x18
  uint8_t mSourceType;                                // +0x1c
  uint8_t pad1d[3];
  float mScale;                                       // +0x20
  cTransform_s00a8_dea0 mTransform;                              // +0x24
  float mRingInnerRadius;                             // +0x5c
  uint8_t pad60[0x160 - 0x60];
  int mNumClusters;                                   // +0x160 (cells N)
  int mClusterStart;                                  // +0x164 (first cell index)
  float mClusterScale;                                // +0x168
  float* mCurveBegin;                                 // +0x16c (size curve)
  float* mCurveEnd;                                   // +0x170
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeSample_s00a8_dea0 {
  uint32_t data[0x4c / 4];
  cDistributeSample_s00a8_dea0(const cTransform_s00a8_dea0& t, int index);  // 0x00a89980
  cDistributeSample_s00a8_dea0(const cDistributeSample_s00a8_dea0& s);      // 0x00a89de0
};
}
}
namespace EA {
namespace Swarm {
struct SampleVector_s00a8_dea0 {
  cDistributeSample_s00a8_dea0* mpBegin;
  cDistributeSample_s00a8_dea0* mpEnd;
  cDistributeSample_s00a8_dea0* mpCapacity;
  uint32_t mAllocator[2];
  void DoInsertValue(cDistributeSample_s00a8_dea0* position, const cDistributeSample_s00a8_dea0& value);  // 0x00a8ce30
  void push_back(const cDistributeSample_s00a8_dea0& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) cDistributeSample_s00a8_dea0(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeEffect_s00a8_dea0 {
  uint32_t pad00[0x14 / 4];
  cDistributeDescription_s00a8_dea0* mDesc;                      // +0x014
  uint32_t pad18[(0x28 - 0x18) / 4];
  uint32_t mFlags;                                    // +0x028 (bit 4: sphere band, bit 5: cube sphere)
  cTransform_s00a8_dea0 mSourceTransform;                        // +0x02c
  uint32_t pad64[(0xbc - 0x64) / 4];
  SampleVector_s00a8_dea0 mSamples;                              // +0x0bc
  uint32_t padd0[(0x100 - 0xd0) / 4];
  Vector3 mSubdivOffset;                              // +0x100
  Vector3 mSubdivScale;                               // +0x10c
  struct cSubdivOwner { uint32_t pad[4]; cTransform_s00a8_dea0* mpTransform; }* mSubdivOwner;  // +0x118
  uint32_t pad11c[(0x15c - 0x11c) / 4];
  void* mEmitMap;                                     // +0x15c
  void* mColorMap;                                    // +0x160
  void* mPinMap;                                      // +0x164
  uint32_t pad168[(0x18c - 0x168) / 4];
  float mSizeScale;                                   // +0x18c

  bool IsMaskedOut(const Vector3& pos, int index, int count);  // 0x00a89a90
  void PinToMap(Vector3& pos);                        // 0x00a89ce0
  void CreateClusteredSamples2D(int count, int first, int last);  // 0x00a8dea0 (EA::Swarm::cDistributeEffect::CreateClusteredSamples2D)
  inline void AddSample_s00a8_dea0(cTransform_s00a8_dea0& sampleTransform, Vector3& pos, int index, int count);
};
}
}
namespace EA {
namespace Swarm {
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
}
}
// ---- items of slice s00a8dea0 end

// ---- items of slice s00a85c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01485378;          // 0.0f
typedef uint16_t uint16;
typedef uint8_t  uint8;
struct Vector3_s00a8_5c00 { float x, y, z; };
struct FloatCurve {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAllocator[2];
};
typedef FloatCurve FloatVec;
struct cIRefObj_s00a8_5c00 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void SetHandle(uint32 h);
};
struct cDistributeDescInit;
struct cSimulatorWorld;
struct cDistributeSimulator {
    volatile uint32 mVtbl00;              // +0x000 (GmeIComponent / simulator)
    volatile uint32 mVtbl04;              // +0x004 (GmeRefCount)
    uint32 pad08;
    cDistributeDescInit* mDesc;           // +0x00c
    uint8  mActive;                       // +0x010
    uint8  pad11[3];
    uint16 mFlags14;                      // +0x014
    uint16 mModCount16;                   // +0x016
    float  mCenterX;                      // +0x018
    float  mCenterY;                      // +0x01c
    float  mCenterZ;                      // +0x020
    float  mRadius;                       // +0x024
    char   pad28[0x38 - 0x28];
    uint32 pad38[(0x4c - 0x38) / 4];
    float  mParam4c;                      // +0x04c
    float  mParam50;                      // +0x050
    float  mParam54;                      // +0x054
    float  mParam58;                      // +0x058
    float  mParam5c;                      // +0x05c
    float  mParam60;                      // +0x060
    float  mParam64;                      // +0x064
    float  mParam68;                      // +0x068
    float  mParam6c;                      // +0x06c
    float  mParam70;                      // +0x070
    float  mParam74;                      // +0x074
    float  mParam78;                      // +0x078
    uint8  mParam7c;                      // +0x07c
    char   pad7d[0x84 - 0x7d];
    float  mParam84;                      // +0x084
    cIRefObj_s00a8_5c00* mpRef88;                    // +0x088
    cIRefObj_s00a8_5c00* mpRef8c;                    // +0x08c
    void*  mHandle90;                     // +0x090
    char   pad94[0x98 - 0x94];
    long long mValueL;                    // +0x098 (int pair: lo = mParam98, hi = mParam9c)
    char   padA0[0xb0 - 0xa0];
    uint32 mHandleB0;                     // +0x0b0
    uint32 mHandleB4;                     // +0x0b4

    cDistributeSimulator(uint32 desc);                    // 0x00a86120
    void* Destroy(uint32 flags);                          // 0x00a86210
    void Initialize(int a, cSimulatorWorld* world, int c); // 0x00a86270
    void Update(float dt);                                // 0x00a86590

    bool OnMessage(int msg, int* pValue, int a3);         // 0x00a85ed0
    bool SetParams(int msg, float* p, int a3);            // 0x00a86050
    void SetEmitterFlags(bool on);                        // 0x00a860e0
    void Deactivate(int unused);                          // 0x00a86010
    void ReleaseEmitter();                                // 0x00a85fb0
};
struct cSimulatorWorld {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual cIRefObj_s00a8_5c00* GetObjByIdx(uint8 idx);             // +0x24
    virtual void SlotA();
    virtual void SlotB();
    virtual void SlotC();
    virtual void SlotD();
    virtual void SlotE();
    virtual void SlotF();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot1a();
    virtual void Slot1b();
    virtual void Slot1c();
    virtual void Slot1d();
    virtual void Slot1e();
    virtual void Slot1f();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual cIRefObj_s00a8_5c00* GetObjById(uint32 idLo, uint32 idHi); // +0x8c
};
struct cDistributeDescInit {
    volatile uint32 mVtbl00;              // +0x000
    volatile uint32 mVtbl04;              // +0x004
    uint32 mMask;                         // +0x008 (bitset; bit0 mode, bit1 map)
    uint8  mParam0c;                      // +0x00c
    uint8  mParam0d;                      // +0x00d
    uint16 mParam0e;                      // +0x00e
    uint32 mParam10;                      // +0x010
    uint32 mParam14;                      // +0x014
    uint8  mParam18;                      // +0x018
    uint8  mParam19;                      // +0x019
    uint8  mParam1a;                      // +0x01a
    uint8  mParam1b;                      // +0x01b
    uint16 mParam1c;                      // +0x01c
    uint16 pad1e;                         // +0x01e
    float  mParam20;                      // +0x020
    uint32 pad24[(0x28 - 0x24) / 4];
    uint32 mParam28;                      // +0x028
    uint32 mParam2c;                      // +0x02c
    float  mParam30;                      // +0x030
    FloatCurve mCurve34;                  // +0x034
    FloatCurve mCurve48;                  // +0x048
    FloatCurve mCurve5c;                  // +0x05c
    FloatCurve mCurve70;                  // +0x070
    FloatCurve mCurve84;                  // +0x084
    float  mParam98;                      // +0x098
    float  mParam9c;                      // +0x09c
    float  mParamA0;                      // +0x0a0
    float  mParamA4;                      // +0x0a4
    float  mParamA8;                      // +0x0a8
    float  mParamAC;                      // +0x0ac
    uint32 mParamB0;                      // +0x0b0
    uint32 mParamB4;                      // +0x0b4

    cDistributeDescInit();
};
struct cSPTransform_s00a8_5c00 {
    float f[0x38 / 4];
    cSPTransform_s00a8_5c00(const void* src);            // 0x538000
    void* Assign(const void* src);            // 0x537dc0
};
struct cSPTransformOps { void* Assign(const void* src); };
static inline float SampleCurve_s00a8_5c00(const FloatCurve& c, float t)
{
    unsigned n = (unsigned)(c.mpEnd - c.mpBegin) - 1;
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n;
    unsigned idx = (unsigned)(f * t);
    float frac = f * t - (float)idx;
    if (frac <= DAT_01485378)
        return c.mpBegin[idx];
    return (c.mpBegin[idx + 1] - c.mpBegin[idx]) * frac + c.mpBegin[idx];
}
static inline void SampleCurve3_s00a8_5c00(const FloatVec& cv, float t, float* out)
{
    const Vector3_s00a8_5c00* b = (const Vector3_s00a8_5c00*)cv.mpBegin;
    const Vector3_s00a8_5c00* e = (const Vector3_s00a8_5c00*)cv.mpEnd;
    if (b == e) {
        out[0] = 1.0f; out[1] = 1.0f; out[2] = 1.0f;
        return;
    }
    unsigned n = (unsigned)(e - b) - 1;
    if (n == 0) {
        out[0] = b[0].x; out[1] = b[0].y; out[2] = b[0].z;
        return;
    }
    float f = (float)n;
    unsigned idx = (unsigned)(f * t);
    float frac = f * t - (float)idx;
    if (frac <= DAT_01485378) {
        out[0] = b[idx].x; out[1] = b[idx].y; out[2] = b[idx].z;
    } else {
        out[0] = b[idx].x + (b[idx + 1].x - b[idx].x) * frac;
        out[1] = b[idx].y + (b[idx + 1].y - b[idx].y) * frac;
        out[2] = b[idx].z + (b[idx + 1].z - b[idx].z) * frac;
    }
}
// ---- items of slice s00a85c00 end

// ---- items of slice s00a86b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __cdecl MulVec(void* dst, const void* src);   // 0x00705290
struct ElemTail {
    int a, b, c, d, e, f;
    void __thiscall CopyFrom(const ElemTail* o);   // 0x006f50f0
    ElemTail& __thiscall operator=(const ElemTail& o);  // 0x006f5cd0
};
struct Elem {
    void* p0;        // +0x00
    int   pad4;      // +0x04 (not copied)
    void* p8;        // +0x08
    void* pc;        // +0x0c
    float f10;       // +0x10
    float f14, f18, f1c, f20, f24, f28, f2c, f30, f34;
    void* p38;       // +0x38
    void* p3c;       // +0x3c
    ElemTail tail;   // +0x40

    Elem* __thiscall CopyFrom(const Elem* o);
    Elem* __thiscall AssignFrom(const Elem* o);
};
struct SimVectorF {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    __declspec(nothrow) ~SimVectorF() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};
struct SimVector58 {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCapacity;
    void __thiscall FreeRange(Elem* first, Elem* last);   // 0x00a87300
    void __thiscall Insert(Elem* pos, unsigned count, const Elem* value);  // 0x00a87980
    SimVector58* __thiscall Assign(SimVector58* src);                      // 0x00a87b90
    void __thiscall EraseRange(Elem* first, Elem* last);                   // 0x00a87cd0
    void __thiscall Resize(unsigned n);
    __declspec(nothrow) ~SimVector58()
    {
        FreeRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct Sim {
    char pad00[0x8];        // vptr + refcount
    char pad08[0x58];
    SimVectorF v60;         // +0x060
    char pad6c[0xc];
    SimVectorF v78;         // +0x078
    char pad84[0x8];
    SimVectorF v8c;         // +0x08c
    char pad98[0x8];
    SimVectorF va0;         // +0x0a0
    char pad_ac[0x20];
    SimVectorF vcc;         // +0x0cc
    char pad_d8[0x14];
    SimVectorF vec;         // +0x0ec
    char pad_f8[0xc];
    SimVector58 v104;       // +0x104
    char pad110[0x5c];
    SimVectorF v16c;        // +0x16c
};
template <class T> static inline T& Fld(void* base, unsigned off) { return *(T*)((char*)base + off); }
template <class T> static inline T* At(void* base, unsigned off) { return (T*)((char*)base + off); }
struct TransOps {
    char data[0x38];
    TransOps* __thiscall Assign(const void* src);   // 0x00537dc0
};
struct Notifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Notify(void* p);    // +0x14
};
struct Vec3 {
    float x, y, z;
};
static float __cdecl SampleCurve_s00a8_6b30(const float* v, unsigned count, float t)
{
    unsigned segs = count - 1;
    if (segs == 0)
        return v[0];
    float fs = (float)segs;
    int i = (int)(fs * t);
    float frac = fs * t - (float)i;
    if (frac <= 0.0f)
        return v[i];
    return (v[i + 1] - v[i]) * frac + v[i];
}
static Vec3 __cdecl SampleVec3(const Vec3* v, unsigned count, float t)
{
    Vec3 r;
    unsigned segs = count - 1;
    if (segs == 0) {
        r = v[0];
        return r;
    }
    float fs = (float)segs;
    int i = (int)(fs * t);
    float frac = fs * t - (float)i;
    if (frac <= 0.0f) {
        r = v[i];
        return r;
    }
    r.x = (v[i + 1].x - v[i].x) * frac + v[i].x;
    r.y = (v[i + 1].y - v[i].y) * frac + v[i].y;
    r.z = (v[i + 1].z - v[i].z) * frac + v[i].z;
    return r;
}
struct SampleIface {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual bool QueryVec(const float* v);          // +0x18
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual void Transform(const void* out, const float* in);   // +0x2c
};
struct SimUpd : Sim {
    void Update(float dt, float blend, void* ctx);
};
// ---- items of slice s00a86b30 end

// ---- items of slice s00a87fb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01678264;
extern const float DAT_01678260;
extern const float DAT_01678300;
extern const float DAT_01678314;
extern const float DAT_01485720;
extern const float DAT_01471064;
extern const float DAT_014853e0;
extern const float DAT_0147b9f0;
extern const float DAT_013eb8a0;
extern "C" double RandomRange(float lo, float hi);   // 0x007d45d0
extern const float DAT_01678278_s00a8_7fb0;
extern const float DAT_0156502c_s00a8_7fb0;
extern const float DAT_01677840_s00a8_7fb0[];
struct Vector3_s00a8_7fb0 { float x, y, z; };
struct Vector2_s00a8_7fb0 { float x, y; };
union U64 { struct { uint32_t lo, hi; }; uint64_t v; };
struct cTransform_s00a8_7fb0 {                    // 0x38 bytes
    uint16_t mFlags;                   // +0x00
    uint16_t mModificationCount;       // +0x02
    Vector3_s00a8_7fb0  mTranslation;             // +0x04
    float    mScale;                   // +0x10
    Matrix3  mRotation;                // +0x14

    void PreRotateX(float angle);      // 0x005a2d90
    void RotateY(float angle);         // 0x006b9050
    void RotateZ(float angle);         // 0x007d1ac0
};
template <class T> struct SpVector_s00a8_7fb0 {   // eastl::vector with sp_vector_allocator (retail 0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};
double RandomSymmetric(float range);                 // 0x00a78f80
static __forceinline float SampleCurve1_s00a8_7fb0(const SpVector_s00a8_7fb0<float>& c, float t)
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
struct cDistributeSample_s00a8_7fb0 {             // 0x4c bytes
    cTransform_s00a8_7fb0 mTransform;             // +0x00
    Vector4    mColorAlpha;            // +0x38
    int        mNumber;                // +0x48
};
struct cSurfaceRec {                   // 0x18 bytes
    void*    mSurface;                 // +0x00
    void*    mSurfaceInfo;             // +0x04
    uint32_t mNumStateBytes;           // +0x08
    uint32_t mStateDataOffset;         // +0x0c
    uint32_t mNumParticleBytes;        // +0x10
    uint32_t mParticleDataOffset;      // +0x14
};
struct cDistributeDescription_s00a8_7fb0 {        // 0x120 bytes
    char     pad00[8];
    uint32_t mFlags;                   // +0x08
    char     pad0c[0x60 - 0x0c];
    SpVector_s00a8_7fb0<float> mSizeCurve;        // +0x60
    float    mSizeVary;                // +0x74
    SpVector_s00a8_7fb0<float> mPitchCurve;       // +0x78
    SpVector_s00a8_7fb0<float> mRollCurve;        // +0x8c
    SpVector_s00a8_7fb0<float> mHeadingCurve;     // +0xa0
    float    mPitchVary;               // +0xb4
    float    mRollVary;                // +0xb8
    float    mHeadingVary;             // +0xbc
    float    mPitchOffset;             // +0xc0
    float    mRollOffset;              // +0xc4
    float    mHeadingOffset;           // +0xc8
    char     padcc[0x120 - 0xcc];
};
struct cIEffectsWorld {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void* v20();  // +0x20 -> object with +0x24 / +0x38 methods
};
struct IWorldThing {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void SetVisibleA(int id, bool visible);   // +0x24
    virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void SetVisibleB(int id, bool visible);   // +0x38
};
struct cDistributeEffect_s00a8_7fb0 {
    char        pad00[0x14];
    cDistributeDescription_s00a8_7fb0* mDesc;     // +0x14
    int         mCollectionIndex;      // +0x18
    cIEffectsWorld* mWorld;            // +0x1c
    void*       mGlobalParams;         // +0x20
    void*       mChildParams;          // +0x24
    uint32_t    mFlags;                // +0x28
    cTransform_s00a8_7fb0  mSourceTransform;      // +0x2c
    cTransform_s00a8_7fb0  mRigidTransform;       // +0x64
    int         mRenderCount;          // +0x9c
    Vector2_s00a8_7fb0     mParamAltitudeRange;   // +0xa0
    SpVector_s00a8_7fb0<cDistributeSample_s00a8_7fb0> mRenderSamples;  // +0xa8
    SpVector_s00a8_7fb0<cDistributeSample_s00a8_7fb0> mSamples;        // +0xbc
    int         mCurrentSampleCount;   // +0xc8
    int         mTargetSampleCount;    // +0xd4
    char        padd0[0xdc - 0xd0];
    SpVector_s00a8_7fb0<void*> mEffects;          // +0xd0
    int         mSetID;                // +0xe0
    uint64_t    mOverrideID;           // +0xe8
    uint8_t     mCurrentFormat;        // +0xf0
    uint8_t     mOffsets[5];           // +0xf1
    char        padf6[0xf8 - 0xf6];
    Vector3_s00a8_7fb0     mSubdivOffset;         // +0xf8
    Vector3_s00a8_7fb0     mSubdivScale;          // +0x104
    void*       mSubdivOwner;          // +0x110
    SpVector_s00a8_7fb0<cSurfaceRec> mSurfaceRecs;// +0x114
    SpVector_s00a8_7fb0<uint8_t> mSurfaceStateData; // +0x124
    SpVector_s00a8_7fb0<uint8_t> mSurfaceSampleData;// +0x134
    int         mSampleDataSize;       // +0x144
    void*       mEmitMap;              // +0x148
    void*       mColorMap;             // +0x14c
    void*       mPinMap;               // +0x150
    uint32_t    mMapModCount;          // +0x154
    float       mUpdateTime;           // +0x158
    Vector3_s00a8_7fb0     mColorScale;           // +0x15c
    float       mCurrentAlphaScale;    // +0x168
    float       mAlphaScale;           // +0x16c
    Vector2_s00a8_7fb0     mLODAlphaScale;        // +0x170
    float       mSizeScale;            // +0x178
    uint32_t    mSeqID;                // +0x17c
    uint32_t    mSeqCount;             // +0x180

    void FUN_00a87fb0(void* stream, int base);                        // 0x00a87fb0
    __int64 FUN_00a88220();                                       // 0x00a88220
    bool FUN_00a88350();                                              // 0x00a88350
    int  FUN_00a88390(int count, void** outBegin, void** outStride);  // 0x00a88390
    void FUN_00a886f0(int visible);                                   // 0x00a886f0
    void FUN_00a887b0(int index, float value);                        // 0x00a887b0
    void RigidTransformRange(int first, int last);                    // 0x00a88800
};
// ---- items of slice s00a87fb0 end

// ---- items of slice s00a89de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0041cb40(void* dst, const void* src);   // Matrix3::Assign
extern "C" void* FUN_00537dc0(void* dst, const void* src);   // cSPTransformOps::Assign
struct Vector3_s00a8_9de0 { float x, y, z; };
struct cTransform {                    // 0x38 bytes
    uint16_t mFlags;                   // +0x00
    uint16_t mModificationCount;       // +0x02
    Vector3_s00a8_9de0  mTranslation;             // +0x04
    float    mScale;                   // +0x10
    Matrix3  mRotation;                // +0x14
};
struct cDistributeSample_s00a8_9de0 {             // 0x4c bytes
    cTransform mTransform;             // +0x00
    float      mColorAlpha[4];         // +0x38
    int        mNumber;                // +0x48

    cDistributeSample_s00a8_9de0(const cDistributeSample_s00a8_9de0& src);            // 0x00a89de0
    void Assign(const cDistributeSample_s00a8_9de0* src);                  // 0x00a8a0a0-family element assign
};
// ---- items of slice s00a89de0 end

// ---- items of slice s00a8a450 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3_s00a8_a450 {
  Vector3 row[3];
  Matrix3_s00a8_a450() {}
  Matrix3_s00a8_a450(const Matrix3_s00a8_a450& m) { row[0] = m.row[0]; row[1] = m.row[1]; row[2] = m.row[2]; }
};
struct cTransform_s00a8_a450 {
  uint16_t mFlags;      // +0x00
  uint16_t mModCount;   // +0x02
  Vector3  mOffset;     // +0x04
  float    mScale;      // +0x10
  Matrix3_s00a8_a450  mRotation;   // +0x14
  cTransform_s00a8_a450() {}
  cTransform_s00a8_a450(const cTransform_s00a8_a450& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  void PostTransformBy(const cTransform_s00a8_a450& parent);   // 0x00a8a140
};
struct cDistributeSample_s00a8_a450 {
  cTransform_s00a8_a450 mTransform;   // +0x00
  float      mColor[4];    // +0x38
  int        mIndex;       // +0x48
};
struct OutRow {
  Vector3 v;
  float   w;
};
struct cDistributeEffect_s00a8_a450 {
  uint8_t             pad00[0x64];
  cTransform_s00a8_a450          mTransform;        // +0x64
  int                 mRenderCount;      // +0x9c
  uint8_t             pad_a0[0x8];
  cDistributeSample_s00a8_a450*  mSamplesBegin;     // +0xa8
  cDistributeSample_s00a8_a450*  mSamplesEnd;       // +0xac
  uint8_t             pad_b0[0x28];
  cDistributeEffect_s00a8_a450** mInstancesBegin;   // +0xd8
  cDistributeEffect_s00a8_a450** mInstancesEnd;     // +0xdc
  uint8_t             pad_e0[0x19];
  uint8_t             mPosOffset;        // +0xf9
  uint8_t             mColorOffset;      // +0xfa
  uint8_t             pad_fb[0x17c - 0xfb];
  float               mAlphaScale;       // +0x17c

  void Stream_Quad_V3F_C4B_T2F(struct IVertexStream* stream);
};
struct IVertexStream {
  virtual int  Acquire(int count, uint8_t** ppBuffer, int* pStride);   // slot 0
  virtual void Commit();                                               // slot 1
};
// ---- items of slice s00a8a450 end

// ---- items of slice s00a8aec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Swarm {
struct Vector3_s00a8_aec0 {
  float x, y, z;
  Vector3_s00a8_aec0() {}
  Vector3_s00a8_aec0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3_s00a8_aec0(const Vector3_s00a8_aec0& v) : x(v.x), y(v.y), z(v.z) {}
};
}
}
namespace EA {
namespace Swarm {
struct Matrix3_s00a8_aec0 {
  Vector3_s00a8_aec0 row[3];
  Matrix3_s00a8_aec0() {}
  Matrix3_s00a8_aec0(const Matrix3_s00a8_aec0& m) { row[0] = m.row[0]; row[1] = m.row[1]; row[2] = m.row[2]; }
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00a8_aec0 {
  uint16_t mFlags;      // +0x00
  uint16_t mModCount;   // +0x02
  Vector3_s00a8_aec0  mOffset;     // +0x04
  float    mScale;      // +0x10
  Matrix3_s00a8_aec0  mRotation;   // +0x14
  cTransform_s00a8_aec0() {}
  cTransform_s00a8_aec0(const cTransform_s00a8_aec0& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  void PostTransformBy(const cTransform_s00a8_aec0& parent);   // 0x00a8a140
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeSample_s00a8_aec0 {
  cTransform_s00a8_aec0 mTransform;   // +0x00
  float      mColor[4];    // +0x38
  int        mIndex;       // +0x48
};
}
}
namespace EA {
namespace Swarm {
struct IVertexStream_s00a8_aec0 {
  virtual int  Acquire(int count, uint8_t** ppBuffer, int* pStride);   // slot 0
  virtual void Slot1();                                                // slot 1
  virtual void Commit();                                               // slot 2
};
}
}
namespace EA {
namespace Swarm {
class cDistributeEffect_s00a8_aec0 { public:
  uint8_t             pad00[0x64];
  cTransform_s00a8_aec0          mTransform;        // +0x64
  uint8_t             pad_a0[0xa8 - 0x9c];
  cDistributeSample_s00a8_aec0*  mSamplesBegin;     // +0xa8
  cDistributeSample_s00a8_aec0*  mSamplesEnd;       // +0xac
  uint8_t             pad_b0[0xd4 - 0xb0];
  int                 mDivisor;          // +0xd4
};
}
}
namespace EA {
namespace Swarm {
struct V4F { float x, y, z, w; };
}
}
namespace EA {
namespace Swarm {
struct T2F { float u, v; };
}
}
namespace EA {
namespace Swarm {
static __forceinline uint8_t ColorToByte(float v)
{
  __m128 x = _mm_max_ss(_mm_set_ss(0.0f), _mm_set_ss(v));
  x = _mm_mul_ss(x, _mm_set_ss(255.0f));
  x = _mm_min_ss(x, _mm_set_ss(255.0f));
  return (uint8_t)_mm_cvt_ss2si(x);
}
}
}
namespace EA {
namespace Swarm {
static __forceinline void WriteVertex(uint8_t*& pPos, uint8_t*& pNrm, uint8_t*& pCol, uint8_t*& pTex,
                                      int stride, const cTransform_s00a8_aec0& xf, float t, uint32_t color,
                                      const T2F& uv)
{
  V4F& v = *(V4F*)pPos;
  v.x = xf.mOffset.x;
  v.y = xf.mOffset.y;
  v.z = xf.mOffset.z;
  v.w = t;
  pPos += stride;

  V4F& nm = *(V4F*)pNrm;
  nm.x = xf.mRotation.row[2].x;
  nm.y = xf.mRotation.row[2].y;
  nm.z = xf.mRotation.row[2].z;
  nm.w = xf.mScale;
  pNrm += stride;

  *(uint32_t*)pCol = color;
  pCol += stride;

  *(T2F*)pTex = uv;
  pTex += stride;
}
}
}
namespace EA {
namespace Swarm {
static __forceinline void WriteVertex(uint8_t*& pPos, uint8_t*& pNrm, uint8_t*& pCol, uint8_t*& pTex,
                                      int stride, const cTransform_s00a8_aec0& xf, float t, uint32_t color,
                                      uint32_t uv)
{
  V4F& v = *(V4F*)pPos;
  v.x = xf.mOffset.x;
  v.y = xf.mOffset.y;
  v.z = xf.mOffset.z;
  v.w = t;
  pPos += stride;

  V4F& nm = *(V4F*)pNrm;
  nm.x = xf.mRotation.row[2].x;
  nm.y = xf.mRotation.row[2].y;
  nm.z = xf.mRotation.row[2].z;
  nm.w = xf.mScale;
  pNrm += stride;

  *(uint32_t*)pCol = color;
  pCol += stride;

  *(uint32_t*)pTex = uv;
  pTex += stride;
}
}
}
// ---- items of slice s00a8aec0 end

// ---- items of slice s00a8b940 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Swarm {
struct Vector3_s00a8_b940 {
  float x, y, z;
  Vector3_s00a8_b940() {}
  Vector3_s00a8_b940(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3_s00a8_b940(const Vector3_s00a8_b940& v) : x(v.x), y(v.y), z(v.z) {}
};
}
}
namespace EA {
namespace Swarm {
struct Matrix3_s00a8_b940 {
  Vector3_s00a8_b940 row[3];
  Matrix3_s00a8_b940() {}
  Matrix3_s00a8_b940(const Matrix3_s00a8_b940& m) { row[0] = m.row[0]; row[1] = m.row[1]; row[2] = m.row[2]; }
};
}
}
namespace EA {
namespace Swarm {
struct cTransform_s00a8_b940 {
  uint16_t mFlags;      // +0x00
  uint16_t mModCount;   // +0x02
  Vector3_s00a8_b940  mOffset;     // +0x04
  float    mScale;      // +0x10
  Matrix3_s00a8_b940  mRotation;   // +0x14
  cTransform_s00a8_b940() {}
  cTransform_s00a8_b940(const cTransform_s00a8_b940& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  void PostTransformBy(const cTransform_s00a8_b940& parent);   // 0x00a8a140
};
}
}
namespace EA {
namespace Swarm {
struct cDistributeSample_s00a8_b940 {
  cTransform_s00a8_b940 mTransform;   // +0x00
  float      mColor[4];    // +0x38
  int        mIndex;       // +0x48
};
}
}
namespace EA {
namespace Swarm {
void* EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
}
}
namespace EA {
namespace Swarm {
void  OperatorDelete(void* p);                                                             // 0x00f47380
}
}
namespace EA {
namespace Swarm {
void* UninitCopyVec(void* out, void* first, void* last, void* dst, void* alloc);           // 0x00a89e40
}
}
namespace EA {
namespace Swarm {
void* VectorDoAllocate(void* self, unsigned n, void* alloc);                               // 0x00a89840
}
}
namespace EA {
namespace Swarm {
void* UninitCopyPtr(void* first, void* last, void* dst);                                   // 0x00a88250
}
}
namespace EA {
namespace Swarm {
void* MovePtr(void* first, void* last, void* dst);                                         // 0x00a882a0
}
}
namespace EA {
namespace Swarm {
void* MoveBackPtr(void* first, void* last, void* dstEnd);                                  // 0x00a882f0
}
}
namespace EA {
namespace Swarm {
void  CopyBack(void* first, void* last, void* dstEnd);                                     // 0x00cc8b50
}
}
namespace EA {
namespace Swarm {
void  UninitMovePtr(void* out, void* first, void* last, void* dst);                        // 0x00a898a0
}
}
namespace EA {
namespace Swarm {
void  CopyPtrAssign(void* first, void* last, void* value);                                 // 0x00a898f0
}
}
namespace EA {
namespace Swarm {
void  UninitFillPtr(void* dst, unsigned n, void* value);                                   // 0x00a89940
}
}
namespace EA {
namespace Swarm {
void* MemMove(void* dst, const void* src, unsigned n);                                     // 0x011e0744
}
}
namespace EA {
namespace Swarm {
static const char* const kEASTLFile = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
}
}
namespace EA {
namespace Swarm {
static const char* const kEASTLTag  = "EASTL";
}
}
namespace EA {
namespace Swarm {
static inline void FreeBlock_s00a8_b940(void* p)
{
  if (p != 0 && ((int*)p)[-1] != 0)
    OperatorDelete(p);
}
}
}
namespace EA {
namespace Swarm {
struct RefCounted {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
  virtual void v12();
  virtual void AddRef();    // at vtable offset 0x34
  virtual void Release();   // at vtable offset 0x38
};
}
}
namespace EA {
namespace Swarm {
struct RefVertexObj {
  virtual void AddRef();    // at vtable offset 0x00
  virtual void Release();   // at vtable offset 0x04
};
}
}
namespace EA {
namespace Swarm {
struct RefVertex {
  void*    mp;        // +0x00  referenced object
  uint32_t mPad[5];   // +0x04  vertex parameter block
};
}
}
namespace EA {
namespace Swarm {
template <class T>
struct SpVector_s00a8_b940 {
  T*       mpBegin;        // +0x00
  T*       mpEnd;          // +0x04
  T*       mpCapacity;     // +0x08
  uint32_t mAllocator[2];  // +0x0c

  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
  void reserve(unsigned n);                       // 0x00a8bf60
  void insert(T* position, const T& value);       // 0x00a8c540
  ~SpVector_s00a8_b940();                                    // 0x00a8c440
};
}
}
namespace EA {
namespace Swarm {
struct SampleVector_s00a8_b940 {
  cDistributeSample_s00a8_b940* mpBegin;      // +0x00
  cDistributeSample_s00a8_b940* mpEnd;        // +0x04
  cDistributeSample_s00a8_b940* mpCapacity;   // +0x08
  uint32_t           mAllocator[2];// +0x0c

  SampleVector_s00a8_b940(const SampleVector_s00a8_b940& src);   // 0x00a8c480
};
}
}
namespace EA {
namespace Swarm {
struct RefPtr {
  void* mp;   // +0x00
};
}
}
namespace EA {
namespace Swarm {
struct PtrVector {
  RefPtr*  mpBegin;        // +0x00
  RefPtr*  mpEnd;          // +0x04
  RefPtr*  mpCapacity;     // +0x08
  uint32_t mAllocator[2];  // +0x0c

  RefPtr* erase(RefPtr* first, RefPtr* last);                   // 0x00a8c4e0
  void    insert(RefPtr* position, unsigned n, const RefPtr& v); // 0x00a8c690
};
}
}
namespace EA {
namespace Swarm {
template struct SpVector_s00a8_b940<RefVertex>;
}
}
// ---- items of slice s00a8b940 end

// ---- items of slice s00a92450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
struct V3_s00a9_2450 { float x, y, z; V3_s00a9_2450() {} V3_s00a9_2450(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} };
template <class T> struct SpVec { T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAlloc[2]; };
struct cEffectParams;
struct cDistributeDescription_s00a9_2450;
struct cDistributeEffect_s00a9_2450;
struct IChildEffect {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool SetFloatParams(int param, const float* data, int count);   // +0x1c
    virtual bool SetIntParams(int param, const int* data, int count);       // +0x20
    virtual bool SetUnknownParam(int param, void* data);                    // +0x24
};
struct cDistributeDescription_s00a9_2450 {
    uint32_t pad00[2];
    uint32_t mFlags;            // +0x08
    int      mDensity;          // +0x0c
    int      mEffectIndex;      // +0x10
    uint8_t  mSourceType;       // +0x14
    uint8_t  pad15[3];
    int      mSourceSize;       // +0x18
    uint32_t pad1c;
    float    mScale;            // +0x20
    uint8_t  pad24[0x130 - 0x24];
    float    mAltitudeRange[2]; // +0x130
    uint8_t  pad138[0x158 - 0x138];
    uint8_t  mOverrideSet;      // +0x158
};
struct cIEffectsWorld_s00a9_2450 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void* v20();        // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void* v30();        // +0x30
};
struct cSurfaceData {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    uint32_t pad08;             // +0x08
    int      mCount;            // +0x0c
    struct Rec { int v0; int v1; int key; int pad; } mRecs[1];  // +0x10
};
struct cEffectParams {
    uint32_t mFloatParams[25];          // +0x00
    SpVec<float> mFloatParamStorage;    // +0x64
    uint32_t mIntParams[10];            // +0x78
    SpVec<int> mIntParamStorage;        // +0xa0
    void* mUnknownParams[9];            // +0xb4
    cEffectParams();                    // 0x007d55e0
    bool FloatStore(int index, const void* src, int count);  // 0x00a83fd0
    bool IntStore(int index, const void* src, int count);    // 0x00a84040
};
void mul_705290(V3_s00a9_2450* out, const V3_s00a9_2450* in);                                                        // 0x00705290
struct cDistributeEffect_s00a9_2450 {
    uint32_t pad00[0x14 / 4];
    cDistributeDescription_s00a9_2450* mDesc;      // +0x14
    int      mCollectionIndex;          // +0x18
    cIEffectsWorld_s00a9_2450* mWorld;             // +0x1c
    void*    mGlobalParams;             // +0x20
    cEffectParams* mChildParams;        // +0x24
    uint32_t mFlags;                    // +0x28
    uint8_t  pad2c[0xa0 - 0x2c];
    float    mAltitudeRange[2];         // +0xa0
    uint8_t  pada8[0xd8 - 0xa8];
    SpVec<IChildEffect*> mEffects;      // +0xd8
    int      mOverrideID_hi;            // +0xec
    uint32_t mFormat0;                  // +0xf0
    uint32_t mFormat1;                  // +0xf4
    uint8_t  padf8[0x100 - 0xf8];
    V3_s00a9_2450       mSubdivOffset;             // +0x100
    V3_s00a9_2450       mSubdivScale;              // +0x10c
    void*    mField118;                 // +0x118
    uint8_t  pad11c[0x170 - 0x11c];
    V3_s00a9_2450       mVec170;                   // +0x170
    float    mField17C;                 // +0x17c
    float    mField180;                 // +0x180
    float    mField184;                 // +0x184
    float    mField188;                 // +0x188
    float    mField18C;                 // +0x18c
    int      mField190;                 // +0x190
    int      mField194;                 // +0x194

    void ClearSamples(int);             // 0x00a8d350
    void ReleaseRenderSet();            // 0x00a89490
    void CreateRenderSet();             // 0x00a91bc0

    bool SetFloatParams(int param, const float* data, int count);
    bool SetIntParams(int param, const int* data, int count);  // 0x00a92450 (cDistributeEffect::SetIntParams)
    bool SetUnknownParam(int param, void* data);
};
typedef bool(__thiscall* FnSetShader)(void*, int, int, int, int, const float*);
typedef cDistributeDescription_s00a9_2450* (__thiscall* FnGetDesc)(void*, int, int, int);
// ---- items of slice s00a92450 end

// ---- items of slice s00a92d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EAAlloc(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
extern "C" void  __cdecl operator_delete(void* p);                                       // 0x00f47380
typedef uint32_t u32;
typedef uint8_t  u8;
struct Vector3_s00a9_2d90 { float x, y, z; };
template <class T> struct SpVec_s00a9_2d90 { T* mpBegin; T* mpEnd; T* mpCapacity; u32 mAlloc[2]; };
struct cDistributeSample_s00a9_2d90;
struct SampleVector_s00a9_2d90 {
    cDistributeSample_s00a9_2d90* mpBegin;
    cDistributeSample_s00a9_2d90* mpEnd;
    cDistributeSample_s00a9_2d90* mpCapacity;
    u32 mAlloc[2];
    void swap(SampleVector_s00a9_2d90& other);                       // 0x00a8cf50
    void Free();                                          // 0x00a8cfe0
};
struct RawVec    { void*     mpBegin; void*     mpEnd; void*     mpCapacity; };
struct Transform38 { float m[0x38 / 4]; };            // 0x38 aligned transform block
struct cDistributeDescription_s00a9_2d90;                        // [EA/Swarm/cDistributeDescription]
struct cIEffectsWorld_s00a9_2d90;                                // [EA/Swarm/cIEffectsWorld]
struct cIVisualEffect_s00a9_2d90;                                // [EA/Swarm/cIVisualEffect]
struct cSurfaceRec_s00a9_2d90;                                   // [EA/Swarm/cSurfaceRec]
struct cBounds {                                      // 0x18 axis-aligned sample bounds
    float mMinX, mMinY, mMinZ, mMaxX, mMaxY, mMaxZ;
    void Init();                                      // 0x006e9530
};
struct cDistributeSample_s00a9_2d90 {                            // 0x4c stride in mSamples
    char    pad00[4];
    Vector3_s00a9_2d90 mPosition;                                // +0x04
    float   mScale;                                   // +0x10
    char    pad14[0x38 - 0x14];
    Vector3_s00a9_2d90 mVec38;                                   // +0x38
    float   mScale44;                                 // +0x44
    char    pad48[0x4c - 0x48];
};
struct cDistributeEffectStats {
    int mField00, mField04, mField08, mField0c;
    int mField10, mField14, mField18, mField1c;
    char pad20[0x34 - 0x20];
    int mFirst_34;                                    // +0x34
    int mFirst_38;                                    // +0x38
};
struct cDistributeDescription_s00a9_2d90 {
    int      mField00;                                // +0x00
    int      mField04;                                // +0x04
    u32      mFlags;                                  // +0x08
    int      mField0c;                                // +0x0c
    int      mField10;                                // +0x10
    u8       mField14;                                // +0x14
    u8       pad15[3];
    int      mField18;                                // +0x18
    u8       mField1c;                                // +0x1c
    u8       pad1d[3];
    char     pad20[0x15c - 0x20];
    void*    mpEffectData15c;                         // +0x15c
    int      mField160;                               // +0x160
};
struct cIVisualEffect_s00a9_2d90 {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08(int);
    virtual void  v0c(int);
    virtual bool  v10();
    virtual bool  v14(void* param, float time, void* stats);
    virtual void  v18(void* sample, void* transform);
    virtual void  v1c(int param, void* data, int count);
    virtual void  v20(int param, void* data, int count);
    virtual void  v24(int param, void* data);
    virtual void  v28(int);
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    bool IsReady();                                   // 0x00a88350, direct call
};
struct cEffectWorldObj {                              // object returned by cIEffectsWorld::v20()
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void SetBounds(int setID, cBounds* bounds, float scale);
    virtual void SetBoundsEx(int setID, int flag);
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void v34(int setID, Vector3_s00a9_2d90* v, float scale);
    virtual void v38(int setID, int flag);
};
struct cIEffectsWorld_s00a9_2d90 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual cEffectWorldObj* v20();
};
struct cSurfaceRec_s00a9_2d90 {                                  // 0x18 element kept in mSurfaceRecs
    void* mpObject;                                   // +0x00  object with a vtable
    int   mField04;                                   // +0x04
    int   mField08;                                   // +0x08
    int   mStateDataOffset;                           // +0x0c
    void* mpData;                                     // +0x10
    int   mField14;                                   // +0x14
};
struct cSurfacePayload {                              // built for effect->v24(4, rec)
    void* mpVtbl;                                     // +0x00
    void* mpVtbl2;                                    // +0x04
    int   mField08;                                   // +0x08
    int   mStateDataOffset;                           // +0x0c
    void* mpData;                                     // +0x10
};
struct cDistributeEffect_s00a9_2d90 {
    void*   mpVtbl;                                   // +0x00
    void*   mpVtbl04;                                 // +0x04
    int     mField08;                                 // +0x08
    void*   mpVtbl0c;                                 // +0x0c
    void*   mpVtbl10;                                 // +0x10
    cDistributeDescription_s00a9_2d90* mDesc;                    // +0x14
    int     mCollectionIndex;                         // +0x18
    cIEffectsWorld_s00a9_2d90* mWorld;                           // +0x1c
    void*   mGlobalParams;                            // +0x20
    cEffectParams* mChildParams;                      // +0x24
    u32     mFlags;                                   // +0x28
    Transform38 mSourceTransform;                     // +0x2c
    Transform38 mRigidTransform;                      // +0x64
    int     mSubdivCount;                             // +0x9c
    float   mAltitudeRange[2];                        // +0xa0
    SampleVector_s00a9_2d90 mRenderSamples;                      // +0xa8
    SampleVector_s00a9_2d90 mSamples;                            // +0xbc
    int     mRenderSampleCount;                       // +0xd0
    int     mTargetSampleCount;                       // +0xd4
    SpVec_s00a9_2d90<cIVisualEffect_s00a9_2d90*> mEffects;                  // +0xd8
    int     mSetID;                                   // +0xec
    int     mFieldF0;                                 // +0xf0
    int     mFieldF4;                                 // +0xf4
    char    padF8[8];
    Vector3_s00a9_2d90 mSubdivOffset;                            // +0x100
    Vector3_s00a9_2d90 mSubdivScale;                             // +0x10c
    void*   mField118;                                // +0x118
    SpVec_s00a9_2d90<cSurfaceRec_s00a9_2d90> mSurfaceRecs;                  // +0x11c
    SpVec_s00a9_2d90<u8> mSurfaceStateData;                      // +0x130
    char    pad144[0x158 - 0x144];
    int     mField158;                                // +0x158
    void*   mpEffectData15c;                          // +0x15c
    int     mField160;                                // +0x160
    int     mField164;                                // +0x164
    int     mField168;                                // +0x168
    float   mField16c;                                // +0x16c
    Vector3_s00a9_2d90 mVec170;                                  // +0x170
    float   mCurrentSubdivScale;                      // +0x17c
    float   mField180;                                // +0x180
    float   mField184;                                // +0x184
    float   mField188;                                // +0x188
    float   mField18C;                                // +0x18c
    int     mField190;                                // +0x190
    int     mField194;                                // +0x194

    int  UpdateSamples(int target);
    int  ApplyEffect(void* param, float time, void* stats);

    // out-of-line in other TUs of the same .obj
    void CreateClusteredMatchingSamples2D(RawVec* out);      // 0x00a8f6a0
    void CreateSamples2D(int a, int b, int c);               // 0x00a8d450
    void CreateClusteredSamples2D(int a, int b, int c);      // 0x00a8dea0
    void CreateRandomSamples(int a, int b, int c);           // 0x00a8e7c0
    void PinSamplesToSurface(int first, int last);           // 0x00a91860
    void ApplyColorAndAlpha(int first, int last);            // 0x00a88d50
    void RigidTransformRange(int first, int last);           // 0x00a88800
    void Start(void* param, float time, void* stats);        // 0x00a91e40
    void ClearSamples(int);                                  // 0x00a8d350
};
struct cAutoRef {                                     // AutoRefCount<cIVisualEffect>
    cIVisualEffect_s00a9_2d90* mpObject;
};
struct RefVec { cAutoRef* mpBegin; cAutoRef* mpEnd; cAutoRef* mpCapacity; };
cIVisualEffect_s00a9_2d90* MakeVisualEffect(u8 type, int effectIndex, int collectionIndex, cEffectParams* params); // 0x00a714f0
void EffectPropagateParams(cEffectParams* params, cIVisualEffect_s00a9_2d90* effect);               // 0x00a88640
void PtrVecInsert(void* vec, unsigned count, void** tmp);                                // 0x00a8c690
void PtrVecErase(void* begin, void* end);                                                // 0x00a8c4e0
namespace EA {
namespace Messaging {
struct IServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual bool Post(int msgId, void* msg, int flags);
};
}
}
namespace EA {
namespace Messaging {
IServer* GetServer();                                                                     // 0x00883860
}
}
struct MsgPair { int mLo; int mHi; };
MsgPair GetEffectMessage(cDistributeEffect_s00a9_2d90* self);                                        // 0x00a88220
struct AllocHeader { int mOwnsBlock; };
static inline void FreeVecBuffer(void* p) {
    if (p && ((AllocHeader*)p)[-1].mOwnsBlock != 0)
        operator_delete(p);
}
// ---- items of slice s00a92d90 end

// @ 0x00705290
void mul_705290(V3* a, V3* b)
{
    V3 r;
    r.x = a->x * b->x;
    r.y = a->y * b->y;
    r.z = a->z * b->z;
    *a = r;
}

// @ 0x00a86590
void cDistributeSimulator::Update(float dt)
{
    if (mpRef8c == 0 || mActive != 0)
        return;

    float t = 0.0f;
    if (dt != 0.0f) {
        uint8 srcType = mDesc->mParam0d;
        if (srcType == 1)
            return;
        if (srcType == 2)
            t = 1.0f;
    }

    uint8 fmt = mDesc->mParam0c;

    cSPTransform_s00a8_5c00 xf(&mFlags14);
    float sz = SampleCurve_s00a8_5c00(*(FloatCurve*)((char*)mDesc + 0x48), t);
    xf.f[1] = mParam68 * sz * xf.f[1];
    mFlags14 |= 1;
    mModCount16 += 1;

    float pitch = SampleCurve_s00a8_5c00(*(FloatCurve*)((char*)mDesc + 0x34), t);
    pitch = mParam6c * pitch;

    void* handle = (*(void*(__thiscall**)(cIRefObj_s00a8_5c00*, uint32, void*, cSPTransform_s00a8_5c00*, void*))(*(uint32*)mpRef8c + 0x10))
        (mpRef8c, fmt, (char*)mDesc + 0x10, &xf, this);
    mHandle90 = handle;
    if (handle == 0)
        return;

    ((cSPTransformOps*)handle)->Assign(&xf);
    *(float*)((char*)handle + 0x48) = pitch;

    float roll = SampleCurve_s00a8_5c00(*(FloatCurve*)((char*)mDesc + 0x84), t);
    *(float*)((char*)handle + 0x4c) = mParam74 * roll;

    if ((mDesc->mMask & 1) != 0) {
        *(float*)((char*)handle + 0x50) = mDesc->mParamA4 * mParam70;
        *(float*)((char*)handle + 0x54) = *(float*)((char*)handle + 0x50) * *(float*)((char*)handle + 0x4c);
    } else {
        *(float*)((char*)handle + 0x50) = 1.0f;
        *(float*)((char*)handle + 0x54) = 1.0f;
    }
    *(float*)((char*)handle + 0x58) = mDesc->mParamA8;
    *(float*)((char*)handle + 0x5c) = mDesc->mParamAC;

    float heading = SampleCurve_s00a8_5c00(*(FloatCurve*)((char*)mDesc + 0x5c), t);
    float colorScale = mParam78 * mParam64 * heading;

    float col[3];
    SampleCurve3_s00a8_5c00(*(FloatVec*)((char*)mDesc + 0x70), t, col);

    if (mpRef88 != 0) {
        float pt[3];
        pt[0] = mCenterX; pt[1] = mCenterY; pt[2] = mCenterZ;
        if ((*(bool(__thiscall**)(cIRefObj_s00a8_5c00*, float*))(*(uint32*)mpRef88 + 0x18))(mpRef88, pt)) {
            float out[3];
            (*(void(__thiscall**)(cIRefObj_s00a8_5c00*, float*, float*))(*(uint32*)mpRef88 + 0x2c))(mpRef88, out, pt);
            colorScale = out[2] * colorScale;
            for (int i = 0; i < 3; ++i)
                col[i] = out[i] * col[i];
        }
    }

    *(float*)((char*)handle + 0x44) = colorScale;
    *(float*)((char*)handle + 0x38) = col[0];
    *(float*)((char*)handle + 0x3c) = col[1];
    *(float*)((char*)handle + 0x40) = col[2];

    (*(void(__thiscall**)(cIRefObj_s00a8_5c00*, void*))(*(uint32*)mpRef8c + 0x14))(mpRef8c, handle);
    *(float*)((char*)this + 0x80) = t;

    if (mDesc->mParam0c == 3) {
        mHandle90 = 0;
        mActive = 0;
        return;
    }
    mActive = 1;
}

// @ 0x00a86b30
void __thiscall SimUpd::Update(float dt, float blend, void* ctx)
{
    if (Fld<void*>(this, 0x90) == 0)
        return;
    Fld<int>((char*)ctx, 0x28) += 1;
    float time = Fld<float>(this, 0x80) + dt;
    Fld<float>(this, 0x80) = time;
    float tt = Fld<float>(this, 0x84) * time;
    void* desc = Fld<void*>(this, 0x0c);
    char mode = *At<char>(desc, 0xd);
    if (mode == 0) {
        int n = (int)tt;
        if (tt < (float)n)
            n = n - 1;
        tt = tt - (float)n;
    } else if (tt > 1.0f) {
        if (mode == 1) {
            void** vt = *(void***)this;
            ((void(__thiscall*)(void*, int))vt[3])(this, 0);
            return;
        }
        tt = 1.0f;
    }

    unsigned n0 = (unsigned)((*(int*)((char*)desc + 0x60) - *(int*)((char*)desc + 0x5c)) >> 2);
    float c0 = SampleCurve_s00a8_6b30(*(const float**)((char*)desc + 0x5c), n0, tt);
    float value = Fld<float>(this, 0x78) * Fld<float>(this, 0x64) * c0
        * ((Fld<float>(this, 0x58) - Fld<float>(this, 0x54)) * blend + Fld<float>(this, 0x54));
    void* target = Fld<void*>(this, 0x90);
    Vec3 ones;
    ones.x = 1.0f; ones.y = 1.0f; ones.z = 1.0f;

    if (((Fld<unsigned>((char*)desc, 0x08) >> 2) & 1) == 0) {
        ((TransOps*)((char*)target + 0x14))->Assign((char*)this + 0x14);

        unsigned n1 = (unsigned)((*(int*)((char*)desc + 0x4c) - *(int*)((char*)desc + 0x48)) >> 2);
        float c1 = SampleCurve_s00a8_6b30(*(const float**)((char*)desc + 0x48), n1, tt);
        Fld<unsigned short>(target, 0x00) |= 1;
        Fld<unsigned short>(target, 0x02) += 1;
        Fld<float>(target, 0x10) = c1 * blend * Fld<float>(target, 0x10);

        unsigned n2 = (unsigned)((*(int*)((char*)desc + 0x38) - *(int*)((char*)desc + 0x34)) >> 2);
        float c2 = SampleCurve_s00a8_6b30(*(const float**)((char*)desc + 0x34), n2, tt);
        Fld<float>(target, 0x48) = Fld<float>(this, 0x6c) * c2;

        unsigned n3 = (unsigned)((*(int*)((char*)desc + 0x88) - *(int*)((char*)desc + 0x84)) >> 2);
        float c3 = SampleCurve_s00a8_6b30(*(const float**)((char*)desc + 0x84), n3, tt);
        Fld<float>(target, 0x4c) = Fld<float>(this, 0x74) * c3;

        Vec3* vb = *(Vec3**)((char*)desc + 0x70);
        Vec3* ve = *(Vec3**)((char*)desc + 0x74);
        if (vb != ve) {
            unsigned nv = (unsigned)((char*)ve - (char*)vb) / 0xc;
            ones = SampleVec3(vb, nv, tt);
        }

        SampleIface* iface = Fld<SampleIface*>(this, 0x88);
        if (iface != 0) {
            float local[3];
            local[0] = Fld<float>(this, 0x18);
            local[1] = Fld<float>(this, 0x1c);
            local[2] = Fld<float>(this, 0x20);
            if (iface->QueryVec(local)) {
                float out[4];
                iface->Transform(out, local);
                value = out[2] * value;
                MulVec(&ones, out);
            }
        }
        Fld<float>(target, 0x44) = value;
        Fld<float>(target, 0x38) = ones.x;
        Fld<float>(target, 0x3c) = ones.y;
        Fld<float>(target, 0x40) = ones.z;
    } else {
        if (Fld<float>(target, 0x44) == value)
            return;
        Fld<float>(target, 0x44) = value;
    }
    Fld<Notifier*>(this, 0x8c)->Notify(target);
}

// @ 0x00a88220
__int64 cDistributeEffect_s00a8_7fb0::FUN_00a88220()
{
    uint32_t a = *(uint32_t*)((char*)this + 0xf0);
    uint32_t b = *(uint32_t*)((char*)this + 0xf4);
    if ((a & b) == (uint32_t)-1) {
        char* w = *(char**)((char*)this + 0x14);
        a = *(uint32_t*)(w + 0x138);
        b = *(uint32_t*)(w + 0x13c);
    }
    U64 r;
    r.lo = a;
    r.hi = b;
    return r.v;
}

// @ 0x00a88350
bool cDistributeEffect_s00a8_7fb0::FUN_00a88350()
{
    void* v = *(void**)((char*)this + 0x15c);
    if (v == 0)
        return false;
    unsigned x = mFlags >> 10;
    if (x & 1)
        return false;
    int r = ((int(__thiscall*)(void*))(*(void***)v)[0x10 / 4])(v);
    if (r != *(int*)((char*)this + 0x168))
        return true;
    return false;
}

// @ 0x00a88390
int cDistributeEffect_s00a8_7fb0::FUN_00a88390(int count, void** outBegin, void** outStride)
{
    if (*(int*)((char*)this + 0xc) == 0 && count > 0) {
        void* src = *(void**)((char*)this + 4);
        ((void(__thiscall*)(void*))(*(void***)src)[0x08 / 4])(src);
        void* fn = *(void**)(*(void***)(*(void**)((char*)this + 4)))[0];
        int got = ((int(__stdcall*)(void*, void*, void*))fn)(
            *(void**)((char*)this + 8), (void*)((char*)this + 0x10), (void*)((char*)this + 0x14));
        *(int*)((char*)this + 8) -= got;
        *(int*)((char*)this + 0xc) = got;
    }
    int avail = *(int*)((char*)this + 0xc);
    *outStride = *(void**)((char*)this + 0x14);
    if (count > avail)
        count = avail;
    *outBegin = *(void**)((char*)this + 0x10);
    *(int*)((char*)this + 0xc) -= count;
    *(int*)((char*)this + 0x10) += *(int*)((char*)this + 0x14) * count * 4;
    return count;
}

// @ 0x00a88490
void FUN_00a88490(float* out, float param_2, float param_3, float param_4)
{
    float fVar3 = param_3 * 2.0f - DAT_01678264;
    float fVar5 = param_2 * 2.0f - DAT_01678260;
    float fVar4, fVar2;
    if (fVar5 <= -fVar3) {
        if (fVar5 < fVar3) {
            fVar4 = (fVar3 / fVar5 + DAT_014853e0) * (DAT_0156502c_s00a8_7fb0 * DAT_013eb8a0);
            fVar2 = -fVar5;
        }
        else {
            fVar4 = 0.0f;
            if (fVar3 != 0.0f)
                fVar4 = (DAT_0147b9f0 - fVar5 / fVar3) * (DAT_0156502c_s00a8_7fb0 * DAT_013eb8a0);
            fVar2 = fVar3;
        }
    }
    else if (fVar3 < fVar5) {
        fVar4 = (fVar3 / fVar5) * (DAT_0156502c_s00a8_7fb0 * DAT_013eb8a0);
        fVar2 = fVar5;
    }
    else {
        fVar4 = (2.0f - fVar5 / fVar3) * (DAT_0156502c_s00a8_7fb0 * DAT_013eb8a0);
        fVar2 = fVar3;
    }
    float t = DAT_01678278_s00a8_7fb0 * fVar4 + 12582912.0f;
    fVar4 = fVar4 - (float)((int)t + (int)0xb4c00000) * DAT_01678300;
    float a = (fVar2 * param_4 + DAT_01485720) - param_4;
    unsigned sel = (unsigned)t & 0xf;
    float c2 = DAT_01677840_s00a8_7fb0[sel * 2 + 1];
    float c1 = DAT_01677840_s00a8_7fb0[sel * 2];
    out[0] = (c2 - ((c2 * fVar4) * DAT_01471064 + c1) * fVar4) * a;
    out[1] = ((c2 - (c1 * fVar4) * DAT_01471064) * fVar4 + c1) * a;
}

// @ 0x00a88640
void FUN_00a88640(int base, void* renderer)
{
    short* p = (short*)(base + 2);
    for (int i = 0; i < 0x19; ++i) {
        unsigned int n = (unsigned short)*p;
        if (n != 0) {
            unsigned int off = (unsigned short)p[-1];
            void* arr = *(void**)(base + 0x64);
            ((void(__thiscall*)(void*, int, void*, unsigned int))(*(void***)renderer)[0x1c / 4])(
                renderer, i, (char*)arr + off * 4, n);
        }
        p += 2;
    }
    p = (short*)(base + 0x7a);
    for (int i = 0; i < 0xa; ++i) {
        unsigned int n = (unsigned short)*p;
        if (n != 0) {
            unsigned int off = (unsigned short)p[-1];
            void* arr = *(void**)(base + 0xa0);
            ((void(__thiscall*)(void*, int, void*, unsigned int))(*(void***)renderer)[0x20 / 4])(
                renderer, i, (char*)arr + off * 4, n);
        }
        p += 2;
    }
    int* q = (int*)(base + 0xb4);
    for (int i = 0; i < 9; ++i) {
        int v = *q;
        if (v != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)renderer)[0x24 / 4])(renderer, i, v);
        ++q;
    }
}

// @ 0x00a886f0
void cDistributeEffect_s00a8_7fb0::FUN_00a886f0(int visible)
{
    if ((visible & 0xff) == 0)
        mFlags &= ~2u;
    else
        mFlags |= 2;

    if ((mFlags & 1) == 0)
        return;

    if (*(int*)((char*)this + 0xec) >= 0) {
        char b;
        if ((visible & 0xff) != 0 && *(int*)((char*)this + 0xd4) > 0) {
            b = 1;
            if (*(int*)((char*)this + 0xd4) != *(int*)((char*)this + 0xd0))
                b = 0;
        }
        else {
            b = 0;
        }
        int flag = (mDesc->mFlags >> 8) & 1;
        IWorldThing* thing = (IWorldThing*)mWorld->v20();
        if (flag)
            thing->SetVisibleA(*(int*)((char*)this + 0xec), b);
        else
            thing->SetVisibleB(*(int*)((char*)this + 0xec), b);
    }

    int n = (int)(*(void***)((char*)this + 0xdc) - *(void***)((char*)this + 0xd8));
    for (int i = 0; i < n; ++i) {
        void* o = *(void**)(*(char**)((char*)this + 0xd8) + i * 4);
        ((void(__thiscall*)(void*, int))(*(void***)o)[0x28 / 4])(o, visible);
    }
}

// @ 0x00a887b0
void cDistributeEffect_s00a8_7fb0::FUN_00a887b0(int index, float value)
{
    if (*(int*)((char*)this + 0xbc) == *(int*)((char*)this + 0xc0)) {
        if (*(int*)((char*)this + 0xa8) != *(int*)((char*)this + 0xac)) {
            *(float*)(index * 0x4c + 0x44 + *(int*)((char*)this + 0xa8)) = value;
            return;
        }
    }
    else {
        *(float*)(index * 0x4c + 0x44 + *(int*)((char*)this + 0xbc)) = value;
    }
}

// @ 0x00a88800
void cDistributeEffect_s00a8_7fb0::RigidTransformRange(int first, int last)
{
    if (mSamples.empty())
        return;

    cDistributeDescription_s00a8_7fb0* desc = mDesc;
    uint32_t flags = desc->mFlags;
    float invCount = 1.0f / (float)mTargetSampleCount;

    if (flags & 0x40) {
        for (int i = first; i < last; ++i) {
            cDistributeSample_s00a8_7fb0* s = &mSamples.mpBegin[i];
            float t = ((float)s->mNumber + 0.5f) * invCount;
            if (!desc->mSizeCurve.empty()) {
                float size = SampleCurve1_s00a8_7fb0(desc->mSizeCurve, t);
                double scaled = RandomRange(1.0f, desc->mSizeVary) * size;
                _ReadWriteBarrier();
                s->mTransform.mScale = (float)(scaled * s->mTransform.mScale);
                s->mTransform.mFlags |= 1;
                s->mTransform.mModificationCount += 1;
            }

            if (!desc->mRollCurve.empty()) {
                float angle = SampleCurve1_s00a8_7fb0(desc->mRollCurve, t) + desc->mRollOffset;
                if (desc->mRollVary > 0.0f)
                    angle = (float)(RandomSymmetric(desc->mRollVary) * angle);
                s->mTransform.RotateY(DAT_01678314 * angle);
            }

            if (!desc->mPitchCurve.empty()) {
                float angle = SampleCurve1_s00a8_7fb0(desc->mPitchCurve, t) + desc->mPitchOffset;
                if (desc->mPitchVary > 0.0f)
                    angle = (float)(RandomSymmetric(desc->mPitchVary) * angle);
                s->mTransform.PreRotateX(DAT_01678314 * angle);
            }

            if (!desc->mHeadingCurve.empty()) {
                float angle = SampleCurve1_s00a8_7fb0(desc->mHeadingCurve, t) + desc->mHeadingOffset;
                if (desc->mHeadingVary > 0.0f)
                    angle = (float)(RandomSymmetric(desc->mHeadingVary) * angle);
                s->mTransform.RotateZ(DAT_01678314 * angle);
            }
        }
    }
    else if (flags & 0x10) {
        for (int i = first; i < last; ++i) {
            cDistributeSample_s00a8_7fb0* s = &mSamples.mpBegin[i];
            float t = ((float)s->mNumber + 0.5f) * invCount;
            float size = SampleCurve1_s00a8_7fb0(desc->mSizeCurve, t);
            double scaled = RandomRange(1.0f, desc->mSizeVary) * size;
            _ReadWriteBarrier();
            s->mTransform.mScale = (float)(scaled * s->mTransform.mScale);
            s->mTransform.mFlags |= 1;
            s->mTransform.mModificationCount += 1;
        }
    }
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

// @ 0x00a89490
void cDistributeEffect::ReleaseRenderSet()
{
    if (mRenderIndex < 0)
        return;
    bool shared = (mFlags & 0x4000) != 0;
    if (shared)
        mpRenderHost->GetTarget()->ReleaseShared(mRenderIndex);
    else
        mpRenderHost->GetTarget()->ReleaseUnshared(mRenderIndex);
    mRenderIndex = -1;
}

// @ 0x00a894e0
void cDistributeEffect::Render(int target)
{
    if (gRenderFns[mRenderType] == 0)
        return;

    int total = 0;
    for (unsigned i = 0; i < mMeshes.size(); ++i) {
        cRenderMesh* mesh = mMeshes.mpBegin[i];
        total += (int)(mesh->mpEnd - mesh->mpBegin);
    }

    cRenderParams params;
    params.mpVtbl = (void*)0x014582e0;
    params.mpRenderer = (void*)target;
    params.mCount = total;
    params.mWritten = 0;
    params.mPad10 = 0;
    params.mPad14 = 0;

    IRenderer* renderer = (IRenderer*)target;
    int written = renderer->Begin(total, &params.mPad10, &params.mPad14);
    params.mCount -= written;
    params.mWritten = written;

    for (unsigned i = 0; i < mMeshes.size(); ++i)
        gRenderFns[mRenderType](mMeshes.mpBegin[i], &params, &mRenderArg);

    renderer->End();
}

// @ 0x00a89680
int CollectSamples(cSampleTarget* target, cSampleSource* info, cSampleOut* out, int capacity)
{
    int count = 0;

    if (info->mCount >= 0) {
        int n = 0;
        if (!info->mFlag14)
            n = target->GetSamples(info->mCount, out, capacity);
        count += n;
        if (out) {
            out += n;
            capacity -= n;
        }
    } else if ((unsigned char)((info->mFlags >> 8) & 1) || (unsigned char)((info->mFlags >> 7) & 1)) {
        FillFromBaseTransform(info->mBaseTransform, (unsigned char)((info->mFlags >> 8) & 1), &count, &out, &capacity);
    }

    int nslots = (int)info->mSlots.size();
    for (int i = 0; i < nslots; ++i) {
        uint32_t a = info->mSlots.mpBegin[i].mMaskA;
        uint32_t b = info->mSlots.mpBegin[i].mMaskB;
        if ((a & b) == 0xffffffffu)
            continue;
        ++count;
        if (capacity > 0) {
            out->mValue0 = a;
            out->mValue1 = b;
            out->mKind = 7;
            ++out;
            --capacity;
        }
    }

    uint32_t a0 = info->mMaskA0;
    uint32_t a1 = info->mMaskA1;
    if ((a0 & a1) != 0xffffffffu) {
        ++count;
        if (capacity > 0) {
            out->mValue0 = a0;
            out->mValue1 = a1;
            out->mKind = 5;
            ++out;
            --capacity;
        }
    }
    uint32_t b0 = info->mMaskB0;
    uint32_t b1 = info->mMaskB1;
    if ((b0 & b1) != 0xffffffffu) {
        ++count;
        if (capacity > 0) {
            out->mValue0 = b0;
            out->mValue1 = b1;
            out->mKind = 5;
            ++out;
            --capacity;
        }
    }
    uint32_t c0 = info->mMaskC0;
    uint32_t c1 = info->mMaskC1;
    if ((c0 & c1) != 0xffffffffu) {
        ++count;
        if (capacity > 0) {
            out->mValue0 = c0;
            out->mValue1 = c1;
            out->mKind = 5;
        }
    }
    return count;
}

// @ 0x00a89940
void CopySamplesWithAddRef(void** dst, unsigned count, void** src)
{
    if (count <= 0)
        return;
    do {
        if (dst) {
            void* p = *src;
            *dst = p;
            if (p)
                ((IRefCounted*)p)->AddRef();
        }
        --count;
        ++dst;
    } while (count > 0);
}

// @ 0x00a89980
cDistributeSample::cDistributeSample(const cDistributeSample& src, int number)
{
    mTransform.mFlags = src.mTransform.mFlags;
    mTransform.mModCount = src.mTransform.mModCount;
    mTransform.mOffset.x = src.mTransform.mOffset.x;
    mTransform.mOffset.y = src.mTransform.mOffset.y;
    mTransform.mOffset.z = src.mTransform.mOffset.z;
    mTransform.mScale = src.mTransform.mScale;
    mTransform.mRotation.CopyFrom(src.mTransform.mRotation);
    mColorAlpha.x = gDefaultSampleColor.x;
    mColorAlpha.y = gDefaultSampleColor.y;
    mColorAlpha.z = gDefaultSampleColor.z;
    mColorAlpha.w = gDefaultSampleColor.w;
    mNumber = number;
}

// @ 0x00a89a00
void cDistributeEffect::SetTransforms(cTransform_s00a8_8d50* source, cTransform_s00a8_8d50* rigid)
{
    mRigidTransform.CopyFrom(rigid);
    mSourceTransform.CopyFrom(source);
    mFlags &= ~0x40u;
}

// @ 0x00a89a30
void cDistributeEffectPart::Dispatch(int arg)
{
    bool renderWhole = (mDesc->mFlags & 0x4000) != 0;
    if (renderWhole) {
        ((cDistributeEffect*)((char*)this - 0xc))->Render(arg);
    } else {
        RenderFn fn = gRenderFns[mRenderType];
        if (fn) {
            fn((cDistributeEffect*)((char*)this - 0xc), (void*)arg, &mRenderArg);
            ++mRenderCounter;
        }
    }
}

// @ 0x00a89a90
bool cDistributeEffect::ProjectSample(Vector3* pos, int i0, int i1)
{
    bool rigidOnly = (mFlags & 0x80) != 0;
    Vector3 v = *pos;
    if (rigidOnly) {
        if (mRigidTransform.mFlags & 2)
            v = MulCols(mRigidTransform.mRotation, v);
        float scale = mRigidTransform.mScale;
        v.x = v.x * scale + mRigidTransform.mOffset.x;
        v.y = v.y * scale + mRigidTransform.mOffset.y;
        v.z = v.z * scale + mRigidTransform.mOffset.z;
    } else {
        mSourceTransform.ApplyInverse(&v);
    }

    if (!mDensityMap->Contains(&v))
        return true;
    float t = mDensityMap->GetValue(&v);

    bool keepLocal = (mDesc->mFlags & 0x400) != 0;
    if (keepLocal) {
        v.z = t;
        bool rigidOnly2 = (mFlags & 0x80) != 0;
        if (rigidOnly2)
            mRigidTransform.ApplyInverse(&v);
        else
            mSourceTransform.ApplyForward(&v);
        *pos = v;
    }

    uint32_t flags = mDesc->mFlags;
    bool rangeTest = (flags & 4) != 0;
    if (rangeTest)
        return t < mRangeLo || t > mRangeHi;
    bool ratioTest = (flags & 8) != 0;
    if (ratioTest)
        return (float)i0 >= (float)i1 * t;
    return false;
}

// @ 0x00a89ce0
void cDistributeEffect::MapSample(Vector3* pos)
{
    Vector3 v = *pos;
    bool noRoundTrip = (mFlags & 0x200) != 0;
    if (!noRoundTrip) {
        mRigidTransform.ApplyInverse(&v);
        mSourceTransform.ApplyInverse(&v);
    }
    if (mHeightMap->Contains(&v)) {
        v.z = mHeightMap->GetValue(&v);
        bool noRoundTrip2 = (mFlags & 0x200) != 0;
        if (!noRoundTrip2) {
            mSourceTransform.ApplyForward(&v);
            mRigidTransform.ApplyForward(&v);
        }
        *pos = v;
    }
}

// @ 0x00a89de0
cDistributeSample_s00a8_9de0::cDistributeSample_s00a8_9de0(const cDistributeSample_s00a8_9de0& src)
{
    mTransform.mFlags = src.mTransform.mFlags;
    mTransform.mModificationCount = src.mTransform.mModificationCount;
    mTransform.mTranslation.x = src.mTransform.mTranslation.x;
    mTransform.mTranslation.y = src.mTransform.mTranslation.y;
    mTransform.mTranslation.z = src.mTransform.mTranslation.z;
    mTransform.mScale = src.mTransform.mScale;
    ((void*(__thiscall*)(void*, const void*))&FUN_0041cb40)(&mTransform.mRotation, &src.mTransform.mRotation);
    mColorAlpha[0] = src.mColorAlpha[0];
    mColorAlpha[1] = src.mColorAlpha[1];
    mColorAlpha[2] = src.mColorAlpha[2];
    mColorAlpha[3] = src.mColorAlpha[3];
    mNumber = src.mNumber;
}

// @ 0x00a89e40
cDistributeSample_s00a8_9de0** FUN_00a89e40(cDistributeSample_s00a8_9de0** out, const cDistributeSample_s00a8_9de0* first, const cDistributeSample_s00a8_9de0* last, cDistributeSample_s00a8_9de0* dst)
{
    cDistributeSample_s00a8_9de0** result = out;
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->mTransform.mFlags = first->mTransform.mFlags;
                dst->mTransform.mModificationCount = first->mTransform.mModificationCount;
                dst->mTransform.mTranslation.x = first->mTransform.mTranslation.x;
                dst->mTransform.mTranslation.y = first->mTransform.mTranslation.y;
                dst->mTransform.mTranslation.z = first->mTransform.mTranslation.z;
                dst->mTransform.mScale = first->mTransform.mScale;
                dst->mTransform.mRotation = first->mTransform.mRotation;
                dst->mColorAlpha[0] = first->mColorAlpha[0];
                dst->mColorAlpha[1] = first->mColorAlpha[1];
                dst->mColorAlpha[2] = first->mColorAlpha[2];
                dst->mColorAlpha[3] = first->mColorAlpha[3];
                dst->mNumber = first->mNumber;
            }
            first = (const cDistributeSample_s00a8_9de0*)((const char*)first + 0x4c);
            dst = (cDistributeSample_s00a8_9de0*)((char*)dst + 0x4c);
        } while (first != last);
        *out = dst;
    }
    return result;
}

// @ 0x00a89f70
cDistributeSample_s00a8_9de0* FUN_00a89f70(cDistributeSample_s00a8_9de0* first, cDistributeSample_s00a8_9de0* last, cDistributeSample_s00a8_9de0* dst)
{
    cDistributeSample_s00a8_9de0* result = dst;
    if (first != last) {
        uint32_t* d = (uint32_t*)((char*)dst + 0xc);
        uint32_t* s = (uint32_t*)((char*)first + 0x28);
        do {
            if (dst != 0) {
                *(uint16_t*)dst = *(uint16_t*)first;
                *(uint16_t*)((char*)d - 0xa) = *(uint16_t*)((char*)s - 0x26);
                *(uint32_t*)((char*)d - 8) = *(uint32_t*)((char*)s - 0x24);
                *(uint32_t*)((char*)d - 4) = *(uint32_t*)((char*)s - 0x20);
                *(uint32_t*)((char*)d) = *(uint32_t*)((char*)s - 0x1c);
                *(uint32_t*)((char*)d + 4) = *(uint32_t*)((char*)s - 0x18);
                *(uint32_t*)((char*)d + 8) = *(uint32_t*)((char*)s - 0x14);
                *(uint32_t*)((char*)d + 0xc) = *(uint32_t*)((char*)s - 0x10);
                *(uint32_t*)((char*)d + 0x10) = *(uint32_t*)((char*)s - 0xc);
                *(uint32_t*)((char*)d + 0x14) = *(uint32_t*)((char*)s - 8);
                *(uint32_t*)((char*)d + 0x18) = *(uint32_t*)((char*)s - 4);
                *(uint32_t*)((char*)d + 0x1c) = *(uint32_t*)((char*)s);
                *(uint32_t*)((char*)d + 0x20) = *(uint32_t*)((char*)s + 4);
                *(uint32_t*)((char*)d + 0x24) = *(uint32_t*)((char*)s + 8);
                *(uint32_t*)((char*)d + 0x28) = *(uint32_t*)((char*)s + 0xc);
                *(uint32_t*)((char*)d + 0x2c) = *(uint32_t*)((char*)s + 0x10);
                *(uint32_t*)((char*)d + 0x30) = *(uint32_t*)((char*)s + 0x14);
                *(uint32_t*)((char*)d + 0x34) = *(uint32_t*)((char*)s + 0x18);
                *(uint32_t*)((char*)d + 0x38) = *(uint32_t*)((char*)s + 0x1c);
                *(uint32_t*)((char*)d + 0x3c) = *(uint32_t*)((char*)s + 0x20);
            }
            first = (cDistributeSample_s00a8_9de0*)((char*)first + 0x4c);
            s = (uint32_t*)((char*)s + 0x4c);
            dst = (cDistributeSample_s00a8_9de0*)((char*)dst + 0x4c);
            d = (uint32_t*)((char*)d + 0x4c);
        } while (first != last);
        result = dst;
    }
    return result;
}

// @ 0x00a8a0a0
cDistributeSample_s00a8_9de0* FUN_00a8a0a0(cDistributeSample_s00a8_9de0* first, cDistributeSample_s00a8_9de0* last, cDistributeSample_s00a8_9de0* dst)
{
    cDistributeSample_s00a8_9de0* out = dst;
    if (first != last) {
        do {
            ((void*(__thiscall*)(void*, const void*))&FUN_00537dc0)(&dst->mTransform, &first->mTransform);
            *(uint32_t*)&dst->mColorAlpha[0] = *(uint32_t*)&first->mColorAlpha[0];
            *(uint32_t*)&dst->mColorAlpha[1] = *(uint32_t*)&first->mColorAlpha[1];
            *(uint32_t*)&dst->mColorAlpha[2] = *(uint32_t*)&first->mColorAlpha[2];
            *(uint32_t*)&dst->mColorAlpha[3] = *(uint32_t*)&first->mColorAlpha[3];
            dst->mNumber = first->mNumber;
            ++first;
            ++dst;
        } while (first != last);
        out = dst;
    }
    return out;
}

// @ 0x00a8a0f0
cDistributeSample_s00a8_9de0* FUN_00a8a0f0(cDistributeSample_s00a8_9de0* first, cDistributeSample_s00a8_9de0* last, cDistributeSample_s00a8_9de0* dst)
{
    cDistributeSample_s00a8_9de0* out = dst;
    if (last != first) {
        do {
            last = (cDistributeSample_s00a8_9de0*)((char*)last - 0x4c);
            dst = (cDistributeSample_s00a8_9de0*)((char*)dst - 0x4c);
            ((void*(__thiscall*)(void*, const void*))&FUN_00537dc0)(&dst->mTransform, &last->mTransform);
            *(uint32_t*)&dst->mColorAlpha[0] = *(uint32_t*)&last->mColorAlpha[0];
            *(uint32_t*)&dst->mColorAlpha[1] = *(uint32_t*)&last->mColorAlpha[1];
            *(uint32_t*)&dst->mColorAlpha[2] = *(uint32_t*)&last->mColorAlpha[2];
            *(uint32_t*)&dst->mColorAlpha[3] = *(uint32_t*)&last->mColorAlpha[3];
            dst->mNumber = last->mNumber;
        } while (last != first);
        out = dst;
    }
    return out;
}

// @ 0x00a8a450
void cDistributeEffect_s00a8_a450::Stream_Quad_V3F_C4B_T2F(IVertexStream* stream)
{
  int instanceCount = (int)(mInstancesEnd - mInstancesBegin);

  int total = 0;
  for (int i = 0; i < instanceCount; ++i)
    total += (int)(mInstancesBegin[i]->mSamplesEnd - mInstancesBegin[i]->mSamplesBegin);

  int remaining = total;
  int groupIndex = 0;
  int groupRemaining = 0;
  cDistributeSample_s00a8_a450* sample;
  uint8_t* buffer;
  int stride;

  while (remaining > 0) {
    int n = stream->Acquire(remaining, &buffer, &stride);
    remaining -= n;
    if (n <= 0) {
      stream->Commit();
      continue;
    }

    while (true) {
      if (groupRemaining == 0) {
        do {
          cDistributeEffect_s00a8_a450* p = mInstancesBegin[groupIndex++];
          sample = p->mSamplesBegin;
          groupRemaining = (int)(p->mSamplesEnd - sample);
        } while (groupRemaining == 0);
      }

      int take = (n < groupRemaining) ? n : groupRemaining;
      groupRemaining -= take;
      if (take <= 0)
        continue;

      for (int k = 0; k < take; ++k) {
        cTransform_s00a8_a450 xf(sample->mTransform);
        xf.PostTransformBy(mTransform);

        OutRow* d = (OutRow*)(buffer + mPosOffset);
        d[0].v = Vector3(xf.mRotation.row[0].x * xf.mScale,
                         xf.mRotation.row[0].y * xf.mScale,
                         xf.mRotation.row[0].z * xf.mScale);
        d[1].v = Vector3(xf.mRotation.row[1].x * xf.mScale,
                         xf.mRotation.row[1].y * xf.mScale,
                         xf.mRotation.row[1].z * xf.mScale);
        d[2].v = Vector3(xf.mRotation.row[2].x * xf.mScale,
                         xf.mRotation.row[2].y * xf.mScale,
                         xf.mRotation.row[2].z * xf.mScale);
        d[3].v = xf.mOffset;

        OutRow* e = (OutRow*)(buffer + mColorOffset);
        e->v = Vector3(sample->mColor[0], sample->mColor[1], sample->mColor[2]);
        e->w = sample->mColor[3] * mAlphaScale;

        ++sample;
        buffer += stride;
      }
    }
  }

  ++mRenderCount;
}

// @ 0x00a8aec0
namespace EA { namespace Swarm {
void Stream_Quad_V4F_N4F_C4B_T2F(cDistributeEffect_s00a8_aec0* effect, IVertexStream_s00a8_aec0* stream, uint8_t* offsets)
{
  int remaining = (int)(effect->mSamplesEnd - effect->mSamplesBegin);
  float inv = 1.0f / (float)effect->mDivisor;
  int sampleIndex = 0;

  T2F uv0; uv0.u = 0.0f; uv0.v = 0.0f;
  T2F uv1; uv1.u = 1.0f; uv1.v = 0.0f;
  T2F uv2; uv2.u = 1.0f; uv2.v = 1.0f;
  T2F uv3; uv3.u = 0.0f; uv3.v = 1.0f;

  while (remaining > 0) {
    uint8_t* buffer;
    int stride;
    int n = stream->Acquire(remaining, &buffer, &stride);

    uint8_t* pPos = buffer + offsets[0];
    uint8_t* pNrm = buffer + offsets[1];
    uint8_t* pCol = buffer + offsets[2];
    uint8_t* pTex = buffer + offsets[3];

    if (n > 0) {
      cDistributeSample_s00a8_aec0* sample = effect->mSamplesBegin + sampleIndex;
      sampleIndex += n;
      for (int k = 0; k < n; ++k) {
        cTransform_s00a8_aec0 xf(sample->mTransform);
        xf.PostTransformBy(effect->mTransform);

        float t = ((float)sample->mIndex + 0.5f) * inv;

        uint8_t r = ColorToByte(sample->mColor[0]);
        uint8_t g = ColorToByte(sample->mColor[1]);
        uint8_t b = ColorToByte(sample->mColor[2]);
        uint8_t a = ColorToByte(sample->mColor[3]);
        uint32_t color = ((((uint32_t)a << 8 | r) << 8 | g) << 8) | b;

        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv0);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv1);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv2);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv3);
        ++sample;
      }
    }

    stream->Commit();
    remaining -= n;
  }
}
}}  // namespace EA::Swarm

// @ 0x00a8b420
namespace EA { namespace Swarm {
void Stream_Quad_V4F_N4F_C4B_T4B(cDistributeEffect_s00a8_aec0* effect, IVertexStream_s00a8_aec0* stream, uint8_t* offsets)
{
  int remaining = (int)(effect->mSamplesEnd - effect->mSamplesBegin);
  float inv = 1.0f / (float)effect->mDivisor;
  int sampleIndex = 0;

  while (remaining > 0) {
    uint8_t* buffer;
    int stride;
    int n = stream->Acquire(remaining, &buffer, &stride);

    uint8_t* pPos = buffer + offsets[0];
    uint8_t* pNrm = buffer + offsets[1];
    uint8_t* pCol = buffer + offsets[2];
    uint8_t* pTex = buffer + offsets[3];

    if (n > 0) {
      cDistributeSample_s00a8_aec0* sample = effect->mSamplesBegin + sampleIndex;
      sampleIndex += n;
      for (int k = 0; k < n; ++k) {
        cTransform_s00a8_aec0 xf(sample->mTransform);
        xf.PostTransformBy(effect->mTransform);

        float t = ((float)sample->mIndex + 0.5f) * inv;

        uint8_t r = ColorToByte(sample->mColor[0]);
        uint8_t g = ColorToByte(sample->mColor[1]);
        uint8_t b = ColorToByte(sample->mColor[2]);
        uint8_t a = ColorToByte(sample->mColor[3]);
        uint32_t color = ((((uint32_t)a << 8 | r) << 8 | g) << 8) | b;

        int32_t frame = (int32_t)sample->mIndex * 0x41c64e6d + 0x3039;
        uint32_t corner = (uint32_t)(frame >> 24 & 0xff) | (uint32_t)(frame >> 16) << 24;

        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xff0000);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xffff00);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xff00);
        ++sample;
      }
    }

    stream->Commit();
    remaining -= n;
  }
}
}}  // namespace EA::Swarm

// @ 0x00a8bf60
namespace EA { namespace Swarm {
template <class T> void SpVector_s00a8_b940<T>::reserve(unsigned n)
{
  if (size() < n) {
    T* pNew = 0;
    if (n)
      pNew = (T*)EAAllocate(n * sizeof(T), kEASTLTag, 0, 0, kEASTLFile, 0xd1);
    UninitCopyPtr(mpBegin, mpEnd, pNew);
    FreeBlock_s00a8_b940(mpBegin);
    unsigned nOld = size();
    mpBegin = pNew;
    mpEnd = pNew + nOld;
    mpCapacity = pNew + n;
  }
}
}}  // namespace EA::Swarm

// @ 0x00a8c070
namespace EA { namespace Swarm {
RefVertex* UninitCopyVertex(RefVertex* first, RefVertex* last, RefVertex* dst)
{
  if (first == last)
    return dst;
  do {
    void* nv = first->mp;
    void* ov = dst->mp;
    if (nv != ov) {
      if (nv)
        ((RefVertexObj*)nv)->AddRef();
      dst->mp = nv;
      if (ov)
        ((RefVertexObj*)ov)->Release();
    }
    dst->mPad[0] = first->mPad[0];
    dst->mPad[1] = first->mPad[1];
    dst->mPad[2] = first->mPad[2];
    dst->mPad[3] = first->mPad[3];
    dst->mPad[4] = first->mPad[4];
    ++first;
    ++dst;
  } while (first != last);
  return dst;
}
}}  // namespace EA::Swarm

// @ 0x00a8c440
namespace EA { namespace Swarm {
template <class T> SpVector_s00a8_b940<T>::~SpVector_s00a8_b940()
{
  T* p = mpBegin;
  T* end = mpEnd;
  if (p < end) {
    do {
      void* obj = ((RefVertex*)p)->mp;
      if (obj)
        ((RefVertexObj*)obj)->AddRef();
      p = (T*)((uint8_t*)p + sizeof(T));
    } while (p < end);
  }
  FreeBlock_s00a8_b940(mpBegin);
}
}}  // namespace EA::Swarm

// @ 0x00a8c480
namespace EA { namespace Swarm {
SampleVector_s00a8_b940::SampleVector_s00a8_b940(const SampleVector_s00a8_b940& src)
{
  VectorDoAllocate(this, (unsigned)(src.mpEnd - src.mpBegin), (void*)&src.mAllocator[0]);
  UninitCopyVec(&mpEnd, src.mpBegin, src.mpEnd, mpBegin, (void*)&src.mAllocator[0]);
}
}}  // namespace EA::Swarm

// @ 0x00a8c4e0
namespace EA { namespace Swarm {
RefPtr* PtrVector::erase(RefPtr* first, RefPtr* last)
{
  RefPtr* p = (RefPtr*)MovePtr(last, mpEnd, first);
  RefPtr* end = mpEnd;
  while (p < end) {
    if (p->mp)
      ((RefCounted*)p->mp)->Release();
    ++p;
  }
  mpEnd -= last - first;
  return first;
}
}}  // namespace EA::Swarm

// @ 0x00a8c540
namespace EA { namespace Swarm {
template <class T> void SpVector_s00a8_b940<T>::insert(T* position, const T& value)
{
  if (mpEnd != mpCapacity) {
    T* src = (T*)&value;
    if (src >= position && src < mpEnd)
      src = (T*)((uint8_t*)src + sizeof(T));
    if (mpEnd) {
      T* e = mpEnd;
      e->mp = mpEnd[-1].mp;
      e->mPad[0] = mpEnd[-1].mPad[0];
      e->mPad[1] = mpEnd[-1].mPad[1];
      e->mPad[2] = mpEnd[-1].mPad[2];
      e->mPad[3] = mpEnd[-1].mPad[3];
      e->mPad[4] = mpEnd[-1].mPad[4];
    }
    CopyBack(position, mpEnd - 1, mpEnd);
    position->mp = src->mp;
    position->mPad[0] = src->mPad[0];
    position->mPad[1] = src->mPad[1];
    position->mPad[2] = src->mPad[2];
    position->mPad[3] = src->mPad[3];
    position->mPad[4] = src->mPad[4];
    mpEnd += 1;
    return;
  }

  unsigned nPrev = size();
  unsigned nNew = (nPrev > 0) ? nPrev * 2 : 1;
  T* pNew = (T*)EAAllocate(nNew * sizeof(T), kEASTLTag, 0, 0, kEASTLFile, 0xd1);
  T* p = UninitCopyVertex((RefVertex*)mpBegin, (RefVertex*)position, (RefVertex*)pNew);
  if (p) {
    p->mp = value.mp;
    p->mPad[0] = value.mPad[0];
    p->mPad[1] = value.mPad[1];
    p->mPad[2] = value.mPad[2];
    p->mPad[3] = value.mPad[3];
    p->mPad[4] = value.mPad[4];
    p = (T*)((uint8_t*)p + sizeof(T));
  }
  T* pEnd = UninitCopyVertex((RefVertex*)position, (RefVertex*)mpEnd, (RefVertex*)p);
  FreeBlock_s00a8_b940(mpBegin);
  mpBegin = pNew;
  mpEnd = pEnd;
  mpCapacity = pNew + nNew;
}
}}  // namespace EA::Swarm

// @ 0x00a8c690
namespace EA { namespace Swarm {
void PtrVector::insert(RefPtr* position, unsigned n, const RefPtr& value)
{
  unsigned nCapacity = (unsigned)(mpCapacity - mpEnd);
  if (n > nCapacity) {
    unsigned nPrev = (unsigned)(mpEnd - mpBegin);
    unsigned nGrow = (nPrev > 0) ? nPrev * 2 : 1;
    unsigned nNew = (nPrev + n > nGrow) ? (nPrev + n) : nGrow;
    RefPtr* pNew = nNew ? (RefPtr*)EAAllocate(nNew * sizeof(RefPtr), kEASTLTag, 0, 0, kEASTLFile, 0xd1) : 0;
    unsigned nPre = (unsigned)(position - mpBegin);
    unsigned nPost = (unsigned)(mpEnd - position);
    RefPtr* p = (RefPtr*)MemMove(pNew, mpBegin, nPre * sizeof(RefPtr));
    p = (RefPtr*)((uint8_t*)p + nPre * sizeof(RefPtr));
    UninitFillPtr(p, n, (void*)&value);
    RefPtr* pEnd = (RefPtr*)((uint8_t*)p + n * sizeof(RefPtr));
    MemMove(pEnd, position, nPost * sizeof(RefPtr));
    FreeBlock_s00a8_b940(mpBegin);
    mpBegin = pNew;
    mpEnd = (RefPtr*)((uint8_t*)pEnd + nPost * sizeof(RefPtr));
    mpCapacity = pNew + nNew;
    return;
  }

  if (n == 0)
    return;

  void* obj = value.mp;
  if (obj)
    ((RefCounted*)obj)->AddRef();

  unsigned nExtra = (unsigned)(mpEnd - position);
  if (n < nExtra) {
    RefPtr* newEnd = mpEnd + n;
    UninitMovePtr(&newEnd, mpEnd - n, mpEnd, mpEnd);
    mpEnd += n;
    MoveBackPtr(position, mpEnd - n, newEnd);
    CopyPtrAssign(position, position + n, (void*)&value);
  } else {
    UninitFillPtr(mpEnd, n - nExtra, (void*)&value);
    mpEnd += n - nExtra;
    UninitMovePtr(&mpEnd, position, mpEnd - (n - nExtra), mpEnd);
    mpEnd += nExtra;
    CopyPtrAssign(position, mpEnd - nExtra, (void*)&value);
  }

  if (obj)
    ((RefCounted*)obj)->Release();
}
}}  // namespace EA::Swarm

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

// @ 0x00a8d450
namespace EA { namespace Swarm {
void cDistributeEffect_s00a8_d450::CreateSamples2D(int count, int first, int last)
{
  Vector2_s00a8_d450 SquareToRing(Vector2_s00a8_d450 p, float innerRadius);  // 0x00a88490
  Vector3 CubeToSphereSurface(const Vector3& v);  // 0x00a88400
  cTransform_s00a8_d450 tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;

  cTransform_s00a8_d450 sampleTransform;
  sampleTransform.SetRotation(tf.mRotation);
  sampleTransform.SetScale(mSizeScale);

  cHalton2D_s00a8_d450 gen;
  gen.Seed(mDesc->mSeed + first);
  bool bReseed = (mDesc->mFlags >> 13) & 1;
  for (int i = first; i < last; ++i) {
    gen.Next();
    if (bReseed && (uint8_t)gen.mIndex == 0)
      gen.Seed(mDesc->mSeed + i + 1);

    Vector2_s00a8_d450 p;
    p = gen.mValue;
    switch (mDesc->mSourceType) {
      case 0:
        p = Vector2_s00a8_d450(gen.mValue.x * 2.0f - kVector2One_s00a8_d450.x, gen.mValue.y * 2.0f - kVector2One_s00a8_d450.y);
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
      FastSinCos_s00a8_d450(angle, s, c);
      pos = Vector3(c * radius, s * radius, z);
    } else if (mFlags & 0x20) {
      pos = CubeToSphereSurface(pos);
    }

    if (tf.mFlags & cTransform_s00a8_d450::kRotation)
      pos = Rotate_s00a8_d450(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = tf.mOffset.y + pos.y * tf.mScale;
    pos.z = tf.mOffset.z + pos.z * tf.mScale;

    if (mEmitMap && IsMaskedOut(pos, i, count))
      continue;
    if (mPinMap)
      PinToMap(pos);
    sampleTransform.SetOffset(pos);

    const cTransform_s00a8_d450& descTransform = mDesc->mTransform;
    cDistributeSample_s00a8_d450 sample;
    if (descTransform.mScale == 1.0f &&
        !(descTransform.mFlags & (cTransform_s00a8_d450::kRotation | cTransform_s00a8_d450::kOffset))) {
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

// @ 0x00a8dea0
namespace EA { namespace Swarm {
void cDistributeEffect_s00a8_dea0::CreateClusteredSamples2D(int count, int first, int last)
{
  Vector2_s00a8_dea0 SquareToRing(Vector2_s00a8_dea0 p, float innerRadius);  // 0x00a88490
  Vector3 CubeToSphereSurface_00a88400(const Vector3& v);  // 0x00a88400
  cTransform_s00a8_dea0 tf(mSourceTransform);
  if (mSubdivOwner)
    tf = *mSubdivOwner->mpTransform;

  cTransform_s00a8_dea0 sampleTransform;
  sampleTransform.SetRotation(tf.mRotation);
  sampleTransform.SetScale(mSizeScale);

  int n = mDesc->mNumClusters;
  int base = mDesc->mClusterStart;
  int seedIndex = mDesc->mSeed + first;
  int cell = seedIndex / n;
  cHalton2D_s00a8_dea0 cellGen;
  cHalton2D_s00a8_dea0 subGen;
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

    Vector2_s00a8_dea0 p;
    p.x = dx * mDesc->mClusterScale + cellGen.mValue.x;
    p.y = cellGen.mValue.y + dy * mDesc->mClusterScale;
    switch (mDesc->mSourceType) {
      case 0:
        p = Vector2_s00a8_dea0(p.x * 2.0f - kVector2One_s00a8_dea0.x, p.y * 2.0f - kVector2One_s00a8_dea0.y);
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
      FastSinCos_s00a8_dea0(angle, s, c);
      pos = Vector3(c * r, s * r, z);
    } else if (mFlags & 0x20) {
      pos = CubeToSphereSurface_00a88400(pos);
    }

    if (tf.mFlags & cTransform_s00a8_dea0::kRotation)
      pos = Rotate_s00a8_dea0(pos, tf.mRotation);
    pos.x = tf.mOffset.x + tf.mScale * pos.x;
    pos.y = tf.mOffset.y + pos.y * tf.mScale;
    pos.z = tf.mOffset.z + pos.z * tf.mScale;
    if (!(mEmitMap && IsMaskedOut(pos, i, count))) {
      if (mPinMap)
        PinToMap(pos);
      sampleTransform.SetOffset(pos);
      const cTransform_s00a8_dea0& descTransform = mDesc->mTransform;
      if (descTransform.mScale != 1.0f ||
          (descTransform.mFlags & (cTransform_s00a8_dea0::kRotation | cTransform_s00a8_dea0::kOffset))) {
        cTransform_s00a8_dea0 t(sampleTransform);
        t.PreTransformBy(descTransform);
        cDistributeSample_s00a8_dea0 sample(t, i);
        mSamples.push_back(sample);
      } else {
        cDistributeSample_s00a8_dea0 sample(sampleTransform, i);
        mSamples.push_back(sample);
      }
    }
  }
}
}}  // namespace EA::Swarm

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

// @ 0x00a92450
bool cDistributeEffect_s00a9_2450::SetFloatParams(int param, const float* data, int count)
{
    if (param <= 0xe) {
        if (param != 0xe) {
            switch (param) {
            case 1: {
                if ((mFlags >> 0xd) & 1)
                    mField18C = data[0];
                break;
            }
            case 4: {
                mField180 = data[0];
                break;
            }
            case 5: {
                mVec170 = V3_s00a9_2450(data[0], data[1], data[2]);
                break;
            }
            }
        } else {
            if (mOverrideID_hi >= 0) {
                uint32_t flags = mDesc->mFlags;
                void* o = mWorld->v20();
                FnSetShader fn = (FnSetShader)(*(void***)o)[0x74 / 4];
                return fn(o, (~(int)(flags >> 8)) & 1, mOverrideID_hi, 0, count, data);
            }
        }
    } else {
        switch (param) {
        case 0x10: {
            cDistributeDescription_s00a9_2450* d = mDesc;
            if (!((d->mFlags >> 2) & 1))
                break;
            float v0 = d->mAltitudeRange[0];
            float v1 = d->mAltitudeRange[1];
            const float* p = data;
            int i = 0;
            if (count > 0) {
                do {
                    if (count == 2 || (int)p[2] == (int)d->mOverrideSet) {
                        v0 = p[0];
                        v1 = p[1];
                        break;
                    }
                    i += 3;
                    p += 3;
                } while (i < count);
            }
            if (mAltitudeRange[0] != v0 || !(mAltitudeRange[1] == v1)) {
                mAltitudeRange[0] = v0;
                mAltitudeRange[1] = v1;
                ClearSamples(0);
            }
            return true;
        }
        case 0x11: {
            mSubdivOffset = *(const V3_s00a9_2450*)data;
            float s = mDesc->mScale;
            mSubdivScale = V3_s00a9_2450(s, s, s);
            mul_705290(&mSubdivScale, (const V3_s00a9_2450*)(data + 3));
            return true;
        }
        case 0x14: {
            if ((mFlags >> 0xd) & 1) {
                if (count == 1) {
                    mField18C = data[0];
                    return true;
                }
                mField18C = 1.0f;
                float want = (float)mDesc->mOverrideSet;
                for (int i = 0; i < count; i += 2) {
                    if (data[i + 1] == want) {
                        mField18C = data[i];
                        break;
                    }
                }
                return true;
            }
            break;
        }
        case 0x101: {
            mField184 = data[2];
            mField188 = data[5];
            if (mDesc->mSourceType >= 1) {
                int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
                for (int i = 0; i < n; ++i)
                    mEffects.mpBegin[i]->SetFloatParams(param, data, count);
            }
            return true;
        }
        }
    }

    // default: propagate to children, then store in the child parameter block.
    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetFloatParams(param, data, count);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    mChildParams->FloatStore(param, data, count);
    return changed;
}

// @ 0x00a92920
bool cDistributeEffect_s00a9_2450::SetIntParams(int param, const int* data, int count)
{
    switch (param) {
    case 0: {
        if (!((mDesc->mFlags >> 8) & 1))
            break;
        int v0 = -1, v1 = -1;
        int i = 0;
        if (count > 0) {
            do {
                if (count < 2 || data[i + 1] == (int)(uint8_t)mDesc->mOverrideSet) {
                    v0 = data[i];
                    v1 = 0;
                    break;
                }
                i += 2;
            } while (i < count);
        }
        if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
            uint32_t flags = mFlags;
            mFormat0 = v0;
            mFormat1 = v1;
            if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                ReleaseRenderSet();
                CreateRenderSet();
            }
        }
        return true;
    }
    case 1: {
        if (!((mDesc->mFlags >> 7) & 1))
            break;
        int v0 = -1, v1 = -1;
        int i = 0;
        if (count > 0) {
            do {
                if (count < 2 || data[i + 1] == (int)(uint8_t)mDesc->mOverrideSet) {
                    v0 = data[i];
                    v1 = 0;
                    break;
                }
                i += 2;
            } while (i < count);
        }
        if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
            uint32_t flags = mFlags;
            mFormat0 = v0;
            mFormat1 = v1;
            if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                ReleaseRenderSet();
                CreateRenderSet();
            }
        }
        return true;
    }
    case 4:
        mField190 = data[0];
        mField194 = data[1];
        return true;
    case 5:
        if (*(const uint8_t*)data & 7)
            ClearSamples(0);
        if (*(const uint8_t*)data & 8)
            mFlags |= 0x400;
        return true;
    }

    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetIntParams(param, data, count);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    mChildParams->IntStore(param, data, count);
    return changed;
}

// @ 0x00a92b80
bool cDistributeEffect_s00a9_2450::SetUnknownParam(int param, void* data)
{
    switch (param) {
    case 3: {
        if (((mFlags >> 0xd) & 1) || ((mDesc->mFlags >> 0xe) & 1)) {
            cDistributeDescription_s00a9_2450* d = mDesc;
            if ((d->mFlags >> 0xe) & 1) {
                void* o = mWorld->v30();
                FnGetDesc fn = (FnGetDesc)(*(void***)o)[0x70 / 4];
                d = fn(o, d->mSourceType, d->mEffectIndex, mCollectionIndex);
            }
            int v0 = -1, v1 = -1;
            cSurfaceData* sd = (cSurfaceData*)data;
            int cnt = sd->mCount;
            volatile int want = d->mOverrideSet;
            int i = 0;
            if (cnt > 0) {
                do {
                    if (sd->mRecs[i].key == want) {
                        v0 = sd->mRecs[i].v0;
                        v1 = sd->mRecs[i].v1;
                        break;
                    }
                    ++i;
                } while (i < cnt);
            }
            if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
                uint32_t flags = mFlags;
                mFormat1 = v1;
                mFormat0 = v0;
                if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                    ReleaseRenderSet();
                    CreateRenderSet();
                }
            }
            if (!((mDesc->mFlags >> 0xe) & 1))
                return true;
        }
        break;
    }
    case 4: {
        mField118 = data;
        if (((cSurfaceData*)data)->mCount == 3)
            mFlags |= 0x10;
        else
            mFlags &= ~0x10;
        if (((cSurfaceData*)mField118)->mCount == 6) {
            mFlags |= 0x20;
            return true;
        }
        mFlags &= ~0x20;
        return true;
    }
    }

    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetUnknownParam(param, data);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    cSurfaceData* sd = (cSurfaceData*)data;
    void* old = mChildParams->mUnknownParams[param];
    if (data != old) {
        if (data)
            sd->AddRef();
        mChildParams->mUnknownParams[param] = data;
        if (old)
            ((cSurfaceData*)old)->Release();
    }
    return changed;
}

// @ 0x00a92d90
int cDistributeEffect_s00a9_2d90::UpdateSamples(int target)
{
    RawVec tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;

    int savedRender = mRenderSampleCount;
    int newRender = mTargetSampleCount;
    int oldCount = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;

    int limit = 0;
    if (mDesc->mFlags & 1) {
        CreateClusteredMatchingSamples2D(&tmp);
    } else {
        if (target != 0) {
            if (mDesc->mFlags & 0x2000)
                limit = ((savedRender + mDesc->mField18 + target + 0xff) & 0xffffff00) - mDesc->mField18;
            else
                limit = savedRender + target;
            if (newRender > limit)
                newRender = limit;
        }
        if (mDesc->mField1c < 3) {
            if (mDesc->mField160 <= 0)
                CreateSamples2D(mTargetSampleCount, savedRender, newRender);
            else
                CreateClusteredSamples2D(mTargetSampleCount, savedRender, newRender);
        } else {
            CreateRandomSamples(mTargetSampleCount, savedRender, newRender);
        }
    }

    int newCount = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;
    if (newCount > oldCount) {
        if (mSurfaceRecs.mpBegin != mSurfaceRecs.mpEnd)
            PinSamplesToSurface(oldCount, newCount);
        if ((mDesc->mFlags & 0x10) || (mDesc->mFlags & 0x40))
            RigidTransformRange(oldCount, newCount);
        if (mDesc->mFlags & 0x20)
            ApplyColorAndAlpha(oldCount, newCount);
    }

    mRenderSampleCount = newRender;

    if (mDesc->mpEffectData15c != 0 && newRender > 0 && newRender == mTargetSampleCount) {
        EA::Messaging::IServer* server = EA::Messaging::GetServer();
        if (server) {
            MsgPair r = GetEffectMessage(this);
            struct EffectMsg {
                int             mSampleCount;            // +0x00
                int             mField04;                // +0x04
                cDistributeSample_s00a9_2d90* mpSampleBegin;        // +0x08
                int   mPad0c;                            // +0x0c
                cDistributeEffect_s00a9_2d90* mpEffect;             // +0x10
                int   mPad14;                            // +0x14
                int   mMsgLo;                            // +0x18
                int   mMsgHi;                            // +0x1c
                int   mField20;                          // +0x20
                int   mPad24;                            // +0x24
                int   mField28;                          // +0x28
                int   mPad2c;                            // +0x2c
                int   mField30;                          // +0x30
                int   mPad34;                            // +0x34
                int   mField38;                          // +0x38
            } msg;
            msg.mSampleCount  = newCount;
            msg.mpSampleBegin = mSamples.mpBegin;
            msg.mpEffect      = this;
            msg.mMsgLo        = r.mLo;
            msg.mMsgHi        = r.mHi;
            msg.mField20      = mField190;
            msg.mField28      = mField194;
            msg.mField30      = 0;
            msg.mField38      = 0;
            server->Post((int)mDesc->mpEffectData15c, &msg, 0);
        }
        if (!((mFlags >> 2) & 1) && !((mFlags >> 0xd) & 1))
            ((void(__thiscall*)(cDistributeEffect_s00a9_2d90*, int))((void**)mpVtbl)[3])(this, 0);
    }

    if (!((mFlags >> 2) & 1)) {
        if (mRenderSampleCount == mTargetSampleCount && mTargetSampleCount > 0) {
            mRenderSamples.swap(mSamples);
            mSamples.Free();
            if (mSetID >= 0) {
                cBounds bounds;
                bounds.Init();
                int count = (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c;
                float maxScale = 0.0f;
                for (int i = 0; i < count; ++i) {
                    cDistributeSample_s00a9_2d90* s = (cDistributeSample_s00a9_2d90*)((char*)mRenderSamples.mpBegin + i * 0x4c);
                    if (s->mPosition.x < bounds.mMinX) bounds.mMinX = s->mPosition.x;
                    if (s->mPosition.x > bounds.mMaxX) bounds.mMaxX = s->mPosition.x;
                    if (s->mPosition.y < bounds.mMinY) bounds.mMinY = s->mPosition.y;
                    if (s->mPosition.y > bounds.mMaxY) bounds.mMaxY = s->mPosition.y;
                    if (s->mPosition.z < bounds.mMinZ) bounds.mMinZ = s->mPosition.z;
                    if (s->mPosition.z > bounds.mMaxZ) bounds.mMaxZ = s->mPosition.z;
                    if (s->mScale > maxScale) maxScale = s->mScale;
                }
                cEffectWorldObj* w = mWorld->v20();
                if (mDesc->mFlags & 0x100) {
                    w->v34(mSetID, &mVec170, mCurrentSubdivScale);
                    w->v38(mSetID, (mFlags >> 1) & 1);
                } else {
                    w->SetBounds(mSetID, (cBounds*)&mVec170, mCurrentSubdivScale);
                    w->SetBoundsEx(mSetID, (mFlags >> 1) & 1);
                }
            }
        }
    } else {
        // resize mEffects to the render sample count, releasing/acquiring the tail
        RefVec* ev = (RefVec*)&mEffects;
        int want = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;
        int have = (int)((char*)ev->mpEnd - (char*)ev->mpBegin) >> 2;
        for (int i = want; i < have; ++i)
            ev->mpBegin[i].mpObject->v0c(0);
        if (want < have)
            PtrVecErase(ev->mpBegin + want, ev->mpEnd);
        else {
            void* zero = 0;
            PtrVecInsert(ev->mpEnd, want - have, &zero);
        }
        if (have <= want) {
            for (int i = 0; i < have; ++i)
                ev->mpBegin[i].mpObject->v18((char*)mSamples.mpEnd + i * 0x4c - 0xc, &mRigidTransform);

            int dataOff1 = mField194 ? mField194 * mTargetSampleCount : mTargetSampleCount;
            int dataOff2 = mField190 ? mField190 * mTargetSampleCount : 0;

            while (have < want) {
                cIVisualEffect_s00a9_2d90* fx = MakeVisualEffect(mDesc->mField14, mDesc->mField10,
                                                      mCollectionIndex, mChildParams);
                cIVisualEffect_s00a9_2d90* old = ev->mpBegin[have].mpObject;
                if (fx != old) {
                    if (fx) fx->v34();
                    ev->mpBegin[have].mpObject = fx;
                    if (old) old->v38();
                }
                fx->v28((mFlags >> 1) & 1);
                if (mDesc->mFlags & 0x4000)
                    *(int*)((char*)fx + 0x28) |= 0x800;
                if (mDesc->mField14 != 0 && mChildParams)
                    EffectPropagateParams(mChildParams, fx);

                if (tmp.mpBegin != tmp.mpEnd) {
                    fx->v1c(0x11, (char*)tmp.mpBegin + have * 0x18, 6);
                    cSurfacePayload* rec = (cSurfacePayload*)mField118;
                    if (!rec) {
                        rec = (cSurfacePayload*)EAAlloc(0x14, "Swarm", 0, 0, 0, 0);
                        if (rec) {
                            rec->mpVtbl = (void*)0x014582ec;
                            rec->mpVtbl2 = (void*)0x014188c0;
                            rec->mField08 = 0;
                            rec->mStateDataOffset = mDesc->mField1c;
                            rec->mpData = &mSourceTransform;
                        }
                    }
                    fx->v24(4, rec);
                }

                struct OffPair { int mOff0; int mOff1; } offs;
                offs.mOff0 = dataOff2 + have;
                offs.mOff1 = dataOff1;
                fx->v20(4, &offs, 2);
                fx->v18((char*)mSamples.mpBegin + have * 0x4c, &mRigidTransform);

                cDistributeSample_s00a9_2d90* s = (cDistributeSample_s00a9_2d90*)((char*)mSamples.mpBegin + have * 0x4c);
                float scl = s->mScale44 * mField180;
                Vector3_s00a9_2d90 v3;
                v3.x = s->mVec38.x * mVec170.x;
                v3.y = s->mVec38.y * mVec170.y;
                v3.z = s->mVec38.z * mVec170.z;
                fx->v1c(4, &scl, 1);
                fx->v1c(5, &v3, 3);
                fx->v08(0);
                ++have;
            }
        }
    }

    int result = newRender - savedRender;
    FreeVecBuffer(tmp.mpBegin);
    return result;
}

// @ 0x00a934e0
int cDistributeEffect_s00a9_2d90::ApplyEffect(void* param, float time, void* stats)
{
    mCurrentSubdivScale = (mField184 + (mField188 - mField184) * time) * mField180;

    if (mSetID >= 0) {
        cEffectWorldObj* w = mWorld->v20();
        if (mDesc->mFlags & 0x100)
            w->v34(mSetID, &mVec170, mCurrentSubdivScale);
        else
            w->SetBounds(mSetID, (cBounds*)&mVec170, mCurrentSubdivScale);
    }

    if (mSurfaceStateData.mpBegin != mSurfaceStateData.mpEnd && !((mFlags >> 6) & 1)) {
        for (cSurfaceRec_s00a9_2d90* rec = mSurfaceRecs.mpBegin; rec != mSurfaceRecs.mpEnd; ++rec) {
            void* obj = rec->mpObject;
            int state = (int)((char*)mSurfaceStateData.mpBegin + rec->mStateDataOffset);
            ((void(__thiscall*)(void*, int, void*, void*, int))((void**)obj)[8])(
                obj, rec->mField04, &mSourceTransform, &mRigidTransform, state);
        }
        mFlags |= 0x40;
    }
    (void)param;

    if (mpEffectData15c != 0 && !((mFlags >> 0xa) & 1)) {
        int mods = ((int(__thiscall*)(void*))((void**)mpEffectData15c)[4])(mpEffectData15c);
        if (mField168 != mods) {
            mField168 = mods;
            ClearSamples(1);
            mField16c = 0.0f;
        }
    }

    cDistributeEffectStats* st = (cDistributeEffectStats*)stats;
    if (mRenderSampleCount != mTargetSampleCount) {
        if (!(mDesc->mFlags & 0x1000)) {
            if (st->mFirst_38 == 0) {
                st->mFirst_34 += UpdateSamples(mGlobalParams ? *(int*)((char*)mGlobalParams + 0x18) : 0);
            } else {
                int want = st->mFirst_38 - st->mFirst_34;
                if (want > 0) {
                    int cap = *(int*)((char*)mGlobalParams + 0x18);
                    if (want > cap) want = cap;
                    st->mFirst_34 += UpdateSamples(want);
                }
            }
        } else {
            UpdateSamples(0);
        }
    }

    if (mRenderSampleCount == mTargetSampleCount && mDesc->mField10 >= 0) {
        if (mDesc->mField14 >= 1) {
            if (mDesc->mFlags & 0x4000) {
                if (!(mFlags & 0x1000)) {
                    Start(param, time, stats);
                } else if ((*mEffects.mpBegin)->IsReady()) {
                    for (cIVisualEffect_s00a9_2d90** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it)
                        (*it)->v14(param, time, stats);
                    mFlags &= ~0x1000;
                }
            } else {
                for (cIVisualEffect_s00a9_2d90** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it)
                    (*it)->v14(param, time, stats);
                st->mField08 += (int)(mEffects.mpEnd - mEffects.mpBegin);
            }
        } else if (mField168 == 0 || (mDesc->mFlags & 0x800)) {
            for (cIVisualEffect_s00a9_2d90** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it) {
                if ((*it)->v10())
                    goto done;
            }
            ((void(__thiscall*)(cDistributeEffect_s00a9_2d90*, int))((void**)mpVtbl)[3])(this, 0);
        }
    }
done:
    if (stats != 0 && mSetID >= 0) {
        if (mDesc->mFlags & 0x100) {
            st->mField18 += (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c;
            st->mField1c += (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c
                            * mSubdivCount;
        } else {
            st->mField10 += (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c;
            st->mField14 += (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c
                            * mSubdivCount;
        }
        mSubdivCount = 0;
    }
    // The retail code has no explicit return: on the paths that skip the stats block eax
    // still holds the last intermediate (ClearSamples/mod-count or the /0x4c quotient), so
    // this int result is undefined C++ in the original. A deterministic 0 is the only
    // source-level choice; difftest can differ in eax alone and nothing else.
    return 0;
}
