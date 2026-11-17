// Scalar deleting destructor (0x00a80fc0): run the destructor (0xa80d10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a80fc0(void* p);   // 0x00f47380

struct Object_a80fc0 {
    ~Object_a80fc0();        // 0x00a80d10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a80fc0
void* Object_a80fc0::DeletingDtor(unsigned int flags)
{
    this->~Object_a80fc0();
    if (flags & 1)
        Free_a80fc0(this);
    return this;
}
