// EA::Swarm simulator family (slice s00a84ca0): curve/ability sampling, transform
// assembly, serialisation and teardown for a Swarm simulator base object.
// Built with VS2008 SP1 (cl 15.00.30729.01) /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// Bit extraction kept in an inline helper: the original tests bits through a
// helper like this (bool return), which cl inlines to `mov r,x; shr r,n; test rl,1`
// instead of folding the test into `test byte [m],mask`.
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }

// ---------------------------------------------------------------------------
// Callees (opaque).
// ---------------------------------------------------------------------------
extern void  __cdecl operator_delete__(void* p);                            // 0x00f47380
extern void  __cdecl FUN_00a84d40(void* s, void* d);                        // 0x00a84d40

extern void  __cdecl FUN_0093a780(void* s, void* p, int n, int z);          // 0x0093a780
extern void  __cdecl FUN_0093a700(void* s, void* p, int n, int z);          // 0x0093a700
extern void  __cdecl FUN_0093a800(void* s, void* p, int n, int z);          // 0x0093a800
extern void  __cdecl FUN_0093a6c0(void* s, void* p, int n);                 // 0x0093a6c0
extern void  __cdecl FUN_007d27d0(void* s, void* p);                        // 0x007d27d0
extern int   __cdecl FUN_0093a9a0(void* s, void* p, int n);                 // 0x0093a9a0
extern int   __cdecl FUN_0093ab10(void* s, void* p, int a, int b);          // 0x0093ab10
extern int   __cdecl FUN_0093a9d0(void* s, void* p, int a, int b);          // 0x0093a9d0
extern int   __cdecl FUN_0093aa70(void* s, void* p, int a, int b);          // 0x0093aa70

struct Mat3  { void __thiscall Assign(const void* src); };                  // 0x0041cb40
struct Xf    { void __thiscall RotateZ(float); void __thiscall PreRotateX(float);
               void __thiscall RotateY(float); };                           // 0x7d1ac0/0x5a2d90/0x6b9050
struct Trn   { void __thiscall PreTransformBy(const void* src); };          // 0x537f40
struct SpTr  { void* __thiscall Assign(const void* src); };                 // 0x537dc0
struct Vec3f { float x, y, z; };

// ---------------------------------------------------------------------------
// The state block (vtbl 0x1457fd8 / dtor 0x13ef094), stride-0x84 array holder.
// ---------------------------------------------------------------------------
struct Cfg
{
    void*    vt;         // 0x00
    void*    p04;        // 0x04
    uint32_t flags;      // 0x08
    uint16_t w0c;        // 0x0c
    uint16_t p0e;        // 0x0e
    float    f10;        // 0x10
    void*    arr14;      // 0x14
    void*    e14;        // 0x18
    uint32_t p1c;        // 0x1c
    uint32_t p20;        // 0x20
    uint32_t p24;        // 0x24
    void*    arr28;      // 0x28
    void*    e28;        // 0x2c
    uint32_t p30;        // 0x30
    uint32_t p34;        // 0x34
    uint32_t p38;        // 0x38
    void*    arr3c;      // 0x3c
    void*    e3c;        // 0x40
    uint32_t p44;        // 0x44
    uint32_t p48;        // 0x48
    uint32_t p4c;        // 0x4c
    void*    arr50;      // 0x50
    void*    e50;        // 0x54
    uint32_t p58;        // 0x58
    uint32_t p5c;        // 0x5c
    uint32_t p60;        // 0x60
    void*    arr64;      // 0x64
    void*    e64;        // 0x68
    uint32_t p6c;        // 0x6c
    uint32_t p70;        // 0x70
    uint32_t p74;        // 0x74
    void*    arr78;      // 0x78
    void*    e78;        // 0x7c
    uint32_t p80;        // 0x80
    uint32_t p84;        // 0x84
    uint32_t p88;        // 0x88
    void*    arr8c;      // 0x8c
    void*    e8c;        // 0x90
    uint32_t p94;        // 0x94
    uint32_t p98;        // 0x98
    uint32_t p9c;        // 0x9c
    uint32_t a0;         // 0xa0
    uint32_t a4;         // 0xa4
    uint16_t wa8;        // 0xa8
    uint16_t paa;        // 0xaa

