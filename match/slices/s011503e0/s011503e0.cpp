// Slice s011503e0: FUN_011503e0 (0x011503e0), a RenderWare audio (rw::audio::core) per-update
// parameter smoother: it converts the control block at +0x98 (filter / envelope settings) into
// per-band biquad (2nd-order Butterworth, K = tan(pi*fc/fs)) coefficients and ramp state.
// /O2 /arch:SSE /fp:fast module, no /EHsc.
#include "types.h"
#include <math.h>

#define NOINLINE __declspec(noinline)

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sin, cos, sqrt)

extern "C" void* __cdecl memset(void* dst, int value, unsigned size);  // 0x011e073e
#pragma function(memset)

struct Elem { float f0, f1, f2, f3; };                       // 0x10 bytes each at params+0x2c

struct Params {                                              // *(this+0x98)
    uint16_t m0;
    uint16_t mCount;                                         // +2
    float f04;
    float f08, f0c, f10, f14;
    float f18, f1c, f20, f24;
    uint32_t pad28;
    Elem mElems[1];                                          // +0x2c
};

struct Band {                                                // 0x50 bytes at this+*(u16*)(this+0xc2)
    char pad00[0x10];
    float c10, c14, c18, c1c, c20, c24, c28, c2c, c30, c34, c38;
    int16_t s3c, s3e;
    float c40, c44, c48, c4c;
};

struct Section {                                             // this+*(u16*)(this+0xc0)
    char pad00[0x24];
    float a24[5];                                            // +0x24
    float d38[5];                                            // +0x38
    float p4c[5];                                            // +0x4c
    float f60, f64, f68;                                     // +0x60..
};

void __stdcall Fn_0114ff00(Section* s, float v);                       // 0x0114ff00
void __stdcall Fn_0114ffd0(void* p, float a, float b);                 // 0x0114ffd0

extern const float _HK_REAL_ONE;                                       // 0x01485720

struct Sub40 {
    float mf40;                                              // +0x40
    char pad44[4];
    float mf48;                                              // +0x48
    char pad4c[8];
};

struct Arc4 {
    float x;                                                 // +0x00
    float y;                                                 // +0x04
    float len2;                                              // +0x08
    float angle;                                             // +0x0c
    void __thiscall Set(float a, float b);                   // 0x01150b20
};

struct IkRow {
    float mW0;                                               // +0x00  r*(t*w0)
    float mMid;                                              // +0x04  r*local4
    float mW1;                                               // +0x08  r*(t*w1)
    float mW2;                                               // +0x0c  (w2*s)*r
    float mW3;                                               // +0x10  (s*w3)*r
};

struct FrameBuffer {
    char pad00[4];
    void* mpData;                                            // +0x04
    char pad08[0x0e - 0x08];
    uint16_t mStride;                                        // +0x0e
};

struct UpdateContext {
    char pad00[0x3000c];
    FrameBuffer* mpA;                                        // +0x3000c
    FrameBuffer* mpB;                                        // +0x30010
};

