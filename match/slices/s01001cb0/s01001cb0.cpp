// Scalar deleting destructor (0x01001cb0): run the destructor (0x1000bb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1001cb0(void* p);   // 0x00f47380

struct Object_1001cb0 {
    ~Object_1001cb0();        // 0x01000bb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01001cb0
void* Object_1001cb0::DeletingDtor(unsigned int flags)
{
    this->~Object_1001cb0();
    if (flags & 1)
        Free_1001cb0(this);
    return this;
}