    Cfg* __fastcall Ctor();
    void __fastcall Release();
};

// ---------------------------------------------------------------------------
// Sim: the simulator object (vtbl 0x1458024).
// ---------------------------------------------------------------------------
struct Sim
{
    void*    vt;         // 0x00
    void*    p04;        // 0x04
    uint32_t p08;        // 0x08
    Cfg*     cfg;        // 0x0c
    void*    h10;        // 0x10
    uint8_t  b14;        // 0x14
    uint8_t  b15;        // 0x15
    uint16_t w16;        // 0x16
    float    f18;        // 0x18
    float    f1c;        // 0x1c
    float    f20;        // 0x20
    uint16_t w24;        // 0x24
    uint16_t w26;        // 0x26
    float    f28;        // 0x28
    float    f2c;        // 0x2c
    float    f30;        // 0x30
    float    f34;        // 0x34
    uint8_t  m38[0x24];  // 0x38
    float    f5c;        // 0x5c
    float    f60;        // 0x60
    float    f64;        // 0x64
    int32_t  i68;        // 0x68

    Sim* __thiscall Ctor(void* cfg);
    void __thiscall Activate(bool);
    void __thiscall Deactivate(bool);
    void __fastcall Sample();
    void __thiscall Build();
    void __thiscall Tick(float dt, void* a, void* b);
    void __thiscall SetCfg(void* c, void* d, void* e);
    void __thiscall Apply(void* src, void* x);
};

// vtable slot helper casts
typedef void* (__thiscall *VF1)(void*);
typedef int   (__thiscall *VFI)(void*);

