// Slice s0113a8b0: rw::audio::core ReverbIR1 / RawPuller2 / Pause / Pan3D plugin job
// handlers and constructors. RenderWare 4 core is VC .NET 2003 (cl 13.10) + /GL + /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP
//
// The Pan3D trig/matrix trio (0113b330/0113b750/0113b810) additionally needs /arch:SSE;
// their per-VA flags live in nonmatching.txt (equiv reads them from the reason).
//
// The plugin objects are accessed by byte offset: the retail layouts differ from the 2008
// dev-build PDB in a few fields, so each function uses the offsets that the disassembly shows.
#include "types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

// the original calls the imported memset/memcpy thunks (0x11e073e / 0x11e0744); keep the
// calls out of line so the import trace matches as well.
#pragma function(memset)
#pragma function(memcpy)

// forward declarations of same-module callees used before their definitions
uint32_t FUN_0113a770(uint32_t* rec);   // 0x113a770  ReverbIR1 reset handler
void     FUN_0113ae50(uint8_t* p);      // 0x113ae50  Pause timer callback

// ---------------------------------------------------------------------------------------
// constants / globals referenced by the original (addresses shown for the equivalence mapper)
extern float g_015bc9e4;                 // 0x15bc9e4  Pan3D default angle X (degrees)
extern float g_015bc9e8;                 // 0x15bc9e8  Pan3D default angle Y (degrees)
extern float g_015bc9ec;                 // 0x15bc9ec  Pan3D default spread mode
extern float g_015bcd9c;                 // 0x15bcd9c  rotator default angle X
extern float g_015bcda0;                 // 0x15bcda0  rotator default angle Y
extern uint8_t g_vtbl_014bc0fc[];        // 0x14bc0fc  shared base vtable (PlugIn-kind)
extern uint8_t g_vtbl_014b6b84[];        // 0x14b6b84  RawPuller2 vtable
extern uint8_t g_vtbl_014b7ee0[];        // 0x14b7ee0  Pause vtable
extern uint8_t g_vtbl_014b81e4[];        // 0x14b81e4  Pan3D vtable
extern void* volatile g_015bc450;        // 0x15bc450
extern uint8_t g_015bc468[];             // 0x15bc468

