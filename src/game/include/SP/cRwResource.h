// SP::cRwResource<T, TypeId>: a SP::cGraphicsResource holding the RenderWare object (dev: <rw::core::arena::Arena,
// 793667611> and <rw::graphics::Raster, 793667612> are 0x1c, base cGraphicsResource 0x18, mData at +0x18).
// Hand-maintained.  Retail layout unverified.
#ifndef GAME_SP_CRWRESOURCE_H
#define GAME_SP_CRWRESOURCE_H
#include "SP/cGraphicsResource.h"
namespace SP {
template <typename T, unsigned int TypeId>
struct cRwResource : public SP::cGraphicsResource {
  T* mData;
};
}  // namespace SP
#endif
