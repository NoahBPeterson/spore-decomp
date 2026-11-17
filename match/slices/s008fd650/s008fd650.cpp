// Scalar deleting destructor (0x008fd650): run the destructor (0x8fd3d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8fd650(void* p);   // 0x00f47380

struct Object_8fd650 {
    ~Object_8fd650();        // 0x008fd3d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008fd650
void* Object_8fd650::DeletingDtor(unsigned int flags)
{
    this->~Object_8fd650();
    if (flags & 1)
        Free_8fd650(this);
    return this;
}
