// Slice s008924f0 -- trivial struct copy-out: 0x11 dwords from +0xc0 into the
// caller's buffer, always returning true.
#include "types.h"

struct Blob924f0 {
    int mWords[0x11];               // 68 bytes
};

struct Obj924f0 {
    char      pad000[0xc0];
    Blob924f0 mBlob;                // +0xc0

    bool CopyTo(Blob924f0* out);
};

// @ 0x008924f0
bool Obj924f0::CopyTo(Blob924f0* out)
{
    *out = mBlob;
    return true;
}
