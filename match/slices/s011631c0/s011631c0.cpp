// s011631c0 -- audio mix-ramp (cMixRamp): mixes one IIR block through a per-channel
// ramp, fills linear / sine / sqrt ramps and applies per-slot weight scaling.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" void* __cdecl memset(void*, int, unsigned int);   // IAT thunk 0x011e073e
#pragma function(memset)

// ---------------------------------------------------------------- float constants
extern "C" const float g_01446dec;   // 6.2831855  (2*pi)
extern "C" const float g_01485378;   // 0.0
extern "C" const float g_01485720;   // 1.0
extern "C" const float g_014cead0;   // 3.1415927
extern "C" const float g_014ceae4;   // 0.99
extern "C" const float g_014ceae8;   // -0.99
extern "C" const float g_01470f1c;   // 2.0
extern "C" const float g_01471064;   // 0.5
extern "C" const float g_0140ebc0;   // 1/24
extern "C" const float g_014ceaf8;   // 1/720
extern "C" const float g_014ceaf4;   // 1/40320
extern "C" const float g_014ceaf0;   // 1/3628800
extern "C" const float g_014ceaec;   // 1/479001600
extern "C" const float g_01440f84;   // 1/6
extern "C" const float g_014ceb0c;   // 1/120
extern "C" const float g_014ceb08;   // 1/5040
extern "C" const float g_014ceb04;   // 1/362880
extern "C" const float g_014ceb00;   // 1/39916800
extern "C" const float g_014ceafc;   // 1/6227020800

// ---------------------------------------------------------------- other externals
extern "C" float* g_015c41ac;                 // 0x015c41ac: weight-table pointer
extern "C" const signed char g_014ceb78[];    // 0x014ceb78: per-index byte offsets
extern "C" const uint8_t g_014d6fd0[];        // 0x014d6fd0: mode table, entries of 0x3c bytes
extern "C" void (*g_016f16f4)(void*);         // 0x016f16f4: release proc
extern "C" void __fastcall cMixRamp_BaseDtor(void* self);   // 0x01168400

// ---------------------------------------------------------------- types
struct cIIRBufferDesc {
    uint8_t pad0[4];
    float* mData;                        // 0x04
    uint8_t pad8[0x0e - 0x08];
    unsigned short mStride;              // 0x0e
};

struct cIIRBuffers {
    uint8_t pad[0x3000c];
    cIIRBufferDesc* mIn;                 // 0x3000c
    cIIRBufferDesc* mOut;                // 0x30010
};

struct cMixFilterRow {                   // 0x18 bytes
    uint8_t pad0[7];
    uint8_t mF07;                        // 0x07
    uint8_t mF08;                        // 0x08
    uint8_t mF09;                        // 0x09
    uint8_t padA[6];
    uint8_t mF10;                        // 0x10
    uint8_t mF11;                        // 0x11
    uint8_t mF12;                        // 0x12
    uint8_t mF13;                        // 0x13
    int     mShift;                      // 0x14
};

struct cMixRamp {
    void*   mVtbl;                       // 0x00
    uint8_t pad04[0x10 - 0x04];
    float   mCur;                        // 0x10
    float   mPrev;                       // 0x14
    uint8_t pad18[0x30 - 0x18];
    float   mF30;                        // 0x30
    float   mF34;                        // 0x34
    float   mF38;                        // 0x38
    int     mF3c;                        // 0x3c
    int     mF40;                        // 0x40
    float   mF44;                        // 0x44
    float   mF48;                        // 0x48
    uint8_t mF4c;                        // 0x4c
    uint8_t pad4d[0x58 - 0x4d];
    uint8_t mFilter[0xb8 - 0x58];        // 0x58: filter rows, stride 0x18
    uint8_t mWeight[0x1b0 - 0xb8];       // 0xb8: weight rows, stride 0x7c
    void*   mBuf;                        // 0x1b0

