// Scalar deleting destructor (0x007afec0): run the destructor (0x7ae980), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7afec0(void* p);   // 0x00f47380

struct Object_7afec0 {
    ~Object_7afec0();        // 0x007ae980
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007afec0
void* Object_7afec0::DeletingDtor(unsigned int flags)
{
    this->~Object_7afec0();
    if (flags & 1)
        Free_7afec0(this);
    return this;
}
