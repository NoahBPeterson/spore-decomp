// Scalar deleting destructor (0x00da5010): run the destructor (0xd9f010), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_da5010(void* p);   // 0x00f47380

struct Object_da5010 {
    ~Object_da5010();        // 0x00d9f010
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00da5010
void* Object_da5010::DeletingDtor(unsigned int flags)
{
    this->~Object_da5010();
    if (flags & 1)
        Free_da5010(this);
    return this;
}
