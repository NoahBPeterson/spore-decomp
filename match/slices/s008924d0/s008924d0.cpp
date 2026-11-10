// Slice s008924d0: copy 0x1d dwords (0x74 bytes) from this+0x4c to the argument.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

struct Blob { int d[0x1d]; };

struct Widget2 {
    uint32_t pad000[0x13];       // +0x000 .. +0x04b
    Blob     mData;              // +0x04c

    bool CopyTo(Blob* dst);      // 0x008924d0
};

// @ 0x008924d0
bool Widget2::CopyTo(Blob* dst)
{
    *dst = mData;
    return true;
}
