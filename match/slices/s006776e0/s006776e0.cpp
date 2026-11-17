// Scalar deleting destructor (0x006776e0): run the destructor (0x677670), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6776e0(void* p);   // 0x00f47380

struct Object_6776e0 {
    ~Object_6776e0();        // 0x00677670
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006776e0
void* Object_6776e0::DeletingDtor(unsigned int flags)
{
    this->~Object_6776e0();
    if (flags & 1)
        Free_6776e0(this);
    return this;
}
