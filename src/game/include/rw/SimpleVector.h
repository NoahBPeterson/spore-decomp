// rw::SimpleVector<T>: RenderWare's resource-backed vector (rw::core::arena::ArenaDictEntry / ArenaSectionSubreferencesRecord
// instantiations).  Hand-maintained.  Layout = the dev PDB (work/devbuild/types.json): 0x20 {IResourceAllocator*
// m_allocator, Resource m_storage (0x10), T* m_elements, unsigned m_capacity, unsigned m_size}.  Unverified in retail.
#ifndef GAME_RW_SIMPLEVECTOR_H
#define GAME_RW_SIMPLEVECTOR_H
#include "rw/Resource.h"
namespace rw {
class IResourceAllocator;
#pragma pack(push, 8)
template <class T>
class SimpleVector {
 public:
  rw::IResourceAllocator* m_allocator;
  rw::Resource m_storage;
  T* m_elements;
  unsigned int m_capacity;
  unsigned int m_size;
};
#pragma pack(pop)
}  // namespace rw
#endif
