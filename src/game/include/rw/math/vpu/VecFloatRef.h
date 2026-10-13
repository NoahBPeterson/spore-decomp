// rw::math::vpu::VecFloatRef<N>: a reference to lane N of an __m128 (what Vector3::GetX/X() return).  Hand-maintained.
// Layout = the dev PDB (work/devbuild/types.json): VecFloatRef<0..2> 0x4 {__m128* mV}.  Unverified in retail.
#ifndef GAME_RW_MATH_VPU_VECFLOATREF_H
#define GAME_RW_MATH_VPU_VECFLOATREF_H
#include "__m128.h"
namespace rw { namespace math { namespace vpu {
#pragma pack(push, 8)
template <int N>
class VecFloatRef {
 public:
  __m128* mV;
};
#pragma pack(pop)
} } }  // namespace rw::math::vpu
#endif
