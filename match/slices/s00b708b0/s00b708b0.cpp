// Scalar deleting destructor (0x00b708b0): run the destructor (0xb705a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b708b0(void* p);   // 0x00f47380

struct Object_b708b0 {
    ~Object_b708b0();        // 0x00b705a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b708b0
void* Object_b708b0::DeletingDtor(unsigned int flags)
{
    this->~Object_b708b0();
    if (flags & 1)
        Free_b708b0(this);
    return this;
}
