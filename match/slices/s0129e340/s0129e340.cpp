// Slice s0129e340 -- reset a global 3x3 matrix to zero.
//
//  0x0129e340  Matrix3Zero(): store a zeroed cMatrix3 into the global at 0x15f3b08.
//              The explicit `tmp` local is what keeps cl emitting the stack temp plus
//              `rep movsd` the retail build has (a direct member-by-member store
//              compiles to nine movss instead).
#include "types.h"

// compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast

struct cMatrix3 {
    float m[3][3];

    __forceinline cMatrix3()
    {
        m[0][0] = 0.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 0.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 0.0f;
    }
};

extern cMatrix3 g_mtx_015f3b08;   // 0x15f3b08

// @ 0x0129e340
void Matrix3Zero()
{
    cMatrix3 tmp;
    g_mtx_015f3b08 = tmp;
}
