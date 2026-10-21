// Slice s00952390 -- EA::UTFWin Renderable2D / Draw2D support helpers
// (retail 0x00952390..0x00953424).
//
// 0x00952390  Draw2D::DrawTextSpan(...)                     (7 stack args, ret 0x1c)
// 0x00952720  glyph-span emitter (this + source struct)
// 0x00952750  copy loop, 0x0c-byte elements (returns end)
// 0x00952800  resource holder dtor (BindPool::Free x2, two sized deletes, ~Mutex)
// 0x00952860  Renderable2DPool::AcquireRenderable
// 0x009528d0  part -> skin-vertex emit (this + out struct + work arg)
// 0x00952a60  AutoOSGlobalPtr<...>::Create
// 0x00952aa0  Renderable2DBuilder::Renderable2DBuilder()
// 0x00952b30  Vertex2DVector::DoInsertFromIterator
// 0x00952d10  Vec40Vector::DoInsertValues
// 0x00952ee0  TextSpanVector::push_back
// 0x00952f30  font-cache shutdown
// 0x00952f80  Renderable2DBuilder::~Renderable2DBuilder
// 0x009531a0  Renderable2DBuilder::BeginPart
// 0x00953220  Renderable2DBuilder::Build
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <intrin.h>

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------------------------------------
// allocators / raw-copy helpers (all out of line in the original)
// ---------------------------------------------------------------------------------------------
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

struct Mutex {
  uint32_t mData[10];  // CRITICAL_SECTION + init flag (0x28)
  ~Mutex();            // 0x00922130
};

struct MemPool {
  void* Alloc(uint32_t size);  // 0x00951d60 (thiscall, ret 4)
};
extern MemPool* g_pMemPool;  // 0x0166aac4

// ---------------------------------------------------------------------------------------------
// UTFWin renderable types
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace UTFWin {

class Image { public:
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};

struct Font {
  virtual void v0();        // +0x0
  virtual void v1();        // +0x4
  virtual void v2();        // +0x8
  virtual void Release();   // +0xc
};

struct Vertex2D {  // 0x14
  float x, y;
  uint32_t c;
  float u, v;
};

struct Renderable2DPart {  // 0x0c
  Image* mpImage;    // +0x0
  int mPrimType;     // +0x4
  uint32_t mCount;   // +0x8
  ~Renderable2DPart() {
    if (mpImage) mpImage->Release();
  }
};

struct Renderable2DTextSpan {  // 0x14
  Font* mpFont;         // +0x0
  uint32_t mVertStart;  // +0x4
  uint32_t mGlyphStart; // +0x8
  uint32_t mGlyphCount; // +0xc
  uint32_t mCacheGen;   // +0x10
  ~Renderable2DTextSpan() {
    if (mpFont) mpFont->Release();
  }
};

struct Renderable2DTextGlyphInfo {  // 0x0c
  uint16_t mGlyphId;  // +0x0
  uint16_t mPad;      // +0x2
  float mU;           // +0x4
  float mV;           // +0x8
};

// The retail eastl::fixed_vector: three vector pointers, a spare slot, the inline pool pointer,
// another spare slot and finally the inline buffer at +0x18.
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

struct Vertex2DVector : FixedVector<Vertex2D, 600> {
  void DoInsertFromIterator(Vertex2D* position, const Vertex2D* first, const Vertex2D* last,
                            int tag);  // 0x00952b30
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    copy_vec20(mpEnd, mpEnd, mpBegin);
    mpEnd = (Vertex2D*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Vertex2D));
  }
};

struct PartVector : FixedVector<Renderable2DPart, 16> {
  void DoInsertValue(Renderable2DPart* position, const Renderable2DPart* value);  // 0x00a27910
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    for (ptrdiff_t i = 0; i < n; ++i)
      if (mpBegin[i].mpImage) mpBegin[i].mpImage->Release();
    mpEnd = (Renderable2DPart*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DPart));
  }
  Renderable2DPart& push_back() {
    Renderable2DPart temp;
    if (mpEnd < mpCapacity)
      ++mpEnd;
    else
      DoInsertValue(mpEnd, &temp);
    return *(mpEnd - 1);
  }
};

struct TextSpanVector : FixedVector<Renderable2DTextSpan, 30> {
  void push_back(const Renderable2DTextSpan& value);                                // 0x00952ee0
  void DoInsertValue(Renderable2DTextSpan* position, const Renderable2DTextSpan* value); // 0x00884d90
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    for (ptrdiff_t i = 0; i < n; ++i)
      if (mpBegin[i].mpFont) mpBegin[i].mpFont->Release();
    mpEnd = (Renderable2DTextSpan*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DTextSpan));
  }
};

