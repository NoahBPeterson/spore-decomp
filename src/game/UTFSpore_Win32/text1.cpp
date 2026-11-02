// src/game/UTFSpore_Win32/text1.cpp -- migrated from slice(s) s009886d0, s008337d0, s00832790 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/text1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char g_vtblSubWin0;    // 0x1414b10
extern char g_vtblSubWin4;    // 0x14431f8
extern char g_vtblMsg0;       // 0x13eb90c  (UI::BehaviorMessage)
extern char g_vtblMsg1;       // 0x13eb844
extern char g_allocTag;       // 0x13f6b3c  EASTL allocator name
extern "C" void  FUN_00b5f950(void);          // AutoRefCount::operator=
extern "C" void* FUN_009512c0(void);
extern "C" void* FUN_009512d0(void);
extern "C" void  FUN_00962a10(void);          // Window::Window
extern "C" void* FUN_00883860(void);          // EA::Messaging::GetServer
extern "C" void  FUN_0089d820(void);          // Typesetter ctor
extern "C" void  FUN_00898bd0(void);          // LineLayout ctor
extern "C" void  FUN_0089c540(void);          // Typesetter dtor
extern "C" void  FUN_008323d0(void);          // LineLayout dtor
extern "C" void  FUN_008975c0(void);
extern "C" void  FUN_0089dc00(void);
extern "C" void* FUN_00885bd0(void);          // EA::Text::GetStyleManager
extern "C" void  FUN_00894670(void);          // StyleManager::GetStyle
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d); // EASTL allocator
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#include <math.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedExchange)

// ---- items of slice s00832790 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void*  (__thiscall *VFi)(void*);
typedef void   (__thiscall *VFv)(void*);
static inline void** VT(void* o) { return *(void***)o; }
extern char g_vtblSubWin0;    // 0x1414b10
extern char g_vtblSubWin4;    // 0x14431f8
extern char g_vtblMsg0;       // 0x13eb90c  (UI::BehaviorMessage)
extern char g_vtblMsg1;       // 0x13eb844
extern char g_allocTag;       // 0x13f6b3c  EASTL allocator name
extern "C" void  FUN_00b5f950(void);          // AutoRefCount::operator=
extern "C" void* FUN_009512c0(void);
extern "C" void* FUN_009512d0(void);
extern "C" void  FUN_00962a10(void);          // Window::Window
extern "C" void* FUN_00883860(void);          // EA::Messaging::GetServer
extern "C" void  FUN_0089d820(void);          // Typesetter ctor
extern "C" void  FUN_00898bd0(void);          // LineLayout ctor
extern "C" void  FUN_0089c540(void);          // Typesetter dtor
extern "C" void  FUN_008323d0(void);          // LineLayout dtor
extern "C" void  FUN_008975c0(void);
extern "C" void  FUN_0089dc00(void);
extern "C" void* FUN_00885bd0(void);          // EA::Text::GetStyleManager
extern "C" void  FUN_00894670(void);          // StyleManager::GetStyle
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d); // EASTL allocator
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
struct Subtitles {
    void*    vptr0;      // +0x00
    uint32_t rc;         // +0x04
    void*    vptr1;      // +0x08
    uint32_t f0c;        // +0x0c
    char     sw[0x18];   // +0x10 stopwatch
    float    f28;        // +0x28
    float    f2c;        // +0x2c
    float    f30;        // +0x30
    float    f34;        // +0x34
    uint8_t  b38;        // +0x38
    uint8_t  b39;        // +0x39
    char     pad3a[2];
    uint32_t f3c;        // +0x3c
    char     anim[0x20]; // +0x40
    void*    mpTextWin;  // +0x60
    void*    mpWindow;   // +0x64
    float    v68, v6c, v70, v74;   // +0x68
    float    v78, v7c, v80, v84;   // +0x78
    uint32_t s88, s8c, s90, s94, s98;  // +0x88
    wchar_t  buf[0x100]; // +0x9c

