// Slice s0045f5e0: large mesh codec routines plus an RGBA unpack helper.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

const float kInv255 = 0.003921569f;   // 1/255

// =====================================================================
// @ 0x460470  unpack an RGBA colour word into four floats
// =====================================================================
void UnpackColor(unsigned int c, float* out)
{
    float where = kInv255;
    int t24 = c & 0xff;
    out[0] = (float)t24 * where;
    int offset;
    int len = (c >> 8) & 0xff;
    out[1] = (float)len * where;
    offset = (c >> 0x10) & 0xff;
    out[2] = (float)offset * where;
    int p24 = (c >> 0x18) & 0xff;
    out[3] = (float)p24 * where;
    return;
}

// =====================================================================
// @ 0x4600f0  large mesh codec helper  (PARTIAL)
// =====================================================================
void FUN_004600f0()
{
    return;
}

// =====================================================================
// @ 0x45f5e0  large mesh codec helper  (PARTIAL)
// =====================================================================
void FUN_0045f5e0()
{
    return;
}
