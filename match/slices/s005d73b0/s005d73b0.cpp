// Scalar deleting destructor (0x005d73b0): run the destructor (0x5d7350), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5d73b0(void* p);   // 0x00f47380

struct Object_5d73b0 {
    ~Object_5d73b0();        // 0x005d7350
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005d73b0
void* Object_5d73b0::DeletingDtor(unsigned int flags)
{
    this->~Object_5d73b0();
    if (flags & 1)
        Free_5d73b0(this);
    return this;
}