    Subtitles();
    void Clear();
    bool Set(const wchar_t* text, float a2, int a3, bool a4, float a5);
    bool SetWindow(void* window);
};
struct Rect { float left, top, right, bottom; };
// ---- items of slice s00832790 end

// ---- items of slice s008337d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_vtblTextWin0;    // 0x141ac90
extern char g_vtblTextWin4;    // 0x141ab70
extern char g_vtblTextWin20c;  // 0x141ab34
extern "C" void  FUN_00989000(void);   // WinText ctor
#pragma intrinsic(_InterlockedExchange)
class cSPUITextWin { public:
    void* vptr0;        // +0x000
    void* vptr4;        // +0x004
    char  pad8[0x204];
    void* vptr20c;      // +0x20c
    cSPUITextWin();
};
// ---- items of slice s008337d0 end

// ---- items of slice s009886d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Text_GetStyleManager(int unk);                      // 0x885bd0
extern "C" void  __cdecl FUN_00951330(void*);                                   // 0x951330
typedef unsigned int uintptr_t;
#define F(o, off)   (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FF(o, off)  (*(float*)((uint8_t*)(o) + (off)))
#define GF(addr)    (*(float*)(uintptr_t)(addr))
struct Iface {
    virtual void  s00();                             // slot 0
    virtual void  s01();                             // 0x04
    virtual void  s02();
    virtual void* s03();                             // 0x0c
    virtual void  s04();                             // 0x10
    virtual void* s05();                             // 0x14  returns object with vtable
    virtual void  s06();
    virtual uint8_t s07(uint32_t);                   // 0x1c
    virtual char  s08(void*, uint32_t, uint32_t);    // 0x20
    virtual void  s09();
    virtual uint32_t s10();                          // 0x28
virtual void  s11();
virtual void s12();
virtual void s13();
virtual void  s14();
virtual void s15();
    virtual void  s16(void*, int);                   // 0x40
virtual void  s17();
virtual void s18();
virtual void s19();
virtual void  s20();
virtual void s21();
virtual void s22();
    virtual void  s23(uint32_t, uint32_t);           // 0x5c
virtual void  s24();
virtual void s25();
virtual void s26();
    virtual void  s27(void*);                        // 0x6c
virtual void  s28();
virtual void s29();
virtual void s30();
virtual void  s31();
virtual void s32();
virtual void s33();
    virtual void  s34();
    virtual void  s35(uint32_t, void*);              // 0x8c
    virtual void  s36();                             // 0x90
virtual void  s37();
virtual void s38();
virtual void s39();
virtual void  s40();
virtual void s41();
virtual void s42();
virtual void  s43();
virtual void s44();
virtual void s45();
virtual void  s46();
virtual void s47();
virtual void s48();
virtual void  s49();
virtual void s50();
virtual void s51();
virtual void  s52();
virtual void s53();
virtual void s54();
virtual void  s55();
virtual void s56();
virtual void s57();
virtual void  s58();
virtual void s59();
virtual void s60();
virtual void  s61();
virtual void s62();
    virtual char  s63(int);                          // 0xfc
    virtual char  s64(uint32_t);                     // 0x100
virtual void  s65();
virtual void s66();
virtual void s67();
    virtual void  s68();
    virtual void  s69(void*);                        // 0x114
};
struct WinBase {
    virtual void  v00();                           // slot 0
virtual void  v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void  v05();
virtual void v06();
    virtual void* v07(uint32_t);                   // 0x1c
virtual void  v08();
virtual void v09();
    virtual uint32_t v10();                        // 0x28
virtual void  v11();
virtual void v12();
virtual void  v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void  v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void  v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void  v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual void  v29();
    virtual void  v30(int, int, int, int, int);   // 0x78
virtual void  v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void  v35(uint32_t, void*);           // 0x8c
    virtual void  v36();                          // 0x90
    virtual void  v37(uint32_t, uint32_t);        // 0x94
};
struct SubWin {
    virtual void  c00();                           // slot 0
virtual void  c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void  c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void  c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void  c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void  c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void  c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void  c25();
virtual void c26();
    virtual void  c27(void*);                     // 0x6c
virtual void  c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void  c32();
virtual void c33();
virtual void c34();
virtual void c35();
    virtual void  c36();                          // 0x90
};
struct WinText {
    WinBase w;                       // +0x000 vtable pair (base)

