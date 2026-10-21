// EA::UTFWin::Draw2D text-glyph / quad-helper closure (retail 0x009559a0..0x009568b3).
//
// 0x009559a0  Draw2D::DrawTextGlyphs(EA::Text::GlyphDisplayEntry const*, unsigned, EA::Text::TextStyle const*) (PDB)
// 0x00955e20  Draw2D::DrawTextGlyphs(unsigned short const*, EA::Text::GlyphLayoutInfo const*, unsigned)         (PDB)
// 0x00956310  FUN_00956310  affine-transform 3 vertices (u/v) + clip + emit one 3-vertex part
// 0x00956500  FUN_00956500  same for 4 vertices
// 0x00956730  FUN_00956730  scaled-image blit (uv = 0..1)
// 0x009567c0  FUN_009567c0  image blit (uv rect supplied)
// 0x00956830  FUN_00956830  image blit (src + dst rects supplied)
// 0x00956870  FUN_00956870  append a CellData pointer to the global cell list
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#define _CRTIMP
#include "types.h"
#include <math.h>
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

namespace Text {

// Stub vtables: only the slot indices matter for the reconstructed call sites.
struct IVt10 {  // 10 slots; GlyphDisplayEntry::mpObject
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual unsigned int v9();  // +0x24
};
struct IVt4 {  // 4 slots; slot 3 = glyph-texture accessor taking a 4-byte id
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* v3(int id);  // +0xc
};

struct GlyphAttributes {    // 0x28
  IVt10* mpObject;          // +0x0
  float mfPenX;             // +0x4
  float mfPenY;             // +0x8
  float mfX1;               // +0xc
  float mfY1;               // +0x10
  float mfX2;               // +0x14
  float mfY2;               // +0x18
  float mfAdvanceX;         // +0x1c
  float mfAdvanceY;         // +0x20
  unsigned short mGlyphId;  // +0x24
  unsigned short mPad;      // +0x26
};
struct GlyphDisplayEntry : GlyphAttributes {};  // 0x28

struct GlyphLayoutInfo {  // 0x20
  IVt10* mpFont;          // +0x0
  float mfPenX;           // +0x4
  float mfPenY;           // +0x8
  float mfAdvance;        // +0xc
  float mfX1;             // +0x10
  float mfY1;             // +0x14
  float mfX2;             // +0x18
  float mfY2;             // +0x1c
};

struct TextStyle {      // 0x228
  char mPad[0x224];     // +0x0
  unsigned int mColor;  // +0x224
};

// The object returned by IVt4::v3(); its u/v affine coefficients live at +0xc..+0x18.
struct FontMetrics {
  char mPad[0xc];
  float mfTx;  // +0xc
  float mfTy;  // +0x10
  float mfSx;  // +0x14
  float mfSy;  // +0x18
};

}  // namespace Text

namespace UTFWin {

struct Point2D {
  float x, y;
};

class Image { public:
  virtual void AddRef();
  virtual void Release();
};

// The retail Renderable2DPart: { Image* mpImage; int mPrimType; uint32_t mCount; }
struct Renderable2DPart {
  Image* mpImage;
  int mPrimType;
  uint32_t mCount;
};

struct Renderable2DTextGlyphInfo {  // 0xc
  unsigned short mGlyphId;         // +0x0
  float mU;                        // +0x4
  float mV;                        // +0x8
};

struct Renderable2DTextSpan {  // 0x14
  void* mpFont;                // +0x0
  uint32_t mVertStart;         // +0x4
  uint32_t mGlyphStart;        // +0x8
  uint32_t mGlyphCount;        // +0xc
  uint32_t mCacheGen;          // +0x10
};

namespace eastl {
struct bidirectional_iterator_tag {};
}  // namespace eastl

// eastl::vector<T> (retail fixed_vector) inline members; D names the instantiation so each
// out-of-line DoInsertValue / resize gets its own declaration.
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
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& back() { return *(mpEnd - 1); }
  void pop_back() { --mpEnd; }
  bool empty() const { return mpBegin == mpEnd; }
};

