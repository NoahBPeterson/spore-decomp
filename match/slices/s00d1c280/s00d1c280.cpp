// Scalar deleting destructor (0x00d1c280): run the destructor (0xd1c200), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d1c280(void* p);   // 0x00f47380

struct Object_d1c280 {
    ~Object_d1c280();        // 0x00d1c200
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d1c280
void* Object_d1c280::DeletingDtor(unsigned int flags)
{
    this->~Object_d1c280();
    if (flags & 1)
        Free_d1c280(this);
    return this;
}
