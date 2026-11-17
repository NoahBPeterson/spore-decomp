// Scalar deleting destructor (0x005e0910): run the destructor (0x5e0440), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5e0910(void* p);   // 0x00f47380

struct Object_5e0910 {
    ~Object_5e0910();        // 0x005e0440
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005e0910
void* Object_5e0910::DeletingDtor(unsigned int flags)
{
    this->~Object_5e0910();
    if (flags & 1)
        Free_5e0910(this);
    return this;
}
