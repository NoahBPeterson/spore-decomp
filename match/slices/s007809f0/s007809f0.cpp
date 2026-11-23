// Same shape as s009515e0's vector<V3>::DoRealloc (0x00951900):
// EASTL allocate (12 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13eb8a4[];   // allocator name string for this family

struct V3_007809f0 { float x, y, z; };

namespace eastl_007809f0 {

struct false_type_007809f0 {};
template <typename T> struct has_trivial_copy_007809f0 : public false_type_007809f0 {};

template <typename T>
struct generic_iterator_007809f0 {
  T* mIterator;
  explicit generic_iterator_007809f0(T* x) : mIterator(x) {}
  generic_iterator_007809f0& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_007809f0<V3_007809f0> uninit_copy_impl_77fa70(
    generic_iterator_007809f0<const V3_007809f0> first,
    generic_iterator_007809f0<const V3_007809f0> last,
    generic_iterator_007809f0<V3_007809f0> dest,
    has_trivial_copy_007809f0<V3_007809f0>);            // 0x77fa70

inline V3_007809f0* uninitialized_copy_ptr_007809f0(const V3_007809f0* first, const V3_007809f0* last, V3_007809f0* result) {
  const generic_iterator_007809f0<V3_007809f0> i(uninit_copy_impl_77fa70(
      generic_iterator_007809f0<const V3_007809f0>(first),
      generic_iterator_007809f0<const V3_007809f0>(last),
      generic_iterator_007809f0<V3_007809f0>(result),
      has_trivial_copy_007809f0<V3_007809f0>()));
  return i.base();
}

}  // namespace eastl_007809f0

// @ 0x00007809f0
__declspec(noinline) V3_007809f0* __stdcall DoRealloc_007809f0(unsigned n, const V3_007809f0* first, const V3_007809f0* last) {
  V3_007809f0* const p = n ? (V3_007809f0*)EASTL_allocator_allocate_f473a0(n * sizeof(V3_007809f0), DATA_13eb8a4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_007809f0::uninitialized_copy_ptr_007809f0(first, last, p);
  return p;
}
