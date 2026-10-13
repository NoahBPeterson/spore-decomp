// __m128: the SSE vector type of the compiler's <xmmintrin.h> (rw::math::vpu::Vector3/Vector4/VecFloat hold one).
// Hand-maintained: the generated `struct __m128 { float m128_f32[4]; }` would collide with <xmmintrin.h>'s union in any
// TU that includes the intrinsics, and the dev code used the compiler's type.
#ifndef GAME_M128_H
#define GAME_M128_H
#include <xmmintrin.h>
#endif  // GAME_M128_H
