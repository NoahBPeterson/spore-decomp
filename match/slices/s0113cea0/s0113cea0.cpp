// Slice s0113cea0: rw::audio::core Dac (DirectSound output) device management - init, mix
// service, device enumeration, mode switching. VC .NET 2003 (cl 13.10) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <string.h>

// keep memset/memcpy out of line so the imported memset trace matches (0x11e073e/0x11e0744)
#pragma function(memset)

// --- globals referenced by the original ---
extern uint8_t  g_16e6304;                  // 0x16e6304  gain-ramp pending
extern uint8_t  g_16e6305;                  // 0x16e6305  active channel count
extern uint8_t  g_16e6306;                  // 0x16e6306  index into g_16e6320
extern uint8_t  g_16e6307;                  // 0x16e6307  dac running
extern uint8_t* g_16e6300;                  // 0x16e6300  EA::Audio::System* / cblock*
extern void*    g_16e6308[];                // 0x16e6308  [device]
extern float    g_16e6320[];                // 0x16e6320  [rate]
extern uint8_t  g_16e633c;                  // 0x16e633c  number of devices
extern uint32_t g_16e7ba8;                  // 0x16e7ba8
extern uint32_t g_16e7ba4;                  // 0x16e7ba4
extern uint32_t g_16e7b9c;                  // 0x16e7b9c  dac state (0/1/2)
extern float    g_16e6380[];                // 0x16e6380  channel gain matrix
extern float    g_14c2f6c[];                // 0x14c2f6c  allowed sample rates (22050...)
extern int      g_14c2f88[];                // 0x14c2f88  device ordinal table
extern uint8_t  g_14c2fa0[];                // 0x14c2fa0  [ordinal] -> max channels
extern uint8_t  g_14f8eb4[];                // 0x14f8eb4  DirectSound GUID
extern uint8_t  g_16e7ba0[];                // 0x16e7ba0 (object lives at this address)

// --- imports / other-TU helpers ---
extern "C" unsigned int __stdcall timeGetTime();          // winmm!timeGetTime
extern "C" void* __stdcall GetForegroundWindow();
extern "C" void* __stdcall GetDesktopWindow();
extern "C" int __stdcall DS_Ordinal9(void*, void*);       // DSOUND ordinal 9
extern "C" int __stdcall DS_Ordinal1(void*, void*, int);  // DSOUND ordinal 1
void  ReChannelGainWrite(float**, float**, float, unsigned int, unsigned int, int); // 0x112d590
uint64_t FUN_0113ccf0(uint8_t*);                          // 0x113ccf0
void  M1155330(void*, void*, int, int);                   // 0x1155330
void  M11552a0(void*, float, float, int);                 // 0x11552a0
void  M11551d0(void*, void*, int);                        // 0x11551d0
void  M1155110(void*, void*, int);                        // 0x1155110

