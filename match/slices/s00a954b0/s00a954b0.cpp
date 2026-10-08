// Slice s00a954b0: EA::Swarm particle quad streamer (0x00a954b0, 2161 bytes), V4F / N4F / C4B / T2F
// vertex layout, one quad (4 vertices) per particle. Same family as 0x00f78a60.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include <xmmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Vector4 { float x, y, z, w; };
struct Matrix33 { float m[3][3]; };

template <typename T>
struct SPVector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cParticle {
    cParticle* mpNext;      // +0x00
    cParticle* mpPrev;      // +0x04
    float      mAge;        // +0x08
    float      mLife;       // +0x0c
    Vector3    mPosition;   // +0x10
    Vector3    mVelocity;   // +0x1c
};

struct cParticlesDescription {
    char              pad[0x80];
    SPVector<float>   mSizeCurve;     // +0x80
    SPVector<Vector3> mColorCurve;    // +0x94
    SPVector<float>   mAlphaCurve;    // +0xa8
};

struct cTransform {                   // at effect + 0xcc
    u8        mFlags;                 // +0x00
    u8        mFlagsHi;               // +0x01
    u16       mModificationCount;     // +0x02
    Vector3   mTranslation;           // +0x04
    float     mScale;                 // +0x10
    Matrix33  mRotation;              // +0x14
};

struct cParticlesEffect {
    char                   pad0[0x14];
    cParticle*             mParticlesFirst;    // +0x14
    cParticle*             mParticlesLast;     // +0x18
    int                    mParticleCount;     // +0x1c
    cParticlesDescription* mDesc;              // +0x20
    char                   pad1[0xcc - 0x24];
    cTransform             mTransform;         // +0xcc
    char                   pad2[0x150 - 0x104];
    float                  mSizeScale;         // +0x150
    float                  mAlphaScale;        // +0x154
    Vector3                mColorScale;        // +0x158
};

class cITextureParticleRenderer {
public:
    virtual int  GetBuffer(int count, u8** buffer, int* stride) = 0;   // slot 0
    virtual void GetVertexAndIndexBuffer() = 0;                        // slot 1
    virtual void ReleaseAndDrawBuffer() = 0;                           // slot 2
};

static __forceinline u8 ColorToByte(float v)
{
    __m128 m = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&v));
    m = _mm_mul_ss(m, _mm_set_ss(255.0f));
    m = _mm_min_ss(m, _mm_set_ss(255.0f));
    return (u8)_mm_cvt_ss2si(m);
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

static __forceinline void SampleCurve(const Vector3* curve, unsigned int last, float t,
                                      float& ox, float& oy, float& oz)
{
    if (last == 0) {
        ox = curve[0].x;
        oy = curve[0].y;
        oz = curve[0].z;
    } else {
        float f = (float)last * t;
        int i = (int)f;
        float frac = f - (float)i;
        const Vector3& a = curve[i];
        if (frac > 0.0f) {
            const Vector3& b = curve[i + 1];
            ox = a.x + (b.x - a.x) * frac;
            oy = a.y + (b.y - a.y) * frac;
            oz = a.z + (b.z - a.z) * frac;
        } else {
            ox = a.x;
            oy = a.y;
            oz = a.z;
        }
    }
}

static __forceinline Vector3 Rotate(const Vector3& v, const Matrix33& m)
{
    Vector3 r;
    r.x = m.m[2][0] * v.z + m.m[1][0] * v.y + m.m[0][0] * v.x;
    r.y = m.m[2][1] * v.z + m.m[1][1] * v.y + m.m[0][1] * v.x;
    r.z = m.m[2][2] * v.z + m.m[1][2] * v.y + m.m[0][2] * v.x;
    return r;
}

// @ 0x00a954b0
void Stream_Quad(cParticlesEffect* effect, cITextureParticleRenderer* renderer, u8* offsets)
{
    cParticlesDescription* desc = effect->mDesc;
    cParticle* particle = effect->mParticlesFirst;
    int remaining = effect->mParticleCount;
    unsigned int lastColor = desc->mColorCurve.size() - 1;
    unsigned int lastAlpha = desc->mAlphaCurve.size() - 1;
    unsigned int lastSize = desc->mSizeCurve.size() - 1;

    u8* buffer;
    int stride;
    while (remaining > 0) {
        int count = renderer->GetBuffer(remaining, &buffer, &stride);
        if (count == 0)
            return;
        remaining -= count;
        if (count > 0) {
            const Vector2 uv0 = { 0.0f, 0.0f };
            const Vector2 uv1 = { 1.0f, 0.0f };
            const Vector2 uv2 = { 1.0f, 1.0f };
            const Vector2 uv3 = { 0.0f, 1.0f };
            do {
                const float t = particle->mAge / particle->mLife;
                float size = effect->mSizeScale * SampleCurve(desc->mSizeCurve.mpBegin, lastSize, t);
                float cx, cy, cz;
                SampleCurve(desc->mColorCurve.mpBegin, lastColor, t, cx, cy, cz);
                Vector3 c;
                c.x = effect->mColorScale.x * cx;
                c.y = cy * effect->mColorScale.y;
                c.z = cz * effect->mColorScale.z;
                float alpha = effect->mAlphaScale * SampleCurve(desc->mAlphaCurve.mpBegin, lastAlpha, t);

                Vector3 pos = particle->mPosition;
                if (effect->mTransform.mFlags & 2)
                    pos = Rotate(pos, effect->mTransform.mRotation);
                const float scale = effect->mTransform.mScale;
                Vector4 v;
                v.x = effect->mTransform.mTranslation.x + pos.x * scale;
                v.y = effect->mTransform.mTranslation.y + pos.y * scale;
                v.z = effect->mTransform.mTranslation.z + pos.z * scale;
                v.w = t;

                Vector3 vel = particle->mVelocity;
                if (effect->mTransform.mFlags & 2)
                    vel = Rotate(vel, effect->mTransform.mRotation);
                Vector4 n;
                n.x = vel.x * scale;
                n.y = vel.y * scale;
                n.z = vel.z * scale;
                n.w = effect->mTransform.mScale * size;

                u8 r = ColorToByte(c.x);
                u8 g = ColorToByte(c.y);
                u8 b = ColorToByte(c.z);
                u8 a = ColorToByte(alpha);
                u32 color = ((((u32)a << 8 | r) << 8 | g) << 8) | b;

                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv0;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv1;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv2;
                buffer += stride;
                *(Vector4*)(buffer + offsets[0]) = v;
                *(Vector4*)(buffer + offsets[1]) = n;
                *(u32*)(buffer + offsets[2]) = color;
                *(Vector2*)(buffer + offsets[3]) = uv3;
                buffer += stride;
                particle = particle->mpNext;
            } while (--count);
        }
        renderer->ReleaseAndDrawBuffer();
    }
}
