// Scalar deleting destructor (0x00c9c4e0): run the destructor (0xc9c120), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c9c4e0(void* p);   // 0x00f47380

struct Object_c9c4e0 {
    ~Object_c9c4e0();        // 0x00c9c120
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c9c4e0
void* Object_c9c4e0::DeletingDtor(unsigned int flags)
{
    this->~Object_c9c4e0();
    if (flags & 1)
        Free_c9c4e0(this);
    return this;
}
