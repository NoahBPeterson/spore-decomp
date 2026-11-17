// Scalar deleting destructor (0x00c9dd30): run the destructor (0xc9d3b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c9dd30(void* p);   // 0x00f47380

struct Object_c9dd30 {
    ~Object_c9dd30();        // 0x00c9d3b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c9dd30
void* Object_c9dd30::DeletingDtor(unsigned int flags)
{
    this->~Object_c9dd30();
    if (flags & 1)
        Free_c9dd30(this);
    return this;
}
