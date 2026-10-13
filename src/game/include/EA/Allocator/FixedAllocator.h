// EA::Allocator::FixedAllocator<T, N>: FixedAllocatorBase's eight words (object size, alignment, count per block,
// head core block, head chunk, core alloc/free functions, context) = 0x20 as in the dev build.  Hand-maintained.
// Retail size not verified by a byte-exact user (the only user so far is Manager::InternalDatabaseList::mAlloc,
// whose engine offset is 4 below the dev one); only Manager's vtable is exercised by the migrated code.
#ifndef GAME_EA_ALLOCATOR_FIXEDALLOCATOR_H
#define GAME_EA_ALLOCATOR_FIXEDALLOCATOR_H
namespace EA { namespace Allocator {
template <typename T, int N>
class FixedAllocator {
 public:
  unsigned char mData[0x20];
};
}}  // namespace EA::Allocator
#endif