struct Vertex2DVector : VectorT<Drawing::Vertex2D, Vertex2DVector> {
  void DoInsertValue(Drawing::Vertex2D* position, const Drawing::Vertex2D& value);  // 0x00884d90
  void DoInsertFromIterator(Drawing::Vertex2D* position, const Drawing::Vertex2D* first,
                            const Drawing::Vertex2D* last,
                            eastl::bidirectional_iterator_tag);  // 0x00952b30
  __forceinline void insert(Drawing::Vertex2D* position, const Drawing::Vertex2D* first,
                            const Drawing::Vertex2D* last) {
    DoInsertFromIterator(position, first, last, eastl::bidirectional_iterator_tag());
  }
};
struct PartVector : VectorT<Renderable2DPart, PartVector> {
  void DoInsertValue(Renderable2DPart* position, const Renderable2DPart& value);  // 0x00a27910
};
struct TextSpanVector : VectorT<Renderable2DTextSpan, TextSpanVector> {
  void DoInsertValue(Renderable2DTextSpan* position, const Renderable2DTextSpan& value);  // 0x00884d90
};
struct GlyphInfoVector : VectorT<Renderable2DTextGlyphInfo, GlyphInfoVector> {
  void DoInsertValue(Renderable2DTextGlyphInfo* position, const Renderable2DTextGlyphInfo& value);
  void resize(unsigned int n);  // 0x009557e0
};

class Renderable2DBuilder { public:
  Vertex2DVector mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)
  uint32_t pad1[(0x2fd0 - 0x2f04) / 4];
  TextSpanVector mTextSpans;  // +0x2fd0 (fixed_vector<Renderable2DTextSpan,30>)
  uint32_t pad2[(0x3240 - 0x2fdc) / 4];
  GlyphInfoVector mGlyphInfos;  // +0x3240 (fixed_vector<Renderable2DTextGlyphInfo,200>)

  void BeginPart(int primType, Image* pImage);  // 0x009531a0

  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};

uint32_t ModulateARGB32(uint32_t a, uint32_t b);  // 0x0095f8c0

extern Image gFontCacheImage;  // 0x0166aacc

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

  __forceinline bool ClipContains(const Point2D& p) const { return mClipRect.Contains(p); }
  __forceinline bool ClipContains(const Drawing::Vertex2D& v) const {
    return mClipRect.mLeft <= v.x && mClipRect.mTop <= v.y && v.x < mClipRect.mRight &&
           v.y < mClipRect.mBottom;
  }

  void DrawTextGlyphs(const Text::GlyphDisplayEntry* pEntries, unsigned int count,
                      const Text::TextStyle* pStyle);  // 0x009559a0
  void DrawTextGlyphs(const unsigned short* pGlyphIds, const Text::GlyphLayoutInfo* pInfos,
                      unsigned int count);  // 0x00955e20

  void FUN_00956310(const Drawing::Vertex2D* pSrc, unsigned int count, Text::IVt4* pObj);
  void FUN_00956500(const Drawing::Vertex2D* pSrc, unsigned int count, Text::IVt4* pObj);
  void FUN_00956730(float x, float y, Text::IVt4* pObj);
  void FUN_009567c0(float x, float y, Text::IVt4* pObj, const RectT<float>* pUV);
  void FUN_00956830(const RectT<float>* pDst, Text::IVt4* pObj, const RectT<float>* pUV);

  void RectBlit(const RectT<float>* pDst, const RectT<float>* pUV, void* pObj);  // 0x009553e0
};

}  // namespace UTFWin

