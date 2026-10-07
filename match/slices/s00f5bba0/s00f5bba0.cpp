// Slice s00f5bba0 - 0x00f5bba0 (4422 B)
// EA::Swarm texture-particle quad streamer, older cParticlesEffect.obj layout (retail copy next to
// the loop-box helper 0x00f58ed0). Same algorithm as the sibling in slice s00aabc20
// (Stream_Quad_V4F_N4F_C4B_T2F @ 0x00aabc20), with different struct offsets and the loop box
// moved out of line (0x00f58ed0). The first sample of the aspect curve is dead code in the original
// (result discarded) and is omitted. Writes V4F (pos, age fraction), N4F (axis*size, size),
// C4B (ARGB packed), T2F (unit square) for each of 4 corners.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE

#include <math.h>
#include <xmmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

namespace EA { namespace Swarm {

struct Vector3 { float x, y, z; };
struct Matrix33 { float m[3][3]; };
struct Matrix44 { float m[4][4]; };

template <typename T>
struct SPVector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];
    int  size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct cWiggle { float mTimeRate; Vector3 mRateDir; Vector3 mWiggleDir; };

struct cParticle {                            // 0x48
    cParticle* mpNext;                        // +0x00
    cParticle* mpPrev;                        // +0x04
    float      mAge;                          // +0x08
    float      mLife;                         // +0x0c
    Vector3    mPosition;                     // +0x10
    Vector3    mVelocity;                     // +0x1c
    float      mOverallSize;                  // +0x28
    float      mOverallAspect;                // +0x2c
    float      mOverallRotation;              // +0x30
    float      mOverallAlpha;                 // +0x34
    Vector3    mOverallColor;                 // +0x38
    u8         mFrame;                        // +0x44
    u8         mUnused[3];
};

struct cTransform {                           // 0x38
    u16      mFlags;
    u16      mModificationCount;
    Vector3  mTranslation;                    // +0x04
    float    mScale;                          // +0x10
    Matrix33 mRotation;                       // +0x14
};

struct cGlobalParams {
    u32      pad[0x1c / 4];
    Matrix44 mProjectionMatrix;               // +0x1c
};

struct cParticlesDescription {
    void*                 vftable;            // +0x000
    u32                   pad004;
    u32                   mFlags;             // +0x008
    u32                   pad00c[(0x78 - 0x0c) / 4];
    float                 mRateCurveTime;     // +0x078
    u32                   pad07c[(0x84 - 0x7c) / 4];
    SPVector<float>       mSizeCurve;         // +0x084
    float                 mSizeVary;          // +0x098
    SPVector<float>       mAspectCurve;       // +0x09c
    float                 mAspectVary;        // +0x0b0
    SPVector<float>       mRotationCurve;     // +0x0b4
    float                 mRotationVary;      // +0x0c8
    float                 mRotationOffset;    // +0x0cc
    SPVector<Vector3>     mColorCurve;        // +0x0d0
    Vector3               mColorVary;         // +0x0e4
    SPVector<float>       mAlphaCurve;        // +0x0f0
    u32                   pad104[(0x15c - 0x104) / 4];
    float                 mVelocityStretch;   // +0x15c
    float                 mScrewRate;         // +0x160
    SPVector<cWiggle>     mWiggles;           // +0x164
    u8                    mScreenBloomAlphaRate;  // +0x178
    u8                    mScreenBloomAlphaBase;  // +0x179
    u8                    mScreenBloomSizeRate;   // +0x17a
    u8                    mScreenBloomSizeBase;   // +0x17b

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
    u32                    pad000[0x18 / 4];
    cParticle*             mParticlesFirst;   // +0x18
    cParticle*             mParticlesLast;    // +0x1c
    int                    mParticleCount;    // +0x20
    cParticlesDescription* mDesc;             // +0x24
    u32                    pad028[(0x34 - 0x28) / 4];
    cGlobalParams*         mGlobalParams;     // +0x34
    u32                    pad038[2];
    double                 mOverallTime;      // +0x40
    u32                    pad048[(0xd0 - 0x48) / 4];
    cTransform             mSourceTransform;  // +0xd0
    cTransform             mRigidTransform;   // +0x108
    u32                    pad140[(0x19c - 0x140) / 4];
    float                  mCurrentSizeScale;     // +0x19c
    float                  mCurrentAlphaScale;    // +0x1a0
    float                  mCurrentMapForceScale; // +0x1a4
    Vector3                mCurrentColorScale;    // +0x1a8
};

struct SinCosEntry { float s, c; };
extern SinCosEntry gSinCosTable[16];          // 0x01677840
extern float       gSinCosInvStep;            // 0x016c940c
extern float       gSinCosStep;               // 0x016c9408
extern float       gDegToRad;                 // 0x016c949c

void WigglePoint(float time, const SPVector<cWiggle>& wiggles, const Vector3& origin,
                 Vector3& point);             // 0x00a9aff0

}} // namespace EA::Swarm

using namespace EA::Swarm;

// Declared outside the anonymous namespace so the checker can map it by its annotation.
void ApplyLoopBox(cParticlesEffect* effect, cParticlesDescription* desc, Vector3* pos,
                  Vector3* color, float* alpha);                                                 // 0x00f58ed0

namespace {

struct StreamerInfo {                         // 0x48
    Vector3 mAxis0;                           // +0x00
    Vector3 mAxis1;                           // +0x0c
    float   mBloomAlphaBase;                  // +0x18
    float   mBloomAlphaRate;                  // +0x1c
    float   mBloomSizeBase;                   // +0x20
    float   mBloomSizeRate;                   // +0x24
    u32     mPad28[6];                        // +0x28
    u8      mBloomInverted;                   // +0x40
    u8      mPad41[7];
};

void StreamerSetup(cParticlesEffect* effect, cParticlesDescription* desc, StreamerInfo* info);  // 0x00f5a200

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


struct CurveLimits {
    unsigned int color;
    unsigned int alpha;
    unsigned int size;
    unsigned int rotation;
};

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