class Smoother {
public:
    char pad00[0x20];
    uint8_t mb20;                                            // +0x20
    uint8_t mb21;                                            // +0x21
    char pad22[0x28 - 0x22];
    float mf28;                                              // +0x28
    char pad2c[4];
    float mf30;                                              // +0x30
    char pad34[4];
    float mf38;                                              // +0x38
    char pad3c[4];
    union {
        char mSub[0x14];                                     // +0x40
        Sub40 sub;
    };
    float mSampleRate;                                       // +0x54
    float mLimit;                                            // +0x58
    float mf5c;                                              // +0x5c
    float mf60, mf64, mf68;                                  // +0x60
    float mf6c, mf70;                                        // +0x6c
    char pad74[4];
    uint32_t mu78;
    union { uint32_t mu7c; float mf7c; };                    // +0x7c
    union { uint32_t mu80; float mf80; };                    // +0x80
    char pad84[4];
    float mf88;                                              // +0x88
    char pad8c[0x98 - 0x8c];
    Params* mpParams;                                        // +0x98
    uint32_t mCapacity;                                      // +0x9c
    uint32_t mCount;                                         // +0xa0
    uint32_t mua4;                                           // +0xa4
    char paddA8[0xb0 - 0xa8];
    uint32_t mub0;                                           // +0xb0
    uint32_t mub4;                                           // +0xb4
    uint32_t mub8;                                           // +0xb8
    uint32_t mubc;                                           // +0xbc
    uint16_t mOffSection;                                    // +0xc0
    uint16_t mOffBands;                                      // +0xc2
    char padc4;
    uint8_t mbC5;                                            // +0xc5
    uint8_t mbC6;                                            // +0xc6
    char padc7[0xcc - 0xc7];
    uint32_t mmodeCC;                                        // +0xcc
    uint32_t mmodeD0;                                        // +0xd0
    IkRow mIk[5];                                            // +0xd4 .. +0x137
    char pad138[4];
    float mf13c, mf140, mf144, mf148, mf14c;
    float mf150, mf154, mf158, mf15c, mf160;
    Arc4 mArcs[5];                                           // +0x164 .. +0x1b3

    void __thiscall Fn_011501f0(float a, float b, float c, float d, float* out);   // 0x011501f0
    void __thiscall Fn_01150100(float a, float b, float* out);                      // 0x01150100
    float Scale(float v)
    {
        if (mLimit - 256.0f / mSampleRate > v && v > 0.0f)
            return v * mSampleRate;
        return 0.0f;
    }
    void __thiscall Update(uint32_t reset);                  // 0x011503e0
    void __thiscall ProcessFrame(FrameBuffer* b, FrameBuffer* a);        // 0x0114fab0
    void __thiscall CopyRowScaled(FrameBuffer* b, FrameBuffer* a);       // 0x0114fe20
    void __thiscall UpdateArcs();                            // 0x01150b80
    void __thiscall BlendIk(int index);                      // 0x01150fb0
};

inline void SetRamp(Smoother* self, float* target, float* delta, const float* prev, float v)
{
    *target = v;
    *delta = (v - *prev) * 0.00048828125f;
    self->mub8 = 8;
}

