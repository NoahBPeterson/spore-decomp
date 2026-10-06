// Slice s00aabc20 — 0x00aabc20 (the frozen function list has ONE 11424-byte function here,
// but it is two packed functions: 0x00aabc20 (5664 B) and 0x00aad240 (5760 B)).
//
// Both are the EA::Swarm particle streamers of cParticlesEffect.obj (anonymous namespace,
// names and signatures from the 2008 dev PDB):
//   0x00aabc20  `anonymous namespace'::Stream_Quad_V4F_N4F_C4B_T2F   (dev 0x01447a00)
//   0x00aad240  `anonymous namespace'::Stream_Quad_V4F_N4F_C4B_T4B   (dev 0x01449070)
//     void (EA::Swarm::cParticlesEffect*, EA::Swarm::cITextureParticleRenderer*, unsigned char* offsets)
// They share one per-particle core (curve sampling, screw, wiggle, loop box, rigid transform,
// screen bloom, colour packing, velocity stretch, rotation) and differ only in how the quad's
// four vertices are written: T2F writes attribute-major with float UVs, T4B writes vertex-major
// with byte UVs + the particle's frame index in the top byte.
//
// Layouts: cParticlesEffect / cParticle / cTransform / cGlobalParams from the dev PDB (offsets
// agree with the retail disassembly); cParticlesDescription from the ModAPI ParticleEffect
// header (retail eastl::vector is 20 bytes, so the dev PDB offsets do not apply).
// Callees: 0x00aa9b70 `anonymous namespace'::StreamerSetup, 0x00a9aff0 EA::Swarm::WigglePoint,
// renderer vtable slot 0 GetBuffer, slot 2 ReleaseAndDrawBuffer.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (scalar SSE + x87 mix, 16-byte aligned frame).

#include <math.h>
#include <xmmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

namespace EA { namespace Swarm {

struct Vector3 {
    float x, y, z;
};

struct Matrix33 {
    float m[3][3];
};

struct Matrix44 {
    float m[4][4];
};

// Retail eastl::vector: begin/end/capacity + an 8-byte allocator (20 bytes).
template <typename T>
struct SPVector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];

    int  size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct cWiggle {                              // 0x1c
    float   mTimeRate;
    Vector3 mRateDir;
    Vector3 mWiggleDir;
};

struct cParticle {                            // 0x48
    cParticle* mpNext;                        // +0x00 intrusive_list_node
    cParticle* mpPrev;                        // +0x04
    float      mAge;                          // +0x08 cParticleBase
    float      mLife;                         // +0x0c
    Vector3    mPosition;                     // +0x10
    Vector3    mVelocity;                     // +0x1c
    float      mOverallSize;                  // +0x28 cParticleProperties
    float      mOverallAspect;                // +0x2c
    float      mOverallRotation;              // +0x30
    float      mOverallAlpha;                 // +0x34
    Vector3    mOverallColor;                 // +0x38
    u8         mFrame;                        // +0x44
    u8         mUnused[3];
};

struct cTransform {                           // 0x38
    u16      mFlags;                          // +0x00
    u16      mModificationCount;              // +0x02
    Vector3  mTranslation;                    // +0x04
    float    mScale;                          // +0x10
    Matrix33 mRotation;                       // +0x14
};

struct cBoundingBox {
    Vector3 mMin;
    Vector3 mMax;
};

struct cGlobalParams {
    float    mParticleDensity;                // +0x00
    float    mParticleScale;                  // +0x04
    int      mParticleMultThreshold;          // +0x08
    float    mMaxParticleSize;                // +0x0c
    int      mMaxParticles;                   // +0x10
    int      mMaxEffects;                     // +0x14
    int      mMaxDistributeSamples;           // +0x18
    Matrix44 mProjectionMatrix;               // +0x1c
};

struct cParticlesDescription {
    void*                 vftable;            // +0x000
    u32                   pad004;
    u32                   mFlags;             // +0x008 (bitset)
    u32                   pad00c[(0x7c - 0x0c) / 4];
    float                 mRateCurveTime;     // +0x07c
    u32                   pad080[2];
    SPVector<float>       mSizeCurve;         // +0x088
    float                 mSizeVary;          // +0x09c
    SPVector<float>       mAspectCurve;       // +0x0a0
    float                 mAspectVary;        // +0x0b4
    SPVector<float>       mRotationCurve;     // +0x0b8
    float                 mRotationVary;      // +0x0cc
    float                 mRotationOffset;    // +0x0d0
    SPVector<Vector3>     mColorCurve;        // +0x0d4
    Vector3               mColorVary;         // +0x0e8
    SPVector<float>       mAlphaCurve;        // +0x0f4
    u32                   pad108[(0x164 - 0x108) / 4];
    float                 mVelocityStretch;   // +0x164
    float                 mScrewRate;         // +0x168
    SPVector<cWiggle>     mWiggles;           // +0x16c
    u8                    mScreenBloomAlphaRate;  // +0x180
    u8                    mScreenBloomAlphaBase;  // +0x181
    u8                    mScreenBloomSizeRate;   // +0x182
    u8                    mScreenBloomSizeBase;   // +0x183
    SPVector<Vector3>     mLoopBoxColorCurve; // +0x184
    SPVector<float>       mLoopBoxAlphaCurve; // +0x198

