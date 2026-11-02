// src/game/UTFSpore_Win32/Draw2D.cpp -- migrated from slice(s) s00fb2ac0, s009559a0, s009541d0, s00953430, s00952390, s009568c0, s00954a00, s009515e0, s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Draw2D.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/MultiHeapObject.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_009289f0(unsigned, int, int, int, int, int);   // cSPMemPool::LockedAlloc
#include <intrin.h>
#include <string.h>
#include <new>
#include "EA/Thread/Mutex.h"
#include "EA/UTFWin/Draw2D.h"
#include "EA/UTFWin/Renderable2DPart.h"
#include "EA/UTFWin/Renderable2DTextGlyphInfo.h"
#include "EA/UTFWin/Renderable2DTextSpan.h"
#include <math.h>

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009289f0(unsigned, int, int, int, int, int);   // cSPMemPool::LockedAlloc
void* __fastcall LockedAllocCall(void* self, int reserved, unsigned size,
                                 int, int, int, int, int);  // 0x009289f0
extern void* g_pMemPool16c8b44;  // 0x016c8b44
struct MemPool {
    char pad0[0x40];
    int  free0;     // +0x40
    int  cur0;      // +0x44
    char pad1[0xc];
    int  free1;     // +0x54
    int  cur1;      // +0x58

    void* Alloc(unsigned size);
};
struct IterCopy {
    int f0, f1, f2, f3, f4, f5, f6, f7;
    IterCopy* Set(int* src);
};
struct Bounds {
    char pad0[0x10];
    char  mValid;       // +0x10
    char pad1[3];
    float mMinX;        // +0x14
    float mMinY;        // +0x18
    float mMaxX;        // +0x1c
    float mMaxY;        // +0x20

    char GetBounds(float* out);
    void SetBounds(char valid, const float* r);
    const float* UnionBounds(const float* r);
};
// ---- items of slice s00950bb0 end

// ---- items of slice s009515e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <typename T>
class generic_iterator { public:
  T* mIterator;
  explicit generic_iterator(T* x) : mIterator(x) {}
  generic_iterator& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};
}
namespace eastl {
template <typename T>
inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b) { return a.mIterator != b.mIterator; }
}
struct Rec40 { int a[10]; };
// ---- items of slice s009515e0 end

// ---- items of slice s00954a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RectT_s0095_4a00 { public:
  T mLeft, mTop, mRight, mBottom;
  template <typename P>
  __forceinline bool Contains(const P& p) const {
    return p.x >= mLeft && p.y >= mTop && p.x < mRight && p.y < mBottom;
  }
};
}
namespace EA {
namespace Drawing {
struct Vertex2D_s0095_4a00 {
  float x, y;
  uint32_t c;
  float u, v;
};  // namespace Drawing
}
}
namespace EA {
namespace UTFWin {
struct Point2D {
  float x, y;
};
}
}
namespace EA {
namespace UTFWin {
class Image_s0095_4a00 { public:
  virtual void AddRef();
  virtual void Release();  // 0x00957550 (EA::UTFWin::Image::Release)
};
}
}
namespace EA {
namespace UTFWin {
namespace Text {
struct FontMetrics : Image_s0095_4a00 {
  char mPad0[8];  // +0x4
  float mfTx;     // +0xc
  float mfTy;     // +0x10
  float mfSx;     // +0x14
  float mfSy;     // +0x18
};  // namespace Text
}
}
}
namespace EA {
namespace UTFWin {
struct IRenderable_s0095_4a00;
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DPart_s0095_4a00 {
  Image_s0095_4a00* mpImage;
  int mPrimType;
  uint32_t mCount;
};
}
}
namespace EA {
namespace UTFWin {
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
}
}
namespace EA {
namespace UTFWin {
struct Vertex2DVector : VectorT<Drawing::Vertex2D_s0095_4a00, Vertex2DVector> {
  void DoInsertValue(Drawing::Vertex2D_s0095_4a00* position, const Drawing::Vertex2D_s0095_4a00& value);  // 0x00884d90
};
}
}
namespace EA {
namespace UTFWin {
struct PartVector : VectorT<Renderable2DPart_s0095_4a00, PartVector> {
  void DoInsertValue(Renderable2DPart_s0095_4a00* position, const Renderable2DPart_s0095_4a00& value);  // 0x00a27910
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2DBuilder_s0095_4a00 { public:
  Vertex2DVector mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)

  void AddVertex(const Drawing::Vertex2D_s0095_4a00& v);         // 0x00952ee0
  IRenderable_s0095_4a00* Flush();                               // 0x00953220
  __forceinline void AddVertexInline(const Point2D& p, uint32_t c) {
    Drawing::Vertex2D_s0095_4a00 v;
    v.x = p.x; v.y = p.y; v.c = c; v.u = 0.0f; v.v = 0.0f;
    mVerts.push_back(v);
  }
  void BeginPart(int primType, Image_s0095_4a00* pImage);        // 0x009531a0

  __forceinline void BeginPartInline(int primType, Image_s0095_4a00* pImage) {
    if (mParts.empty() || mParts.back().mPrimType != primType || mParts.back().mpImage != pImage) {
      if (pImage) pImage->AddRef();
      mParts.push_back();
      Renderable2DPart_s0095_4a00& part = mParts.back();
      part.mpImage = pImage;
      part.mPrimType = primType;
      part.mCount = 0;
    }
  }
  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image_s0095_4a00* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};
}
}
namespace EA {
namespace UTFWin {
uint32_t ModulateARGB32(uint32_t a, uint32_t b);  // 0x0095f8c0
}
}
namespace EA {
namespace UTFWin {
uint32_t ClipPolygon2D(const RectT_s0095_4a00<float>* pRect, const Drawing::Vertex2D_s0095_4a00* pIn, uint32_t nIn,
                       Drawing::Vertex2D_s0095_4a00* pOut, uint32_t nOutMax);
}
}
namespace EA {
namespace UTFWin {
struct IDrawContext {
  virtual void Dummy0();
};
}
}
namespace EA {
namespace UTFWin {
class Draw2D_s0095_4a00 : public IDrawContext {
 public:
  Renderable2DBuilder_s0095_4a00* mpRenderable;  // +0x4
  void* mpWindowMgr;                  // +0x8
  uint32_t mColor;                    // +0xc
  bool mbClip;                        // +0x10
  RectT_s0095_4a00<float> mClipRect;             // +0x14
  Renderable2DBuilder_s0095_4a00 mDefaultRenderable;  // +0x24

  __forceinline bool ClipContains(const Point2D& p) const {
    return mClipRect.Contains(p);
  }
  static __forceinline void SetVert(Drawing::Vertex2D_s0095_4a00& v, const Point2D& p, uint32_t c) {
    v.x = p.x;
    v.y = p.y;
    v.c = c;
    v.u = 0.0f;
    v.v = 0.0f;
  }
  __forceinline void AddVert(const Point2D& p, uint32_t c) { mpRenderable->AddVertexInline(p, c); }
  __forceinline void AddClippedTri(const Drawing::Vertex2D_s0095_4a00* verts, Drawing::Vertex2D_s0095_4a00* clipped) {
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
  void RectBlit(const RectT_s0095_4a00<float>* pDst, const RectT_s0095_4a00<float>* pUV, Text::FontMetrics* pFont);
  IRenderable_s0095_4a00* Flush();
};
}
}
namespace EA {
namespace SP {
struct CellPart {              // 0xc, same shape as UTFWin::Renderable2DPart
  UTFWin::Image_s0095_4a00* mpImage;      // +0x0
  int mPrimType;               // +0x4
  uint32_t mCount;             // +0x8
};
}
}
namespace EA {
namespace SP {
struct IRefCounted {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void Release();      // +0xc
};
}
}
namespace EA {
namespace SP {
struct CellSpan {              // 0x14
  IRefCounted* mpFont;         // +0x0
  char mPad0[0x10];
};
}
}
namespace EA {
namespace SP {
struct CellData_s0095_4a00;
}
}
namespace EA {
namespace SP {
struct SimpleVectorCell {
  CellData_s0095_4a00** mpBegin;    // +0x0
  CellData_s0095_4a00** mpEnd;      // +0x4
  CellData_s0095_4a00** mpCapacity; // +0x8
  int mPad0;             // +0xc
  int mPad1;             // +0x10
  int mCount;            // +0x14

  void DoInsertValue(CellData_s0095_4a00** position, CellData_s0095_4a00* const& value);  // 0x00a80dd0
  void push_back(CellData_s0095_4a00* p) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) CellData_s0095_4a00*(p);
    else
      DoInsertValue(mpEnd, p);
  }
};
}
}
namespace EA {
namespace SP {
struct CellPool {              // gCellPool @ 0x0166aac4
  char mPad0[0x30];
  void* mRange1Begin;          // +0x30
  void* mRange1End;            // +0x34
  void* mRange2Begin;          // +0x38
  void* mRange2End;            // +0x3c
  SimpleVectorCell mFree1;     // +0x40
  SimpleVectorCell mFree2;     // +0x54
};
}
}
namespace EA {
namespace SP {
extern CellPool* gCellPool;    // 0x0166aac4
}
}
namespace EA {
namespace SP {
struct CellReleaser {
  void Release(CellData_s0095_4a00* p);   // 0x009276c0
};
}
}
namespace EA {
namespace SP {
extern CellReleaser* gCellReleaser;  // 0x016c8b44
}
}
namespace EA {
namespace SP {
struct CellData_s0095_4a00 {
  void* mpVtbl;                 // +0x0
  CellPart* mPartsBegin;        // +0x4
  CellPart* mPartsEnd;          // +0x8
  CellPart* mPartsCapacity;     // +0xc
  uint32_t mPartsCount;         // +0x10
  CellSpan* mSpansBegin;        // +0x14
  CellSpan* mSpansEnd;          // +0x18
  CellSpan* mSpansCapacity;     // +0x1c
  uint32_t mSpansCount;         // +0x20
  CellData_s0095_4a00* mpCell;             // +0x24