// @ 0x011503e0
void Smoother::Update(uint32_t reset)
{
    Params* p = mpParams;
    Section* sec = (Section*)((char*)this + mOffSection);
    Band* bands = (Band*)((char*)this + mOffBands);

    Fn_0114ff00(sec, p->f18 / mSampleRate);
    Fn_0114ffd0(mSub, 1000.0f / mSampleRate, p->f1c);

    float v = Scale(p->f04);
    sec->f60 = v;
    if (fabs(mf6c - v) > 1e-10) {
        mf70 = mf6c;
        mf6c = sec->f60;
    }
    mu80 = mu7c;
    mu7c = mub4;
    float cur = sec->f60;
    if ((uint8_t)reset) {
        sec->f64 = cur;
        mf6c = cur;
        mf70 = cur;
        mu7c = mub4;
        mu80 = mub4;
        sec->f68 = 0.0f;
        mf60 = 0.0f;
        mf64 = 0.0f;
        mf68 = 0.0f;
        mf5c = 1.0f;
        mub8 = 0;
    } else if (cur == 0.0f && p->f04 > 0.0f) {
        float t = p->f20;
        if (fabs(t - 1.0f) > 1e-10) {
            sec->f68 = 1.0f - t;
            mf5c = 1.0f;
            mbC6 = 1;
        } else {
            sec->f68 = 0.0f;
            mf5c = 1.0f;
            mbC6 = 0;
        }
    } else if (256.0f > cur) {
        sec->f68 = 0.0f;
        mf60 = 0.0f;
        mf64 = 0.0f;
        mf68 = 0.0f;
        mf5c = 1.0f;
        mbC6 = 0;
    } else {
        mbC6 = 0;
        float t = p->f20;
        if (fabs(t - 1.0f) > 1e-10) {
            float x = 1.0f - t;
            sec->f68 = x;
            int r = (int)fabs((mf6c - sec->f64) / x);
            mf5c = (float)((r / 256) * 256);
        } else {
            if (mub4 <= mu80)
                mf5c = 256.0f;
            else
                mf5c = (float)((mub4 - mu80) << 8);
            sec->f68 = (mf70 - sec->f64) / mf5c;
        }
    }

    float c = sec->f68;
    if (c < 2.0f && !(c > -2.0f))
        c = -2.0f;
    sec->f68 = c;
    float prev = mf68 * 0.1f;
    mf60 = c;
    float sum = (prev + c * 0.6f) + mf64 * 0.3f;
    sec->f68 = sum;
    mf68 = mf64;
    mf64 = mf60;

    float out[5];
    Fn_011501f0(p->f0c, p->f08, p->f10, p->f14, out);
    SetRamp(this, &sec->a24[0], &sec->d38[0], &sec->p4c[0], out[0]);
    SetRamp(this, &sec->a24[1], &sec->d38[1], &sec->p4c[1], out[1]);
    SetRamp(this, &sec->a24[2], &sec->d38[2], &sec->p4c[2], out[2]);
    SetRamp(this, &sec->a24[3], &sec->d38[3], &sec->p4c[3], out[3]);
    SetRamp(this, &sec->a24[4], &sec->d38[4], &sec->p4c[4], out[4]);

    uint32_t n = p->mCount;
    if (n >= mCapacity)
        n = mCapacity;
    mCount = n;
    float sign = 1.0f;
    const float* e = (const float*)((char*)p + 0x2c);
    float* q = (float*)((char*)bands + 0x18);
    for (uint32_t i = 0; i < mCount; i++, e += 4, q += 20) {
        float fc = e[3] / mSampleRate;
        if (fc < 0.001f) {
            q[0] = 0.0f;
            q[1] = 0.0f;
            q[2] = 0.0f;
            q[-2] = 0.0f;
            q[-1] = 0.0f;
        } else {
            float k = (float)tan(fc * 3.1415927f);
            float k2 = k * k;
            float k14 = k * 1.414f;
            float norm = 1.0f / ((k14 + k2) + 1.0f);
            float a0 = norm * k2;
            q[0] = a0;
            q[2] = a0;
            q[1] = a0 * 2.0f;
            q[-2] = ((k2 - 1.0f) * norm) * 2.0f;
            q[-1] = ((1.0f - k14) + k2) * norm;
        }
        Fn_01150100(e[1], e[2], out);
        float time = Scale(e[0]);
        int ia = (int)out[0];
        float fa = (out[0] - (float)(uint16_t)ia) * sign;
        sign = sign * -1.0f;
        *(int16_t*)(q + 9) = (int16_t)ia;
        q[3] = fa;
        int ib = (int)out[1];
        float fb = (out[1] - (float)(uint16_t)ib) * sign;
        q[10] = time;
        *(int16_t*)((char*)q + 0x26) = (int16_t)ib;
        q[4] = fb;
        if ((uint8_t)reset) {
            q[7] = q[3];
            q[12] = 0.0f;
            q[11] = time;
            q[5] = 0.0f;
            q[8] = fb;
            q[6] = 0.0f;
        } else {
            if (sec->f60 < time) {
                float d = mf5c;
                if (d < 256.0f)
                    d = 2048.0f;
                float r = (time - q[11]) / d;
                q[13] = d;
                q[12] = r;
                if (0.0f > r)
                    q[12] = 0.0f;
            } else {
                q[3] = 0.0f;
                q[4] = 0.0f;
                q[12] = 0.0f;
            }
            q[5] = (q[3] - q[7]) * 0.00390625f;
            q[6] = (q[4] - q[8]) * 0.00390625f;
            float w = q[12];
            if (w < 2.0f && !(w > -2.0f))
                w = -2.0f;
            q[12] = w;
        }
    }
    mf88 = p->f24;
    mbC5 = 1;
    mua4 = 0;
}

