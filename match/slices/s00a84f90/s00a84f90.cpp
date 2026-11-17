// Scalar deleting destructor (0x00a84f90): run the destructor (0xa84e50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a84f90(void* p);   // 0x00f47380

struct Object_a84f90 {
    ~Object_a84f90();        // 0x00a84e50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a84f90
void* Object_a84f90::DeletingDtor(unsigned int flags)
{
    this->~Object_a84f90();
    if (flags & 1)
        Free_a84f90(this);
    return this;
}
