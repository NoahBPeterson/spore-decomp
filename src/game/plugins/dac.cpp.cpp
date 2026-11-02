// src/game/plugins/dac.cpp.cpp -- migrated from slice(s) s0113cea0, s0113baf0 by tools/migrate/rewrite.py
// Object file: plugins/dac.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s0113baf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Ctx {
    uint8_t b[0x800];

    // callees (other TUs) — declared, mapped by address
    void     PlugInInit16();                 // 0x114f4f0  PlugIn::Initialize<Pan3D>
    void     InitSndPlayer1();               // 0x112dbb0  PlugIn::Initialize<SndPlayer1>
    void*    SysAlloc(uint32_t, const char*, int, int); // 0x112c820 System::Alloc
    bool     AddTimer(void*, void*, void*, const char*, int, int); // 0x112d8e0
    void     RemoveTimer(void*);             // 0x112dad0
    void     SysLock();                      // 0x112c600
    void     SysUnlock();                    // 0x112c620
    uint32_t SysGetDec();                    // 0x112dc80
    void*    RegGet(void*);                  // 0x1133ed0
    void*    DecoderFactory(void*, uint8_t, int, void*); // 0x1133fc0
    uint32_t SubFeed(void*, int, int, int, int, int); // 0x114c8c0
    void     Ctor1153b00();                  // 0x1153b00
    void     Ctor11546f0();                  // 0x11546f0
    void     Ctor11547b0();                  // 0x11547b0
    void     D770();                         // 0x114d770
    void     D730();                         // 0x114d730
    bool     DelayLineInit(int, int, uint32_t); // 0x114d7b0
    void     D840(int);                      // 0x114d840
    void     C1154ee0();                     // 0x1154ee0
    void     C1154ca0(void*);                // 0x1154ca0
    uint64_t Get64();                        // 0x68c140

    // slice functions
    void     FUN_0113bb30();
    bool     FUN_0113bb90(int);
    bool     FUN_0113bc60();
    void     FUN_0113bf10(int, uint32_t*);
    void     FUN_0113ca00(int, uint8_t*);
    void     FUN_0113cb20();
    uint8_t* FUN_0113cbb0(uint8_t);
    bool     FUN_0113cd80(uint8_t*);
    uint8_t* FUN_0113cdd0(uint8_t);
    void     FUN_0113ce00();
};
// ---- items of slice s0113baf0 end

// ---- items of slice s0113cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t  g_16e6306;                  // 0x16e6306  index into g_16e6320
extern void*    g_16e6308[];                // 0x16e6308  [device]
extern float    g_16e6320[];                // 0x16e6320  [rate]
extern uint8_t  g_16e633c;                  // 0x16e633c  number of devices
extern float    g_14c2f6c[];                // 0x14c2f6c  allowed sample rates (22050...)
extern int      g_14c2f88[];                // 0x14c2f88  device ordinal table
extern uint8_t  g_14c2fa0[];                // 0x14c2fa0  [ordinal] -> max channels
extern uint8_t  g_14f8eb4[];                // 0x14f8eb4  DirectSound GUID
extern "C" void* __stdcall GetForegroundWindow();
extern "C" void* __stdcall GetDesktopWindow();
extern "C" int __stdcall DS_Ordinal9(void*, void*);       // DSOUND ordinal 9
extern "C" int __stdcall DS_Ordinal1(void*, void*, int);  // DSOUND ordinal 1
#pragma function(memset)
uint64_t FUN_0113ccf0(uint8_t*);                          // 0x113ccf0
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }
static inline void Release(void* p)
{
    void* vt = *(void**)p;
    void (__stdcall* volatile f)(void*) = (void(__stdcall*)(void*))((void**)vt)[2];
    f(p);
}
struct Ctx_s0113_cea0 {
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
// ---- items of slice s0113cea0 end

// @ 0x0113ccf0
uint64_t FUN_0113ccf0(uint8_t* p)
{
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v = (v << 8) | p[i];
    return v;
}

// @ 0x0113cd80
bool Ctx::FUN_0113cd80(uint8_t* p)
{
    uint64_t a = ((Ctx*)((char*)this + 8))->Get64();
    uint64_t b = FUN_0113ccf0(p);
    return a == b;
}

// @ 0x0113d7b0
void Ctx_s0113_cea0::FUN_0113d7b0()
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
        if (((Ctx_s0113_cea0*)this)->FUN_0113d3a0(mc, 0xac44, 0)) {
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
            if (((Ctx_s0113_cea0*)this)->FUN_0113d3a0(maxCh, (int)rate, 0)) {
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
bool Ctx_s0113_cea0::FUN_0113d930()
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
    if (!((Ctx_s0113_cea0*)W(this, 0x40))->FUN_0113cd80(local_10))
        ((Ctx_s0113_cea0*)this)->FUN_0113d7b0();
    {
        uint64_t v = FUN_0113ccf0(local_10);
        ((Ctx_s0113_cea0*)((char*)W(this, 0x40) + 8))->M68c1b0((uint32_t)v, (uint32_t)(v >> 32));
        ((Ctx_s0113_cea0*)W(this, 0x40))->M11547e0();
    }
    return true;
fail:
    {
        void* p = P(this, 0x48);
        if (p) { Release(p); W(this, 0x48) = 0; }
    }
    return false;
}
