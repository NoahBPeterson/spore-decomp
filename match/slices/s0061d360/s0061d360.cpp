// Scalar deleting destructor (0x0061d360): run the destructor (0x61d240), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_61d360(void* p);   // 0x00f47380

struct Object_61d360 {
    ~Object_61d360();        // 0x0061d240
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0061d360
void* Object_61d360::DeletingDtor(unsigned int flags)
{
    this->~Object_61d360();
    if (flags & 1)
        Free_61d360(this);
    return this;
}
