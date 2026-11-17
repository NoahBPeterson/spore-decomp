// Scalar deleting destructor (0x00a0a000): run the destructor (0xa09f90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a0a000(void* p);   // 0x00f47380

struct Object_a0a000 {
    ~Object_a0a000();        // 0x00a09f90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a0a000
void* Object_a0a000::DeletingDtor(unsigned int flags)
{
    this->~Object_a0a000();
    if (flags & 1)
        Free_a0a000(this);
    return this;
}
