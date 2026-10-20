// Slice s00953430 -- EA::UTFWin Draw2D helpers (retail 0x00953430..0x009541f0).
//
// 0x00953430  Renderable2DMemoryManager::Renderable2DMemoryManager()
// 0x009535a0  Renderable2DPool::~Renderable2DPool
// 0x00953600  Draw2D fill helper (two vertices in the current part)
// 0x009537e0  Draw2D textured-rect helper (four vertices)
// 0x009539c0  Draw2D::FillQuad
// 0x00953eb0  Draw2D::FillGradH
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------------------------
// allocators / out-of-line helpers (addresses embedded in the symbol names)
// ---------------------------------------------------------------------------------------------
void* EAAllocate(uint32_t size, const char* name, int p3, int p4, const char* file, int line);  // 0x00f473a0
void EADelete(void* p);                                                                         // 0x00f47380
void FUN_011e0744(void* dst, const void* src, uint32_t bytes);                                  // 0x011e0744
struct MemPool {
  void* LockedAlloc(uint32_t size, int, int, int, int, int);  // 0x009289f0
};
uint32_t __cdecl ModulateARGB32(uint32_t a, uint32_t b);                                        // 0x0095f8c0
uint32_t __cdecl ClipPolygon2D(const void* pRect, const void* pIn, uint32_t nIn, void* pOut,
                               uint32_t nOutMax);                                               // 0x00917e10

extern MemPool* g_pMemPool;   // 0x016c8b44
extern float g_half;       // 0x01471064
extern float g_one;        // 0x01485720

namespace EA {
namespace Thread {
struct Mutex {
  uint32_t mData[10];  // 0x28
  Mutex(const void*, bool);  // 0x009222a0
};
}  // namespace Thread
}  // namespace EA

namespace EA {
namespace UTFWin {

struct Image {
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};

struct Vertex2D {  // 0x14
  float x, y;
  uint32_t c;
  float u, v;
};

struct Point2D {  // 0x8
  float x, y;
};

struct Renderable2DPart {  // 0x0c
  Image* mpImage;   // +0x0
  int mPrimType;    // +0x4
  uint32_t mCount;  // +0x8
};

// The retail eastl::fixed_vector: begin/end/capacity, two spare words, the inline pool pointer
// and the inline buffer at +0x18.
template <class T, int N>
struct FixedVector {
  T* mpBegin;                            // +0x00
  T* mpEnd;                              // +0x04
  T* mpCapacity;                         // +0x08
  int mPad0;                             // +0x0c
  T* mpPool;                             // +0x10
  int mPad1;                             // +0x14
  unsigned char mBuffer[N * sizeof(T)];  // +0x18

