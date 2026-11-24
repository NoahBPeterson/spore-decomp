// Same shape as s009515e0's vector<V3>::DoAssignFromIterator (0x00951A80):
// grow via the family's DoRealloc (+DoFree through 0x00f47380), else copy or
// copy+uninitialized_copy_impl into place.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void EASTL_allocator_deallocate_f47380(void* p); // 0x00f47380

struct V3_00b86270 { float x, y, z; };

namespace eastl_00b86270 {

struct false_type_00b86270 {};
template <typename T> struct has_trivial_copy_00b86270 : public false_type_00b86270 {};

template <typename T>
struct generic_iterator_00b86270 {
  T* mIterator;
  explicit generic_iterator_00b86270(T* x) : mIterator(x) {}
  generic_iterator_00b86270& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00b86270<V3_00b86270> uninit_copy_impl_951740(
    generic_iterator_00b86270<const V3_00b86270> first,
    generic_iterator_00b86270<const V3_00b86270> last,
    generic_iterator_00b86270<V3_00b86270> dest,
    has_trivial_copy_00b86270<V3_00b86270>);            // 0x951740
inline V3_00b86270* uninitialized_copy_ptr_00b86270(const V3_00b86270* first, const V3_00b86270* last, V3_00b86270* result) {
  const generic_iterator_00b86270<V3_00b86270> i(uninit_copy_impl_951740(
      generic_iterator_00b86270<const V3_00b86270>(first),
      generic_iterator_00b86270<const V3_00b86270>(last),
      generic_iterator_00b86270<V3_00b86270>(result),
      has_trivial_copy_00b86270<V3_00b86270>()));
  return i.base();
}

// the family's eastl::copy (defined elsewhere)
V3_00b86270* copy_b84c80(const V3_00b86270* first, const V3_00b86270* last, V3_00b86270* result);   // 0xb84c80
}  // namespace eastl_00b86270

struct vector_00b86270 {
  V3_00b86270* mpBegin;
  V3_00b86270* mpEnd;
  V3_00b86270* mpCapacity;
  int mAllocator;

  V3_00b86270* DoRealloc_d59410(unsigned n, const V3_00b86270* first, const V3_00b86270* last); // 0xd59410
  void DoAssignFromIterator_00b86270(const V3_00b86270* first, const V3_00b86270* last, int);
  void DoFree(V3_00b86270* p, unsigned) {
    if (p && ((int*)p)[-1] != 0)
      EASTL_allocator_deallocate_f47380(p);
  }

};

// @ 0x0000b86270
__declspec(noinline) void vector_00b86270::DoAssignFromIterator_00b86270(const V3_00b86270* first, const V3_00b86270* last, int) {
  const unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(mpCapacity - mpBegin)) {
    V3_00b86270* const pNewData = DoRealloc_d59410(n, first, last);
    DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = mpBegin + n;
    mpCapacity = mpEnd;
  } else if (n <= (unsigned)(mpEnd - mpBegin)) {
    V3_00b86270* const pNewEnd = eastl_00b86270::copy_b84c80(first, last, mpBegin);
    mpEnd = pNewEnd;
  } else {
    const V3_00b86270* position = first + (mpEnd - mpBegin);
    eastl_00b86270::copy_b84c80(first, position, mpBegin);
    mpEnd = eastl_00b86270::uninitialized_copy_ptr_00b86270(position, last, mpEnd);
  }
}
