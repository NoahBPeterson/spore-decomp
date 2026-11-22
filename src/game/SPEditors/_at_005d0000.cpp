// src/game/SPEditors/_at_005d0000.cpp
// Object file: SPEditors/_at_005d0000.obj.
//
// 2D curve and circle-intersection geometry helpers, the SPEditors token translator
// constructor, and the resource-loader / shared-object globals the SPEditors module uses.

#include "game/types.h"
#include <new>
#include <math.h>

// ---- 2D geometry helpers ---------------------------------------------------
// Flat 0x14-byte curve endpoint record iterated by CopyE20Range. PathIntersection in
// the shipping build; the fields are only reached through the pointers.
struct E20 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20() {}
  E20(const E20& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};
struct E20Iter {
  E20* mpNode;
  E20Iter() {}
  E20Iter(E20* p) : mpNode(p) {}
  E20& operator*() const { return *mpNode; }
  bool operator!=(const E20Iter& o) const { return mpNode != o.mpNode; }
  E20Iter& operator++() {
    ++mpNode;
    return *this;
  }
};
// A straight 2D curve segment (two endpoints plus a sweep angle) with param/arc evaluation.
struct Curve2D {
  char pad04[4];
  float x0;    // +0x4
  float y0;    // +0x8
  float x1;    // +0xc
  float y1;    // +0x10
  float angle; // +0x14
  void Lerp(float* out, float t);  // 005d5200
  void Arc(float* out, float t);   // 005d5160
};
// A circle (centre and radius) with a two-circle intersection test.
struct CircXY {
  float x, y, r;
  int Intersect(const CircXY* b, float* out);
};

// Debug-new used by the placement-new loop above.
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);  // 0x00f473a0

// ---- SPEditors token translator and module globals -------------------------
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380

namespace eastl {
// 0x10-byte wchar_t string: begin/end/capacity + a 4-byte allocator, the retail layout
// (eastl::basic_string<wchar_t> is the same 0x10 bytes). RangeInitialize/assign live in
// the shipping build; only the constructor and destructor are compiled here.
class string16_s005d_53e0 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  string16_s005d_53e0(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~string16_s005d_53e0() {
    if (((mpCapacity - mpBegin) > 1) && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);         // 0x00579a90
  string16_s005d_53e0& operator=(const string16_s005d_53e0& x);         // 0x0057cb60
  string16_s005d_53e0& operator=(const wchar_t* p);          // 0x005c3d90
  string16_s005d_53e0& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  string16_s005d_53e0& assign(const wchar_t* p) {
    const wchar_t* end = p;
    while (*end)
      ++end;
    return assign(p, p + (end - p));
  }
};

}  // namespace eastl

namespace SP {
// Ref-counted token-translator base: a vptr plus the refcount.
class cStringTokenTranslator_s005d_53e0 {
 public:
  cStringTokenTranslator_s005d_53e0();           // 0x006b5870
  virtual ~cStringTokenTranslator_s005d_53e0();  // 0x005725a0
  virtual int AddRef();
  virtual int Release();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result);
  int mRefCount;
};

// Translates editor tokens, keeping the old and new model names to substitute.
class cEditorsTokenTranslator_s005d_53e0 : public cStringTokenTranslator_s005d_53e0 {
 public:
  cEditorsTokenTranslator_s005d_53e0();
  virtual ~cEditorsTokenTranslator_s005d_53e0();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result);  // 0x005d5ef0 (SP::cEditorsTokenTranslator::TranslateToken)

  unsigned int mAmount;               // +0x8
  eastl::string16_s005d_53e0 mOldModelName;      // +0xc
  eastl::string16_s005d_53e0 mNewModelName;      // +0x1c
  const wchar_t* mUserName;           // +0x2c
  const wchar_t* mYear;               // +0x30
  const wchar_t* mMonth;              // +0x34
  const wchar_t* mDayOfMonth;         // +0x38
  const wchar_t* mTime;               // +0x3c
};
}  // namespace SP

// Loads a resource through the shared resource loader.
class cResourceLoader {
 public:
  void* Load(void* a, void* b, int c, int d, int e, int f, int g, int h);  // 0x00928a30
};
extern cResourceLoader* gResourceLoader;  // 0x016c8b44

// Reference-counted object released through Release() when the refcount reaches 0.
class cSharedObject {
 public:
  virtual ~cSharedObject();
  short mbRefCounted;  // +0x4
  short mRefCount;     // +0x6
  void Release() {
    if (mbRefCounted) {
      if (--mRefCount == 0)
        delete this;
    }
  }
};
extern cSharedObject* gSharedObject;  // 0x016e4184

// Returns the pack directory name for an index.
class cDataDirectory {
 public:
  const wchar_t* GetDirectoryName(int index);
};

// ---- items of slice s005d53e0_nosse begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags, const char* file,
                     int line);  // 0x00f473a0

