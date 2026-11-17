// Scalar deleting destructor (0x00e313a0): run the destructor (0xe31220), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e313a0(void* p);   // 0x00f47380

struct Object_e313a0 {
    ~Object_e313a0();        // 0x00e31220
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e313a0
void* Object_e313a0::DeletingDtor(unsigned int flags)
{
    this->~Object_e313a0();
    if (flags & 1)
        Free_e313a0(this);
    return this;
}
