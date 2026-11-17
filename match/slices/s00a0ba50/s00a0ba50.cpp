// Scalar deleting destructor (0x00a0ba50): run the destructor (0xa0aaa0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a0ba50(void* p);   // 0x00f47380

struct Object_a0ba50 {
    ~Object_a0ba50();        // 0x00a0aaa0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a0ba50
void* Object_a0ba50::DeletingDtor(unsigned int flags)
{
    this->~Object_a0ba50();
    if (flags & 1)
        Free_a0ba50(this);
    return this;
}
