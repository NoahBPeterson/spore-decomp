// EA::UTFWin::Draw2D::FillQuadGrad (0x00954a00): fill a quad with per-vertex colors, clipping each of
// its two triangles (p0,p1,p3) and (p3,p1,p2) against the clip rect when they are not fully inside.
// The name is inferred: it follows Draw2D::FillGradH/FillGradV/FillTriGrad (dev PDB) in the binary.
#include "types.h"
#include <new>

namespace EA {

template <typename T>
class RectT { public:
  T mLeft, mTop, mRight, mBottom;
  template <typename P>
  __forceinline bool Contains(const P& p) const {
    return p.x >= mLeft && p.y >= mTop && p.x < mRight && p.y < mBottom;
  }
};

namespace Drawing {
struct Vertex2D {
  float x, y;
  uint32_t c;
  float u, v;
};
}  // namespace Drawing

namespace UTFWin {

struct Point2D {
  float x, y;
};

class Image { public:
  virtual void AddRef();
  virtual void Release();
};

namespace Text {
// The glyph-atlas image handed to Draw2D::RectBlit; its u/v affine coefficients live at +0xc..0x18.
struct FontMetrics : Image {
  char mPad0[8];  // +0x4
  float mfTx;     // +0xc
  float mfTy;     // +0x10
  float mfSx;     // +0x14
  float mfSy;     // +0x18
};
}  // namespace Text

struct IRenderable;

// The retail Renderable2DPart: { Image* mpImage; PrimitiveType3D mPrimType; uint32_t mCount; }
struct Renderable2DPart {
  Image* mpImage;
  int mPrimType;
  uint32_t mCount;
};

// eastl::vector<T> (retail fixed_vector) inline members; D names the instantiation so each
// out-of-line DoInsertValue gets its own declaration.
template <typename T, typename D>
struct VectorT {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;

  void DoInsertValue(T* position, const T& value) { static_cast<D*>(this)->DoInsertValue(position, value); }
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
  T& push_back() {
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else {
      T temp;
      DoInsertValue(mpEnd, temp);
    }
    return *(mpEnd - 1);
  }
  T& back() { return *(mpEnd - 1); }
  void pop_back() { --mpEnd; }
  bool empty() const { return mpBegin == mpEnd; }
};


struct Vertex2DVector : VectorT<Drawing::Vertex2D, Vertex2DVector> {
  void DoInsertValue(Drawing::Vertex2D* position, const Drawing::Vertex2D& value);  // 0x00884d90
};
struct PartVector : VectorT<Renderable2DPart, PartVector> {
  void DoInsertValue(Renderable2DPart* position, const Renderable2DPart& value);  // 0x00a27910
};

class Renderable2DBuilder { public:
  Vertex2DVector mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)

  void AddVertex(const Drawing::Vertex2D& v);         // 0x00952ee0
  IRenderable* Flush();                               // 0x00953220
  __forceinline void AddVertexInline(const Point2D& p, uint32_t c) {
    Drawing::Vertex2D v;
    v.x = p.x; v.y = p.y; v.c = c; v.u = 0.0f; v.v = 0.0f;
    mVerts.push_back(v);
  }
  void BeginPart(int primType, Image* pImage);        // 0x009531a0

  __forceinline void BeginPartInline(int primType, Image* pImage) {
    if (mParts.empty() || mParts.back().mPrimType != primType || mParts.back().mpImage != pImage) {
      if (pImage) pImage->AddRef();
      mParts.push_back();
      Renderable2DPart& part = mParts.back();
      part.mpImage = pImage;
      part.mPrimType = primType;
      part.mCount = 0;
    }
  }
  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};

uint32_t ModulateARGB32(uint32_t a, uint32_t b);  // 0x0095f8c0
// 0x00917e10: clip a polygon against a rect; returns the output vertex count.
uint32_t ClipPolygon2D(const RectT<float>* pRect, const Drawing::Vertex2D* pIn, uint32_t nIn,
                       Drawing::Vertex2D* pOut, uint32_t nOutMax);

struct IDrawContext {
  virtual void Dummy0();
};

class Draw2D : public IDrawContext {
 public:
  Renderable2DBuilder* mpRenderable;  // +0x4
  void* mpWindowMgr;                  // +0x8
  uint32_t mColor;                    // +0xc
  bool mbClip;                        // +0x10
  RectT<float> mClipRect;             // +0x14
  Renderable2DBuilder mDefaultRenderable;  // +0x24

