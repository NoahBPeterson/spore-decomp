// Scalar deleting destructor (0x00e018a0): run the destructor (0xe00f40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e018a0(void* p);   // 0x00f47380

struct Object_e018a0 {
    ~Object_e018a0();        // 0x00e00f40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e018a0
void* Object_e018a0::DeletingDtor(unsigned int flags)
{
    this->~Object_e018a0();
    if (flags & 1)
        Free_e018a0(this);
    return this;
}
