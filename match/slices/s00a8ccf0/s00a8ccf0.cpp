// Scalar deleting destructor (0x00a8ccf0): run the destructor (0xa8cb00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a8ccf0(void* p);   // 0x00f47380

struct Object_a8ccf0 {
    ~Object_a8ccf0();        // 0x00a8cb00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a8ccf0
void* Object_a8ccf0::DeletingDtor(unsigned int flags)
{
    this->~Object_a8ccf0();
    if (flags & 1)
        Free_a8ccf0(this);
    return this;
}
