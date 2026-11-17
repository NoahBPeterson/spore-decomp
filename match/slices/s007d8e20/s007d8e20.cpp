// Scalar deleting destructor (0x007d8e20): run the destructor (0x7d8d40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7d8e20(void* p);   // 0x00f47380

struct Object_7d8e20 {
    ~Object_7d8e20();        // 0x007d8d40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007d8e20
void* Object_7d8e20::DeletingDtor(unsigned int flags)
{
    this->~Object_7d8e20();
    if (flags & 1)
        Free_7d8e20(this);
    return this;
}
