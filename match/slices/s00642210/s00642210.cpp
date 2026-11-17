// Scalar deleting destructor (0x00642210): run the destructor (0x642190), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_642210(void* p);   // 0x00f47380

struct Object_642210 {
    ~Object_642210();        // 0x00642190
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00642210
void* Object_642210::DeletingDtor(unsigned int flags)
{
    this->~Object_642210();
    if (flags & 1)
        Free_642210(this);
    return this;
}
