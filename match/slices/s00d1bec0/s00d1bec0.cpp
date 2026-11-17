// Scalar deleting destructor (0x00d1bec0): run the destructor (0xd1bcc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d1bec0(void* p);   // 0x00f47380

struct Object_d1bec0 {
    ~Object_d1bec0();        // 0x00d1bcc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d1bec0
void* Object_d1bec0::DeletingDtor(unsigned int flags)
{
    this->~Object_d1bec0();
    if (flags & 1)
        Free_d1bec0(this);
    return this;
}
