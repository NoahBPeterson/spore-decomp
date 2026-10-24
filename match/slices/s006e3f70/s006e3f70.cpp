// slice s006e3f70: 4x4 matrix multiply (assembled through the 16-dword Set
// helper 0x006e2ae0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Matrix44 {
    float m[16];
    Matrix44& Set(const float* a, const float* b, const float* c, const float* d);
};
float* Matrix44Multiply(float* out, const float* lhs, const float* rhs);

// @ 0x006e3f70
float* Matrix44Multiply(float* out, const float* lhs, const float* rhs) {
    // The w column (element 3 of each row) is intentionally left unset, exactly as
    // retail does: only 12 of the 16 dwords are computed before the Set helper
    // copies four 4-dword rows into the destination.
    float r0[4];
    float r1[4];
    float r2[4];
    float r3[4];
    float f1 = lhs[0xc];
    float f2 = rhs[1];
    float f3 = lhs[0xd];
    float f4 = *rhs;
    float f5 = lhs[0xe];
    r3[0] = rhs[0xc] + (rhs[8] * f5 + (rhs[4] * f3 + f1 * f4));
    r3[1] = rhs[0xd] + (rhs[9] * f5 + (rhs[5] * f3 + f2 * f1));
    r3[2] = rhs[0xe] + (rhs[10] * f5 + (rhs[6] * f3 + rhs[2] * f1));
    float f6 = lhs[8];
    float f7 = lhs[9];
    float f8 = lhs[10];
    r2[1] = rhs[9] * f8 + (rhs[5] * f7 + f6 * f2);
    r2[0] = f8 * rhs[8] + (f7 * rhs[4] + f6 * f4);
    r2[2] = rhs[10] * f8 + (rhs[6] * f7 + f6 * rhs[2]);
    float f9 = lhs[4];
    float f10 = lhs[5];
    float f11 = lhs[6];
    r1[0] = rhs[8] * f11 + (rhs[4] * f10 + f9 * f4);
    r1[1] = rhs[9] * f11 + (rhs[5] * f10 + f9 * f2);
    r1[2] = rhs[10] * f11 + (rhs[6] * f10 + f9 * rhs[2]);
    float f12 = lhs[0];
    float f13 = lhs[1];
    float f14 = lhs[2];
    r0[0] = f14 * rhs[8] + (f13 * rhs[4] + f12 * f4);
    r0[1] = rhs[9] * f14 + (rhs[5] * f13 + f12 * f2);
    r0[2] = rhs[10] * f14 + (rhs[6] * f13 + f12 * rhs[2]);
    ((Matrix44*)out)->Set(r0, r1, r2, r3);
    return out;
}
