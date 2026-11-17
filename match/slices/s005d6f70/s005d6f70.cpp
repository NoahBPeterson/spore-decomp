// Scalar deleting destructor (0x005d6f70): run the destructor (0x5d6850), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5d6f70(void* p);   // 0x00f47380

struct Object_5d6f70 {
    ~Object_5d6f70();        // 0x005d6850
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005d6f70
void* Object_5d6f70::DeletingDtor(unsigned int flags)
{
    this->~Object_5d6f70();
    if (flags & 1)
        Free_5d6f70(this);
    return this;
}
