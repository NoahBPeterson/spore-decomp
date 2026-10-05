// Slice s00496d30 (batch w1g0, slice 94), 0x00496d30..0x004974d8.
// /Od editor-region code.

#include "types.h"

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

char FUN_004a7e60(void* p);
char FUN_0043bd80(void* self, float f, Matrix3 m);

struct X973 {
    char pad[0xdc8];
    uint32_t flags;                       // 0xdc8
};

// @ 0x004973f0
char FUN_004973f0(X973* p, void* mat, float f, char flag) {
    char result = 0;
    if (p != 0) {
        Matrix3 m;
        if (mat == 0) {
            const float* src = (const float*)((char*)p + 0xf0);
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        } else {
            const float* src = (const float*)mat;
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        }
        result = 0;
        char r = FUN_0043bd80(p, f, m);
        if (r) {
            if ((p->flags & 1) == 0) {
                result = 1;
            } else {
                if (FUN_004a7e60(p) || flag)
                    result = 1;
            }
        }
    }
    return result;
}

// @ 0x00496d30
void FUN_00496d30(void* p, void* a, void* b, void* c) {
    (void)p;
    (void)a;
    (void)b;
    (void)c;
}