    enum { kFlagScrewCylindrical = 29, kFlagLoopBox = 30 };
    bool IsSet(int bit) const { return ((mFlags >> bit) & 1) != 0; }
};

class cITextureParticleRenderer {
public:
    virtual int  GetBuffer(int count, u8** buffer, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                        // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                           // slot 2
};

struct cParticlesEffect {
    u32                    pad000[0x18 / 4];  // vtables + cComponentBase
    cParticle*             mParticlesFirst;   // +0x18 intrusive_list anchor.mpNext
    cParticle*             mParticlesLast;    // +0x1c
    int                    mParticleCount;    // +0x20
    cParticlesDescription* mDesc;             // +0x24
    int                    mCollectionIndex;  // +0x28
    void*                  mWorld;            // +0x2c
    cGlobalParams*         mGlobalParams;     // +0x30
    u32                    pad034;
    double                 mOverallTime;      // +0x38
    u32                    pad040[(0xc8 - 0x40) / 4];
    cTransform             mSourceTransform;  // +0xc8
    cTransform             mRigidTransform;   // +0x100
    u32                    pad138[(0x198 - 0x138) / 4];
    float                  mCurrentSizeScale;     // +0x198
    float                  mCurrentAlphaScale;    // +0x19c
    float                  mCurrentMapForceScale; // +0x1a0
    Vector3                mCurrentColorScale;    // +0x1a4
    u32                    pad1b0[(0x1c0 - 0x1b0) / 4];
    cBoundingBox           mEmissionVolume;   // +0x1c0
};

// Fast sin/cos table (runtime initialised): 16 {sin, cos} pairs and its step constants.
struct SinCosEntry { float s, c; };
extern SinCosEntry gSinCosTable[16];          // 0x01677840
extern float       gSinCosInvStep;            // 0x01679468  16 / (2 pi)
extern float       gSinCosStep;               // 0x01679518  2 pi / 16
extern float       gDegToRad;                 // 0x0167952c

void WigglePoint(float time, const SPVector<cWiggle>& wiggles, const Vector3& origin,
                 Vector3& point);             // 0x00a9aff0

}} // namespace EA::Swarm

using namespace EA::Swarm;

