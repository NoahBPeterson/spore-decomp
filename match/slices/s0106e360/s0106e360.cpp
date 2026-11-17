// Scalar deleting destructor (0x0106e360): run the destructor (0x106db90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_106e360(void* p);   // 0x00f47380

struct Object_106e360 {
    ~Object_106e360();        // 0x0106db90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0106e360
void* Object_106e360::DeletingDtor(unsigned int flags)
{
    this->~Object_106e360();
    if (flags & 1)
        Free_106e360(this);
    return this;
}
