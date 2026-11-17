// Scalar deleting destructor (0x006f3dd0): run the destructor (0x6f3d50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6f3dd0(void* p);   // 0x00f47380

struct Object_6f3dd0 {
    ~Object_6f3dd0();        // 0x006f3d50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006f3dd0
void* Object_6f3dd0::DeletingDtor(unsigned int flags)
{
    this->~Object_6f3dd0();
    if (flags & 1)
        Free_6f3dd0(this);
    return this;
}
