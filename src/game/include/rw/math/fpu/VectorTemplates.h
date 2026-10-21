// rw::math::fpu::Vector2Template/Vector3Template/Vector4Template<float, 0> and Matrix33Template<float, 0>: the RenderWare
// math value types that cSPVector2/3/4, cSPColorRGB/RGBA and cSPMatrix3 derive from.  Hand-maintained.
// Layout = the dev PDB (work/devbuild/types.json): Vector2 0x8 {x, y}, Vector3 0xc {x, y, z}, Vector4 0x10 {x, y, z, w},
// Matrix33 0x24 {xAxis, yAxis, zAxis}; Matrix44 0x40 {xAxis, yAxis, zAxis, wAxis} (Vector4Template rows); Quaternion 0x10
// {x, y, z, w} (fix pass 3: cSPMatrix4 / cSPQuaternion derive from the <float,0> instantiations; unverified in retail).  The PDB's PaddingForAlignment arrays overlap the last component (the Aligned=1
// variants pad to 16); only the <float,0> instantiations exist in the pilot.
#ifndef GAME_RW_MATH_FPU_VECTORTEMPLATES_H
#define GAME_RW_MATH_FPU_VECTORTEMPLATES_H
namespace rw { namespace math { namespace fpu {
template <class T, int Aligned> class Vector2Template { public: T x, y; };
template <class T, int Aligned> class Vector3Template { public: T x, y, z; };
template <class T, int Aligned> class Vector4Template { public: T x, y, z, w; };
template <class T, int Aligned> class Matrix33Template { public: Vector3Template<T, Aligned> xAxis, yAxis, zAxis; };
template <class T, int Aligned> class Matrix44Template { public: Vector4Template<T, Aligned> xAxis, yAxis, zAxis, wAxis; };
template <class T, int Aligned> class QuaternionTemplate { public: T x, y, z, w; };
} } }
#endif
