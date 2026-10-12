// eastl::fixed_vector with the RETAIL layout: a 0x18 header (begin/end/capacity, the overflow
// allocator, the pool pointer, one word the constructor never writes) and the buffer at +0x18
// (aligned to T).  Measured for bOverflow = true; the no-overflow form is not measured.
// Hand-maintained.
#ifndef GAME_EASTL_FIXED_VECTOR_H
#define GAME_EASTL_FIXED_VECTOR_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

template <typename T, uint32_t N, bool bOverflow = true, typename OA = allocator>
class fixed_vector {
 public:
  T* mpBegin;          // +0x00
  T* mpEnd;            // +0x04
  T* mpCapacity;       // +0x08
  OA mOverflowAllocator;  // +0x0c
  void* mpPoolBegin;   // +0x10
  uint32_t mUnknown14; // +0x14, never written by the constructor
  T mBuffer[N];        // +0x18
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

}  // namespace eastl

#endif
