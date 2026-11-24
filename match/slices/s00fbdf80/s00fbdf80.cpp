// Same shape as s009515e0's vector<V8>::DoAssignFromIterator (0x009519B0-copy-inline):
// grow via the family's DoRealloc (+DoFree through 0x00f47380), else copy or
// copy+uninitialized_copy_impl into place.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void EASTL_allocator_deallocate_f47380(void* p); // 0x00f47380

struct V8_00fbdf80 { int a, b; };

namespace eastl_00fbdf80 {

struct false_type_00fbdf80 {};
template <typename T> struct has_trivial_copy_00fbdf80 : public false_type_00fbdf80 {};

template <typename T>
struct generic_iterator_00fbdf80 {
  T* mIterator;
  explicit generic_iterator_00fbdf80(T* x) : mIterator(x) {}
  generic_iterator_00fbdf80& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00fbdf80<V8_00fbdf80> uninit_copy_impl_479c00(
    generic_iterator_00fbdf80<const V8_00fbdf80> first,
    generic_iterator_00fbdf80<const V8_00fbdf80> last,
    generic_iterator_00fbdf80<V8_00fbdf80> dest,
    has_trivial_copy_00fbdf80<V8_00fbdf80>);            // 0x479c00
inline V8_00fbdf80* uninitialized_copy_ptr_00fbdf80(const V8_00fbdf80* first, const V8_00fbdf80* last, V8_00fbdf80* result) {
  const generic_iterator_00fbdf80<V8_00fbdf80> i(uninit_copy_impl_479c00(
      generic_iterator_00fbdf80<const V8_00fbdf80>(first),
      generic_iterator_00fbdf80<const V8_00fbdf80>(last),
      generic_iterator_00fbdf80<V8_00fbdf80>(result),
      has_trivial_copy_00fbdf80<V8_00fbdf80>()));
  return i.base();
}

template <typename T>
__forceinline T* copy_00fbdf80(const T* first, const T* last, T* result) {
  for (; first != last; ++first, ++result)
    *result = *first;
  return result;
}
}  // namespace eastl_00fbdf80

struct vector_00fbdf80 {
  V8_00fbdf80* mpBegin;
  V8_00fbdf80* mpEnd;
  V8_00fbdf80* mpCapacity;
  int mAllocator;

  V8_00fbdf80* DoRealloc_476340(unsigned n, const V8_00fbdf80* first, const V8_00fbdf80* last); // 0x476340
  void DoAssignFromIterator_00fbdf80(const V8_00fbdf80* first, const V8_00fbdf80* last, int);
  void DoFree(V8_00fbdf80* p, unsigned) {
    if (p && ((int*)p)[-1] != 0)
      EASTL_allocator_deallocate_f47380(p);
  }

};

// @ 0x0000fbdf80
__declspec(noinline) void vector_00fbdf80::DoAssignFromIterator_00fbdf80(const V8_00fbdf80* first, const V8_00fbdf80* last, int) {
  const unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(mpCapacity - mpBegin)) {
    V8_00fbdf80* const pNewData = DoRealloc_476340(n, first, last);
    DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = mpBegin + n;
    mpCapacity = mpEnd;
  } else if (n <= (unsigned)(mpEnd - mpBegin)) {
    V8_00fbdf80* const pNewEnd = eastl_00fbdf80::copy_00fbdf80(first, last, mpBegin);
    mpEnd = pNewEnd;
  } else {
    const V8_00fbdf80* position = first + (mpEnd - mpBegin);
    eastl_00fbdf80::copy_00fbdf80(first, position, mpBegin);
    mpEnd = eastl_00fbdf80::uninitialized_copy_ptr_00fbdf80(position, last, mpEnd);
  }
}