namespace SP {

struct CellData {
  void FUN_009558c0();  // 0x009558c0
};

struct SimpleVectorCell {
  CellData** mpBegin;     // +0x0
  CellData** mpEnd;       // +0x4
  CellData** mpCapacity;  // +0x8
  int mPad0;              // +0xc
  int mPad1;              // +0x10
  int mCount;             // +0x14
  void DoInsertValue(CellData** position, CellData* const& value);  // 0x00a80dd0
  void push_back(CellData* p) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) CellData*(p);
    else
      DoInsertValue(mpEnd, p);
  }
};

extern SimpleVectorCell* gCellList;  // 0x0166aac0

}  // namespace SP
}  // namespace EA

namespace EA {
namespace UTFWin {

// @ 0x009559a0
void Draw2D::DrawTextGlyphs(const Text::GlyphDisplayEntry* pEntries, unsigned int count,
                            const Text::TextStyle* pStyle) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;
  if (count == 0) return;

  mpRenderable->BeginPart(2, &gFontCacheImage);

  unsigned int color;
  if (pEntries->mpObject->v9() == 0x20)
    color = 0xffffffff;
  else
    color = ModulateARGB32(mColor, pStyle->mColor);

  const unsigned int glyphBase = mpRenderable->mGlyphInfos.size();
  mpRenderable->mGlyphInfos.resize(glyphBase + count);

  Renderable2DTextGlyphInfo* pGlyph = mpRenderable->mGlyphInfos.mpBegin + glyphBase;

  Renderable2DTextSpan span;
  span.mpFont = pEntries->mpObject;
  span.mVertStart = (unsigned int)(mpRenderable->mVerts.mpEnd - mpRenderable->mVerts.mpBegin);
  span.mGlyphStart = glyphBase;
  span.mGlyphCount = count;
  span.mCacheGen = 0;
  pEntries->mpObject->v2();
  mpRenderable->mTextSpans.push_back(span);

  const Text::GlyphDisplayEntry* pEnd = pEntries + count;
  for (const Text::GlyphDisplayEntry* p = pEntries; p < pEnd; ++p) {
    pGlyph->mGlyphId = p->mGlyphId;
    pGlyph->mU = 0.0f;
    pGlyph->mV = 0.0f;

    float fLeft = (float)floor(p->mfX1);
    float fTop = (float)floor(p->mfY1);
    float fRight = (float)floor(p->mfX2);
    float fBottom = (float)floor(p->mfY2);

    if (mbClip) {
      float d = mClipRect.mLeft - fLeft;
      if (0.0f < d) {
        pGlyph->mU = d;
        fLeft = mClipRect.mLeft;
      }
      d = mClipRect.mTop - fTop;
      if (0.0f < d) {
        pGlyph->mV = d;
        fTop = mClipRect.mTop;
      }
      if (mClipRect.mRight < fRight) fRight = mClipRect.mRight;
      if (mClipRect.mBottom < fBottom) fBottom = mClipRect.mBottom;
      if (fRight < fLeft || fBottom < fTop) {
        fRight = fLeft;
        fBottom = fTop;
      }
    }

    Drawing::Vertex2D v;
    v.x = fLeft;
    v.y = fTop;
    v.c = color;
    v.u = 0.0f;
    v.v = 0.0f;
    mpRenderable->mVerts.push_back(v);

    v.x = fRight;
    v.y = fTop;
    v.u = 1.0f;
    v.v = 0.0f;
    mpRenderable->mVerts.push_back(v);

    v.x = fRight;
    v.y = fBottom;
    v.u = 1.0f;
    v.v = 1.0f;
    mpRenderable->mVerts.push_back(v);

    v.x = fLeft;
    v.y = fBottom;
    v.u = 0.0f;
    v.v = 1.0f;
    mpRenderable->mVerts.push_back(v);

    ++pGlyph;
  }

