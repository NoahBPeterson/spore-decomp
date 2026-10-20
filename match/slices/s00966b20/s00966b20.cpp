// Slice s00966b20 -- UTFWinControls WinButton / ButtonDrawable factories,
// CascadeEffect, CircularAllocator helpers, WinComboBox and small drawables.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// MSVC rejects __thiscall on free functions (C3865), so every function whose
// object really arrives in ecx is written as a member of a tiny opaque struct.
// The member reads its object through `this`; a local `uint8_t* this_` alias
// keeps the body readable.

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef signed int     int32_t;

#define F(o, off)  (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FB(o, off) (*(uint8_t*)((uint8_t*)(o) + (off)))
#define FF(o, off) (*(float*)((uint8_t*)(o) + (off)))

// ---------------------------------------------------------------------------
// Free helpers / allocations.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_009512c0();                                  // 0x9512c0
extern "C" void* __cdecl FUN_009512d0(uint32_t size, uint32_t align,
                                      const char* name, void* heap);       // 0x9512d0
extern "C" void  __cdecl FUN_00951330(void* p);                            // 0x951330
struct S_962740 { void __thiscall m(); };                                  // 0x962740
struct S_962a10 { void* __thiscall m(); };                                  // 0x962a10
extern "C" void  __cdecl FUN_009614a0();                                   // 0x9614a0
struct S_9614a0 { void __thiscall m(); };                                  // 0x9614a0 SerUpdate
struct S_9609b0 { void __thiscall m(); };                                  // 0x9609b0 InvalidateLayout
struct S_961e80 { bool __thiscall m(); };                                  // 0x961e80
extern "C" void  __cdecl FUN_00830150(int);                                // 0x830150
extern "C" void  __cdecl FUN_00830280(int);                                // 0x830280
struct S_830150 { void __thiscall m(uint32_t); };                          // 0x830150 SetMode2
struct S_830280 { void __thiscall m(uint32_t); };                          // 0x830280 SetMode1
extern "C" void  __cdecl FUN_008323d0(void*);                              // 0x8323d0
extern "C" void  __cdecl FUN_0089c540(void*);                              // 0x89c540
struct S_8323d0 { void __thiscall m(); };                                  // 0x8323d0
struct S_89c540 { void __thiscall m(); };                                  // 0x89c540
struct S_89d820 { void __thiscall m(int); };                               // 0x89d820
struct S_898bd0 { void __thiscall m(int); };                               // 0x898bd0
extern "C" void* __cdecl FUN_00957f30();                                   // 0x957f30
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name,
                                       int, int, int, int);                // 0xf473a0
extern "C" void  __cdecl FUN_00f47380(void* p);                            // 0xf47380
extern "C" void* __cdecl FUN_0093a560(int, int);                           // 0x93a560
extern "C" void  __cdecl FUN_0093a1a0(int);                                // 0x93a1a0
struct Stopwatch {
    void* __thiscall Ctor(int, int);   // 0x93a560
    void  __thiscall SetUnits(int);    // 0x93a1a0
};
struct S_93a3a0 { double __thiscall m(); };                                // 0x93a3a0
struct S_571e80 { void   __thiscall m(); };                                // 0x571e80
struct S_93a2e0 { void   __thiscall m(); };                                // 0x93a2e0
extern float g_13f9428;                                                    // 0.001f

static inline const uint32_t& max_u32(const uint32_t& a, const uint32_t& b)
{
    return a < b ? b : a;
}

