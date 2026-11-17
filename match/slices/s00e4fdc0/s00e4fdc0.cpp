// Scalar deleting destructor (0x00e4fdc0): run the destructor (0xc2f3e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e4fdc0(void* p);   // 0x00f47380

struct Object_e4fdc0 {
    ~Object_e4fdc0();        // 0x00c2f3e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e4fdc0
void* Object_e4fdc0::DeletingDtor(unsigned int flags)
{
    this->~Object_e4fdc0();
    if (flags & 1)
        Free_e4fdc0(this);
    return this;
}
