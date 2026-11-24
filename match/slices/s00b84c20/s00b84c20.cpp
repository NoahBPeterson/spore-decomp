// Same shape as s009515e0's vector<V3>::DoRealloc (0x00951900):
// EASTL allocate (12 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13f09b4[];   // allocator name string for this family

struct V3_00b84c20 { float x, y, z; };

namespace eastl_00b84c20 {

struct false_type_00b84c20 {};
template <typename T> struct has_trivial_copy_00b84c20 : public false_type_00b84c20 {};

template <typename T>
struct generic_iterator_00b84c20 {
  T* mIterator;
  explicit generic_iterator_00b84c20(T* x) : mIterator(x) {}
  generic_iterator_00b84c20& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00b84c20<V3_00b84c20> uninit_copy_impl_898b80(
    generic_iterator_00b84c20<const V3_00b84c20> first,
    generic_iterator_00b84c20<const V3_00b84c20> last,
    generic_iterator_00b84c20<V3_00b84c20> dest,
    has_trivial_copy_00b84c20<V3_00b84c20>);            // 0x898b80

inline V3_00b84c20* uninitialized_copy_ptr_00b84c20(const V3_00b84c20* first, const V3_00b84c20* last, V3_00b84c20* result) {
  const generic_iterator_00b84c20<V3_00b84c20> i(uninit_copy_impl_898b80(
      generic_iterator_00b84c20<const V3_00b84c20>(first),
      generic_iterator_00b84c20<const V3_00b84c20>(last),
      generic_iterator_00b84c20<V3_00b84c20>(result),
      has_trivial_copy_00b84c20<V3_00b84c20>()));
  return i.base();
}

}  // namespace eastl_00b84c20

// @ 0x0000b84c20
__declspec(noinline) V3_00b84c20* __stdcall DoRealloc_00b84c20(unsigned n, const V3_00b84c20* first, const V3_00b84c20* last) {
  V3_00b84c20* const p = n ? (V3_00b84c20*)EASTL_allocator_allocate_f473a0(n * sizeof(V3_00b84c20), DATA_13f09b4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_00b84c20::uninitialized_copy_ptr_00b84c20(first, last, p);
  return p;
}