  __forceinline bool ClipContains(const Point2D& p) const {
    return mClipRect.Contains(p);
  }
  static __forceinline void SetVert(Drawing::Vertex2D& v, const Point2D& p, uint32_t c) {
    v.x = p.x;
    v.y = p.y;
    v.c = c;
    v.u = 0.0f;
    v.v = 0.0f;
  }
  __forceinline void AddVert(const Point2D& p, uint32_t c) { mpRenderable->AddVertexInline(p, c); }
  __forceinline void AddClippedTri(const Drawing::Vertex2D* verts, Drawing::Vertex2D* clipped) {
    const uint32_t n = ClipPolygon2D(&mClipRect, verts, 3, clipped, 8);
    if (n) {
      mpRenderable->BeginPart(1, 0);
      for (uint32_t i = 2; i < n; ++i) {
        mpRenderable->mVerts.push_back(clipped[0]);
        mpRenderable->mVerts.push_back(clipped[i - 1]);
        mpRenderable->mVerts.push_back(clipped[i]);
      }
      mpRenderable->EndPart(n * 3 - 6);
    }
  }

  void FillQuadGrad(const Point2D& p0, uint32_t color0, const Point2D& p1, uint32_t color1,
                    const Point2D& p2, uint32_t color2, const Point2D& p3, uint32_t color3);
  void RectBlit(const RectT<float>* pDst, const RectT<float>* pUV, Text::FontMetrics* pFont);
  IRenderable* Flush();
};

}  // namespace UTFWin
}  // namespace EA

namespace EA {
namespace SP {

// A renderable part / text span owned by a SP::CellData scratch renderable.
struct CellPart {              // 0xc, same shape as UTFWin::Renderable2DPart
  UTFWin::Image* mpImage;      // +0x0
  int mPrimType;               // +0x4
  uint32_t mCount;             // +0x8
};

struct IRefCounted {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void Release();      // +0xc
};

struct CellSpan {              // 0x14
  IRefCounted* mpFont;         // +0x0
  char mPad0[0x10];
};

struct CellData;

// SimpleVector<CellData*> (retail): 3 pointers + counters, value list lives in the pool.
struct SimpleVectorCell {
  CellData** mpBegin;    // +0x0
  CellData** mpEnd;      // +0x4
  CellData** mpCapacity; // +0x8
  int mPad0;             // +0xc
  int mPad1;             // +0x10
  int mCount;            // +0x14

  void DoInsertValue(CellData** position, CellData* const& value);  // 0x00a80dd0
  void push_back(CellData* p) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) CellData*(p);
    else
      DoInsertValue(mpEnd, p);
  }
};

// The cell allocator whose two arenas and free lists feed the recycling path.
struct CellPool {              // gCellPool @ 0x0166aac4
  char mPad0[0x30];
  void* mRange1Begin;          // +0x30
  void* mRange1End;            // +0x34
  void* mRange2Begin;          // +0x38
  void* mRange2End;            // +0x3c
  SimpleVectorCell mFree1;     // +0x40
  SimpleVectorCell mFree2;     // +0x54
};

extern CellPool* gCellPool;    // 0x0166aac4

struct CellReleaser {
  void Release(CellData* p);   // 0x009276c0
};
extern CellReleaser* gCellReleaser;  // 0x016c8b44

struct CellData {
  void* mpVtbl;                 // +0x0
  CellPart* mPartsBegin;        // +0x4
  CellPart* mPartsEnd;          // +0x8
  CellPart* mPartsCapacity;     // +0xc
  uint32_t mPartsCount;         // +0x10
  CellSpan* mSpansBegin;        // +0x14
  CellSpan* mSpansEnd;          // +0x18
  CellSpan* mSpansCapacity;     // +0x1c
  uint32_t mSpansCount;         // +0x20
  CellData* mpCell;             // +0x24

  void FUN_009558c0();
};

}  // namespace SP
}  // namespace EA

namespace EA {
namespace UTFWin {


// @ 0x00954a00
void Draw2D::FillQuadGrad(const Point2D& p0, uint32_t color0, const Point2D& p1, uint32_t color1,
                          const Point2D& p2, uint32_t color2, const Point2D& p3, uint32_t color3) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  const uint32_t c0 = ModulateARGB32(mColor, color0);
  color1 = ModulateARGB32(mColor, color1);
  color2 = ModulateARGB32(mColor, color2);
  color3 = ModulateARGB32(mColor, color3);

  if (mbClip) {
    const bool bIn1 = ClipContains(p1);
    const bool bIn3 = ClipContains(p3);
    const bool bClip0 = !(bIn1 && bIn3 && ClipContains(p0));
    const bool bClip2 = !(bIn1 && bIn3 && ClipContains(p2));

    if (bClip0 || bClip2) {
      if (bClip0) {
        Drawing::Vertex2D verts[3];
        Drawing::Vertex2D clipped[8];
        SetVert(verts[0], p0, c0);
        SetVert(verts[1], p1, color1);
        SetVert(verts[2], p3, color3);
        AddClippedTri(verts, clipped);
      } else {
        mpRenderable->BeginPart(1, 0);
        Drawing::Vertex2D v;
        SetVert(v, p0, c0);     mpRenderable->AddVertex(v);
        SetVert(v, p1, color1); mpRenderable->AddVertex(v);
        SetVert(v, p3, color3); mpRenderable->AddVertex(v);
        mpRenderable->EndPart(3);
      }

      if (bClip2) {
        Drawing::Vertex2D verts[3];
        Drawing::Vertex2D clipped[8];
        SetVert(verts[0], p3, color3);
        SetVert(verts[1], p1, color1);
        SetVert(verts[2], p2, color2);
        AddClippedTri(verts, clipped);
      } else {
        mpRenderable->BeginPart(1, 0);
        AddVert(p3, color3);
        AddVert(p1, color1);
        AddVert(p2, color2);
        mpRenderable->EndPart(3);
      }
      return;
    }
  }

