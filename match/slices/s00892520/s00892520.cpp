#include "types.h"

// @ 0x00892520
// Reads nothing and writes a zero 2-float result into the third argument,
// returning false: `out->x = 0; out->y = 0; return false;`.
bool __stdcall FUN_00892520(int a, int b, float* out, int c, int d)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    return false;
}
