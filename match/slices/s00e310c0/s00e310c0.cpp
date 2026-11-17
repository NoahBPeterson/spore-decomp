// Scalar deleting destructor (0x00e310c0): run the destructor (0xe30f90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e310c0(void* p);   // 0x00f47380

struct Object_e310c0 {
    ~Object_e310c0();        // 0x00e30f90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e310c0
void* Object_e310c0::DeletingDtor(unsigned int flags)
{
    this->~Object_e310c0();
    if (flags & 1)
        Free_e310c0(this);
    return this;
}
