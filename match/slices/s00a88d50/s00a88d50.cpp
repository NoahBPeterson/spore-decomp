// slice s00a88d50: EA::Swarm::cDistributeEffect, per-sample colour/alpha curves, random variation and
// colour-map modulation for samples [first, last) (0x00a88d50, 1851 bytes). Method name is Claude-coined
// ("ApplyColorAndAlpha"); the layout is retail (vectors are 0x14 bytes, not 0x10 as in the 2008 PDB).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for the double random range).
#include "types.h"
#include <intrin.h>

namespace EA { namespace Random {
struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x009360d0
} }
extern EA::Random::RandomLinearCongruential sRandom_Swarm;           // 0x016778dc

// Uniform random in [lo, hi], clamped (inlined helper in the original).
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

// Piecewise-linear curve lookup, t in [0,1] (both curve flavours are inlined in the original).
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

// Row-by-vector dot products (inverse-transform direction), sums grouped (z + y) + x as in the asm.
static __forceinline Vector3 MulRows(const Matrix3& m, const Vector3& v)
{
    return Vector3(m.m[2] * v.z + m.m[1] * v.y + m.m[0] * v.x,
                   m.m[5] * v.z + m.m[4] * v.y + m.m[3] * v.x,
                   m.m[8] * v.z + m.m[7] * v.y + m.m[6] * v.x);
}

// Undo a transform: (p - offset) / scale, then the rotation rows.
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

// Normalised position of a sample along the curves: (index + 0.5) / count.
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
