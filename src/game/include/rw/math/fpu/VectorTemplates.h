// rw::math::fpu::Vector2Template/Vector3Template/Vector4Template<float, 0> and Matrix33Template<float, 0>: the RenderWare
// math value types that cSPVector2/3/4, cSPColorRGB/RGBA and cSPMatrix3 derive from.  Hand-maintained.
// Layout = the dev PDB (work/devbuild/types.json): Vector2 0x8 {x, y}, Vector3 0xc {x, y, z}, Vector4 0x10 {x, y, z, w},
// Matrix33 0x24 {xAxis, yAxis, zAxis}.  The PDB's PaddingForAlignment arrays overlap the last component (the Aligned=1
// variants pad to 16); only the <float,0> instantiations exist in the pilot.
#ifndef GAME_RW_MATH_FPU_VECTORTEMPLATES_H
#define GAME_RW_MATH_FPU_VECTORTEMPLATES_H
namespace rw { namespace math { namespace fpu {
template <class T, int Aligned> struct Vector2Template { T x, y; };
template <class T, int Aligned> struct Vector3Template { T x, y, z; };
template <class T, int Aligned> struct Vector4Template { T x, y, z, w; };
template <class T, int Aligned> struct Matrix33Template { Vector3Template<T, Aligned> xAxis, yAxis, zAxis; };
} } }
#endif