// Generic virtual-call helpers over raw this-pointers.
static inline void VCALL0(void* o, int off) {
    ((void (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline uint32_t VCALL0R(void* o, int off) {
    return ((uint32_t (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline void VCALL1(void* o, int off, uint32_t a) {
    ((void (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline uint32_t VCALL1R(void* o, int off, uint32_t a) {
    return ((uint32_t (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline void* VCALL1P(void* o, int off, uint32_t a) {
    return ((void* (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline void VCALL2(void* o, int off, uint32_t a, uint32_t b) {
    ((void (__thiscall*)(void*, uint32_t, uint32_t))(*(void***)o)[off / 4])(o, a, b);
}
static inline uint32_t VCALL2R(void* o, int off, uint32_t a, uint32_t b) {
    return ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))(*(void***)o)[off / 4])(o, a, b);
}

// ---------------------------------------------------------------------------
// Member-function carriers (one tiny struct per code object).
// ---------------------------------------------------------------------------
struct S_966b20 { uint8_t __thiscall m(uint32_t, float*); };
struct S_966bb0 { uint8_t __thiscall m(uint32_t, float*); };
struct S_966c70 { void     __thiscall m(); };
struct S_966dc0 { void*    __thiscall m(); };
struct S_966df0 { void*    __thiscall m(uint8_t); };
struct S_966e40 { void     __thiscall m(); };
struct S_966f90 { void*    __thiscall m(); };
struct S_967120 { void*    __thiscall m(uint8_t); };
struct S_967300 { void     __thiscall m(float); };
struct S_967320 { void     __thiscall m(float); };
struct S_9675c0 { void*    __thiscall m(); };
struct S_9673b0 { uint32_t __thiscall m(void*, uint8_t*); };
struct S_967690 { void     __thiscall m(); };
struct S_9676a0 { uint32_t __thiscall m(uint32_t, uint32_t); };
struct S_9676f0 { void     __thiscall m(uint32_t, const char*); };
struct S_967770 { uint32_t __thiscall m(uint32_t); };
struct S_9677d0 { uint32_t* __thiscall m(uint32_t); };
struct S_967980 { void     __thiscall m(); };
struct S_9679c0 { bool     __thiscall m(); };
struct S_967a60 { void     __thiscall m(uint32_t); };
struct S_967d20 { void     __thiscall m(); };
struct S_967ac0 { void     __thiscall m(void*); };
struct S_967b10 { bool     __thiscall m(uint32_t, uint32_t, uint32_t, int); };
struct S_967bc0 { bool     __thiscall m(uint32_t, uint32_t, uint32_t, uint8_t); };
struct S_967c90 { uint8_t  __thiscall m(float, float, uint32_t); };
struct S_967cd0 { uint8_t  __thiscall m(int, void*); };
struct S_967d10 { uint8_t  __thiscall m(); };

// ---------------------------------------------------------------------------
// 00966b20 / 00966bb0 -- combo-box alpha / uv lookup helpers.
// ---------------------------------------------------------------------------
extern uint32_t g_1440f84;
extern uint32_t g_1485720;
extern float    g_1488874;   // 0.1f
extern float    g_13eb8a0;

// @ 0x00966b20
uint8_t S_966b20::m(uint32_t param_2, float* param_3)
{
    if (F(this, 0x10) != 0) {
        uint32_t v = 0;
        switch (param_2 & 7) {
        case 0: v = (((uint8_t)param_2 & 8) | 4) >> 2; break;
        case 1: v = 0; break;
        case 2: v = 2; break;
        case 3: v = 3; break;
        }
        param_3[0] = (float)v * g_13eb8a0;
        param_3[1] = 0.0f;
        param_3[2] = (float)(v + 1) * g_13eb8a0;
        param_3[3] = *(float*)&g_1485720;
        return 1;
    }
    return 0;
}

// @ 0x00966bb0
uint8_t S_966bb0::m(uint32_t param_2, float* param_3)
{
    if (F(this, 0x10) != 0) {
        uint32_t v = 0;
        switch (param_2 & 7) {
        case 0:
        case 1: v = (uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3; break;
        case 2: v = ((uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3) + 1; break;
        case 3: v = ((uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3) + 2; break;
        }
        param_3[0] = (float)v * *(float*)&g_1440f84;
        param_3[1] = 0.0f;
        param_3[2] = (float)(v + 1) * *(float*)&g_1440f84;
        param_3[3] = *(float*)&g_1485720;
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 00966c70 -- WinComboBox::UpdateSelection (timer-driven child cycling).
// ---------------------------------------------------------------------------
// @ 0x00966c70
void S_966c70::m()
{
    uint8_t* this_ = (uint8_t*)this;
    if (FB(this_, 0x210) == 0)
        return;

    void* sub4 = this_ + 4;
    void** vt = *(void***)sub4;
    uint32_t fn = ((uint32_t*)vt)[0x7c / 4];
    FB(this_, 0x210) = 0;
    ((void (__thiscall*)(void*, int, int))fn)(sub4, 8, 0);

    VCALL0(this_, 0x9c);
    VCALL0(this_, 0xa0);

    uint8_t* child = *(uint8_t**)(this_ + 0x38);
    if (child != 0 && F(this_, 0x214) == 3 &&
        (FB(this_, 0xac) & 4) != 0 && F(this_, 0x220) != 0) {
        void* begin;
        VCALL1(child + 4, 0xcc, (uint32_t)&begin);
        void* end;
        uint32_t* endp = (uint32_t*)VCALL1P(child + 4, 0xd0, (uint32_t)&end);
        while (begin != (void*)*endp) {
            uint8_t* node = (uint8_t*)begin;
            uint8_t* obj = node - 4;
            if (obj != 0) {
                void* cast = VCALL1P(obj, 0x0c, 0x8ed27e7a);
                if (cast != 0 && cast != (void*)(this_ + 0x20c)) {
                    if (VCALL0R(cast, 0x40) == F(this_, 0x220) &&
                        (VCALL0R(cast, 0x20) & 0x20) == 0) {
                        VCALL2(cast, 0x28, 4, 0);
                    }
                }
            }
            begin = *(void**)node;
            endp = (uint32_t*)VCALL1P(child + 4, 0xd0, (uint32_t)&end);
        }
    }

    VCALL2(this_ + 0x20c, 0x28, 0x20, 0);
    VCALL0(this_ + 4, 0x90);
}

// ---------------------------------------------------------------------------
// 00966dc0 -- ButtonDrawableRadio ctor / 00966df0 -- its deleting dtor.
// ---------------------------------------------------------------------------
// @ 0x00966dc0
void* S_966dc0::m()
{
    void* this_ = this;
    F(this_, 0x04) = 0x13fa72c;
    F(this_, 0x08) = 0;
    F(this_, 0x0c) = 0x13fa72c;
    F(this_, 0x00) = 0x1441088;
    F(this_, 0x04) = 0x1441070;
    F(this_, 0x0c) = 0x1441058;
    F(this_, 0x10) = 0;
    FB(this_, 0x14) = 0;
    return this_;
}

// @ 0x00966df0
void* S_966df0::m(uint8_t param_2)
{
    void* this_ = this;
    void* img = (void*)F(this_, 0x10);
    F(this_, 0x00) = 0x1441088;
    F(this_, 0x04) = 0x1441070;
    F(this_, 0x0c) = 0x1441058;
    if (img != 0)
        VCALL0(img, 0x04);
    F(this_, 0x0c) = 0x13eb938;
    F(this_, 0x04) = 0x13eb938;
    F(this_, 0x00) = 0x13eb938;
    if ((param_2 & 1) != 0)
        FUN_00951330(this_);
    return this_;
}

// ---------------------------------------------------------------------------
// 00966e40 / 00967120 -- WinButton dtor & deleting dtor.
// ---------------------------------------------------------------------------
// @ 0x00966e40
void S_966e40::m()
{
    void* this_ = this;
    S_8323d0* ll = (S_8323d0*)((uint8_t*)this_ + 0x7b0);
    F(this_, 0x00) = 0x1441240;
    F(this_, 0x04) = 0x1441120;
    F(this_, 0x20c) = 0x14410b0;
    ll->m();
    ((S_89c540*)((uint8_t*)this_ + 0x280))->m();
    F(this_, 0x20c) = 0x13eb938;
    ((S_962740*)this_)->m();
}

// @ 0x00967120
void* S_967120::m(uint8_t param_2)
{
    void* this_ = this;
    S_8323d0* ll = (S_8323d0*)((uint8_t*)this_ + 0x7b0);
    F(this_, 0x00) = 0x1441240;
    F(this_, 0x04) = 0x1441120;
    F(this_, 0x20c) = 0x14410b0;
    ll->m();
    ((S_89c540*)((uint8_t*)this_ + 0x280))->m();
    F(this_, 0x20c) = 0x13eb938;
    ((S_962740*)this_)->m();
    if ((param_2 & 1) != 0)
        FUN_00951330(this_);
    return this_;
}

// ---------------------------------------------------------------------------
// 00966ed0 / 00966f30 -- drawable factories (0x18-byte objects).
// ---------------------------------------------------------------------------
struct DrawableStd {
    uint32_t v00, v04, v08, v0c, v10;
    uint8_t  v14, pad[3];
};

struct BasicFactoryStd  { DrawableStd* __thiscall CreateInstance(uint32_t, void*); };
struct BasicFactoryRadio{ DrawableStd* __thiscall CreateInstance(uint32_t, void*); };

// @ 0x00966ed0
DrawableStd* BasicFactoryStd::CreateInstance(uint32_t, void* heap)
{
    if (heap == 0)
        heap = FUN_009512c0();
    DrawableStd* p = (DrawableStd*)FUN_009512d0(
        0x18, 4, "UTFWin/EA::UTFWinControls::ButtonDrawableStandard", heap);
    if (p != 0) {
        p->v04 = 0x13fa72c;
        p->v08 = 0;
        p->v0c = 0x13fa72c;
        p->v10 = 0;
        p->v14 = 0;
        p->v00 = 0x141788c;
        p->v04 = 0x1417874;
        p->v0c = 0x141785c;
    }
    return p;
}

// @ 0x00966f30
DrawableStd* BasicFactoryRadio::CreateInstance(uint32_t, void* heap)
{
    if (heap == 0)
        heap = FUN_009512c0();
    DrawableStd* p = (DrawableStd*)FUN_009512d0(
        0x18, 4, "UTFWin/EA::UTFWinControls::ButtonDrawableRadio", heap);
    if (p != 0) {
        p->v04 = 0x13fa72c;
        p->v08 = 0;
        p->v0c = 0x13fa72c;
        p->v10 = 0;
        p->v14 = 0;
        p->v00 = 0x14178b0;
        p->v04 = 0x1417874;
        p->v0c = 0x141785c;
    }
    return p;
}

// ---------------------------------------------------------------------------
// 00966f90 -- WinButton ctor.
// ---------------------------------------------------------------------------
// @ 0x00966f90
void* S_966f90::m()
{
    void* this_ = this;
    ((S_962a10*)this_)->m();
    F(this_, 0x20c) = 0x1440fe8;
    F(this_, 0x00) = 0x1441240;
    F(this_, 0x04) = 0x1441120;
    F(this_, 0x20c) = 0x14410b0;
    F(this_, 0x214) = 1;
    F(this_, 0x21c) = 1;
    FB(this_, 0x210) = 0;
    F(this_, 0x218) = 0;
    F(this_, 0x220) = 0;
    F(this_, 0x224) = 0;
    FF(this_, 0x228) = 0.0f;
    FF(this_, 0x22c) = 0.0f;
    FF(this_, 0x230) = 1.0f;
    FF(this_, 0x234) = 1.0f;
    FF(this_, 0x238) = 0.0f;
    FF(this_, 0x23c) = 0.0f;
    FF(this_, 0x240) = 1.0f;
    FF(this_, 0x244) = 1.0f;
    FF(this_, 0x248) = 1.0f;
    FF(this_, 0x24c) = 1.0f;
    FF(this_, 0x250) = 1.0f;
    FF(this_, 0x254) = 1.0f;
    FF(this_, 0x258) = 1.0f;
    FF(this_, 0x25c) = 1.0f;
    ((S_89d820*)((uint8_t*)this_ + 0x280))->m(0);
    ((S_898bd0*)((uint8_t*)this_ + 0x7b0))->m(0);
    {
        uint8_t* l = (uint8_t*)this_ + 0x860;
        F(l, 0x00) = 0;
        F(l, 0x04) = 2;
        F(l, 0x08) = 3;
        FF(l, 0x14) = 0.0f;
        FF(l, 0x18) = 0.0f;
        FF(l, 0x0c) = 0.0f;
        FF(l, 0x10) = 0.0f;
        F(l, 0x24) = 0;
    }
    ((S_830150*)((uint8_t*)this_ + 0x860))->m(2);
    F(this_, 0x260) = 0;
    F(this_, 0x264) = 0;
    F(this_, 0x268) = 0;
    F(this_, 0x26c) = 0;
    F(this_, 0x270) = 0;
    F(this_, 0x274) = 0;
    F(this_, 0x278) = 0;
    F(this_, 0x27c) = 0;
    F(this_, 0xac) |= (F(this_, 0x2c) >> 1) & 1;
    if (FB(this_, 0x210) == 0) {
        void* s4 = (uint8_t*)this_ + 4;
        void** vt = *(void***)s4;
        void (__thiscall* fn)(void*, int, int) =
            (void (__thiscall*)(void*, int, int))vt[0x7c / 4];
        FB(this_, 0x210) = 1;
        fn(s4, 8, 1);
    }
    return this_;
}

// @ 0x009671c0
extern "C" void* __cdecl FUN_009671c0(uint32_t param_1, uint32_t param_2,
                                      uint32_t param_3)
{
    void* heap = FUN_009512c0();
    void* p = FUN_009512d0(0x888, 4, "UTFWin/WinButton", heap);
    if (p == 0)
        return 0;
    uint8_t* obj = (uint8_t*)((S_966f90*)p)->m();
    if (obj == 0)
        return 0;
    uint8_t* sub = obj + 0x20c;
    if (sub != 0) {
        VCALL1(sub, 0x1c, param_1);
        VCALL1(sub, 0x30, param_2);
        VCALL1(sub, 0x44, param_3);

        void* heap2 = FUN_009512c0();
        DrawableStd* d = (DrawableStd*)FUN_009512d0(
            0x18, 4, "UTFWin/ButtonDrawableStandard", heap2);
        uint8_t* dp;
        if (d == 0) {
            dp = 0;
        } else {
            dp = (uint8_t*)d + 0x0c;
            d->v04 = 0x13fa72c;
            d->v08 = 0;
            d->v0c = 0x13fa72c;
            d->v10 = 0;
            d->v14 = 0;
            d->v00 = 0x141788c;
            d->v04 = 0x1417874;
            d->v0c = 0x141785c;
        }
        VCALL1(sub, 0x60, (uint32_t)dp);
        VCALL2(sub, 0x4c, 0, 0xff00044a);
        VCALL2(sub, 0x4c, 3, 0xff0055e6);
    }
    return sub;
}

// @ 0x00967300
void S_967300::m(float v)
{
    void* this_ = this;
    if (v < 0.0f)
        FF(this_, 4) = 0.0f;
    else
        FF(this_, 4) = v;
}

// @ 0x00967320
void S_967320::m(float v)
{
    void* this_ = this;
    if (v < 0.0f)
        FF(this_, 8) = 0.0f;
    else
        FF(this_, 8) = v;
}

// ---------------------------------------------------------------------------
// 009673b0 -- CascadeEffect::DoMessage.
// ---------------------------------------------------------------------------
// @ 0x009673b0
uint32_t S_9673b0::m(void* param_2, uint8_t* param_3)
{
    void* this_ = this;
    int msg = *(int*)(param_3 + 8);

    if (msg == 0xc) {
        if (F(this_, 0x30) == 0)
            return 0;
        double lo = ((S_93a3a0*)((uint8_t*)this_ + 0x18))->m();
        float f = ((float)lo * FF(this_, 0x2c)) * g_13f9428;
        if (FB(this_, 0x38) == 0) {
            if (f < FF(this_, 0x14))
                return 0;
        } else {
            if (f < FF(this_, 0x10))
                return 0;
            FB(this_, 0x38) = 0;
        }
        ((S_571e80*)((uint8_t*)this_ + 0x18))->m();

        if (F(this_, 0x30) > 0) {
            void* e = VCALL1P(param_2, 0xd0, 0);
            uint8_t* cur = *(uint8_t**)((uint8_t*)this_ + 0x34);
            if (cur == *(uint8_t**)e) {
                F(this_, 0x30) = 0;
                ((S_93a2e0*)((uint8_t*)this_ + 0x18))->m();
                VCALL0(param_2, 0xa0);
                return 0;
            }
            uint8_t* base = cur - 4;
            void** vt = *(void***)base;
            void (__thiscall* fn)(void*, int, uint32_t) =
                (void (__thiscall*)(void*, int, uint32_t))vt[0x7c / 4];
            fn(base, 1, (uint32_t)FB(this_, 0x39));
            F(this_, 0x34) = *(uint32_t*)cur;
            return 0;
        }
        void* e = VCALL1P(param_2, 0xcc, 0);
        uint8_t* cur = *(uint8_t**)((uint8_t*)this_ + 0x34);
        if (cur == *(uint8_t**)e) {
            F(this_, 0x30) = 0;
            ((S_93a2e0*)((uint8_t*)this_ + 0x18))->m();
            VCALL0(param_2, 0xa0);
            return 0;
        }
        uint8_t* prev = *(uint8_t**)(cur + 4);
        F(this_, 0x34) = (uint32_t)prev;
        {
            uint8_t* base = prev - 4;
            void** vt = *(void***)base;
            void (__thiscall* fn)(void*, int, uint32_t) =
                (void (__thiscall*)(void*, int, uint32_t))vt[0x7c / 4];
            fn(base, 1, (uint32_t)FB(this_, 0x39));
        }
        return 0;
    }

    if (msg == 0xe) {
        int d = *(int*)(param_3 + 0xc);
        if (d != 1 && d != -1)
            return 0;
        uint32_t sel = VCALL0R(param_2, 0x28);
        void* e0 = VCALL1P(param_2, 0xd0, 0);
        void* e1 = VCALL1P(param_2, 0xcc, 0);
        if (*(uint32_t*)e1 == *(uint32_t*)e0)
            return 0;
        uint32_t t = sel & 1;
        int sign = (int)t + (int)t - 1;
        if (F(this_, 0x30) == 0) {
            FB(this_, 0x38) = 1;
            void* res = (sign > 0) ? VCALL1P(param_2, 0xcc, 0)
                                   : VCALL1P(param_2, 0xd0, 0);
            F(this_, 0x34) = *(uint32_t*)res;
        }
        F(this_, 0x30) = (uint32_t)sign;
        FB(this_, 0x39) = (uint8_t)t;
        ((S_571e80*)((uint8_t*)this_ + 0x18))->m();
        VCALL0(param_2, 0x9c);
        return 0;
    }

    return 0;
}

// ---------------------------------------------------------------------------
// 009675c0 -- CascadeEffect ctor.
// ---------------------------------------------------------------------------
// @ 0x009675c0
void* S_9675c0::m()
{
    void* this_ = this;
    F(this_, 0x04) = 0x13fa72c;
    F(this_, 0x08) = 0;
    F(this_, 0x0c) = 0x1444434;
    FF(this_, 0x10) = 0.0f;
    F(this_, 0x00) = 0x14414b8;
    F(this_, 0x04) = 0x144149c;
    F(this_, 0x0c) = 0x1441478;
    FF(this_, 0x14) = g_1488874;
    Stopwatch* sw = (Stopwatch*)((uint8_t*)this_ + 0x18);
    sw->Ctor(0, 0);
    F(this_, 0x30) = 0;
    FB(this_, 0x38) = 0;
    FB(this_, 0x39) = 0;
    sw->SetUnits(4);
    return this_;
}

// ---------------------------------------------------------------------------
// 00967690 / 009676a0 / 009676f0 / 00967770 / 009677d0 -- CircularAllocator.
// ---------------------------------------------------------------------------
// @ 0x00967690
void S_967690::m()
{
    uint32_t* this_ = (uint32_t*)this;
    this_[3] = this_[0];
    this_[2] = this_[0];
}

// @ 0x009676a0
uint32_t S_9676a0::m(uint32_t param_2, uint32_t param_3)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t m = ~(((param_3 - 1) | 7) + 1 - 1);
    uint32_t cur = this_[2];
    uint32_t last = this_[3];
    uint32_t a;
    if (cur > last) {
        a = (cur - param_2) & m;
        if (a <= last) {
            return 0;
        }
        this_[2] = a;
        return a;
    }
    a = (cur - param_2) & m;
    if (a >= this_[0]) {
        this_[2] = a;
        return a;
    }
    a = (this_[1] - param_2) & m;
    if (a <= last) {
        return 0;
    }
    this_[2] = a;
    return a;
}

// @ 0x009676f0
void S_9676f0::m(uint32_t param_2, const char* param_3)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t base = this_[0];
    if (this_[1] - base == param_2)
        return;
    if (base != 0) {
        FUN_00f47380((void*)base);
        this_[3] = 0;
        this_[2] = 0;
        this_[1] = 0;
        this_[0] = 0;
    }
    if (param_2 > 0) {
        if (param_3 == 0)
            param_3 = "UTFWin/CircularAllocator";
        void* p = FUN_00f473a0(param_2, param_3, 0, 0, 0, 0);
        this_[0] = (uint32_t)p;
        this_[1] = (uint32_t)p + param_2;
        this_[3] = (uint32_t)p;
        this_[2] = (uint32_t)p;
    }
}

// @ 0x00967770
uint32_t S_967770::m(uint32_t param_2)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t align = ((param_2 - 1) | 7) + 1;
    uint32_t cur = this_[2];
    uint32_t last = this_[3];
    if (cur <= last) {
        uint32_t m = ~(align - 1);
        uint32_t b = this_[1] - ((last + align) & m);
        uint32_t a = cur - ((this_[0] + align - 1) & m);
        return max_u32(a, b);
    }
    uint32_t m = ~(align - 1);
    return cur - ((last + align) & m);
}

// @ 0x009677d0
uint32_t* S_9677d0::m(uint32_t param_2)
{
    uint32_t* this_ = (uint32_t*)this;
    this_[0] = 0;
    this_[1] = 0;
    this_[2] = 0;
    this_[3] = 0;
    if (param_2 == 0)
        return this_;
    if (!(param_2 > 0))
        return this_;
    void* p = FUN_00f473a0(param_2, "UTFWin/CircularAllocator", 0, 0, 0, 0);
    this_[0] = (uint32_t)p;
    this_[1] = (uint32_t)p + param_2;
    this_[3] = (uint32_t)p;
    this_[2] = (uint32_t)p;
    return this_;
}

// ---------------------------------------------------------------------------
// 00967890 / 009678f0 -- serialization via the combo-box sub-object.
// ---------------------------------------------------------------------------
// @ 0x00967890
extern "C" uint8_t __cdecl FUN_00967890(uint32_t param_1, uint32_t param_2)
{
    uint32_t obj = F(param_1, 4);
    if (obj != 0) {
        uint8_t* sub = (uint8_t*)(obj + 0x20c);
        VCALL0(sub, 0x2c);
        uint32_t arr = F(param_2, 4);
        if (arr != 0) {
            for (uint32_t i = 0; i < F(param_2, 8); i++)
                VCALL1(sub, 0x20, *(uint32_t*)(arr + i * 4));
        }
        return 1;
    }
    return 0;
}

// @ 0x009678f0
extern "C" uint8_t __cdecl FUN_009678f0(uint32_t* param_1, uint32_t param_2,
                                        uint32_t param_3, uint32_t* param_4)
{
    uint32_t obj = F(param_2, 4);
    if (obj != 0) {
        uint8_t* sub = (uint8_t*)(obj + 0x20c);
        uint32_t n = VCALL0R(sub, 0x3c);
        param_1[2] = n;

        uint32_t* arr = (uint32_t*)((void* (__thiscall*)(void*, uint32_t, int))
            ((void**)*(void**)param_4)[0])(param_4, n * 4, 4);
        param_1[1] = (uint32_t)arr;

        uint32_t kind = (*(uint16_t*)(param_3 + 0xc)) & 0xfff;
        param_1[0] = ((uint32_t*)0x154eea0)[kind];

        if (arr != 0) {
            uint32_t* dst = arr;
            for (uint32_t i = 0; i < n; i++, dst++)
                *dst = VCALL1R(sub, 0x34, i);
        }
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 00967980 / 009679c0 / 00967a60 / 00967d20 -- window lifecycle.
// ---------------------------------------------------------------------------
// @ 0x00967980
void S_967980::m()
{
    void* this_ = this;
    VCALL1(this_, 0x8c, 1);
    uint8_t* cb = (uint8_t*)this_ + 0x290;
    ((S_830280*)cb)->m(F(this_, 0x290));
    ((S_830150*)cb)->m(F(this_, 0x294));
    ((S_9614a0*)this_)->m();
}

// @ 0x009679c0
bool S_9679c0::m()
{
    void* this_ = this;
    void* mgr = FUN_00957f30();
    if (mgr != 0) {
        void* m2 = FUN_00957f30();
        void* combo = (void*)VCALL0R(m2, 0x84);
        if (combo != 0) {
            if (VCALL1R(combo, 0x0c, 0xaf1ee902)) {
                if (VCALL0R(combo, 0x1c) == (uint32_t)this_) {
                    void* m3 = FUN_00957f30();
                    ((void (__thiscall*)(void*, void*, int))
                        (*(void***)m3)[0x78 / 4])(m3, combo, 0);
                }
            }
        }
    }
    return ((S_961e80*)this_)->m();
}

// @ 0x00967a60
void S_967a60::m(uint32_t param_2)
{
    uint32_t* v = *(uint32_t**)((uint8_t*)this - 0x20c);
    F(this, 0x30) = param_2;
    ((void (__thiscall*)(void*, int))(void*)v[0x8c / 4])((uint8_t*)this - 0x20c, 1);
}

// @ 0x00967d20
void S_967d20::m()
{
    void* this_ = this;
    uint8_t* base = (uint8_t*)this_ - 4;
    void** vt = *(void***)base;
    void (__thiscall* fn)(void*, int) = (void (__thiscall*)(void*, int))vt[0x8c / 4];
    fn(base, 1);
    ((S_9609b0*)this_)->m();
}

// ---------------------------------------------------------------------------
// 00967ac0 -- WinComboBox::SetDrawable.
// ---------------------------------------------------------------------------
// @ 0x00967ac0
void S_967ac0::m(void* param_2)
{
    void* this_ = this;
    uint32_t arg = param_2 ? VCALL0R(param_2, 0x10) : 0;
    VCALL1((uint8_t*)this_ - 0x208, 0xb0, arg);
    VCALL1((uint8_t*)this_ - 0x20c, 0x8c, 1);
}

// ---------------------------------------------------------------------------
// 00967b10 -- WinComboBox::OnMouseDown.
// ---------------------------------------------------------------------------
// @ 0x00967b10
bool S_967b10::m(uint32_t a, uint32_t b, uint32_t param_4, int param_5)
{
    void* this_ = this;
    if (param_5 != 8)
        return 0;
    uint8_t* s4 = (uint8_t*)this_ + 4;
    uint32_t u = VCALL0R(s4, 0x28);
    if ((u & 2) == 0)
        return 1;

    uint32_t r = VCALL2R(this_, 0x9c, a, b);
    F(this_, 0x218) = r;
    if (r != 0xffffffff) {
        uint8_t* list = (uint8_t*)F(this_, 0x34);
        void** lvt = *(void***)list;
        if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 1) != s4)
            ((void (__thiscall*)(void*, int, void*))lvt[0x58 / 4])(list, 1, s4);
        if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 0) != s4)
            ((void (__thiscall*)(void*, int, void*))lvt[0x58 / 4])(list, 0, s4);
        VCALL0(this_, 0x94);
        VCALL0(s4, 0x90);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 00967bc0 -- WinComboBox::OnMouseUp.
// ---------------------------------------------------------------------------
// @ 0x00967bc0
bool S_967bc0::m(uint32_t a, uint32_t b, uint32_t param_4, uint8_t flags)
{
    void* this_ = this;
    if ((flags & 8) != 0)
        return 0;

    uint8_t* s4 = (this_ != 0) ? (uint8_t*)this_ + 4 : 0;
    uint8_t* list = (uint8_t*)F(this_, 0x34);
    void** lvt = *(void***)list;

    if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 1) == s4)
        ((void (__thiscall*)(void*, int, void*))lvt[0x5c / 4])(list, 1, (uint8_t*)this_ + 4);
    if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 0) == (uint8_t*)this_ + 4)
        ((void (__thiscall*)(void*, int, void*))lvt[0x5c / 4])(list, 0, (uint8_t*)this_ + 4);

    void** vt = *(void***)this_;
    void* fn = vt[0x9c / 4];
    uint8_t* self4 = (uint8_t*)this_ + 4;

    if (FB(this_, 0x245) != 0) {
        uint32_t r = ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))fn)(this_, a, b);
        F(this_, 0x218) = r;
        F(this_, 0x214) = 0xffffffff;
        VCALL0(self4, 0x90);
        return 1;
    }
    F(this_, 0x218) = 0xffffffff;
    uint32_t r = ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))fn)(this_, a, b);
    F(this_, 0x214) = r;
    VCALL0(self4, 0x90);
    return 1;
}

// ---------------------------------------------------------------------------
// 00967c90 -- WinComboBox::OnMouseMove.
// ---------------------------------------------------------------------------
// @ 0x00967c90
uint8_t S_967c90::m(float a, float b, uint32_t)
{
    void* this_ = this;
    uint32_t r = ((uint32_t (__thiscall*)(void*, float, float))
        (*(void***)this_)[0x9c / 4])(this_, a, b);
    if (F(this_, 0x214) != r) {
        uint8_t* s4 = (uint8_t*)this_ + 4;
        F(this_, 0x214) = r;
        VCALL0(s4, 0x90);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 00967cd0 -- selection-changed notify.
// ---------------------------------------------------------------------------
// @ 0x00967cd0
uint8_t S_967cd0::m(int param_2, void* param_3)
{
    void* this_ = this;
    if (param_2 == 1) {
        void* s4 = (this_ != 0) ? (uint8_t*)this_ + 4 : 0;
        if (param_3 != s4 && F(this_, 0x214) != 0xffffffff) {
            F(this_, 0x214) = 0xffffffff;
            VCALL0((uint8_t*)this_ + 4, 0x90);
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 00967d10 -- invalidate forwarder.
// ---------------------------------------------------------------------------
// @ 0x00967d10
uint8_t S_967d10::m()
{
    void* this_ = this;
    VCALL0(this_, 0x90);
    return 1;
}
