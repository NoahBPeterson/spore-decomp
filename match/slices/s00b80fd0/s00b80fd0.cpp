// Scalar deleting destructor (0x00b80fd0): run the destructor (0xb80d30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b80fd0(void* p);   // 0x00f47380

struct Object_b80fd0 {
    ~Object_b80fd0();        // 0x00b80d30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b80fd0
void* Object_b80fd0::DeletingDtor(unsigned int flags)
{
    this->~Object_b80fd0();
    if (flags & 1)
        Free_b80fd0(this);
    return this;
}
