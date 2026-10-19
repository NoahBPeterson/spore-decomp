// src/game/plugins/packetplayer.cpp.cpp -- migrated from slice(s) s0113baf0 by tools/migrate/rewrite.py
// Object file: plugins/packetplayer.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t  g_vtbl_014bb50c[];          // 0x14bb50c  PacketPlayer vtable
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s0113baf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t  g_vtbl_014bb50c[];          // 0x14bb50c  PacketPlayer vtable
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint16_t& W16(void* p, unsigned o) { return *(uint16_t*)((char*)p + o); }
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

// @ 0x0113bb30
void Ctx::FUN_0113bb30()
{
    uint8_t* pc = (uint8_t*)this + 0x55;
    int n = 0x14;
    do {
        if (*pc == 2) {
            uint8_t* dec = (uint8_t*)W(this, 0x148);
            uint32_t base = W(dec, 0x24);
            uint8_t ch = pc[-1];
            uint32_t off = base + (uint32_t)ch * 0x14;
            uint32_t v = W(dec + off, 0xc);
            if (v != 0) {
                uint32_t sub;
                if (ch == B(dec, 0x31))
                    sub = W(dec, 0x1c);
                else
                    sub = W(dec + off + 8, 0);
                if (v == sub) {
                    *pc = 0;
                    W(pc - 9, 0) = 0;
                }
            } else {
                *pc = 0;
                W(pc - 9, 0) = 0;
            }
        }
        pc += 0xc;
    } while (--n != 0);
}

// @ 0x0113bb90
bool Ctx::FUN_0113bb90(int param_2)
{
    bool result = false;
    if (W(this, 0x140) == 0)
        return false;
    for (;;) {
        uint8_t bl = B(this, 0x167);
        if (*(uint8_t*)((char*)this + 0x55 + (uint32_t)bl * 0xc) != 0)
            return result;
        uint8_t cur = bl;
        bl = (uint8_t)((bl + 1 == 0x14) ? 0 : bl + 1);
        B(this, 0x167) = bl;
        uint8_t* node = (uint8_t*)W(this, 0x140);
        uint8_t* got = 0;
        if (node != 0) {
            uint32_t nxt = W(node, 0xc);
            W(this, 0x140) = nxt;
            if (nxt == 0)
                W(this, 0x144) = 0;
            W(node, 0xc) = 0;
            got = node;
        }
        uint8_t* feed = (uint8_t*)P(this, 0x48);
        B(feed, 5) = cur;
        W((char*)this + 0x4c + (uint32_t)cur * 0xc, 0) = (uint32_t)got;
        uint8_t* slot = (uint8_t*)((char*)this + 0x4c + (uint32_t)cur * 0xc);
        W(slot, 4) = 0;
        B(slot, 9) = 1;
        uint8_t ok = (uint8_t)((Ctx*)W(this, 0x148))->SubFeed((void*)W(got, 8), W(got, 0),
                                                              param_2 != 1, 0, 0, 0);
        B(slot, 8) = ok;
        W(feed, 0) += W(got, 0);
        result = true;
        if (W(this, 0x140) == 0)
            return result;
    }
}

// @ 0x0113bd60
void FUN_0113bd60(uint8_t* p)
{
    if (B((uint8_t*)P(p, 8), 0x47) == 2)
        return;
    ((Ctx*)p)->FUN_0113bb30();
    uint8_t st = B(p, 0x152);
    if (st == 4 || st == 0) {
        *(double*)(p + 0x28) = 0.0;
        return;
    }
    *(double*)(p + 0x28) = (double)((float)*(int*)(p + 0x158) / F(p, 0x14c));
    for (;;) {
        uint8_t c = B(p, 0x152);
        if (c == 4 || c == 0)
            return;
        if (*(uint8_t*)((char*)p + 0x55 + (uint32_t)B(p, 0x167) * 0xc) != 0)
            return;
        if (c == 1) {
            if (!((Ctx*)p)->FUN_0113bc60())
                return;
            B(p, 0x152) = 2;
        } else if (c != 2) {
            continue;
        }
        if (*(uint8_t*)((char*)p + 0x55 + (uint32_t)B(p, 0x167) * 0xc) != 0)
            return;
        if (!((Ctx*)p)->FUN_0113bb90(0))
            return;
    }
}

// @ 0x0113be10
bool FUN_0113be10(uint8_t* p)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bb50c;
        ((Ctx*)(p + 0x30))->InitSndPlayer1();
        W(p, 0x140) = 0;
        W(p, 0x144) = 0;
    }
    W(p, 0xc) = (uint32_t)(p + 0x28);
    B(p, 0x169) = 0;
    {
        uint32_t a = ((unsigned)p + 0x177) & ~7u;
        W16(p, 0x162) = (uint16_t)(a - (unsigned)p);
    }
    uint8_t* arr = (uint8_t*)((Ctx*)P(p, 4))->SysAlloc(8, "PacketPlayer RequestExternal array", 0x10, 0);
    W(p, 0x48) = (uint32_t)arr;
    if (arr == 0)
        return false;
    *(double*)(p + 0x28) = 0.0;
    B(p, 0x164) = B(p, 0x21);
    B(p, 0x152) = 0;
    W(p, 0x140) = 0;
    W(p, 0x144) = 0;
    W(p, 0x158) = 0;
    B(p, 0x166) = 0;
    B(p, 0x165) = 0;
    F(p, 0x15c) = F((uint8_t*)P(p, 4), 0xc0);
    B(p, 0x167) = 0;
    B(p, 0x168) = 0;
    for (int i = 0; i < 0x14; i++) {
        B(p + 0x4c + i * 0xc, 9) = 0;
        W(p + 0x4c + i * 0xc, 0) = 0;
    }
    bool r = ((Ctx*)((char*)P(p, 4) + 0x60))->AddTimer((void*)(p + 0x30), (void*)&FUN_0113bd60, p,
                                                       "PacketPlayer", 1, 1);
    if (!r) {
        B(p, 0x169) = 1;
        return true;
    }
    return false;
}
