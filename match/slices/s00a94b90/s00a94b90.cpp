// Slice s00a94b90: EA::Swarm particle-trail routines.
//
//   0x00a94b90  cEffectSpawner::ResetParticle(cParticle*)  -- re-randomise a recycled particle
//               (life from the descriptor's life range, random start position, random velocity
//               normalised to the speed range, optional attractor kick, then the transform).
//   0x00a94fb0  StreamTrail(effect, renderer, offsets)     -- one vertex per particle:
//               position / ARGB colour / width, sampled from the descriptor's three curves.
//
// Layouts (retail offsets, shared with the sibling slices s00a954b0 / s00a95d30 / s00a96cb0):
//   cParticle            +0x00 next, +0x04 prev, +0x08 age, +0x0c life,
//                        +0x10/+0x14/+0x18 position, +0x1c/+0x20/+0x24 velocity,
//                        +0x28 u16 stream index, +0x2a u16 flags
//   cSPTransform (0x38)  +0x00 u8 flags, +0x01 u8 flagsHi, +0x02 u16 modCount,
//                        +0x04 translation, +0x10 scale, +0x14 rotation (3x3, row-major float[3][3])
//   descriptor           +0x80 size curve (float), +0x94 colour curve (Vector3), +0xa8 alpha curve
//   effect               +0x14 first particle, +0x18 last, +0x1c live count, +0x20 descriptor,
//                        +0xcc transform, +0x150 size scale, +0x154 alpha scale, +0x158 colour scale
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE; the double-precision random range
// blocks keep x87, exactly as in s00a96cb0).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vector3 {
    float x, y, z;
};

struct Matrix33 {
    float m[3][3];
};

// eastl::vector<T> as laid out in this build (20 bytes).
template <class T>
struct sp_vector {
    T* mpBegin;      // +0x00
    T* mpEnd;        // +0x04
    T* mpCapacity;   // +0x08
    int mAllocator;  // +0x0c
    int mPad;        // +0x10
    int size() const { return (int)(mpEnd - mpBegin); }
};

// ------------------------------------------------------------------ particles
struct cParticle {
    cParticle* mpNext;     // +0x00
    cParticle* mpPrev;     // +0x04
    float mAge;            // +0x08
    float mLife;           // +0x0c
    Vector3 mPosition;     // +0x10
    Vector3 mVelocity;     // +0x1c
    u16 mStreamIndex;      // +0x28
    u16 mFlags;            // +0x2a
};

struct cSPTransform {          // 0x38 bytes
    u8 mFlags;                 // +0x00
    u8 mFlagsHi;               // +0x01
    u16 mModCount;             // +0x02
    Vector3 mTranslation;      // +0x04
    float mScale;              // +0x10
    Matrix33 mRotation;        // +0x14
};

struct cCurves {               // the descriptor part both writers sample
    char pad00[0x80];
    sp_vector<float> mSizeCurve;      // +0x80
    sp_vector<Vector3> mColorCurve;   // +0x94
    sp_vector<float> mAlphaCurve;     // +0xa8
};

struct cVectorRange {
    Vector3 mMin;   // +0x00
    Vector3 mMax;   // +0x0c
};

// ------------------------------------------------------------------ callees
struct cRandomGlobal {
    double RandomDouble();                   // 0x009360d0
};
extern cRandomGlobal gRandomGlobal;          // 0x016778dc

Vector3 RandomVector3(const cVectorRange* range);   // 0x007cdbe0 (struct return by value)

static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m);

// ================================================================================
// 0x00a94b90 -- randomise a recycled particle for the effect that owns the list.
// ================================================================================
struct cEffectSpawner;

struct cSpawnerDesc {
    char pad00[0x0c];
    float mLifeMin;          // +0x0c
    float mLifeMax;          // +0x10
    char pad14[0x14];
    cVectorRange mVelocityRange;   // +0x28
    float mSpeedMin;         // +0x40
    float mSpeedMax;         // +0x44
    char pad48[0xb0];
    float mAttractRadius;    // +0xf8
    Vector3 mAttractCenter;  // +0xfc
};

