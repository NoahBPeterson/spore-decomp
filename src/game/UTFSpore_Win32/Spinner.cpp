// src/game/UTFSpore_Win32/Spinner.cpp -- migrated from slice(s) s00985ad0, s009873a0, s00986680 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Spinner.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Window.h"
#include "EA/Stopwatch.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>

// ---- items of slice s00986680 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct Image_s0098_6680 { uint32_t pad[7]; int mWidth; int mHeight; };
}
}
namespace EA {
namespace UTFWin {
struct Point2 { float x, y; Point2(float ax, float ay) : x(ax), y(ay) {} };
}
}
namespace EA {
namespace UTFWin {
struct Graphics2D {
    virtual void v0();
    virtual void SetColor(uint32_t color);
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void FillQuad(const Point2& a, const Point2& b, const Point2& c, const Point2& d);
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void DrawImageScaled(const float* area, const Image_s0098_6680* image, const float* texCoords);
};
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0098_6680 {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};
}
}
static __forceinline void FillRect(EA::UTFWin::Graphics2D* g, float l, float t, float r, float b) {
    using EA::UTFWin::Point2;
    g->FillQuad(Point2(l, t), Point2(r, t), Point2(r, b), Point2(l, b));
}
static __forceinline void FillTriangle(EA::UTFWin::Graphics2D* g, float ax, float ay, float bx, float by,
                                       float cx, float cy) {
    using EA::UTFWin::Point2;
    g->FillQuad(Point2(ax, ay), Point2(bx, by), Point2(cx, cy), Point2(ax, ay));
}
namespace EA {
namespace UTFWinControls {
struct DrawState { uint32_t flags; uint32_t part; };
}
}
namespace EA {
namespace UTFWinControls {
class SpinnerDrawable { public:
    uint32_t pad[4];                        // +0x00 (vptrs, refcount, ...)
    UTFWin::Image_s0098_6680* mImages[3];              // +0x10 (indexed by part)
    void __thiscall CreateRenderables(UTFWin::RenderContext_s0098_6680* ctx, const float* rc, const DrawState* st);
};
}
}
// ---- items of slice s00986680 end

// ---- items of slice s009873a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00951330(void* p);                      // 0x951330 operator delete
extern "C" void* FUN_011e073e(void* dst, int zero, unsigned size); // 0x11e073e operator_new[]
extern "C" void  FUN_00f47380(void* p);                      // 0xf47380 operator delete
extern "C" wchar_t g_emptyW[2];                                  // 0x1667bac (eastl empty string rep)
extern "C" void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...) throw();   // 0x41e050 eastl::basic_string<wchar_t>::sprintf
extern const wchar_t g_spinnerFmt[];                             // 0x13f01bc
#pragma intrinsic(sqrt)
struct WinBase { void ctor962a10(); void dtor962740(); };
struct Sw {                                     // EA::Stopwatch
    void ctor(unsigned a, unsigned b);          // 0x0093a560
    void SetUnits(int u);                       // 0x0093a1a0
};
struct IWinSub {
    void SetFlag(unsigned flag, unsigned char on);  // 0x00961760 EA::UTFWin::Window::SetFlag
};
struct WinSpinner {
    char   pad_00[0x20c];
    void*  vtbl20c;    // +0x20c
    char   pad_210[0x248 - 0x210];
    void*  mText;      // +0x248
    char   pad_24c[0x4c0];

    void* Ctor();
    void* ScalarDtor(unsigned flags);
    void  Refresh();
};
struct WStrTmp {
    wchar_t* b;
    wchar_t* e;
    wchar_t* cap;
    WStrTmp() : b(g_emptyW), e(g_emptyW), cap(g_emptyW + 1) {}
    void Free() {
        if ((((unsigned)cap - (unsigned)b) & 0xfffffffe) > 2 && b)
            FUN_00f47380(b);
    }
};
// ---- items of slice s009873a0 end

