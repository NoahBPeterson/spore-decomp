// slice s00a78ce0 -- EA::Swarm steering: the 16-entry sin/cos table reduction, the polynomial
// FastAtan2, the transform direction helpers, the random / spherical helpers and the cRWState
// steering state (per-frame parameter update, force accumulation, keyed impulse table) plus the
// small stream helpers used by the key records.
//
//   @ 0x00a78ce0  FastSinCos(float, float*, float*)         table-reduced sin/cos
//   @ 0x00a78d90  EA::Swarm::FastAtan2(float, float)        polynomial atan2 (returns float10)
//   @ 0x00a78e30  CopyRec7(Rec7*, Rec7*, Rec7*)            copy a range of 0x1c-byte records; returns the end pointer
//   @ 0x00a78e90  Xform::InverseTransformDir(Vec3*)         inverse rotate (transpose) + 1/scale
//   @ 0x00a78f80  RandomSymmetric(float)                    uniform double in [-r, r] clamped
//   @ 0x00a78fd0  SphericalDir(const Vec3*, float*, float*) yaw / pitch of a direction
//   @ 0x00a790a0  EA::Swarm::cRWState::Update(const KeyDesc*)
//   @ 0x00a79300  EA::Swarm::cRWState::AccumulateForce(Vec3*)
//   @ 0x00a79430  EA::Swarm::cRWState::Init(const KeyDesc*, const Vec3*, bool)
//   @ 0x00a79500  ApplyDirectedImpulse(const ImpulseTable*, const Vec3*, float, Vec3*)
//   @ 0x00a79660  ReadState(State*, const KeyList*)
//   @ 0x00a796d0  ReadRec(IStream*, KeyRec*)
//   @ 0x00a79710  WriteRec(IStream*, KeyRec*)
//   @ 0x00a79760  ReadRecB(IStream*, KeyRecB*)
//   @ 0x00a797a0  WriteRecB(IStream*, KeyRecB*)
//   @ 0x00a797f0  Xform::TransformDir(Vec3*)                rotate + scale
//
// Build: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

typedef unsigned int uint32;

// ---------------------------------------------------------------- external helpers
extern "C" double __cdecl asin(double);                          // 0x011e08bc lib_cblock asin
double __cdecl cConfigManagerUnnamedB90(float* pair);            // 0x007cdb90 random float of a pair
float  FUN_00a78c80(float pitch);                                // 0x00a78c80 pitch helper

namespace EA { namespace Random {
class RandomLinearCongruential {                                  // 0x009360d0
public:
    double RandomDoubleUniform();
};
}}
typedef EA::Random::RandomLinearCongruential ExtRandom;
extern ExtRandom g_Random;                                       // 0x016778dc shared math RNG
extern float g_SinFreq;                                          // 0x016770d8 16 / 2pi
extern float g_SinPeriod;                                        // 0x01677160 2pi / 16
extern float g_TwoPi;                                            // 0x01677174 2pi
extern float g_SinTable[32];                                     // 0x01677840 {sin, cos} of i * period
extern float g_HalfPi;                                           // 0x01554b54 pi / 2
extern float g_Three;                                            // 0x013eb95c 3.0f

// ---------------------------------------------------------------- records
struct Vec3 { float x, y, z; };

struct Rec7 { float f[7]; };                                      // 0x1c

struct Xform {                                                    // 0x38
    unsigned flags;              // +0x00
    Vec3     translation;        // +0x04
    float    scale;              // +0x10
    float    m[9];               // +0x14
    void InverseTransformDir(Vec3* v) const;
    void TransformDir(Vec3* v) const;
};

struct ImpulseTable {                                             // impulse falloff description
    float* begin;                // +0x00 keyed speed table
    float* end;                  // +0x04
    int    pad0[3];              // +0x08
    float  speed;                // +0x14 distance the table spans
    float  threshold;            // +0x18 below this the impulse is dropped
};

struct KeyDesc {                                                  // per-state steering description
    float  aLo, aHi;             // +0x00
    float  bLo, bHi;             // +0x08
    float  jitter;               // +0x10
    float  spread;               // +0x14
    float  weight;               // +0x18
    float* keysBegin;            // +0x1c
    float* keysEnd;              // +0x20
    int    pad[3];               // +0x24
    unsigned char mode;          // +0x30
};

struct cRWState {                                                 // 0x18
    float f0;                    // +0x00
    float a;                     // +0x04
    float b;                     // +0x08
    float phase;                 // +0x0c
    float pitch;                 // +0x10
    int   frame;                 // +0x14
    void Update(const KeyDesc* d);
    void AccumulateForce(Vec3* force);
    void Init(const KeyDesc* d, const Vec3* dir, bool instant);
};

struct KeyList { Rec7* begin; Rec7* end; };

struct State {                                                    // key state record
    int   unk0;                   // +0x00
    float g;                      // +0x04
    Vec3  a;                      // +0x08
    Vec3  b;                      // +0x14
};