  void FUN_009558c0();
};
}
}
// ---- items of slice s00954a00 end

// ---- items of slice s009568c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern long g_refCount2D;            // 0x166aac8
extern int    g_154ecd4;             // 0x154ecd4
extern char   g_uiImage[0x40];       // 0x166aacc
extern char   g_154ecd0[];           // 0x154ecd0
extern char g_defaultTextStyle[];          // 0x166ae78
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);        // 0xf473a0 (EA allocator, name/flags form)
void  __cdecl operator delete(void*) throw();                                      // 0xf47380
void  __cdecl operator_delete__(void*) throw();                                    // 0xf47380
void __cdecl InitFontSystem();                            // 0x951c60
void __cdecl FUN_00956870(void*);
void __cdecl FUN_00952f30();
void __cdecl FUN_009558c0();
void __fastcall ObjectAddRef(void*);                       // 0x95f990
void __fastcall FUN_00957530(int*);                        // 0x957530 (defined below)
struct SysInfo { char pad0[0x34]; int f34; char pad38[0x10]; int f48; };
struct I2DSystem {
    virtual void v0();
    virtual void v1();
    virtual void Init(int, int);                 // +8
    virtual void Shutdown();                     // +0xc
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual SysInfo* GetInfo(int, int);          // +0x30
};
struct IFontObj {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual bool Init();                         // +0x20
    virtual void Shutdown();                     // +0x24
};
struct IFontMgr {
    virtual void v0();
    virtual void Release();                      // +4
    virtual void v2();
    virtual IFontObj* Get(int id);               // +0xc
};
struct R2DMemoryManager { char pad[0x68]; R2DMemoryManager(); ~R2DMemoryManager(); };   // 0x953430 / 0x952800
struct R2DPool {
    int f0, f4, f8, fc, f10, f14;
    R2DPool() : f0(0), f4(0), f8(0), f14(0) { Reserve(200); }
    ~R2DPool();                                  // 0x9535a0
    void Reserve(int n);                         // 0x9529d0
};
struct TwoDState { const void* pDefault; int f4; float f8, fc, f10, f14; int f18, f1c, f20; };
extern I2DSystem* g_pI2DSystem;      // 0x166aab8
extern R2DMemoryManager* g_pR2DMemoryManager;   // 0x166aac4
extern R2DPool* g_pR2DPool;          // 0x166aac0
extern IFontMgr* g_pFontMgr;         // 0x166ae74
extern TwoDState g_twoDState;        // 0x166aad0
typedef void (__thiscall *VFn1i)(void*, int);
static inline void** Vt(void* p) { return *(void***)p; }
struct GlyphDisplayEntry { char data[0x28]; };
struct GlyphFixedVec {                     // eastl::fixed_vector<GlyphDisplayEntry, 256>
    GlyphDisplayEntry* mpBegin;
    GlyphDisplayEntry* mpEnd;
    GlyphDisplayEntry* mpCapacity;
    int                mAllocFlags;
    GlyphDisplayEntry* mpPoolBegin;
    int                mAllocPad;
    GlyphDisplayEntry  mBuffer[256];
    GlyphFixedVec() {
        mpEnd = mBuffer;
        mpPoolBegin = mBuffer;
        mpCapacity = mBuffer + 256;
        mpBegin = mBuffer;
    }
    ~GlyphFixedVec() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    void resize(unsigned int n);           // 0x955850
};
struct TextLayout {                        // EA::Text::Layout
    int LayoutTextLine(const wchar_t* text, int len, float x, float y, const void* style,
                       GlyphDisplayEntry* out, unsigned int cap, void* extra);                    // 0x890570
    int LayoutTextLine(const wchar_t* text, int len, float a, float b, float c, float d, const void* style,
                       GlyphDisplayEntry* out, unsigned int cap, void* extra);                    // 0x890830
};
extern TextLayout g_defaultTextLayout;     // 0x166aaf8
struct GlyphRenderer {
    void* mpTarget;                        // +4 (after vptr); defaults to this+0x24
virtual void v0();
virtual void v1();
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
    virtual void DrawGlyphs(GlyphDisplayEntry* pGlyphs, int nCount, const void* pStyle);     // +0x34
    void DrawText(float x, float y, const wchar_t* pText, int nLen, const void* pStyle,
                  TextLayout* pLayout, void* pExtra);
    void DrawText(float a, float b, float c, float d, const wchar_t* pText, int nLen, const void* pStyle,
                  TextLayout* pLayout, void* pExtra);
};
void GlyphRenderer::DrawText(float a, float b, float c, float d, const wchar_t* pText, int nLen, const void* pStyle,
                             TextLayout* pLayout, void* pExtra) {
    if (mpTarget == 0)
        mpTarget = (char*)this + 0x24;
    if (nLen == -1) {
        const wchar_t* p = pText;
        while (*p++ != 0)
            ;
        nLen = (int)(p - (pText + 1));
    }
    if (pStyle == 0)
        pStyle = g_defaultTextStyle;
    if (pLayout == 0)
        pLayout = &g_defaultTextLayout;
    GlyphFixedVec glyphs;
    glyphs.resize(nLen * 2);
    int n = pLayout->LayoutTextLine(pText, nLen, a, b, c, d, pStyle, glyphs.mpBegin, nLen * 2, pExtra);
    DrawGlyphs(glyphs.mpBegin, n, pStyle);
}
struct UIRes { void* Dtor(unsigned char flags); };
// ---- items of slice s009568c0 end

// ---- items of slice s00952390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool g_fontCacheActive;      // 0x0166aabc
extern void* g_fontHead;            // 0x0166ab10
extern void* g_fontTail;            // 0x0166ab14
extern void* g_fontRoot;            // 0x0166ab18
extern uint8_t g_fontFlag;          // 0x0166ab1c
extern uint32_t g_fontCount;        // 0x0166ab20
#pragma intrinsic(_InterlockedExchange)
void* EAAllocate(uint32_t size, const char* name, int p3, int p4, const char* file, int line);  // 0x00f473a0
void* EANew(uint32_t size, int align, int p3, const char* name, int p5, int p6, int p7, int p8); // 0x00f473d0
void  EADelete(void* p);                                                                        // 0x00f47380
void* copy_vec20(const void* first, const void* last, void* dest);       // 0x00951bf0  (0x14)
void* uninit_copy20(const void* first, const void* last, void* dest);    // 0x00951bb0  (0x14)
void* uninit_copy40(const void* first, const void* last, void* dest);    // 0x00951c30  (0x28)
void* copy_rec40(const void* first, const void* last, void* dest);       // 0x00952790  (0x28)
void* copy_vec40b(void** out, const void* first, const void* last, void* dest, const void* p5); // 0x009527c0
void* fill_rec40(void* dst, uint32_t n, const void* value);              // 0x009529a0  (0x28)
void  memmove_0fb3210(void* dst, const void* src, uint32_t n);           // 0x00fb3210
void* vec_copy5(void** out, const void* first, const void* last, void* dest, const void* p5);   // 0x008f05f0
void* copy_backward20(const void* first, const void* last, void* destEnd);                      // 0x00c50ad0
struct BindElem;
struct BindPool {
  void Free(BindElem* p);  // 0x009276c0 (thiscall, ret 4)
};
extern BindPool* g_pBindPool;  // 0x016c8b44
struct Mutex_s0095_2390 {
  uint32_t mData[10];  // CRITICAL_SECTION + init flag (0x28)
  ~Mutex_s0095_2390();            // 0x00922130
};
struct MemPool_s0095_2390 {
  void* Alloc(uint32_t size);  // 0x00951d60 (thiscall, ret 4)
};
extern MemPool_s0095_2390* g_pMemPool;  // 0x0166aac4
namespace EA {
namespace UTFWin {
class Image_s0095_2390 { public:
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4 0x00957550
};
}
}
namespace EA {
namespace UTFWin {
struct Font {
  virtual void v0();        // +0x0
  virtual void v1();        // +0x4
  virtual void v2();        // +0x8
  virtual void Release();   // +0xc
};
}
}
namespace EA {
namespace UTFWin {
struct Vertex2D {  // 0x14
  float x, y;
  uint32_t c;
  float u, v;
};
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DPart_s0095_2390 {  // 0x0c
  Image_s0095_2390* mpImage;    // +0x0
  int mPrimType;     // +0x4
  uint32_t mCount;   // +0x8
  ~Renderable2DPart_s0095_2390() {
    if (mpImage) mpImage->Release();
  }
};
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DTextSpan_s0095_2390 {  // 0x14
  Font* mpFont;         // +0x0
  uint32_t mVertStart;  // +0x4
  uint32_t mGlyphStart; // +0x8
  uint32_t mGlyphCount; // +0xc
  uint32_t mCacheGen;   // +0x10
  ~Renderable2DTextSpan_s0095_2390() {
    if (mpFont) mpFont->Release();
  }
};
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DTextGlyphInfo_s0095_2390 {  // 0x0c
  uint16_t mGlyphId;  // +0x0
  uint16_t mPad;      // +0x2
  float mU;           // +0x4
  float mV;           // +0x8
};
}
}
namespace EA {
namespace UTFWin {
template <class T, int N>
struct FixedVector {
  T* mpBegin;     // +0x0
  T* mpEnd;       // +0x4
  T* mpCapacity;  // +0x8
  int mPad0;      // +0xc
  T* mpPool;      // +0x10
  int mPad1;      // +0x14
  unsigned char mBuffer[N * sizeof(T)];  // +0x18 (raw storage)

