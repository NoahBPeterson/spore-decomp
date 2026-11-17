// Scalar deleting destructor (0x0103d0f0): run the destructor (0x103d090), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_103d0f0(void* p);   // 0x00f47380

struct Object_103d0f0 {
    ~Object_103d0f0();        // 0x0103d090
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0103d0f0
void* Object_103d0f0::DeletingDtor(unsigned int flags)
{
    this->~Object_103d0f0();
    if (flags & 1)
        Free_103d0f0(this);
    return this;
}
