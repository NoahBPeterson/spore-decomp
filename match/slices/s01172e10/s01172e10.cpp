// Slice s01172e10 -- rw::audio::core MPEG polyphase synthesis helpers.
//
//  0x01172e10  cPolySynth::Window(int band, float* out, const float* in)
//  0x01173100  Clear8(float* p)
//  0x01173130  ResampleFir(float* c, int n, const float* in, float* out)
//  0x01173460  cSynthWindow::SetWindow(int type)
//  0x01173730  OnePole(float* state, int n, const float* in, float* out)
//  0x01173770  Interpolate(int n, const float* in, float* out, int* pos,
//                         unsigned* frac, int stepLo, int stepHi)
#include "types.h"

// ---------------------------------------------------------------- externals
extern "C" float* g_WinTable;   // 0x014dcbb0: 512+ float prototype-filter table

extern "C" void __fastcall Dct32(float* out1, float* out2, const float* in);  // 0x01171ba0
extern "C" double MixCosPoly(float x);                                        // 0x01163c30
extern "C" double MixSinPoly(float x);                                        // 0x01163ce0

static const float PI = 3.1415927410125732f;
static const float PI_4 = 0.7853981852531433f;

// ---------------------------------------------------------------- 0x01172e10
struct cPolySynth {
    char pad000[0x2c];
    unsigned char mPhase[0x18];   // 0x2c: per-band window rotation
    float* mBuf;                  // 0x44: per-band history (0x900 bytes per band)

    void Window(int band, float* out, const float* in);
};

// @ 0x01172e10
void cPolySynth::Window(int band, float* out, const float* in)
{
    unsigned char b = (unsigned char)((mPhase[band] - 1) & 0xf);
    mPhase[band] = b;
    const int e = b & 1;
    const int o = e ^ 1;
    float* base = mBuf + band * 0x240;
    float* out2 = base + o * 0x120;
    float* out1 = base + ((b + e) & 0xf) + e * 0x120;

    Dct32(out1, out2, in);

    const float* s = out2 + (b + o);
    const float* w = g_WinTable - (b + o);

    int k;
    for (k = 0; k < 16; k++) {
        out[k] = w[0x00] * s[0x00] - w[0x01] * s[0x01]
               + w[0x02] * s[0x02] - w[0x03] * s[0x03]
               + w[0x04] * s[0x04] - w[0x05] * s[0x05]
               + w[0x06] * s[0x06] - w[0x07] * s[0x07]
               + w[0x08] * s[0x08] - w[0x09] * s[0x09]
               + w[0x0a] * s[0x0a] - w[0x0b] * s[0x0b]
               + w[0x0c] * s[0x0c] - w[0x0d] * s[0x0d]
               + w[0x0e] * s[0x0e] - w[0x0f] * s[0x0f];
        w += 0x20;
        s += 0x10;
    }

    out[16] = w[0x00] * s[0x00] + w[0x02] * s[0x02]
            + w[0x04] * s[0x04] + w[0x06] * s[0x06]
            + w[0x08] * s[0x08] + w[0x0a] * s[0x0a]
            + w[0x0c] * s[0x0c] + w[0x0e] * s[0x0e];

    s -= 0x10;
    w += (b + o) * 2 - 0x20;

    for (k = 0; k < 15; k++) {
        out[17 + k] = -w[-0x01] * s[0x00] - w[-0x02] * s[0x01]
                    - w[-0x03] * s[0x02] - w[-0x04] * s[0x03]
                    - w[-0x05] * s[0x04] - w[-0x06] * s[0x05]
                    - w[-0x07] * s[0x06] - w[-0x08] * s[0x07]
                    - w[-0x09] * s[0x08] - w[-0x0a] * s[0x09]
                    - w[-0x0b] * s[0x0a] - w[-0x0c] * s[0x0b]
                    - w[-0x0d] * s[0x0c] - w[-0x0e] * s[0x0d]
                    - w[-0x0f] * s[0x0e] - w[-0x10] * s[0x0f];
        w -= 0x20;
        s -= 0x10;
    }
}

// ---------------------------------------------------------------- 0x01173100
// @ 0x01173100
void Clear8(float* p)
{
    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;
    p[3] = 0.0f;
    p[4] = 0.0f;
    p[5] = 0.0f;
    p[6] = 0.0f;
    p[7] = 0.0f;
}

