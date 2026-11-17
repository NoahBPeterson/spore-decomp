// Scalar deleting destructor (0x005f0ed0): run the destructor (0x5f0e30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5f0ed0(void* p);   // 0x00f47380

struct Object_5f0ed0 {
    ~Object_5f0ed0();        // 0x005f0e30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005f0ed0
void* Object_5f0ed0::DeletingDtor(unsigned int flags)
{
    this->~Object_5f0ed0();
    if (flags & 1)
        Free_5f0ed0(this);
    return this;
}
