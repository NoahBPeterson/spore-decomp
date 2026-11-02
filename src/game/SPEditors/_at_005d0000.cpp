// src/game/SPEditors/_at_005d0000.cpp -- migrated from slice(s) s005d53e0, s005d4630 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <math.h>
#include <xmmintrin.h>
#include "SP/cEditorsTokenTranslator.h"
#include "SP/cStringTokenTranslator.h"

// ---- items of slice s005d4630 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct CircXY {
  float x, y, r;
  int Intersect(const CircXY* b, float* out);
};
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
// ---- items of slice s005d4630 end

// ---- items of slice s005d53e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
namespace eastl {
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
};  // namespace eastl
}
namespace SP {
class cStringTokenTranslator_s005d_53e0 {
 public:
  cStringTokenTranslator_s005d_53e0();           // 0x006b5870
  virtual ~cStringTokenTranslator_s005d_53e0();  // 0x005725a0
  virtual int AddRef();
  virtual int Release();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16_s005d_53e0& result);
  int mRefCount;
};
}
namespace SP {
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
}
class cResourceLoader {
 public:
  void* Load(void* a, void* b, int c, int d, int e, int f, int g, int h);  // 0x00928a30
};
extern cResourceLoader* gResourceLoader;  // 0x016c8b44
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
class cDataDirectory {
 public:
  const wchar_t* GetDirectoryName(int index);
};
// ---- items of slice s005d53e0 end

// @ 0x005d5120
E20* CopyE20Range(E20Iter first, E20Iter last, E20Iter dest)
{
  for (; first != last; ++first, ++dest)
    if (&*dest) new ((void*)&*dest) E20(*first);
  return dest.mpNode;
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
float __fastcall SegmentLength(void* p)
{
  float* f = (float*)p;
  float dx = f[3] - f[1];
  float dy = f[4] - f[2];
  float sum = dx * dx;
  sum = sum + dy * dy;
  return sqrtf(sum);
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
