// src/game/UTFSpore_Win32/Button.cpp -- migrated from slice(s) s009656d0, s00964190, s00962ff0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Button.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/LineLayout.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Text/Typesetter.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/Image.h"

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WinButtonX {
    int   GetSlot(uint32_t i);                          // 0x964020
    void  SetSlot(uint32_t i, int v);                   // 0x963fd0
    int   GetCaptionColor();                            // 0x964000
};
struct FlexFlag {
    int  GetEffectFlag();                       // 0x963f60
    void SetEffectFlag(uint32_t m, bool on);    // 0x963f70
};
struct Cap { void SelectCaptionColor(); };
// ---- items of slice s00962ff0 end

// ---- items of slice s00964190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define F(T, o) (*(T*)((char*)this + (o)))
template <class T> inline const T& eastl_max(const T& a, const T& b) { return b < a ? a : b; }
struct Msg {
    uint32_t src, dst, id;
    uint32_t p0, p1, p2, p3;
};
struct DropShadow {
    void SetMode1(uint32_t);               // 0x00830280
    void SetMode2(uint32_t);               // 0x00830150
    void F96e740(uint32_t h, uint32_t a, uint32_t b, int r, uint32_t c, uint32_t ch, bool flag);  // 0x0096e740
};
struct LineLayout {
    void Clear(int all);  // 0x0089cbc0
};
struct Typesetter {
    int  F89dc00(const uint16_t* text, int len, float l, float t, float r, float b, void* style, void* layout, int flags);  // 0x0089dc00
    void LayoutLine(const uint16_t* text, int len, float x, float y, void* style);  // 0x0089db20
};
struct StyleManager {
    void* GetStyle(uint32_t id, int arg);  // 0x00894670
};
StyleManager* __cdecl GetStyleManager(bool create);                              // 0x00885bd0
struct RenderContext { uint32_t Begin2D(int arg); };                              // 0x0095bc10
struct RenderContext;
struct IObjVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void* V10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual bool V8c();
};
struct IWinVt;
struct IFocusMgr {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void* GetFocus(int);
    virtual void SetFocus(int, IWinVt*);
    virtual void ReleaseFocus(int, IWinVt*);
};
struct IWinVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual IObjVt* GetObj();
    virtual void s18();
    virtual void s1c();
    virtual uint32_t V20();
    virtual void s24();
    virtual uint32_t GetFlags();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void SetFlags(uint32_t);
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void SetFlag(uint32_t, bool);
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void V90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void Vb0(void*);
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void Send(Msg*);
};
struct IBtnVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void SetFlag(uint32_t, bool);
};
struct IPrimVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void V4c(int, void*);
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void V88(uint32_t);
    virtual void s8c();
    virtual void s90();
    virtual void V94(uint32_t);
    virtual void V98();
    virtual void V9c();
};
struct IPainterVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void Paint(void*, void*, void*);
    virtual void s14();
    virtual void GetSize(float*, int, int);
};
struct WB {
    IWinVt* W() { return (IWinVt*)((char*)this + 4); }
    IBtnVt* Btn() { return (IBtnVt*)((char*)this + 0x20c); }
    IPrimVt* P() { return (IPrimVt*)this; }
    IFocusMgr* Mgr() { return *(IFocusMgr**)((char*)this + 0x34); }
    bool OnButtonClicked(int a);
    bool OnKeyDown(int a, int b, int c);
    bool OnKeyUp(int a, int b, int c);
    bool OnMouseDown(int a, int b, int c, uint32_t f);
    bool OnMouseUp(int a, int b, int c, uint32_t f);
    bool OnFocusChange(int a, void* w);
    bool OnTick();
    void SerUpdate();
    bool OnRebuild(RenderContext* rc);
    bool CalcSize(int a, float* out);
    void WindowSerUpdate();                       // 0x009614a0
    void WindowOnPaint(RenderContext* rc);        // 0x00960310
};
// ---- items of slice s00964190 end

