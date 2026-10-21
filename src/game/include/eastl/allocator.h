// Allocators with their RETAIL layouts (tools/migrate/leafsizes.py, measured from byte-exact slices).
// Hand-maintained: the generator (tools/migrate/headers.py) includes this for any allocator type.
#ifndef GAME_EASTL_ALLOCATOR_H
#define GAME_EASTL_ALLOCATOR_H
#include "game/types.h"

namespace EA { namespace Allocator { class ICoreAllocator; } }

namespace eastl {

// 4 bytes in strings, hash tables, trees and lists (as in the dev build); inside a vector the
// allocator slot is 8 bytes (see vector.h).
class allocator {
 public:
  const char* mpName;
};

struct sp_vector_allocator : public allocator { private:};

}  // namespace eastl

namespace EA { namespace Allocator {

// 8 bytes in retail (dev 0xc: the mpName word only exists with EASTL_NAME_ENABLED).
class EASTLCoreAllocator {
 public:
  ICoreAllocator* mpCoreAllocator;
  int mnFlags;
};

}}  // namespace EA::Allocator

#endif
