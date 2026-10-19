// src/game/UTFSpore_Win32/RenderUtils.cpp -- migrated from slice(s) s0095d000, s0095b310 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/RenderUtils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Renderable2DBuilder.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/UTFWin/IRenderable.h"
#include "EA/UTFWin/IRenderer.h"
#include "EA/Thread/Mutex.h"
#include "EA/Text/Typesetter.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_1471064, g_1485720, g_1470f1c, g_13eb1bc_f;

// ---- items of slice s0095b310 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t u8;
typedef uint32_t u32;
struct Node { Node* next; Node* prev; };
struct V2 {
    float x, y;
    V2() {}
    V2(float a, float b) : x(a), y(b) {}
    V2(const V2& o) : x(o.x), y(o.y) {}
};
struct IWin;
struct IRel { virtual void r0(); virtual void Release(); };   // vtbl+4
struct IWin {
    virtual void i00();
    virtual void i01();
    virtual void i02();
    virtual void i03();
    virtual IWin* vGetParent();
    virtual void i05();
    virtual void i06();
    virtual void i07();
    virtual void i08();
    virtual void i09();
    virtual void i0a();
    virtual void i0b();
    virtual void i0c();
    virtual void i0d();
    virtual void i0e();
    virtual void i0f();
    virtual void i10();
    virtual void i11();
    virtual void i12();
    virtual void i13();
    virtual void i14();
    virtual void i15();
    virtual void i16();
    virtual void i17();
    virtual void i18();
    virtual void i19();
    virtual void i1a();
    virtual void i1b();
    virtual void i1c();
    virtual void i1d();
    virtual void i1e();
    virtual void vSetFlags(int a, int b);              // vtbl+0x7c (31)
    virtual void i32(); virtual void i33(); virtual void i34(); virtual void i35();
    virtual void i36(); virtual void i37(); virtual void i38(); virtual void i39();
    virtual void i40(); virtual void i41(); virtual void i42(); virtual void i43();
    virtual void i44(); virtual void i45(); virtual void i46();
    virtual bool vHitLocal(V2 p);                      // vtbl+0xbc (47)
    virtual void i48();
    virtual V2 vToLocal(V2 p);                         // vtbl+0xc4 (49)
    virtual bool vHit(V2 p, V2* out);                  // vtbl+0xc8 (50)
    virtual void i51(); virtual void i52(); virtual void i53(); virtual void i54();
    virtual void i55(); virtual void i56(); virtual void i57();
    virtual void vSetOwner(IWin* w);                   // vtbl+0xe8 (58)
    virtual void i59(); virtual void i60(); virtual void i61();
    virtual bool vAccepts(IWin* w);                    // vtbl+0xf8 (62)
};
struct ChunkItem { IRel* obj; u32 b; };
struct Chunk { Chunk* next; int count; ChunkItem items[5]; void __thiscall Swap(Chunk* o); };   // Swap 0x95ba90
typedef uint16_t u16;
struct RectF {
    float x0, y0, x1, y1;
    void __thiscall Intersect(const RectF& a, const RectF& b);     // 0x634b60
};
struct Xform {
    float m[17];                                                    // 0x44 bytes (Matrix43)
    void __thiscall Init(const float* trans, const float* scale);   // 0x95e810
    void __thiscall Multiply(const Xform* o);                       // 0x95f860
};
struct RenderCtx;
struct IRenderable {
    virtual void AddRef();                                          // +0
    virtual void Release();                                         // +4
    virtual void r2();
    virtual void Render(RenderCtx* c);                              // +0xc
};
struct IRenderMode {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void Begin();                                           // +0x10
    virtual void Render(IRenderable* r, RenderCtx* c);              // +0x14
    virtual void End();                                             // +0x18
    virtual bool vFlag();                                           // +0x1c
};
struct IRenderer {
    virtual void AddRef(); virtual void Release(); virtual void r2();
    virtual bool NeedsPrepass();                                    // +0xc
    virtual void* CreateData(IWin* w);                              // +0x10
    virtual void  FreeData(void* d);                                // +0x14
    virtual void  RenderBatch(void* data, RenderCtx* c, Node** begin, int n, int flag);   // +0x18
    virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16();
    virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
    virtual void DrawRect(const RectF* dst, const RectF* clip, const RectF* uv);   // +0x58
};
struct Base2D {                                                  // size 0x24
    Base2D(void* a);                                             // 0x9520a0
    virtual ~Base2D();                                           // 0x951ba0
    u32 d[8];
};
struct Builder {
    Builder();                                                   // 0x952aa0
    ~Builder();                                                  // 0x952f80
    u32 d[40];
};
struct Batch2D : Base2D {
    Builder b;                                                       // +0x24
    Batch2D(void* a) : Base2D(a) {}
    IRenderable* __thiscall Take();                                  // 0x9557c0
};
struct RenderData {                                                  // 0x5c
    Xform xf;                                                        // +0
    float r0, r1, r2, r3;                                            // +0x44 clip rect
    u32 shade;                                                       // +0x54
    void* rdata;                                                     // +0x58
};
struct DispEntry {                                                   // 0x100
    Node link;                                                       // +0
    DispEntry* prevEntry;                                            // +8
    u8 bReplace, bActive, bSecond, pad0f;                            // +0xc..
    u16 depth, lowest;                                               // +0x10 / +0x12
    IRenderer* renderer;                                             // +0x14
    Chunk chunks;                                                    // +0x18 (0x30)
    RenderData data[2];                                              // +0x48
};
struct RenderCtx {
    Xform* xf;          // 0
    u32    shade;       // 4
    RectF  clip;        // 8
    RectF  vp;          // 0x18
    float  trans[3];    // 0x28
    float  scale[3];    // 0x34
    IRenderMode* mode;  // 0x40
    IRenderMode* defMode;   // 0x44
    Node*  list;        // 0x48
    Xform* mat;         // 0x4c
    u32    colorMod;    // 0x50
    Chunk* chunks;      // 0x54
    Batch2D batch;      // 0x58

