// Scalar deleting destructor (0x00b60300): run the destructor (0xb600a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b60300(void* p);   // 0x00f47380

struct Object_b60300 {
    ~Object_b60300();        // 0x00b600a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b60300
void* Object_b60300::DeletingDtor(unsigned int flags)
{
    this->~Object_b60300();
    if (flags & 1)
        Free_b60300(this);
    return this;
}
