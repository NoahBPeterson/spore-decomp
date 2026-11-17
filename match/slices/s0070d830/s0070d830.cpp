// Scalar deleting destructor (0x0070d830): run the destructor (0x70d6d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_70d830(void* p);   // 0x00f47380

struct Object_70d830 {
    ~Object_70d830();        // 0x0070d6d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0070d830
void* Object_70d830::DeletingDtor(unsigned int flags)
{
    this->~Object_70d830();
    if (flags & 1)
        Free_70d830(this);
    return this;
}
