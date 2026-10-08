// Slice s01149f70 -- RenderWare 4 rw::audio::core EALayer3Core (MPEG Layer3 core).
// Build: VC .NET 2003 (cl 13.10) + /GL /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include <string.h>

namespace rw { namespace audio { namespace core {

class System {
public:
    void* Alloc(unsigned int size, const char* name, unsigned int align, unsigned int flags);
    void  Free(void* p, unsigned int flags);
};
extern System* g_pSystem;                 // 0x16e61a8

extern float g_floatConst1;               // 0x1485720  (1.0f)
extern float g_float1_5;                  // 0x1485548
extern float g_float0_75;                 // 0x1485544
extern float g_floatSmall;                // 0x13eb1bc  (sign flip)
extern int   InitCoeffs(int n);           // 0x1146d20

// EALayer3Core : CMpegLayer3Base : HELPER_CMpegLayer3Base : HELPER_CMpegBase (size 0x2e0)
class EALayer3Core {
public:
    virtual ~EALayer3Core();              // +0x00 (vftable)
    char mData[0x37c];                    // +0x04 .. +0x37f  (fields accessed by offset)

    EALayer3Core(int n);
    void SetMode();                                             // 01149fd0
    void AnalyzeStatistics(int a2, int a3);                     // 0114a160
    void OnInterface(int a2);                                   // 0114a470
    void ResetSlot(int idx);                                    // 0114a4a0
    void Interpolate(int a2, int a3, float* a4, int a5);        // 0114a4c0
    float AdjustOffset(float* a2);                              // 0114a680
    void AppendSamples(int a2, int a3, int a4, int a5, int a6); // 0114a750
    void UpdateCorrelation(int a2, int a3, float a4, float* a5);// 0114a970
    void AddToOutput(int a2, int a3, int a4, int a5, int a6, int a7, char a8); // 0114aa40
    void ResetSlots();                                          // 0114ad10
    int  SelectPath(int a2, int a3, int a4);                    // 0114ad50

