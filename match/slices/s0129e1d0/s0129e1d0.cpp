// slice s0129e1d0: initialise the 3x3 matrix global at 0x015f3a68 to one scale constant
// on the diagonal and zero elsewhere (row-major: diag = k, rest = 0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Scale written on the diagonal (read from 0x01485720).
extern const float kDiagonal;

struct Mat3 {
    float a00, a01, a02;
    float a10, a11, a12;
    float a20, a21, a22;
};

extern Mat3 g_mat15f3a68;   // 0x015f3a68

// @ 0x0129e1d0
void InitMat15f3a68()
{
    float k = kDiagonal;
    g_mat15f3a68.a00 = k; g_mat15f3a68.a01 = 0.0f; g_mat15f3a68.a02 = 0.0f;
    g_mat15f3a68.a10 = 0.0f; g_mat15f3a68.a11 = k; g_mat15f3a68.a12 = 0.0f;
    g_mat15f3a68.a20 = 0.0f; g_mat15f3a68.a21 = 0.0f; g_mat15f3a68.a22 = k;
}
