// Scalar deleting destructor (0x00d3c360): run the destructor (0xd3bb10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d3c360(void* p);   // 0x00f47380

struct Object_d3c360 {
    ~Object_d3c360();        // 0x00d3bb10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d3c360
void* Object_d3c360::DeletingDtor(unsigned int flags)
{
    this->~Object_d3c360();
    if (flags & 1)
        Free_d3c360(this);
    return this;
}
