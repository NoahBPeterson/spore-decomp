// Scalar deleting destructor (0x005c6590): run the destructor (0x5c6530), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c6590(void* p);   // 0x00f47380

struct Object_5c6590 {
    ~Object_5c6590();        // 0x005c6530
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c6590
void* Object_5c6590::DeletingDtor(unsigned int flags)
{
    this->~Object_5c6590();
    if (flags & 1)
        Free_5c6590(this);
    return this;
}