    // Members used through byte offsets by the bodies below.
    // 0x009886d0
    void __thiscall m_9886d0(int* p);
    // 0x00988710
    void __thiscall m_988710(uint32_t flag, uint8_t value);
    // 0x00988760
    void __thiscall m_988760(void* p);
    // 0x00988780
    void __thiscall m_988780(int v);
    // 0x009887b0
    void __thiscall m_9887b0(float v);
    // 0x009887e0
    void __thiscall m_9887e0(float a, float b, float c, float d);
    // 0x00988860
    void __thiscall m_988860(uint32_t v);
    // 0x00988890
    void __thiscall m_988890();
    // 0x009888c0
    void __thiscall m_9888c0(uint32_t v);
    // 0x00988920
    uint8_t __thiscall m_988920(void* ctx, Iface* styleMgr);
    // 0x00988ad0
    uint8_t __thiscall m_988ad0(uint32_t p2, float* out);
    // 0x00988c40
    void __thiscall m_988c40(uint32_t p2);
    // 0x00988c90
    void __thiscall m_988c90(uint32_t p2);
    // 0x00988cd0
    uint8_t __thiscall m_988cd0(float* out, uint8_t p3, uint8_t p4);
    // 0x00988f60
    char __thiscall m_988f60(uint32_t p2, float* p3);
    // 0x00988f90
    void __thiscall m_988f90();
    // 0x00989000
    WinText* __thiscall m_989000();
    // 0x009890d0
    WinText* __thiscall m_9890d0(uint8_t p2);
    // 0x00989130
    static WinText* __cdecl Factory(void* p1);
    // 0x00989240
    void __thiscall m_989240(uint32_t p2);
    // 0x00989290
    uint32_t __thiscall m_989290(uint32_t i);
    // 0x009892b0
    void __thiscall m_9892b0(uint32_t i, uint32_t v);
    // 0x00989370
    void __thiscall m_989370(uint32_t v);
    // 0x00989390
    void __thiscall m_989390(uint32_t a, uint32_t b, uint32_t c);
    // 0x009893b0
    void __thiscall m_9893b0(uint32_t a, uint32_t b);
    // 0x009893d0
    void __thiscall m_9893d0(uint32_t a);
    // 0x00989410
    void __thiscall m_989410(uint32_t a, uint8_t flag);
    // 0x00989450
    int __thiscall m_989450(int, int, int, int, int);
    // 0x00989460
    void __thiscall m_989460(uint32_t v);
    // 0x009894a0
    uint32_t __thiscall m_9894a0(uint32_t i);
    // 0x009894c0
    char __thiscall m_9894c0(int, int, int, int);
    // 0x00989500
    uint32_t __thiscall m_989500(uint32_t p2, uint32_t p3);
    // 0x00989660
    void __thiscall m_989660(uint8_t p2);
};
extern "C" void* __cdecl FUN_009512d0_s0098_86d0(int, int, const char*, void*);            // 0x9512d0
struct C_894670 { void* __thiscall GetStyle(uint32_t, void*); };
struct C_89cbc0 { void __thiscall Clear(int); };
struct C_89dc00 { void* __thiscall Layout(uint32_t, int, uint32_t, uint32_t,
                                         float, float, void*, void*, void*); };struct C_95bc10 { void* __thiscall Begin2D(void*); };
