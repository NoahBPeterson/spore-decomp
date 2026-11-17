// Scalar deleting destructor (0x00ad82e0): run the destructor (0xad7470), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ad82e0(void* p);   // 0x00f47380

struct Object_ad82e0 {
    ~Object_ad82e0();        // 0x00ad7470
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ad82e0
void* Object_ad82e0::DeletingDtor(unsigned int flags)
{
    this->~Object_ad82e0();
    if (flags & 1)
        Free_ad82e0(this);
    return this;
}