namespace {

// Output of StreamerSetup: the camera-facing quad axes and the screen-bloom factors.
struct StreamerInfo {                         // 0x40
    Vector3 mAxis0;                           // +0x00
    Vector3 mAxis1;                           // +0x0c
    float   mBloomAlphaBase;                  // +0x18
    float   mBloomAlphaRate;                  // +0x1c
    float   mBloomSizeBase;                   // +0x20
    float   mBloomSizeRate;                   // +0x24
    u8      mField28;                         // +0x28
    float   mField2c;                         // +0x2c
    float   mField30;                         // +0x30
    u32     mField34;                         // +0x34
    u32     mField38;                         // +0x38
    u32     mField3c;                         // +0x3c
};

void StreamerSetup(cParticlesEffect* effect, cParticlesDescription* desc, StreamerInfo* info);  // 0x00aa9b70

// ---- math helpers -------------------------------------------------------------------

static __forceinline float Min(float a, float b)
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Max(float a, float b)
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Clamp(float v, float lo, float hi)
{
    return Min(Max(lo, v), hi);
}

static __forceinline int FloatToInt(float v)          // cvtss2si (current rounding mode)
{
    return _mm_cvt_ss2si(_mm_set_ss(v));
}

static __forceinline int FloorToInt(float v)
{
    int i = FloatToInt(v);
    if (v < (float)i)
        i = i - 1;
    return i;
}

static __forceinline const float& MaxRef(const float& a, const float& b)
{
    return (a < b) ? b : a;
}

static __forceinline const float& MinRef(const float& a, const float& b)
{
    return (b < a) ? b : a;
}

// Table sin/cos: nearest table angle by the 1.5*2^23 rounding trick, then a 2nd-order
// Taylor correction around it.
static __forceinline void FastSinCos(float angle, float& s, float& c)
{
    float k = angle * gSinCosInvStep + 12582912.0f;
    u32 bits = *(u32*)&k;
    u32 idx = bits & 0xf;
    float r = angle - (float)(int)(bits - 0x4b400000) * gSinCosStep;
    float s0 = gSinCosTable[idx].s;
    float c0 = gSinCosTable[idx].c;
    s = (c0 - s0 * r * 0.5f) * r + s0;
    c = c0 - (c0 * r * 0.5f + s0) * r;
}

// Curve evaluation at t in [0,1]; last = number of keys - 1.
static __forceinline float SampleCurve(const float* curve, unsigned int last, float t)
{
    if (last == 0)
        return curve[0];
    float f = (float)last * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f)
        return (curve[i + 1] - curve[i]) * frac + curve[i];
    return curve[i];
}

static __forceinline Vector3 SampleCurve(const Vector3* curve, unsigned int last, float t)
{
    Vector3 v;
    if (last == 0) {
        v = curve[0];
    } else {
        float f = (float)last * t;
        int i = (int)f;
        float frac = f - (float)i;
        const Vector3& a = curve[i];
        if (frac > 0.0f) {
            const Vector3& b = curve[i + 1];
            v.x = a.x + (b.x - a.x) * frac;
            v.y = a.y + (b.y - a.y) * frac;
            v.z = a.z + (b.z - a.z) * frac;
        } else {
            v = a;
        }
    }
    return v;
}

// Row-vector times a 3x3 rotation.
static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m)
{
    Vector3 r;
    r.x = m.m[2][0] * v.z + m.m[1][0] * v.y + m.m[0][0] * v.x;
    r.y = m.m[2][1] * v.z + m.m[1][1] * v.y + m.m[0][1] * v.x;
    r.z = m.m[2][2] * v.z + m.m[1][2] * v.y + m.m[0][2] * v.x;
    return r;
}

static __forceinline u8 ColorToByte(float v)
{
    return (u8)FloatToInt(Min(Max(0.0f, v) * 255.0f, 255.0f));
}

// Wraps a particle into the effect's emission volume (dev: `anonymous namespace'::ApplyLoopBox,
// inlined here) and modulates its colour/alpha by the loop-box curves.
static __forceinline void ApplyLoopBox(cParticlesEffect* effect, cParticlesDescription* desc,
                                       Vector3& pos, Vector3& color, float& alpha)
{
    const Vector3& origin = effect->mSourceTransform.mTranslation;
    const cBoundingBox& box = effect->mEmissionVolume;

    Vector3 rel;
    rel.x = (pos.x - origin.x) - box.mMin.x;
    rel.y = (pos.y - origin.y) - box.mMin.y;
    rel.z = (pos.z - origin.z) - box.mMin.z;

    Vector3 u;
    u.x = rel.x / (box.mMax.x - box.mMin.x);
    u.y = rel.y / (box.mMax.y - box.mMin.y);
    u.z = rel.z / (box.mMax.z - box.mMin.z);

    Vector3 frac;
    frac.x = u.x - (float)FloorToInt(u.x);
    frac.y = u.y - (float)FloorToInt(u.y);
    frac.z = u.z - (float)FloorToInt(u.z);

    const Matrix33& rot = effect->mSourceTransform.mRotation;
    float t = rot.m[1][2] * (frac.z - 0.5f) + rot.m[1][1] * (frac.y - 0.5f)
            + rot.m[1][0] * (frac.x - 0.5f) + 0.5f;
    t = Clamp(t, 0.0f, 1.0f);

    if (!desc->mLoopBoxColorCurve.empty()) {
        Vector3 c = SampleCurve(desc->mLoopBoxColorCurve.mpBegin,
                                desc->mLoopBoxColorCurve.size() - 1, t);
        color.x = c.x * color.x;
        color.y = c.y * color.y;
        color.z = c.z * color.z;
    }
    if (!desc->mLoopBoxAlphaCurve.empty())
        alpha = SampleCurve(desc->mLoopBoxAlphaCurve.mpBegin,
                            desc->mLoopBoxAlphaCurve.size() - 1, t) * alpha;

    pos.x = (box.mMax.x - box.mMin.x) * frac.x + box.mMin.x + origin.x;
    pos.y = (box.mMax.y - box.mMin.y) * frac.y + box.mMin.y + origin.y;
    pos.z = (box.mMax.z - box.mMin.z) * frac.z + box.mMin.z + origin.z;
}

