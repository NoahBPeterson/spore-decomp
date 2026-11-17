// Scalar deleting destructor (0x005f0b20): run the destructor (0x5f07e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5f0b20(void* p);   // 0x00f47380

struct Object_5f0b20 {
    ~Object_5f0b20();        // 0x005f07e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005f0b20
void* Object_5f0b20::DeletingDtor(unsigned int flags)
{
    this->~Object_5f0b20();
    if (flags & 1)
        Free_5f0b20(this);
    return this;
}
