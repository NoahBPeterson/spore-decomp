// Slice s0113baf0: rw::audio::core PacketPlayer / Pan3D-family / Delay / Dac job handlers,
// queue helpers and constructors. RenderWare 4 core is VC .NET 2003 (cl 13.10) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
//
// Retail layouts differ from the 2008 dev PDB in places, so the plugin objects are addressed
// by the byte offsets that the disassembly shows.
#include "types.h"
#include <string.h>
#include <math.h>

// --- globals referenced by the original (addresses for the equivalence mapper) ---
extern uint8_t  g_vtbl_014bc0fc[];          // 0x14bc0fc  shared base vtable
extern uint8_t  g_vtbl_014bb50c[];          // 0x14bb50c  PacketPlayer vtable
extern uint8_t  g_vtbl_014c258c[];          // 0x14c258c  Delay vtable
extern uint8_t  g_vtbl_014c13b8[];          // 0x14c13b8
extern uint8_t  g_vtbl_014c2fa8[];          // 0x14c2fa8
extern void*    g_tbl_014bb508[];           // 0x14bb508  [channel] -> decoder-name table
extern uint8_t* g_sys;                      // 0x16e61a8  rw::audio::core::System* singleton
extern double   g_16e7b80;                  // 0x16e7b80
extern uint32_t g_16e7b88;                  // 0x16e7b88
extern float    g_16e7b8c;                  // 0x16e7b8c
extern uint16_t g_16e7b90;                  // 0x16e7b90
extern uint8_t  g_16e7b93;                  // 0x16e7b93
extern uint8_t  g_16e7ba0[];                // 0x16e7ba0
extern uint32_t g_16e7ba8;                  // 0x16e7ba8

// free (cdecl) helpers from other TUs
int   Fir64GetSize(int, int);               // 0x1153770  static
void* Fir64Create(void*, int, int, void*);  // 0x1153790  static
int   BwGetSize(int);                        // 0x11538d0  static
void* BwCreate(void*, int, void*);          // 0x11538f0  static
void  op_delete(void*);                      // 0xf47380  operator delete
uint32_t FUN_0113ba40(uint32_t* rec);        // 0x113ba40  RawPuller2 reset handler
void  FUN_0113c620(uint8_t* p, int n);       // 0x113c620  Pan3D-family ctor

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

// @ 0x0113baf0
uint32_t FUN_0113baf0(uint32_t* rec)
{
    uint8_t* self = (uint8_t*)rec[1];
    uint32_t v = rec[2];
    uint32_t* head = (uint32_t*)(self + 0x140);
    if (*head == 0) {
        head[0] = v;
        head[1] = v;
        W((uint8_t*)v, 0xc) = 0;
        return 0xc;
    }
    W((uint8_t*)head[1], 0xc) = v;
    head[1] = v;
    W((uint8_t*)v, 0xc) = 0;
    return 0xc;
}

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
        B(feed, 5) = bl;
        W((char*)this + 0x4c + (uint32_t)bl * 0xc, 0) = (uint32_t)got;
        uint8_t* slot = (uint8_t*)((char*)this + 0x4c + (uint32_t)B(feed, 5) * 0xc);
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

// @ 0x0113bc60
bool Ctx::FUN_0113bc60()
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint8_t* feed = (uint8_t*)P(this, 0x48);
    bool ok = false;
    ((Ctx*)sys)->SysLock();
    uint32_t reg = ((Ctx*)P(this, 4))->SysGetDec();
    void* name = g_tbl_014bb508[B(feed, 4)];
    void* d = ((Ctx*)reg)->RegGet(name);
    void* dec = ((Ctx*)reg)->DecoderFactory(d, B(this, 0x153), 0x14, P(this, 4));
    W(this, 0x148) = (uint32_t)dec;
    if (dec != 0) {
        W16(this, 0x150) = W16(dec, 0x20);
        ((Ctx*)this)->FUN_0113bb90(1);
        ok = true;
    }
    ((Ctx*)sys)->SysUnlock();
    return ok;
}