    void Configure(float a, float b, float f, int n1, int n2, bool flag);   // 0x01163380
    void ResetState();                                                      // 0x011633e0
    void Mix(cIIRBuffers* io, unsigned count);                              // 0x011631c0
    void SetFade(float f);                                                  // 0x01163be0
    void ApplyWeights(int a, int b, float* scratch);                        // 0x01163f50
    void MixKernel_01161900(float* in, float* out, float* extra, float* params, int idx);
    ~cMixRamp();                                                            // 0x01163dc0
};

// ---------------------------------------------------------------- free functions
extern "C" int MixRampSin(float* dst, int n, float a, float b, int start, int total);      // 0x011633f0
extern "C" int MixRampSqrt(float* dst, int n, float a, float b, int start, int total);     // 0x01163520
extern "C" int MixRampLinear(float* dst, int n, float a, float b, int start, int total);   // 0x01163620
extern "C" void MixBlockLinear(int n, float scale, float* coef, float* a, float* b, float* c);  // 0x01163710
extern "C" void MixBlockCross(int n, float g0, float g1, float* acc,
                              float* e, float* f, float* g, float* out, float* out2);      // 0x01163850
extern "C" void MixDispatch(cMixRamp* self, int n, int a3, int a4, float** params);        // 0x01163b50
extern "C" void cMixRamp_ClearFade(cMixRamp* p);                                           // 0x01163bc0
extern "C" double MixCosPoly(float x);                                                     // 0x01163c30
extern "C" double MixSinPoly(float x);                                                     // 0x01163ce0

// Scales n floats at p by s.  MSVC gives this file-local helper a custom register
// convention: p=EAX, n=EDX, s=XMM0.
static void ScaleBlock(float* p, int n, float s);

// @ 0x011631c0
void cMixRamp::Mix(cIIRBuffers* io, unsigned count)
{
    cIIRBufferDesc* out = io->mOut;
    cIIRBufferDesc* in = io->mIn;
    float* params = (float*)this;
    for (unsigned i = 0; i < count; ++i) {
        float* orow = out->mData + out->mStride * i;
        float* irow = in->mData + in->mStride * i;
        float* extra = 0;
        if (mF4c) extra = (i == 0) ? orow : out->mData;
        MixKernel_01161900(irow, orow, extra, params, i);
        params += 2;
    }
    if (!mF4c) {
        for (unsigned i = 0; i < count; ++i) {
            float* irow = in->mData + in->mStride * i;
            float* orow = out->mData + out->mStride * i;
            for (int j = 0; j < 0x100; ++j) orow[j] *= irow[j];
        }
    } else {
        for (int i = (int)count - 1; i >= 0; --i) {
            float* irow = in->mData + in->mStride * i;
            float* orow = out->mData + out->mStride * i;
            float* base = out->mData;
            if (i < 1) base = orow;
            for (int j = 0; j < 0x100; ++j) orow[j] = irow[j] * base[j];
        }
    }
    cIIRBufferDesc* t = io->mOut;
    io->mOut = io->mIn;
    io->mIn = t;
}

// @ 0x01163380
void cMixRamp::Configure(float a, float b, float f, int n1, int n2, bool flag)
{
    mF30 = a;
    mF34 = b;
    mF38 = f;
    mF3c = n1;
    mF40 = n2;
    mF4c = flag ? 1 : 0;
    mF44 = f / (float)n1;
    mF48 = f / (float)n2;
}

// @ 0x011633e0
void cMixRamp::ResetState()
{
    memset(this, 0, 0x30);
}

// @ 0x011633f0
extern "C" int MixRampSin(float* dst, int n, float a, float b, int start, int total)
{
    float d = b - a;
    int endAll = n - 1 + start;
    int lim = total - 1;
    if (endAll <= lim) lim = endAll;
    int i = start;
    for (; i < 0; ++i) *dst++ = a;
    float ft = (float)total;
    float scale = 3.1415927f / (ft * 2.0f);
    if (d < g_01485378) {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = b - (float)(sin(((double)ft - k) * scale) * d);
                ++k;
            } while (--cnt);
        }
    } else {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = a + (float)(sin((double)k * scale) * d);
                ++k;
            } while (--cnt);
        }
    }
    for (int k = i; k <= endAll; ++k) *dst++ = b;
    return 1;
}

