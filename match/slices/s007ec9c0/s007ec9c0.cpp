// Scalar deleting destructor (0x007ec9c0): run the destructor (0x7ec660), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7ec9c0(void* p);   // 0x00f47380

struct Object_7ec9c0 {
    ~Object_7ec9c0();        // 0x007ec660
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007ec9c0
void* Object_7ec9c0::DeletingDtor(unsigned int flags)
{
    this->~Object_7ec9c0();
    if (flags & 1)
        Free_7ec9c0(this);
    return this;
}
