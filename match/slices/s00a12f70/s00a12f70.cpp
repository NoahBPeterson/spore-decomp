// Scalar deleting destructor (0x00a12f70): run the destructor (0xa12ad0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a12f70(void* p);   // 0x00f47380

struct Object_a12f70 {
    ~Object_a12f70();        // 0x00a12ad0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a12f70
void* Object_a12f70::DeletingDtor(unsigned int flags)
{
    this->~Object_a12f70();
    if (flags & 1)
        Free_a12f70(this);
    return this;
}
