// Slice s00493640 (batch w1g0, slice 90), 0x00493640..0x004942a3.
// /Od editor-region code. 00494270 is a small wrapper (reconstructed faithfully);
// 00493640 and MoveBlockAndTranslateSnappedBlocks are large and are skeletons.

#include "types.h"

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);
};

// out-of-line copy ctor: cl emits an out-of-line copy of the by-value argument
Matrix3::Matrix3(const Matrix3& o) {
    for (int i = 0; i < 9; ++i)
        m[i] = o.m[i];
}

// forward decls
void FUN_00493ce0(void* a, void* b, Matrix3 m);
int FUN_00493640(float* p, float a, float b, float c, int* d);

// @ 0x00494270
void* FUN_00494270(void* a, void* b) {
    FUN_00493ce0(a, b, *(Matrix3*)((char*)b + 0xa8));
    return a;
}

// @ 0x00493640
int FUN_00493640(float* p, float a, float b, float c, int* d) {
    (void)p;
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    return 0;
}

// @ 0x00493ce0
void FUN_00493ce0(void* a, void* b, Matrix3 m) {
    (void)a;
    (void)b;
    (void)m;
}
