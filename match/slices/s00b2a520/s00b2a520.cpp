// Scalar deleting destructor (0x00b2a520): run the destructor (0xf8fa90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b2a520(void* p);   // 0x00f47380

struct Object_b2a520 {
    ~Object_b2a520();        // 0x00f8fa90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b2a520
void* Object_b2a520::DeletingDtor(unsigned int flags)
{
    this->~Object_b2a520();
    if (flags & 1)
        Free_b2a520(this);
    return this;
}
