// Scalar deleting destructor (0x007d2560): run the destructor (0x7d2490), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7d2560(void* p);   // 0x00f47380

struct Object_7d2560 {
    ~Object_7d2560();        // 0x007d2490
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007d2560
void* Object_7d2560::DeletingDtor(unsigned int flags)
{
    this->~Object_7d2560();
    if (flags & 1)
        Free_7d2560(this);
    return this;
}