// ---------------------------------------------------------------------------
// @ 0x00a84f00   (constructor of the state block)
// ---------------------------------------------------------------------------
Cfg* __fastcall Cfg::Ctor()
{
    volatile uint32_t* v = (volatile uint32_t*)this;
    v[1] = 0;                                          // 0x04
    v[0] = 0x1457fd8;                                  // 0x00
    v[2] = 0;                                          // 0x08
    *(volatile float*)((char*)this + 0x10) = 1.0f;
    *(volatile uint16_t*)((char*)this + 0x0c) = 0;
    v[5] = 0;
    v[6] = 0;
    v[7] = 0;
    v[0x0a] = 0;
    v[0x0b] = 0;
    v[0x0c] = 0;
    v[0x0f] = 0;
    v[0x10] = 0;
    v[0x11] = 0;
    v[0x14] = 0;
    v[0x15] = 0;
    v[0x16] = 0;
    v[0x19] = 0;
    v[0x1a] = 0;
    v[0x1b] = 0;
    v[0x1e] = 0;
    v[0x1f] = 0;
    v[0x20] = 0;
    v[0x23] = 0;
    v[0x24] = 0;
    v[0x25] = 0;
    v[0x28] = 0;
    v[0x29] = 0;
    *(volatile uint16_t*)((char*)this + 0xa8) = 0x100;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00a84e50   (releases the seven heap blocks of the state block)
// ---------------------------------------------------------------------------
void __fastcall Cfg::Release()
{
    if (this->arr8c != 0 && *(int32_t*)((char*)this->arr8c - 4) != 0)
        operator_delete__(this->arr8c);
    if (this->arr78 != 0 && *(int32_t*)((char*)this->arr78 - 4) != 0)
        operator_delete__(this->arr78);
    if (this->arr64 != 0 && *(int32_t*)((char*)this->arr64 - 4) != 0)
        operator_delete__(this->arr64);
    if (this->arr50 != 0 && *(int32_t*)((char*)this->arr50 - 4) != 0)
        operator_delete__(this->arr50);
    if (this->arr3c != 0 && *(int32_t*)((char*)this->arr3c - 4) != 0)
        operator_delete__(this->arr3c);
    if (this->arr28 != 0 && *(int32_t*)((char*)this->arr28 - 4) != 0)
        operator_delete__(this->arr28);
    if (this->arr14 != 0 && *(int32_t*)((char*)this->arr14 - 4) != 0)
        operator_delete__(this->arr14);
    *(void**)this = (void*)0x13ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00a853b0   (Sim constructor)
// ---------------------------------------------------------------------------
Sim* __thiscall Sim::Ctor(void* cfg)
{
    *(void**)((char*)this + 0x04) = (void*)0x13ef094;
    *(uint32_t*)((char*)this + 0x08) = 0;
    this->cfg = (Cfg*)cfg;
    this->f18 = 0.0f;
    this->f1c = 0.0f;
    this->f20 = 0.0f;
    *(void**)this = (void*)0x1458024;
    *(void**)((char*)this + 0x04) = (void*)0x14599e8;
    this->h10 = 0;
    this->b14 = 0;
    this->w26 = 0;
    this->w24 = 0;
    float a = *(float*)0x1677d7c;
    this->f28 = a;
    float b = *(float*)0x1677d80;
    this->f2c = b;
    float c = *(float*)0x1677d84;
    this->f30 = c;
    float d = *(float*)0x1485720;
    this->f34 = d;
    ((Mat3*)((char*)this + 0x38))->Assign((void*)0x1677e28);
    float k = *(float*)0x13eb1bc;
    this->f5c = k;
    this->f60 = k;
    this->f64 = k;
    this->i68 = -1;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00a850d0
// ---------------------------------------------------------------------------
void __thiscall Sim::Activate(bool)
{
    if (this->b14 != 0)
        return;
    this->b14 = 1;
    if (this->h10 != 0) {
        if (Bit(this->cfg->flags, 2))
            (*(void (__thiscall**)(void*))(*(uint32_t**)this->h10 + 0x18 / 4))(this->h10);
        uint32_t f = this->cfg->flags;
        if (Bit(f, 4)) {
            uint32_t w = this->cfg->wa8;
            (*(void (__thiscall**)(void*, uint32_t, void*))(*(uint32_t**)this->h10 + 0x1c / 4))
                (this->h10, w,
                 Bit(f, 6) ? (void*)((char*)this + 0x28) : 0);
        }
        this->i68 = -1;
        if (Bit(this->cfg->flags, 1)) {
            (*(void (__thiscall**)(void*, uint32_t, uint32_t))(*(uint32_t**)this->h10 + 0x0c / 4))
                (this->h10, this->cfg->a0, this->cfg->a4);
        } else if (this->cfg->f10 > 0.0f) {
            this->i68 = (*(int (__thiscall**)(void*, uint32_t, uint32_t))(*(uint32_t**)this->h10 + 0x10 / 4))
                (this->h10, this->cfg->a0, this->cfg->a4);
            if (this->i68 < 0) {
                this->b14 = 0;
                return;
            }
        }
    }
    this->f1c = 0.0f;
    this->f20 = 0.0f;
    this->f18 = (this->cfg->f10 > 0.0f) ? (1.0f / this->cfg->f10) : 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00a85790
// ---------------------------------------------------------------------------
void __thiscall Sim::Deactivate(bool)
{
    if (this->b14 == 0)
        return;
    this->b14 = 0;
    if (this->h10 == 0)
        return;
    if (Bit(this->cfg->flags, 3) || Bit(this->cfg->flags, 5)) {
        if (this->cfg->flags & 1)
            this->Build();
        if (Bit(this->cfg->flags, 3))
            (*(void (__thiscall**)(void*))(*(uint32_t**)this->h10 + 0x18 / 4))(this->h10);
        if (Bit(this->cfg->flags, 5)) {
            void* arg = Bit(this->cfg->flags, 6) ? (void*)((char*)this + 0x28) : 0;
            (*(void (__thiscall**)(void*, uint32_t, void*))(*(uint32_t**)this->h10 + 0x1c / 4))
                (this->h10, this->cfg->wa8, arg);
        }
    }
    if (this->i68 >= 0) {
        (*(void (__thiscall**)(void*, int32_t))(*(uint32_t**)this->h10 + 0x14 / 4))
            (this->h10, this->i68);
        this->i68 = -1;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a858c0
// ---------------------------------------------------------------------------
void __thiscall Sim::Tick(float dt, void* a, void* b)
{
    this->f1c = dt * this->f18 + this->f1c;
    if (this->f1c > 1.0f) {
        if (Bit(this->cfg->flags, 7)) {
            int i = (int)this->f1c;
            if (this->f1c < (float)i)
                i--;
            this->f1c = this->f1c - (float)i;
        } else {
            this->f1c = 1.0f;
        }
    }
    if (this->h10 != 0) {
        if (Bit(this->cfg->flags, 0))
            this->Build();
        if (this->h10 != 0 && Bit(this->cfg->flags, 9))
            this->Sample();
    }
    if (this->f18 == 0.0f || this->f1c == 1.0f) {
        if (Bit(this->cfg->flags, 8))
            (*(void (__thiscall**)(void*, void*))(*(uint32_t**)this + 0x0c / 4))(this, 0);
    }
    (void)a; (void)b;
}

// ---------------------------------------------------------------------------
// helper: linear sample of a float curve at parameter t
// ---------------------------------------------------------------------------
static float Curve(void* begin, void* end, float t)
{
    int n = (int)(((char*)end - (char*)begin) >> 2) - 1;
    if (n == 0)
        return *(float*)begin;
    float f = (float)(uint32_t)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    float* base = (float*)begin;
    if (frac > 0.0f)
        return base[i] + (base[i + 1] - base[i]) * frac;
    return base[i];
}

// ---------------------------------------------------------------------------
// @ 0x00a851d0   (sample the three curves and feed the handler)
// ---------------------------------------------------------------------------
void __fastcall Sim::Sample()
{
    Cfg* c = this->cfg;
    if (c->arr64 != c->e64)
        this->f5c = Curve(c->arr64, c->e64, this->f1c);
    c = this->cfg;
    if (c->arr78 != c->e78)
        this->f60 = Curve(c->arr78, c->e78, this->f1c);
    c = this->cfg;
    if (c->arr8c != c->e8c)
        this->f64 = Curve(c->arr8c, c->e8c, this->f1c);
    Cfg* cc = this->cfg;
    void* h = this->h10;
    (*(void (__thiscall**)(void*, float, float, float, uint32_t))(*(uint32_t**)h + 0x08 / 4))
        (h, this->f5c, this->f60, this->f64, cc->w0c);
}

// ---------------------------------------------------------------------------
// @ 0x00a85460
// ---------------------------------------------------------------------------
void __thiscall Sim::Build()
{
    Xf local;
    *(float*)((char*)&local + 0x10) = this->f28;
    *(float*)((char*)&local + 0x14) = this->f2c;
    *(float*)((char*)&local + 0x18) = this->f30;
    *(float*)((char*)&local + 0x1c) = this->f34;
    *(uint16_t*)((char*)&local + 0x00) = this->w24;
    *(uint16_t*)((char*)&local + 0x02) = this->w26;
    ((Mat3*)((char*)&local + 0x14))->Assign((char*)this + 0x38);

    Cfg* c = this->cfg;
    if (c->arr14 != c->e14)
        local.RotateZ(Curve(c->arr14, c->e14, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr28 != c->e28)
        local.PreRotateX(Curve(c->arr28, c->e28, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr3c != c->e3c)
        local.RotateY(Curve(c->arr3c, c->e3c, this->f1c) * *(float*)0x1677e14);

    c = this->cfg;
    if (c->arr50 != c->e50)
        *(float*)((char*)&local + 0x0c) = Curve(c->arr50, c->e50, this->f1c) * *(float*)0x1677e14;

    Cfg* cc = this->cfg;
    void* h = this->h10;
    (*(void (__thiscall**)(void*, void*, uint32_t))(*(uint32_t**)h + 0x04 / 4))
        (h, &local, cc->w0c);
}

// ---------------------------------------------------------------------------
// @ 0x00a85840
// ---------------------------------------------------------------------------
struct Head14 { uint16_t w0, w2; float f4, f8, fC, f10; };
struct Buf30  { Head14 h; uint32_t m00, m04, m08, m0c, m10, m14, m18, m1c, m20; };

void __thiscall Sim::Apply(void* src, void* x)
{
    Buf30 buf;
    Head14* hx = (Head14*)x;
    buf.h.w0  = hx->w0;
    buf.h.w2  = hx->w2;
    buf.h.f4  = hx->f4;
    buf.h.f8  = hx->f8;
    buf.h.fC  = hx->fC;
    buf.h.f10 = hx->f10;
    ((Mat3*)&buf.m00)->Assign((char*)x + 0x14);
    ((Trn*)&buf)->PreTransformBy(src);
    ((SpTr*)((char*)this + 0x24))->Assign(&buf);
}

// ---------------------------------------------------------------------------
// @ 0x00a84ca0   (stride-0x84 array growth; this = a begin/end container)
// ---------------------------------------------------------------------------
struct Tmp84
{
    uint32_t s00, s04, s08, s0c, s10, s14, s18, s1c;
    uint32_t s20, s24, s28, s2c, s30, s34, s38, s3c;
    uint32_t s40;
    void*    p44;        // 0x44
    uint32_t s48, s4c, s50, s54, s58, s5c, s60;
    uint32_t s64, s68, s6c, s70, s74, s78, s7c, s80;
    void* __thiscall New();
};

struct Vec84
{
    void* begin;         // 0x00
    void* end;           // 0x04
    void __thiscall Grow(void* e, uint32_t n, void* p);
    void __thiscall Erase(void* a, void* b);
    void __thiscall Reserve(uint32_t n);
};

void __thiscall Vec84::Reserve(uint32_t n)
{
    if (n > (uint32_t)(((char*)this->end - (char*)this->begin) / 0x84)) {
        Tmp84 tmp;
        void* p = tmp.New();
        this->Grow(this->end,
                   n - (uint32_t)(((char*)this->end - (char*)this->begin) / 0x84), p);
        if (tmp.p44 != 0 && *(int32_t*)((char*)tmp.p44 - 4) != 0)
            operator_delete__(tmp.p44);
    } else {
        this->Erase((char*)this->begin + n * 0x84, this->end);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a84da0
// ---------------------------------------------------------------------------
extern "C" void FUN_00a84da0(void* s, void* unused, void* d)
{
    uint32_t tmp;
    FUN_0093a780(s, &tmp, 1, 0);
    *(uint32_t*)((char*)d + 0x00) = tmp & 0x3fffff;
    FUN_0093a780(s, (char*)d + 0x04, 1, 0);
    FUN_0093a780(s, (char*)d + 0x08, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))(*(uint32_t**)s + 0xc))(s, (char*)d + 0x0c, 8);
    FUN_0093a780(s, (char*)d + 0x14, 1, 0);
    FUN_0093a6c0(s, (char*)d + 0x18, 1);
    FUN_007d27d0(s, (char*)d + 0x1c);
    (*(void (__thiscall**)(void*, void*, int))(*(uint32_t**)s + 0xc))(s, (char*)d + 0x30, 0xc);
    FUN_0093a780(s, (char*)d + 0x40, 1, 0);
    FUN_00a84d40(s, (char*)d + 0x44);
}

// ---------------------------------------------------------------------------
// @ 0x00a84fb0
// ---------------------------------------------------------------------------
extern "C" void FUN_00a84fb0(void* s, int, char* d)
{
    uint32_t tmp;
    FUN_0093a780(s, &tmp, 1, 0);
    *(uint32_t*)(d + 0x08) = tmp & 0x3ff;
    FUN_0093a700(s, d + 0x0c, 1, 0);
    FUN_0093a780(s, d + 0x10, 1, 0);
    FUN_007d27d0(s, d + 0x14);
    FUN_007d27d0(s, d + 0x28);
    FUN_007d27d0(s, d + 0x3c);
    FUN_007d27d0(s, d + 0x50);
    FUN_007d27d0(s, d + 0x64);
    FUN_007d27d0(s, d + 0x78);
    FUN_007d27d0(s, d + 0x8c);
    FUN_0093a800(s, d + 0xa0, 1, 0);
    FUN_0093a700(s, d + 0xa8, 1, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00a85070
// ---------------------------------------------------------------------------
void __thiscall Sim::SetCfg(void* c, void* d, void* e)
{
    void* o = (*(VF1*)(*(uint32_t**)c + 0x20 / 4))(c);
    this->h10 = (void*)(*(VFI*)(*(uint32_t**)o + 0x60 / 4))(o);
    (void)d; (void)e;
}

// ---------------------------------------------------------------------------
// @ 0x00a85090
// ---------------------------------------------------------------------------
extern "C" int FUN_00a85090(int a1, void* a2, int* out, int count)
{
    int r = 0;
    uint32_t lo = *(uint32_t*)((char*)a2 + 0xa0);
    uint32_t hi = *(uint32_t*)((char*)a2 + 0xa4);
    if ((lo & hi) != 0xffffffffu) {
        r = 1;
        if (count > 0) {
            out[0] = lo;
            out[1] = hi;
            out[2] = 8;
        }
    }
    (void)a1;
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00a85a20
// ---------------------------------------------------------------------------
extern "C" void* FUN_00a85a20(void* s, void* src)
{
    uint64_t q;
    uint8_t b;
    q = *(uint64_t*)src;
    FUN_0093ab10(s, &q, 1, 0);
    b = *(uint8_t*)((char*)src + 8);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 9);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 0xa);
    FUN_0093a9a0(s, &b, 1);
    b = *(uint8_t*)((char*)src + 0xb);
    FUN_0093a9a0(s, &b, 1);
    uint32_t dw = *(uint16_t*)((char*)src + 0xc);
    FUN_0093a9d0(s, &dw, 1, 0);
    float fl = *(float*)((char*)src + 0x10);
    FUN_0093aa70(s, &fl, 1, 0);
    q = *(uint64_t*)((char*)src + 0x18);
    FUN_0093ab10(s, &q, 1, 0);
    return s;
}

// ---------------------------------------------------------------------------
// @ 0x00a85b00
// ---------------------------------------------------------------------------
extern "C" void* FUN_00a85b00(void* s, void* d)
{
    FUN_0093a800(s, d, 1, 0);
    FUN_0093a6c0(s, (char*)d + 8, 1);
    FUN_0093a6c0(s, (char*)d + 9, 1);
    FUN_0093a6c0(s, (char*)d + 0xa, 1);
    FUN_0093a6c0(s, (char*)d + 0xb, 1);
    FUN_0093a700(s, (char*)d + 0xc, 1, 0);
    FUN_0093a780(s, (char*)d + 0x10, 1, 0);
    FUN_0093a800(s, (char*)d + 0x18, 1, 0);
    return s;
}

// ---------------------------------------------------------------------------
// @ 0x00a85b80
// ---------------------------------------------------------------------------
struct Heap5
{
    uint32_t pad00[0x34 / 4];
    void*    p34;        // 0x34
    uint32_t pad38[(0x48 - 0x38) / 4];
    void*    p48;        // 0x48
    uint32_t pad4c[(0x5c - 0x4c) / 4];
    void*    p5c;        // 0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    void*    p70;        // 0x70
    uint32_t pad74[(0x84 - 0x74) / 4];
    void*    p84;        // 0x84

    void __fastcall Release();
};

void __fastcall Heap5::Release()
{
    if (this->p84 != 0 && *(int32_t*)((char*)this->p84 - 4) != 0)
        operator_delete__(this->p84);
    if (this->p70 != 0 && *(int32_t*)((char*)this->p70 - 4) != 0)
        operator_delete__(this->p70);
    if (this->p5c != 0 && *(int32_t*)((char*)this->p5c - 4) != 0)
        operator_delete__(this->p5c);
    if (this->p48 != 0 && *(int32_t*)((char*)this->p48 - 4) != 0)
        operator_delete__(this->p48);
    if (this->p34 != 0 && *(int32_t*)((char*)this->p34 - 4) != 0)
        operator_delete__(this->p34);
    *(void**)this = (void*)0x13ef094;
}
