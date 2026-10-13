// eastl::deque<T, A, N>: DequeBase layout (0x2c = dev size of every eastl::deque<.., eastl::allocator, N> in
// work/devbuild/types.json: pointer array, its size, begin/end iterators of four words, the 4-byte allocator).
// Hand-maintained.  Retail layout unverified (deques on eastl::allocator are assumed unchanged, like lists and strings).
#ifndef GAME_EASTL_DEQUE_H
#define GAME_EASTL_DEQUE_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

template <typename T, typename Pointer, typename Reference, unsigned N>
struct DequeIterator {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
};

template <typename T, typename A, unsigned N>
struct DequeBase {
  T** mpPtrArray;                                    // +0x00
  unsigned int mnPtrArraySize;                       // +0x04
  DequeIterator<T, T*, T&, N> mItBegin;              // +0x08
  DequeIterator<T, T*, T&, N> mItEnd;                // +0x18
  A mAllocator;                                      // +0x28
};

template <typename T, typename A = allocator, unsigned N = 64>
class deque : public DequeBase<T, A, N> {};

}  // namespace eastl
#endif
