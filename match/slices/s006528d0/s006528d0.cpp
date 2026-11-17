// Scalar deleting destructor (0x006528d0): run the destructor (0x651c80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6528d0(void* p);   // 0x00f47380

struct Object_6528d0 {
    ~Object_6528d0();        // 0x00651c80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006528d0
void* Object_6528d0::DeletingDtor(unsigned int flags)
{
    this->~Object_6528d0();
    if (flags & 1)
        Free_6528d0(this);
    return this;
}
