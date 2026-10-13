// eastl::basic_string with the RETAIL layout: begin/end/capacity + the allocator (0x10 with
// eastl::allocator, same as dev; 0x14 with EASTLCoreAllocator).  Hand-maintained.
#ifndef GAME_EASTL_STRING_H
#define GAME_EASTL_STRING_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

template <typename T, typename A = allocator>
class basic_string {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  const T* c_str() const { return mpBegin; }
  uint32_t length() const { return (uint32_t)(mpEnd - mpBegin); }
  // library instantiations, defined elsewhere in the image (not here): assign(pBegin, pEnd) is 0x00454cb0 for char and
  // 0x00423650 for wchar_t (the byte-exact SP::GetPropertyAsString8/16 call them)
  void assign(const T* pBegin, const T* pEnd);
};

typedef basic_string<char> string8;
typedef basic_string<wchar_t> string16;

}  // namespace eastl

#endif