// The original object types (only the offsets used here matter).
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint16_t& W16(void* p, unsigned o) { return *(uint16_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline float&    F(void* p, unsigned o) { return *(float*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }

// A generic plug-in object large enough for every class in this slice. All member functions
// are declared with the real thiscall convention; those of other compilation units are only
// declared (the byte diff masks their targets, the equivalence checker resolves them by address).
struct Ctx {
    uint8_t b[0x800];

    // --- real (callee) members, never defined here ---
    void     FastFirReset();                       // 0x114e580  FastFirEngine::Reset
    float    FastFirApply(int, int, int, int);     // 0x114e390  FastFirEngine::Apply
    void     ReverbConfigure(int);                 // 0x113a7a0  ReverbIR1 filter setup
    void*    SysAlloc(uint32_t, const char*, int, int); // 0x112c820 System::Alloc
    void     SysFree(void*, int);                  // 0x112c850  System::Free
    bool     AddTimer(void*, void*, void*, const char*, int, int); // 0x112d8e0 TimerManager::AddTimer
    void     RemoveTimer(void*);                   // 0x112dad0  System::RemoveTimer
    void     InitSndPlayer1();                     // 0x112dbb0  PlugIn::Initialize<SndPlayer1>
    void     Init16();                             // 0x114f4f0  PlugIn::Initialize<Pan3D> (zero 16 bytes)
    float    VoiceDecayRate();                     // 0x112e440  Voice decay / sample rate

    // --- slice functions (defined below) ---
    void     FUN_0113aa50(int, uint32_t*);
    void     FUN_0113ac60(int, uint32_t*);
    void     FUN_0113ae30();
    void     FUN_0113af90();
    void     FUN_0113b290(int, uint32_t*);
    void     FUN_0113b330();
    void     FUN_0113b750(int, float, float);
    void     FUN_0113b810();
    void     FUN_0113b9d0();
};

// store a dword big-endian (the FilterInfo coefficient block is kept byte-swapped)
static inline void StoreBE(void* dst, uint32_t v)
{
    uint8_t* d = (uint8_t*)dst;
    d[0] = (uint8_t)(v >> 24);
    d[1] = (uint8_t)(v >> 16);
    d[2] = (uint8_t)(v >> 8);
    d[3] = (uint8_t)v;
}

// Unary negation of a float. cl 13.10.3052 lowers `-x` to `0 - x`, which loses the sign of a
// zero result (and the sign of an out-of-range special); the retail build (13.10.3077) lowered
// it to a sign-bit flip (xorps). Flip the sign bit explicitly so +-0, +-inf and NaN signs match.
static inline float NegF(float x)
{
    union { float f; uint32_t u; } v;
    v.f = x;
    v.u ^= 0x80000000u;
    return v.f;
}

// @ 0x0113a8b0
// ReverbIR1 IR handler: unpacks 9 big-endian coefficient dwords from the request data, runs
// the FastFir engine and, if the result exceeds the voice threshold, scales the voice mix.
uint32_t FUN_0113a8b0(uint32_t* rec)
{
    uint8_t* self = (uint8_t*)rec[1];
    uint32_t* p = (uint32_t*)rec[2];

    W(self, 0x24) = rec[2];
    for (int i = 0; i < 9; i++)
        StoreBE(self + 0x28 + i * 4, p[i]);
    W(self, 0xe4) = (uint32_t)(p + 8);

    float res = ((Ctx*)(self + 0x50))->FastFirApply(W(self, 0x34), W(self, 0x3c), W(self, 0x40), 0x100);

    float* thr = (float*)P(self, 8);
    if (*thr < res) {
        float v = res * (1.0f / 3.0f);
        thr[0] = v;
        thr[1] = v;
        thr[2] = v;
    }

    ((Ctx*)self)->ReverbConfigure(0);
    W(self, 0xe8) = 1;
    return 0xc;
}

// @ 0x0113aa50
// ReverbIR1: enqueue a command record { handler, this, arg } into the system command buffer.
void Ctx::FUN_0113aa50(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint32_t* q = (uint32_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0xc;
        q[0] = (uint32_t)&FUN_0113a8b0;
        q[1] = (uint32_t)this;
        q[2] = param_3[0];
    } else {
        W(sys, 0xb4) = off + 8;
        q[0] = (uint32_t)&FUN_0113a770;
        q[1] = (uint32_t)this;
    }
}

// @ 0x0113aae0
uint32_t FUN_0113aae0(uint8_t* p)
{
    return (uint32_t)B(p, 8) * 8 + 0x50;
}

// @ 0x0113aaf0
bool FUN_0113aaf0(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 1.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = -1.0f;
    F(p, 0x34) = 1.0f;
    F(p, 0x38) = 1.0f;
    W(p, 0x44) = 0x10000;
    W(p, 0x48) = 0;
    memset(p + 0x50, 0, (uint32_t)B(p, 0x21) * 8);
    return true;
}

// @ 0x0113abb0
void FUN_0113abb0()
{
    void* p = g_015bc468;
    g_015bc450 = p;
}

// @ 0x0113abd0
uint32_t FUN_0113abd0(uint8_t* rec)
{
    uint8_t* self = (uint8_t*)P(rec, 4);
    if (F(self, 0x2c) != F(rec, 0xc) || B(self, 0x35) != (uint8_t)(int)F(rec, 8))
        B(self, 0x34) = 1;
    B(self, 0x35) = (uint8_t)(int)F(rec, 8);
    F(self, 0x2c) = F(rec, 0xc);
    W(self, 0x28) = W(rec, 0x10);
    W(self, 0x24) = W(rec, 0x14);
    return 0x18;
}

// @ 0x0113ac20
uint32_t FUN_0113ac20(uint8_t* rec)
{
    W((uint8_t*)P(rec, 4), 0x24) = 0;
    return 8;
}

// @ 0x0113ac40
bool FUN_0113ac40(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014b6b84;
    W(p, 0x24) = 0;
    W(p, 0x30) = 0;
    B(p, 0x34) = 1;
    return true;
}

// @ 0x0113ac60
void Ctx::FUN_0113ac60(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint8_t* q = (uint8_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0x18;
        W(q, 4) = (uint32_t)this;
        W(q, 0) = (uint32_t)&FUN_0113abd0;
        W(q, 8) = param_3[0];
        W(q, 0xc) = param_3[1];
        W(q, 0x10) = param_3[2];
        W(q, 0x14) = param_3[3];
    } else {
        W(sys, 0xb4) = off + 8;
        W(q, 0) = (uint32_t)&FUN_0113ac20;
        W(q, 4) = (uint32_t)this;
    }
}

// @ 0x0113ad10
void FUN_0113ad10(uint8_t* p, int param_2)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014bc0fc;
        uint8_t* e = p + 0x40;
        int i = 5;
        do {
            ((Ctx*)e)->Init16();
            e += 0x10;
        } while (--i >= 0);
    }
    if (param_2 != 0)
        W(p, 0xc) = (uint32_t)(p + param_2);
}

// @ 0x0113ae30
void Ctx::FUN_0113ae30()
{
    if (B(this, 0x59) == 1)
        ((Ctx*)P(this, 4))->RemoveTimer((char*)this + 0x34);
}

// @ 0x0113ae50
void FUN_0113ae50(uint8_t* p)
{
    float fv = ((Ctx*)P(p, 8))->VoiceDecayRate() * F((uint8_t*)P(p, 4), 0xc0) + 1.0f;
    *(int*)(p + 0x4c) = _mm_cvt_ss2si(_mm_set_ss(fv));
}

// @ 0x0113aeb0
bool FUN_0113aeb0(uint8_t* p)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014b7ee0;
        ((Ctx*)(p + 0x34))->InitSndPlayer1();
    }
    F(p, 0x28) = 0.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = 1.0f;
    B(p, 0x57) = 2;
    B(p, 0x58) = 0;
    B(p, 0x59) = 0;
    W(p, 0x4c) = 0;
    W(p, 0x50) = 0;
    bool r = ((Ctx*)((char*)P(p, 4) + 0x60))->AddTimer((char*)p + 0x34, (void*)&FUN_0113ae50, p, "SndPlayer", 1, 1);
    if (r)
        return false;
    B(p, 0x59) = 1;
    return true;
}

