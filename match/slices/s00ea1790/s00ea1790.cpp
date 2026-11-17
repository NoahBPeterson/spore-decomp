// Scalar deleting destructor (0x00ea1790): run the destructor (0xea1470), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea1790(void* p);   // 0x00f47380

struct Object_ea1790 {
    ~Object_ea1790();        // 0x00ea1470
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea1790
void* Object_ea1790::DeletingDtor(unsigned int flags)
{
    this->~Object_ea1790();
    if (flags & 1)
        Free_ea1790(this);
    return this;
}
