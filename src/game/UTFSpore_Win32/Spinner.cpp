// src/game/UTFSpore_Win32/Spinner.cpp -- migrated from slice(s) s009873a0, s00986680 by tools/migrate/rewrite.py
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

// @ 0x00987470
void* WinSpinner::ScalarDtor(unsigned flags)
{
    WinSpinner* self = this;
    *(void**)self = (void*)0x1445060;
    *(void**)((char*)self + 4) = (void*)0x1444f40;
    *(void**)((char*)self + 0x20c) = (void*)0x1444ee8;
    void* p = self->mText;
    if (p)
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    *(void**)((char*)self + 0x20c) = (void*)0x13eb938;
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
