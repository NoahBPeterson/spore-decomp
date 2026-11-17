// Scalar deleting destructor (0x00728250): run the destructor (0x7281d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_728250(void* p);   // 0x00f47380

struct Object_728250 {
    ~Object_728250();        // 0x007281d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00728250
void* Object_728250::DeletingDtor(unsigned int flags)
{
    this->~Object_728250();
    if (flags & 1)
        Free_728250(this);
    return this;
}
