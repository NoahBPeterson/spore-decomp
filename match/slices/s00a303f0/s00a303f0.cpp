// Scalar deleting destructor (0x00a303f0): run the destructor (0xa30280), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a303f0(void* p);   // 0x00f47380

struct Object_a303f0 {
    ~Object_a303f0();        // 0x00a30280
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a303f0
void* Object_a303f0::DeletingDtor(unsigned int flags)
{
    this->~Object_a303f0();
    if (flags & 1)
        Free_a303f0(this);
    return this;
}