  T* buffer() { return (T*)mBuffer; }
  FixedVector() {
    T* b = buffer();
    mpPool = b;
    mpEnd = b;
    mpBegin = b;
    mpCapacity = mpPool + N;
  }
  ~FixedVector() {
    T* p = mpBegin;
    if (p && p != mpPool) EADelete(p);
  }
  void erase(T* first, T* last);
};
}
}
namespace EA {
namespace UTFWin {
struct Vertex2DVector_s0095_2390 : FixedVector<Vertex2D, 600> {
  void DoInsertFromIterator(Vertex2D* position, const Vertex2D* first, const Vertex2D* last,
                            int tag);  // 0x00952b30
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    copy_vec20(mpEnd, mpEnd, mpBegin);
    mpEnd = (Vertex2D*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Vertex2D));
  }
};
}
}
namespace EA {
namespace UTFWin {
struct PartVector_s0095_2390 : FixedVector<Renderable2DPart_s0095_2390, 16> {
  void DoInsertValue(Renderable2DPart_s0095_2390* position, const Renderable2DPart_s0095_2390* value);  // 0x00a27910
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    for (ptrdiff_t i = 0; i < n; ++i)
      if (mpBegin[i].mpImage) mpBegin[i].mpImage->Release();
    mpEnd = (Renderable2DPart_s0095_2390*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DPart_s0095_2390));
  }
  Renderable2DPart_s0095_2390& push_back() {
    Renderable2DPart_s0095_2390 temp;
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else
      DoInsertValue(mpEnd, &temp);
    return *(mpEnd - 1);
  }
};
}
}
namespace EA {
namespace UTFWin {
struct TextSpanVector : FixedVector<Renderable2DTextSpan_s0095_2390, 30> {
  void push_back(const Renderable2DTextSpan_s0095_2390& value);                                // 0x00952ee0
  void DoInsertValue(Renderable2DTextSpan_s0095_2390* position, const Renderable2DTextSpan_s0095_2390* value); // 0x00884d90
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    for (ptrdiff_t i = 0; i < n; ++i)
      if (mpBegin[i].mpFont) mpBegin[i].mpFont->Release();
    mpEnd = (Renderable2DTextSpan_s0095_2390*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DTextSpan_s0095_2390));
  }
};
}
}
namespace EA {
namespace UTFWin {
struct GlyphInfoVector : FixedVector<Renderable2DTextGlyphInfo_s0095_2390, 200> {
  void DoInsertValue(Renderable2DTextGlyphInfo_s0095_2390* position,
                     const Renderable2DTextGlyphInfo_s0095_2390* value);
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    mpEnd = (Renderable2DTextGlyphInfo_s0095_2390*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DTextGlyphInfo_s0095_2390));
  }
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2D { public:
  virtual void AddRef();                     // +0x0
  Renderable2DPart_s0095_2390* mpPartsBegin;            // +0x4
  Renderable2DPart_s0095_2390* mpPartsEnd;              // +0x8
  Vertex2D* mpVertsBegin;                    // +0xc
  Vertex2D* mpVertsEnd;                      // +0x10
  Renderable2DTextSpan_s0095_2390* mpSpansBegin;        // +0x14
  Renderable2DTextSpan_s0095_2390* mpSpansEnd;          // +0x18
  Renderable2DTextGlyphInfo_s0095_2390* mpGlyphsBegin;  // +0x1c
  Renderable2DTextGlyphInfo_s0095_2390* mpGlyphsEnd;    // +0x20
  void* mpMemoryBuffer;                      // +0x24
  volatile long mRefCount;                   // +0x28

  Renderable2D() {
    mpPartsBegin = 0;
    mpPartsEnd = 0;
    mpVertsBegin = 0;
    mpVertsEnd = 0;
    mpSpansBegin = 0;
    mpSpansEnd = 0;
    mpGlyphsBegin = 0;
    mpGlyphsEnd = 0;
    mpMemoryBuffer = 0;
    _InterlockedExchange(&mRefCount, 0);
  }
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2DPool { public:
  Renderable2D** mpBegin;     // +0x0
  Renderable2D** mpEnd;       // +0x4
  Renderable2D** mpCapacity;  // +0x8
  int mPad0;                  // +0xc
  int mPad1;                  // +0x10
  int mCount;                 // +0x14
  Renderable2D* AcquireRenderable();  // 0x00952860
};
}
}
namespace EA {
namespace UTFWin {
extern Renderable2DPool* g_pRenderable2DPool;  // 0x0166aac0
}
}
namespace EA {
namespace UTFWin {
class Renderable2DBuilder_s0095_2390 { public:
  Vertex2DVector_s0095_2390 mVerts;                      // +0x0
  PartVector_s0095_2390 mParts;                          // +0x2ef8
  TextSpanVector mTextSpans;                  // +0x2fd0
  GlyphInfoVector mGlyphInfos;                // +0x3240

  Renderable2DBuilder_s0095_2390();                      // 0x00952aa0
  ~Renderable2DBuilder_s0095_2390();                     // 0x00952f80
  void BeginPart(int primType, Image_s0095_2390* pImage);  // 0x009531a0
  Renderable2D* Build();                      // 0x00953220
};
}
}
namespace EA {
namespace UTFWin {
uint32_t roundUp8(uint32_t n) { return (n + 7u) & ~7u; }
}
}
struct SpanSource {
  char pad0[0x2c];
  uint16_t* mpBegin;  // +0x2c
  uint16_t* mpEnd;    // +0x30
  char pad1[0x54 - 0x34];
  void* mpFont;       // +0x54
};
struct DrawSpanCtx {
  virtual void v0();   // +0x00
  virtual void v1();
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
  virtual void DrawSpan(const void* begin, void* font, int count);  // +0x30
  void FUN_00952720(const SpanSource* p);                           // 0x00952720
};
struct Elem0C {
  uint32_t m0, m4, m8;
};
struct ResourceHolder {
  uint32_t mMutex[10];     // +0x0 (EA::Thread::Mutex storage)
  char pad0[0x30 - 0x28];  // +0x28
  BindElem* mpElem30;      // +0x30
  uint32_t mPad34;         // +0x34
  BindElem* mpElem38;      // +0x38
  uint32_t mPad3C;         // +0x3c
  void* mpBuf40;           // +0x40
  char pad1[0x54 - 0x44];  // +0x44
  void* mpBuf54;           // +0x54
  void Destroy();          // 0x00952800
};
struct SkinPart {
  EA::UTFWin::Image_s0095_2390* mpImage;  // +0x0
  int mPrimType;               // +0x4
  uint32_t mCount;             // +0x8
};
struct ImageData {
  char pad[0x24];
  uint32_t mFlags;  // +0x24
};
struct SkinOut {
  int mPrimType;                 // +0x0
  uint32_t mCount;               // +0x4
  uint32_t mFlags;               // +0x8
  void* mpVerts;                 // +0xc
  EA::UTFWin::Image_s0095_2390* mpImage;    // +0x10
};
struct SkinBuilder {
  int m0;            // +0x0
  SkinPart* mpPartsCur;  // +0x4
  SkinPart* mpPartsEnd;  // +0x8
  int mC;            // +0xc
  uint8_t* mpVertsCur;   // +0x10
  uint8_t* mpSaved14;    // +0x14
  int m18;           // +0x18
  uint8_t* mpVertsEnd;   // +0x1c
  bool BuildSkinVertices(int arg);  // 0x00951e10 (thiscall, ret 4)