struct C_96e740 { int __thiscall Run(void*, uint32_t, uint32_t, void*, int, int, int); };
struct C_9614a0 { void __thiscall SerUpdate(); };
struct C_830280 { void __thiscall SetMode1(int); };
struct C_830150 { void __thiscall SetMode2(int); };
struct C_950bb0 { void __thiscall Rem(void*); };
struct C_961760 { void __thiscall SetFlag(uint32_t, uint8_t); };
struct C_961f20 { void __thiscall Set(void*); };
struct C_8323d0 { void __thiscall Dtor(); };
struct C_89c540 { void __thiscall Dtor(); };
struct C_962740 { void __thiscall Free(); };
struct C_962a10 { void __thiscall Ctor(); };
struct C_89d820 { void __thiscall Ctor(int); };
struct C_898bd0 { void __thiscall Ctor(int); };
struct C_960310 { void __thiscall OnPaint(void*); };
// ---- items of slice s009886d0 end

// @ 0x008329b0
bool Subtitles::SetWindow(void* window)
{
    if (window == 0)
        return false;
    void* a = ((VFi)VT(window)[0x10 / 4])(window);
    void* b = ((VFi)VT(a)[0x10 / 4])(a);
    if (b == 0)
        return false;
    if (mpWindow == window)
        return true;
    Clear();
    ((void (__thiscall*)(void*, void*))FUN_00b5f950)((char*)this + 0x64, window);
    void* win = ((void* (__cdecl*)(int, int, const char*, void*))FUN_009512d0)
        (0x20c, 4, "UI/cSPUISubtitles", FUN_009512c0());
    if (win) {
        ((VFv)FUN_00962a10)(win);
        *(void**)win = &g_vtblSubWin0;
        *(void**)((char*)win + 4) = &g_vtblSubWin4;
    }
    ((void (__thiscall*)(void*, void*))FUN_00b5f950)((char*)this + 0x60, win);
    void* tw = *(void**)((char*)this + 0x60);
    ((void (__thiscall*)(void*, int))VT(tw)[0x5c / 4])(tw, -1);
    ((void (__thiscall*)(void*, int, int))VT(tw)[0x7c / 4])(tw, 0x400, 1);
    ((void (__thiscall*)(void*, int, int))VT(tw)[0x7c / 4])(tw, 0x10, 1);

    void* c = ((VFi)VT(mpWindow)[0x10 / 4])(mpWindow);
    float* r = ((float* (__thiscall*)(void*))VT(c)[0x38 / 4])(c);
    v68 = r[0];
    v6c = r[1];
    v70 = r[2];
    v74 = r[3];
    ((void (__thiscall*)(void*, float*, float*, float*, float*))VT(mpWindow)[0x34 / 4])
        (mpWindow, &v78, &v7c, &v80, &v84);
    void* d = ((VFi)VT(c)[0x10 / 4])(c);
    ((void (__thiscall*)(void*, void*))VT(d)[0xd8 / 4])(d, *(void**)((char*)this + 0x60));
    void* e = ((VFi)VT(c)[0x10 / 4])(c);
    ((void (__thiscall*)(void*, void*))VT(e)[0xdc / 4])(e, c);
    ((void (__thiscall*)(void*, void*))VT(*(void**)((char*)this + 0x60))[0xd8 / 4])
        (*(void**)((char*)this + 0x60), c);

    char* winBase = mpWindow ? (char*)mpWindow - 0x20c : 0;

    char tsMem[0x540];
    char llMem[0xb0];
    wchar_t txt[2];
    txt[0] = 0x37;
    txt[1] = 0;
    ((void (__thiscall*)(void*, int))FUN_0089d820)(tsMem, 0);
    ((void (__thiscall*)(void*, int))FUN_00898bd0)(llMem, 0);
    uint32_t styleId = ((uint32_t (__thiscall*)(void*))VT(winBase + 4)[0x40 / 4])(winBase + 4);
    void* sm = ((void* (__cdecl*)(int))FUN_00885bd0)(0);
    const void* style = ((const void* (__thiscall*)(void*, uint32_t, void*))FUN_00894670)(sm, styleId, 0);
    ((void (__thiscall*)(void*, const wchar_t*, uint32_t, float, float, float, float,
                         const void*, void*, int))FUN_0089dc00)
        (tsMem, txt, 2, 0.0f, 0.0f, 100.0f, 100.0f, style, llMem, 2);
    float hgt = ((float (__thiscall*)(void*))FUN_008975c0)(llMem);
    f28 = hgt;
    Rect rc;
    rc.left = v68 + v78;
    rc.top = v6c + v7c;
    rc.right = v70 - v80;
    rc.bottom = v74 - v84;
    rc.bottom = (float)floor((double)((rc.bottom - rc.top) / hgt)) * hgt + rc.top;
    ((void (__thiscall*)(void*, Rect*))VT(tw)[0x6c / 4])(tw, &rc);
    ((void (__thiscall*)(void*, float, float, float, float))VT(mpWindow)[0x38 / 4])
        (mpWindow, 0.0f, 0.0f, 0.0f, 0.0f);
    Rect rc2;
    rc2.left = 0.0f;
    rc2.top = 0.0f;
    rc2.right = rc.right - rc.left;
    rc2.bottom = rc.bottom - rc.top;
    ((void (__thiscall*)(void*, Rect*))VT(c)[0x6c / 4])(c, &rc2);

    void* srv = FUN_00883860();
    ((void (__thiscall*)(void*, void*, int))VT(srv)[0x20 / 4])(srv, (char*)this + 8, 0x61dd1b7);
    void* m = FUN_00f473a0(0x40, &g_allocTag, 0, 0, 0, 0);
    if (m) {
        *(uint32_t*)((char*)m + 0x30) = 0;
        *(void**)m = &g_vtblMsg0;
        _InterlockedExchange((volatile long*)((char*)m + 4), 0);
        *(void**)m = &g_vtblMsg1;
        *(uint32_t*)((char*)m + 0x38) = 0;
    }
    *(void**)((char*)m + 8) = this;
    srv = FUN_00883860();
    ((void (__thiscall*)(void*, int, void*, int, int))VT(srv)[0x18 / 4])
        (srv, 0x61dd1b7, m, 0, 0);
    ((void (__thiscall*)(void*))FUN_008323d0)(llMem);
    ((void (__thiscall*)(void*))FUN_0089c540)(tsMem);
    return true;
}

