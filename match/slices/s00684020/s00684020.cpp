// Scalar deleting destructor (0x00684020): run the destructor (0x683f80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_684020(void* p);   // 0x00f47380

struct Object_684020 {
    ~Object_684020();        // 0x00683f80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00684020
void* Object_684020::DeletingDtor(unsigned int flags)
{
    this->~Object_684020();
    if (flags & 1)
        Free_684020(this);
    return this;
}
