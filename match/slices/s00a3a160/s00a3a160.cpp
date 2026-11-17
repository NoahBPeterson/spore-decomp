// Scalar deleting destructor (0x00a3a160): run the destructor (0xa3a0e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a3a160(void* p);   // 0x00f47380

struct Object_a3a160 {
    ~Object_a3a160();        // 0x00a3a0e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a3a160
void* Object_a3a160::DeletingDtor(unsigned int flags)
{
    this->~Object_a3a160();
    if (flags & 1)
        Free_a3a160(this);
    return this;
}
