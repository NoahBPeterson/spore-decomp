// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13eb8a4[];   // allocator name string for this family

struct Pt_00754f80 { float t, v; };

namespace eastl_00754f80 {

struct false_type_00754f80 {};
template <typename T> struct has_trivial_copy_00754f80 : public false_type_00754f80 {};

template <typename T>
struct generic_iterator_00754f80 {
  T* mIterator;
  explicit generic_iterator_00754f80(T* x) : mIterator(x) {}
  generic_iterator_00754f80& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00754f80<Pt_00754f80> uninit_copy_impl_76ffd0(
    generic_iterator_00754f80<const Pt_00754f80> first,
    generic_iterator_00754f80<const Pt_00754f80> last,
    generic_iterator_00754f80<Pt_00754f80> dest,
    has_trivial_copy_00754f80<Pt_00754f80>);            // 0x76ffd0

inline Pt_00754f80* uninitialized_copy_ptr_00754f80(const Pt_00754f80* first, const Pt_00754f80* last, Pt_00754f80* result) {
  const generic_iterator_00754f80<Pt_00754f80> i(uninit_copy_impl_76ffd0(
      generic_iterator_00754f80<const Pt_00754f80>(first),
      generic_iterator_00754f80<const Pt_00754f80>(last),
      generic_iterator_00754f80<Pt_00754f80>(result),
      has_trivial_copy_00754f80<Pt_00754f80>()));
  return i.base();
}

}  // namespace eastl_00754f80

// @ 0x0000754f80
__declspec(noinline) Pt_00754f80* __stdcall DoRealloc_00754f80(unsigned n, const Pt_00754f80* first, const Pt_00754f80* last) {
  Pt_00754f80* const p = n ? (Pt_00754f80*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_00754f80), DATA_13eb8a4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_00754f80::uninitialized_copy_ptr_00754f80(first, last, p);
  return p;
}
