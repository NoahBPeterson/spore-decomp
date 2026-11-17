// Scalar deleting destructor (0x00bfd5f0): run the destructor (0xbfcd00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bfd5f0(void* p);   // 0x00f47380

struct Object_bfd5f0 {
    ~Object_bfd5f0();        // 0x00bfcd00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bfd5f0
void* Object_bfd5f0::DeletingDtor(unsigned int flags)
{
    this->~Object_bfd5f0();
    if (flags & 1)
        Free_bfd5f0(this);
    return this;
}