// @ 0x0113af70
uint32_t FUN_0113af70(uint8_t* rec)
{
    W((uint8_t*)P(rec, 4), 0xbc) = 0;
    return 8;
}

// @ 0x0113af90
void Ctx::FUN_0113af90()
{
    if (W(this, 0x90) != 0) {
        ((Ctx*)P(this, 4))->SysFree((void*)W(this, 0x8c), 0);
        W(this, 0x90) = 0;
    }
}

// @ 0x0113afc0
uint32_t FUN_0113afc0(uint32_t* p)
{
    int v = 0;
    if (*p != 0)
        v = (int)F((uint8_t*)*p, 4);
    return (uint32_t)v * 0x50 + 0x138;
}

// @ 0x0113b000
uint32_t FUN_0113b000(uint8_t* rec)
{
    uint8_t* self = (uint8_t*)P(rec, 4);
    void* src = P(rec, 8);
    if (src != 0) {
        W(self, 0xa4) = 1;
        memcpy(P(self, 0x98), src, 0x22c);
        W(self, 0xbc) = 1;
        return 0xc;
    }
    W(self, 0xa4) = 0;
    W(self, 0xbc) = 0;
    return 0xc;
}

// @ 0x0113b060
bool FUN_0113b060(uint8_t* p, uint8_t* params)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014b81e4;
        ((Ctx*)(p + 0x30))->Init16();
    }
    uint8_t* ebp = p + 0x28;
    W(p, 0xc) = (uint32_t)ebp;
    if (params == 0) {
        F(p, 0x58) = 1.0f;
        W(p, 0x9c) = 0;
    } else {
        F(p, 0x58) = F(params, 0);
        W(p, 0x9c) = (uint32_t)(int)F(params, 4);
    }

    unsigned int aligned = ((unsigned int)p + 0xcf) & ~7u;
    uint32_t u3 = (uint32_t)(aligned - (unsigned int)p);
    W16(p, 0xc0) = (uint16_t)u3;
    memset((void*)((unsigned int)(uint16_t)u3 + (unsigned int)p), 0, 0x6c);

    uint32_t aligned2 = (uint32_t)((aligned + 0x73) & ~7u);
    W16(p, 0xc2) = (uint16_t)(aligned2 - (uint32_t)(unsigned int)p);
    memset((void*)((unsigned int)(uint16_t)(aligned2 - (uint32_t)(unsigned int)p) + (unsigned int)p), 0,
           W(p, 0x9c) * 0x50);

    float rate = F((uint8_t*)P(p, 4), 0xc0);
    F(p, 0x54) = rate;
    int delay = (int)(rate * F(p, 0x58));
    int n = ((delay + 0xff) & ~0xff) + 0x100;
    uint32_t size = (uint32_t)n * 4 + 0x122c;
    W(p, 0xa8) = (uint32_t)n;
    void* dst = ((Ctx*)P(p, 4))->SysAlloc(size,
        "rw::audio::core::Pan3D::Delay line, internal buffer and DSPSettingsLocal", 0x80, 0);
    W(p, 0x8c) = (uint32_t)dst;
    memset(dst, 0, size);

    uint32_t u = ((uint32_t)(unsigned int)dst + 0x7f) & ~(uint32_t)0x7f;
    W(p, 0x94) = u;
    W(p, 0x90) = (u + 0x100f) & ~(uint32_t)0xf;
    W(p, 0x98) = (W(p, 0x90) + W(p, 0xa8) * 4 + 0xf) & ~(uint32_t)0xf;

    F(p, 0x84) = 1.0f;
    F(ebp, 0) = 1.0f;
    W(p, 0xb0) = 0;
    W(p, 0xa0) = 0;
    B(p, 0xc6) = 0;
    F(p, 0x5c) = 1.0f;
    W(p, 0xa4) = 0;
    B(p, 0xc5) = 0;
    F(p, 0x6c) = 0.0f;
    F(p, 0x70) = 0.0f;
    W(p, 0xbc) = 0;
    W(p, 0x7c) = 0;
    W(p, 0x80) = 0;
    F(p, 0x60) = 0.0f;
    F(p, 0x64) = 0.0f;
    F(p, 0x68) = 0.0f;

    uint32_t n32 = W(p, 0xa8);
    float fn = (float)n32;
    if ((int)n32 < 0)
        fn += 4294967296.0f;
    uint8_t* voice = (uint8_t*)P(p, 8);
    F(voice, 0x28) = fn - F(p, 0x18) + F(voice, 0x28);
    F(p, 0x18) = fn;
    return true;
}

