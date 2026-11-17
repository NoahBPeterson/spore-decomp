// Scalar deleting destructor (0x00c64bd0): run the destructor (0xc63ef0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c64bd0(void* p);   // 0x00f47380

struct Object_c64bd0 {
    ~Object_c64bd0();        // 0x00c63ef0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c64bd0
void* Object_c64bd0::DeletingDtor(unsigned int flags)
{
    this->~Object_c64bd0();
    if (flags & 1)
        Free_c64bd0(this);
    return this;
}
