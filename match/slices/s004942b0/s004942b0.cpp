// Slice s004942b0 (batch w1g0, slice 91), 0x004942b0..0x004956??.
// /Od editor-region code. One very large routine (5113 bytes); only the entry
// (a Matrix3 copy from param_3 and the manager guard) is reconstructed.

#include "types.h"

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

struct cSPEditorBlock {
    char pad[0x2000];
};

// @ 0x004942b0
int FUN_004942b0(cSPEditorBlock* p, char* a, float* b) {
    if (p == 0)
        return 0;
    Matrix3 m;
    m.Assign(b);
    (void)a;
    return 0;
}