  bool FUN_009528d0(SkinOut* out, int arg);  // 0x009528d0
};
struct Rec40_s0095_2390 {
  uint32_t m[10];  // 0x28
};
struct Vec40Vector {
  Rec40_s0095_2390* mpBegin;     // +0x0
  Rec40_s0095_2390* mpEnd;       // +0x4
  Rec40_s0095_2390* mpCapacity;  // +0x8
  int mPad0;          // +0xc
  Rec40_s0095_2390* mpPool;      // +0x10
  void DoInsertValues(Rec40_s0095_2390* position, uint32_t n, const Rec40_s0095_2390& value);  // 0x00952d10
};
namespace EA {
namespace Text {
struct FontTree {
  void DoNukeSubtree(void* pNode);  // 0x0088fda0
};  // namespace Text
}
}
extern EA::Text::FontTree g_fontTree;  // 0x0166ab0c
struct TextLayoutObj {
  char pad[0x248];
  uint32_t mKind;  // +0x248
  char pad2[4];
  uint32_t mFlag;  // +0x250
};
void* FUN_008976a0(void*);                              // 0x008976a0 (thiscall)
void  FUN_0089cdf0(void*, int);                         // 0x0089cdf0
void  FUN_008981f0(void*, const void*);                 // 0x008981f0
void* FUN_00897670(void*);                              // 0x00897670
void  FUN_0089b1e0(void*, const void*, int);            // 0x0089b1e0
void  FUN_00897640(void*, float, float, float);         // 0x00897640
void* FUN_0089d9a0(void*);                              // 0x0089d9a0
float FUN_008975c0(void*);                              // 0x008975c0
void  FUN_00897b40(void*, float, float, int, int, int); // 0x00897b40
int   FUN_00897680(void*);                              // 0x00897680
void  FUN_0089c5d0(void*, int);                         // 0x0089c5d0
void  FUN_008945a0(void*, const void*);                 // 0x008945a0
struct Draw2DLike {
  virtual void v0();          // +0x0
  void* mpRenderable;         // +0x4
  void* mpWindowMgr;          // +0x8
  uint32_t mColor;            // +0xc
  bool mbClip;                // +0x10
  float mClip[4];             // +0x14
  char mBuilder[0x3bb8];      // +0x24 (Renderable2DBuilder mDefaultRenderable)
};
struct Draw2DWindowMgr {
  virtual void w0();  // +0x0
  char pad[0x88 - 4];
  void* GetTextEngine();  // +0x88
};
// ---- items of slice s00952390 end

// ---- items of slice s00953430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_half;       // 0x01471064
extern float g_one;        // 0x01485720
void FUN_011e0744(void* dst, const void* src, uint32_t bytes);                                  // 0x011e0744
struct MemPool_s0095_3430 {
  void* LockedAlloc(uint32_t size, int, int, int, int, int);  // 0x009289f0
};
uint32_t __cdecl ModulateARGB32(uint32_t a, uint32_t b);                                        // 0x0095f8c0
extern MemPool_s0095_3430* g_pMemPool_s0095_3430;   // 0x016c8b44
namespace EA {
namespace Thread {
class Mutex_s0095_3430 { public:
  uint32_t mData[10];  // 0x28
  Mutex_s0095_3430(const void*, bool);  // 0x009222a0
};  // namespace Thread
}
}
namespace EA {
namespace UTFWin {
class Image_s0095_3430 { public:
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4 0x00957550
};
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DPart_s0095_3430 {  // 0x0c
  Image_s0095_3430* mpImage;   // +0x0
  int mPrimType;    // +0x4
  uint32_t mCount;  // +0x8
};
}
}
namespace EA {
namespace UTFWin {
template <class T, int N>
struct FixedVector_s0095_3430 {
  T* mpBegin;                            // +0x00
  T* mpEnd;                              // +0x04
  T* mpCapacity;                         // +0x08
  int mPad0;                             // +0x0c
  T* mpPool;                             // +0x10
  int mPad1;                             // +0x14
  unsigned char mBuffer[N * sizeof(T)];  // +0x18

  T* buffer() { return (T*)mBuffer; }
  FixedVector_s0095_3430() {
    T* b = buffer();
    mpPool = b;
    mpEnd = b;
    mpBegin = b;
    mpCapacity = b + N;
  }
  bool empty() const { return mpBegin == mpEnd; }
  T& back() { return *(mpEnd - 1); }
  void pop_back() { --mpEnd; }
};
}
}
namespace EA {
namespace UTFWin {
struct Vertex2DVector_s0095_3430 : FixedVector_s0095_3430<Vertex2D, 600> {
  void DoInsertValue(Vertex2D* position, const Vertex2D* value);  // 0x00884d90
  void push_back(const Vertex2D& value) {
    Vertex2D* p = mpEnd;
    if (p < mpCapacity) {
      mpEnd = p + 1;
      if (p) *p = value;
    } else {
      DoInsertValue(p, &value);
    }
  }
};
}
}
namespace EA {
namespace UTFWin {
struct PartVector_s0095_3430 : FixedVector_s0095_3430<Renderable2DPart_s0095_3430, 16> {
  void DoInsertValue(Renderable2DPart_s0095_3430* position, const Renderable2DPart_s0095_3430* value);  // 0x00a27910
  Renderable2DPart_s0095_3430& push_back() {
    Renderable2DPart_s0095_3430 temp;
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else
      DoInsertValue(mpEnd, &temp);
    return *(mpEnd - 1);
  }
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2DBuilder_s0095_3430 { public:
  Vertex2DVector_s0095_3430 mVerts;  // +0x0000
  PartVector_s0095_3430 mParts;      // +0x2ef8

  void BeginPart(int primType, Image_s0095_3430* pImage);  // 0x009531a0
  void Add(const Vertex2D& value);              // 0x00952ee0

  __forceinline void BeginPartInline(int primType, Image_s0095_3430* pImage) {
    if (mParts.mpBegin != mParts.mpEnd) {
      Renderable2DPart_s0095_3430* pLast = mParts.mpEnd - 1;
      if (pLast->mPrimType == primType && pLast->mpImage == pImage) return;
    }
    if (pImage) pImage->AddRef();
    mParts.push_back();
    Renderable2DPart_s0095_3430* part = mParts.mpEnd - 1;
    part->mpImage = pImage;
    part->mPrimType = primType;
    part->mCount = 0;
  }

  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image_s0095_3430* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};
}
}
namespace EA {
namespace UTFWin {
struct Rect {  // 0x10
  float m[4];
};
}
}
namespace EA {
namespace UTFWin {
class Draw2D_s0095_3430 { public:
  void* mpVtable;                      // +0x00
  Renderable2DBuilder_s0095_3430* mpRenderable;   // +0x04
  void* mpWindowMgr;                   // +0x08
  uint32_t mColor;                     // +0x0c
  bool mbClip;                         // +0x10
  char mPad11[3];                      // +0x11
  Rect mClipRect;                      // +0x14
  Renderable2DBuilder_s0095_3430 mDefaultRenderable;  // +0x24

  void DrawLine4(float x0, float y0, float x1, float y1);   // 0x00953600
  void DrawQuadUV(float x0, float y0, float x1, float y1);  // 0x009537e0
  void FillQuad(const Point2D* p0, const Point2D* p1, const Point2D* p2, const Point2D* p3);
  void FillGradH(const Rect& r, uint32_t color0, uint32_t color1);  // 0x00953eb0 (EA::UTFWin::Draw2D::FillGradH)
};
}
}
namespace EA {
namespace UTFWin {
__forceinline void AddVertexInline(Renderable2DBuilder_s0095_3430* pBuilder, float x, float y,
                                    uint32_t c) {
  Vertex2D v;
  v.x = x;
  v.y = y;
  v.c = c;
  v.u = 0.0f;
  v.v = 0.0f;
  pBuilder->mVerts.push_back(v);
}
}
}
namespace EA {
namespace UTFWin {
__forceinline void AddVertexInline(Renderable2DBuilder_s0095_3430* pBuilder, const Point2D& p,
                                   uint32_t c) {
  AddVertexInline(pBuilder, p.x, p.y, c);
}
}
}
namespace EA {
namespace UTFWin {
struct CellData {  // 0x80
  uint32_t m[0x20];
};
}
}
namespace EA {
namespace UTFWin {
struct CellDataVector {
  CellData** mpBegin;     // +0x0
  CellData** mpEnd;       // +0x4
  CellData** mpCapacity;  // +0x8

  void reserve(uint32_t n);  // 0x009529d0
  void DoInsertValue(CellData** position, CellData* const& value);  // 0x00a80dd0

