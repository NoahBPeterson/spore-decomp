// Same shape as s009515e0's vector<V3>::DoRealloc (0x00951900):
// EASTL allocate (12 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_14479f4[];   // allocator name string for this family

struct V3_009de840 { float x, y, z; };

namespace eastl_009de840 {

struct false_type_009de840 {};
template <typename T> struct has_trivial_copy_009de840 : public false_type_009de840 {};

template <typename T>
struct generic_iterator_009de840 {
  T* mIterator;
  explicit generic_iterator_009de840(T* x) : mIterator(x) {}
  generic_iterator_009de840& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_009de840<V3_009de840> uninit_copy_impl_898b80(
    generic_iterator_009de840<const V3_009de840> first,
    generic_iterator_009de840<const V3_009de840> last,
    generic_iterator_009de840<V3_009de840> dest,
    has_trivial_copy_009de840<V3_009de840>);            // 0x898b80

inline V3_009de840* uninitialized_copy_ptr_009de840(const V3_009de840* first, const V3_009de840* last, V3_009de840* result) {
  const generic_iterator_009de840<V3_009de840> i(uninit_copy_impl_898b80(
      generic_iterator_009de840<const V3_009de840>(first),
      generic_iterator_009de840<const V3_009de840>(last),
      generic_iterator_009de840<V3_009de840>(result),
      has_trivial_copy_009de840<V3_009de840>()));
  return i.base();
}

}  // namespace eastl_009de840

// @ 0x00009de840
__declspec(noinline) V3_009de840* __stdcall DoRealloc_009de840(unsigned n, const V3_009de840* first, const V3_009de840* last) {
  V3_009de840* const p = n ? (V3_009de840*)EASTL_allocator_allocate_f473a0(n * sizeof(V3_009de840), DATA_14479f4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_009de840::uninitialized_copy_ptr_009de840(first, last, p);
  return p;
}
