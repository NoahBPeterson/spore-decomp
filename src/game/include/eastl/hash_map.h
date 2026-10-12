// eastl::hashtable / hash_map with the RETAIL layout: 0x20 with eastl::allocator (= dev), 0x24 with
// EASTLCoreAllocator (dev 0x28).  The hash/equal functors occupy the first word.  Hand-maintained.
#ifndef GAME_EASTL_HASH_MAP_H
#define GAME_EASTL_HASH_MAP_H
#include "game/types.h"
#include "eastl/allocator.h"
#include "eastl/map.h"   // pair, use_first

namespace eastl {

template <typename T> struct hash { uint32_t operator()(const T& v) const { return (uint32_t)v; } };
template <typename T> struct equal_to { bool operator()(const T& a, const T& b) const { return a == b; } };

struct prime_rehash_policy {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
};

template <typename V>
struct hash_node {
  V mValue;
  hash_node* mpNext;
};

template <typename K, typename V, typename A, typename E, typename P, typename H>
class hashtable {
 public:
  typedef V value_type;
  typedef hash_node<V> node_type;

  uint32_t mFunctors;                 // +0x00  hash_code_base: the (empty) functors, one word
  node_type** mpBucketArray;          // +0x04
  uint32_t mnBucketCount;             // +0x08
  uint32_t mnElementCount;            // +0x0c
  prime_rehash_policy mRehashPolicy;  // +0x10
  A mAllocator;                       // +0x1c

  uint32_t size() const { return mnElementCount; }
  bool empty() const { return mnElementCount == 0; }
};

template <typename K, typename V, typename H = hash<K>, typename P = equal_to<K>, typename A = allocator, bool bCache = false>
class hash_map : public hashtable<K, pair<const K, V>, A, use_first<pair<const K, V> >, P, H> {};

template <typename K, typename V, typename H = hash<K>, typename P = equal_to<K>, typename A = allocator, bool bCache = false>
class hash_multimap : public hashtable<K, pair<const K, V>, A, use_first<pair<const K, V> >, P, H> {};

template <typename K, typename H = hash<K>, typename P = equal_to<K>, typename A = allocator, bool bCache = false>
class hash_set : public hashtable<K, K, A, use_self<K>, P, H> {};

}  // namespace eastl

#endif
