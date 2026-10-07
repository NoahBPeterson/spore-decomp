// Slice s00986680: EA::UTFWinControls::SpinnerDrawable::CreateRenderables (UTFWin 2D renderer).
// Draws one spinner button (part 1 = up/left, part 2 = down/right): either a quarter of the button image strip, or
// a WinXP-style bevelled button plus an arrow triangle (as a degenerate quad).
// Shape and Graphics2D slots follow the sibling SliderDrawable (s00984a70).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace UTFWin {
struct Image { uint32_t pad[7]; int mWidth; int mHeight; };

struct Point2 { float x, y; Point2(float ax, float ay) : x(ax), y(ay) {} };

// Graphics2D vtable (slot byte offsets): 0x04 SetColor, 0x3c FillQuad, 0x58 DrawImageScaled
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
    virtual void DrawImageScaled(const float* area, const Image* image, const float* texCoords);
};

struct RenderContext {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};
}}

static __forceinline void FillRect(EA::UTFWin::Graphics2D* g, float l, float t, float r, float b) {
    using EA::UTFWin::Point2;
    g->FillQuad(Point2(l, t), Point2(r, t), Point2(r, b), Point2(l, b));
}
static __forceinline void FillTriangle(EA::UTFWin::Graphics2D* g, float ax, float ay, float bx, float by,
                                       float cx, float cy) {
    using EA::UTFWin::Point2;
    g->FillQuad(Point2(ax, ay), Point2(bx, by), Point2(cx, cy), Point2(ax, ay));
}

namespace EA { namespace UTFWinControls {

struct DrawState { uint32_t flags; uint32_t part; };

struct SpinnerDrawable {
    uint32_t pad[4];                        // +0x00 (vptrs, refcount, ...)
    UTFWin::Image* mImages[3];              // +0x10 (indexed by part)
    void __thiscall CreateRenderables(UTFWin::RenderContext* ctx, const float* rc, const DrawState* st);
};

// @ 0x986680
void __thiscall SpinnerDrawable::CreateRenderables(UTFWin::RenderContext* ctx, const float* rc, const DrawState* st) {
    using namespace UTFWin;
    Graphics2D* g = ctx->Begin2D(0);
    g->SetColor(0xffffffff);
    uint32_t part = st->part;
    Image* img = mImages[part];
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

}}
