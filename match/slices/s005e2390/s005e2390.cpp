// Scalar deleting destructor (0x005e2390): run the destructor (0x5e2280), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5e2390(void* p);   // 0x00f47380

struct Object_5e2390 {
    ~Object_5e2390();        // 0x005e2280
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005e2390
void* Object_5e2390::DeletingDtor(unsigned int flags)
{
    this->~Object_5e2390();
    if (flags & 1)
        Free_5e2390(this);
    return this;
}
