// Scalar deleting destructor (0x0062b5a0): run the destructor (0x62b3a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_62b5a0(void* p);   // 0x00f47380

struct Object_62b5a0 {
    ~Object_62b5a0();        // 0x0062b3a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0062b5a0
void* Object_62b5a0::DeletingDtor(unsigned int flags)
{
    this->~Object_62b5a0();
    if (flags & 1)
        Free_62b5a0(this);
    return this;
}
