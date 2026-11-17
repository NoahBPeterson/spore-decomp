// Scalar deleting destructor (0x00a6e300): run the destructor (0xa6db40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a6e300(void* p);   // 0x00f47380

struct Object_a6e300 {
    ~Object_a6e300();        // 0x00a6db40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a6e300
void* Object_a6e300::DeletingDtor(unsigned int flags)
{
    this->~Object_a6e300();
    if (flags & 1)
        Free_a6e300(this);
    return this;
}
