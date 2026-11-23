// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13f09b4[];   // allocator name string for this family

struct Pt_00ac4000 { float t, v; };

namespace eastl_00ac4000 {

struct false_type_00ac4000 {};
template <typename T> struct has_trivial_copy_00ac4000 : public false_type_00ac4000 {};

template <typename T>
struct generic_iterator_00ac4000 {
  T* mIterator;
  explicit generic_iterator_00ac4000(T* x) : mIterator(x) {}
  generic_iterator_00ac4000& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_00ac4000<Pt_00ac4000> uninit_copy_impl_76ffd0(
    generic_iterator_00ac4000<const Pt_00ac4000> first,
    generic_iterator_00ac4000<const Pt_00ac4000> last,
    generic_iterator_00ac4000<Pt_00ac4000> dest,
    has_trivial_copy_00ac4000<Pt_00ac4000>);            // 0x76ffd0

inline Pt_00ac4000* uninitialized_copy_ptr_00ac4000(const Pt_00ac4000* first, const Pt_00ac4000* last, Pt_00ac4000* result) {
  const generic_iterator_00ac4000<Pt_00ac4000> i(uninit_copy_impl_76ffd0(
      generic_iterator_00ac4000<const Pt_00ac4000>(first),
      generic_iterator_00ac4000<const Pt_00ac4000>(last),
      generic_iterator_00ac4000<Pt_00ac4000>(result),
      has_trivial_copy_00ac4000<Pt_00ac4000>()));
  return i.base();
}

}  // namespace eastl_00ac4000

// @ 0x0000ac4000
__declspec(noinline) Pt_00ac4000* __stdcall DoRealloc_00ac4000(unsigned n, const Pt_00ac4000* first, const Pt_00ac4000* last) {
  Pt_00ac4000* const p = n ? (Pt_00ac4000*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_00ac4000), DATA_13f09b4, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_00ac4000::uninitialized_copy_ptr_00ac4000(first, last, p);
  return p;
}
