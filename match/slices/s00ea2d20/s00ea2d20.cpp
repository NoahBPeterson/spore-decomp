// Scalar deleting destructor (0x00ea2d20): run the destructor (0xea29b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea2d20(void* p);   // 0x00f47380

struct Object_ea2d20 {
    ~Object_ea2d20();        // 0x00ea29b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea2d20
void* Object_ea2d20::DeletingDtor(unsigned int flags)
{
    this->~Object_ea2d20();
    if (flags & 1)
        Free_ea2d20(this);
    return this;
}
