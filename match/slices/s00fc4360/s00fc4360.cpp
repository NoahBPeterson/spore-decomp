// Scalar deleting destructor (0x00fc4360): run the destructor (0xfc2f90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fc4360(void* p);   // 0x00f47380

struct Object_fc4360 {
    ~Object_fc4360();        // 0x00fc2f90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fc4360
void* Object_fc4360::DeletingDtor(unsigned int flags)
{
    this->~Object_fc4360();
    if (flags & 1)
        Free_fc4360(this);
    return this;
}
