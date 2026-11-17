// Scalar deleting destructor (0x00924150): run the destructor (0x923f90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_924150(void* p);   // 0x00f47380

struct Object_924150 {
    ~Object_924150();        // 0x00923f90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00924150
void* Object_924150::DeletingDtor(unsigned int flags)
{
    this->~Object_924150();
    if (flags & 1)
        Free_924150(this);
    return this;
}