struct KeyRec {                                                   // 0x1c stream record
    float f0;                     // +0x00
    Vec3  a;                      // +0x04
    Vec3  b;                      // +0x10
    float c;                      // +0x18
};
struct KeyRecB {                                                  // 0x1c stream record (no id)
    Vec3  a;                      // +0x00
    Vec3  b;                      // +0x0c
    float c;                      // +0x18
};

// ---------------------------------------------------------------- IStream
struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int  Read(void* data, uint32 size);                   // +0x30
    virtual void v13();
    virtual bool Write(const void* data, uint32 size);            // +0x38
};
bool ReadInt32(IStream* s, int* p, uint32 count, int endian);     // 0x0093a780
bool WriteUint32(IStream* s, const uint32* p, uint32 count, int endian); // 0x0093aa70
inline bool WriteFloat32(IStream* s, float value) { return WriteUint32(s, (uint32*)&value, 1, 0); }

// ---------------------------------------------------------------- helpers
static __forceinline double Clamp(double v, double lo, double hi)
{
    if (v < hi) {
        if (lo <= v)
            return v;
        return lo;
    }
    return hi;
}

// @ 0x00a78ce0
__declspec(noinline) void FastSinCos(float angle, float* outSin, float* outCos)
{
    float scaled = g_SinFreq * angle + 12582912.0f;
    unsigned idx = *(unsigned*)&scaled & 0xf;
    int ip = *(int*)&scaled + (int)0xB4C00000u;
    float frac = angle - (float)ip * g_SinPeriod;
    float* e = &g_SinTable[idx * 2];
    float& a = e[0];
    float& b = e[1];
    *outSin = (b - (a * frac) * 0.5f) * frac + a;
    *outCos = b - ((b * frac) * 0.5f + a) * frac;
}

// @ 0x00a78d90
__declspec(noinline) long double FastAtan2(float y, float x)
{
    float ay = (float)fabs(y) + 1e-10f;
    float ax = (float)fabs(x);
    float t = (ay - ax) / (ax + ay);
    float r = (0.9817f - (t * t) * 0.1963f) * t;
    if (x < 0.0f)
        r = g_HalfPi * g_Three - r;
    else
        r = g_HalfPi + r;
    if (y < 0.0f)
        r = -r;
    return r;
}

