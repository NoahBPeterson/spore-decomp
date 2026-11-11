// Slice s0129e230: fill a global 4x4 matrix: a candidate value on the diagonal, zero elsewhere.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

extern float g_f_01485720;   // 0x01485720
float g_matrix_015f39c0[16]; // 0x015f39c0

// @ 0x0129e230
void FUN_0129e230()
{
    float d = g_f_01485720;
    g_matrix_015f39c0[0]  = d;
    g_matrix_015f39c0[1]  = 0.0f;
    g_matrix_015f39c0[2]  = 0.0f;
    g_matrix_015f39c0[3]  = 0.0f;
    g_matrix_015f39c0[4]  = 0.0f;
    g_matrix_015f39c0[5]  = d;
    g_matrix_015f39c0[6]  = 0.0f;
    g_matrix_015f39c0[7]  = 0.0f;
    g_matrix_015f39c0[8]  = 0.0f;
    g_matrix_015f39c0[9]  = 0.0f;
    g_matrix_015f39c0[10] = d;
    g_matrix_015f39c0[11] = 0.0f;
    g_matrix_015f39c0[12] = 0.0f;
    g_matrix_015f39c0[13] = 0.0f;
    g_matrix_015f39c0[14] = 0.0f;
    g_matrix_015f39c0[15] = d;
}
