// Scalar deleting destructor (0x00a63db0): run the destructor (0xa63d20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a63db0(void* p);   // 0x00f47380

struct Object_a63db0 {
    ~Object_a63db0();        // 0x00a63d20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a63db0
void* Object_a63db0::DeletingDtor(unsigned int flags)
{
    this->~Object_a63db0();
    if (flags & 1)
        Free_a63db0(this);
    return this;
}
