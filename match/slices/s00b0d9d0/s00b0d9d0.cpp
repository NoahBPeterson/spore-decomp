// Scalar deleting destructor (0x00b0d9d0): run the destructor (0xb0d610), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b0d9d0(void* p);   // 0x00f47380

struct Object_b0d9d0 {
    ~Object_b0d9d0();        // 0x00b0d610
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b0d9d0
void* Object_b0d9d0::DeletingDtor(unsigned int flags)
{
    this->~Object_b0d9d0();
    if (flags & 1)
        Free_b0d9d0(this);
    return this;
}
