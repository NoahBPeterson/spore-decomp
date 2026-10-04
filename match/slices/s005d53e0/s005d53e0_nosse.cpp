// slice s005d53e0 -- eastl::vector<PathIntersection, sp_vector_allocator> instantiation from a TU built
// without /arch:SSE (float members copied with fld/fstp).  Flags: /O2 /MD /Gy /TP (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
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

// @ 0x005D5830
template <typename T>
void sp_vector<T>::DoInsertValue(T* position, const T& value) {
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

// @ 0x005D5970
template <typename T>
void sp_vector<T>::push_back(const T& value) {
  if (mpEnd < mpCapacity)
    ::new (mpEnd++) T(value);
  else
    DoInsertValue(mpEnd, value);
}

template class sp_vector<PathIntersection>;
}  // namespace eastl
