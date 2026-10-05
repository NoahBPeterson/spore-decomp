// slice s0057af00 — SP::cAppModeEditorBase::Pick (oversized; skeleton only)
#include "types.h"

// 0x1c-byte result: 5 floats, a byte flag, and an int (offsets +0,+4,+8,+0xc,+0x10,+0x14,+0x18)
struct PickResult28 {
    float mF[5];
    uint8_t mByte;      // +0x14
    uint8_t pad[3];
    int32_t mInt;       // +0x18
};

struct cAppModeEditorBase {
    PickResult28 Pick(const void* a, const void* b, bool flag);
};

// @ 0x0057af00  (4270 bytes) — NOT reconstructed (oversized function; see docs/Papercuts.md)
PickResult28 cAppModeEditorBase::Pick(const void* a, const void* b, bool flag)
{
    PickResult28 r = {};
    return r;
}
