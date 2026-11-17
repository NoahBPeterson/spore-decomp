// Scalar deleting destructor (0x00833b80): run the destructor (0x833a80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_833b80(void* p);   // 0x00f47380

struct Object_833b80 {
    ~Object_833b80();        // 0x00833a80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00833b80
void* Object_833b80::DeletingDtor(unsigned int flags)
{
    this->~Object_833b80();
    if (flags & 1)
        Free_833b80(this);
    return this;
}
