// Slice s00491b40 (batch w1g0, slice 88), 0x00491b40..0x00491c??.
// /Od editor-region code. One very large routine (3458 bytes) that has bit 0x16
// of the block's flag word at +0xdc8 as an early guard and then does extensive
// bounding-box / basis math. Only a skeleton is reconstructed here.

#include "types.h"

struct cSPEditorBlock {
    char pad[0x2000];
};

// @ 0x00491b40
float FUN_00491b40(cSPEditorBlock* p, int a, int b, int c, float d) {
    if (p == 0)
        return -1.0f;
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    return -1.0f;
}