// ---- items of slice s00985ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
class Stopwatch_s0098_5ad0 { public:
    uint64_t mnStartTime;                   // +0x00 (tested as one 64-bit value)
    uint64_t mnTotalElapsedTime;            // +0x08
    int      mnUnits;                       // +0x10
    float    mfCyclesToUnitsCoefficient;    // +0x14
    int64_t GetElapsedTime();               // 0093A5E0 0x0093a5e0
    void    Restart();                      // 00571E80 0x00571e80
    void    SetBoolProperty();              // 0093A2E0
};
}
namespace EA {
namespace UTFWinControls {
class WinSpinner_s0098_5ad0;
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerPrim;
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerIWin;
}
}
namespace EA {
namespace UTFWinControls {
struct Image {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[6];
    int w, h;                               // +0x1c, +0x20
};
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerMsg { uint32_t w0, w1, type, src; int from, to; uint32_t w6; };
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerDrawableIf {
    virtual void d00();
    virtual void d04();
    virtual void d08();
    virtual void* QueryInterface(uint32_t id);          // 0x0c
    virtual void Render(int g, float* rect, void* state);   // 0x10
    virtual void d14();
    virtual char GetSize(float* out, int mask, int idx);    // 0x18
};
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerWinMgr {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
virtual void m2c();
virtual void m30();
virtual void m34();
virtual void m38();
virtual void m3c();
virtual void m40();
virtual void m44();
virtual void m48();
virtual void m4c();
    virtual void m50();
    virtual void* GetCapture(int which);                // 0x54
    virtual void SetCapture(int which, void* w);        // 0x58
    virtual void ReleaseCapture(int which, void* w);    // 0x5c
};
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerPrim {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
virtual void p2c();
virtual void p30();
virtual void p34();
virtual void p38();
virtual void p3c();
virtual void p40();
virtual void p44();
virtual void p48();
virtual void p4c();
virtual void p50();
virtual void p54();
virtual void p58();
virtual void p5c();
virtual void p60();
virtual void p64();
virtual void p68();
virtual void p6c();
virtual void p70();
virtual void p74();
virtual void p78();
virtual void p7c();
virtual void p80();
virtual void p84();
virtual void p88();
    virtual void Refresh();                             // 0x8c
    virtual void RenderComponent(int g, uint32_t idx);  // 0x90
    virtual int  PickComponent(float x, float y);       // 0x94
    virtual void p98();
};
}
}
namespace EA {
namespace UTFWinControls {
struct SpinnerIWin {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
    virtual uint8_t GetFlags();                         // 0x28
virtual void w2c();
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
virtual void w60();
virtual void w64();
virtual void w68();
virtual void w6c();
virtual void w70();
virtual void w74();
virtual void w78();
virtual void w7c();
virtual void w80();
virtual void w84();
virtual void w88();
virtual void w8c();
    virtual void Invalidate();                          // 0x90
virtual void w94();
virtual void w98();
virtual void w9c();
virtual void wa0();
virtual void wa4();
virtual void wa8();
virtual void wac();
    virtual void SetDrawable(void* d);                  // 0xb0
virtual void wb4();
virtual void wb8();
virtual void wbc();
virtual void wc0();
virtual void wc4();
virtual void wc8();
virtual void wcc();
virtual void wd0();
virtual void wd4();
virtual void wd8();
virtual void wdc();
virtual void we0();
virtual void we4();
virtual void we8();
virtual void wec();
virtual void wf0();
virtual void wf4();
virtual void wf8();
virtual void wfc();
virtual void w100();
virtual void w104();
virtual void w108();
virtual void w10c();
    virtual void w110();
    virtual void SendMessage(SpinnerMsg* m);            // 0x114
    void SetFlag(uint32_t flag, uint8_t on);            // 00961760
};
}
}
namespace EA {
namespace UTFWinControls {
struct Window : SpinnerPrim, SpinnerIWin {
    uint32_t p08[(0x34 - 0x08) / 4];        // +0x008
    SpinnerWinMgr* mgr;                     // +0x034
    uint32_t p38[(0x80 - 0x38) / 4];        // +0x038
    int id0, id1;                           // +0x080, +0x084
    float area[4];                          // +0x088
    uint32_t p98[(0x1d8 - 0x98) / 4];       // +0x098
    uint32_t state0, state1;                // +0x1d8, +0x1dc
    SpinnerDrawableIf* drawable;            // +0x1e0
    uint32_t p1e4[(0x20c - 0x1e4) / 4];     // +0x1e4
    Window();                               // 00962A10
    void OnPaintBase(int g);                // 00960310
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinSpinner_s0098_5ad0 { public:
virtual void i00();
virtual void i04();
virtual void i08();
virtual void i0c();
    virtual void i10();
    virtual void SetValue(int v, char notify);          // 0x14
virtual void i18();
virtual void i1c();
virtual void i20();
virtual void i24();
    virtual void i28();
    virtual void SetMinimumValue(int v, int notify);    // 0x2c
    virtual void i30();
    virtual void SetMaximumValue(int v, int notify);    // 0x34
    virtual void i38();
    virtual void SetMode(int v);                        // 0x3c
    virtual void i40();
    virtual void SetComponentDrawable(Image* p);        // 0x44
    virtual void i48();
    virtual void SetDrawable(void* d);                  // 0x4c
    virtual void* GetDrawable();                        // 0x50 0x00986360
    int current;                            // +0x04
    int minVal;                             // +0x08
    int maxVal;                             // +0x0c
    int deltaPerTick;                       // +0x10
    int tickPeriod;                         // +0x14
    uint8_t hlComp;                         // +0x18
    uint8_t selComp;                        // +0x19
    uint8_t f1a;                            // +0x1a
    uint8_t pad1b;
    int mode;                               // +0x1c
    uint8_t refresh;                        // +0x20
    uint8_t pad21[3];
    EA::Stopwatch_s0098_5ad0 timer;                    // +0x24
    Image* compDrawable;                    // +0x3c
    float compArea[3][4];                   // +0x40
    IWinSpinner_s0098_5ad0() { minVal = 0; maxVal = 0; }
    WinSpinner_s0098_5ad0*   win() { return (WinSpinner_s0098_5ad0*)((char*)this - 0x20c); }
    SpinnerIWin*  iw()  { return (SpinnerIWin*)((char*)this - 0x208); }
};
}
}
namespace EA {
namespace UTFWinControls {
class WinSpinner_s0098_5ad0 : public Window, public IWinSpinner_s0098_5ad0 { public:
    bool OnMouseDown(float x, float y, int a3, int button);   // 00985e50 0x00985e50
    bool OnMouseUp(float x, float y, int a3, int flags);      // 00985f30 0x00985f30
    bool OnMouseMove(float x, float y, int flags);            // 00985fc0 0x00985fc0
    bool OnTick();                                            // 00986000 0x00986000
    bool GetPreferredSize(int flag, float* out);              // 009861a0
    bool OnRebuild(int g);                                    // 009863c0 0x009863c0
    void Refresh();                                           // 00987590 (override, external) 0x00987590
    void RenderComponent(int g, uint32_t idx);                // 00986420 (override) 0x00986420
    int  PickComponent(float x, float y);                     // 00986510 (override) 0x00986510
};
}
}
// ---- items of slice s00985ad0 end

// @ 0x00986360
void* EA::UTFWinControls::IWinSpinner_s0098_5ad0::GetDrawable()
{
    EA::UTFWinControls::SpinnerDrawableIf* d = win()->drawable;
    if (d) return d->QueryInterface(0x6f0631df);
    return 0;
}

// @ 0x009863c0
bool EA::UTFWinControls::WinSpinner_s0098_5ad0::OnRebuild(int g)
{
    if (drawable) {
        RenderComponent(g, 0);
        RenderComponent(g, 1);
        RenderComponent(g, 2);
        return true;
    }
    ((EA::UTFWinControls::Window*)this)->OnPaintBase(g);
    return true;
}

// @ 0x00986680
namespace EA { namespace UTFWinControls {
void __thiscall SpinnerDrawable::CreateRenderables(UTFWin::RenderContext_s0098_6680* ctx, const float* rc, const DrawState* st)
{
    using namespace UTFWin;
    Graphics2D* g = ctx->Begin2D(0);
    g->SetColor(0xffffffff);
    uint32_t part = st->part;
    Image_s0098_6680* img = mImages[part];
    if (part - 1 > 1)
        return;
    if (img) {
        uint32_t flags = st->flags;
        float u0 = 0.0f;
        switch (flags & 7) {
        case 0:
            if ((flags & 8) == 0) { u0 = 0.25f; break; }
            // fall through
        case 3: u0 = 0.75f; break;
        case 1: u0 = 0.0f; break;
        case 2: u0 = 0.5f; break;
        }
        float uv[4];
        uv[0] = u0; uv[1] = 0.0f; uv[2] = u0 + 0.25f; uv[3] = 1.0f;
        g->DrawImageScaled(rc, img, uv);
        return;
    }

    uint32_t flags = st->flags;
    uint32_t state = flags & 7;
    if (state == 3 || state == 1) {
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
    } else {
        g->SetColor((flags & 2) ? 0xfffbfbf9u : 0xffece9d8u);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xfff1efe2);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        g->SetColor(0xffffffff);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
    }

