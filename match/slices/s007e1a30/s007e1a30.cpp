// Scalar deleting destructor (0x007e1a30): run the destructor (0x83cd90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7e1a30(void* p);   // 0x00f47380

struct Object_7e1a30 {
    ~Object_7e1a30();        // 0x0083cd90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007e1a30
void* Object_7e1a30::DeletingDtor(unsigned int flags)
{
    this->~Object_7e1a30();
    if (flags & 1)
        Free_7e1a30(this);
    return this;
}
