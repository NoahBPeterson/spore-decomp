// src/game/UTFSpore_Win32/Slider.cpp -- migrated from slice(s) s00985ad0, s00984a70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Slider.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWinControls/IWinSpinner.h"

// ---- items of slice s00984a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct Image_s0098_4a70 { uint32_t pad[7]; int mWidth; int mHeight; };   // +0x1c width, +0x20 height
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
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void v14();
    virtual void FillQuad(Point2& tl, Point2& tr, Point2& br, Point2& bl);
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void DrawImageScaled(const float* area, const Image_s0098_4a70* image, const float* texCoords);
};
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0098_4a70 {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl BltEdgeStretch(Graphics2D* g, const float* rect, const float* src, const Image_s0098_4a70* image,
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
struct DrawState { uint32_t flags; int imageIndex; };
}
}
namespace EA {
namespace UTFWinControls {
class SliderDrawable { public:
    uint32_t pad[5];                        // +0x00 (vptrs, refcount, ...)
    UTFWin::Image_s0098_4a70* mImages[3];              // +0x14 (indexed by imageIndex - 1)
    void __thiscall Paint(UTFWin::RenderContext_s0098_4a70* ctx, const float* rc, const DrawState* st);
};
}
}
// ---- items of slice s00984a70 end

// ---- items of slice s00985ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) { return p; }
void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)
namespace EA {
namespace UTFWinControls {
extern void* vtbl_Resource_Async[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vtbl_SliderDrawable[];         // 0x01444c90
}
}
namespace EA {
namespace UTFWinControls {
extern void* vtbl_SliderDrawable_1[];       // 0x01444c78
}
}
namespace EA {
namespace UTFWinControls {
extern void* vtbl_SliderDrawable_3[];       // 0x01444c60
}
}
namespace EA {
namespace UTFWinControls {
struct ObjHead { void* vt; };
}
}
namespace EA {
namespace UTFWinControls {
struct AsyncBase {
    void* vt4; int f8; void* vtc;
    AsyncBase() { vt4 = vtbl_Resource_Async; f8 = 0; vtc = vtbl_Resource_Async; }
};
}
}
namespace EA {
namespace UTFWinControls {
class SliderDrawable_s0098_5ad0 : public ObjHead, public AsyncBase { public:
    int f[3];                               // +0x10, +0x14, +0x18
    SliderDrawable_s0098_5ad0() {
        vt = vtbl_SliderDrawable;
        vt4 = vtbl_SliderDrawable_1;
        vtc = vtbl_SliderDrawable_3;
        f[0] = 0; f[1] = 0; f[2] = 0;
    }
};
}
}
namespace EA {
namespace UTFWinControls {
class BasicFactory_SliderDrawable { public:
    SliderDrawable_s0098_5ad0* CreateInstance(int unused, void* alloc);  // 00985bd0
};
}
}
// ---- items of slice s00985ad0 end

// @ 0x00984a70
namespace EA { namespace UTFWinControls {
void __thiscall SliderDrawable::Paint(UTFWin::RenderContext_s0098_4a70* ctx, const float* rc, const DrawState* st)
{
    using namespace UTFWin;
    Graphics2D* g = ctx->Begin2D(0);
    g->SetColor(0xffffffff);
    int n = st->imageIndex - 1;
    Image_s0098_4a70* img = mImages[n];
    if (n == 0) {
        uint32_t flags = st->flags;
        if (img) {
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
        if ((flags & 7) == 3) {
            g->SetColor(0xffece9d8);
            FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 1.0f);
            g->SetColor(0xff716f64);
            FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
            FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
            FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
            FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
            return;
        }
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
    } else if (n == 1) {
        if (img == 0) {
            float a, b, c, d;
            if ((st->flags & 0x80) == 0) {
                float W = rc[2] - rc[0];
                float H = rc[3] - rc[1];
                float t3 = H * 0.33333334f;
                float o = (H - t3) * 0.5f;
                a = 0.0f; b = o; c = W; d = o + t3;
            } else {
                float W = rc[2] - rc[0];
                float t3 = W * 0.33333334f;
                float o = (W - t3) * 0.5f;
                a = o; b = 0.0f; c = o + t3; d = rc[3] - rc[1];
            }
            g->SetColor(0xffece9d8);
            FillRect(g, a + 2.0f, b + 2.0f, c - 2.0f, d - 2.0f);
            g->SetColor(0xff716f64);
            FillRect(g, a, b, c - 1.0f, b + 1.0f);
            FillRect(g, a, b + 1.0f, a + 1.0f, d - 1.0f);
            g->SetColor(0xffaca899);
            FillRect(g, a + 1.0f, b + 1.0f, c - 2.0f, b + 2.0f);
            FillRect(g, a + 1.0f, b + 2.0f, a + 2.0f, d - 2.0f);
            g->SetColor(0xfff1efe2);
            FillRect(g, c - 1.0f, b, c, d - 1.0f);
            FillRect(g, a, d - 1.0f, c, d);
            g->SetColor(0xffffffff);
            FillRect(g, c - 2.0f, b + 1.0f, c - 1.0f, d - 2.0f);
            FillRect(g, a + 1.0f, d - 2.0f, c - 1.0f, d - 1.0f);
            return;
        }
        float hx = 0.5f / (float)img->mWidth;
        float hy = 0.5f / (float)img->mHeight;
        float src[4];
        src[0] = 0.5f - hx; src[1] = 0.5f - hy; src[2] = hx + 0.5f; src[3] = hy + 0.5f;
        float full[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
        Drawing::BltEdgeStretch(g, rc, full, img, src, 1.0f, 1.0f);
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x00985bd0
EA::UTFWinControls::SliderDrawable_s0098_5ad0* EA::UTFWinControls::BasicFactory_SliderDrawable::CreateInstance(int unused, void* alloc)
{
    (void)unused;
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x1c, 4, "UTFWin/EA::UTFWinControls::SliderDrawable", alloc);
    if (mem) return new (mem) EA::UTFWinControls::SliderDrawable_s0098_5ad0();
    return 0;
}