    // @ 0x95bb80
    RenderCtx(void* a) : mode(0), defMode(0), mat(0), colorMod(0xffffffff), chunks(0), batch(a) {}
    // @ 0x95bb20
    void __thiscall End2D();
    // @ 0x95bbc0
    void __thiscall AddRenderable(IRenderable* r);
    // @ 0x95bc10
    Batch2D* __thiscall Begin2D(IRenderMode* m);
    // @ 0x95bc40
    Node** __thiscall RenderBatch(Node** pIt, DispEntry* head, int flag);
    // @ 0x95bd60
    void __thiscall RenderList(Node* lst, const RectF* r);
};
extern const float g_1471064, g_1485720, g_1470f1c, g_13eb1bc_f;
// ---- items of slice s0095b310 end

// ---- items of slice s0095d000 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct Image_s0095_d000 { char pad0[0x1c]; int width; int height; };   // +0x1c w, +0x20 h
}
}
namespace EA {
namespace UTFWin {
struct Canvas {
    virtual void v00();
    virtual void SetColor(uint32_t);                                  // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(float, float, float, float);                     // +0x38
    virtual void FillQuad();                                          // +0x3c
    virtual void v16(); virtual void v17();
    virtual void DrawQuad(const void*, float, const void*, float,
                          const void*, float, const void*, float);    // +0x48
    virtual void v19(); virtual void v20(); virtual void v21();
    virtual void DrawImage(const float* rect, Image_s0095_d000* img, const float* uv); // +0x58
};
}
}
namespace EA {
namespace UTFWin {
namespace Color {
uint32_t __cdecl Lerp(uint32_t a, uint32_t b, float t);               // 0x7f5eb0
}
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl BltEdgeStretch(Canvas*, const float* dest, const float* edge, Image_s0095_d000* img,
                            const float* uv, float sx, float sy);                     // 0x95d000
}
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl GradientBox(Canvas*, const float* outer, const float* inner,
                         const float* colOuter, const float* colInner);               // 0x95d540
}
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl DrawStdButton(Canvas*, const float* rect, uint32_t color, uint32_t state,
                           float thickness);                                          // 0x95d780
}
}
}
// ---- items of slice s0095d000 end