struct cEffectSpawner {
    char pad00[0x14];
    cParticle* mpParticlesFirst;   // +0x14
    char pad18[0x04];
    int mParticleCount;            // +0x1c
    cSpawnerDesc* mpDesc;          // +0x20
    char pad24[0x70];
    cSPTransform mTransform;       // +0x94
    char padCC[0x60];
    float mSpeedScale;             // +0x12c
    char pad130[0x04];
    float mLifeScale;              // +0x134
    char pad138[0x2c];
    cVectorRange mSpawnRange;      // +0x164
    u16 mStreamCounter;            // +0x17c

    void ResetParticle(cParticle* particle);
};

// @ 0x00a94b90
void cEffectSpawner::ResetParticle(cParticle* particle)
{
    particle->mAge = 0.0f;

    cSpawnerDesc* desc = mpDesc;
    double lo = desc->mLifeMin;
    double hi = desc->mLifeMax;
    double r = gRandomGlobal.RandomDouble();
    double v = r * (hi - lo) + lo;
    if (v < hi) {
        if (v < lo)
            v = lo;
    } else {
        v = hi;
    }
    particle->mLife = v * mLifeScale;

    particle->mPosition = RandomVector3(&mSpawnRange);
    particle->mVelocity = RandomVector3(&desc->mVelocityRange);

    double slo = desc->mSpeedMin;
    double shi = desc->mSpeedMax;
    r = gRandomGlobal.RandomDouble();
    double speed = r * (shi - slo) + slo;
    if (speed < shi) {
        if (speed < slo)
            speed = slo;
    } else {
        speed = shi;
    }

    Vector3 dir = particle->mVelocity;
    float len2 = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (len2 > 0.0f) {
        double k = speed * mSpeedScale / sqrt((double)len2);
        particle->mVelocity.x = (float)(dir.x * k);
        particle->mVelocity.y = (float)(dir.y * k);
        particle->mVelocity.z = (float)(dir.z * k);
    }

    cSpawnerDesc* attract = mpDesc;
    if (attract->mAttractRadius != 0.0f) {
        Vector3 delta;
        delta.x = particle->mPosition.x - attract->mAttractCenter.x;
        delta.y = particle->mPosition.y - attract->mAttractCenter.y;
        delta.z = particle->mPosition.z - attract->mAttractCenter.z;
        float dist2 = delta.z * delta.z + delta.y * delta.y + delta.x * delta.x;
        if (dist2 > 0.0f) {
            float k = (float)(attract->mAttractRadius / sqrt((double)dist2));
            Vector3 kick;
            kick.x = delta.x * k;
            kick.y = delta.y * k;
            kick.z = delta.z * k;
            particle->mVelocity.x = particle->mVelocity.x + kick.x;
            particle->mVelocity.y = particle->mVelocity.y + kick.y;
            particle->mVelocity.z = particle->mVelocity.z + kick.z;
        }
    }

    if (mTransform.mFlags & 2)
        particle->mPosition = Rotate(particle->mPosition, mTransform.mRotation);

    const float scale = mTransform.mScale;
    particle->mPosition.x = particle->mPosition.x * scale + mTransform.mTranslation.x;
    particle->mPosition.y = particle->mPosition.y * scale + mTransform.mTranslation.y;
    particle->mPosition.z = particle->mPosition.z * scale + mTransform.mTranslation.z;

    if (mTransform.mFlags & 2)
        particle->mVelocity = Rotate(particle->mVelocity, mTransform.mRotation);

    particle->mStreamIndex = mStreamCounter++;
    particle->mFlags = 0;
}

