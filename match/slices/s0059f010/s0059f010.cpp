// Scalar deleting destructor (0x0059f010): run the destructor (0x59efa0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_59f010(void* p);   // 0x00f47380

struct Object_59f010 {
    ~Object_59f010();        // 0x0059efa0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0059f010
void* Object_59f010::DeletingDtor(unsigned int flags)
{
    this->~Object_59f010();
    if (flags & 1)
        Free_59f010(this);
    return this;
}
