// Scalar deleting destructor (0x0104e2d0): run the destructor (0x104c910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_104e2d0(void* p);   // 0x00f47380

struct Object_104e2d0 {
    ~Object_104e2d0();        // 0x0104c910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0104e2d0
void* Object_104e2d0::DeletingDtor(unsigned int flags)
{
    this->~Object_104e2d0();
    if (flags & 1)
        Free_104e2d0(this);
    return this;
}