// @ 0x00834020
cSPUITextWin::cSPUITextWin()
{
    ((VFv)FUN_00989000)(this);
    vptr0 = &g_vtblTextWin0;
    vptr4 = &g_vtblTextWin4;
    *(void**)((char*)this + 0x20c) = &g_vtblTextWin20c;
}

// @ 0x009886d0
void __thiscall WinText::m_9886d0(int* p)
{
    if (p[2] == 0x76376e3) {
        uint32_t base = (uint32_t)(this ? (uint8_t*)this + 4 : 0);
        if (base == (uint32_t)*p) {
            ((Iface*)((uint8_t*)this + 4))->s36();
        }
    }
    ((C_950bb0*)this)->Rem(p);
}

// @ 0x00988710
void __thiscall WinText::m_988710(uint32_t flag, uint8_t value)
{
    uint8_t old = (uint8_t)w.v10();
    ((C_961760*)this)->SetFlag(flag, value);
    if (((old ^ 0xff) & 1) != 0) {
        if ((uint8_t)w.v10() & 1) {
            F(this, 0x804) = 0;
        }
    }
}

// @ 0x00988760
void __thiscall WinText::m_988760(void* p)
{
    ((C_961f20*)this)->Set(p);
    F(this, 0x804) = 0;
}

// @ 0x00988780
void __thiscall WinText::m_988780(int v)
{
    if (F(this, 4) != (uint32_t)v) {
        F(this, 4) = v;
        ((SubWin*)((uint8_t*)this - 0x208))->c36();
    }
}

// @ 0x009887b0
void __thiscall WinText::m_9887b0(float v)
{
    if (FF(this, 8) != v) {
        FF(this, 8) = v;
        void* fn = *(void**)(*(uint32_t*)((uint8_t*)this - 0x208) + 0x90);
        ((void (__thiscall*)(void*))fn)((uint8_t*)this - 0x208);
    }
}

