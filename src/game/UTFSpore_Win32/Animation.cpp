// EA::UTFWin animation objects: curves, 2D paths and their factories.
// Object file: UTFSpore_Win32/Animation.obj.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1440200[];
extern "C" char g_1440250[];

#include "game/types.h"
#include <string.h>
#include <new>

namespace EA {
namespace UTFWin {
// Reference-counted window procedure stub; only Release is part of this module.
// The virtual slots are unnamed (no canonical header); slot2 is the deleting destructor.
struct CustomWinProc_s0095_0bb0 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);

    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    int Release();                   // 0x009514A0
};
}
}

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl {

struct false_type {};
template <typename T> struct has_trivial_copy : public false_type {};

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T> inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }

template <typename T>
class generic_iterator { public:
  T* mIterator;
  explicit generic_iterator(T* x) : mIterator(x) {}
  generic_iterator& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

template <typename T>
inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b) { return a.mIterator != b.mIterator; }

template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  const generic_iterator<T> i(uninitialized_copy_impl(generic_iterator<const T>(first), generic_iterator<const T>(last),
                                                      generic_iterator<T>(result), has_trivial_copy<T>()));
  return i.base();
}

template <typename T>
__forceinline T* copy(const T* first, const T* last, T* result) {
  for (; first != last; ++first, ++result)
    *result = *first;
  return result;
}

// Minimal stand-in for eastl::vector<T> (the game's own vector, slice s009515e0).
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

}  // namespace eastl

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
ICoreAllocator* GetDefaultAllocator();
void* AllocObject(unsigned size, unsigned align, const char* name, ICoreAllocator* a);
void FreeObject(void* p);
struct TypeDesc { int x; };
extern const TypeDesc kCurveDesc;
extern const TypeDesc kPath2DDesc;
struct PropertyRef {
  const TypeDesc* type;
  void* obj;
  int count;
  int value;
};
class Object {
 public:
  virtual int f0();
  virtual int f1() = 0;
  virtual ~Object() = 0;
};
inline Object::~Object() {}
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
  virtual unsigned GetPoints(CurvePoint* dst, unsigned maxCount);
};
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
  virtual unsigned GetPoints(Math::Vector3* dst, unsigned maxCount);
};
class AnimationCurveFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
  const char* GetName(int);
};
class AnimationPath2DFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
};
}

// @ 0x009513d0
bool InitArray8(int* out, int src, int, int* allocator)
{
    int* obj = *(int**)(src + 4);
    out[2] = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, out[2] * 8, 4);
    out[1] = (int)(size_t)p;
    out[0] = (int)g_1440200;
    if (out[2] != 0) {
        if (p != 0)
            ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, out[2]);
        else
            return false;
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
    // Forwards b[1], b[2] to virtual slot 9 of the object held at a[1].
    void* obj = *(void**)((char*)a + 4);
    typedef void (__thiscall* ForwardFn)(void*, int, int);
    ((ForwardFn)((void**)*(void**)obj)[0x24 / 4])(obj, b[1], b[2]);
    return true;
}

// @ 0x009514f0
bool InitArray12(int* out, int src, int, int* allocator)
{
    int* obj = *(int**)(src + 4);
    out[2] = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, out[2] * 0xc, 4);
    out[1] = (int)(size_t)p;
    out[0] = (int)g_1440250;
    if (out[2] != 0) {
        if (p != 0)
            ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, out[2]);
        else
            return false;
    }
    return true;
}

// @ 0x009515e0
namespace UTFWin {
const char* AnimationCurveFactory::GetName(int)
{ return "AnimationCurve"; }

// @ 0x009515f0
unsigned AnimationCurve::GetPointCount()
{ return mPoints.size(); }

// @ 0x00951600
unsigned AnimationCurve::GetPoints(CurvePoint* dst, unsigned maxCount)
{
  if (dst) {
    unsigned count = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(count, maxCount) * sizeof(CurvePoint));
  }
  return mPoints.size();
}

// @ 0x00951650
void AnimationCurve::GetProperty(PropertyRef* out)
{
  out->type = &kCurveDesc;
  out->obj = this;
  out->count = 1;
  out->value = f5();
}

// @ 0x00951680
unsigned AnimationPath2D::GetPointCount()
{ return mPoints.size(); }

// @ 0x009516a0
unsigned AnimationPath2D::GetPoints(Math::Vector3* dst, unsigned maxCount)
{
  if (dst) {
    unsigned count = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(count, maxCount) * sizeof(Math::Vector3));
  }
  return mPoints.size();
}

// @ 0x00951710
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

// @ 0x00951960
Object* AnimationCurveFactory::Create(unsigned, ICoreAllocator* alloc)
{
  if (!alloc)
    alloc = GetDefaultAllocator();
  return new (alloc) AnimationCurve();
}

// @ 0x00951b60
void AnimationCurve::SetPoints(const CurvePoint* p, int n)
{ mPoints.assign(p, p + n); }

// @ 0x00951b80
void AnimationPath2D::SetPoints(const Math::Vector3* p, int n)
{ mPoints.assign(p, p + n); }
}  // namespace UTFWin
