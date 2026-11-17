// Scalar deleting destructor (0x00d2d7b0): run the destructor (0xd2d3d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d2d7b0(void* p);   // 0x00f47380

struct Object_d2d7b0 {
    ~Object_d2d7b0();        // 0x00d2d3d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d2d7b0
void* Object_d2d7b0::DeletingDtor(unsigned int flags)
{
    this->~Object_d2d7b0();
    if (flags & 1)
        Free_d2d7b0(this);
    return this;
}
