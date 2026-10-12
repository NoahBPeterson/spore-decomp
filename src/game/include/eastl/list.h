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

}  // namespace eastl

#endif