// Curve key counts (minus one) of the description, hoisted out of the particle loop.
struct CurveLimits {
    unsigned int color;
    unsigned int alpha;
    unsigned int size;
    unsigned int aspect;
    unsigned int rotation;
};

// Everything a quad needs: centre + age fraction, the oriented half-axis, size and colour.
struct QuadParticle {
    Vector3 pos;
    float   t;
    Vector3 axis;
    float   size;
    u32     color;
};

static __forceinline void ComputeQuadParticle(cParticlesEffect* effect, cParticlesDescription* desc,
                                              const StreamerInfo& info, const CurveLimits& lim,
                                              const cParticle* particle, QuadParticle& q)
{
    const float t = particle->mAge / particle->mLife;

    float aspect = SampleCurve(desc->mAspectCurve.mpBegin, lim.aspect, t);   // unused by quads
    (void)aspect;

    float size = particle->mOverallSize * effect->mCurrentSizeScale
               * SampleCurve(desc->mSizeCurve.mpBegin, lim.size, t);
    float rotation = particle->mOverallRotation * SampleCurve(desc->mRotationCurve.mpBegin, lim.rotation, t)
                   + desc->mRotationOffset;

    Vector3 c = SampleCurve(desc->mColorCurve.mpBegin, lim.color, t);
    Vector3 color;
    color.x = effect->mCurrentColorScale.x * (c.x * particle->mOverallColor.x);
    color.y = effect->mCurrentColorScale.y * (particle->mOverallColor.y * c.y);
    color.z = effect->mCurrentColorScale.z * (particle->mOverallColor.z * c.z);

    float alpha = particle->mOverallAlpha * SampleCurve(desc->mAlphaCurve.mpBegin, lim.alpha, t)
                * effect->mCurrentAlphaScale;

    Vector3 pos = particle->mPosition;

    // Screw: spin the particle about the effect's vertical axis.
    const float screwRate = desc->mScrewRate;
    if (screwRate != 0.0f) {
        const Vector3& origin = effect->mSourceTransform.mTranslation;
        float dx = pos.x - origin.x;
        float dy = pos.y - origin.y;
        float dz = pos.z - origin.z;
        float s, cs;
        if (desc->IsSet(cParticlesDescription::kFlagScrewCylindrical)) {
            float angle = sqrtf(dx * dx + dy * dy) * screwRate;
            FastSinCos(angle, s, cs);
        } else {
            FastSinCos(screwRate * dz, s, cs);
        }
        pos.x = dx * cs - dy * s + origin.x;
        pos.y = dx * s + dy * cs + origin.y;
    }

    if (desc->mWiggles.mpBegin != desc->mWiggles.mpEnd)
        WigglePoint((float)(desc->mRateCurveTime * effect->mOverallTime), desc->mWiggles,
                    effect->mSourceTransform.mTranslation, pos);

    if (desc->IsSet(cParticlesDescription::kFlagLoopBox))
        ApplyLoopBox(effect, desc, pos, color, alpha);

    // Rigid transform (rotation only when flagged, then scale + translation).
    const cTransform& rigid = effect->mRigidTransform;
    if (rigid.mFlags & 2)
        pos = Rotate(pos, rigid.mRotation);
    const float scale = rigid.mScale;
    pos.x = rigid.mTranslation.x + pos.x * scale;
    pos.y = rigid.mTranslation.y + pos.y * scale;
    pos.z = rigid.mTranslation.z + pos.z * scale;
    size = scale * size;

    // Screen bloom: fade/shrink particles toward the screen edges.
    if (desc->mScreenBloomAlphaRate || desc->mScreenBloomSizeRate) {
        const Matrix44& m = effect->mGlobalParams->mProjectionMatrix;
        float sx = m.m[2][0] * pos.z + m.m[1][0] * pos.y + m.m[0][0] * pos.x + m.m[3][0];
        float sy = m.m[2][1] * pos.z + m.m[1][1] * pos.y + m.m[0][1] * pos.x + m.m[3][1];
        float sw = m.m[2][3] * pos.z + m.m[1][3] * pos.y + m.m[0][3] * pos.x + m.m[3][3];
        float invW = 1.0f / sw;
        float ay = fabsf(invW * sy);
        float ax = fabsf(invW * sx);
        float d = 1.0f - MaxRef(ax, ay);
        float sizeFactor;
        if (d > 0.0f) {
            float one = 1.0f;
            float a = info.mBloomAlphaRate * d + info.mBloomAlphaBase;
            alpha = alpha * MinRef(a, one);
            float one2 = 1.0f;
            float b = info.mBloomSizeRate * d + info.mBloomSizeBase;
            sizeFactor = MinRef(b, one2);
        } else {
            alpha = info.mBloomAlphaBase * alpha;
            sizeFactor = info.mBloomSizeBase;
        }
        size = sizeFactor * size;
    }

    u8 r = ColorToByte(color.x);
    u8 g = ColorToByte(color.y);
    u8 b = ColorToByte(color.z);
    u8 a = ColorToByte(alpha);
    q.color = ((((u32)a << 8 | r) << 8 | g) << 8) | b;

    // Quad axes: camera-facing by default, aligned with the velocity when stretched.
    Vector3 axis0 = info.mAxis0;
    Vector3 axis1 = info.mAxis1;
    if (desc->mVelocityStretch != 0.0f) {
        Vector3 vel = particle->mVelocity;
        if (rigid.mFlags & 2)
            vel = Rotate(vel, rigid.mRotation);
        float v1 = vel.x * info.mAxis1.x + vel.z * info.mAxis1.z + vel.y * info.mAxis1.y;
        float v0 = vel.x * info.mAxis0.x + vel.z * info.mAxis0.z + vel.y * info.mAxis0.y;
        float len = sqrtf(v0 * v0 + v1 * v1);
        if (len > 1e-6f) {
            float inv = 1.0f / len;
            float cs = inv * v0;
            float sn = inv * v1;
            axis1.x = info.mAxis1.x * sn + info.mAxis0.x * cs;
            axis1.y = info.mAxis1.y * sn + info.mAxis0.y * cs;
            axis1.z = info.mAxis1.z * sn + info.mAxis0.z * cs;
            axis0.x = info.mAxis0.x * sn - info.mAxis1.x * cs;
            axis0.y = info.mAxis0.y * sn - info.mAxis1.y * cs;
            axis0.z = info.mAxis0.z * sn - info.mAxis1.z * cs;
            if (len > desc->mVelocityStretch) {
                float stretch = len / desc->mVelocityStretch;
                axis1.x = axis1.x * stretch;
                axis1.y = stretch * axis1.y;
                axis1.z = stretch * axis1.z;
            }
        }
    }

    // Particle spin.
    if (fabsf(rotation) > 1e-6f) {
        float s, cs;
        FastSinCos(gDegToRad * rotation, s, cs);
        axis1.x = axis1.x * cs - axis0.x * s;
        axis1.y = cs * axis1.y - s * axis0.y;
        axis1.z = cs * axis1.z - s * axis0.z;
    }

    q.pos = pos;
    q.t = t;
    q.axis = axis1;
    q.size = size;
}

