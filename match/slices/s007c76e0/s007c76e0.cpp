// Scalar deleting destructor (0x007c76e0): run the destructor (0x7c74a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7c76e0(void* p);   // 0x00f47380

struct Object_7c76e0 {
    ~Object_7c76e0();        // 0x007c74a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007c76e0
void* Object_7c76e0::DeletingDtor(unsigned int flags)
{
    this->~Object_7c76e0();
    if (flags & 1)
        Free_7c76e0(this);
    return this;
}
