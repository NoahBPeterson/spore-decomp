#include "resource/Hash.h"

namespace Spore::Resource {

uint32_t HashName(std::string_view name) {
  uint32_t h = 0x811C9DC5u;
  for (char ch : name) {
    uint16_t c = static_cast<uint16_t>(static_cast<int16_t>(static_cast<signed char>(ch)));
    if (c >= 'A' && c <= 'Z') c = static_cast<uint16_t>(c + ('a' - 'A'));
    h = (h * 0x01000193u) ^ c;
  }
  return h;
}

}  // namespace Spore::Resource
