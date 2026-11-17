// Scalar deleting destructor (0x0068c0b0): run the destructor (0x68bc50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68c0b0(void* p);   // 0x00f47380

struct Object_68c0b0 {
    ~Object_68c0b0();        // 0x0068bc50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068c0b0
void* Object_68c0b0::DeletingDtor(unsigned int flags)
{
    this->~Object_68c0b0();
    if (flags & 1)
        Free_68c0b0(this);
    return this;
}