// @ 0x01150a40
void __cdecl ProcessSmoother(Smoother* self, UpdateContext* ctx, uint32_t flags)
{
    if ((uint8_t)flags) {
        self->mbC6 = 0;
        self->mub0 = 0x100;
        self->mub4 = 0;
        self->mub8 = 0;
    }
    if (self->mua4 == 1)
        self->Update(flags);

    FrameBuffer* a = ctx->mpA;
    FrameBuffer* b = ctx->mpB;
    if (self->mubc == 0) {
        for (unsigned i = 0; i < self->mb21; ++i)
            memset((char*)b->mpData + (unsigned)b->mStride * i * 4, 0, 0x400);
    } else if (self->mubc == 1) {
        if (self->mbC5 == 1)
            self->ProcessFrame(b, a);
        else
            self->CopyRowScaled(b, a);
    }
    ctx->mpA = b;
    ctx->mpB = a;
    ++self->mub4;
}

// @ 0x01150b20
NOINLINE void __thiscall Arc4::Set(float a, float b)
{
    x = a;
    y = b;
    float sum = a * a + b * b;
    len2 = sum;
    if (sum > _HK_REAL_ONE) {
        len2 = _HK_REAL_ONE;
        double inv = 1.0 / sqrt((double)sum);
        x = (float)(inv * (double)a);
        y = (float)((double)b * inv);
    }
}

static __forceinline void SetArcInline(Arc4* v, float a, float b)
{
    v->x = a;
    v->y = b;
    float sum = a * a + b * b;
    v->len2 = sum;
    if (sum > _HK_REAL_ONE) {
        v->len2 = _HK_REAL_ONE;
        double inv = 1.0 / sqrt((double)sum);
        v->x = (float)((double)a * inv);
        v->y = (float)(inv * (double)b);
    }
}

#pragma float_control(precise, off, push)
// @ 0x01150b80
void __thiscall Smoother::UpdateArcs()
{
    const float DEG2RAD = -0.017453292f;
    double aE = (double)mf28 * (double)DEG2RAD;
    double f14E = (double)sub.mf40 * (double)DEG2RAD;
    float a = (float)aE;
    float f14 = (float)f14E;
    float f13 = mf38;
    float r = mf30;
    float ca = (float)(cos(aE) * (double)r);
    float sa = (float)(sin(aE) * (double)r);

    uint32_t mode = mmodeCC;
    if (mode - 1 > 4)
        return;

    double aC = aE;
    switch (mode) {
    case 1: {
        mArcs[0].Set(ca, sa);
        float ang = a;
        if (r <= 0.0f)
            ang = a + 3.1415927f;
        mArcs[0].angle = ang;
        break;
    }
    case 2: {
        double ang = ((double)f14 + aE) + (double)1.5707964f;
        mArcs[0].Set((float)((double)ca + cos(ang) * (double)f13),
                     (float)((double)sa + sin(ang) * (double)f13));
        mArcs[0].angle = (float)atan2((double)mArcs[0].y, (double)mArcs[0].x);
        mArcs[1].Set((float)((double)ca - cos(ang) * (double)f13),
                     (float)((double)sa - sin(ang) * (double)f13));
        mArcs[1].angle = (float)atan2((double)mArcs[1].y, (double)mArcs[1].x);
        break;
    }
    case 3:
        break;
    case 5: {
        double ang = (double)f14 + aE;
        mArcs[1].Set((float)((double)ca + cos(ang) * (double)f13),
                     (float)((double)sa + sin(ang) * (double)f13));
        mArcs[1].angle = (float)atan2((double)mArcs[1].y, (double)mArcs[1].x);
        aC = (double)a;
        /* fall through */
    }
    case 4: {
        int i0, i1, i2;
        if (mode == 4) {
            i0 = 1; i1 = 2; i2 = 3;
        } else {
            i0 = 2; i1 = 3; i2 = 4;
        }
        double ang;

        ang = ((double)mf7c + (double)f14) + aC;
        SetArcInline(&mArcs[0],
                     (float)(cos(ang) * (double)f13 + (double)ca),
                     (float)(sin(ang) * (double)f13 + (double)sa));
        mArcs[0].angle = (float)atan2((double)mArcs[0].y, (double)mArcs[0].x);

        ang = ((double)f14 + (double)a) - (double)mf7c;
        SetArcInline(&mArcs[i0],
                     (float)(cos(ang) * (double)f13 + (double)ca),
                     (float)(sin(ang) * (double)f13 + (double)sa));
        mArcs[i0].angle = (float)atan2((double)mArcs[i0].y, (double)mArcs[i0].x);

        ang = ((double)mf80 + (double)f14) + aC;
        SetArcInline(&mArcs[i1],
                     (float)(cos(ang) * (double)f13 + (double)ca),
                     (float)(sin(ang) * (double)f13 + (double)sa));
        mArcs[i1].angle = (float)atan2((double)mArcs[i1].y, (double)mArcs[i1].x);

        ang = ((double)f14 + (double)a) - (double)mf80;
        SetArcInline(&mArcs[i2],
                     (float)(cos(ang) * (double)f13 + (double)ca),
                     (float)(sin(ang) * (double)f13 + (double)sa));
        mArcs[i2].angle = (float)atan2((double)mArcs[i2].y, (double)mArcs[i2].x);
        break;
    }
    }
}
#pragma float_control(pop)

