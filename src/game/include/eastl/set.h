// eastl::set / multiset on the rbtree of map.h.  Hand-maintained.
#ifndef GAME_EASTL_SET_H
#define GAME_EASTL_SET_H
#include "eastl/map.h"

namespace eastl {

template <typename K, typename C = less<K>, typename A = allocator>
class set : public rbtree<K, K, C, A, use_self<K>, false, true> {};

template <typename K, typename C = less<K>, typename A = allocator>
class multiset : public rbtree<K, K, C, A, use_self<K>, false, false> {};

}  // namespace eastl

#endif
