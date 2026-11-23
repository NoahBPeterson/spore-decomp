// Same shape as s009515e0's vector<V3>::DoRealloc (0x00951900):
// EASTL allocate (12 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13eb8a4[];   // allocator name string for this family

struct V3_006f4f30 { float x, y, z; };

namespace eastl_006f4f30 {

struct false_type_006f4f30 {};
template <typename T> struct has_trivial_copy_006f4f30 : public false_type_006f4f30 {};

template <typename T>
struct generic_iterator_006f4f30 {
  T* mIterator;
  explicit generic_iterator_006f4f30(T* x) : mIterator(x) {}
  generic_iterator_006f4f30& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_006f4f30<V3_006f4f30> uninit_copy_impl_951740(
    generic_iterator_006f4f30<const V3_006f4f30> first,
    generic_iterator_006f4f30<const V3_006f4f30> last,
    generic_iterator_006f4f30<V3_006f4f30> dest,
    has_trivial_copy_006f4f30<V3_006f4f30>);            // 0x951740

inline V3_006f4f30* uninitialized_copy_ptr_006f4f30(const V3_006f4f30* first, const V3_006f4f30* last, V3_006f4f30* result) {
  const generic_iterator_006f4f30<V3_006f4f30> i(uninit_copy_impl_951740(
      generic_iterator_006f4f30<const V3_006f4f30>(first),
      generic_iterator_006f4f30<const V3_006f4f30>(last),
      generic_iterator_006f4f30<V3_006f4f30>(result),
      has_trivial_copy_006f4f30<V3_006f4f30>()));
  return i.base();
}

}  // namespace eastl_006f4f30

// @ 0x00006f4f30
__declspec(noinline) V3_006f4f30* __stdcall DoRealloc_006f4f30(unsigned n, const V3_006f4f30* first, const V3_006f4f30* last) {
  V3_006f4f30* const p = n ? (V3_006f4f30*)EASTL_allocator_allocate_f473a0(n * sizeof(V3_006f4f30), DATA_13eb8a4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_006f4f30::uninitialized_copy_ptr_006f4f30(first, last, p);
  return p;
}
