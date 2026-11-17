// Scalar deleting destructor (0x0075fb70): run the destructor (0x75f7e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_75fb70(void* p);   // 0x00f47380

struct Object_75fb70 {
    ~Object_75fb70();        // 0x0075f7e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0075fb70
void* Object_75fb70::DeletingDtor(unsigned int flags)
{
    this->~Object_75fb70();
    if (flags & 1)
        Free_75fb70(this);
    return this;
}
