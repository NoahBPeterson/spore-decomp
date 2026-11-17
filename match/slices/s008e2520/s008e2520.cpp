// Scalar deleting destructor (0x008e2520): run the destructor (0x8e52e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8e2520(void* p);   // 0x00f47380

struct Object_8e2520 {
    ~Object_8e2520();        // 0x008e52e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008e2520
void* Object_8e2520::DeletingDtor(unsigned int flags)
{
    this->~Object_8e2520();
    if (flags & 1)
        Free_8e2520(this);
    return this;
}
