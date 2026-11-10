// Slice s00ad33a0: scalar deleting destructor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

void EASTL_Free(void* p);  // 0x00f47380

struct Obj00ad33a0 {
    void** vftable;
    char pad[0xd4 - 4];
    void** mSecondaryVt;  // 0xd4

    void Body();  // 0x00c8a420 thiscall
    void* DeletingDtor(unsigned flags);  // 0x00ad33a0
};

// @ 0x00ad33a0
void* Obj00ad33a0::DeletingDtor(unsigned flags)
{
    mSecondaryVt = (void**)0x013ef094;
    Body();
    if (flags & 1)
        EASTL_Free(this);
    return this;
}