// @ 0x009887e0
void __thiscall WinText::m_9887e0(float a, float b, float c, float d)
{
    if (FF(this, 0xc) != a || FF(this, 0x10) != b || FF(this, 0x14) != c || FF(this, 0x18) != d) {
        void* vt = *(void**)((uint8_t*)this - 0x208);
        FF(this, 0xc)  = a;
        FF(this, 0x10) = b;
        FF(this, 0x14) = c;
        FF(this, 0x18) = d;
        void* fn = *(void**)((uint8_t*)vt + 0x90);
        ((void (__thiscall*)(void*))fn)((uint8_t*)this - 0x208);
    }
}

// @ 0x00988860
void __thiscall WinText::m_988860(uint32_t v)
{
    void** vt = *(void***)this;
    void* sm = EA_Text_GetStyleManager(1);
    ((void (__thiscall*)(void*, uint32_t, void*))vt[0x8c / 4])(this, v, sm);
}

// @ 0x00988890
void __thiscall WinText::m_988890()
{
    ((C_9614a0*)this)->SerUpdate();
    void* p = (uint8_t*)this + 0x80c;
    ((C_830280*)p)->SetMode1(F(this, 0x80c));
    ((C_830150*)p)->SetMode2(F(this, 0x810));
}

// @ 0x009888c0
void __thiscall WinText::m_9888c0(uint32_t v)
{
    w.v07(v);
    ((SubWin*)((uint8_t*)this - 0x208))->c36();
}

// @ 0x00988920
uint8_t __thiscall WinText::m_988920(void* ctx, Iface* styleMgr)
{
    ((C_960310*)this)->OnPaint(ctx);
    if (F(this, 0xb0) == F(this, 0xb4)) return 1;
    if (styleMgr == 0) return 1;
    void* style = ((C_894670*)styleMgr)->GetStyle(F(this, 0xc0), 0);
    if (style == 0) return 1;
    float saved = FF(style, 0x200);
    float over = FF(this, 0x214);
    if (over != 0.0f) {
        FF(style, 0x200) = over;
    }
    void* layout = (uint8_t*)this + 0x758;
    ((C_89cbc0*)layout)->Clear(1);
    int w_ = F(this, 0xb4) - F(this, 0xb0);
    float fw = FF(this, 0x94) - FF(this, 0x8c) - FF(this, 0x224);
    float fh = FF(this, 0x90) - FF(this, 0x88) - FF(this, 0x220);
    void* out = ((C_89dc00*)((uint8_t*)this + 0x228))->Layout(F(this, 0xb0), w_ >> 1,
        F(this, 0x218), F(this, 0x21c), fh, fw, style, layout, (void*)0x14);
    void* batch = ((C_95bc10*)ctx)->Begin2D(0);
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    void* unk = sub->s05();
    uint8_t mode = (uint8_t)((uint32_t (__thiscall*)(void*))((void**) *(void**)unk)[0x23])(unk);
    ((C_96e740*)((uint8_t*)this + 0x80c))->Run(batch,
                 F(this, 0x784), F(this, 0x7ac), out,
                 (int)F(this, 0x210), *(uint16_t*)(uintptr_t)F(this, 0xb0), (int)mode);
    FF(style, 0x200) = saved;
    return 1;
}

