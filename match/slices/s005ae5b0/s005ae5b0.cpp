// Scalar deleting destructor (0x005ae5b0): run the destructor (0x5ae1b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5ae5b0(void* p);   // 0x00f47380

struct Object_5ae5b0 {
    ~Object_5ae5b0();        // 0x005ae1b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005ae5b0
void* Object_5ae5b0::DeletingDtor(unsigned int flags)
{
    this->~Object_5ae5b0();
    if (flags & 1)
        Free_5ae5b0(this);
    return this;
}
