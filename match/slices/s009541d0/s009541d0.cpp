// EA::UTFWin::Draw2D::FillGradV (0x009541d0): vertical gradient fill (two colors, 4 verts,
// kPrimType3DQuadList), clamped against the clip rect.
// EA::UTFWin::Draw2D::FillTriGrad (0x009544f0): per-vertex-color triangle; when the triangle is not
// fully inside the clip rect it is clipped with ClipPolygon2D and emitted as a triangle-list fan.
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
  Point2D(float px, float py) : x(px), y(py) {}
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
  T& back() { return *(mpEnd - 1); }
  void pop_back() { --mpEnd; }
  bool empty() const { return mpBegin == mpEnd; }
  T& push_back() {
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else {
      T temp;
      DoInsertValue(mpEnd, temp);
    }
    return *(mpEnd - 1);
  }
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

  void BeginPart(int primType, Image* pImage);        // 0x009531a0
  __forceinline void AddVertexInline(const Point2D& p, uint32_t c) {
    Drawing::Vertex2D v;
    v.x = p.x; v.y = p.y; v.c = c; v.u = 0.0f; v.v = 0.0f;
    mVerts.push_back(v);
  }

  __forceinline void BeginPartInline(int primType, Image* pImage) {
    if (mParts.empty() || mParts.back().mPrimType != primType || mParts.back().mpImage != pImage) {
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

  __forceinline void AddVert(const Point2D& p, uint32_t c) { mpRenderable->AddVertexInline(p, c); }

  void FillGradV(const RectT<float>& rect, uint32_t color0, uint32_t color1);
  void FillTriGrad(const Point2D& p0, uint32_t color0, const Point2D& p1, uint32_t color1,
                   const Point2D& p2, uint32_t color2);
};

}  // namespace UTFWin
}  // namespace EA

namespace EA {
namespace UTFWin {


// @ 0x009541d0
void Draw2D::FillGradV(const RectT<float>& rect, uint32_t color0, uint32_t color1) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  float left = rect.mLeft;
  float top = rect.mTop;
  float right = rect.mRight;
  float bottom = rect.mBottom;

  if (mbClip) {
    if (mClipRect.mLeft > left) left = mClipRect.mLeft;
    if (mClipRect.mTop > top) top = mClipRect.mTop;
    if (right > mClipRect.mRight) right = mClipRect.mRight;
    if (bottom > mClipRect.mBottom) bottom = mClipRect.mBottom;
    if (left >= right) return;
    if (top >= bottom) return;
  }

  const uint32_t c0 = ModulateARGB32(mColor, color0);
  const uint32_t c1 = ModulateARGB32(mColor, color1);

  mpRenderable->BeginPartInline(2, 0);
  AddVert(Point2D(left, top), c0);
  AddVert(Point2D(right, top), c0);
  AddVert(Point2D(right, bottom), c1);
  AddVert(Point2D(left, bottom), c1);
  mpRenderable->EndPart(4);
}


// @ 0x009544f0
void Draw2D::FillTriGrad(const Point2D& p0, uint32_t color0, const Point2D& p1, uint32_t color1,
                         const Point2D& p2, uint32_t color2) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  if (mbClip && !(mClipRect.Contains(p0) && mClipRect.Contains(p1) && mClipRect.Contains(p2))) {
    Drawing::Vertex2D in[3];
    in[0].x = p0.x; in[0].y = p0.y; in[0].c = ModulateARGB32(mColor, color0); in[0].u = 0.0f; in[0].v = 0.0f;
    in[1].x = p1.x; in[1].y = p1.y; in[1].c = ModulateARGB32(mColor, color1); in[1].u = 0.0f; in[1].v = 0.0f;
    in[2].x = p2.x; in[2].y = p2.y; in[2].c = ModulateARGB32(mColor, color2); in[2].u = 0.0f; in[2].v = 0.0f;

    Drawing::Vertex2D out[8];
    const uint32_t n = ClipPolygon2D(&mClipRect, in, 3, out, 8);
    if (n == 0) return;

    mpRenderable->BeginPart(1, 0);
    for (uint32_t i = 2; i < n; ++i) {
      mpRenderable->mVerts.push_back(out[0]);
      mpRenderable->mVerts.push_back(out[i - 1]);
      mpRenderable->mVerts.push_back(out[i]);
    }
    mpRenderable->EndPart(n * 3 - 6);
    return;
  }

  mpRenderable->BeginPartInline(1, 0);
  AddVert(p0, ModulateARGB32(mColor, color0));
  AddVert(p1, ModulateARGB32(mColor, color1));
  AddVert(p2, ModulateARGB32(mColor, color2));
  mpRenderable->EndPart(3);
}

}  // namespace UTFWin
}  // namespace EA
