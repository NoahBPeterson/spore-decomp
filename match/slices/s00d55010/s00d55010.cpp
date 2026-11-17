// Scalar deleting destructor (0x00d55010): run the destructor (0xd54e50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d55010(void* p);   // 0x00f47380

struct Object_d55010 {
    ~Object_d55010();        // 0x00d54e50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d55010
void* Object_d55010::DeletingDtor(unsigned int flags)
{
    this->~Object_d55010();
    if (flags & 1)
        Free_d55010(this);
    return this;
}
