// eastl::rbtree / map / multimap with the RETAIL layout (= dev, allocator aside): the comparator
// base (1 byte, padded), the anchor node (0x10), the element count, the allocator.  Hand-maintained.
#ifndef GAME_EASTL_MAP_H
#define GAME_EASTL_MAP_H
#include "game/types.h"
#include "eastl/allocator.h"

namespace eastl {

template <typename T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
// empty functor bases (EASTL functional.h; no data, so no layout to verify)
template <typename A, typename R> struct unary_function { typedef A argument_type; typedef R result_type; };
template <typename A1, typename A2, typename R> struct binary_function {
  typedef A1 first_argument_type; typedef A2 second_argument_type; typedef R result_type;
};
template <typename T> struct use_self {};
template <typename T> struct use_first {};

template <typename K, typename V>
struct pair {
  K first;
  V second;
};

struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};

template <typename V>
struct rbtree_node : public rbtree_node_base {
  V mValue;
};

template <typename V>
struct rbtree_iterator {
  rbtree_node<V>* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(rbtree_node_base* n) : mpNode((rbtree_node<V>*)n) {}
  V& operator*() const { return mpNode->mValue; }
  V* operator->() const { return &mpNode->mValue; }
  bool operator==(const rbtree_iterator& o) const { return mpNode == o.mpNode; }
  bool operator!=(const rbtree_iterator& o) const { return mpNode != o.mpNode; }
};

// The comparator lives in a base so the tree can hold a stateless one; it is 1 byte in the dev
// build (not optimised away: mAnchor sits at +4).
template <typename C>
struct rb_base {
  C mCompare;
};

template <typename K, typename V, typename C, typename A, typename E, bool bMutableIterators, bool bUniqueKeys>
class rbtree : public rb_base<C> {
 public:
  typedef K key_type;
  typedef V value_type;
  typedef rbtree_node<V> node_type;
  typedef rbtree_iterator<V> iterator;

  rbtree_node_base mAnchor;   // +0x4
  uint32_t mnSize;            // +0x14
  A mAllocator;               // +0x18

  rbtree_node_base* anchor() { return &mAnchor; }
  iterator begin() { return iterator(mAnchor.mpNodeLeft); }
  iterator end() { return iterator(&mAnchor); }
  uint32_t size() const { return mnSize; }
  bool empty() const { return mnSize == 0; }
  iterator find(const K& key);   // out of line in retail (per instantiation)
};

template <typename K, typename V, typename C = less<K>, typename A = allocator>
class map : public rbtree<K, pair<const K, V>, C, A, use_first<pair<const K, V> >, true, true> {};

template <typename K, typename V, typename C = less<K>, typename A = allocator>
class multimap : public rbtree<K, pair<const K, V>, C, A, use_first<pair<const K, V> >, true, false> {};

}  // namespace eastl

#endif
