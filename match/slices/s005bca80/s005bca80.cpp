// Scalar deleting destructor (0x005bca80): run the destructor (0x5bc930), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5bca80(void* p);   // 0x00f47380

struct Object_5bca80 {
    ~Object_5bca80();        // 0x005bc930
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005bca80
void* Object_5bca80::DeletingDtor(unsigned int flags)
{
    this->~Object_5bca80();
    if (flags & 1)
        Free_5bca80(this);
    return this;
}