// @ 0x0113bcf0
uint32_t FUN_0113bcf0(uint32_t* rec)
{
    uint8_t* self = (uint8_t*)rec[1];
    W(self, 0x148) = 0;
    B(self, 0x154) = (uint8_t)(int)F(rec, 8);
    F(self, 0x14c) = F(rec, 0xc);
    B(self, 0x153) = (uint8_t)(int)F(rec, 0x10);
    uint8_t* q = (uint8_t*)P(self, 0x48);
    B(self, 0x152) = 1;
    W(q, 0) = 0;
    B(q, 4) = B(self, 0x154);
    uint8_t st = B(self, 0x152);
    if (st == 4 || st == 0)
        ((Ctx*)self)->FUN_0113bc60();
    return 0x14;
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

// @ 0x0113bf10
void Ctx::FUN_0113bf10(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    if (param_2 == 0) {
        uint8_t* q = (uint8_t*)(W(sys, 0x20) + W(sys, 0xb4));
        W(sys, 0xb4) += 0x14;
        W(q, 0) = (uint32_t)&FUN_0113bcf0;
        W(q, 4) = (uint32_t)this;
        F(q, 8) = ((float*)param_3)[0];
        F(q, 0xc) = ((float*)param_3)[1];
        F(q, 0x10) = ((float*)param_3)[2];
    } else if (param_2 == 1) {
        uint8_t* q = (uint8_t*)(W(sys, 0x20) + W(sys, 0xb4));
        W(sys, 0xb4) += 8;
        W(q, 0) = (uint32_t)&FUN_0113ba40;
        W(q, 4) = (uint32_t)this;
    } else if (param_2 == 2) {
        uint8_t* q = (uint8_t*)(W(sys, 0x20) + W(sys, 0xb4));
        W(sys, 0xb4) += 0xc;
        W(q, 0) = (uint32_t)&FUN_0113baf0;
        W(q, 4) = (uint32_t)this;
        W(q, 8) = param_3[0];
    } else if (param_2 == 3) {
        uint32_t key = param_3[0];
        uint32_t x;
        for (x = W(this, 0x140); x != 0; x = W((uint8_t*)x, 0xc))
            if (x == key) {
                *(float*)(param_3 + 1) = 0.0f;
                return;
            }
        int i = 0;
        for (; i < 0x14; i++)
            if (W((char*)this + 0x4c + i * 0xc, 0) == key)
                break;
        if (i < 0x14)
            *(float*)(param_3 + 1) = (B((char*)this + 0x55 + i * 0xc, 0) == 2) ? 1.0f : 0.0f;
        else
            *(float*)(param_3 + 1) = 1.0f;
    }
}

// @ 0x0113c060
bool FUN_0113c060(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    uint8_t ch = B(p, 0x21);
    uint8_t* edx = p + 0x28;
    W(p, 0xc) = (uint32_t)edx;
    if (ch == 2)
        B(p, 0x70) = 0;
    else
        B(p, 0x70) = (uint8_t)((ch != 4) + 1);
    F(p, 0x28) = 1.0f;
    F(p, 0x58) = 1.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0x5c) = 1.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x60) = 1.0f;
    F(p, 0x40) = 1.0f;
    F(p, 0x64) = 1.0f;
    F(p, 0x48) = 1.0f;
    F(p, 0x68) = 1.0f;
    F(p, 0x50) = 1.0f;
    F(p, 0x6c) = 1.0f;
    return true;
}

// @ 0x0113c120
uint32_t FUN_0113c120(uint8_t* p)
{
    return (uint32_t)B(p, 8) + 0x28;
}

// @ 0x0113c130
bool FUN_0113c130(uint8_t* p, float* src)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    uint8_t* base = (uint8_t*)(((unsigned)p + 0x2f) & ~7u);
    W16(p, 0x24) = (uint16_t)((unsigned)base - (unsigned)p);
    int ch = B(p, 0x21);
    int i = 0;
    if (src == 0) {
        for (; i < ch; i++)
            base[i] = (uint8_t)i;
    } else {
        for (; i < ch; i++)
            base[i] = (uint8_t)(int)src[i];
    }
    return true;
}

// @ 0x0113c1d0
bool FUN_0113c1d0(uint8_t* p)
{
    FUN_0113c620(p, 0x28);
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(p, 0x28) = 0.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0xb0) = 0.0f;
    F(p, 0xb4) = 1.0f;
    W(p, 0x98) = 0;
    F(voice, 0x28) = 700.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 700.0f;
    return true;
}

