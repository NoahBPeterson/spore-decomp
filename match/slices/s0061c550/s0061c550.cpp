// Scalar deleting destructor (0x0061c550): run the destructor (0x61bf50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_61c550(void* p);   // 0x00f47380

struct Object_61c550 {
    ~Object_61c550();        // 0x0061bf50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0061c550
void* Object_61c550::DeletingDtor(unsigned int flags)
{
    this->~Object_61c550();
    if (flags & 1)
        Free_61c550(this);
    return this;
}