// @ 0x00a78e30
__declspec(noinline) Rec7* CopyRec7(Rec7* first, Rec7* last, Rec7* dst)
{
    while (first != last) {
        if (dst)
            *dst = *first;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00a78e90
void Xform::InverseTransformDir(Vec3* v) const
{
    if (scale != 1.0f) {
        float inv = 1.0f / scale;
        v->x = v->x * inv;
        v->y = inv * v->y;
        v->z = inv * v->z;
    }
    if (flags & 2) {
        float z = v->z;
        float y = v->y;
        float x = v->x;
        Vec3 t;
        t.x = (m[1] * y + m[2] * z) + m[0] * x;
        t.y = (m[4] * y + m[5] * z) + m[3] * x;
        t.z = (m[7] * y + m[8] * z) + m[6] * x;
        *v = t;
    }
}

// @ 0x00a78f80
__declspec(noinline) double RandomSymmetric(float range)
{
    double lo = -(double)range;
    double hi = (double)range;
    double v = g_Random.RandomDoubleUniform() * (hi - lo) + lo;
    return Clamp(v, lo, hi);
}

// @ 0x00a78fd0
__declspec(noinline) void SphericalDir(const Vec3* v, float* outYaw, float* outPitch)
{
    float x = v->x;
    float y = v->y;
    float d = x * x + y * y;
    if (d < 1e-6f) {
        float half = 1.5707964f;
        *outYaw = 0.0f;
        if (v->z < 0.0f)
            *outPitch = -half;
        else
            *outPitch = half;
        return;
    }
    *outYaw = (float)FastAtan2(y, x);
    *outPitch = (float)asin((double)v->z / sqrt((double)d + (double)v->z * (double)v->z));
}

// @ 0x00a790a0
void cRWState::Update(const KeyDesc* d)
{
    {
        double lo = d->aLo;
        double hi = d->aHi;
        float v = (float)Clamp(g_Random.RandomDoubleUniform() * (hi - lo) + lo, lo, hi);
        f0 = f0 + v;
    }
    {
        double lo = d->bLo;
        double hi = d->bHi;
        float v = (float)Clamp(g_Random.RandomDoubleUniform() * (hi - lo) + lo, lo, hi);
        if (d->weight < 0.5f) {
            b = v;
            a = d->weight * v * 2.0f;
        } else {
            b = (1.0f - d->weight) * v * 2.0f;
            a = v;
        }
    }
    if (d->weight < 1.0f) {
        float r = (float)RandomSymmetric(d->jitter + 1e-5f);
        float w = g_TwoPi;
        phase = w * r + phase;
        float sp = d->spread * w;
        if (r >= 0.0f)
            phase = sp + phase;
        else
            phase = phase - sp;
    }
    if (d->weight > 0.0f) {
        float r = (float)RandomSymmetric(d->jitter + 1e-5f);
        float w = g_TwoPi;
        pitch = w * r + pitch;
        float sp = d->spread * w;
        if (r >= 0.0f)
            pitch = sp + pitch;
        else
            pitch = pitch - sp;
    }
    if (d->keysBegin != d->keysEnd) {
        int n = (int)(d->keysEnd - d->keysBegin);
        unsigned i = frame;
        float w = g_TwoPi;
        if (i < (unsigned)n) {
            phase = d->keysBegin[i] * w + phase;
            if (phase > w)
                phase = phase - w;
            if (phase < -w)
                phase = phase + w;
            frame = ++i;
            if (i >= (unsigned)n) {
                if (d->mode == 0) {
                    frame = 0;
                    return;
                }
                if (d->mode == 1)
                    n--;
                frame = n;
            }
        }
    }
}

// @ 0x00a79300
void cRWState::AccumulateForce(Vec3* force)
{
    if (a == 0.0f) {
        if (b == 0.0f)
            return;
        float sn, cs;
        FastSinCos(phase, &sn, &cs);
        force->x = cs * b + force->x;
        force->y = sn * b + force->y;
        return;
    }
    if (b == 0.0f) {
        force->z = FUN_00a78c80(pitch) * a + force->z;
        return;
    }
    float s1, c1, s2, c2;
    FastSinCos(pitch, &s1, &c1);
    FastSinCos(phase, &s2, &c2);
    force->x = (s2 * c1) * b + force->x;
    force->y = (c2 * c1) * b + force->y;
    force->z = s1 * a + force->z;
}

// @ 0x00a79430
void cRWState::Init(const KeyDesc* d, const Vec3* dir, bool instant)
{
    SphericalDir(dir, &phase, &pitch);
    frame = 0;
    if (!instant) {
        f0 = 0.0f;
        Update(d);
    } else {
        f0 = (float)cConfigManagerUnnamedB90((float*)d);
        float v = (float)cConfigManagerUnnamedB90((float*)((const char*)d + 8));
        if (d->weight < 0.5f) {
            b = v;
            a = d->weight * v * 2.0f;
        } else {
            b = (1.0f - d->weight) * v * 2.0f;
            a = v;
        }
    }
}

// @ 0x00a79500
bool ApplyDirectedImpulse(const ImpulseTable* tbl, const Vec3* dir, float magnitude, Vec3* force)
{
    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float len2 = (z * z + y * y) + x * x;
    if (0.0f < len2) {
        float len = (float)sqrt((double)len2);
        if (len < tbl->threshold)
            return false;
        float inv = 1.0f / len;
        float t = len / tbl->speed;
        float u = t > 1.0f ? 1.0f : t;
        int n = (int)(tbl->end - tbl->begin) - 1;
        float s;
        if (n == 0) {
            s = tbl->begin[0];
        } else {
            float f = (float)(unsigned)n * u;
            int i = (int)f;
            float fr = f - (float)i;
            if (fr <= 0.0f)
                s = tbl->begin[i];
            else
                s = (tbl->begin[i + 1] - tbl->begin[i]) * fr + tbl->begin[i];
        }
        float nx = inv * x;
        float ny = y * inv;
        float nz = z * inv;
        float m = s * magnitude;
        force->x = nx * m + force->x;
        force->y = ny * m + force->y;
        force->z = nz * m + force->z;
    }
    return true;
}

// @ 0x00a79660
bool ReadState(State* dst, const KeyList* src)
{
    if (src->begin == src->end)
        return false;
    if (src->begin->f[6] != 0.0f)
        return false;
    dst->a = *(Vec3*)&src->begin->f[0];
    dst->b = *(Vec3*)&src->begin->f[3];
    float last = src->end[-1].f[6];
    if (0.0f < last)
        dst->g = last;
    return true;
}

// @ 0x00a796d0
void ReadRec(IStream* s, KeyRec* r)
{
    ReadInt32(s, (int*)&r->f0, 1, 0);
    s->Read(&r->a, 0xc);
    s->Read(&r->b, 0xc);
}

// @ 0x00a79710
void WriteRec(IStream* s, KeyRec* r)
{
    WriteFloat32(s, r->f0);
    s->Write(&r->a, 0xc);
    s->Write(&r->b, 0xc);
}

// @ 0x00a79760
void ReadRecB(IStream* s, KeyRecB* r)
{
    s->Read(&r->a, 0xc);
    s->Read(&r->b, 0xc);
    ReadInt32(s, (int*)&r->c, 1, 0);
}

// @ 0x00a797a0
void WriteRecB(IStream* s, KeyRecB* r)
{
    s->Write(&r->a, 0xc);
    s->Write(&r->b, 0xc);
    WriteFloat32(s, r->c);
}

// @ 0x00a797f0
void Xform::TransformDir(Vec3* v) const
{
    if (flags & 2) {
        float y = v->y;
        float z = v->z;
        float x = v->x;
        Vec3 t;
        t.x = (m[3] * y + m[6] * z) + m[0] * x;
        t.y = (m[1] * x + m[4] * y) + m[7] * z;
        t.z = (m[2] * x + m[5] * y) + m[8] * z;
        *v = t;
    }
    float s = scale;
    v->x = v->x * s;
    v->y = v->y * s;
    v->z = s * v->z;
}