  mpRenderable->EndPart(count * 4);
}

// @ 0x00955e20
void Draw2D::DrawTextGlyphs(const unsigned short* pGlyphIds, const Text::GlyphLayoutInfo* pInfos,
                            unsigned int count) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  const Text::GlyphLayoutInfo* pEnd = pInfos + count;
  for (const Text::GlyphLayoutInfo* pRun = pInfos;;) {
    unsigned int run = 0;
    if (pRun < pEnd) {
      const Text::GlyphLayoutInfo* q = pRun;
      do {
        if (pRun->mpFont != q->mpFont) break;
        ++q;
        ++run;
      } while (q != pEnd);
    }
    if (run == 0) return;

    mpRenderable->BeginPart(2, &gFontCacheImage);

    const unsigned int runColor = mColor;
    const unsigned int glyphBase = mpRenderable->mGlyphInfos.size();
    mpRenderable->mGlyphInfos.resize(glyphBase + run);

    Renderable2DTextGlyphInfo* pGlyph = mpRenderable->mGlyphInfos.mpBegin + glyphBase;

    Renderable2DTextSpan span;
    span.mpFont = pRun->mpFont;
    span.mVertStart = (unsigned int)(mpRenderable->mVerts.mpEnd - mpRenderable->mVerts.mpBegin);
    span.mGlyphStart = glyphBase;
    span.mGlyphCount = run;
    span.mCacheGen = 0;
    pRun->mpFont->v2();
    mpRenderable->mTextSpans.push_back(span);

    const Text::GlyphLayoutInfo* q = pRun + run;
    const unsigned short* pId = pGlyphIds;
    for (const Text::GlyphLayoutInfo* p = pRun; p < q; ++p, ++pId) {
      pGlyph->mGlyphId = *pId;
      pGlyph->mU = 0.0f;
      pGlyph->mV = 0.0f;

      float fLeft = (float)floor(p->mfX1);
      float fTop = (float)floor(p->mfY1);
      float fRight = (float)floor(p->mfX2);
      float fBottom = (float)floor(p->mfY2);

      if (mbClip) {
        float d = mClipRect.mLeft - fLeft;
        if (0.0f < d) {
          pGlyph->mU = d;
          fLeft = mClipRect.mLeft;
        }
        d = mClipRect.mTop - fTop;
        if (0.0f < d) {
          pGlyph->mV = d;
          fTop = mClipRect.mTop;
        }
        if (mClipRect.mRight < fRight) fRight = mClipRect.mRight;
        if (mClipRect.mBottom < fBottom) fBottom = mClipRect.mBottom;
        if (fRight < fLeft || fBottom < fTop) {
          fRight = fLeft;
          fBottom = fTop;
        }
      }

      Drawing::Vertex2D v;
      v.x = fLeft;
      v.y = fTop;
      v.c = runColor;
      v.u = 0.0f;
      v.v = 0.0f;
      mpRenderable->mVerts.push_back(v);

      v.x = fRight;
      v.y = fTop;
      v.u = 1.0f;
      v.v = 0.0f;
      mpRenderable->mVerts.push_back(v);

      v.x = fRight;
      v.y = fBottom;
      v.u = 1.0f;
      v.v = 1.0f;
      mpRenderable->mVerts.push_back(v);

      v.x = fLeft;
      v.y = fBottom;
      v.u = 0.0f;
      v.v = 1.0f;
      mpRenderable->mVerts.push_back(v);

      ++pGlyph;
    }

    mpRenderable->EndPart(run * 4);
    pRun = q;
  }
}

// @ 0x00956310
void Draw2D::FUN_00956310(const Drawing::Vertex2D* pSrc, unsigned int count, Text::IVt4* pObj) {
  if (!pObj) return;
  Text::FontMetrics* pFont = (Text::FontMetrics*)pObj->v3(0x1be6ab3);
  if (!pFont) return;
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;
  if (count == 0) return;

  const Drawing::Vertex2D* src = pSrc;
  for (unsigned int n = count; n != 0; --n) {
    Drawing::Vertex2D out[3];
    for (unsigned int i = 0; i < 3; ++i) {
      out[i].x = src[i].x;
      out[i].y = src[i].y;
      out[i].c = src[i].c;
      out[i].u = pFont->mfSx * src[i].u + pFont->mfTx;
      out[i].v = pFont->mfSy * src[i].v + pFont->mfTy;
    }

    bool bClip = false;
    if (mbClip) {
      for (unsigned int i = 0; i < 3; ++i)
        if (!ClipContains(out[i])) {
          bClip = true;
          break;
        }
    }
    if (!bClip) {
      mpRenderable->BeginPart(1, (Image*)pFont);
      mpRenderable->mVerts.insert(mpRenderable->mVerts.mpEnd, out, out + 3);
      mpRenderable->EndPart(3);
    }
    ++src;
  }
}

