// Scalar deleting destructor (0x007f9210): run the destructor (0x7f8c20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7f9210(void* p);   // 0x00f47380

struct Object_7f9210 {
    ~Object_7f9210();        // 0x007f8c20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007f9210
void* Object_7f9210::DeletingDtor(unsigned int flags)
{
    this->~Object_7f9210();
    if (flags & 1)
        Free_7f9210(this);
    return this;
}
