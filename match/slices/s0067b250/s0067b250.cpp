// Scalar deleting destructor (0x0067b250): run the destructor (0x67b1f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67b250(void* p);   // 0x00f47380

struct Object_67b250 {
    ~Object_67b250();        // 0x0067b1f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067b250
void* Object_67b250::DeletingDtor(unsigned int flags)
{
    this->~Object_67b250();
    if (flags & 1)
        Free_67b250(this);
    return this;
}
