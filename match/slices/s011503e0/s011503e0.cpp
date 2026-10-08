// Slice s011503e0: FUN_011503e0 (0x011503e0), a RenderWare audio (rw::audio::core) per-update
// parameter smoother: it converts the control block at +0x98 (filter / envelope settings) into
// per-band biquad (2nd-order Butterworth, K = tan(pi*fc/fs)) coefficients and ramp state.
// /O2 /arch:SSE /fp:fast module, no /EHsc.
#include "types.h"
#include <math.h>

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

class Smoother {
public:
    char pad00[0x40];
    char mSub[0x14];                                         // +0x40
    float mSampleRate;                                       // +0x54
    float mLimit;                                            // +0x58
    float mf5c;                                              // +0x5c
    float mf60, mf64, mf68;                                  // +0x60
    float mf6c, mf70;                                        // +0x6c
    char pad74[4];
    uint32_t mu78;
    uint32_t mu7c, mu80;                                     // +0x7c
    char pad84[4];
    float mf88;                                              // +0x88
    char pad8c[0x98 - 0x8c];
    Params* mpParams;                                        // +0x98
    uint32_t mCapacity;                                      // +0x9c
    uint32_t mCount;                                         // +0xa0
    uint32_t mua4;                                           // +0xa4
    char paddA8[0xb4 - 0xa8];
    uint32_t mub4;                                           // +0xb4
    uint32_t mub8;                                           // +0xb8
    char padbc[4];
    uint16_t mOffSection;                                    // +0xc0
    uint16_t mOffBands;                                      // +0xc2
    char padc4;
    uint8_t mbC5;                                            // +0xc5
    uint8_t mbC6;                                            // +0xc6

    void __thiscall Fn_011501f0(float a, float b, float c, float d, float* out);   // 0x011501f0
    void __thiscall Fn_01150100(float a, float b, float* out);                      // 0x01150100
    float Scale(float v)
    {
        if (mLimit - 256.0f / mSampleRate > v && v > 0.0f)
            return v * mSampleRate;
        return 0.0f;
    }
    void __thiscall Update(bool reset);                      // 0x011503e0
};

inline void SetRamp(Smoother* self, float* target, float* delta, const float* prev, float v)
{
    *target = v;
    *delta = (v - *prev) * 0.00048828125f;
    self->mub8 = 8;
}

// @ 0x011503e0
void Smoother::Update(bool reset)
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
    if (reset) {
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
        if (reset) {
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