  void push_back(CellData* const& value) {
    CellData** p = mpEnd;
    if (p < mpCapacity) {
      mpEnd = p + 1;
      if (p) *p = value;
    } else {
      DoInsertValue(p, value);
    }
  }
};
}
}
namespace EA {
namespace UTFWin {
__forceinline void ReserveInline(CellDataVector& v, uint32_t n) {
  if ((uint32_t)(v.mpCapacity - v.mpBegin) >= n) return;
  CellData** p = (CellData**)EAAllocate(
      n * sizeof(CellData*), "EASTL", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  FUN_011e0744(p, v.mpBegin, (uint32_t)((char*)v.mpEnd - (char*)v.mpBegin));
  if (v.mpBegin && ((int*)v.mpBegin)[-1]) EADelete(v.mpBegin);
  CellData** pEnd = p + (v.mpEnd - v.mpBegin);
  v.mpBegin = p;
  v.mpEnd = pEnd;
  v.mpCapacity = p + n;
}
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DMemoryManager {
  EA::Thread::Mutex_s0095_3430 mMutex;  // +0x00
  int mPad28;                // +0x28
  int mPad2c;                // +0x2c
  CellData* mpSmall;         // +0x30
  CellData* mpSmallEnd;      // +0x34
  CellData* mpLarge;         // +0x38
  CellData* mpLargeEnd;      // +0x3c
  CellDataVector mSmallFree; // +0x40
  char mPad4c[8];            // +0x4c
  CellDataVector mLargeFree; // +0x54
  char mPad60[8];            // +0x60

  Renderable2DMemoryManager();
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2D_s0095_3430 { public:
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2DPool_s0095_3430 { public:
  Renderable2D_s0095_3430** mpBegin;     // +0x0
  Renderable2D_s0095_3430** mpEnd;       // +0x4
  Renderable2D_s0095_3430** mpCapacity;  // +0x8
  int mPad0;                  // +0xc
  int mPad1;                  // +0x10
  int mCount;                 // +0x14
  ~Renderable2DPool_s0095_3430();
};
}
}
// ---- items of slice s00953430 end

// ---- items of slice s009541d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RectT_s0095_41d0 { public:
  T mLeft, mTop, mRight, mBottom;
  template <typename P>
  __forceinline bool Contains(const P& p) const {
    return p.x >= mLeft && p.y >= mTop && p.x < mRight && p.y < mBottom;
  }
};
}
namespace EA {
namespace Drawing {
struct Vertex2D_s0095_41d0 {
  float x, y;
  uint32_t c;
  float u, v;
};  // namespace Drawing
}
}
namespace EA {
namespace UTFWin {
struct Point2D_s0095_41d0 {
  float x, y;
  Point2D_s0095_41d0(float px, float py) : x(px), y(py) {}
};
}
}
namespace EA {
namespace UTFWin {
class Image_s0095_41d0 { public:
  virtual void AddRef();
  virtual void Release();  // 0x00957550 (EA::UTFWin::Image::Release)
};
}
}
namespace EA {
namespace UTFWin {
struct Renderable2DPart_s0095_41d0 {
  Image_s0095_41d0* mpImage;
  int mPrimType;
  uint32_t mCount;
};
}
}
namespace EA {
namespace UTFWin {
template <typename T, typename D>
struct VectorT_s0095_41d0 {
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
}
}
namespace EA {
namespace UTFWin {
struct Vertex2DVector_s0095_41d0 : VectorT_s0095_41d0<Drawing::Vertex2D_s0095_41d0, Vertex2DVector_s0095_41d0> {
  void DoInsertValue(Drawing::Vertex2D_s0095_41d0* position, const Drawing::Vertex2D_s0095_41d0& value);  // 0x00884d90
};
}
}
namespace EA {
namespace UTFWin {
struct PartVector_s0095_41d0 : VectorT_s0095_41d0<Renderable2DPart_s0095_41d0, PartVector_s0095_41d0> {
  void DoInsertValue(Renderable2DPart_s0095_41d0* position, const Renderable2DPart_s0095_41d0& value);  // 0x00a27910
};
}
}
namespace EA {
namespace UTFWin {
class Renderable2DBuilder_s0095_41d0 { public:
  Vertex2DVector_s0095_41d0 mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector_s0095_41d0 mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)

  void BeginPart(int primType, Image_s0095_41d0* pImage);        // 0x009531a0
  __forceinline void AddVertexInline(const Point2D_s0095_41d0& p, uint32_t c) {
    Drawing::Vertex2D_s0095_41d0 v;
    v.x = p.x; v.y = p.y; v.c = c; v.u = 0.0f; v.v = 0.0f;
    mVerts.push_back(v);
  }

  __forceinline void BeginPartInline(int primType, Image_s0095_41d0* pImage) {
    if (mParts.empty() || mParts.back().mPrimType != primType || mParts.back().mpImage != pImage) {
      mParts.push_back();
      Renderable2DPart_s0095_41d0& part = mParts.back();
      part.mpImage = pImage;
      part.mPrimType = primType;
      part.mCount = 0;
    }
  }
  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image_s0095_41d0* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};
}
}
namespace EA {
namespace UTFWin {
uint32_t ClipPolygon2D(const RectT_s0095_41d0<float>* pRect, const Drawing::Vertex2D_s0095_41d0* pIn, uint32_t nIn,
                       Drawing::Vertex2D_s0095_41d0* pOut, uint32_t nOutMax);
}
}
namespace EA {
namespace UTFWin {
class Draw2D_s0095_41d0 : public IDrawContext {
 public:
  Renderable2DBuilder_s0095_41d0* mpRenderable;  // +0x4
  void* mpWindowMgr;                  // +0x8
  uint32_t mColor;                    // +0xc
  bool mbClip;                        // +0x10
  RectT_s0095_41d0<float> mClipRect;             // +0x14
  Renderable2DBuilder_s0095_41d0 mDefaultRenderable;  // +0x24

  __forceinline void AddVert(const Point2D_s0095_41d0& p, uint32_t c) { mpRenderable->AddVertexInline(p, c); }

  void FillGradV(const RectT_s0095_41d0<float>& rect, uint32_t color0, uint32_t color1);  // 0x009541d0 (EA::UTFWin::Draw2D::FillGradV)
  void FillTriGrad(const Point2D_s0095_41d0& p0, uint32_t color0, const Point2D_s0095_41d0& p1, uint32_t color1,
                   const Point2D_s0095_41d0& p2, uint32_t color2);
};
}
}
// ---- items of slice s009541d0 end

// ---- items of slice s009559a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace SP {
struct CellData_s0095_59a0 {
  void FUN_009558c0();  // 0x009558c0
};
}
}
namespace EA {
namespace SP {
struct SimpleVectorCell_s0095_59a0 {
  CellData_s0095_59a0** mpBegin;     // +0x0
  CellData_s0095_59a0** mpEnd;       // +0x4
  CellData_s0095_59a0** mpCapacity;  // +0x8
  int mPad0;              // +0xc
  int mPad1;              // +0x10
  int mCount;             // +0x14
  void DoInsertValue(CellData_s0095_59a0** position, CellData_s0095_59a0* const& value);  // 0x00a80dd0
  void push_back(CellData_s0095_59a0* p) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) CellData_s0095_59a0*(p);
    else
      DoInsertValue(mpEnd, p);
  }
};
}
}
namespace EA {
namespace SP {
extern SimpleVectorCell_s0095_59a0* gCellList;  // 0x0166aac0
}
}
// ---- items of slice s009559a0 end

// ---- items of slice s00fb2ac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct E40 { unsigned d[10]; };
struct Vec40 {
    E40*  begin;
    E40*  end;
    E40*  cap;
    E40*  erase(E40* first, E40* last);
};
// ---- items of slice s00fb2ac0 end

// @ 0x00951c30
Rec40* uninitialized_copy_Rec40(const Rec40* first, const Rec40* last, Rec40* dest)
{
  for (; first != last; ++first, ++dest)
    ::new (dest) Rec40(*first);
  return dest;
}

// @ 0x00951d60
void* MemPool::Alloc(unsigned size)
{
    if (size == 0) return 0;
    if (size < 0x80 && free0 != cur0) {
        void* v = *(void**)(cur0 - 4);
        cur0 -= 4;
        return v;
    }
    if (size < 0x800 && free1 != cur1) {
        void* v = *(void**)(cur1 - 4);
        cur1 -= 4;
        return v;
    }
    return LockedAllocCall(g_pMemPool16c8b44, 0, size, 0, 0, 0, 0, 0);
}

// @ 0x00951dc0
IterCopy* IterCopy::Set(int* src)
{
    f0 = (int)(size_t)src;
    f1 = src[1];
    f2 = src[2];
    int v = src[3];
    f3 = v;
    f4 = v;
    int v2 = src[5];
    f5 = v2;
    f6 = src[6];
    f7 = 0;
    if (v2 != f6) f7 = f3 + *(int*)(v2 + 4) * 0x14;
    return this;
}

// @ 0x00951e10
bool BuildSkinVertices(int* self, int)
{
    (void)self;
    return true;
}

// @ 0x009520a0
void XformQuad(void* self, float a, float b, float c, float d)
{
    ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, a, b, c, d);
}

// @ 0x00952100
char Bounds::GetBounds(float* out)
{
    out[0] = mMinX;
    out[1] = mMinY;
    out[2] = mMaxX;
    out[3] = mMaxY;
    return mValid;
}

// @ 0x00952130
void Bounds::SetBounds(char valid, const float* r)
{
    mValid = valid;
    if (valid) {
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
    }
}

// @ 0x00952160
const float* Bounds::UnionBounds(const float* r)
{
    if (mValid == 0) {
        mValid = 1;
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
        return r;
    }
    if (mMaxX <= r[0] || r[2] <= mMinX || mMaxY <= r[1] || r[3] <= mMinY) {
        mMinX = 0; mMinY = 0; mMaxX = 0; mMaxY = 0;
        return r;
    }
    _ReadWriteBarrier();
    if (r[0] > mMinX) mMinX = r[0];
    if (r[1] > mMinY) mMinY = r[1];
    if (r[2] < mMaxX) mMaxX = r[2];
    if (r[3] < mMaxY) mMaxY = r[3];
    return r;
}

// @ 0x00952230
void AddElement(float* self, float x0, float y0, float x1, float y1, float z)
{
    if (*(int*)((char*)self + 4) == 0) *(int*)((char*)self + 4) = (int)(self + 9);
    float w = x1 - x0, h = y1 - y0;
    float dw = (w <= z) ? w : z;
    float dh = (h <= z) ? h : z;
    if (dw > 0.0f && dh > 0.0f) {
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y0, x1 + dw, y1);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x1 - dw, y0, x1, y1);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y0, x1, y0 + dh);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y1 - dh, x1, y1);
    }
}

