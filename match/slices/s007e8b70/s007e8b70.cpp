// Scalar deleting destructor (0x007e8b70): run the destructor (0x7e78d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7e8b70(void* p);   // 0x00f47380

struct Object_7e8b70 {
    ~Object_7e8b70();        // 0x007e78d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007e8b70
void* Object_7e8b70::DeletingDtor(unsigned int flags)
{
    this->~Object_7e8b70();
    if (flags & 1)
        Free_7e8b70(this);
    return this;
}
