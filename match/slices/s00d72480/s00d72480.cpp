// Scalar deleting destructor (0x00d72480): run the destructor (0xd79fd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d72480(void* p);   // 0x00f47380

struct Object_d72480 {
    ~Object_d72480();        // 0x00d79fd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d72480
void* Object_d72480::DeletingDtor(unsigned int flags)
{
    this->~Object_d72480();
    if (flags & 1)
        Free_d72480(this);
    return this;
}