static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint16_t& W16(void* p, unsigned o) { return *(uint16_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline float&    F(void* p, unsigned o) { return *(float*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }

// COM-style release: (*(void***)p)[2](p), __stdcall, |this| passed explicitly
static inline void Release(void* p)
{
    ((void(__stdcall*)(void*))((void**)p)[2])(p);
}

struct Ctx {
    uint8_t b[0x800];

    // callees (other TUs)
    void M112c560();                          // 0x112c560
    void M112c570();                          // 0x112c570
    void M112c5f0(void*);                     // 0x112c5f0
    void M112c6e0();                          // 0x112c6e0
    void M1154fa0();                          // 0x1154fa0
    void M1154fb0();                          // 0x1154fb0
    void M1154ee0();                          // 0x1154ee0
    void M68c1b0(uint32_t, uint32_t);         // 0x68c1b0
    void M11547e0();                          // 0x11547e0
    void SysFree(void*, int);                 // 0x112c850
    bool FUN_0113cd80(uint8_t*);              // 0x113cd80
    void FUN_0113ce00();                      // 0x113ce00  Dac::Mix

    // slice functions
    void     FUN_0113cea0();
    void     FUN_0113cf20();
    void     FUN_0113cf70();
    void     FUN_0113cff0(void*, int);
    void     FUN_0113d200(int);
    bool     FUN_0113d3a0(int, int, int);
    int      FUN_0113d5d0();
    void     FUN_0113d710();
    void     FUN_0113d7b0();
    bool     FUN_0113d930();
    void     FUN_0113d9f0();
    void     FUN_0113dae0(int);
    void     FUN_0113db70();
};

// @ 0x0113cea0
void Ctx::FUN_0113cea0()
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    ((Ctx*)sys)->M112c560();
    if (g_16e6307 != 0) {
        ((Ctx*)g_16e6300)->M1154fa0();
        g_16e7ba8 = 1;
        ((Ctx*)sys)->M112c6e0();
        if (g_16e6307 != 0) {
            if (g_16e7b9c != 0) {
                ((Ctx*)this)->FUN_0113ce00();
                g_16e7ba4 += (1 - g_16e7ba8);
            }
            ((Ctx*)g_16e6300)->M1154fb0();
        }
    }
    ((Ctx*)sys)->M112c570();
}

// @ 0x0113cf20
void Ctx::FUN_0113cf20()
{
    void* p = P(this, 0x50);
    if (p != 0) {
        Release(p);
        W(this, 0x50) = 0;
    }
    p = P(this, 0x4c);
    if (p != 0) {
        Release(p);
        W(this, 0x4c) = 0;
    }
    p = P(this, 0x48);
    if (p != 0) {
        Release(p);
        W(this, 0x48) = 0;
    }
}

// @ 0x0113cf70
void Ctx::FUN_0113cf70()
{
    void* p = P(this, 0x50);
    if (p != 0) {
        Release(p);
        W(this, 0x50) = 0;
    }
    p = P(this, 0x4c);
    if (p != 0) {
        Release(p);
        W(this, 0x4c) = 0;
    }
    p = P(this, 0x48);
    if (p != 0) {
        Release(p);
        W(this, 0x48) = 0;
    }
    ((Ctx*)((char*)W(this, 0x40) + 8))->M68c1b0(0, 0);
    ((Ctx*)W(this, 0x40))->M11547e0();
    g_16e633c = 0;
    g_16e6306 = 0;
    *(double*)((char*)this + 0x90) = 0.0;
    B(this, 0x9c) = 1;
    W(this, 0x98) = timeGetTime();
}

// @ 0x0113cff0
void Ctx::FUN_0113cff0(void* param_2, int param_3)
{
    if (param_3 == 0) {
        memset(param_2, 0, (uint32_t)B(this, 0x89) << 8);
        return;
    }
    if (g_16e6305 != 6) {
        uint8_t* srcA = (uint8_t*)W((uint8_t*)W(this, 0x24), 0x30010);
        uint8_t* srcB = (uint8_t*)W((uint8_t*)W(this, 0x24), 0x3000c);
        if (srcA == 0) {
            memset(param_2, 0, (uint32_t)B(this, 0x89) << 8);
            return;
        }
        float* local_30[6];
        float* local_18[6];
        for (uint32_t i = 0; i < 6; i++)
            local_30[i] = (float*)(W(srcB, 4) + (uint32_t)W16(srcB, 0xe) * i * 4);
        uint32_t n = g_16e6305;
        for (uint32_t i = 0; i < n; i++)
            local_18[i] = (float*)(W(srcA, 4) + (uint32_t)W16(srcA, 0xe) * i * 4);
        ReChannelGainWrite(local_18, local_30, 1.0f, n, 6, 0x100);
        uint8_t* o = (uint8_t*)W(this, 0x24);
        uint32_t t = W(o, 0x30010);
        W(o, 0x30010) = W(o, 0x3000c);
        W(o, 0x3000c) = t;
    }
    M1155330(g_16e6380, (void*)W((uint8_t*)W(this, 0x24), 0x3000c), g_16e6305, 0x100);
    M11552a0(g_16e6380, -1.0f, 1.0f, (uint32_t)g_16e6305 << 8);
    uint8_t b = g_16e6305;
    if (g_16e6304 != 0) {
        float ramp = 0.0f;
        uint32_t stride = g_16e6305;
        uint8_t* end = (uint8_t*)g_16e6380 + stride * 0x80;
        for (uint8_t* q = (uint8_t*)g_16e6380; q < end; q += stride * 4) {
            for (uint32_t i = 0; i < stride; i++) {
                *(float*)(q + i * 4) = (ramp * 0.0078125f) * *(float*)(q + i * 4);
                b = g_16e6305;
            }
            stride = b;
            ramp += 1.0f;
        }
        g_16e6304 = 0;
    }
    if (B(this, 0x44) != 0)
        M11551d0(param_2, g_16e6380, (uint32_t)b << 8);
    else
        M1155110(param_2, g_16e6380, (uint32_t)b << 8);
}

// @ 0x0113d200
void Ctx::FUN_0113d200(int unused)
{
    if (B(this, 0x9c) != 0)
        return;
    uint8_t* buf = (uint8_t*)P(this, 0x50);
    int local_4 = 0, local_8 = 0;
    int ok = ((int(__stdcall*)(void*, int*, int*))((void**)buf)[4])(buf, &local_4, &local_8);
    if (ok < 0) {
        ((Ctx*)this)->FUN_0113cf70();
        return;
    }
    uint32_t ch = B(this, 0x89);
    uint32_t frames = (uint32_t)local_4 / ch;
    int nBytes = local_8;
    if ((int)W(this, 0x64) + nBytes <= (int)frames)
        nBytes += W(this, 0x60);
    int limit = (int)(F(this, 0x30) * 0.001f) * 0;
    limit = (int)((float)(int)(F(this, 0x30) * 0.001f * 5.0f)) + (int)frames;
    if (limit < nBytes) {
        float target = ((float)(nBytes - (int)frames) / F(this, 0x30)) * 1000.0f;
        if (target < F(this, 0x58))
            F(this, 0x58) = target;
        if (*(double*)((char*)this + 0x80) <= *(double*)((uint8_t*)P(this, 4) + 8)) {
            float t2 = F(this, 0x58);
            *(double*)((char*)this + 0x80) = *(double*)((uint8_t*)P(this, 4) + 8) + 10.0;
            if (t2 <= 10.0f) {
                if (t2 < 5.0f)
                    F(this, 0x54) = (5.0f - t2) + F(this, 0x54);
            } else if (t2 < 500.0f) {
                float v = F(this, 0x54) - (t2 - 5.0f) * 0.5f;
                F(this, 0x54) = v;
                if (v < 25.0f)
                    F(this, 0x54) = 50.0f;
            }
            F(this, 0x58) = 1000.0f;
        }
    } else {
        if (*(double*)((char*)this + 0x70) < *(double*)((uint8_t*)P(this, 4) + 8))
            F(this, 0x54) = F(this, 0x54) * 1.1f;
        F(this, 0x58) = 1000.0f;
        *(double*)((char*)this + 0x80) = *(double*)((uint8_t*)P(this, 4) + 8) + 10.0;
    }
    if (F(this, 0x54) > 200.0f)
        F(this, 0x54) = 200.0f;
}

// @ 0x0113d3a0
bool Ctx::FUN_0113d3a0(int ch, int rate, int is3d)
{
    uint8_t desc[0x24];
    memset(desc, 0, sizeof(desc));
    ((uint32_t*)desc)[0] = 0x24;
    ((uint32_t*)desc)[1] = 1;
    uint8_t* ds = (uint8_t*)P(this, 0x48);
    int r = ((int(__stdcall*)(void*, void*, void*))((void**)ds)[3])(ds, desc, (char*)this + 0x4c);
    if (r < 0)
        goto fail;

    {
        int16_t fmtCh, bits;
        if (is3d == 1) { fmtCh = 4; bits = 0x20; }
        else { fmtCh = 2; bits = 0x10; }
        uint16_t blockAlign = (uint16_t)(fmtCh * ch);
        uint8_t wf[0x28];
        memset(wf, 0, sizeof(wf));
        *(uint16_t*)(wf + 0x00) = 0xfffe;
        *(uint16_t*)(wf + 0x02) = (uint16_t)ch;
        *(uint32_t*)(wf + 0x04) = (uint32_t)rate;
        *(uint32_t*)(wf + 0x08) = (uint32_t)blockAlign * (uint32_t)rate;
        *(uint16_t*)(wf + 0x0c) = blockAlign;
        *(uint16_t*)(wf + 0x0e) = bits;
        *(uint16_t*)(wf + 0x10) = 0x16;
        *(uint16_t*)(wf + 0x12) = (uint16_t)(fmtCh * ch);
        *(uint32_t*)(wf + 0x14) = 0x3f;
        *(uint32_t*)(wf + 0x18) = 1;
        *(uint32_t*)(wf + 0x1c) = 0x100000;
        *(uint32_t*)(wf + 0x20) = 0xaa000080;
        *(uint32_t*)(wf + 0x24) = 0x719b3800;
        if (ch == 6) *(uint32_t*)(wf + 0x14) = 0x3f;
        else if (ch == 4) *(uint32_t*)(wf + 0x14) = 0x33;
        else if (ch == 2) *(uint32_t*)(wf + 0x14) = 3;
        else if (ch == 1) *(uint32_t*)(wf + 0x14) = 4;
        if (ch < 3 && is3d == 0) {
            *(uint16_t*)(wf + 0x00) = 1;
            *(uint16_t*)(wf + 0x10) = 0;
        }
        B(this, 0x89) = (uint8_t)blockAlign;
        r = ((int(__stdcall*)(void*, void*))((void**)ds)[0xe])(ds, wf);
        if (r < 0)
            goto fail;

        uint32_t bytes = ((uint32_t)rate * 500 / 1000 + 0xff) & ~0xffu;
        W(this, 0x64) = bytes >> 1;
        W(this, 0x60) = bytes;
        uint8_t desc2[0x24];
        memset(desc2, 0, sizeof(desc2));
        *(uint32_t*)(desc2 + 0x00) = 0x24;
        *(uint32_t*)(desc2 + 0x04) = 0x18000;
        *(uint32_t*)(desc2 + 0x10) = (uint32_t)wf;
        r = ((int(__stdcall*)(void*, void*, void*, int))((void**)ds)[3])(ds, desc2, (char*)this + 0x50, 0);
        if (r < 0)
            goto fail;
    }
    return true;

fail:
    {
        void* p = P(this, 0x50);
        if (p != 0) { Release(p); W(this, 0x50) = 0; }
        p = P(this, 0x4c);
        if (p != 0) { Release(p); W(this, 0x4c) = 0; }
    }
    return false;
}

// @ 0x0113d5d0
int Ctx::FUN_0113d5d0()
{
    if (g_16e7b9c == 0)
        return 0;
    if (B(this, 0x9c) == 0) {
        uint8_t* buf = (uint8_t*)P(this, 0x50);
        int local_8 = 0;
        uint32_t local_c = 0;
        int ok = ((int(__stdcall*)(void*, int*, uint32_t*))((void**)buf)[4])(buf, &local_8, &local_c);
        if (ok >= 0) {
            uint32_t ch = B(this, 0x89);
            int total = W(this, 0x60);
            uint32_t target = (uint32_t)((int)(F(this, 0x54) * 0.001f * F(this, 0x30)) + 0xff
                                         + (int)((uint32_t)local_8 / ch)) & ~0xffu;
            if ((int)target >= total)
                target -= total;
            int delta = (int)target - (int)W(this, 0x5c);
            int half = (int)W(this, 0x64);
            if (delta < 0) {
                if (delta <= -half || delta > half)
                    delta = 0;
                else if (delta < 0)
                    delta = total - (int)W(this, 0x5c) + (int)target;
            } else if (delta > half) {
                delta = 0;
            }
            int off = (int)W(this, 0x5c) - (int)(local_c / ch);
            if (off < 0)
                off += total;
            F(this, 0x38) = (float)off / F((uint8_t*)P(this, 4), 0xc0);
            return delta;
        }
        ((Ctx*)this)->FUN_0113cf70();
    }
    {
        uint32_t dt = timeGetTime() - W(this, 0x98);
        double f = (double)(int)dt;
        if ((int)dt < 0)
            f += 4294967296.0;
        f = (f * (double)F((uint8_t*)P(this, 4), 0xc0)) * 0.001 - *(double*)((char*)this + 0x90);
        int r = (int)f;
        if (r < 0 || r < 0x100)
            return 0;
        return r & ~0xff;
    }
}

// @ 0x0113d710
void Ctx::FUN_0113d710()
{
    if (g_16e7b9c != 0) {
        if (g_16e7b9c == 1)
            ((Ctx*)this)->FUN_0113cf20();
        g_16e7b9c = 0;
    }
    g_16e6307 = 0;
    uint32_t tmp = 0;
    ((Ctx*)P(this, 4))->M112c5f0(&tmp);
    uint32_t p = W(this, 0x24);
    if (p != 0)
        ((Ctx*)P(this, 4))->SysFree((void*)p, 0);
}

// @ 0x0113d770
int FUN_0113d770(uint32_t* rec)
{
    if (g_16e7b9c != 0) {
        if (g_16e7b9c == 1)
            ((Ctx*)P(rec, 4))->FUN_0113cf20();
        g_16e7b9c = 0;
        ((Ctx*)(void*)g_16e7ba0)->M1154ee0();
    }
    return 8;
}

// @ 0x0113d7b0
void Ctx::FUN_0113d7b0()
{
    uint8_t desc[0x60];
    memset(desc, 0, sizeof(desc));
    ((uint32_t*)desc)[0] = 0x60;
    uint8_t* buf = (uint8_t*)P(this, 0x48);
    int r = ((int(__stdcall*)(void*, void*))((void**)buf)[4])(buf, desc);
    g_16e633c = 0;
    if (r < 0) {
        g_16e6306 = 0;
        B(this, 0x44) = 0;
        return;
    }
    uint8_t maxCh = 0;
    for (int i = 0; i < 6; i++) {
        int ord = g_14c2f88[i];
        uint8_t mc = g_14c2fa0[ord];
        if (((Ctx*)this)->FUN_0113d3a0(mc, 0xac44, 0)) {
            if (maxCh < mc) maxCh = mc;
            uint32_t idx = g_16e633c++;
            g_16e6308[idx] = (void*)ord;
            void* p = P(this, 0x50);
            if (p) { Release(p); W(this, 0x50) = 0; }
            p = P(this, 0x4c);
            if (p) { Release(p); W(this, 0x4c) = 0; }
        }
    }
    float lo = (float)(int)((uint32_t*)desc)[1];
    float hi = (float)(int)((uint32_t*)desc)[2];
    g_16e6306 = 0;
    for (int i = 0; i < 7; i++) {
        float rate = g_14c2f6c[i];
        if (!(rate < lo) && !(hi < rate)) {
            if (((Ctx*)this)->FUN_0113d3a0(maxCh, (int)rate, 0)) {
                uint32_t idx = g_16e6306++;
                g_16e6320[idx] = rate;
                void* p = P(this, 0x50);
                if (p) { Release(p); W(this, 0x50) = 0; }
                p = P(this, 0x4c);
                if (p) { Release(p); W(this, 0x4c) = 0; }
            }
        }
    }
    B(this, 0x44) = 0;
}

// @ 0x0113d930
bool Ctx::FUN_0113d930()
{
    uint8_t local_10[16];
    if (DS_Ordinal9(g_14f8eb4, local_10) < 0)
        goto fail;
    if (DS_Ordinal1(local_10, (char*)this + 0x48, 0) < 0) {
        W(this, 0x48) = 0;
        goto fail;
    }
    {
        uint8_t* ds = (uint8_t*)W(this, 0x48);
        void* hwnd = GetForegroundWindow();
        if (hwnd == 0)
            hwnd = GetDesktopWindow();
        if (((int(__stdcall*)(void*, void*, int))((void**)ds)[6])(ds, hwnd, 2) < 0)
            goto fail;
    }
    if (!((Ctx*)W(this, 0x40))->FUN_0113cd80(local_10))
        ((Ctx*)this)->FUN_0113d7b0();
    {
        uint64_t v = FUN_0113ccf0(local_10);
        ((Ctx*)((char*)W(this, 0x40) + 8))->M68c1b0((uint32_t)v, (uint32_t)(v >> 32));
        ((Ctx*)W(this, 0x40))->M11547e0();
    }
    return true;
fail:
    {
        void* p = P(this, 0x48);
        if (p) { Release(p); W(this, 0x48) = 0; }
    }
    return false;
}

// @ 0x0113d9f0
void Ctx::FUN_0113d9f0()
{
    if (!((Ctx*)this)->FUN_0113d930() || g_16e633c == 0)
        goto fail;
    if (!((Ctx*)this)->FUN_0113d3a0(g_16e6305, (int)F(this, 0x30), B(this, 0x44) != 0))
        goto fail;
    {
        uint8_t* buf = (uint8_t*)P(this, 0x50);
        uint32_t size = (uint32_t)B(this, 0x89) * W(this, 0x60);
        uint32_t local_c = 0, local_8 = 0;
        int r = ((int(__stdcall*)(void*, int, uint32_t, uint32_t*, uint32_t*, int, int, int))
                 ((void**)buf)[0xb])(buf, 0, size, &local_c, &local_8, 0, 0, 0);
        if (r < 0) goto fail;
        memset((void*)local_c, 0, size);
        r = ((int(__stdcall*)(void*, uint32_t, uint32_t, int, int))((void**)buf)[0x13])
            (buf, local_c, size, 0, 0);
        if (r < 0) goto fail;
        r = ((int(__stdcall*)(void*, int, int, int))((void**)buf)[0xc])(buf, 0, 0, 1);
        if (r < 0) goto fail;
        B(this, 0x9c) = 0;
        return;
    }
fail:
    ((Ctx*)this)->FUN_0113cf70();
}

// @ 0x0113dae0
void Ctx::FUN_0113dae0(int param_2)
{
    if (g_16e7b9c == 2)
        return;
    if (g_16e7b9c == 1 && B(this, 0x9c) == 0)
        return;
    g_16e6304 = 1;
    W(this, 0x5c) = 0;
    F(this, 0x58) = 1000.0f;
    *(double*)((char*)this + 0x80) = *(double*)((uint8_t*)P(this, 4) + 8) + 10.0;
    W(this, 0x68) = 5;
    *(double*)((char*)this + 0x70) = *(double*)((uint8_t*)P(this, 4) + 8) + 1.0;
    if (param_2 == 0) {
        ((Ctx*)this)->FUN_0113d9f0();
        g_16e7b9c = 1;
    } else if (param_2 == 1) {
        g_16e7b9c = 2;
    }
}

// @ 0x0113db70
void Ctx::FUN_0113db70()
{
    uint32_t state = g_16e7b9c;
    if (state == 0)
        return;
    if (state == 1)
        ((Ctx*)this)->FUN_0113cf20();
    g_16e7b9c = 0;
    if (state == 1) {
        ((Ctx*)this)->FUN_0113dae0(0);
        return;
    }
    if (state == 2) {
        g_16e6304 = 1;
        W(this, 0x5c) = 0;
        F(this, 0x58) = 1000.0f;
        *(double*)((char*)this + 0x80) = *(double*)((uint8_t*)P(this, 4) + 8) + 10.0;
        W(this, 0x68) = 5;
        *(double*)((char*)this + 0x70) = *(double*)((uint8_t*)P(this, 4) + 8) + 1.0;
        g_16e7b9c = state;
    }
}