// @ 0x00952390
void FUN_00952390(Draw2DLike* self, const float* pRect, const uint16_t* pText, int count, void* pStyle, int halign, int valign)
{
  if (count == -1) count = 0;

  Draw2DWindowMgr* pMgr = (Draw2DWindowMgr*)self->mpWindowMgr;
  void* pEngine = pMgr->GetTextEngine();

  void* pLayout = FUN_008976a0(pEngine);
  FUN_0089cdf0(pEngine, 1);

  if (halign != 5 || valign != 4) {
    FUN_008945a0(&pStyle, pStyle);
  }
  FUN_008981f0(pEngine, &pStyle);
  TextLayoutObj* pObj = (TextLayoutObj*)FUN_00897670(pEngine);
  FUN_0089b1e0(pEngine, pText, count);

  if (pObj->mFlag == 0) {
    FUN_00897640(pEngine, pRect[0], pRect[1], pRect[2] - pRect[0]);
    FUN_0089d9a0(pEngine);
    float fMetric = FUN_008975c0(pLayout);
    if (pObj->mKind == 2) {
      FUN_00897b40(pLayout, 0.0f, pRect[3] - pRect[1] - fMetric, (int)(pObj->mFlag), 0, 0);
    } else if (pObj->mKind == 1) {
      FUN_00897b40(pLayout, 0.0f, (pRect[3] - pRect[1] - fMetric) * 0.5f, 0, 0, 0);
    }
    return;
  }

  FUN_00897640(pEngine, pRect[0], pRect[1], pRect[2] - pRect[0]);
  while (FUN_00897680(pEngine) != 2) {
    FUN_0089d9a0(pEngine);
    float fAdv = FUN_008975c0(pLayout);
    FUN_0089c5d0(pEngine, 0);
  }
  if (pObj->mKind == 2) {
  } else if (pObj->mKind == 1) {
  }
  FUN_0089cdf0(pEngine, 0);
  FUN_0089b1e0(pEngine, pText, count);
}

// @ 0x00952720
void DrawSpanCtx::FUN_00952720(const SpanSource* p)
{
  DrawSpan(p->mpBegin, p->mpFont, (int)(p->mpEnd - p->mpBegin));
}

// @ 0x00952750
Elem0C* FUN_00952750(const Elem0C* first, const Elem0C* last, Elem0C* dst)
{
  if (first == last) return dst;
  ptrdiff_t off = (const char*)first - (const char*)dst;
  do {
    if (dst) *dst = *(const Elem0C*)((const char*)dst + off);
    dst = (Elem0C*)((const char*)dst + 0xc);
  } while ((const char*)dst + off != (const char*)last);
  return dst;
}

// @ 0x00952800
void ResourceHolder::Destroy()
{
  g_pBindPool->Free(mpElem30);
  g_pBindPool->Free(mpElem38);
  if (mpBuf54 && ((int*)mpBuf54)[-1]) EADelete(mpBuf54);
  if (mpBuf40 && ((int*)mpBuf40)[-1]) EADelete(mpBuf40);
  ((Mutex_s0095_2390*)this)->~Mutex_s0095_2390();
}

// @ 0x00952860
namespace EA { namespace UTFWin {
Renderable2D* Renderable2DPool::AcquireRenderable()
{
  Renderable2D** pEnd = mpEnd;
  if (mpBegin == pEnd) {
    Renderable2D* p = (Renderable2D*)EAAllocate(0x2c, "UTFWin/Renderable2D", 0, 0, 0, 0);
    Renderable2D* r = 0;
    if (p) r = new (p) Renderable2D();
    r->AddRef();
    ++mCount;
    return r;
  }
  Renderable2D* p = *(pEnd - 1);
  ++mCount;
  mpEnd = pEnd - 1;
  return p;
}
}}  // namespace EA::UTFWin

// @ 0x009528d0
bool SkinBuilder::FUN_009528d0(SkinOut* out, int arg)
{
  SkinPart* pPart = mpPartsCur;
  if (pPart == mpPartsEnd) return false;

  EA::UTFWin::Image_s0095_2390* pImage = pPart->mpImage;
  out->mFlags = 0;
  if (pImage) {
    uint8_t* pSavedEnd = mpVertsEnd;
    uint8_t* pSaved14 = mpSaved14;
    while (mpVertsEnd != 0 && mpVertsEnd < mpVertsCur + pPart->mCount * 0x14) {
      if (!BuildSkinVertices(arg)) {
        mpVertsEnd = pSavedEnd;
        mpSaved14 = pSaved14;
        return false;
      }
      out->mFlags |= 0x1000;
    }
    uint32_t flags = ((ImageData*)pImage)->mFlags;
    if (flags & 2) out->mFlags |= 2;
    if (!(flags & 4)) out->mFlags |= 1;
  }
  out->mPrimType = pPart->mPrimType;
  out->mpImage = pImage;
  out->mpVerts = mpVertsCur;
  out->mCount = pPart->mCount;
  mpPartsCur += 1;
  mpVertsCur += pPart->mCount * 0x14;
  return true;
}

// @ 0x00952a60
void* FUN_00952a60()
{
  void* p = EANew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
  if (!p) return 0;
  ((uint32_t*)p)[1] = 0;
  ((uint32_t*)p)[0] = 0;
  ((uint32_t*)p)[4] = 0;
  return p;
}

// @ 0x00952aa0
EA::UTFWin::Renderable2DBuilder_s0095_2390::Renderable2DBuilder_s0095_2390()
{}

// @ 0x00952b30
namespace EA { namespace UTFWin {
void Vertex2DVector_s0095_2390::DoInsertFromIterator(Vertex2D* position, const Vertex2D* first, const Vertex2D* last, int /*tag*/)
{
  if (first == last) return;

  const uint32_t n = (uint32_t)(last - first);
  const uint32_t available = (uint32_t)(mpCapacity - mpEnd);
  if (n > available) {
    // grow
    uint32_t oldCapacity = (uint32_t)(mpEnd - mpBegin);
    uint32_t newCapacity = oldCapacity * 2;
    if (oldCapacity == 0) newCapacity = 1;
    if (newCapacity < n + oldCapacity) newCapacity = n + oldCapacity;
    Vertex2D* pNew = newCapacity
                         ? (Vertex2D*)EAAllocate(
                               newCapacity * 0x14, "EASTL", 0, 0,
                               "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                               "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                               0xd1)
                         : 0;
    Vertex2D* p1 = (Vertex2D*)uninit_copy20(mpBegin, position, pNew);
    vec_copy5((void**)&p1, first, last, p1, position);
    Vertex2D* p2 = (Vertex2D*)uninit_copy20(position, mpEnd, p1);
    if (mpBegin && mpBegin != mpPool) EADelete(mpBegin);
    mpBegin = pNew;
    mpEnd = p2;
    mpCapacity = pNew + newCapacity;
    return;
  }

  const uint32_t elemsAfter = (uint32_t)(mpEnd - position);
  if (n < elemsAfter) {
    Vertex2D* pEnd = mpEnd;
    Vertex2D* pShifted = pEnd - n;
    void* out = 0;
    copy_vec40b(&out, pShifted, pEnd, pEnd, position);
    mpEnd += n;
    memmove_0fb3210(position, pShifted, (uint32_t)(pEnd - position) * 0x14);
    copy_backward20(pEnd, pEnd, pShifted);
    vec_copy5((void**)&out, first, last, position, position);
    return;
  }

  Vertex2D* pEnd = mpEnd;
  void* out = 0;
  copy_vec40b(&out, pEnd, pEnd, pEnd, position);
  mpEnd += (uint32_t)(pEnd - position);
  vec_copy5((void**)&out, first, last, pEnd, position);
  mpEnd += n;
  copy_backward20(first, last, position);
}
}}  // namespace EA::UTFWin

