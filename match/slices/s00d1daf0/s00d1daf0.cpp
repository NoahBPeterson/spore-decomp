// Scalar deleting destructor (0x00d1daf0): run the destructor (0xd1da60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d1daf0(void* p);   // 0x00f47380

struct Object_d1daf0 {
    ~Object_d1daf0();        // 0x00d1da60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d1daf0
void* Object_d1daf0::DeletingDtor(unsigned int flags)
{
    this->~Object_d1daf0();
    if (flags & 1)
        Free_d1daf0(this);
    return this;
}
