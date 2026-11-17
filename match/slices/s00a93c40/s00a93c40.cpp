// Scalar deleting destructor (0x00a93c40): run the destructor (0xa93910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a93c40(void* p);   // 0x00f47380

struct Object_a93c40 {
    ~Object_a93c40();        // 0x00a93910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a93c40
void* Object_a93c40::DeletingDtor(unsigned int flags)
{
    this->~Object_a93c40();
    if (flags & 1)
        Free_a93c40(this);
    return this;
}
