// Scalar deleting destructor (0x00e93d50): run the destructor (0xe93c00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e93d50(void* p);   // 0x00f47380

struct Object_e93d50 {
    ~Object_e93d50();        // 0x00e93c00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e93d50
void* Object_e93d50::DeletingDtor(unsigned int flags)
{
    this->~Object_e93d50();
    if (flags & 1)
        Free_e93d50(this);
    return this;
}