    float size = particle->mOverallSize * effect->mCurrentSizeScale
               * SampleCurve(desc->mSizeCurve.mpBegin, lim.size, t);
    float rotation = particle->mOverallRotation * SampleCurve(desc->mRotationCurve.mpBegin, lim.rotation, t)
                   + desc->mRotationOffset;

    Vector3 c = SampleCurve(desc->mColorCurve.mpBegin, lim.color, t);
    Vector3 color;
    color.x = particle->mOverallColor.x * c.x * effect->mCurrentColorScale.x;
    color.y = particle->mOverallColor.y * c.y * effect->mCurrentColorScale.y;
    color.z = particle->mOverallColor.z * c.z * effect->mCurrentColorScale.z;

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
            FastSinCos(dz * screwRate, s, cs);
        }
        pos.x = dx * cs - dy * s + origin.x;
        pos.y = dy * cs + dx * s + origin.y;
    }

    if (desc->mWiggles.mpBegin != desc->mWiggles.mpEnd)
        WigglePoint((float)(desc->mRateCurveTime * effect->mOverallTime), desc->mWiggles,
                    effect->mSourceTransform.mTranslation, pos);

    if (desc->IsSet(cParticlesDescription::kFlagLoopBox))
        ApplyLoopBox(effect, desc, &pos, &color, &alpha);

    // Rigid transform (rotation only when flagged, then scale + translation).
    const cTransform& rigid = effect->mRigidTransform;
    if (rigid.mFlags & 2)
        pos = Rotate(pos, rigid.mRotation);
    const float scale = rigid.mScale;
    pos.x = rigid.mTranslation.x + pos.x * scale;
    pos.y = rigid.mTranslation.y + pos.y * scale;
    pos.z = rigid.mTranslation.z + pos.z * scale;
    size = size * scale;

    // Screen bloom: fade/shrink particles toward the screen edges.
    if (desc->mScreenBloomAlphaRate || desc->mScreenBloomSizeRate) {
        const Matrix44& m = effect->mGlobalParams->mProjectionMatrix;
        float sw = m.m[2][3] * pos.z + m.m[1][3] * pos.y + m.m[0][3] * pos.x + m.m[3][3];
        float invW = 1.0f / sw;
        float sy = m.m[2][0] * pos.z + m.m[1][0] * pos.y + m.m[0][0] * pos.x + m.m[3][0];
        float sx = m.m[2][1] * pos.z + m.m[1][1] * pos.y + m.m[0][1] * pos.x + m.m[3][1];
        sy = invW * sy;
        sx = invW * sx;
        float ay = fabsf(sy);
        float ax = fabsf(sx);
        float d = 1.0f - MaxRef(ay, ax);
        float sizeFactor;
        if (d > 0.0f) {
            float one = 1.0f;
            float a;
            if (info.mBloomInverted == 0)
                a = info.mBloomAlphaRate * d + info.mBloomAlphaBase;
            else
                a = (1.0f - d) * info.mBloomAlphaRate + info.mBloomAlphaBase;
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
        float v1 = vel.x * info.mAxis1.x + (vel.z * info.mAxis1.z + vel.y * info.mAxis1.y);
        float v0 = vel.x * info.mAxis0.x + (vel.y * info.mAxis0.y + vel.z * info.mAxis0.z);
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
                axis1.y = axis1.y * stretch;
                axis1.z = axis1.z * stretch;
            }
        }
    }

    // Particle spin.
    if (fabsf(rotation) > 1e-6f) {
        float s, cs;
        FastSinCos(gDegToRad * rotation, s, cs);
        axis1.x = axis1.x * cs - axis0.x * s;
        axis1.y = axis1.y * cs - axis0.y * s;
        axis1.z = axis1.z * cs - axis0.z * s;
    }

    q.pos = pos;
    q.t = t;
    q.axis = axis1;
    q.size = size;
}

struct V4F { float x, y, z, w; };
struct T2F { float u, v; };

// @ 0x00f5bba0
void Stream_Quad_V4F_N4F_C4B_T2F_Old(cParticlesEffect* effect, cITextureParticleRenderer* renderer,
                                     u8* offsets)
{
    cParticlesDescription* desc = effect->mDesc;
    StreamerInfo info;
    StreamerSetup(effect, desc, &info);

    cParticle* particle = effect->mParticlesFirst;
    CurveLimits lim;
    lim.color    = desc->mColorCurve.size() - 1;
    lim.alpha    = desc->mAlphaCurve.size() - 1;
    lim.size     = desc->mSizeCurve.size() - 1;
    lim.rotation = desc->mRotationCurve.size() - 1;

    int remaining = effect->mParticleCount;
    while (remaining > 0) {
        u8* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        remaining -= count;

        for (; count > 0; count--) {
            QuadParticle q;
            ComputeQuadParticle(effect, desc, info, lim, particle, q);

            u8* p = buffer + offsets[0];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)p;
                v.x = q.pos.x;
                v.y = q.pos.y;
                v.z = q.pos.z;
                v.w = q.t;
                p += stride;
            }
            p = buffer + offsets[1];
            for (int i = 0; i < 4; i++) {
                V4F& v = *(V4F*)p;
                v.x = q.axis.x * q.size;
                v.y = q.axis.y * q.size;
                v.z = q.axis.z * q.size;
                v.w = q.size;
                p += stride;
            }
            p = buffer + offsets[2];
            for (int i = 0; i < 4; i++) {
                *(u32*)p = q.color;
                p += stride;
            }
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

} // namespace
