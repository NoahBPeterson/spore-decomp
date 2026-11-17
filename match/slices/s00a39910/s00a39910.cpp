// Scalar deleting destructor (0x00a39910): run the destructor (0xa39710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a39910(void* p);   // 0x00f47380

struct Object_a39910 {
    ~Object_a39910();        // 0x00a39710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a39910
void* Object_a39910::DeletingDtor(unsigned int flags)
{
    this->~Object_a39910();
    if (flags & 1)
        Free_a39910(this);
    return this;
}
