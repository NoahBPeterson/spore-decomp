// Scalar deleting destructor (0x00b34f90): run the destructor (0xe88a30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b34f90(void* p);   // 0x00f47380

struct Object_b34f90 {
    ~Object_b34f90();        // 0x00e88a30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b34f90
void* Object_b34f90::DeletingDtor(unsigned int flags)
{
    this->~Object_b34f90();
    if (flags & 1)
        Free_b34f90(this);
    return this;
}
