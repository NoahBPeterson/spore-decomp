// Scalar deleting destructor (0x00bae6d0): run the destructor (0xbabe70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bae6d0(void* p);   // 0x00f47380

struct Object_bae6d0 {
    ~Object_bae6d0();        // 0x00babe70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bae6d0
void* Object_bae6d0::DeletingDtor(unsigned int flags)
{
    this->~Object_bae6d0();
    if (flags & 1)
        Free_bae6d0(this);
    return this;
}