  T* buffer() { return (T*)mBuffer; }
  FixedVector() {
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

struct Vertex2DVector : FixedVector<Vertex2D, 600> {
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

struct PartVector : FixedVector<Renderable2DPart, 16> {
  void DoInsertValue(Renderable2DPart* position, const Renderable2DPart* value);  // 0x00a27910
  Renderable2DPart& push_back() {
    Renderable2DPart temp;
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else
      DoInsertValue(mpEnd, &temp);
    return *(mpEnd - 1);
  }
};

struct Renderable2DBuilder {
  Vertex2DVector mVerts;  // +0x0000
  PartVector mParts;      // +0x2ef8

  void BeginPart(int primType, Image* pImage);  // 0x009531a0
  void Add(const Vertex2D& value);              // 0x00952ee0

  __forceinline void BeginPartInline(int primType, Image* pImage) {
    if (mParts.mpBegin != mParts.mpEnd) {
      Renderable2DPart* pLast = mParts.mpEnd - 1;
      if (pLast->mPrimType == primType && pLast->mpImage == pImage) return;
    }
    if (pImage) pImage->AddRef();
    mParts.push_back();
    Renderable2DPart* part = mParts.mpEnd - 1;
    part->mpImage = pImage;
    part->mPrimType = primType;
    part->mCount = 0;
  }

  __forceinline void EndPart(uint32_t count) {
    if ((mParts.back().mCount += count) == 0) {
      Image* pImage = mParts.back().mpImage;
      if (pImage) pImage->Release();
      mParts.pop_back();
    }
  }
};

struct Rect {  // 0x10
  float m[4];
};

struct Draw2D {
  void* mpVtable;                      // +0x00
  Renderable2DBuilder* mpRenderable;   // +0x04
  void* mpWindowMgr;                   // +0x08
  uint32_t mColor;                     // +0x0c
  bool mbClip;                         // +0x10
  char mPad11[3];                      // +0x11
  Rect mClipRect;                      // +0x14
  Renderable2DBuilder mDefaultRenderable;  // +0x24

  void DrawLine4(float x0, float y0, float x1, float y1);   // 0x00953600
  void DrawQuadUV(float x0, float y0, float x1, float y1);  // 0x009537e0
  void FillQuad(const Point2D* p0, const Point2D* p1, const Point2D* p2, const Point2D* p3);
  void FillGradH(const Rect& r, uint32_t color0, uint32_t color1);
};

__forceinline void AddVertexInline(Renderable2DBuilder* pBuilder, float x, float y,
                                    uint32_t c) {
  Vertex2D v;
  v.x = x;
  v.y = y;
  v.c = c;
  v.u = 0.0f;
  v.v = 0.0f;
  pBuilder->mVerts.push_back(v);
}

__forceinline void AddVertexInline(Renderable2DBuilder* pBuilder, const Point2D& p,
                                   uint32_t c) {
  AddVertexInline(pBuilder, p.x, p.y, c);
}

// ---------------------------------------------------------------------------------------------
// 0x00953430  Renderable2DMemoryManager::Renderable2DMemoryManager()
// ---------------------------------------------------------------------------------------------
struct CellData {  // 0x80
  uint32_t m[0x20];
};

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

// 0x009529d0 is the out-of-line CellDataVector::reserve; the second reserve in the constructor
// was inlined by the original compiler, so it is spelled out here.
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

struct Renderable2DMemoryManager {
  EA::Thread::Mutex mMutex;  // +0x00
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

// @ 0x00953430
Renderable2DMemoryManager::Renderable2DMemoryManager()
    : mMutex(0, true), mSmallFree(), mLargeFree() {
  mpSmall = (CellData*)g_pMemPool->LockedAlloc(0x10000, 0, 0, 0, 0, 0);
  mpSmallEnd = (CellData*)((char*)mpSmall + 0x10000);
  mSmallFree.reserve(0x200);
  for (CellData* p = mpSmall; p != mpSmallEnd; p = (CellData*)((char*)p + 0x80)) {
    CellData* temp = p;
    mSmallFree.push_back(temp);
  }

  mpLarge = (CellData*)g_pMemPool->LockedAlloc(0x80000, 0, 0, 0, 0, 0);
  mpLargeEnd = (CellData*)((char*)mpLarge + 0x80000);
  ReserveInline(mLargeFree, 0x100);
  for (CellData* p = mpLarge; p != mpLargeEnd; p = (CellData*)((char*)p + 0x800)) {
    CellData* temp = p;
    mLargeFree.push_back(temp);
  }
}

// ---------------------------------------------------------------------------------------------
// 0x009535a0  Renderable2DPool::~Renderable2DPool
// ---------------------------------------------------------------------------------------------
struct Renderable2D {
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};

struct Renderable2DPool {
  Renderable2D** mpBegin;     // +0x0
  Renderable2D** mpEnd;       // +0x4
  Renderable2D** mpCapacity;  // +0x8
  int mPad0;                  // +0xc
  int mPad1;                  // +0x10
  int mCount;                 // +0x14
  ~Renderable2DPool();
};

// @ 0x009535a0
Renderable2DPool::~Renderable2DPool() {
  const uint32_t n = (uint32_t)(mpEnd - mpBegin);
  for (uint32_t i = 0; i < n; ++i) mpBegin[i]->Release();
  FUN_011e0744(mpBegin, mpEnd, 0);
  mpEnd += -(mpEnd - mpBegin);
  if (mpBegin && ((int*)mpBegin)[-1]) EADelete(mpBegin);
}

// ---------------------------------------------------------------------------------------------
// 0x00953600  fill helper: a two-vertex part
// ---------------------------------------------------------------------------------------------
// @ 0x00953600
void Draw2D::DrawLine4(float x0, float y0, float x1, float y1) {
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

// ---------------------------------------------------------------------------------------------
// 0x009537e0  textured-rect helper: four vertices with 0/1 texture coordinates
// ---------------------------------------------------------------------------------------------
// @ 0x009537e0
void Draw2D::DrawQuadUV(float x0, float y0, float x1, float y1) {
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

// ---------------------------------------------------------------------------------------------
// 0x009539c0  Draw2D::FillQuad
// ---------------------------------------------------------------------------------------------
__forceinline void SetVert(Vertex2D& v, const Point2D& p, uint32_t c) {
  v.x = p.x;
  v.y = p.y;
  v.c = c;
  v.u = 0.0f;
  v.v = 0.0f;
}

// @ 0x009539c0
void Draw2D::FillQuad(const Point2D* p0, const Point2D* p1, const Point2D* p2,
                      const Point2D* p3) {
  if (!mpRenderable) mpRenderable = &mDefaultRenderable;

  bool bInside = true;
  if (mbClip) {
    const Rect& r = mClipRect;
    bInside = p0->x >= r.m[0] && p0->y >= r.m[1] && r.m[2] > p0->x && r.m[3] > p0->y &&
              p1->x >= r.m[0] && p1->y >= r.m[1] && r.m[2] > p1->x && r.m[3] > p1->y &&
              p2->x >= r.m[0] && p2->y >= r.m[1] && r.m[2] > p2->x && r.m[3] > p2->y &&
              p3->x >= r.m[0] && p3->y >= r.m[1] && r.m[2] > p3->x && r.m[3] > p3->y;
  }

  if (bInside) {
    mpRenderable->BeginPart(2, 0);
    AddVertexInline(mpRenderable, *p0, mColor);
    AddVertexInline(mpRenderable, *p1, mColor);
    AddVertexInline(mpRenderable, *p2, mColor);
    AddVertexInline(mpRenderable, *p3, mColor);
    mpRenderable->EndPart(4);
    return;
  }

  Vertex2D verts[4];
  Vertex2D clipped[8];
  SetVert(verts[0], *p0, mColor);
  SetVert(verts[1], *p1, mColor);
  SetVert(verts[2], *p2, mColor);
  SetVert(verts[3], *p3, mColor);

  const uint32_t n = ClipPolygon2D(&mClipRect, verts, 4, clipped, 8);
  if (n == 0) return;

  mpRenderable->BeginPart(1, 0);
  for (uint32_t i = 2; i < n; ++i) {
    mpRenderable->mVerts.push_back(clipped[0]);
    mpRenderable->mVerts.push_back(clipped[i - 1]);
    mpRenderable->mVerts.push_back(clipped[i]);
  }
  mpRenderable->EndPart(n * 3 - 6);
}

// ---------------------------------------------------------------------------------------------
// 0x00953eb0  Draw2D::FillGradH
// ---------------------------------------------------------------------------------------------
// @ 0x00953eb0
void Draw2D::FillGradH(const Rect& r, uint32_t color0, uint32_t color1) {
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

}  // namespace UTFWin
}  // namespace EA