    // the arrow (pressed buttons shift it by one pixel)
    if (state == 1)
        g->SetColor(0xffc0c0c0);
    else
        g->SetColor(0xff000000);
    float L = rc[0], T = rc[1], R = rc[2], B = rc[3];
    float w = (R - L) * 0.2857143f;
    float h = (B - T) * 0.2857143f;
    float oy = 0.0f;
    float ox = 0.0f;
    if (state == 3 || state == 1) {
        oy = 1.0f;
        ox = 1.0f;
    }
    if (st->part == 2) {
        if (st->flags & 0x80) {

            float x0 = (ox + w) + L;
            float y0 = (oy + h) + rc[1];
            FillTriangle(g, x0, y0, (R - w) + ox, y0, ((R - L) * 0.5f + ox) + L, (B - h) + oy);
        } else {

            float x0 = (ox + w) + L;
            FillTriangle(g, x0, ((rc[3] - rc[1]) * 0.5f + rc[1]) + oy, (R - w) + ox, (rc[1] + oy) + h,
                         (R - w) + ox, (rc[3] - h) + oy);
        }
    } else {
        float x0 = (ox + w) + L;
        if (st->flags & 0x80) {

            float y1 = (rc[3] - h) + oy;
            FillTriangle(g, x0, y1, ((rc[2] - L) * 0.5f + ox) + L, (rc[1] + oy) + h, (rc[2] - w) + ox, y1);
        } else {

            FillTriangle(g, x0, (rc[1] + oy) + h, (R - w) + ox, ((rc[3] - rc[1]) * 0.5f + rc[1]) + oy,
                         x0, (rc[3] - h) + oy);
        }
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x009873a0
void* WinSpinner::Ctor()
{
    WinSpinner* self = this;
    ((WinBase*)self)->ctor962a10();
    *(void**)((char*)self + 0x20c) = (void*)0x1444e90;
    unsigned char ff = 0xff;
    Sw*     sw  = (Sw*)((char*)self + 0x230);
    IWinSub* sub = (IWinSub*)((char*)self + 4);
    *(void**)((char*)self) = (void*)0x1445060;
    *(void**)((char*)self + 4) = (void*)0x1444f40;
    *(void**)((char*)self + 0x20c) = (void*)0x1444ee8;
    *(void**)((char*)self + 0x210) = 0;
    *(void**)((char*)self + 0x214) = 0;
    *(void**)((char*)self + 0x218) = (void*)0x100;
    *(void**)((char*)self + 0x21c) = (void*)1;
    *(void**)((char*)self + 0x220) = (void*)0x64;
    *((unsigned char*)self + 0x224) = ff;
    *((unsigned char*)self + 0x225) = ff;
    *(void**)((char*)self + 0x228) = (void*)2;
    *((unsigned char*)self + 0x22c) = 1;
    sw->ctor(0, 0);
    *(void**)((char*)self + 0x248) = 0;
    FUN_011e073e((char*)self + 0x24c, 0, 0x30);
    sw->SetUnits(4);
    sub->SetFlag(8, 1);
    return self;
}

extern "C" char g_1445060[];  // WinSpinner vtables
extern "C" char g_1444f40[];
extern "C" char g_1444ee8[];
extern "C" char g_13eb938[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// @ 0x00987470
void* WinSpinner::ScalarDtor(unsigned flags)
{
    WinSpinner* self = this;
    *(void**)self = g_1445060;
    *(void**)((char*)self + 4) = g_1444f40;
    *(void**)((char*)self + 0x20c) = g_1444ee8;
    _ReadWriteBarrier();
    void* p = self->mText;
    if (p)
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    *(void**)((char*)self + 0x20c) = g_13eb938;
    ((WinBase*)self)->dtor962740();
    if (flags & 1)
        FUN_00951330(self);
    return self;
}

// @ 0x00987530
void* __stdcall BasicFactory_SpinnerDrawable_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x1c, 4, "UTFWin/EA::UTFWinControls::SpinnerDrawable", (void*)alloc);
    if (p) {
        *(void* volatile*)((char*)p + 4) = (void*)0x13fa72c;
        *(void**)((char*)p + 8) = 0;
        *(void* volatile*)((char*)p + 0xc) = (void*)0x13fa72c;
        *(void**)((char*)p + 0x00) = (void*)0x1445128;
        *(void**)((char*)p + 0x04) = (void*)0x1445110;
        *(void**)((char*)p + 0x0c) = (void*)0x14450f8;
        *(void**)((char*)p + 0x10) = 0;
        *(void**)((char*)p + 0x14) = 0;
        *(void**)((char*)p + 0x18) = 0;
        return p;
    }
    return 0;
}

// @ 0x00987590
void WinSpinner::Refresh()
{
    char* self = (char*)this;
    if (self[0x22c] == 0)
        return;
    if (*(int*)(self + 0x1e0) == 0)
        return;
    self[0x22c] = 0;
    float* pc = (float*)(self + 0x250);        // three component rects (l,t,r,b) at 0x24c, step 0x10
    for (unsigned i = 0; i < 3; i++) {
        float out[2];                           // [0] width, [1] height
        char* mgr = *(char**)(self + 0x1e0);
        bool ok = (*(bool(__thiscall**)(char*, float*, int, unsigned))((char*)*(void**)mgr + 0x18))(
            mgr, out, (*(int*)(self + 0x228) == 2) ? 0x80 : 0, i);
        if (!ok) {
            void* sub = self + 4;
            float* r = (*(float*(__thiscall**)(void*))((char*)*(void**)sub + 0x38))(sub);
            if (*(int*)(self + 0x228) == 1) {
                float a = (r[2] - r[0]) * 0.5f;
                float b = r[3] - r[1];
                const float* m = (b > a) ? &a : &b;
                out[0] = *m;
                out[1] = r[3] - r[1];
            } else {
                out[0] = r[2] - r[0];
                float a = (r[3] - r[1]) * 0.5f;
                float b = r[2] - r[0];
                const float* m = (b > a) ? &a : &b;
                out[1] = *m;
            }
        }
        pc[-1] = 0.0f;
        pc[0] = 0.0f;
        pc[1] = out[0];
        pc[2] = out[1];
        pc += 4;
    }
    float* c1 = (float*)(self + 0x25c);
    float* c2 = (float*)(self + 0x26c);
    float w1 = c1[2] - c1[0];
    float h1 = c1[3] - c1[1];
    float w2 = c2[2] - c2[0];
    float h2 = c2[3] - c2[1];
    float* win = (float*)(self + 0x88);
    if (*(int*)(self + 0x228) == 1) {
        c2[0] = 0.0f;
        c2[2] = w2;
        c2[1] = (win[3] - win[1] - h2) * 0.5f;
        c2[3] = c2[1] + h2;
        c1[0] = (win[2] - win[0]) - w1;
        c1[2] = c1[0] + w1;
        c1[1] = (win[3] - win[1] - h1) * 0.5f;
        c1[3] = c1[1] + h1;
    } else {
        c1[0] = ((win[2] - win[0]) - w1) * 0.5f;
        c1[2] = c1[0] + w1;
        c1[1] = 0.0f;
        c1[3] = h1;
        c2[0] = ((win[2] - win[0]) - w2) * 0.5f;
        c2[2] = c2[0] + w2;
        c2[1] = (win[3] - win[1]) - h2;
        c2[3] = c2[1] + h2;
    }
    if (*(void**)(self + 0x248)) {
        WStrTmp str;
        WStr_Format(&str, g_spinnerFmt, *(int*)(self + 0x210));
        void* t1 = *(void**)(self + 0x248);
        (*(void(__thiscall**)(void*, wchar_t*))((char*)*(void**)t1 + 0x80))(t1, str.b);
        void* t2 = *(void**)(self + 0x248);
        (*(void(__thiscall**)(void*))((char*)*(void**)t2 + 0x90))(t2);
        str.Free();
    }
    void* sub = self + 4;
    (*(void(__thiscall**)(void*))((char*)*(void**)sub + 0x90))(sub);
}
