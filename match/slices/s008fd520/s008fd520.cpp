// Scalar deleting destructor (0x008fd520): run the destructor (0x8fd2e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8fd520(void* p);   // 0x00f47380

struct Object_8fd520 {
    ~Object_8fd520();        // 0x008fd2e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008fd520
void* Object_8fd520::DeletingDtor(unsigned int flags)
{
    this->~Object_8fd520();
    if (flags & 1)
        Free_8fd520(this);
    return this;
}
