// Scalar deleting destructor (0x005e16a0): run the destructor (0x5e0d80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5e16a0(void* p);   // 0x00f47380

struct Object_5e16a0 {
    ~Object_5e16a0();        // 0x005e0d80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005e16a0
void* Object_5e16a0::DeletingDtor(unsigned int flags)
{
    this->~Object_5e16a0();
    if (flags & 1)
        Free_5e16a0(this);
    return this;
}
