// src/game/UTFSpore_Win32/Animation.cpp -- migrated from slice(s) s009515e0, s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Animation.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include <intrin.h>
#include <string.h>
#include <new>

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct CustomWinProc_s0095_0bb0 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    void* AsInterface(int typeId);   // 0x00950EB0
    void* AsInterfaceA(int typeId);  // 0x00951240
    int   Release();                 // 0x009514A0
};
}
}
using EA::UTFWin::CustomWinProc_s0095_0bb0;
// ---- items of slice s00950bb0 end

// ---- items of slice s009515e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl {
struct false_type {};
}
namespace eastl {
template <typename T> struct has_trivial_copy : public false_type {};
}
namespace eastl {
struct input_iterator_tag {};
}
namespace eastl {
struct forward_iterator_tag : public input_iterator_tag {};
}
namespace eastl {
struct bidirectional_iterator_tag : public forward_iterator_tag {};
}
namespace eastl {
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}
namespace eastl {
template <typename T> inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }
}
namespace eastl {
template <typename T>
struct generic_iterator {
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
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  const generic_iterator<T> i(uninitialized_copy_impl(generic_iterator<const T>(first), generic_iterator<const T>(last),
                                                      generic_iterator<T>(result), has_trivial_copy<T>()));
  return i.base();
}
}
namespace eastl {
template <typename T>
__forceinline T* copy(const T* first, const T* last, T* result) {
  for (; first != last; ++first, ++result)
    *result = *first;
  return result;
}
}
namespace eastl {
template <typename T>
class vector_s0095_15e0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator;

  vector_s0095_15e0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector_s0095_15e0() { DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin)); }

  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
  T* data() { return mpBegin; }

  void assign(const T* first, const T* last) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }

  T* DoAllocate(unsigned n) {
    return n ? (T*)EASTL_allocator_allocate(n * sizeof(T), "EASTL", 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
             : 0;
  }
  void DoFree(T* p, unsigned) {
    if (p && ((int*)p)[-1] != 0)
      EASTL_allocator_deallocate(p);
  }
  // @ 0x009518A0  vector<CurvePoint>::DoRealloc
  // @ 0x00951900  vector<Math::Vector3>::DoRealloc
  __declspec(noinline) T* DoRealloc(unsigned n, const T* first, const T* last) {
    T* const p = DoAllocate(n);
    uninitialized_copy_ptr(first, last, p);
    return p;
  }
  // @ 0x009519B0  vector<CurvePoint>::DoAssignFromIterator
  // @ 0x00951A80  vector<Math::Vector3>::DoAssignFromIterator
  __declspec(noinline) void DoAssignFromIterator(const T* first, const T* last, random_access_iterator_tag) {
    const unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
      T* const pNewData = DoRealloc(n, first, last);
      DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin));
      mpBegin = pNewData;
      mpEnd = mpBegin + n;
      mpCapacity = mpEnd;
    } else if (n <= (unsigned)(mpEnd - mpBegin)) {
      T* const pNewEnd = eastl::copy(first, last, mpBegin);
      mpEnd = pNewEnd;
    } else {
      const T* position = first + (mpEnd - mpBegin);
      eastl::copy(first, position, mpBegin);
      mpEnd = uninitialized_copy_ptr(position, last, mpEnd);
    }
  }
};
}
namespace Math {
struct Vector3 {
  float x, y, z;
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
}
struct CurvePoint { float t, v; };
namespace UTFWin {
class ICoreAllocator;
}
namespace UTFWin {
ICoreAllocator* GetDefaultAllocator();
}
namespace UTFWin {
void* AllocObject(unsigned size, unsigned align, const char* name, ICoreAllocator* a);
}
namespace UTFWin {
void FreeObject(void* p);
}
namespace UTFWin {
struct TypeDesc { int x; };
}
namespace UTFWin {
extern const TypeDesc kCurveDesc;
}
namespace UTFWin {
extern const TypeDesc kPath2DDesc;
}
namespace UTFWin {
struct PropertyRef {
  const TypeDesc* type;
  void* obj;
  int count;
  int value;
};
}
namespace UTFWin {
class Object {
 public:
  virtual int f0();
  virtual int f1() = 0;
  virtual ~Object() = 0;
};
}
namespace UTFWin {
inline Object::~Object() {}
}
namespace UTFWin {
class AnimationCurve : public Object {
 public:
  eastl::vector_s0095_15e0<CurvePoint> mPoints;
  int m14;
  int m18;
  int m1c;

  AnimationCurve() : m18(1), m1c(0) {}
  static void* operator new(size_t n, ICoreAllocator* a) { return AllocObject(n, 4, "UTFWin/EA::UTFWin::AnimationCurve", a); }
  static void operator delete(void* p) { FreeObject(p); }
  static void operator delete(void* p, ICoreAllocator*) { FreeObject(p); }

  virtual int f1();
  // @ 0x00951780  (scalar deleting destructor ??_G)
  virtual ~AnimationCurve() {}
  virtual int f3();
  virtual void GetProperty(PropertyRef* out);
  virtual int f5();
  virtual unsigned GetPointCount();
  virtual int f7();
  virtual int f8();
  virtual void SetPoints(const CurvePoint* p, int n);
  virtual unsigned GetPoints(CurvePoint* dst, unsigned max);
};
}
namespace UTFWin {
class AnimationPath2D : public Object {
 public:
  eastl::vector_s0095_15e0<Math::Vector3> mPoints;
  int m14;
  int m18;
  int m1c;

