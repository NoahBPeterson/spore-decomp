// Slice s00a95d30 -- particle quad vertex writer (0x00a95d30, 2019 bytes).
//
// Walks a linked list of live particles of an effect and writes four vertices per particle
// (a billboard quad) into vertex buffers handed out by a sink object. For each particle the
// age fraction (age / life) samples three piecewise-linear curves of the effect's descriptor:
// a size curve (float), a color curve (Vec3) and an alpha curve (float). Two particle vectors
// (a: corner offset, b: second attribute) are optionally rotated by the effect's 3x3 matrix
// (flag 2), scaled and offset, and the clamped color is packed as ARGB. The four corners use
// the same position/attribute/color words and differ only in the corner mask OR-ed into the
// rotated UV word (none, 0xff0000, 0xffff00, 0xff00).
// The sink supplies (base pointer, stride) for up to `want` vertex groups per Fetch call.
// Module flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- (aligned frame: SSE intrinsics).
#include "types.h"
#include <math.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <intrin.h>
#pragma intrinsic(_rotr)

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
struct Vec4 { float x, y, z, w; };

struct FloatCurve {          // eastl::vector<float> (20 bytes in this build)
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    int mAlloc;
    int pad;
};
struct Vec3Curve {           // eastl::vector<Vec3>
    Vec3* mpBegin;
    Vec3* mpEnd;
    Vec3* mpCap;
    int mAlloc;
    int pad;
};

struct EffectDesc {
    uint32_t pad00[0x20];
    FloatCurve size;         // +0x80
    Vec3Curve color;         // +0x94
    FloatCurve alpha;        // +0xa8
};

struct Particle {
    Particle* next;          // +0x00
    int pad04;
    float age;               // +0x08
    float life;              // +0x0c
    Vec3 a;                  // +0x10
    Vec3 b;                  // +0x1c
    uint16_t uv;             // +0x28
};

struct Mat3 {
    float m[9];
    Vec3 Mul(const Vec3& v) const
    {
        return Vec3((m[6] * v.z + m[3] * v.y) + m[0] * v.x,
                    (m[7] * v.z + m[4] * v.y) + m[1] * v.x,
                    (m[8] * v.z + m[5] * v.y) + m[2] * v.x);
    }
};

struct Effect {
    uint32_t pad00[5];
    Particle* mpParticles;   // +0x14
    uint32_t pad18;
    int mCount;              // +0x1c
    EffectDesc* mpDesc;      // +0x20
    uint32_t pad24[0x2a];
    uint32_t mFlags;         // +0xcc
    float origin[3];         // +0xd0
    float scale;             // +0xdc
    Mat3 mat;                // +0xe0
    uint32_t pad104[0x13];
    float sizeScale;         // +0x150
    float alphaScale;        // +0x154
    float colorScale[3];     // +0x158
};

struct VertexSink {
    virtual int Fetch(int want, char** base, int* stride);   // slot 0
    virtual void pv_1();
    virtual void Flush();                                    // slot 2
};

__forceinline float SampleFloat(const FloatCurve& c, unsigned n, float t)
{
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f) {
        float a = c.mpBegin[i];
        return (c.mpBegin[i + 1] - a) * frac + a;
    }
    return c.mpBegin[i];
}

__forceinline Vec3 SampleVec3(const Vec3Curve& c, unsigned n, float t)
{
    if (n == 0)
        return c.mpBegin[0];
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    const Vec3* p = c.mpBegin + i;
    if (frac > 0.0f) {
        Vec3 r;
        r.x = p[0].x + (p[1].x - p[0].x) * frac;
        r.y = p[0].y + (p[1].y - p[0].y) * frac;
        r.z = p[0].z + (p[1].z - p[0].z) * frac;
        return r;
    }
    return *p;
}

// Clamp to [0,1], scale to 0..255 and round (maxss, mulss, minss, cvtss2si).
static const float k255 = 255.0f;
inline uint32_t ToByte(float x)
{
    __m128 v = _mm_max_ss(_mm_setzero_ps(), _mm_load_ss(&x));
    v = _mm_mul_ss(v, _mm_load_ss(&k255));
    v = _mm_min_ss(v, _mm_load_ss(&k255));
    return (uint8_t)_mm_cvtss_si32(v);
}

inline void WriteVertex(char* v, const uint8_t* off, const Vec4& p, const Vec4& q, uint32_t color, uint32_t uvw)
{
    *(Vec4*)(v + off[0]) = p;
    *(Vec4*)(v + off[1]) = q;
    *(uint32_t*)(v + off[2]) = color;
    *(uint32_t*)(v + off[3]) = uvw;
}

// @ 0x00a95d30
void __cdecl WriteParticleQuads(Effect* fx, VertexSink* sink, const uint8_t* off)
{
    EffectDesc* d = fx->mpDesc;
    Particle* node = fx->mpParticles;
    int remaining = fx->mCount;
    unsigned nColor = (unsigned)(d->color.mpEnd - d->color.mpBegin) - 1;
    unsigned nAlpha = (unsigned)(d->alpha.mpEnd - d->alpha.mpBegin) - 1;
    unsigned nSize = (unsigned)(d->size.mpEnd - d->size.mpBegin) - 1;

    while (remaining > 0) {
        char* base;
        int stride;
        int n = sink->Fetch(remaining, &base, &stride);
        if (n == 0)
            return;
        remaining -= n;
        for (int k = n; k > 0; --k) {
            float t = node->age / node->life;

            float sz = fx->sizeScale * SampleFloat(d->size, nSize, t);

            Vec3 col = SampleVec3(d->color, nColor, t);
            float cr = fx->colorScale[0] * col.x;
            float cg = col.y * fx->colorScale[1];
            float cb = col.z * fx->colorScale[2];

            float al = fx->alphaScale * SampleFloat(d->alpha, nAlpha, t);

            Vec3 a = node->a;
            Vec3 b = node->b;
            if (fx->mFlags & 2)
                a = fx->mat.Mul(a);
            float s = fx->scale;
            Vec4 pos = { fx->origin[0] + a.x * s, fx->origin[1] + a.y * s, fx->origin[2] + a.z * s, t };

            if (fx->mFlags & 2)
                b = fx->mat.Mul(b);
            Vec4 att = { b.x * fx->scale, b.y * fx->scale, b.z * fx->scale, fx->scale * sz };

            uint32_t r = ToByte(cr);
            uint32_t g = ToByte(cg);
            uint32_t bl = ToByte(cb);
            uint32_t aa = ToByte(al);
            uint32_t color = (((aa << 8 | r) << 8 | g) << 8) | bl;
            uint32_t uvw = _rotr(node->uv, 8);

            WriteVertex(base, off, pos, att, color, uvw);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xff0000);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xffff00);
            base += stride;
            WriteVertex(base, off, pos, att, color, uvw | 0xff00);
            base += stride;
            node = node->next;
        }
        sink->Flush();
    }
}
