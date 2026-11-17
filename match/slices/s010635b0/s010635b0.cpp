// Scalar deleting destructor (0x010635b0): run the destructor (0x1063400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_10635b0(void* p);   // 0x00f47380

struct Object_10635b0 {
    ~Object_10635b0();        // 0x01063400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x010635b0
void* Object_10635b0::DeletingDtor(unsigned int flags)
{
    this->~Object_10635b0();
    if (flags & 1)
        Free_10635b0(this);
    return this;
}
