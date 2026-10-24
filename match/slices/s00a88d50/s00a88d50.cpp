// slice s00a88d50: EA::Swarm::cDistributeEffect, per-sample colour/alpha curves, random variation and
// colour-map modulation for samples [first, last) (0x00a88d50, 1851 bytes). Method name is Claude-coined
// ("ApplyColorAndAlpha"); the layout is retail (vectors are 0x14 bytes, not 0x10 as in the 2008 PDB).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for the double random range).
#include "types.h"
#include <intrin.h>

namespace EA { namespace Random {
class RandomLinearCongruential { public: double RandomDoubleUniform(); };   // 0x009360d0
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

extern Vector4 gDefaultSampleColor;        // 0x01678318 (default sample colour/alpha)

struct Matrix3 {
    float m[9];
    void CopyFrom(const Matrix3& src);     // 0x0041cb40 (out-of-line copy)
};

struct cTransform {                        // 0x38 bytes
    uint16_t mFlags;                       // +0x00 (bit 1: rotation)
    uint16_t mModCount;                    // +0x02
    Vector3 mOffset;                       // +0x04
    float mScale;                          // +0x10
    Matrix3 mRotation;                     // +0x14

    void CopyFrom(const cTransform* src);  // 0x00537dc0 (flags compare + full copy)
    void ApplyInverse(Vector3* p) const;   // 0x007cda70 (p = R^-1 * ((p - offset) / scale))
    void ApplyForward(Vector3* p) const;   // 0x007cdee0 (p = R * p * scale + offset)
};

// Object returned by the render host at +0x1c; the sample index is released on it.
struct IRenderTarget {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18();
    virtual void ReleaseUnshared(int index);                    // +0x1c
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void ReleaseShared(int index);                      // +0x30
};

struct IRenderHost {                       // object at effect +0x1c
    virtual void h00(); virtual void h04(); virtual void h08(); virtual void h0c();
    virtual void h10(); virtual void h14(); virtual void h18(); virtual void h1c();
    virtual IRenderTarget* GetTarget();                         // +0x20
};

struct IRefCounted {                       // samples at +0xbc are AddRef'd when copied out
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28(); virtual void r2c();
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
    cTransform mTransform;                 // +0x00
    Vector4 mColorAlpha;                   // +0x38
    int mNumber;                           // +0x48

    cDistributeSample() {}
    cDistributeSample(const cDistributeSample& src, int number);
};

struct cIMap {                             // colour map (vtable only)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool Contains(const Vector3* p);                    // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector4* Sample(Vector4* out, const Vector3* p);    // +0x2c
};

struct cISampleMap {                       // density/height map at +0x15c and +0x164
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
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
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28();
    virtual int GetSamples(int count, cSampleOut* out, int capacity);   // +0x2c
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
    cTransform mSourceTransform;           // +0x2c
    cTransform mRigidTransform;            // +0x64
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
    cIMap* mColorMap;                      // +0x160
    cISampleMap* mHeightMap;               // +0x164

    void ApplyColorAndAlpha(int first, int last);
    void ReleaseRenderSet();
    void Render(int target);
    void SetTransforms(cTransform* source, cTransform* rigid);
    bool ProjectSample(Vector3* pos, int i0, int i1);
    void MapSample(Vector3* pos);
};

// The effect seen through the sub-object that starts at +0xc (virtual dispatcher 0x00a89a30).
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

// Renderer entry points indexed by cDistributeEffect::mRenderType (table at 0x016781b0).
typedef void (__cdecl* RenderFn)(void* mesh, void* ctx, uint8_t* arg);
extern RenderFn gRenderFns[];              // 0x016781b0

// Copy `count` destination pointers from the single source pointer, AddRef'ing each object.
void CopySamplesWithAddRef(void** dst, unsigned count, void** src);

// Output records for one source list (0x00a89680).
int CollectSamples(cSampleTarget* target, cSampleSource* info, cSampleOut* out, int capacity);
void FillFromBaseTransform(void* base, unsigned char flag, int* count, cSampleOut** out, int* capacity);   // 0x00a6c7a0

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

// Column-dot form used when applying a rigid transform to a point (out.x = m0*x + m3*y + m6*z).
static __forceinline Vector3 MulCols(const Matrix3& m, const Vector3& v)
{
    return Vector3(m.m[6] * v.z + m.m[3] * v.y + m.m[0] * v.x,
                   m.m[7] * v.z + m.m[4] * v.y + m.m[1] * v.x,
                   m.m[8] * v.z + m.m[5] * v.y + m.m[2] * v.x);
}

// Render-context block handed to the per-platform callbacks (vtable 0x014582e0 lives at +0).
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
void cDistributeEffect::SetTransforms(cTransform* source, cTransform* rigid)
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
