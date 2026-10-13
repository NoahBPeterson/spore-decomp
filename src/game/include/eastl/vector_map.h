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
  // The default constructor zeroes begin/end/capacity and nothing else (the allocator slot and the comparator are not
  // written): the property-list constructors 0x6a1b90 / 0x6a1c40 / 0x6a1ca0 (byte-exact in s006a11b0) store three zero
  // words at +0x18/+0x1c/+0x20 and skip +0x24..+0x2c.  Kept here, not in vector, so that other vector users keep their layout/codegen.
  vector_map() { this->mpBegin = 0; this->mpEnd = 0; this->mpCapacity = 0; }
  // Out-of-line in retail, one instantiation per key/value type: vector_map<unsigned int, Variant>::erase is 0x006a2cb0 (the
  // byte-exact cPropertyList::RemoveProperty 0x6a2ef0 calls it with the key by reference and discards the count).
  unsigned int erase(const K& key);
};

template <typename K, typename C = less<K>, typename A = allocator, typename RAC = vector<K, A> >
class vector_set : public RAC {
 public:
  C mCompare;
};

}  // namespace eastl

#endif
