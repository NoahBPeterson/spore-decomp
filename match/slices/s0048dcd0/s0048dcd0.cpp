// Slice s0048dcd0: SP::EditorUtils::GetMissStackingPosition + a Vec4 helper.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec4T {
    float x, y, z, w;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

// @ 0x48e510
float* F_48e510(float* out, Vec4T& src)
{
    float z = src[0];
    float x = src[1];
    float y = src[2];
    out[0] = z;
    out[1] = x;
    out[2] = y;
    out[3] = 0.0f;
    return out;
}

namespace SP {
namespace EditorUtils {

// @ 0x48dcd0
// Best-effort skeleton of the 2110-byte miss-stacking evaluation. It consumes a
// cSPEditorManipulationStacking object (param_1+0x18c) and writes the blended
// candidate position through `out`.
int GetMissStackingPosition(int param_1, int param_2, float p3, float p4, float p5, float* out)
{
    (void)param_2; (void)p3; (void)p4; (void)p5;
    bool found = false;
    int stacking = (param_1 != 0) ? *(int*)(param_1 + 0x18c) : 0;
    if (stacking != 0) {
        // original: builds two candidate transforms, runs MoveBlockLowAngleStacking,
        // blends the block offset with the miss vector and writes out[].
        if (out) { out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f; }
    }
    return found ? 1 : 0;
}

}  // namespace EditorUtils
}  // namespace SP
