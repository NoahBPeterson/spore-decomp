// Scalar deleting destructor (0x006a1c80): run the destructor (0x686320), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6a1c80(void* p);   // 0x00f47380

struct Object_6a1c80 {
    ~Object_6a1c80();        // 0x00686320
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006a1c80
void* Object_6a1c80::DeletingDtor(unsigned int flags)
{
    this->~Object_6a1c80();
    if (flags & 1)
        Free_6a1c80(this);
    return this;
}
