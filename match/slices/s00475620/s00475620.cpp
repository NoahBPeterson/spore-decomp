// Slice s00475620: Forwarder-like function (shape of 0x00422d60)
// Frame layout: flag at [ebp-3], this at [ebp-8], param1 at [ebp+8], param2 at [ebp+0xc]
// Calls eastl::vector DoAssignFromIterator at 0x004d04f0

#include "types.h"

struct Forwarder {
    void FUN_004d04f0(void* first, void* last, unsigned char flag);  // 0x004d04f0
    void FUN_00475620(uint32_t a, uint32_t b);
};

// @ 0x00475620
void Forwarder::FUN_00475620(uint32_t a, uint32_t b)
{
    unsigned char x, y, z, flag;  // frame layout: flag lands at [ebp-3]
    // Use z as the flag parameter (same as Fwd1 uses z)
    FUN_004d04f0((void*)a, (void*)b, z);
}
