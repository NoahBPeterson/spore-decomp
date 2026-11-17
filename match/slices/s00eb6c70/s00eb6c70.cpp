// Scalar deleting destructor (0x00eb6c70): run the destructor (0xeb6490), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eb6c70(void* p);   // 0x00f47380

struct Object_eb6c70 {
    ~Object_eb6c70();        // 0x00eb6490
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eb6c70
void* Object_eb6c70::DeletingDtor(unsigned int flags)
{
    this->~Object_eb6c70();
    if (flags & 1)
        Free_eb6c70(this);
    return this;
}
