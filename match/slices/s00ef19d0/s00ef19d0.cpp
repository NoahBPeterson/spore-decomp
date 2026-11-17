// Scalar deleting destructor (0x00ef19d0): run the destructor (0xef0400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ef19d0(void* p);   // 0x00f47380

struct Object_ef19d0 {
    ~Object_ef19d0();        // 0x00ef0400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ef19d0
void* Object_ef19d0::DeletingDtor(unsigned int flags)
{
    this->~Object_ef19d0();
    if (flags & 1)
        Free_ef19d0(this);
    return this;
}
