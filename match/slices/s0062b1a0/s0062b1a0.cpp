// Scalar deleting destructor (0x0062b1a0): run the destructor (0x62b160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_62b1a0(void* p);   // 0x00f47380

struct Object_62b1a0 {
    ~Object_62b1a0();        // 0x0062b160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0062b1a0
void* Object_62b1a0::DeletingDtor(unsigned int flags)
{
    this->~Object_62b1a0();
    if (flags & 1)
        Free_62b1a0(this);
    return this;
}
