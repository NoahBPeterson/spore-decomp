// Scalar deleting destructor (0x007824c0): run the destructor (0x7821b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7824c0(void* p);   // 0x00f47380

struct Object_7824c0 {
    ~Object_7824c0();        // 0x007821b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007824c0
void* Object_7824c0::DeletingDtor(unsigned int flags)
{
    this->~Object_7824c0();
    if (flags & 1)
        Free_7824c0(this);
    return this;
}