// @ 0x0095c0d0
void __cdecl DrawClippedRect(IRenderer* obj, const RectF* a, const RectF* c, const RectF* b)
{
    float x0 = a->x0;
    RectF R;
    if (x0 >= b->x0 && b->x1 >= a->x1 && a->y0 >= b->y0 && b->y1 >= a->y1) {
        R.x0 = 0.0f; R.y0 = 0.0f; R.x1 = g_1485720; R.y1 = g_1485720;   // full-texture uv
        obj->DrawRect(a, c, &R);
        return;
    }
    float x1 = a->x1;
    float y1 = a->y1;
    float y0 = a->y0;
    float w = x1 - x0;
    float h = y1 - y0;
    if (g_1485720 > w || g_1485720 > h)
        return;
    R.x0 = x0; R.y0 = y0; R.x1 = x1; R.y1 = y1;
    R.Intersect(*a, *b);
    if (R.x0 == R.x1 || R.y0 == R.y1)
        return;
    float sx = g_1485720 / w;
    float sy = g_1485720 / h;
    RectF uv;
    uv.x0 = (R.x0 - x0) * sx;
    uv.y0 = (R.y0 - a->y0) * sy;
    uv.x1 = (R.x1 - x0) * sx;
    uv.y1 = (R.y1 - a->y0) * sy;
    obj->DrawRect(&R, c, &uv);
}

// @ 0x0095d000
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl BltEdgeStretch(Canvas* c, const float* dest, const float* edge, Image_s0095_d000* img, const float* uv, float sx, float sy)
{
    float iw = (float)img->width;
    float ih = (float)img->height;
    float dw = edge[2] - edge[0];
    float dh = edge[3] - edge[1];
    float du = iw * dw * sx;
    float dv = ih * dh * sy;
    float fx0 = uv[0] * du + dest[0];
    float fy0 = uv[1] * dv + dest[1];
    float fx1 = dest[2] - (1.0f - uv[2]) * du;
    float fy1 = dest[3] - (1.0f - uv[3]) * dv;
    if (!(fx1 >= fx0)) { fx0 = fx1 = (fx1 + fx0) * 0.5f; }
    if (!(fy1 >= fy0)) { fy0 = fy1 = (fy1 + fy0) * 0.5f; }

    float xs[4] = { dest[0], fx0, fx1, dest[2] };
    float ys[4] = { dest[1], fy0, fy1, dest[3] };
    float us[4] = { edge[0], uv[0], uv[2], edge[2] };
    float vs[4] = { edge[1], uv[1], uv[3], edge[3] };

    // corners (always)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i == 1 && !(fx1 > fx0)) || (j == 1 && !(fy1 > fy0)))
                continue;
            float r[4] = { xs[i], ys[j], xs[i + 1], ys[j + 1] };
            float t[4] = { us[i], vs[j], us[i + 1], vs[j + 1] };
            c->DrawImage(r, img, t);
        }
    }
}
}}}  // namespace EA::UTFWin::Drawing

