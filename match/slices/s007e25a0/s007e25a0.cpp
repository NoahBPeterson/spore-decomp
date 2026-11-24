// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13ebc58[];   // allocator name string for this family

struct Pt_007e25a0 { float t, v; };

namespace eastl_007e25a0 {

struct false_type_007e25a0 {};
template <typename T> struct has_trivial_copy_007e25a0 : public false_type_007e25a0 {};

template <typename T>
struct generic_iterator_007e25a0 {
  T* mIterator;
  explicit generic_iterator_007e25a0(T* x) : mIterator(x) {}
  generic_iterator_007e25a0& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_007e25a0<Pt_007e25a0> uninit_copy_impl_7e17a0(
    generic_iterator_007e25a0<const Pt_007e25a0> first,
    generic_iterator_007e25a0<const Pt_007e25a0> last,
    generic_iterator_007e25a0<Pt_007e25a0> dest,
    has_trivial_copy_007e25a0<Pt_007e25a0>);            // 0x7e17a0

inline Pt_007e25a0* uninitialized_copy_ptr_007e25a0(const Pt_007e25a0* first, const Pt_007e25a0* last, Pt_007e25a0* result) {
  const generic_iterator_007e25a0<Pt_007e25a0> i(uninit_copy_impl_7e17a0(
      generic_iterator_007e25a0<const Pt_007e25a0>(first),
      generic_iterator_007e25a0<const Pt_007e25a0>(last),
      generic_iterator_007e25a0<Pt_007e25a0>(result),
      has_trivial_copy_007e25a0<Pt_007e25a0>()));
  return i.base();
}

}  // namespace eastl_007e25a0

// @ 0x00007e25a0
__declspec(noinline) Pt_007e25a0* __stdcall DoRealloc_007e25a0(unsigned n, const Pt_007e25a0* first, const Pt_007e25a0* last) {
  Pt_007e25a0* const p = n ? (Pt_007e25a0*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_007e25a0), DATA_13ebc58, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_007e25a0::uninitialized_copy_ptr_007e25a0(first, last, p);
  return p;
}