// @ 0x0113b290
void Ctx::FUN_0113b290(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint32_t* q = (uint32_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0xc;
        q[0] = (uint32_t)&FUN_0113b000;
        q[1] = (uint32_t)this;
        q[2] = param_3[0];
    } else {
        W(sys, 0xb4) = off + 8;
        q[0] = (uint32_t)&FUN_0113af70;
        q[1] = (uint32_t)this;
    }
}

// @ 0x0113b330
void Ctx::FUN_0113b330()
{
    float a = F(this, 0x7c);
    F(this, 0x88) = (float)(cos(a) * 2.0);
    F(this, 0x13c) = (float)cos(a);
    F(this, 0x140) = (float)sin(a);
    float na = NegF(a);
    F(this, 0x14c) = (float)cos(na);
    F(this, 0x150) = (float)sin(na);
    float b = F(this, 0x80);
    F(this, 0x154) = (float)cos(b);
    F(this, 0x158) = (float)sin(b);
    float nb = NegF(b);
    F(this, 0x15c) = (float)cos(nb);
    F(this, 0x160) = (float)sin(nb);
    F(this, 0x148) = 0.0f;
    F(this, 0x144) = 1.0f;

    float c1 = F(this, 0x13c), s1 = F(this, 0x140);
    float c2 = F(this, 0x14c), s2 = F(this, 0x150);
    float i1 = 1.0f / (c1 * s2 - s1 * c2);
    F(this, 0x8c) = i1 * c1;
    F(this, 0x90) = NegF(i1 * s1);
    F(this, 0x98) = i1 * s2;
    F(this, 0x94) = NegF(i1 * c2);

    float c3 = F(this, 0x154), s3 = F(this, 0x158);
    float i2 = 1.0f / (c3 * s1 - s3 * c1);
    F(this, 0xbc) = i2 * c3;
    F(this, 0xc0) = NegF(i2 * s3);
    F(this, 0xc4) = NegF(i2 * c1);
    F(this, 0xc8) = i2 * s1;

    float c4 = F(this, 0x15c), s4 = F(this, 0x160);
    float i3 = 1.0f / (c4 * s3 - s4 * c3);
    F(this, 0xac) = i3 * c4;
    F(this, 0xb0) = NegF(i3 * s4);
    F(this, 0xb4) = NegF(i3 * c3);
    F(this, 0xb8) = i3 * s3;

    float c2b = F(this, 0x14c), s2b = F(this, 0x150);
    float c3b = F(this, 0x15c), s3b = F(this, 0x160);
    float i4 = 1.0f / (c2b * s3b - s2b * c3b);
    F(this, 0x9c) = i4 * c2b;
    F(this, 0xa0) = NegF(i4 * s2b);
    F(this, 0xa4) = NegF(i4 * c3b);
    F(this, 0xa8) = i4 * s3b;
}

