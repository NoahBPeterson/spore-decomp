// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13eb8a4[];   // allocator name string for this family

struct Pt_006f4f90 { float t, v; };

namespace eastl_006f4f90 {

struct false_type_006f4f90 {};
template <typename T> struct has_trivial_copy_006f4f90 : public false_type_006f4f90 {};

template <typename T>
struct generic_iterator_006f4f90 {
  T* mIterator;
  explicit generic_iterator_006f4f90(T* x) : mIterator(x) {}
  generic_iterator_006f4f90& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_006f4f90<Pt_006f4f90> uninit_copy_impl_714bc0(
    generic_iterator_006f4f90<const Pt_006f4f90> first,
    generic_iterator_006f4f90<const Pt_006f4f90> last,
    generic_iterator_006f4f90<Pt_006f4f90> dest,
    has_trivial_copy_006f4f90<Pt_006f4f90>);            // 0x714bc0

inline Pt_006f4f90* uninitialized_copy_ptr_006f4f90(const Pt_006f4f90* first, const Pt_006f4f90* last, Pt_006f4f90* result) {
  const generic_iterator_006f4f90<Pt_006f4f90> i(uninit_copy_impl_714bc0(
      generic_iterator_006f4f90<const Pt_006f4f90>(first),
      generic_iterator_006f4f90<const Pt_006f4f90>(last),
      generic_iterator_006f4f90<Pt_006f4f90>(result),
      has_trivial_copy_006f4f90<Pt_006f4f90>()));
  return i.base();
}

}  // namespace eastl_006f4f90

// @ 0x00006f4f90
__declspec(noinline) Pt_006f4f90* __stdcall DoRealloc_006f4f90(unsigned n, const Pt_006f4f90* first, const Pt_006f4f90* last) {
  Pt_006f4f90* const p = n ? (Pt_006f4f90*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_006f4f90), DATA_13eb8a4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_006f4f90::uninitialized_copy_ptr_006f4f90(first, last, p);
  return p;
}
