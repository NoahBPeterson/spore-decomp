// eastl::vector with the RETAIL layout: begin/end/capacity plus an 8-byte allocator slot for every
// allocator (0x14 in total; dev was 0x10 with a 4-byte eastl::allocator).  The second word of the
// slot is never written by the constructors (tools/migrate/leafsizes.py).  Hand-maintained.
#ifndef GAME_EASTL_VECTOR_H
#define GAME_EASTL_VECTOR_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

template <typename A, int N> struct vector_allocator_slot { A mAllocator; unsigned char mPad[8 - N]; };
template <typename A> struct vector_allocator_slot<A, 8> { A mAllocator; };

template <typename T, typename A = allocator>
class VectorBase {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  vector_allocator_slot<A, sizeof(A)> mAllocatorSlot;   // +0xc, 8 bytes
};

template <typename T, typename A = allocator>
class vector : public VectorBase<T, A> {
 public:
  typedef T value_type;
  typedef T* iterator;
  typedef const T* const_iterator;
  // Out of line in retail (fix pass 4): the destructor of a vector of AutoRefCount<T> is one folded function, 0x5c7f10
  // (`~SharedLibraryRegistry` 0x936740 ends `lea ecx,[esi+8]; jmp 0x5c7f10`), and erase(first, last) of the same element
  // kind is 0x5c2170 (`SharedLibraryRegistry::Shutdown` 0x936e10: `push [esi+0xc]; push [esi+8]; lea ecx,[esi+8]; call
  // 0x5c2170`).  Declared, not defined: every user calls them.
  ~vector();
  iterator erase(iterator first, iterator last);
  iterator begin() { return this->mpBegin; }
  iterator end() { return this->mpEnd; }
  uint32_t size() const { return (uint32_t)(this->mpEnd - this->mpBegin); }
  bool empty() const { return this->mpBegin == this->mpEnd; }
  T& operator[](uint32_t i) { return this->mpBegin[i]; }
  const T& operator[](uint32_t i) const { return this->mpBegin[i]; }
};

}  // namespace eastl

#endif