// @ 0x0113b5b0
bool FUN_0113b5b0(uint8_t* p, float* params)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    uint8_t al = B(p, 0x20);
    uint8_t* esi = p + 0x28;
    W(p, 0xc) = (uint32_t)esi;
    uint32_t edx = 5;
    if (al != 6)
        edx = al;
    W(p, 0xcc) = edx;
    uint8_t al2 = B(p, 0x21);
    uint32_t eax = 5;
    if (al2 != 6)
        eax = al2;
    W(p, 0xd0) = eax;

    const float K = 0.017453292f;
    float z;
    if (params != 0) {
        F(p, 0x7c) = params[0] * K;
        F(p, 0x80) = params[1] * K;
        z = params[2];
    } else {
        F(p, 0x7c) = g_015bc9e4 * K;
        F(p, 0x80) = g_015bc9e8 * K;
        z = g_015bc9ec;
    }
    if (z == 0.0f)
        F(p, 0x84) = 1.0f;
    else if (z == 1.0f)
        F(p, 0x84) = 1.0f / (float)edx;
    else if (z == 2.0f)
        F(p, 0x84) = 1.0f / sqrtf((float)edx);

    F(p, 0x60) = 0.0f;
    F(esi, 0) = 0.0f;
    F(p, 0x64) = 1.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0x68) = 1.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x6c) = 0.0f;
    F(p, 0x40) = 0.0f;
    F(p, 0x70) = 1.0f;
    F(p, 0x48) = 1.0f;
    F(p, 0x74) = 1.0f;
    F(p, 0x50) = 1.0f;
    F(p, 0x78) = 0.0f;
    F(p, 0x58) = 0.0f;
    ((Ctx*)p)->FUN_0113b330();
    return true;
}

// @ 0x0113b750
void Ctx::FUN_0113b750(int idx, float a, float b)
{
    float sa = (float)sin(a), ca = (float)cos(a);
    float sb = (float)sin(b), cb = (float)cos(b);
    float inv = 1.0f / (cb * sa - sb * ca);
    uint8_t* e = (uint8_t*)this + idx * 0x10;
    F(e, 0x7c) = inv * cb;
    F((uint8_t*)this + (idx + 8) * 0x10, 0) = NegF(inv * sb);
    F(e, 0x84) = NegF(inv * ca);
    F(e, 0x88) = inv * sa;
}

// @ 0x0113b810
void Ctx::FUN_0113b810()
{
    const float K = 0.017453292f;
    float a, b;
    if (B(this, 0xec) == 0) {
        a = g_015bcd9c * K;
        b = g_015bcda0;
    } else {
        a = F(this, 0x64) * K;
        b = F(this, 0x68);
    }
    F(this, 0x6c) = a;
    F(this, 0x70) = b * K;
    F(this, 0x74) = cos(a) * 2.0f;
    F(this, 0x78) = cos(3.1415927f - F(this, 0x70)) * 2.0f;

    float a2 = F(this, 0x6c);
    float b2 = F(this, 0x70);
    FUN_0113b750(0, NegF(a2), a2);
    FUN_0113b750(1, a2, b2);
    FUN_0113b750(2, b2, NegF(b2));
    FUN_0113b750(3, NegF(b2), NegF(a2));
}

// @ 0x0113b910
bool FUN_0113b910(uint8_t* p, float* params)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    if (params != 0) {
        F(p, 0x64) = params[0];
        F(p, 0x68) = params[1];
        B(p, 0xec) = 1;
    } else {
        B(p, 0xec) = 0;
    }
    F(p, 0x50) = 0.0f;
    F(p, 0x28) = 0.0f;
    F(p, 0x54) = 1.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0x58) = 1.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x5c) = 1.0f;
    F(p, 0x40) = 1.0f;
    F(p, 0x60) = 0.0f;
    F(p, 0x48) = 0.0f;
    ((Ctx*)p)->FUN_0113b810();
    return true;
}

// @ 0x0113b9d0
void Ctx::FUN_0113b9d0()
{
    if (B(this, 0x169) != 0)
        ((Ctx*)P(this, 4))->RemoveTimer((char*)this + 0x30);
    uint32_t a = W(this, 0x48);
    if (a != 0)
        ((Ctx*)P(this, 4))->SysFree((void*)a, 0);
}

// @ 0x0113ba30
uint32_t FUN_0113ba30(uint8_t* p)
{
    return (uint32_t)B(p, 8) * 4 + 0x170;
}