// @ 0x00952d10
void Vec40Vector::DoInsertValues(Rec40_s0095_2390* position, uint32_t n, const Rec40_s0095_2390& value)
{
  if (n > (uint32_t)(mpCapacity - mpEnd)) {
    uint32_t oldCapacity = (uint32_t)(mpEnd - mpBegin);
    uint32_t newCapacity = oldCapacity * 2;
    if (oldCapacity == 0) newCapacity = 1;
    if (newCapacity < oldCapacity + n) newCapacity = oldCapacity + n;
    Rec40_s0095_2390* pNew =
        newCapacity
            ? (Rec40_s0095_2390*)EAAllocate(newCapacity * 0x28, "EASTL", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                                 "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                 0xd1)
            : 0;
    Rec40_s0095_2390* p1 = (Rec40_s0095_2390*)uninit_copy40(mpBegin, position, pNew);
    fill_rec40(p1, n, &value);
    Rec40_s0095_2390* p2 = (Rec40_s0095_2390*)uninit_copy40(position, mpEnd, p1 + n);
    if (mpBegin && mpBegin != mpPool) EADelete(mpBegin);
    mpBegin = pNew;
    mpEnd = p2;
    mpCapacity = pNew + newCapacity;
    return;
  }
  if (n == 0) return;

  Rec40_s0095_2390 local;
  memmove_0fb3210(&local, &value, 0x28);
  uint32_t elemsAfter = (uint32_t)(mpEnd - position);
  if (n < elemsAfter) {
    Rec40_s0095_2390* pEnd = mpEnd;
    Rec40_s0095_2390* pShifted = pEnd - n;
    void* out = 0;
    copy_vec40b(&out, pShifted, pEnd, pEnd, position);
    mpEnd += n;
    memmove_0fb3210(position, pShifted, (uint32_t)(pEnd - position) * 0x28);
    copy_rec40(position, position, &local);
    return;
  }
  Rec40_s0095_2390* pEnd = mpEnd;
  fill_rec40(pEnd, n - elemsAfter, &local);
  mpEnd += n - elemsAfter;
  void* out = 0;
  copy_vec40b(&out, position, pEnd, mpEnd, position);
  mpEnd += elemsAfter;
  fill_rec40(position, elemsAfter, &local);
}

// @ 0x00952ee0
namespace EA { namespace UTFWin {
void TextSpanVector::push_back(const Renderable2DTextSpan_s0095_2390& value)
{
  if (mpEnd < mpCapacity) {
    Renderable2DTextSpan_s0095_2390* p = mpEnd++;
    if (p) *p = value;
  } else {
    DoInsertValue(mpEnd, &value);
  }
}
}}  // namespace EA::UTFWin

// @ 0x00952f30
void FUN_00952f30()
{
  if (g_fontCacheActive) {
    g_fontCacheActive = false;
    g_fontTree.DoNukeSubtree(g_fontRoot);
    g_fontHead = (void*)&g_fontHead;
    g_fontTail = (void*)&g_fontHead;
    g_fontRoot = 0;
    g_fontFlag = 0;
    g_fontCount = 0;
  }
}

// @ 0x00952f80
namespace EA { namespace UTFWin {
Renderable2DBuilder_s0095_2390::~Renderable2DBuilder_s0095_2390()
{
  mVerts.clear();
  mParts.clear();
  mTextSpans.clear();
  mGlyphInfos.clear();
}
}}  // namespace EA::UTFWin

// @ 0x009531a0
namespace EA { namespace UTFWin {
void Renderable2DBuilder_s0095_2390::BeginPart(int primType, Image_s0095_2390* pImage)
{
  if (mParts.mpBegin != mParts.mpEnd) {
    Renderable2DPart_s0095_2390* pLast = mParts.mpEnd - 1;
    if (pLast->mPrimType == primType && pLast->mpImage == pImage) return;
  }
  if (pImage) pImage->AddRef();
  if (mParts.mpEnd < mParts.mpCapacity) {
    ++mParts.mpEnd;
  } else {
    struct PartRaw {
      void* mpImage;
      int mPrimType;
      uint32_t mCount;
    } raw;
    mParts.DoInsertValue(mParts.mpEnd, (const Renderable2DPart_s0095_2390*)&raw);
  }
  Renderable2DPart_s0095_2390* part = mParts.mpEnd - 1;
  part->mpImage = pImage;
  part->mPrimType = primType;
  part->mCount = 0;
}
}}  // namespace EA::UTFWin

// @ 0x00953220
namespace EA { namespace UTFWin {
Renderable2D* Renderable2DBuilder_s0095_2390::Build()
{
  uint32_t offVerts = roundUp8((uint32_t)(mParts.mpEnd - mParts.mpBegin) * 0xc);
  uint32_t offSpans = roundUp8(offVerts + (uint32_t)(mVerts.mpEnd - mVerts.mpBegin) * 0x14);
  uint32_t offGlyphs = roundUp8(offSpans + (uint32_t)(mTextSpans.mpEnd - mTextSpans.mpBegin) * 0x14);
  uint32_t total = offGlyphs + (uint32_t)(mGlyphInfos.mpEnd - mGlyphInfos.mpBegin) * 0xc;

  Renderable2D* p = g_pRenderable2DPool->AcquireRenderable();
  char* pBuf = (char*)g_pMemPool->Alloc(total);

  p->mpPartsBegin = (Renderable2DPart_s0095_2390*)pBuf;
  p->mpPartsEnd = (Renderable2DPart_s0095_2390*)FUN_00952750((const Elem0C*)mParts.mpBegin,
                                                  (const Elem0C*)mParts.mpEnd, (Elem0C*)pBuf);
  p->mpVertsBegin = (Vertex2D*)(pBuf + offVerts);
  p->mpVertsEnd = (Vertex2D*)uninit_copy20(mVerts.mpBegin, mVerts.mpEnd, p->mpVertsBegin);
  p->mpSpansBegin = (Renderable2DTextSpan_s0095_2390*)(pBuf + offSpans);
  p->mpSpansEnd =
      (Renderable2DTextSpan_s0095_2390*)uninit_copy20(mTextSpans.mpBegin, mTextSpans.mpEnd, p->mpSpansBegin);
  p->mpGlyphsBegin = (Renderable2DTextGlyphInfo_s0095_2390*)(pBuf + offGlyphs);
  p->mpGlyphsEnd = (Renderable2DTextGlyphInfo_s0095_2390*)FUN_00952750((const Elem0C*)mGlyphInfos.mpBegin,
                                                            (const Elem0C*)mGlyphInfos.mpEnd,
                                                            (Elem0C*)p->mpGlyphsBegin);
  p->mpMemoryBuffer = pBuf;

  mParts.erase(mParts.mpBegin, mParts.mpEnd);
  mVerts.clear();
  mTextSpans.clear();
  mGlyphInfos.erase(mGlyphInfos.mpBegin, mGlyphInfos.mpEnd);
  return p;
}
}}  // namespace EA::UTFWin

// @ 0x00953430
namespace EA { namespace UTFWin {
Renderable2DMemoryManager::Renderable2DMemoryManager()
: mMutex(0, true), mSmallFree(), mLargeFree() {
  mpSmall = (CellData*)g_pMemPool_s0095_3430->LockedAlloc(0x10000, 0, 0, 0, 0, 0);
  mpSmallEnd = (CellData*)((char*)mpSmall + 0x10000);
  mSmallFree.reserve(0x200);
  for (CellData* p = mpSmall; p != mpSmallEnd; p = (CellData*)((char*)p + 0x80)) {
    CellData* temp = p;
    mSmallFree.push_back(temp);
  }

  mpLarge = (CellData*)g_pMemPool_s0095_3430->LockedAlloc(0x80000, 0, 0, 0, 0, 0);
  mpLargeEnd = (CellData*)((char*)mpLarge + 0x80000);
  ReserveInline(mLargeFree, 0x100);
  for (CellData* p = mpLarge; p != mpLargeEnd; p = (CellData*)((char*)p + 0x800)) {
    CellData* temp = p;
    mLargeFree.push_back(temp);
  }
}
}}  // namespace EA::UTFWin

// @ 0x009535a0
namespace EA { namespace UTFWin {
Renderable2DPool_s0095_3430::~Renderable2DPool_s0095_3430()
{
  const uint32_t n = (uint32_t)(mpEnd - mpBegin);
  for (uint32_t i = 0; i < n; ++i) mpBegin[i]->Release();
  FUN_011e0744(mpBegin, mpEnd, 0);
  mpEnd += -(mpEnd - mpBegin);
  if (mpBegin && ((int*)mpBegin)[-1]) EADelete(mpBegin);
}
}}  // namespace EA::UTFWin

// @ 0x00953600
namespace EA { namespace UTFWin {
void Draw2D_s0095_3430::DrawLine4(float x0, float y0, float x1, float y1)
{
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  mpRenderable->BeginPartInline(0, 0);

  x0 += g_half;
  y0 += g_half;
  x1 += g_half;
  y1 += g_half;

  AddVertexInline(mpRenderable, x0, y0, mColor);
  AddVertexInline(mpRenderable, x1, y1, mColor);
  mpRenderable->EndPart(2);
}
}}  // namespace EA::UTFWin

// @ 0x009537e0
namespace EA { namespace UTFWin {
void Draw2D_s0095_3430::DrawQuadUV(float x0, float y0, float x1, float y1)
{
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  if (mbClip) {
    if (x0 < mClipRect.m[0]) x0 = mClipRect.m[0];
    if (y0 < mClipRect.m[1]) y0 = mClipRect.m[1];
    if (mClipRect.m[2] < x1) x1 = mClipRect.m[2];
    if (mClipRect.m[3] < y1) y1 = mClipRect.m[3];
  }

  if (x1 - x0 <= 0.0f) return;
  if (y1 - y0 <= 0.0f) return;

  mpRenderable->BeginPart(2, 0);

  Vertex2D v;
  v.x = x0; v.y = y0; v.c = mColor; v.u = 0.0f; v.v = 0.0f;
  mpRenderable->Add(v);
  v.x = x1; v.y = y0; v.c = mColor; v.u = g_one; v.v = 0.0f;
  mpRenderable->Add(v);
  v.x = x1; v.y = y1; v.c = mColor; v.u = g_one; v.v = g_one;
  mpRenderable->Add(v);
  v.x = x0; v.y = y1; v.c = mColor; v.u = 0.0f; v.v = g_one;
  mpRenderable->Add(v);

  mpRenderable->EndPart(4);
}
}}  // namespace EA::UTFWin

// @ 0x00953eb0
namespace EA { namespace UTFWin {
void Draw2D_s0095_3430::FillGradH(const Rect& r, uint32_t color0, uint32_t color1)
{
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  float l = r.m[0];
  float t = r.m[1];
  float rr = r.m[2];
  float b = r.m[3];
  if (mbClip) {
    if (l < mClipRect.m[0]) l = mClipRect.m[0];
    if (t < mClipRect.m[1]) t = mClipRect.m[1];
    if (mClipRect.m[2] < rr) rr = mClipRect.m[2];
    if (mClipRect.m[3] < b) b = mClipRect.m[3];
    if (l >= rr) return;
    if (t >= b) return;
  }

  const uint32_t c0 = ModulateARGB32(mColor, color0);
  const uint32_t c1 = ModulateARGB32(mColor, color1);

  const int primType = 2;
  mpRenderable->BeginPartInline(primType, 0);
  AddVertexInline(mpRenderable, l, t, c0);
  AddVertexInline(mpRenderable, rr, t, c1);
  AddVertexInline(mpRenderable, rr, b, c1);
  AddVertexInline(mpRenderable, l, b, c0);
  mpRenderable->EndPart(4);
}
}}  // namespace EA::UTFWin

// @ 0x009541d0
namespace EA { namespace UTFWin {
void Draw2D_s0095_41d0::FillGradV(const RectT_s0095_41d0<float>& rect, uint32_t color0, uint32_t color1)
{
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
  AddVert(Point2D_s0095_41d0(left, top), c0);
  AddVert(Point2D_s0095_41d0(right, top), c0);
  AddVert(Point2D_s0095_41d0(right, bottom), c1);
  AddVert(Point2D_s0095_41d0(left, bottom), c1);
  mpRenderable->EndPart(4);
}
}}  // namespace EA::UTFWin

// @ 0x009544f0
namespace EA { namespace UTFWin {
void Draw2D_s0095_41d0::FillTriGrad(const Point2D_s0095_41d0& p0, uint32_t color0, const Point2D_s0095_41d0& p1, uint32_t color1, const Point2D_s0095_41d0& p2, uint32_t color2)
{
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  if (mbClip && !(mClipRect.Contains(p0) && mClipRect.Contains(p1) && mClipRect.Contains(p2))) {
    Drawing::Vertex2D_s0095_41d0 in[3];
    in[0].x = p0.x; in[0].y = p0.y; in[0].c = ModulateARGB32(mColor, color0); in[0].u = 0.0f; in[0].v = 0.0f;
    in[1].x = p1.x; in[1].y = p1.y; in[1].c = ModulateARGB32(mColor, color1); in[1].u = 0.0f; in[1].v = 0.0f;
    in[2].x = p2.x; in[2].y = p2.y; in[2].c = ModulateARGB32(mColor, color2); in[2].u = 0.0f; in[2].v = 0.0f;

    Drawing::Vertex2D_s0095_41d0 out[8];
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
}}  // namespace EA::UTFWin

// @ 0x00954a00
namespace EA { namespace UTFWin {
void Draw2D_s0095_4a00::FillQuadGrad(const Point2D& p0, uint32_t color0, const Point2D& p1, uint32_t color1, const Point2D& p2, uint32_t color2, const Point2D& p3, uint32_t color3)
{
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
        Drawing::Vertex2D_s0095_4a00 verts[3];
        Drawing::Vertex2D_s0095_4a00 clipped[8];
        SetVert(verts[0], p0, c0);
        SetVert(verts[1], p1, color1);
        SetVert(verts[2], p3, color3);
        AddClippedTri(verts, clipped);
      } else {
        mpRenderable->BeginPart(1, 0);
        Drawing::Vertex2D_s0095_4a00 v;
        SetVert(v, p0, c0);     mpRenderable->AddVertex(v);
        SetVert(v, p1, color1); mpRenderable->AddVertex(v);
        SetVert(v, p3, color3); mpRenderable->AddVertex(v);
        mpRenderable->EndPart(3);
      }

      if (bClip2) {
        Drawing::Vertex2D_s0095_4a00 verts[3];
        Drawing::Vertex2D_s0095_4a00 clipped[8];
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
}}  // namespace EA::UTFWin

// @ 0x009553e0
namespace EA { namespace UTFWin {
void Draw2D_s0095_4a00::RectBlit(const RectT_s0095_4a00<float>* pDst, const RectT_s0095_4a00<float>* pUV, Text::FontMetrics* pFont)
{
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

  Drawing::Vertex2D_s0095_4a00 v;
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
}}  // namespace EA::UTFWin

// @ 0x009557c0
namespace EA { namespace UTFWin {
IRenderable_s0095_4a00* Draw2D_s0095_4a00::Flush()
{
  if (!mpRenderable) return 0;
  IRenderable_s0095_4a00* p = mpRenderable->Flush();
  mpRenderable = 0;
  return p;
}
}}  // namespace EA::UTFWin

// @ 0x009558c0
namespace EA { namespace SP {
void CellData_s0095_4a00::FUN_009558c0()
{
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

  CellData_s0095_4a00* c = mpCell;
  if (c) {
    CellPool* pool = gCellPool;
    if (c >= (CellData_s0095_4a00*)pool->mRange1Begin && c < (CellData_s0095_4a00*)pool->mRange1End)
      pool->mFree1.push_back(c);
    else if (c >= (CellData_s0095_4a00*)pool->mRange2Begin && c < (CellData_s0095_4a00*)pool->mRange2End)
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
}}  // namespace EA::SP

// @ 0x00956870
void FUN_00956870(EA::SP::CellData_s0095_59a0* p)
{
  EA::SP::SimpleVectorCell_s0095_59a0* pList = EA::SP::gCellList;
  p->FUN_009558c0();
  pList->push_back(p);
  --pList->mCount;
}

// @ 0x009568c0
bool __cdecl InternalInit2DSystem(I2DSystem* pSystem)
{
    if (g_pI2DSystem == 0)
        g_pI2DSystem = pSystem;
    g_pI2DSystem->Init(1, 0);
    if (_InterlockedIncrement(&g_refCount2D) - 1 == 0) {
        if (g_pR2DMemoryManager == 0)
            g_pR2DMemoryManager = new("UTFWin/Renderable2DMemoryManager", 0, 0, 0, 0) R2DMemoryManager;
        if (g_pR2DPool == 0)
            g_pR2DPool = new("UTFWin/Renderable2DPool", 0, 0, 0, 0) R2DPool;
        SysInfo* pInfo = g_pI2DSystem->GetInfo(0, 0);
        g_154ecd4 = pInfo->f34;
        ObjectAddRef(g_uiImage);
        g_twoDState.f8 = 0.0f;
        g_twoDState.fc = 0.0f;
        g_twoDState.pDefault = g_154ecd0;
        g_twoDState.f4 = 0;
        g_twoDState.f10 = 1.0f;
        g_twoDState.f14 = 1.0f;
        g_twoDState.f18 = pInfo->f48;
        g_twoDState.f1c = pInfo->f48;
        g_twoDState.f20 = 0;
        InitFontSystem();
        if (g_pFontMgr != 0) {
            IFontObj* pFont = g_pFontMgr->Get(0x838293);
            if (pFont != 0) {
                if (!pFont->Init()) {
                    FUN_00952f30();
                    return false;
                }
            }
        }
    }
    return true;
}

// @ 0x00956a30
void __cdecl FUN_00956a30()
{
    if (_InterlockedDecrement(&g_refCount2D) == 0) {
        if (g_pFontMgr != 0) {
            IFontObj* pFont = g_pFontMgr->Get(0x838293);
            if (pFont != 0)
                pFont->Shutdown();
            if (g_pFontMgr != 0) {
                IFontMgr* pMgr = g_pFontMgr;
                g_pFontMgr = 0;
                pMgr->Release();
            }
        }
        FUN_00957530((int*)g_uiImage);
        FUN_00952f30();
        g_pI2DSystem->Shutdown();
        g_pI2DSystem = 0;
        if (g_pR2DPool) {
            delete g_pR2DPool;
            g_pR2DPool = 0;
        }
        if (g_pR2DMemoryManager) {
            delete g_pR2DMemoryManager;
            g_pR2DMemoryManager = 0;
        }
    }
}

// @ 0x00956af0
int __fastcall FUN_00956af0(void* self)
{
    int n = _InterlockedDecrement((volatile long*)((char*)self + 0x28));
    if (n == 0) {
        if (self != 0)
            ((VFn1i)Vt(self)[2])(self, 1);
    } else if (n == 1) {
        FUN_00956870(self);
    }
    return n;
}

// @ 0x00956b30
void GlyphRenderer::DrawText(float x, float y, const wchar_t* pText, int nLen, const void* pStyle, TextLayout* pLayout, void* pExtra)
{
    if (mpTarget == 0)
        mpTarget = (char*)this + 0x24;
    if (nLen == -1) {
        const wchar_t* p = pText;
        while (*p++ != 0)
            ;
        nLen = (int)(p - (pText + 1));
    }
    if (pStyle == 0)
        pStyle = g_defaultTextStyle;
    if (pLayout == 0)
        pLayout = &g_defaultTextLayout;
    GlyphFixedVec glyphs;
    glyphs.resize(nLen * 2);
    int n = pLayout->LayoutTextLine(pText, nLen, x, y, pStyle, glyphs.mpBegin, nLen * 2, pExtra);
    DrawGlyphs(glyphs.mpBegin, n, pStyle);
}

// @ 0x00956d60
void* UIRes::Dtor(unsigned char flags)
{
    void* self = this;
    *(void**)self = (void*)0x14404ac;
    FUN_009558c0();
    *(void**)self = (void*)0x13eb938;
    if (flags & 1)
        operator_delete__(self);
    return self;
}

// @ 0x00fb32b0
E40* Vec40::erase(E40* first, E40* last)
{
    E40* i = first;
    E40* j = last;
    while (j != end) {
        *i = *j;
        ++i;
        ++j;
    }
    int n = (int)(last - first);
    end = end + n;
    return first;
}