// @ 0x01163520
extern "C" int MixRampSqrt(float* dst, int n, float a, float b, int start, int total)
{
    float d = b - a;
    int endAll = n - 1 + start;
    int lim = total - 1;
    if (endAll <= lim) lim = endAll;
    int i = start;
    for (; i < 0; ++i) *dst++ = a;
    float ft = (float)total;
    double step = (double)d / sqrt((double)total);
    if (d < g_01485378) {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = (float)((double)b - sqrt((double)ft - k) * step);
                ++k;
            } while (--cnt);
        }
    } else {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = (float)((double)a + sqrt((double)k) * step);
                ++k;
            } while (--cnt);
        }
    }
    for (int k = i; k <= endAll; ++k) *dst++ = b;
    return 1;
}

// @ 0x01163620
extern "C" int MixRampLinear(float* dst, int n, float a, float b, int start, int total)
{
    float d = b - a;
    int endAll = n - 1 + start;
    int lim = total - 1;
    if (endAll <= lim) lim = endAll;
    int i = start;
    for (; i < 0; ++i) *dst++ = a;
    float step = d / (float)total;
    if (d < g_01485378) {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = b - ((float)total - (float)k) * step;
                ++k;
            } while (--cnt);
        }
    } else {
        if (i <= lim) {
            int cnt = lim - i + 1;
            int k = i + 1;
            i += cnt;
            do {
                *dst++ = a + (float)k * step;
                ++k;
            } while (--cnt);
        }
    }
    for (int k = i; k <= endAll; ++k) *dst++ = b;
    return 1;
}

// @ 0x01163710
extern "C" void MixBlockLinear(int n, float scale, float* coef, float* a, float* b, float* c)
{
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] * scale + coef[i];
        c[i] = a[i];
    }
}

// @ 0x01163850
extern "C" void MixBlockCross(int n, float g0, float g1, float* acc,
                              float* e, float* f, float* g, float* out, float* out2)
{
    for (int i = 0; i < n; ++i) {
        float gi = g[i];
        out[i] = (1.0f - gi) * g0 * e[i] + gi * g1 * f[i] + acc[i];
        out2[i] = (1.0f - gi) * e[i] + gi * f[i];
    }
}

// @ 0x01163b50
extern "C" void MixDispatch(cMixRamp* self, int n, int a3, int a4, float** params)
{
    if (params[2] == 0)
        MixBlockLinear(n, self->mCur, params[0], params[1], params[4], params[5]);
    else
        MixBlockCross(n, self->mCur, self->mPrev, params[0], params[1], params[2],
                      params[3], params[4], params[5]);
}

// @ 0x01163bc0
extern "C" void cMixRamp_ClearFade(cMixRamp* p)
{
    p->mCur = 0.0f;
    p->mPrev = 0.0f;
}

// @ 0x01163be0
void cMixRamp::SetFade(float f)
{
    if (fabsf(f) > 0.99f) {
        if (f > 0.0f) {
            mPrev = mCur;
            mCur = 0.99f;
            return;
        }
        f = -0.99f;
    }
    mPrev = mCur;
    mCur = f;
}

// @ 0x01163c30
extern "C" double MixCosPoly(float x)
{
    while (x > 6.2831855f) x -= 6.2831855f;
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;
    float x8 = x4 * x4;
    float x10 = x2 * x8;
    float x12 = x6 * x6;
    return 1.0 - 0.5 * x2 + x4 * 0.0416666679084301f - x6 * 0.0013888889225199819f
         + x8 * 2.4801587642286904e-05f - x10 * 2.755731998149713e-07f
         + x12 * 2.08767581000302e-09f;
}