// @ 0x0113c290
void FUN_0113c290(uint8_t* p, int param_2)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bc0fc;
        uint8_t* e = p + 0x30;
        int i = 5;
        do {
            ((Ctx*)e)->PlugInInit16();
            e += 0x10;
        } while (--i >= 0);
    }
    if (param_2 != 0)
        W(p, 0xc) = (uint32_t)(p + param_2);
}

// @ 0x0113c360
int FUN_0113c360(uint8_t* p)
{
    return Fir64GetSize(B(p, 8), 0x40) + 0xc0;
}

// @ 0x0113c380
bool FUN_0113c380(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 1000000.0f;
    F(p, 0xb4) = 1000000.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x14) = 32.0f;
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(voice, 0x28) = 64.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 64.0f;
    Fir64GetSize(B(p, 0x21), 0x40);
    uint32_t aligned = ((unsigned)p + 0xc7) & ~7u;
    Fir64Create(P(p, 4), B(p, 0x21), 0x40, (void*)aligned);
    W16(p, 0xb8) = (uint16_t)(aligned - (unsigned)p);
    return true;
}

// @ 0x0113c460
int FUN_0113c460(uint8_t* p)
{
    return BwGetSize(B(p, 8)) + 0x50;
}

// @ 0x0113c480
bool FUN_0113c480(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 96000.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = 4.0f;
    F(p, 0x38) = 15000.0f;
    BwGetSize(B(p, 0x21));
    uint32_t aligned = ((unsigned)p + 0x57) & ~7u;
    BwCreate(P(p, 4), B(p, 0x21), (void*)aligned);
    uint8_t* voice = (uint8_t*)P(p, 8);
    W16(p, 0x48) = (uint16_t)(aligned - (unsigned)p);
    F(voice, 0x28) = 450.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 450.0f;
    return true;
}

// @ 0x0113c550
bool FUN_0113c550(uint8_t* p)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bc0fc;
        ((Ctx*)(p + 0x40))->Ctor1153b00();
    }
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x28) = 120.0f;
    F(p, 0x30) = 0.1f;
    F(p, 0x90) = 120.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x94) = 0.1f;
    F(p, 0x98) = 1.0f;
    F(p, 0x9c) = 0.0f;
    W(p, 0xa0) = 0;
    return true;
}

// @ 0x0113c620
void FUN_0113c620(uint8_t* p, int param_2)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bc0fc;
        uint8_t* e = p + 0x38;
        int i = 5;
        do {
            ((Ctx*)e)->PlugInInit16();
            e += 0x10;
        } while (--i >= 0);
    }
    if (param_2 != 0)
        W(p, 0xc) = (uint32_t)(p + param_2);
}

// @ 0x0113c710
bool FUN_0113c710(uint8_t* p)
{
    FUN_0113c290(p, 0x28);
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(p, 0x28) = 0.0f;
    F(p, 0xa4) = 0.0f;
    F(voice, 0x28) = 450.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 450.0f;
    return true;
}

// @ 0x0113c7a0
bool FUN_0113c7a0(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 0.0f;
    F(p, 0xb4) = 0.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x14) = 32.0f;
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(voice, 0x28) = 64.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 64.0f;
    Fir64GetSize(B(p, 0x21), 0x40);
    uint32_t aligned = ((unsigned)p + 0xc7) & ~7u;
    Fir64Create(P(p, 4), B(p, 0x21), 0x40, (void*)aligned);
    W16(p, 0xb8) = (uint16_t)(aligned - (unsigned)p);
    return true;
}

// @ 0x0113c870
bool FUN_0113c870(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 0.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = 4.0f;
    F(p, 0x38) = 15000.0f;
    BwGetSize(B(p, 0x21));
    uint32_t aligned = ((unsigned)p + 0x57) & ~7u;
    BwCreate(P(p, 4), B(p, 0x21), (void*)aligned);
    uint8_t* voice = (uint8_t*)P(p, 8);
    W16(p, 0x48) = (uint16_t)(aligned - (unsigned)p);
    F(voice, 0x28) = 450.0f - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = 450.0f;
    return true;
}

