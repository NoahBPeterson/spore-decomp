// src/game/plugins/delay.cpp.cpp -- migrated from slice(s) s0113baf0 by tools/migrate/rewrite.py
// Object file: plugins/delay.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t  g_vtbl_014c258c[];          // 0x14c258c  Delay vtable
extern uint8_t* g_sys;                      // 0x16e61a8  rw::audio::core::System* singleton
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s0113baf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t  g_vtbl_014c258c[];          // 0x14c258c  Delay vtable
extern uint8_t* g_sys;                      // 0x16e61a8  rw::audio::core::System* singleton
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline float&    F(void* p, unsigned o) { return *(float*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }
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

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_0113cb50(uint8_t* p);  // 0x0113cb50 (stays in the slice: not this object's)

// @ 0x0113cbf0
bool FUN_0113cbf0(uint8_t* p, float* params)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014c258c;
        ((Ctx*)(p + 0x44))->Ctor11546f0();
        ((Ctx*)(p + 0x5c))->D730();
        ((Ctx*)(p + 0x98))->InitSndPlayer1();
    }
    F(p, 0x28) = 0.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    B(p, 0xb0) = 0;
    F(p, 0x30) = 0.0f;
    F(p, 0x3c) = F(g_sys, 0xc0);
    W(p, 0x38) = 0;
    F(p, 0x40) = 0.0f;
    if (params != 0)
        F(p, 0x40) = F(params, 0);
    uint32_t delaySamples = (uint32_t)_mm_cvtt_ss2si(_mm_set_ss(F(p, 0x40) * F(p, 0x3c)));
    bool ok = ((Ctx*)(p + 0x5c))->DelayLineInit(B(p, 0x20), (int)delaySamples, W(p, 0x4c));
    if (ok) {
        bool r = ((Ctx*)((char*)P(p, 4) + 0x60))->AddTimer((void*)(p + 0x98), (void*)&FUN_0113cb50,
                                                            p, "Delay", 1, 1);
        if (!r) {
            B(p, 0xb0) = 1;
            return true;
        }
    }
    return false;
}
