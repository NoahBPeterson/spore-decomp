// Scalar deleting destructor (0x006ac750): run the destructor (0x6ac6f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6ac750(void* p);   // 0x00f47380

struct Object_6ac750 {
    ~Object_6ac750();        // 0x006ac6f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ac750
void* Object_6ac750::DeletingDtor(unsigned int flags)
{
    this->~Object_6ac750();
    if (flags & 1)
        Free_6ac750(this);
    return this;
}
