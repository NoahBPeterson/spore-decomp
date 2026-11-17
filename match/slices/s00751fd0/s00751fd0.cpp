// Scalar deleting destructor (0x00751fd0): run the destructor (0x7503a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_751fd0(void* p);   // 0x00f47380

struct Object_751fd0 {
    ~Object_751fd0();        // 0x007503a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00751fd0
void* Object_751fd0::DeletingDtor(unsigned int flags)
{
    this->~Object_751fd0();
    if (flags & 1)
        Free_751fd0(this);
    return this;
}