struct GlyphInfoVector : FixedVector<Renderable2DTextGlyphInfo, 200> {
  void DoInsertValue(Renderable2DTextGlyphInfo* position,
                     const Renderable2DTextGlyphInfo* value);
  void clear() {
    const ptrdiff_t n = mpEnd - mpBegin;
    mpEnd = (Renderable2DTextGlyphInfo*)((char*)mpEnd + n * (ptrdiff_t)sizeof(Renderable2DTextGlyphInfo));
  }
};

class Renderable2D { public:
  virtual void AddRef();                     // +0x0
  Renderable2DPart* mpPartsBegin;            // +0x4
  Renderable2DPart* mpPartsEnd;              // +0x8
  Vertex2D* mpVertsBegin;                    // +0xc
  Vertex2D* mpVertsEnd;                      // +0x10
  Renderable2DTextSpan* mpSpansBegin;        // +0x14
  Renderable2DTextSpan* mpSpansEnd;          // +0x18
  Renderable2DTextGlyphInfo* mpGlyphsBegin;  // +0x1c
  Renderable2DTextGlyphInfo* mpGlyphsEnd;    // +0x20
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

class Renderable2DPool { public:
  Renderable2D** mpBegin;     // +0x0
  Renderable2D** mpEnd;       // +0x4
  Renderable2D** mpCapacity;  // +0x8
  int mPad0;                  // +0xc
  int mPad1;                  // +0x10
  int mCount;                 // +0x14
  Renderable2D* AcquireRenderable();  // 0x00952860
};
extern Renderable2DPool* g_pRenderable2DPool;  // 0x0166aac0

class Renderable2DBuilder { public:
  Vertex2DVector mVerts;                      // +0x0
  PartVector mParts;                          // +0x2ef8
  TextSpanVector mTextSpans;                  // +0x2fd0
  GlyphInfoVector mGlyphInfos;                // +0x3240

  Renderable2DBuilder();                      // 0x00952aa0
  ~Renderable2DBuilder();                     // 0x00952f80
  void BeginPart(int primType, Image* pImage);  // 0x009531a0
  Renderable2D* Build();                      // 0x00953220
};

uint32_t roundUp8(uint32_t n) { return (n + 7u) & ~7u; }

}  // namespace UTFWin
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// 0x00952720  glyph-span emitter: forwards a span source to the drawing context (vtable +0x30)
// ---------------------------------------------------------------------------------------------
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

// @ 0x00952720
void DrawSpanCtx::FUN_00952720(const SpanSource* p) {
  DrawSpan(p->mpBegin, p->mpFont, (int)(p->mpEnd - p->mpBegin));
}

// ---------------------------------------------------------------------------------------------
// 0x00952750  forward copy, 0x0c-byte elements, returns the destination end
// ---------------------------------------------------------------------------------------------
struct Elem0C {
  uint32_t m0, m4, m8;
};

// @ 0x00952750
Elem0C* FUN_00952750(const Elem0C* first, const Elem0C* last, Elem0C* dst) {
  if (first == last) return dst;
  ptrdiff_t off = (const char*)first - (const char*)dst;
  do {
    if (dst) *dst = *(const Elem0C*)((const char*)dst + off);
    dst = (Elem0C*)((const char*)dst + 0xc);
  } while ((const char*)dst + off != (const char*)last);
  return dst;
}

// ---------------------------------------------------------------------------------------------
// 0x00952800  resource holder dtor
// ---------------------------------------------------------------------------------------------
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

// @ 0x00952800
void ResourceHolder::Destroy() {
  g_pBindPool->Free(mpElem30);
  g_pBindPool->Free(mpElem38);
  if (mpBuf54 && ((int*)mpBuf54)[-1]) EADelete(mpBuf54);
  if (mpBuf40 && ((int*)mpBuf40)[-1]) EADelete(mpBuf40);
  ((Mutex*)this)->~Mutex();
}

