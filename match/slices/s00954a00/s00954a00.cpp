// EA::UTFWin::Draw2D::FillQuadGrad (0x00954a00): fill a quad with per-vertex colors, clipping each of
// its two triangles (p0,p1,p3) and (p3,p1,p2) against the clip rect when they are not fully inside.
// The name is inferred: it follows Draw2D::FillGradH/FillGradV/FillTriGrad (dev PDB) in the binary.
#include "types.h"
#include <new>

namespace EA {

template <typename T>
struct RectT {
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

struct Image {
  virtual void AddRef();
  virtual void Release();
};

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

struct Renderable2DBuilder {
  Vertex2DVector mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)

  void AddVertex(const Drawing::Vertex2D& v);         // 0x00952ee0
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
};

}  // namespace UTFWin
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

}  // namespace UTFWin
}  // namespace EA