// ---- items of slice s009656d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                // 0x01485720 = 1.0f
namespace EA {
namespace UTFWin {
struct Image_s0096_56d0 { uint32_t pad[8]; };
}
}
namespace EA {
namespace UTFWin {
struct Point2 { float x, y; };
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
    virtual void FillQuad(Point2& tl, Point2& tr, Point2& br, Point2& bl);
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void DrawImageScaled(const float* area, const Image_s0096_56d0* image, const float* texCoords);
};
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0096_56d0 {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl BltEdgeStretch(Graphics2D* g, const float* rect, const float* src, const Image_s0096_56d0* image,
                            const float* uv, float sx, float sy);   // 0x95d000
}
}
}
struct Rect4 { float x1, y1, x2, y2; Rect4(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {} };
static __forceinline void FillRectR(EA::UTFWin::Graphics2D* g, const Rect4& r) {
    EA::UTFWin::Point2 tl = { r.x1, r.y1 };
    EA::UTFWin::Point2 tr = { r.x2, r.y1 };
    EA::UTFWin::Point2 br = { r.x2, r.y2 };
    EA::UTFWin::Point2 bl = { r.x1, r.y2 };
    g->FillQuad(tl, tr, br, bl);
}
static __forceinline void FillRect(EA::UTFWin::Graphics2D* g, float l, float t, float r, float b) {
    Rect4 rc(l, t, r, b);
    FillRectR(g, rc);
}
namespace EA {
namespace UTFWinControls {
struct DrawState { uint32_t flags; };
}
}
namespace EA {
namespace UTFWinControls {
class ButtonDrawable { public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool GetSourceRect(uint32_t flags, float* out);   // +0x20
    uint32_t pad[3];                    // +0x04 (second base, refcount ...)
    UTFWin::Image_s0096_56d0* mpImage;             // +0x10
    bool mbTileable;                    // +0x14
    void __thiscall Paint(UTFWin::RenderContext_s0096_56d0* ctx, const float* rc, const DrawState* st);
};
}
}
// ---- items of slice s009656d0 end

// @ 0x00963f60
int FlexFlag::GetEffectFlag()
{
    return *(int*)((char*)this - 0x160);
}

// @ 0x00963f70
void FlexFlag::SetEffectFlag(uint32_t m, bool on)
{
    int v = *(int*)((char*)this - 0x160);
    if (on) {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v | m);
    } else {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v & ~m);
    }
}

// @ 0x00963fd0
void WinButtonX::SetSlot(uint32_t i, int v)
{
    if (i < 8 && *(int*)((char*)this + 0x54 + i * 4) != v) {
        *(int*)((char*)this + 0x54 + i * 4) = v;
        int* base = (int*)((char*)this - 0x20c);
        (*(void(__thiscall**)(int*))((char*)*base + 0xa0))(base);
    }
}

// @ 0x00964000
int WinButtonX::GetCaptionColor()
{
    if (*(char*)((char*)this + 0x210) != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0xa0))(this);
    return *(int*)((char*)this + 0x224);
}

// @ 0x00964020
int WinButtonX::GetSlot(uint32_t i)
{
    if (i < 8)
        return *(int*)((char*)this + 0x54 + i * 4);
    return 0;
}

// @ 0x00964040
void Cap::SelectCaptionColor()
{
    void* self = this;
    uint32_t v = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)self + 0x28))(self);
    uint32_t xf = *(uint32_t*)((char*)self + 0x3c);
    char c2 = (char)((xf >> 4) | (v >> 1)) & 1;
    (void)c2;
}

// @ 0x009643c0
bool WB::OnMouseDown(int a, int b, int c, uint32_t f)
{
    if (!(f & 8) || (f & 0x30))
        return false;
    void* w = this ? (char*)this + 4 : 0;
    if (Mgr()->GetFocus(1) != w)
        {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x58 / 4])(m, 1, W());
        }
    uint32_t fl = F(uint32_t, 0xac);
    if (!(fl & 2) && (fl & 8)) {
        Btn()->SetFlag(2, 1);
        if (F(uint8_t, 0x218) & 1)
            P()->V94(f);
    }
    return true;
}

// @ 0x00964450
bool WB::OnMouseUp(int a, int b, int c, uint32_t f)
{
    if (!(f & 8)) {
        void* w = this ? (char*)this + 4 : 0;
        if (Mgr()->GetFocus(1) == w)
            {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x5c / 4])(m, 1, W());
        }
        if (F(uint32_t, 0xac) & 2) {
            Btn()->SetFlag(2, 0);
            if (!(F(uint8_t, 0x218) & 1))
                P()->V94(f);
        }
        return true;
    }
    return false;
}

// @ 0x00964c90
bool WB::OnRebuild(RenderContext* rc)
{
    P()->V9c();
    void* painter = F(void*, 0x1e0);
    if (painter == 0) {
        WindowOnPaint(rc);
    } else {
        uint32_t f = F(uint32_t, 0xac);
        bool b2 = (f >> 2) & 1;
        bool b1 = (f >> 1) & 1;
        bool b3 = (f >> 3) & 1;
        uint32_t wf = W()->GetFlags();
        uint32_t st[4];
        st[0] = 0;
        st[1] = 0;
        st[2] = F(uint32_t, 0x1dc);
        st[3] = F(uint32_t, 0x1d8);
        if (!((wf >> 1) & 1))
            st[0] = 1;
        int type = F(int, 0x214);
        if (type == 2 || type == 3) {
            if (b3) st[0] = 2;
            if (b2) st[0] |= 8;
            if (b1) st[0] |= 3;
        } else if (b1) {
            st[0] = 3;
        } else if (b3) {
            st[0] = 2;
        }
        ((IPainterVt*)painter)->Paint(rc, (char*)this + 0x228, st);
    }
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                uint32_t oldv = *(uint32_t*)(style + 0x224);
                *(uint32_t*)(style + 0x224) = F(uint32_t, 0x224);
                float l = F(float, 0x258) + F(float, 0x238);
                float t = F(float, 0x25c) + F(float, 0x23c);
                float r = F(float, 0x258) + F(float, 0x240);
                float b = F(float, 0x25c) + F(float, 0x244);
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                ll->Clear(1);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                int res = ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, l, t, r, b, style, ll, 0x14);
                uint32_t h = rc->Begin2D(0);
                bool flag = W()->GetObj()->V8c();
                ((DropShadow*)((char*)this + 0x860))->F96e740(h, F(uint32_t, 0x7dc), F(uint32_t, 0x804), res,
                                                             F(uint32_t, 0x224), *F(uint16_t*, 0xb0), flag);
                *(uint32_t*)(style + 0x224) = oldv;
            }
        }
    }
    return true;
}