// ---------------------------------------------------------------------------------------------
// 0x00952860  Renderable2DPool::AcquireRenderable
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace UTFWin {

// @ 0x00952860
Renderable2D* Renderable2DPool::AcquireRenderable() {
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

}  // namespace UTFWin
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// 0x009528d0  emit the vertices for the next queued part (skin) into an output descriptor
// ---------------------------------------------------------------------------------------------
struct SkinPart {
  EA::UTFWin::Image* mpImage;  // +0x0
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
  EA::UTFWin::Image* mpImage;    // +0x10
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

// @ 0x009528d0
bool SkinBuilder::FUN_009528d0(SkinOut* out, int arg) {
  SkinPart* pPart = mpPartsCur;
  if (pPart == mpPartsEnd) return false;

  EA::UTFWin::Image* pImage = pPart->mpImage;
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

// ---------------------------------------------------------------------------------------------
// 0x00952a60  AutoOSGlobalPtr<...>::Create
// ---------------------------------------------------------------------------------------------
// @ 0x00952a60
void* FUN_00952a60() {
  void* p = EANew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
  if (!p) return 0;
  ((uint32_t*)p)[1] = 0;
  ((uint32_t*)p)[0] = 0;
  ((uint32_t*)p)[4] = 0;
  return p;
}

// ---------------------------------------------------------------------------------------------
// 0x00952aa0  Renderable2DBuilder::Renderable2DBuilder
// ---------------------------------------------------------------------------------------------
// @ 0x00952aa0
EA::UTFWin::Renderable2DBuilder::Renderable2DBuilder() {}

// ---------------------------------------------------------------------------------------------
// 0x00952b30  Vertex2DVector::DoInsertFromIterator
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace UTFWin {

// @ 0x00952b30
void Vertex2DVector::DoInsertFromIterator(Vertex2D* position, const Vertex2D* first,
                                          const Vertex2D* last, int /*tag*/) {
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

}  // namespace UTFWin
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// 0x00952d10  Vec40Vector::DoInsertValues
// ---------------------------------------------------------------------------------------------
struct Rec40 {
  uint32_t m[10];  // 0x28
};

struct Vec40Vector {
  Rec40* mpBegin;     // +0x0
  Rec40* mpEnd;       // +0x4
  Rec40* mpCapacity;  // +0x8
  int mPad0;          // +0xc
  Rec40* mpPool;      // +0x10
  void DoInsertValues(Rec40* position, uint32_t n, const Rec40& value);  // 0x00952d10
};

// @ 0x00952d10
void Vec40Vector::DoInsertValues(Rec40* position, uint32_t n, const Rec40& value) {
  if (n > (uint32_t)(mpCapacity - mpEnd)) {
    uint32_t oldCapacity = (uint32_t)(mpEnd - mpBegin);
    uint32_t newCapacity = oldCapacity * 2;
    if (oldCapacity == 0) newCapacity = 1;
    if (newCapacity < oldCapacity + n) newCapacity = oldCapacity + n;
    Rec40* pNew =
        newCapacity
            ? (Rec40*)EAAllocate(newCapacity * 0x28, "EASTL", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                                 "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                 0xd1)
            : 0;
    Rec40* p1 = (Rec40*)uninit_copy40(mpBegin, position, pNew);
    fill_rec40(p1, n, &value);
    Rec40* p2 = (Rec40*)uninit_copy40(position, mpEnd, p1 + n);
    if (mpBegin && mpBegin != mpPool) EADelete(mpBegin);
    mpBegin = pNew;
    mpEnd = p2;
    mpCapacity = pNew + newCapacity;
    return;
  }
  if (n == 0) return;

  Rec40 local;
  memmove_0fb3210(&local, &value, 0x28);
  uint32_t elemsAfter = (uint32_t)(mpEnd - position);
  if (n < elemsAfter) {
    Rec40* pEnd = mpEnd;
    Rec40* pShifted = pEnd - n;
    void* out = 0;
    copy_vec40b(&out, pShifted, pEnd, pEnd, position);
    mpEnd += n;
    memmove_0fb3210(position, pShifted, (uint32_t)(pEnd - position) * 0x28);
    copy_rec40(position, position, &local);
    return;
  }
  Rec40* pEnd = mpEnd;
  fill_rec40(pEnd, n - elemsAfter, &local);
  mpEnd += n - elemsAfter;
  void* out = 0;
  copy_vec40b(&out, position, pEnd, mpEnd, position);
  mpEnd += elemsAfter;
  fill_rec40(position, elemsAfter, &local);
}

// ---------------------------------------------------------------------------------------------
// 0x00952ee0  TextSpanVector::push_back
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace UTFWin {

// @ 0x00952ee0
void TextSpanVector::push_back(const Renderable2DTextSpan& value) {
  if (mpEnd < mpCapacity) {
    Renderable2DTextSpan* p = mpEnd++;
    if (p) *p = value;
  } else {
    DoInsertValue(mpEnd, &value);
  }
}

// ---------------------------------------------------------------------------------------------
// 0x00952f80  Renderable2DBuilder::~Renderable2DBuilder
// ---------------------------------------------------------------------------------------------
// @ 0x00952f80
Renderable2DBuilder::~Renderable2DBuilder() {
  mVerts.clear();
  mParts.clear();
  mTextSpans.clear();
  mGlyphInfos.clear();
}

// ---------------------------------------------------------------------------------------------
// 0x009531a0  Renderable2DBuilder::BeginPart
// ---------------------------------------------------------------------------------------------
// @ 0x009531a0
void Renderable2DBuilder::BeginPart(int primType, Image* pImage) {
  if (mParts.mpBegin != mParts.mpEnd) {
    Renderable2DPart* pLast = mParts.mpEnd - 1;
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
    mParts.DoInsertValue(mParts.mpEnd, (const Renderable2DPart*)&raw);
  }
  Renderable2DPart* part = mParts.mpEnd - 1;
  part->mpImage = pImage;
  part->mPrimType = primType;
  part->mCount = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00953220  Renderable2DBuilder::Build
// ---------------------------------------------------------------------------------------------
// @ 0x00953220
Renderable2D* Renderable2DBuilder::Build() {
  uint32_t offVerts = roundUp8((uint32_t)(mParts.mpEnd - mParts.mpBegin) * 0xc);
  uint32_t offSpans = roundUp8(offVerts + (uint32_t)(mVerts.mpEnd - mVerts.mpBegin) * 0x14);
  uint32_t offGlyphs = roundUp8(offSpans + (uint32_t)(mTextSpans.mpEnd - mTextSpans.mpBegin) * 0x14);
  uint32_t total = offGlyphs + (uint32_t)(mGlyphInfos.mpEnd - mGlyphInfos.mpBegin) * 0xc;

  Renderable2D* p = g_pRenderable2DPool->AcquireRenderable();
  char* pBuf = (char*)g_pMemPool->Alloc(total);

  p->mpPartsBegin = (Renderable2DPart*)pBuf;
  p->mpPartsEnd = (Renderable2DPart*)FUN_00952750((const Elem0C*)mParts.mpBegin,
                                                  (const Elem0C*)mParts.mpEnd, (Elem0C*)pBuf);
  p->mpVertsBegin = (Vertex2D*)(pBuf + offVerts);
  p->mpVertsEnd = (Vertex2D*)uninit_copy20(mVerts.mpBegin, mVerts.mpEnd, p->mpVertsBegin);
  p->mpSpansBegin = (Renderable2DTextSpan*)(pBuf + offSpans);
  p->mpSpansEnd =
      (Renderable2DTextSpan*)uninit_copy20(mTextSpans.mpBegin, mTextSpans.mpEnd, p->mpSpansBegin);
  p->mpGlyphsBegin = (Renderable2DTextGlyphInfo*)(pBuf + offGlyphs);
  p->mpGlyphsEnd = (Renderable2DTextGlyphInfo*)FUN_00952750((const Elem0C*)mGlyphInfos.mpBegin,
                                                            (const Elem0C*)mGlyphInfos.mpEnd,
                                                            (Elem0C*)p->mpGlyphsBegin);
  p->mpMemoryBuffer = pBuf;

  mParts.erase(mParts.mpBegin, mParts.mpEnd);
  mVerts.clear();
  mTextSpans.clear();
  mGlyphInfos.erase(mGlyphInfos.mpBegin, mGlyphInfos.mpEnd);
  return p;
}

}  // namespace UTFWin
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// 0x00952f30  font cache shutdown
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace Text {
struct FontTree {
  void DoNukeSubtree(void* pNode);  // 0x0088fda0
};
}  // namespace Text
}  // namespace EA

extern bool g_fontCacheActive;      // 0x0166aabc
extern EA::Text::FontTree g_fontTree;  // 0x0166ab0c
extern void* g_fontHead;            // 0x0166ab10
extern void* g_fontTail;            // 0x0166ab14
extern void* g_fontRoot;            // 0x0166ab18
extern uint8_t g_fontFlag;          // 0x0166ab1c
extern uint32_t g_fontCount;        // 0x0166ab20

// @ 0x00952f30
void FUN_00952f30() {
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

// ---------------------------------------------------------------------------------------------
// 0x00952390  Draw2D::DrawTextSpan
// ---------------------------------------------------------------------------------------------
// Reconstructed call sequence.  Several callees are text-layout internals whose signatures are
// inferred from the call sites only.
struct TextRun {
  void* m0;  // +0x0
};
struct TextLayoutObj {
  char pad[0x248];
  uint32_t mKind;  // +0x248
  char pad2[4];
  uint32_t mFlag;  // +0x250
};
struct TextStyle228 {
  char pad[0x228];
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
float FUN_011e0906(double);                             // 0x011e0906

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

// @ 0x00952390
void FUN_00952390(Draw2DLike* self, const float* pRect, const uint16_t* pText, int count,
                  void* pStyle, int halign, int valign) {
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
