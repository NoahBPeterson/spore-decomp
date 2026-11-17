// Scalar deleting destructor (0x007ede90): run the destructor (0x7edc90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7ede90(void* p);   // 0x00f47380

struct Object_7ede90 {
    ~Object_7ede90();        // 0x007edc90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007ede90
void* Object_7ede90::DeletingDtor(unsigned int flags)
{
    this->~Object_7ede90();
    if (flags & 1)
        Free_7ede90(this);
    return this;
}
