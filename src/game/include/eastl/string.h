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
  // append(pBegin, pEnd) is 0x00455d60 for char and 0x00429580 for wchar_t, sprintf(fmt, ...) 0x00472fe0 / 0x0041e050
  // (symbols/pdb_names.json, callee-single; ArgumentSpec AddArgDocs 0x839c00 and INetFileCache Init 0x949cc0 call append)
  basic_string& append(const T* pBegin, const T* pEnd);
  // assign(p) (NUL-terminated) is 0x006a4380 for char (pdb_names callee-single; slice s0083c900 declares it there)
  basic_string& assign(const T* p);
  int sprintf(const T* pFormat, ...);
};

typedef basic_string<char> string8;
typedef basic_string<wchar_t> string16;

}  // namespace eastl

#endif
