// Scalar deleting destructor (0x00e1f6e0): run the destructor (0xe1f420), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e1f6e0(void* p);   // 0x00f47380

struct Object_e1f6e0 {
    ~Object_e1f6e0();        // 0x00e1f420
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e1f6e0
void* Object_e1f6e0::DeletingDtor(unsigned int flags)
{
    this->~Object_e1f6e0();
    if (flags & 1)
        Free_e1f6e0(this);
    return this;
}
