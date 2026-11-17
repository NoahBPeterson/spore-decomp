// Scalar deleting destructor (0x00bed1e0): run the destructor (0xbec890), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bed1e0(void* p);   // 0x00f47380

struct Object_bed1e0 {
    ~Object_bed1e0();        // 0x00bec890
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bed1e0
void* Object_bed1e0::DeletingDtor(unsigned int flags)
{
    this->~Object_bed1e0();
    if (flags & 1)
        Free_bed1e0(this);
    return this;
}
