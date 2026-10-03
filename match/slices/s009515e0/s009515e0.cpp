// UTFWin AnimationCurve / AnimationPath2D (EA::UTFWin) and their EASTL vector helpers.
#include <string.h>
#include <new>

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int x, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

namespace eastl {

struct false_type {};
template <typename T> struct has_trivial_copy : public false_type {};
struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T> inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }

template <typename T>
struct generic_iterator {
  T* mIterator;
  explicit generic_iterator(T* x) : mIterator(x) {}
  generic_iterator& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};
template <typename T>
inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b) { return a.mIterator != b.mIterator; }

// @ 0x00951740  uninitialized_copy_impl<generic_iterator<Math::Vector3*>> (the CurvePoint
// instantiation is FUN_0076ffd0, outside this slice)
template <typename T>
__declspec(noinline) generic_iterator<T> uninitialized_copy_impl(generic_iterator<const T> first, generic_iterator<const T> last,
                                            generic_iterator<T> dest, false_type) {
  generic_iterator<T> currentDest(dest);
  for (; first.mIterator != last.mIterator; ++first, ++currentDest)
    ::new (&*currentDest) T(*first);
  return currentDest;
}

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

template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator;

  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector() { DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin)); }

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
namespace eastl {
// @ 0x00951800  eastl::copy<Math::Vector3> (NONMATCHING: original uses a different induction-variable layout)
template <>
__declspec(noinline) Math::Vector3* copy(const Math::Vector3* first, const Math::Vector3* last, Math::Vector3* result) {
  for (; first != last; ++first, ++result)
    *result = *first;
  return result;
}
}

struct Rec20 { int a[5]; };
struct Rec40 { int a[10]; };

// @ 0x00951BB0
Rec20* uninitialized_copy_Rec20(const Rec20* first, const Rec20* last, Rec20* dest) {
  for (; first != last; ++first, ++dest)
    ::new (dest) Rec20(*first);
  return dest;
}

// @ 0x00951BF0
Rec20* copy_Rec20(const Rec20* first, const Rec20* last, Rec20* dest) {
  for (; first != last; ++first, ++dest)
    *dest = *first;
  return dest;
}

// @ 0x00951C30
Rec40* uninitialized_copy_Rec40(const Rec40* first, const Rec40* last, Rec40* dest) {
  for (; first != last; ++first, ++dest)
    ::new (dest) Rec40(*first);
  return dest;
}

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
  eastl::vector<CurvePoint> mPoints;
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

class AnimationPath2D : public Object {
 public:
  eastl::vector<Math::Vector3> mPoints;
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

class AnimationCurveFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
  const char* GetName(int);
};
class AnimationPath2DFactory {
 public:
  Object* Create(unsigned type, ICoreAllocator* alloc);
};

// @ 0x009515E0
const char* AnimationCurveFactory::GetName(int) { return "AnimationCurve"; }

// @ 0x009515F0
unsigned AnimationCurve::GetPointCount() { return mPoints.size(); }

// @ 0x00951600
unsigned AnimationCurve::GetPoints(CurvePoint* dst, unsigned max) {
  if (dst) {
    unsigned n = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(n, max) * sizeof(CurvePoint));
  }
  return mPoints.size();
}

// @ 0x00951650
void AnimationCurve::GetProperty(PropertyRef* out) {
  out->type = &kCurveDesc;
  out->obj = this;
  out->count = 1;
  out->value = f5();
}

// @ 0x00951680
unsigned AnimationPath2D::GetPointCount() { return mPoints.size(); }

// @ 0x009516A0
unsigned AnimationPath2D::GetPoints(Math::Vector3* dst, unsigned max) {
  if (dst) {
    unsigned n = mPoints.size();
    memcpy(dst, mPoints.mpBegin, eastl::min_alt(n, max) * sizeof(Math::Vector3));
  }
  return mPoints.size();
}

// @ 0x00951710
void AnimationPath2D::GetProperty(PropertyRef* out) {
  out->type = &kPath2DDesc;
  out->obj = this;
  out->count = 1;
  out->value = f5();
}

// @ 0x00951850
Object* AnimationPath2DFactory::Create(unsigned, ICoreAllocator* alloc) {
  if (!alloc)
    alloc = GetDefaultAllocator();
  return new (alloc) AnimationPath2D();
}

// @ 0x00951960
Object* AnimationCurveFactory::Create(unsigned, ICoreAllocator* alloc) {
  if (!alloc)
    alloc = GetDefaultAllocator();
  return new (alloc) AnimationCurve();
}

// @ 0x00951B60
void AnimationCurve::SetPoints(const CurvePoint* p, int n) { mPoints.assign(p, p + n); }

// @ 0x00951B80
void AnimationPath2D::SetPoints(const Math::Vector3* p, int n) { mPoints.assign(p, p + n); }

// Unknown class with vtable 0x014403C0 (slot 1 = FUN_009520e0, remaining slots _purecall).
class Unknown_14403C0 {
 public:
  virtual int f0();
  virtual int f1();
  ~Unknown_14403C0();
};

// @ 0x00951BA0
Unknown_14403C0::~Unknown_14403C0() {}

}  // namespace UTFWin
