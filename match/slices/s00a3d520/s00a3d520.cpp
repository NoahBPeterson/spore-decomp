// Same shape as s009515e0's vector<V3>::DoRealloc (0x00951900):
// EASTL allocate (12 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13f2150[];   // allocator name string for this family

struct V3_00a3d520 { float x, y, z; };

namespace eastl_00a3d520 {

struct false_type_00a3d520 {};
template <typename T> struct has_trivial_copy_00a3d520 : public false_type_00a3d520 {};

template <typename T>
struct generic_iterator_00a3d520 {
  T* mIterator;
  explicit generic_iterator_00a3d520(T* x) : mIterator(x) {}
  generic_iterator_00a3d520& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00a3d520<V3_00a3d520> uninit_copy_impl_898b80(
    generic_iterator_00a3d520<const V3_00a3d520> first,
    generic_iterator_00a3d520<const V3_00a3d520> last,
    generic_iterator_00a3d520<V3_00a3d520> dest,
    has_trivial_copy_00a3d520<V3_00a3d520>);            // 0x898b80

inline V3_00a3d520* uninitialized_copy_ptr_00a3d520(const V3_00a3d520* first, const V3_00a3d520* last, V3_00a3d520* result) {
  const generic_iterator_00a3d520<V3_00a3d520> i(uninit_copy_impl_898b80(
      generic_iterator_00a3d520<const V3_00a3d520>(first),
      generic_iterator_00a3d520<const V3_00a3d520>(last),
      generic_iterator_00a3d520<V3_00a3d520>(result),
      has_trivial_copy_00a3d520<V3_00a3d520>()));
  return i.base();
}

}  // namespace eastl_00a3d520

// @ 0x0000a3d520
__declspec(noinline) V3_00a3d520* __stdcall DoRealloc_00a3d520(unsigned n, const V3_00a3d520* first, const V3_00a3d520* last) {
  V3_00a3d520* const p = n ? (V3_00a3d520*)EASTL_allocator_allocate_f473a0(n * sizeof(V3_00a3d520), DATA_13f2150, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_00a3d520::uninitialized_copy_ptr_00a3d520(first, last, p);
  return p;
}