// ---------------------------------------------------------------- 0x01173130
// @ 0x01173130
void ResampleFir(float* c, int n, const float* in, float* out)
{
    int i;
    for (i = 0; i + 4 <= n; i += 4) {
        float r0 = (c[7] + in[i]) * c[8];
        r0 = r0 + (c[5] + c[1]) * c[10];
        r0 = r0 + (c[4] + c[2]) * c[11];
        r0 = r0 + (c[0] + c[6]) * c[9];
        r0 = r0 + c[3] * c[12];
        out[i] = r0;
        c[7] = c[6]; c[6] = c[5]; c[5] = c[4]; c[4] = c[3];
        c[3] = c[2]; c[2] = c[1]; c[1] = c[0]; c[0] = in[i];
        float r1 = (c[7] + in[i + 1]) * c[8];
        r1 = r1 + (c[5] + c[1]) * c[10];
        r1 = r1 + (c[4] + c[2]) * c[11];
        r1 = r1 + (c[0] + c[6]) * c[9];
        r1 = r1 + c[3] * c[12];
        out[i + 1] = r1;
        c[7] = c[6]; c[6] = c[5]; c[5] = c[4]; c[4] = c[3];
        c[3] = c[2]; c[2] = c[1]; c[1] = c[0]; c[0] = in[i + 1];
        float r2 = (c[7] + in[i + 2]) * c[8];
        r2 = r2 + (c[5] + c[1]) * c[10];
        r2 = r2 + (c[4] + c[2]) * c[11];
        r2 = r2 + (c[0] + c[6]) * c[9];
        r2 = r2 + c[3] * c[12];
        out[i + 2] = r2;
        c[7] = c[6]; c[6] = c[5]; c[5] = c[4]; c[4] = c[3];
        c[3] = c[2]; c[2] = c[1]; c[1] = c[0]; c[0] = in[i + 2];
        float r3 = (c[7] + in[i + 3]) * c[8];
        r3 = r3 + (c[5] + c[1]) * c[10];
        r3 = r3 + (c[4] + c[2]) * c[11];
        r3 = r3 + (c[0] + c[6]) * c[9];
        r3 = r3 + c[3] * c[12];
        out[i + 3] = r3;
        c[7] = c[6]; c[6] = c[5]; c[5] = c[4]; c[4] = c[3];
        c[3] = c[2]; c[2] = c[1]; c[1] = c[0]; c[0] = in[i + 3];
    }
    for (; i < n; i++) {
        float r = (c[7] + in[i]) * c[8];
        r = r + (c[5] + c[1]) * c[10];
        r = r + (c[4] + c[2]) * c[11];
        r = r + (c[0] + c[6]) * c[9];
        r = r + c[3] * c[12];
        out[i] = r;
        c[7] = c[6]; c[6] = c[5]; c[5] = c[4]; c[4] = c[3];
        c[3] = c[2]; c[2] = c[1]; c[1] = c[0]; c[0] = in[i];
    }
}

// ---------------------------------------------------------------- 0x01173460
struct cSynthWindow {
    char pad000[0x20];
    float mWin[5];    // 0x20: five window taps, mWin[4] doubles as the centre term
    float mLow;       // 0x34
    float mHigh;      // 0x38
};

void SetWindow(cSynthWindow* self, int type);

// @ 0x01173460
void SetWindow(cSynthWindow* p, int type)
{
    int i;
    if ((type == 3 || type == 4) && p->mLow > 0.8f) p->mLow = 0.8f;

    switch (type) {
    case 2:
        p->mWin[4] = p->mHigh;
        for (i = 1; i <= 4; i++) {
            const float ph = (float)i * PI;
            p->mWin[4 - i] = (float)(MixSinPoly(p->mHigh * ph) / ph);
        }
        break;
    case 3:
        p->mWin[4] = p->mLow;
        for (i = 1; i <= 4; i++) {
            const float ph = (float)i * PI;
            p->mWin[4 - i] = (float)(MixSinPoly(p->mLow * ph) / ph);
        }
        break;
    case 4:
        p->mWin[4] = p->mHigh - p->mLow;
        for (i = 1; i <= 4; i++) {
            const float ph = (float)i * PI;
            const float s = (float)(MixSinPoly((p->mHigh - p->mLow) * ph * 0.5f) / ph);
            const float v = s * (float)MixCosPoly((p->mHigh + p->mLow) * ph * 0.5f);
            p->mWin[4 - i] = v + v;
        }
        break;
    }

    float sum = 0.0f;
    for (i = 0; i < 5; i++) {
        if (type == 2 || type == 4) {
            const float v = p->mWin[i] * (0.54f - 0.46f * MixCosPoly((float)i * PI_4));
            p->mWin[i] = v;
            if (i & 1) sum -= v; else sum += v;
        }
        else if (type == 3) {
            const float v = -(p->mWin[i] * (0.54f - 0.46f * MixCosPoly((float)i * PI_4)));
            p->mWin[i] = v;
            if (i & 1) sum -= v; else sum += v;
        }
    }

    if (type == 3) {
        p->mWin[4] = p->mWin[4] + 1.0f;
        sum = sum + 1.0f;
    }

    sum = sum * 2.0f - p->mWin[4];
    if (sum < 0.0f) sum = -sum;
    const float g = 1.0f / sum;
    p->mWin[0] = p->mWin[0] * g;
    p->mWin[1] = p->mWin[1] * g;
    p->mWin[2] = p->mWin[2] * g;
    p->mWin[3] = p->mWin[3] * g;
    p->mWin[4] = p->mWin[4] * g;
}

// ---------------------------------------------------------------- 0x01173730
// @ 0x01173730
void OnePole(float* state, int n, const float* in, float* out)
{
    float y = state[0] * state[1];
    for (int i = 0; i < n; i++) {
        y = state[2] * in[i] + y;
        out[i] = y;
    }
    state[0] = y;
}

// ---------------------------------------------------------------- 0x01173770
// @ 0x01173770
void Interpolate(int n, const float* in, float* out, int* pos, unsigned* frac,
                 int stepLo, int stepHi)
{
    const unsigned step = ((unsigned)stepLo << 16) | ((unsigned)stepHi >> 16);
    *frac = *frac >> 16;
    for (int i = 0; i < n; i++) {
        const float t = (float)*frac * (1.0f / 65536.0f);
        const int idx = *pos;
        const float a = in[idx];
        const float b = in[idx + 1];
        const float c = in[idx - 1];
        const float d = in[idx + 2];
        const float t2 = t * t;
        const float t3 = t2 * t;
        out[i] = ((a - b) * 3.0f - c + d) * 0.5f * t3
               + ((c + b * 2.0f) - (a * 5.0f + d) * 0.5f) * t2
               + (b - c) * 0.5f * t
               + a;
        *frac += step;
        *pos += *frac >> 16;
        *(unsigned short*)((char*)frac + 2) = 0;
    }
    *frac = *frac << 16;
}
