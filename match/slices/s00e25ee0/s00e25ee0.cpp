// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_013f09b4[];   // allocator name string for this family

struct Pt_00e25ee0 { float t, v; };

namespace eastl_00e25ee0 {

struct false_type_00e25ee0 {};
template <typename T> struct has_trivial_copy_00e25ee0 : public false_type_00e25ee0 {};

template <typename T>
struct generic_iterator_00e25ee0 {
  T* mIterator;
  explicit generic_iterator_00e25ee0(T* x) : mIterator(x) {}
  generic_iterator_00e25ee0& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00e25ee0<Pt_00e25ee0> uninit_copy_impl_e24310(
    generic_iterator_00e25ee0<const Pt_00e25ee0> first,
    generic_iterator_00e25ee0<const Pt_00e25ee0> last,
    generic_iterator_00e25ee0<Pt_00e25ee0> dest,
    has_trivial_copy_00e25ee0<Pt_00e25ee0>);            // 0xe24310

inline Pt_00e25ee0* uninitialized_copy_ptr_00e25ee0(const Pt_00e25ee0* first, const Pt_00e25ee0* last, Pt_00e25ee0* result) {
  const generic_iterator_00e25ee0<Pt_00e25ee0> i(uninit_copy_impl_e24310(
      generic_iterator_00e25ee0<const Pt_00e25ee0>(first),
      generic_iterator_00e25ee0<const Pt_00e25ee0>(last),
      generic_iterator_00e25ee0<Pt_00e25ee0>(result),
      has_trivial_copy_00e25ee0<Pt_00e25ee0>()));
  return i.base();
}

}  // namespace eastl_00e25ee0

// @ 0x0000e25ee0
__declspec(noinline) Pt_00e25ee0* __stdcall DoRealloc_00e25ee0(unsigned n, const Pt_00e25ee0* first, const Pt_00e25ee0* last) {
  Pt_00e25ee0* const p = n ? (Pt_00e25ee0*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_00e25ee0), DATA_013f09b4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_00e25ee0::uninitialized_copy_ptr_00e25ee0(first, last, p);
  return p;
}
