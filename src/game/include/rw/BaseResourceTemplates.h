// rw::BaseResourceDescriptors<N>, rw::BaseResourceDescriptorType<T>, rw::BaseResources<N>: the RenderWare resource
// templates that rw::ResourceDescriptor (0x20) / rw::Resource (0x10) derive from.  Hand-maintained.
// Layout = the dev PDB (work/devbuild/types.json): BaseResourceDescriptors<4> 0x20 {BaseResourceDescriptor
// m_baseResourceDescriptors[4]}, BaseResourceDescriptorType<0..3> 0x8 (a BaseResourceDescriptor, no members of its own),
// BaseResources<4> 0x10 {void* m_baseResources[4]}.  Only N = 4 exists in the dev build.  Unverified in retail.
#ifndef GAME_RW_BASERESOURCETEMPLATES_H
#define GAME_RW_BASERESOURCETEMPLATES_H
#include "rw/BaseResourceDescriptor.h"
namespace rw {
#pragma pack(push, 8)
template <int T>
class BaseResourceDescriptorType : public BaseResourceDescriptor {
 public:
};
template <int N>
class BaseResourceDescriptors {
 public:
  BaseResourceDescriptor m_baseResourceDescriptors[N];
};
template <int N>
class BaseResources {
 public:
  void* m_baseResources[N];
};
#pragma pack(pop)
}  // namespace rw
#endif
