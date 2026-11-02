// src/game/UTFSpore_Win32/RenderUtils.cpp -- migrated from slice(s) s0095c260, s0095d000, s0095b310 by tools/migrate/rewrite.py
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
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void FillRectangle(uint32_t color, float x0, float y0, float x1); // +0x38
    virtual void v15();                                               // +0x3c
virtual void v16();
virtual void v17();
    virtual void FillQuadGradient(const float* topRight, uint32_t topRightColor,
                                  const float* topLeft, uint32_t topLeftColor,
                                  const float* bottomLeft, uint32_t bottomLeftColor,
                                  const float* bottomRight, uint32_t bottomRightColor); // +0x48
virtual void v19();
virtual void v20();
virtual void v21();
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
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl DrawBevel(Canvas*, const float* rect, uint32_t color, float width);      // 0x95da40
}
}
}
// ---- items of slice s0095d000 end

// ---- items of slice s0095c260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern "C" __declspec(dllimport) double __cdecl floor(double);
double iat_floor(double x) { return floor(x); }
namespace EA {
struct RectF_s0095_c260 {
  RectF_s0095_c260() {}
  RectF_s0095_c260(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
  float mLeft, mTop, mRight, mBottom;
  bool Intersect(RectF_s0095_c260 const& a, RectF_s0095_c260 const& b);  // 0x00634b60 (RectF::Intersect)
};
}
namespace EA {
struct IRenderer_s0095_c260 {
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05();
  virtual void v06();
  virtual void v07();
  virtual void v08();
  virtual void v09();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual void DrawImage(RectF_s0095_c260 const* pDst, void* pObj, RectF_s0095_c260 const* pUV);  // +0x58
};
}
namespace EA {
struct TileSource {
  char mPad[0x1c];
  int mWidth;   // +0x1c
  int mHeight;  // +0x20
};
}
using EA::IRenderer_s0095_c260;
using EA::RectF_s0095_c260;
using EA::TileSource;
void DrawClippedRect(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pRect, void* pObj, RectF_s0095_c260 const* pDst);
void FUN_0095c260(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, void* pObj,
                  RectF_s0095_c260 const* pClip);
void FUN_0095c420(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, TileSource* pObj, float sx, float sy,
                  float offx, float offy);
void FUN_0095c5f0(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj,
                  float sx, float sy, float offx, float offy);
void FUN_0095c800(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj,
                  float sx, float offx);
void FUN_0095c920(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj,
                  float sy, float offy);
void FUN_0095ca40(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj,
                  float const* pSlices, float sx, float sy);
// ---- items of slice s0095c260 end

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

// @ 0x0095c260
void FUN_0095c260(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, void* pObj, RectF_s0095_c260 const* pClip)
{
  float left = pDst->mLeft;
  if (left >= pClip->mLeft && pDst->mRight <= pClip->mRight && pDst->mTop >= pClip->mTop &&
      pDst->mBottom <= pClip->mBottom) {
    pRenderer->DrawImage(pDst, pObj, pUV);
    return;
  }
  float w = pDst->mRight - left;
  float h = pDst->mBottom - pDst->mTop;
  if (1.0f > w || 1.0f > h) return;
  RectF_s0095_c260 inter(*pDst);
  inter.Intersect(*pDst, *pClip);
  if (inter.mLeft != inter.mRight && inter.mTop != inter.mBottom) {
    float invW = 1.0f / w;
    float invH = 1.0f / h;
    float uvW = pUV->mRight - pUV->mLeft;
    float uvH = pUV->mBottom - pUV->mTop;
    RectF_s0095_c260 u;
    u.mLeft = (inter.mLeft - left) * invW * uvW + pUV->mLeft;
    u.mRight = (inter.mRight - left) * invW * uvW + pUV->mLeft;
    u.mTop = (inter.mTop - pDst->mTop) * invH * uvH + pUV->mTop;
    u.mBottom = (inter.mBottom - pDst->mTop) * invH * uvH + pUV->mTop;
    pRenderer->DrawImage(&inter, pObj, &u);
  }
}

// @ 0x0095c420
void FUN_0095c420(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, TileSource* pObj, float sx, float sy, float offx, float offy)
{
  float w = (float)pObj->mWidth * sx;
  float h = (float)pObj->mHeight * sy;
  if (1.0f > w || 1.0f > h) return;
  if (offx > 0.0f) {
    offx = offx - (float)ceil((double)(offx / w)) * w;
  } else if (offx <= w) {
    offx = (float)iat_floor((double)-(offx / w)) * w + offx;
  }
  if (offy > 0.0f) {
    offy = offy - (float)ceil((double)(offy / h)) * h;
  } else if (offy <= h) {
    offy = (float)iat_floor((double)-(offy / h)) * h + offy;
  }
  float y = pDst->mTop + offy;
  if (y < pDst->mBottom) {
    do {
      float x = pDst->mLeft + offx;
      while (x < pDst->mRight) {
        float nx = x + w;
        RectF_s0095_c260 tile(x, y, nx, y + h);
        DrawClippedRect(pRenderer, &tile, pObj, pDst);
        x = nx;
      }
      y += h;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095c5f0
void FUN_0095c5f0(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj, float sx, float sy, float offx, float offy)
{
  float w = ((pUV->mRight - pUV->mLeft) * (float)pObj->mWidth) * sx;
  float h = ((pUV->mBottom - pUV->mTop) * (float)pObj->mHeight) * sy;
  if (1.0f > w || 1.0f > h) return;
  if (offx > 0.0f) {
    offx = offx - (float)ceil((double)(offx / w)) * w;
  } else if (offx <= w) {
    offx = (float)iat_floor((double)-(offx / w)) * w + offx;
  }
  if (offy > 0.0f) {
    offy = offy - (float)ceil((double)(offy / h)) * h;
  } else if (offy <= h) {
    offy = (float)iat_floor((double)-(offy / h)) * h + offy;
  }
  float y = pDst->mTop + offy;
  if (y < pDst->mBottom) {
    do {
      float x = pDst->mLeft + offx;
      while (x < pDst->mRight) {
        float nx = x + w;
        RectF_s0095_c260 tile(x, y, nx, y + h);
        FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
        x = nx;
      }
      y += h;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095c800
void FUN_0095c800(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj, float sx, float offx)
{
  float w = ((pUV->mRight - pUV->mLeft) * (float)pObj->mWidth) * sx;
  if (1.0f > w) return;
  if (offx > 0.0f) {
    offx = offx - (float)ceil((double)(offx / w)) * w;
  } else if (offx <= w) {
    offx = (float)iat_floor((double)-(offx / w)) * w + offx;
  }
  float x = pDst->mLeft + offx;
  if (x < pDst->mRight) {
    do {
      float nx = x + w;
      RectF_s0095_c260 tile(x, pDst->mTop, nx, pDst->mBottom);
      FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
      x = nx;
    } while (x < pDst->mRight);
  }
}

// @ 0x0095c920
void FUN_0095c920(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj, float sy, float offy)
{
  float h = ((pUV->mBottom - pUV->mTop) * (float)pObj->mHeight) * sy;
  if (1.0f > h) return;
  if (offy > 0.0f) {
    offy = offy - (float)ceil((double)(offy / h)) * h;
  } else if (offy <= h) {
    offy = (float)iat_floor((double)-(offy / h)) * h + offy;
  }
  float y = pDst->mTop + offy;
  if (y < pDst->mBottom) {
    do {
      float ny = y + h;
      RectF_s0095_c260 tile(pDst->mLeft, y, pDst->mRight, ny);
      FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
      y = ny;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095ca40
void FUN_0095ca40(IRenderer_s0095_c260* pRenderer, RectF_s0095_c260 const* pDst, RectF_s0095_c260 const* pUV, TileSource* pObj, float const* pSlices, float sx, float sy)
{
  float a = pSlices[0];
  float b = pSlices[1];
  float c = pSlices[2];
  float d = pSlices[3];
  float uvW = pUV->mRight - pUV->mLeft;
  float uvH = pUV->mBottom - pUV->mTop;
  float wStep = ((float)pObj->mWidth * uvW) * sx;
  float hStep = ((float)pObj->mHeight * uvH) * sy;

  float left = pDst->mLeft + a * wStep;
  float top = pDst->mTop + b * hStep;
  float right = pDst->mRight - (1.0f - c) * wStep;
  float bottom = pDst->mBottom - (1.0f - d) * hStep;
  if (left > right) {
    left = (left + right) * 0.5f;
    right = left;
  }
  if (top > bottom) {
    top = (top + bottom) * 0.5f;
    bottom = top;
  }

  float ul = pUV->mLeft + uvW * a;
  float ut = pUV->mTop + uvH * b;
  float ur = pUV->mLeft + uvW * c;
  float ub = pUV->mTop + uvH * d;

  RectF_s0095_c260 uvTL(pUV->mLeft, pUV->mTop, ul, ut);
  RectF_s0095_c260 dstTL(pDst->mLeft, pDst->mTop, left, top);
  pRenderer->DrawImage(&dstTL, pObj, &uvTL);

  RectF_s0095_c260 uvTR(ur, pUV->mTop, pUV->mRight, ut);
  RectF_s0095_c260 dstTR(right, pDst->mTop, pDst->mRight, top);
  pRenderer->DrawImage(&dstTR, pObj, &uvTR);

  RectF_s0095_c260 uvBL(pUV->mLeft, ub, ul, pUV->mBottom);
  RectF_s0095_c260 dstBL(pDst->mLeft, bottom, left, pDst->mBottom);
  pRenderer->DrawImage(&dstBL, pObj, &uvBL);

  RectF_s0095_c260 uvBR(ur, ub, pUV->mRight, pUV->mBottom);
  RectF_s0095_c260 dstBR(right, bottom, pDst->mRight, pDst->mBottom);
  pRenderer->DrawImage(&dstBR, pObj, &uvBR);

  if (left < right) {
    RectF_s0095_c260 dstTop(left, pDst->mTop, right, top);
    RectF_s0095_c260 uvTop(ul, pUV->mTop, ur, ut);
    FUN_0095c800(pRenderer, &dstTop, &uvTop, pObj, sx, 0.0f);
    RectF_s0095_c260 dstBot(left, bottom, right, pDst->mBottom);
    RectF_s0095_c260 uvBot(ul, ub, ur, pUV->mBottom);
    FUN_0095c800(pRenderer, &dstBot, &uvBot, pObj, sx, 0.0f);
  }
  if (top < bottom) {
    RectF_s0095_c260 dstLeft(pDst->mLeft, top, left, bottom);
    RectF_s0095_c260 uvLeft(pUV->mLeft, ut, ul, ub);
    FUN_0095c920(pRenderer, &dstLeft, &uvLeft, pObj, sy, 0.0f);
    RectF_s0095_c260 dstRight(right, top, pDst->mRight, bottom);
    RectF_s0095_c260 uvRight(ur, ut, pUV->mRight, ub);
    FUN_0095c920(pRenderer, &dstRight, &uvRight, pObj, sy, 0.0f);
  }
  if (left != right && top != bottom) {
    RectF_s0095_c260 dstMid(left, top, right, bottom);
    RectF_s0095_c260 uvMid(ul, ut, ur, ub);
    FUN_0095c5f0(pRenderer, &dstMid, &uvMid, pObj, sx, sy, 0.0f, 0.0f);
  }
}

// @ 0x0095d000
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl BltEdgeStretch(Canvas* c, const float* dest, const float* edge, Image_s0095_d000* img, const float* uv, float sx, float sy)
{
    float ew = edge[2] - edge[0];               // xmm0 - horizontal extent of the uv border box
    float eh = edge[3] - edge[1];               // xmm1 - vertical extent
    float du = (float)img->width * ew * sx;     // xmm3 - tile width
    float dv = (float)img->height * eh * sy;    // xmm4 - tile height

    float fx0 = uv[0] * du + dest[0];
    float fy0 = uv[1] * dv + dest[1];
    float fx1 = dest[2] - (1.0f - uv[2]) * du;
    float fy1 = dest[3] - (1.0f - uv[3]) * dv;
    if (fx1 < fx0) { fx0 = fx1 = (fx1 + fx0) * 0.5f; }
    if (fy1 < fy0) { fy0 = fy1 = (fy1 + fy0) * 0.5f; }

    // Scratch area reused as the destination rect / uv rect of every blit below.
    float q[8];
    q[0] = edge[0]; q[1] = edge[1]; q[2] = edge[2]; q[3] = edge[3];

    // top-left corner
    q[4] = dest[0]; q[5] = dest[1]; q[6] = fx0; q[7] = fy0;
    { float u[4] = { q[0], q[1], q[4] + ew * uv[0], q[1] + eh * uv[1] }; c->DrawImage(q + 4, img, u); }
    // top-right corner
    q[4] = fx1; q[5] = dest[1]; q[6] = dest[2]; q[7] = fy0;
    { float u[4] = { q[0], q[5], q[4] + ew * uv[2], q[5] + eh * uv[1] }; c->DrawImage(q + 4, img, u); }
    // bottom-left corner
    q[4] = dest[0]; q[5] = fy1; q[6] = fx0; q[7] = dest[3];
    { float u[4] = { q[5], q[1], q[6], q[2] }; c->DrawImage(q + 4, img, u); }
    // bottom-right corner
    q[4] = fx1; q[5] = fy1; q[6] = dest[2]; q[7] = dest[3];
    { float u[4] = { q[4], q[5], fx1, fy1 }; c->DrawImage(q + 4, img, u); }

    if (fx1 - fx0 > 0.0f) {
        // top band
        q[4] = fx0; q[5] = dest[1]; q[6] = fx1; q[7] = fy0;
        { float u[4] = { q[0], q[5], q[6], q[2] }; c->DrawImage(q + 4, img, u); }
        // bottom band
        q[4] = fx0; q[5] = fy1; q[6] = fx1; q[7] = dest[3];
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
    if (fy1 - fy0 > 0.0f) {
        // left band
        q[4] = dest[0]; q[5] = fy0; q[6] = fx0; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
        // right band
        q[4] = fx1; q[5] = fy0; q[6] = dest[2]; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
    if (fx0 != fx1 && fy0 != fy1) {
        // centre
        q[4] = fx0; q[5] = fy0; q[6] = fx1; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
}
}}}  // namespace EA::UTFWin::Drawing

// @ 0x0095d540
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl GradientBox(Canvas* c, const float* outer, const float* inner, const float* colOuter, const float* colInner)
{
    if (outer[0] == outer[2] || outer[1] == outer[3])
        return;

    // The gradient colour arrays arrive as raw ARGB words stored behind a "const float*" API.
    const uint32_t* co = (const uint32_t*)colOuter;
    const uint32_t* ci = (const uint32_t*)colInner;

    float oTL[2] = { outer[0], outer[1] };
    float oTR[2] = { outer[2], outer[1] };
    float oBL[2] = { outer[0], outer[3] };
    float oBR[2] = { outer[2], outer[3] };
    float iTL[2] = { inner[0], inner[1] };
    float iTR[2] = { inner[2], inner[1] };
    float iBL[2] = { inner[0], inner[3] };
    float iBR[2] = { inner[2], inner[3] };

    // left band
    c->FillQuadGradient(oTL, co[0], iTL, ci[0], iBL, ci[0], oBL, co[0]);
    // top band
    c->FillQuadGradient(oTL, co[1], oTR, co[1], iTR, ci[1], iTL, ci[1]);
    // right band
    c->FillQuadGradient(iTR, ci[2], oTR, co[2], oBR, co[2], iBR, ci[2]);
    // bottom band
    c->FillQuadGradient(iBL, ci[3], iBR, ci[3], oBR, co[3], oBL, co[3]);
}
}}}  // namespace EA::UTFWin::Drawing

// @ 0x0095d780
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl DrawStdButton(Canvas* c, const float* rect, uint32_t color, uint32_t state, float thickness)
{
    float inner[4];
    inner[0] = rect[0] + 3.0f;
    inner[1] = rect[1] + 3.0f;
    inner[2] = rect[2] - 3.0f;
    inner[3] = rect[3] - 3.0f;
    (void)thickness;

    uint32_t col = color;
    uint32_t g[4];             // four gradient colours (g[0]..g[3] = original local_30..local_24)
    uint32_t hi;               // the "highlight" endpoint colour

    if ((state & 8) == 0) {
        switch (state & 7) {
        case 0: break;
        case 1: goto LAB_866;
        case 2:
            col = Color::Lerp(col, col | 0xffffff, 0.4f);
            break;
        case 3: goto CASE_8_0_3;
        default: goto DEFAULT_;
        }
        g[0] = Color::Lerp(col, col | 0xffffff, 0.6f);
        g[1] = Color::Lerp(col, col | 0xffffff, 0.9f);
        hi = col & 0xff000000;
    } else {
        switch (state & 7) {
        case 0:
        case 3:
        CASE_8_0_3:
            col = Color::Lerp(col, col & 0xff000000, 0.1f);
            break;
        case 1:
        LAB_866:
            col = Color::Lerp(col, 0xff7f7f7f, 0.2f);
            g[0] = Color::Lerp(col, col | 0xffffff, 0.2f);
            g[1] = Color::Lerp(col, col | 0xffffff, 0.3f);
            hi = col & 0xff000000;
            g[2] = Color::Lerp(col, hi, 0.2f);
            goto FINISH_HI03;
        case 2: break;
        default: goto DEFAULT_;
        }
        g[0] = Color::Lerp(col, col & 0xff000000, 0.4f);
        g[1] = Color::Lerp(col, col & 0xff000000, 0.7f);
        hi = col | 0xffffff;
    }
    g[2] = Color::Lerp(col, hi, 0.4f);
    g[3] = Color::Lerp(col, hi, 0.7f);
    goto DRAW;

FINISH_HI03:
    g[3] = Color::Lerp(col, hi, 0.3f);
    goto DRAW;

DEFAULT_:
    // The original's default case (state&7 > 3) jumps straight to the draw with the four
    // gradient colours left uninitialised; keep that shape (no writes here).
DRAW:
    {
        uint32_t fill[4] = { col, col, col, col };
        GradientBox(c, rect, inner, (const float*)g, (const float*)fill);
    }
    c->SetColor(col);
    c->FillRectangle(g[3], inner[0], inner[1], inner[2]);
}
}}}  // namespace EA::UTFWin::Drawing

// @ 0x0095da40
namespace EA { namespace UTFWin { namespace Drawing {
void __cdecl DrawBevel(Canvas* c, const float* rect, uint32_t color, float width)
{
    // The colour arrays are raw ARGB words behind a "const float*" API (cleared first, then
    // filled with the flat colour), matching the original's integer stores.
    uint32_t colInner[4] = { 0, 0, 0, 0 };
    uint32_t colOuter[4] = { color, color, color, color };

    float half = width * 0.5f;

    float outerHalf[4];
    outerHalf[0] = rect[0] - half;
    outerHalf[1] = rect[1] - half;
    outerHalf[2] = rect[2] + half;
    outerHalf[3] = rect[3] + half;

    float outerFull[4];
    outerFull[0] = rect[0] - width;
    outerFull[1] = rect[1] - width;
    outerFull[2] = rect[2] + width;
    outerFull[3] = rect[3] + width;

    GradientBox(c, outerHalf, rect, (const float*)colOuter, (const float*)colInner);
    GradientBox(c, outerFull, outerHalf, (const float*)colInner, (const float*)colOuter);
}
}}}  // namespace EA::UTFWin::Drawing