  mpRenderable->BeginPartInline(2, 0);
  AddVert(p0, c0);
  AddVert(p1, color1);
  AddVert(p2, color2);
  AddVert(p3, color3);
  mpRenderable->EndPart(4);
}

// @ 0x009553e0
void Draw2D::RectBlit(const RectT<float>* pDst, const RectT<float>* pUV, Text::FontMetrics* pFont) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  float left = pDst->mLeft;
  float top = pDst->mTop;
  float right = pDst->mRight;
  float bottom = pDst->mBottom;

  // Map the source rect through the font image's u/v affine transform.
  float u0 = pUV->mLeft * pFont->mfSx + pFont->mfTx;
  float v0 = pUV->mTop * pFont->mfSy + pFont->mfTy;
  float u1 = pUV->mRight * pFont->mfSx + pFont->mfTx;
  float v1 = pUV->mBottom * pFont->mfSy + pFont->mfTy;

  if (mbClip) {
    const float w = right - left;
    const float h = bottom - top;
    if (w <= 0.0f || h <= 0.0f) return;

    const float du = (u1 - u0) / w;
    const float dv = (v1 - v0) / h;

    if (mClipRect.mLeft > left) {
      u0 += (mClipRect.mLeft - left) * du;
      left = mClipRect.mLeft;
    }
    if (mClipRect.mTop > top) {
      v0 += (mClipRect.mTop - top) * dv;
      top = mClipRect.mTop;
    }
    if (right > mClipRect.mRight) {
      u1 += (mClipRect.mRight - right) * du;
      right = mClipRect.mRight;
    }
    if (bottom > mClipRect.mBottom) {
      v1 += (mClipRect.mBottom - bottom) * dv;
      bottom = mClipRect.mBottom;
    }

    if (left >= right) return;
    if (top >= bottom) return;
  }

  mpRenderable->BeginPart(2, pFont);

  Drawing::Vertex2D v;
  v.x = left;  v.y = top;    v.c = mColor; v.u = u0; v.v = v0;
  mpRenderable->mVerts.push_back(v);
  v.x = right; v.y = top;    v.c = mColor; v.u = u1; v.v = v0;
  mpRenderable->mVerts.push_back(v);
  v.x = right; v.y = bottom; v.c = mColor; v.u = u1; v.v = v1;
  mpRenderable->mVerts.push_back(v);
  v.x = left;  v.y = bottom; v.c = mColor; v.u = u0; v.v = v1;
  mpRenderable->mVerts.push_back(v);

  mpRenderable->EndPart(4);
}

// @ 0x009557c0
IRenderable* Draw2D::Flush() {
  if (!mpRenderable) return 0;
  IRenderable* p = mpRenderable->Flush();
  mpRenderable = 0;
  return p;
}

}  // namespace UTFWin
}  // namespace EA

namespace EA {
namespace SP {

// @ 0x009558c0
void CellData::FUN_009558c0() {
  CellSpan* s = mSpansBegin;
  CellSpan* sEnd = mSpansEnd;
  for (; s != sEnd; ++s) {
    if (s->mpFont) s->mpFont->Release();
  }

  CellPart* p = mPartsBegin;
  CellPart* pEnd = mPartsEnd;
  for (; p != pEnd; ++p) {
    if (p->mpImage) p->mpImage->Release();
  }

  CellData* c = mpCell;
  if (c) {
    CellPool* pool = gCellPool;
    if (c >= (CellData*)pool->mRange1Begin && c < (CellData*)pool->mRange1End)
      pool->mFree1.push_back(c);
    else if (c >= (CellData*)pool->mRange2Begin && c < (CellData*)pool->mRange2End)
      pool->mFree2.push_back(c);
    else
      gCellReleaser->Release(c);

    mpCell = 0;
    mPartsCount = 0;
    mPartsCapacity = 0;
    mPartsEnd = 0;
    mPartsBegin = 0;
    mSpansEnd = 0;
    mSpansBegin = 0;
    mSpansCount = 0;
    mSpansCapacity = 0;
  }
}

}  // namespace SP
}  // namespace EA
