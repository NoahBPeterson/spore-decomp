// eastl::vector_map / vector_set: a vector plus the comparator word (0x18 in retail).  Hand-maintained.
#ifndef GAME_EASTL_VECTOR_MAP_H
#define GAME_EASTL_VECTOR_MAP_H
#include "eastl/vector.h"
#include "eastl/map.h"   // pair, less

namespace eastl {

template <typename K, typename V, typename C = less<K>, typename A = allocator, typename RAC = vector<pair<K, V>, A> >
class vector_map : public RAC {
 public:
  C mCompare;   // +0x14, padded to 4
};

template <typename K, typename C = less<K>, typename A = allocator, typename RAC = vector<K, A> >
class vector_set : public RAC {
 public:
  C mCompare;
};

}  // namespace eastl

#endif
