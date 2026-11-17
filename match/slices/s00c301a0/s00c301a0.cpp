// Scalar deleting destructor (0x00c301a0): run the destructor (0xc2f9c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c301a0(void* p);   // 0x00f47380

struct Object_c301a0 {
    ~Object_c301a0();        // 0x00c2f9c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c301a0
void* Object_c301a0::DeletingDtor(unsigned int flags)
{
    this->~Object_c301a0();
    if (flags & 1)
        Free_c301a0(this);
    return this;
}
