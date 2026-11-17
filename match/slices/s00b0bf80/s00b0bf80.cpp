// Scalar deleting destructor (0x00b0bf80): run the destructor (0xb0bb50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b0bf80(void* p);   // 0x00f47380

struct Object_b0bf80 {
    ~Object_b0bf80();        // 0x00b0bb50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b0bf80
void* Object_b0bf80::DeletingDtor(unsigned int flags)
{
    this->~Object_b0bf80();
    if (flags & 1)
        Free_b0bf80(this);
    return this;
}