// @ 0x0095d540
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl GradientBox(Canvas* c, const float* outer, const float* inner, const float* colOuter, const float* colInner)
{
    if (outer[0] == outer[2])
        return;
    if (outer[1] == outer[3])
        return;
    float ox0 = outer[0], oy0 = outer[1], ox1 = outer[2], oy1 = outer[3];
    float ix0 = inner[0], iy0 = inner[1], ix1 = inner[2], iy1 = inner[3];
    struct P { float x, y; };
    // top, bottom, left, right bands, each as a quad with outer/inner colours
    {
        P p0 = { ox0, oy0 }, p1 = { ox1, oy0 }, p2 = { ix0, iy0 }, p3 = { ix1, iy0 };
        c->DrawQuad(&p0, colOuter[0], &p1, colOuter[2], &p2, colInner[0], &p3, colInner[2]);
    }
    {
        P p0 = { ox0, oy1 }, p1 = { ox1, oy1 }, p2 = { ix0, iy1 }, p3 = { ix1, iy1 };
        c->DrawQuad(&p0, colOuter[1], &p1, colOuter[3], &p2, colInner[1], &p3, colInner[3]);
    }
    {
        P p0 = { ox0, oy0 }, p1 = { ox0, oy1 }, p2 = { ix0, iy0 }, p3 = { ix0, iy1 };
        c->DrawQuad(&p0, colOuter[0], &p1, colOuter[1], &p2, colInner[0], &p3, colInner[1]);
    }
    {
        P p0 = { ox1, oy0 }, p1 = { ox1, oy1 }, p2 = { ix1, iy0 }, p3 = { ix1, iy1 };
        c->DrawQuad(&p0, colOuter[2], &p1, colOuter[3], &p2, colInner[2], &p3, colInner[3]);
    }
}
}}}  // namespace EA::UTFWin::Drawing

// @ 0x0095d780
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl DrawStdButton(Canvas* c, const float* rect, uint32_t color, uint32_t state, float thickness)
{
    (void)thickness;
    float x0 = rect[0] + 3.0f;
    float y0 = rect[1] + 3.0f;
    float x1 = rect[2] - 3.0f;
    float y1 = rect[3] - 3.0f;
    uint32_t local_30, local_2c, local_28, local_24;
    uint32_t local_10, local_c, local_8, local_4;
    uint32_t uVar2, uVar1;
    uint32_t col = color;

    if ((state & 8) == 0) {
        switch (state & 7) {
        case 0: break;
        case 1: goto LAB_866;
        case 2:
            col = Color::Lerp(col, col | 0xffffff, 0.4f);
            break;
        case 3: goto CASED0;
        default: goto DEFAULT_;
        }
        local_30 = Color::Lerp(col, col | 0xffffff, 0.6f);
        local_2c = Color::Lerp(col, col | 0xffffff, 0.9f);
        uVar2 = col & 0xff000000;
    } else {
        switch (state & 7) {
        case 0:
        case 3:
        CASED0:
            col = Color::Lerp(col, col & 0xff000000, 0.1f);
            break;
        case 1:
        LAB_866:
            col = Color::Lerp(col, 0xff7f7f7f, 0.2f);
            local_30 = Color::Lerp(col, col | 0xffffff, 0.2f);
            local_2c = Color::Lerp(col, col | 0xffffff, 0.3f);
            uVar2 = col & 0xff000000;
            local_28 = Color::Lerp(col, uVar2, 0.2f);
            uVar1 = 0x3e99999a;
            goto LAB_945;
        case 2: break;
        default: goto DEFAULT_;
        }
        local_30 = Color::Lerp(col, col & 0xff000000, 0.4f);
        local_2c = Color::Lerp(col, col & 0xff000000, 0.7f);
        uVar2 = col | 0xffffff;
    }
    local_28 = Color::Lerp(col, uVar2, 0.4f);
    uVar1 = 0x3f333333;
LAB_945:
    local_24 = Color::Lerp(col, uVar2, *(float*)&uVar1);
DEFAULT_:
    local_10 = col; local_c = col; local_8 = col; local_4 = col;
    GradientBox(c, rect, (const float*)&x0, (const float*)&local_30, (const float*)&local_10);
    c->SetColor(col);
    c->v14((float)local_24, x0, y0, x1);
    (void)y1; (void)local_28;
}
}}}  // namespace EA::UTFWin::Drawing
