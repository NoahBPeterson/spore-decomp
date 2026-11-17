// Scalar deleting destructor (0x00c33ca0): run the destructor (0xc33410), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c33ca0(void* p);   // 0x00f47380

struct Object_c33ca0 {
    ~Object_c33ca0();        // 0x00c33410
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c33ca0
void* Object_c33ca0::DeletingDtor(unsigned int flags)
{
    this->~Object_c33ca0();
    if (flags & 1)
        Free_c33ca0(this);
    return this;
}