// @ 0x01150fb0
void __thiscall Smoother::BlendIk(int index)
{
    Arc4* arc = &mArcs[index];
    float ax = arc->x;
    float ay = arc->y;

    float d0x = mf13c - ax, d0y = mf140 - ay;
    float d1x = mf14c - ax, d1y = mf150 - ay;
    float d2x = mf154 - ax, d2y = mf158 - ay;
    float d3x = mf15c - ax, d3y = mf160 - ay;

    float w0 = 1.0f - (float)(sqrt((double)d0x * (double)d0x + (double)d0y * (double)d0y) * 0.5);
    float w1 = 1.0f - (float)(sqrt((double)d1x * (double)d1x + (double)d1y * (double)d1y) * 0.5);
    float w2 = 1.0f - (float)(sqrt((double)d2x * (double)d2x + (double)d2y * (double)d2y) * 0.5);
    float w3 = 1.0f - (float)(sqrt((double)d3x * (double)d3x + (double)d3y * (double)d3y) * 0.5);

    float u = (ax + 1.0f) * 0.5f;
    if (fabs((double)u) < (double)0.0005f)
        u = 0.0f;
    float v = 1.0f - u;
    if (fabs((double)v) < (double)0.0005f)
        v = 0.0f;

    float t;
    float local4 = 0.0f;
    if (mmodeD0 == 5) {
        float d4x = mf144 - ax, d4y = mf148 - ay;
        local4 = (1.0f - (float)(sqrt((double)d4y * (double)d4y + (double)d4x * (double)d4x) * 0.5)) * sub.mf48;
        t = (float)sqrt((double)u / ((double)local4 * (double)local4 +
                                     ((double)w0 * (double)w0 + (double)w1 * (double)w1)));
        local4 = t * local4;
    } else {
        t = (float)sqrt((double)u / ((double)w0 * (double)w0 + (double)w1 * (double)w1));
    }
    float s = (float)sqrt((double)v / ((double)w2 * (double)w2 + (double)w3 * (double)w3));
    float rr = (float)sqrt(1.0 - (double)arc->len2 * (double)arc->len2);

    IkRow* row = &mIk[index];
    row->mW0 = (float)((double)rr * ((double)t * (double)w0));
    row->mMid = (float)((double)rr * (double)local4);
    row->mW1 = (float)((double)rr * ((double)t * (double)w1));
    row->mW2 = (float)(((double)w2 * (double)s) * (double)rr);
    row->mW3 = (float)(((double)s * (double)w3) * (double)rr);
}
