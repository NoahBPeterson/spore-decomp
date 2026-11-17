// Scalar deleting destructor (0x00f33b30): run the destructor (0xf32b90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f33b30(void* p);   // 0x00f47380

struct Object_f33b30 {
    ~Object_f33b30();        // 0x00f32b90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f33b30
void* Object_f33b30::DeletingDtor(unsigned int flags)
{
    this->~Object_f33b30();
    if (flags & 1)
        Free_f33b30(this);
    return this;
}
