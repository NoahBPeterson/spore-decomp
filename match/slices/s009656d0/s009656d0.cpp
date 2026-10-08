// Slice s009656d0: EA::UTFWinControls::ButtonDrawable::Paint (0x009656d0)
// (PDB candidate name: ButtonDrawable::CreateRenderables, but the body is the drawable paint:
// it begins 2D rendering and either blits the state image or draws the classic Windows
// bevelled button with flat quads). __thiscall, this in ECX, three stack args, `ret 0xc`.
// UI module flags: /O2 /MD /Gy /TP /arch:SSE (same family as the SliderDrawable paint).
//
// Behavior:
//  * If the drawable has an image (+0x10) and slot +0x20 yields a source rectangle for the
//    current state flags, draw it (stretched with BltEdgeStretch when tileable (+0x14),
//    otherwise as a plain scaled image) and return.
//  * Otherwise draw the flat-quad fallback chosen by the state flags (bits 0-2 = state,
//    bit 3 = disabled, handled as state 3):
//      0         raised bevel (white/light top-left, dark bottom-right)
//      1, 3, 8   sunken one-pixel look with a black outline
//      2         thicker (3 px) bevel with a black outline
//      4..7      nothing
#include "types.h"

namespace EA { namespace UTFWin {
struct Image { uint32_t pad[8]; };

struct Point2 { float x, y; };

// Graphics2D vtable (slot byte offsets): 0x04 SetColor, 0x3c FillQuad, 0x58 DrawImageScaled
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
    virtual void DrawImageScaled(const float* area, const Image* image, const float* texCoords);
};

struct RenderContext {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};

namespace Drawing {
void __cdecl BltEdgeStretch(Graphics2D* g, const float* rect, const float* src, const Image* image,
                            const float* uv, float sx, float sy);   // 0x95d000
}
}}

extern const float kOne;                // 0x01485720 = 1.0f

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

namespace EA { namespace UTFWinControls {

struct DrawState { uint32_t flags; };

struct ButtonDrawable {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool GetSourceRect(uint32_t flags, float* out);   // +0x20
    uint32_t pad[3];                    // +0x04 (second base, refcount ...)
    UTFWin::Image* mpImage;             // +0x10
    bool mbTileable;                    // +0x14
    void __thiscall Paint(UTFWin::RenderContext* ctx, const float* rc, const DrawState* st);
};

// @ 0x009656d0
void __thiscall ButtonDrawable::Paint(UTFWin::RenderContext* ctx, const float* rc, const DrawState* st) {
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

}}
