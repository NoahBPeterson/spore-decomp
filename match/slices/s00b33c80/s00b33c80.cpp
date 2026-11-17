// Scalar deleting destructor (0x00b33c80): run the destructor (0xe8eaa0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b33c80(void* p);   // 0x00f47380

struct Object_b33c80 {
    ~Object_b33c80();        // 0x00e8eaa0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b33c80
void* Object_b33c80::DeletingDtor(unsigned int flags)
{
    this->~Object_b33c80();
    if (flags & 1)
        Free_b33c80(this);
    return this;
}
