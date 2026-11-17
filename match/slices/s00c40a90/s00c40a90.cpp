// Scalar deleting destructor (0x00c40a90): run the destructor (0xc40720), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c40a90(void* p);   // 0x00f47380

struct Object_c40a90 {
    ~Object_c40a90();        // 0x00c40720
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c40a90
void* Object_c40a90::DeletingDtor(unsigned int flags)
{
    this->~Object_c40a90();
    if (flags & 1)
        Free_c40a90(this);
    return this;
}