// @ 0x00956500
void Draw2D::FUN_00956500(const Drawing::Vertex2D* pSrc, unsigned int count, Text::IVt4* pObj) {
  if (!pObj) return;
  Text::FontMetrics* pFont = (Text::FontMetrics*)pObj->v3(0x1be6ab3);
  if (!pFont) return;
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;
  if (count == 0) return;

  const Drawing::Vertex2D* src = pSrc;
  for (unsigned int n = count; n != 0; --n) {
    Drawing::Vertex2D out[4];
    for (unsigned int i = 0; i < 4; ++i) {
      out[i].x = src[i].x;
      out[i].y = src[i].y;
      out[i].c = src[i].c;
      out[i].u = pFont->mfSx * src[i].u + pFont->mfTx;
      out[i].v = pFont->mfSy * src[i].v + pFont->mfTy;
    }

    bool bClip = false;
    if (mbClip) {
      for (unsigned int i = 0; i < 4; ++i)
        if (!ClipContains(out[i])) {
          bClip = true;
          break;
        }
    }
    if (!bClip) {
      mpRenderable->BeginPart(2, (Image*)pFont);
      mpRenderable->mVerts.insert(mpRenderable->mVerts.mpEnd, out, out + 4);
      mpRenderable->EndPart(4);
    }
    ++src;
  }
}

// @ 0x00956730
void Draw2D::FUN_00956730(float x, float y, Text::IVt4* pObj) {
  if (!pObj) return;
  Text::FontMetrics* pFont = (Text::FontMetrics*)pObj->v3(0x1be6ab3);
  if (!pFont) return;
  const float w = (float)*(int*)((char*)pFont + 0x1c);
  const float h = (float)*(int*)((char*)pFont + 0x20);
  RectT<float> uv = {0.0f, 0.0f, 1.0f, 1.0f};
  RectT<float> rect = {x, y, x + w, y + h};
  RectBlit(&rect, &uv, pFont);
}

// @ 0x009567c0
void Draw2D::FUN_009567c0(float x, float y, Text::IVt4* pObj, const RectT<float>* pUV) {
  if (!pObj) return;
  Text::FontMetrics* pFont = (Text::FontMetrics*)pObj->v3(0x1be6ab3);
  if (!pFont) return;
  const float w = (float)*(int*)((char*)pFont + 0x1c);
  const float h = (float)*(int*)((char*)pFont + 0x20);
  RectT<float> rect;
  rect.mLeft = x;
  rect.mTop = y;
  rect.mRight = x + w;
  rect.mBottom = y + h;
  RectBlit(&rect, pUV, pFont);
}

// @ 0x00956830
void Draw2D::FUN_00956830(const RectT<float>* pDst, Text::IVt4* pObj, const RectT<float>* pUV) {
  if (!pObj) return;
  Text::FontMetrics* pFont = (Text::FontMetrics*)pObj->v3(0x1be6ab3);
  if (!pFont) return;
  RectBlit(pDst, pUV, pFont);
}

}  // namespace UTFWin
}  // namespace EA

// @ 0x00956870
void FUN_00956870(EA::SP::CellData* p) {
  EA::SP::SimpleVectorCell* pList = EA::SP::gCellList;
  p->FUN_009558c0();
  pList->push_back(p);
  --pList->mCount;
}
