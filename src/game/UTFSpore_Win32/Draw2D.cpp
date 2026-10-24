// src/game/UTFSpore_Win32/Draw2D.cpp -- migrated from slice(s) s009568c0, s00954a00, s009515e0, s00950bb0 by tools/migrate/rewrite.py
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
struct RectT_s0095_4a00 {
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
struct Image_s0095_4a00 {
  virtual void AddRef();
  virtual void Release();
};
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
struct Renderable2DBuilder_s0095_4a00 {
  Vertex2DVector mVerts;  // +0x0 (fixed_vector<Vertex2D,600>)
  uint32_t pad0[(0x2ef8 - 0xc) / 4];
  PartVector mParts;  // +0x2ef8 (fixed_vector<Renderable2DPart,16>)

  void AddVertex(const Drawing::Vertex2D_s0095_4a00& v);         // 0x00952ee0
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
};
}
}
// ---- items of slice s00954a00 end

// ---- items of slice s009568c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern long g_refCount2D;            // 0x166aac8
extern int    g_154ecd4;             // 0x154ecd4
extern char   g_uiImage[0x40];       // 0x166aacc
extern char   g_154ecd0[];           // 0x154ecd0
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);        // 0xf473a0 (EA allocator, name/flags form)
void __cdecl InitFontSystem();                            // 0x951c60
void __cdecl FUN_00956870(void*);
void __cdecl FUN_00952f30();
void __fastcall ObjectAddRef(void*);                       // 0x95f990
struct SysInfo { char pad0[0x34]; int f34; char pad38[0x10]; int f48; };
struct I2DSystem {
    virtual void v0();
    virtual void v1();
    virtual void Init(int, int);                 // +8
    virtual void Shutdown();                     // +0xc
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual SysInfo* GetInfo(int, int);          // +0x30
};
struct IFontObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
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
// ---- items of slice s009568c0 end

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
