// Scalar deleting destructor (0x00698010): run the destructor (0x697ee0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_698010(void* p);   // 0x00f47380

struct Object_698010 {
    ~Object_698010();        // 0x00697ee0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00698010
void* Object_698010::DeletingDtor(unsigned int flags)
{
    this->~Object_698010();
    if (flags & 1)
        Free_698010(this);
    return this;
}
