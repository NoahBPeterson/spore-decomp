// Scalar deleting destructor (0x007e10a0): run the destructor (0x7e0f70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7e10a0(void* p);   // 0x00f47380

struct Object_7e10a0 {
    ~Object_7e10a0();        // 0x007e0f70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007e10a0
void* Object_7e10a0::DeletingDtor(unsigned int flags)
{
    this->~Object_7e10a0();
    if (flags & 1)
        Free_7e10a0(this);
    return this;
}