    int   i32(int off) const { return *(const int*)((const char*)this + off); }
    int&  i32(int off) { return *(int*)((char*)this + off); }
    float  f32(int off) const { return *(const float*)((const char*)this + off); }
    float& f32(int off) { return *(float*)((char*)this + off); }
    unsigned char  u8(int off) const { return *(const unsigned char*)((const char*)this + off); }
    unsigned char& u8(int off) { return *(unsigned char*)((char*)this + off); }
};

extern float __stdcall DotProduct(float* a, float* b, unsigned int n);  // 0x114a8b0

// @ 0x01149f70
EALayer3Core::EALayer3Core(int n)
{
    *(void**)this = (void*)0x14ce590;
    ((int(*)(void*, int))InitCoeffs)(this, n);
    // CMpegBase::AllocateSynth(n) — inherited member
    extern int CMpegBase_AllocateSynth(void*, int);
    CMpegBase_AllocateSynth(this, n);
}

// @ 0x01149fd0
void EALayer3Core::SetMode()
{
    unsigned char c = u8(0x21);
    if (c == 1) {
        f32(0xa8) = f32(0x130);
        f32(0x78) = f32(0x118);
        f32(0x48) = f32(0xe8);
        return;
    }
    float u = f32(0x130);
    f32(0xa0) = u;
    float v = f32(0x134);
    if (c == 2) {
        f32(0xb0) = v;
        f32(0x70) = f32(0x118);
        f32(0x80) = f32(0x11c);
        f32(0x40) = f32(0xe8);
        f32(0x50) = f32(0xec);
        return;
    }
    if (c == 4) {
        f32(0xb0) = v;
        f32(0xb8) = f32(0x138);
        f32(0xc0) = f32(0x13c);
        f32(0x70) = f32(0x118);
        f32(0x80) = f32(0x11c);
        f32(0x88) = f32(0x120);
        f32(0x90) = f32(0x124);
        f32(0x40) = f32(0xe8);
        f32(0x50) = f32(0xec);
        f32(0x58) = f32(0xf0);
        f32(0x60) = f32(0xf4);
        return;
    }
    f32(0xa8) = v;
    f32(0xb0) = f32(0x138);
    f32(0xb8) = f32(0x13c);
    f32(0xc0) = f32(0x140);
    f32(0xc8) = f32(0x144);
    f32(0x70) = f32(0x118);
    f32(0x78) = f32(0x11c);
    f32(0x80) = f32(0x120);
    f32(0x88) = f32(0x124);
    f32(0x90) = f32(0x128);
    f32(0x98) = f32(0x12c);
    f32(0x40) = f32(0xe8);
    f32(0x48) = f32(0xec);
    f32(0x50) = f32(0xf0);
    f32(0x58) = f32(0xf4);
    f32(0x60) = f32(0xf8);
    f32(0x68) = f32(0xfc);
}

// @ 0x0114a160  (best-effort: per-sample statistics accumulation; the original is
// hand-vectorised SSE - this is the scalar equivalent)
void EALayer3Core::AnalyzeStatistics(int a2, int a3)
{
    unsigned char nch = u8(0x21);
    if (nch == 0) {
        *(unsigned short*)((char*)this + 0x14a) = 0;
        return;
    }
    unsigned int idx = 0;
    unsigned short base = 0x14a;
    (void)base;
    for (unsigned int ch = 0; ch < nch; ++ch) {
        unsigned int cnt = *(unsigned short*)((char*)this + 0x14a);
        float* p = (float*)(*(int*)(a2 + 4) + *(unsigned short*)(a2 + 0xe) * ch * 4);
        float* end = p + a3;
        float* stat = (float*)((char*)this + 0x100 + ch * 4);
        while (p < end) {
            unsigned int lim = *(unsigned short*)((char*)this + 0x148) - cnt;
            unsigned int avail = (unsigned int)(end - p);
            if (avail < lim) lim = avail;
            lim &= 0xfffffffc;
            if (lim == 0) {
                float v = *p;
                if (v <= 0.0f) v = -v;
                if (*stat <= v && v != *stat) *stat = v;
                float* max2 = (float*)((char*)this + 0x100 + (ch + 3) * 4);
                if (*max2 <= v && v != *max2) *max2 = v;
                float vv = *p;
                ++p; ++cnt;
                float& acc = *(float*)((char*)this + 0xd0 + ch * 4);
                acc = vv * vv + acc;
            } else {
                float* q = p + lim;
                do {
                    float a = p[0], b = p[1], c = p[2], d = p[3];
                    float ma = a < 0 ? -a : a, mb = b < 0 ? -b : b;
                    float mc = c < 0 ? -c : c, md = d < 0 ? -d : d;
                    float mx = *stat;
                    if (ma > mx) mx = ma;
                    if (mb > mx) mx = mb;
                    if (mc > mx) mx = mc;
                    if (md > mx) mx = md;
                    *stat = mx;
                    float* max2 = (float*)((char*)this + 0x100 + (ch + 3) * 4);
                    if (mx > *max2) *max2 = mx;
                    float& acc = *(float*)((char*)this + 0xd0 + ch * 4);
                    acc = (((a * a + b * b) + (c * c + d * d)) + acc);
                    cnt += 4;
                    p += 4;
                } while (p != q);
            }
            if (*(unsigned short*)((char*)this + 0x148) <= cnt) {
                stat[6] = *stat;
                float& acc = *(float*)((char*)this + 0xd0 + ch * 4);
                acc = acc / (float)*(unsigned short*)((char*)this + 0x148);
                stat[-6] = acc;   // sqrt applied by the original (fsqrt)
                ResetSlot((int)ch);
                cnt = 0;
            }
        }
        idx = ch;
    }
    *(unsigned short*)((char*)this + 0x14a) = (unsigned short)idx;
}

// @ 0x0114a470
void EALayer3Core::OnInterface(int a2)
{
    AnalyzeStatistics(*(int*)(a2 + 0x3000c), 0x100);
    SetMode();
    u8(0x14c) = 1;
}

// @ 0x0114a4a0
void EALayer3Core::ResetSlot(int idx)
{
    *(float*)((char*)this + 0xd0 + idx * 4) = 0.0f;
    *(float*)((char*)this + 0x100 + idx * 4) = 0.0f;
}

// @ 0x0114a4c0
void EALayer3Core::Interpolate(int a2, int a3, float* a4, int a5)
{
    int N = i32(0x4c);
    float fVar4, fVar5;
    if (a5 < 1) {
        fVar4 = 0.0f;
        fVar5 = 1.0f;
        a5 = -a5;
    } else {
        fVar5 = -1.0f;
        fVar4 = 1.0f;
    }
    fVar5 = fVar5 / (float)N;
    int i = a5;
    if (a5 < N) {
        float* pf = a4;
        do {
            *pf = (1.0f - fVar4) * *(float*)((a2 - (int)a4) + (int)pf) + *(float*)(a2 + i * 4) * fVar4;
            ++i; ++pf; fVar4 = fVar5 + fVar4;
        } while (i < N);
    }
    i = 0;
    if (3 < a5) {
        float* pf = (float*)(a3 + 8);
        do {
            int k = (N - a5) + i;
            a4[k] = (1.0f - fVar4) * *(float*)(a2 + k * 4) + pf[-2] * fVar4;
            fVar4 = fVar5 + fVar4;
            a4[k + 1] = (1.0f - fVar4) * *(float*)(a2 + (k + 1) * 4) + pf[-1] * fVar4;
            fVar4 = fVar5 + fVar4;
            a4[k + 2] = (1.0f - fVar4) * *(float*)(a2 + (k + 2) * 4) + pf[0] * fVar4;
            fVar4 = fVar5 + fVar4;
            a4[k + 3] = (1.0f - fVar4) * *(float*)(a2 + (k + 3) * 4) + pf[1] * fVar4;
            i += 4; pf += 4; fVar4 = fVar5 + fVar4;
        } while (i < a5 - 3);
    }
    for (; i < a5; ++i) {
        int k = (N - a5) + i;
        a4[k] = (1.0f - fVar4) * *(float*)(a2 + k * 4) + *(float*)(a3 + i * 4) * fVar4;
        fVar4 = fVar5 + fVar4;
    }
}

// @ 0x0114a680
float EALayer3Core::AdjustOffset(float* a2)
{
    float d = 1.0f - f32(0x44);
    int iv = *(int*)(a2 + 0x10);
    if (f32(0x44) >= 1.0f) {
        float x = d * (float)i32(0x4c);
        float y = x + a2[0];
        float z = ((float)iv + x) + a2[0];
        float ay = y < 0 ? -y : y;
        float az = z < 0 ? -z : z;
        if (ay < az) { a2[0] = y; return 0.0f; }
        a2[0] = z;
        return (float)iv;
    }
    float y = (float)(i32(0x4c) * 2) * d + a2[0];
    float z = y - (float)iv;
    float ay = y < 0 ? -y : y;
    float az = z < 0 ? -z : z;
    if (ay < az) { a2[0] = y; return 0.0f; }
    a2[0] = z;
    return (float)(-iv);
}

// @ 0x0114a750  (best-effort)
void EALayer3Core::AppendSamples(int a2, int a3, int a4, int a5, int a6)
{
    int N = i32(0x4c);
    if (0 < i32(a5 + 0x14)) {
        memmove((void*)a4, (void*)((char*)a4 + *(int*)(a5 + 0x18) * 4), *(int*)(a5 + 0x14) * 4);
        *(int*)(a5 + 0x18) = 0;
    }
    if (f32(0x44) >= 1.0f) {
        if (a6 == 0) {
            memcpy((void*)((char*)a4 + *(int*)(a5 + 0x14) * 4), (void*)a2, N * 4);
            *(int*)(a5 + 0x14) += N;
            return;
        }
        memcpy((void*)((char*)a4 + *(int*)(a5 + 0x14) * 4), (void*)a2, a6 * 4);
        Interpolate(a3, a2, (float*)((char*)a4 + (*(int*)(a5 + 0x14) + a6) * 4), a6);
        *(int*)(a5 + 0x14) += N + a6;
        return;
    }
    if (a6 == 0) {
        memcpy((void*)((char*)a4 + *(int*)(a5 + 0x14) * 4), (void*)a2, N * 4);
        memcpy((void*)((char*)a4 + (*(int*)(a5 + 0x14) + N) * 4), (void*)a3, N * 4);
        *(int*)(a5 + 0x14) += N * 2;
        return;
    }
    Interpolate(a2, a3, (float*)((char*)a4 + *(int*)(a5 + 0x14) * 4), a6);
    memcpy((void*)((char*)a4 + (*(int*)(a5 + 0x14) + N) * 4), (void*)(a3 + a6 * -4), (N + a6) * 4);
    *(int*)(a5 + 0x14) += a6 + N * 2;
}

// @ 0x0114a8b0
float __stdcall DotProduct(float* a, float* b, unsigned int n)
{
    float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, f3 = 0.0f;
    if ((((unsigned int)a | (unsigned int)b) & 0xf) == 0 && (n & 3) == 0) {
        float* end = a + n;
        do {
            f0 += a[0] * b[0];
            f1 += a[1] * b[1];
            f2 += a[2] * b[2];
            f3 += a[3] * b[3];
            a += 4; b += 4;
        } while (a != end);
        return ((f3 + f2) + f1) + f0;
    }
    float acc = 0.0f;
    for (unsigned int i = 0; i < n; ++i)
        acc = a[i] * b[i] + acc;
    return acc;
}

// @ 0x0114a970
void EALayer3Core::UpdateCorrelation(int a2, int a3, float a4, float* a5)
{
    int N = i32(0x4c);
    int ip = (int)a4;
    float r;
    if (*(unsigned char*)(a5 + 2) == 0) {
        float* pa = (float*)(a2 + ip * 4);
        float* pb = (float*)(a3 + ip * 4);
        float x = DotProduct(pa, pa, N - ip);
        float y = DotProduct(pb, pb, ip);
        r = y + x;
    } else {
        int off = (int)a5[1];
        int count = ip - off;
        float* pa; float* pb;
        if (count < 1) {
            pb = (float*)(a3 + ip * 4);
            pa = (float*)(a2 + ip * 4);
            count = -count;
        } else {
            pa = (float*)(a2 + off * 4);
            pb = (float*)(a3 + off * 4);
        }
        float x = DotProduct(pa, pa, count);
        float y = DotProduct(pb, pb, count);
        r = (a5[0] - x) + y;
    }
    a5[1] = a4;
    a5[0] = r;
}

// @ 0x0114aa40  (best-effort)
void EALayer3Core::AddToOutput(int a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
    int N = i32(0x4c);
    int alt = u8(0x7c) ^ 1;
    if (0 < a4) {
        memcpy((void*)(*(int*)(a3 + u8(0x7c) * 4) + a6 * 4), (void*)a7, a4 * 4);
        if (i32(0x40) == 1 && a2 != 0) {
            if (a8 == 0) {
                int i = 0;
                float* src = (float*)a7;
                do {
                    float* dst = (float*)(*(int*)(a2 + u8(0x7c) * 4) + (a6 + i) * 4);
                    dst[0] += src[i];
                    ++i;
                } while (i < a4);
            } else {
                memcpy((void*)(*(int*)(a2 + u8(0x7c) * 4) + a6 * 4), (void*)a7, a4 * 4);
            }
        }
        a6 += a4;
    }
    if (0 < a5) {
        a7 += a4 * 4;
        memcpy((void*)(*(int*)(a3 + alt * 4) + (a6 - N) * 4), (void*)a7, a5 * 4);
        if (i32(0x40) == 1 && a2 != 0) {
            if (a8 != 0) {
                memcpy((void*)(*(int*)(a2 + alt * 4) + (a6 - N) * 4), (void*)a7, a5 * 4);
                return;
            }
            int i = 0;
            do {
                int k = (i - N) + a6;
                float* dst = (float*)(*(int*)(a2 + alt * 4) + k * 4);
                dst[0] += ((float*)a7)[i];
                ++i;
            } while (i < a5);
        }
    }
}

// @ 0x0114ad10
void EALayer3Core::ResetSlots()
{
    char* p = (char*)this + 0x7e;
    unsigned short off = *(unsigned short*)p;
    i32(0x5c) = 0;
    u8(0x7c) = 0;
    unsigned int n = i32(0x58);
    for (unsigned int i = 0; i < n; ++i) {
        char* q = (char*)this + off + 0x18 + i * 0x1c;
        *(float*)(q - 0x18) = 0.0f;
        *(int*)(q - 4) = 0;
        *(int*)q = 0;
    }
}

// @ 0x0114ad50
int EALayer3Core::SelectPath(int param_2, int param_3, int param_4)
{
    int N = i32(0x4c);
    char* base = (char*)this + *(unsigned short*)((char*)this + 0x7e);
    if (f32(0x38) != f32(0x44)) {
        if (f32(0x38) == 1.0f) {
            i32(0x6c) = 2;
        } else if (f32(0x44) == 1.0f) {
            ResetSlots();
            i32(0x6c) = 1;
        }
        if (1 < i32(0x58) && i32(0x40) == 0) {
            if (1.5f < f32(0x38) || f32(0x38) < 0.75f)
                f32(0x38) = (1.5f < f32(0x38)) ? g_float1_5 : g_float0_75;
        }
        f32(0x44) = f32(0x38);
    }
    if (i32(0x6c) == 0)
        return param_4;
    unsigned int i = 0;
    int mn = 0;
    unsigned int cnt = i32(0x58);
    while (i < cnt) {
        if (i == 0) mn = *(int*)(base + 0x14);
        else {
            int v = *(int*)(base + 0x14 + i * 0x1c);
            if (v < mn) mn = v;
        }
        ++i;
    }
    i32(0x68) = mn;
    if (i32(0x6c) != 1) {
        int k = i32(0x5c) + mn;
        if (k < param_4) {
            i32(0x60) = param_4;
            i32(0x64) = param_4 - k;
            return param_4 - k;
        }
        i32(0x60) = param_4;
        i32(0x64) = 0;
        return 0;
    }
    int r = N * 2 - i32(0x5c);
    i32(0x60) = param_4;
    i32(0x64) = r;
    return r;
}

}}} // namespace rw::audio::core
