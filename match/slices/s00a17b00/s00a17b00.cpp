// Same shape as s009515e0's vector<V3>::DoAssignFromIterator (0x00951A80):
// grow via the family's DoRealloc (+DoFree through 0x00f47380), else copy or
// copy+uninitialized_copy_impl into place.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void EASTL_allocator_deallocate_f47380(void* p); // 0x00f47380

struct V3_00a17b00 { float x, y, z; };

namespace eastl_00a17b00 {

struct false_type_00a17b00 {};
template <typename T> struct has_trivial_copy_00a17b00 : public false_type_00a17b00 {};

template <typename T>
struct generic_iterator_00a17b00 {
  T* mIterator;
  explicit generic_iterator_00a17b00(T* x) : mIterator(x) {}
  generic_iterator_00a17b00& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00a17b00<V3_00a17b00> uninit_copy_impl_512050(
    generic_iterator_00a17b00<const V3_00a17b00> first,
    generic_iterator_00a17b00<const V3_00a17b00> last,
    generic_iterator_00a17b00<V3_00a17b00> dest,
    has_trivial_copy_00a17b00<V3_00a17b00>);            // 0x512050
inline V3_00a17b00* uninitialized_copy_ptr_00a17b00(const V3_00a17b00* first, const V3_00a17b00* last, V3_00a17b00* result) {
  const generic_iterator_00a17b00<V3_00a17b00> i(uninit_copy_impl_512050(
      generic_iterator_00a17b00<const V3_00a17b00>(first),
      generic_iterator_00a17b00<const V3_00a17b00>(last),
      generic_iterator_00a17b00<V3_00a17b00>(result),
      has_trivial_copy_00a17b00<V3_00a17b00>()));
  return i.base();
}

// the family's eastl::copy (defined elsewhere)
V3_00a17b00* copy_b84c80(const V3_00a17b00* first, const V3_00a17b00* last, V3_00a17b00* result);   // 0xb84c80
}  // namespace eastl_00a17b00

struct vector_00a17b00 {
  V3_00a17b00* mpBegin;
  V3_00a17b00* mpEnd;
  V3_00a17b00* mpCapacity;
  int mAllocator;

  V3_00a17b00* DoRealloc_6604b0(unsigned n, const V3_00a17b00* first, const V3_00a17b00* last); // 0x6604b0
  void DoAssignFromIterator_00a17b00(const V3_00a17b00* first, const V3_00a17b00* last, int);
  void DoFree(V3_00a17b00* p, unsigned) {
    if (p && ((int*)p)[-1] != 0)
      EASTL_allocator_deallocate_f47380(p);
  }

};

// @ 0x0000a17b00
__declspec(noinline) void vector_00a17b00::DoAssignFromIterator_00a17b00(const V3_00a17b00* first, const V3_00a17b00* last, int) {
  const unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(mpCapacity - mpBegin)) {
    V3_00a17b00* const pNewData = DoRealloc_6604b0(n, first, last);
    DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = mpBegin + n;
    mpCapacity = mpEnd;
  } else if (n <= (unsigned)(mpEnd - mpBegin)) {
    V3_00a17b00* const pNewEnd = eastl_00a17b00::copy_b84c80(first, last, mpBegin);
    mpEnd = pNewEnd;
  } else {
    const V3_00a17b00* position = first + (mpEnd - mpBegin);
    eastl_00a17b00::copy_b84c80(first, position, mpBegin);
    mpEnd = eastl_00a17b00::uninitialized_copy_ptr_00a17b00(position, last, mpEnd);
  }
}