// @ 0x00988ad0
uint8_t __thiscall WinText::m_988ad0(uint32_t p2, float* out)
{
    if (F(this, 0xb0) != F(this, 0xb4)) {
        void* styleMgr = EA_Text_GetStyleManager(1);
        if (styleMgr != 0) {
            void* style = ((C_894670*)styleMgr)->GetStyle(F(this, 0xc0), 0);
            if (style != 0) {
                float local0 = FF(style, 0x200) * GF(0x14853bc);
                void* layout = (uint8_t*)this + 0x758;
                ((C_89cbc0*)layout)->Clear(1);
                ((C_89dc00*)((uint8_t*)this + 0x228))->Layout(F(this, 0xb0),
                    (F(this, 0xb4) - F(this, 0xb0)) >> 1,
                    0, 0, local0, GF(0x13f6d90), style, layout, (void*)0);
                float y = FF(this, 0x7f4) + FF(this, 0x220) + FF(this, 0x218);
                float lim = GF(0x13f7674);
                float arr[2];
                arr[0] = y;
                arr[1] = lim;
                *out = (y > lim) ? arr[0] : arr[1];
                float fi = (float)(int32_t)F(this, 0x800);
                if ((int32_t)F(this, 0x800) < 0) fi += GF(0x13f4fd0);
                float h = (FF(this, 0x7f8) - FF(this, 0x7fc)) * fi + FF(this, 0x224) + FF(this, 0x21c);
                arr[0] = lim;
                arr[1] = h;
                out[1] = (h > lim) ? arr[1] : arr[0];
                return 1;
            }
        }
    }
    *out = 0.0f;
    out[1] = 0.0f;
    return 0;
}

// @ 0x00988c40
void __thiscall WinText::m_988c40(uint32_t p2)
{
    uint32_t buf[4];
    if (((Iface*)this)->s08(buf, p2, 1)) {
        ((SubWin*)((uint8_t*)this - 0x208))->c27(buf);
    }
    ((SubWin*)((uint8_t*)this - 0x208))->c36();
}

// @ 0x00988c90
void __thiscall WinText::m_988c90(uint32_t p2)
{
    uint32_t buf[4];
    if (((Iface*)this)->s08(buf, p2, 0)) {
        ((SubWin*)((uint8_t*)this - 0x208))->c27(buf);
    }
}

// @ 0x00988cd0
uint8_t __thiscall WinText::m_988cd0(float* out, uint8_t p3, uint8_t p4)
{
    uint8_t* b = (uint8_t*)this;
    if (*(int*)(b - 0x15c) == *(int*)(b - 0x158)) {
        if (p3 != 0) {
            float a = *(float*)(b - 0x180);
            float c = *(float*)(b - 0x17c);
            out[0] = *(float*)(b - 0x184);
            out[1] = a;
            out[2] = c;
            out[3] = a;
            return 1;
        }
        void* sm = EA_Text_GetStyleManager(1);
        if (sm != 0) {
            void* style = ((C_894670*)sm)->GetStyle(*(uint32_t*)(b - 0x14c), 0);
            float a = *(float*)(b - 0x180);
            float c = (*(int*)((uint8_t*)style + 0x244) == 2) ? *(float*)(b - 0x17c)
                                                              : *(float*)(b - 0x184);
            out[0] = c;
            out[1] = a;
            out[2] = c;
            out[3] = a;
            return 1;
        }
        return 0;
    }
    void* sm = EA_Text_GetStyleManager(1);
    if (sm == 0) return 0;
    void* style = ((C_894670*)sm)->GetStyle(*(uint32_t*)(b - 0x14c), 0);
    if (style == 0) return 0;
    void* layout = b + 0x54c;
    ((C_89cbc0*)layout)->Clear(1);
    int i0 = *(int*)(b - 0x15c);
    int half = (*(int*)(b - 0x158) - i0) >> 1;
    if (p3 != 0) {
        ((C_89dc00*)(b + 0x1c))->Layout(i0, half, F(b, 0xc), F(b, 0x10),
            (*(float*)(b - 0x17c) - *(float*)(b - 0x184)) - *(float*)(b + 0x14),
            GF(0x13f6d90), style, layout, (void*)0);
        float f4 = *(float*)(b + 0x5ec);
        float f5 = *(float*)(b + 0x5f0);
        float fa = *(float*)(b - 0x180);
        float fc = *(float*)(b - 0x17c);
        float fi = (float)*(int*)(b + 0x5f4);
        if (*(int*)(b + 0x5f4) < 0) fi += GF(0x13f4fd0);
        out[0] = *(float*)(b - 0x184);
        out[1] = fa;
        out[2] = fc;
        out[3] = ((fi * (f4 - f5) + *(float*)(b + 0x18)) + *(float*)(b + 0x10)) + fa;
        return 1;
    }
    ((C_89dc00*)(b + 0x1c))->Layout(i0, half, F(b, 0xc), F(b, 0x10),
        GF(0x13f6d90), GF(0x13f6d90), style, layout, (void*)0);
    if (p4 != 0 && *(int*)((uint8_t*)style + 0x244) == 2) {
        float fc = *(float*)(b - 0x17c);
        float fa = *(float*)(b - 0x180);
        out[0] = fc - ((*(float*)(b + 0x5e4) + *(float*)(b + 0x14)) + *(float*)(b + 0xc));
        out[2] = fc;
        out[3] = *(float*)(b - 0x178);
        out[1] = fa;
        return 1;
    }
    float fa = *(float*)(b - 0x180);
    float fb = *(float*)(b - 0x184);
    out[0] = fb;
    out[2] = ((*(float*)(b + 0x5e4) + *(float*)(b + 0x14)) + *(float*)(b + 0xc)) + fb;
    out[3] = *(float*)(b - 0x178);
    out[1] = fa;
    return 1;
}

