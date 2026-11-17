// Scalar deleting destructor (0x00a85db0): run the destructor (0xa85b80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a85db0(void* p);   // 0x00f47380

struct Object_a85db0 {
    ~Object_a85db0();        // 0x00a85b80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a85db0
void* Object_a85db0::DeletingDtor(unsigned int flags)
{
    this->~Object_a85db0();
    if (flags & 1)
        Free_a85db0(this);
    return this;
}