struct Vector2 {
  float x, y;
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
class cPathShape;
struct PathIntersection {
  cPathShape* mpShape;   // +0x0
  cPathShape* mpOther;   // +0x4
  Vector2 mPosition;     // +0x8
  int mFlags;            // +0x10
};

namespace eastl {
template <typename T>
T* uninitialized_copy_ptr(T* first, T* last, T* result);  // 0x005d5120
template <typename T>
T* copy_backward(T* first, T* last, T* resultEnd);         // 0x00c50ad0

template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T* DoAllocate(unsigned int n) {
    return n ? (T*)operator new[](n * sizeof(T), "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFWin", 0xd1)
             : 0;
  }
  void DoFree(T* p) {
    if (p && ((int*)p)[-1] != 0)
      EASTL_allocator_deallocate(p);
  }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value);
};
}
// ---- items of slice s005d53e0_nosse end

// @ 0x005d5120
E20* CopyE20Range(E20* first, E20* last, E20* dest)
{
  for (; first != last; ++first, ++dest)
    if (dest) new ((void*)dest) E20(*first);
  return dest;
}

// @ 0x005d5160
void Curve2D::Arc(float* out, float t)
{
  float a = -(angle * t);
  float c = cosf(a);
  float s = sinf(a);
  float dyc = (y1 - y0) * c;
  float dxc = (x1 - x0) * c;
  float dxs = (x1 - x0) * s;
  out[1] = dxs + dyc + y0;
  out[0] = dxc - (y1 - y0) * s + x0;
}

// @ 0x005d51e0
// Length of the segment from (f[1], f[2]) to (f[3], f[4]) in a flat 0x14-byte endpoint record.
// The accumulator is kept in two steps (dx*dx, then + dy*dy) to match the retail x87 schedule.
float __fastcall SegmentLength(void* p)
{
  float* f = (float*)p;
  float dx = f[3] - f[1];
  float dy = f[4] - f[2];
  float lenSq = dx * dx;
  lenSq = lenSq + dy * dy;
  return sqrtf(lenSq);
}

// @ 0x005d5200
void Curve2D::Lerp(float* out, float t)
{
  out[0] = (x1 - x0) * t + x0;
  out[1] = (y1 - y0) * t + y0;
}

// @ 0x005d5250
int CircXY::Intersect(const CircXY* b, float* out)
{
  float dx = b->x - x;
  float dy = b->y - y;
  float dist2 = dx * dx + dy * dy;
  float dist = sqrtf(dist2);
  if (dist > r + b->r) return 0;
  if (fabsf(b->r - r) > dist) return 0;
  float t = (r * r - b->r * b->r + dist2) / (dist * 2.0f);
  float h = sqrtf(r * r - t * t);
  float inv = 1.0f / dist;
  float X1 = x + dx * t * inv;
  float Y1 = y + dy * t * inv;
  if (h < 1.5258789e-05f) {
    out[0] = X1;
    out[1] = Y1;
    return 1;
  }
  float ox = dy * h * inv;
  float oy = dx * h * inv;
  out[0] = X1 + ox;
  out[1] = Y1 - oy;
  out[2] = X1 - ox;
  out[3] = Y1 + oy;
  return 2;
}

// @ 0x005d5830
namespace eastl {
template <typename T> void sp_vector<T>::DoInsertValue(T* position, const T& value)
{
  if (mpEnd != mpCapacity) {
    const T* pValue = &value;
    if ((pValue >= position) && (pValue < mpEnd))
      ++pValue;
    ::new (mpEnd) T(*(mpEnd - 1));
    copy_backward(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
    const unsigned int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    T* const pNewData = DoAllocate(nNewSize);
    T* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
    ::new (pNewEnd) T(value);
    pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
    DoFree(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
  }
}
}  // namespace eastl

// @ 0x005d5970
namespace eastl {
template <typename T> void sp_vector<T>::push_back(const T& value)
{
  if (mpEnd < mpCapacity)
    ::new (mpEnd++) T(value);
  else
    DoInsertValue(mpEnd, value);
}

template class sp_vector<PathIntersection>;
}  // namespace eastl

// @ 0x005d5e40
namespace SP {
cEditorsTokenTranslator_s005d_53e0::cEditorsTokenTranslator_s005d_53e0()
: mAmount(0), mOldModelName(L"UnsetName"), mNewModelName(L"UnsetName") {}
}  // namespace SP

// @ 0x005d60f0
void* LoadResource(void* a, void* b)
{
  return gResourceLoader->Load(a, b, 0, 0, 0, 0, 0, 0);
}

// @ 0x005d6120
void SetSharedObject(cSharedObject* object)
{
  if (gSharedObject)
    gSharedObject->Release();
  gSharedObject = object;
}

// @ 0x005d6170
const wchar_t* cDataDirectory::GetDirectoryName(int index)
{
  return index == 0 ? L"data" : 0;
}