// @ 0x0113c950
uint32_t FUN_0113c950(uint8_t* rec)
{
    uint8_t* self = (uint8_t*)P(rec, 4);
    if (*(double*)(rec + 8) == 0.0 && F(rec, 0x10) == 0.0f) {
        F(self, 0x64) = F(rec, 0x14);
        B(self, 0x69) = 0;
        B(self, 0x68) = 0;
        return 0x20;
    }
    *(double*)(self + 0x30) = *(double*)(rec + 8);
    F(self, 0x38) = F(rec, 0x10);
    F(self, 0x3c) = F(rec, 0x14);
    W(self, 0x40) = W(rec, 0x18);
    B(self, 0x68) = 1;
    return 0x20;
}

// @ 0x0113c9d0
bool FUN_0113c9d0(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014c13b8;
    F(p, 0x28) = 1.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    B(p, 0x68) = 0;
    B(p, 0x69) = 0;
    F(p, 0x64) = 1.0f;
    return true;
}

// @ 0x0113ca00
void Ctx::FUN_0113ca00(int param_2, uint8_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    if (param_2 == 0) {
        uint8_t* q = (uint8_t*)(W(sys, 0x20) + W(sys, 0xb4));
        W(sys, 0xb4) += 0x20;
        W(q, 0) = (uint32_t)&FUN_0113c950;
        W(q, 4) = (uint32_t)this;
        *(double*)(q + 8) = *(double*)(param_3 + 0);
        F(q, 0x10) = F(param_3, 8);
        F(q, 0x14) = F(param_3, 0xc);
        W(q, 0x18) = (uint32_t)(int)F(param_3, 0x10);
    }
}

// @ 0x0113cab0
bool FUN_0113cab0(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = 1.0f;
    F(p, 0x28) = 1.0f;
    return true;
}

// @ 0x0113cb20
void Ctx::FUN_0113cb20()
{
    ((Ctx*)((char*)this + 0x5c))->D770();
    if (B(this, 0xb0) != 0)
        ((Ctx*)g_sys)->RemoveTimer((char*)this + 0x98);
}

// @ 0x0113cb50
void FUN_0113cb50(uint8_t* p)
{
    float a = F(p, 0x28);
    if (a > F(p, 0x40))
        F(p, 0x40) = a;
    float rate = F(g_sys, 0xc0);
    if (rate != F(p, 0x3c)) {
        W(p, 0x38) = 0;
        F(p, 0x3c) = rate;
    }
    int n = (int)(F(p, 0x40) * F(p, 0x3c));
    if ((int)W(p, 0x68) < n)
        ((Ctx*)(p + 0x5c))->D840(n);
}

// @ 0x0113cbb0
uint8_t* Ctx::FUN_0113cbb0(uint8_t param_2)
{
    ((Ctx*)((char*)this + 0x98))->C1154ee0();
    ((Ctx*)((char*)this + 0x5c))->D770();
    P(this, 0) = g_vtbl_014bc0fc;
    if (param_2 & 1)
        op_delete(this);
    return (uint8_t*)this;
}

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
    uint32_t delaySamples = (uint32_t)(int)(F(p, 0x40) * F(p, 0x3c));
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

// @ 0x0113cdd0
uint8_t* Ctx::FUN_0113cdd0(uint8_t param_2)
{
    Ctx* c = (Ctx*)W(this, 0x40);
    P(this, 0) = g_vtbl_014c2fa8;
    c->Ctor11547b0();
    P(this, 0) = g_vtbl_014bc0fc;
    if (param_2 & 1)
        op_delete(this);
    return (uint8_t*)this;
}

// @ 0x0113ce00
void Ctx::FUN_0113ce00()
{
    ((Ctx*)g_16e7ba0)->C1154ee0();
    uint8_t* sys = (uint8_t*)P(this, 4);
    g_16e7b80 = *(double*)(sys + 8);
    g_16e7b88 = W(sys, 0x58);
    g_16e7b8c = F(sys, 0xc0);
    g_16e7b90 = W16(sys, 0xf0);
    g_16e7b93 = (B(g_sys, 0xf9) != 0) ? 1 : 0;
    ((Ctx*)W(this, 0x24))->C1154ca0(&g_16e7b80);
    W((uint8_t*)P(this, 4), 0xcc) = W((uint8_t*)W(this, 0x24), 0x3001c);
    uint8_t* s2 = (uint8_t*)P(this, 4);
    *(double*)(s2 + 8) = (double)(F(s2, 0xbc) + (float)*(double*)(s2 + 8));
    g_16e7ba8 = 1;
}
