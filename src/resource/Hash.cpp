#include "resource/Hash.h"

namespace Spore::Resource {

uint32_t HashName(std::string_view name) {
  uint32_t h = 0x811C9DC5u;
  for (unsigned char c : name) {
    if (c >= 'A' && c <= 'Z') c = static_cast<unsigned char>(c + ('a' - 'A'));
    h = (h * 0x01000193u) ^ c;
  }
  return h;
}

}  // namespace Spore::Resource
