// Scalar deleting destructor (0x00cba540): run the destructor (0xcb8b20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cba540(void* p);   // 0x00f47380

struct Object_cba540 {
    ~Object_cba540();        // 0x00cb8b20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cba540
void* Object_cba540::DeletingDtor(unsigned int flags)
{
    this->~Object_cba540();
    if (flags & 1)
        Free_cba540(this);
    return this;
}
