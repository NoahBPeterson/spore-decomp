// Spore SporeApp.exe 0x0095c260..0x0095cff6 — tiled / 9-slice image blit family.
//
// 0x0095c260  FUN_0095c260  clip dst rect to clip rect, remap uv proportionally, blit
// 0x0095c420  FUN_0095c420  tile a uniform-uv image over dst (each tile via DrawClippedRect)
// 0x0095c5f0  FUN_0095c5f0  tile an image (caller uv rect) over dst via FUN_0095c260
// 0x0095c800  FUN_0095c800  single-row horizontal tiling via FUN_0095c260
// 0x0095c920  FUN_0095c920  single-column vertical tiling via FUN_0095c260
// 0x0095ca40  FUN_0095ca40  9-slice scaled blit (4 corners + 4 edges + center)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" {
__declspec(dllimport) double __cdecl ceil(double);
__declspec(dllimport) double __cdecl floor(double);
}

// The original routes floor() through a local jmp-through-IAT stub (?iat_floor@@YANN@Z).
double iat_floor(double x) { return floor(x); }

namespace EA {

struct RectF {
  RectF() {}
  RectF(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
  float mLeft, mTop, mRight, mBottom;
  bool Intersect(RectF const& a, RectF const& b);
};

// Only the vtable slot that matters is modelled; slot +0x58 = DrawImage.
struct IRenderer {
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
  virtual void DrawImage(RectF const* pDst, void* pObj, RectF const* pUV);  // +0x58
};

// A blittable source (font glyph / image handle): pixel extents at +0x1c / +0x20.
struct TileSource {
  char mPad[0x1c];
  int mWidth;   // +0x1c
  int mHeight;  // +0x20
};

}  // namespace EA

using EA::IRenderer;
using EA::RectF;
using EA::TileSource;

// 0x0095c0d0  ?DrawClippedRect@@YAXPAUIRenderer@@PBURectF@@11@Z
void DrawClippedRect(IRenderer* pRenderer, RectF const* pRect, void* pObj, RectF const* pDst);

void FUN_0095c260(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, void* pObj,
                  RectF const* pClip);
void FUN_0095c420(IRenderer* pRenderer, RectF const* pDst, TileSource* pObj, float sx, float sy,
                  float offx, float offy);
void FUN_0095c5f0(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sx, float sy, float offx, float offy);
void FUN_0095c800(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sx, float offx);
void FUN_0095c920(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sy, float offy);
void FUN_0095ca40(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float const* pSlices, float sx, float sy);

// @ 0x0095c260
void FUN_0095c260(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, void* pObj,
                  RectF const* pClip) {
  float left = pDst->mLeft;
  if (left >= pClip->mLeft && pDst->mRight <= pClip->mRight && pDst->mTop >= pClip->mTop &&
      pDst->mBottom <= pClip->mBottom) {
    pRenderer->DrawImage(pDst, pObj, pUV);
    return;
  }
  float w = pDst->mRight - left;
  float h = pDst->mBottom - pDst->mTop;
  if (1.0f > w || 1.0f > h) return;
  RectF inter(*pDst);
  inter.Intersect(*pDst, *pClip);
  if (inter.mLeft != inter.mRight && inter.mTop != inter.mBottom) {
    float invW = 1.0f / w;
    float invH = 1.0f / h;
    float uvW = pUV->mRight - pUV->mLeft;
    float uvH = pUV->mBottom - pUV->mTop;
    RectF u;
    u.mLeft = (inter.mLeft - left) * invW * uvW + pUV->mLeft;
    u.mRight = (inter.mRight - left) * invW * uvW + pUV->mLeft;
    u.mTop = (inter.mTop - pDst->mTop) * invH * uvH + pUV->mTop;
    u.mBottom = (inter.mBottom - pDst->mTop) * invH * uvH + pUV->mTop;
    pRenderer->DrawImage(&inter, pObj, &u);
  }
}

// @ 0x0095c420
void FUN_0095c420(IRenderer* pRenderer, RectF const* pDst, TileSource* pObj, float sx, float sy,
                  float offx, float offy) {
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
        RectF tile(x, y, nx, y + h);
        DrawClippedRect(pRenderer, &tile, pObj, pDst);
        x = nx;
      }
      y += h;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095c5f0
void FUN_0095c5f0(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sx, float sy, float offx, float offy) {
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
        RectF tile(x, y, nx, y + h);
        FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
        x = nx;
      }
      y += h;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095c800
void FUN_0095c800(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sx, float offx) {
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
      RectF tile(x, pDst->mTop, nx, pDst->mBottom);
      FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
      x = nx;
    } while (x < pDst->mRight);
  }
}

// @ 0x0095c920
void FUN_0095c920(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float sy, float offy) {
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
      RectF tile(pDst->mLeft, y, pDst->mRight, ny);
      FUN_0095c260(pRenderer, &tile, pUV, pObj, pDst);
      y = ny;
    } while (y < pDst->mBottom);
  }
}

// @ 0x0095ca40
void FUN_0095ca40(IRenderer* pRenderer, RectF const* pDst, RectF const* pUV, TileSource* pObj,
                  float const* pSlices, float sx, float sy) {
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

  RectF uvTL(pUV->mLeft, pUV->mTop, ul, ut);
  RectF dstTL(pDst->mLeft, pDst->mTop, left, top);
  pRenderer->DrawImage(&dstTL, pObj, &uvTL);

  RectF uvTR(ur, pUV->mTop, pUV->mRight, ut);
  RectF dstTR(right, pDst->mTop, pDst->mRight, top);
  pRenderer->DrawImage(&dstTR, pObj, &uvTR);

  RectF uvBL(pUV->mLeft, ub, ul, pUV->mBottom);
  RectF dstBL(pDst->mLeft, bottom, left, pDst->mBottom);
  pRenderer->DrawImage(&dstBL, pObj, &uvBL);

  RectF uvBR(ur, ub, pUV->mRight, pUV->mBottom);
  RectF dstBR(right, bottom, pDst->mRight, pDst->mBottom);
  pRenderer->DrawImage(&dstBR, pObj, &uvBR);

  if (left < right) {
    RectF dstTop(left, pDst->mTop, right, top);
    RectF uvTop(ul, pUV->mTop, ur, ut);
    FUN_0095c800(pRenderer, &dstTop, &uvTop, pObj, sx, 0.0f);
    RectF dstBot(left, bottom, right, pDst->mBottom);
    RectF uvBot(ul, ub, ur, pUV->mBottom);
    FUN_0095c800(pRenderer, &dstBot, &uvBot, pObj, sx, 0.0f);
  }
  if (top < bottom) {
    RectF dstLeft(pDst->mLeft, top, left, bottom);
    RectF uvLeft(pUV->mLeft, ut, ul, ub);
    FUN_0095c920(pRenderer, &dstLeft, &uvLeft, pObj, sy, 0.0f);
    RectF dstRight(right, top, pDst->mRight, bottom);
    RectF uvRight(ur, ut, pUV->mRight, ub);
    FUN_0095c920(pRenderer, &dstRight, &uvRight, pObj, sy, 0.0f);
  }
  if (left != right && top != bottom) {
    RectF dstMid(left, top, right, bottom);
    RectF uvMid(ul, ut, ur, ub);
    FUN_0095c5f0(pRenderer, &dstMid, &uvMid, pObj, sx, sy, 0.0f, 0.0f);
  }
}
