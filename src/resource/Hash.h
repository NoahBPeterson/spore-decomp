#pragma once
#include <cstdint>
#include <string_view>

namespace Spore::Resource {

// 32-bit FNV-1 over ASCII-lowercased bytes; Spore's name -> ID hash.
uint32_t HashName(std::string_view name);

}  // namespace Spore::Resource
