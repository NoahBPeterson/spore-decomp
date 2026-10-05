// Slice s0049b340 (batch w1g0, slice 99), 0x0049b340..0x0049c20c.
// /Od editor-region code.

#include "types.h"

struct BitOwner {
    char pad0[0xdc8];
    uint32_t bits[2];                     // 0xdc8, 0xdcc
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// @ 0x0049b340
bool FUN_0049b340(BitOwner* p) {
    if (p != 0) {
        if (p->GetFlag(7))
            return true;
        if (p->GetFlag(8))
            return true;
        if (p->GetFlag(0x23))
            return true;
    }
    return false;
}

// @ 0x0049c0f0
struct Y9c0 {
    char pad0[0x3c9];
    char flag;                            // 0x3c9
    char pad1[0x3e0 - 0x3ca];
    void* tracker;                        // 0x3e0
    void Set(char v);
};
void Y9c0::Set(char v) {
    this->flag = v;
    Y9c0* t = (Y9c0*)this->tracker;
    if (t != 0) {
        Y9c0* t2 = (Y9c0*)this->tracker;
        t2->flag = v;
    }
}

// @ 0x0049b460
void FUN_0049b460(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
}

// @ 0x0049b8b0
void FUN_0049b8b0(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
}

// @ 0x0049bcc0
void FUN_0049bcc0(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
}

// @ 0x0049c140
void FUN_0049c140(void* out, void* p, float x, float y, float z) {
    (void)out; (void)p; (void)x; (void)y; (void)z;
}
