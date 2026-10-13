// rw::HashContainer<Policy, Traits>, rw::PreallocatedBufferPolicy<Traits>, rw::SeparateKeyAndDatumContained<K, D>: the
// RenderWare open hash table (rw::core::arena::ArenaIdMap).  Hand-maintained.
// Layout = the dev PDB (work/devbuild/types.json): HashContainer<PreallocatedBufferPolicy<ArenaIdMapHashTraits>,
// ArenaIdMapHashTraits> 0xc = the policy base (0x8: {contents, capacity}) + `size`; nested Index 0x8 {pos, size} and
// IteratorT<E> 0x8 {ptr, end}; SeparateKeyAndDatumContained<unsigned, Arena*> 0x8 {key, data}.  Unverified in retail.
#ifndef GAME_RW_HASHCONTAINER_H
#define GAME_RW_HASHCONTAINER_H
namespace rw {
#pragma pack(push, 8)
template <class K, class D>
class SeparateKeyAndDatumContained {
 public:
  K key;
  D data;
};
template <class Traits>
class PreallocatedBufferPolicy {
 public:
  void* contents;      // SeparateKeyAndDatumContained<..>* (the element type comes from Traits in RenderWare)
  unsigned int capacity;
};
template <class Policy, class Traits>
class HashContainer : public Policy {
 public:
  class Index {
   public:
    unsigned int pos;
    unsigned int size;
  };
  template <class E>
  class IteratorT {
   public:
    E* ptr;
    E* end;
  };
  unsigned int size;
};
#pragma pack(pop)
}  // namespace rw
#endif
