// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (the original uses scalar SSE float math)
#include "types.h"

namespace EA { namespace UTFWin {
struct Image { char pad0[0x1c]; int width; int height; };
struct Vec2 { float x, y; };
struct Canvas {
    virtual void v0();
    virtual void SetColor(uint32_t argb);                       // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void FillQuad(const Vec2* a, const Vec2* b, const Vec2* c, const Vec2* d); // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void DrawImage(const float* rect, Image* img, const float* uv);            // +0x58
};
struct RenderContext { Canvas* Begin2D(int); };
namespace Drawing {
void __cdecl BltEdgeStretch(Canvas*, const float* rect, const float* edge, Image* img,
                            const float* uv, Vec2 scale);
}
}}

namespace EA { namespace UTFWinControls {
using namespace EA::UTFWin;

struct DrawInfo { uint32_t flags; uint32_t part; };

static inline void Quad(Canvas* c, float ax, float ay, float bx, float by,
                        float cx, float cy, float dx, float dy)
{
    Vec2 a = { ax, ay }, b = { bx, by }, cc = { cx, cy }, d = { dx, dy };
    c->FillQuad(&a, &b, &cc, &d);
}

struct ScrollbarDrawable {
    char pad[0x10];
    Image* mComponentImage[7];

    // @ 0x00982780
    void __thiscall Paint(RenderContext* rc, const float* r, const DrawInfo* info);
};

void ScrollbarDrawable::Paint(RenderContext* rc, const float* r, const DrawInfo* info)
{
    Canvas* c = rc->Begin2D(0);
    c->SetColor(0xffffffff);
    uint32_t part = info->part;
    Image* img = mComponentImage[part];
    float L, T, R, B;                    // read from r only on the paths that draw quads

    switch (part) {
    case 0:
        if (img) {
            float edge[4], uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
            edge[0] = 0.5f - 0.5f / (float)img->width;
            edge[1] = 0.5f - 0.5f / (float)img->height;
            edge[2] = 0.5f / (float)img->width + 0.5f;
            edge[3] = 0.5f / (float)img->height + 0.5f;
            Vec2 one = { 1.0f, 1.0f };
            Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
        }
        break;

    case 1:
    case 3:
    case 6:
        if (img) {
            float u = 0.0f;
            switch (info->flags & 7) {
            case 0:
                if ((info->flags & 8) == 0) { u = 0.25f; break; }
                u = 0.75f;
                break;
            case 3: u = 0.75f; break;
            case 1: u = 0.0f; break;
            case 2: u = 0.5f; break;
            }
            float uv[4] = { u, 0.0f, u + 0.25f, 1.0f };
            if (part == 3) {
                float edge[4];
                edge[0] = 0.5f - 0.5f / (float)img->width;
                edge[1] = 0.5f - 0.5f / (float)img->height;
                edge[2] = 0.5f / (float)img->width + 0.5f;
                edge[3] = 0.5f / (float)img->height + 0.5f;
                Vec2 one = { 1.0f, 1.0f };
                Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
                return;
            }
            c->DrawImage(r, img, uv);
            return;
        }

        L = r[0]; T = r[1]; R = r[2]; B = r[3];
        if ((info->flags & 7) == 3) {
            c->SetColor(0xffece9d8);
            Quad(c, L + 1.0f, T + 1.0f, R - 1.0f, T + 1.0f, R - 1.0f, B - 1.0f, L + 1.0f, B - 1.0f);
            c->SetColor(0xff716f64);
            Quad(c, L, T, R - 1.0f, T, R - 1.0f, T + 1.0f, L, T + 1.0f);
            Quad(c, L, T + 1.0f, L, B - 1.0f, L + 1.0f, B - 1.0f, L + 1.0f, T + 1.0f);
            Quad(c, R - 1.0f, T, R, T, R, B - 1.0f, R - 1.0f, B - 1.0f);
            Quad(c, L, B - 1.0f, R, B - 1.0f, R, B, L, B);
        } else {
            c->SetColor((info->flags & 2) ? 0xfffbfbf9u : 0xffece9d8u);
            Quad(c, L + 2.0f, T + 2.0f, R - 2.0f, T + 2.0f, R - 2.0f, B - 2.0f, L + 2.0f, B - 2.0f);
            c->SetColor(0xfff1efe2);
            Quad(c, L, T, R - 1.0f, T, R - 1.0f, T + 1.0f, L, T + 1.0f);
            Quad(c, L, T + 1.0f, L, B - 1.0f, L + 1.0f, B - 1.0f, L + 1.0f, T + 1.0f);
            c->SetColor(0xffffffff);
            Quad(c, L + 1.0f, T + 1.0f, R - 2.0f, T + 1.0f, R - 2.0f, T + 2.0f, L + 1.0f, T + 2.0f);
            Quad(c, L + 1.0f, T + 2.0f, L + 2.0f, T + 2.0f, L + 2.0f, B - 2.0f, L + 1.0f, B - 2.0f);
            c->SetColor(0xff716f64);
            Quad(c, R - 1.0f, T, R, T, R, B - 1.0f, R - 1.0f, B - 1.0f);
            Quad(c, L, B - 1.0f, R, B - 1.0f, R, B, L, B);
            c->SetColor(0xffaca899);
            Quad(c, R - 2.0f, T + 1.0f, R - 1.0f, T + 1.0f, R - 1.0f, B - 2.0f, R - 2.0f, B - 2.0f);
            Quad(c, L + 1.0f, B - 2.0f, R - 1.0f, B - 2.0f, R - 1.0f, B - 1.0f, L + 1.0f, B - 1.0f);
        }
        if (part == 1 || part == 6) {
            c->SetColor(0xff000000);
            float dx = (R - L) * 0.2857143f;
            float dy = (B - T) * 0.2857143f;
            float o = ((info->flags & 7) == 3) ? 1.0f : 0.0f;
            if (part == 1) {
                if (info->flags & 0x80) {
                    float x0 = L + o + dx;
                    float yb = (B - dy) + o;
                    Quad(c, x0, yb, ((R - L) * 0.5f + L) + o, (T + o) + dy,
                         (R - dx) + o, yb, x0, yb);
                } else {
                    float x0 = L + o + dx;
                    float x1 = (R - dx) + o;
                    float ym = ((B - T) * 0.5f + T) + o;
                    Quad(c, x0, ym, x1, (T + o) + dy, x1, (B - dy) + o, x0, ym);
                }
            } else {
                if (info->flags & 0x80) {
                    float x0 = L + o + dx;
                    float y0 = (o + dy) + T;
                    Quad(c, x0, y0, (R - dx) + o, y0, ((R - L) * 0.5f + L) + o, (B - dy) + o, x0, y0);
                } else {
                    float x0 = L + o + dx;
                    float y0 = (T + o) + dy;
                    Quad(c, x0, y0, (R - dx) + o, ((B - T) * 0.5f + T) + o, x0, (B - dy) + o, x0, y0);
                }
            }
        }
        break;

    case 4:
        if (img) {
            float edge[4], uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
            edge[0] = 0.5f - 0.5f / (float)img->width;
            edge[1] = 0.5f - 0.5f / (float)img->height;
            edge[2] = 0.5f / (float)img->width + 0.5f;
            edge[3] = 0.5f / (float)img->height + 0.5f;
            Vec2 one = { 1.0f, 1.0f };
            Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
            return;
        }
        c->SetColor(0xffaca899);
        L = r[0]; T = r[1]; R = r[2]; B = r[3];
        Quad(c, L, T, R, T, R, B, L, B);
        return;
    }
}

}}
