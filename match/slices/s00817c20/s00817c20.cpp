// Scalar deleting destructor (0x00817c20): run the destructor (0x817b00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_817c20(void* p);   // 0x00f47380

struct Object_817c20 {
    ~Object_817c20();        // 0x00817b00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00817c20
void* Object_817c20::DeletingDtor(unsigned int flags)
{
    this->~Object_817c20();
    if (flags & 1)
        Free_817c20(this);
    return this;
}
