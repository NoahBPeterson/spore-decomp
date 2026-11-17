// Scalar deleting destructor (0x005ccc70): run the destructor (0x5ccc00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5ccc70(void* p);   // 0x00f47380

struct Object_5ccc70 {
    ~Object_5ccc70();        // 0x005ccc00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005ccc70
void* Object_5ccc70::DeletingDtor(unsigned int flags)
{
    this->~Object_5ccc70();
    if (flags & 1)
        Free_5ccc70(this);
    return this;
}