// @ 0x00964f10
bool WB::CalcSize(int a, float* out)
{
    if (a != 0)
        return false;
    out[0] = eastl_max(F(float, 0x90) - F(float, 0x88), 14.0f);
    out[1] = eastl_max(F(float, 0x94) - F(float, 0x8c), 14.0f);
    float lxy[2];
    lxy[0] = 0.0f;
    lxy[1] = 0.0f;
    void* obj = F(void*, 0x1e0);
    if (obj)
        ((IPainterVt*)obj)->GetSize(lxy, 0, 0);
    if ((obj == 0 || (lxy[0] == 0.0f && lxy[1] == 0.0f)) && F(uint16_t*, 0xb0) == F(uint16_t*, 0xb4))
        return false;
    float pw = out[0];
    float tx = 0.0f, ty = 0.0f;
    float fv7 = 0.0f, fv8 = 0.0f;
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                float bh = F(float, 0x240) - F(float, 0x238);
                if (bh < 1.0f)
                    bh = 100.0f;
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                ll->Clear(1);
                ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, bh, 10000.0f, style, ll, 0);
                if (F(uint32_t, 0x858) < 2) {
                    ll->Clear(1);
                    ts->LayoutLine(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, style);
                }
                float cnt = (float)F(uint32_t, 0x858);
                tx = (F(float, 0x848) + F(float, 0x254)) + F(float, 0x24c);
                ty = ((F(float, 0x850) - F(float, 0x854)) * cnt + F(float, 0x250)) + F(float, 0x248);
                fv7 = tx;
                fv8 = ty;
            }
        }
    }
    if (!(F(uint8_t, 0x218) & 2)) {
        pw = eastl_max(lxy[0], fv8);
    } else {
        uint32_t m = F(uint32_t, 0x21c);
        if (m != 0) {
            if (m > 2) {
                if (m == 3)
                    pw = lxy[0];
            } else {
                pw = fv8 + lxy[0];
            }
        }
    }
    float ph = eastl_max(lxy[1], fv7);
    out[0] = eastl_max(pw, 14.0f);
    out[1] = eastl_max(ph, 14.0f);
    return true;
}

// @ 0x009656d0
namespace EA { namespace UTFWinControls {
void __thiscall ButtonDrawable::Paint(UTFWin::RenderContext_s0096_56d0* ctx, const float* rc, const DrawState* st)
{
    using namespace UTFWin;
    if (mpImage) {
        float src[4];
        if (GetSourceRect(st->flags, src)) {
            Graphics2D* g = ctx->Begin2D(0);
            g->SetColor(0xffffffff);
            if (mbTileable) {
                float edge[4];
                edge[0] = 0.33333334f;
                edge[1] = 0.33333334f;
                edge[2] = 0.6666667f;
                edge[3] = 0.6666667f;
                Drawing::BltEdgeStretch(g, rc, src, mpImage, edge, kOne, kOne);
            } else {
                g->DrawImageScaled(rc, mpImage, src);
            }
            return;
        }
    }
    Graphics2D* g = ctx->Begin2D(0);
    g->SetColor(0xffffffff);
    uint32_t flags = st->flags;
    uint32_t state = flags & 7;
    if (flags & 8)
        state = 3;
    switch (state) {
    case 0:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xffffffff);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        g->SetColor(0xfff1efe2);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        break;
    case 1:
    case 3:
    case 8:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff000000);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        break;
    case 2:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 3.0f, rc[1] + 3.0f, rc[2] - 3.0f, rc[3] - 3.0f);
        g->SetColor(0xffffffff);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xfff1efe2);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 3.0f, rc[1] + 3.0f);
        FillRect(g, rc[0] + 2.0f, rc[1] + 3.0f, rc[0] + 3.0f, rc[3] - 3.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 3.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 3.0f);
        FillRect(g, rc[0] + 2.0f, rc[3] - 3.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff000000);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        break;
    default:
        break;
    }
}
}}  // namespace EA::UTFWinControls
