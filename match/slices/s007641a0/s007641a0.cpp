// Scalar deleting destructor (0x007641a0): run the destructor (0x764130), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7641a0(void* p);   // 0x00f47380

struct Object_7641a0 {
    ~Object_7641a0();        // 0x00764130
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007641a0
void* Object_7641a0::DeletingDtor(unsigned int flags)
{
    this->~Object_7641a0();
    if (flags & 1)
        Free_7641a0(this);
    return this;
}
