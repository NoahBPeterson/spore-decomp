// Same shape as s009515e0's vector<Pt>::DoRealloc (0x009518A0):
// EASTL allocate (4 bytes/element, allocator.h path, line 0xd1), then the
// family's uninitialized_copy_impl. Callee and allocator name re-pointed.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>

extern "C" void* EASTL_allocator_allocate_f473a0(unsigned int n, const char* name, int flags, int x, const char* file, int line); // 0x00f473a0
extern char DATA_13ebc58[];   // allocator name string for this family

struct Pt_007f1980 { float t, v; };

namespace eastl_007f1980 {

struct false_type_007f1980 {};
template <typename T> struct has_trivial_copy_007f1980 : public false_type_007f1980 {};

template <typename T>
struct generic_iterator_007f1980 {
  T* mIterator;
  explicit generic_iterator_007f1980(T* x) : mIterator(x) {}
  generic_iterator_007f1980& operator++() { ++mIterator; return *this; }
  T& operator*() const { return *mIterator; }
  T* base() const { return mIterator; }
};

// the family's uninitialized_copy_impl (defined elsewhere): sret-returning
generic_iterator_007f1980<Pt_007f1980> uninit_copy_impl_76ffd0(
    generic_iterator_007f1980<const Pt_007f1980> first,
    generic_iterator_007f1980<const Pt_007f1980> last,
    generic_iterator_007f1980<Pt_007f1980> dest,
    has_trivial_copy_007f1980<Pt_007f1980>);            // 0x76ffd0

inline Pt_007f1980* uninitialized_copy_ptr_007f1980(const Pt_007f1980* first, const Pt_007f1980* last, Pt_007f1980* result) {
  const generic_iterator_007f1980<Pt_007f1980> i(uninit_copy_impl_76ffd0(
      generic_iterator_007f1980<const Pt_007f1980>(first),
      generic_iterator_007f1980<const Pt_007f1980>(last),
      generic_iterator_007f1980<Pt_007f1980>(result),
      has_trivial_copy_007f1980<Pt_007f1980>()));
  return i.base();
}

}  // namespace eastl_007f1980

// @ 0x00007f1980
__declspec(noinline) Pt_007f1980* __stdcall DoRealloc_007f1980(unsigned n, const Pt_007f1980* first, const Pt_007f1980* last) {
  Pt_007f1980* const p = n ? (Pt_007f1980*)EASTL_allocator_allocate_f473a0(n * sizeof(Pt_007f1980), DATA_13ebc58, 0, 0,
                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  eastl_007f1980::uninitialized_copy_ptr_007f1980(first, last, p);
  return p;
}
