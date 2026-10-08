// Slice s00e5a430 -- SP::sLevelGetTextureCoord (00e5a850): converts a level-relative position into the two
// signed-byte texture coordinates, scaled by the level size and the box-size multiplier.
// Module flags (guess, verify): /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cCellGameTC { char pad[0x514c]; float mLevelScale; };   // only the field this function reads
extern cCellGameTC* gspCellGame;                               // 0x016b3c04
extern float kLevelSize[];                                      // 0x01483bd0, one float per level

namespace SP {

float sGetBoxSizeMultiplier2(int level, int unused);            // 0x00e51ff0, cdecl, float in st0

__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline uint32_t WrapTexCoord(int v) {
    uint32_t u = (uint32_t)v & 0x8000007fu;
    if ((int)u < 0) u = (u - 1 | 0xffffff80u) + 1;
    return u;
}

// @ 0x00e5a850
void sLevelGetTextureCoord(int level, float* pos, uint32_t* out0, uint32_t* out1) {
    // volatile temps force each float to be rounded to 32 bits at the same points as the original's stores
    volatile float size = (kLevelSize[level] / gspCellGame->mLevelScale) * (sGetBoxSizeMultiplier2(level, 0) * 0.85f);
    volatile float inv = 1.0f / size;
    volatile float p0 = pos[0] * inv;
    *out0 = WrapTexCoord(RoundToInt(p0 * 128.0f));
    volatile float p1 = pos[1] * inv;
    *out1 = WrapTexCoord(RoundToInt(p1 * 128.0f));
    if ((int)*out0 < 1) *out0 = *out0 + 0x80;
    if ((int)*out1 < 1) *out1 = *out1 + 0x80;
}

}  // namespace SP