static __forceinline void InitCurveLimits(const cParticlesDescription* desc, CurveLimits& lim)
{
    lim.color    = desc->mColorCurve.size() - 1;
    lim.alpha    = desc->mAlphaCurve.size() - 1;
    lim.aspect   = desc->mAspectCurve.size() - 1;
    lim.size     = desc->mSizeCurve.size() - 1;
    lim.rotation = desc->mRotationCurve.size() - 1;
}

struct V4F { float x, y, z, w; };
struct T2F { float u, v; };

// @ 0x00aabc20
void Stream_Quad_V4F_N4F_C4B_T2F(cParticlesEffect* effect, cITextureParticleRenderer* renderer,
                                 u8* offsets)
{
    cParticlesDescription* desc = effect->mDesc;
    StreamerInfo info;
    StreamerSetup(effect, desc, &info);

    cParticle* particle = effect->mParticlesFirst;
    CurveLimits lim;
    InitCurveLimits(desc, lim);

    int remaining = effect->mParticleCount;
    while (remaining > 0) {
        u8* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        remaining -= count;

        for (; count > 0; count--) {
            QuadParticle q;
            ComputeQuadParticle(effect, desc, info, lim, particle, q);

            // V4F: centre + age fraction
            u8* p = buffer + offsets[0];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)p;
                v.x = q.pos.x;
                v.y = q.pos.y;
                v.z = q.pos.z;
                v.w = q.t;
                p += stride;
            }
            // N4F: half-axis * size, size
            p = buffer + offsets[1];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)p;
                v.x = q.axis.x * q.size;
                v.y = q.axis.y * q.size;
                v.z = q.axis.z * q.size;
                v.w = q.size;
                p += stride;
            }
            // C4B
            p = buffer + offsets[2];
            for (int i = 0; i < 4; i++) {
                *(u32*)p = q.color;
                p += stride;
            }
            // T2F
            p = buffer + offsets[3];
            ((T2F*)p)->u = 0.0f; ((T2F*)p)->v = 0.0f; p += stride;
            ((T2F*)p)->u = 1.0f; ((T2F*)p)->v = 0.0f; p += stride;
            ((T2F*)p)->u = 1.0f; ((T2F*)p)->v = 1.0f; p += stride;
            ((T2F*)p)->u = 0.0f; ((T2F*)p)->v = 1.0f;

            buffer += stride * 4;
            particle = particle->mpNext;
        }
        renderer->ReleaseAndDrawBuffer();
    }
}

