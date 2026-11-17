// Scalar deleting destructor (0x00fe4d40): run the destructor (0xfe49e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fe4d40(void* p);   // 0x00f47380

struct Object_fe4d40 {
    ~Object_fe4d40();        // 0x00fe49e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fe4d40
void* Object_fe4d40::DeletingDtor(unsigned int flags)
{
    this->~Object_fe4d40();
    if (flags & 1)
        Free_fe4d40(this);
    return this;
}
