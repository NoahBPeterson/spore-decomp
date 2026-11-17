// Scalar deleting destructor (0x006ae3b0): run the destructor (0x6ae120), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6ae3b0(void* p);   // 0x00f47380

struct Object_6ae3b0 {
    ~Object_6ae3b0();        // 0x006ae120
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ae3b0
void* Object_6ae3b0::DeletingDtor(unsigned int flags)
{
    this->~Object_6ae3b0();
    if (flags & 1)
        Free_6ae3b0(this);
    return this;
}
