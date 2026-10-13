// eastl::list with the RETAIL layout (0xc: anchor node + allocator, = dev).  Hand-maintained.
#ifndef GAME_EASTL_LIST_H
#define GAME_EASTL_LIST_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};

template <typename T>
struct ListNode : public ListNodeBase {
  T mValue;
};

template <typename T, typename A = allocator>
class list {
 public:
  ListNodeBase mNode;   // +0x0
  A mAllocator;         // +0x8
};

struct intrusive_list_node {
  intrusive_list_node* mpNext;
  intrusive_list_node* mpPrev;
};

// eastl::intrusive_list<T> (fix pass 3): dev PDB intrusive_list_base 0x8 {intrusive_list_node mAnchor}; every
// intrusive_list<T> instantiation is 0x8 with that base and no members of its own (SP::cJobData mDependencies at 0x38 /
// mDependents at 0x40, exact-backed by s0068f670).  Layout only: no member functions (the slices walk mAnchor by hand).
class intrusive_list_base {
 public:
  intrusive_list_node mAnchor;   // +0x0
};

template <typename T = intrusive_list_node>
class intrusive_list : public intrusive_list_base {
 public:
};

}  // namespace eastl

#endif
