// Slice s004974e0 (batch w1g0, slice 95), 0x004974e0..0x0049846d.
// /Od editor-region code.

#include "types.h"

struct Vector3 {
    float x, y, z;
};

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

struct FlagOwner {
    void SetFlag(int flag, char v);       // 0x00435a10
};

void FUN_00498230(int p, char flag);
void* __stdcall FUN_00401050(int key, int a, int p, int b);
struct X5ae40 {
    void F();                             // 0x0045ae40
};
void FUN_00498470();
char FUN_00498470_c(void* p, void* v, void* m1, void* m2, char a, float b, char c, int d);
void FUN_0043ffa0();
void RepinBlockToTorso(void* p, Vector3 v, Matrix3 m, int a);

struct X982 {
    char pad0[0x340];
    void** begin;                          // 0x340
    void** end;                            // 0x344
    char pad2[0xdc8 - 0x348];
    uint32_t bits[1];                      // 0xdc8
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// @ 0x00498230
void FUN_00498230(int p, char flag) {
    ((FlagOwner*)p)->SetFlag(0xf, flag);
    int* pv = (int*)(p + 0x340);
    int n = (pv[1] - pv[0]) >> 2;
    for (int i = 0; i < n; ++i) {
        int child;
        int* slot = (int*)(pv[0] + i * 4);
        child = *slot;
        FUN_00498230(child, flag);
    }
}

// @ 0x004983d0
void FUN_004983d0(X982* p, uint8_t flag) {
    if (p->GetFlag(0xf)) {
        if (flag == 0)
            ((X5ae40*)FUN_00401050(0x3f1bf55, 0, (int)p, 0))->F();
    } else {
        if (flag != 0)
            ((X5ae40*)FUN_00401050(0x3f1bf56, 0, (int)p, 0))->F();
    }
}

// @ 0x004982b0
char FUN_004982b0(char* p, char a, float b, char c) {
    Vector3 v;
    v.x = *(float*)(p + 0x48);
    v.y = *(float*)(p + 0x4c);
    v.z = *(float*)(p + 0x50);
    Matrix3 m1;
    m1.Assign(p + 0xa8);
    Matrix3 m2;
    m2.Assign(p + 0xf0);
    char r = FUN_00498470_c(p, &v, &m1, &m2, a, b, c, 1);
    if (r) {
        FUN_0043ffa0();
        RepinBlockToTorso(p, v, m1, 0);
    }
    return r;
}

// @ 0x004974e0
void FUN_004974e0(void* p, void* a, void* b) {
    (void)p;
    (void)a;
    (void)b;
}

// @ 0x00497f20
void FUN_00497f20(void* p, void* a, void* b, void* c) {
    (void)p;
    (void)a;
    (void)b;
    (void)c;
}
