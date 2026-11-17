// Scalar deleting destructor (0x00b5e3d0): run the destructor (0xb5e380), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b5e3d0(void* p);   // 0x00f47380

struct Object_b5e3d0 {
    ~Object_b5e3d0();        // 0x00b5e380
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b5e3d0
void* Object_b5e3d0::DeletingDtor(unsigned int flags)
{
    this->~Object_b5e3d0();
    if (flags & 1)
        Free_b5e3d0(this);
    return this;
}
