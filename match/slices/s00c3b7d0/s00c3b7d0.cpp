// Scalar deleting destructor (0x00c3b7d0): run the destructor (0xc38c90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c3b7d0(void* p);   // 0x00f47380

struct Object_c3b7d0 {
    ~Object_c3b7d0();        // 0x00c38c90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c3b7d0
void* Object_c3b7d0::DeletingDtor(unsigned int flags)
{
    this->~Object_c3b7d0();
    if (flags & 1)
        Free_c3b7d0(this);
    return this;
}
