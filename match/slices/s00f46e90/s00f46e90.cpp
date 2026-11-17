// Scalar deleting destructor (0x00f46e90): run the destructor (0xf46e30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f46e90(void* p);   // 0x00f47380

struct Object_f46e90 {
    ~Object_f46e90();        // 0x00f46e30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f46e90
void* Object_f46e90::DeletingDtor(unsigned int flags)
{
    this->~Object_f46e90();
    if (flags & 1)
        Free_f46e90(this);
    return this;
}
