#pragma once
#include <cstdint>
#include <string_view>

namespace Spore::Resource {

// @ 0x0068C680 — 32-bit FNV-1 over towlower() of each char, Spore's name -> ID hash.
// Bytes >= 0x80 are sign-extended to a 16-bit wchar before hashing (the original
// passes (short)(signed char)c to towlower), so they contribute 0xFF80..0xFFFF.
// towlower is modeled in the "C" locale: only 'A'..'Z' change.
uint32_t HashName(std::string_view name);

}  // namespace Spore::Resource