// @ 0x01163ce0
extern "C" double MixSinPoly(float x)
{
    while (x > 6.2831855f) x -= 6.2831855f;
    float x2 = x * x;
    float x3 = x2 * x;
    float x5 = x3 * x2;
    float x7 = x5 * x2;
    float x9 = x7 * x2;
    float x11 = x9 * x2;
    float x13 = x11 * x2;
    return (double)x - x3 * 0.1666666716337204f + x5 * 0.008333330042660236f
         - x7 * 0.00019841270113829523f + x9 * 2.7557318844628753e-06f
         - x11 * 2.5052107943679403e-08f + x13 * 1.6058999963153298e-10f;
}

// @ 0x01163dc0
cMixRamp::~cMixRamp()
{
    void* b = mBuf;
    mVtbl = (void*)0x14d75b0;
    if (b) g_016f16f4(b);
    cMixRamp_BaseDtor(this);
}

// @ 0x01163df0
static void ScaleBlock(float* p, int n, float s)
{
    if (((int)p & 0xf) != 0) {
        p[0] *= s;
        p[1] *= s;
        n -= 2;
        p += 2;
    }
    if (n >= 16) {
        int c = n >> 4;
        n -= c * 16;
        do {
            p[0] *= s;  p[1] *= s;  p[2] *= s;  p[3] *= s;
            p[4] *= s;  p[5] *= s;  p[6] *= s;  p[7] *= s;
            p[8] *= s;  p[9] *= s;  p[10] *= s; p[11] *= s;
            p[12] *= s; p[13] *= s; p[14] *= s; p[15] *= s;
            p += 16;
        } while (--c);
    }
    if (n >= 2) {
        n >>= 1;
        do {
            p[0] *= s;
            p[1] *= s;
            p += 2;
        } while (--n);
    }
}

// @ 0x01163f50
void cMixRamp::ApplyWeights(int a, int b, float* scratch)
{
    unsigned char md = (unsigned char)mF3c;
    cMixFilterRow* fi = (cMixFilterRow*)((char*)this + 0x58 + (b + a * 2) * 0x18);
    short* wrow = (short*)((char*)this + 0xb8 + a * 0x7c);
    unsigned char* mode = (unsigned char*)(g_014d6fd0 + md * 0x3c);
    int n = (fi->mF07 == 0 || fi->mF08 != 2) ? 0x16
          : (fi->mF09 == 0 ? 0 : (md < 3 ? 8 : 6));
    for (int k = 0; k < n; ++k) {
        int idx = ((short*)mode)[k];
        int cnt = ((short*)mode)[k + 1] - idx;
        int wi = wrow[k];
        if (fi->mF13) wi += (int)g_014ceb78[k];
        float w = ((float*)g_015c41ac)[(wi << fi->mShift) * 2];
        if (w != 1.0f) ScaleBlock(scratch + idx, cnt, w);
        (void)cnt;
        (void)k;
    }
    int m = (n == 0x16) ? 0xd : (n == 0 ? 0 : 3);
    if (m < 0xd) {
        unsigned char* p = mode + 0x2e + m;
        short* q = (short*)((char*)wrow + 0x48 + m * 2);
        int cnt = 0xd - m;
        do {
            int b0 = p[0];
            int b1 = p[1];
            int c = b1 - b0;
            int base3 = b0 * 3;
            float w0 = ((float*)g_015c41ac)[((q[-0xd] << fi->mShift) + fi->mF10 * 4) * 2];
            if (w0 != 1.0f) ScaleBlock(scratch + base3, c, w0);
            float w1 = ((float*)g_015c41ac)[((q[0] << fi->mShift) + fi->mF11 * 4) * 2];
            if (w1 != 1.0f) ScaleBlock(scratch + base3 + c, c, w1);
            float w2 = ((float*)g_015c41ac)[((q[0xd] << fi->mShift) + fi->mF12 * 4) * 2];
            if (w2 != 1.0f) ScaleBlock(scratch + base3 + c * 2, c, w2);
            ++p;
            ++q;
        } while (--cnt);
    }
}