// ================================================================================
// 0x00a94fb0 -- stream the live particles as one vertex each.
//   offsets[0] = position (Vector3), offsets[1] = packed ARGB colour,
//   offsets[2] = width (float).
// ================================================================================
struct cITextureParticleRenderer {
    virtual int GetBuffer(int want, char** base, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                      // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                         // slot 2
};

struct cParticlesEffect {
    char pad00[0x14];
    cParticle* mpParticlesFirst;   // +0x14
    cParticle* mpParticlesLast;    // +0x18
    int mParticleCount;            // +0x1c
    cCurves* mpDesc;               // +0x20
    char pad24[0xcc - 0x24];
    cSPTransform mTransform;       // +0xcc
    char pad104[0x150 - 0x104];
    float mSizeScale;              // +0x150
    float mAlphaScale;             // +0x154
    Vector3 mColorScale;           // +0x158
};

static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m)
{
    Vector3 r;
    r.x = m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[0][0] * v.x;
    r.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
    r.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;
    return r;
}

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
    if (last == 0)
        return curve[0];
    float f = (float)last * t;
    int i = (int)f;
    float frac = f - (float)i;
    const Vector3& a = curve[i];
    if (frac > 0.0f) {
        const Vector3& b = curve[i + 1];
        Vector3 r;
        r.x = a.x + (b.x - a.x) * frac;
        r.y = a.y + (b.y - a.y) * frac;
        r.z = a.z + (b.z - a.z) * frac;
        return r;
    }
    return a;
}

static const float k255 = 255.0f;

static __forceinline u32 ToByte(float x)
{
    __m128 v = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&x));
    v = _mm_mul_ss(v, _mm_load_ss(&k255));
    v = _mm_min_ss(v, _mm_load_ss(&k255));
    return (u8)_mm_cvtss_si32(v);
}

// @ 0x00a94fb0
void __cdecl StreamTrail(cParticlesEffect* effect, cITextureParticleRenderer* renderer,
                         const u8* offsets)
{
    cCurves* desc = effect->mpDesc;
    cParticle* particle = effect->mpParticlesFirst;
    int remaining = effect->mParticleCount;
    unsigned int lastColor = desc->mColorCurve.size() - 1;
    unsigned int lastAlpha = desc->mAlphaCurve.size() - 1;
    unsigned int lastSize = desc->mSizeCurve.size() - 1;

    while (remaining > 0) {
        char* buffer;
        int stride;
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        if (count == 0)
            return;
        remaining -= count;
        if (count > 0) {
            do {
                float t = particle->mAge / particle->mLife;
                float width = effect->mSizeScale * SampleCurve(desc->mSizeCurve.mpBegin, lastSize, t);
                Vector3 colour = SampleCurve(desc->mColorCurve.mpBegin, lastColor, t);
                Vector3 c;
                c.x = effect->mColorScale.x * colour.x;
                c.y = colour.y * effect->mColorScale.y;
                c.z = colour.z * effect->mColorScale.z;
                float alpha = effect->mAlphaScale * SampleCurve(desc->mAlphaCurve.mpBegin, lastAlpha, t);

                Vector3 pos = particle->mPosition;
                if (effect->mTransform.mFlags & 2)
                    pos = Rotate(pos, effect->mTransform.mRotation);
                const float scale = effect->mTransform.mScale;
                pos.x = effect->mTransform.mTranslation.x + pos.x * scale;
                pos.y = effect->mTransform.mTranslation.y + pos.y * scale;
                pos.z = effect->mTransform.mTranslation.z + pos.z * scale;

                u32 r = ToByte(c.x);
                u32 g = ToByte(c.y);
                u32 b = ToByte(c.z);
                u32 a = ToByte(alpha);
                u32 packed = (((a << 8) | r) << 8 | g) << 8 | b;

                *(Vector3*)(buffer + offsets[0]) = pos;
                *(u32*)(buffer + offsets[1]) = packed;
                *(float*)(buffer + offsets[2]) = effect->mTransform.mScale * width;

                buffer += stride;
                particle = particle->mpNext;
            } while (--count);
        }
        renderer->ReleaseAndDrawBuffer();
    }
}