// @ 0x00988f60
char __thiscall WinText::m_988f60(uint32_t p2, float* p3)
{
    if (m_988ad0(p2, p3)) {
        ((Iface*)((uint8_t*)this + 4))->s36();
    }
    return 1;
}

// @ 0x00988f90
void __thiscall WinText::m_988f90()
{
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    ((C_8323d0*)((uint8_t*)this + 0x758))->Dtor();
    ((C_89c540*)((uint8_t*)this + 0x228))->Dtor();
    F(this, 0x20c) = 0x13eb938;
    ((C_962740*)this)->Free();
}

// @ 0x00989000
WinText* __thiscall WinText::m_989000()
{
    ((C_962a10*)this)->Ctor();
    F(this, 0x20c) = 0x14085f0;
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    F(this, 0x210) = 0xffffffff;
    FF(this, 0x214) = 0.0f;
    FF(this, 0x218) = 0.0f;
    FF(this, 0x21c) = 0.0f;
    FF(this, 0x220) = 0.0f;
    FF(this, 0x224) = 0.0f;
    ((C_89d820*)((uint8_t*)this + 0x228))->Ctor(0);
    ((C_898bd0*)((uint8_t*)this + 0x758))->Ctor(0);
    F(this, 0x808) = 0;
    F(this, 0x80c) = 0;
    F(this, 0x810) = 2;
    F(this, 0x814) = 3;
    FF(this, 0x820) = 0.0f;
    FF(this, 0x824) = 0.0f;
    FF(this, 0x818) = 0.0f;
    FF(this, 0x81c) = 0.0f;
    F(this, 0x830) = 0;
    ((C_830150*)((uint8_t*)this + 0x80c))->SetMode2(2);
    return this;
}

// @ 0x009890d0
WinText* __thiscall WinText::m_9890d0(uint8_t p2)
{
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    ((C_8323d0*)((uint8_t*)this + 0x758))->Dtor();
    ((C_89c540*)((uint8_t*)this + 0x228))->Dtor();
    F(this, 0x20c) = 0x13eb938;
    ((C_962740*)this)->Free();
    if (p2 & 1) {
        FUN_00951330(this);
    }
    return this;
}

// @ 0x00989130
WinText* __cdecl WinText::Factory(void* p1)
{
    void* r = FUN_009512d0_s0098_86d0(0x834, 4, "UTFWin/WinText", FUN_009512c0());
    if (r == 0) return 0;
    WinText* t = ((WinText*)r)->m_989000();
    if (t == 0) return 0;
    Iface* s = (Iface*)((uint8_t*)t + 0x20c);
    if (s != 0) {
        ((void (__thiscall*)(void*, void*))((void**)*(void**)s)[0x28 / 4])(s, p1);
        void* o = ((void* (__thiscall*)(void*))((void**)*(void**)s)[0x10 / 4])(s);
        ((void (__thiscall*)(void*, void*))((void**)*(void**)o)[0x84 / 4])(o, p1);
    }
    return (WinText*)s;
}