// @ 0x00aad240
void Stream_Quad_V4F_N4F_C4B_T4B(cParticlesEffect* effect, cITextureParticleRenderer* renderer,
                                 u8* offsets)
{
    cParticlesDescription* desc = effect->mDesc;
    StreamerInfo info;
    StreamerSetup(effect, desc, &info);

    cParticle* particle = effect->mParticlesFirst;
    CurveLimits lim;
    InitCurveLimits(desc, lim);

    int remaining = effect->mParticleCount;
    while (remaining > 0) {
        u8* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        remaining -= count;

        for (; count > 0; count--) {
            QuadParticle q;
            ComputeQuadParticle(effect, desc, info, lim, particle, q);

            // T4B: (frame, u, v, 0) bytes; corners (0,0) (1,0) (1,1) (0,1).
            const u32 frame = (u32)particle->mFrame << 24;
            const u32 corner[4] = { frame, frame | 0xff0000, frame | 0xffff00, frame | 0xff00 };

            u8* pPos   = buffer + offsets[0];
            u8* pAxis  = buffer + offsets[1];
            u8* pColor = buffer + offsets[2];
            u8* pTex   = buffer + offsets[3];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)pPos;
                v.x = q.pos.x;
                v.y = q.pos.y;
                v.z = q.pos.z;
                v.w = q.t;
                pPos += stride;

                V4F& n = *(V4F*)pAxis;
                n.x = q.axis.x * q.size;
                n.y = q.axis.y * q.size;
                n.z = q.axis.z * q.size;
                n.w = q.size;
                pAxis += stride;

                *(u32*)pColor = q.color;
                pColor += stride;

                *(u32*)pTex = corner[i];
                pTex += stride;
            }

            buffer += stride * 4;
            particle = particle->mpNext;
        }
        renderer->ReleaseAndDrawBuffer();
    }
}

} // anonymous namespace

// The streamers are reached through the sStreamers table (SetParticlesStreamer); keep them
// referenced so the anonymous-namespace definitions are emitted.
typedef void (*ParticleStreamerFn)(cParticlesEffect*, cITextureParticleRenderer*, u8*);
ParticleStreamerFn gParticleQuadStreamers[2] = {
    &Stream_Quad_V4F_N4F_C4B_T2F,
    &Stream_Quad_V4F_N4F_C4B_T4B,
};