  AnimationPath2D() : m18(1), m1c(0) {}
  static void* operator new(size_t n, ICoreAllocator* a) { return AllocObject(n, 4, "UTFWin/EA::UTFWin::AnimationPath2D", a); }
  static void operator delete(void* p) { FreeObject(p); }
  static void operator delete(void* p, ICoreAllocator*) { FreeObject(p); }

  virtual int f1();
  // @ 0x009517C0  (scalar deleting destructor ??_G)
  virtual ~AnimationPath2D() {}
  virtual int f3();
  virtual void GetProperty(PropertyRef* out);
  virtual int f5();
  virtual unsigned GetPointCount();
  virtual int f7();
  virtual int f8();
  virtual void SetPoints(const Math::Vector3* p, int n);
  virtual unsigned GetPoints(Math::Vector3* dst, unsigned max);
};
}
namespace UTFWin {
class AnimationCurveFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
  const char* GetName(int);
};
}
namespace UTFWin {
class AnimationPath2DFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
};
}
// ---- items of slice s009515e0 end

// @ 0x009513d0
bool InitArray8(int* out, int src, int, int* allocator)
{
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 8, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440200;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

// @ 0x009514a0
namespace EA { namespace UTFWin {
int CustomWinProc_s0095_0bb0::Release()
{
    int n = (*(volatile int*)&mnRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}
}}  // namespace EA::UTFWin

// @ 0x009514d0
bool ForwardCall514d0(int* a, int* b)
{
    void* obj = *(void**)((char*)a + 4);
    ((void(__thiscall*)(void*, int, int))((void**)*(void**)obj)[0x24 / 4])(obj, b[1], b[2]);
    return true;
}

// @ 0x009514f0
bool InitArray12(int* out, int src, int, int* allocator)
{
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 0xc, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440250;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

// @ 0x009515e0
namespace UTFWin {
const char* AnimationCurveFactory::GetName(int)
{ return "AnimationCurve"; }
}  // namespace UTFWin

// @ 0x009515f0
namespace UTFWin {
unsigned AnimationCurve::GetPointCount()
{ return mPoints.size(); }
}  // namespace UTFWin

// @ 0x00951600
namespace UTFWin {
unsigned AnimationCurve::GetPoints(CurvePoint* dst, unsigned max)
{
  if (dst) {
    unsigned n = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(n, max) * sizeof(CurvePoint));
  }
  return mPoints.size();
}
}  // namespace UTFWin

// @ 0x00951650
namespace UTFWin {
void AnimationCurve::GetProperty(PropertyRef* out)
{
  out->type = &kCurveDesc;
  out->obj = this;
  out->count = 1;
  out->value = f5();
}
}  // namespace UTFWin

// @ 0x00951680
namespace UTFWin {
unsigned AnimationPath2D::GetPointCount()
{ return mPoints.size(); }
}  // namespace UTFWin

// @ 0x009516a0
namespace UTFWin {
unsigned AnimationPath2D::GetPoints(Math::Vector3* dst, unsigned max)
{
  if (dst) {
    unsigned n = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(n, max) * sizeof(Math::Vector3));
  }
  return mPoints.size();
}
}  // namespace UTFWin

// @ 0x00951710
namespace UTFWin {
void AnimationPath2D::GetProperty(PropertyRef* out)
{
  out->type = &kPath2DDesc;
  out->obj = this;
  out->count = 1;
  out->value = f5();
}
}  // namespace UTFWin

// @ 0x00951740
namespace eastl {
template <typename T> __declspec(noinline) generic_iterator<T> uninitialized_copy_impl(generic_iterator<const T> first, generic_iterator<const T> last, generic_iterator<T> dest, false_type)
{
  generic_iterator<T> currentDest(dest);
  for (; first.mIterator != last.mIterator; ++first, ++currentDest)
    ::new (&*currentDest) T(*first);
  return currentDest;
}
}  // namespace eastl

// @ 0x00951850
namespace UTFWin {
Object* AnimationPath2DFactory::Create(unsigned, ICoreAllocator* alloc)
{
  if (!alloc)
    alloc = GetDefaultAllocator();
  return new (alloc) AnimationPath2D();
}
}  // namespace UTFWin

// @ 0x00951960
namespace UTFWin {
Object* AnimationCurveFactory::Create(unsigned, ICoreAllocator* alloc)
{
  if (!alloc)
    alloc = GetDefaultAllocator();
  return new (alloc) AnimationCurve();
}
}  // namespace UTFWin

// @ 0x00951b60
namespace UTFWin {
void AnimationCurve::SetPoints(const CurvePoint* p, int n)
{ mPoints.assign(p, p + n); }
}  // namespace UTFWin

// @ 0x00951b80
namespace UTFWin {
void AnimationPath2D::SetPoints(const Math::Vector3* p, int n)
{ mPoints.assign(p, p + n); }
}  // namespace UTFWin
